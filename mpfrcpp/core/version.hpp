#ifndef MPFRCPP_CORE_VERSION
#define MPFRCPP_CORE_VERSION

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
 * @file version.hpp
 * @date 2007-04-06
 * Product (library) version class.
 * INTERNAL HEADER, NOT TO BE USED DIRECTLY.
 */

#ifndef INCLUDED_BY_MPFRCPP
    #error THIS IS AN INTERNAL HEADER ONLY, NOT TO BE USED DIRECTLY
#endif

namespace mpfr {

    class Version {
        unsigned int major_, minor_, patch_;

        static int cmp_ (const Version& v1, const Version& v2) throw() {
            if (v1.getMajor() > v2.getMajor()) return 1;
            if (v1.getMajor() < v2.getMajor()) return -1;
        
            if (v1.getMinor() > v2.getMinor()) return 1;
            if (v1.getMinor() < v2.getMinor()) return -1;

            if (v1.getPatch() > v2.getPatch()) return 1;
            if (v1.getPatch() < v2.getPatch()) return -1;

            return 0;
        }

    public:
        
        Version (unsigned int major, unsigned int minor, unsigned int patch ) throw() : major_( major ), minor_( minor ), patch_( patch ) {}

        unsigned int getMajor() const throw() { return major_; }
        unsigned int getMinor() const throw() { return minor_; }
        unsigned int getPatch() const throw() { return patch_; }

        std::string toString() const throw() {
            std::ostringstream s;
            s << major_ << '.' << minor_ << '.' << patch_;
            return s.str();
        }

        operator std::string() const throw () { return toString(); }

        bool operator> (const Version& v) const throw() {
            return cmp_ (*this, v) == 1;
        }
        bool operator< (const Version& v) const throw() {
            return cmp_ (*this, v) == -1;
        }
        bool operator>= (const Version& v) const throw() {
            return cmp_ (*this, v) != -1;
        }
        bool operator<= (const Version& v) const throw() {
            return cmp_ (*this, v) != 1;
        }
        bool operator== (const Version& v) const throw() {
            return cmp_ (*this, v) == 0;
        }
        bool operator!= (const Version& v) const throw() {
            return cmp_ (*this, v) != 0;
        }

    };

} // namespace mpfr

#endif // MPFRCPP_CORE_VERSION
