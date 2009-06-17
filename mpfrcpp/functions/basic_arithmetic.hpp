#ifndef MPFRCPP_FUNCTIONS_BASIC_ARITHMETIC
#define MPFRCPP_FUNCTIONS_BASIC_ARITHMETIC

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
 * @file basic_arithmetic.hpp
 * @date 2007-04-03
 * MPFRCPP basic arithmetic functions.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

/**
 * @class AddClass
 * Addition
 */

    class AddClass : public NumericFunction {
        public:
            AddClass () throw() : NumericFunction () {}
            AddClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            AddClass (const Precision& pr) throw() : NumericFunction (pr) {}
            AddClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_add (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const Real& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const Real& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const unsigned long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_add_ui (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const unsigned long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const unsigned long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const unsigned long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const unsigned int &y) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y));
            }
            Real operator() (const Real& x, const unsigned int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const unsigned int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr);
            }
            Real operator() (const Real& x, const unsigned int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), rm);
            }
            Real operator() (const Real& x, const unsigned short int &y) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y));
            }
            Real operator() (const Real& x, const unsigned short int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const unsigned short int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr);
            }
            Real operator() (const Real& x, const unsigned short int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), rm);
            }

            Real operator() (const Real& x, const long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_add_si (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const int &y) const throw() {
                return (*this) (x, static_cast<long int>(y));
            }
            Real operator() (const Real& x, const int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<long int>(y), pr);
            }
            Real operator() (const Real& x, const int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), rm);
            }
            Real operator() (const Real& x, const short int &y) const throw() {
                return (*this) (x, static_cast<long int>(y));
            }
            Real operator() (const Real& x, const short int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const short int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<long int>(y), pr);
            }
            Real operator() (const Real& x, const short int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), rm);
            }

            Real operator() (const Real& x, const mpz_t& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_add_z (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpz_t& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpz_t& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpz_t& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const Real& x, const mpz_class& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_add_z (z.getMpfrT(), x.getMpfrT(), y.get_mpz_t(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpz_class& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpz_class& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpz_class& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const Real& x, const mpq_t& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_add_q (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpq_t& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpq_t& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpq_t& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const Real& x, const mpq_class& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_add_q (z.getMpfrT(), x.getMpfrT(), y.get_mpq_t(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpq_class& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpq_class& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpq_class& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const unsigned long int &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const unsigned long int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const unsigned long int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const unsigned long int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }
            Real operator() (const unsigned int &x, const Real& y) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x));
            }
            Real operator() (const unsigned int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), pr, rm);
            }
            Real operator() (const unsigned int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), pr);
            }
            Real operator() (const unsigned int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), rm);
            }
            Real operator() (const unsigned short int &x, const Real& y) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x));
            }
            Real operator() (const unsigned short int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), pr, rm);
            }
            Real operator() (const unsigned short int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), pr);
            }
            Real operator() (const unsigned short int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), rm);
            }

            Real operator() (const long int &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const long int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const long int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const long int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }
            Real operator() (const int &x, const Real& y) const throw() {
                return (*this) (y, static_cast<long int>(x));
            }
            Real operator() (const int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<long int>(x), pr, rm);
            }
            Real operator() (const int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, static_cast<long int>(x), pr);
            }
            Real operator() (const int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<long int>(x), rm);
            }
            Real operator() (const short int &x, const Real& y) const throw() {
                return (*this) (y, static_cast<long int>(x));
            }
            Real operator() (const short int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<long int>(x), pr, rm);
            }
            Real operator() (const short int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, static_cast<long int>(x), pr);
            }
            Real operator() (const short int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<long int>(x), rm);
            }

            Real operator() (const mpz_t &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const mpz_t &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const mpz_t &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const mpz_t &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const mpz_class &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const mpz_class &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const mpz_class &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const mpz_class &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const mpq_t &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const mpq_t &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const mpq_t &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const mpq_t &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const mpq_class &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const mpq_class &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const mpq_class &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const mpq_class &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }
#endif    // GMP_CPP_INTERFACE

    };    // AddClass


/**
 * @class SubClass
 * Subtraction
 */

    class SubClass : public NumericFunction {
        public:
            SubClass () throw() : NumericFunction () {}
            SubClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            SubClass (const Precision& pr) throw() : NumericFunction (pr) {}
            SubClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_sub (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const Real& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const Real& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const unsigned long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_sub_ui (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const unsigned long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const unsigned long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const unsigned long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const unsigned int &y) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y));
            }
            Real operator() (const Real& x, const unsigned int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const unsigned int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr);
            }
            Real operator() (const Real& x, const unsigned int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), rm);
            }
            Real operator() (const Real& x, const unsigned short int &y) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y));
            }
            Real operator() (const Real& x, const unsigned short int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const unsigned short int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr);
            }
            Real operator() (const Real& x, const unsigned short int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), rm);
            }

            Real operator() (const Real& x, const long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_sub_si (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const int &y) const throw() {
                return (*this) (x, static_cast<long int>(y));
            }
            Real operator() (const Real& x, const int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<long int>(y), pr);
            }
            Real operator() (const Real& x, const int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), rm);
            }
            Real operator() (const Real& x, const short int &y) const throw() {
                return (*this) (x, static_cast<long int>(y));
            }
            Real operator() (const Real& x, const short int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const short int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<long int>(y), pr);
            }
            Real operator() (const Real& x, const short int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), rm);
            }

            Real operator() (const Real& x, const mpz_t& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_sub_z (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpz_t& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpz_t& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpz_t& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const Real& x, const mpz_class& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_sub_z (z.getMpfrT(), x.getMpfrT(), y.get_mpz_t(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpz_class& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpz_class& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpz_class& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const Real& x, const mpq_t& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_sub_q (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpq_t& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpq_t& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpq_t& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const Real& x, const mpq_class& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_sub_q (z.getMpfrT(), x.getMpfrT(), y.get_mpq_t(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpq_class& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpq_class& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpq_class& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const unsigned long int& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_ui_sub (z.getMpfrT(), x, y.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const unsigned long int& x, const Real& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const unsigned long int& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const unsigned long int& x, const Real& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const unsigned int &x, const Real& y) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y);
            }
            Real operator() (const unsigned int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr, rm);
            }
            Real operator() (const unsigned int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr);
            }
            Real operator() (const unsigned int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, rm);
            }
            Real operator() (const unsigned short int &x, const Real& y) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y);
            }
            Real operator() (const unsigned short int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr, rm);
            }
            Real operator() (const unsigned short int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr);
            }
            Real operator() (const unsigned short int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, rm);
            }

            Real operator() (const long int& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_si_sub (z.getMpfrT(), x, y.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const long int& x, const Real& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const long int& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const long int& x, const Real& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const int &x, const Real& y) const throw() {
                return (*this) (static_cast<long int>(x), y);
            }
            Real operator() (const int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<long int>(x), y, pr, rm);
            }
            Real operator() (const int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (static_cast<long int>(x), y, pr);
            }
            Real operator() (const int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (static_cast<long int>(x), y, rm);
            }
            Real operator() (const short int &x, const Real& y) const throw() {
                return (*this) (static_cast<long int>(x), y);
            }
            Real operator() (const short int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<long int>(x), y, pr, rm);
            }
            Real operator() (const short int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (static_cast<long int>(x), y, pr);
            }
            Real operator() (const short int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (static_cast<long int>(x), y, rm);
            }
    };    // SubClass


/**
 * @class MulClass
 * Multiplication
 */

    class MulClass : public NumericFunction {
        public:
            MulClass () throw() : NumericFunction () {}
            MulClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            MulClass (const Precision& pr) throw() : NumericFunction (pr) {}
            MulClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_mul (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const Real& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const Real& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const unsigned long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_mul_ui (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const unsigned long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const unsigned long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const unsigned long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const unsigned int &y) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y));
            }
            Real operator() (const Real& x, const unsigned int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const unsigned int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr);
            }
            Real operator() (const Real& x, const unsigned int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), rm);
            }
            Real operator() (const Real& x, const unsigned short int &y) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y));
            }
            Real operator() (const Real& x, const unsigned short int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const unsigned short int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr);
            }
            Real operator() (const Real& x, const unsigned short int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), rm);
            }

            Real operator() (const Real& x, const long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_mul_si (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const int &y) const throw() {
                return (*this) (x, static_cast<long int>(y));
            }
            Real operator() (const Real& x, const int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<long int>(y), pr);
            }
            Real operator() (const Real& x, const int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), rm);
            }
            Real operator() (const Real& x, const short int &y) const throw() {
                return (*this) (x, static_cast<long int>(y));
            }
            Real operator() (const Real& x, const short int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const short int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<long int>(y), pr);
            }
            Real operator() (const Real& x, const short int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), rm);
            }

            Real operator() (const Real& x, const mpz_t& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_mul_z (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpz_t& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpz_t& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpz_t& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const Real& x, const mpz_class& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_mul_z (z.getMpfrT(), x.getMpfrT(), y.get_mpz_t(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpz_class& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpz_class& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpz_class& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const Real& x, const mpq_t& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_mul_q (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpq_t& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpq_t& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpq_t& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const Real& x, const mpq_class& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_mul_q (z.getMpfrT(), x.getMpfrT(), y.get_mpq_t(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpq_class& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpq_class& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpq_class& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const unsigned long int &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const unsigned long int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const unsigned long int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const unsigned long int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }
            Real operator() (const unsigned int &x, const Real& y) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x));
            }
            Real operator() (const unsigned int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), pr, rm);
            }
            Real operator() (const unsigned int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), pr);
            }
            Real operator() (const unsigned int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), rm);
            }
            Real operator() (const unsigned short int &x, const Real& y) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x));
            }
            Real operator() (const unsigned short int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), pr, rm);
            }
            Real operator() (const unsigned short int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), pr);
            }
            Real operator() (const unsigned short int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<unsigned long int>(x), rm);
            }

            Real operator() (const long int &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const long int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const long int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const long int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }
            Real operator() (const int &x, const Real& y) const throw() {
                return (*this) (y, static_cast<long int>(x));
            }
            Real operator() (const int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<long int>(x), pr, rm);
            }
            Real operator() (const int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, static_cast<long int>(x), pr);
            }
            Real operator() (const int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<long int>(x), rm);
            }
            Real operator() (const short int &x, const Real& y) const throw() {
                return (*this) (y, static_cast<long int>(x));
            }
            Real operator() (const short int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<long int>(x), pr, rm);
            }
            Real operator() (const short int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, static_cast<long int>(x), pr);
            }
            Real operator() (const short int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, static_cast<long int>(x), rm);
            }

            Real operator() (const mpz_t &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const mpz_t &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const mpz_t &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const mpz_t &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const mpz_class &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const mpz_class &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const mpz_class &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const mpz_class &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const mpq_t &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const mpq_t &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const mpq_t &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const mpq_t &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const mpq_class &x, const Real& y) const throw() {
                return (*this) (y, x);
            }
            Real operator() (const mpq_class &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (y, x, pr, rm);
            }
            Real operator() (const mpq_class &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (y, x, pr);
            }
            Real operator() (const mpq_class &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (y, x, rm);
            }
#endif    // GMP_CPP_INTERFACE

    };    // MulClass


/**
 * @class DivClass
 * Division
 */

    class DivClass : public NumericFunction {
        public:
            DivClass () throw() : NumericFunction () {}
            DivClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            DivClass (const Precision& pr) throw() : NumericFunction (pr) {}
            DivClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_div (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const Real& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const Real& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const unsigned long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_div_ui (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const unsigned long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const unsigned long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const unsigned long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const unsigned int &y) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y));
            }
            Real operator() (const Real& x, const unsigned int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const unsigned int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr);
            }
            Real operator() (const Real& x, const unsigned int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), rm);
            }
            Real operator() (const Real& x, const unsigned short int &y) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y));
            }
            Real operator() (const Real& x, const unsigned short int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const unsigned short int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr);
            }
            Real operator() (const Real& x, const unsigned short int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), rm);
            }

            Real operator() (const Real& x, const long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_div_si (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const int &y) const throw() {
                return (*this) (x, static_cast<long int>(y));
            }
            Real operator() (const Real& x, const int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<long int>(y), pr);
            }
            Real operator() (const Real& x, const int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), rm);
            }
            Real operator() (const Real& x, const short int &y) const throw() {
                return (*this) (x, static_cast<long int>(y));
            }
            Real operator() (const Real& x, const short int &y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const short int &y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<long int>(y), pr);
            }
            Real operator() (const Real& x, const short int &y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), rm);
            }

            Real operator() (const Real& x, const mpz_t& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_div_z (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpz_t& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpz_t& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpz_t& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const Real& x, const mpz_class& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_div_z (z.getMpfrT(), x.getMpfrT(), y.get_mpz_t(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpz_class& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpz_class& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpz_class& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const Real& x, const mpq_t& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_div_q (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpq_t& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpq_t& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpq_t& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const Real& x, const mpq_class& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_div_q (z.getMpfrT(), x.getMpfrT(), y.get_mpq_t(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpq_class& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpq_class& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpq_class& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const unsigned long int& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_ui_div (z.getMpfrT(), x, y.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const unsigned long int& x, const Real& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const unsigned long int& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const unsigned long int& x, const Real& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const unsigned int &x, const Real& y) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y);
            }
            Real operator() (const unsigned int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr, rm);
            }
            Real operator() (const unsigned int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr);
            }
            Real operator() (const unsigned int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, rm);
            }
            Real operator() (const unsigned short int &x, const Real& y) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y);
            }
            Real operator() (const unsigned short int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr, rm);
            }
            Real operator() (const unsigned short int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr);
            }
            Real operator() (const unsigned short int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, rm);
            }

            Real operator() (const long int& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_si_div (z.getMpfrT(), x, y.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const long int& x, const Real& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const long int& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const long int& x, const Real& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const int &x, const Real& y) const throw() {
                return (*this) (static_cast<long int>(x), y);
            }
            Real operator() (const int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<long int>(x), y, pr, rm);
            }
            Real operator() (const int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (static_cast<long int>(x), y, pr);
            }
            Real operator() (const int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (static_cast<long int>(x), y, rm);
            }
            Real operator() (const short int &x, const Real& y) const throw() {
                return (*this) (static_cast<long int>(x), y);
            }
            Real operator() (const short int &x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<long int>(x), y, pr, rm);
            }
            Real operator() (const short int &x, const Real& y, const Precision &pr) const throw() {
                return (*this) (static_cast<long int>(x), y, pr);
            }
            Real operator() (const short int &x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (static_cast<long int>(x), y, rm);
            }
    };    // DivClass


/**
 * @class NegClass
 * Unary negative sign
 */

    class NegClass : public NumericFunction {
        public:
            NegClass () throw() : NumericFunction () {}
            NegClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            NegClass (const Precision& pr) throw() : NumericFunction (pr) {}
            NegClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &pr, const RoundMode &rm) const throw() {
                Real y (pr);
                mpfr_neg (y.getMpfrT(), x.getMpfrT(), rm.getMpfrRndT());
                return y;
            }
            Real operator() (const Real& x, const Precision &pr) const throw() {
                return (*this)(x, pr, getRoundMode());
            }
            Real operator() (const Real& x, const RoundMode &rm) const throw() {
                return (*this)(x, getPrecision(), rm);
            }
            Real operator() (const Real& x) const throw() {
                return (*this)(x, getPrecision(), getRoundMode());
            }
    };


/**
 * @class AbsClass
 * Absolute value
 */

    class AbsClass : public NumericFunction {
        public:
            AbsClass () throw() : NumericFunction () {}
            AbsClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            AbsClass (const Precision& pr) throw() : NumericFunction (pr) {}
            AbsClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &pr, const RoundMode &rm) const throw() {
                Real y (pr);
                mpfr_abs (y.getMpfrT(), x.getMpfrT(), rm.getMpfrRndT());
                return y;
            }
            Real operator() (const Real& x, const Precision &pr) const throw() {
                return (*this)(x, pr, getRoundMode());
            }
            Real operator() (const Real& x, const RoundMode &rm) const throw() {
                return (*this)(x, getPrecision(), rm);
            }
            Real operator() (const Real& x) const throw() {
                return (*this)(x, getPrecision(), getRoundMode());
            }
    };


/**
 * @class SqrtClass
 * Square root
 */

    class SqrtClass : public NumericFunction {
        public:
            SqrtClass () throw() : NumericFunction () {}
            SqrtClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            SqrtClass (const Precision& pr) throw() : NumericFunction (pr) {}
            SqrtClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &pr, const RoundMode &rm) const throw() {
                Real y (pr);
                mpfr_sqrt (y.getMpfrT(), x.getMpfrT(), rm.getMpfrRndT());
                return y;
            }
            Real operator() (const Real& x, const Precision &pr) const throw() {
                return (*this)(x, pr, getRoundMode());
            }
            Real operator() (const Real& x, const RoundMode &rm) const throw() {
                return (*this)(x, getPrecision(), rm);
            }
            Real operator() (const Real& x) const throw() {
                return (*this)(x, getPrecision(), getRoundMode());
            }
    };


/**
 * @class CbrtClass
 * Cubic root
 */

    class CbrtClass : public NumericFunction {
        public:
            CbrtClass () throw() : NumericFunction () {}
            CbrtClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            CbrtClass (const Precision& pr) throw() : NumericFunction (pr) {}
            CbrtClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &pr, const RoundMode &rm) const throw() {
                Real y (pr);
                mpfr_cbrt (y.getMpfrT(), x.getMpfrT(), rm.getMpfrRndT());
                return y;
            }
            Real operator() (const Real& x, const Precision &pr) const throw() {
                return (*this)(x, pr, getRoundMode());
            }
            Real operator() (const Real& x, const RoundMode &rm) const throw() {
                return (*this)(x, getPrecision(), rm);
            }
            Real operator() (const Real& x) const throw() {
                return (*this)(x, getPrecision(), getRoundMode());
            }
    };


/**
 * @class RootClass
 * k-th root
 */

    class RootClass : public NumericFunction {
        public:
            RootClass () throw() : NumericFunction () {}
            RootClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            RootClass (const Precision& pr) throw() : NumericFunction (pr) {}
            RootClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const unsigned long int k, const Precision &pr, const RoundMode &rm) const throw() {
                Real y (pr);
                mpfr_root (y.getMpfrT(), x.getMpfrT(), k, rm.getMpfrRndT());
                return y;
            }
            Real operator() (const Real& x, const unsigned long int k, const Precision &pr) const throw() {
                return (*this)(x, k, pr, getRoundMode());
            }
            Real operator() (const Real& x, const unsigned long int k, const RoundMode &rm) const throw() {
                return (*this)(x, k, getPrecision(), rm);
            }
            Real operator() (const Real& x, const unsigned long int k) const throw() {
                return (*this)(x, k, getPrecision(), getRoundMode());
            }
            Real operator() (const Real& x, const unsigned int k) const throw() {
                return (*this) (x, static_cast<unsigned long int>(k));
            }
            Real operator() (const Real& x, const unsigned int k, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(k), pr, rm);
            }
            Real operator() (const Real& x, const unsigned int k, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(k), pr);
            }
            Real operator() (const Real& x, const unsigned int k, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(k), rm);
            }
            Real operator() (const Real& x, const unsigned short int k) const throw() {
                return (*this) (x, static_cast<unsigned long int>(k));
            }
            Real operator() (const Real& x, const unsigned short int k, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(k), pr, rm);
            }
            Real operator() (const Real& x, const unsigned short int k, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(k), pr);
            }
            Real operator() (const Real& x, const unsigned short int k, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(k), rm);
            }
    };


/**
 * @class SqrClass
 * Square
 */

    class SqrClass : public NumericFunction {
        public:
            SqrClass () throw() : NumericFunction () {}
            SqrClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            SqrClass (const Precision& pr) throw() : NumericFunction (pr) {}
            SqrClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &pr, const RoundMode &rm) const throw() {
                Real y (pr);
                mpfr_sqr (y.getMpfrT(), x.getMpfrT(), rm.getMpfrRndT());
                return y;
            }
            Real operator() (const Real& x, const Precision &pr) const throw() {
                return (*this)(x, pr, getRoundMode());
            }
            Real operator() (const Real& x, const RoundMode &rm) const throw() {
                return (*this)(x, getPrecision(), rm);
            }
            Real operator() (const Real& x) const throw() {
                return (*this)(x, getPrecision(), getRoundMode());
            }
    };


/**
 * @class PowClass
 * Power
 */

    class PowClass : public NumericFunction {
        public:
        
            PowClass () throw() : NumericFunction () {}
            PowClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            PowClass (const Precision& pr) throw() : NumericFunction (pr) {}
            PowClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_pow (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const Real& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const Real& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
  
            Real operator() (const Real& x, const unsigned long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_pow_ui (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const unsigned long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const unsigned long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const unsigned long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const unsigned int& y) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y));
            }
            Real operator() (const Real& x, const unsigned int& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const unsigned int& y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr);
            }
            Real operator() (const Real& x, const unsigned int& y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), rm);
            }
            Real operator() (const Real& x, const unsigned short int& y) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y));
            }
            Real operator() (const Real& x, const unsigned short int& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const unsigned short int& y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), pr);
            }
            Real operator() (const Real& x, const unsigned short int& y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<unsigned long int>(y), rm);
            }

            Real operator() (const unsigned long int& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_ui_pow (z.getMpfrT(), x, y.getMpfrT(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const unsigned long int& x, const Real& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const unsigned long int& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const unsigned long int& x, const Real& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
    
            Real operator() (const unsigned int& x, const Real& y) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y);
            }
            Real operator() (const unsigned int& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr, rm);
            }
            Real operator() (const unsigned int& x, const Real& y, const Precision &pr) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr);
            }
            Real operator() (const unsigned int& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, rm);
            }
            Real operator() (const unsigned short int& x, const Real& y) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y);
            }
            Real operator() (const unsigned short int& x, const Real& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr, rm);
            }
            Real operator() (const unsigned short int& x, const Real& y, const Precision &pr) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, pr);
            }
            Real operator() (const unsigned short int& x, const Real& y, const RoundMode &rm) const throw() {
                return (*this) (static_cast<unsigned long int>(x), y, rm);
            }
  
            Real operator() (const Real& x, const long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_pow_si (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

            Real operator() (const Real& x, const int& y) const throw() {
                return (*this) (x, static_cast<long int>(y));
            }
            Real operator() (const Real& x, const int& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const int& y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<long int>(y), pr);
            }
            Real operator() (const Real& x, const int& y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), rm);
            }
            Real operator() (const Real& x, const short int& y) const throw() {
                return (*this) (x, static_cast<long int>(y));
            }
            Real operator() (const Real& x, const short int& y, const Precision &pr, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), pr, rm);
            }
            Real operator() (const Real& x, const short int& y, const Precision &pr) const throw() {
                return (*this) (x, static_cast<long int>(y), pr);
            }
            Real operator() (const Real& x, const short int& y, const RoundMode &rm) const throw() {
                return (*this) (x, static_cast<long int>(y), rm);
            }

            Real operator() (const Real& x, const mpz_t& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_pow_z (z.getMpfrT(), x.getMpfrT(), y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpz_t& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpz_t& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpz_t& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }

#ifdef GMP_CPP_INTERFACE
            Real operator() (const Real& x, const mpz_class& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_pow_z (z.getMpfrT(), x.getMpfrT(), y.get_mpz_t(), rm.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const mpz_class& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const Real& x, const mpz_class& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const Real& x, const mpz_class& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
#endif    // GMP_CPP_INTERFACE

            Real operator() (const unsigned long int& x, const unsigned long int& y, const Precision &pr, const RoundMode &rm) const throw() {
                Real z (pr);
                mpfr_ui_pow_ui (z.getMpfrT(), x, y, rm.getMpfrRndT());
                return z;
            }
            Real operator() (const unsigned long int& x, const unsigned long int& y, const Precision &pr) const throw() {
                return (*this)(x, y, pr, getRoundMode());
            }
            Real operator() (const unsigned long int& x, const unsigned long int& y, const RoundMode &rm) const throw() {
                return (*this)(x, y, getPrecision(), rm);
            }
            Real operator() (const unsigned long int& x, const unsigned long int& y) const throw() {
                return (*this)(x, y, getPrecision(), getRoundMode());
            }
    };

} // namespace mpfr

#endif    // MPFRCPP_FUNCTIONS_BASIC_ARITHMETIC
