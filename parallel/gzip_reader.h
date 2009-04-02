#ifndef GZIP_READER_H_X1I0YHN0
#define GZIP_READER_H_X1I0YHN0

#include "tbb/pipeline.h"
#include "parallel/input_slice.h"
#include "zlib.h"

class GzipReader : public tbb::filter {
public:
  GzipReader(gzFile file);
  ~GzipReader();
private:
  gzFile file_;
  InputSlice *next_slice;
  void* operator()(void*);
};

#endif /* end of include guard: GZIP_READER_H_X1I0YHN0 */
