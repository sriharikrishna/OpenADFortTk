// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlParentize.cxx,v 1.2 2004/02/19 22:02:07 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlParentize.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Partly based on Open64 be/whirl2c/w2cf_parentize.cxx
//
//***************************************************************************

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "WhirlParentize.h"

//************************** Forward Declarations ***************************

//***************************************************************************

// FIXME: FindParentWNBlock was written before I learned about the
// parent map.  I should rewrite the former to use the latter.


// FindParentWNBlock: Given two WHIRL nodes, a subtree 'wn_tree' and an
// some descendent 'wn', return the BLOCK WN that contains 'wn', or
// NULL.
WN* 
FindParentWNBlock(const WN* wn_tree, const WN* wn)
{
  if (!wn_tree || !wn) { return NULL; }

  OPERATOR opr = WN_operator(wn_tree);
  if (!OPERATOR_is_scf(opr)) {
    // 'wn_tree' is not structured control flow and cannot contain blocks
    return NULL;
  } else {

    WN* blkWN = NULL;
    if (opr == OPR_BLOCK) {
      
      // Test to see if 'wn' is a child of 'wn_tree'
      WN *kid = WN_first(wn_tree);
      while (kid) {
	
	// Test this child
	if (kid == wn) {
	  return const_cast<WN*>(wn_tree); // we found the parent block|
	} 

	// Recursively test 
	if ( (blkWN = FindParentWNBlock(kid, wn)) ) {
	  return blkWN;
	}

	kid = WN_next(kid);
      }
    } else {
      
      // Recur on for non-block structured control flow
      for (INT kidno = 0; kidno < WN_kid_count(wn_tree); kidno++) {
	WN* kid = WN_kid(wn_tree, kidno);
	if ( (blkWN = FindParentWNBlock(kid, wn)) ) {
	  return blkWN;
	}
      }

    }

    return NULL; // not found
  }
}

//***************************************************************************
// WhirlParentMap
//***************************************************************************

// Note: whirl2f implementation of parentizing for each PU
// W2F_Push_PU
//   MEM_POOL_Push(&W2F_Parent_Pool);
//   W2CF_Parent_Map = WN_MAP_Create(&W2F_Parent_Pool);
//   W2CF_Parentize(pu);
// W2F_Pop_PU
//   WN_MAP_Delete(W2CF_Parent_Map);
//   W2CF_Parent_Map = WN_MAP_UNDEFINED;
//   MEM_POOL_Pop(&W2F_Parent_Pool);

WhirlParentMap::WhirlParentMap() 
{
  Ctor();
}

WhirlParentMap::WhirlParentMap(const WN* wn)
{
  Ctor();
  Create(wn);
}

void 
WhirlParentMap::Ctor()
{
  // Create a pool to hold the parent map for every PU, one at a time.
  MEM_POOL_Initialize(&memPool, "WhirlParentMap_Pool", FALSE);
  MEM_POOL_Push(&memPool);   
  parentMap = WN_MAP_UNDEFINED;
}

WhirlParentMap::~WhirlParentMap() 
{ 
  MEM_POOL_Pop(&memPool);
  MEM_POOL_Delete(&memPool);
}

void 
WhirlParentMap::Create(const WN* wn)
{
  if (parentMap != WN_MAP_UNDEFINED) {
    Clear();
  }
  
  parentMap = WN_MAP_Create(&memPool);
  Parentize(wn);
}

void 
WhirlParentMap::Clear()
{
  WN_MAP_Delete(parentMap);
  parentMap = WN_MAP_UNDEFINED;
}

// Parentize: Given a tree, initialize its parent pointers, overriding
// anything that may have been in the map.  Does not update parent
// pointer of the root node 'wn'.
void 
WhirlParentMap::Parentize(const WN* wn)
{
  OPERATOR opr = WN_operator(wn);
  
  if (!OPERATOR_is_leaf(opr)) {
    if (opr == OPR_BLOCK) { // WN_opcode(wn) == OPC_BLOCK
      WN *kid = WN_first(wn);
      while (kid) {
	Insert(kid, wn);
	Parentize(kid);
	kid = WN_next(kid);
      }
    } else {
      for (INT kidno = 0; kidno < WN_kid_count(wn); kidno++) {
	WN* kid = WN_kid(wn, kidno);
	if (kid) { 
	  Insert(kid, wn);
	  Parentize(kid);
	}
      }
    }
  }
}

