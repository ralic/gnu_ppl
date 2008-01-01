/* Different ways of creating an empty BD_Shape.
   Copyright (C) 2001-2008 Roberto Bagnara <bagnara@cs.unipr.it>

This file is part of the Parma Polyhedra Library (PPL).

The PPL is free software; you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation; either version 3 of the License, or (at your
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

namespace {

bool
test01() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd1(4);
  TBD_Shape bd2(4);

  bd1.add_constraint(-x <= 4);
  bd1.add_constraint(y - x <= 0);
  bd1.add_constraint(x - y <= -5);

  bool empty = bd1.is_empty();

  nout << "*** bd1.is_empty() ***" << endl;
  nout << (empty ? "true" : "false ") << endl;

  bd2.add_constraint(-x <= 4);
  bd2.add_constraint(y - x <= 0);
  bd2.add_constraint(x - y <= 5);
  bd2.add_constraint(z - x <= 1);

  bool empty1 = bd2.is_empty();

  nout << "*** bd2.is_empty() ***" << endl;
  nout << (empty1 ? "true" : "false") << endl;

  return !empty1 && empty;

}

bool
test02() {
  Variable x(0);
  Variable y(1);
  Variable z(2);

  TBD_Shape bd1(4);
  TBD_Shape bd2(4);

  bd1.add_constraint(-x <= 2);
  bd1.add_constraint(y - x <= -9);
  bd1.add_constraint(x - y <= -7);

  bool empty = bd1.is_empty();

  print_constraints(bd1, "*** bd1 ***");
  nout << "*** bd1.is_empty() ***" << endl;
  nout << (empty ? "true" : "false") << endl;

  bd2.add_constraint(-x <= 7);
  bd2.add_constraint(y - x <= 1);
  bd2.add_constraint(-y <= 2);
  bd2.add_constraint(z - x <= 1);

  bool empty1 = bd2.is_empty();

  print_constraints(bd2, "*** bd2 ***");
  nout << "*** bd2.is_empty() ***" << endl;
  nout << (empty1 ? "true" : "false") << endl;

  return !empty1 && empty;
}

bool
test03() {
  Variable x1(0);
  Variable x2(1);
  Variable x3(2);
  Variable x4(3);
  Variable x5(4);
  // Variable x6(5);

  TBD_Shape bd1(6);
  TBD_Shape bd2(6);

  bd1.add_constraint(x1 <= 3);
  bd1.add_constraint(x4 <= 3);
  bd1.add_constraint(x2 - x1 <= 0);
  bd1.add_constraint(x3 - x1 <= -2);
  bd1.add_constraint(x5 - x1 <= 2);
  bd1.add_constraint(-x2 <= 0);
  bd1.add_constraint(x3 - x2 <= 5);
  bd1.add_constraint(x4 - x3 <= -6);
  bd1.add_constraint(x1 - x4 <= 5);
  bd1.add_constraint(x5 - x4 <= 2);
  bd1.add_constraint(-x5 <= -5);
  bd1.add_constraint(x3 - x5 <= 7);

  bool empty = bd1.is_empty();

  nout << "*** bd1.is_empty() ***" << endl;
  nout << (empty ? "true" : "false") << endl;

  bd2.add_constraint(x1 <= 3);
  bd2.add_constraint(x4 <= 3);
  bd2.add_constraint(x2 - x1 <= 0);
  bd2.add_constraint(x3 - x1 <= 2);
  bd2.add_constraint(x5 - x1 <= 2);
  bd2.add_constraint(-x2 <= 0);
  bd2.add_constraint(x3 - x2 <= 5);
  bd2.add_constraint(x4 - x3 <= 6);
  bd2.add_constraint(x1 - x4 <= 5);
  bd2.add_constraint(x5 - x4 <= 2);
  bd2.add_constraint(-x5 <= 5);
  bd2.add_constraint(x3 - x5 <= 7);

  bool empty1 = bd2.is_empty();

  nout << "*** bd2.is_empty() ***" << endl;
  nout << (empty1 ? "true" : "false") << endl;

  return !empty1 && empty;
}

bool
test04() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  TBD_Shape bd(3);

  bd.add_constraint(A == 0);
  bd.add_constraint(C >= 0);
  bd.add_constraint(B - C >= 1);

  bool empty = bd.is_empty();

  print_constraints(bd, "*** bd ***");
  nout << "*** bd.is_empty() ***"
       << endl
       << (empty ? "true" : "false") << endl;

  return !empty;
}

bool
test05() {
  Variable x1(0);
  Variable x2(1);
  Variable x3(2);
  Variable x4(3);
  Variable x5(4);

  TBD_Shape bd(5);

  Coefficient a;
  if (std::numeric_limits<Coefficient>::is_bounded)
    a = -(std::numeric_limits<Coefficient>::min()/2) + 1;
  else
    a = 1300000000;

  bd.add_constraint(x1 - x2 <= -a);
  bd.add_constraint(x2 - x3 <= -a);
  bd.add_constraint(x3 - x4 <= a);
  bd.add_constraint(x4 - x5 <= a);
  bd.add_constraint(x5 - x1 <= a);

  print_constraints(bd, "*** bd ***");

  bool empty = bd.is_empty();

  nout << "*** bd.is_empty() ***" << endl;
  nout << (empty ? "true" : "false") << endl;

  return !empty;
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  DO_TEST(test04);
  DO_TEST(test05);
END_MAIN

