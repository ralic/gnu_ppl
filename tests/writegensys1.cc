/* Test operator<<(std::ostream&, const GenSys&).
   Copyright (C) 2001, 2002 Roberto Bagnara <bagnara@cs.unipr.it>

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
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
USA.

For the most up-to-date information see the Parma Polyhedra Library
site: http://www.cs.unipr.it/ppl/ . */

#include <fstream>
#include "ppl_test.hh"
#include "files.hh"

using namespace std;
using namespace Parma_Polyhedra_Library;

#ifndef NOISY
#define NOISY 0
#endif

const char* my_file = "writegensys1.dat";

int
main() {
  set_handlers();
  Variable A(0);
  Variable B(1);
  Variable C(2);

  GenSys gs;
  gs.insert(point());
  gs.insert(point(A + B));
  gs.insert(point(A + C));
  gs.insert(ray(B + C));
  gs.insert(line(C));

  fstream f;
  open(f, my_file, ios_base::out);
  f << gs << endl;
  close(f);

  return 0;
}
