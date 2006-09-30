/* SWI Prolog Common Foreign Language Interface: declarations.
   Copyright (C) 2001-2006 Roberto Bagnara <bagnara@cs.unipr.it>

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 2 of the License, or (at your
option) any later version.

The PPL is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software Foundation,
Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#ifndef PCFLI_swi_cfli_h
#define PCFLI_swi_cfli_h 1

/* Include gmp.h before SWI-Prolog.h.  This is required in order to
   get access to interface functions dealing with GMP numbers and
   SWI-Prolog terms.  */
#include <gmp.h>
#include <SWI-Prolog.h>

#ifdef __GNUC__
# define PCFLI_EXTERN_INLINE extern __inline__
# define PCFLI_INLINE_PROTOTYPES 1
#endif

#if defined(__cplusplus) && !defined(PCFLI_EXTERN_INLINE)
# define PCFLI_EXTERN_INLINE inline
#endif

#ifdef PCFLI_EXTERN_INLINE
# ifndef PCFLI_INLINE_PROTOTYPES
#  define PCFLI_INLINE_PROTOTYPES 0
# endif
#else
# define PCFLI_INLINE_PROTOTYPES 1
#endif

/* Temporary. */
#define PCFLI_DECLSPEC

#ifdef __cplusplus
//extern "C" {
#endif

typedef term_t Prolog_term_ref;
typedef atom_t Prolog_atom;
typedef foreign_t Prolog_foreign_return_type;

const Prolog_foreign_return_type PROLOG_SUCCESS = TRUE;
const Prolog_foreign_return_type PROLOG_FAILURE = FALSE;

#if PCFLI_INLINE_PROTOTYPES

PCFLI_DECLSPEC Prolog_term_ref
Prolog_new_term_ref();

PCFLI_DECLSPEC int
Prolog_put_term(Prolog_term_ref t, Prolog_term_ref u);

PCFLI_DECLSPEC int
Prolog_put_long(Prolog_term_ref t, long i);

PCFLI_DECLSPEC int
Prolog_put_atom_chars(Prolog_term_ref t, const char* s);

PCFLI_DECLSPEC int
Prolog_put_atom(Prolog_term_ref t, Prolog_atom a);

PCFLI_DECLSPEC int
Prolog_put_address(Prolog_term_ref t, void* p);

Prolog_atom
Prolog_atom_from_string(const char* s);

PCFLI_DECLSPEC int
Prolog_construct_compound(Prolog_term_ref t, Prolog_atom f,
			  Prolog_term_ref a1);

PCFLI_DECLSPEC int
Prolog_construct_compound(Prolog_term_ref t, Prolog_atom f,
			  Prolog_term_ref a1, Prolog_term_ref a2);

PCFLI_DECLSPEC int
Prolog_construct_compound(Prolog_term_ref t, Prolog_atom f,
			  Prolog_term_ref a1, Prolog_term_ref a2,
			  Prolog_term_ref a3);

PCFLI_DECLSPEC int
Prolog_construct_compound(Prolog_term_ref t, Prolog_atom f,
			  Prolog_term_ref a1, Prolog_term_ref a2,
			  Prolog_term_ref a3, Prolog_term_ref a4);

PCFLI_DECLSPEC int
Prolog_construct_cons(Prolog_term_ref c,
		      Prolog_term_ref h, Prolog_term_ref t);

PCFLI_DECLSPEC void
Prolog_raise_exception(Prolog_term_ref t);

PCFLI_DECLSPEC int
Prolog_is_variable(Prolog_term_ref t);

PCFLI_DECLSPEC int
Prolog_is_atom(Prolog_term_ref t);

PCFLI_DECLSPEC int
Prolog_is_integer(Prolog_term_ref t);

PCFLI_DECLSPEC int
Prolog_is_address(Prolog_term_ref t);

PCFLI_DECLSPEC int
Prolog_is_compound(Prolog_term_ref t);

PCFLI_DECLSPEC int
Prolog_is_cons(Prolog_term_ref t);

PCFLI_DECLSPEC int
Prolog_get_long(Prolog_term_ref t, long& v);

PCFLI_DECLSPEC int
Prolog_get_address(Prolog_term_ref t, void*& p);

PCFLI_DECLSPEC int
Prolog_get_atom_name(Prolog_term_ref t, Prolog_atom& name);

PCFLI_DECLSPEC int
Prolog_get_compound_name_arity(Prolog_term_ref t,
			       Prolog_atom& name, int& arity);

PCFLI_DECLSPEC int
Prolog_get_arg(int i, Prolog_term_ref t, Prolog_term_ref a);

PCFLI_DECLSPEC int
Prolog_get_cons(Prolog_term_ref c, Prolog_term_ref h, Prolog_term_ref t);

PCFLI_DECLSPEC int
Prolog_unify(Prolog_term_ref t, Prolog_term_ref u);

#endif /* !PCFLI_INLINE_PROTOTYPES */

#include "swi_cfli.ic"

#ifdef __cplusplus
//} /* extern "C" */
#endif

#endif // !defined(PCFLI_swi_cfli_h)