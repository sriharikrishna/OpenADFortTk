// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.i,v 1.3 2003/07/24 14:36:15 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.i,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/whirl2f_common.h
//
//***************************************************************************

#ifndef whirl2f_common_INCLUDED

#include "stab_attr.h"
#include "wn_attr.h"
#include "w2cf_symtab.h"
#include "diagnostics.h"

//***************************************************************************

//FIXME
extern BOOL W2F_Verbose;         /* Show translation information */
extern BOOL W2F_Old_F77;         /* Use macros for new intrinsics */
extern BOOL W2F_Ansi_Format;     /* Line-formatting to f77 standard */
extern BOOL W2F_No_Pragmas;      /* Do not emit pragmas */
extern BOOL W2F_Emit_Prefetch;   /* Emit comments for prefetches */
extern BOOL W2F_Emit_All_Regions;/* Emit cmplr-generated regions */
extern BOOL W2F_Emit_Linedirs;   /* Emit preprocessing line-directives */

//***************************************************************************

#define whirl2xaif_divider_comment \
  "********************************************************************"

/* Ensure that we never refer to Cur_PU_Name, since this will not be
 * initialized, but instead use the PUinfo facilities.
 */
#define Cur_PU_Name You_should_not_use("Cur_PU_Name")


typedef mUINT32 WN2F_STATUS;
#define EMPTY_WN2F_STATUS (WN2F_STATUS)0

//***************************************************************************

// W2FC flag accessors..
extern void Set_TY_is_translated_to_c(const TY_IDX ty);
extern void Reset_TY_is_translated_to_c(const TY_IDX ty);
extern BOOL TY_is_translated_to_c(const TY_IDX ty);
extern void Clear_w2fc_flags(void);

/* Some general utility routines for memory allocation.  Include
 * "mempool.h" when using these!
 */
#define TYPE_ALLOC_N(type, count)\
   TYPE_MEM_POOL_ALLOC_N(type, Malloc_Mem_Pool, count)

#define TYPE_REALLOC_N(type, old_ptr, old_count, new_count)\
   TYPE_MEM_POOL_REALLOC_N(type, Malloc_Mem_Pool, old_ptr,\
			   old_count, new_count)

#define FREE(ptr) MEM_POOL_FREE(Malloc_Mem_Pool, ptr)

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


#endif /* whirl2f_common_INCLUDED */
