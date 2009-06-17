#ifndef MPFRCPP_LIBRARY_GLOBAL_PARAMETERS
#define MPFRCPP_LIBRARY_GLOBAL_PARAMETERS

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
 * @file global_parameters.hpp
 * @date 2007-03-23
 * MPFRCPP global parameters.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

    //------------------------------------------------------------

    /**
     * MPFRCPP global parameters
     */

    class GlobalParameters {

            Precision defaultPrecision_;
            Base defaultBase_;
            RoundMode defaultRoundMode_;
            bool initializeByZero_; // initializeByNaN otherwise

        public:

            GlobalParameters (const Precision& pr = Precision(), const Base& b = Base(), const RoundMode& rm = RoundMode(), bool initializeByZero = true) throw() : defaultPrecision_ (pr), defaultBase_ (b), defaultRoundMode_ (rm), initializeByZero_(initializeByZero) {}

            Base getDefaultBase () const throw() {
                return defaultBase_;
            }
            void setDefaultBase (const Base& b) throw() {
                defaultBase_ = b;
            }

            Precision getDefaultPrecision () const throw() {
                return defaultPrecision_;
            }
            void setDefaultPrecision (const Precision& pr) throw() {
                defaultPrecision_ = pr;
            }
            RoundMode getDefaultRoundMode () const throw() {
                return defaultRoundMode_;
            }
            void setDefaultRoundMode (const RoundMode& rm) throw() {
                defaultRoundMode_ = rm;
            }

            bool initializeByZero () throw() {
                bool z = initializeByZero_;
                initializeByZero_ = true;
                return z;
            }

            bool initializeByNaN () throw() {
                bool z = !initializeByZero_;
                initializeByZero_ = false;
                return z;
            }

            bool isInitializedByZero () const throw() {
                return initializeByZero_;
            }

            bool isInitializedByNaN() const throw() {
                return !initializeByZero_;
            }

            // Methods implemented in MPFR:

            static int setExponentMin (const Exponent& e) throw() {
                return mpfr_set_emin(e.getMpExpT());
            }
            static Exponent getExponentMin () throw() {
                return Exponent (mpfr_get_emin());
            }
            static int setExponentMax (const Exponent& e) throw() {
                return mpfr_set_emax (e.getMpExpT());
            }
            static Exponent getExponentMax () throw() {
                return Exponent (mpfr_get_emax());
            }

            static inline Exponent getExponentMinMin() throw() {
                return Exponent (mpfr_get_emin_min());
            }
            static inline Exponent getExponentMinMax() throw() {
                return Exponent (mpfr_get_emin_max());
            }
            static inline Exponent getExponentMaxMin() throw() {
                return Exponent (mpfr_get_emax_min());
            }
            static inline Exponent getExponentMaxMax() throw() {
                return Exponent (mpfr_get_emax_max());
            }
    };

} // namespace mpfr

#endif    // MPFRCPP_LIBRARY_GLOBAL_PARAMETERS
