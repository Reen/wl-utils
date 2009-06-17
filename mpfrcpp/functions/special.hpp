#ifndef MPFRCPP_FUNCTIONS_SPECIAL
#define MPFRCPP_FUNCTIONS_SPECIAL

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
 * @file special.hpp
 * @date 2007-04-03
 * MPFRCPP special functions: error function, complementary error
 * function, exponential integral, Gamma function, Gamma function logarithm,
 * Riemann Zeta function.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

#ifdef HAVE_BESSEL_FUNCTIONS_SUPPORT

/**
 * @class BesselJ0Class
 * First order Bessel function of order 0
 */

    class BesselJ0Class : public NumericFunction {
        public:
            BesselJ0Class () throw() : NumericFunction () {}
            BesselJ0Class (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            BesselJ0Class (const Precision& pr) throw() : NumericFunction (pr) {}
            BesselJ0Class (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_j0 (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class BesselJ1Class
 * First order Bessel function of order 1
 */

    class BesselJ1Class : public NumericFunction {
        public:
            BesselJ1Class () throw() : NumericFunction () {}
            BesselJ1Class (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            BesselJ1Class (const Precision& pr) throw() : NumericFunction (pr) {}
            BesselJ1Class (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_j1 (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class BesselJnClass
 * First order Bessel function of order n
 */

    class BesselJnClass : public NumericFunction {
        public:
            BesselJnClass () throw() : NumericFunction () {}
            BesselJnClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            BesselJnClass (const Precision& pr) throw() : NumericFunction (pr) {}
            BesselJnClass (const RoundMode& rm) throw() : NumericFunction (rm) {}
            Real operator() (const long& n, const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_jn (y.getMpfrT(), n, x.getMpfrT(), r.getMpfrRndT());
                return y;
            }
            Real operator() (const long& n, const Real& x, const Precision &p) const throw () {
                return (*this) (n, x, p, getRoundMode());
            }
            Real operator() (const long& n, const Real& x, const RoundMode &r) const throw () {
                return (*this) (n, x, getPrecision(), r);
            }
            Real operator() (const long& n, const Real& x) const throw () {
                return (*this) (n, x, getPrecision(), getRoundMode());
            }
    };


/**
 * @class BesselY0Class
 * Second order Bessel function of order 0
 */

    class BesselY0Class : public NumericFunction {
        public:
            BesselY0Class () throw() : NumericFunction () {}
            BesselY0Class (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            BesselY0Class (const Precision& pr) throw() : NumericFunction (pr) {}
            BesselY0Class (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_y0 (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class BesseYJ1Class
 * Second order Bessel function of order 1
 */

    class BesselY1Class : public NumericFunction {
        public:
            BesselY1Class () throw() : NumericFunction () {}
            BesselY1Class (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            BesselY1Class (const Precision& pr) throw() : NumericFunction (pr) {}
            BesselY1Class (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_y1 (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class BesselYnClass
 * Second order Bessel function of order n
 */

    class BesselYnClass : public NumericFunction {
        public:
            BesselYnClass () throw() : NumericFunction () {}
            BesselYnClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            BesselYnClass (const Precision& pr) throw() : NumericFunction (pr) {}
            BesselYnClass (const RoundMode& rm) throw() : NumericFunction (rm) {}
            Real operator() (const long& n, const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_yn (y.getMpfrT(), n, x.getMpfrT(), r.getMpfrRndT());
                return y;
            }
            Real operator() (const long& n, const Real& x, const Precision &p) const throw () {
                return (*this) (n, x, p, getRoundMode());
            }
            Real operator() (const long& n, const Real& x, const RoundMode &r) const throw () {
                return (*this) (n, x, getPrecision(), r);
            }
            Real operator() (const long& n, const Real& x) const throw () {
                return (*this) (n, x, getPrecision(), getRoundMode());
            }
    };

#endif    // HAVE_BESSEL_FUNCTIONS_SUPPORT


/**
 * @class EintClass
 * Exponential Integral
 */

    class EintClass : public NumericFunction {
        public:
            EintClass () throw() : NumericFunction () {}
            EintClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            EintClass (const Precision& pr) throw() : NumericFunction (pr) {}
            EintClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_eint (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class ErfClass
 * Error Function
 */

    class ErfClass : public NumericFunction {
        public:
            ErfClass () throw() : NumericFunction () {}
            ErfClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            ErfClass (const Precision& pr) throw() : NumericFunction (pr) {}
            ErfClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_erf (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class ErfcClass
 * Complementary Error Function
 */

    class ErfcClass : public NumericFunction {
        public:
            ErfcClass () throw() : NumericFunction () {}
            ErfcClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            ErfcClass (const Precision& pr) throw() : NumericFunction (pr) {}
            ErfcClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_erfc (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class GammaClass
 * Gamma Function
 */

    class GammaClass : public NumericFunction {
        public:
            GammaClass () throw() : NumericFunction () {}
            GammaClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            GammaClass (const Precision& pr) throw() : NumericFunction (pr) {}
            GammaClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_gamma (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class LngammaClass
 * Gamma Function Logarithm
 */

    class LngammaClass : public NumericFunction {
        public:
            LngammaClass () throw() : NumericFunction () {}
            LngammaClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            LngammaClass (const Precision& pr) throw() : NumericFunction (pr) {}
            LngammaClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_lngamma (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class ZetaClass
 * Riemann Zeta Function
 */

    class ZetaClass : public NumericFunction {
        public:
            ZetaClass () throw() : NumericFunction () {}
            ZetaClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            ZetaClass (const Precision& pr) throw() : NumericFunction (pr) {}
            ZetaClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_zeta (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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

#endif    // MPFRCPP_FUNCTIONS_SPECIAL
