#ifndef PARQ_TRANSFORM_FILTER_H_PA3GNQL9
#define PARQ_TRANSFORM_FILTER_H_PA3GNQL9

#include "tbb/pipeline.h"
#include "q_matrix.h"

#include "tbb/spin_mutex.h"
typedef boost::numeric::ublas::banded_matrix< tbb::spin_mutex > spin_mutex_matrix;

class ParQTransformFilter : public tbb::filter {
  std::size_t minParticles;
  double minEnergy;
  double energyBinWidth;
  QMatrix<uint32_t>& q_matrix_;
  spin_mutex_matrix &q_mutex_;
  std::size_t outer_cols_;
  std::size_t outer_rows_;
  std::size_t inner_cols_;
  std::size_t inner_rows_;
public:
  ParQTransformFilter(QMatrix<uint32_t> &qm,
                      spin_mutex_matrix &qmut);
  void* operator()(void* item);
};

#endif /* end of include guard: PARQ_TRANSFORM_FILTER_H_PA3GNQL9 */
