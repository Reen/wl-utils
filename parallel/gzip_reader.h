#ifndef GZIP_READER_H_X1I0YHN0
#define GZIP_READER_H_X1I0YHN0

#include "tbb/pipeline.h"
#include "parallel/input_slice.h"
#include "zlib.h"

class GzipReader : public tbb::filter {
public:
  GzipReader(gzFile file, std::size_t N);
  ~GzipReader();
private:
  gzFile file_;
  std::size_t N_;
  std::size_t N_read_;
  std::size_t N_to_read_;
  std::size_t N_last_read_;
  InputSlice *next_slice;
  void* operator()(void*);
};

#endif /* end of include guard: GZIP_READER_H_X1I0YHN0 */
