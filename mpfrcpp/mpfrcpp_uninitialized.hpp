#ifndef MPFRCPP_UNINITIALIZED
#define MPFRCPP_UNINITIALIZED

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
 * @file mpfrcpp_uninitialized.hpp
 * @date 2007-08-045
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

//------------------------------------------------------------

/**
 * @name INCLUDED_BY_MPFRCPP
 * We define INCLUDED_BY_MPFRCPP macro and undefine it at the end of
 * this file to prevent including of internal headers by user.
 */

#define INCLUDED_BY_MPFRCPP

//------------------------------------------------------------

#include <mpfr.h>
#include <gmp.h>
#include <gmpxx.h>

//------------------------------------------------------------

#ifdef __GMP_PLUSPLUS__
    #define GMP_CPP_INTERFACE
#endif

//------------------------------------------------------------

/* MPFR 2.3.0 is not widely spreaded at this moment and there are
   only release candidate. */
#if (MPFR_VERSION >= MPFR_VERSION_NUM(2,3,0))
    #define HAVE_BESSEL_FUNCTIONS_SUPPORT
    #define HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT
    #define HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT
#endif

//------------------------------------------------------------

/* Don't use MPFRCPP_VERSION_ definitions unless you really need
   preprocessing. Use Version class from "core/version.hpp". */
#define MPFRCPP_VERSION_MAJOR 1
#define MPFRCPP_VERSION_MINOR 4
#define MPFRCPP_VERSION_PATCHLEVEL 2

//------------------------------------------------------------

#include "library/error.hpp"

#include "core/primitive_wrapper.hpp"
#include "core/base.hpp"
#include "core/exp.hpp"
#include "core/precision.hpp"
#include "core/random_state.hpp"
#include "core/round_mode.hpp"
#include "core/version.hpp"

#include "library/flags.hpp"
#include "library/global_parameters.hpp"

#include "real/real.hpp"
#include "real/arithmetic_operators.hpp"
#include "real/fits.hpp"
#include "real/to_string.hpp"
#include "real/stream.hpp"

#include "core/numeric_function.hpp"

#include "library/numeric_functions_global_parameters_binder.hpp"

#include "functions/basic_arithmetic.hpp"
#include "functions/constants.hpp"
#include "functions/exponential.hpp"
#include "functions/hyperbolic.hpp"
#include "functions/integer_related.hpp"
#include "functions/inverse_hyperbolic.hpp"
#include "functions/inverse_trigonometric.hpp"
#include "functions/logarithmic.hpp"
#include "functions/miscellaneous.hpp"
#include "functions/random.hpp"
#include "functions/special.hpp"
#include "functions/trigonometric.hpp"

//------------------------------------------------------------

#undef INCLUDED_BY_MPFRCPP

//------------------------------------------------------------

#endif    // MPFRCPP_UNINITIALIZED
