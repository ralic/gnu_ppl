m4_define(`dnl', `m4_dnl')`'dnl
m4_divert(-1)
dnl Copyright (C) 2001-2008 Roberto Bagnara <bagnara@cs.unipr.it>
dnl
dnl This file is part of the Parma Polyhedra Library (PPL).
dnl
dnl The PPL is free software; you can redistribute it and/or modify it
dnl under the terms of the GNU General Public License as published by the
dnl Free Software Foundation; either version 3 of the License, or (at your
dnl option) any later version.
dnl
dnl The PPL is distributed in the hope that it will be useful, but WITHOUT
dnl ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
dnl FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with this program; if not, write to the Free Software Foundation,
dnl Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02111-1307, USA.
dnl
dnl For the most up-to-date information see the Parma Polyhedra Library
dnl site: http://www.cs.unipr.it/ppl/ .
dnl
dnl This file generates ppl_predicate_check.pl.
m4_divert`'dnl
%<--%<--%<-- ppl_predicate_check_main.pl
/* Prolog code for checking all predicates.  -*- C++ -*-
m4_include(`ppl_interface_generator_copyright')`'dnl
*/
m4_divert(-1)
dnl
dnl ==================================================================
dnl Common files are included here
dnl ==================================================================
dnl
m4_include(`ppl_interface_generator_common.m4')
m4_include(`ppl_interface_generator_common_dat.m4')
m4_include(`ppl_interface_generator_prolog_procedure_generators.m4')
m4_include(`ppl_interface_generator_predicate_check_code.m4')

dnl ==================================================================
dnl Useful macros needed to generate the test code.
dnl ==================================================================

dnl m4_filter_code(Schema_Code, Procedure_Spec1, Procedure_Spec1...)
dnl
m4_define(`m4_filter_code', `dnl
m4_ifelse($#, 0, , $#, 1, , $#, 2,
  `m4_ifelse(`$2', `', keep,
    `m4_ifelse(m4_index($1, `m4_regexp($2, `ppl_[^ /]+', `\&')'), -1,
      keep, throw)')',
  `m4_ifelse(m4_index($1, m4_regexp($2, `ppl_[^ /]+', `\&')), -1,
    `m4_filter_code($1, m4_shift(m4_shift($@)))', throw)')')`'dnl

dnl m4_check_test_usability(Procedure_name,
dnl                         Procedure_Spec1, Procedure_Spec1...)
dnl
m4_define(`m4_check_test_usability', `dnl
m4_filter_code(m4_indir($1_code),
  m4_filter_all_procedures($2, 0, m4_procedure_list))`'dnl
')
dnl
dnl
dnl ==================================================================
dnl Now generate the test code.
dnl ==================================================================
dnl
dnl
dnl ==================================================================
dnl Generate code for the include statements.
dnl ==================================================================
dnl
dnl -----------------------------------------------------------------
dnl Extra files and definitions needed
dnl -----------------------------------------------------------------
dnl
m4_pushdef(`m4_one_class_code',
`m4_define(`m4_current_interface', m4_interface_class`'$1)`'dnl
:- include(QUOTE../tests/ppl_predicate_check_`'m4_current_interface`'.plQUOTE).
m4_undefine(`m4_current_interface')`'dnl
')
dnl
dnl -----------------------------------------------------------------
dnl Main call to generate code for the include statements.
dnl -----------------------------------------------------------------
dnl
m4_divert`'dnl
%<--%<--%<-- ppl_predicate_check_main.pl

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                   %
%       Include the common code and all class dependent files       %
%                                                                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:- include('ppl_predicate_check_common.pl').
:- dynamic(all_class_dependent_predicates/1).
:- discontiguous(all_class_dependent_predicates/1).
m4_patsubst(m4_all_code`'m4_changequote(`[*[', `]*]')[*[]*],
                                        QUOTE, [*[']*])[*[]*]dnl
m4_changequote`'dnl
m4_popdef(`m4_one_class_code')`'dnl
dnl
dnl ==================================================================
dnl Generate code for the top-level call
dnl ==================================================================
dnl
dnl -----------------------------------------------------------------
dnl Extra files and definitions
dnl -----------------------------------------------------------------
dnl
m4_pushdef(`m4_one_class_code', `
m4_define(`m4_current_interface', m4_interface_class`'$1)`'dnl
test_`'m4_current_interface`'COMMA`'dnl
m4_undefine(`m4_current_interface')`'dnl
')
dnl
dnl -----------------------------------------------------------------
dnl Main call to generate code
dnl -----------------------------------------------------------------
m4_define(`m4_gen_code', m4_all_code)
m4_divert`'dnl
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                   %
%                       Main call for tests                         %
%                                                                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

check_all :-
  (noisy(_) -> true; make_quiet),
  ppl_initialize, `'dnl
m4_patsubst(m4_gen_code, COMMA, `,')
  ppl_finalize.
m4_popdef(`m4_one_class_code')`'dnl
dnl ==================================================================
dnl Generate code for defining test_<class_name>.
dnl ==================================================================
dnl
dnl -----------------------------------------------------------------
dnl Extra files and definitions
dnl -----------------------------------------------------------------
m4_divert(-1)`'dnl
m4_include(`ppl_interface_generator_prolog_systems.m4')dnl
m4_define(`m4_start1', 0)`'dnl
m4_pushdef(`m4_check_test_usability', keep)`'dnl
m4_pushdef(`m4_extension', `dnl
m4_ifdef(`$1_code',
         `m4_ifelse(m4_check_test_usability($1, $5), keep,
                    `m4_ifelse(m4_start1, 0,
                      `m4_undefine(`m4_start1')  ', `
')'  ``  '($1_$2_test
      -> (!COMMA write_error($1))
      ;  write_success($1))COMMA
`  '')')`'dnl
')`'dnl
dnl
m4_pushdef(`m4_pre_extra_class_code', `dnl
m4_define(`m4_current_interface', m4_interface_class`'$1)`'dnl

%<--%<--%<-- ppl_predicate_check_`'m4_current_interface.pl
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                   %
%                       Main call for tests                         %
%                                                                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
test_`'m4_current_interface :-
m4_undefine(`m4_current_interface')`'dnl
')
m4_pushdef(`m4_post_extra_class_code', `
  true.
')`'dnl
dnl
dnl -----------------------------------------------------------------
dnl Main calls to macros to generate code
dnl -----------------------------------------------------------------
m4_divert`'dnl
m4_patsubst(m4_all_code, COMMA, `,')`'dnl
m4_popdef(`m4_extension')`'dnl
m4_popdef(`m4_pre_extra_class_code')`'dnl
m4_popdef(`m4_post_extra_class_code')`'dnl
dnl  m4_popdef(`m4_check_test_usability')dnl
dnl
dnl ==================================================================
dnl Generate code for the declarations
dnl ==================================================================
dnl
dnl -----------------------------------------------------------------
dnl Extra definitions
dnl -----------------------------------------------------------------
m4_divert(-1)`'dnl
m4_pushdef(`m4_extension', `dnl
m4_ifdef(`$1_code',
         `m4_ifelse(m4_check_test_usability($1, $5), keep,
:- dynamic($1_$2_test/0).
:- discontiguous($1_$2_test/0).)')
')`'dnl
m4_pushdef(`m4_pre_extra_class_code', `
m4_define(`m4_current_interface', m4_interface_class`'$1)`'dnl
%<--%<--%<-- ppl_predicate_check_`'m4_current_interface.pl
m4_undefine(`m4_current_interface')`'dnl
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                   %
%                   discontiguous declarations                      %
%                                                                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
')
dnl -----------------------------------------------------------------
dnl Main call to macros to generate code
dnl -----------------------------------------------------------------
m4_divert`'dnl
m4_all_code`'dnl
m4_popdef(`m4_extension')`'dnl
m4_popdef(`m4_pre_extra_class_code')`'dnl
dnl
dnl ==================================================================
dnl Generate code for the class dependent predicate tests
dnl ==================================================================
dnl
dnl -----------------------------------------------------------------
dnl Extra definitions
dnl -----------------------------------------------------------------
m4_divert(-1)`'dnl
m4_include(`ppl_interface_generator_predicate_check_code.m4')`'dnl
dnl
m4_define(`m4_arg_sequence',
  `m4_ifelse(`$1', 0, ,
     `Arg1`'m4_ifelse(`$1', 1, ,
       `m4_forloop(`i', 2, `$1', `m4_separator Arg`'i')')')')`'dnl
dnl
m4_define(`m4_find_name',
  `m4_regexp($1, `\(ppl_[^ /]+\)', `\1')`'dnl
')`'dnl
dnl
m4_define(`m4_find_arity',
  `m4_regexp($1, `ppl_[^ /]+\(.*\)', `m4_get_arity(\1)')`'dnl
')`'dnl
dnl
m4_define(`m4_make_clean_defs', `dnl
clean_$1`'m4_ifelse(`$2', 0, , `(`'m4_arg_sequence($2))') :-
  ($1`'m4_ifelse(`$2', 0, , `(`'m4_arg_sequence($2))'),
  ppl_cleanup_@CLASS@(Arg`'$2)).
')`'dnl
dnl
m4_define(`m4_replace_patterns_in_clean_defs', `dnl
m4_replace_all_patterns_in_string($1,
                                  m4_make_clean_defs(m4_find_name($2),
                                                     m4_find_arity($2)),
                                  m4_pattern_list)
')`'dnl
dnl
m4_define(`m4_extras', `dnl
m4_ifelse($#, 0, ,
          $#, 1, ,
          $#, 2,
          `m4_ifelse(m4_index($2, new), -1, ,
                     m4_replace_patterns_in_clean_defs($1, $2))',
          `m4_ifelse(m4_index($2, new), -1, ,
                     m4_replace_patterns_in_clean_defs($1, $2))'dnl
`m4_extras($1, m4_shift(m4_shift($@)))')`'dnl
')`'dnl
dnl
m4_define(`m4_pre_extra_class_code', `dnl
m4_define(`m4_current_interface', m4_interface_class`'$1)`'dnl

%<--%<--%<-- ppl_predicate_check_`'m4_current_interface.pl
m4_undefine(`m4_current_interface')`'dnl
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                   %
%               class dependent predicate tests                     %
%                                                                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
m4_replace_all_patterns_in_string($1,
  m4_add_build_class_code($1),
  m4_pattern_list)`'dnl
m4_replace_all_patterns_in_string($1,
  m4_add_comparison_class_code($1),
  m4_pattern_list)`'dnl
m4_replace_all_patterns_in_string($1,
  m4_add_wdn_exn_class_code($1),
  m4_pattern_list)`'dnl
m4_replace_all_patterns_in_string($1,
  m4_add_cleanup_class_code($1),
  m4_pattern_list)`'dnl
m4_replace_all_patterns_in_string($1,
  m4_add_out_class_code($1),
  m4_pattern_list)`'dnl
m4_replace_all_patterns_in_string($1,
  m4_add_out_extra_class_code($1),
  m4_pattern_list)`'dnl
m4_extras($1, m4_procedure_list)
')`'dnl
dnl
m4_pushdef(`m4_default_code', `')`'dnl
dnl
m4_pushdef(`m4_extension', `dnl
m4_ifdef(`$1_code',
`m4_ifelse(m4_check_test_usability($1, $5), keep, `
m4_indir(`$1_code')`'dnl
')', `')
')`'dnl
dnl
dnl -----------------------------------------------------------------
dnl Main call to macros to generate code
dnl -----------------------------------------------------------------
m4_divert`'dnl
m4_all_code`'dnl
m4_popdef(`m4_extension')`'dnl
m4_popdef(`m4_pre_extra_class_code')`'dnl
dnl
dnl ==================================================================
dnl Generate code,
dnl defining the argument of "all_class_dependent_predicates/1",
dnl a list of all the class dependent predicates that are implemented.
dnl ==================================================================
dnl
dnl -----------------------------------------------------------------
dnl Extra files and definitions
dnl -----------------------------------------------------------------
m4_divert(-1)`'dnl
m4_pushdef(`m4_pre_extra_class_code', `
m4_define(`m4_current_interface', m4_interface_class`'$1)`'dnl
%<--%<--%<-- ppl_predicate_check_`'m4_current_interface.pl
m4_undefine(`m4_current_interface')`'dnl
m4_define(`m4_start1', 0)`'dnl
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                                   %
%               class dependent predicate tests                     %
%                                                                   %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

all_class_dependent_predicates(
  [
  ')`'dnl
m4_define(`m4_post_extra_class_code', `
  ]
).
')`'dnl
m4_define(`m4_start1', 0)`'dnl
m4_pushdef(`m4_extension', `dnl
m4_ifelse(m4_start1, 0,
  `m4_undefine(`m4_start1')', `COMMA
')  `$1'dnl
')`'dnl
dnl
dnl -----------------------------------------------------------------
dnl Main calls to macros to generate code
dnl -----------------------------------------------------------------
m4_divert`'dnl
m4_patsubst(m4_all_code, COMMA, `,')`'dnl
m4_popdef(`m4_extension')`'dnl
m4_popdef(`m4_pre_extra_class_code')`'dnl
