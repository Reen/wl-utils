#ifndef MPFRCPP_REAL_FITS
#define MPFRCPP_REAL_FITS

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
 * @file fits.hpp
 * @date 2007-10-25
 * mpfr::Real fits<T> method.
 * Based on ISO/IEC 14882:1998, section 18.2.1, `Numeric limits'.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

    template <typename T> bool Real::isFits () const throw() {
        if (isNumber()) {

            if (sign() < 0 && !std::numeric_limits<T>::is_signed)
                return false;

            Real y (getPrecision());
            mpfr_abs (y.getMpfrT(), getMpfrT(),
                      getParameters().getDefaultRoundMode().getMpfrRndT());

            if (y < Real(std::numeric_limits<T>::min()))
                return false;

            if (y > Real(std::numeric_limits<T>::max()))
                return false;

            if (!std::numeric_limits<T>::is_integer) {
                if (getExponent().getMpExpT() < std::numeric_limits<T>::min_exponent)
                    return false;
                if (getExponent().getMpExpT() > std::numeric_limits<T>::max_exponent)
                    return false;
            }
        }
        else {
            if (isNaN() &&
                    (!std::numeric_limits<T>::has_quiet_NaN ||
                     !std::numeric_limits<T>::has_signaling_NaN))
                return false;
            if (isInfinity() && !std::numeric_limits<T>::has_infinity)
                return false;
        }

        return true;

    }

}    // namespace mpfr

#endif    // MPFRCPP_REAL_FITS
