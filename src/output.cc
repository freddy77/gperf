/* Output routines.
   Copyright (C) 1989-1998, 2000, 2002-2004, 2006-2007, 2009, 2011-2012, 2016, 2018, 2021 Free Software Foundation, Inc.
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

/* Specification. */
#include "output.h"

#include <stdio.h>
#include <limits.h> /* defines SCHAR_MAX etc. */
#include "options.h"
#include "output-c.h"
#include "version.h"
#include "config.h"

/* ========================================================================= */

/* Constructor.
   Note about the keyword list starting at head:
   - The list is ordered by increasing _hash_value.  This has been achieved
     by Search::sort().
   - Duplicates, i.e. keywords with the same _selchars set, are chained
     through the _duplicate_link pointer.  Only one representative per
     duplicate equivalence class remains on the linear keyword list.
   - Accidental duplicates, i.e. keywords for which the _asso_values[] search
     couldn't achieve different hash values, cannot occur on the linear
     keyword list.  Search::optimize would catch this mistake.
 */
Output::Output (KeywordExt_List *head, const char *struct_decl,
                unsigned int struct_decl_lineno, const char *return_type,
                const char *struct_tag, const char *verbatim_declarations,
                const char *verbatim_declarations_end,
                unsigned int verbatim_declarations_lineno,
                const char *verbatim_code, const char *verbatim_code_end,
                unsigned int verbatim_code_lineno, bool charset_dependent,
                int total_keys, int max_key_len, int min_key_len,
                bool hash_includes_len, const Positions& positions,
                const unsigned int *alpha_inc, int total_duplicates,
                unsigned int alpha_size, const int *asso_values)
  : _head (head), _struct_decl (struct_decl),
    _struct_decl_lineno (struct_decl_lineno), _return_type (return_type),
    _struct_tag (struct_tag),
    _verbatim_declarations (verbatim_declarations),
    _verbatim_declarations_end (verbatim_declarations_end),
    _verbatim_declarations_lineno (verbatim_declarations_lineno),
    _verbatim_code (verbatim_code),
    _verbatim_code_end (verbatim_code_end),
    _verbatim_code_lineno (verbatim_code_lineno),
    _charset_dependent (charset_dependent),
    _total_keys (total_keys),
    _max_key_len (max_key_len), _min_key_len (min_key_len),
    _hash_includes_len (hash_includes_len),
    _key_positions (positions), _alpha_inc (alpha_inc),
    _total_duplicates (total_duplicates), _alpha_size (alpha_size),
    _asso_values (asso_values)
{
  compute_min_max ();
}

/* ------------------------------------------------------------------------- */

/* Computes the minimum and maximum hash values, and stores them
   in _min_hash_value and _max_hash_value.  */

void
Output::compute_min_max ()
{
  /* Since the list is already sorted by hash value all we need to do is
     to look at the first and the last element of the list.  */

  _min_hash_value = _head->first()->_hash_value;

  KeywordExt_List *temp;
  for (temp = _head; temp->rest(); temp = temp->rest())
    ;
  _max_hash_value = temp->first()->_hash_value;
}

/* ------------------------------------------------------------------------- */

/* Returns the number of different hash values.  */

int
Output::num_hash_values () const
{
  /* Since the list is already sorted by hash value and doesn't contain
     duplicates, we can simply count the number of keywords on the list.  */
  int count = 0;
  for (KeywordExt_List *temp = _head; temp; temp = temp->rest())
    count++;
  return count;
}

Output *
create_output (KeywordExt_List *head,
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
               const int *asso_values)
{
  return new Output_C (head, struct_decl, struct_decl_lineno,
                       return_type, struct_tag,
                       verbatim_declarations, verbatim_declarations_end,
                       verbatim_declarations_lineno,
                       verbatim_code, verbatim_code_end,
                       verbatim_code_lineno,
                       charset_dependent, total_keys,
                       max_key_len, min_key_len,
                       hash_includes_len, positions,
                       alpha_inc, total_duplicates,
                       alpha_size, asso_values);
}
