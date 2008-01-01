/* PPL Java interface fixed routines implementation.
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
   site: http://www.cs.unipr.it/ppl/ . */

#include "ppl_java_Parma_Polyhedra_Library.h"
#include "ppl_java_common.hh"
#include "ppl_java_MIP_Problem.h"
#include "ppl_java_Linear_Expression.h"
#include "ppl_java_Constraint.h"
#include "ppl_java_Constraint_System.h"
#include "ppl_java_Congruence.h"
#include "ppl_java_Congruence_System.h"
#include "ppl_java_Generator.h"
#include "ppl_java_Generator_System.h"
#include "ppl_java_Grid_Generator.h"
#include "ppl_java_Grid_Generator_System.h"

JNIEXPORT jint JNICALL Java_ppl_1java_Parma_1Polyhedra_1Library_version_1major
(JNIEnv *, jclass) {
  return version_major();
}

JNIEXPORT jint JNICALL Java_ppl_1java_Parma_1Polyhedra_1Library_version_1minor
(JNIEnv *, jclass)  {
  return version_minor();
}


JNIEXPORT jint JNICALL Java_ppl_1java_Parma_1Polyhedra_1Library_version_1revision
(JNIEnv *, jclass) {
  return version_revision();
}

JNIEXPORT jint JNICALL Java_ppl_1java_Parma_1Polyhedra_1Library_version_1beta
(JNIEnv *, jclass) {
  return version_beta();
}


JNIEXPORT jstring JNICALL Java_ppl_1java_Parma_1Polyhedra_1Library_version
(JNIEnv* env, jclass) {
  return env->NewStringUTF(version());
}

JNIEXPORT jstring JNICALL Java_ppl_1java_Parma_1Polyhedra_1Library_banner
(JNIEnv* env, jclass) {
  return env->NewStringUTF(banner());
}

JNIEXPORT jlong JNICALL Java_ppl_1java_MIP_1Problem_max_1space_1dimension
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    return mip->max_space_dimension();
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jlong JNICALL Java_ppl_1java_MIP_1Problem_space_1dimension
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    return mip->space_dimension();
  }
  CATCH_ALL;
  return 0;
}

JNIEXPORT jobject JNICALL Java_ppl_1java_MIP_1Problem_integer_1space_1dimensions
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    return build_java_variables_set(env, mip->integer_space_dimensions());
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT jobject JNICALL Java_ppl_1java_MIP_1Problem_objective_1function
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jclass j_le_coeff_class
      = env->FindClass("ppl_java/Linear_Expression_Coefficient");
    jclass j_le_class
      = env->FindClass("ppl_java/Linear_Expression");
    jmethodID j_le_sum_id
      = env->GetMethodID(j_le_class,
			 "sum",
			 "(Lppl_java/Linear_Expression;)"
			 "Lppl_java/Linear_Expression;");
    jmethodID j_le_coeff_ctr_id
      = env->GetMethodID(j_le_coeff_class, "<init>",
			 "(Lppl_java/Coefficient;)V");
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    TEMP_INTEGER(inhomogeneous_term);
    inhomogeneous_term = mip->objective_function().inhomogeneous_term();
    jobject j_coeff_inhomogeneous_term
      = build_java_coeff(env, inhomogeneous_term);
    jobject j_le_coeff = env->NewObject(j_le_coeff_class, j_le_coeff_ctr_id,
					j_coeff_inhomogeneous_term);

    jobject j_le = get_linear_expression(env, mip->objective_function());
    return env->CallObjectMethod(j_le, j_le_sum_id, j_le_coeff);
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT jobject JNICALL Java_ppl_1java_MIP_1Problem_optimization_1mode
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    return build_java_optimization_mode(env, mip->optimization_mode());
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT jobject JNICALL Java_ppl_1java_MIP_1Problem_constraints
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jclass j_cs_class = env->FindClass("ppl_java/Constraint_System");
    jmethodID j_cs_ctr_id = env->GetMethodID(j_cs_class, "<init>", "()V");
    jmethodID j_cs_add_id = env->GetMethodID(j_cs_class, "add",
					     "(Ljava/lang/Object;)Z");
    jobject j_cs = env->NewObject(j_cs_class, j_cs_ctr_id);
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    for (MIP_Problem::const_iterator cs_it = mip->constraints_begin(),
	   cs_end = mip->constraints_end(); cs_it != cs_end; ++cs_it) {
      jobject j_constraint = build_java_constraint(env, *cs_it);
      env->CallBooleanMethod(j_cs, j_cs_add_id, j_constraint);
    }
    return j_cs;
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}


JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_clear
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    mip->clear();
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_add_1space_1dimensions_1and_1embed
(JNIEnv* env , jobject j_this_mip_problem, jlong j_dim) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    dimension_type ppl_dim = jtype_to_unsigned<dimension_type>(j_dim);
    mip->add_space_dimensions_and_embed(ppl_dim);
  }
  CATCH_ALL;
}


JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_add_1to_1integer_1space_1dimensions
(JNIEnv* env , jobject j_this_mip_problem, jobject j_vset) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    Variables_Set v_set = build_ppl_variables_set(env, j_vset);
    mip->add_to_integer_space_dimensions(v_set);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_add_1constraint
(JNIEnv* env , jobject j_this_mip_problem, jobject j_c) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    Constraint c = build_ppl_constraint(env, j_c);
    mip->add_constraint(c);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_add_1constraints
(JNIEnv* env , jobject j_this_mip_problem, jobject j_cs) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    Constraint_System cs = build_ppl_constraint_system(env, j_cs);
    mip->add_constraints(cs);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_set_1objective_1function
(JNIEnv* env , jobject j_this_mip_problem, jobject j_le) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    Linear_Expression le = build_linear_expression(env, j_le);
    mip->set_objective_function(le);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_set_1optimization_1mode
(JNIEnv* env , jobject j_this_mip_problem, jobject j_opt_mode) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    Optimization_Mode opt_mode = build_ppl_optimization_mode(env, j_opt_mode);
    mip->set_optimization_mode(opt_mode);
  }
  CATCH_ALL;
}

JNIEXPORT jboolean JNICALL Java_ppl_1java_MIP_1Problem_is_1satisfiable
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    return mip->is_satisfiable();
  }
  CATCH_ALL;
  return false;
}

JNIEXPORT jobject JNICALL Java_ppl_1java_MIP_1Problem_solve
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    return build_java_mip_status(env, mip->solve());
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_evaluate_1objective_1function
(JNIEnv* env, jobject j_this_mip_problem, jobject j_gen, jobject j_coeff_num,
 jobject j_coeff_den) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    Generator g = build_ppl_generator(env, j_gen);
    TEMP_INTEGER(num);
    TEMP_INTEGER(den);
    num = build_ppl_coeff(env, j_coeff_num);
    den = build_ppl_coeff(env, j_coeff_den);
    mip->evaluate_objective_function(g, num, den);
    set_coefficient(env, j_coeff_num, build_java_coeff(env, num));
    set_coefficient(env, j_coeff_den, build_java_coeff(env, den));
  }
  CATCH_ALL;
}

JNIEXPORT jobject JNICALL Java_ppl_1java_MIP_1Problem_feasible_1point
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    Generator g = mip->feasible_point();
    return build_java_generator(env, g);
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT jobject JNICALL Java_ppl_1java_MIP_1Problem_optimizing_1point
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    Generator g = mip->optimizing_point();
    return build_java_generator(env, g);
  }
  CATCH_ALL;
  jobject null = 0;
  return null;
}

JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_optimal_1value
(JNIEnv* env, jobject j_this_mip_problem, jobject j_coeff_num,
 jobject j_coeff_den) {
  try {
    TEMP_INTEGER(coeff_num);
    TEMP_INTEGER(coeff_den);
    coeff_num = build_ppl_coeff(env, j_coeff_num);
    coeff_den = build_ppl_coeff(env, j_coeff_den);
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    mip->optimal_value(coeff_num, coeff_den);
    jobject j_coeff_num_result = build_java_coeff(env, coeff_num);
    jobject j_coeff_den_result = build_java_coeff(env, coeff_den);
    set_coefficient(env, j_coeff_num, j_coeff_num_result);
    set_coefficient(env, j_coeff_den, j_coeff_den_result);
  }
  CATCH_ALL;
}

JNIEXPORT jboolean JNICALL Java_ppl_1java_MIP_1Problem_OK
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    return mip->OK();
  }
  CATCH_ALL;
  return false;
}

JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_build_1cpp_1object__J
(JNIEnv* env, jobject j_this_mip_problem, jlong j_dim) {
  try {
    jclass j_mip_problem_class = env->GetObjectClass(j_this_mip_problem);
    dimension_type ppl_dim = jtype_to_unsigned<dimension_type>(j_dim);
    MIP_Problem* mip_ptr = new MIP_Problem(ppl_dim);
    jfieldID pointer_field = env->GetFieldID(j_mip_problem_class, "ptr", "J");
    env->SetLongField(j_this_mip_problem, pointer_field, (long long) mip_ptr);
  }
  CATCH_ALL;
}

JNIEXPORT void JNICALL Java_ppl_1java_MIP_1Problem_build_1cpp_1object__JLppl_1java_Constraint_1System_2Lppl_1java_Linear_1Expression_2Lppl_1java_Optimization_1Mode_2
(JNIEnv* env , jobject j_this_mip_problem, jlong j_dim, jobject j_cs,
 jobject j_le, jobject j_opt_mode) {
  try {
    jclass j_mip_problem_class = env->GetObjectClass(j_this_mip_problem);
    dimension_type ppl_dim = jtype_to_unsigned<dimension_type>(j_dim);
    Constraint_System cs = build_ppl_constraint_system(env, j_cs);
    Linear_Expression le = build_linear_expression(env, j_le);
    Optimization_Mode opt_mode =  build_ppl_optimization_mode(env, j_opt_mode);
    MIP_Problem* mip_ptr = new MIP_Problem(ppl_dim, cs, le, opt_mode);
    jfieldID pointer_field = env->GetFieldID(j_mip_problem_class, "ptr", "J");
    env->SetLongField(j_this_mip_problem, pointer_field, (long long) mip_ptr);
  }
  CATCH_ALL;
}

JNIEXPORT jstring JNICALL Java_ppl_1java_MIP_1Problem_toString
(JNIEnv* env, jobject j_this_mip_problem) {
 using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  jlong ptr = get_ptr(env, j_this_mip_problem);
  MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
  s << mip;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL Java_ppl_1java_Linear_1Expression_toString
(JNIEnv* env, jobject le) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Linear_Expression ppl_le = build_linear_expression(env, le);
  s << ppl_le;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL Java_ppl_1java_Generator_toString
(JNIEnv* env, jobject g) {
  using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Generator ppl_g = build_ppl_generator(env, g);
  s << ppl_g;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL Java_ppl_1java_Constraint_toString
(JNIEnv* env, jobject c) {
 using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Constraint ppl_c = build_ppl_constraint(env, c);
  s << ppl_c;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL  Java_ppl_1java_Grid_1Generator_toString
(JNIEnv* env, jobject g) {
 using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Grid_Generator ppl_g = build_ppl_grid_generator(env, g);
  s << ppl_g;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL Java_ppl_1java_Congruence_toString
(JNIEnv* env, jobject g) {
 using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Congruence ppl_g = build_ppl_congruence(env, g);
  s << ppl_g;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL Java_ppl_1java_Grid_1Generator_1System_toString
(JNIEnv* env, jobject ggs) {
 using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Grid_Generator_System ppl_ggs = build_ppl_grid_generator_system(env, ggs);
  s << ppl_ggs;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL Java_ppl_1java_Generator_1System_toString
(JNIEnv* env, jobject gs) {
 using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Generator_System ppl_gs = build_ppl_generator_system(env, gs);
  s << ppl_gs;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL Java_ppl_1java_Constraint_1System_toString
(JNIEnv* env, jobject cs) {
 using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Constraint_System ppl_cs = build_ppl_constraint_system(env, cs);
  s << ppl_cs;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jstring JNICALL Java_ppl_1java_Congruence_1System_toString
(JNIEnv* env, jobject cgs) {
 using namespace Parma_Polyhedra_Library::IO_Operators;
  std::ostringstream s;
  Congruence_System ppl_cgs = build_ppl_congruence_system(env, cgs);
  s << ppl_cgs;
  return env->NewStringUTF(s.str().c_str());
}

JNIEXPORT jlong JNICALL Java_ppl_1java_MIP_1Problem_total_1memory_1in_1bytes
(JNIEnv* env , jobject j_this_mip_problem) {
  try {
    jlong ptr = get_ptr(env, j_this_mip_problem);
    MIP_Problem* mip = reinterpret_cast<MIP_Problem*>(ptr);
    return mip->total_memory_in_bytes();
  }
  CATCH_ALL;
  return 0;
}
