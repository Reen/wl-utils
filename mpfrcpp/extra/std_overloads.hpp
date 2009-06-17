#ifndef MPFRCPP_EXTRA_STD_OVERLOADS
#define MPFRCPP_EXTRA_STD_OVERLOADS

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
 * @file std_overloads.hpp
 * @date 2007-07-04
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 *
 * Overloads the folowing functions:
 * abs, acos, asin, atan, atan2, ceil, cos, cosh, exp, fabs, floor, fmod,
 * frexp, ldexp, log, log10, modf, pow, sin, sinh, sqrt, swap, tan, tanh
 * in the std namespace.
 * Could conflict with simple_functions.hpp,
 * DO NOT USE with simple_functions.hpp.
 */

namespace std {

    inline void swap (mpfr::Real &x, mpfr::Real &y) throw() {
        mpfr_swap (x.getMpfrT(), y.getMpfrT());
    }

    //------------------------------------------------------------

    inline mpfr::Real abs (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_abs (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real acos (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_acos (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real asin (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_asin (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real atan (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_atan (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real atan2 (const mpfr::Real &x, const mpfr::Real &y) throw() {
        mpfr::Real z (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_atan2 (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }

    //------------------------------------------------------------

    inline mpfr::Real ceil (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_ceil (y.getMpfrT(), x.getMpfrT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real cos (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_cos (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real cosh (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_cosh (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real exp (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_exp (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real fabs (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_abs (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real floor (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_floor (y.getMpfrT(), x.getMpfrT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real fmod (const mpfr::Real &x, const mpfr::Real &y) throw() {
#ifdef HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT
        mpfr::Real z (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_remainder (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
#else
        mpfr::Real n = std::floor(x / y);
        return x - n*y;
#endif    // HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT
    }

    //------------------------------------------------------------

    inline mpfr::Real frexp (const mpfr::Real &x, int *exp) throw() {
        mpfr::Real y (x);
        *exp = y.getExponent().getMpExpT();
        y.setExponent(mpfr::Exponent(0));
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real ldexp (const mpfr::Real &x, int exp) throw() {
        mpfr::Real y;
        mpfr_set_ui_2exp (y.getMpfrT(), 1, exp, mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return x*y;
    }

    //------------------------------------------------------------

    inline mpfr::Real log (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_log (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real log10 (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_log10 (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real modf (const mpfr::Real &x, mpfr::Real *y) throw() {
        mpfr::Real z (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_frac (z.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        mpfr_trunc (y->getMpfrT(), x.getMpfrT());
        return z;
    }

    //------------------------------------------------------------

    // x^y

    inline mpfr::Real pow (const mpfr::Real& x, const mpfr::Real& y) throw() {
        mpfr::Real z (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_pow (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }

    inline mpfr::Real pow (const mpfr::Real& x, const unsigned long int& y) throw() {
        mpfr::Real z (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_pow_ui (z.getMpfrT(), x.getMpfrT(), y, mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }

    inline mpfr::Real pow (const mpfr::Real& x, const long int& y) throw() {
        mpfr::Real z (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_pow_si (z.getMpfrT(), x.getMpfrT(), y, mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }

    inline mpfr::Real pow (const mpfr::Real& x, const unsigned int& y) throw() {
        return pow (x, static_cast<unsigned long int>(y));
    }

    inline mpfr::Real pow (const mpfr::Real& x, const int& y) throw() {
        return pow (x, static_cast<long int>(y));
    }

    //------------------------------------------------------------

    inline mpfr::Real sin (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_sin (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real sinh (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_sinh (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real sqrt (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_sqrt (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real tan (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_tan (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

    inline mpfr::Real tanh (const mpfr::Real &x) throw() {
        mpfr::Real y (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_tanh (y.getMpfrT(), x.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    //------------------------------------------------------------

} // namespace std

#endif    // MPFRCPP_EXTRA_STD_OVERLOADS
