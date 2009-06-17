#ifndef MPFRCPP_TEST_COMPLEX
#define MPFRCPP_TEST_COMPLEX

/* This file is part of the MPFRCPP Library.

   Copyright (c) 2006--2007 Alexey V. Beshenov <al@beshenov.ru>.

   The MPFRCPP Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License as
   published by the Free Software Foundation; either version 2.1 of the
   License, or (at your option) any later version.

   The MPFRCPP Library is distributed in the hope that it will be
   useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the MPFRCPP Library; see the file COPYING.LIB. If
   not, write to the Free Software Foundation, Inc., 51 Franklin Street,
   Fifth Floor, Boston, MA 02110-1301, USA. */

/**
 * @file native_complex.hpp
 * @date 2007-04-07
 * MPFRCPP complex numbers test, mpfr::Complex.
 * Part of the library test suite.
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

#include <mpfrcpp/mpfrcpp.hpp>

#include <complex>
#include <iostream>
#include <mpfrcpp/extra/complex.hpp>

#define INCLUDED_BY_MPFRCPP
#include "random.hpp"
#undef INCLUDED_BY_MPFRCPP

namespace mpfr {
    namespace test {

        class NativeComplex {
            public:

                static void start () throw() {
                    std::ios_base::fmtflags old_flags = std::cout.flags();

                    std::cout.setf( std::ios_base::scientific );

                    std::cout << ">> MPFRCPP complex numbers test, mpfr::Complex" << std::endl;
                    std::cout << '(' << __FILE__ << ')' << std::endl;
                    std::cout << std::endl;

                    double dx, dy;
                    Real rx, ry;

                    dx = random ( -10.0, 10.0 );
                    rx = Real ( dx );
                    dy = random ( -10.0, 10.0 );
                    ry = Real ( dy );

                    std::complex<double> dz ( dx, dy );
                    Complex rz ( rx, dy );

                    std::cout << "complex<double> (double, double) :" << std::endl;
                    std::cout << "\tcomplex<double> (" << dx << ", " << dy << ") = " << dz << std::endl;
                    std::cout << "mpfr::Complex (mpfr::Real, mpfr::Real) :" << std::endl;
                    std::cout << "\tmpfr::Complex (" << rx << ", " << ry << ") = " << rz << std::endl;
                    std::cout << std::endl;

                    std::cout << "polar (double, double) :" << std::endl;
                    std::cout << "\tpolar (" << std::abs( dz ) << ", " << std::arg( dz ) << ") = " << dz << std::endl;
                    std::cout << "mpfr::polar (mpfr::Real, mpfr::Real) :" << std::endl;
                    std::cout << "\tmpfr::polar (" << abs( rz ) << ", " << arg( rz ) << ") = " << rz << std::endl;
                    std::cout << std::endl;

                    std::cout << "abs (complex<double>) :" << std::endl;
                    std::cout << "\tabs (" << dz << ") = " << std::abs( dz ) << std::endl;
                    std::cout << "mpfr::abs (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::abs (" << rz << ") = " << abs( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "arg (complex<double>) :" << std::endl;
                    std::cout << "\targ (" << dz << ") = " << std::arg( dz ) << std::endl;
                    std::cout << "mpfr::arg (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::arg (" << rz << ") = " << arg( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "conj (complex<double>) :" << std::endl;
                    std::cout << "\tconj (" << dz << ") = " << std::conj( dz ) << std::endl;
                    std::cout << "mpfr::conj (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::conj (" << rz << ") = " << conj( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "norm (complex<double>) :" << std::endl;
                    std::cout << "\tnorm (" << dz << ") = " << std::norm( dz ) << std::endl;
                    std::cout << "mpfr::norm (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::norm (" << rz << ") = " << norm( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "sqrt (complex<double>) :" << std::endl;
                    std::cout << "\tsqrt (" << dz << ") = " << std::sqrt( dz ) << std::endl;
                    std::cout << "mpfr::sqrt (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::sqrt (" << rz << ") = " << sqrt( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "sin (complex<double>) :" << std::endl;
                    std::cout << "\tsin (" << dz << ") = " << std::sin( dz ) << std::endl;
                    std::cout << "mpfr::sin (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::sin (" << rz << ") = " << sin( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "cos (complex<double>) :" << std::endl;
                    std::cout << "\tcos (" << dz << ") = " << std::cos( dz ) << std::endl;
                    std::cout << "mpfr::cos (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::cos (" << rz << ") = " << cos( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "tan (complex<double>) :" << std::endl;
                    std::cout << "\ttan (" << dz << ") = " << std::tan( dz ) << std::endl;
                    std::cout << "mpfr::tan (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::tan (" << rz << ") = " << tan( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "sinh (complex<double>) :" << std::endl;
                    std::cout << "\tsinh (" << dz << ") = " << std::sinh( dz ) << std::endl;
                    std::cout << "mpfr::sinh (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::sinh (" << rz << ") = " << sinh( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "cosh (complex<double>) :" << std::endl;
                    std::cout << "\tcosh (" << dz << ") = " << std::cosh( dz ) << std::endl;
                    std::cout << "mpfr::cosh (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::cosh (" << rz << ") = " << cosh( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "tanh (complex<double>) :" << std::endl;
                    std::cout << "\ttanh (" << dz << ") = " << std::tanh( dz ) << std::endl;
                    std::cout << "mpfr::tanh (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::tanh (" << rz << ") = " << tanh( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "exp (complex<double>) :" << std::endl;
                    std::cout << "\texp (" << dz << ") = " << std::exp( dz ) << std::endl;
                    std::cout << "mpfr::exp (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::exp (" << rz << ") = " << exp( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "log (complex<double>) :" << std::endl;
                    std::cout << "\tlog (" << dz << ") = " << std::log( dz ) << std::endl;
                    std::cout << "mpfr::log (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::log (" << rz << ") = " << log( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "log10 (complex<double>) :" << std::endl;
                    std::cout << "\tlog10 (" << dz << ") = " << std::log10( dz ) << std::endl;
                    std::cout << "mpfr::log10 (mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::log10 (" << rz << ") = " << log10( rz ) << std::endl;
                    std::cout << std::endl;

                    int n = random ( -10, 10 );
                    std::cout << "pow (complex<double>, int) :" << std::endl;
                    std::cout << "\tpow (" << dz << ", " << n << ") = " << std::pow( dz, n ) << std::endl;
                    std::cout << "mpfr::pow (mpfr::Complex, int) :" << std::endl;
                    std::cout << "\tmpfr::pow (" << rz << ", " << n << ") = " << pow( rz, n ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "pow (complex<double>, double) :" << std::endl;
                    std::cout << "\tpow (" << dz << ", " << std::real( dz ) << ") = " << std::pow( dz, std::real( dz ) ) << std::endl;
                    std::cout << "mpfr::pow (mpfr::Complex, mpfr::Real) :" << std::endl;
                    std::cout << "\tmpfr::pow (" << rz << ", " << real( rz ) << ") = " << pow( rz, real( rz ) ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "pow (complex<double>, complex<double>) :" << std::endl;
                    std::cout << "\tpow (" << dz << ", " << dz << ") = " << std::pow( dz, dz ) << std::endl;
                    std::cout << "mpfr::pow (mpfr::Complex, mpfr::Complex) :" << std::endl;
                    std::cout << "\tmpfr::pow (" << rz << ", " << rz << ") = " << pow( rz, rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout.flags( old_flags );

                }

        };

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_COMPLEX
