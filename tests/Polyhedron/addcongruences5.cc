/* Test Polyhedron::add_congruences(): add a system of congruences to
   an empty, zero-dimensional polyhedron.
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

#include "ppl_test.hh"

using namespace std;
using namespace Parma_Polyhedra_Library;

int
main() TRY {
  set_handlers();

  C_Polyhedron ph;
  ph.add_constraint(Linear_Expression(-2) >= 0);

  print_constraints(ph, "*** ph ***");

  Congruence_System cgs;
  cgs.insert(Linear_Expression(-1) %= 0);

  print_constraints(cgs, "*** cgs ***");

  ph.add_congruences(cgs);

  C_Polyhedron known_result(0, EMPTY);

  int retval = (known_result == ph) ? 0 : 1;

  print_constraints(ph, "*** After add_constraints ***");

  return retval;
}
CATCH
