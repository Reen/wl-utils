#ifndef MPFRCPP_TEST_SPECIAL_FUNCTIONS
#define MPFRCPP_TEST_SPECIAL_FUNCTIONS

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
 * @file special_functions.hpp
 * @date 2007-04-07
 * MPFRCPP special functions test.
 * Part of the library test suite.
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

#include <mpfrcpp/mpfrcpp.hpp>

#include <iostream>

#define INCLUDED_BY_MPFRCPP
#include "function_table.hpp"
#undef INCLUDED_BY_MPFRCPP

namespace mpfr {
    namespace test {

        class SpecialFunctions {
            public:

                static void start () throw() {
                    std::cout << ">> MPFRCPP special functions test" << std::endl;
                    std::cout << '(' << __FILE__ << ')' << std::endl;
                    std::cout << std::endl;

#ifdef HAVE_BESSEL_FUNCTIONS_SUPPORT
                    std::cout << "First order Bessel function of order 0 J_0" << std::endl;
                    functionTable ( BesselJ0, Real( -2 ), Real( 2 ), 16 );
                    std::cout << std::endl;

                    std::cout << "First order Bessel function of order 1 J_1" << std::endl;
                    functionTable ( BesselJ1, Real( -2 ), Real( 2 ), 16 );
                    std::cout << std::endl;

                    std::cout << "Second order Bessel function of order 0 Y_0" << std::endl;
                    functionTable ( BesselY0, Real( -2 ), Real( 2 ), 16 );

                    std::cout << "Second order Bessel function of order 1 Y_1" << std::endl;
                    functionTable ( BesselY1, Real( -2 ), Real( 2 ), 16 );
                    std::cout << std::endl;
#endif    // HAVE_BESSEL_FUNCTIONS_SUPPORT

                    std::cout << "Error Function" << std::endl;
                    functionTable ( Erf, Real( -2 ), Real( 2 ), 16 );
                    std::cout << std::endl;

                    std::cout << "Complementary Error Function" << std::endl;
                    functionTable ( Erfc, Real( -2 ), Real( 2 ), 16 );
                    std::cout << std::endl;

                    std::cout << "Exponential Integral" << std::endl;
                    functionTable ( Eint, Real( 0 ), Real( 10 ), 20 );
                    std::cout << std::endl;

                    std::cout << "Gamma Function" << std::endl;
                    functionTable ( Gamma, Real( 0 ), Real( 10 ), 20 );
                    std::cout << std::endl;

                    std::cout << "Gamma Function Logarithm" << std::endl;
                    functionTable ( Lngamma, Real( 0 ), Real( 10 ), 20 );
                    std::cout << std::endl;

                    std::cout << "Riemann Zeta Function" << std::endl;
                    functionTable ( Zeta, Real( 1 ), Real( 20 ), 19 );
                    std::cout << std::endl;
                }

        };

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_SPECIAL_FUNCTIONS
