/* Test Polyhedron::add_generators_and_minimize(): we add a system of
   generators to a polyhedron defined by its system of constraints.
   Copyright (C) 2001-2005 Roberto Bagnara <bagnara@cs.unipr.it>

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

int
main() TRY {
  set_handlers();

  Variable x(0);
  Variable y(1);

  C_Polyhedron ph(2);
  ph.add_constraint(x >= 0);
  ph.add_constraint(x <= -1);

  print_constraints(ph, "*** ph ***");

  Generator_System gs;
  gs.insert(ray(x + y));
  gs.insert(point());

  print_generators(gs, "--- gs ---");

  ph.add_generators_and_minimize(gs);

  Generator_System gs_known_result;
  gs_known_result.insert(point());
  gs_known_result.insert(ray(x + y));
  C_Polyhedron known_result(gs_known_result);

  int retval = (ph == known_result) ? 0 : 1;

  print_generators(ph, "*** After add_generators_and_minimize ***");

  return retval;
}
CATCH
