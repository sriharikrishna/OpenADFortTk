// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlParentize.h,v 1.2 2004/02/19 22:02:07 eraxxon Exp $

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
//   A WHIRL abstract syntax tree only contains child pointers -- no
//   parent pointers.  WhirlParentMap provides parent pointers -- in
//   an auxillary object -- for times when they would be useful.
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
FindParentWNBlock(const WN* wn_tree, const WN* wn);

//***************************************************************************

// WhirlParentMap
class WhirlParentMap {
public:
  
  WhirlParentMap();
  WhirlParentMap(const WN* wn); // automatically creates the map
  ~WhirlParentMap();
  
  // Create: Given a WN*, creates the map.  Clears any previously existing map.
  void Create(const WN* wn);
  
  // Clear: Clears the map.
  void Clear();

  // Find: Given a WN*, return its parent.  N.B. Does not check that
  // the map exists.
  WN* Find(const WN* wn) { return (WN *)WN_MAP_Get(parentMap, wn); }
  
  // Insert: Given a WN* and its parent, insert in the map. Overwrites
  // any existing value.
  void Insert(const WN* wn, const WN* parent) {
    WN_MAP_Set(parentMap, (WN*)wn, (void *)parent);
  }
  
private:
  void Ctor();
  void Parentize(const WN* wn);
  
private:
  // For now keep the implementation using Open64's WN_MAP
  MEM_POOL memPool;
  WN_MAP parentMap;
};

//***************************************************************************

#endif /* WhirlParentize_h_INCLUDED */
