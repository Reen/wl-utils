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

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
namespace fs = boost::filesystem;


#include <boost/xpressive/xpressive.hpp>

#include <tclap/CmdLine.h>
#include "exact_dos.h"
#include "wl_exceptions.h"

typedef mpfr::Real float_type;



class ErrorTask {
public:
  typedef std::pair<float_type,float_type> dos_type;
  typedef std::map<float_type,dos_type> data_type;
private:
  float_type sigma_;
  float_type epsilon_;
  float_type L_;
  ExactDos<float_type> omega_;
	std::string working_directory_;

  std::string get_timestep_(const std::string& comment) {
    std::string timestep;
    // extract timestep from comment
    using namespace boost::xpressive;
    sregex time_rex = sregex::compile("timestep\\s+(\\d+)");
    smatch what;
    if (regex_search(comment, what, time_rex)) {
      timestep = what[1];
    } else {
      std::cout << "WARNING: Can't determin timestep!" << std::endl;
    }
    return timestep;
  }

  float_type get_diff_(data_type& data) {
    float_type diff(0);
    float_type eps(0.01);
    std::size_t i(0);
    for(data_type::iterator it = data.begin(); it != data.end(); ++it) {
      if(it->first >= eps || it->first < -eps) {
        //std::cout << omega[it->first] << " " << it->second.first << "\n";
        ++i;
        diff += (omega_[it->first] - it->second.first);
      }
    }
    diff/=i;
    return diff;
  }

  bool read_file_(const std::string &input_file, data_type& data, std::string& comment) {
    using namespace boost::xpressive;
    sregex gz_rex = sregex::compile("\\.gz$");
    sregex bz2_rex = sregex::compile("\\.bz2$");
    smatch what;
    io::filtering_istream in;
    if (regex_search(input_file, what, gz_rex)) {
      in.push(io::gzip_decompressor());
    }
    if (regex_search(input_file, what, bz2_rex)) {
      in.push(io::bzip2_decompressor());
    }
    in.push(io::file_source(input_file, std::ios::in));

    if(!in.good()) {
      throw file_not_found(input_file);
      return false;
    }

    std::string line;
    std::ostringstream cmt;
    while (std::getline(in,line)) {
      if (line[0] != '#' && line.size() > 0) {
        std::istringstream lin(line);
        float_type x;
        float_type t1,t2,t3;
        lin >> t1;
        lin >> x;
        lin >> t2;
        t3 = mpfr::Exp(t2);
        dos_type d(t2,t3);
        data[x] = d;
      } else {
        cmt << line << "\n";
      }
    }
    comment = cmt.str();
    return true;
  }

public:
  ErrorTask(double sigma, double epsilon, double L,
            std::string working_dir)
      : sigma_(sigma), epsilon_(epsilon), L_(L),
        omega_(epsilon, sigma, L), working_directory_(working_dir)
  {
  }

  ~ErrorTask() {}

  std::string process_file(std::string input_file, bool output_data, bool batch = false) {
    data_type data;
    std::string comment;
    if(!read_file_(input_file, data, comment)) {
      throw file_not_found(input_file);
      //std::cout << "Can't find file '" << input_file << "'" << std::endl;
      //return "Error in file " + input_file + "\n";
    }
    float_type diff = get_diff_(data);
    std::ostringstream out, short_out;
    std::string timestep = get_timestep_(comment);

    out << "# offset " << diff << std::endl;
    out << comment;

    float_type sum(0);
    float_type tmp;
    float_type eps(0.01);
    std::size_t i(0);
    for (data_type::iterator it = data.begin(); it != data.end(); ++it) {
      tmp = mpfr::Abs((mpfr::Exp((it->second.first+diff)) - omega_(it->first))
                /omega_(it->first));
      if (it->first >= eps || it->first < -eps) {
        i++;
        sum += tmp;
      }
      out << it->first << " " << omega_[it->first] << " "
          << (it->second.first+diff) << " " << tmp << "\n";
    }
    sum /= i;

    if (output_data) {
      if (true /*batch*/) {
        using namespace boost::xpressive;
        sregex fn_rex = sregex::compile("(\\.dat(?:\\.gz)?(?:\\.bz2)?)");
        //std::string err_file = working_directory_ + '/' +
        //                       regex_replace(input_file, fn_rex, ".err");
        std::string err_file = regex_replace(input_file, fn_rex, ".err");
        std::cout << "Processing: " << err_file << std::endl;
        std::ofstream err_out(err_file.c_str());
        if(!err_out.good()) {
          throw file_not_found(err_file);
        } else {
          err_out << "# mean error " << sum << "\n" << out.str();
        }
      }/* else {
        std::cout << "# mean error " << sum << "\n" << out.str();
      }*/
    }
    short_out << std::setw(20) << std::right << timestep
              << std::setw(20) << std::right << sum << "\n";
    return short_out.str();
  }
};

int main (int argc, char *argv[])
{
  std::string input_file, output_file;
  bool output_data = false;
  try
  {
    TCLAP::CmdLine cmd(argv[0], ' ', "0.1");
    TCLAP::UnlabeledValueArg<std::string> fileArg("file","File containing the density of states",true,"","file", cmd);
    TCLAP::ValueArg<std::string> outFileArg("", "outfile","Where output should be written to",false,"","file", cmd);
    TCLAP::SwitchArg printArg("", "output", "Turn on data output, which will be written to file.", cmd);

    cmd.parse( argc, argv );
    input_file = fileArg.getValue();
    output_file = outFileArg.getValue();
    output_data = printArg.getValue();
  }
  catch (TCLAP::ArgException &e)  // catch any exceptions
  {
    std::cerr << "error: "   << e.error()
              << " for arg " << e.argId() << std::endl;
    return -1;
  }

  if (fs::is_regular_file(input_file)) {
    fs::path full_path(input_file);
    ErrorTask t(1.0, 1.0, 5.0, full_path.directory_string());
    std::cout << t.process_file(input_file, output_data);
    return 0;
  }

  fs::path full_path( fs::initial_path<fs::path>() );
  if (fs::is_directory(input_file) && input_file != ".") {
    char resolved_path[1000];
    realpath(input_file.c_str(), resolved_path);
    full_path = fs::system_complete( fs::path(resolved_path) );
  }

  ErrorTask t(1.0, 1.0, 5.0, full_path.directory_string());

  if(output_file.size() == 0) {
    output_file = "error.dat";
    std::err << "You did not provide an outfile! Assuming error.dat!" << std::endl;
  }
  using namespace boost::xpressive;
  sregex fn_rex = sregex::compile("(?:dos3_|dos\\.).+\\.dat(?:\\.gz|\\.bz2)?");
  if (fs::is_directory(full_path)) {
    fs::directory_iterator end_iter;
    std::cout << "processing direcotry "
              << full_path.directory_string() << "\n"
              << "writing output to "
              << output_file << std::endl;
    output_file = full_path.directory_string()+'/'+output_file;
    std::cout << output_file << std::endl;
    std::ofstream out(output_file.c_str());
    for (fs::directory_iterator dir_iter(full_path);
         dir_iter != end_iter;
         ++dir_iter)
    {
      if (fs::is_regular_file(dir_iter->status())) {
        smatch what;
        if (regex_match(dir_iter->path().filename(), what, fn_rex)) {
          out << t.process_file(dir_iter->path().string(), output_data, true);
        }
      }
    }
  }
  return 0;
}