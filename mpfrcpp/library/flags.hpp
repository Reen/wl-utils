#ifndef MPFRCPP_LIBRARY_FLAGS
#define MPFRCPP_LIBRARY_FLAGS

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
 * @file flags.hpp
 * @date 2007-03-23
 * MPFRCPP flags.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

    //------------------------------------------------------------

    /**
     * MPFRCPP flags
     */

    class Flags {
        public:
            static void clear () throw () {
                return mpfr_clear_flags ();
            }

            static bool getErange () throw () {
                if (mpfr_erangeflag_p() == 0)
                    return false;
                else
                    return true;
            }
            static bool getInexact () throw () {
                if (mpfr_inexflag_p() == 0)
                    return false;
                else
                    return true;
            }
            static bool getNaN () throw () {
                if (mpfr_nanflag_p() == 0)
                    return false;
                else
                    return true;
            }
            static bool getOverflow () throw () {
                if (mpfr_overflow_p() == 0)
                    return false;
                else
                    return true;
            }
            static bool getUnderflow () throw () {
                if (mpfr_underflow_p() == 0)
                    return false;
                else
                    return true;
            }

            static void setErange (bool f) throw () {
                if (f)
                    mpfr_set_erangeflag();
                else
                    mpfr_clear_erangeflag();
            }
            static void setInexact (bool f) throw () {
                if (f)
                    mpfr_set_inexflag();
                else
                    mpfr_clear_inexflag();
            }
            static void setNaN (bool f) throw () {
                if (f)
                    mpfr_set_nanflag();
                else
                    mpfr_clear_nanflag();
            }
            static void setOverflow (bool f) throw () {
                if (f)
                    mpfr_set_overflow();
                else
                    mpfr_clear_overflow();
            }
            static void setUnderflow (bool f) throw () {
                if (f)
                    mpfr_set_underflow();
                else
                    mpfr_clear_underflow();
            }
    };

    //------------------------------------------------------------

}    // namespace mpfr

#endif    // MPFRCPP_LIBRARY_FLAGS
