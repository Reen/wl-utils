#include <iostream>
#include <iomanip>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/foreach.hpp>

#include <boost/program_options.hpp>

#include "misc.h"
#include "rootfinding.hpp"

namespace po = boost::program_options;
namespace io = boost::iostreams;

struct Point {
  int N;
  double E;
  double dos;
  double sl;
};

class PhaseDiagram {
public:
  std::vector<Point> points;
  double temperature;
  double volume;
  int n0;
  double sum_vapor;
  double sum_liquid;
  std::string comment;
  double offset;
  double Tmin;
  double Tmax;
  double dT;
  double mu_min;
  double mu_max;

  PhaseDiagram(double volume_, int n0_, double tmin, double tmax, double dt, double mumin, double mumax)
   : volume(volume_), n0(n0_), Tmin(tmin), Tmax(tmax), dT(dt), mu_min(mumin), mu_max(mumax)
  {}

  void read(std::string file) {
    // open input ifle
    io::filtering_istream fin;
    appendDecompressor(fin, file);
    fin.push(io::file_source(file, std::ios::in));
    std::string line;
    std::ostringstream cmt(comment);
    while(getline(fin,line)) {
      if(line[0] != '#' && line.size() > 0) {
        std::istringstream lin(line);
        Point p;
        lin >> p.N;
        lin >> p.E;
        lin >> p.dos;
        points.push_back(p);
      } else {
        cmt << line << "\n";
      }
    }
    comment = cmt.str();
  }

  double operator()(double mu) {
    using namespace std;
    static int i = 0;
    int out = 0;
    sum_vapor = 0.0;
    sum_liquid = 0.0;

    BOOST_FOREACH( Point& p, points)
    {
      double sl = offset + p.dos + (-p.E+p.N*mu)/temperature;
      p.sl = sl;
      if(sl < -300) {
        out++;
        continue;
      }
      double summand = exp(sl);
      if(p.N <= n0) {
        sum_vapor += summand;
      } else {
        sum_liquid += summand;
      }
    }
    double diff = sum_vapor-sum_liquid;
    cout << setprecision(12) << left << setw(7) << i++
      << right << setw(20) << sum_vapor
      << right << setw(20) << sum_liquid
      << right << setw(20) << diff
      << setprecision(16) << right << setw(30) << mu
      << right << setw(8)  << out
      << endl;
    return diff;
  }

  void write(std::string file, bool do_vl) {
    // open output file
    std::ofstream fout(file.c_str());
    fout << comment;
    // calculate the phase diagram at some points
    std::map<double,double> phase_diag;
    for(double t = Tmin; t <= Tmax; t+= dT) {
      temperature = t;
      std::cout << "Temperature: " << t << std::endl;
      RootFinding::BrentRootFinder brf(*this, 300, 0.0000001);
      double mu = brf.solve(mu_min,mu_max,false);

      if(do_vl){
        using namespace std;
        stringstream fn;
        fn << "svl_" << temperature << ".dat";
        ofstream svlout(fn.str().c_str());
        svlout << setprecision(12);
        BOOST_FOREACH( Point& p, points)
        {
          svlout << right << setw(20) << p.N << right << setw(20) << p.E << right << setw(20) << p.sl << "\n";
        }
      }

      double sum_n_vapor = 0.0;
      double sum_n_liquid = 0.0;
      double dummy = (*this)(mu);
      BOOST_FOREACH( Point& p, points)
      {
        if(p.sl < -300) continue;
        double summand = p.N * exp(p.sl);
        if(p.N <= n0) {
          sum_n_vapor += summand;
        } else {
          sum_n_liquid += summand;
        }
      }
      phase_diag[(sum_n_vapor/(volume*sum_vapor))] = t;
      phase_diag[(sum_n_liquid/(volume*sum_liquid))] = t;
    }
    for(std::map<double,double>::iterator it = phase_diag.begin(); it != phase_diag.end(); ++it) {
      fout
      << std::setw(15) << std::right << it->first
      << std::setw(20) << std::right << it->second << std::endl;
    }
  }
};

int main (int argc, char *argv[])
{
  using namespace boost::numeric::ublas;
  using namespace std;

  double Tmin, Tmax, volume, offset, mu_min, mu_max, dT;
  int n0;
  std::string out_file(""), in_file("");
  bool do_vl;

  po::options_description desc("Options");
  desc.add_options()
    ("help",                                  "outputs this message")
    ("volume,V",   po::value<double>(&volume)->default_value(125),   "Volume")
    ("output,o",   po::value<std::string>(&out_file),                "Output to file")
    ("input-file", po::value<std::string>(),                         "Input file")
    ("n0,n",       po::value<int>(&n0)->default_value(35),           "N0")
    ("offset",     po::value<double>(&offset)->default_value(0.0),   "offset")
    ("Tmin",       po::value<double>(&Tmin)->default_value(0.5),     "Tmin")
    ("Tmax",       po::value<double>(&Tmax)->default_value(1.5),     "Tmax")
    ("dT",         po::value<double>(&dT)->default_value(0.02),      "delta T")
    ("mumin",      po::value<double>(&mu_min)->default_value(-10.0), "mu min")
    ("mumax",      po::value<double>(&mu_max)->default_value(0.0),   "mu max")
    ("outputvl",   po::value<bool>(&do_vl)->default_value(false),    "output a lot of files, one for every temperature point (very slow)")
    ;

  po::positional_options_description p;
  p.add("input-file", -1);

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).options(desc).positional(p).run(), vm);
  po::notify(vm);

  if(vm.count("help")) {
    cout << desc << endl;
    return 1;
  }

  if(vm.count("input-file") == 1) {
    in_file = vm["input-file"].as< std::string >();
  } else {
    cout << desc << endl;
    return 1;
  }

  if(vm.count("output") == 0) {
    ostringstream ff;
    ff << in_file << ".p";
    out_file = ff.str();
  }

  PhaseDiagram pd(volume, n0, Tmin, Tmax, dT, mu_min, mu_max);
  pd.offset = offset;
  pd.read(in_file);
  pd.write(out_file, do_vl);

  return 0;
}

