#ifndef MPFRCPP_FUNCTIONS_INVERSE_HYPERBOLIC
#define MPFRCPP_FUNCTIONS_INVERSE_HYPERBOLIC

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
 * @file inverse_hyperbolic.hpp
 * @date 2007-04-03
 * MPFRCPP inverse hyperbolic functions.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {


/**
 * @class AcoshClass
 * Inverse hyperbolic cosine
 */

    class AcoshClass : public NumericFunction {
        public:
            AcoshClass () throw() : NumericFunction () {}
            AcoshClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            AcoshClass (const Precision& pr) throw() : NumericFunction (pr) {}
            AcoshClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_acosh (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
                return y;
            }
            Real operator() (const Real& x, const Precision &p) const throw () {
                return (*this) (x, p, getRoundMode());
            }
            Real operator() (const Real& x, const RoundMode &r) const throw () {
                return (*this) (x, getPrecision(), r);
            }
            Real operator() (const Real& x) const throw () {
                return (*this) (x, getPrecision(), getRoundMode());
            }
    };


/**
 * @class AsinhClass
 * Inverse hyperbolic sine
 */

    class AsinhClass : public NumericFunction {
        public:
            AsinhClass () throw() : NumericFunction () {}
            AsinhClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            AsinhClass (const Precision& pr) throw() : NumericFunction (pr) {}
            AsinhClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_asinh (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
                return y;
            }
            Real operator() (const Real& x, const Precision &p) const throw () {
                return (*this) (x, p, getRoundMode());
            }
            Real operator() (const Real& x, const RoundMode &r) const throw () {
                return (*this) (x, getPrecision(), r);
            }
            Real operator() (const Real& x) const throw () {
                return (*this) (x, getPrecision(), getRoundMode());
            }
    };


/**
 * @class AtanhClass
 * Inverse hyperbolic tangent
 */

    class AtanhClass : public NumericFunction {
        public:
            AtanhClass () throw() : NumericFunction () {}
            AtanhClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            AtanhClass (const Precision& pr) throw() : NumericFunction (pr) {}
            AtanhClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_atanh (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
                return y;
            }
            Real operator() (const Real& x, const Precision &p) const throw () {
                return (*this) (x, p, getRoundMode());
            }
            Real operator() (const Real& x, const RoundMode &r) const throw () {
                return (*this) (x, getPrecision(), r);
            }
            Real operator() (const Real& x) const throw () {
                return (*this) (x, getPrecision(), getRoundMode());
            }
    };


} // namespace mpfr

#endif    // MPFRCPP_FUNCTIONS_INVERSE_HYPERBOLIC
