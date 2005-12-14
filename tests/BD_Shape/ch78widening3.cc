/* Test BD_Shape::CH78_widening_assign().
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
  Variable A(0);
  Variable B(1);
  Variable C(2);
  Variable D(3);
  Variable E(4);

  TBD_Shape bd1(5);
  TBD_Shape bd2(5);
  TBD_Shape known_result(5);

  bd1.add_constraint(A >= 0);
  bd1.add_constraint(B >= 0);
  bd1.add_constraint(C >= 1);
  bd1.add_constraint(D >= 0);
  bd1.add_constraint(E >= 0);
  bd1.add_constraint(C - D <= 76);
  bd1.add_constraint(C - E <= 76);
  bd1.add_constraint(E - D == 0);

  bd2.add_constraint(A >= 0);
  bd2.add_constraint(B >= 0);
  bd2.add_constraint(C >= 1);
  bd2.add_constraint(D >= 0);
  bd2.add_constraint(E >= 0);
  bd2.add_constraint(C - D <= 75);
  bd2.add_constraint(C - E <= 75);
  bd2.add_constraint(E - D == 0);

  print_constraints(bd1, "*** bd1 ***");
  print_constraints(bd2, "*** bd2 ***");

  bd1.CH78_widening_assign(bd2);

  known_result.add_constraint(A >= 0);
  known_result.add_constraint(B >= 0);
  known_result.add_constraint(C >= 1);
  known_result.add_constraint(D >= 0);
  known_result.add_constraint(E - D == 0);

  print_constraints(bd1, "*** bd1.CH78_widening_assign(bd2) ***");

  int retval = (bd1 == known_result) ? 0 : 1;

  return retval;

}
CATCH
