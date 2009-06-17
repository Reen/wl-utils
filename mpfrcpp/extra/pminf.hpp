#ifndef MPFRCPP_EXTRA_PMINF
#define MPFRCPP_EXTRA_PMINF

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
 * @file pminf.hpp
 * @date 2007-04-03
 * Functors rounding to +/- infinity.
 * OPTIONAL HEADER, INCLUDE ONLY IF NEEDED.
 */

namespace mpfr {

    extern AbsClass AbsMInf;
    extern AbsClass AbsPInf;

    extern AcosClass AcosMInf;
    extern AcosClass AcosPInf;

    extern AcoshClass AcoshMInf;
    extern AcoshClass AcoshPInf;

    extern AgmClass AgmMInf;
    extern AgmClass AgmPInf;

    extern AsinhClass AsinhMInf;
    extern AsinhClass AsinhPInf;

    extern AtanClass AtanMInf;
    extern AtanClass AtanPInf;

    extern AtanhClass AtanhMInf;
    extern AtanhClass AtanhPInf;

    extern CbrtClass CbrtMInf;
    extern CbrtClass CbrtPInf;

    extern ConstantClass ConstantMInf;
    extern ConstantClass ConstantPInf;

    extern CosClass CosMInf;
    extern CosClass CosPInf;

    extern CoshClass CoshMInf;
    extern CoshClass CoshPInf;

    extern CotClass CotMInf;
    extern CotClass CotPInf;

    extern CothClass CothMInf;
    extern CothClass CothPInf;

    extern CscClass CscMInf;
    extern CscClass CscPInf;

    extern CschClass CschMInf;
    extern CschClass CschPInf;

    extern DivClass DivMInf;
    extern DivClass DivPInf;

    extern EintClass EintMInf;
    extern EintClass EintPInf;

    extern ErfClass ErfMInf;
    extern ErfClass ErfPInf;

    extern ErfcClass ErfcMInf;
    extern ErfcClass ErfcPInf;

    extern ExpClass ExpMInf;
    extern ExpClass ExpPInf;

    extern Exp10Class Exp10MInf;
    extern Exp10Class Exp10PInf;

    extern Exp2Class Exp2MInf;
    extern Exp2Class Exp2PInf;

    extern Expm1Class Expm1MInf;
    extern Expm1Class Expm1PInf;

    extern FactorialClass FactorialMInf;
    extern FactorialClass FactorialPInf;

    extern FmaClass FmaMInf;
    extern FmaClass FmaPInf;

    extern FracClass FracMInf;
    extern FracClass FracPInf;

    extern GammaClass GammaMInf;
    extern GammaClass GammaPInf;

    extern HypotClass HypotMInf;
    extern HypotClass HypotPInf;

    extern LngammaClass LngammaMInf;
    extern LngammaClass LngammaPInf;

    extern LogClass LogMInf;
    extern LogClass LogPInf;

    extern Log10Class Log10MInf;
    extern Log10Class Log10PInf;

    extern Log1pClass Log1pMInf;
    extern Log1pClass Log1pPInf;

    extern Log2Class Log2MInf;
    extern Log2Class Log2PInf;

    extern MulClass MulMInf;
    extern MulClass MulPInf;

    extern NegClass NegMInf;
    extern NegClass NegPInf;

    extern PowClass PowMInf;
    extern PowClass PowPInf;

    extern RootClass RootMInf;
    extern RootClass RootPInf;

    extern SecClass SecMInf;
    extern SecClass SecPInf;

    extern SechClass SechMInf;
    extern SechClass SechPInf;

    extern SinClass SinMInf;
    extern SinClass SinPInf;

    extern SinCosClass SinCosMInf;
    extern SinCosClass SinCosPInf;

    extern SinhClass SinhMInf;
    extern SinhClass SinhPInf;

    extern SqrClass SqrMInf;
    extern SqrClass SqrPInf;

    extern SqrtClass SqrtMInf;
    extern SqrtClass SqrtPInf;

    extern SubClass SubMInf;
    extern SubClass SubPInf;

    extern TanClass TanMInf;
    extern TanClass TanPInf;

    extern TanhClass TanhMInf;
    extern TanhClass TanhPInf;

    extern ZetaClass ZetaMInf;
    extern ZetaClass ZetaPInf;

    //------------------------------------------------------------

    class ExtraNumericFunctions : public NumericFunctions {
        public:
            ExtraNumericFunctions () throw() {
                insert (AbsMInf);
                insert (AbsPInf);
                insert (AcosMInf);
                insert (AcosPInf);
                insert (AcoshMInf);
                insert (AcoshPInf);
                insert (AgmMInf);
                insert (AgmPInf);
                insert (AsinhMInf);
                insert (AsinhPInf);
                insert (AtanMInf);
                insert (AtanPInf);
                insert (AtanhMInf);
                insert (AtanhPInf);
                insert (CbrtMInf);
                insert (CbrtPInf);
                insert (ConstantMInf);
                insert (ConstantPInf);
                insert (CosMInf);
                insert (CosPInf);
                insert (CoshMInf);
                insert (CoshPInf);
                insert (CotMInf);
                insert (CotPInf);
                insert (CothMInf);
                insert (CothPInf);
                insert (CscMInf);
                insert (CscPInf);
                insert (CschMInf);
                insert (CschPInf);
                insert (DivMInf);
                insert (DivPInf);
                insert (EintMInf);
                insert (EintPInf);
                insert (ErfMInf);
                insert (ErfPInf);
                insert (ErfcMInf);
                insert (ErfcPInf);
                insert (ExpMInf);
                insert (ExpPInf);
                insert (Exp10MInf);
                insert (Exp10PInf);
                insert (Exp2MInf);
                insert (Exp2PInf);
                insert (Expm1MInf);
                insert (Expm1PInf);
                insert (FactorialMInf);
                insert (FactorialPInf);
                insert (FmaMInf);
                insert (FmaPInf);
                insert (FracMInf);
                insert (FracPInf);
                insert (GammaMInf);
                insert (GammaPInf);
                insert (HypotMInf);
                insert (HypotPInf);
                insert (LngammaMInf);
                insert (LngammaPInf);
                insert (LogMInf);
                insert (LogPInf);
                insert (Log10MInf);
                insert (Log10PInf);
                insert (Log1pMInf);
                insert (Log1pPInf);
                insert (Log2MInf);
                insert (Log2PInf);
                insert (MulMInf);
                insert (MulPInf);
                insert (NegMInf);
                insert (NegPInf);
                insert (PowMInf);
                insert (PowPInf);
                insert (RootMInf);
                insert (RootPInf);
                insert (SecMInf);
                insert (SecPInf);
                insert (SechMInf);
                insert (SechPInf);
                insert (SinMInf);
                insert (SinPInf);
                insert (SinCosMInf);
                insert (SinCosPInf);
                insert (SinhMInf);
                insert (SinhPInf);
                insert (SqrMInf);
                insert (SqrPInf);
                insert (SqrtMInf);
                insert (SqrtPInf);
                insert (SubMInf);
                insert (SubPInf);
                insert (TanMInf);
                insert (TanPInf);
                insert (TanhMInf);
                insert (TanhPInf);
                insert (ZetaMInf);
                insert (ZetaPInf);
            }
    };

    extern ExtraNumericFunctions ExtraFunctions;

}    // namespace mpfr

#endif    // MPFRCPP_EXTRA_PMINF
