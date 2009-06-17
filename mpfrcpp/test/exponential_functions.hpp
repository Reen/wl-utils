#ifndef MPFRCPP_TEST_EXPONENTIAL_FUNCTIONS
#define MPFRCPP_TEST_EXPONENTIAL_FUNCTIONS

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
 * @file exponential_functions.hpp
 * @date 2007-04-07
 * MPFRCPP exponential functions test.
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

        class ExponentialFunctions {
            public:

                static void start () throw() {
                    std::cout << ">> MPFRCPP exponential functions test" << std::endl;
                    std::cout << '(' << __FILE__ << ')' << std::endl;
                    std::cout << std::endl;

                    std::cout << "Exponential" << std::endl;
                    functionTable ( Exp, Real(-10), Real(10), 10 );
                    std::cout << std::endl;

                    std::cout << "Exponential of x−1" << std::endl;
                    functionTable ( Expm1, Real(-10), Real(10), 10 );
                    std::cout << std::endl;

                    std::cout << "10^x" << std::endl;
                    functionTable ( Exp10, Real(-10), Real(10), 10 );
                    std::cout << std::endl;

                    std::cout << "2^x" << std::endl;
                    functionTable ( Exp2, Real(-10), Real(10), 10 );
                    std::cout << std::endl;
                }

        };

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_EXPONENTIAL_FUNCTIONS
