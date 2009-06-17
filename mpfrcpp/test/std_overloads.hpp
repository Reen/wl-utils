#ifndef MPFRCPP_TEST_STD_OVERLOADS
#define MPFRCPP_TEST_STD_OVERLOADS

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
 * @file std_overloads.hpp
 * @date 2007-04-07
 * MPFRCPP namespace std numerics overloads test.
 * Part of the library test suite.
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

#include <mpfrcpp/mpfrcpp.hpp>

#include <cmath>
#include <iostream>
#include <mpfrcpp/extra/std_overloads.hpp>

#define INCLUDED_BY_MPFRCPP
#include "random.hpp"
#undef INCLUDED_BY_MPFRCPP

namespace mpfr {
    namespace test {

        class StdOverloads {
            public:

                static void start () throw() {
                    std::ios_base::fmtflags old_flags = std::cout.flags();

                    std::cout.setf( std::ios_base::scientific );

                    std::cout << ">> MPFRCPP namespace std numerics overloads test";
                    std::cout << std::endl;
                    std::cout << '(' << __FILE__ << ')' << std::endl;
                    std::cout << std::endl;

                    double dx, dy;
                    Real rx, ry;
                    int e;

                    dx = random ();
                    if ( dx > 0.0 )
                        dx = -dx;
                    rx = Real ( dx );
                    std::cout << "std::abs (double) :" << std::endl;
                    std::cout << "\tstd::abs (" << dx << ") = " << std::abs( dx );
                    std::cout << std::endl;
                    std::cout << "std::abs (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::abs (" << rx << ") = " << std::abs( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ( -1.0, 1.0 );
                    rx = Real ( dx );
                    std::cout << "std::acos (double) :" << std::endl;
                    std::cout << "\tstd::acos (" << dx << ") = " << std::acos( dx );
                    std::cout << std::endl;
                    std::cout << "std::acos (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::acos (" << rx << ") = " << std::acos( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ( -1.0, 1.0 );
                    rx = Real ( dx );
                    std::cout << "std::asin (double) :" << std::endl;
                    std::cout << "\tstd::asin (" << dx << ") = " << std::asin( dx );
                    std::cout << std::endl;
                    std::cout << "std::asin (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::asin (" << rx << ") = " << std::asin( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::atan (double) :" << std::endl;
                    std::cout << "\tstd::atan (" << dx << ") = " << std::atan( dx ) << std::endl;
                    std::cout << "std::atan (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::atan (" << rx << ") = " << std::atan( rx ) << std::endl;
                    std::cout << std::endl;

                    dx = random ();
                    dy = random ();
                    rx = Real ( dx );
                    ry = Real ( dy );
                    std::cout << "std::atan2 (double, double) :" << std::endl;
                    std::cout << "\tstd::atan2 (" << dx << ", " << dy << ") = " << std::atan2( dx, dy ) << std::endl;
                    std::cout << "std::atan2 (mpfr::Real, mpfr::Real) :";
                    std::cout << std::endl;
                    std::cout << "\tstd::atan2 (" << rx << ", " << ry << ") = "  << std::atan2( rx, ry ) << std::endl;
                    std::cout << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::ceil (double) :" << std::endl;
                    std::cout << "\tstd::ceil (" << dx << ") = " << std::atan( dx );
                    std::cout << std::endl;
                    std::cout << "std::ceil (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::ceil (" << rx << ") = " << std::atan( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::cos (double) :" << std::endl;
                    std::cout << "\tstd::cos (" << dx << ") = " << std::cos( dx );
                    std::cout << std::endl;
                    std::cout << "std::cos (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::cos (" << rx << ") = " << std::cos( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::cosh (double) :" << std::endl;
                    std::cout << "\tstd::cosh (" << dx << ") = " << std::cosh( dx ) << std::endl;
                    std::cout << "std::cosh (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::cosh (" << rx << ") = " << std::cosh( rx ) << std::endl;
                    std::cout << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::exp (double) :" << std::endl;
                    std::cout << "\tstd::exp (" << dx << ") = " << std::exp( dx );
                    std::cout << std::endl;
                    std::cout << "std::exp (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::exp (" << rx << ") = " << std::exp( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    if ( dx > 0.0 )
                        dx = -dx;
                    rx = Real ( dx );
                    std::cout << "std::fabs (double) :" << std::endl;
                    std::cout << "\tstd::fabs (" << dx << ") = " << std::fabs( dx );
                    std::cout << std::endl;
                    std::cout << "std::fabs (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::fabs (" << rx << ") = " << std::fabs( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::floor (double) :" << std::endl;
                    std::cout << "\tstd::floor (" << dx << ") = " << std::floor( dx );
                    std::cout << std::endl;
                    std::cout << "std::floor (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::floor (" << rx << ") = " << std::floor( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    dy = random ();
                    rx = Real ( dx );
                    ry = Real ( dy );
                    std::cout << "std::fmod (double, double) :" << std::endl;
                    std::cout << "\tstd::fmod (" << dx << ", " << dy << ") = " << std::fmod( dx, dy ) << std::endl;
                    std::cout << "std::fmod (mpfr::Real, mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::fmod (" << rx << ", " << ry << ") = " << std::fmod( rx, ry ) << std::endl;
                    std::cout << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::frexp (double, int*) :" << std::endl;
                    std::cout << "\tstd::frexp (" << dx << ", &e) = " << std::frexp( dx, &e ) << std::endl;
                    std::cout << "\t\t=> e = " << e << std::endl;
                    std::cout << "std::frexp (mpfr::Real, int*) :" << std::endl;
                    std::cout << "\tstd::frexp (" << rx << ", &e) = " << std::frexp( rx, &e ) << std::endl;
                    std::cout << "\t\t=> e = " << e << std::endl;
                    std::cout << std::endl;

                    dx = random ();
                    e = static_cast<int>( random ( -10, 10 ) );
                    rx = Real ( dx );
                    std::cout << "std::ldexp (double, int) :" << std::endl;
                    std::cout << "\tstd::ldexp (" << dx << ", " << e << ") = " << std::ldexp( dx, e ) << std::endl;
                    std::cout << "std::ldexp (mpfr::Real, int) :" << std::endl;
                    std::cout << "\tstd::ldexp (" << rx << ", " << e << ") = " << std::ldexp( rx, e ) << std::endl;
                    std::cout << std::endl;

                    dx = random ();
                    while ( dx <= 0.0 )
                        dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::log (double) :" << std::endl;
                    std::cout << "\tstd::log (" << dx << ") = " << std::log( dx );
                    std::cout << std::endl;
                    std::cout << "std::log (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::log (" << rx << ") = " << std::log( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    while ( dx <= 0.0 )
                        dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::log10 (double) :" << std::endl;
                    std::cout << "\tstd::log10 (" << dx << ") = " << std::log10( dx );
                    std::cout << std::endl;
                    std::cout << "std::log10 (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::log10 (" << rx << ") = " << std::log10( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::modf (double, doule*) :" << std::endl;
                    std::cout << "\tstd::modf (" << dx << ", &y) = " << std::modf( dx, &dy ) << std::endl;
                    std::cout << "\t\t=> y = " << dy << std::endl;
                    std::cout << "std::modf (mpfr::Real, mpfr::Real*) :";
                    std::cout << std::endl;
                    std::cout << "\tstd::modf (" << rx << ", &y) = " << std::modf( rx, &ry ) << std::endl;
                    std::cout << "\t\t=> y = " << ry << std::endl;
                    std::cout << std::endl;

                    dx = random ();
                    dy = random ();
                    if ( dx < 0 )
                        dx = -dx;
                    if ( dy < 0 )
                        dy = -dy;
                    rx = Real ( dx );
                    ry = Real ( dy );
                    std::cout << "std::pow (double, double) :" << std::endl;
                    std::cout << "\tstd::pow (" << dx << ", " << dy << ") = " << std::pow( dx, dy ) << std::endl;
                    std::cout << "std::pow (mpfr::Real, mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::pow (" << rx << ", " << ry << ") = " << std::pow( rx, ry ) << std::endl;
                    std::cout << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::sin (double) :" << std::endl;
                    std::cout << "\tstd::sin (" << dx << ") = " << std::sin( dx );
                    std::cout << std::endl;
                    std::cout << "std::sin (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::sin (" << rx << ") = " << std::sin( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::sinh (double) :" << std::endl;
                    std::cout << "\tstd::sinh (" << dx << ") = " << std::sinh( dx );
                    std::cout << std::endl;
                    std::cout << "std::sinh (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::sinh (" << rx << ") = " << std::sinh( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    while ( dx <= 0.0 )
                        dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::sqrt (double) :" << std::endl;
                    std::cout << "\tstd::sqrt (" << dx << ") = " << std::sqrt( dx );
                    std::cout << std::endl;
                    std::cout << "std::sqrt (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::sqrt (" << rx << ") = " << std::sqrt( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ();
                    rx = Real ( dx );
                    std::cout << "std::tan (double) :" << std::endl;
                    std::cout << "\tstd::tan (" << dx << ") = " << std::tan( dx );
                    std::cout << std::endl;
                    std::cout << "std::tan (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::tan (" << rx << ") = " << std::tan( rx );
                    std::cout << std::endl << std::endl;

                    dx = random ( -5.0, 5.0 );
                    rx = Real ( dx );
                    std::cout << "std::tanh (double) :" << std::endl;
                    std::cout << "\tstd::tanh (" << dx << ") = " << std::tanh( dx );
                    std::cout << std::endl;
                    std::cout << "std::tanh (mpfr::Real) :" << std::endl;
                    std::cout << "\tstd::tanh (" << rx << ") = " << std::tanh( rx );
                    std::cout << std::endl << std::endl;

                    std::cout.flags( old_flags );
                }

        };

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_STD_OVERLOADS

