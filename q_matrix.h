#ifndef _Q_MATRIX_H_
#define _Q_MATRIX_H_

#include <iomanip>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/banded.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

#include <boost/progress.hpp>

#include <boost/utility.hpp>

#include "matrix_generics.h"
#include "zlib.h"

#include "state.h"

namespace io = boost::iostreams;

template<class matrix_t>
void resize_matrix(matrix_t& matrix,
                   std::size_t outer_cols,
                   std::size_t outer_rows,
                   std::size_t inner_cols,
                   std::size_t inner_rows) {
  matrix.resize(outer_cols,outer_rows,1,1);
  for (int i = 0; i < static_cast<int>(matrix.size1()); ++ i) {
    for (int j = std::max(i-1, 0); j < std::min(i+2, static_cast<int>(matrix.size2())); ++j) {
      matrix(i, j).resize(inner_cols,inner_rows);
      matrix(i, j).clear();
    }
  }
}

template<class matrix_float_t, class calc_float_t = double>
class QMatrix : boost::noncopyable {
public:
  typedef boost::numeric::ublas::matrix< matrix_float_t, boost::numeric::ublas::column_major > inner_matrix_t;
  typedef boost::numeric::ublas::banded_matrix< inner_matrix_t, boost::numeric::ublas::column_major > matrix_t;
  typedef boost::numeric::ublas::matrix< calc_float_t, boost::numeric::ublas::row_major > dos_matrix_t;
private:
  matrix_t q_matrix_;
  dos_matrix_t dos_matrix_;
  std::size_t outer_cols_;
  std::size_t outer_rows_;
  std::size_t inner_cols_;
  std::size_t inner_rows_;


  template<class U, class V> friend class QMatrix;

  void resize() {
    resize_matrix(q_matrix_, outer_cols_, outer_rows_, inner_cols_, inner_rows_);
  }

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
    boost::progress_display show_progress(Nskip, std::cout, "Skipping...\n");
    while ((Z_NULL != gzgets(file, buf, 1000)) && --Nskip > 0) {
      // skip lines
      ++show_progress;
    }
    ++show_progress;
    std::size_t count(0);
    do {
      count++;
      if (EOF != sscanf(buf,"%i %i %lf %lf", &N1,&N2,&E1,&E2)) {
        std::size_t ni1 = N1-minParticles;
        std::size_t ni2 = N2-minParticles;
        //std::cout << N << " " << N1 << " " << N2 << " " << E1 << " " << E2 << std::endl;
        if (ni1 < outer_cols_ && ni2 < outer_rows_) {
          std::size_t i1 = static_cast<size_t>((E1-minEnergy)/energyBinWidth);
          std::size_t i2 = static_cast<size_t>((E2-minEnergy)/energyBinWidth);
          if (i1 < inner_cols_ && i2 < inner_rows_) {
            q_matrix_(ni1,ni2)(i1,i2)++;
          }
        }
      }
    } while(--N >  0 && (Z_NULL != gzgets(file, buf, 1000)));
    std::cerr << cc << " " << count << std::endl;
    return file;
  }

  void print_(const matrix_t& matrix, std::string file = "") const {
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
  // constructor
  QMatrix(std::size_t n1,
          std::size_t n2,
          std::size_t n3,
          std::size_t n4) {
    resize(n1, n2, n3, n4);
  }

  QMatrix()
      : outer_cols_(0),
        outer_rows_(0),
        inner_cols_(0),
        inner_rows_(0) {
    resize();
  }

  void resize(std::size_t n1, std::size_t n2, std::size_t n3, std::size_t n4) {
    outer_cols_ = n1;
    outer_rows_ = n2;
    inner_cols_ = n3;
    inner_rows_ = n4;
    resize();
  }

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

  void stochastic_from(const QMatrix<uint32_t> &mat) {
    assert(mat.inner_cols_ == inner_cols_);
    assert(mat.inner_rows_ == inner_rows_);
    assert(mat.outer_cols_ == outer_cols_);
    assert(mat.outer_rows_ == outer_rows_);

    for (std::size_t ni = 0; ni < outer_cols_; ++ni) {
      int s_ni = int(ni);
      // minor column
      for (std::size_t ei = 0; ei < inner_cols_; ++ei) {
        std::size_t i_sum(0);
        // major row
        for (std::size_t nj = std::max(s_ni-1, 0);
             nj < std::min(ni+2, outer_rows_);
             ++nj) {
          // minor row
          for (std::size_t ej = 0; ej < inner_rows_; ++ej) {
            i_sum += mat(ni, nj)(ei, ej);
          }
        }
        if (i_sum > 0) {
          matrix_float_t d_sum(i_sum);
          // major row
          for (std::size_t nj = std::max(s_ni-1, 0);
               nj < std::min(ni+2, outer_rows_);
               ++nj) {
            // minor row
            for (std::size_t ej = 0; ej < inner_rows_; ++ej) {
              // copy and divide by column sum
              q_matrix_(ni, nj)(ei, ej) =
                static_cast<matrix_float_t>(mat(ni, nj)(ei, ej)) / d_sum;
            }
          }
        } // else -> all values in the column are zero so we do nothing
      }
    }
  }

  void operator-=(const QMatrix<matrix_float_t> &mat) {
    assert(mat.inner_cols_ == inner_cols_);
    assert(mat.inner_rows_ == inner_rows_);
    assert(mat.outer_cols_ == outer_cols_);
    assert(mat.outer_rows_ == outer_rows_);
    // TODO: rewrite using -= operator of inner matrices
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
            //qD1(ni,nj)(ei,ej) = (qD1(ni,nj)(ei,ej) - qD2(ni, nj)(ei, ej));
            q_matrix_(ni,nj)(ei,ej) -= mat(ni, nj)(ei, ej);
          }
        }
      }
    }
  }

  bool operator==(const QMatrix<matrix_float_t> &mat) {
    bool ret(true);
    for (int i = 0; i < static_cast<int>(outer_cols_); ++ i) {
      for (int j = std::max(i-1, 0);
           ret && (j < std::min(i+2, static_cast<int>(outer_rows_)));
           ++j) {
        ret = (ret && (0 == boost::numeric::ublas::norm_inf(q_matrix_(i,j) - mat.q_matrix_(i,j))));
      }
    }
    return ret;
  }

  void clear() {
    for (int i = 0; i < static_cast<int>(outer_cols_); ++ i) {
      for (int j = std::max(i-1, 0);
           j < std::min(i+2, static_cast<int>(outer_rows_));
           ++j) {
        q_matrix_(i, j).clear();
      }
    }
  }

  const inner_matrix_t& operator()(const std::size_t &i,
                                   const std::size_t &j) const {
    return q_matrix_(i,j);
  }

  inner_matrix_t& operator()(const std::size_t &i,
                             const std::size_t &j) {
    assert(0 <= i);
    assert(0 <= j);
    assert(i < outer_rows_);
    assert(j < outer_cols_);
    return q_matrix_(i,j);
  }

  void print() const {
    print_(q_matrix_);
  }

  void calculate_dos(std::string dos_fn = "") {
    State::lease s;
    std::size_t nParticles(s->n_particles());
    std::size_t nEnergy(s->n_energy());

    calc_float_t zero(0), one(1), crit(1.0e-7), dist(0);
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
            calc_float_t incr(boost::numeric::ublas::inner_prod(
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
      for (typename dos_matrix_t::array_type::iterator
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
      dos /= n;

      dos_old = dos;
      if(converged)
      {
        dos_matrix_ = dos;
        break;
      }

      if (i%100 == 0) {
        std::cout << "I: "
                  << std::setw(10) << std::right << i
                  << std::setw(10) << std::right << (t.elapsed()/100.0)
                  << " seconds/iterations, current dist: " << (dist-1.0)
                  << std::endl;
        print_dos(dos, i);
        t.restart();
      }
    }
    return;
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

  void save_to(io::filtering_ostream &out) {
    out.write((char*)&outer_cols_, sizeof(outer_cols_));
    out.write((char*)&outer_rows_, sizeof(outer_rows_));
    out.write((char*)&inner_cols_, sizeof(inner_cols_));
    out.write((char*)&inner_rows_, sizeof(inner_rows_));
    std::cout << outer_cols_ << " " << outer_rows_ << " " << inner_cols_ << " " << inner_rows_ << "\n";

    for (int i = 0; i < static_cast<int>(outer_cols_); ++i) {
      for (int j = std::max(i-1, 0);
           j < std::min(i+2, static_cast<int>(outer_rows_));
           ++j) {
        out.write((char*)(&q_matrix_(i,j).data()[0]), q_matrix_(i,j).data().size() * sizeof(matrix_float_t));
      }
    }
  }

  void load_from(io::filtering_istream &in) {
    in.read((char*)&outer_cols_, sizeof(outer_cols_));
    in.read((char*)&outer_rows_, sizeof(outer_rows_));
    in.read((char*)&inner_cols_, sizeof(inner_cols_));
    in.read((char*)&inner_rows_, sizeof(inner_rows_));
    std::cout << outer_cols_ << " " << outer_rows_ << " " << inner_cols_ << " " << inner_rows_ << "\n";

    resize();

    for (int i = 0; i < static_cast<int>(outer_cols_); ++i) {
      for (int j = std::max(i-1, 0);
           j < std::min(i+2, static_cast<int>(outer_rows_));
           ++j) {
        in.read((char*)(&q_matrix_(i,j).data()[0]), q_matrix_(i,j).data().size() * sizeof(matrix_float_t));
      }
    }
  }
};

#endif /* _Q_MATRIX_H_ */
