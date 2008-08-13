(* FIXME: to be written.
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
site: http://www.cs.unipr.it/ppl/ . *)

open Ppl_ocaml
open Printf
open Gmp

let rec print_linear_expression = function
    Variable v ->
      print_string "V(";
      print_int v;
      print_string ")";
  | Coefficient c ->
      print_int(Z.to_int c)
  | Unary_Minus e ->
      print_string "-(";
      print_linear_expression e;
      print_string ")";
  | Unary_Plus e ->
      print_linear_expression e
  | Plus (e1, e2) ->
      print_string "(";
      print_linear_expression e1;
      print_string " + ";
      print_linear_expression e2;
      print_string ")";
  | Minus (e1, e2) ->
      print_string "(";
      print_linear_expression e1;
      print_string " - ";
      print_linear_expression e2;
      print_string ")";
  | Times (c, e) ->
      print_int(Z.to_int c);
      print_string "*(";
      print_linear_expression e;
      print_string ")";
;;

let rec print_constraints = function
    Less_Than (le1, le2) ->
      print_linear_expression le1;
      print_string " < ";
      print_linear_expression le2;
  | Less_Or_Equal (le1, le2) ->
      print_linear_expression le1;
      print_string " <= ";
      print_linear_expression le2;
  | Equal (le1, le2) ->
      print_linear_expression le1;
      print_string " == ";
      print_linear_expression le2;
  | Greater_Than (le1, le2) ->
      print_linear_expression le1;
      print_string " > ";
      print_linear_expression le2;
  | Greater_Or_Equal (le1, le2) ->
      print_linear_expression le1;
      print_string " >= ";
      print_linear_expression le2;
;;

let rec print_generator = function
    Ray (le1) ->
      print_string "Ray: ";
      print_linear_expression le1;
      print_newline();
  |  Line (le1) ->
      print_string "Line: ";
      print_linear_expression le1;
      print_newline();
  | Point (le1, c) ->
      print_string "Point: ";
      print_linear_expression le1;
      print_string " den: ";
      print_int(Z.to_int c);
      print_newline();
| Closure_Point (le1, c) ->
      print_string "Closure_Point: ";
      print_linear_expression le1;
      print_string " den: ";
      print_int(Z.to_int c);
      print_newline();;

let print_congruence = function x,y,z ->
   print_linear_expression x;
  print_string " %= ";
  print_linear_expression y;
  print_string " mod ";
  print_int(Z.to_int z);
  print_newline();;


(* Build linear expressions the hard way. *)

print_string "Build linear expressions manually:\n" ;;

let rec a = Variable 0
and b = Variable 1
and c = Variable 2
and n = Coefficient (Z.from_int 3)
and e1 = Plus (c, c)
and e2 = Times ((Z.from_int 7), a)
and e3 = Plus (n, c)
;;

print_linear_expression a; print_string "\n" ;;
print_linear_expression b; print_string "\n" ;;
print_linear_expression c; print_string "\n" ;;
print_linear_expression n; print_string "\n" ;;
print_linear_expression e1; print_string "\n" ;;
print_linear_expression e2; print_string "\n" ;;

(* See whether operators can make life better. *)

print_string "Build linear expressions with operators:\n" ;;

let linear_expression_of_int n = Coefficient (Z.of_int n) ;;
let linear_expression_plus e1 e2 = Plus (e1, e2) ;;
let linear_expression_minus e1 e2 = Minus (e1, e2) ;;
let linear_expression_times c e = Times (c, e) ;;
let linear_constraint_eq e1 e2 = Equal (e1, e2) ;;
let linear_constraint_lt e1 e2 = Less_Than (e1, e2) ;;
let linear_constraint_gt e1 e2 = Greater_Than (e1, e2) ;;
let linear_constraint_le e1 e2 = Less_Or_Equal (e1, e2) ;;
let linear_constraint_ge e1 e2 = Greater_Or_Equal (e1, e2) ;;

let ( +/ ) = linear_expression_plus
let ( -/ ) = linear_expression_minus
let ( */ ) = linear_expression_times
let ( =/ ) = linear_constraint_eq
let ( </ ) = linear_constraint_lt
let ( >/ ) = linear_constraint_gt
let ( <=/ ) = linear_constraint_le
let ( >=/ ) = linear_constraint_ge

let e3 =
  (Z.of_int 3) */ a
  +/
  (Z.of_int 4) */ b
  -/
  (linear_expression_of_int 7)
;;

print_linear_expression e3; print_string "\n" ;;

(* Probably the most convenient thing for the user will be to use the
   the Camlp4 preprocessor: see
   http://caml.inria.fr/pub/docs/manual-ocaml/manual003.html#htoc10 *)

(* Build a PPL::Linear_Expression out of an OCaml linear_expression. *)

print_string "Build and print the corresponding PPL::Linear_Expression:\n" ;;

test_linear_expression e3 ;;

(* Build a PPL::Constraint out of an OCaml linear_constraint. *)

print_string "Build and print a PPL::Constraint:\n" ;;

test_linear_constraint (e3 >/ e1) ;;

(* Build a PPL::Generator out of an OCaml linear_generator. *)

print_string "Build and print a PPL::Generator:\n" ;;

test_linear_generator (Ray e3) ;;

(* Build a PPL::Constraint_System out of an OCaml constraint_system. *)

print_string "Build and print a PPL::Constraint_System:\n" ;;

test_constraint_system [e3 >/ e1; e1 >/ e2; e1 <=/ e2 -/ n] ;;

(* Build a PPL::Generator_System out of an OCaml generator_system. *)

print_string "Build and print a PPL::Generator_System:\n" ;;

test_generator_system [(Ray e3); (Line e1); (Closure_Point (e2, (Z.from_int 5)))] ;;

(* Build some PPL::C_Polyhedron. *)

for i = 6 downto 0 do
  let ph = ppl_new_C_Polyhedron_from_space_dimension i Empty
  in let dimension =  ppl_C_Polyhedron_space_dimension(ph)
  in printf "dimension %d\n" dimension
done;;
print_newline();;

let cs = [e3 >=/ e1; e1 >=/ e2; e1 <=/ e2 -/ n] ;;
let gs1 = [Point (e2, (Z.from_int 1)); Point (e1, (Z.from_int 2))] ;;

let cong = (e2, e2 , (Z.from_int 1));;
let cgs = [e3, e2 , (Z.from_int 20)];;
let ph =  ppl_new_MIP_Problem 10 cs e3 Maximization;;
let objective_func = ppl_MIP_Problem_objective_function ph;;
print_linear_expression objective_func;;
let i = ppl_MIP_Problem_space_dimension ph;;
print_int i;;
let i = ppl_MIP_Problem_constraints ph;;
print_newline();;
let ph = ppl_new_C_Polyhedron_from_constraints(cs);;
let result =  ppl_C_Polyhedron_bounds_from_above ph e2;;
ppl_C_Polyhedron_add_constraint ph (e2 >=/ e2);;
let ph2 = ppl_new_C_Polyhedron_from_generators(gs1);;
let b = ppl_C_Polyhedron_is_disjoint_from_C_Polyhedron ph ph2;;
ppl_C_Polyhedron_concatenate_assign ph ph2;;
let constr = ppl_C_Polyhedron_get_congruences ph in
List.iter print_congruence constr;;
ppl_C_Polyhedron_bounded_affine_preimage ph 1 e1 e2 (Z.from_int 10);;
ppl_C_Polyhedron_bounded_affine_preimage ph 1 e1 e2 (Z.from_int 10);;
ppl_C_Polyhedron_affine_image ph 1 e1 (Z.from_int 10);;
let a = ppl_C_Polyhedron_limited_BHRZ03_extrapolation_assign_with_tokens ph ph cs 10;;
let b = ppl_C_Polyhedron_bounded_BHRZ03_extrapolation_assign_with_tokens ph ph cs 10;;
let b = ppl_C_Polyhedron_bounded_H79_extrapolation_assign_with_tokens ph ph cs 10;;
 ppl_C_Polyhedron_H79_widening_assign ph ;;
print_int b;;
let b = ppl_C_Polyhedron_OK ph;;
ppl_C_Polyhedron_generalized_affine_preimage_lhs_rhs ph e1 Equal_RS e1;;
ppl_C_Polyhedron_generalized_affine_image ph 1 Equal_RS e2 (Z.from_int 10);;
let is_bounded, num, den, is_supremum, gen = ppl_C_Polyhedron_minimize ph e3;;
let dimensions_to_remove = [3;0];;
ppl_C_Polyhedron_remove_space_dimensions ph dimensions_to_remove;;
let dimensions_to_fold = [1];;
ppl_C_Polyhedron_fold_space_dimensions ph dimensions_to_fold 0;;
let dimensions_to_map = [(0,1);(1,2);(2,0);];;
let i = ppl_C_Polyhedron_space_dimension ph;;
print_string "Space dimension is: ";
print_int i;;
print_string "\n";;
ppl_C_Polyhedron_map_space_dimensions ph dimensions_to_map;;
(* Pointset_Powersed_Grid is not enabled by default, the following code is *)
(* commented *)
(* let pps = ppl_new_Pointset_Powerset_Grid_from_space_dimension 3;; *)
(* let space_dim = ppl_Pointset_Powerset_Grid_space_dimension pps;; *)
(* ppl_Pointset_Powerset_Grid_add_constraints  pps cs;; *)
(* let caml_grid_it = ppl_Pointset_Powerset_Grid_begin_iterator pps;; *)
(* let grid1 =  ppl_Pointset_Powerset_Grid_iterator_get_disjunct caml_grid_it;; *)
(* let space_dim = ppl_Grid_space_dimension grid1;; *)
(* let grid2 = ppl_new_Grid_from_space_dimension 3;; *)
(* ppl_Pointset_Powerset_Grid_add_disjunct pps grid2;; *)
(* let space_dim = ppl_Pointset_Powerset_Grid_space_dimension pps;; *)
(* let caml_grid_it1 = ppl_Pointset_Powerset_Grid_end_iterator pps;; *)
(* let caml_grid_it2 = ppl_Pointset_Powerset_Grid_end_iterator pps;; *)
(* ppl_Pointset_Powerset_Grid_iterator_decrement caml_grid_it1;; *)
(* ppl_Pointset_Powerset_Grid_drop_disjunct pps caml_grid_it1;; *)
(* ppl_Pointset_Powerset_Grid_iterator_equals_iterator caml_grid_it1 caml_grid_it1;; *)
(* print_int space_dim;; *)
(* print_newline();; *)
(* print_string "PPS size : ";; *)
(* let size = ppl_Pointset_Powerset_Grid_size pps;; *)
(* print_int size;; *)
print_newline();
print_string "Testing minimization";
print_newline();
print_string "Value ";
print_int(Z.to_int num);
print_string "/";
print_int(Z.to_int den);
print_newline();
print_string (string_of_bool is_bounded);
print_newline();
print_string (string_of_bool is_supremum);
print_newline();
print_generator(gen);
print_newline();
ppl_C_Polyhedron_swap ph ph2;
at_exit Gc.full_major;;
print_string "Bye!\n"