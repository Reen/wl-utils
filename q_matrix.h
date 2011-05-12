#ifndef _Q_MATRIX_H_
#define _Q_MATRIX_H_

#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
//#include <boost/iostreams/filter/bzip2.hpp>
namespace io = boost::iostreams;

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/banded.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>

template<class T>
void resize_matrix(T& matrix,
              std::size_t outer_cols_, std::size_t outer_rows_,
              std::size_t inner_cols_, std::size_t inner_rows_) {
  matrix.resize(outer_cols_,outer_rows_,1,1);
  for (int i = 0; i < static_cast<int>(matrix.size1()); ++i) {
    for (int j = std::max(i-1, 0); j < std::min(i+2, static_cast<int>(matrix.size2())); ++j) {
      matrix(i, j).resize(inner_cols_,inner_rows_);
      matrix(i, j).clear();
    }
  }
}

template<class T>
class QMatrix : boost::noncopyable {
public:
  typedef boost::numeric::ublas::matrix< T, boost::numeric::ublas::row_major > inner_matrix_t;
  typedef boost::numeric::ublas::banded_matrix< inner_matrix_t, boost::numeric::ublas::row_major > matrix_t;
  typedef boost::numeric::ublas::matrix< double, boost::numeric::ublas::row_major > dos_matrix_t;
protected:
  matrix_t q_matrix_;
  dos_matrix_t dos_matrix_;
  std::size_t outer_cols_;
  std::size_t outer_rows_;
  std::size_t inner_cols_;
  std::size_t inner_rows_;

  void resize() {
    resize_matrix(q_matrix_,
                  outer_cols_, outer_rows_, inner_cols_, inner_rows_);
  }

public:
  // constructor
  QMatrix(std::size_t n1,
          std::size_t n2,
          std::size_t n3,
          std::size_t n4) {
    resize(n1, n2, n3, n4);
  }

  QMatrix()
      : outer_cols_(0),
        outer_rows_(0),
        inner_cols_(0),
        inner_rows_(0) {
    resize();
  }

  const std::size_t& outer_cols() const {
    return outer_cols_;
  }

  const std::size_t& outer_rows() const {
    return outer_rows_;
  }
  const std::size_t& inner_cols() const {
    return inner_cols_;
  }
  const std::size_t& inner_rows() const {
    return inner_rows_;
  }

  void resize(std::size_t n1, std::size_t n2, std::size_t n3, std::size_t n4) {
    outer_cols_ = n1;
    outer_rows_ = n2;
    inner_cols_ = n3;
    inner_rows_ = n4;
    resize();
  }
  
  void clear() {
    for (int i = 0; i < static_cast<int>(outer_cols_); ++ i) {
      for (int j = std::max(i-1, 0);
           j < std::min(i+2, static_cast<int>(outer_rows_));
           ++j) {
        q_matrix_(i, j).clear();
      }
    }
  }

  const inner_matrix_t& operator()(const std::size_t &i,
                                   const std::size_t &j) const {
    return q_matrix_(i,j);
  }

  inner_matrix_t& operator()(const std::size_t &i,
                             const std::size_t &j) {
    assert(0 <= i);
    assert(0 <= j);
    assert(i < outer_rows_);
    assert(j < outer_cols_);
    return q_matrix_(i,j);
  }

  const matrix_t& matrix() const { return q_matrix_; }
  matrix_t& matrix() { return q_matrix_; }
  
  void save_to(io::filtering_ostream &out) {
    uint32_t o_c(outer_cols_), o_r(outer_rows_), i_c(inner_cols_), i_r(inner_rows_);
    out.write((char*)&o_c, sizeof(o_c));
    out.write((char*)&o_r, sizeof(o_r));
    out.write((char*)&i_c, sizeof(i_c));
    out.write((char*)&i_r, sizeof(i_r));
    std::cout << outer_cols_ << " " << outer_rows_ << " " << inner_cols_ << " " << inner_rows_ << "\n";

    for (int i = 0; i < static_cast<int>(outer_cols_); ++i) {
      for (int j = std::max(i-1, 0);
           j < std::min(i+2, static_cast<int>(outer_rows_));
           ++j) {
        out.write((char*)(&q_matrix_(i,j).data()[0]), q_matrix_(i,j).data().size() * sizeof(T));
      }
    }
  }

  void load_from(io::filtering_istream &in, bool do_resize = true) {
    uint32_t o_c, o_r, i_c, i_r;
    in.read((char*)&o_c, sizeof(o_c));
    in.read((char*)&o_r, sizeof(o_r));
    in.read((char*)&i_c, sizeof(i_c));
    in.read((char*)&i_r, sizeof(i_r));
    outer_cols_ = o_c;
    outer_rows_ = o_r;
    inner_cols_ = i_c;
    inner_rows_ = i_r;
    std::cout << "size: " << outer_cols_ << " " << outer_rows_ << " " << inner_cols_ << " " << inner_rows_ << "\n";

    if(do_resize) {
        resize();
    }

    for (int i = 0; i < static_cast<int>(outer_cols_); ++i) {
      for (int j = std::max(i-1, 0);
           j < std::min(i+2, static_cast<int>(outer_rows_));
           ++j) {
        in.read((char*)(&q_matrix_(i,j).data()[0]), q_matrix_(i,j).data().size() * sizeof(T));
      }
    }
  }
};

#endif /* _Q_MATRIX_H_ */
