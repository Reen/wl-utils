#ifndef MPFRCPP_FUNCTIONS_TRIGONOMETRIC
#define MPFRCPP_FUNCTIONS_TRIGONOMETRIC

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
 * @file trigonometric.hpp
 * @date 2007-04-03
 * MPFRCPP trigonometric functions.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {


/**
 * @class CosClass
 * Cosine
 */

    class CosClass : public NumericFunction {
        public:
            CosClass () throw() : NumericFunction () {}
            CosClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            CosClass (const Precision& pr) throw() : NumericFunction (pr) {}
            CosClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_cos (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class CotClass
 * Cotangent
 */

    class CotClass : public NumericFunction {
        public:
            CotClass () throw() : NumericFunction () {}
            CotClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            CotClass (const Precision& pr) throw() : NumericFunction (pr) {}
            CotClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_cot (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class CscClass
 * Cosecant
 */

    class CscClass : public NumericFunction {
        public:
            CscClass () throw() : NumericFunction () {}
            CscClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            CscClass (const Precision& pr) throw() : NumericFunction (pr) {}
            CscClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_csc (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class SecClass
 * Secant
 */

    class SecClass : public NumericFunction {
        public:
            SecClass () throw() : NumericFunction () {}
            SecClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            SecClass (const Precision& pr) throw() : NumericFunction (pr) {}
            SecClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_sec (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class SinClass
 * Sine
 */

    class SinClass : public NumericFunction {
        public:
            SinClass () throw() : NumericFunction () {}
            SinClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            SinClass (const Precision& pr) throw() : NumericFunction (pr) {}
            SinClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_sin (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class SinCosStruct
 * Sine and cosine values
 */

    class SinCosStruct {
        public:
            SinCosStruct () throw() {}
            Real sin;
            Real cos;
    };


/**
 * @class SinCosClass
 * Sine and cosine
 */

    class SinCosClass : public NumericFunction {
        public:
            SinCosClass () throw() : NumericFunction () {}
            SinCosClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            SinCosClass (const Precision& pr) throw() : NumericFunction (pr) {}
            SinCosClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            SinCosStruct operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                SinCosStruct sc;
                sc.sin = Real (p);
                sc.cos = Real (p);
                mpfr_sin_cos (sc.sin.getMpfrT(), sc.cos.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
                return sc;
            }

            SinCosStruct operator() (const Real& x, const Precision &p) const throw () {
                return (*this) (x, p, getRoundMode());
            }
            SinCosStruct operator() (const Real& x, const RoundMode &r) const throw () {
                return (*this) (x, getPrecision(), r);
            }
            SinCosStruct operator() (const Real& x) const throw () {
                return (*this) (x, getPrecision(), getRoundMode());
            }
    };


/**
 * @class TanClass
 * Tangent
 */

    class TanClass : public NumericFunction {
        public:
            TanClass () throw() : NumericFunction () {}
            TanClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            TanClass (const Precision& pr) throw() : NumericFunction (pr) {}
            TanClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_tan (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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

#endif    // MPFRCPP_FUNCTIONS_TRIGONOMETRIC
