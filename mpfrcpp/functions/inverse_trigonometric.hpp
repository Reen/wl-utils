#ifndef MPFRCPP_FUNCTIONS_INVERSE_TRIGONOMETRIC
#define MPFRCPP_FUNCTIONS_INVERSE_TRIGONOMETRIC

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
 * @file inverse_trigonometric.hpp
 * @date 2007-04-03
 * MPFRCPP inverse trigonometric functions.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {


/**
 * @class AcosClass
 * Arc-cosine
 */

    class AcosClass : public NumericFunction {
        public:
            AcosClass () throw() : NumericFunction () {}
            AcosClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            AcosClass (const Precision& pr) throw() : NumericFunction (pr) {}
            AcosClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_acos (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class AsinClass
 * Arc-sine
 */

    class AsinClass : public NumericFunction {
        public:
            AsinClass () throw() : NumericFunction () {}
            AsinClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            AsinClass (const Precision& pr) throw() : NumericFunction (pr) {}
            AsinClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_asin (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class AtanClass
 * Arc-tangent
 */

    class AtanClass : public NumericFunction {
        public:
            AtanClass () throw() : NumericFunction () {}
            AtanClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            AtanClass (const Precision& pr) throw() : NumericFunction (pr) {}
            AtanClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_atan (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class Atan2Class
 * Arc-tangent 2:
 * atan2(x,y) = atan(x/y) for x > 0,
 * atan2(x,y) = sign(y) (pi - atan |x/y|) for x < 0
 */

    class Atan2Class : public NumericFunction {
        public:
            Atan2Class () throw() : NumericFunction () {}
            Atan2Class (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            Atan2Class (const Precision& pr) throw() : NumericFunction (pr) {}
            Atan2Class (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Precision &p, const RoundMode &r) const throw () {
                Real z (p);
                mpfr_atan2 (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), r.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const Real& y, const Precision &p) const throw () {
                return (*this) (x, y, p, getRoundMode());
            }
            Real operator() (const Real& x, const Real& y, const RoundMode &r) const throw () {
                return (*this) (x, y, getPrecision(), r);
            }
            Real operator() (const Real& x, const Real& y) const throw () {
                return (*this) (x, y, getPrecision(), getRoundMode());
            }
    };

} // namespace mpfr

#endif    // MPFRCPP_FUNCTIONS_INVERSE_TRIGONOMETRIC
