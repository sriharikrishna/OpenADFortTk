// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Attic/w2cf_symtab.h,v 1.4 2003/08/19 14:05:10 eraxxon Exp $

// * BeginCopyright *********************************************************
/*
  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan
*/
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Attic/w2cf_symtab.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2c/w2cf_symtab.h
//
//***************************************************************************

#ifndef w2cf_symtab_INCLUDED
#define w2cf_symtab_INCLUDED
/* ====================================================================
 * ====================================================================
 *
 * Description:
 *  
 *  The symbol table has been implemented as a state-machine maintaining
 *  a stack of symbol-tables.  There are routines to push and pop symbol 
 *  tables, get the name of a given symbol, enter symbols into the 
 *  current symbol table, push and pop symbol tables, etc.
 *
 *  The memory allocated to hold symbol-names and the symbol-table data
 *  structure is never freed up until the use of this package is
 *  terminated or a forced free operation is invoked.
 *
 *  W2CF_Symtab_Push: Pushes a new symbol table onto the stack and
 *     makes it the current symbol-table new symbol entries.
 *
 *  W2CF_Symtab_Pop: Pops the last symbol table entered onto the stack
 *     off the stack, putting all related symbol-table objects onto
 *     free-lists.
 *
 *  W2CF_Symtab_Nameof_St:
 *  W2CF_Symtab_Nameof_St_Pointee:
 *  W2CF_Symtab_Nameof_Ty:
 *  W2CF_Symtab_Nameof_Fld:
 *  W2CF_Symtab_Nameof_Fld_Pointee:
 *  W2CF_Symtab_Nameof_Tempvar:
 *  W2CF_Symtab_Nameof_Preg:
 *     Tries to find the symbol in the symbol table, and if it has been
 *     found, returns its assigned name.  Numerical suffices are added 
 *     to names to disambiguate them from one another.  An attempt will
 *     be made to retain numeric suffices to names, but since such 
 *     suffices are used by this module to disambiguate names they may
 *     sometime be changed.
 *
 *  W2CF_Symtab_Unique_Name:
 *     Adds a name to the symbol table, which matches no other name.
 *     An attempt will be made to keep the name as it is given, but
 *     name-clashes may change it.  There is no way to retrieve this
 *     name again, as its sole purpose is to permanently occupy a
 *     slot in the current symbol-table.
 *
 *  W2CF_Symtab_Unique_Label:
 *     This assumes that label-numbers around 99999 are not used.
 *     Starting with that number, this function returns a number
 *     decremented by one every time it is called.
 *
 *  W2CF_Symtab_Free: Frees up from memory all objects kept on free-
 *     lists, i.e. all symbol-table related information that was used
 *     at some point, but which is not currently in use.
 *
 *  W2CF_Symtab_Terminate: Pops all symbol-tables off the stack and
 *     frees up all memory allocated.  Resets the state to allow
 *     subsequent use of this module.
 *
 * ====================================================================
 * ====================================================================
 */


#include <include/Open64BasicTypes.h>


void W2CF_Symtab_Push(void);
void W2CF_Symtab_Pop(void);

const char * W2CF_Symtab_Nameof_St(const ST *st);
const char * W2CF_Symtab_Nameof_St_Pointee(const ST *st);
const char * W2CF_Symtab_Nameof_Ty(TY_IDX ty);
const char * W2CF_Symtab_Nameof_Fld(FLD_HANDLE fld);
const char * W2CF_Symtab_Nameof_Fld_Pointee(FLD_HANDLE fld);
const char * W2CF_Symtab_Nameof_Tempvar(INT32 tempvar_id);

/* Solaris CC workaround
 * See Forte C++ Documentation
 * This is a feature in Solaris CC compiler's name mangling,
 * "const" parameter and general parameter has different name mangling
 * on the function name
 */
#if defined(_SOLARIS_SOLARIS) && !defined(__GNUC__)
const char * W2CF_Symtab_Nameof_Preg(const TY_IDX preg_ty, PREG_NUM preg_num);
#else
const char * W2CF_Symtab_Nameof_Preg(TY_IDX preg_ty, PREG_NUM preg_num);
#endif

const char * W2CF_Symtab_Unique_Name(const char *name);
UINT32 W2CF_Symtab_Unique_Label(void);

void W2CF_Symtab_Free(void);
void W2CF_Symtab_Terminate(void);


/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 * This file is to be included in all major translating modules
 * belonging to whirl2f.  It includes all files that these modules
 * will depend on and defines some utilities that are generally
 * useful.
 *
 *    Identifier Naming
 *    -----------------
 *       We provide some utilities for creating identifier names.  For
 *       names that are generated or altered by whirl2f, these utilities
 *       can be used to prepend a reserved whirl2f prefix (e.g. "w2f$").
 *       While this moves names outside of the user's name-space, it
 *       does not prevent prefixed names from being overloaded.
 *
 *       Note that this is all fine and dandy for local names, while
 *       some extra work is required by the caller of these routines
 *       for external names.  An external name ending in '_' should
 *       be converted into a name without the '_', while an external
 *       name not ending in a '_' should be suffixed by a '$'.  This
 *       will be left to the users of the routines provided here, since
 *       we do not know whether or not a name is external in this
 *       module.
 *
 *       WHIRL2F_number_as_name: Converts the given number into
 *          a valid Fortran identifier (prefixed by WHIRL2F_prefix).
 *
 *       WHIRL2F_ptr_as_name: Converts the given pointer value
 *           into a valid Fortran identifier.  Note that the number
 *           may be a 32 or 64 bits value, depending on the pointer
 *           representation and will be prefixed by WHIRL2F_prefix.
 *
 *       WHIRL2F_make_valid_name: If the given name is already a
 *          valid Fortran name, then it is simply returned.  If the name
 *          is NULL, then return NULL.  Otherwise, construct a valid
 *          Fortran identifier by removing invalid characters, thus
 *          returning a non-NULL name.
 *
 * ====================================================================
 * ====================================================================
 */

   /* Error checking during type accesses */
   /*-------------------------------------*/

#define W2F_TY_pointed(ty, msg) \
   (ASSERT_DBG_FATAL(TY_Is_Pointer(ty), (DIAG_W2F_EXPECTED_PTR, (msg))), \
    TY_pointed(ty))

                     /* Identifier naming */
                     /*-------------------*/

#define WHIRL2F_number_as_name(number) Num2Str(number, "%lld")
   
#define WHIRL2F_ptr_as_name(ptr) Ptr_as_String(ptr)

extern const char * WHIRL2F_make_valid_name(const char *name, BOOL allow_dot);

/* This variable is TRUE for Fortran 90 program units */
extern BOOL WN2F_F90_pu;



#endif /* w2cf_symtab */
