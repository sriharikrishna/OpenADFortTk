// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/w2cf_parentize.cxx,v 1.2 2003/06/02 13:43:22 eraxxon Exp $
// -*-C++-*-

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/w2cf_parentize.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2c/w2cf_parentize.cxx
//
//***************************************************************************

#include "Open64BasicTypes.h"

#include "w2cf_parentize.h"

WN_MAP W2CF_Parent_Map = WN_MAP_UNDEFINED;


void 
W2CF_Parentize(const WN* wn)
{
   /* Given a tree, initialize its parent pointers.
    * Override what was there, if anything.
    * Do not update parent pointer of the root node 'wn'.
    * This is copied from be/lno/lwn_util.h!
    */
  OPERATOR opr = WN_operator(wn);
  
  if (!OPERATOR_is_leaf(opr)) {
    if (opr == OPR_BLOCK) { // WN_opcode(wn) == OPC_BLOCK
      WN *kid = WN_first(wn);
      while (kid) {
	W2CF_Set_Parent(kid, wn);
	W2CF_Parentize(kid);
	kid = WN_next(kid);
      }
    } else {
      INT kidno;
      WN *kid;
      for (kidno=0; kidno < WN_kid_count(wn); kidno++) {
	kid = WN_kid (wn, kidno);
	if (kid) { 
	  W2CF_Set_Parent(kid, wn);
	  W2CF_Parentize(kid);
	}
      }
    }
  }
} /* W2FC_Parentize */
