// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/PUinfo.cxx,v 1.8 2004/02/17 18:53:48 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/PUinfo.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2c/PUinfo.cxx
//
//***************************************************************************

/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *    Maintains information pertaining to the translation of compilation
 *    units, and provides routines for collecting such information:
 *
 *       * Symbol-name and Symbol-id information
 *
 *       * Preg usage information
 *
 *       * Function call and return site information
 *
 *    The details of the information collected here may vary between 
 *    whirl2f and whirl2c, but every collection of information 
 *    pertains to both.  A collection of information pertaining only
 *    to one or the other should be maintained in a module specific
 *    to one or the other, not here.
 *
 * ====================================================================
 * ====================================================================
 */

//************************* System Include Files ****************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "PUinfo.h"
#include "whirl2f_common.h"

#include <lib/support/WhirlParentize.h>

//*************************** Forward Declarations ***************************

//****************************************************************************

/*------------------ Some PU state variables --------------------------*
 *---------------------------------------------------------------------*/

const WN          *PUinfo_current_func = NULL; /* OPR_FUNC_ENTRY node */

/*--------------- Information about the local PU symbols --------------
 *
 * We enter the local declarations for a PU into the name-disambiguation 
 * symbol table before attempting any translation of the PU.  This 
 * ensures that the symbol names remain invariant regardless whether or 
 * not we translate only a small portion of the PU.
 *---------------------------------------------------------------------*/

static void
Enter_Local_Syms_Into_Symtab(const ST *func_st)
{
   ST_IDX    st_idx;
   const ST *st;

   (void)W2CF_Symtab_Nameof_St(func_st);
   FOREACH_SYMBOL(CURRENT_SYMTAB, st, st_idx)
   {
      if ((ST_sym_class(st) == CLASS_VAR || ST_sym_class(st) == CLASS_FUNC) &&
	  !Stab_Is_Based_At_Common_Or_Equivalence(st))
      {
#ifdef BUILD_WHIRL2F
	 if (TY_Is_Pointer(ST_type(st)))
	    (void)W2CF_Symtab_Nameof_St_Pointee(st);
#endif
	 (void)W2CF_Symtab_Nameof_St(st);
      }
   }
} /* Enter_Local_Syms_Into_Symtab */


/*------------------------ exported routines --------------------------*/
/*---------------------------------------------------------------------*/

void 
PUinfo_init_pu(const WN *pu, WN *body_part_of_interest)
{
   /* TODO: Handle nested procedures and call/return list stacks.
    * NOTE: This should never cause side-effects to the incoming
    *       PU (e.g. creating a pointer type), without making
    *       sure this is handled by W2C_Pop_Pu() in w2c_driver.c
    *       and W2F_Pop_Pu() in w2f_driver.c.xc
    */
   Is_True(WN_operator(pu) == OPR_FUNC_ENTRY,
	   ("Expected an OPR_FUNC_ENTRY node in PUinfo_init()"));
   Is_True(PUinfo_current_func == NULL, ("Unexpected in PUinfo_init_pu()"));

   PUinfo_current_func = pu; /* PUINFO_RETURN_TY uses this! */

   /* Push a new symbol-table for name-disambiguation, and enter 
    * every pseudo-register, variable, function, constant, and type
    * of this PU scope into the symbol-table.  The former 
    * accumulative prepass over the expression trees should have 
    * determined all preg uses.
    */
   W2CF_Symtab_Push();
   Enter_Local_Syms_Into_Symtab(&St_Table[WN_entry_name(pu)]);
   
} /* PUinfo_init_pu */


void 
PUinfo_exit_pu(void)
{
   /* Pop the current symbol-table for name-disambiguation */
   W2CF_Symtab_Pop();
   
   PUinfo_current_func = NULL; /* Reset the PU state */
} /* PUinfo_exit_pu */

