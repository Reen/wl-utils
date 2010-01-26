#ifndef Q_MATRIX_CONVERT_INTERFACE_H_4X1WK1KG
#define Q_MATRIX_CONVERT_INTERFACE_H_4X1WK1KG

#include "q_matrix.h"
#include "state.h"

#include <boost/progress.hpp>

#include <iomanip>

//#include "tbb/pipeline.h"
#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

#include "zlib.h"

//#include "parallel/gzip_reader.h"
//#include "parallel/parq_transform_filter.h"


typedef boost::numeric::ublas::banded_matrix<boost::numeric::ublas::matrix< uint32_t, boost::numeric::ublas::column_major >, boost::numeric::ublas::column_major > int_q_matrix_t;

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

  void print(std::string file) const {
    std::ofstream outfile;
    std::streambuf*  strm_buffer = std::cout.rdbuf();
    if(file != "") {
      outfile.open(file.c_str());
      std::cout.rdbuf(outfile.rdbuf());
    }
    State::lease s;
    s->print_to_stream(std::cout);
    std::cout.precision(15);
    for (std::size_t ni = 0; ni < outer_cols_; ++ni) {
      int s_ni = int(ni);
      // minor column
      for (std::size_t ei = 0; ei < inner_cols_; ++ei) {
        // major row
        for (std::size_t nj = std::max(s_ni-1, 0);
             nj < std::min(ni+2, outer_rows_);
             ++nj) {
          // minor row
          for (std::size_t ej = 0; ej < inner_rows_; ++ej) {
            if (q_matrix_(ni,nj)(ei,ej) > 0.0) {
              std::cout << std::setw(15) << std::right << (ni - s->min_particles())
                        << std::setw(15) << std::right << (nj - s->min_particles())
                        << std::setw(25) << std::right << (s->bin_to_energy(ei))
                        << std::setw(25) << std::right << (s->bin_to_energy(ej))
                        << std::setw(25) << std::right << q_matrix_(ni,nj)(ei,ej) << "\n";
            }
          }
        }
      }
    }
    std::cout.rdbuf(strm_buffer);
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

  struct binary_line {
    int32_t N1;
    int32_t N2;
    double E1;
    double E2;
  };

  gzFile read_file_(gzFile file, std::size_t N, std::size_t Nskip) {
    // skip Nskip lines from the beginning
    if (Nskip > 0) {
      gzseek(file, 24*Nskip,SEEK_SET);
    }

    // create a unsinged matrix to operate on
    int_q_matrix_t matrix;
    resize_matrix(matrix, outer_rows_, outer_cols_, inner_rows_, inner_cols_);

    int32_t N1, N2;
    double E1, E2, minEnergy, energyBinWidth;
    std::size_t outer_cols(matrix.size1()), outer_rows(matrix.size2());
    std::size_t inner_cols(matrix(0,0).size1()), inner_rows(matrix(0,0).size2()), minParticles;
    {
      State::lease s;
      minParticles = s->min_particles();
      minEnergy = s->min_energy();
      energyBinWidth = s->energy_bin_width();
    }
    binary_line bl;
    boost::progress_display show_progress(N, std::cout, "Reading...\n");
    std::size_t skip_count(0);
    for(std::size_t i = 0; i < N && !gzeof(file); ++i) {
      ++show_progress;
      gzread(file, &bl, 24);
      //std::cout << bl.N1 << " " << bl.N2 << " " << bl.E1 << " " << bl.E2 << std::endl;
      std::size_t ni1 = bl.N1-minParticles;
      std::size_t ni2 = bl.N2-minParticles;
      if (ni1 < outer_cols && ni2 < outer_rows) {
        std::size_t i1 = static_cast<size_t>((bl.E1-minEnergy)/energyBinWidth);
        std::size_t i2 = static_cast<size_t>((bl.E2-minEnergy)/energyBinWidth);
        if (i1 < inner_cols && i2 < inner_rows) {
          matrix(ni1,ni2)(i1,i2)++;
        } else {
          skip_count++;
#ifndef NDEBUG
          std::cout << bl.N1 << " " << bl.N2 << " " << bl.E1 << " " << bl.E2 << "\n";
#endif
        }
      } else {
        skip_count++;
#ifndef NDEBUG
        std::cout << bl.N1 << " " << bl.N2 << " " << bl.E1 << " " << bl.E2 << "\n";
#endif
      }
    }
    // create the stochastic matrix from the integer matrix
    tbb::parallel_for(tbb::blocked_range<std::size_t>(0,outer_cols_),
                      TransformToStochastic(matrix, q_matrix_,
                                            outer_cols_, outer_rows_,
                                            inner_cols_, inner_rows_),
                      tbb::auto_partitioner());
    std::cout << "Skipped lines: " << skip_count << "\tRead lines: " << show_progress.count() << std::endl;
    return file;
  }
};

#endif /* end of include guard: Q_MATRIX_CONVERT_INTERFACE_H_4X1WK1KG */
