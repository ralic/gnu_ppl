/* Declaration of simple print functions used in test programs.
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

#ifndef _print_hh
#define _print_hh 1

#if NOISY

#include <iosfwd>
#include <string>
#include "ppl_install.hh"

bool
easy_print(const Parma_Polyhedra_Library::Polyhedron& ph,
	   const std::string& intro = "",
	   std::ostream& s = std::cout);

void
print_constraint(const Parma_Polyhedra_Library::Constraint& c,
		 const std::string& intro = "",
		 std::ostream& s = std::cout) {
  if (!intro.empty())
    s << intro << endl;
  s << c << endl;
}

inline void
print_constraints(const Parma_Polyhedra_Library::ConSys& cs,
		  const std::string& intro = "",
		  std::ostream& s = std::cout) {
  if (!intro.empty())
    s << intro << endl;
  ConSys::const_iterator i = cs.begin();
  ConSys::const_iterator cs_end = cs.end();
  while (i != cs_end) {
    s << *i++;
    if (i != cs_end)
      s << "," << endl;
  }
  s << "." << endl;
}

inline void
print_constraints(const Parma_Polyhedra_Library::Polyhedron& ph,
		  const std::string& intro = "",
		  std::ostream& s = std::cout) {
  if (!easy_print(ph, intro, s))
    print_constraints(ph.constraints(), "", s);
}

inline void
print_generator(const Parma_Polyhedra_Library::Generator& g,
		const std::string& intro = "",
		std::ostream& s = std::cout) {
  if (!intro.empty())
    s << intro << endl;
  s << g << endl;
}

inline void
print_generators(const Parma_Polyhedra_Library::GenSys& gs,
		 const std::string& intro = "",
		 std::ostream& s = std::cout);

void
print_generators(const Parma_Polyhedra_Library::Polyhedron& ph,
		 const std::string& intro = "",
		 std::ostream& s = std::cout);

#endif

#endif
