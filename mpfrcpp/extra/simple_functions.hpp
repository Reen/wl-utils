#ifndef MPFRCPP_EXTRA_SIMPLE_FUNCTIONS
#define MPFRCPP_EXTRA_SIMPLE_FUNCTIONS

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
 * @file simple_functions.hpp
 * @date 2007-09-15
 *
 * Overloads the folowing functions:
 *     abs, acos, acosh, agm, asin, asinh, atan2, atan, atanh, besselJ0,
 *     besselJ1, besselJn, besselY0, besselY1, besselYn, cbrt, ceil,
 *     cos, cosh, cot, coth, csc, csch, eint, erf, erfc, exp10, exp2, exp,
 *     expm1, factorial, floor, fma, fms, frac, gamma, hypot, lngamma, log10,
 *     log1p, log2, log, pow, remainder, root, round, sec, sech, sin, sinh,
 *      sqr, sqrt, tan, tanh, trunc, zeta
 * in the mpfr namespace.
 *
 * Could conflict with std_overloads.hpp,
 * DO NOT USE with std_overloads.hpp.
 *
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

namespace mpfr {

    inline Real abs (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_abs (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real acos (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_acos (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real acosh (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_acosh (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real agm (const Real& x, const Real& y) throw() {
        Real z (Real::getParameters().getDefaultPrecision());
        mpfr_agm (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }

    inline Real asin (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_asin (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real asinh (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_asinh (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real atan2 (const Real& x, const Real& y) throw() {
        Real z (Real::getParameters().getDefaultPrecision());
        mpfr_atan2 (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }

    inline Real atan (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_atan (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real atanh (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_atanh (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

#ifdef HAVE_BESSEL_FUNCTIONS_SUPPORT
    inline Real besselJ0 (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_j0 (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real besselJ1 (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_j1 (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real besselJn (const long& n, const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_jn (y.getMpfrT(), n, x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real besselY0 (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_y0 (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real besselY1 (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_y1 (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real besselYn (const long& n, const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_yn (y.getMpfrT(), n, x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }
#endif    // HAVE_BESSEL_FUNCTIONS_SUPPORT

    inline Real cbrt (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_cbrt (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real ceil (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_ceil (y.getMpfrT(), x.getMpfrT());
        return y;
    }

    inline Real cos (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_cos (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real cosh (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_cosh (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real cot (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_cot (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real coth (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_coth (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real csc (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_csc (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real csch (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_csch (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real eint (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_eint (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real erf (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_erf (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real erfc (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_erfc (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real exp10 (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_exp10 (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real exp2 (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_exp2 (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real exp (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_exp (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real expm1 (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_expm1 (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real factorial (unsigned int x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_fac_ui (y.getMpfrT(), x, Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real floor (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_floor (y.getMpfrT(), x.getMpfrT());
        return y;
    }

    inline Real fma (const Real& x, const Real& y, const Real& z) throw() {
        Real u (Real::getParameters().getDefaultPrecision());
        mpfr_fma (u.getMpfrT(), x.getMpfrT(), y.getMpfrT(), z.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return u;
    }

#ifdef HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT
    inline Real fms (const Real& x, const Real& y, const Real& z) throw() {
        Real u (Real::getParameters().getDefaultPrecision());
        mpfr_fms (u.getMpfrT(), x.getMpfrT(), y.getMpfrT(), z.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return u;
    }
#endif   // HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT

    inline Real frac (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_frac (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real gamma (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_gamma (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real hypot (const Real& x, const Real& y) throw() {
        Real z (Real::getParameters().getDefaultPrecision());
        mpfr_hypot (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }

    inline Real lngamma (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_lngamma (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real log10 (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_log10 (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real log1p (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_log1p (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real log2 (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_log2 (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real log (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_log (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real pow (const Real& x, const Real& y) throw() {
        Real z (Real::getParameters().getDefaultPrecision());
        mpfr_pow (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }
    inline Real pow (const Real& x, unsigned int& y) throw() {
        Real z (Real::getParameters().getDefaultPrecision());
        mpfr_pow_ui (z.getMpfrT(), x.getMpfrT(), y, Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }
    inline Real pow (const Real& x, int& y) throw() {
        Real z (Real::getParameters().getDefaultPrecision());
        mpfr_pow_si (z.getMpfrT(), x.getMpfrT(), y, Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }
    inline Real pow (const Real& x, const mpz_t& y) throw() {
        Real z (Real::getParameters().getDefaultPrecision());
        mpfr_pow_z (z.getMpfrT(), x.getMpfrT(), y, Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }
    inline Real pow (const Real& x, const mpz_class& y) throw() {
        Real z (Real::getParameters().getDefaultPrecision());
        mpfr_pow_z (z.getMpfrT(), x.getMpfrT(), y.get_mpz_t(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }

#ifdef HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT
    inline Real remainder (const mpfr::Real &x, const mpfr::Real &y) throw() {
        mpfr::Real z (mpfr::Real::getParameters().getDefaultPrecision());
        mpfr_remainder (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), mpfr::Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return z;
    }
#endif    // HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT

    inline Real root (const Real& x, unsigned int k) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_root (y.getMpfrT(), x.getMpfrT(), k, Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real round (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_round (y.getMpfrT(), x.getMpfrT());
        return y;
    }

    inline Real sec (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_sec (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real sech (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_sech (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real sin (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_sin (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real sinh (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_sinh (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real sqr (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_sqr (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real sqrt (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_sqrt (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real tan (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_tan (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real tanh (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_tanh (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

    inline Real trunc (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_trunc (y.getMpfrT(), x.getMpfrT());
        return y;
    }

    inline Real zeta (const Real& x) throw() {
        Real y (Real::getParameters().getDefaultPrecision());
        mpfr_zeta (y.getMpfrT(), x.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
        return y;
    }

}     // namespace mpfr

#endif    // MPFRCPP_EXTRA_SIMPLE_FUNCTIONS
