#ifndef MPFRCPP_REAL_REAL
#define MPFRCPP_REAL_REAL

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
 * @file real.hpp
 * @date 2007-03-30
 * mpfr::Real definition.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

    class Real {

            mpfr_t x_;    // Number
            static GlobalParameters& params_;

        public:

            /**
             * Constructors
             */

            Real (const Precision& pr = getParameters().getDefaultPrecision()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                if (getParameters().isInitializedByZero())
                    mpfr_set_ui(getMpfrT(), 0, getParameters().getDefaultRoundMode().getMpfrRndT());
                /* set number to NaN else */
            }

            Real (const Real& x) throw() {
                mpfr_init2(getMpfrT(), x.getPrecision().getMpfrPrecT());
                mpfr_set (getMpfrT(), x.getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
            }

            Real (const Real& x, const Precision& pr, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set (getMpfrT(), x.getMpfrT(), rm.getMpfrRndT ());
            }

            Real (const Real& x, const Precision& pr) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set (getMpfrT(), x.getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
            }

            Real (const Real& x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set (getMpfrT(), x.getMpfrT(), rm.getMpfrRndT ());
            }

            Real (const mpfr_t& x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const mpfr_t& x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const unsigned long int x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_ui (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const unsigned long int x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_ui (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const unsigned int x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_ui (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const unsigned int x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_ui (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const unsigned short int x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_ui (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const unsigned short int x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_ui (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const long int x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_si (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const long int x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_si (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const int x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_si (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const int x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_si (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const short int x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_si (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const short int x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_si (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const double& x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_d (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const double& x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_d (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const long double& x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_ld (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const long double& x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_ld (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const mpz_t& x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_z (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const mpz_t& x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_z (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const mpq_t& x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_q (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const mpq_t& x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_q (getMpfrT(), x, rm.getMpfrRndT ());
            }

            Real (const mpf_t& x, const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), mpf_get_prec(x));
                mpfr_set_f (getMpfrT(), x, rm.getMpfrRndT ());
            }
    
            Real (const std::string& x, const Base& base, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw (InvalidNumberStringError) {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                int c = mpfr_set_str(getMpfrT(), x.c_str(), base.getInt(), rm.getMpfrRndT ());
                if (c == -1) throw InvalidNumberStringError();
            }
            Real (const std::string& x, const Base& base, const RoundMode& rm) throw (InvalidNumberStringError) {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                int c = mpfr_set_str (getMpfrT(), x.c_str(), base.getInt(), rm.getMpfrRndT ());
                if (c == -1) throw InvalidNumberStringError();
            }
            Real (const std::string& x, const Precision& pr = getParameters().getDefaultPrecision()) throw (InvalidNumberStringError) {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                int c = mpfr_set_str(getMpfrT(), x.c_str(), getParameters().getDefaultBase().getInt(), getParameters().getDefaultRoundMode().getMpfrRndT ());
                if (c == -1) throw InvalidNumberStringError();
            }
            Real (const std::string& x, const RoundMode& rm) throw (InvalidNumberStringError) {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                int c = mpfr_set_str(getMpfrT(), x.c_str(), getParameters().getDefaultBase().getInt(), rm.getMpfrRndT ());
                if (c == -1) throw InvalidNumberStringError();
            }

#ifdef GMP_CPP_INTERFACE
            Real (const mpz_class& x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_z (getMpfrT(), x.get_mpz_t(), rm.getMpfrRndT ());
            }
            Real (const mpz_class& x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_z (getMpfrT(), x.get_mpz_t(), rm.getMpfrRndT ());
            }

            Real (const mpq_class& x, const Precision& pr = getParameters().getDefaultPrecision(), const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), pr.getMpfrPrecT());
                mpfr_set_q(getMpfrT(), x.get_mpq_t(), rm.getMpfrRndT ());
            }
            Real (const mpq_class& x, const RoundMode& rm) throw() {
                mpfr_init2(getMpfrT(), getParameters().getDefaultPrecision().getMpfrPrecT());
                mpfr_set_q (getMpfrT(), x.get_mpq_t(), rm.getMpfrRndT ());
            }

            Real (const mpf_class& x, const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_init2(getMpfrT(), x.get_prec());
                mpfr_set_f (getMpfrT(), x.get_mpf_t(), rm.getMpfrRndT ());
            }
#endif    // GMP_CPP_INTERFACE

            ~Real() throw() {
                mpfr_clear(getMpfrT());
            }

            //------------------------------------------------------------

            /**
             * Static methods
             */

            static GlobalParameters& getParameters() throw() {
                return params_;
            }
            static void setParameters (GlobalParameters& params) throw() {
                params_ = params;
            }
            static Real epsilon (const Precision& pr = getParameters().getDefaultPrecision()) throw() {
                Real e (pr);
                mpfr_set_ui_2exp (e.getMpfrT(), 1, 1 - pr.getMpfrPrecT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return e;
            }

            //------------------------------------------------------------

            /**
             * Non-static methods
             */

            mpfr_t& getMpfrT () throw() {
                return x_;
            }
            const mpfr_t& getMpfrT () const throw() {
                return x_;
            }

            int checkRange () throw() {
                int r = 0;
                mpfr_check_range (getMpfrT(), r, getParameters().getDefaultRoundMode().getMpfrRndT());
                return r;
            }

            Exponent getExponent () const throw() {
                return Exponent (mpfr_get_exp(getMpfrT()));
            }

            Precision getPrecision() const throw() {
                return Precision(mpfr_get_prec(getMpfrT()));
            }

            template <typename T> bool isFits () const throw();

            bool isInfinity () const throw() {
                return mpfr_inf_p (getMpfrT ()) != 0;
            }

            bool isInteger () const throw() {
                return mpfr_integer_p (getMpfrT ()) != 0;
            }

            bool isNaN () const throw() {
                return mpfr_nan_p (getMpfrT ()) != 0;
            }

            bool isNumber () const throw() {
                return mpfr_number_p (getMpfrT ()) != 0;
            }

            bool isZero () const throw() {
                return mpfr_zero_p (getMpfrT ()) != 0;
            }

            void round (const Precision& pr, const RoundMode& rm) throw() {
                mpfr_prec_round (getMpfrT (), pr.getMpfrPrecT(), rm.getMpfrRndT());
            }
            void round (const Precision& pr) throw() { // with default round mode
                round (pr, getParameters().getDefaultRoundMode());
            }
            void setExponent (const Exponent& e) throw() {
                mpfr_set_exp(getMpfrT(), e.getMpExpT());
            }
            void setPrecision(const Precision& pr) throw() {
                mpfr_set_prec(getMpfrT(), pr.getMpfrPrecT());
            }
            void setPrecision(mpfr_prec_t pr) throw() {
                mpfr_set_prec(getMpfrT(), pr);
            }
            void setToInfinity (const int sign) throw() {
                mpfr_set_inf(getMpfrT(), sign);
            }
            void setToNaN () throw() {
                mpfr_set_nan(getMpfrT());
            }
            int sign () const throw(ComparisonWithNaNError) {
                if (isNaN ()) throw ComparisonWithNaNError();
                int n = mpfr_sgn(getMpfrT ());
                if (n > 0)      return 1;
                else if (n < 0) return -1;
                else            return 0;
            }
            void subnormalize (const Precision& pr, const RoundMode& rm = getParameters().getDefaultRoundMode()) throw() {
                mpfr_subnormalize (getMpfrT(), pr.getMpfrPrecT(), rm.getMpfrRndT());
            }

            /**
             * toString
             *     p is precision FOR GIVEN BASE.
             *     p = -1 means real precision.
             *     now p = 0 is equivalent to p = -1, but reserved to denote precision 0
             *     in further versions.
             */

            inline std::string toString () const throw(StringOutputError);

            inline std::string toString (int p, const RoundMode&, const Base&) const throw(StringOutputError);

            inline std::string toString (int p) const throw(StringOutputError);

            inline std::string toString (const RoundMode&) const throw(StringOutputError);

            inline std::string toString (const Base&) const throw(StringOutputError);

            inline std::string toString (int p, const RoundMode&) const throw(StringOutputError);

            inline std::string toString (int p, const Base&) const throw(StringOutputError);

            inline std::string toString (const RoundMode&, const Base&) const throw(StringOutputError);

            //------------------------------------------------------------

            /**
             * Assignment
             */

            Real& operator= (const Real& y) throw() {
                if (getPrecision() < y.getPrecision())
                    setPrecision(y.getPrecision());
                mpfr_set (getMpfrT(), y.getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }
            Real& operator= (const mpfr_t& x) throw() {
                mpfr_set (getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const unsigned long int y) throw() {
                mpfr_set_ui (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const unsigned int y) throw() {
                mpfr_set_ui (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const unsigned short int y) throw() {
                mpfr_set_ui (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const long int y) throw() {
                mpfr_set_si (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const int y) throw() {
                mpfr_set_si (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const short int y) throw() {
                mpfr_set_si (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const double& y) throw() {
                mpfr_set_d (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const long double& y) throw() {
                mpfr_set_ld (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const mpz_t& y) throw() {
                mpfr_set_z (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const mpq_t& y) throw() {
                mpfr_set_q (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const mpf_t& y) throw() {
                if (getPrecision() < mpf_get_prec(y))
                    setPrecision(mpf_get_prec(y));
                mpfr_set_f (getMpfrT(), y, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

#ifdef GMP_CPP_INTERFACE
            Real& operator= (const mpz_class& y) throw() {
                mpfr_set_z (getMpfrT(), y.get_mpz_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const mpq_class& y) throw() {
                mpfr_set_q (getMpfrT(), y.get_mpq_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const mpf_class& y) throw() {
                if (getPrecision() < Precision(y.get_prec()))
                    setPrecision(Precision(y.get_prec()));
                mpfr_set_f (getMpfrT(), y.get_mpf_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }
#endif    // GMP_CPP_INTERFACE

            Real& operator= (const std::string& s) throw() {
                mpfr_set_str(getMpfrT(), s.c_str(), 0, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            Real& operator= (const bool y) throw() {
                mpfr_set_ui (getMpfrT(), static_cast<int>(y), getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            //------------------------------------------------------------

            /**
             * Conversion
             */

            operator double () const throw (ConversionDoesNotFitsError)  {
                if (isFits<double>())
                    return mpfr_get_d (getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                else
                    throw ConversionDoesNotFitsError ();
            }
            operator long int () const throw (ConversionDoesNotFitsError) {
                if (isFits<long int>())
                    return mpfr_get_si(getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                else
                    throw ConversionDoesNotFitsError();
            }
            operator int () const throw(ConversionDoesNotFitsError) {
                if (isFits<int>())
                    return mpfr_get_si(getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                else
                    throw ConversionDoesNotFitsError();
            }
            operator short int () const throw (ConversionDoesNotFitsError) {
                if (isFits<short int>())
                    return mpfr_get_si(getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                else
                    throw ConversionDoesNotFitsError();
            }
            operator long double () const throw (ConversionDoesNotFitsError) {
                if (isFits<long double>())
                    return mpfr_get_ld (getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                else
                    throw ConversionDoesNotFitsError();
            }

#ifdef GMP_CPP_INTERFACE
            operator mpz_class () const throw() {
                mpz_t x;
                mpfr_get_z (x, getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return mpz_class (x);
            }
            operator mpf_class () const throw() {
                mpf_t x;
                mpfr_get_f (x, getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return mpf_class (x);
            }
#endif

            operator std::string() const throw (StringOutputError) {
                return toString();
            }
            operator unsigned long int() const throw (ConversionDoesNotFitsError) {
                if (isFits<unsigned long int>())
                    return mpfr_get_ui(getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                else
                    throw ConversionDoesNotFitsError();
            }
            operator unsigned int() const throw (ConversionDoesNotFitsError) {
                if (isFits<unsigned int>())
                    return mpfr_get_ui (getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());    
                else
                    throw ConversionDoesNotFitsError();
            }
            operator unsigned short int() const throw (ConversionDoesNotFitsError) {
                if (isFits<unsigned short int>())
                    return mpfr_get_ui(getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                else
                    throw ConversionDoesNotFitsError();
            }

            //------------------------------------------------------------

            /**
             * Arithmetic operators
             */

            Real operator- () const throw() {
                Real y (getPrecision());
                mpfr_neg (y.getMpfrT(), getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator+ () const throw() {
                return *this;
            }

            Real operator+ (const Real &x) const throw() {
                Real y (std::max(getPrecision(), x.getPrecision()));
                mpfr_add (y.getMpfrT(), getMpfrT(), x.getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator+ (const unsigned long int &x) const throw() {
                Real y (getPrecision());
                mpfr_add_ui (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator+ (const unsigned int &x) const throw() {
                return * this + static_cast<unsigned long int>(x);
            }
            Real operator+ (const unsigned short int &x) const throw() {
                return * this + static_cast<unsigned long int>(x);
            }
            Real operator+ (const long int &x) const throw() {
                Real y (getPrecision());
                mpfr_add_si (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator+ (const int &x) const throw() {
                return * this + static_cast<long int>(x);
            }
            Real operator+ (const short int &x) const throw() {
                return * this + static_cast<long int>(x);
            }
            Real operator+ (const mpz_t &x) const throw() {
                Real y (getPrecision());
                mpfr_add_z (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator+ (const mpq_t &x) const throw() {
                Real y (getPrecision());
                mpfr_add_q (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
#ifdef GMP_CPP_INTERFACE
            Real operator+ (const mpz_class& x) const throw() {
                Real y (getPrecision());
                mpfr_add_z (y.getMpfrT(), getMpfrT(), x.get_mpz_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator+ (const mpq_class& x) const throw() {
                Real y (getPrecision());
                mpfr_add_q (y.getMpfrT(), getMpfrT(), x.get_mpq_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
#endif

            Real operator- (const Real &x) const throw() {
                Real y (std::max(getPrecision(), x.getPrecision()));
                mpfr_sub (y.getMpfrT(), getMpfrT(), x.getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator- (const unsigned long int &x) const throw() {
                Real y (getPrecision());
                mpfr_sub_ui (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator- (const unsigned int &x) const throw() {
                return * this - static_cast<unsigned long int>(x);
            }
            Real operator- (const unsigned short int &x) const throw() {
                return * this - static_cast<unsigned long int>(x);
            }
            Real operator- (const long int &x) const throw() {
                Real y (getPrecision());
                mpfr_sub_si (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator- (const int &x) const throw() {
                return * this - static_cast<long int>(x);
            }
            Real operator- (const short int &x) const throw() {
                return * this - static_cast<long int>(x);
            }
            Real operator- (const mpz_t &x) const throw() {
                Real y (getPrecision());
                mpfr_sub_z (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator- (const mpq_t& x) const throw() {
                Real y (getPrecision());
                mpfr_sub_q (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
#ifdef GMP_CPP_INTERFACE
            Real operator- (const mpz_class& x) const throw() {
                Real y (getPrecision());
                mpfr_sub_z (y.getMpfrT(), getMpfrT(), x.get_mpz_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator- (const mpq_class& x) const throw() {
                Real y (getPrecision());
                mpfr_sub_q (y.getMpfrT(), getMpfrT(), x.get_mpq_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
#endif

            Real operator* (const Real &x) const throw() {
                Real y (std::max(getPrecision(), x.getPrecision()));
                mpfr_mul (y.getMpfrT(), getMpfrT(), x.getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator* (const unsigned long int &x) const throw() {
                Real y (getPrecision());
                mpfr_mul_ui (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator* (const unsigned int &x) const throw() {
                return * this * static_cast<unsigned long int>(x);
            }
            Real operator* (const unsigned short int &x) const throw() {
                return * this * static_cast<unsigned long int>(x);
            }
            Real operator* (const long int &x) const throw() {
                Real y (getPrecision());
                mpfr_mul_si (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator* (const int &x) const throw() {
                return * this * static_cast<long int>(x);
            }
            Real operator* (const short int &x) const throw() {
                return * this * static_cast<long int>(x);
            }
            Real operator* (const mpz_t &x) const throw() {
                Real y (getPrecision());
                mpfr_mul_z (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator* (const mpq_t &x) const throw() {
                Real y (getPrecision());
                mpfr_mul_q (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
#ifdef GMP_CPP_INTERFACE
            Real operator* (const mpz_class& x) const throw() {
                Real y (getPrecision());
                mpfr_mul_z (y.getMpfrT(), getMpfrT(), x.get_mpz_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator* (const mpq_class& x) const throw() {
                Real y (getPrecision());
                mpfr_mul_q (y.getMpfrT(), getMpfrT(), x.get_mpq_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
#endif

            Real operator/ (const Real &x) const throw() {
                Real y (std::max(getPrecision(), x.getPrecision()));
                mpfr_div (y.getMpfrT(), getMpfrT(), x.getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator/ (const unsigned long int &x) const throw() {
                Real y (getPrecision());
                mpfr_div_ui (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator/ (const unsigned int &x) const throw() {
                return * this / static_cast<unsigned long int>(x);
            }
            Real operator/ (const unsigned short int &x) const throw() {
                return * this / static_cast<unsigned long int>(x);
            }
            Real operator/ (const long int &x) const throw() {
                Real y (getPrecision());
                mpfr_div_si (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator/ (const int &x) const throw() {
                return * this / static_cast<long int>(x);
            }
            Real operator/ (const short int &x) const throw() {
                return * this / static_cast<long int>(x);
            }
            Real operator/ (const mpz_t &x) const throw() {
                Real y (getPrecision());
                mpfr_div_z (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator/ (const mpq_t& x) const throw() {
                Real y (getPrecision());
                mpfr_div_q (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
#ifdef GMP_CPP_INTERFACE
            Real operator/ (const mpz_class& x) const throw() {
                Real y (getPrecision());
                mpfr_div_z (y.getMpfrT(), getMpfrT(), x.get_mpz_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator/ (const mpq_class& x) const throw() {
                Real y (getPrecision());
                mpfr_div_q (y.getMpfrT(), getMpfrT(), x.get_mpq_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
#endif

            Real operator^ (const Real& x) const throw() {
                Real y (getPrecision());
                mpfr_pow (y.getMpfrT(), getMpfrT(), x.getMpfrT(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator^ (const unsigned long int& x) const throw() {
                Real y (getPrecision());
                mpfr_pow_ui (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator^ (const unsigned int& x) const throw() {
                return (*this)^static_cast<unsigned long int>(x);
            }
            Real operator^ (const unsigned short int& x) const throw() {
                return (*this)^static_cast<unsigned long int>(x);
            }
            Real operator^ (const long int& x) const throw() {
                Real y (getPrecision());
                mpfr_pow_si (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator^ (const int& x) const throw() {
                return (*this) ^ static_cast<long int>(x);
            }
            Real operator^ (const short int& x) const throw() {
                return (*this) ^ static_cast<long int>(x);
            }
            Real operator^ (const mpz_t& x) const throw() {
                Real y (getPrecision());
                mpfr_pow_z (y.getMpfrT(), getMpfrT(), x, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
#ifdef GMP_CPP_INTERFACE
            Real operator^ (const mpz_class& x) const throw() {
                Real y (getPrecision());
                mpfr_pow_z (y.getMpfrT(), getMpfrT(), x.get_mpz_t(), getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
#endif

            Real operator-- (int) throw() {
                Real y = *this;
                mpfr_sub_ui (getMpfrT(), getMpfrT(), 1, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator++ (int) throw() {
                Real y = *this;
                mpfr_add_ui (getMpfrT(), getMpfrT(), 1, getParameters().getDefaultRoundMode().getMpfrRndT());
                return y;
            }
            Real operator-- () throw() {
                mpfr_sub_ui (getMpfrT(), getMpfrT(), 1, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }
            Real operator++ () throw() {
                mpfr_add_ui (getMpfrT(), getMpfrT(), 1, getParameters().getDefaultRoundMode().getMpfrRndT());
                return *this;
            }

            //------------------------------------------------------------

            /**
             * Comparison
             */

            bool operator> (const Real& x) const throw (ComparisonWithNaNError) {
                if (isNaN () || x.isNaN()) throw ComparisonWithNaNError();
                return mpfr_greater_p (getMpfrT(), x.getMpfrT()) != 0;
            }

            bool operator>= (const Real& x) const throw (ComparisonWithNaNError) {
                if (isNaN () || x.isNaN()) throw ComparisonWithNaNError();
                return mpfr_greaterequal_p (getMpfrT(), x.getMpfrT()) != 0;
            }

            bool operator< (const Real& x) const throw (ComparisonWithNaNError) {
                if (isNaN () || x.isNaN()) throw ComparisonWithNaNError();
                return mpfr_less_p (getMpfrT(), x.getMpfrT()) != 0;
            }

            bool operator<= (const Real& x) const throw (ComparisonWithNaNError) {
                if (isNaN () || x.isNaN()) throw ComparisonWithNaNError();
                return mpfr_lessequal_p (getMpfrT(), x.getMpfrT()) != 0;
            }

            bool operator== (const Real& x) const throw (ComparisonWithNaNError) {
                if (isNaN () || x.isNaN()) throw ComparisonWithNaNError();
                return mpfr_equal_p (getMpfrT(), x.getMpfrT()) != 0;
            }

            bool operator!= (const Real& x) const throw (ComparisonWithNaNError) {
                return !(*this == x);
            }
    };    // class Real

    //------------------------------------------------------------

}    // namespace mpfr

#endif    // MPFRCPP_REAL_REAL
