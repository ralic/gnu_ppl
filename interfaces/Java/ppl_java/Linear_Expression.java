/* Linear_Expression Java declaration and implementation.
   Copyright (C) 2001-2006 Roberto Bagnara <bagnara@cs.unipr.it>

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

package ppl_java;
//! A linear expression.
/*! \ingroup PPL_Java_interface
  An object of the class Linear_Expression represents a linear expression
  that can be built from a Linear_Expression_Variable,
  Linear_Expression_Coefficient, Linear_Expression_Sum,
  Linear_Expression_Difference, Linear_Expression_Unary_Minus.
*/

public class Linear_Expression {

    //! Returns the sum of \p this and \p y.
    public Linear_Expression sum(Linear_Expression y) {
	return new Linear_Expression_Sum(this, y);
    }

    //! Returns the difference of \p this and \p y.
    public Linear_Expression subtract(Linear_Expression y) {
	return new Linear_Expression_Difference(this, y);
    }
    //! Returns the product of \p this times \p c.
    public Linear_Expression times(Coefficient c) {
	return new Linear_Expression_Times(this, c);
    }

    //! Returns the negation of \p this.
    public Linear_Expression unary_minus() {
	return new Linear_Expression_Unary_Minus(this);
    }
}