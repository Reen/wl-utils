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

#include <boost/serialization/access.hpp>
#include <boost/serialization/split_member.hpp>

#include <boost/utility.hpp>

#include "zlib.h"

#include "state.h"

namespace io = boost::iostreams;

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
    q_matrix_.resize(outer_cols_,outer_rows_,1,1);
    for (int i = 0; i < static_cast<int>(q_matrix_.size1()); ++ i) {
      for (int j = std::max(i-1, 0); j < std::min(i+2, static_cast<int>(q_matrix_.size2())); ++j) {
        q_matrix_(i, j).resize(inner_cols_,inner_rows_);
        q_matrix_(i, j).clear();
      }
    }
  }

  gzFile read_file_(gzFile file, std::size_t N) {
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
                   std::size_t N = std::numeric_limits<std::size_t>::max()) {
    gzFile file = gzopen(filename.c_str(), "r");
    return read_file_(file,N);
  }

  gzFile read_file(gzFile file,
                   std::size_t N = std::numeric_limits<std::size_t>::max()) {
    return read_file_(file,N);
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
              printf("%lu %lu %lu %lu %f\n",
                     ni,
                     nj,
                     ei,
                     ej,
                     q_matrix_(ni,nj)(ei,ej));
            }
          }
        }
      }
    }
  }

  void calculate_dos() {
    State::lease s;
    std::size_t nParticles(s->n_particles());
    std::size_t nEnergy(s->n_energy());

    calc_float_t zero(0), one(1), crit(1.0e-7), dist(0);
    std::size_t i(0);
    dos_matrix_t dos(nParticles,nEnergy);
  	dos_matrix_t dos_old(nParticles,nEnergy);
  	std::fill(dos_old.data().begin(), dos_old.data().end(), 1.0/dos_old.data().size());


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
            boost::numeric::ublas::matrix_column< inner_matrix_t > m1(q_matrix_(ni, nj), ej);
            boost::numeric::ublas::matrix_row< dos_matrix_t > m2(dos_old, ni);
            calc_float_t incr(boost::numeric::ublas::inner_prod(m1,m2));
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
                  << " seconds/iterations, current dist: " << dist
                  << std::endl;
        print_dos(dos, i);
        t.restart();
      }
    }
    return;
  }

  void print_dos(const dos_matrix_t& dos, std::size_t iteration) const {
    char filename[50];
    sprintf( filename, "dos.%05lu.dat.gz", iteration);

    State::lease s;
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
              << std::setw(20) << std::right << j
              << std::setw(20) << std::right << (log_dos + fakln)
              << std::setw(20) << std::right << log_dos
              << std::setw(20) << std::right << dos(i,j)
              << "\n";
        }
      }
    }
  }

  void check_detailed_balance() {
    matrix_t balance(outer_rows_, inner_rows_);
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
  }

private:
  friend class boost::serialization::access;

  template<class Archive>
  void save(Archive & ar, const unsigned int /* version */) const {
    ar << outer_cols_;
    ar << outer_rows_;
    ar << inner_cols_;
    ar << inner_rows_;

    for (int i = 0; i < static_cast<int>(outer_cols_); ++i) {
      for (int j = std::max(i-1, 0);
           j < std::min(i+2, static_cast<int>(outer_rows_));
           ++j) {
        ar << q_matrix_(i, j);
      }
    }
  }

  template<class Archive>
  void load(Archive & ar, const unsigned int /* version */) {
    ar >> outer_cols_;
    ar >> outer_rows_;
    ar >> inner_cols_;
    ar >> inner_rows_;

    resize();

    for (int i = 0; i < static_cast<int>(outer_cols_); ++i) {
      for (int j = std::max(i-1, 0);
           j < std::min(i+2, static_cast<int>(outer_rows_));
           ++j) {
        ar >> q_matrix_(i, j);
      }
    }
  }

public:
  BOOST_SERIALIZATION_SPLIT_MEMBER()

};

#endif /* _Q_MATRIX_H_ */
