#include "q_matrix.h"
#include "q_matrix_convert_interface.h"

#include <limits>
#include <boost/assign/std/set.hpp>
#include <tclap/CmdLine.h>

#include <boost/iostreams/filter/gzip.hpp>

int main (int argc, char *argv[])
{
  std::string out_filename;//,file,file_cb;
  std::size_t skip, read;
  std::vector<std::string> files;
  try
  {
    using namespace boost::assign;
    TCLAP::CmdLine cmd("matrix_convert", ' ', "0.99");
    TCLAP::UnlabeledMultiArg<std::string> fileArg("file1","Filenames of the parQ dat files",true,"filenames", cmd);
    TCLAP::ValueArg<std::size_t> nminArg("","nmin","Minimum number of particles.",false,0,"int", cmd);
    TCLAP::ValueArg<std::size_t> nmaxArg("","nmax","Maximum number of particles.",false,0,"int", cmd);
    TCLAP::ValueArg<std::size_t> nEnergyArg("","nEnergy","Number of Energy bins. = 500",false,500,"int", cmd);
    TCLAP::ValueArg<double> eminArg("","emin","Minimum energy.",false,-700.0,"float", cmd);
    TCLAP::ValueArg<double> emaxArg("","emax","Maximum energy.",false,20.0,"float", cmd);
    TCLAP::ValueArg<double> volumeArg("","volume","Box volume.",false,125.0,"float", cmd);
    TCLAP::ValueArg<std::string> outArg("o","out","Filename for serialized output.",false,"","filename.gz", cmd);
    TCLAP::ValueArg<std::size_t> skipArg("", "skip", "Lines to skip.", false, 0, "int", cmd);
    TCLAP::ValueArg<std::size_t> readArg("", "read", "Lines to read.", false, std::numeric_limits<std::size_t>::max(), "int", cmd);
    fileArg.requires() += &nminArg, &nmaxArg, &nEnergyArg, &eminArg, &emaxArg, &volumeArg, &outArg;

    cmd.parse( argc, argv );

    files = fileArg.getValue();
    State::lease s;
    s->set_min_particles(nminArg.getValue());
    s->set_max_particles(nmaxArg.getValue());
    s->set_min_energy(eminArg.getValue());
    s->set_max_energy(emaxArg.getValue());
    s->set_n_energy(nEnergyArg.getValue());
    s->set_volume(volumeArg.getValue());

    out_filename = outArg.getValue();
    skip = skipArg.getValue();
    read = readArg.getValue();
  }
  catch (TCLAP::ArgException &e)  // catch any exceptions
  {
    std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    return -1;
  }

  std::size_t nParticles(State::instance->n_particles());
  std::size_t nEnergy(State::instance->n_energy());
  QMatrixConvertInterface qD(nParticles,nParticles,nEnergy,nEnergy);

  for(size_t i = 0; i < files.size(); ++i) {
    std::cerr << "reading " << files[i] << std::endl;
    gzFile parq_file_1 = qD.read_file(files[i], read, skip);
    gzclose(parq_file_1);
  }
  qD.make_stochastic();

  std::cerr << "saving to " << out_filename << std::endl;
  io::filtering_ostream out;
  out.push(io::gzip_compressor());
  out.push(io::file_sink(out_filename, std::ios::binary|std::ios::out));
  State::lease s;
  s->save_to(out);
  qD.save_to(out);
  out.pop();
  return 0;
}
