/* Prolog main program for the 2nd toy PPL/CIAO-Prolog CLP(Q) interpreter.
   Copyright (C) 2001-2003 Roberto Bagnara <bagnara@cs.unipr.it>

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
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

:- module(_, [main/0], []).
:- use_module(library(debugger)). 
:- use_module(library(dynamic)). 
:- use_module(library(lists)). 
:- use_module(library(prolog_sys)).
:- use_module(library(read)).
:- use_module(library(write)).
:- use_module(ppl_ciao).
/*
,
[
	ppl_initialize/0,
	ppl_finalize/0,
	ppl_new_Polyhedron_from_dimension/3,
	ppl_new_Polyhedron_from_Polyhedron/4,
	ppl_delete_Polyhedron/1,
	ppl_Polyhedron_space_dimension/2,
	ppl_Polyhedron_get_constraints/2,
	ppl_Polyhedron_add_constraints_and_minimize/2,
	ppl_Polyhedron_add_dimensions_and_embed/2,
	ppl_Polyhedron_remove_higher_dimensions/2
]).
*/

:- set_prolog_flag(multi_arity_warnings, off).

eat_eol.

:- include('clpq2.pl').

main :-
    ppl_initialize,
    common_main.
