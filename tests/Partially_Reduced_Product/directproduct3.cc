/* Test Direct_Product<NNC_Polyhedron, Grid>.
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

#define PH_IS_FIRST

// ONE AND ONLY ONE OF THESE MUST BE 1
#define NNC_Poly_Class 1
#define C_Poly_Class 0
#define BD_Shape_Class 0
#define Octagonal_Shape_Class 0
#define Box_Class 0

#if Box_Class
typedef TBox Poly;
#endif

#if Octagonal_Shape_Class
typedef TOctagonal_Shape Poly;
#endif

#if BD_Shape_Class
typedef BD_Shape<mpq_class> Poly;
#endif

#if NNC_Poly_Class
typedef NNC_Polyhedron Poly;
#endif

#if C_Poly_Class
typedef C_Polyhedron Poly;
#endif

#ifdef PH_IS_FIRST
typedef Domain_Product<Poly, Grid>::Direct_Product Product;
#else
typedef Domain_Product<Grid, Poly>::Direct_Product Product;
#endif

namespace {

// space_dimension()
bool
test01() {
  Variable A(0);
  Variable E(4);

#if NNC_Poly_Class
  Constraint_System cs(A + E < 9);
#else
  Constraint_System cs(A + E <= 9);
#endif

  Product dp(cs);

  bool ok = (dp.space_dimension() == 5);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}


// affine_dimension()
bool
test02() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
#if Box_Class
  dp.add_constraint(A <= 9);
  dp.add_constraint(A >= 9);
#else
  dp.add_constraint(A - C >= 9);
  dp.add_constraint(A - C <= 9);
#endif
  dp.add_constraint(B >= 2);

  bool ok;

#ifdef PH_IS_FIRST
  ok = (dp.domain2().affine_dimension() == 3
	&& dp.domain1().affine_dimension() == 2);
#else
  ok = (dp.domain1().affine_dimension() == 2
	&& dp.domain2().affine_dimension() == 3);
#endif
  ok = (ok && dp.affine_dimension() == 2);

  if (!ok)
    return false;

  dp.add_constraint(C == 4);
  dp.add_constraint(B == 2);

#ifdef PH_IS_FIRST
  ok = (dp.domain2().affine_dimension() == 1
	&& dp.domain1().affine_dimension() == 0);
#else
  ok = (dp.domain1().affine_dimension() == 1
	&& dp.domain2().affine_dimension() == 0);
#endif

  ok &= (ok && dp.affine_dimension() == 0);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// contains()
bool
test03() {
  Variable A(0);

  Product dp1(1);
  dp1.add_constraint(A <= 3);
  dp1.add_congruence((A %= 3) / 2);

  Product dp2(1);
  dp2.add_constraint(A <= 3);
  dp2.add_congruence(A %= 3);

  bool ok1 = !dp1.contains(dp2);

  dp2.add_congruence((A %= 1) / 4);

  bool ok2 = dp1.contains(dp2);

  dp1.add_congruence((A == 1) / 0);
  dp2.add_constraint(A <= 2);
  dp2.add_constraint(A >= -1);
  dp2.add_congruence((A %= 1) / 3);

  bool ok3 = !dp1.contains(dp2);

  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp1, "*** dp1 congruences ***");

  return ok1 && ok2 && ok3;
}

// strictly_contains()
bool
test04() {
  Variable A(0);

  Product dp1(1);
  dp1.add_constraint(A <= 2);
  dp1.add_congruence(A %= 0);

  Product dp2(1);
  dp2.add_constraint(A <= 1);
  dp2.add_congruence(A %= 0);

  bool ok1 = dp1.strictly_contains(dp2);

  dp1.add_constraint(A <= 1);
  dp2.add_congruence((A %= 1) /2);

  bool ok2 = dp1.strictly_contains(dp2);

  dp1.add_congruence((A %= 1) /2);

  bool ok3 = !dp1.strictly_contains(dp2);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok1 && ok2 && ok3;
}

// FIXME: Waiting for covering box methods, details in
//        Direct_Product.defs.hh.
#if 0
// get_covering_box(box), via grid.
bool
test05() {
  Variable A(0);
  Variable B(1);

  Rational_Box box(1);

  Product dp(1);
  dp.add_congruence((A %= 0) / 3);

  dp.get_covering_box(box);

  Rational_Box known_box(1);
  known_box.add_constraint(A >= 0);
  known_box.add_constraint(A <= 3);

  bool ok = (box == known_box);

  Rational_Box box1(1);

  Product dp1(2);
  dp1.add_constraint(B < 3);
  dp1.add_constraint(B > 0);

  dp1.get_covering_box(box1);

  Rational_Box known_box1(1);
  known_box1.add_constraint(B == 0 /* FIX */);

  bool ok1 = (box1 == known_box1);

  Rational_Box box2(2);

  Product dp2(2);
  dp2.add_constraint(B <= 0);
  dp2.add_constraint(B >= 0);
  dp2.add_congruence(A - B %= 0);

  dp2.get_covering_box(box2);

  Rational_Box known_box2(2);
  known_box2.add_constraint(A >= 0);
  known_box2.add_constraint(A <= 1);

  bool ok2 = !(box2 == known_box2);

  return ok && ok1 && ok2;
}
#endif

// intersection_assign()
bool
test06() {
  Variable A(0);
  Variable B(1);

  Product dp1(3);
  dp1.add_constraint(A >= 0);
  dp1.add_congruence((A %= 0) / 2);

  Product dp2(3);
  dp2.add_constraint(A <= 0);
  dp2.add_congruence((A %= 0) / 7);

  dp1.intersection_assign(dp2);

  Product known_dp(3);
  known_dp.add_congruence((A %= 0) / 14);
  known_dp.add_constraint(A >= 0);
  known_dp.add_constraint(A <= 0);

  bool ok = (dp1 == known_dp);

  if (!ok) {
    print_congruences(dp1, "*** dp1 congruences ***");
    print_constraints(dp1, "*** dp1 constraints ***");
    print_congruences(dp2, "*** dp2 congruences ***");
    print_constraints(dp2, "*** dp2 constraints ***");
    return ok;
  }

  dp1.add_constraint(B <= 1);
  dp2.add_constraint(B >= 1);
  dp1.intersection_assign(dp2);
  ok = !dp1.is_empty();

  if (!ok) {
    print_congruences(dp1, "*** dp1 congruences ***");
    print_constraints(dp1, "*** dp1 constraints ***");
    print_congruences(dp2, "*** dp2 congruences ***");
    print_constraints(dp2, "*** dp2 constraints ***");
    return ok;
  }

  dp2.add_constraint(B >= 2);
  dp1.intersection_assign(dp2);
  ok = dp1.is_empty();

  if (!ok) {
    print_congruences(dp1, "*** dp1 congruences ***");
    print_constraints(dp1, "*** dp1 constraints ***");
    print_congruences(dp2, "*** dp2 congruences ***");
    print_constraints(dp2, "*** dp2 constraints ***");
  }

  return ok;
}

// upper_bound_assign(dp2)
bool
test07() {
  Variable A(0);
  Variable B(1);

  Constraint_System cs(A == 9);

  Product dp1(cs);

  Product dp2(1);
  dp2.add_constraint(A == 19);

  dp1.upper_bound_assign(dp2);

  Product known_dp(1);
  known_dp.add_constraint(A >= 9);
  known_dp.add_constraint(A <= 19);
  known_dp.add_congruence((A %= 9) / 10);

  bool ok = (dp1 == known_dp);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

// upper_bound_assign_if_exact()
bool
test08() {
  Variable A(0);
  Variable B(1);

  Product dp1(3);
  dp1.add_constraint(B == 0);

  Product dp2(3);
  dp2.add_constraint(B == 0);
  dp2.add_constraint(A == 12);
  dp2.add_constraint(A == 16);

  dp1.upper_bound_assign_if_exact(dp2);

  Product known_dp(3);
  known_dp.add_constraint(B == 0);

  bool ok = (dp1 == known_dp);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

// difference_assign()
bool
test09() {
  Variable A(0);
  Variable B(1);

  Product dp1(3);
  dp1.add_constraint(A >= 0);
  dp1.add_congruence((A - B %= 0) / 2);

  Product dp2(3);
  dp2.add_constraint(A >= 3);
  dp2.add_congruence((A - B %= 0) / 4);

  dp1.difference_assign(dp2);

  Product known_dp(3);
  known_dp.add_constraint(A >= 0);
#if NNC_Poly_Class
  known_dp.add_constraint(A < 3);
#else
#if !Box_Class
// FIXME Box class returns the box unchanged.
  known_dp.add_constraint(A <= 3);
#endif
#endif
  known_dp.add_congruence((A - B %= 2) / 4);

  bool ok = (dp1 == known_dp);

  print_congruences(dp1, "*** dp1 ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2,  "*** dp2 ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

// add_space_dimensions_and_embed()
bool
test10() {
  Variable A(0);
  Variable B(1);

  Product dp1(2);
  dp1.add_constraint(A >= 0);
  dp1.add_congruence((A %= 0) / 2);

  dp1.add_space_dimensions_and_embed(3);

  Product known_dp(5);
  known_dp.add_congruence((A %= 0) / 2);
  known_dp.add_constraint(A >= 0);

  bool ok = (dp1 == known_dp);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");

  return ok;
}

// add_space_dimensions_and_project()
bool
test11() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp1(2);
  dp1.add_constraint(A >= 0);
  dp1.add_congruence((A %= 0) / 2);

  dp1.add_space_dimensions_and_project(1);

  Product known_dp(3);
  known_dp.add_congruence((A %= 0) / 2);
  known_dp.add_constraint(A >= 0);
  known_dp.add_constraint(C == 0);

  bool ok = (dp1 == known_dp);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");

  return ok;
}

// concatenate_assign()
bool
test12() {
  Variable A(0);
  Variable B(1);
  Variable C(2);
  Variable D(3);

  Product dp1(2);
  dp1.add_constraint(A >= 0);
  dp1.add_congruence((A %= 0) / 2);

  Product dp2(2);
  dp2.add_constraint(A <= 1);
  dp2.add_constraint(B >= 0);

  dp1.concatenate_assign(dp2);

  Product known_dp(4);
  known_dp.add_constraint(A >= 0);
  known_dp.add_congruence((A %= 0) / 2);
  known_dp.add_constraint(C <= 1);
  known_dp.add_constraint(D >= 0);

  bool ok = (dp1 == known_dp);

  print_congruences(dp1, "*** dp1 congruences ***");
  print_constraints(dp1, "*** dp1 constraints ***");
  print_congruences(dp2, "*** dp2 congruences ***");
  print_constraints(dp2, "*** dp2 constraints ***");

  return ok;
}

// remove_space_dimensions()
bool
test13() {
  Variable A(0);
  Variable C(2);
  Variable D(3);

  Product dp(4);
  dp.add_constraint(A >= 0);
  dp.add_congruence((A %= 0) / 2);
  dp.add_congruence((A - C %= 0) / 2);

  Variables_Set vars;
  vars.insert(C);
  vars.insert(D);

  dp.remove_space_dimensions(vars);

  Product known_dp(2);
  known_dp.add_constraint(A >= 0);
  known_dp.add_congruence((A %= 0) / 2);

  bool ok = (dp == known_dp);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp ***");

  return ok;
}

// remove_higher_space_dimensions()
bool
test14() {
  Variable A(0);
  Variable C(2);
  Variable D(3);

  Product dp(4);
  dp.add_constraint(A >= 0);
  dp.add_congruence((A %= 0) / 2);
  dp.add_congruence((A - C %= 0) / 2);

  dp.remove_higher_space_dimensions(2);

  Product known_dp(2);
  known_dp.add_constraint(A >= 0);
  known_dp.add_congruence((A %= 0) / 2);

  bool ok = (dp == known_dp);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// map_space_dimensions()
bool
test15() {
  Variable A(0);
  Variable B(1);

  Product dp(2);
  dp.add_constraint(A >= 0);
  dp.add_congruence((A - B %= 0) / 2);

  Partial_Function function;
  function.insert(0, 1);
  function.insert(1, 0);

  dp.map_space_dimensions(function);

  Product known_dp(2);
  known_dp.add_constraint(B >= 0);
  known_dp.add_congruence((B - A %= 0) / 2);

  bool ok = (dp == known_dp);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// expand_space_dimension()
bool
  test16() {
  Variable A(0);
  Variable B(1);
  Variable C(2);
  Variable D(3);

  Product dp(3);
  dp.add_congruence((A + B %= 2) / 7);
  dp.add_constraint(A >= 0);

  dp.expand_space_dimension(A, 1);

  Product known_dp(4);
  known_dp.add_congruence((A + B %= 2) / 7);
  known_dp.add_congruence((D + B %= 2) / 7);
  known_dp.add_constraint(A >= 0);
  known_dp.add_constraint(D >= 0);

  bool ok = (dp == known_dp);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// fold_space_dimensions()
bool
test17() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
  dp.add_congruence((A %= 2) / 7);
  dp.add_congruence((B %= 2) / 14);
  dp.add_congruence((C %= 2) / 21);
  dp.add_constraint(A <= 5);
  dp.add_constraint(B <= 10);
  dp.add_constraint(C <= 0);
  dp.add_constraint(C >= 0);

  Variables_Set to_fold;
  to_fold.insert(A);
  to_fold.insert(C);

  dp.fold_space_dimensions(to_fold, B);

  Product known_dp(1);
  known_dp.add_congruence((A %= 2) / 7);
  known_dp.add_constraint(A <= 10);

  bool ok = (dp == known_dp);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// time_elapse_assign(y)
bool
test18() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp1(3);
  dp1.add_constraint(A >= 0);
  dp1.add_constraint(B >= 0);
  dp1.add_constraint(A + B >= 3);
  dp1.add_constraint(2*A - B == 0);
  dp1.add_constraint(3*A + C == 0);
  dp1.add_congruence(3*A %= 0);

  Product dp2(3);
  dp2.add_constraint(7*C == 4);
  dp2.add_constraint(7*B == -1);
  dp2.add_constraint(7*A == 3);

  dp1.time_elapse_assign(dp2);

  Product known_dp(3);
  known_dp.add_constraint(5*A - 13*B - 7*C == 0);
  known_dp.add_constraint(3*A + C >= 0);
  known_dp.add_constraint(A + B >= 3);
  known_dp.add_constraint(4*A - 3*C >= 13);
  known_dp.add_congruence((65*A - B %= 0) / 7);
  known_dp.add_congruence(21*A %= 0);
  known_dp.add_constraint(A >= 0);

  bool ok = (dp1 == known_dp);

  print_congruences(dp1, "*** dp1.time_elapse_assign(dp1) congruences ***");
  print_constraints(dp1, "*** dp1.time_elapse_assign(dp1) constraints ***");
  print_congruences(dp2, "*** dp2.time_elapse_assign(dp2) congruences ***");
  print_constraints(dp2, "*** dp2.time_elapse_assign(dp2) constraints ***");

  return ok;
}

// topological_closure_assign
bool
test19() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp(3);
  dp.add_constraint(B >= 0);
  dp.add_constraint(3*A + C == 0);
  dp.add_constraint(2*A - B == 0);
  dp.add_congruence(3*A %= 0);
#if NNC_Poly_Class
  dp.add_constraint(A > 0);
#else
  dp.add_constraint(A >= 0);
#endif

#if !Box_Class
  dp.topological_closure_assign();
#endif

  Product known_dp(3);
  known_dp.add_constraint(B >= 0);
  known_dp.add_constraint(3*A + C == 0);
  known_dp.add_constraint(2*A - B == 0);
  known_dp.add_congruence(3*A %= 0);
  known_dp.add_constraint(A >= 0);

  bool ok = (dp.is_topologically_closed() && dp == known_dp);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  return ok;
}

// widening_assign
bool
test20() {
  Variable A(0);
  Variable B(1);
  Variable C(2);

  Product dp_prev(3);
  dp_prev.add_constraint(C == 0);
  dp_prev.add_constraint(A - B >= 1);
  dp_prev.add_constraint(A <= 2);
  dp_prev.add_constraint(B >= 0);
  dp_prev.add_congruence((B %= 0) / 2);
  dp_prev.add_congruence(3*A %= 0);

  print_congruences(dp_prev, "*** dp_prev congruences ***");
  print_constraints(dp_prev, "*** dp_prev constraints ***");

  Product dp(3);
  dp.add_constraint(C == 0);
  dp.add_constraint(A <= 2);
  dp.add_constraint(B >= 0);
  dp.add_constraint(2*A - B >= 2);
  dp.add_constraint(B >= 0);
  dp.add_congruence(6*A %= 0);
  dp.add_congruence((B %= 0) / 2);

  dp.upper_bound_assign(dp_prev);

  print_congruences(dp, "*** dp congruences ***");
  print_constraints(dp, "*** dp constraints ***");

  dp.widening_assign(dp_prev);

  Product known_dp(3);
  known_dp.add_constraint(C == 0);
  known_dp.add_constraint(A <= 2);
  known_dp.add_constraint(B >= 0);
  known_dp.add_congruence((B %= 0) / 2);

  bool ok = (dp == known_dp);

  print_congruences(dp, "*** dp.widening_assign(dp_prev) congruences ***");
  print_constraints(dp, "*** dp.widening_assign(dp_prev) constraints ***");

  return ok;
}

} // namespace

BEGIN_MAIN
  DO_TEST(test01);
  DO_TEST(test02);
  DO_TEST(test03);
  DO_TEST(test04);
#if 0
  DO_TEST(test05);
#endif
  DO_TEST(test06);
#if C_Poly_Class
  DO_TEST_F8A(test07);
#else
  DO_TEST(test07);
#endif
  DO_TEST(test08);
  DO_TEST(test09);
  DO_TEST(test10);
  DO_TEST(test11);
  DO_TEST(test12);
  DO_TEST(test13);
  DO_TEST(test14);
  DO_TEST(test15);
  DO_TEST(test16);
  DO_TEST(test17);
  DO_TEST_F8(test18);
//  DO_TEST(test19);
  DO_TEST(test20);
END_MAIN