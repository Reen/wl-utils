#ifndef MPFRCPP_TEST_RANDOM
#define MPFRCPP_TEST_RANDOM

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
 * @file random.hpp
 * @date 2007-03-31
 * Part of the library test suite.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#include <cmath>
#include <cstdlib>    // random numbers
#include <ctime>    // time() to initialize srand()

namespace mpfr {
    namespace test {

        inline double random (double min, double max) throw() {
            static bool called = false;
            if (!called) {
                std::srand (std::time(NULL));
                called = true;
            }
            return (double) (std::rand()) * (max - min) / static_cast<double>(RAND_MAX) + min;
        }

        inline int random (int min, int max) throw() {
            static bool called = false;
            if (!called) {
                std::srand (std::time(NULL));
                called = true;
            }
            //      return static_cast<int>(round (random(static_cast<double>(min),
            //                              static_cast<double>(max))));
            return rand() % (max - min + 1) + min;
        }

        inline double random () throw() {
            return random (-100.0, 100.0);
        }

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_RANDOM
