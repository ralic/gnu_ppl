/* Grid class implementation: inline functions.
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

#ifndef PPL_Grid_inlines_hh
#define PPL_Grid_inlines_hh 1

#include "Grid_Generator.defs.hh"
#include "Grid_Generator_System.defs.hh"
#include "Grid_Generator_System.inlines.hh"
#include <algorithm>

namespace Parma_Polyhedra_Library {

inline dimension_type
Grid::max_space_dimension() {
  // One dimension is reserved to have a value of type dimension_type
  // that does not represent a legal dimension.
  return std::min(std::numeric_limits<dimension_type>::max() - 1,
		  std::min(Congruence_System::max_space_dimension(),
			   Grid_Generator_System::max_space_dimension()
			   )
		  );
}

inline void
Grid::set_congruences_up_to_date() {
  status.set_c_up_to_date();
}

inline
Grid::Grid(dimension_type num_dimensions,
	   const Degenerate_Element kind)
  : con_sys(),
    gen_sys(num_dimensions > max_space_dimension()
	    ? (throw_space_dimension_overflow("Grid(n, k)",
					      "n exceeds the maximum "
					      "allowed space dimension"),
	       0)
	    : num_dimensions) {
  construct(num_dimensions, kind);
  assert(OK());
}

inline
Grid::Grid(const Congruence_System& cgs)
  : con_sys(cgs.space_dimension() > max_space_dimension()
	    ? throw_space_dimension_overflow("Grid(cgs)",
					     "the space dimension of cgs "
					     "exceeds the maximum allowed "
					     "space dimension"), 0
	    : cgs.space_dimension()),
    gen_sys(cgs.space_dimension()) {
  Congruence_System cgs_copy(cgs);
  construct(cgs_copy);
}

inline
Grid::Grid(Congruence_System& cgs, Recycle_Input)
  : con_sys(cgs.space_dimension() > max_space_dimension()
	    ? throw_space_dimension_overflow("Grid(cgs, recycle)",
					     "the space dimension of cgs "
					     "exceeds the maximum allowed "
					     "space dimension"), 0
	    : cgs.space_dimension()),
    gen_sys(cgs.space_dimension()) {
  construct(cgs);
}

inline
Grid::Grid(const Grid_Generator_System& ggs)
  : con_sys(ggs.space_dimension() > max_space_dimension()
	    ? throw_space_dimension_overflow("Grid(ggs)",
					     "the space dimension of ggs "
					     "exceeds the maximum allowed "
					     "space dimension"), 0
	    : ggs.space_dimension()),
    gen_sys(ggs.space_dimension()) {
  Grid_Generator_System ggs_copy(ggs);
  construct(ggs_copy);
}

inline
Grid::Grid(Grid_Generator_System& ggs, Recycle_Input)
  : con_sys(ggs.space_dimension() > max_space_dimension()
	    ? throw_space_dimension_overflow("Grid(ggs, recycle)",
					     "the space dimension of ggs "
					     "exceeds the maximum allowed "
					     "space dimension"), 0
	    : ggs.space_dimension()),
    gen_sys(ggs.space_dimension()) {
  construct(ggs);
}

inline
Grid::Grid(const Generator_System& gs)
  : con_sys(),
    gen_sys(gs.space_dimension() > max_space_dimension()
	    ? throw_space_dimension_overflow("Grid(gs)",
					     "n exceeds the maximum "
					     "allowed space dimension"), 0
	    : gs.space_dimension()) {
  construct(gs.space_dimension(), UNIVERSE);
}

inline
Grid::Grid(Generator_System& gs, Recycle_Input)
  : con_sys(),
    gen_sys(gs.space_dimension() > max_space_dimension()
	    ? throw_space_dimension_overflow("Grid(gs, recycle)",
					     "n exceeds the maximum "
					     "allowed space dimension"), 0
	    : gs.space_dimension()) {
  construct(gs.space_dimension(), UNIVERSE);
}

inline
Grid::~Grid() {
}

inline dimension_type
Grid::space_dimension() const {
  return space_dim;
}

inline Generator_System
Grid::generators() const {
  Generator_System gs;
  // Trivially true point.
  gs.insert(point());
  // A line for each dimension.
  dimension_type dim = space_dimension();
  while (dim--)
    gs.insert(line(Variable(dim)));
  return gs;
}

inline Generator_System
Grid::minimized_generators() const {
  return generators();
}

inline void
Grid::add_generator(const Generator& g) const {
  used(g);
}

inline bool
Grid::add_generator_and_minimize(const Generator& g) const {
  used(g);
  return !is_empty();
}

inline memory_size_type
Grid::total_memory_in_bytes() const {
  return sizeof(*this) + external_memory_in_bytes();
}

inline int32_t
Grid::hash_code() const {
  return space_dimension() & 0x7fffffff;
}

inline Constraint_System
Grid::constraints() const {
  if (space_dimension() == 0)
    return is_universe() ? Constraint_System()
      : Constraint_System::zero_dim_empty();
  else
    return Constraint_System(congruences());;
}

inline Constraint_System
Grid::minimized_constraints() const {
  if (space_dimension() == 0)
    return is_universe() ? Constraint_System()
      : Constraint_System::zero_dim_empty();
  else
    return Constraint_System(minimized_congruences());;
}

inline void
Grid::upper_bound_assign(const Grid& y) {
  join_assign(y);
}

inline void
Grid::upper_bound_assign_and_minimize(const Grid& y) {
  join_assign_and_minimize(y);
}

inline bool
Grid::upper_bound_assign_if_exact(const Grid& y) {
  return join_assign_if_exact(y);
}

inline void
Grid::difference_assign(const Grid& y) {
  grid_difference_assign(y);
}

inline void
Grid::swap(Grid& y) {
  std::swap(con_sys, y.con_sys);
  std::swap(gen_sys, y.gen_sys);
  std::swap(status, y.status);
  std::swap(space_dim, y.space_dim);
  std::swap(dim_kinds, y.dim_kinds);
}

} // namespace Parma_Polyhedra_Library

/*! \relates Parma_Polyhedra_Library::Grid */
inline void
std::swap(Parma_Polyhedra_Library::Grid& x,
	  Parma_Polyhedra_Library::Grid& y) {
  x.swap(y);
}

namespace Parma_Polyhedra_Library {

inline bool
Grid::marked_empty() const {
  return status.test_empty();
}

inline bool
Grid::congruences_are_up_to_date() const {
  return status.test_c_up_to_date();
}

inline bool
Grid::generators_are_up_to_date() const {
  return status.test_g_up_to_date();
}

inline bool
Grid::congruences_are_minimized() const {
  return status.test_c_minimized();
}

inline bool
Grid::generators_are_minimized() const {
  return status.test_g_minimized();
}

inline void
Grid::set_generators_up_to_date() {
  status.set_g_up_to_date();
}

inline void
Grid::set_congruences_minimized() {
  set_congruences_up_to_date();
  status.set_c_minimized();
}

inline void
Grid::set_generators_minimized() {
  set_generators_up_to_date();
  status.set_g_minimized();
}

inline void
Grid::clear_empty() {
  status.reset_empty();
}

inline void
Grid::clear_congruences_minimized() {
  status.reset_c_minimized();
}

inline void
Grid::clear_generators_minimized() {
  status.reset_g_minimized();
}

inline void
Grid::clear_congruences_up_to_date() {
  clear_congruences_minimized();
  status.reset_c_up_to_date();
  // Can get rid of con_sys here.
}

inline void
Grid::clear_generators_up_to_date() {
  clear_generators_minimized();
  status.reset_g_up_to_date();
  // Can get rid of gen_sys here.
}

inline bool
Grid::bounds_from_above(const Linear_Expression& expr) const {
  return bounds(expr, "bounds_from_above(e)");
}

inline bool
Grid::bounds_from_below(const Linear_Expression& expr) const {
  return bounds(expr, "bounds_from_below(e)");
}

inline bool
Grid::maximize(const Linear_Expression& expr,
	       Coefficient& sup_n, Coefficient& sup_d, bool& maximum) const {
  return max_min(expr, "maximize(e, ...)", sup_n, sup_d, maximum);
}

inline bool
Grid::maximize(const Linear_Expression& expr,
	       Coefficient& sup_n, Coefficient& sup_d, bool& maximum,
	       Grid_Generator& point) const {
  return max_min(expr, "maximize(e, ...)", sup_n, sup_d, maximum, &point);
}

inline bool
Grid::minimize(const Linear_Expression& expr,
	       Coefficient& inf_n, Coefficient& inf_d, bool& minimum) const {
  return max_min(expr, "minimize(e, ...)", inf_n, inf_d, minimum);
}

inline bool
Grid::minimize(const Linear_Expression& expr,
	       Coefficient& inf_n, Coefficient& inf_d, bool& minimum,
	       Grid_Generator& point) const {
  return max_min(expr, "minimize(e, ...)", inf_n, inf_d, minimum, &point);
}

inline void
Grid::normalize_divisors(Grid_Generator_System& sys) {
  TEMP_INTEGER(divisor);
  divisor = 1;
  normalize_divisors(sys, divisor);
}

/*! \relates Grid */
inline bool
operator!=(const Grid& x, const Grid& y) {
  return !(x == y);
}

inline bool
Grid::strictly_contains(const Grid& y) const {
  const Grid& x = *this;
  return x.contains(y) && !y.contains(x);
}

inline void
Grid::topological_closure_assign() {
  return;
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Grid_inlines_hh)
