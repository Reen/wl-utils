#ifndef EXACT_DOS_H_3PRDUQ46
#define EXACT_DOS_H_3PRDUQ46

#include <mpfrcpp/mpfrcpp.hpp>
#include <mpfrcpp/initialization/initialization.cpp>


#define Power(x, y)     (mpfr::Pow((x), (y)))
#define Sqrt(x)         (mpfr::Sqrt((x)))
#define Log(x)          (mpfr::Log((x)))
#define Pi              (mpfr::Constant.pi())

// g++ error.cpp -o error -I/Users/rene/towhee/svn/tbt/include/ -I/sw/include -L/sw/lib -lmpfr

template<class T>
class ExactDos {
public:
  typedef T value_type;

private:
  value_type Epsilon;
  value_type Sigma;
  value_type L;
  value_type zero;

public:
  ExactDos(value_type epsilon, value_type sigma, value_type size)
      : Epsilon(epsilon), Sigma(sigma), L(size), zero(0) {
  }

  value_type operator()(const value_type& U) {
    if ((U < zero && U + (256*Epsilon*Power(Sigma,6)*(Power(L,6) - 64*Power(Sigma,6)))/Power(L,12) > zero) || U > zero) {
      return (
        (
          Sqrt(2)*Pi*Epsilon*(
            U + 2*Epsilon - 2*Sqrt(Epsilon*(U + Epsilon))
          )*Power(Sigma,3)
        )/(
          3*Power(U,2)*Sqrt(Epsilon*(U + Epsilon))*Sqrt(
            (-Epsilon + Sqrt(Epsilon*(U + Epsilon)))/U
          )
        )
      );
    }
    if(U + (256*Epsilon*Power(Sigma,6)*(Power(L,6) - 64*Power(Sigma,6)))/Power(L,12) <= zero) {
      return (
        (Sqrt(2)*Pi*Epsilon*((U + 2*Epsilon - 2*Sqrt(Epsilon*(U + Epsilon)))/Sqrt((-Epsilon + Sqrt(Epsilon*(U + Epsilon)))/U) +
           (U + 2*(Epsilon + Sqrt(Epsilon*(U + Epsilon))))/Sqrt(-((Epsilon + Sqrt(Epsilon*(U + Epsilon)))/U)))*Power(Sigma,3))/
       (3*Power(U,2)*Sqrt(Epsilon*(U + Epsilon)))
      );
    }
    return 0;
  }

  value_type operator[](const value_type& U) {
    return Log((*this)(U));
  }
};

#endif /* end of include guard: EXACT_DOS_H_3PRDUQ46 */
