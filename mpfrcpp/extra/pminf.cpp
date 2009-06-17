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
 * @file pminf.cpp
 * @date 2007-05-07
 * Functors rounding to +/- infinity.
 */

#include "../mpfrcpp.hpp"
#include "pminf.hpp"

namespace mpfr {

    AbsClass AbsMInf = AbsClass (roundTowardNegInfinity);
    AbsClass AbsPInf = AbsClass (roundTowardInfinity);

    AcosClass AcosMInf = AcosClass (roundTowardNegInfinity);
    AcosClass AcosPInf = AcosClass (roundTowardInfinity);

    AcoshClass AcoshMInf = AcoshClass (roundTowardNegInfinity);
    AcoshClass AcoshPInf = AcoshClass (roundTowardInfinity);

    AgmClass AgmMInf = AgmClass (roundTowardNegInfinity);
    AgmClass AgmPInf = AgmClass (roundTowardInfinity);

    AsinhClass AsinhMInf = AsinhClass (roundTowardNegInfinity);
    AsinhClass AsinhPInf = AsinhClass (roundTowardInfinity);

    AtanClass AtanMInf = AtanClass (roundTowardNegInfinity);
    AtanClass AtanPInf = AtanClass (roundTowardInfinity);

    AtanhClass AtanhMInf = AtanhClass (roundTowardNegInfinity);
    AtanhClass AtanhPInf = AtanhClass (roundTowardInfinity);

#ifdef HAVE_BESSEL_FUNCTIONS_SUPPORT
    BesselJ0Class BesselJ0MInf = BesselJ0Class (roundTowardNegInfinity);
    BesselJ0Class BesselJ0PInf = BesselJ0Class (roundTowardInfinity);

    BesselJ1Class BesselJ1MInf = BesselJ1Class (roundTowardNegInfinity);
    BesselJ1Class BesselJ1PInf = BesselJ1Class (roundTowardInfinity);

    BesselJnClass BesselJnMInf = BesselJnClass (roundTowardNegInfinity);
    BesselJnClass BesselJnPInf = BesselJnClass (roundTowardInfinity);

    BesselY0Class BesselY0MInf = BesselY0Class (roundTowardNegInfinity);
    BesselY0Class BesselY0PInf = BesselY0Class (roundTowardInfinity);

    BesselY1Class BesselY1MInf = BesselY1Class (roundTowardNegInfinity);
    BesselY1Class BesselY1PInf = BesselY1Class (roundTowardInfinity);

    BesselYnClass BesselYnMInf = BesselYnClass (roundTowardNegInfinity);
    BesselYnClass BesselYnPInf = BesselYnClass (roundTowardInfinity);
#endif    // HAVE_BESSEL_FUNCTIONS_SUPPORT

    CbrtClass CbrtMInf = CbrtClass (roundTowardNegInfinity);
    CbrtClass CbrtPInf = CbrtClass (roundTowardInfinity);

    ConstantClass ConstantMInf = ConstantClass (roundTowardNegInfinity);
    ConstantClass ConstantPInf = ConstantClass (roundTowardInfinity);

    CosClass CosMInf = CosClass (roundTowardNegInfinity);
    CosClass CosPInf = CosClass (roundTowardInfinity);

    CoshClass CoshMInf = CoshClass (roundTowardNegInfinity);
    CoshClass CoshPInf = CoshClass (roundTowardInfinity);

    CotClass CotMInf = CotClass (roundTowardNegInfinity);
    CotClass CotPInf = CotClass (roundTowardInfinity);

    CothClass CothMInf = CothClass (roundTowardNegInfinity);
    CothClass CothPInf = CothClass (roundTowardInfinity);

    CscClass CscMInf = CscClass (roundTowardNegInfinity);
    CscClass CscPInf = CscClass (roundTowardInfinity);

    CschClass CschMInf = CschClass (roundTowardNegInfinity);
    CschClass CschPInf = CschClass (roundTowardInfinity);

    DivClass DivMInf = DivClass (roundTowardNegInfinity);
    DivClass DivPInf = DivClass (roundTowardInfinity);

    EintClass EintMInf = EintClass (roundTowardNegInfinity);
    EintClass EintPInf = EintClass (roundTowardInfinity);

    ErfClass ErfMInf = ErfClass (roundTowardNegInfinity);
    ErfClass ErfPInf = ErfClass (roundTowardInfinity);

    ErfcClass ErfcMInf = ErfcClass (roundTowardNegInfinity);
    ErfcClass ErfcPInf = ErfcClass (roundTowardInfinity);

    ExpClass ExpMInf = ExpClass (roundTowardNegInfinity);
    ExpClass ExpPInf = ExpClass (roundTowardInfinity);

    Exp10Class Exp10MInf = Exp10Class (roundTowardNegInfinity);
    Exp10Class Exp10PInf = Exp10Class (roundTowardInfinity);

    Exp2Class Exp2MInf = Exp2Class (roundTowardNegInfinity);
    Exp2Class Exp2PInf = Exp2Class (roundTowardInfinity);

    Expm1Class Expm1MInf = Expm1Class (roundTowardNegInfinity);
    Expm1Class Expm1PInf = Expm1Class (roundTowardInfinity);

    FactorialClass FactorialMInf = FactorialClass (roundTowardNegInfinity);
    FactorialClass FactorialPInf = FactorialClass (roundTowardInfinity);

    FmaClass FmaMInf = FmaClass (roundTowardNegInfinity);
    FmaClass FmaPInf = FmaClass (roundTowardInfinity);

#ifdef HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT
    FmsClass FmsMInf = FmsClass (roundTowardNegInfinity);
    FmsClass FmsPInf = FmsClass (roundTowardInfinity);
#endif   // HAVE_FAST_MULTIPLICATION_SUBTRACTION_SUPPORT

    FracClass FracMInf = FracClass (roundTowardNegInfinity);
    FracClass FracPInf = FracClass (roundTowardInfinity);

    GammaClass GammaMInf = GammaClass (roundTowardNegInfinity);
    GammaClass GammaPInf = GammaClass (roundTowardInfinity);

    HypotClass HypotMInf = HypotClass (roundTowardNegInfinity);
    HypotClass HypotPInf = HypotClass (roundTowardInfinity);

    LngammaClass LngammaMInf = LngammaClass (roundTowardNegInfinity);
    LngammaClass LngammaPInf = LngammaClass (roundTowardInfinity);

    LogClass LogMInf = LogClass (roundTowardNegInfinity);
    LogClass LogPInf = LogClass (roundTowardInfinity);

    Log10Class Log10MInf = Log10Class (roundTowardNegInfinity);
    Log10Class Log10PInf = Log10Class (roundTowardInfinity);

    Log1pClass Log1pMInf = Log1pClass (roundTowardNegInfinity);
    Log1pClass Log1pPInf = Log1pClass (roundTowardInfinity);

    Log2Class Log2MInf = Log2Class (roundTowardNegInfinity);
    Log2Class Log2PInf = Log2Class (roundTowardInfinity);

    MulClass MulMInf = MulClass (roundTowardNegInfinity);
    MulClass MulPInf = MulClass (roundTowardInfinity);

    NegClass NegMInf = NegClass (roundTowardNegInfinity);
    NegClass NegPInf = NegClass (roundTowardInfinity);

    PowClass PowMInf = PowClass (roundTowardNegInfinity);
    PowClass PowPInf = PowClass (roundTowardInfinity);

#ifdef HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT
    RemainderClass RemainderMInf = RemainderClass (roundTowardNegInfinity);
    RemainderClass RemainderPInf = RemainderClass (roundTowardInfinity);
#endif    // HAVE_DIVISION_REMAINDER_FUNCTION_SUPPORT

    RootClass RootMInf = RootClass (roundTowardNegInfinity);
    RootClass RootPInf = RootClass (roundTowardInfinity);

    SecClass SecMInf = SecClass (roundTowardNegInfinity);
    SecClass SecPInf = SecClass (roundTowardInfinity);

    SechClass SechMInf = SechClass (roundTowardNegInfinity);
    SechClass SechPInf = SechClass (roundTowardInfinity);

    SinClass SinMInf = SinClass (roundTowardNegInfinity);
    SinClass SinPInf = SinClass (roundTowardInfinity);

    SinCosClass SinCosMInf = SinCosClass (roundTowardNegInfinity);
    SinCosClass SinCosPInf = SinCosClass (roundTowardInfinity);

    SinhClass SinhMInf = SinhClass (roundTowardNegInfinity);
    SinhClass SinhPInf = SinhClass (roundTowardInfinity);

    SqrClass SqrMInf = SqrClass (roundTowardNegInfinity);
    SqrClass SqrPInf = SqrClass (roundTowardInfinity);

    SqrtClass SqrtMInf = SqrtClass (roundTowardNegInfinity);
    SqrtClass SqrtPInf = SqrtClass (roundTowardInfinity);

    SubClass SubMInf = SubClass (roundTowardNegInfinity);
    SubClass SubPInf = SubClass (roundTowardInfinity);

    TanClass TanMInf = TanClass (roundTowardNegInfinity);
    TanClass TanPInf = TanClass (roundTowardInfinity);

    TanhClass TanhMInf = TanhClass (roundTowardNegInfinity);
    TanhClass TanhPInf = TanhClass (roundTowardInfinity);

    ZetaClass ZetaMInf = ZetaClass (roundTowardNegInfinity);
    ZetaClass ZetaPInf = ZetaClass (roundTowardInfinity);

    //------------------------------------------------------------

    ExtraNumericFunctions ExtraFunctions = ExtraNumericFunctions ();

}    // namespace mpfr
