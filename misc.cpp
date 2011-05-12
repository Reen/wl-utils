#include "misc.h"
#include <stdio.h>

#include <boost/filesystem.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <boost/regex.hpp>

#include "state.h"
#include "q_matrix.h"

namespace io = boost::iostreams;
namespace fs = boost::filesystem;

CompressionType getFileCompression(std::string filepath) {
  char head[4], gzip[] = {0x1f, 0x8b, 0x08}, bzip[] = {0x42, 0x5A, 0x68};
  // read first 3 bytes and check whether the file is uncompressed, gzip or bzip2 compressed.
  FILE * test = fopen(filepath.c_str(), "rb");
  fread(head, 1, 3, test);
  fclose(test);
  if (head[0] == gzip[0] && head[1] == gzip[1] && head[2] == gzip[2]) {
    return CT_GZIP;
  } else if (head[0] == bzip[0] && head[1] == bzip[1] && head[2] == bzip[2]) {
    return CT_BZIP2;
  } else {
    return CT_NONE;
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

std::string generateOutputFilename(std::string infile) {
  fs::path inpath(infile);
  inpath = fs::absolute(inpath);
  std::string infile_path(inpath.parent_path().string()),
              infile_name(inpath.filename().string()),
              outfile;
  static const boost::regex e(".dat");
  if (infile_name.find(".dat") != std::string::npos) {
    outfile = boost::regex_replace(infile_name, e, ".norm.dat", boost::match_default | boost::format_sed);
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


