#ifndef PARQ_TRANSFORM_FILTER_H_PA3GNQL9
#define PARQ_TRANSFORM_FILTER_H_PA3GNQL9

#include "tbb/pipeline.h"
#include "q_matrix.h"

#include "tbb/spin_mutex.h"
typedef boost::numeric::ublas::banded_matrix< tbb::spin_mutex > spin_mutex_matrix;
typedef boost::numeric::ublas::banded_matrix<boost::numeric::ublas::matrix< uint32_t, boost::numeric::ublas::column_major >, boost::numeric::ublas::column_major > int_q_matrix_t;

class ParQTransformFilter : public tbb::filter {
  std::size_t minParticles;
  double minEnergy;
  double energyBinWidth;
  int_q_matrix_t& q_matrix_;
  spin_mutex_matrix &q_mutex_;
  std::size_t outer_cols_;
  std::size_t outer_rows_;
  std::size_t inner_cols_;
  std::size_t inner_rows_;
public:
  ParQTransformFilter(int_q_matrix_t &qm, spin_mutex_matrix &qmut);
  void* operator()(void* item);
};

#endif /* end of include guard: PARQ_TRANSFORM_FILTER_H_PA3GNQL9 */
