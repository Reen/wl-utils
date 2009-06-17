#ifndef MPFRCPP_FUNCTIONS_RANDOM
#define MPFRCPP_FUNCTIONS_RANDOM

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
 * MPFRCPP random numbers.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

class Random {
    static RandomState defaultState_;
public:
    static Real random2 (const mp_size_t& s, const Exponent& e, const Precision& pr = Real::getParameters().getDefaultPrecision()) throw() {
        Real x (pr.getMpfrPrecT());
        mpfr_random2 (x.getMpfrT(), s, e.getMpExpT());
        return x;
    }

    Real urandomb (RandomState s, const Precision& pr) throw() {
        Real x (pr.getMpfrPrecT());
        mpfr_urandomb (x.getMpfrT(), s.getGmpRandstateT());
        return x;
    }

    Real urandomb (const Precision& pr) throw() {
        Real x (pr.getMpfrPrecT());
        mpfr_urandomb (x.getMpfrT(), defaultState_.getGmpRandstateT());
        return x;
    }

    RandomState& getDefaultRandomState () throw() {
        return defaultState_;
    }

    void setDefaultRandomState (const RandomState& rs) throw() {
        defaultState_ = rs;
    }
};

} // namespace mpfr

#endif    // MPFRCPP_FUNCTIONS_RANDOM
