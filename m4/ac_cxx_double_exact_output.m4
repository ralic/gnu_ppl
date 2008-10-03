dnl A function to detect whether C++ provides exact output for doubles.
dnl Copyright (C) 2001-2008 Roberto Bagnara <bagnara@cs.unipr.it>
dnl
dnl This file is part of the Parma Polyhedra Library (PPL).
dnl
dnl The PPL is free software; you can redistribute it and/or modify it
dnl under the terms of the GNU General Public License as published by the
dnl Free Software Foundation; either version 3 of the License, or (at your
dnl option) any later version.
dnl
dnl The PPL is distributed in the hope that it will be useful, but WITHOUT
dnl ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
dnl FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software Foundation,
dnl Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.
dnl
dnl For the most up-to-date information see the Parma Polyhedra Library
dnl site: http://www.cs.unipr.it/ppl/ .

AC_DEFUN([AC_CXX_DOUBLE_EXACT_OUTPUT],
[
AC_REQUIRE([AC_CXX_DOUBLE_BINARY_FORMAT])
ac_save_CPPFLAGS="$CPPFLAGS"
ac_save_LIBS="$LIBS"
AC_LANG_PUSH(C++)

AC_MSG_CHECKING([whether C++ provide exact output for doubles])
ac_cxx_double_exact_output=unknown

AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <limits>
#ifdef HAVE_STDINT_H
#ifndef __STDC_LIMIT_MACROS
#define __STDC_LIMIT_MACROS 1
#endif
#include <stdint.h>
#endif
#ifdef HAVE_INTTYPES_H
#include <inttypes.h>
#endif
#include <cstdlib>
#include <sstream>
//#include <iostream>

/* Unique (nonzero) code for the IEEE 754 Single Precision
   floating point format.  */
# define PPL_FLOAT_IEEE754_SINGLE 1

/* Unique (nonzero) code for the IEEE 754 Double Precision
   floating point format.  */
# define PPL_FLOAT_IEEE754_DOUBLE 2

/* Unique (nonzero) code for the IEEE 754 Quad Precision
   floating point format.  */
# define PPL_FLOAT_IEEE754_QUAD 3

/* Unique (nonzero) code for the Intel Double-Extended
   floating point format.  */
# define PPL_FLOAT_INTEL_DOUBLE_EXTENDED 4

bool
check(double value, const char* text) {
  std::ostringstream ss;
  ss.precision(10000);
  ss << value;
  //std::cout << ss.str() << " ?==? " << text << std::endl;
  return ss.str() == text;
}

#if SIZEOF_DOUBLE == 8

double
convert(uint32_t msp, uint32_t lsp) {
  union {
    double value;
    struct {
#ifdef WORDS_BIGENDIAN
      uint32_t msp;
      uint32_t lsp;
#else
      uint32_t lsp;
      uint32_t msp;
#endif
    } parts;
  } u;

  u.parts.msp = msp;
  u.parts.lsp = lsp;
  return u.value;
}

#if CXX_DOUBLE_BINARY_FORMAT == PPL_FLOAT_IEEE754_DOUBLE

int
main() {
  if (check(convert(0xaaacccaaUL, 0xacccaaacUL),
            "-4.018242396032647085467373664662028399901175154542925376476863248797653889888945947404163925979898721593782464256360719269163883854613473748830842329884157359816532025640075051481726120707111709993717456369512975427023957197464411926714771905463723621065863511603311053477227687835693359375e-103")
      && check(convert(0xcccaaaccUL, 0xcaaacccaUL),
               "-85705035845709846787631445265530356117787053916987832397725696")
      && check(convert(0x00000000UL, 0x00000001UL),
               "4.940656458412465441765687928682213723650598026143247644255856825006755072702087518652998363616359923797965646954457177309266567103559397963987747960107818781263007131903114045278458171678489821036887186360569987307230500063874091535649843873124733972731696151400317153853980741262385655911710266585566867681870395603106249319452715914924553293054565444011274801297099995419319894090804165633245247571478690147267801593552386115501348035264934720193790268107107491703332226844753335720832431936092382893458368060106011506169809753078342277318329247904982524730776375927247874656084778203734469699533647017972677717585125660551199131504891101451037862738167250955837389733598993664809941164205702637090279242767544565229087538682506419718265533447265625e-324")
      && check(convert(0x80000000UL, 0x00000001UL),
               "-4.940656458412465441765687928682213723650598026143247644255856825006755072702087518652998363616359923797965646954457177309266567103559397963987747960107818781263007131903114045278458171678489821036887186360569987307230500063874091535649843873124733972731696151400317153853980741262385655911710266585566867681870395603106249319452715914924553293054565444011274801297099995419319894090804165633245247571478690147267801593552386115501348035264934720193790268107107491703332226844753335720832431936092382893458368060106011506169809753078342277318329247904982524730776375927247874656084778203734469699533647017972677717585125660551199131504891101451037862738167250955837389733598993664809941164205702637090279242767544565229087538682506419718265533447265625e-324"))
    exit(0);
  else
    exit(1);
}

#else // CXX_DOUBLE_EXACT_OUTPUT != FLOAT_IEEE754_DOUBLE

int
main() {
  exit(1);
}

#endif // CXX_DOUBLE_EXACT_OUTPUT != FLOAT_IEEE754_DOUBLE

#else // SIZEOF_DOUBLE != 8

int
main() {
  exit(1);
}

#endif // SIZEOF_DOUBLE != 8
]])],
  AC_MSG_RESULT(yes)
  ac_cxx_double_exact_output=1,
  AC_MSG_RESULT(no)
  ac_cxx_double_exact_output=0)

AC_DEFINE_UNQUOTED(CXX_DOUBLE_EXACT_OUTPUT, $ac_cxx_double_exact_output,
  [Not zero if C++ supports exact output for doubles.])

AC_LANG_POP(C++)
CPPFLAGS="$ac_save_CPPFLAGS"
LIBS="$ac_save_LIBS"
])
