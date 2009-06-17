#ifndef MPFRCPP_FUNCTIONS_EXPONENTIAL
#define MPFRCPP_FUNCTIONS_EXPONENTIAL

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
 * @file exponential.hpp
 * @date 2007-04-03
 * MPFRCPP exponential functions.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {


/**
 * @class ExpClass
 * Exponential
 */

    class ExpClass : public NumericFunction {
        public:
            ExpClass () throw() : NumericFunction () {}
            ExpClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            ExpClass (const Precision& pr) throw() : NumericFunction (pr) {}
            ExpClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_exp (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class Exp10Class
 * 10^x
 */

    class Exp10Class : public NumericFunction {
        public:
            Exp10Class () throw() : NumericFunction () {}
            Exp10Class (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            Exp10Class (const Precision& pr) throw() : NumericFunction (pr) {}
            Exp10Class (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_exp10 (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class Exp2Class
 * 2^x
 */

    class Exp2Class : public NumericFunction {
        public:
            Exp2Class () throw() : NumericFunction () {}
            Exp2Class (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            Exp2Class (const Precision& pr) throw() : NumericFunction (pr) {}
            Exp2Class (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_exp2 (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class Expm1Class
 * Exponential of x-1
 */

    class Expm1Class : public NumericFunction {
        public:
            Expm1Class () throw() : NumericFunction () {}
            Expm1Class (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            Expm1Class (const Precision& pr) throw() : NumericFunction (pr) {}
            Expm1Class (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_expm1 (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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

#endif    // MPFRCPP_FUNCTIONS_EXPONENTIAL
