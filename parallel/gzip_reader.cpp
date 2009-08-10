#include "parallel/gzip_reader.h"
#include <iostream>

#define BYTES_TO_READ 100000000

GzipReader::GzipReader(gzFile file, std::size_t N)
    : tbb::filter(true),
      file_(file), N_(N), N_read_(0), N_to_read_(N), N_last_read_(0),
      next_slice(InputSlice::allocate(BYTES_TO_READ)) {}

GzipReader::~GzipReader() {
  std::cout << "read: " << N_read_ << std::endl;
  next_slice->free();
}

void* GzipReader::operator()(void*) {
  // großes N ist Anzahl an Zeilen
  // kleines n ist Anzahl Bytes
  //std::cout << "startet writing to " << next_slice << std::endl;
  if (N_to_read_ == 0 || gzeof(file_)) {
    return NULL;
  }
  size_t N_by_line = (N_to_read_ < 1.1*N_last_read_ ? N_to_read_ : 1);
  // N_by_line is 1 if we have not reached the end yet
  if (N_by_line == 1) {
    size_t n_avail = next_slice->avail();
    int n_read  = gzread(file_, next_slice->end(), n_avail-2000);
    if (n_read < 1 && next_slice->size()==0) {
        // No more characters to process
        return NULL;
    }
    next_slice->set_end(next_slice->end() + n_read);
  }
  for (size_t line = 0; line < N_by_line; ++line) {
    if(next_slice->avail() < 1000) {
	break;
    }
    char* buf = gzgets(file_, next_slice->end(), 1000);
    size_t n_temp = strlen(next_slice->end());
    if (gzeof(file_)) {
	std::cout << "End of file reached."<< std::endl;
	break;
    }
    /*if (buf == Z_NULL && next_slice->size()==0) {
        // No more characters to process
        return NULL;
    }*/
    next_slice->set_end(next_slice->end() + n_temp);
  }
  //std::cout << "finished writing to " << next_slice << std::endl;
  InputSlice* ret = next_slice;
  next_slice = InputSlice::allocate(BYTES_TO_READ);
  N_last_read_ = ret->count_newline();
  N_read_ += N_last_read_;
  N_to_read_ = N_-N_read_;
  //std::cout << ret << " " << ret->size() << " " << N_last_read_ << " "
  //          << N_read_ << " " << N_to_read_ << std::endl;
  return ret;
}
