#ifndef MPFRCPP_EXTRA_POLYNOMIAL
#define MPFRCPP_EXTRA_POLYNOMIAL

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
 * @file polynomial.hpp
 * @date 2007-07-04
 * + General polynomial class.
 * + Orthogonal polynomials (Chebyshev, Hermite, Laguerre, Legendre).
 * + Polynomial roots (Muller method).
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

#include "std_overloads.hpp"
#include <nacre/polynomial.hpp>

namespace mpfr {

typedef class nacre::polynomial::Polynomial<Real> Polynomial;
using namespace nacre::polynomial;

}     // namespace mpfr

#endif    // MPFRCPP_EXTRA_POLYNOMIAL
