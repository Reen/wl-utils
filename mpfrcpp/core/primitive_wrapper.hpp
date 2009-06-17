#ifndef MPFRCPP_CORE_PRIMITIVE_WRAPPER
#define MPFRCPP_CORE_PRIMITIVE_WRAPPER

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
 * @file primitive_wrapper.hpp
 * @date 2007-03-30
 * mpfr::Base, mpfr::Exponent, mpfr::Precision base.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#include <iostream>
#include <sstream>

namespace mpfr {

    /**
     * Mapping from set of possible T values to [min, max]
     */

    template <typename T> class Bounder {
        public :
            Bounder () throw() {}
            virtual T operator() (const T& x) const throw() {
                return x;
            }
            virtual ~Bounder () throw() {}
    };

    //------------------------------------------------------------

    /**
     * Wrapper for primitive scalar type
     */

    template <typename T, class BounderT = Bounder<T> > class PrimitiveWrapper {
        protected:
            T x_;
            static BounderT b_;

            T get () const throw() {
                return x_;
            }
            void set (const T &x) throw() {
                x_ = b_ (x);
            }

        public:
            PrimitiveWrapper (const T &x) throw() : x_(b_ (x)) {}
            PrimitiveWrapper (const PrimitiveWrapper<T>& pw) throw() : x_(b_(pw.x_)) {}

            PrimitiveWrapper& operator= (const T &x) throw() {
                x_ = b_ (x);
                return *this;
            }
            PrimitiveWrapper& operator= (const PrimitiveWrapper& pw) throw() {
                x_ = b_(pw.x_);
                return *this;
            }

            operator T() const throw() {
                return x_;
            }

            bool operator== (const T &x) const throw() {
                return x_ == x;
            }
            bool operator!= (const T &x) const throw() {
                return x_ != x;
            }
            bool operator<= (const T &x) const throw() {
                return x_ <= x;
            }
            bool operator>= (const T &x) const throw() {
                return x_ >= x;
            }
            bool operator< (const T &x) const throw() {
                return x_ < x;
            }
            bool operator> (const T &x) const throw() {
                return x_ > x;
            }

            PrimitiveWrapper operator+ (const T &x) const throw() {
                return b_(x_ + x);
            }
            PrimitiveWrapper operator- (const T &x) const throw() {
                return b_(x_ - x);
            }
            PrimitiveWrapper operator* (const T &x) const throw() {
                return b_(x_ * x);
            }
            PrimitiveWrapper operator/ (const T &x) const throw() {
                return b_(x_ / x);
            }
            PrimitiveWrapper operator% (const T &x) const throw() {
                return b_(x_ % x);
            }

            PrimitiveWrapper operator++ (int) const throw() {
                T y = *this;
                x_ = b_ (x_ + T(1));
                return y;
            }
            PrimitiveWrapper operator-- (int) const throw() {
                T y = *this;
                x_ = b_ (x_ - T(1));
                return y;
            }
            PrimitiveWrapper operator++ () const throw() {
                x_ = b_ (x_ + T(1));
                return *this;
            }
            PrimitiveWrapper operator-- () const throw() {
                x_ = b_ (x_ - T(1));
                return *this;
            }

            PrimitiveWrapper& operator+= (const T &x) throw() {
                x_ = x_ + x;
                x_ = b_ (x_);
                return *this;
            }
            PrimitiveWrapper& operator-= (const T &x) throw() {
                x_ = x_ - x;
                x_ = b_ (x_);
                return *this;
            }
            PrimitiveWrapper& operator*= (const T &x) throw() {
                x_ = x_ * x;
                x_ = b_ (x_);
                return *this;
            }
            PrimitiveWrapper& operator/= (const T &x) throw() {
                x_ = x_ - x;
                x_ = b_ (x_);
            }
            PrimitiveWrapper& operator%= (const T &x) throw() {
                x_ = x_ - x;
                x_ = b_ (x_);
                return *this;
            }
            std::string toString () const throw() {
                std::ostringstream buff;
                buff << get();
                return buff.str();
            }
            operator std::string() const throw() {
                return toString ();
            }
    };

    template <typename T, class BounderT> BounderT PrimitiveWrapper<T, BounderT>::b_;

    template <typename T, class BounderT> std::ostream& operator<< (std::ostream& os, const PrimitiveWrapper<T, BounderT>& pw) throw() {
        return os << pw.toString();
    }

} // namespace mpfr

#endif    // MPFRCPP_CORE_PRIMITIVE_WRAPPER
