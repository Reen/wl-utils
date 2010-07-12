#ifndef Q_MATRIX_BALANCE_INTERFACE_H_V2LKAPIR
#define Q_MATRIX_BALANCE_INTERFACE_H_V2LKAPIR
// -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
#include "q_matrix.h"
#include "state.h"
#include "matrix_generics.h"

#include <limits>

#include <boost/progress.hpp>
#include <boost/numeric/ublas/matrix_sparse.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/numeric/ublas/lu.hpp>
#include <boost/numeric/ublas/io.hpp>

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

template <class T>
class basic_iteration {
public:
  basic_iteration(std::size_t max_iter, double relative_eps)
      : i(0), max_iter_(max_iter), relative_eps_(relative_eps) {}
  
  inline bool converged(T iter1, T iter1end, T iter2, double & dist) {
    bool converged = true;
    for (;iter1 < iter1end;
         ++iter1, ++iter2) {
      if (*iter1 > 0) {
        if (converged && fabs((*iter2)/(*iter1)-1.0) > relative_eps_) {
          dist = (*iter2)/(*iter1);
          converged = false;
          break;
        }
      }
    }
    return converged;
  }
  
  inline void operator++() { ++i; }
  inline bool first() { return i == 0; }
  inline std::size_t iterations() { return i; }
  inline double relative_tolerance() { return relative_eps_; }
  inline std::size_t max_iterations() { return max_iter_; }
protected:
  std::size_t i;
  std::size_t max_iter_;
  double relative_eps_;
};

namespace ublas = boost::numeric::ublas;

class QMatrixBalanceInterface : public QMatrix {
  bool dos_matrix_set_;
  void print_(const matrix_t& matrix, std::string file = "") const {
    std::ofstream outfile;
    std::streambuf*  strm_buffer = std::cout.rdbuf();
    State::lease s;
    if(file != "") {
      if (s->working_directory() != "") {
        file = s->working_directory()+file;
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
              std::cout << std::setw(15) << std::right << (ni + s->min_particles())
                        << std::setw(15) << std::right << (nj + s->min_particles())
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

  void initialize_dos_matrix(dos_matrix_t &dos, std::string dos_fn = "") {
    if (dos_fn == "") {
      if(dos_matrix_set_) {
        std::cout << "initializing DoS matrix to data calculated by broad histogram equation\n";
        dos = dos_matrix_; // take the data calculated via the broad histogram equation
      } else {
        std::cout << "initializing DoS matrix to 1/size\n";
        std::fill(dos.data().begin(), dos.data().end(), 1.0/dos.data().size());
      }
    } else {
      std::cout << "Reading initial density of states from " << dos_fn << std::endl;
      State::lease s;
      io::filtering_istream in;
      in.push(shell_comments_input_filter());
      in.push(io::gzip_decompressor());
      in.push(io::file_source(dos_fn));
      read_matrix_from_stream<std::size_t, double>(
          in,
          dos,
          5,
          std::bind2nd(std::minus<std::size_t>(),s->min_particles()),
          value_to_bin<double>(s->min_energy(), s->energy_bin_width()));
    }
  }

public:
  QMatrixBalanceInterface()
      : QMatrix(), dos_matrix_set_(false) {}

  /**
   * ILU - Incomplete LU-Decomposition
   * Inspired by fenwick.m.06.accurate.144905.
   * (M. K. Fenwick, Journal of Chemical Physics 125, 144905 (2006))
   * Performs an incomplete LU decomposition on a copy of our Q matrix.
   * Only entries different from 0 will be modified, which makes this
   * algoritm preferable for spares matrices. Resulting DoS differs
   * slightly in the positive energy region.
   * This algorithm is only used for NVT simulations.
   */
  void calculate_dos_ilu0(dos_matrix_t & dos, dos_matrix_t & dos_old) {
    std::cerr << "Calculating DOS using Incomplete LU-Decomposition" << std::endl;
    inner_matrix_t& inner_mat(q_matrix_(0,0));
    // also try comparing with != 0 instead of >0
    // perform ILU(0)
    namespace ublas = boost::numeric::ublas;
    inner_mat = ublas::trans(inner_mat);
    inner_matrix_t A(inner_mat); // Backup copy
    inner_mat -= ublas::identity_matrix<double>(inner_cols_);
    std::cout << __LINE__ << std::endl;
    for (std::size_t i = 0; i < inner_rows_; ++i) {
      //std::cout << __LINE__ << "i: " << i << std::endl;
      for (std::size_t j = 0; j < inner_cols_; ++j) {
        //std::cout << __LINE__<< "j: " << j << std::endl;
        if (inner_mat(i,j) != 0) {
          //double s = inner_mat(i,j);
          for (int k = 0; k < std::min(i,j); ++k) {
            //std::cout << __LINE__ << "k: " << k << std::endl;
            inner_mat(i,j) -= inner_mat(i,k)*inner_mat(k,j);
          }
          if(i > j) {
            inner_mat(i,j) /= inner_mat(j,j);
          }
        }
      }
    }
    ublas::vector<double> temp1(inner_rows_, 1.0/inner_rows_);
    ublas::vector<double> temp2(inner_rows_, 0);
    for (std::size_t trials = 0; trials < 10; trials++) {
      temp2 = ublas::prod(A, temp1);
      ublas::inplace_solve(inner_mat, temp2, ublas::unit_lower_tag());
      ublas::inplace_solve(inner_mat, temp2, ublas::upper_tag());
      temp1 -= temp2;
      temp1 /= ublas::norm_2(temp1);
      std::copy(temp1.begin(), temp1.end(), dos.data().begin());
      print_dos("ilu0", dos, trials);
    }
    inner_mat = ublas::trans(A); // Restore backup
  }

  /**
   * Implementation of the GTH method of fenwick.m.06.accurate.144905.
   * Given up as the matrix size exeeds the available memory size.
   * We only use it for canonical ensembles.
   * E.g. (111*300)^2  * 8 ~=  8 GB
   *      (111*1000)^2 * 8 ~= 80 GB
   */
  void calculate_dos_gth(dos_matrix_t & dos, dos_matrix_t & dos_old) {
    std::cerr << "Calculating DOS using GTH method" << std::endl;
    // we assume small matrix and try GTH method
    // do GTH LU decomposition
    namespace ublas = boost::numeric::ublas;
    inner_matrix_t inner_mat(q_matrix_(0,0));
    for (std::size_t i = inner_rows_-1; i > 0; --i) {
      double s = ublas::norm_1(ublas::subrange(ublas::row(inner_mat,i), 0, i));
      if (s != 0) {
        inner_mat(i,i) = -s;
        for (std::size_t j = 0; j < i; ++j) {
          inner_mat(j,i) /= s;
        }
      }
      for (std::size_t k = 0; k < i; ++k) {
        for (std::size_t j = 0; j < i; ++j) {
          inner_mat(k,j) += inner_mat(k,i)*inner_mat(i,j);
        }
      }
    }
    // now just do eqn 33 of M. Fenwick - J. Chem. Phys. 125, 144905
    dos.clear();
    dos.data()[0] = 1;
    for (std::size_t i = 1; i < outer_rows_*inner_rows_; ++i) {
      //std::cout << i << " " << dos.data()[i-1] << ": ";
      for (std::size_t j = 0; j < i; ++j) {
        //std::cout << "(" << dos.data()[j] << " " << dos.data()[i-1] << " " << log(whole(j,i)) << ") ";
        dos.data()[i] += exp(dos.data()[j] - dos.data()[i-1] + log(inner_mat(j,i)));
      }
      //std::cout << ": "<< dos.data()[i] << "\n";
      dos.data()[i] = dos.data()[i-1] + log(dos.data()[i]);
    }
    for (std::size_t ei = 0; ei < inner_cols_; ++ei) {
      dos(0,ei) = exp(dos(0,ei)-5);
    }
    print_dos("gth", dos, 4);
  }

  /**
   * Full LU Decomposition for NVT
   * Partial LU for µVT
   */
  void calculate_dos_pLU(dos_matrix_t & dos, dos_matrix_t & dos_old) {
    /**
     * Inverse Iteration with Partial LU Decomposition
     * ***********************************************
     * inverse iteration:
     * (A-µI)b_{k+1} = b_k/C_k
     * with µ = 0 and A = (P^T - I) and C_k being the normalization
     * can be solved via LU decomposition:
     * b_{k+1} = A^-1 b_k / C_k
     * A^-1 = (LU)^-1 = U^-1 L^-1
     * To reduce the matrix fill-in accompanied by LU decomposition
     * we use a scheme similar to the incomplete LU decomposition,
     * where only entries originally occupied (!=0) are modified.
     * For partial LU we reduce this stringent criterium to submatrices
     * that are 0. E. g.
     * ┌─────┐      ┌─────┐ with L/U containing only lower/upper entries
     * |AA   |      |XU   | and X containing upper (including the main
     * |AAA  |      |LXU  | diagonal) and lower entries.
     * | AAA |  ->  | LXU | The indices of the following loops have
     * |  AAA|      |  LXU| been switched to avoid the transposition
     * |   AA|      |   LX| imposed by A = (P^T - I).
     * └─────┘      └─────┘
     * Thus we perform:
     * ┌─────┐      ┌─────┐ Here we have to remember that rows in the
     * |PP   |      |XL   | original matrix are columns in the
     * |PPP  |      |UXL  | transposed one.
     * | PPP |  ->  | UXL |
     * |  PPP|      |  UXL| Fill-in may happen in all non-zero sub-
     * |   PP|      |   UX| matrices of P regardless of the an entry
     * └─────┘      └─────┘ being zero or not.
     */
    std::cerr << "Calculating DOS using Inverse Iteration via LU-Decomposition" <<  std::endl;
    // #0 backup the matrix to a temporary file
    std::string temp_fn = tmpnam(NULL);
    /*{
        std::cout << "Writing Matrix to temporary file: " << temp_fn << std::endl;
        io::filtering_ostream out;
        out.push(io::gzip_compressor());
        out.push(io::file_sink(temp_fn, std::ios::binary|std::ios::out));
        save_to(out);
        io::close(out);
    }*/
    // create a copy of out matrix
    matrix_t lu_matrix(q_matrix_);
    // #1 A-µI: µ=1, substract identity matrix
    for (std::size_t nj = 0; nj < outer_rows_; ++nj) {
      lu_matrix(nj,nj) -= ublas::identity_matrix<double>(inner_cols_);
    }
    // #2 do partial LU
    boost::progress_display show_progress(outer_rows_, std::cout, "Calculating partial LU...\n");
    for (std::size_t nj = 0; nj < outer_rows_; ++nj) {
      ++show_progress;
      const int s_nj = int(nj);
      for (std::size_t ej = 0; ej < inner_rows_; ++ej) {
        for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, outer_cols_); ++ni) {
          for (std::size_t ei = 0; ei < inner_cols_; ++ei) {
            // non-const reference as a shortcut
            double& s = lu_matrix(ni,nj)(ei,ej);
            //if(s != 0)
            {
              /**
               * LU decomposition basically consists of the inner product
               * of row and column left and above the current point.
               * The lenght of this subranges is determined by min(i,j).
               * Every entry not on one of the major diagonals is and
               * stays 0. Thus we only need to additionaly consider the
               * matrix left or above (or both) of the current position.
               * This is reflected in the booleans converted into size_t
               * and the special treatment for the main diagonal:
               */
              // we need special treatment if ni == 0
              if (ni == nj && ni > 0) {
                s -= ublas::inner_prod(
                  ublas::row(lu_matrix(ni,ni-1), ei),
                  ublas::column(lu_matrix(ni-1,ni), ej)
                );
              }
              s -= ublas::inner_prod(
                ublas::subrange(   ublas::row(lu_matrix(ni, nj-(std::size_t)(ni < nj)), ei), 0, std::min(ei,ej)),
                ublas::subrange(ublas::column(lu_matrix(ni-(std::size_t)(ni > nj), nj), ej), 0, std::min(ei,ej))
              );
              // All L entries have to be divided by the main diagonal of U
              if (ni*inner_cols_+ei < nj*inner_rows_+ej) {
                s /= lu_matrix(ni,ni)(ei,ei);
              }
            }
          }
        }
      }
    }
    for (std::size_t ni = 0; ni < outer_cols_; ++ni) {
      int s_ni = int(ni);
      std::cout << s_ni << std::endl;
      // minor column
      for (std::size_t ei = 0; ei < inner_cols_; ++ei) {
        double d_sum(0);
        // major row
        for (std::size_t nj = std::max(s_ni-1, 0);
             nj < std::min(ni+2, outer_rows_);
             ++nj) {
          // minor row
          for (std::size_t ej = 0; ej < inner_rows_; ++ej) {
            d_sum += lu_matrix(ni, nj)(ei, ej);
          }
        }
        lu_matrix(ni,ni)(ei,ei) += 1.0-d_sum;
      }
    }
    std::ofstream fout("mat.dat");
    for(std::size_t i = 0; i < inner_rows_; i++) {
      for(std::size_t j = 0; j < inner_rows_; j++) {
        fout << lu_matrix(outer_rows_-1,outer_rows_-1)(i,j) << "\t";
      }
      fout << "\n";
    }
    // #3 perform inverse power iteration
    dos_matrix_t dos_prev(dos.size1(), dos.size2());
    std::fill(dos_prev.data().begin(), dos_prev.data().end(), 1.0/dos_prev.data().size());
    /**
     * Loop performs forward and backward substitution as long as
     * iteration has not converged.
     * Algorithm: A*x=b -> x = (LU)^-1 * b
     * L*y = b -> solve for y
     * U*x = y -> solve for x
     **#1 forward substitution ***************************************
     * y_1 = b_1 / L_11
     * y_i = 1/L_ii * (b_i - \sum_{j=1}^{i-1} L_ij*y_j)
     * with L_ii = 1
     **#2 backward substitution **************************************
     * x_N = y_N / U_NN
     * x_i = 1/U_ii * (y_i - \sum_{j=i+1}^{N} U_ij*x_j)
     *****************************************************************
     * We only need to perform backward substituion as stated in
     * fenwick.m.06.accurate.144905 as L is nonsingular and thus can
     * be eliminated.
     **/
    std::size_t trials = 0;
    do {
      trials++;
      /**
       * Explanation of the following code:
       *  --> nj, ej
       *    ┌───┬───┬───┬───┬───┬ ... - major diagonal belongs to U
       *    |ULL|LLL|   |   |   |     - L_ii = 1
       *  | |UUL|LLL|   |   |   |     - forward substitution only works
       *  | |UUU|LLL|   |   |   |       on L
       *  ↓ ├───┼───┼───┼───┼───┼ ... - the \sum in forward subst. is
       * ni |UUU|ULL|LLL|   |   |       the inner product of the matrix
       * ei |UUU|UUL|LLL|   |   |       elements L in a given row and
       *    |UUU|UUU|LLL|   |   |       the corresponding y elements
       *    ├───┼───┼───┼───┼───┼ ... - therefore we split our calculation
       *    |   |UUU|ULL|LLL|   |       into one part belonging to the
       *    |   |UUU|UUL|LLL|   |       major diagonal matrix (partial
       *    |   |UUU|UUU|LLL|   |       row) and a part belonging to
       *    └───┼───┼───┼───┼───┼ ...   the subdiagonal matrix (full row)
       **/
      dos_old = dos_prev;
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
            dos(nj, ej) += ublas::inner_prod(
                ublas::column(q_matrix_(ni, nj), ej),
                ublas::row(dos_old, ni)
              );
              
          }
        }
      }
      /*for (std::size_t nj = 0; nj < outer_rows_; ++nj)
      {
        int s_nj = int(nj);
        ublas::matrix_row<dos_matrix_t> dos_row(dos, nj);
        for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, outer_cols_); ++ni)
        {
          ublas::axpy_prod(q_matrix_(ni,nj), ublas::row(dos_old,ni), dos_row ,false);
        }
      }*/
      // forward substitution
      dos_old(0,0) = dos(0,0)/*/q_matrix_(0,0)(0,0) ==  1*/;
      for (std::size_t nj = 0; nj < outer_rows_; ++nj) {
        //int s_nj = int(nj);
        //dos /= std::accumulate(dos.data().begin(), dos.data().end(), 0.0);
        for (std::size_t ej = (nj == 0 ? 1 : 0); ej < inner_rows_; ++ej) {
          dos_old(nj,ej) = dos(nj,ej);
          dos_old(nj,ej) -= ublas::inner_prod(
            ublas::subrange(ublas::column(lu_matrix(nj,nj), ej),0,ej),
            ublas::subrange(ublas::row(dos_old, nj),0,ej)
          );
          if(nj > 0) {
            dos_old(nj,ej) -= ublas::inner_prod(
              ublas::column(lu_matrix(nj,nj-1), ej),
              ublas::row(dos_old, nj-1)
            );
          }
        }
      }
      // backward substitution
      dos(outer_rows_-1, inner_rows_-1) = dos_old(outer_rows_-1, inner_rows_-1) / lu_matrix(outer_rows_-1,outer_rows_-1)(inner_rows_-1, inner_rows_-1); // what happens if this is eq 0?
      for (int nj = outer_rows_-1; nj >= 0; --nj) {
        for (int ej = (nj == outer_rows_-1 ? inner_rows_-2 : inner_rows_-1); ej >= 0; --ej) {
          dos(nj,ej) = dos_old(nj,ej);
          dos(nj,ej) -= ublas::inner_prod(
            ublas::subrange(ublas::column(lu_matrix(nj,nj), ej), ej+1, inner_cols_),
            ublas::subrange(ublas::row(dos, nj), ej+1, inner_cols_)
          );
          if (nj < outer_rows_-1) {
            dos(nj,ej) -= ublas::inner_prod(
              ublas::column(lu_matrix(nj+1,nj), ej), // evtl nj und nj+1 tauschen
              ublas::row(dos, nj+1)
            );
          }
          dos(nj,ej) /= lu_matrix(nj,nj)(ej,ej);
        }
      }
      dos_old = dos_prev;
      dos_prev -= dos;
      //dos_prev /= std::inner_product(dos_prev.data().begin(), dos_prev.data().end(), dos_prev.data().begin(), 0.0);
      dos_prev /= std::accumulate(dos_prev.data().begin(), dos_prev.data().end(), 0.0);
      //dos_old = dos_old - dos;
      //double r = std::inner_product(dos_old.data().begin(), dos_old.data().end(), dos_old.data().begin(), 0.0);
      //std::cerr << r << std::endl;
      double r = 0;
      bool converged = true;
      for (dos_matrix_t::array_type::iterator
           i1(dos_old.data().begin()), i2(dos_prev.data().begin());
           i1 != dos_old.data().end();
           ++i1, ++i2) {
        if (*i1 > 0) {
          if (converged && fabs((*i2)/(*i1)-1.0) > 0) {
            r = (*i2)/(*i1);
            converged = false;
            break;
          }
        }
      }
      std::cerr << r << std::endl;
      if (converged || trials > 2500) {
        break;
      }
      if(trials%11 == 0) {
          print_dos("plu", dos_prev, trials, false);
      }
      //dos_old.swap(dos);
    } while(true);
    print_dos("plu", dos_prev, trials, false);
    /*{
        std::cout << "Loading Matrix from temporary file: " << temp_fn << std::endl;
        io::filtering_istream in;
        in.push(io::gzip_decompressor());
        in.push(io::file_source(temp_fn, std::ios::binary|std::ios::in));
        load_from(in, false);
        unlink(temp_fn.c_str());
    }*/
  }

  void calculate_dos_power_iteration(dos_matrix_t & dos, dos_matrix_t & dos_old) {
    std::cerr << "calculating dos via power iteration" << std::endl;
    typedef boost::numeric::ublas::matrix<bool> bool_matrix_t;
    bool_matrix_t zero_mat(dos.size1(), dos.size2());
    zero_mat.clear();
    double zero(0), one(1), crit(1.0e-7), dist(0), dist_old(0);
    std::size_t i(0);
    
    for (std::size_t nj = 0; nj < outer_rows_; ++nj)
    {
      int s_nj = int(nj);
      for (std::size_t ej = 0; ej < inner_rows_; ++ej)
      {
        bool brk = false;
        for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, outer_cols_); ++ni)
        {
          for (std::size_t ei = 0; ei < inner_rows_; ++ei)
          {
            if(q_matrix_(ni, nj)(ei,ej) != 0) {
              zero_mat(nj, ej) = true;
              brk = true;
              break;
            }
          }
          if(brk) {break;}
        }
      }
    }
    // begin simple Power Iteration Method
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
          if(!zero_mat(nj,ej)) {
            dos(nj,ej) = dos_old(nj,ej);
            n += dos_old(nj,ej);
            continue;
          }
          for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, outer_cols_); ++ni)
          {
            double incr(boost::numeric::ublas::inner_prod(
              boost::numeric::ublas::matrix_column< inner_matrix_t >(q_matrix_(ni, nj), ej),
              boost::numeric::ublas::matrix_row< dos_matrix_t >(dos_old, ni)
            ));
            dos(nj, ej) += incr;
            n += incr;
          }
        }
      }

      dos /= n;


      // check wether the iteration has converged
      bool converged = true;
      for (dos_matrix_t::array_type::iterator
           i1(dos.data().begin()), i2(dos_old.data().begin());
           i1 < dos.data().end();
           ++i1, ++i2) {
        if (*i1 > zero) {
          if (converged && fabs((*i2)/(*i1)-one) > crit) {
            dist = (*i2)/(*i1);
            converged = false;
            break;
          }
        }
      }

      dos_old.swap(dos);
      dist_old = dist;
      if (converged) {
        print_dos("dos", dos, i, false);
        dos_matrix_ = dos;
        break;
      }

      if (i%1000 == 0) {
        std::cout << "I: "
                  << std::setw(10) << std::right << i
                  << std::setw(10) << std::right << (1000.0/t.elapsed())
                  << " iterations/second, d: "
                  << std::setw(10) << std::right << (dist-1.0)
                  << std::setw(10) << std::right << (zero_mat.data().size() - std::accumulate(zero_mat.data().begin(), zero_mat.data().end(), 0u))
                  << std::endl;
        print_dos("dos", dos, i, false);
        t.restart();
      }
    }
  }

  void calculate_dos_sparse(dos_matrix_t & dos, dos_matrix_t & dos_old) {
    std::size_t nonz(0);
    std::cout << "counting nonzeros:" << std::endl;
    for (std::size_t nj = 0; nj < outer_rows_; ++nj)
    {
      int s_nj = int(nj);
      for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, outer_cols_); ++ni)
      {
        nonz += (inner_cols_*inner_rows_) - std::count(q_matrix_(ni,nj).data().begin(), q_matrix_(ni,nj).data().end(), 0.0);
      }
    }
    std::cout << nonz << std::endl;
    boost::numeric::ublas::compressed_matrix<double> q_mat(inner_cols_*outer_cols_, inner_rows_*outer_rows_, nonz);
    std::cout << "remapping" << std::endl;
    for (std::size_t nj = 0; nj < outer_rows_; ++nj)
    {
      int s_nj = int(nj);
      for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, outer_cols_); ++ni)
      {
        for (std::size_t ej = 0; ej < inner_rows_; ++ej)
        {
          for (std::size_t ei = 0; ei < inner_rows_; ++ei)
          {
            if(q_matrix_(ni,nj)(ei,ej) != 0) {
              q_mat(inner_rows_*nj+ej, inner_cols_*ni+ei) = q_matrix_(ni,nj)(ei,ej);
            }
          }
        }
      }
    }
    std::cout << "power iteration " << q_mat.nnz() << std::endl;
    boost::numeric::ublas::vector<double> t1(inner_rows_*outer_rows_),t2(inner_rows_*outer_rows_),t3(inner_rows_*outer_rows_);
    std::fill(t1.begin(), t1.end(), 1.0/t1.size());
    double lambda, residual, dist;
    std::size_t i(0);
    basic_iteration<ublas::vector<double>::iterator> iter(100000, 1e-8);
    boost::timer t;
    do
    {
      i++;
      t3 = t1;
      //std::cout << i << t1 << "\n" << t2 << std::endl;
      boost::numeric::ublas::axpy_prod(q_mat, t1, t2, true);
      lambda = ublas::inner_prod(t1,t2);
      t1 *= -lambda;
      t1 += t2;
      residual = ublas::norm_2(t1);
      t1 = t2/ublas::norm_2(t2);
      if (i%1000 == 0) {
        std::cout << "I: "
                  << std::setw(10) << std::right << i
                  << std::setw(10) << std::right << (1000.0/t.elapsed())
                  << " iterations/second, d: "
                  << std::setw(12) << std::right << (dist-1.0)
                  << std::setw(10) << std::right << lambda
                  << std::setw(12) << std::right << residual
                  << std::endl;
        std::copy(t1.begin(), t1.end(), dos.data().begin());
        print_dos("spa", dos, i, false);
        t.restart();
      }
    } while(!iter.converged(t3.begin(), t3.end(), t1.begin(), dist));
    std::copy(t1.begin(), t1.end(), dos.data().begin());
    print_dos("spa", dos, i, false);
  }

  void calculate_dos(std::string dos_fn = "") {
    State::lease s;
    std::size_t nParticles(s->n_particles());
    std::size_t nEnergy(s->n_energy());

    dos_matrix_t dos(nParticles,nEnergy);
    dos_matrix_t dos_old(nParticles,nEnergy);
    initialize_dos_matrix(dos_old, dos_fn);


    if (outer_rows_ == 1 && outer_cols_ == 1) {
      calculate_dos_ilu0(dos, dos_old);
    }


    if (outer_rows_ == 1 && outer_cols_ == 1) {
      calculate_dos_gth(dos, dos_old);
    }

    if (outer_rows_ >= 1 && outer_cols_ >= 1) {
      calculate_dos_sparse(dos, dos_old);
      //calculate_dos_pLU(dos, dos_old);
    }

    //tbb::parallel_for(tbb::blocked_range<std::size_t>(0,outer_rows_,2), DoParallelPowerMethod(&q_matrix_, outer_cols_) );
    //return;

    calculate_dos_power_iteration(dos, dos_old);
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
            balance(ni,nj)(ei,ej) = fabs(q_matrix_(ni,nj)(ei,ej)*dos_matrix_(ni,ei) - q_matrix_(nj,ni)(ej,ei)*dos_matrix_(nj,ej));
          }
        }
      }
    }
    print_(balance, "balance.dat");
  }

  void print_dos(const std::string& prefix, const dos_matrix_t& dos, std::size_t iteration, bool print_all=true) const {
    char filename[5000];
    State::lease s;
    sprintf(filename, "%s%s.%06lu.dat.gz",
            s->working_directory().c_str(),
            prefix.c_str(),
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
        if(print_all || dos(i,j) > 0) {
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

  void broad_histogram() {
    if (outer_cols_ != 1 || outer_rows_ != 1) {
      return;
    }

    State::lease s;
    std::size_t nParticles(s->n_particles());
    std::size_t nEnergy(s->n_energy());

    dos_matrix_.resize(nParticles,nEnergy);
    dos_matrix_.clear();
    // minor column
    for (std::size_t ei = 0; ei < inner_cols_-1; ++ei) {
      std::size_t ej = ei+1;
      double log_frac = log(q_matrix_(0,0)(ei,ej) / q_matrix_(0,0)(ej,ei));
      if(!boost::math::isfinite(log_frac) && ej +1 < inner_cols_) {
        log_frac = log(q_matrix_(0,0)(ei,ej+1) / q_matrix_(0,0)(ej+1,ei));
      }
      dos_matrix_(0,ej) = dos_matrix_(0,ei) + log_frac;
      //std::cout << ei << " " << ej << " " << dos_matrix_(0,ei) << " " << (q_matrix_(0,0)(ei,ej) / q_matrix_(0,0)(ej,ei)) << " " << q_matrix_(0,0)(ei,ej) << " " << q_matrix_(0,0)(ej,ei) << std::endl;
    }
    for (std::size_t ei = 0; ei < inner_cols_; ++ei) {
      dos_matrix_(0,ei) = exp(dos_matrix_(0,ei));
    }
    dos_matrix_set_ = true;
    print_dos("bh", dos_matrix_, 1, true);
    dos_matrix_ /= std::inner_product(dos_matrix_.data().begin(), dos_matrix_.data().end(), dos_matrix_.data().begin(),0.0);
  }
};

#endif /* end of include guard: Q_MATRIX_BALANCE_INTERFACE_H_V2LKAPIR */
