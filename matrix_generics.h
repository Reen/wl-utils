#ifndef _MATRIX_GENERICS_H_
#define _MATRIX_GENERICS_H_

#include <boost/numeric/ublas/matrix.hpp>

#include <boost/iostreams/char_traits.hpp> // EOF, WOULD_BLOCK
#include <boost/iostreams/concepts.hpp>    // input_filter
#include <boost/iostreams/operations.hpp>  // get

#include <boost/function.hpp>

class shell_comments_input_filter : public boost::iostreams::input_filter {
public:
    explicit shell_comments_input_filter(char comment_char = '#')
        : comment_char_(comment_char), skip_(false)
        { }

    template<typename Source>
    int get(Source& src)
    {
        int c;
        while (true) {
            if ((c = boost::iostreams::get(src)) == EOF || c == boost::iostreams::WOULD_BLOCK)
                break;
            skip_ = c == comment_char_ ?
                true :
                c == '\n' ?
                    false :
                    skip_;
            if (!skip_)
                break;
        }
        return c;
    }

    template<typename Source>
    void close(Source&) { skip_ = false; }
private:
    char comment_char_;
    bool skip_;
};

template<class T>
struct value_to_bin {
  typedef std::size_t size_type;
  
  value_to_bin(T offset, T bin_width)
   : offset_(offset), bin_width_(bin_width) {}
  
  size_type operator()(const T& value) {
    return static_cast<size_type>((value-offset_)/bin_width_);
  }
  
private:
  T bin_width_;
  T offset_;
};

template<class T1, class T2, class T, class A, class B>
void read_matrix_from_stream(std::istream& in,
                         boost::numeric::ublas::matrix<T,A,B>& matrix,
                         std::size_t value_column,
                         boost::function<std::size_t (const T1&)> f1,
                         boost::function<std::size_t (const T2&)> f2) {
  T1 x_coord;
  T2 y_coord;
  T  value, dummy;
  std::size_t i,j;
  std::string line;
  std::size_t count(0);
  /* if e.g. value_colum == 5 and we alredy read 2 cols we still have 
   * to consume 2 cols more into /dev/null ... */
  value_column -= 3;
  std::cout << matrix.size1() << " " << matrix.size2() << std::endl;
  while (std::getline(in,line)) {
    if(line.size() > 0) {
      std::istringstream iss(line);
      iss >> x_coord;
      iss >> y_coord;
      for (int k = 0; k < value_column; ++k) {
        iss >> dummy;
      }
      iss >> value;
      i = f1(x_coord);
      j = f2(y_coord);
      //std::cout << i << " " << j << " " << y_coord << " " << value << std::endl;
      matrix(i,j) = value;
    }
  }
}

bool argv_has(int argc, char *argv[], const std::string& arg) {
  for (int i = 0; i < argc; ++i) {
    if (argv[i] == arg) {
      return true;
    }
  }
  return false;
}

#endif /* _MATRIX_GENERICS_H_ */
