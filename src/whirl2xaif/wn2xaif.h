// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif.h,v 1.18 2004/02/19 22:02:30 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f.h
//
//***************************************************************************

#ifndef wn2xaif_h
#define wn2xaif_h

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "whirl2xaif.i"
#include "XlationContext.h"
#include <lib/support/xmlostream.h>
#include <lib/support/IntrinsicXlationTable.h>

//************************** Forward Declarations ***************************

//***************************************************************************
// Commonly used WHIRL translation functions
//***************************************************************************

namespace whirl2xaif {
  
  extern IntrinsicXlationTable IntrinsicTable;
  
  // TranslateWN: Given a translation context, translates the given
  // WHIRL node, emitting output to 'xos'.
  extern whirl2xaif::status 
  TranslateWN(xml::ostream& xos, WN *wn, XlationContext& ctxt);

  // xlate_SymRef: Given a base symbol 'base_st' and an offset 'offset'
  // within it, generate an XAIF expression to reference an object of
  // 'ref_ty' at this location.  The base symbol 'base_st' has an
  // address of type 'baseptr_ty'.
  extern whirl2xaif::status
  xlate_SymRef(xml::ostream& xos, ST* base_st, TY_IDX baseptr_ty, 
	       TY_IDX ref_ty, STAB_OFFSET offset, XlationContext& ctxt);
  
  // xlate_MemRef: 
  extern whirl2xaif::status 
  xlate_MemRef(xml::ostream& xos, WN* addr, TY_IDX addr_ty, TY_IDX object_ty,
	       STAB_OFFSET addr_offset, XlationContext& ctxt);
  
}; /* namespace whirl2xaif */


// REMOVE/FIXME
// WN2F_Sum_Offsets:  Sums any ADD nodes encountered in an address tree
// WN2F_Address_Of: Generates an expression to explicitly take the
// address of the lvalue constituted by the tokens in the given
// token-buffer.
extern void WN2F_Address_Of(xml::ostream& xos);
extern WN_OFFSET WN2F_Sum_Offsets(WN *addr);


//***************************************************************************
// 
//***************************************************************************

class DGraph;
class DGraph::Node;
class DGraph::Edge;

typedef std::vector<DGraph::Node*> DGraphNodeVec;
typedef std::vector<DGraph::Edge*> DGraphEdgeVec;

// SortDGraphNodes: Sorts DGraph nodes.  User must deallocate returned
// object.
extern DGraphNodeVec*
SortDGraphNodes(DGraph* g);

// SortDGraphEdges: Sorts DGraph edges.  User must deallocate returned
// object.
extern DGraphEdgeVec*
SortDGraphEdges(DGraph* g);

//***************************************************************************
// 
//***************************************************************************

// FIXME: 
// ForAllNonScalarRefsOp: Abstract base class for the operator passed
// to the function 'ForAllNonScalarRefs(...)'.  Any caller of this
// function must define its own operator object, using this class
// as a base class and providing a definition for 'operator()'.
class ForAllNonScalarRefsOp {
public:
  ForAllNonScalarRefsOp() { }
  virtual ~ForAllNonScalarRefsOp() { }

  // Given a non-scalar reference 'wn', does something interesting.
  // Returns 0 on success; non-zero on error.
  virtual int operator()(const WN* wn) = 0;
private: 
};


//FIXME: locate elsewhere...
#include <lib/support/SymTab.h> // FIXME

// Given a symbol table, add references to it
class AddToNonScalarSymTabOp : public ForAllNonScalarRefsOp {
public:
  AddToNonScalarSymTabOp(NonScalarSymTab* symtab_);
  ~AddToNonScalarSymTabOp() { }
  
  NonScalarSymTab* GetSymTab() { return symtab; }

  // Given a non-scalar reference 'wn', create a dummy variable and
  // add to the map.  
  int operator()(const WN* wn);

private:
  NonScalarSymTab* symtab;
};

void 
ForAllNonScalarRefs(const WN* wn, ForAllNonScalarRefsOp& op);


//***************************************************************************

#endif /* wn2xaif_h */
