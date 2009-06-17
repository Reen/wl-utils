#ifndef MPFRCPP_CORE_RANDOM_STATE
#define MPFRCPP_CORE_RANDOM_STATE

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
 * @file random_state.hpp
 * @date 2007-04-06
 * Wrapper to the GMP Random State type (gmp_randstate_t).
 * See GMP manual for details.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

    class RandomState {
            gmp_randstate_t rs_;
    public:
        /// Mersenne Twister algorithm
        RandomState () throw() {
            gmp_randinit_mt (rs_);
        }

        /// Copy
        RandomState (const RandomState& rs) throw() {
            gmp_randinit_set(rs_, rs.rs_);
        }
        /// Copy
        RandomState (const gmp_randstate_t& rs) throw() {
            gmp_randinit_set(rs_, rs);
        }

        /// Linear congruental algorithm X = (aX+c) mod 2^{m2exp}
        RandomState (const mpz_class& a, unsigned long int c, unsigned long int m2exp) throw() {
            gmp_randinit_lc_2exp (rs_, a.get_mpz_t(), c, m2exp);
        }

        /// Linear congruental algorithm with data selected from a table
        RandomState (unsigned long int size) throw() {
            gmp_randinit_lc_2exp_size (rs_, size);
        }

        /// Copy
        RandomState& operator= (const RandomState& rs) throw() {
            gmp_randinit_set(rs_, rs.rs_);
            return *this;
        }

        gmp_randstate_t& getGmpRandstateT () throw() {
            return rs_;
        }

        const gmp_randstate_t& getGmpRandstateT () const throw() {
            return rs_;
        }

        void seed (const mpz_class& seed) throw() {
            gmp_randseed (rs_, seed.get_mpz_t());
        }

        void seed (unsigned long int seed) throw() {
            gmp_randseed_ui (rs_, seed);
        }

        ~RandomState () throw() {
            gmp_randclear (rs_);
        }
    };

} // namespace mpfr

#endif    // MPFRCPP_CORE_RANDOM_STATE
