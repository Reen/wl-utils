#ifndef MPFRCPP_INITIALIZATION_INITIALIZATION
#define MPFRCPP_INITIALIZATION_INITIALIZATION

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
 * @file initialization.hpp
 * @date 2007-03-23
 * MPFRCPP library initialization.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

#include <limits> // Inf / NaN

namespace mpfr {

    //------------------------------------------------------------

    extern const Version MPFRCPPVersion;
    extern const Version MPFRVersion;

    //------------------------------------------------------------

    /**
     * Basic arithmetic functions
     */

    extern NegClass Neg;
    extern AddClass Add;
    extern SubClass Sub;
    extern MulClass Mul;
    extern DivClass Div;
    extern AbsClass Abs;
    extern SqrtClass Sqrt;
    extern CbrtClass Cbrt;
    extern RootClass Root;
    extern SqrClass Sqr;
    extern PowClass Pow;

    //------------------------------------------------------------

    /**
     * Exponential functions
     */

    extern ExpClass Exp;
    extern Expm1Class Expm1;
    extern Exp10Class Exp10;
    extern Exp2Class Exp2;

    //------------------------------------------------------------

    /**
     * Hyperbolic functions
     */

    extern SinhClass Sinh;
    extern CoshClass Cosh;
    extern SechClass Sech;
    extern CschClass Csch;
    extern TanhClass Tanh;
    extern CothClass Coth;

    //------------------------------------------------------------

    /**
     * Integer related functions
     */

    extern CeilClass Ceil;
    extern FloorClass Floor;

#ifdef HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT
    extern RemainderClass Remainder;
#endif   // HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT

    extern RoundClass Round;
    extern TruncClass Trunc;
    extern FracClass Frac;

    //------------------------------------------------------------

    /**
     * Inverse hyperbolic functions
     */

    extern AsinhClass Asinh;
    extern AcoshClass Acosh;
    extern AtanhClass Atanh;

    //------------------------------------------------------------

    /**
     * Inverse trigonometric functions
     */

    extern AsinClass Asin;
    extern AcosClass Acos;
    extern AtanClass Atan;
    extern Atan2Class Atan2;

    //------------------------------------------------------------

    /**
     * Miscellaneous fuctions
     */

    extern FmaClass Fma;
#ifdef HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT
    extern FmsClass Fms;
#endif   // HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT
    extern AgmClass Agm;
    extern HypotClass Hypot;
    extern FactorialClass Factorial;

    //------------------------------------------------------------

    /**
     * Special fuctions
     */

#ifdef HAVE_BESSEL_FUNCTIONS_SUPPORT
    extern BesselJ0Class BesselJ0;
    extern BesselJ1Class BesselJ1;
    extern BesselJnClass BesselJn;
    extern BesselY0Class BesselY0;
    extern BesselY1Class BesselY1;
    extern BesselYnClass BesselYn;
#endif    // HAVE_BESSEL_FUNCTIONS_SUPPORT

    extern ErfClass Erf;
    extern ErfcClass Erfc;
    extern EintClass Eint;
    extern GammaClass Gamma;
    extern LngammaClass Lngamma;
    extern ZetaClass Zeta;

    //------------------------------------------------------------

    /**
     * Trigonometric functions
     */

    extern SinClass Sin;
    extern SinCosClass SinCos;
    extern CosClass Cos;
    extern SecClass Sec;
    extern CscClass Csc;
    extern TanClass Tan;
    extern CotClass Cot;

    //------------------------------------------------------------

    /**
     * Logarithmic functions
     */

    extern LogClass Log;
    extern Log10Class Log10;
    extern Log2Class Log2;
    extern Log1pClass Log1p;

    //------------------------------------------------------------

    /**
     * Numeric constants
     */

    extern ConstantClass Constant;

    //------------------------------------------------------------

    /**
     * Set of default functions.
     */

    class DefaultNumericFunctions : public NumericFunctions {
        public:
            DefaultNumericFunctions () throw() {
                insert (Abs);
                insert (Acos);
                insert (Acosh);
                insert (Add);
                insert (Agm);
                insert (Asin);
                insert (Asinh);
                insert (Atan);
                insert (Atan2);
                insert (Atanh);

#ifdef HAVE_BESSEL_FUNCTIONS_SUPPORT
                insert (BesselJ0);
                insert (BesselJ1);
                insert (BesselJn);
                insert (BesselY0);
                insert (BesselY1);
                insert (BesselYn);
#endif    // HAVE_BESSEL_FUNCTIONS_SUPPORT

                insert (Cbrt);
                insert (Ceil);
                insert (Constant);
                insert (Cos);
                insert (Cosh);
                insert (Cot);
                insert (Coth);
                insert (Csc);
                insert (Csch);
                insert (Div);
                insert (Eint);
                insert (Erf);
                insert (Erfc);
                insert (Exp);
                insert (Exp10);
                insert (Exp2);
                insert (Expm1);
                insert (Factorial);
                insert (Fma);

#ifdef HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT
                insert (Fms);
#endif    // HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT

                insert (Floor);
                insert (Frac);
                insert (Gamma);
                insert (Hypot);
                insert (Lngamma);
                insert (Log);
                insert (Log10);
                insert (Log1p);
                insert (Log2);
                insert (Mul);
                insert (Neg);
                insert (Pow);

#ifdef HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT
                insert (Remainder);
#endif    // HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT

                insert (Root);
                insert (Round);
                insert (Sec);
                insert (Sech);
                insert (Sin);
                insert (SinCos);
                insert (Sinh);
                insert (Sqr);
                insert (Sqrt);
                insert (Sub);
                insert (Tan);
                insert (Tanh);
                insert (Trunc);
                insert (Zeta);
            }
    };

    extern NumericFunctions Functions;
    extern GlobalParameters Parameters;
    extern NumericFunctionsGlobalParametersBinder Library;

    //------------------------------------------------------------

    /**
     * Avoid constructing RoundMode from std::round_mode.
     * Use pre-defined objects:
     *     roundTowardZero
     *     roundToNearest
     *     roundTowardInfinity
     *     roundTowardNegInfinity
     */

    extern const RoundMode roundTowardZero;
    extern const RoundMode roundToNearest;
    extern const RoundMode roundTowardInfinity;
    extern const RoundMode roundTowardNegInfinity;

    //------------------------------------------------------------

    extern Real Infinity;
    extern Real NaN;

    //------------------------------------------------------------

} // namespace mpfr

// #include "initialization.cpp"
#endif    // MPFRCPP_INITIALIZATION_INITIALIZATION
