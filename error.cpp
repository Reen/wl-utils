//#include <mdefs.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>


#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
namespace io = boost::iostreams;

#include <boost/xpressive/xpressive.hpp>

#include <tclap/CmdLine.h>
#include "exact_dos.h"



int main (int argc, char *argv[])
{
  std::string input_file;
  bool noprint = false;
  try
  {
    TCLAP::CmdLine cmd(argv[0], ' ', "0.1");
    TCLAP::UnlabeledValueArg<std::string> fileArg("file1","File containing the density of states",true,"","file", cmd);
    TCLAP::SwitchArg printArg("", "noprint", "Turn off data output. Only print error.", cmd);

    cmd.parse( argc, argv );
    input_file = fileArg.getValue();
    noprint = printArg.getValue();
  }
  catch (TCLAP::ArgException &e)  // catch any exceptions
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    return -1;
  }

  typedef mpfr::Real float_type;
  mpfr::Library.setPrecision( mpfr::Precision( 200 ) );
  float_type Sigma = 1.0;
  float_type Epsilon = 1.0;
  float_type L = 5.0;

  typedef std::pair<float_type,float_type> dos_type;
  typedef std::map<float_type,dos_type> data_type;
  data_type data;
  std::string comment;
  {
    using namespace boost::xpressive;
    sregex gz_rex = sregex::compile("\\.gz$");
    sregex bz2_rex = sregex::compile("\\.bz2$");
    smatch what;
    io::filtering_istream in;
    if (regex_match(input_file, what, gz_rex)) {
      in.push(io::gzip_decompressor());
    }
    if (regex_match(input_file, what, bz2_rex)) {
      in.push(io::bzip2_decompressor());
    }
    in.push(io::file_source(input_file, std::ios::in));

    //std::ifstream in(input_file.c_str());
    std::string line;
    std::ostringstream cmt(comment);
    while (std::getline(in,line)) {
      if (line[0] != '#' && line.size() > 0) {
        std::istringstream lin(line);
        float_type x;
//        dos_type y;
        float_type t1,t2,t3;
        lin >> t1;
        lin >> x;
        lin >> t2;
        t3 = Exp(t2);
        dos_type d(t2,t3);
        data[x] = d;
      } else {
        cmt << line << "\n";
      }
    }
  }

  ExactDos<float_type> omega(Epsilon, Sigma, L);

  float_type diff(0);
  float_type eps(0.01);
  std::size_t i(0);
  for(data_type::iterator it = data.begin(); it != data.end(); ++it) {
    if(it->first >= eps || it->first < -eps) {
      //std::cout << it->first << "\n";
      ++i;
      diff += (omega[it->first] - it->second.first);
    }
  }
  diff/=i;

  std::ostringstream out;

  out << comment;
  out << "# offset " << diff << std::endl;

  float_type sum(0);
  float_type tmp;
  for (data_type::iterator it = data.begin(); it != data.end(); ++it) {
    tmp = Abs((Exp((it->second.first+diff)) - omega(it->first))
              /omega(it->first));
    if (it->first >= eps || it->first < -eps) {
      sum += tmp;
    }
    out << it->first << " " << omega[it->first] << " "
        << (it->second.first+diff) << " " << tmp << "\n";
  }
  sum /= i;
  if (noprint) {
    std::cout << sum << "\n";
  } else {
    std::cout << "# mean error " << sum << "\n" << out.str();
  }
  return 0;
}