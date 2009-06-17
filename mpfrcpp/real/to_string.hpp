#ifndef MPFRCPP_REAL_TO_STRING
#define MPFRCPP_REAL_TO_STRING

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
 * @file to_string.hpp
 * @date 2007-03-29
 * mpfr::Real -> std::string conversions.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#include <sstream>
#include <string>
#include <cmath>

namespace mpfr {

    namespace internal {

        inline std::string toString (const mpfr::Real& x, int p, const mpfr::Base &b, const mpfr::RoundMode &r, bool showpos = false, bool uppercase = false) throw (mpfr::StringOutputError) {

            std::ostringstream s;
            mp_exp_t exp;

            if (p <= 0) p = -1;

            char* c_str = mpfr_get_str (NULL, &exp, b.getInt(), p + 1, x.getMpfrT(), r.getMpfrRndT());

            exp--; // Real exponent

            if (c_str == NULL) throw mpfr::StringOutputError();

            if (showpos && !x.isNaN() && x.sign() > 0) s << '+';

            if (mpfr_number_p (x.getMpfrT())) {
                if (c_str[ 0 ] != '-') s << std::string(c_str).insert(1, 1, '.');
                else s << std::string( c_str ).insert( 2, 1, '.' );
            }
            else s << std::string(c_str);

            mpfr_free_str(c_str);


            if (x.isNumber() && !x.isZero()) {

                if (b.getInt() > 10) s << '@';
                else if (uppercase) s << 'E';
                else s << 'e';

                if (exp < 0) s << '-';
                else s << '+';

                if (std::abs(exp) < 10) s << '0';

                s << std::abs(exp);

            }

            return s.str();
        }

    }    // namespace internal

    //------------------------------------------------------------

    inline std::string Real::toString () const throw (StringOutputError) {
        return internal::toString (*this, -1, getParameters().getDefaultBase(), getParameters().getDefaultRoundMode());
    }

    inline std::string Real::toString (int p, const RoundMode& r, const Base& b) const throw (StringOutputError) {
        return internal::toString (*this, p, b, r);
    }

    inline std::string Real::toString (int p) const throw (StringOutputError) {
        return internal::toString (*this, p, getParameters().getDefaultBase(), getParameters().getDefaultRoundMode());
    }

    inline std::string Real::toString (const RoundMode& r) const throw (StringOutputError) {
        return internal::toString (*this, -1, getParameters().getDefaultBase(), r);
    }

    inline std::string Real::toString (const Base& b) const throw(StringOutputError) {
        return internal::toString (*this, -1, b, getParameters().getDefaultRoundMode());
    }

    inline std::string Real::toString (int p, const RoundMode& r) const throw (StringOutputError) {
        return internal::toString (*this, p, getParameters().getDefaultBase(), r);
    }

    inline std::string Real::toString (int p, const Base& b) const throw (StringOutputError) {
        return internal::toString (*this, p, b, getParameters().getDefaultRoundMode() );
    }

    inline std::string Real::toString (const RoundMode& r, const Base& b) const throw (StringOutputError) {
        return internal::toString (*this, -1, b, r);
    }

} // namespace mpfr

#endif // MPFRCPP_REAL_TO_STRING
