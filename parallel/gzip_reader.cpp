#include "parallel/gzip_reader.h"
#include <iostream>

GzipReader::GzipReader(gzFile file, std::size_t N)
    : filter(true),
      file_(file), N_(N),
      next_slice(InputSlice::allocate(10000000)) {}

GzipReader::~GzipReader() {
    next_slice->free();
}

void* GzipReader::operator()(void*) {
  size_t n_avail = next_slice->avail();
  int n_read  = gzread(file_, next_slice->end(), n_avail-1000);
  if (n_read < 1 && next_slice->size()==0) {
      // No more characters to process
      return NULL;
  }
  next_slice->set_end(next_slice->end() + n_read);
  gzgets(file_, next_slice->end(), 1000);
  size_t n_temp = strlen(next_slice->end());
  if (n_temp == Z_NULL && next_slice->size()==0) {
      // No more characters to process
      return NULL;
  }
  next_slice->set_end(next_slice->end() + n_temp);
  InputSlice* ret = next_slice;
  next_slice = InputSlice::allocate(10000000);
  N_read_ += ret->count_newline();
  std::cout << n_read << " " << n_temp << " " << ret->size() << " "
            << N_read_ << " " << (N_-N_read_) << std::endl;
  return ret;
}
