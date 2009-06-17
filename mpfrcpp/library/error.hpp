#ifndef MPFRCPP_LIBRARY_ERROR
#define MPFRCPP_LIBRARY_ERROR

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
 * @file error.hpp
 * @date 2007-04-08
 * Error classes based on the std::exception.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#include <stdexcept>

#define MPFRCPP_DEBUG

#ifdef MPFRCPP_DEBUG
#include <iostream>
#endif

namespace mpfr {

    //------------------------------------------------------------

    class ComparisonWithNaNError : public std::exception {
        public:
#ifdef MPFRCPP_DEBUG
            ComparisonWithNaNError () { std::cerr << what() << std::endl; }
#endif
            const char* what () const throw() {
                return "comparison with NaN operand(s)";
            }
    };

    //------------------------------------------------------------

    class ConversionDoesNotFitsError : public std::exception {
        public:
#ifdef MPFRCPP_DEBUG
            ConversionDoesNotFitsError () { std::cerr << what() << std::endl; }
#endif
            const char* what () const throw() {
                return "number does not fits in conversion target type";
            }
    };

    //------------------------------------------------------------

    class InvalidNumberStringError : public std::exception {
        public:
#ifdef MPFRCPP_DEBUG
            InvalidNumberStringError () { std::cerr << what() << std::endl; }
#endif
            const char* what () const throw() {
                return "invalid number string";
            }
    };

    //------------------------------------------------------------

    class StringOutputError : public std::exception {
        public:
#ifdef MPFRCPP_DEBUG
            StringOutputError () { std::cerr << what() << std::endl; }
#endif
            const char* what () const throw() {
                return "string output error";
            }
    };

    //------------------------------------------------------------

    class UnknownRoundModeError : public std::exception {
        public:
#ifdef MPFRCPP_DEBUG
            UnknownRoundModeError () { std::cerr << what() << std::endl; }
#endif
            const char* what () const throw() {
                return "unknown round mode";
            }
    };

    //------------------------------------------------------------

} // namespace mpfr

#endif    // MPFRCPP_LIBRARY_ERROR
