#ifndef MPFRCPP_CORE_BASE
#define MPFRCPP_CORE_BASE

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
 * @file base.hpp
 * @date 2007-04-07
 * MPFRCPP number base (used for I/O only).
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#define MPFRCPP_BASE_MIN 2
#define MPFRCPP_BASE_MAX 36

namespace mpfr {

    /**
     * Mapping from set of possible unsigned short int values to the
     * [MPFRCPP_BASE_MIN, MPFRCPP_BASE_MAX]
     */

    class BaseBounder : public Bounder<unsigned short int> {
        public:
            unsigned short int operator() ( const unsigned short int& x )
            const throw() {
                if (x > MPFRCPP_BASE_MAX) return MPFRCPP_BASE_MAX;
                if (x < MPFRCPP_BASE_MIN) return MPFRCPP_BASE_MIN;
                return x;
            }
    };

    //------------------------------------------------------------

    /**
     * Number base
     */

    class Base :
        public PrimitiveWrapper<unsigned short int, BaseBounder> {
        public:
            Base (unsigned short int x = 10) throw() :
            PrimitiveWrapper<unsigned short int, BaseBounder>(x) {}

            unsigned short int getInt () const throw() {
                return get ();
            }
            void setInt (unsigned short int x) throw() {
                set (x);
            }
    };

} // namespace mpfr

#undef MPFRCPP_BASE_MIN
#undef MPFRCPP_BASE_MAX

#endif    // MPFRCPP_CORE_BASE
