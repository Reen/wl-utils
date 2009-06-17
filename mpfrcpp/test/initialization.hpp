#ifndef MPFRCPP_TEST_INITIALIZATION
#define MPFRCPP_TEST_INITIALIZATION

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
 * @file initialization.hpp
 * @date 2007-03-31
 * MPFRCPP initialization test.
 * Part of the library test suite.
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

#include <mpfrcpp/mpfrcpp.hpp>

#include <iostream>

namespace mpfr {
    namespace test {

        class Initialization {
            public:
                static void start () throw() {
                    std::cout << ">> MPFRCPP initialization test" << std::endl;
                    std::cout << '(' << __FILE__ << ')' << std::endl;
                    std::cout << std::endl;
                    std::cout << "MPFR version:       ";
                    std::cout << MPFRVersion.toString() << std::endl;
                    std::cout << "MPFRCPP version:    ";
                    std::cout << MPFRCPPVersion.toString() << std::endl;
                    std::cout << std::endl;
                    std::cout << "base:               ";
                    std::cout << Real::getParameters().getDefaultBase().getInt();
                    std::cout << std::endl;
                    std::cout << "precision:          ";
                    std::cout << Real::getParameters().getDefaultPrecision().getMpfrPrecT();
                    std::cout << std::endl;
                    std::cout << "round mode:         ";
                    std::cout << Real::getParameters().getDefaultRoundMode().toString();
                    std::cout << std::endl;
                    std::cout << "machine epsilon:    " << Real::epsilon() << std::endl;
                    std::cout << std::endl;
                }
        };

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_INITIALIZATION
