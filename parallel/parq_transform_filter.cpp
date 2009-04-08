#include "parallel/parq_transform_filter.h"
#include "parallel/input_slice.h"
#include "state.h"

ParQTransformFilter::ParQTransformFilter(int_q_matrix_t &qm,
                                         spin_mutex_matrix &qmut)
    : tbb::filter(false),
      q_matrix_(qm),
      q_mutex_(qmut),
      outer_cols_(qm.size1()),
      outer_rows_(qm.size2()),
      inner_cols_(qm(0,0).size1()),
      inner_rows_(qm(0,0).size2()) {
  State::lease s;
  minParticles = s->min_particles();
  minEnergy = s->min_energy();
  energyBinWidth = s->energy_bin_width();
  //std::cout << minParticles << " " << minEnergy << " " << energyBinWidth << std::endl;
}

void* ParQTransformFilter::operator()(void* item) {
  InputSlice& input = *static_cast<InputSlice*>(item);
  char* p = input.begin();
  char* next_p = 0;
  int N1,N2;
  double E1,E2;
  while (true) {
    int rest = input.size()-(p-input.begin());
    if (rest < 1) break;
    //std::cout << __LINE__<< " " <<  << std::endl;
    next_p = static_cast<char*>(memchr(p, '\n', input.size()-(p-input.begin())));
    //std::cout << __LINE__<< " " << next_p-input.begin() << std::endl;
    *next_p = '\0';
    //std::cout << __LINE__<< std::endl;
    int ret = sscanf(p,"%i %i %lf %lf", &N1,&N2,&E1,&E2);
    //std::cout << p-input.begin() << " " << next_p-input.begin() << " " << next_p-p << " " << ret << std::endl;
    if (ret != 4) break;
    //std::cout << __LINE__<< std::endl;
    p = next_p+1;
    //std::cout << __LINE__<< std::endl;
    std::size_t ni1 = N1-minParticles;
    std::size_t ni2 = N2-minParticles;
    //std::cout << N << " " << N1 << " " << N2 << " " << E1 << " " << E2 << std::endl;
    if (ni1 < outer_cols_ && ni2 < outer_rows_) {
      std::size_t i1 = static_cast<size_t>((E1-minEnergy)/energyBinWidth);
      std::size_t i2 = static_cast<size_t>((E2-minEnergy)/energyBinWidth);
      if (i1 < inner_cols_ && i2 < inner_rows_) {
        tbb::spin_mutex::scoped_lock lock(q_mutex_(ni1,ni2));
        q_matrix_(ni1,ni2)(i1,i2)++;
      }
    }
  }
  input.free();
  return NULL;
}