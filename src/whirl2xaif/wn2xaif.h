// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif.h,v 1.20 2004/02/23 18:24:52 eraxxon Exp $

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
#include <lib/support/XAIFStrings.h>
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
// Graph utilities
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
// XAIF xml::ostream utilities
//***************************************************************************

// DumpGraphEdge: Generic edge dumper.  Given an edge name 'nm', id,
// source id, target id and position, dumps the edge in XAIF.  If
// 'pos' is 0 it will not be output.
void 
DumpGraphEdge(xml::ostream& xos, const char* nm, 
	      UINT eid, UINT srcid, UINT targid, UINT pos);

// DumpScopeGraphEdge: Dumps a xaif:ScopeEdge
inline void 
DumpScopeGraphEdge(xml::ostream& xos, UINT eid, UINT srcid, UINT targid)
{
  DumpGraphEdge(xos, "xaif:ScopeEdge", eid, srcid, targid, 0);
}

// DumpCallGraphEdge: Dumps a xaif:CallGraphEdge
inline void 
DumpCallGraphEdge(xml::ostream& xos, UINT eid, UINT srcid, UINT targid)
{
  DumpGraphEdge(xos, "xaif:CallGraphEdge", eid, srcid, targid, 0);
}

// DumpCFGraphEdge: Dumps a xaif:ControlFlowEdge
inline void 
DumpCFGraphEdge(xml::ostream& xos, UINT eid, UINT srcid, UINT targid)
{
  DumpGraphEdge(xos, "xaif:ControlFlowEdge", eid, srcid, targid, 0);
}

// DumpExprGraphEdge: Dumps a xaif:ExpressionEdge
inline void 
DumpExprGraphEdge(xml::ostream& xos, UINT eid, UINT srcid, UINT targid,
		  UINT pos)
{
  DumpGraphEdge(xos, "xaif:ExpressionEdge", eid, srcid, targid, pos);
}


//***************************************************************************
// XAIF xml::ostream operators
//***************************************************************************

// ---------------------------------------------------------
// AttrSymId: Generate an XAIF symbol id attribute
// ---------------------------------------------------------

struct AttrSymTab_ {
  const ST* st;
};

inline ostream&
operator<<(std::ostream& os, const AttrSymTab_& x) 
{
  xml::ostream& xos = dynamic_cast<xml::ostream&>(os); // FIXME

  const char* st_name = ST_name(x.st);
  SymId st_id = (SymId)ST_index(x.st);
  
  xos << xml::BegAttr(XAIFStrings.attr_symId())
      << st_name << "_" << st_id
      << xml::EndAttr;

  return xos;
}

// AttrSymId: Given a symtab symbol (ST*), generate a symbol id attribute
inline AttrSymTab_
AttrSymId(ST* st_)
{
  AttrSymTab_ x;
  x.st = st_;
  return x;
}


// ---------------------------------------------------------
// AttrAnnot, AttrAnnotVal: Generate an XAIF annotation attribute
// ---------------------------------------------------------
template<class T> 
struct AttrAnnotInfo_ {
  bool completeAttr;
  const char* tag;
  const T* val;
};

template<class T> 
ostream&
operator<<(std::ostream& os, const AttrAnnotInfo_<T>& x) 
{
  xml::ostream& xos = dynamic_cast<xml::ostream&>(os); // FIXME

  if (x.completeAttr) {
    xos << xml::BegAttr(XAIFStrings.attr_annot());
  }

  xos << x.tag << *x.val << XAIFStrings.tag_End();
  
  if (x.completeAttr) {
    xos << xml::EndAttr;
  }

  return xos;
}

// AttrAnnot: Given a tag and a value, generate a complete annotiation
// attribute
template<class T> 
AttrAnnotInfo_<T> 
AttrAnnot(const char* tag_, const T& val_)
{
  AttrAnnotInfo_<T> x;
  x.completeAttr = true;
  x.tag = tag_;
  x.val = &val_;
  return x;
}

// AttrAnnotVal: Given a tag and a value, generate only the
// annotiation attribute value
template<class T> 
AttrAnnotInfo_<T>
AttrAnnotVal(const char* tag_, const T& val_)
{
  AttrAnnotInfo_<T> x;
  x.completeAttr = false;
  x.val = &val_;
  x.tag = tag_;
  return x;
}

// *AttrAnnot: Given a value, generate a complete annotiation
// attribute with appropriate tag
template<class T> 
AttrAnnotInfo_<T> 
SymTabIdAnnot(const T& val_) 
{
  return AttrAnnot(XAIFStrings.tag_SymTabId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
SymIdAnnot(const T& val_) 
{
  return AttrAnnot(XAIFStrings.tag_SymId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
PUIdAnnot(const T& val_) 
{
  return AttrAnnot(XAIFStrings.tag_PUId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
WhirlIdAnnot(const T& val_) 
{
  return AttrAnnot(XAIFStrings.tag_WHIRLId(), val_);
}

// *AttrAnnotVal: Given a tag and a value, generate only the
// annotiation attribute value with the appropriate tag
template<class T> 
AttrAnnotInfo_<T>
SymTabIdAnnotVal(const T& val_)
{
  return AttrAnnotVal(XAIFStrings.tag_SymTabId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
SymIdAnnotVal(const T& val_)
{
  return AttrAnnotVal(XAIFStrings.tag_SymId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
PUIdAnnotVal(const T& val_)
{
  return AttrAnnotVal(XAIFStrings.tag_PUId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
WhirlIdAnnotVal(const T& val_)
{
  return AttrAnnotVal(XAIFStrings.tag_WHIRLId(), val_);
}


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

void 
ForAllNonScalarRefs(const WN* wn, ForAllNonScalarRefsOp& op);


//***************************************************************************

#endif /* wn2xaif_h */
