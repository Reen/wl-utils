#include "normalize.h"
#include <stdint.h>
#include "q_matrix.h"
#include "state.h"

void do_normalization(QMatrix<int32_t>::matrix_t & imat,
                      QMatrix<double>::matrix_t & dmat) {
  State::lease s;
  std::size_t outer_rows(imat.size1());
  std::size_t outer_cols(imat.size2());
  std::size_t inner_rows(imat(0,0).size1());
  std::size_t inner_cols(imat(0,0).size2());

  for (std::size_t ni = 0; ni != outer_cols; ++ni) {
    int s_ni = int(ni);
    // minor column
    for (std::size_t ei = 0; ei < inner_cols; ++ei) {
      double i_sum(0);
      // major row
      for (std::size_t nj = std::max(s_ni-1, 0);
           nj < std::min(ni+2, outer_rows);
           ++nj) {
        // minor row
        for (std::size_t ej = 0; ej < inner_rows; ++ej) {
          i_sum += imat(nj, ni)(ej, ei);
        }
      }
      if (i_sum > 0) {
        double d_sum(i_sum);
        // major row
        for (std::size_t nj = std::max(s_ni-1, 0);
             nj < std::min(ni+2, outer_rows);
             ++nj) {
          // minor row
          for (std::size_t ej = 0; ej < inner_rows; ++ej) {
            // copy and divide by column sum
            dmat(ni, nj)(ei, ej) =
              static_cast<double>(imat(ni, nj)(ei, ej)) / d_sum;
          }
        }
      } // else -> all values in the column are zero so we do nothing
    }
  }
  /*for (std::size_t nj = 0; nj < outer_rows; ++nj)
  {
    int s_nj = int(nj);
    for (std::size_t ni = std::max(s_nj-1, 0); ni < std::min(nj+2, outer_cols); ++ni)
    {
      if (ni != nj && ni < nj) {
        dmat(ni, nj).swap(dmat(nj,ni));
        dmat(ni, nj) = trans(dmat(ni,nj));
        dmat(nj, ni) = trans(dmat(nj,ni));
      } else if(ni == nj) {
        dmat(ni, nj) = trans(dmat(ni,nj));
      }
    }
  }*/
}

void normalize(std::string filepath) {
  CompressionType ct = getFileCompression(filepath);

  io::filtering_istream in;
  openMatrixFileRead(in, filepath, ct);
  State::lease s;
  s->load_from(in);
  if (s->matrix_type() != 1) {
    throw std::runtime_error("Integer Matrix expected, different data type found.");
  }
  QMatrix<int32_t> qi;
  qi.load_from(in);
  in.pop();

  QMatrix<double> qd(qi.outer_rows(), qi.outer_cols(), qi.inner_rows(), qi.inner_cols());
  do_normalization(qi.matrix(), qd.matrix());
  s->set_matrix_type(2);

  io::filtering_ostream out;
  std::string outfilepath = generateOutputFilename(filepath);
  openMatrixFileWrite(out, outfilepath, ct);
  s->save_to(out);
  qd.save_to(out);
}
