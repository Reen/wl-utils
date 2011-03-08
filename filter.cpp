#include <fstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <queue>
#include <string>
#include <sstream>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/filesystem/convenience.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/xtime.hpp>
#include <boost/numeric/ublas/matrix.hpp>


using namespace std;
namespace ub = boost::numeric::ublas;
// ../../svn/towhee-wl/Source/towhee | ../../svn/wl-utils/filter 

/*
 * $Id: filter.cpp 217 2008-04-10 13:10:23Z rhab $
 */

typedef map<string, double> config_type;
typedef queue< stringstream* > work_type;

class MatrixThread {
	work_type* __work;
	config_type* __config;
	boost::mutex* __mutex;
	unsigned int N1,N2,Nmin;
	double dE, EbinWidth, Emin, Emax;
	bool* __done;
	bool __config_read;
	std::string* __config_str;
	
	void readConfig() {
		Nmin = (unsigned int)((*__config)["nmin"]);
		N1 = (unsigned int)((*__config)["nmax"]-(*__config)["nmin"]+1);
		N2 = (unsigned int)((*__config)["E_N"]);
		Emin = (*__config)["emin"];
		Emax = (*__config)["emax"];
		dE = Emax-Emin;
		EbinWidth = dE/N2;
		cout <<"Simulation startet with:\n"
			<< std::setw(12) << "Nmin:"			<< std::setw(12) << std::right << Nmin	<< "\n"
			<< std::setw(12) << "N:"			<< std::setw(12) << std::right << N1	<< "\n"
			<< std::setw(12) << "E_N:"			<< std::setw(12) << std::right << N2	<< "\n"
			<< std::setw(12) << "Emin:"			<< std::setw(12) << std::right << Emin	<< "\n"
			<< std::setw(12) << "Emax:"			<< std::setw(12) << std::right << Emax	<< "\n"
			<< std::setw(12) << "Ediff:"		<< std::setw(12) << std::right << dE	<< "\n"
			<< std::setw(12) << "EbinWidth:"	<< std::setw(12) << std::right << EbinWidth << endl;
		__config_read = true;
	}
public:
	MatrixThread(work_type* work, config_type* config, boost::mutex* mutex, bool* done, std::string* config_str)
	: __work(work), __config(config), __mutex(mutex), __done(done), __config_read(false), __config_str(config_str) { }
	
	void operator()() {
		while(true) {
			// will point to the data we work with
			stringstream* data;
			
			// sleep while there is nothing to do
			while(__work->size() == 0) {
				boost::xtime xt;
				boost::xtime_get(&xt, boost::TIME_UTC);
				xt.nsec += 10000000;
				boost::thread::sleep(xt);
				// return if we are finished
				if(*__done) {
					return;
				}
			}
						
			// acquire a lock on the work list and fetch some data
			{
				boost::mutex::scoped_lock lock(*__mutex);
				data = __work->front();
				__work->pop();
			}
			
			// read the config if we haven't read it yet
			if(!__config_read) {
				readConfig();
			}
			
			// start working
			unsigned int timestep;
			double ln_f;
			ub::matrix<double> dos(N1,N2);
			*data >> timestep;
			*data >> ln_f;
			
			cout << "processing DoS " << std::setw(20) << std::right <<	 timestep << std::setw(20) << std::right << ln_f << endl;
			
			double max = 0.0;
			for(unsigned int i = 0; i < N1; i++) {
				for(unsigned int j = 0; j < N2; j++) {
					*data >> dos(i,j);
					max = std::max(max,dos(i,j));
				}
			}
			
			stringstream filename;
			filename<< "dos/dos3_"
					<< std::setw(15) << std::right << std::setfill('0') << timestep
					<< "_"
					<< ln_f
					<< ".dat";
			ofstream out(filename.str().c_str(), ios::trunc);
			out << *__config_str;
			out << "# timestep\t" << timestep << "\n";
			out << "# ln_f\t" << ln_f << "\n";
			
			double Eoffset = Emin+(EbinWidth/2.0);
			for (unsigned i = 0; i < N1; ++i) {
				for (unsigned j = 0; j < N2; ++j) {
					if(dos(i,j) > 0.0) {
						out << std::setw(20) << std::right << (Nmin+i)
							<< std::setw(20) << std::right << (EbinWidth*j+Eoffset)
							<< std::setw(20) << std::right << (dos(i,j)-max) << endl;
					}
				}
			}
			delete data;
		}
	}
};


int main (int argc, char const *argv[])
{
	using namespace boost::filesystem;
	
	string line;
	bool done = false;

	// last known timestep
	int last_timestep = 0;
	
	// Filestreams
	boost::iostreams::filtering_ostream parq, data, output, stats, datahist;
	
	// open file for parq-data with gzip comrpession
	// parq.push(boost::iostreams::gzip_compressor());
	// parq.push(boost::iostreams::file_sink("parq.dat.gz"));
	
	// open file for some statistical data
	data.push(boost::iostreams::file_sink("wang_landau.dat"));

	// open another file for statistical data
	stats.push(boost::iostreams::file_sink("wl_stats.dat"));

	// open file for some statistical data
	datahist.push(boost::iostreams::file_sink("wang_landau_hist.dat"));
	
	// open file for output of towhee (compressed)
	output.push(boost::iostreams::gzip_compressor());
	output.push(boost::iostreams::file_sink("output.gz"));
	
	// map for config-data
	config_type config;
	
	// work queue
	work_type work;
	boost::mutex work_mutex;
	
	// string for config-output
	string config_str;
	
	// starting thread
	boost::thread matrix_thrd(MatrixThread(&work, &config, &work_mutex, &done, &config_str));
	
	// paths for the different filetypes
	path histPath("./histograms/");
	path dosPath("./dos/");
	
	if(!exists(histPath) || !is_directory(histPath)) {
		create_directory(histPath);
	}
	if(!exists(dosPath) || !is_directory(dosPath)) {
		create_directory(dosPath);
	}
	
	while(getline(cin, line)) {
		unsigned int line_size = line.size();
		if(line_size > 7 && line.compare(0,4," WL#") == 0) {
			/*if(line.compare(4,4,"parq") == 0) {
				copy(line.begin()+8, line.end(), ostream_iterator<char>(parq));
				parq << "\n";
			} else*/ if(line.compare(4,9,"data_hist") == 0) {
				copy(line.begin()+8, line.end(), ostream_iterator<char>(datahist));
				datahist << "\n";
			} else if(line.compare(4,4,"data") == 0) {
				copy(line.begin()+8, line.end(), ostream_iterator<char>(data));
				data << "\n";
			} else if(line.compare(4,4,"stat") == 0) {
				stats << last_timestep;
				{
					istringstream temp(line);
					string temp_str;
					int t1,t2,t3,t4,t5,t6;
					temp >> temp_str; //stat
					temp >> temp_str; //T:
					temp >> t1 >> t2 >> t3;
					temp >> temp_str; //S:
					temp >> t4 >> t5 >> t6;
					stats << std::setw(15) << std::right << t1;
					stats << std::setw(15) << std::right << t2;
					stats << std::setw(15) << std::right << t3;
					stats << std::setw(15) << std::right << t4;
					stats << std::setw(15) << std::right << t5;
					stats << std::setw(15) << std::right << t6;
				}
				stats << "\n";
			} else if(line.compare(4,10,"matr_begin") == 0) {
				output.flush();
				unsigned int lines = 0;
				stringstream *matrix_str = new stringstream;
				unsigned int timestep;
				double ln_f;
				stringstream filename;
				{
					istringstream temp(line);
					string temp_str;
					temp >> temp_str;
					temp >> timestep;
					temp >> ln_f;
					*matrix_str << timestep << " " << ln_f << "\n";
					filename<< "dos_"
							<< std::setw(15) << std::right << std::setfill('0') << timestep
							<< "_"
							<< ln_f
							<< ".dat.gz";
					last_timestep = timestep;
				}
				boost::iostreams::filtering_ostream dosFile;
				dosFile.push(boost::iostreams::gzip_compressor());
				dosFile.push(boost::iostreams::file_sink( (dosPath / filename.str() ).string()));
				//config_str.seekg(0, ios::beg);
				//boost::iostreams::copy(config_str, dosFile);
				dosFile << config_str;
				dosFile << "# timestep\t" << timestep << "\n# ln_f\t" << ln_f << "\n";
				
				while(getline(cin, line)) {
					if(line.compare(4,8,"matr_end") != 0) {
						lines++;
						*matrix_str << line << "\n";
						dosFile	 << line << "\n";
					} else {
						break;
					}
				}
				// process matrix
				//boost::iostreams::copy(matrix_str, dosFile);
				matrix_str->seekg(0, ios::beg);
				matrix_str->seekp(0, ios::beg);
				boost::mutex::scoped_lock lock(work_mutex);
				work.push(matrix_str);
			} else if(line.compare(4,10,"hist_begin") == 0) {
				unsigned int lines = 0;
				unsigned int timestep;
				double ln_f;
				stringstream filename;
				{
					istringstream temp(line);
					string temp_str;
					temp >> temp_str;
					temp >> timestep;
					temp >> ln_f;
					filename<< "hist_"
							<< std::setw(15) << std::right << std::setfill('0') << timestep
							<< "_"
							<< ln_f
							<< ".dat.gz";
					last_timestep = timestep;
				}
				boost::iostreams::filtering_ostream histFile;
				histFile.push(boost::iostreams::gzip_compressor());
				histFile.push(boost::iostreams::file_sink( (histPath / filename.str()).string() ));
				//config_str.seekg(0, ios::beg);
				//boost::iostreams::copy(config_str, histFile);
				histFile << config_str;
				histFile << "# timestep\t" << timestep << "\n# ln_f\t" << ln_f << "\n";
				while(getline(cin, line)) {
					if(line.compare(4,8,"hist_end") != 0) {
						lines++;
						histFile << line << "\n";
					} else {
						break;
					}
				}
			} else if(line.compare(4,15,"hist_full_begin") == 0) {
				unsigned int lines = 0;
				unsigned int timestep;
				double ln_f;
				stringstream filename;
				{
					istringstream temp(line);
					string temp_str;
					temp >> temp_str;
					temp >> timestep;
					temp >> ln_f;
					filename<< "hist_full_"
							<< std::setw(15) << std::right << std::setfill('0') << timestep
							<< "_"
							<< ln_f
							<< ".dat.gz";
					last_timestep = timestep;
				}
				boost::iostreams::filtering_ostream histFile;
				histFile.push(boost::iostreams::gzip_compressor());
				histFile.push(boost::iostreams::file_sink( (histPath / filename.str()).string() ));
				//config_str.seekg(0, ios::beg);
				//boost::iostreams::copy(config_str, histFile);
				histFile << config_str;
				histFile << "# timestep\t" << timestep << "\n# ln_f\t" << ln_f << "\n";
				while(getline(cin, line)) {
					if(line.compare(4,13,"hist_full_end") != 0) {
						lines++;
						histFile << line << "\n";
					} else {
						break;
					}
				}
			} else if(line.compare(4,10,"init_begin") == 0) {
				while(getline(cin,line)) {
					if(line.compare(4,8,"init_end") != 0) {
						line = line.substr(4);
						istringstream line_str(line);
						string key;
						line_str >> key;
						double value;
						line_str >> value;
						if(key[0] == '$') {
							key = "rev";
						}
						config[key] = value;
					} else {
						break;
					}
				}
				config["binwidth"] = (config["emax"] - config["emin"]) / (config["E_N"]);
				stringstream config_temp(config_str);
				for(config_type::iterator it = config.begin(); it != config.end(); it++) {
					config_temp <<	"# " << it->first	 <<	 "\t" << it->second << "\n";
				}
				config_str = config_temp.str();
				parq << config_str;
				data << config_str;
				//boost::iostreams::copy(config_str, parq);
				//config_str.seekg(0, ios::beg);
				//boost::iostreams::copy(config_str, data);
				//config_str.seekg(0, ios::beg);
			} else {
				cout << "WL_U: " << line << endl;
			}
		} else {
			output << line << "\n";
			//cout << line << endl;
		}
		
	}
	done = true;
	matrix_thrd.join();
	return 0;
}
