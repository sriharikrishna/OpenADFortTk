// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/XlationContext.cxx,v 1.15 2004/06/02 02:01:28 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/XlationContext.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f.cxx
//
//***************************************************************************

//************************** System Include Files ***************************

#include <stdio.h>

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

#include "XlationContext.h"
#include <lib/support/SymTab.h>

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// XlationContext
//***************************************************************************

XlationContext::XlationContext()
  : flags(0), 
    wnParentMap(NULL), stab2idMap(NULL), pu2idMap(NULL), wn2idMap(NULL),
    wn2vnMap(NULL), nssymtab(NULL)
{
  ctxtstack.push_front(Ctxt());
}

XlationContext::~XlationContext()
{
  ctxtstack.clear(); // clear the stack
}


// -------------------------------------------------------
// Context manipulation (Create, Delete...)
// -------------------------------------------------------

XlationContext&
XlationContext::CreateContext()
{
  return Ctor(NOFLAG, NULL);
}

XlationContext&
XlationContext::CreateContext(uint32_t flags_)
{
  return Ctor(flags_, NULL);
}

XlationContext&
XlationContext::CreateContext(uint32_t flags_, WN* wn_)
{
  return Ctor(flags_, wn_);
}

XlationContext&
XlationContext::Ctor(uint32_t flags_, WN* wn_)
{
  // If available, get enclosing context
  const Ctxt* enclCtxt = NULL;
  if (ctxtstack.size() > 0) {
    enclCtxt = &(ctxtstack.front());
  }
  
  // Create new context
  ctxtstack.push_front(Ctxt());
  CurContext().SetFlags(flags_);
  CurContext().SetWN(wn_);

  // Set inherited flags from enclosing context
  Ctxt& curCtxt = CurContext();
  if (enclCtxt->AreFlags(ASSIGN)) { curCtxt.SetFlags(ASSIGN); }
  if (enclCtxt->AreFlags(VARREF)) { curCtxt.SetFlags(VARREF); }
  
  return (*this);
}

XlationContext&
XlationContext::DeleteContext()
{
  if (ctxtstack.size() > 1) {
    // maintain invariant that there is at least one context
    ctxtstack.pop_front();
  }
  return (*this);
}


// -------------------------------------------------------
// 
// -------------------------------------------------------

WN* 
XlationContext::GetWN_MR()
{
  for (XlationContextIterator it(*this); it.IsValid(); ++it) {
    Ctxt* ctxt = it.Current();
    WN* wn = ctxt->GetWN();
    if (wn) { return wn; }
  }
  return NULL;
}


// -------------------------------------------------------
// Procedure-level maps/data
// -------------------------------------------------------

WN*
XlationContext::FindParentWN(WN* wn)
{
  if (wnParentMap) { return (wnParentMap->Find(wn)); }
  return NULL;
}

WN*
XlationContext::FindParentBlockWN(WN* wn)
{
  if (wnParentMap) { return (wnParentMap->FindBlock(wn)); }
  return NULL;
}

SymTabId
XlationContext::FindSymTabId(ST_TAB* stab)
{
  if (stab2idMap) { return (stab2idMap->Find(stab)); }
  return 0;
}

PUId
XlationContext::FindPUId(PU_Info* pu)
{
  if (pu2idMap) { return (pu2idMap->Find(pu)); }
  return 0;
}

WNId
XlationContext::FindWNId(WN* wn)
{
  if (wn2idMap) { return wn2idMap->Find(wn); }
  return 0;
}

VN
XlationContext::FindVN(WN* wnexpr)
{
  if (wn2vnMap) { return wn2vnMap->Find((ExprHandle)wnexpr); }
  return 0;
}

ScalarizedRef* 
XlationContext::FindScalarizedRef(WN* wn)
{
  if (nssymtab) { return nssymtab->Find(wn); }
  return NULL;
}


// -------------------------------------------------------
// Misc
// -------------------------------------------------------

void 
XlationContext::Dump(std::ostream& o, const char* pre) const
{
  o << "(";

  // FIXME: convert to member functions
  if (IsDerefAddr())                           o << " deref";
  if (XlationContext_has_logical_arg(*this))   o << " logical_arg";
  if (XlationContext_io_stmt(*this))           o << " in_io";
  if (XlationContext_deref_io_item(*this))     o << " deref_io";
  if (XlationContext_origfmt_ioctrl(*this))    o << " varfmt";
  if (XlationContext_fmt_io(*this))            o << " formatted io";
  if (XlationContext_cray_io(*this))           o << " craylib";
  o << ")\n";

  // Skeleton code for iterating through context stack
  for (XlationContextIterator it(*this); it.IsValid(); ++it) {
    Ctxt* ctxt = it.Current();
    ctxt->Dump();
  }

}

void 
XlationContext::DDump() const
{
  Dump(std::cerr);
}


//***************************************************************************
// XlationContext::Ctxt
//***************************************************************************

XlationContext::Ctxt::Ctxt()
  : wn(NULL), nextVId(0), nextEId(0)
{
}

XlationContext::Ctxt::~Ctxt()
{
}

void 
XlationContext::Ctxt::Dump(std::ostream& o) const
{
  o << "{context}";
  CtxtFlags::Dump(o);
}

void 
XlationContext::Ctxt::DDump() const
{
  Dump(std::cerr);
}


//***************************************************************************
// XlationContextIterator
//***************************************************************************

XlationContextIterator::XlationContextIterator(const XlationContext& x)
  : xctxt(x)
{
  Reset();
}

XlationContextIterator::~XlationContextIterator()
{
}
