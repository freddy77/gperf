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

#ifndef output_h
#define output_h 1

#include "keyword-list.h"
#include "positions.h"

class Output
{
public:
  /* Constructor.  */
                        Output (KeywordExt_List *head,
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

  /* Destructor.  */
  virtual               ~Output () {};

  /* Generates the hash function and the key word recognizer function.  */
  virtual void /*abstract*/
                        output () = 0;

protected:

  /* Returns the number of different hash values.  */
  int                   num_hash_values () const;

  /* Linked list of keywords.  */
  KeywordExt_List *     _head;

  /* Declaration of struct type for a keyword and its attributes.  */
  const char * const    _struct_decl;
  unsigned int const    _struct_decl_lineno;
  /* Pointer to return type for lookup function. */
  const char *          _return_type;
  /* Shorthand for user-defined struct tag type. */
  const char *          _struct_tag;
  /* The C code from the declarations section.  */
  const char * const    _verbatim_declarations;
  const char * const    _verbatim_declarations_end;
  unsigned int const    _verbatim_declarations_lineno;
  /* The C code from the end of the file.  */
  const char * const    _verbatim_code;
  const char * const    _verbatim_code_end;
  unsigned int const    _verbatim_code_lineno;
  /* Whether the keyword chars would have different values in a different
     character set.  */
  bool                  _charset_dependent;
  /* Total number of keys, counting duplicates. */
  int const             _total_keys;
  /* Maximum length of the longest keyword. */
  int const             _max_key_len;
  /* Minimum length of the shortest keyword. */
  int const             _min_key_len;
  /* Whether the hash function includes the length.  */
  bool                  _hash_includes_len;
  /* Key positions.  */
  Positions const       _key_positions;
  /* Adjustments to add to bytes add specific key positions.  */
  const unsigned int * const _alpha_inc;
  /* Total number of duplicate hash values. */
  int const             _total_duplicates;
  /* Minimum hash value for all keywords. */
  int                   _min_hash_value;
  /* Maximum hash value for all keywords. */
  int                   _max_hash_value;
  /* Size of alphabet. */
  unsigned int const    _alpha_size;
  /* Value associated with each character. */
  const int * const     _asso_values;

private:

  /* Computes the minimum and maximum hash values, and stores them
     in _min_hash_value and _max_hash_value.  */
  void                  compute_min_max ();
};

Output * create_output (KeywordExt_List *head,
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

#endif
