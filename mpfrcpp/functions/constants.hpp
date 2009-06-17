#ifndef MPFRCPP_FUNCTIONS_CONSTANTS
#define MPFRCPP_FUNCTIONS_CONSTANTS

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
 * @file constants.hpp
 * @date 2007-04-03
 * MPFRCPP numeric constants.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

    class ConstantClass : public NumericFunction {
        public :
            ConstantClass () throw() : NumericFunction () {}
            ConstantClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction () {}
            ConstantClass (const Precision& pr) throw() : NumericFunction () {}
            ConstantClass (const RoundMode& rm) throw() : NumericFunction () {}

            static void freeCache () throw () {
                mpfr_free_cache ();
            }

/**
 * log 2, 0,693...
 */

            Real log2 (const Precision &pr, const RoundMode &rm) const throw () {
                Real x (pr);
                mpfr_const_log2 (x.getMpfrT(), rm.getMpfrRndT());
                return x;
            }
            Real log2 (const Precision &pr) const throw () {
                return log2 (pr, getRoundMode());
            }
            Real log2 (const RoundMode &rm) const throw () {
                return log2 (getPrecision(), rm);
            }
            Real log2 () const throw () {
                return log2 (getPrecision(), getRoundMode());
            }

/**
 * pi, 3.1415926...
 */

            Real pi (const Precision &pr, const RoundMode &rm) const throw () {
                Real x (pr);
                mpfr_const_pi (x.getMpfrT(), rm.getMpfrRndT());
                return x;
            }
            Real pi (const Precision &pr) const throw () {
                return pi (pr, getRoundMode());
            }
            Real pi (const RoundMode &rm) const throw () {
                return pi (getPrecision(), rm);
            }
            Real pi () const throw () {
                return pi (getPrecision(), getRoundMode());
            }

/**
 * The Euler-Mascheroni constant, 0.577...
 */

            Real Euler (const Precision &pr, const RoundMode &rm) const throw () {
                Real x (pr);
                mpfr_const_euler (x.getMpfrT(), rm.getMpfrRndT());
                return x;
            }
            Real Euler (const Precision &pr) const throw () {
                return Euler (pr, getRoundMode());
            }
            Real Euler (const RoundMode &rm) const throw () {
                return Euler (getPrecision(), rm);
            }
            Real Euler () const throw () {
                return Euler (getPrecision(), getRoundMode());
            }

/**
 * The Catalan constant, 0.915...
 */

            Real Catalan (const Precision &pr, const RoundMode &rm) const throw () {
                Real x (pr);
                mpfr_const_catalan (x.getMpfrT(), rm.getMpfrRndT());
                return x;
            }
            Real Catalan (const Precision &pr) const throw () {
                return Catalan (pr, getRoundMode());
            }
            Real Catalan (const RoundMode &rm) const throw () {
                return Catalan (getPrecision(), rm);
            }
            Real Catalan () const throw () {
                return Catalan (getPrecision(), getRoundMode());
            }
    };

}    // namespace mpfr

#endif    // MPFRCPP_FUNCTIONS_CONSTANTS
