#ifndef MPFRCPP
#define MPFRCPP

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
 * @file mpfrcpp.hpp
 * @date 2007-04-09
 * THIS HEADER SHOULD BE INCLUDED TO USE MPFRCPP.
 */

//------------------------------------------------------------

/**
 * @name INCLUDED_BY_MPFRCPP
 * We define INCLUDED_BY_MPFRCPP macro and undefine it at the end of
 * this file to prevent including of internal headers by user.
 */

#include "mpfrcpp_uninitialized.hpp"

#define INCLUDED_BY_MPFRCPP
// Library Initialization
#include "initialization/initialization.hpp"

// Extra

/*
    #include "extra/beta.hpp"
    #include "extra/complex.hpp"
    #include "extra/fp_comparator.hpp"
    #include "extra/pminf.hpp"
    #include "extra/simple_functions.hpp"
    #include "extra/std_overloads.hpp"
*/

#undef INCLUDED_BY_MPFRCPP

#endif    // MPFRCPP
