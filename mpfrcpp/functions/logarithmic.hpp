#ifndef MPFRCPP_FUNCTIONS_LOGARITHMIC
#define MPFRCPP_FUNCTIONS_LOGARITHMIC

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
 * @file logarithmic.hpp
 * @date 2007-03-31
 * MPFRCPP logarithmic functions.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {


/**
 * @class LogClass
 * Natural Logarithm
 */

    class LogClass : public NumericFunction {
        public:
            LogClass () throw() : NumericFunction () {}
            LogClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            LogClass (const Precision& pr) throw() : NumericFunction (pr) {}
            LogClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_log (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class Log10Class
 * Decimal Logarithm
 */

    class Log10Class : public NumericFunction {
        public:
            Log10Class () throw() : NumericFunction () {}
            Log10Class (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            Log10Class (const Precision& pr) throw() : NumericFunction (pr) {}
            Log10Class (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_log10 (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class Log1pClass
 * Natural Logarithm of x+1
 */

    class Log1pClass : public NumericFunction {
        public:
            Log1pClass () throw() : NumericFunction () {}
            Log1pClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            Log1pClass (const Precision& pr) throw() : NumericFunction (pr) {}
            Log1pClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_log1p (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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
 * @class Log2Class
 * Binary Logarithm
 */

    class Log2Class : public NumericFunction {
        public:
            Log2Class () throw() : NumericFunction () {}
            Log2Class (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            Log2Class (const Precision& pr) throw() : NumericFunction (pr) {}
            Log2Class (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_log2 (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
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

#endif    // MPFRCPP_FUNCTIONS_LOGARITHMIC
