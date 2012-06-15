// std includes
#include <numeric>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

#include <boost/assign/std/vector.hpp>
#include <boost/assign/std/set.hpp>
#include <boost/filesystem.hpp>
#include <boost/iostreams/filtering_stream.hpp>

namespace io = boost::iostreams;
namespace fs = boost::filesystem;


#include <tclap/CmdLine.h>

#include "q_matrix.h"
#include "state.h"
#include "combine.h"
#include "eigenvector.h"
#include "normalize.h"
#include "variance.h"


int main (int argc, char *argv[])
{
  std::string command, out_filename;
  std::vector<std::string> files;
  int maxIter;
  try
  {
    using namespace boost::assign;

    TCLAP::CmdLine cmd("q_matrix", ' ', "0.9");
    std::vector<std::string> allowed_commands_vec;
    allowed_commands_vec += "normalize", "calcdos", "variance", "combine";
    TCLAP::ValuesConstraint<std::string> allowed_commands(allowed_commands_vec);
    TCLAP::UnlabeledValueArg<std::string> commandArg("command","Command to be executed",true,"", &allowed_commands, cmd);

    /*
    TCLAP::ValueArg<std::size_t> nminArg("","nmin","Minimum number of particles.",false,0,"int", cmd);
    TCLAP::ValueArg<std::size_t> nmaxArg("","nmax","Maximum number of particles.",false,0,"int", cmd);
    TCLAP::ValueArg<std::size_t> nEnergyArg("","nEnergy","Number of Energy bins. = 500",false,500,"int", cmd);
    TCLAP::ValueArg<double> eminArg("","emin","Minimum energy.",false,-700.0,"float", cmd);
    TCLAP::ValueArg<double> emaxArg("","emax","Maximum energy.",false,20.0,"float", cmd);
    TCLAP::ValueArg<double> volumeArg("","volume","Box volume.",false,125.0,"float", cmd);
    TCLAP::ValueArg<std::string> outArg("o","out","Filename for serialized output.",false,"","filename.gz", cmd);
    commandArg.requires("dos") += &nminArg, &nmaxArg, &nEnergyArg, &eminArg, &emaxArg, &volumeArg;
    */
    TCLAP::ValueArg<int> maxIterArg("i", "maxIter", "Maximum number of iterations for iterative methods", false, 999999, "unsigned integer", cmd);
    TCLAP::ValueArg<std::string> outArg("o","out","Filename or directory for output.",false,"","filename.gz", cmd);
    TCLAP::UnlabeledMultiArg<std::string> filesArg("files","Filenames of matrix files.",true,"filenames", cmd);

    cmd.parse( argc, argv );

    State::lease s;
    command = commandArg.getValue();
    files = filesArg.getValue();
    out_filename = outArg.getValue();
    maxIter = maxIterArg.getValue();
    if (files.size() > 1) {
      // the user specified multiple input files, interpret -o as output directory
      if (outArg.isSet() && fs::is_directory(out_filename)) {
        s->set_working_directory(out_filename);
      }
    } else  {
      if (outArg.isSet()) {
        fs::path p(files[0]);
        s->set_working_directory(p.parent_path().string());
      }
    }
  }
  catch (TCLAP::ArgException &e)  // catch any exceptions
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    return -1;
  }

  // check if all files are existant and regular
  for (int i = 0; i < files.size(); i++) {
    if (fs::exists(files[i]) && fs::is_regular_file(files[i])) {
      continue;
    }
    std::cerr << "File not found: " << files[i] << std::endl;
    return -1;
  }

  if (command == "normalize") {
    for (int i = 0; i < files.size(); i++) {
      normalize(files[i]);
    }
  } else if (command == "calcdos") {
    for (int i = 0; i < files.size(); i++) {
      calcdos(files[i], maxIter);
    }
  } else if (command == "variance") {
    variance(files);
  } else if (command == "combine") {
    return combine(files);
  }

  return 0;
}
