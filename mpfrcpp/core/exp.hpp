#ifndef MPFRCPP_CORE_EXP
#define MPFRCPP_CORE_EXP

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
 * @file exp.hpp
 * @date 2007-04-01
 * MPFRCPP number exponent.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

    //------------------------------------------------------------

    /**
     * Mapping from set of possible mp_exp_t values to the
     * [mpfr_get_emin(), mpfr_get_emax()]
     */

    class ExponentBounder : public Bounder<mp_exp_t> {
            mp_exp_t min_, max_;
        public:
            ExponentBounder () throw() :
            min_( mpfr_get_emin() ), max_( mpfr_get_emax() ) {}
            mp_exp_t operator() ( const mp_exp_t& x ) const throw() {
                if ( x > max_ )
                    return max_;
                if ( x < min_ )
                    return min_;
                return x;
            }
    };

    //------------------------------------------------------------

    /**
     * Number exponent
     */

    class Exponent : public PrimitiveWrapper<mp_exp_t, ExponentBounder> {
        public:
            Exponent (mp_exp_t x = 0) throw() :
                PrimitiveWrapper<mp_exp_t, ExponentBounder>( x ) {}

            mp_exp_t getMpExpT () const throw() {
                return get ();
            }
            void setMpExpT ( mp_exp_t x ) throw() {
                set (x);
            }
    };

    //------------------------------------------------------------

} // namespace mpfr

#endif    // MPFRCPP_CORE_EXP
