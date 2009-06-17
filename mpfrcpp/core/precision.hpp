#ifndef MPFRCPP_CORE_PRECISION
#define MPFRCPP_CORE_PRECISION

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
 * @file precision.hpp
 * @date 2007-03-23
 * MPFRCPP number precision.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */
#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

    /**
     * Mapping from set of possible mpfr_prec_t values to the
     * [MPFR_PREC_MIN, MPFR_PREC_MAX]
     */

    class PrecisionBounder : public Bounder<mpfr_prec_t> {
        public:
            mpfr_prec_t operator() (const mpfr_prec_t& x) const throw() {
                if (x > MPFR_PREC_MAX) return MPFR_PREC_MAX;
                if (x < MPFR_PREC_MIN) return MPFR_PREC_MIN;
                return x;
            }
    };

    //------------------------------------------------------------

    /**
     * Number [binary] precision
     */

    class Precision : public PrimitiveWrapper<mpfr_prec_t, PrecisionBounder> {
        public:
            Precision (mpfr_prec_t x = 53) throw() : PrimitiveWrapper<mpfr_prec_t, PrecisionBounder>(x) {}

            mpfr_prec_t getMpfrPrecT () const throw() {
                return get ();
            }
            void setMpfrPrecT (mpfr_prec_t x) throw() {
                set (x);
            }
    };

} // namespace mpfr

#endif    // MPFRCPP_CORE_PRECISION
