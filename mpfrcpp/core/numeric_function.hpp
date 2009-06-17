#ifndef MPFRCPP_CORE_NUMERIC_FUNCTION
#define MPFRCPP_CORE_NUMERIC_FUNCTION

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
 * @file numeric_function.hpp
 * @date 2007-04-03
 * MPFRCPP numeric functors base.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#include "precision.hpp"
#include "round_mode.hpp"

#include <set>
#include <algorithm>

namespace mpfr {

    //------------------------------------------------------------

    /**
     * MPFRCPP numeric function base.
     */

    class NumericFunction {
            Precision pr_;
            RoundMode rm_;
        public:

        NumericFunction () throw() : pr_(Real::getParameters().getDefaultPrecision()), rm_(Real::getParameters().getDefaultRoundMode()) {}
        NumericFunction (const Precision &pr, const RoundMode &rm) throw() : pr_(pr), rm_(rm) {}
        NumericFunction (const Precision &pr) throw() : pr_(pr), rm_(Real::getParameters().getDefaultRoundMode()) {}
        NumericFunction (const RoundMode &rm) throw() : pr_(Real::getParameters().getDefaultPrecision()), rm_(rm) {}

        Precision getPrecision () const throw() {
            return pr_;
        }
        RoundMode getRoundMode () const throw() {
            return rm_;
        }

        void setPrecision (const Precision &pr) throw() {
            pr_ = pr;
        }
        void setRoundMode (const RoundMode &rm) throw() {
            rm_ = rm;
        }
    };

    //------------------------------------------------------------

    namespace internal {

        /**
         * INTERNAL functor
         */

        class setPrecision {
                Precision pr_;
            public:
                setPrecision (const Precision& pr) throw() : pr_(pr) {}
                void operator() (NumericFunction* x) const throw() {
                    x->setPrecision(pr_);
                }
        };

        /**
         * INTERNAL functor
         */

        class setRoundMode {
                RoundMode rm_;
            public:
                setRoundMode (const RoundMode& rm) throw() : rm_(rm) {}
                void operator() (NumericFunction* x) const throw() {
                    x->setRoundMode(rm_);
                }
        };

    }    // namespace internal

    //------------------------------------------------------------

    /**
     * Set of NumericFunction objects (stored by pointers).
     * Should be used for synchronous changing of precision
     * and round mode.
     */

    class NumericFunctions {
            std::set<NumericFunction*> functions_;
        public :
            NumericFunctions () throw() {}

            void erase (NumericFunction* p) throw() {
                functions_.erase(p);
            }
            void erase (NumericFunction& p) throw() {
                functions_.erase(&p);
            }

            // NOTE: insertion keeps precision and round mode
            void insert (NumericFunction& p) throw() {
                functions_.insert(&p);
            }

            // Set Precision / RoundMode for each stored function:
            void setPrecision (const Precision &pr) throw() {
                std::for_each (functions_.begin(), functions_.end(), internal::setPrecision(pr));
            }
            void setRoundMode (const RoundMode &rm) throw() {
                std::for_each (functions_.begin(), functions_.end(), internal::setRoundMode(rm));
            }
    };

    //------------------------------------------------------------

} // namespace mpfr

#endif    // MPFRCPP_CORE_NUMERIC_FUNCTION
