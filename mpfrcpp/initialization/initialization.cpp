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
 * @file initialization.cpp
 * @date 2007-08-05
 * MPFRCPP library initialization.
 */

#include "../mpfrcpp.hpp"
#include <limits> // Inf / NaN

namespace mpfr {

    //------------------------------------------------------------

    // The initialization of mpfr::Parameters and mpfr::Real::params_
    // should be executed first.

    GlobalParameters Parameters = GlobalParameters();
    GlobalParameters& Real::params_ = Parameters;

    //------------------------------------------------------------

    const Version MPFRCPPVersion = Version (MPFRCPP_VERSION_MAJOR,
                                            MPFRCPP_VERSION_MINOR,
                                            MPFRCPP_VERSION_PATCHLEVEL);

    const Version MPFRVersion = Version (MPFR_VERSION_MAJOR,
                                         MPFR_VERSION_MINOR,
                                         MPFR_VERSION_PATCHLEVEL);

    //------------------------------------------------------------

    /**
     * Basic arithmetic functions
     */

    NegClass Neg = NegClass();
    AddClass Add = AddClass();
    SubClass Sub = SubClass();
    MulClass Mul = MulClass();
    DivClass Div = DivClass();
    AbsClass Abs = AbsClass();
    SqrtClass Sqrt = SqrtClass();
    CbrtClass Cbrt = CbrtClass();
    RootClass Root = RootClass();
    SqrClass Sqr = SqrClass();
    PowClass Pow = PowClass();

    //------------------------------------------------------------

    /**
     * Exponential functions
     */

    ExpClass Exp = ExpClass();
    Expm1Class Expm1 = Expm1Class();
    Exp10Class Exp10 = Exp10Class();
    Exp2Class Exp2 = Exp2Class();

    //------------------------------------------------------------

    /**
     * Hyperbolic functions
     */

    SinhClass Sinh = SinhClass();
    CoshClass Cosh = CoshClass();
    SechClass Sech = SechClass();
    CschClass Csch = CschClass();
    TanhClass Tanh = TanhClass();
    CothClass Coth = CothClass();

    //------------------------------------------------------------

    /**
     * Integer related functions
     */

    CeilClass Ceil = CeilClass();
    FloorClass Floor = FloorClass();

#ifdef HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT
    RemainderClass Remainder = RemainderClass();
#endif    // HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT

    RoundClass Round = RoundClass();
    TruncClass Trunc = TruncClass();
    FracClass Frac = FracClass();

    //------------------------------------------------------------

    /**
     * Inverse hyperbolic functions
     */

    AsinhClass Asinh = AsinhClass();
    AcoshClass Acosh = AcoshClass();
    AtanhClass Atanh = AtanhClass();

    //------------------------------------------------------------

    /**
     * Inverse trigonometric functions
     */

    AsinClass Asin = AsinClass();
    AcosClass Acos = AcosClass();
    AtanClass Atan = AtanClass();
    Atan2Class Atan2 = Atan2Class();

    //------------------------------------------------------------

    /**
     * Miscellaneous fuctions
     */

    FmaClass Fma = FmaClass();

#ifdef HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT
    FmsClass Fms = FmsClass();
#endif    // HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT

    AgmClass Agm = AgmClass();
    HypotClass Hypot = HypotClass();
    FactorialClass Factorial = FactorialClass();

    //------------------------------------------------------------

    /**
     * Special fuctions
     */

#ifdef HAVE_BESSEL_FUNCTIONS_SUPPORT
    BesselJ0Class BesselJ0 = BesselJ0Class();
    BesselJ1Class BesselJ1 = BesselJ1Class();
    BesselJnClass BesselJn = BesselJnClass();
    BesselY0Class BesselY0 = BesselY0Class();
    BesselY1Class BesselY1 = BesselY1Class();
    BesselYnClass BesselYn = BesselYnClass();
#endif    // HAVE_BESSEL_FUNCTIONS_SUPPORT

    ErfClass Erf = ErfClass();
    ErfcClass Erfc = ErfcClass();
    EintClass Eint = EintClass();
    GammaClass Gamma = GammaClass();
    LngammaClass Lngamma = LngammaClass();
    ZetaClass Zeta = ZetaClass();

    //------------------------------------------------------------

    /**
     * Trigonometric functions
     */

    SinClass Sin = SinClass();
    SinCosClass SinCos = SinCosClass();
    CosClass Cos = CosClass();
    SecClass Sec = SecClass();
    CscClass Csc = CscClass();
    TanClass Tan = TanClass();
    CotClass Cot = CotClass();

    //------------------------------------------------------------

    /**
     * Logarithmic functions
     */

    LogClass Log = LogClass();
    Log10Class Log10 = Log10Class();
    Log2Class Log2 = Log2Class();
    Log1pClass Log1p = Log1pClass();

    //------------------------------------------------------------

    /**
     * Numeric constants
     */

    ConstantClass Constant = ConstantClass();

    //------------------------------------------------------------

    NumericFunctions Functions = DefaultNumericFunctions ();
    NumericFunctionsGlobalParametersBinder Library = NumericFunctionsGlobalParametersBinder (Functions, Parameters);

    //------------------------------------------------------------

    const RoundMode roundTowardZero = RoundMode (std::round_toward_zero);
    const RoundMode roundToNearest = RoundMode (std::round_to_nearest);
    const RoundMode roundTowardInfinity = RoundMode (std::round_toward_infinity);
    const RoundMode roundTowardNegInfinity = RoundMode (std::round_toward_neg_infinity);

    //------------------------------------------------------------

    Real Infinity = Real (std::numeric_limits<double>::infinity());
    Real NaN = Real (std::numeric_limits<double>::quiet_NaN());

    //------------------------------------------------------------

} // namespace mpfr
