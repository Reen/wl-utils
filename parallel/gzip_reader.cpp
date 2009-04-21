#include "parallel/gzip_reader.h"
#include <iostream>

#define BYTES_TO_READ 100000000

GzipReader::GzipReader(gzFile file, std::size_t N)
    : filter(true),
      file_(file), N_(N), N_read_(0), N_to_read_(N), N_last_read_(0),
      next_slice(InputSlice::allocate(BYTES_TO_READ)) {}

GzipReader::~GzipReader() {
    next_slice->free();
}

void* GzipReader::operator()(void*) {
  // großes N ist Anzahl an Zeilen
  // kleines n ist Anzahl Bytes
  if (N_to_read_ == 0) {
    return 0;
  }
  size_t N_by_line = (N_to_read_ < N_last_read_ ? N_to_read_ : 1);
  // N_by_line is 1 if we have not reached the end yet
  if (N_by_line == 1) {
    size_t n_avail = next_slice->avail();
    int n_read  = gzread(file_, next_slice->end(), n_avail-1000);
    if (n_read < 1 && next_slice->size()==0) {
        // No more characters to process
        return NULL;
    }
    next_slice->set_end(next_slice->end() + n_read);
  }
  for (size_t line = 0; line < N_by_line; ++line) {
    gzgets(file_, next_slice->end(), 1000);
    size_t n_temp = strlen(next_slice->end());
    if (n_temp == Z_NULL && next_slice->size()==0) {
        // No more characters to process
        return NULL;
    }
    next_slice->set_end(next_slice->end() + n_temp);
  }
  InputSlice* ret = next_slice;
  next_slice = InputSlice::allocate(BYTES_TO_READ);
  N_last_read_ = ret->count_newline();
  N_read_ += N_last_read_;
  N_to_read_ = N_-N_read_;
  std::cout <</* n_read << " " <<*/ ret->size() << " " << N_last_read_ << " "
            << N_read_ << " " << N_to_read_ << std::endl;
  return ret;
}