/* Partially_Reduced_Product class implementation: inline functions.
   Copyright (C) 2001-2007 Roberto Bagnara <bagnara@cs.unipr.it>

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

#ifndef PPL_Partially_Reduced_Product_inlines_hh
#define PPL_Partially_Reduced_Product_inlines_hh 1

#include "compiler.hh"

namespace Parma_Polyhedra_Library {

template <typename D1, typename D2, typename R>
inline dimension_type
Partially_Reduced_Product<D1, D2, R>::max_space_dimension() {
  return std::min(D1::max_space_dimension(), D2::max_space_dimension());
}

template <typename D1, typename D2, typename R>
inline
Partially_Reduced_Product<D1, D2, R>::Partially_Reduced_Product(dimension_type num_dimensions,
				       const Degenerate_Element kind)
  : d1(num_dimensions, kind), d2(num_dimensions, kind) {
  set_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline
Partially_Reduced_Product<D1, D2, R>::Partially_Reduced_Product(const Congruence_System& ccgs)
  : d1(ccgs), d2(ccgs) {
  set_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline
Partially_Reduced_Product<D1, D2, R>::Partially_Reduced_Product(Congruence_System& cgs)
  : d1(const_cast<const Congruence_System&>(cgs)), d2(cgs) {
  set_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline
Partially_Reduced_Product<D1, D2, R>::Partially_Reduced_Product(const Constraint_System& ccs)
  : d1(ccs), d2(ccs) {
  set_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline
Partially_Reduced_Product<D1, D2, R>::Partially_Reduced_Product(Constraint_System& cs)
  : d1(const_cast<const Constraint_System&>(cs)), d2(cs) {
  set_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline
Partially_Reduced_Product<D1, D2, R>::Partially_Reduced_Product(const Generator_System& gs)
  : d1(gs), d2(gs) {
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline
Partially_Reduced_Product<D1, D2, R>::Partially_Reduced_Product(Generator_System& gs)
  : d1(gs), d2(gs) {
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
template <typename Interval>
inline
Partially_Reduced_Product<D1, D2, R>::Partially_Reduced_Product(const Box<Interval>& box)
  : d1(box), d2(box) {
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline
Partially_Reduced_Product<D1, D2, R>::Partially_Reduced_Product(const Partially_Reduced_Product& y)
  : d1(y.d1), d2(y.d2) {
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline
Partially_Reduced_Product<D1, D2, R>::~Partially_Reduced_Product() {
}

template <typename D1, typename D2, typename R>
inline memory_size_type
Partially_Reduced_Product<D1, D2, R>::external_memory_in_bytes() const {
  return d1.external_memory_in_bytes() + d2.external_memory_in_bytes();
}

template <typename D1, typename D2, typename R>
inline memory_size_type
Partially_Reduced_Product<D1, D2, R>::total_memory_in_bytes() const {
  return sizeof(*this) + external_memory_in_bytes();
}

template <typename D1, typename D2, typename R>
inline dimension_type
Partially_Reduced_Product<D1, D2, R>::space_dimension() const {
  assert(d1.space_dimension() == d2.space_dimension());
  return d1.space_dimension();
}

template <typename D1, typename D2, typename R>
inline dimension_type
Partially_Reduced_Product<D1, D2, R>::affine_dimension() const {
  reduce();
  const dimension_type d1_dim = d1.affine_dimension();
  const dimension_type d2_dim = d2.affine_dimension();
  return std::min(d1_dim, d2_dim);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::intersection_assign(const Partially_Reduced_Product& y) {
  d1.intersection_assign(y.d1);
  d2.intersection_assign(y.d2);
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::difference_assign(const Partially_Reduced_Product& y) {
  d1.difference_assign(y.d1);
  d2.difference_assign(y.d2);
  // FIXME: check this.
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::upper_bound_assign(const Partially_Reduced_Product& y) {
  d1.upper_bound_assign(y.d1);
  d2.upper_bound_assign(y.d2);
  // FIXME: can we do better than this?
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::upper_bound_assign_if_exact(const Partially_Reduced_Product& y) {
  return d1.upper_bound_assign_if_exact(y.d1)
    || d2.upper_bound_assign_if_exact(y.d2);
  // FIXME: can we do better than this?
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::affine_image(Variable var,
	       const Linear_Expression& expr,
	       Coefficient_traits::const_reference denominator) {
  d1.affine_image(var, expr, denominator);
  d2.affine_image(var, expr, denominator);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::affine_preimage(Variable var,
		  const Linear_Expression& expr,
		  Coefficient_traits::const_reference denominator) {
  d1.affine_preimage(var, expr, denominator);
  d2.affine_preimage(var, expr, denominator);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::generalized_affine_image(Variable var,
			   const Relation_Symbol relsym,
			   const Linear_Expression& expr,
			   Coefficient_traits::const_reference denominator) {
  d1.generalized_affine_image(var, relsym, expr, denominator);
  d2.generalized_affine_image(var, relsym, expr, denominator);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::generalized_affine_preimage(Variable var,
			      const Relation_Symbol relsym,
			      const Linear_Expression& expr,
			      Coefficient_traits::const_reference denominator) {
  d1.generalized_affine_preimage(var, relsym, expr, denominator);
  d2.generalized_affine_preimage(var, relsym, expr, denominator);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::generalized_affine_image(const Linear_Expression& lhs,
			   const Relation_Symbol relsym,
			   const Linear_Expression& rhs) {
  d1.generalized_affine_image(lhs, relsym, rhs);
  d2.generalized_affine_image(lhs, relsym, rhs);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::generalized_affine_preimage(const Linear_Expression& lhs,
			      const Relation_Symbol relsym,
			      const Linear_Expression& rhs) {
  d1.generalized_affine_preimage(lhs, relsym, rhs);
  d2.generalized_affine_preimage(lhs, relsym, rhs);
}


template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::bounded_affine_image(Variable var,
			       const Linear_Expression& lb_expr,
			       const Linear_Expression& ub_expr,
			       Coefficient_traits::const_reference denominator) {
  d1.bounded_affine_image(var, lb_expr, ub_expr, denominator);
  d2.bounded_affine_image(var, lb_expr, ub_expr, denominator);
  // FIXME: check this.
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::bounded_affine_preimage(Variable var,
			       const Linear_Expression& lb_expr,
			       const Linear_Expression& ub_expr,
			       Coefficient_traits::const_reference denominator) {
  d1.bounded_affine_preimage(var, lb_expr, ub_expr, denominator);
  d2.bounded_affine_preimage(var, lb_expr, ub_expr, denominator);
  // FIXME: check this.
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::time_elapse_assign(const Partially_Reduced_Product& y) {
  d1.time_elapse_assign(y.d1);
  d2.time_elapse_assign(y.d2);
  // FIXME: check this.
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::topological_closure_assign() {
  d1.topological_closure_assign();
  d2.topological_closure_assign();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::swap(Partially_Reduced_Product& y) {
  std::swap(d1, y.d1);
  std::swap(d2, y.d2);
  std::swap(reduced, y.reduced);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_constraint(const Constraint& c) {
  d1.add_constraint(c);
  d2.add_constraint(c);
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_congruence(const Congruence& cg) {
  d1.add_congruence(cg);
  d2.add_congruence(cg);
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_generator(const Generator& g) {
  d1.add_generator(g);
  d2.add_generator(g);
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::add_generator_and_minimize(const Generator& g) {
  bool empty = d1.add_generator_and_minimize(g);
  return d2.add_generator_and_minimize(g) || empty;
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_grid_generator(const Grid_Generator& g) {
  d1.add_grid_generator(g);
  d2.add_grid_generator(g);
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>
::add_grid_generator_and_minimize(const Grid_Generator& g) {
  bool empty = d1.add_grid_generator_and_minimize(g);
  return d2.add_grid_generator_and_minimize(g) || empty;
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_constraints(const Constraint_System& cs) {
  d1.add_constraints(cs);
  d2.add_constraints(cs);
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_recycled_constraints(Constraint_System& cs) {
  d1.add_recycled_constraints(cs);
  d2.add_recycled_constraints(cs);
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>
::add_constraints_and_minimize(const Constraint_System& cs) {
  bool empty = d1.add_constraints_and_minimize(cs);
  return d2.add_constraints_and_minimize(cs) || empty;
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>
::add_recycled_constraints_and_minimize(Constraint_System& cs) {
  bool empty = d1.add_recycled_constraints_and_minimize(cs);
  return d2.add_recycled_constraints_and_minimize(cs) || empty;
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_congruences(const Congruence_System& cgs) {
  d1.add_congruences(cgs);
  d2.add_congruences(cgs);
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_generators(const Generator_System& gs) {
  d1.add_generators(gs);
  d2.add_generators(gs);
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_grid_generators(const Grid_Generator_System& gs) {
  d1.add_grid_generators(gs);
  d2.add_grid_generators(gs);
  clear_reduced_flag();
}

template <typename D1, typename D2, typename R>
inline Partially_Reduced_Product<D1, D2, R>&
Partially_Reduced_Product<D1, D2, R>::operator=(const Partially_Reduced_Product& y) {
  d1 = y.d1;
  d2 = y.d2;
  reduced = y.reduced;
  return *this;
}

template <typename D1, typename D2, typename R>
inline const D1&
Partially_Reduced_Product<D1, D2, R>::domain1() const {
  Partially_Reduced_Product& dp = const_cast<Partially_Reduced_Product&>(*this);  dp.reduce();
  return dp.d1;
}

template <typename D1, typename D2, typename R>
inline const D2&
Partially_Reduced_Product<D1, D2, R>::domain2() const {
  reduce();
  return d2;
}

template <typename D1, typename D2, typename R>
inline Generator_System
Partially_Reduced_Product<D1, D2, R>::generators() const {
  reduce();
  Generator_System gs = d2.generators();
  const Generator_System& gs1 = d1.generators();
  for (Generator_System::const_iterator i = gs1.begin(),
	 gs_end = gs1.end(); i != gs_end; ++i)
    gs.insert(*i);
  return gs;
}

template <typename D1, typename D2, typename R>
inline Generator_System
Partially_Reduced_Product<D1, D2, R>::minimized_generators() const {
  reduce();
  Generator_System gs = d2.generators();
  const Generator_System& gs1 = d1.generators();
  for (Generator_System::const_iterator i = gs1.begin(),
	 gs_end = gs1.end(); i != gs_end; ++i)
    gs.insert(*i);
  NNC_Polyhedron ph(gs);
  return ph.minimized_generators();
}

template <typename D1, typename D2, typename R>
inline Grid_Generator_System
Partially_Reduced_Product<D1, D2, R>::grid_generators() const {
  reduce();
  Grid_Generator_System gs = d2.grid_generators();
  const Grid_Generator_System& gs1 = d1.grid_generators();
  for (Grid_Generator_System::const_iterator i = gs1.begin(),
	 gs_end = gs1.end(); i != gs_end; ++i)
    gs.insert(*i);
  return gs;
}

template <typename D1, typename D2, typename R>
inline Grid_Generator_System
Partially_Reduced_Product<D1, D2, R>::minimized_grid_generators() const {
  reduce();
  Grid_Generator_System gs = d2.grid_generators();
  const Grid_Generator_System& gs1 = d1.grid_generators();
  for (Grid_Generator_System::const_iterator i = gs1.begin(),
	 gs_end = gs1.end(); i != gs_end; ++i)
    gs.insert(*i);
  Grid gr(gs);
  return gr.minimized_grid_generators();
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::is_empty() const {
  return d1.is_empty() || d2.is_empty();
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::is_universe() const {
  return d1.is_universe() && d2.is_universe();
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::is_topologically_closed() const {
  return d1.is_topologically_closed() && d2.is_topologically_closed();
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::is_disjoint_from(const Partially_Reduced_Product& y) const {
  return d1.is_disjoint_from(y.d1) || d2.is_disjoint_from(y.d2);
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::is_discrete() const {
  return d1.is_discrete() || d2.is_discrete();
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::is_bounded() const {
  return d1.is_bounded() || d2.is_bounded();
 }

template <typename D1, typename D2, typename R>
inline bool
  Partially_Reduced_Product<D1, D2, R>::bounds_from_above(
                                        const Linear_Expression& expr) const {
  return d1.bounds_from_above(expr) || d2.bounds_from_above(expr);
 }

template <typename D1, typename D2, typename R>
inline bool
  Partially_Reduced_Product<D1, D2, R>::bounds_from_below(
                                        const Linear_Expression& expr) const {
  return d1.bounds_from_below(expr) || d2.bounds_from_below(expr);
 }

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::widening_assign(const Partially_Reduced_Product& y,
					unsigned* tp) {
  d1.widening_assign(y.d1, tp);
  d2.widening_assign(y.d2, tp);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_space_dimensions_and_embed(dimension_type m) {
  d1.add_space_dimensions_and_embed(m);
  d2.add_space_dimensions_and_embed(m);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::add_space_dimensions_and_project(dimension_type m) {
  d1.add_space_dimensions_and_project(m);
  d2.add_space_dimensions_and_project(m);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::concatenate_assign(const Partially_Reduced_Product& y) {
  d1.concatenate_assign(y.d1);
  d2.concatenate_assign(y.d2);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::remove_space_dimensions(const Variables_Set& to_be_removed) {
  d1.remove_space_dimensions(to_be_removed);
  d2.remove_space_dimensions(to_be_removed);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::remove_higher_space_dimensions(dimension_type new_dimension) {
  d1.remove_higher_space_dimensions(new_dimension);
  d2.remove_higher_space_dimensions(new_dimension);
}

template <typename D1, typename D2, typename R>
template <typename Partial_Function>
inline void
Partially_Reduced_Product<D1, D2, R>::map_space_dimensions(const Partial_Function& pfunc) {
  d1.map_space_dimensions(pfunc);
  d2.map_space_dimensions(pfunc);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::expand_space_dimension(Variable var, dimension_type m) {
  d1.expand_space_dimension(var, m);
  d2.expand_space_dimension(var, m);
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>
::fold_space_dimensions(const Variables_Set& to_be_folded,
			Variable var) {
  d1.fold_space_dimensions(to_be_folded, var);
  d2.fold_space_dimensions(to_be_folded, var);
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::contains(const Partially_Reduced_Product& y) const {
  reduce();
  y.reduce();
  return d1.contains(y.d1) && d2.contains(y.d2);
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::strictly_contains(const Partially_Reduced_Product& y) const {
  reduce();
  y.reduce();
  return (d1.contains(y.d1) && d2.strictly_contains(y.d2))
    || (d2.contains(y.d2) && d1.strictly_contains(y.d1));
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::reduce() const {
  Partially_Reduced_Product& dp = const_cast<Partially_Reduced_Product&>(*this);
  if (dp.is_reduced())
    return false;
  R r;
  r.product_reduce(dp.d1, dp.d2);
  set_reduced_flag();
  return true;
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::is_reduced() const {
  return reduced;
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::clear_reduced_flag() const {
  const_cast<Partially_Reduced_Product&>(*this).reduced = false;
}

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::set_reduced_flag() const {
  const_cast<Partially_Reduced_Product&>(*this).reduced = true;
}

  // FIXME: Improve this name.
PPL_OUTPUT_3_PARAM_TEMPLATE_DEFINITIONS(D1, D2, R, Partially_Reduced_Product)

template <typename D1, typename D2, typename R>
inline void
Partially_Reduced_Product<D1, D2, R>::ascii_dump(std::ostream& s) const {
  s << "Domain 1:\n";
  d1.ascii_dump(s);
  s << "Domain 2:\n";
  d2.ascii_dump(s);
}

template <typename D1, typename D2, typename R>
inline bool
Partially_Reduced_Product<D1, D2, R>::OK() const {
  return d1.OK() && d2.OK();
}

/*! \relates Parma_Polyhedra_Library::Partially_Reduced_Product */
template <typename D1, typename D2, typename R>
inline bool
operator==(const Partially_Reduced_Product<D1, D2, R>& x,
	   const Partially_Reduced_Product<D1, D2, R>& y) {
  x.reduce();
  y.reduce();
  return x.d1 == y.d1 && x.d2 == y.d2;
}

/*! \relates Parma_Polyhedra_Library::Partially_Reduced_Product */
template <typename D1, typename D2, typename R>
inline bool
operator!=(const Partially_Reduced_Product<D1, D2, R>& x,
	   const Partially_Reduced_Product<D1, D2, R>& y) {
  return !(x == y);
}

/*! \relates Parma_Polyhedra_Library::Partially_Reduced_Product */
template <typename D1, typename D2, typename R>
inline std::ostream&
IO_Operators::operator<<(std::ostream& s, const Partially_Reduced_Product<D1, D2, R>& pd) {
  return s << "Domain 1:\n"
	   << pd.d1
	   << "Domain 2:\n"
	   << pd.d2;
}

} // namespace Parma_Polyhedra_Library

namespace Parma_Polyhedra_Library {

template <typename D1, typename D2>
inline
No_Reduction<D1, D2>::No_Reduction() {
}

template <typename D1, typename D2>
void No_Reduction<D1, D2>::product_reduce(D1&, D2&) {
}

template <typename D1, typename D2>
inline
No_Reduction<D1, D2>::~No_Reduction() {
}

template <typename D1, typename D2>
inline
Constraints_Reduction<D1, D2>::Constraints_Reduction() {
}

template <typename D1, typename D2>
void Constraints_Reduction<D1, D2>::product_reduce(D1& d1, D2& d2) {
  d1.add_constraints(d2.minimized_constraints());
  d2.add_constraints(d1.minimized_constraints());
}

template <typename D1, typename D2>
inline
Constraints_Reduction<D1, D2>::~Constraints_Reduction() {
}

} // namespace Parma_Polyhedra_Library

/*! \relates Parma_Polyhedra_Library::Partially_Reduced_Product */
template <typename D1, typename D2, typename R>
inline void
std::swap(Parma_Polyhedra_Library::Partially_Reduced_Product<D1, D2, R>& x,
	  Parma_Polyhedra_Library::Partially_Reduced_Product<D1, D2, R>& y) {
  x.swap(y);
}

#endif // !defined(PPL_Partially_Reduced_Product_inlines_hh)