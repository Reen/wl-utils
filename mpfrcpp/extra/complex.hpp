#ifndef MPFRCPP_EXTRA_COMPLEX
#define MPFRCPP_EXTRA_COMPLEX

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
 * @file complex.hpp
 * @date 2007-07-04
 * Complex numbers implementation.
 * Based on the GNU ISO C++ Library implementation by Gabriel Dos Reis.
 * It's not a std::complex<T> specialization for T = mpfrcpp::Real
 * because of distinctions in different std::complex<T> implementations
 * (actually, not all implementations are ISO-conforming).
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

#include "std_overloads.hpp"
#include <nacre/complex.hpp>

namespace mpfr {

typedef class nacre::complex::Complex<Real> Complex;
using namespace nacre::complex;

}     // namespace mpfr

#endif    // MPFRCPP_EXTRA_COMPLEX
