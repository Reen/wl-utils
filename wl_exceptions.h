#ifndef WL_EXCEPTIONS_H_I45893BK
#define WL_EXCEPTIONS_H_I45893BK

// exceptions
#include <exception>

class file_exception : public std::exception {
public:
  file_exception() : what_("File handling error!") {}
  file_exception(std::string what) : what_(what) {}
  std::string what() {
    return what_;
  }
  virtual ~file_exception() throw() {}
private:
  std::string what_;
};

class file_not_found : public file_exception {
public:
  file_not_found(std::string filename)
      : file_exception("Can't find file " + filename) {}
};

#endif /* end of include guard: WL_EXCEPTIONS_H_I45893BK */
