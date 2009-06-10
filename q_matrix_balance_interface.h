#ifndef Q_MATRIX_BALANCE_INTERFACE_H_V2LKAPIR
#define Q_MATRIX_BALANCE_INTERFACE_H_V2LKAPIR

#include "q_matrix.h"
#include "state.h"
#include "matrix_generics.h"

#include <boost/progress.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>

#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_for.h"

class DoParallelPowerMethod {
  std::size_t outer_cols_;
  QMatrix::matrix_t *const q_matrix_;
  typedef boost::numeric::ublas::vector<double> vector_t;
public:
  void operator()(const tbb::blocked_range<std::size_t>& r) const {
    QMatrix::matrix_t& q_matrix(*q_matrix_);
    for(std::size_t nj = r.begin(); nj != r.end(); ++nj) {
      int s_nj = int(nj);
      for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, outer_cols_); ++ni)
      {
        std::cout << ni << " " << nj << std::endl;
        QMatrix::inner_matrix_t m(q_matrix(ni, nj));
        for(std::size_t i = 0; i < m.size1(); ++i) {
          boost::numeric::ublas::matrix_column<QMatrix::inner_matrix_t> col(m, i);
          double sum = std::accumulate(col.begin(), col.end(), 0.0);
          if(sum > 0) {
            col /= sum;
          }
        }
        vector_t dos_old(m.size1());
        vector_t dos(m.size1());
        std::fill(dos_old.data().begin(),
                  dos_old.data().end(),
                  1.0/dos_old.data().size());
        std::size_t iterations = 0;
        while (true) {
          iterations++;
          dos = prod(m, dos_old);
          dos /= std::inner_product(dos.data().begin(),
                                    dos.data().end(),
                                    dos.data().begin(), 0.0);
          bool converged = true;
          double dist;
          for (vector_t::array_type::iterator
               i1(dos.data().begin()), i2(dos_old.data().begin());
               i1 < dos.data().end();
               ++i1, ++i2) {
            if (*i1 > 0.0) {
              if (fabs((*i2)/(*i1)-1.0) > 1.0e-7) {
                dist = (*i2)/(*i1);
                converged = false;
                break;
              }
            }
          }
          dos_old = dos;
          if (iterations%1000) {
            std::cout << ni << " " << nj << " " << dist << std::endl;
          }
          if (converged || iterations > 100000) {
            break;
          }
        }
        // write to file
        char filename[50];
        State::lease s;
        sprintf(filename, "%sdos.%04lu.%04lu.%05lu.dat.gz",
                s->working_directory().c_str(), ni, nj, iterations);
        io::filtering_ostream out;
        out.push(io::gzip_compressor());
        out.push(io::file_sink(filename));
        double fak = 1.0;
        for (std::size_t i = 0; i < dos.size(); ++i) {
          if(dos(i) > 0.0) {
            double log_dos = log(dos(i));
            out << std::setw(20) << std::right << s->bin_to_energy(i)
                << std::setw(20) << std::right << log_dos
                << std::setw(20) << std::right << dos(i)
                << "\n";
          }
        }
      }
    }
  }

  DoParallelPowerMethod( QMatrix::matrix_t *const q_matrix, std::size_t outer_cols )
      : q_matrix_(q_matrix), outer_cols_(outer_cols)
  {
    
  }
};

class QMatrixBalanceInterface : public QMatrix {
  void print_(const matrix_t& matrix, std::string file = "") const {
    std::ofstream outfile;
    std::streambuf*  strm_buffer = std::cout.rdbuf();
    State::lease s;
    if(file != "") {
      if (s->working_directory() != "") {
        file = s->working_directory()+'/'+file;
      }
      std::cerr << file << std::endl;
      outfile.open(file.c_str());
      std::cout.rdbuf(outfile.rdbuf());
    }
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
            if (matrix(ni,nj)(ei,ej) > 0.0) {
              std::cout << std::setw(15) << std::right << (ni - s->min_particles())
                        << std::setw(15) << std::right << (nj - s->min_particles())
                        << std::setw(25) << std::right << (s->bin_to_energy(ei))
                        << std::setw(25) << std::right << (s->bin_to_energy(ej))
                        << std::setw(25) << std::right << matrix(ni,nj)(ei,ej) << "\n";
            }
          }
        }
      }
    }
    std::cout.rdbuf(strm_buffer);
  }
public:
  QMatrixBalanceInterface()
      : QMatrix() {}

  void calculate_dos(std::string dos_fn = "") {
    State::lease s;
    std::size_t nParticles(s->n_particles());
    std::size_t nEnergy(s->n_energy());

    double zero(0), one(1), crit(1.0e-7), dist(0);
    std::size_t i(0);
    dos_matrix_t dos(nParticles,nEnergy);
    dos_matrix_t dos_old(nParticles,nEnergy);
    if (dos_fn == "") {
      std::fill(dos_old.data().begin(), dos_old.data().end(), 1.0/dos_old.data().size());
    } else {
      std::cout << "Reading initial density of states from " << dos_fn << std::endl;
      State::lease s;
      io::filtering_istream in;
      in.push(shell_comments_input_filter());
      in.push(io::gzip_decompressor());
      in.push(io::file_source(dos_fn));
      read_matrix_from_stream<std::size_t, double>(
          in,
          dos_old,
          5,
          std::bind2nd(std::minus<std::size_t>(),s->min_particles()),
          value_to_bin<double>(s->min_energy(), s->energy_bin_width()));
    }
    //tbb::parallel_for(tbb::blocked_range<std::size_t>(0,outer_rows_,2), DoParallelPowerMethod(&q_matrix_, outer_cols_) );
    //return;
    /**
     * Implementation of the GTH method of fenwick.m.06.accurate.144905.
     * Given up as the matrix size exeeds the available memory size.
     * E.g. (111*300)^2  * 8 ~=  8 GB
     *      (111*1000)^2 * 8 ~= 80 GB
     */
    /*
    // transform sparse matrix to solid
    std::cout << __LINE__ << std::endl;
    boost::numeric::ublas::mapped_matrix<double> whole(outer_rows_*inner_rows_, outer_cols_*inner_cols_);
    for (std::size_t ni = 0; ni < outer_cols_; ++ni) {
      int s_ni = int(ni);
      // major row
      for (std::size_t nj = std::max(s_ni-1, 0);
           nj < std::min(ni+2, outer_rows_);
           ++nj) {
        // minor column
        for (std::size_t ei = 0; ei < inner_cols_; ++ei) {
          // minor row
          for (std::size_t ej = 0; ej < inner_rows_; ++ej) {
            if (q_matrix_(ni,nj)(ei,ej) > 0) {
              whole(ni*inner_rows_+ei, nj*inner_cols_+ej) = q_matrix_(ni,nj)(ei,ej);
            }
          }
        }
      }
    }
    std::cout << __LINE__ << std::endl;
    // do GTH Gaussian elimination
    for (std::size_t i = outer_rows_*inner_rows_-1; i > 0; --i) {
      std::cout << __LINE__ << " " << i << std::endl;
      double s = 0;
      for (std::size_t j = 0; j < i-1; ++j) {
        s+=whole(i,j);
      }
      if(s != 0){
        whole(i,i) = -s;
        for (std::size_t j = 0; j < i-1; ++j) {
          whole(j,i) /= s;
        }
      }
      for (std::size_t k = 0; k < i-1; ++k) {
        for (std::size_t j = 0; j < i-1; ++j) {
          if (whole(k,i) != 0 && whole(i,j) != 0) {
            whole(k,j) += whole(k,i)*whole(i,j);
          }
        }
      }
    }
    // now just do eqn 33 of M. Fenwick - J. Chem. Phys. 125, 144905
    dos.clear();
    for (std::size_t i = 1; i < outer_rows_*inner_rows_; ++i) {
      for (std::size_t j = 0; j < i-1; ++j) {
        dos.data()[i] += exp(dos.data()[j] - dos.data()[i-1] + log(whole(j,i)));
      }
      dos.data()[i] = dos.data()[i-1] + log(dos.data()[i]);
    }
    print_dos(dos, 1);
    dos_matrix_ = dos;
    // END GTH method
    */
    boost::timer t;
    while (true) {
      i++;
      dos.clear();
      // do the matrix-vector-multiplication
      double n(0);
      for (std::size_t nj = 0; nj < outer_rows_; ++nj)
      {
        int s_nj = int(nj);
        for (std::size_t ej = 0; ej < inner_rows_; ++ej)
        {
          for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, outer_cols_); ++ni)
          {
            double incr(boost::numeric::ublas::inner_prod(
              boost::numeric::ublas::matrix_column< inner_matrix_t >(q_matrix_(ni, nj), ej),
              boost::numeric::ublas::matrix_row< dos_matrix_t >(dos_old, ni)
            ));
            //incr = std::inner_product(m1.begin(), m1.end(), m2.begin(), incr);
            dos(nj, ej) += incr;
            n += incr;
          }
          //std::cout << std::endl;
        }
      }

      // check wether the iteration has converged
      bool converged = true;
      for (dos_matrix_t::array_type::iterator
           i1(dos.data().begin()), i2(dos_old.data().begin());
           i1 < dos.data().end();
           ++i1, ++i2) {
        if (*i1 > zero) {
          if (fabs((*i2)/(*i1)-one) > crit) {
            dist = (*i2)/(*i1);
            converged = false;
            break;
          }
        }
      }
      // norm eigenvector
      //dos /= std::inner_product(dos.data().begin(), dos.data().end(), dos.data().begin(),0.0);
      dos /= n;

      dos_old = dos;
      if (converged) {
        print_dos(dos, i);
        dos_matrix_ = dos;
        break;
      }

      if (i%100 == 0) {
        std::cout << "I: "
                  << std::setw(10) << std::right << i
                  << std::setw(10) << std::right << (t.elapsed()/100.0)
                  << " seconds/iteration, d: " << (dist-1.0)
                  << std::endl;
        print_dos(dos, i);
        t.restart();
      }
    }
    return;
  }

  void check_detailed_balance() {
    matrix_t balance;
    resize_matrix(balance, outer_rows_, outer_rows_, inner_rows_, inner_rows_);
    for (std::size_t ni = 0; ni < outer_cols_; ++ni) {
      int s_ni = int(ni);
      // major row
      for (std::size_t nj = std::max(s_ni-1, 0);
           nj < std::min(ni+2, outer_rows_);
           ++nj) {
        // minor column
        for (std::size_t ei = 0; ei < inner_cols_; ++ei) {
          // minor row
          for (std::size_t ej = 0; ej < inner_rows_; ++ej) {
            balance(ni,nj)(ei,ej) = q_matrix_(ni,nj)(ei,ej)*dos_matrix_(ni,ei) - q_matrix_(nj,ni)(ej,ei)*dos_matrix_(nj,ej);
          }
        }
      }
    }
    print_(balance, "balance.dat");
  }

  void print_dos(const dos_matrix_t& dos, std::size_t iteration) const {
    char filename[50];
    State::lease s;
    sprintf(filename, "%sdos.%05lu.dat.gz",
            s->working_directory().c_str(),
            iteration);

    std::size_t minParticles(s->min_particles());
    std::size_t maxParticles(s->max_particles());
    double minEnergy(s->min_energy());
    double maxEnergy(s->max_energy());
    double energyBinWidth(s->energy_bin_width());
    double volume(s->volume());

    io::filtering_ostream out;
    out.push(io::gzip_compressor());
    out.push(io::file_sink(filename));
    s->print_to_stream(out);
    double fak = 1.0;
    for (std::size_t i = 0; i < dos.size1(); ++i) {
      std::size_t n = i + minParticles;
      double fakln = 0.0;
      if(n > 0) {
        fak *= n;
        fakln = n*log(volume)-log(fak);
      }
      for (std::size_t j = 0; j < dos.size2(); ++j) {
        if(dos(i,j) > 0.0) {
          double log_dos = log(dos(i,j));
          out << std::setw(20) << std::right << n
              << std::setw(20) << std::right << s->bin_to_energy(j)
              << std::setw(20) << std::right << (log_dos + fakln)
              << std::setw(20) << std::right << log_dos
              << std::setw(20) << std::right << dos(i,j)
              << "\n";
        }
      }
    }
  }
};

#endif /* end of include guard: Q_MATRIX_BALANCE_INTERFACE_H_V2LKAPIR */
