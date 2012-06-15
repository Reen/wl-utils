#ifndef EIGENVECTOR_RWZKSNZX

#define EIGENVECTOR_RWZKSNZX

#include <string>
#include "q_matrix.h"


void calculate_dos_power_iteration(QMatrix<double> & mat,
                                   QMatrix<double>::dos_matrix_t & dos,
                                   QMatrix<double>::dos_matrix_t & dos_old,
                                   int maxIter);

void calcdos(std::string, int maxIter);

#endif /* end of include guard: EIGENVECTOR_RWZKSNZX */