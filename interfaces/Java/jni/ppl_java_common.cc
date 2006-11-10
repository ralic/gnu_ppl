/* PPL Java interface common routines implementation.
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

#include "ppl_java_common.hh"
using namespace Parma_Polyhedra_Library;

Parma_Polyhedra_Library::Congruence
build_ppl_congruence(JNIEnv* env, const jobject& j_congruence) {
  jclass congruence_le_class
    = env->FindClass("ppl_java/Congruence_Linear_Expression");
  jclass congruence_constraint_class
    = env->FindClass("ppl_java/Congruence_Constraint");
  jclass congruence_class
    = env->FindClass("ppl_java/Congruence");
  jclass current_class = env->GetObjectClass(j_congruence);
  jfieldID modulus_field_id = env->GetFieldID(congruence_class,
					      "modulus",
					      "Lppl_java/Coefficient;");
  jobject j_modulus = env->GetObjectField(j_congruence, modulus_field_id);
  Coefficient ppl_modulus = j_coeff_to_ppl_coeff(env, j_modulus);
  Linear_Expression(Variable(0) + ppl_modulus);
  // Constraint
  if (env->IsAssignableFrom(congruence_constraint_class, current_class)) {
    jfieldID constraint_field_id
      = env->GetFieldID(congruence_constraint_class,
			"constr",
			"Lppl_java/Constraint;");
    jobject j_constr = env->GetObjectField(j_congruence,
					   constraint_field_id);
    Constraint c = build_ppl_constraint(env, j_constr);
    Congruence cg =  c / ppl_modulus;
    return cg;
  }

  // Linear_Expression
  if (env->IsAssignableFrom(congruence_le_class, current_class)) {
    jfieldID lhs_field_id
      = env->GetFieldID(congruence_le_class,
 			"lhs",
 			"Lppl_java/Linear_Expression;");
    jfieldID rhs_field_id
      = env->GetFieldID(congruence_le_class,
 			"rhs",
 			"Lppl_java/Linear_Expression;");
    jobject j_lhs = env->GetObjectField(j_congruence, lhs_field_id);
    jobject j_rhs = env->GetObjectField(j_congruence, rhs_field_id);
    Linear_Expression lhs = build_linear_expression(env, j_lhs);
    Linear_Expression rhs = build_linear_expression(env, j_rhs);
    return (lhs %= rhs) / ppl_modulus;
  }
  jclass newExcCls = env->FindClass("javax/management/RuntimeErrorException");
  env->ThrowNew(newExcCls, "ppl.java: \n runtime error");
  // We should not be here!
  throw std::runtime_error("PPL Java interface internal error");

}

// Converts a C++ bool to a Java boolean.

// jobject
// bool_to_j_boolean(JNIEnv* env,
// 		  const bool bool_value) {
//  jclass boolean_java_class = env->FindClass("java/lang/Boolean");
//  jmethodID getboolean_method_id = env->GetStaticMethodID(boolean_java_class,
// 							 "valueOf", "(Z)java/lang/Boolean;");
//  return env->CallStaticObjectMethod(boolean_java_class,
// 				    getboolean_method_id,
// 				    bool_value);
//}

// bool
// j_boolean_to_bool(JNIEnv* env,
// 		  const jobject& j_boolean) {
//   jclass boolean_class = env->GetObjectClass(j_boolean);
//   jmethodID booleanvalue_method_id = env->GetMethodID(boolean_class,
// 						      "booleanValue",
// 						      "()Z");
//   return env->CallBooleanMethod(j_boolean, booleanvalue_method_id);

// }

Variables_Set
j_variables_set_to_ppl_variables_set(JNIEnv* env,
				     const jobject& j_v_set) {
  jclass variables_set_class = env->GetObjectClass(j_v_set);
  jclass iterator_java_class = env->FindClass("java/util/Iterator");
  Variables_Set v_set;
  jmethodID iterator_method_id = env->GetMethodID(variables_set_class,
						  "iterator",
 						  "()Ljava/util/Iterator;");
  jobject j_iterator = env->CallObjectMethod(j_v_set, iterator_method_id);
  jmethodID has_next_method_id = env->GetMethodID(iterator_java_class,
  						  "hasNext",
  						  "()Z");
  jboolean has_next_value = env->CallBooleanMethod(j_iterator,
						   has_next_method_id);
  jmethodID next_method_id = env->GetMethodID(iterator_java_class,
					      "next",
					      "()Ljava/lang/Object;");

  while (has_next_value) {
    jobject j_variable = env->CallObjectMethod(j_iterator,
					       next_method_id);
    v_set.insert(j_variable_to_ppl_variable(env, j_variable));
    has_next_value = env->CallBooleanMethod(j_iterator,
					    has_next_method_id);
  }
  return v_set;
}

Variable
j_variable_to_ppl_variable(JNIEnv* env, const jobject& j_var) {
  jclass j_variable_class = env->FindClass("ppl_java/Variable");
  jfieldID varid_field_id = env->GetFieldID(j_variable_class,
					  "varid",
					  "I");
  // Retrieve the value.
  return Variable(env->GetIntField(j_var, varid_field_id));
}

Relation_Symbol
j_relsym_to_ppl_relsym(JNIEnv* env, const jobject& j_relsym) {

  jclass rel_sym_class = env->FindClass("ppl_java/Relation_Symbol");
  jmethodID rel_sym_ordinal_id = env->GetMethodID(rel_sym_class, "ordinal",
						  "()I");
  jint rel_sym = env->CallIntMethod(j_relsym, rel_sym_ordinal_id);
  switch (rel_sym) {
  case 0: {
    if (rel_sym == 0)
      return LESS_THAN;
  }
  case 1: {
    if (rel_sym == 1)
      return LESS_THAN_OR_EQUAL;
  }
 case 2: {
    if (rel_sym == 2)
      return EQUAL;
 }
  case 3: {
    if (rel_sym == 3)
      return GREATER_THAN_OR_EQUAL;
  }
  case 4: {
    if (rel_sym == 4)
      return GREATER_THAN;
  }
  default:
    ;
  }
  jclass newExcCls = env->FindClass("javax/management/RuntimeErrorException");
  env->ThrowNew(newExcCls, "ppl.java: \n runtime error");
  // We should not be here!
  throw std::runtime_error("PPL Java interface internal error");
}

Coefficient
j_coeff_to_ppl_coeff(JNIEnv* env, const jobject& j_coeff) {
  jclass j_coeff_class = env->GetObjectClass(j_coeff);
  jfieldID fid = env->GetFieldID(j_coeff_class, "value",
				 "Ljava/math/BigInteger;");
  jobject bi = env->GetObjectField(j_coeff, fid);
  jclass big_integer_class = env->GetObjectClass(bi);
  jmethodID bi_to_string = env->GetMethodID(big_integer_class, "toString",
					    "()Ljava/lang/String;");
  jstring bi_string = (jstring) env->CallObjectMethod(bi, bi_to_string);
  const char *nativeString = env->GetStringUTFChars(bi_string, 0);
  Coefficient ppl_coeff = Coefficient(nativeString);
  env->ReleaseStringUTFChars(bi_string, nativeString);
  return ppl_coeff;
}

// Converts a PPL coefficient to a Java coefficient.
jobject
ppl_coeff_to_j_coeff(JNIEnv* env, const Coefficient& ppl_coeff) {
  std::ostringstream s;
  s << ppl_coeff;
  jclass j_coefficient_class = env->FindClass("ppl_java/Coefficient");
  jmethodID j_coefficient_ctr_id = env->GetMethodID(j_coefficient_class,
						    "<init>",
						    "(Ljava/lang/String;)V");
  jstring coeff_string = env->NewStringUTF(s.str().c_str());
  return env->NewObject(j_coefficient_class, j_coefficient_ctr_id,
			coeff_string);
}

Constraint
build_ppl_constraint(JNIEnv* env, const jobject& j_constraint) {
  jclass constraint_class = env->FindClass("ppl_java/Constraint");
  jclass rel_sym_class = env->FindClass("ppl_java/Relation_Symbol");
  jfieldID lhs_field_id = env->GetFieldID(constraint_class, "lhs",
					  "Lppl_java/Linear_Expression;");
  jfieldID rhs_field_id = env->GetFieldID(constraint_class, "rhs",
					  "Lppl_java/Linear_Expression;");
  jobject lhs_value = env->GetObjectField(j_constraint, lhs_field_id);
  jobject rhs_value = env->GetObjectField(j_constraint, rhs_field_id);
  Linear_Expression first_le = build_linear_expression(env, lhs_value);
  Linear_Expression second_le = build_linear_expression(env, rhs_value);
  jfieldID kind_field_id = env->GetFieldID(constraint_class, "kind",
					   "Lppl_java/Relation_Symbol;");
  jobject kind = env->GetObjectField(j_constraint, kind_field_id);
  jmethodID rel_sym_ordinal_id = env->GetMethodID(rel_sym_class, "ordinal",
						  "()I");
  jint rel_sym = env->CallIntMethod(kind, rel_sym_ordinal_id);
  switch (rel_sym) {
  case 0:
    return Constraint(first_le < second_le);
  case 1:
    return Constraint(first_le <= second_le);
  case 2:
    return Constraint(first_le == second_le);
  case 3:
  if (rel_sym == 3)
    return Constraint(first_le >= second_le);
  case 4:
    return Constraint(first_le > second_le);
  default:
    ;
  }
  jclass newExcCls = env->FindClass("javax/management/RuntimeErrorException");
  env->ThrowNew(newExcCls, "ppl.java: \n runtime error");
  // We should not be here!
  throw std::runtime_error("PPL Java interface internal error");
}


Linear_Expression
build_linear_expression(JNIEnv* env, const jobject& j_le) {
  jclass le_sum_class = env->FindClass("ppl_java/Linear_Expression_Sum");
  jclass le_difference_class
    = env->FindClass("ppl_java/Linear_Expression_Difference");
  jclass le_times_class
    = env->FindClass("ppl_java/Linear_Expression_Times");
  jclass le_unary_minus_class
    = env->FindClass("ppl_java/Linear_Expression_Unary_Minus");
  jclass j_coeff_le_class
    = env->FindClass("ppl_java/Linear_Expression_Coefficient");
  jclass j_variable_le_class
    = env->FindClass("ppl_java/Linear_Expression_Variable");
  jclass j_variable_class = env->FindClass("ppl_java/Variable");

  jclass current_class = env->GetObjectClass(j_le);
  // Variable
  if (env->IsAssignableFrom(j_variable_le_class, current_class)) {
    jfieldID arg_field_id = env->GetFieldID(j_variable_le_class,
					    "arg",
					    "Lppl_java/Variable;");
    jobject var = env->GetObjectField(j_le, arg_field_id);
    jfieldID varid_field_id = env->GetFieldID(j_variable_class,
					      "varid",
					      "I");

    // Retrieve the value.
    jint varid = env->GetIntField(var, varid_field_id);
    return Linear_Expression(Variable(varid));
  }
  // Coefficient
  if (env->IsAssignableFrom(j_coeff_le_class, current_class)) {
    jfieldID coeff_field_id = env->GetFieldID(j_coeff_le_class,
					      "coeff",
					      "Lppl_java/Coefficient;");
    jobject ppl_coeff = env->GetObjectField(j_le, coeff_field_id);

    return Linear_Expression(j_coeff_to_ppl_coeff(env, ppl_coeff));
  }
  // Sum
  if (env->IsAssignableFrom(le_sum_class, current_class)) {
    jfieldID l_field_id = env->GetFieldID(current_class, "lhs",
					  "Lppl_java/Linear_Expression;");
    jfieldID r_field_id = env->GetFieldID(current_class, "rhs",
					  "Lppl_java/Linear_Expression;");
    jobject l_value = env->GetObjectField(j_le, l_field_id);
    jobject r_value = env->GetObjectField(j_le, r_field_id);
    return (build_linear_expression(env, l_value)
	    + build_linear_expression(env, r_value));
  }
  // Difference
  if (env->IsAssignableFrom(current_class, le_difference_class)) {
    jfieldID l_field_id = env->GetFieldID(current_class, "lhs",
					  "Lppl_java/Linear_Expression;");
    jfieldID r_field_id = env->GetFieldID(current_class, "rhs",
					  "Lppl_java/Linear_Expression;");
    jobject l_value = env->GetObjectField(j_le, l_field_id);
    jobject r_value = env->GetObjectField(j_le, r_field_id);
    return (build_linear_expression(env, l_value)
	    - build_linear_expression(env, r_value));
  }
  // Times
  if (env->IsAssignableFrom(le_times_class, current_class)) {
    jfieldID le_field_id = env->GetFieldID(current_class, "rhs",
					   "Lppl_java/Linear_Expression;");
    jfieldID le_coeff_field_id
      = env->GetFieldID(current_class, "lhs",
			"Lppl_java/Linear_Expression_Coefficient;");
    jobject le_value = env->GetObjectField(j_le, le_field_id);
    jobject le_coeff_value = env->GetObjectField(j_le, le_coeff_field_id);
    jfieldID coeff_field_id = env->GetFieldID(j_coeff_le_class,
					      "coeff",
					      "Lppl_java/Coefficient;");
    jobject ppl_coeff = env->GetObjectField(le_coeff_value, coeff_field_id);
    return (j_coeff_to_ppl_coeff(env, ppl_coeff)
	    * build_linear_expression(env, le_value));
  }
  // Unary_Minus
  if (env->IsAssignableFrom(current_class, le_unary_minus_class)) {
    jfieldID le_field_id = env->GetFieldID(current_class, "arg",
					   "Lppl_java/Linear_Expression;");
    jobject le_value = env->GetObjectField(j_le, le_field_id);
    return (-build_linear_expression(env, le_value));
  }
  // We should not be here!
  throw std::runtime_error("PPL Java interface internal error");
}

Generator
build_generator(JNIEnv* env, const jobject& j_generator) {
  jclass generator_class = env->FindClass("ppl_java/Generator");
  jclass generator_type_class = env->FindClass("ppl_java/Generator_Type");

  jfieldID j_le_field = env->GetFieldID(generator_class, "le",
					"Lppl_java/Linear_Expression;");
  jobject j_le = env->GetObjectField(j_generator, j_le_field);
  jfieldID j_coeff_field = env->GetFieldID(generator_class, "den",
					   "Lppl_java/Coefficient;");
  jobject j_coeff = env->GetObjectField(j_generator, j_coeff_field);

  jfieldID generator_type_field = env->GetFieldID(generator_class, "gt",
						  "Lppl_java/Generator_Type;");
  jobject generator_type = env->GetObjectField(j_generator,
					       generator_type_field);
  jmethodID generator_type_ordinal_id = env->GetMethodID(generator_type_class,
							 "ordinal",
							 "()I");
  jint generator_type_ordinal = env->CallIntMethod(generator_type,
						   generator_type_ordinal_id);
  switch (generator_type_ordinal) {
  case 0:
    return line(build_linear_expression(env, j_le));
  case 1:
    return ray(build_linear_expression(env, j_le));
  case 2:
    return point(build_linear_expression(env, j_le),
		 j_coeff_to_ppl_coeff(env, j_coeff));
  case 3:
    return closure_point(build_linear_expression(env, j_le),
			 j_coeff_to_ppl_coeff(env, j_coeff));
  default:
    ;
  }
  jclass newExcCls = env->FindClass("javax/management/RuntimeErrorException");
  env->ThrowNew(newExcCls, "ppl.java: \n runtime error");
  // We should not be here!
  throw std::runtime_error("PPL Java interface internal error");
}

jlong
get_ptr(JNIEnv* env, const jobject& ppl_object) {
  jclass ppl_object_class = env->GetObjectClass(ppl_object);
  jfieldID pointer_field = env->GetFieldID(ppl_object_class, "ptr","J");
  return  env->GetLongField(ppl_object, pointer_field);
}

Constraint_System
build_ppl_constraint_system(JNIEnv* env, const jobject& j_iterable) {
  jclass j_iterable_class = env->GetObjectClass(j_iterable);
  jclass iterator_java_class = env->FindClass("java/util/Iterator");
  Constraint_System cs;
  jmethodID iterator_method_id = env->GetMethodID(j_iterable_class,
						  "iterator",
 						  "()Ljava/util/Iterator;");
  jobject j_iterator = env->CallObjectMethod(j_iterable, iterator_method_id);
  jmethodID has_next_method_id = env->GetMethodID(iterator_java_class,
  						  "hasNext",
  						  "()Z");
  jboolean has_next_value = env->CallBooleanMethod(j_iterator,
						   has_next_method_id);
  jmethodID next_method_id = env->GetMethodID(iterator_java_class,
					      "next",
					      "()Ljava/lang/Object;");

  while (has_next_value) {
    jobject j_constraint = env->CallObjectMethod(j_iterator,
						 next_method_id);
    cs.insert(build_ppl_constraint(env, j_constraint));
    has_next_value = env->CallBooleanMethod(j_iterator,
					    has_next_method_id);
  }
 return cs;
}

Generator_System
build_ppl_generator_system(JNIEnv* env, const jobject& j_iterable) {
  jclass j_iterable_class = env->GetObjectClass(j_iterable);
  jclass iterator_java_class = env->FindClass("java/util/Iterator");
  Generator_System gs;
  jmethodID iterator_method_id = env->GetMethodID(j_iterable_class,
						  "iterator",
 						  "()Ljava/util/Iterator;");
  jobject j_iterator = env->CallObjectMethod(j_iterable, iterator_method_id);
  jmethodID has_next_method_id = env->GetMethodID(iterator_java_class,
  						  "hasNext",
  						  "()Z");
  jboolean has_next_value = env->CallBooleanMethod(j_iterator,
						   has_next_method_id);
  jmethodID next_method_id = env->GetMethodID(iterator_java_class,
					      "next",
					      "()Ljava/lang/Object;");

  while (has_next_value) {
    jobject j_constraint = env->CallObjectMethod(j_iterator,
						 next_method_id);
    gs.insert(build_generator(env, j_constraint));
    has_next_value = env->CallBooleanMethod(j_iterator,
					    has_next_method_id);
  }
  return gs;
}

Congruence_System
build_ppl_congruence_system(JNIEnv* env, const jobject& j_iterable) {
  jclass j_iterable_class = env->GetObjectClass(j_iterable);
  jclass iterator_java_class = env->FindClass("java/util/Iterator");
  Congruence_System cgs;
  jmethodID iterator_method_id = env->GetMethodID(j_iterable_class,
						  "iterator",
 						  "()Ljava/util/Iterator;");
  jobject j_iterator = env->CallObjectMethod(j_iterable, iterator_method_id);
  jmethodID has_next_method_id = env->GetMethodID(iterator_java_class,
  						  "hasNext",
  						  "()Z");
  jboolean has_next_value = env->CallBooleanMethod(j_iterator,
						   has_next_method_id);
  jmethodID next_method_id = env->GetMethodID(iterator_java_class,
					      "next",
					      "()Ljava/lang/Object;");

  while (has_next_value) {
    jobject j_congruence = env->CallObjectMethod(j_iterator,
						 next_method_id);
    cgs.insert(build_ppl_congruence(env, j_congruence));
    has_next_value = env->CallBooleanMethod(j_iterator,
					    has_next_method_id);
  }
  return cgs;
}