#ifndef MPFRCPP_REAL_STREAM
#define MPFRCPP_REAL_STREAM

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
 * @file stream.hpp
 * @date 2007-05-13
 * Overloads for std::istream / std::ostream and mpfrcpp::Real.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#include <iostream>
#include <sstream>
#include <string>

namespace mpfr {

    /**
     * Output
     */

    inline std::ostream& operator<< (std::ostream& os, const Real& x) throw(StringOutputError) {
        std::ios_base::fmtflags f = os.flags();
        return os << internal::toString (x, os.precision(), Real::getParameters().getDefaultBase(), Real::getParameters().getDefaultRoundMode(), f & std::ios_base::showpos, f & std::ios_base::uppercase);
    }

    /**
     * Input
     */

    inline std::istream& operator>> (std::istream& is, Real& x) throw(/* InvalidNumberStringError */) {
        std::string s;
        is >> s;
        if (mpfr_set_str(x.getMpfrT(), s.c_str(), Real::getParameters().getDefaultBase(), Real::getParameters().getDefaultRoundMode().getMpfrRndT() ) == -1)
            /*throw InvalidNumberStringError();*/
            is.setstate(std::ios_base::failbit);
        return is;
    }

} // namespace mpfr

#endif // MPFRCPP_REAL_STREAM
