#ifndef MPFRCPP_REAL_ARITHMETIC_OPERATORS
#define MPFRCPP_REAL_ARITHMETIC_OPERATORS

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
 * @file arithmetic_operators.hpp
 * @date 2007-05-09
 * mpfr::Real arithmetic operators.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

/**
 * Arithmetic operators
 */

inline Real operator+ (const unsigned long int &x, const Real &y) throw() {
    return y + x;
}
inline Real operator+ (const unsigned int &x, const Real &y) throw() {
    return y + x;
}
inline Real operator+ (const unsigned short int &x, const Real &y) throw() {
    return y + x;
}

inline Real operator+ (const long int &x, const Real &y) throw() {
    return y + x;
}
inline Real operator+ (const int &x, const Real &y) throw() {
    return y + x;
}
inline Real operator+ (const short int &x, const Real &y) throw() {
    return y + x;
}

inline Real operator+ (const mpz_t &x, const Real &y) throw() {
    return y + x;
}
inline Real operator+ (const mpq_t &x, const Real &y) throw() {
    return y + x;
}

//------------------------------------------------------------

/**
 * Subtraction
 */

inline Real operator- (const unsigned long int &x, const Real & y) throw() {
    Real z (y.getPrecision());
    mpfr_ui_sub (z.getMpfrT(), x, y.getMpfrT(), y.getParameters().getDefaultRoundMode().getMpfrRndT());
    return z;
}
inline Real operator- (const unsigned int &x, const Real & y) throw() {
    return static_cast<unsigned long int>(x) - y;
}
inline Real operator- (const unsigned short int &x, const Real & y) throw() {
    return static_cast<unsigned long int>(x) - y;
}

inline Real operator- (const long int &x, const Real &y) throw() {
    Real z (y.getPrecision());
    mpfr_si_sub (z.getMpfrT(), x, y.getMpfrT(), y.getParameters().getDefaultRoundMode().getMpfrRndT());
    return z;
}
inline Real operator- (const int &x, const Real & y) throw() {
    return static_cast<long int>(x) - y;
}
inline Real operator- (const short int &x, const Real & y) throw() {
    return static_cast<long int>(x) - y;
}

//------------------------------------------------------------

/**
 * Multiplication
 */

inline Real operator* (const unsigned long int &x, const Real &y) throw() {
    return y * x;
}
inline Real operator* (const unsigned int &x, const Real &y) throw() {
    return y * x;
}
inline Real operator* (const unsigned short int &x, const Real &y) throw() {
    return y * x;
}

inline Real operator* (const long int &x, const Real &y) throw() {
    return y * x;
}
inline Real operator* (const int &x, const Real &y) throw() {
    return y * x;
}
inline Real operator* (const short int &x, const Real &y) throw() {
    return y * x;
}

inline Real operator* (const mpz_t& y, const Real &x) throw() {
    return y * x;
}
inline Real operator* (const mpq_t& x, const Real &y) throw() {
    return y * x;
}

inline Real operator* (const mpz_class& y, const Real &x) throw() {
    return y * x;
}
inline Real operator* (const mpq_class& x, const Real &y) throw() {
    return y * x;
}

//------------------------------------------------------------

/**
 * Division
 */

inline Real operator/ (const unsigned long int &x, const Real &y) throw() {
    Real z (y.getPrecision());
    mpfr_ui_div (z.getMpfrT(), x, y.getMpfrT(), y.getParameters().getDefaultRoundMode().getMpfrRndT());
    return z;
}
inline Real operator/ (const unsigned int &x, const Real &y) throw() {
    return static_cast<unsigned long int>(x) / y;
}
inline Real operator/ (const unsigned short int &x, const Real &y) throw() {
    return static_cast<unsigned long int>(x) / y;
}

inline Real operator/ (const long int &x, const Real &y) throw() {
    Real z (y.getPrecision());
    mpfr_si_div (z.getMpfrT(), x, y.getMpfrT(), y.getParameters().getDefaultRoundMode().getMpfrRndT());
    return z;
}
inline Real operator/ (const int &x, const Real &y) throw() {
    return static_cast<long int>(x) / y;
}
inline Real operator/ (const short int &x, const Real &y) throw() {
    return static_cast<long int>(x) / y;
}

//------------------------------------------------------------

/**
 * Power
 */

inline Real operator^ (const unsigned long int& x, const Real& y) throw() {
    Real z (y.getPrecision());
    mpfr_ui_pow (z.getMpfrT(), x, y.getMpfrT(), Real::getParameters().getDefaultRoundMode().getMpfrRndT());
    return z;
}
inline Real operator^ (const unsigned int& x, const Real& y) throw() {
    return static_cast<unsigned long int>(x)^y;
}
inline Real operator^ (const unsigned short int& x, const Real& y) throw() {
    return static_cast<unsigned long int>(x)^y;
}

//------------------------------------------------------------

/**
 * Operations with assignment
 */

template <typename T> Real& operator+= (Real& x, const T &y) throw() {
    return x = x + y;
}
template <typename T> Real& operator-= (Real& x, const T &y) throw() {
    return x = x - y;
}
template <typename T> Real& operator*= (Real& x, const T &y) throw() {
    return x = x * y;
}
template <typename T> Real& operator/= (Real& x, const T &y) throw() {
    return x = x / y;
}
template <typename T> Real& operator^= (Real& x, const T &y) throw() {
    return x = x ^ y;
}

//------------------------------------------------------------

}    // namespace mpfr

#endif    // MPFRCPP_REAL_ARITHMETIC_OPERATORS
