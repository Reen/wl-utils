#ifndef MPFRCPP_EXTRA_BOOST_INTERVAL
#define MPFRCPP_EXTRA_BOOST_INTERVAL

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
 * @file boost_interval.hpp
 * @date 2007-05-05
 * boost::numeric::interval specification for MPFRCPP.
 */

#include <boost/numeric/interval.hpp>
#include <mpfrcpp/mpfrcpp.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

template<> class rounded_math<mpfr::Real> {
public:
    // mathematical operations
    static mpfr::Real add_down (const mpfr::Real& x, const mpfr::Real& y) {
        return mpfr::Add (x, y, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real add_up (const mpfr::Real& x, const mpfr::Real& y) {
        return mpfr::Add (x, y, mpfr::roundTowardInfinity);
    }

    static mpfr::Real sub_down (const mpfr::Real& x, const mpfr::Real& y) {
        return mpfr::Sub (x, y, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real sub_up (const mpfr::Real& x, const mpfr::Real& y) {
        return mpfr::Sub (x, y, mpfr::roundTowardInfinity);
    }

    static mpfr::Real mul_down (const mpfr::Real& x, const mpfr::Real& y) {
        return mpfr::Mul (x, y, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real mul_up (const mpfr::Real& x, const mpfr::Real& y) {
        return mpfr::Mul (x, y, mpfr::roundTowardInfinity);
    }

    static mpfr::Real div_down (const mpfr::Real& x, const mpfr::Real& y) {
        return mpfr::Div (x, y, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real div_up (const mpfr::Real& x, const mpfr::Real& y) {
        return mpfr::Div (x, y, mpfr::roundTowardInfinity);
    }

    static mpfr::Real sqrt_down (const mpfr::Real& x) {
        return mpfr::Sqrt (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real sqrt_up (const mpfr::Real& x) {
        return mpfr::Sqrt (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real exp_down (const mpfr::Real& x) {
        return mpfr::Exp (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real exp_up (const mpfr::Real& x) {
        return mpfr::Exp (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real log_down (const mpfr::Real& x) {
        return mpfr::Log (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real log_up (const mpfr::Real& x) {
        return mpfr::Log (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real cos_down (const mpfr::Real& x) {
        return mpfr::Cos (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real cos_up (const mpfr::Real& x) {
        return mpfr::Cos (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real tan_down (const mpfr::Real& x) {
        return mpfr::Tan (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real tan_up (const mpfr::Real& x) {
        return mpfr::Tan (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real asin_down (const mpfr::Real& x) {
        return mpfr::Asin (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real asin_up (const mpfr::Real& x) {
        return mpfr::Asin (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real acos_down (const mpfr::Real& x) {
        return mpfr::Acos (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real acos_up (const mpfr::Real& x) {
        return mpfr::Acos (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real atan_down (const mpfr::Real& x) {
        return mpfr::Atan (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real atan_up (const mpfr::Real& x) {
        return mpfr::Atan (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real sinh_down (const mpfr::Real& x) {
        return mpfr::Sinh (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real sinh_up (const mpfr::Real& x) {
        return mpfr::Sinh (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real cosh_down (const mpfr::Real& x) {
        return mpfr::Cosh (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real cosh_up (const mpfr::Real& x) {
        return mpfr::Cosh (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real tanh_down (const mpfr::Real& x) {
        return mpfr::Tanh (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real tanh_up (const mpfr::Real& x) {
        return mpfr::Tanh (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real asinh_down (const mpfr::Real& x) {
        return mpfr::Asinh (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real asinh_up (const mpfr::Real& x) {
        return mpfr::Asinh (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real acosh_down (const mpfr::Real& x) {
        return mpfr::Acosh (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real acosh_up (const mpfr::Real& x) {
        return mpfr::Acosh (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real atanh_down (const mpfr::Real& x) {
        return mpfr::Atanh (x, mpfr::roundTowardNegInfinity);
    }
    static mpfr::Real atanh_up (const mpfr::Real& x) {
        return mpfr::Atanh (x, mpfr::roundTowardInfinity);
    }

    static mpfr::Real median(const mpfr::Real& x, const mpfr::Real& y) {
        return (x+y)/mpfr::Real(2);
    }

    static mpfr::Real int_down (const mpfr::Real& x) {
        return mpfr::Floor (x);
    }
    static mpfr::Real int_up (const mpfr::Real& x) {
        return mpfr::Ceil (x);
    }

    template<typename T> static mpfr::Real conv_down (const T& x) {
        return mpfr::Real(x, mpfr::roundTowardNegInfinity);
    }
    template<typename T> static mpfr::Real conv_up  (const T& x) {
        return mpfr::Real(x, mpfr::roundTowardInfinity);
    }

  // unprotected rounding class
  typedef rounded_math<mpfr::Real> unprotected_rounding;
};

//------------------------------------------------------------

template<> class checking_base<mpfr::Real> {
public:
    static mpfr::Real pos_inf() {
        return mpfr::Infinity;
    }
    static mpfr::Real neg_inf() {
        return -mpfr::Infinity;
    }

    static mpfr::Real nan() {
        return mpfr::NaN;
    }
    static bool is_nan(const mpfr::Real& x) {
        return x.isNaN ();
    }

    static mpfr::Real empty_lower() {
        return mpfr::NaN;
    }
    static mpfr::Real empty_upper() {
        return mpfr::NaN;
    }

    static bool is_empty(const mpfr::Real& x, const mpfr::Real& y) {
        return x.isNaN () && y.isNaN ();
    }
};

namespace user {
    inline bool is_zero(const mpfr::Real& x) { return x.isZero (); }
    inline bool is_neg (const mpfr::Real& x) { return x.sign () < 0; }
    inline bool is_pos (const mpfr::Real& x) { return x.sign () > 0; }
}

namespace constants {
    template<> inline mpfr::Real pi_half_lower<mpfr::Real>() {
        return mpfr::Constant.pi (mpfr::roundTowardNegInfinity) / mpfr::Real(2);
    }
    template<> inline mpfr::Real pi_half_upper<mpfr::Real>() {
        return mpfr::Constant.pi (mpfr::roundTowardInfinity) / mpfr::Real(2);
    }
    template<> inline mpfr::Real pi_lower<mpfr::Real>() {
        return mpfr::Constant.pi (mpfr::roundTowardNegInfinity);
    }
    template<> inline mpfr::Real pi_upper<mpfr::Real>() {
        return mpfr::Constant.pi (mpfr::roundTowardInfinity);
    }
    template<> inline mpfr::Real pi_twice_lower<mpfr::Real>() {
        return mpfr::Constant.pi (mpfr::roundTowardNegInfinity) * mpfr::Real(2);
    }
    template<> inline mpfr::Real pi_twice_upper<mpfr::Real>() {
        return mpfr::Constant.pi (mpfr::roundTowardInfinity) * mpfr::Real(2);
    }
}

} // namespace interval_lib
} // namespace numeric
} // namespace boost

#endif    // MPFRCPP_EXTRA_BOOST_INTERVAL
