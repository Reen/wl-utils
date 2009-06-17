#ifndef MPFRCPP_LIBRARY_NUMERIC_FUNCTIONS_GLOBAL_PARAMETERS_BINDER
#define MPFRCPP_LIBRARY_NUMERIC_FUNCTIONS_GLOBAL_PARAMETERS_BINDER

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
 * @file numeric_functions_global_parameters_binder.hpp
 * @date 2007-03-23
 * NumericFunctions -- GlobalParameters Binder.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

    //------------------------------------------------------------

    /**
     * NumericFunctions -- GlobalParameters Binder, should be used to
     * synchronize Precision and RoundMode for NumericFunctions and
     * GlobalParameters objects.
     */

    class NumericFunctionsGlobalParametersBinder {
            NumericFunctions& nf_;
            GlobalParameters& gp_;
        public:
            NumericFunctionsGlobalParametersBinder (NumericFunctions& nf, GlobalParameters& gp) throw() : nf_(nf), gp_(gp) {
                synchronize();
            }

            void setPrecision (const Precision& p) throw() {
                nf_.setPrecision(p);
                gp_.setDefaultPrecision(p);
            }

            void setRoundMode (const RoundMode& r) throw() {
                nf_.setRoundMode(r);
                gp_.setDefaultRoundMode(r);
            }

            void synchronize() throw() {
                nf_.setPrecision(gp_.getDefaultPrecision());
                nf_.setRoundMode(gp_.getDefaultRoundMode());
            }

            Precision getPrecision () const throw() {
                return gp_.getDefaultPrecision();
            }

            RoundMode getRoundMode () const throw() {
                return gp_.getDefaultRoundMode();
            }
    };

    //------------------------------------------------------------

} // namespace mpfr

#endif    // MPFRCPP_LIBRARY_NUMERIC_FUNCTIONS_GLOBAL_PARAMETERS_BINDER
