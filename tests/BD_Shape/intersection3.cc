/* Test BD_Shape::intersection_assign().
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
  Variable x(0);
  Variable y(1);
  // Variable z(2);

  TBD_Shape bd1(3);
  TBD_Shape bd2(3);
  TBD_Shape known_result(3);

  bd2.add_constraint(y - x <= -1);
  bd2.add_constraint(x <= 3);
  bd2.add_constraint(-y <= 5);

  bd1.add_constraint(x <= 4);
  bd1.add_constraint(-x <= -1);
  bd1.add_constraint(y <= 3);
  bd1.add_constraint(-y <= -1);
  bd1.add_constraint(x - y <= 1);

  print_constraints(bd1, "*** bd1 ***");
  print_constraints(bd2, "*** bd2 ***");

  bd1.intersection_assign(bd2);

  known_result.add_constraint(x <= 3);
  known_result.add_constraint(-x <= -1);
  known_result.add_constraint(y <= 3);
  known_result.add_constraint(-y <= -1);
  known_result.add_constraint(y - x <= -1);
  known_result.add_constraint(x - y <= 1);

  print_constraints(bd1, "*** bd1.intersection_assign(bd2) ***");

  int retval = (bd1 == known_result) ? 0 : 1;

  return retval;

}
CATCH
