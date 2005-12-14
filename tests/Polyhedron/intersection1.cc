/* Intersection of an icosahedron with a column.
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
  Variable z(2);

  C_Polyhedron icosahedron(3);
  icosahedron.add_constraint(4*x - 2*y - z + 14 >= 0);
  icosahedron.add_constraint(4*x + 2*y - z + 2 >= 0);
  icosahedron.add_constraint(x + y - 1 >= 0);
  icosahedron.add_constraint(x + y + 2*z - 5 >= 0);
  icosahedron.add_constraint(x + 1 >= 0);
  icosahedron.add_constraint(x + z - 1 >= 0);
  icosahedron.add_constraint(2*x + y -2*z + 7 >= 0);
  icosahedron.add_constraint(x - y + 2*z + 1 >= 0);
  icosahedron.add_constraint(x - y + 5 >= 0);
  icosahedron.add_constraint(2*x - y - 2*z + 13 >= 0);
  icosahedron.add_constraint(-2*x - y + 2*z + 1 >= 0);
  icosahedron.add_constraint(-x + y - 1 >= 0);
  icosahedron.add_constraint(-x + y -2*z + 7 >= 0);
  icosahedron.add_constraint(-4*x + 2*y + z - 4 >= 0);
  icosahedron.add_constraint(-2*x + y + 2*z - 5 >= 0);
  icosahedron.add_constraint(-x + 1 >= 0);
  icosahedron.add_constraint(-x - z + 5 >= 0);
  icosahedron.add_constraint(-4*x - 2*y + z + 8 >= 0);
  icosahedron.add_constraint(-x - y + 5 >= 0);
  icosahedron.add_constraint(-x - y -2*z +13 >= 0);

  C_Polyhedron column(3);
  column.add_constraint(y >= 2);
  column.add_constraint(y <= 4);
  column.add_constraint(x >= 0);
  column.add_constraint(x <= 1);

  C_Polyhedron computed_result = icosahedron;
  computed_result.intersection_assign_and_minimize(column);

  C_Polyhedron known_result(3);
  known_result.add_constraint(-4*x - 2*y + z >= -8);
  known_result.add_constraint(-4*x + 2*y + z >= 4);
  known_result.add_constraint(-2*x - y + 2*z >= -1);
  known_result.add_constraint(-2*x + y + 2*z >= 5);
  known_result.add_constraint(-x - y - 2*z >= -13);
  known_result.add_constraint(-x - z >= -5);
  known_result.add_constraint(-x >= -1);
  known_result.add_constraint(-x + y - 2*z >= -7);
  known_result.add_constraint(-y >= -4);
  known_result.add_constraint(y >= 2);
  known_result.add_constraint(x >= 0);

  int retval = (computed_result == known_result) ? 0 : 1;

  print_constraints(icosahedron, "*** icosahedron ***");
  print_constraints(column, "*** column ***");
  print_constraints(computed_result, "*** computed_result ***");

  return retval;
}
CATCH
