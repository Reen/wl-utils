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
 * @file std_complex.hpp
 * @date 2007-07-04
 * MPFRCPP complex numbers test, std::complex<mpfr::Real>.
 * Part of the library test suite.
 * Actually, compiller SHOULD NOT pass this test.
 * GCC has a little bug: http://gcc.gnu.org/bugzilla/show_bug.cgi?id=31511
 * which could be fixed quickly.
 * Microsoft (R) C/C++ Optimizing Compiler has incompatible <complex>
 * implementation.
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

#include <mpfrcpp/mpfrcpp.hpp>
#include <mpfrcpp/extra/std_overloads.hpp>

#include <complex>
#include <iostream>

#define INCLUDED_BY_MPFRCPP
#include "random.hpp"
#undef INCLUDED_BY_MPFRCPP

namespace mpfr {
    namespace test {

        class StdComplex {
            public:

                static void start () throw() {
                    std::ios_base::fmtflags old_flags = std::cout.flags();

                    std::cout.setf( std::ios_base::scientific );

                    std::cout << ">> MPFRCPP complex numbers test, std::complex<mpfr::Real>" << std::endl;
                    std::cout << '(' << __FILE__ << ')' << std::endl;
                    std::cout << std::endl;

                    double dx, dy;
                    Real rx, ry;

                    dx = random ( -10.0, 10.0 );
                    rx = Real ( dx );
                    dy = random ( -10.0, 10.0 );
                    ry = Real ( dy );

                    std::complex<double> dz ( dx, dy );
                    std::complex<Real> rz ( rx, dy );

                    std::cout << "complex<double> (double, double) :" << std::endl;
                    std::cout << "\tcomplex<double> (" << dx << ", " << dy << ") = " << dz << std::endl;
                    std::cout << "complex<mpfr::Real> (mpfr::Real, mpfr::Real) :" << std::endl;
                    std::cout << "\tcomplex<mpfr::Real> (" << rx << ", " << ry << ") = " << rz << std::endl;
                    std::cout << std::endl;

                    std::cout << "polar (double, double) :" << std::endl;
                    std::cout << "\tpolar (" << std::abs( dz ) << ", " << std::arg( dz ) << ") = " << dz << std::endl;
                    std::cout << "polar (mpfr::Real, mpfr::Real) :" << std::endl;
                    std::cout << "\tpolar (" << std::abs( rz ) << ", " << std::arg( rz ) << ") = " << rz << std::endl;
                    std::cout << std::endl;

                    std::cout << "abs (complex<double>) :" << std::endl;
                    std::cout << "\tabs (" << dz << ") = " << std::abs( dz ) << std::endl;
                    std::cout << "abs (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tabs (" << rz << ") = " << std::abs( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "arg (complex<double>) :" << std::endl;
                    std::cout << "\targ (" << dz << ") = " << std::arg( dz ) << std::endl;
                    std::cout << "arg (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\targ (" << rz << ") = " << std::arg( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "conj (complex<double>) :" << std::endl;
                    std::cout << "\tconj (" << dz << ") = " << std::conj( dz ) << std::endl;
                    std::cout << "conj (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tconj (" << rz << ") = " << std::conj( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "norm (complex<double>) :" << std::endl;
                    std::cout << "\tnorm (" << dz << ") = " << std::norm( dz ) << std::endl;
                    std::cout << "norm (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tnorm (" << rz << ") = " << std::norm( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "sqrt (complex<double>) :" << std::endl;
                    std::cout << "\tsqrt (" << dz << ") = " << std::sqrt( dz ) << std::endl;
                    std::cout << "sqrt (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tsqrt (" << rz << ") = " << std::sqrt( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "sin (complex<double>) :" << std::endl;
                    std::cout << "\tsin (" << dz << ") = " << std::sin( dz ) << std::endl;
                    std::cout << "sin (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tsin (" << rz << ") = " << std::sin( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "cos (complex<double>) :" << std::endl;
                    std::cout << "\tcos (" << dz << ") = " << std::cos( dz ) << std::endl;
                    std::cout << "cos (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tcos (" << rz << ") = " << std::cos( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "tan (complex<double>) :" << std::endl;
                    std::cout << "\ttan (" << dz << ") = " << std::tan( dz ) << std::endl;
                    std::cout << "tan (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\ttan (" << rz << ") = " << std::tan( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "sinh (complex<double>) :" << std::endl;
                    std::cout << "\tsinh (" << dz << ") = " << std::sinh( dz ) << std::endl;
                    std::cout << "sinh (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tsinh (" << rz << ") = " << std::sinh( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "cosh (complex<double>) :" << std::endl;
                    std::cout << "\tcosh (" << dz << ") = " << std::cosh( dz ) << std::endl;
                    std::cout << "cosh (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tcosh (" << rz << ") = " << std::cosh( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "tanh (complex<double>) :" << std::endl;
                    std::cout << "\ttanh (" << dz << ") = " << std::tanh( dz ) << std::endl;
                    std::cout << "tanh (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\ttanh (" << rz << ") = " << std::tanh( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "exp (complex<double>) :" << std::endl;
                    std::cout << "\texp (" << dz << ") = " << std::exp( dz ) << std::endl;
                    std::cout << "exp (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\texp (" << rz << ") = " << std::exp( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "log (complex<double>) :" << std::endl;
                    std::cout << "\tlog (" << dz << ") = " << std::log( dz ) << std::endl;
                    std::cout << "log (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tlog (" << rz << ") = " << std::log( rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "log10 (complex<double>) :" << std::endl;
                    std::cout << "\tlog10 (" << dz << ") = " << std::log10( dz ) << std::endl;
                    std::cout << "log10 (complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tlog10 (" << rz << ") = " << std::log10( rz ) << std::endl;
                    std::cout << std::endl;

                    int n = random ( -10, 10 );
                    std::cout << "pow (complex<double>, int) :" << std::endl;
                    std::cout << "\tpow (" << dz << ", " << n << ") = " << std::pow( dz, n ) << std::endl;
                    std::cout << "pow (complex<mpfr::Real>, int) :" << std::endl;
                    std::cout << "\tpow (" << rz << ", " << n << ") = " << std::pow( rz, n ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "pow (complex<double>, double) :" << std::endl;
                    std::cout << "\tpow (" << dz << ", " << std::real( dz ) << ") = " << std::pow( dz, std::real( dz ) ) << std::endl;
                    std::cout << "pow (complex<mpfr::Real>, mpfr::Real) :" << std::endl;
                    std::cout << "\tpow (" << rz << ", " << std::real( rz ) << ") = " << std::pow( rz, std::real( rz ) ) << std::endl;
                    std::cout << std::endl;

                    std::cout << "pow (complex<double>, complex<double>) :" << std::endl;
                    std::cout << "\tpow (" << dz << ", " << dz << ") = " << std::pow( dz, dz ) << std::endl;
                    std::cout << "pow (complex<mpfr::Real>, complex<mpfr::Real>) :" << std::endl;
                    std::cout << "\tpow (" << rz << ", " << rz << ") = " << std::pow( rz, rz ) << std::endl;
                    std::cout << std::endl;

                    std::cout.flags( old_flags );
                }

        };

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_COMPLEX
