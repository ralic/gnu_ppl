dnl This file generates ppl_prolog.icc.
dnl
dnl Include files defining macros that generate the non-fixed part.
include(`ppl_interface_generator_prolog_icc_code.m4')dnl
include(`ppl_interface_generator_common.m4')dnl
include(`ppl_interface_generator_prolog_dat.m4')dnl
dnl
divert(-1)dnl

dnl m4_add_term_to_class_handle_code(Class, CPP_Class)
dnl
dnl Adds the code to convert a term to a Class handle.
define(`m4_add_term_to_class_handle_code', `dnl
m4_replace_all_patterns($1, m4_term_to_class_handle_code,
  m4_pattern_list)`'dnl
ifelse(m4_cplusplus_class$1, Polyhedron, `dnl
m4_replace_all_patterns($1, m4_term_to_topology_Polyhedron_handle_code,
  m4_pattern_list)`'dnl
')`'dnl
')

dnl m4_pre_all_classes_code
dnl
dnl Definition for converting a term to a class handle code for all
dnl classes must be placed before all the generated code so that one class
dnl can be copied from another.
define(`m4_pre_all_classes_code', `dnl
m4_forloop(m4_ind, 1, m4_num_classes,
  `m4_add_term_to_class_handle_code(m4_ind)')`'dnl
')

dnl m4_add_bop_assign_code(Class, CPP_Class)
dnl
dnl Adds the extra code used by the binary operators.
define(`m4_add_bop_assign_code', `dnl
m4_replace_all_patterns($1, bop_assign_code,
  m4_pattern_list)`'dnl
')

dnl m4_pre_extra_class_code(Class_Counter, Class_Kind)
dnl Prefix extra code for each class.
define(`m4_pre_extra_class_code', `dnl
dnl m4_add_term_to_class_handle_code($1)`'dnl
m4_add_bop_assign_code($1)`'dnl
')

divert`'dnl
dnl
dnl Output the fixed preamble.
include(`ppl_interface_generator_prolog_icc_preamble')
dnl
dnl Generate the non-fixed part of the file.
m4_all_classes_code`'dnl
dnl
dnl End of file generation.
