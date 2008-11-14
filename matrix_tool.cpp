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
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>

namespace io = boost::iostreams;


#include <tclap/CmdLine.h>

#include "q_matrix.h"
#include "state.h"

// g++ -O3 -fomit-frame-pointer -msse -msse2 matrix_tool.cpp -o matrix_tool -I/Users/rene/usr/include/boost-1_37 -I./include/ -lz -L/Users/rene/usr/lib -lboost_thread-xgcc43-mt-1_37 -lboost_serialization-xgcc43-mt-1_37 -lboost_iostreams-xgcc43-mt-1_37 -DNDEBUG -ftree-vectorize -fopenmp 

int main (int argc, char *argv[])
{
	std::string file1, file2, command, out_filename;
  bool load_archive = false;
	try
	{
	  using namespace boost::assign;
	  
		//std::size_t minParticles, maxParticles, nEnergy;
		//double minEnergy, maxEnergy;
		
		TCLAP::CmdLine cmd("q_matrix", ' ', "0.9");
    std::vector<std::string> allowed_commands_vec;
    allowed_commands_vec += "convert","compare","balance", "dos";
    TCLAP::ValuesConstraint<std::string> allowed_commands(allowed_commands_vec);
		TCLAP::UnlabeledValueArg<std::string> commandArg("command","Available commands:\n\n\tcompare\n\tbalance\n\tdos",true,"", &allowed_commands, cmd);
		TCLAP::UnlabeledValueArg<std::string> file1Arg("file1","Filename of the first parQ dat file",true,"","filename", cmd);
		TCLAP::UnlabeledValueArg<std::string> file2Arg("file2","Filename of the second parQ dat file.\nLeave empty to use the first twice.",false,"","filename", cmd);

		TCLAP::ValueArg<std::size_t> nminArg("","nmin","Minimum number of particles.",true,0,"int", cmd);
		TCLAP::ValueArg<std::size_t> nmaxArg("","nmax","Maximum number of particles.",true,0,"int", cmd);
		TCLAP::ValueArg<std::size_t> nEnergyArg("","nEnergy","Number of Energy bins. = 500",false,500,"int", cmd);
		TCLAP::ValueArg<double> eminArg("","emin","Minimum energy.",true,-700.0,"float", cmd);
		TCLAP::ValueArg<double> emaxArg("","emax","Maximum energy.",true,20.0,"float", cmd);
		TCLAP::ValueArg<double> volumeArg("","volume","Box volume.",true,125.0,"float", cmd);
		TCLAP::ValueArg<std::string> outArg("o","out","Filename for serialized output.",false,"","filename.gz", cmd);
    TCLAP::SwitchArg loadArg("l", "load", "If serialized matrix should be read instead of parQ data.", cmd);

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
	
	
	//std::size_t max_line_count = -1;
	
	//typedef ublas::matrix< double, ublas::row_major > dos_matrix_type;

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
	} else if (command == "balance") {
	  QMatrix<uint32_t> q;
		QMatrix<double> qD;
		std::cerr << "reading " << file1 << std::endl;
	  if(load_archive) {
	    io::filtering_istream in;
      in.push(io::gzip_decompressor());
      in.push(io::file_source(file1));
      boost::archive::text_iarchive ia(in);
      State::lease s;
      s->load_from(ia);
      ia & qD;
	  } else {
	    std::size_t nParticles(State::instance->n_particles());
  		std::size_t nEnergy(State::instance->n_energy());
      q.resize(nParticles,nParticles,nEnergy,nEnergy);
  		qD.resize(nParticles,nParticles,nEnergy,nEnergy);
  		gzFile parq_file_1 = q.read_file(file1);
  		qD.stochastic_from(q);
      gzclose(parq_file_1);
	  }
		std::cerr << "calculating" << std::endl;
    qD.calculate_dos();
    std::cerr << "checking detailed balance" << std::endl;
    qD.check_detailed_balance();
		
	} else if (command == "dos") {
		
	} else {
		std::cout << "Error: unknown command." << std::endl;
		return -1;
	}
	/*
	q_matrix_type q;
	qD_matrix_type qD;
	std::size_t nParticles(maxParticles-minParticles);
	double energyBinWidth((maxEnergy-minEnergy)/nEnergy);

	std::cout << "Setting up matrices." << std::endl;
	setupMatrix(q , nParticles,nParticles,nEnergy,nEnergy);
	setupMatrix(qD, nParticles,nParticles,nEnergy,nEnergy);
	int N1,N2;
	double E1,E2;
	std::cout << "Reading from stdin." << std::endl;
	std::size_t line_count = 0;
	while(EOF != scanf("%i %i %lf %lf", &N1,&N2,&E1,&E2)) {
		//std::cout << N1 << " " << N2 << " " << E1 << " " << E2 << "\n";
		if(N1 >= minParticles && N2 <= maxParticles && E1 > minEnergy && E2 < maxEnergy) {
			std::size_t i1 = static_cast<size_t>((E1-minEnergy)/energyBinWidth);
			std::size_t i2 = static_cast<size_t>((E2-minEnergy)/energyBinWidth);
			std::size_t ni1 = N1-minParticles;
			std::size_t ni2 = N2-minParticles;
			q(ni1,ni2)(i1,i2)++;
		}
		line_count++;
		while(getchar() != '\n') {}
		if(line_count >= max_line_count) {
			break;
		}
	}
	std::cout << "Read " << line_count << " lines from stdin." << std::endl;

	std::cout << "Converting matrix to double." << std::endl;
	for (std::size_t ni = 0; ni < qD.size1(); ++ni)
	{
		int s_ni = int(ni);
		// minor column
		for (std::size_t ei = 0; ei < nEnergy; ++ei)
		{
			q_inner_matrix_type::value_type i_sum(0);
			// major row
			for (std::size_t nj = std::max(s_ni-1, 0); nj < std::min(ni+2, qD.size2()); ++nj)
			{
				// minor row
				for (std::size_t ej = 0; ej < nEnergy; ++ej)
				{
					i_sum += q(ni, nj)(ei, ej);
				}
			}
			if (i_sum > 0)
			{
				double d_sum(i_sum);
				// major row
				for (std::size_t nj = std::max(s_ni-1, 0); nj < std::min(ni+2, qD.size2()); ++nj)
				{
					// minor row
					for (std::size_t ej = 0; ej < nEnergy; ++ej)
					{
						// copy and divide by column sum
						qD(ni, nj)(ei, ej) = q(ni, nj)(ei, ej) / d_sum;
					}
				}
			} // else -> all values in the column are zero so we do nothing
		}
	}
	*/
	
	//std::cout << "Starting power method iteration." << std::endl;
	//dos_matrix_type dos(nParticles,nEnergy);
	//dos_matrix_type dos_old(nParticles,nEnergy);
	//std::fill(dos_old.data().begin(), dos_old.data().end(), 1.0/dos_old.data().size());

	/* ### 2 ### Power Iteration
	 * Power Iteration to calculate the eigenvector to the largest eigenvalue, which is 1, as the matrix is stochastic.
	 *
	 * We have iterations over columns in the inner loop, thus we have to use ublas::column_major order in the Q matrix.
	 * @todo: eventually parallize this iteration for maximum speed on SMP machines
	 * @todo: compare the precision of float/double/mpfr::Real DoSes
	 */
	/*
	double zero(0), one(1), crit(1.0e-7), dist(0);
	std::size_t i(0);
	while (true)
	{
		i++;
		dos.clear();
		// do the matrix-vector-multiplication
		double n(0);
#pragma omp parallel for reduction(+:n)
		for (std::size_t nj = 0; nj < qD.size2(); ++nj)
		{
			int s_nj = int(nj);
			for (std::size_t ej = 0; ej < nEnergy; ++ej)
			{
				for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, qD.size1()); ++ni)
				{
					ublas::matrix_column< qD_inner_matrix_type > m1(qD(ni, nj), ej);
					ublas::matrix_row< dos_matrix_type > m2(dos_old, ni);
					double incr(0);
					incr = std::inner_product(m1.begin(), m1.end(), m2.begin(), incr);
					dos(nj, ej) += incr;
					n += incr;
				}
				//std::cout << std::endl;
			}
		}
		// check wether the iteration has converged
		bool converged = true;
		for (dos_matrix_type::array_type::iterator i1(dos.data().begin()), i2(dos_old.data().begin()); i1 < dos.data().end(); ++i1, ++i2)
		{
			if (*i1 > zero)
			{
				if (fabs((*i2)/(*i1)-one) > crit)
				{
					dist = (*i2)/(*i1);
					converged = false;
					break;
				}
			}
		}
		// norm eigenvector
		dos /= n;

		dos_old = dos;
		if(converged)
		{
			printDoS(dos,i, "parq", minEnergy, energyBinWidth, minParticles);
			break;
		}

		if (i%1000 == 1)
		{
			std::cout << "Writing DOS of iteration " << i << " to disk." << std::endl;
			printDoS(dos,i, "parq", minEnergy, energyBinWidth, minParticles);
		}
	}
	*/
	return 0;
}
