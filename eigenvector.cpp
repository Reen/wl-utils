#include "eigenvector.h"
#include "misc.h"
#include "state.h"

#include <numeric>
#include <iomanip>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/operation.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/progress.hpp>

namespace io = boost::iostreams;
namespace ublas = boost::numeric::ublas;

void print_dos(const std::string& prefix,
               const QMatrix<double>::dos_matrix_t& dos,
               std::size_t iteration, bool print_all=true) {
  char filename[5000];
  State::lease s;
  snprintf(filename, 5000, "%s%s.%06lu.dat.gz",
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

void broad_histogram(QMatrix<double>::matrix_t & mat,
                     QMatrix<double>::dos_matrix_t & dos) {
  State::lease s;
  std::size_t nParticles(s->n_particles());
  std::size_t nEnergy(s->n_energy());
  std::size_t outer_rows(mat.size1());
  std::size_t outer_cols(mat.size2());
  std::size_t inner_rows(mat(0,0).size1());
  std::size_t inner_cols(mat(0,0).size1());
  if (outer_cols != 1 || outer_rows != 1) {
    return;
  }

  dos.resize(nParticles,nEnergy);
  dos.clear();
  // minor column
  for (std::size_t ei = 0; ei < inner_cols-1; ++ei) {
    std::size_t ej = ei+1;
    double log_frac = log(mat(0,0)(ei,ej) / mat(0,0)(ej,ei));
    if(!boost::math::isfinite(log_frac) && (ej + 1) < inner_cols) {
      log_frac = log(mat(0,0)(ei,ej+1) / mat(0,0)(ej+1,ei));
    }
    dos(0,ej) = dos(0,ei) + log_frac;
    //std::cout << ei << " " << ej << " " << dos(0,ei) << " " << (mat(0,0)(ei,ej) / mat(0,0)(ej,ei)) << " " << mat(0,0)(ei,ej) << " " << mat(0,0)(ej,ei) << std::endl;
  }
  for (std::size_t ei = 0; ei < inner_cols; ++ei) {
    dos(0,ei) = exp(dos(0,ei));
  }
  print_dos("bh", dos, 1, true);
  dos /= std::inner_product(dos.data().begin(), dos.data().end(), dos.data().begin(),0.0);
}

void calculate_dos_power_iteration(QMatrix<double>::matrix_t & mat,
                                   QMatrix<double>::dos_matrix_t & dos,
                                   QMatrix<double>::dos_matrix_t & dos_old,
                                   std::string prefix) {
  std::cerr << "calculating dos via power iteration" << std::endl;
  typedef ublas::matrix<bool> bool_matrix_t;
  typedef ublas::banded_matrix< std::vector<std::pair<std::size_t,std::size_t> > > pair_matrix_t;
  double crit(1.0e-7), dist(0), dist_old(0);
  std::size_t i(0);
  std::size_t outer_rows(mat.size1());
  std::size_t outer_cols(mat.size2());
  std::size_t inner_rows(mat(0,0).size1());
  std::size_t inner_cols(mat(0,0).size2());
  std::size_t num_filled;
  bool_matrix_t zero_mat(outer_rows, inner_rows);
  pair_matrix_t pair_mat(outer_rows, outer_cols, 1, 1);
  zero_mat.clear();

  for (std::size_t ni = 0; ni < outer_rows; ++ni)
  {
    int s_ni = int(ni);
    for (std::size_t ei = 0; ei < inner_rows; ++ei)
    {
      for (std::size_t nj = std::max(s_ni-1, 0); nj < std::min(ni+2, outer_cols); ++nj)
      {
        pair_mat(ni, nj).resize(inner_rows);
        bool have_first = false;
        for (std::size_t ej = 0; ej < inner_rows; ++ej)
        {
          if(mat(ni, nj)(ei, ej) != 0) {
            zero_mat(ni, ei) = true;
            if (!have_first) {
              pair_mat(ni, nj)[ei].first = ej;
              have_first = true;
            }
            pair_mat(ni, nj)[ei].second = ej;
          }
        }
#ifndef NDEBUG
        std::cerr << ni << " " << nj << " " << ei << " " << (int)zero_mat(ni, ei) << " " << pair_mat(ni, nj)[ei].first << " " << pair_mat(ni, nj)[ei].second << std::endl;
#endif
      }
    }
  }
  num_filled = (zero_mat.data().size() - std::accumulate(zero_mat.data().begin(), zero_mat.data().end(), 0u));
  // begin simple Power Iteration Method
  boost::timer t;
  while (true) {
    i++;
    dos.clear();
    // do the matrix-vector-multiplication
    double n(0);
    for (std::size_t ni = 0; ni < outer_rows; ++ni)
    {
      int s_ni = int(ni);
      for (std::size_t ei = 0; ei < inner_rows; ++ei)
      {
        if(!zero_mat(ni,ei)) {
          dos(ni,ei) = 0;
          continue;
        }
        for (std::size_t nj = std::max(s_ni-1, 0); nj < std::min(ni+2, outer_cols); ++nj)
        {
          double incr(ublas::inner_prod(
            ublas::subrange(ublas::matrix_row< QMatrix<double>::inner_matrix_t >(mat(ni, nj), ei), pair_mat(ni, nj)[ei].first, pair_mat(ni, nj)[ei].second+1),
            ublas::subrange(ublas::matrix_row< QMatrix<double>::dos_matrix_t >(dos_old, nj), pair_mat(ni, nj)[ei].first, pair_mat(ni, nj)[ei].second+1)
          ));
          dos(ni, ei) += incr;
          n += incr;
        }
      }
    }

    dos /= n;


    // check wether the iteration has converged
    bool converged = true;
    for (QMatrix<double>::dos_matrix_t::array_type::iterator
         i1(dos.data().begin()), i2(dos_old.data().begin());
         i1 < dos.data().end();
         ++i1, ++i2) {
      if (*i1 > 0) {
        if (converged && fabs((*i2)/(*i1)-1) > crit) {
          dist = (*i2)/(*i1);
          converged = false;
          break;
        }
      }
    }

    if (converged) {
      print_dos(prefix, dos, i, false);
      break;
    }

    if (i%1000 == 0) {
      std::cout << "I: "
                << std::setw(10) << std::right << i
                << std::setw(10) << std::right << (1000.0/t.elapsed())
                << " iterations/second, d: "
                << std::setw(12) << std::right << (dist-1.0)
                << std::setw(10) << std::right << num_filled
                << std::endl;
      print_dos(prefix, dos, i, false);
      t.restart();
    }

    dos_old.swap(dos);
    dist_old = dist;
  }
}

/**
 * Implementation of the GTH method of fenwick.m.06.accurate.144905.
 * Given up as the matrix size exeeds the available memory size.
 * We only use it for canonical ensembles.
 * E.g. (111*300)^2  * 8 ~=  8 GB
 *      (111*1000)^2 * 8 ~= 80 GB
 */
void calculate_dos_gth(QMatrix<double>::inner_matrix_t inner_mat, // copy
                      ublas::matrix_row<QMatrix<double>::dos_matrix_t> & dos) { // hier die Zeile der jeweiligen Zustandsdichte
  std::cerr << "Calculating DOS using GTH method" << std::endl;
  std::size_t inner_rows(inner_mat.size1());
  std::size_t inner_cols(inner_mat.size1());
  // we assume small matrix and try GTH method
  // do GTH LU decomposition
  for (std::size_t i = inner_rows-1; i > 0; --i) {
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
  std::fill(dos.begin(), dos.end(), 0.0);//dos.clear();
  dos[0] = 1;
  for (std::size_t i = 1; i < inner_rows; ++i) {
    //std::cout << i << " " << dos.data()[i-1] << ": ";
    for (std::size_t j = 0; j < i; ++j) {
      //std::cout << "(" << dos.data()[j] << " " << dos.data()[i-1] << " " << log(whole(j,i)) << ") ";
      dos[i] += exp(dos[j] - dos[i-1] + log(inner_mat(j,i)));
    }
    //std::cout << ": "<< dos.data()[i] << "\n";
    dos[i] = dos[i-1] + log(dos[i]);
  }
  for (std::size_t ei = 0; ei < inner_cols; ++ei) {
    dos(ei) = exp(dos(ei)-5);
  }
  //print_dos("gth", dos, 4);
}

void calcdos(std::string filepath) {
  CompressionType ct = getFileCompression(filepath);

  io::filtering_istream in;
  openMatrixFileRead(in, filepath, ct);
  State::lease s;
  s->load_from(in);
  if (s->matrix_type() != 2) {
    throw std::runtime_error("Double Matrix expected, different data type found.");
  }
  QMatrix<double> qd;
  qd.load_from(in);
  in.pop();

  QMatrix<double>::dos_matrix_t dos(s->n_particles(),s->n_energy());
  QMatrix<double>::dos_matrix_t dos_old(s->n_particles(),s->n_energy());
  std::fill(dos_old.data().begin(), dos_old.data().end(), 1.0/dos_old.data().size());
  /*
  for (size_t i = 0; i < s->n_particles(); i++) {
    ublas::matrix_row< QMatrix<double>::dos_matrix_t > mr(dos_old, i);
    calculate_dos_gth(qd.matrix()(i,i), mr);
  }
  print_dos("dos", dos_old, 0);
  */

  std::string prefix;
  calculate_dos_power_iteration(qd.matrix(), dos, dos_old, generateOutputPrefix(filepath, "dos"));

  //io::filtering_ostream out;
  //std::string outfilepath = generateOutputFilename(filepath);
  //openMatrixFileWrite(out, outfilepath, ct);
  //s->save_to(out);
}

