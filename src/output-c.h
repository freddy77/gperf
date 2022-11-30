/* This may look like C code, but it is really -*- C++ -*- */

/* Output routines.

   Copyright (C) 1989-1998, 2000, 2002-2003, 2009, 2016 Free Software Foundation, Inc.
   Written by Douglas C. Schmidt <schmidt@ics.uci.edu>
   and Bruno Haible <bruno@clisp.org>.

   This file is part of GNU GPERF.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#ifndef output_c_h
#define output_c_h 1

#include "output.h"

/* OSF/1 cxx needs these forward declarations. */
struct Output_Constants;
struct Output_Compare;

class Output_C : public Output
{
public:
  /* Constructor.  */
                        Output_C (KeywordExt_List *head,
                                  const char *struct_decl,
                                  unsigned int struct_decl_lineno,
                                  const char *return_type,
                                  const char *struct_tag,
                                  const char *verbatim_declarations,
                                  const char *verbatim_declarations_end,
                                  unsigned int verbatim_declarations_lineno,
                                  const char *verbatim_code,
                                  const char *verbatim_code_end,
                                  unsigned int verbatim_code_lineno,
                                  bool charset_dependent,
                                  int total_keys,
                                  int max_key_len, int min_key_len,
                                  bool hash_includes_len,
                                  const Positions& positions,
                                  const unsigned int *alpha_inc,
                                  int total_duplicates,
                                  unsigned int alpha_size,
                                  const int *asso_values);

  /* Generates the hash function and the key word recognizer function.  */
  void                  output () override;

private:

  /* Outputs the maximum and minimum hash values etc.  */
  void                  output_constants (struct Output_Constants&) const;

  /* Generates a C expression for an asso_values[] index.  */
  void                  output_asso_values_index (int pos) const;

  /* Generates a C expression for an asso_values[] reference.  */
  void                  output_asso_values_ref (int pos) const;

  /* Generates C code for the hash function that returns the
     proper encoding for each keyword.  */
  void                  output_hash_function () const;

  /* Prints out a table of keyword lengths, for use with the
     comparison code in generated function 'in_word_set'.  */
  void                  output_keylength_table () const;

  /* Prints out the string pool, containing the strings of the keyword table.
   */
  void                  output_string_pool () const;

  /* Prints out the array containing the keywords for the hash function.  */
  void                  output_keyword_table () const;

  /* Generates the large, sparse table that maps hash values into
     the smaller, contiguous range of the keyword table.  */
  void                  output_lookup_array () const;

  /* Generate all pools needed for the lookup function.  */
  void                  output_lookup_pools () const;

  /* Generate all the tables needed for the lookup function.  */
  void                  output_lookup_tables () const;

  /* Generates C code to perform the keyword lookup.  */
  void                  output_lookup_function_body (const struct Output_Compare&) const;

  /* Generates C code for the lookup function.  */
  void                  output_lookup_function () const;

  /* Element type of keyword array.  */
  const char *          _wordlist_eltype;
};

#endif
