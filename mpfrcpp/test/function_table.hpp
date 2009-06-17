#ifndef MPFRCPP_TEST_FUNCTION_TABLE
#define MPFRCPP_TEST_FUNCTION_TABLE

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
 * @file function_table.hpp
 * @date 2007-04-01
 * Part of the library test suite.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#include <iostream>

namespace mpfr {
    namespace test {

        template <typename T, class F>
        void functionTable (const F& function, const T& start, const T& end, size_t steps) {
            T step = (end - start) / T(steps);
            std::ios_base::fmtflags old_flags = std::cout.flags();
            std::cout.setf(std::ios_base::showpos);
            std::cout << "x\tf(x)" << std::endl;
            for (T x = start; x <= end; x += step)
                std::cout << x << "\t" << function(x) << std::endl;
            std::cout.flags(old_flags);
        }

        template <typename T, class F>
        void functionTable2 (const F& function, const T& start, const T& end, size_t steps) {
            T step = (end - start) / T(steps);
            std::ios_base::fmtflags old_flags = std::cout.flags();
            std::cout.setf(std::ios_base::showpos);
            std::cout << "x\ty\tf(x,y)" << std::endl;
            for (T x = start; x <= end; x += step)
                for (T y = start; y <= end; y += step)
                    std::cout << x << "\t" << y << "\t" << function(x, y) << std::endl;
            std::cout.flags(old_flags);
        }

        template <typename Tx, typename Ty, class F>
        void functionTable2 (const F& function, const Tx& startx, const Tx& endx, size_t stepsx, const Ty& starty, const Ty& endy, size_t stepsy) {
            Tx stepx = (endx - startx) / Tx(stepsx);
            Ty stepy = (endy - starty) / Ty(stepsy);
            std::ios_base::fmtflags old_flags = std::cout.flags();
            std::cout.setf(std::ios_base::showpos);
            std::cout << "x\ty\tf(x,y)" << std::endl;
            for (Tx x = startx; x <= endx; x += stepx)
                for (Ty y = starty; y <= endy; y += stepy)
                    std::cout << x << "\t" << y << "\t" << function(x, y) << std::endl;
            std::cout.flags(old_flags);
        }

    } // namespace test
} // namespace mpfr

#endif    // MPFRCPP_TEST_FUNCTION_TABLE
