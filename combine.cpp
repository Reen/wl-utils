#include "combine.h"
#include "misc.h"
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/shared_ptr.hpp>
#include <sys/resource.h>
#include <errno.h>

namespace io = boost::iostreams;
namespace ublas = boost::numeric::ublas;

/**
 * Combine
 *
 * Combines parQ matrix files (integer) into one file by adding up all the matrices.
 * It acts like a stream processor and does not need memory for a full matrix.
 * On a downside it is restricted to the number of files a user is allowed to open.
 * It checks that conditions and presents a warning in the unlikely event of
 * combining more than ~256 files.
 */
int combine(std::vector<std::string> files) {
  // local variables
  uint32_t tmp, version = 0;
  uint32_t mtype, ghstrlen;
  uint32_t outer_cols, outer_rows, inner_cols, inner_rows;
  char githead[100];
  const std::size_t settingslen = 4 * sizeof(uint32_t) + 4 * sizeof(double);
  char settings[settingslen];
  // we can copy / assign filtering_istreams, so we use a vector of shared pointers
  typedef boost::shared_ptr<io::filtering_istream> filter_type;
  std::vector<filter_type> ins;
  io::filtering_ostream out;
  std::vector<CompressionType> cts;
  std::string githeadref;
  ins.resize(files.size());
  cts.resize(files.size());
  ublas::matrix<int32_t> sum, mtmp;
  // check for limit of open files
  if (fileLimitReached(files.size())) {
    return EXIT_FAILURE;
  }
  for (int i = 0; i < files.size(); i++) {
    std::cout << "reading: " << files[i] << std::endl;
    cts[i] = getFileCompression(files[i]);
    ins[i] = filter_type(new io::filtering_istream);
    openMatrixFileRead(*ins[i], files[i], cts[i]);
    // version
    ins[i]->read((char*)&tmp, sizeof(tmp));
    if (tmp != 1) {
      throw std::runtime_error("Unknown parq matrix file version.");
    }
    if (version == 0) {
      version = tmp;
    }
    if (tmp != version) {
      throw std::runtime_error("Matrix files have different versions.");
    }
    // matrix type
    ins[i]->read((char*)&mtype, sizeof(mtype));
    if (mtype != 1) {
      throw std::runtime_error("Integer matrix expected.");
    }
    // githead strlen
    ins[i]->read((char*)&ghstrlen, sizeof(ghstrlen));
    if (ghstrlen > 100) {
      throw std::runtime_error("githead strlen longer than expected");
    }
    // githead
    ins[i]->read(githead, ghstrlen);
    if (githeadref.size() == 0) {
      githeadref = githead;
    }
    if (githead != githeadref) {
      throw std::runtime_error("combining matrix files from different towhee versions currently not supported");
    }
    ins[i]->read(settings, settingslen);
    ins[i]->read((char*)&outer_cols, sizeof(outer_cols));
    ins[i]->read((char*)&outer_rows, sizeof(outer_rows));
    ins[i]->read((char*)&inner_cols, sizeof(inner_cols));
    ins[i]->read((char*)&inner_rows, sizeof(inner_rows));
    if (outer_cols != outer_rows || inner_cols != inner_rows) {
      throw std::runtime_error("Error reading size of matrix");
    }
  }
  std::string outfn = generateOutputFilename(files[0], "comb");
  openMatrixFileWrite(out, outfn, cts[0]);
  out.write((char*)&version, sizeof(version));
  out.write((char*)&mtype, sizeof(mtype));
  out.write((char*)&ghstrlen, sizeof(ghstrlen));
  out.write(githeadref.c_str(), ghstrlen);
  out.write(settings, settingslen);
  out.write((char*)&outer_cols, sizeof(outer_cols));
  out.write((char*)&outer_rows, sizeof(outer_rows));
  out.write((char*)&inner_cols, sizeof(inner_cols));
  out.write((char*)&inner_rows, sizeof(inner_rows));
  sum.resize(inner_rows, inner_cols);
  mtmp.resize(inner_rows, inner_cols);
  for (int i = 0; i < static_cast<int>(outer_cols); ++i) {
    for (int j = std::max(i-1, 0);
         j < std::min(i+2, static_cast<int>(outer_rows));
         ++j) {
      for (int k = 0; k < ins.size(); k++) {
        ins[k]->read((char*)(&mtmp.data()[0]), inner_cols*inner_cols*sizeof(int32_t));
        sum += mtmp;
      }
      out.write((char*)(&sum.data()[0]), inner_cols*inner_cols*sizeof(int32_t));
      sum.clear();
    }
  }
  return EXIT_SUCCESS;
}


