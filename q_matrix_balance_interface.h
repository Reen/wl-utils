#ifndef Q_MATRIX_BALANCE_INTERFACE_H_V2LKAPIR
#define Q_MATRIX_BALANCE_INTERFACE_H_V2LKAPIR

#include "q_matrix.h"
#include "state.h"
#include "matrix_generics.h"

#include <boost/progress.hpp>

#include "tbb/task_scheduler_init.h"
#include "tbb/blocked_range.h"
#include "tbb/parallel_reduce.h"

class QMatrixBalanceInterface : public QMatrix {
  void print_(const matrix_t& matrix, std::string file = "") const {
    std::ofstream outfile;
    std::streambuf*  strm_buffer = std::cout.rdbuf();
    State::lease s;
    if(file != "") {
      file = s->working_directory()+'/'+file;
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
          value_to_bin<double>(s->min_energy(), s->n_energy()));
    }

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
