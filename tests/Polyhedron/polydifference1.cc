/* Test Polyhedron::poly_difference_assign().
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

  Generator_System gs1;
  gs1.insert(point(0*x + 0*y));
  gs1.insert(point(4*x + 0*y));
  gs1.insert(point(2*x + 2*y));

  C_Polyhedron ph1(gs1);

  print_generators(ph1, "*** ph1 ***");

  Generator_System gs2;
  gs2.insert(point(0*x + 3*y));
  gs2.insert(point(4*x + 3*y));
  gs2.insert(point(2*x + 1*y));

  C_Polyhedron ph2(gs2);

  print_generators(ph2, "*** ph2 ***");

  C_Polyhedron computed_result = ph1;

  computed_result.poly_difference_assign(ph2);

  Generator_System gs_known_result;
  gs_known_result.insert(point());
  gs_known_result.insert(point(3*x + 3*y, 2));
  gs_known_result.insert(point(4*x));
  gs_known_result.insert(point(5*x + 3*y, 2));

  C_Polyhedron known_result(gs_known_result);

  C_Polyhedron ph3(2);
  ph3.add_constraint(2*y >= 3);

  known_result.poly_difference_assign(ph3);

  int retval = (computed_result == known_result) ? 0 : 1;

  print_generators(computed_result, "*** After poly_difference_assign ***");
  print_generators(known_result, "*** known_result ***");

  return retval;
}
CATCH
