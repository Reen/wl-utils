// std includes
#include <numeric>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/assign/std/vector.hpp>
#include <boost/assign/std/set.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

namespace io = boost::iostreams;


#include <tclap/CmdLine.h>

#include "q_matrix.h"
#include "state.h"


int main (int argc, char *argv[])
{
  std::string file1, file2, command, out_filename;
  bool load_archive = false;
  try
  {
    using namespace boost::assign;

    TCLAP::CmdLine cmd("q_matrix", ' ', "0.9");
    std::vector<std::string> allowed_commands_vec;
    allowed_commands_vec += "convert","compare","dos";
    TCLAP::ValuesConstraint<std::string> allowed_commands(allowed_commands_vec);
    TCLAP::UnlabeledValueArg<std::string> commandArg("command","Command to be executed",true,"", &allowed_commands, cmd);
    TCLAP::UnlabeledValueArg<std::string> file1Arg("file1","Filename of the first parQ dat file",true,"","filename", cmd);
    TCLAP::UnlabeledValueArg<std::string> file2Arg("file2","Filename of the second parQ dat file.\nLeave empty to use the first twice.",false,"","filename", cmd);

    TCLAP::ValueArg<std::size_t> nminArg("","nmin","Minimum number of particles.",false,0,"int", cmd);
    TCLAP::ValueArg<std::size_t> nmaxArg("","nmax","Maximum number of particles.",false,0,"int", cmd);
    TCLAP::ValueArg<std::size_t> nEnergyArg("","nEnergy","Number of Energy bins. = 500",false,500,"int", cmd);
    TCLAP::ValueArg<double> eminArg("","emin","Minimum energy.",false,-700.0,"float", cmd);
    TCLAP::ValueArg<double> emaxArg("","emax","Maximum energy.",false,20.0,"float", cmd);
    TCLAP::ValueArg<double> volumeArg("","volume","Box volume.",false,125.0,"float", cmd);
    TCLAP::ValueArg<std::string> outArg("o","out","Filename for serialized output.",false,"","filename.gz", cmd);
    commandArg.requires("convert") += &nminArg, &nmaxArg, &nEnergyArg, &eminArg, &emaxArg, &volumeArg, &outArg;
    commandArg.requires("dos") += &nminArg, &nmaxArg, &nEnergyArg, &eminArg, &emaxArg, &volumeArg;
    
    cmd.parse( argc, argv );

    command = commandArg.getValue();
    file1 = file1Arg.getValue();
    file2 = file2Arg.getValue();
    State::lease s;
    s->set_min_particles(nminArg.getValue());
    s->set_max_particles(nmaxArg.getValue());
    s->set_min_energy(eminArg.getValue());
    s->set_max_energy(emaxArg.getValue());
    s->set_n_energy(nEnergyArg.getValue());
    s->set_volume(volumeArg.getValue());

    out_filename = outArg.getValue();
    load_archive = loadArg.getValue();

    if(command == "convert" && out_filename == "") {
      throw TCLAP::CmdLineParseException("Option --out missing", "command=convert");
    }
  }
  catch (TCLAP::ArgException &e)  // catch any exceptions
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    return -1;
  }

  if (command == "compare") {
    std::size_t nParticles(State::instance->n_particles());
    std::size_t nEnergy(State::instance->n_energy());
    QMatrix<uint32_t> q(nParticles,nParticles,nEnergy,nEnergy);
    QMatrix<double> qD1(nParticles,nParticles,nEnergy,nEnergy);
    QMatrix<double> qD2(nParticles,nParticles,nEnergy,nEnergy);

    std::cerr << "reading 1" << std::endl;
    gzFile parq_file_1 = q.read_file(file1, 10000000);
    qD1.stochastic_from(q);

    q.clear();

    std::cerr << "reading 2" << std::endl;
    if (file2 != "") {
      q.read_file(file2, 10000000);
    } else {
      q.read_file(parq_file_1, 10000000);
    }

    qD2.stochastic_from(q);

    qD1 -= qD2;

    qD1.print();
  } else if (command == "convert") {
    std::size_t nParticles(State::instance->n_particles());
    std::size_t nEnergy(State::instance->n_energy());
    QMatrix<uint32_t> q(nParticles,nParticles,nEnergy,nEnergy);
    QMatrix<double> qD(nParticles,nParticles,nEnergy,nEnergy);

    std::cerr << "reading " << file1 << std::endl;
    gzFile parq_file_1 = q.read_file(file1);
    qD.stochastic_from(q);
    gzclose(parq_file_1);

    std::cerr << "saving to " << out_filename << std::endl;
    io::filtering_ostream out;
    out.push(io::gzip_compressor());
    out.push(io::file_sink(out_filename));
    boost::archive::text_oarchive oa(out);
    State::lease s;
    s->save_to(oa);
    oa & qD;
  } else if (command == "dos") {

  } else {
    std::cout << "Error: unknown command." << std::endl;
    return -1;
  }
  return 0;
}
