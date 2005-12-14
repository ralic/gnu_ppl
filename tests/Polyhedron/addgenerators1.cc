/* Adds a system of generators to a polyhedron and minimizes it.
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
  gs1.insert(point(x));
  gs1.insert(point(y));
  gs1.insert(line(x));
  C_Polyhedron ph1(gs1);

  print_generators(ph1, "*** before ***");

  Generator_System gs2;
  gs2.insert(point());

  ph1.add_generators_and_minimize(gs2);

  C_Polyhedron known_result(2, EMPTY);
  known_result.add_generator(point());
  known_result.add_generator(point(y));
  known_result.add_generator(line(x));

  int retval = (ph1 == known_result) ? 0: 1;

  print_generators(ph1, "*** add_generators_and_minimize ***");

  return retval;
}
CATCH
