// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/PUinfo.h,v 1.5 2004/02/20 18:57:41 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/PUinfo.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2c/PUinfo.h
//
//***************************************************************************

#ifndef PUinfo_INCLUDED
#define PUinfo_INCLUDED
/* ====================================================================
 * ====================================================================
 *
 * Revision history:
 *   26-Dec-94 - Original Version
 *
 * Description:
 *
 *   Maintains information about the scope and block associated with
 *   a program unit (function/procedure).  We have defined three
 *   data-structures for accessing information about call-sites,
 *   return-sites, and function return types respectively.  The
 *   interface is as follows:
 *
 *  Interface routines:
 *  -------------------
 *    PUinfo_init_pu:
 *      Given the OPC_FUNC_ENTRY node for a PU, and a subtree under
 *      that block, this function will traverse the current symbol-
 *      table, and the subtree to accumulate information needed 
 *      in the actual translation of the given subtree to a HLL.  
 *      The other functions provided in the interface to this file 
 *      will allow us to access the information accumulated during 
 *      this prepass over the subtree.  Note that no WHIRL->HLL
 *      translation is expected outside the given subtree!
 *
 *    PUinfo_exit_pu:
 *      Free up the information accumulated by means of PUinfo_init_pu().
 *      This may not literally free up memory, but may make it
 *      available for reuse when processing the next PU.
 *
 * ====================================================================
 * ====================================================================
 */

#include <include/Open64BasicTypes.h>

extern void PUinfo_init_pu(const WN *wn, WN *body_part_of_interest);
extern void PUinfo_exit_pu(void);

#endif /* PUinfo_INCLUDED */

