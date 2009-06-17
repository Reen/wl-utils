#ifndef MPFRCPP_EXTRA_BETA
#define MPFRCPP_EXTRA_BETA

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
 * @file beta.hpp
 * @date 2007-05-07
 * Beta function definition with Gamma function or Gamma function logarithm.
 */

// #include "../mpfrcpp.hpp"
// #include "beta.hpp"

namespace mpfr {

    /**
     * Beta function.
     * Could be defined as
     *     Beta (x,y) = Gamma(x)Gamma(y)/Gamma(x+y)
     */

#define MPFRCPP_CALC_BETA_WITH_LNGAMMA

    inline Real Beta (const Real &x, const Real &y) throw() {
#ifdef MPFRCPP_CALC_BETA_WITH_LNGAMMA
        return Exp( Lngamma(x) + Lngamma(y) - Lngamma(x + y) );
#else

        return Gamma(x) * Gamma(y) / Gamma(x + y);
#endif
    }

#undef MPFRCPP_CALC_BETA_WITH_LNGAMMA

} // namespace mpfr

#endif    // MPFRCPP_EXTRA_BETA
