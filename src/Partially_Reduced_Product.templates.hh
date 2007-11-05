/* Partially_Reduced_Product class implementation:
   non-inline template functions.
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

#ifndef PPL_Partially_Reduced_Product_templates_hh
#define PPL_Partially_Reduced_Product_templates_hh 1

#include "Grid_Generator.defs.hh"
#include "Grid_Generator_System.defs.hh"
#include "Grid_Generator_System.inlines.hh"
#include <algorithm>
#include <deque>

namespace Parma_Polyhedra_Library {

  template <typename D1, typename D2, typename R>
Constraint_System
Partially_Reduced_Product<D1, D2, R>::constraints() const {
  reduce();
  Constraint_System cs = d2.constraints();
  const Constraint_System& cs1 = d1.constraints();
  for (Constraint_System::const_iterator i = cs1.begin(),
	 cs_end = cs1.end(); i != cs_end; ++i)
    cs.insert(*i);
  return cs;
}

template <typename D1, typename D2, typename R>
Constraint_System
Partially_Reduced_Product<D1, D2, R>::minimized_constraints() const {
  reduce();
  Constraint_System cs = d2.constraints();
  const Constraint_System& cs1 = d1.constraints();
  for (Constraint_System::const_iterator i = cs1.begin(),
	 cs_end = cs1.end(); i != cs_end; ++i)
    cs.insert(*i);
  if (cs.has_strict_inequalities()) {
    NNC_Polyhedron ph(cs);
    return ph.minimized_constraints();
  }
  else {
    C_Polyhedron ph(cs);
    return ph.minimized_constraints();
  }
}

template <typename D1, typename D2, typename R>
Congruence_System
Partially_Reduced_Product<D1, D2, R>::congruences() const {
  reduce();
  Congruence_System cgs = d2.congruences();
  const Congruence_System& cgs1 = d1.congruences();
  for (Congruence_System::const_iterator i = cgs1.begin(),
	 cgs_end = cgs1.end(); i != cgs_end; ++i)
    cgs.insert(*i);
  return cgs;
}

template <typename D1, typename D2, typename R>
Congruence_System
Partially_Reduced_Product<D1, D2, R>::minimized_congruences() const {
  reduce();
  Congruence_System cgs = d2.congruences();
  const Congruence_System& cgs1 = d1.congruences();
  for (Congruence_System::const_iterator i = cgs1.begin(),
	 cgs_end = cgs1.end(); i != cgs_end; ++i)
    cgs.insert(*i);
  Grid gr(cgs);
  return gr.minimized_congruences();
}

template <typename D1, typename D2, typename R>
Poly_Gen_Relation
Partially_Reduced_Product<D1, D2, R>::relation_with(const Generator& g) const {
  reduce();
  if (Poly_Gen_Relation::nothing() == d1.relation_with(g)
      || Poly_Gen_Relation::nothing() == d2.relation_with(g))
    return Poly_Gen_Relation::nothing();
  else
    return Poly_Gen_Relation::subsumes();
}

template <typename D1, typename D2, typename R>
Poly_Con_Relation
Partially_Reduced_Product<D1, D2, R>::relation_with(const Constraint& c) const {

  reduce();
  Poly_Con_Relation relation1 = d1.relation_with(c);
  Poly_Con_Relation relation2 = d2.relation_with(c);

  Poly_Con_Relation result = Poly_Con_Relation::nothing();

  if (relation1.implies(Poly_Con_Relation::is_included()))
    result = result && Poly_Con_Relation::is_included();
  else if (relation2.implies(Poly_Con_Relation::is_included()))
    result = result && Poly_Con_Relation::is_included();
  if (relation1.implies(Poly_Con_Relation::saturates()))
    result = result && Poly_Con_Relation::saturates();
  else if (relation2.implies(Poly_Con_Relation::saturates()))
    result = result && Poly_Con_Relation::saturates();
  if (relation1.implies(Poly_Con_Relation::is_disjoint()))
    result = result && Poly_Con_Relation::is_disjoint();
  else if (relation2.implies(Poly_Con_Relation::is_disjoint()))
    result = result && Poly_Con_Relation::is_disjoint();

  return result;
}

template <typename D1, typename D2, typename R>
bool
  Partially_Reduced_Product<D1, D2, R>::maximize(const Linear_Expression& expr,
				   Coefficient& sup_n,
                                   Coefficient& sup_d,
                                   bool& maximum) const {
  reduce();
  if (is_empty())
    return false;
  Coefficient sup1_n;
  Coefficient sup1_d;
  Coefficient sup2_n;
  Coefficient sup2_d;
  bool maximum1;
  bool maximum2;
  bool r1 = d1.maximize(expr, sup1_n, sup1_d, maximum1);
  bool r2 = d2.maximize(expr, sup2_n, sup2_d, maximum2);
  // If neither is bounded from above, return false.
  if (!r1 && !r2)
    return false;
  // If only d2 is bounded from above, then use the values for d2.
  if (!r1) {
    sup_n = sup2_n;
    sup_d = sup2_d;
    maximum = maximum2;
    return true;
  }
  // If only d1 is bounded from above, then use the values for d1.
  if (!r2) {
    sup_n = sup1_n;
    sup_d = sup1_d;
    maximum = maximum1;
    return true;
  }
  // If both d1 and d2 are bounded from above, then use the minimum values.
  if (sup2_d * sup1_n >= sup1_d * sup2_n) {
    sup_n = sup1_n;
    sup_d = sup1_d;
    maximum = maximum1;
  }
  else {
    sup_n = sup2_n;
    sup_d = sup2_d;
    maximum = maximum2;
  }
  return true;
 }

template <typename D1, typename D2, typename R>
bool
  Partially_Reduced_Product<D1, D2, R>::minimize(const Linear_Expression& expr,
				   Coefficient& inf_n,
                                   Coefficient& inf_d,
                                   bool& minimum) const {
  reduce();
  if (is_empty())
    return false;
  Coefficient inf1_n;
  Coefficient inf1_d;
  Coefficient inf2_n;
  Coefficient inf2_d;
  bool minimum1;
  bool minimum2;
  bool r1 = d1.minimize(expr, inf1_n, inf1_d, minimum1);
  bool r2 = d2.minimize(expr, inf2_n, inf2_d, minimum2);
  // If neither is bounded from below, return false.
  if (!r1 && !r2)
    return false;
  // If only d2 is bounded from below, then use the values for d2.
  if (!r1) {
    inf_n = inf2_n;
    inf_d = inf2_d;
    minimum = minimum2;
    return true;
  }
  // If only d1 is bounded from below, then use the values for d1.
  if (!r2) {
    inf_n = inf1_n;
    inf_d = inf1_d;
    minimum = minimum1;
    return true;
  }
  // If both d1 and d2 are bounded from below, then use the minimum values.
  if (inf2_d * inf1_n <= inf1_d * inf2_n) {
    inf_n = inf1_n;
    inf_d = inf1_d;
    minimum = minimum1;
  }
  else {
    inf_n = inf2_n;
    inf_d = inf2_d;
    minimum = minimum2;
  }
  return true;
 }

template <typename D1, typename D2, typename R>
bool
  Partially_Reduced_Product<D1, D2, R>::maximize(const Linear_Expression& expr,
				   Coefficient& sup_n,
                                   Coefficient& sup_d,
                                   bool& maximum,
                                   Generator& pnt) const {
  reduce();
  if (is_empty())
    return false;
  Coefficient sup1_n;
  Coefficient sup1_d;
  Coefficient sup2_n;
  Coefficient sup2_d;
  bool maximum1;
  bool maximum2;
  Generator pnt1(point());
  Generator pnt2(point());
  bool r1 = d1.maximize(expr, sup1_n, sup1_d, maximum1, pnt1);
  bool r2 = d2.maximize(expr, sup2_n, sup2_d, maximum2, pnt2);
  // If neither is bounded from above, return false.
  if (!r1 && !r2)
    return false;
  // If only d2 is bounded from above, then use the values for d2.
  if (!r1) {
    sup_n = sup2_n;
    sup_d = sup2_d;
    maximum = maximum2;
    pnt = pnt2;
    return true;
  }
  // If only d1 is bounded from above, then use the values for d1.
  if (!r2) {
    sup_n = sup1_n;
    sup_d = sup1_d;
    maximum = maximum1;
    pnt = pnt1;
    return true;
  }
  // If both d1 and d2 are bounded from above, then use the minimum values.
  if (sup2_d * sup1_n >= sup1_d * sup2_n) {
    sup_n = sup1_n;
    sup_d = sup1_d;
    maximum = maximum1;
    pnt = pnt1;
  }
  else {
    sup_n = sup2_n;
    sup_d = sup2_d;
    maximum = maximum2;
    pnt = pnt2;
  }
  return true;
 }

template <typename D1, typename D2, typename R>
bool
  Partially_Reduced_Product<D1, D2, R>::minimize(const Linear_Expression& expr,
				   Coefficient& inf_n,
                                   Coefficient& inf_d,
                                   bool& minimum,
                                   Generator& pnt) const {
  reduce();
  if (is_empty())
    return false;
  Coefficient inf1_n;
  Coefficient inf1_d;
  Coefficient inf2_n;
  Coefficient inf2_d;
  bool minimum1;
  bool minimum2;
  Generator pnt1(point());
  Generator pnt2(point());
  bool r1 = d1.minimize(expr, inf1_n, inf1_d, minimum1, pnt1);
  bool r2 = d2.minimize(expr, inf2_n, inf2_d, minimum2, pnt2);
  // If neither is bounded from below, return false.
  if (!r1 && !r2)
    return false;
  // If only d2 is bounded from below, then use the values for d2.
  if (!r1) {
    inf_n = inf2_n;
    inf_d = inf2_d;
    minimum = minimum2;
    pnt = pnt2;
    return true;
  }
  // If only d1 is bounded from below, then use the values for d1.
  if (!r2) {
    inf_n = inf1_n;
    inf_d = inf1_d;
    minimum = minimum1;
    pnt = pnt1;
    return true;
  }
  // If both d1 and d2 are bounded from below, then use the minimum values.
  if (inf2_d * inf1_n <= inf1_d * inf2_n) {
    inf_n = inf1_n;
    inf_d = inf1_d;
    minimum = minimum1;
    pnt = pnt1;
  }
  else {
    inf_n = inf2_n;
    inf_d = inf2_d;
    minimum = minimum2;
    pnt = pnt2;
  }
  return true;
 }

template <typename D1, typename D2, typename R>
bool
Partially_Reduced_Product<D1, D2, R>::ascii_load(std::istream& s) {
  std::string str;
  return ((s >> str) && str == "Domain"
	  && (s >> str) && str == "1:"
	  && d1.ascii_load(s)
	  && (s >> str) && str == "Domain"
	  && (s >> str) && str == "2:"
	  && d2.ascii_load(s));
}

} // namespace Parma_Polyhedra_Library

namespace Parma_Polyhedra_Library {

template <typename D1, typename D2>
inline
Smash_Reduction<D1, D2>::Smash_Reduction() {
}

template <typename D1, typename D2>
void Smash_Reduction<D1, D2>::product_reduce(D1& d1, D2& d2) {
  if (d2.is_empty()) {
    if (!d1.is_empty()) {
      D1 new_d1(d1.space_dimension(), EMPTY);
      std::swap(d1, new_d1);
    }
  }
  else if (d1.is_empty()) {
    D2 new_d2(d2.space_dimension(), EMPTY);
    std::swap(d2, new_d2);
  }
}

template <typename D1, typename D2>
inline
Smash_Reduction<D1, D2>::~Smash_Reduction() {
}

} // namespace Parma_Polyhedra_Library

#endif // !defined(PPL_Partially_Reduced_Product_templates_hh)