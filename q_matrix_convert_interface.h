#ifndef Q_MATRIX_CONVERT_INTERFACE_H_4X1WK1KG
#define Q_MATRIX_CONVERT_INTERFACE_H_4X1WK1KG

#include "q_matrix_interface.h"
#include "state.h"

#include <boost/numeric/ublas/banded.hpp>
#include <boost/progress.hpp>

#include "tbb/pipeline.h"
#include "tbb/task_scheduler_init.h"

#include "zlib.h"

#include "parallel/gzip_reader.h"
#include "parallel/parq_transform_filter.h"


template<class q_matrix_t>
class QMatrixConvertInterface : protected QMatrixInterface<q_matrix_t> {
private:
  spin_mutex_matrix q_mutex_;
public:
  QMatrixConvertInterface(q_matrix_t &matrix)
      : QMatrixInterface<q_matrix_t>(matrix) {}
  
  gzFile read_file(const std::string &filename,
                   std::size_t N = std::numeric_limits<std::size_t>::max(),
                   std::size_t Nskip = 0) {
    gzFile file = gzopen(filename.c_str(), "r");
    return read_file_(file, N, Nskip);
  }

  gzFile read_file(gzFile file,
                   std::size_t N = std::numeric_limits<std::size_t>::max(),
                   std::size_t Nskip = 0) {
    return read_file_(file, N, Nskip);
  }

private:
  gzFile read_file_(gzFile file, std::size_t N, std::size_t Nskip) {
    State::lease s;
    std::size_t minParticles(s->min_particles());
    double minEnergy(s->min_energy()), energyBinWidth(s->energy_bin_width());
    char buf[1000];
    int N1,N2;
    double E1,E2;
    std::size_t cc(0);
    while ((Z_NULL != gzgets(file, buf, 1000)) && buf[0] == '#') {
      // skip comment lines
      std::cerr << buf;
    }
    if(Nskip > 0) {
      boost::progress_display show_progress(Nskip, std::cout, "Skipping...\n");
      while ((Z_NULL != gzgets(file, buf, 1000)) && --Nskip > 0) {
        // skip lines
        ++show_progress;
      }
    }
    q_mutex_.resize(QMatrixInterface<q_matrix_t>::q_matrix_.outer_cols(),
                    QMatrixInterface<q_matrix_t>::q_matrix_.outer_rows(),
                    1,1);
    tbb::pipeline pipeline;
    GzipReader input_filter(file);
    pipeline.add_filter(input_filter);
    ParQTransformFilter transform_filter(QMatrixInterface<q_matrix_t>::q_matrix_, q_mutex_);
    pipeline.add_filter(transform_filter);
    std::cout << tbb::task_scheduler_init::automatic << std::endl;
    //pipeline.run(tbb::task_scheduler_init::automatic);
    pipeline.run(4);
    pipeline.clear();
    return file;
  }
};

#endif /* end of include guard: Q_MATRIX_CONVERT_INTERFACE_H_4X1WK1KG */
