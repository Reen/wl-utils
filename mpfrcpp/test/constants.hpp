#ifndef MPFRCPP_TEST_CONSTANTS
#define MPFRCPP_TEST_CONSTANTS

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
 * @file constants.hpp
 * @date 2007-04-01
 * MPFRCPP numeric constants test.
 * Part of the library test suite.
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

#include <mpfrcpp/mpfrcpp.hpp>

#include <complex>
#include <iostream>

namespace mpfr {
    namespace test {

        class Constants {
            public:

                static void start () throw() {
                    std::ios_base::fmtflags old_flags = std::cout.flags();

                    std::cout.setf( std::ios_base::scientific );
                    std::cout << ">> MPFRCPP numeric constants test" << std::endl;
                    std::cout << '(' << __FILE__ << ')' << std::endl;
                    std::cout << std::endl;

                    std::cout << "log 2:   " << Constant.log2() << std::endl;
                    std::cout << "pi:      " << Constant.pi() << std::endl;
                    std::cout << "Euler:   " << Constant.Euler() << std::endl;
                    std::cout << "Catalan: " << Constant.Catalan() << std::endl;
                    std::cout << std::endl;

                    std::cout.flags( old_flags );
                }

        };

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_CONSTANTS
