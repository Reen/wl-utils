#ifndef MPFRCPP_FUNCTIONS_INTEGER_RELATED
#define MPFRCPP_FUNCTIONS_INTEGER_RELATED

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
 * @file integer_related.hpp
 * @date 2007-04-08
 * MPFRCPP integer related functions.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {


/**
 * @class CeilClass
 * 
 */

    class CeilClass : public NumericFunction {
        private:  // hide round mode related items
            void setRoundMode (const RoundMode&) throw() {}
            RoundMode getRoundMode () const throw() { return Real::getParameters().getDefaultRoundMode(); }
            CeilClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            CeilClass (const RoundMode& rm) throw() : NumericFunction (rm) {}
        public:
            CeilClass () throw() : NumericFunction () {}
            CeilClass (const Precision& pr) throw() : NumericFunction (pr) {}

            Real operator() (const Real& x, const Precision &p) const throw () {
                Real y (p);
                mpfr_ceil (y.getMpfrT(), x.getMpfrT());
                return y;
            }
            Real operator() (const Real& x) const throw () {
                return (*this) (x, getPrecision());
            }
    };


/**
 * @class FloorClass
 * 
 */

    class FloorClass : public NumericFunction {
        private:  // hide round mode related items
            void setRoundMode (const RoundMode&) throw() {}
            RoundMode getRoundMode () const throw() { return Real::getParameters().getDefaultRoundMode(); }
            FloorClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            FloorClass (const RoundMode& rm) throw() : NumericFunction (rm) {}
        public:
            FloorClass () throw() : NumericFunction () {}
            FloorClass (const Precision& pr) throw() : NumericFunction (pr) {}

            Real operator() (const Real& x, const Precision &p) const throw () {
                Real y (p);
                mpfr_floor (y.getMpfrT(), x.getMpfrT());
                return y;
            }
            Real operator() (const Real& x) const throw () {
                return (*this) (x, getPrecision());
            }
    };


/**
 * @class FracClass
 * 
 */

    class FracClass : public NumericFunction {
        public:
            FracClass () throw() : NumericFunction () {}
            FracClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            FracClass (const Precision& pr) throw() : NumericFunction (pr) {}
            FracClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Precision &p, const RoundMode &r) const throw () {
                Real y (p);
                mpfr_frac (y.getMpfrT(), x.getMpfrT(), r.getMpfrRndT());
                return y;
            }
            Real operator() (const Real& x, const Precision &p) const throw () {
                return (*this) (x, p, getRoundMode());
            }
            Real operator() (const Real& x, const RoundMode &r) const throw () {
                return (*this) (x, getPrecision(), r);
            }
            Real operator() (const Real& x) const throw () {
                return (*this) (x, getPrecision(), getRoundMode());
            }
    };


#ifdef HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT
/**
 * @class RemainderClass
 * Division remainder
 */

    class RemainderClass : public NumericFunction {
        public:
            RemainderClass () throw() : NumericFunction () {}
            RemainderClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            RemainderClass (const Precision& pr) throw() : NumericFunction (pr) {}
            RemainderClass (const RoundMode& rm) throw() : NumericFunction (rm) {}

            Real operator() (const Real& x, const Real& y, const Precision &p, const RoundMode &r) const throw () {
                Real z (p);
                mpfr_remainder (z.getMpfrT(), x.getMpfrT(), y.getMpfrT(), r.getMpfrRndT());
                return z;
            }
            Real operator() (const Real& x, const Real& y, const Precision &p) const throw () {
                return (*this) (x, y, p, getRoundMode());
            }
            Real operator() (const Real& x, const Real& y, const RoundMode &r) const throw () {
                return (*this) (x, y, getPrecision(), r);
            }
            Real operator() (const Real& x, const Real& y) const throw () {
                return (*this) (x, y, getPrecision(), getRoundMode());
            }
    };
#endif    // HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT


/**
 * @class RoundClass
 * 
 */

    class RoundClass : public NumericFunction {
        private:  // hide round mode related items
            void setRoundMode (const RoundMode&) throw() {}
            RoundMode getRoundMode () const throw() { return Real::getParameters().getDefaultRoundMode(); }
            RoundClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            RoundClass (const RoundMode& rm) throw() : NumericFunction (rm) {}
        public:
            RoundClass () throw() : NumericFunction () {}
            RoundClass (const Precision& pr) throw() : NumericFunction (pr) {}

            Real operator() (const Real& x, const Precision &p) const throw () {
                Real y (p);
                mpfr_round (y.getMpfrT(), x.getMpfrT());
                return y;
            }
            Real operator() (const Real& x) const throw () {
                return (*this) (x, getPrecision());
            }
    };


/**
 * @class TruncClass
 * 
 */

    class TruncClass : public NumericFunction {
        private:  // hide round mode related items
            void setRoundMode (const RoundMode&) throw() {}
            RoundMode getRoundMode () const throw() { return Real::getParameters().getDefaultRoundMode(); }
            TruncClass (const Precision& pr, const RoundMode& rm) throw() : NumericFunction (pr, rm) {}
            TruncClass (const RoundMode& rm) throw() : NumericFunction (rm) {}
        public:
            TruncClass () throw() : NumericFunction () {}
            TruncClass (const Precision& pr) throw() : NumericFunction (pr) {}

            Real operator() (const Real& x, const Precision &p) const throw () {
                Real y (p);
                mpfr_trunc (y.getMpfrT(), x.getMpfrT());
                return y;
            }
            Real operator() (const Real& x) const throw () {
                return (*this) (x, getPrecision());
            }
    };


} // namespace mpfr

#endif    // MPFRCPP_FUNCTIONS_INTEGER_RELATED
