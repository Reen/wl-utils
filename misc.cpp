#include "misc.h"
#include <stdio.h>
#include <sys/resource.h>

#include <boost/filesystem.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/regex.hpp>

#include "state.h"
#include "q_matrix.h"

namespace io = boost::iostreams;
namespace fs = boost::filesystem;

CompressionType getFileCompression(std::string filepath) {
  size_t ierr;
  char head[4], gzip[] = {0x1f, 0x8b, 0x08}, bzip[] = {0x42, 0x5A, 0x68};
  // read first 3 bytes and check whether the file is uncompressed, gzip or bzip2 compressed.
  FILE * test = fopen(filepath.c_str(), "rb");
  ierr = fread(head, 3, 1, test);
  if (ierr != 1) {
    perror("Could not determin compression type of file");
    exit(1);
  }
  fclose(test);
  if (head[0] == gzip[0] && head[1] == gzip[1] && head[2] == gzip[2]) {
    return CT_GZIP;
  } else if (head[0] == bzip[0] && head[1] == bzip[1] && head[2] == bzip[2]) {
    return CT_BZIP2;
  } else {
    return CT_NONE;
  }
}

void appendDecompressor(io::filtering_istream &in, std::string filepath) {
  CompressionType ct = getFileCompression(filepath);
  if (ct == CT_GZIP) {
    in.push(io::gzip_decompressor());
  } else if (ct == CT_BZIP2) {
    in.push(io::bzip2_decompressor());
  }
}

void openMatrixFileRead(io::filtering_istream &in, std::string filepath, CompressionType ct) {
  if (ct == CT_GZIP) {
    in.push(io::gzip_decompressor());
  } else if (ct == CT_BZIP2) {
    in.push(io::bzip2_decompressor());
  }
  in.push(io::file_source(filepath, std::ios::binary|std::ios::in));
}

void openMatrixFileWrite(io::filtering_ostream &out, std::string filepath, CompressionType ct) {
  if (ct == CT_GZIP) {
    out.push(io::gzip_compressor());
  } else if (ct == CT_BZIP2) {
    out.push(io::bzip2_compressor());
  }
  out.push(io::file_sink(filepath, std::ios::binary|std::ios::in));
}

std::string generateOutputFilename(std::string infile, std::string tag) {
  fs::path inpath(infile);
  inpath = fs::absolute(inpath);
  std::string infile_path(inpath.parent_path().string()),
              infile_name(inpath.filename().string()),
              outfile;
  static const boost::regex e(".dat");
  if (infile_name.find(".dat") != std::string::npos) {
    outfile = boost::regex_replace(infile_name, e, "."+tag+".dat", boost::match_default | boost::format_sed);
  } else {
    outfile += ".norm";
  }
  State::lease s;
  if (s->have_working_directory()) {
    return s->working_directory() + outfile;
  } else {
    return infile_path + "/" + outfile;
  }
}

std::string generateOutputPrefix(std::string infile, std::string tag) {
  fs::path inpath(infile);
  inpath = fs::absolute(inpath);
  std::string infile_path(inpath.parent_path().string()),
              infile_name(inpath.filename().string()),
              outfile;
  static const boost::regex e("\\..+");
  outfile = boost::regex_replace(infile_name, e, "."+tag, boost::match_default | boost::format_sed);
  State::lease s;
  if (s->have_working_directory()) {
    return s->working_directory() + outfile;
  } else {
    return infile_path + "/" + outfile;
  }
}

bool fileLimitReached(std::size_t num_files) {
  struct rlimit limit;
  if (getrlimit(RLIMIT_NOFILE, &limit) != 0) {
    std::cerr << "rlimit failed with errno=" << errno << std::endl;
    return true;
  } else {
    if (num_files > limit.rlim_cur) {
      std::cerr << "More matrix files specified than number of files allowed to be opened.\n"
                   "Please raise ulimit -n..." << std::endl;
      return true;
    }
  }
}

void checkMatrixHeader(const MatrixHeader &header,
                       uint32_t version,
                       uint32_t matrix_type,
                       bool check_matrix_type) {
  if (header.version != version) {
    throw std::runtime_error("Unknown parq matrix file version.");
  }
  if (check_matrix_type && header.matrix_type != matrix_type) {
    if (matrix_type == 1) {
      throw std::runtime_error("Integer matrix expected.");
    } else if (matrix_type == 2) {
      throw std::runtime_error("Double matrix expected.");
    } else {
      throw std::runtime_error("Matrix type mismatch. You requested unkown matrix type and got a different one.");
    }
  }
}
