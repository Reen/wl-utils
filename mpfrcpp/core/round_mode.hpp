#ifndef MPFRCPP_CORE_ROUND_MODE
#define MPFRCPP_CORE_ROUND_MODE

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
 * @file round_mode.hpp
 * @date 2007-04-06
 * Round mode for FP arithmetic.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#include <limits>    // std::float_round_style

namespace mpfr {

    //------------------------------------------------------------

    /**
     * Round mode for FP arithmetic
     */

    class RoundMode {
        mpfr_rnd_t r_;
 
        static mpfr_rnd_t FloatRoundStyle2MpRndT (const std::float_round_style &r) throw(UnknownRoundModeError) {
            if (r == std::round_toward_zero)          return GMP_RNDZ;
            if (r == std::round_to_nearest)           return GMP_RNDN;
            if (r == std::round_toward_infinity)      return GMP_RNDU;
            if (r == std::round_toward_neg_infinity)  return GMP_RNDD;
            throw UnknownRoundModeError();
        }

        static std::float_round_style MpRndT2FloatRoundStyle (const mpfr_rnd_t &r) throw(UnknownRoundModeError) {
            if (r == GMP_RNDZ) return std::round_toward_zero;
            if (r == GMP_RNDN) return std::round_to_nearest;
            if (r == GMP_RNDU) return std::round_toward_infinity;
            if (r == GMP_RNDD) return std::round_toward_neg_infinity;
            throw UnknownRoundModeError();
        }

    public:

        RoundMode (const std::float_round_style& r = std::round_to_nearest) throw() : r_(FloatRoundStyle2MpRndT(r)) {}

        bool operator== (const RoundMode& f) const throw() {
            return r_ == f.r_;
        }
        bool operator!= (const RoundMode& f) const throw() {
            return r_ != f.r_;
        }

        std::float_round_style getFloatRoundStyle () const throw() {
            return MpRndT2FloatRoundStyle(r_);
        }

        mpfr_rnd_t getMpfrRndT () const throw() {
            return r_;
        }

        void setFloatRoundStyle (const std::float_round_style& r) throw() {
            r_ = FloatRoundStyle2MpRndT(r);
        }

        void setMpfrRndT (const mpfr_rnd_t& r) throw() {
            r_ = r;
        }

        const char* toString() const throw (UnknownRoundModeError) {
            if (r_ == GMP_RNDZ) return "round toward zero";
            if (r_ == GMP_RNDN) return "round to nearest";
            if (r_ == GMP_RNDU) return "round toward infinity";
            if (r_ == GMP_RNDD) return "round toward negative infinity";
            throw UnknownRoundModeError(); // never get here
        }

        operator std::string() const throw (UnknownRoundModeError) {
            return toString();
        }

    };

} // namespace mpfr

#endif    // MPFRCPP_CORE_ROUND_MODE
