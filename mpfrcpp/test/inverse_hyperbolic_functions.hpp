#ifndef MPFRCPP_TEST_INVERSE_HYPERBOLIC_FUNCTIONS
#define MPFRCPP_TEST_INVERSE_HYPERBOLIC_FUNCTIONS

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
 * @file inverse_hyperbolic_functions.hpp
 * @date 2007-04-07
 * MPFRCPP inverse hyperbolic functions test.
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

        class InverseHyperbolicFunctions {
            public:

                static void start () throw() {
                    std::cout << ">> MPFRCPP inverse hyperbolic functions test" << std::endl;
                    std::cout << '(' << __FILE__ << ')' << std::endl;
                    std::cout << std::endl;

                    std::cout << "Inverse Hyperbolic Sine" << std::endl;
                    functionTable ( Asinh, Real(-100), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Inverse Hyperbolic Cosine" << std::endl;
                    functionTable ( Acosh, Real(1), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Inverse Hyperbolic Tangnt" << std::endl;
                    functionTable ( Atanh, Real(-1), Real(1), 10 );
                    std::cout << std::endl;
                }

        };

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_INVERSE_HYPERBOLIC_FUNCTIONS
