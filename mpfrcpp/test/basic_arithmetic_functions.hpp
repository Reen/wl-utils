#ifndef MPFRCPP_TEST_BASIC_ARITMETIC_FUNCTIONS
#define MPFRCPP_TEST_BASIC_ARITMETIC_FUNCTIONS

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
 * @file basic_arithmetic_functions.hpp
 * @date 2007-04-07
 * MPFRCPP basic aritmetic functions test.
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

        class BasicAritmeticFunctions {
            public:

                static void start () throw() {
                    std::cout << ">> MPFRCPP basic aritmetic functions test" << std::endl;
                    std::cout << '(' << __FILE__ << ')' << std::endl;
                    std::cout << std::endl;

                    std::cout << "Addition" << std::endl;
                    functionTable2 ( Add, Real(-100), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Subtraction" << std::endl;
                    functionTable2 ( Sub, Real(-100), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Multiplication" << std::endl;
                    functionTable2 ( Mul, Real(-100), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Division" << std::endl;
                    functionTable2 ( Div, Real(-100), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Negative Sign" << std::endl;
                    functionTable ( Neg, Real(-100), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Absolute Value" << std::endl;
                    functionTable ( Abs, Real(-100), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Square Root" << std::endl;
                    functionTable ( Sqrt, Real(0), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Cubic Root" << std::endl;
                    functionTable ( Cbrt, Real(-100), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "k^th Root" << std::endl;
                    functionTable2 ( Root, Real(0), Real(100), 10,
                                           static_cast<unsigned int>(1), static_cast<unsigned int>(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Square" << std::endl;
                    functionTable ( Sqr, Real(-100), Real(100), 10 );
                    std::cout << std::endl;

                    std::cout << "Power" << std::endl;
                    functionTable2 ( Pow, Real(0), Real(100), 10,
                                          Real(-100), Real(100), 10 );
                    std::cout << std::endl;
                }

        };

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_BASIC_ARITMETIC_FUNCTIONS
