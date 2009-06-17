#ifndef MPFRCPP_FUNCTIONS_HYPERBOLIC
#define MPFRCPP_FUNCTIONS_HYPERBOLIC

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
 * @file hyperbolic.hpp
 * @date 2007-04-03
 * MPFRCPP hyperbolic functions.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {


/**
 * @class CoshClass
 * Hyperbolic cosine
 */

    class CoshClass : public NumericFunction {
        public:
            CoshClass () throw() : NumericFunction () {}
            CoshClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            CoshClass (const Precision& pr) throw() : NumericFunction (pr) {}
            CoshClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_cosh (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class CothClass
 * Hyperbolic cotangent
 */

    class CothClass : public NumericFunction {
        public:
            CothClass () throw() : NumericFunction () {}
            CothClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            CothClass (const Precision& pr) throw() : NumericFunction (pr) {}
            CothClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_coth (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class CschClass
 * Hyperbolic cosecant
 */

    class CschClass : public NumericFunction {
        public:
            CschClass () throw() : NumericFunction () {}
            CschClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            CschClass (const Precision& pr) throw() : NumericFunction (pr) {}
            CschClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_csch (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class SechClass
 * Hyperbolic secant
 */

    class SechClass : public NumericFunction {
        public:
            SechClass () throw() : NumericFunction () {}
            SechClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            SechClass (const Precision& pr) throw() : NumericFunction (pr) {}
            SechClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_sech (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class SinhClass
 * Hyperbolic sine
 */

    class SinhClass : public NumericFunction {
        public:
            SinhClass () throw() : NumericFunction () {}
            SinhClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            SinhClass (const Precision& pr) throw() : NumericFunction (pr) {}
            SinhClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_sinh (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class TanhClass
 * Hyperbolic tangent
 */

    class TanhClass : public NumericFunction {
        public:
            TanhClass () throw() : NumericFunction () {}
            TanhClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            TanhClass (const Precision& pr) throw() : NumericFunction (pr) {}
            TanhClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_tanh (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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

#endif    // MPFRCPP_FUNCTIONS_HYPERBOLIC
