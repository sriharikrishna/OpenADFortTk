// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlParentize.h,v 1.1 2004/01/25 02:38:11 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlParentize.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Partly based on Open64 be/whirl2c/w2cf_parentize.h
//
//***************************************************************************

#ifndef WhirlParentize_h_INCLUDED
#define WhirlParentize_h_INCLUDED

//************************** System Include Files ***************************


//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

//***************************************************************************

extern WN* 
FindParentWNBlock(WN* wn_tree, WN* wn);

//***************************************************************************

/* ====================================================================
 * ====================================================================
 * Description:
 *  
 *    The W2CF_Parent_Map is defined to be WN_MAP_UNDEFINED in 
 *    w2cf_parentize.c, and must be set by the user of this module
 *    before using any of the utilities (macros or subroutines).
 *
 * ====================================================================
 * ====================================================================
 */

extern WN_MAP W2CF_Parent_Map;

inline const WN *W2CF_Get_Parent(const WN *wn)
{
   return (const WN *)WN_MAP_Get(W2CF_Parent_Map, wn);
} /* W2CF_Get_Parent */

inline void W2CF_Set_Parent(WN *wn, const WN *p)
{
   WN_MAP_Set(W2CF_Parent_Map, wn, (void *)p);
} /* W2CF_Set_Parent */

extern void W2CF_Parentize(const WN* wn);

//***************************************************************************

#endif /* WhirlParentize_h_INCLUDED */