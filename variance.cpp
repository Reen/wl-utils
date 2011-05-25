#include "variance.h"
#include "state.h"
#include "misc.h"
#include <algorithm>
#include <iostream>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

namespace io = boost::iostreams;
namespace ublas = boost::numeric::ublas;

typedef boost::shared_ptr<io::filtering_istream> filter_type;

template <class T>
void do_variance(std::vector<filter_type> &ins,
                 io::filtering_ostream &out,
                 MatrixDimensions &dimensions) {
  ublas::matrix<T> sum, mtmp;
  ublas::matrix<double>  sqsum, var;
  sum.resize(dimensions.inner_rows, dimensions.inner_cols);
  var.resize(dimensions.inner_rows, dimensions.inner_cols);
  sqsum.resize(dimensions.inner_rows, dimensions.inner_cols);
  mtmp.resize(dimensions.inner_rows, dimensions.inner_cols);
  for (int i = 0; i < static_cast<int>(dimensions.outer_cols); ++i) {
    for (int j = std::max(i-1, 0);
         j < std::min(i+2, static_cast<int>(dimensions.outer_rows));
         ++j) {
      for (int k = 0; k < ins.size(); k++) {
        ins[k]->read((char*)(&mtmp.data()[0]), dimensions.inner_cols*dimensions.inner_cols*sizeof(T));
        for (int l = 0; l < mtmp.data().size(); l++) {
          sum.data()[l] += mtmp.data()[l];
          sqsum.data()[l] += (double)mtmp.data()[l]*mtmp.data()[l];
        }
      }
      double dN = static_cast<double>(ins.size());
      for (int l = 0; l < sum.data().size(); l++) {
        var.data()[l] = (sqsum.data()[l]/dN - (sum.data()[l]/dN * sum.data()[l]/dN));
      }
      out.write((char*)(&var.data()[0]), dimensions.inner_cols*dimensions.inner_cols*sizeof(double));
      sum.clear();
      sqsum.clear();
      var.clear();
    }
  }
}

void variance(std::vector<std::string> files) {
  typedef boost::shared_array<char> charp_type;
  std::vector<MatrixHeader>        headers(files.size());
  std::vector<charp_type>         githeads(files.size());
  std::vector<MatrixSettings>     settings(files.size());
  std::vector<MatrixDimensions> dimensions(files.size());
  std::vector<filter_type>             ins(files.size());
  std::vector<CompressionType>         cts(files.size());
  /**
   * INPUT
   */
  for (int i = 0; i < files.size(); i++) {
    std::cout << "reading: " << files[i] << std::endl;
    cts[i] = getFileCompression(files[i]);
    ins[i] = filter_type(new io::filtering_istream);
    openMatrixFileRead(*ins[i], files[i], cts[i]);
    ins[i]->read((char*)&(headers[i]), sizeof(MatrixHeader));
    checkMatrixHeader(headers[i], 1, 1, false); // throws exeption if version or type mismatch
    if (headers[i].githead_strlen > 0) {
      githeads[i] = charp_type(new char[headers[i].githead_strlen + 1]);
      ins[i]->read(githeads[i].get(), headers[i].githead_strlen);
      githeads[i][headers[i].githead_strlen] = '\0';
      if (i > 0 && strcmp(githeads[0].get(), githeads[i].get())) {
        throw std::runtime_error("Matrix files produced with different towhee versions. Not supported!");
      }
    }
    ins[i]->read((char*)&(settings[i]), sizeof(MatrixSettings));
    ins[i]->read((char*)&(dimensions[i]), sizeof(MatrixDimensions));
  }
  if ((files.size() != std::count(headers.begin(), headers.end(), headers[0]))
      || (files.size() != std::count(settings.begin(), settings.end(), settings[0]))
      || (files.size() != std::count(dimensions.begin(), dimensions.end(), dimensions[0]))) {
    throw std::runtime_error("Matrix headers differ.");
  }
  /**
   * OUTPUT
   */
  std::string outfn = generateOutputFilename(files[0], "var");
  io::filtering_ostream out;
  openMatrixFileWrite(out, outfn, cts[0]);
  // set output matrix type to double
  MatrixHeader outHeader = headers[0];
  outHeader.matrix_type = 2;
  out.write((char*)&(outHeader), sizeof(MatrixHeader));
  if (outHeader.githead_strlen > 0) {
    out.write(githeads[0].get(), outHeader.githead_strlen);
  }
  out.write((char*)&(settings[0]), sizeof(MatrixSettings));
  out.write((char*)&(dimensions[0]), sizeof(MatrixDimensions));

  if (outHeader.matrix_type == 0) {
    do_variance<double>(ins, out, dimensions[0]);
  } else {
    do_variance<int32_t>(ins, out, dimensions[0]);
  }

  return;
}
