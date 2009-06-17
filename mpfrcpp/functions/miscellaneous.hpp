#ifndef MPFRCPP_FUNCTIONS_MISCELLANEOUS
#define MPFRCPP_FUNCTIONS_MISCELLANEOUS

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
 * @file miscellaneous.hpp
 * @date 2007-03-31
 * MPFRCPP miscellaneous functions: arithmetic-geometric mean,
 * Euclidean norm, factorial, fast multiplicaion-addition.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {


/**
 * @class AgmClass
 * Arithmetic-geometric mean
 */

    class AgmClass : public NumericFunction {
        public:
            AgmClass () throw() : NumericFunction () {}
            AgmClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            AgmClass (const Precision& pr) throw() : NumericFunction (pr) {}
            AgmClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Precision &p, const RoundMode &r) const throw () {
                Real z (p);
                mpfr_agm (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), r.getMpfrRndT());
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


/**
 * @class FactorialClass
 * Factorial
 */

    class FactorialClass : public NumericFunction {
        public:
            FactorialClass () throw() : NumericFunction () {}
            FactorialClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            FactorialClass (const Precision& pr) throw() : NumericFunction (pr) {}
            FactorialClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const unsigned long int& x, const Precision &pr, const RoundMode &rm) const throw () {
                Real y (pr);
                mpfr_fac_ui (y.getMpfrT(), x, rm.getMpfrRndT());
                return y;
            }
            Real operator() (const unsigned long int& x, const Precision &pr) const throw () {
                return (*this) (x, pr, getRoundMode());
            }
            Real operator() (const unsigned long int& x, const RoundMode &rm) const throw () {
                return (*this) (x, getPrecision(), rm);
            }
            Real operator() (const unsigned long int& x) const throw () {
                return (*this) (x, getPrecision(), getRoundMode());
            }

            Real operator() (const unsigned int&x) const throw() {
                return (*this) (static_cast<unsigned long int>(x));
            }
            Real operator() (const unsigned int&x, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), pr, rm);
            }
            Real operator() (const unsigned int&x, const Precision &pr) const throw() {
                return (*this) (static_cast<unsigned long int>(x), pr);
            }
            Real operator() (const unsigned int&x, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), rm);
            }

            Real operator() (const unsigned short int&x) const throw() {
                return (*this) (static_cast<unsigned long int>(x));
            }
            Real operator() (const unsigned short int&x, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), pr, rm);
            }
            Real operator() (const unsigned short int&x, const Precision &pr) const throw() {
                return (*this) (static_cast<unsigned long int>(x), pr);
            }
            Real operator() (const unsigned short int&x, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), rm);
            }
    };


/**
 * @class FmaClass
 * xy + z
 */

    class FmaClass : public NumericFunction {
        public:
            FmaClass () throw() : NumericFunction () {}
            FmaClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            FmaClass (const Precision& pr) throw() : NumericFunction (pr) {}
            FmaClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Real& z, const Precision &pr, const RoundMode &rm) const throw () {
                Real u (pr);
                mpfr_fma (u.getMpfrT(), x.getMpfrT(), y.getMpfrT(), z.getMpfrT(), rm.getMpfrRndT());
                return u;
            }
            Real operator() (const Real& x, const Real& y, const Real& z, const Precision &pr) const throw () {
                return (*this) (x, y, z, pr, getRoundMode());
            }
            Real operator() (const Real& x, const Real& y, const Real& z, const RoundMode &rm) const throw () {
                return (*this) (x, y, z, getPrecision(), rm);
            }
            Real operator() (const Real& x, const Real& y, const Real& z) const throw () {
                return (*this) (x, y, z, getPrecision(), getRoundMode());
            }
    };


#ifdef HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT
/**
 * @class FmsClass
 * xy - z
 */

    class FmsClass : public NumericFunction {
        public:
            FmsClass () throw() : NumericFunction () {}
            FmsClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            FmsClass (const Precision& pr) throw() : NumericFunction (pr) {}
            FmsClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Real& z, const Precision &pr, const RoundMode &rm) const throw () {
                Real u (pr);
                mpfr_fms (u.getMpfrT(), x.getMpfrT(), y.getMpfrT(), z.getMpfrT(), rm.getMpfrRndT());
                return u;
            }
            Real operator() (const Real& x, const Real& y, const Real& z, const Precision &pr) const throw () {
                return (*this) (x, y, z, pr, getRoundMode());
            }
            Real operator() (const Real& x, const Real& y, const Real& z, const RoundMode &rm) const throw () {
                return (*this) (x, y, z, getPrecision(), rm);
            }
            Real operator() (const Real& x, const Real& y, const Real& z) const throw () {
                return (*this) (x, y, z, getPrecision(), getRoundMode());
            }
    };
#endif   // HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT


/**
 * @class HypotClass
 * Euclidean norm
 */

    class HypotClass : public NumericFunction {
        public:
            HypotClass () throw() : NumericFunction () {}
            HypotClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            HypotClass (const Precision& pr) throw() : NumericFunction (pr) {}
            HypotClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw () {
                Real z (pr);
                mpfr_hypot (z.getMpfrT(), y.getMpfrT(), x.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const Real& y, const Precision &pr) const throw () {
                return (*this) (x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const Real& y, const RoundMode &rm) const throw () {
                return (*this) (x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const Real& y) const throw () {
                return (*this) (x, y, getPrecision(), getRoundMode());
            }
    };


} // namespace mpfr

#endif    // MPFRCPP_FUNCTIONS_MISCELLANEOUS
