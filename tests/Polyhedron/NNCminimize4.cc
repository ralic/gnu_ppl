/* Full minimization of a NNC-redundant constraint system.
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

using namespace Parma_Polyhedra_Library::IO_Operators;

int
main() TRY {
  set_handlers();

  Variable x(0);
  Variable y(1);

  // Building an open square.
  Generator_System gs;
  gs.insert(closure_point());
  gs.insert(closure_point(15*x));
  gs.insert(closure_point(15*y));
  gs.insert(closure_point(15*x + 15*y));

  // All of these points, but a (any) single one of them, are redundant.
  gs.insert(point(3*x + 3*y));
  gs.insert(point(6*x + y));
  gs.insert(point(9*x + y));
  gs.insert(point(12*x + 3*y));
  gs.insert(point(3*x + 12*y));
  gs.insert(point(6*x + 14*y));
  gs.insert(point(9*x + 14*y));
  gs.insert(point(12*x + 12*y));
  gs.insert(point(x + 6*y));
  gs.insert(point(x + 9*y));
  gs.insert(point(14*x + 6*y));
  gs.insert(point(14*x + 9*y));

  NNC_Polyhedron ph(gs);

  nout << endl << "Before NNC minimization" << endl;
  print_constraints(ph.constraints(), "*** ph constraints ***");
  print_generators(ph.generators(), "*** ph generators ***");

  ph.minimized_constraints();

  nout << endl << "After NNC minimization" << endl;
  print_constraints(ph.constraints(), "*** ph constraints ***");

  nout << endl << "=== ph ===" << endl << ph << endl;

  print_generators(ph.generators(), "*** ph generators ***");

  nout << endl << "=== ph ===" << endl << ph << endl;

  gs.clear();
  gs.insert(closure_point());
  gs.insert(closure_point(15*x));
  gs.insert(closure_point(15*y));
  gs.insert(closure_point(15*x + 15*y));
  gs.insert(point(x + y));

  NNC_Polyhedron known_result(gs);

  bool equal = (ph == known_result);

  nout << endl << "=== ph ===" << endl << ph << endl;
  nout << endl << "=== kr ===" << endl << known_result << endl;

  // FIXME: find a way to correctly check if the output
  // is strongly minimized.
  // return (equal && ph.constraints().num_rows() == 5) ? 0 : 1;

  return equal ? 0 : 1;
}
CATCH
