#ifndef Q_MATRIX_INTERFACE_H_6ASF7Z11
#define Q_MATRIX_INTERFACE_H_6ASF7Z11

#include <boost/utility.hpp>

template<class q_matrix_t>
class QMatrixInterface : boost::noncopyable {
public:
  q_matrix_t &q_matrix_;
public:
  QMatrixInterface(q_matrix_t &matrix)
      : q_matrix_(matrix) {}
};

#endif /* end of include guard: Q_MATRIX_INTERFACE_H_6ASF7Z11 */
