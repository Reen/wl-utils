#ifndef Q_MATRIX_CONVERT_INTERFACE_H_4X1WK1KG
#define Q_MATRIX_CONVERT_INTERFACE_H_4X1WK1KG

#include "q_matrix.h"
#include "state.h"

#include <boost/progress.hpp>

#include "tbb/pipeline.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

#include "zlib.h"

#include "parallel/gzip_reader.h"
#include "parallel/parq_transform_filter.h"


class QMatrixConvertInterface : public QMatrix {
public:
  QMatrixConvertInterface(std::size_t n1,
                          std::size_t n2,
                          std::size_t n3,
                          std::size_t n4)
      : QMatrix(n1, n2, n3, n4) {}
  
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
  class TransformToStochastic {
  private:
    int_q_matrix_t *const int_m_;
    matrix_t *const float_m_;
    std::size_t outer_cols_;
    std::size_t outer_rows_;
    std::size_t inner_cols_;
    std::size_t inner_rows_;
  public:
    TransformToStochastic(int_q_matrix_t& int_m, matrix_t& float_m,
                          std::size_t outer_cols, std::size_t outer_rows,
                          std::size_t inner_cols, std::size_t inner_rows)
        : int_m_(&int_m), float_m_(&float_m),
          outer_cols_(outer_cols), outer_rows_(outer_rows),
          inner_cols_(inner_cols), inner_rows_(inner_rows) {}

    void operator()(const tbb::blocked_range<std::size_t>& r) const {
      int_q_matrix_t& int_m(*int_m_);
      matrix_t& float_m(*float_m_);
      for (std::size_t ni = r.begin(); ni != r.end(); ++ni) {
        int s_ni = int(ni);
        std::cout << s_ni << std::endl;
        // minor column
        for (std::size_t ei = 0; ei < inner_cols_; ++ei) {
          std::size_t i_sum(0);
          // major row
          for (std::size_t nj = std::max(s_ni-1, 0);
               nj < std::min(ni+2, outer_rows_);
               ++nj) {
            // minor row
            for (std::size_t ej = 0; ej < inner_rows_; ++ej) {
              i_sum += int_m(ni, nj)(ei, ej);
            }
          }
          if (i_sum > 0) {
            double d_sum(i_sum);
            // major row
            for (std::size_t nj = std::max(s_ni-1, 0);
                 nj < std::min(ni+2, outer_rows_);
                 ++nj) {
              // minor row
              for (std::size_t ej = 0; ej < inner_rows_; ++ej) {
                // copy and divide by column sum
                float_m(ni, nj)(ei, ej) =
                  static_cast<double>(int_m(ni, nj)(ei, ej)) / d_sum;
              }
            }
          } // else -> all values in the column are zero so we do nothing
        }
      }
    }
  };

  gzFile read_file_(gzFile file, std::size_t N, std::size_t Nskip) {
    char buf[1000];
    // skip comment lines
    std::size_t n_comments(0);
    while ((Z_NULL != gzgets(file, buf, 1000)) && buf[0] == '#') {
      n_comments++;
      std::cerr << buf;
    }
    // skip Nskip lines from the beginning
    if(Nskip > 0) {
      boost::progress_display show_progress(Nskip, std::cout, "Skipping...\n");
      while ((Z_NULL != gzgets(file, buf, 1000)) && --Nskip > 0) {
        ++show_progress;
      }
    }

    // create a unsinged matrix to operate on
    int_q_matrix_t matrix;
    resize_matrix(matrix, outer_rows_, outer_cols_, inner_rows_, inner_cols_);

    // create a banded matrix of mutexes to lock single sub matrices
    spin_mutex_matrix q_mutex_;
    q_mutex_.resize(outer_cols_, outer_rows_, 1, 1);

    // create a processing pipeline
    tbb::pipeline pipeline;
    GzipReader input_filter(file, N);
    pipeline.add_filter(input_filter);
    ParQTransformFilter transform_filter(matrix, q_mutex_);
    pipeline.add_filter(transform_filter);
    std::cout << tbb::task_scheduler_init::automatic << std::endl;
    //pipeline.run(tbb::task_scheduler_init::automatic);
    pipeline.run(8);
    pipeline.clear();
    std::cout << "finnished processing pipeline" << std::endl;
    // create the stochastic matrix from the integer matrix
    tbb::parallel_for(tbb::blocked_range<std::size_t>(0,outer_cols_),
                      TransformToStochastic(matrix, q_matrix_,
                                            outer_cols_, outer_rows_,
                                            inner_cols_, inner_rows_),
                      tbb::auto_partitioner());
    return file;
  }
};

#endif /* end of include guard: Q_MATRIX_CONVERT_INTERFACE_H_4X1WK1KG */
