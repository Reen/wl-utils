#ifndef MPFRCPP_EXTRA_LIMITS
#define MPFRCPP_EXTRA_LIMITS

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
 * @file limits.hpp
 * @date 2007-04-13
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 *
 * Partial std::numeric_limits<Real> specification.
 */

#include <limits>

namespace std {

/**
 * numeric_limits<mpfr::Real>::is_specialized == false since the
 * complete specification depends on type precision.
 * Current code should be used to get epsilon / NaN / Infinity only.
 */

    template<> class numeric_limits<mpfr::Real> {
    public:
        static const bool is_specialized = false; // FIXME
        static const int radix = 2;
        static const bool is_signed = true;
        static const bool is_integer = false;
        static const bool is_iec559 = true;
        static const bool has_infinity = true;
        static const bool has_quiet_NaN = true;
        static const bool is_bounded = true;
        static const bool is_modulo = false;
        static const bool is_exact = false;

        static mpfr::Real epsilon () throw() { return mpfr::Real::epsilon(); }
        static mpfr::Real quiet_NaN() throw() { return mpfr::Real (std::numeric_limits<double>::quiet_NaN()); }
        static mpfr::Real signaling_NaN() throw() { return mpfr::Real (std::numeric_limits<double>::quiet_NaN()); }
        static mpfr::Real infinity() throw() { return mpfr::Real (std::numeric_limits<double>::infinity()); }
    };

} // namespace std

#endif    // MPFRCPP_EXTRA_LIMITS
