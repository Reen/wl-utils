// std includes
#include <numeric>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <limits>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
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
  std::string file, initial_dos("");
  bool load_archive = false;
  try
	{
	  using namespace boost::assign;
    TCLAP::CmdLine cmd("Matrix Detailed Balance Calculator", ' ', "0.91");
    TCLAP::UnlabeledValueArg<std::string> fileArg("file","Filename of the parQ dat file or Q matrix archive.",true,"","filename", cmd);

    TCLAP::ValueArg<std::size_t> nminArg("","nmin","Minimum number of particles.",false,0,"int", cmd);
    TCLAP::ValueArg<std::size_t> nmaxArg("","nmax","Maximum number of particles.",false,0,"int", cmd);
    TCLAP::ValueArg<std::size_t> nEnergyArg("","nEnergy","Number of Energy bins. = 500",false,500,"int", cmd);
    TCLAP::ValueArg<double> eminArg("","emin","Minimum energy.",false,-700.0,"float", cmd);
    TCLAP::ValueArg<double> emaxArg("","emax","Maximum energy.",false,20.0,"float", cmd);
    TCLAP::ValueArg<double> volumeArg("","volume","Box volume.",false,125.0,"float", cmd);

    TCLAP::SwitchArg loadArg("l", "load", "If serialized matrix should be read instead of parQ data.", cmd);
    
    TCLAP::ValueArg<std::string> initialDosArg("","initial_dos", "Starting value of the power iteration.", false, "", "filename", cmd);

    if (!argv_has(argc, argv, "--load")) {
      fileArg.requires() += &nminArg, &nmaxArg, &nEnergyArg, &eminArg, &emaxArg, &volumeArg;
    }

    cmd.parse( argc, argv );

    file = fileArg.getValue();
    initial_dos = initialDosArg.getValue();
    State::lease s;
    s->set_min_particles(nminArg.getValue());
    s->set_max_particles(nmaxArg.getValue());
    s->set_min_energy(eminArg.getValue());
    s->set_max_energy(emaxArg.getValue());
    s->set_n_energy(nEnergyArg.getValue());
    s->set_volume(volumeArg.getValue());

    load_archive = loadArg.getValue();
  }
  catch (TCLAP::ArgException &e)  // catch any exceptions
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    return -1;
  }

  QMatrix<uint32_t> q;
	QMatrix<double> qD;
	std::cerr << "reading " << file << std::endl;
  if(load_archive) {
    io::filtering_istream in;
    in.push(io::gzip_decompressor());
    in.push(io::file_source(file));
    boost::archive::text_iarchive ia(in);
    State::lease s;
    s->load_from(ia);
    ia & qD;
  } else {
    std::size_t nParticles(State::instance->n_particles());
		std::size_t nEnergy(State::instance->n_energy());
    q.resize(nParticles,nParticles,nEnergy,nEnergy);
		qD.resize(nParticles,nParticles,nEnergy,nEnergy);
		gzFile parq_file_1 = q.read_file(file);
		qD.stochastic_from(q);
    gzclose(parq_file_1);
  }
	std::cerr << "calculating" << std::endl;
  qD.calculate_dos(initial_dos);
  std::cerr << "checking detailed balance" << std::endl;
  qD.check_detailed_balance();

  return 0;
}
