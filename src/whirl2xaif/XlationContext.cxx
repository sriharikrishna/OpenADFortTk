// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/XlationContext.cxx,v 1.4 2003/05/23 18:33:47 eraxxon Exp $
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
#include "SymTab.h"

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// XlationContext
//***************************************************************************

XlationContext::XlationContext()
  : flags(0)
{ 
  ctxtstack.push_front(Ctxt());
}

XlationContext::~XlationContext()
{
  ctxtstack.clear(); // clear the stack
}

XlationContext&
XlationContext::CreateContext()
{
  return Ctor(NOFLAG, NULL, NULL);
}

XlationContext&
XlationContext::CreateContext(mUINT32 flags_)
{
  return Ctor(flags_, NULL, NULL);
}

XlationContext&
XlationContext::CreateContext(mUINT32 flags_, NonScalarSymTab* symtab_)
{
  return Ctor(flags_, symtab_, NULL);
}

XlationContext&
XlationContext::CreateContext(mUINT32 flags_, WN* wn_)
{
  return Ctor(flags_, NULL, wn_);
}

XlationContext&
XlationContext::Ctor(mUINT32 flags_, NonScalarSymTab* symtab_, WN* wn_)
{
  // If available, get enclosing context
  const Ctxt* enclCtxt = NULL;
  if (ctxtstack.size() > 0) {
    enclCtxt = &(ctxtstack.front());
  }
  
  // Create new context
  ctxtstack.push_front(Ctxt());
  CurContext().SetFlags(flags_);
  CurContext().SetSymTab(symtab_);
  CurContext().SetWN(wn_);

  // Set inherited flags from enclosing context
  Ctxt& curCtxt = CurContext();
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


NonScalarSym* 
XlationContext::FindNonScalarSym(WN* wn)
{
  for (XlationContextIterator it(*this); it.IsValid(); ++it) {
    Ctxt* ctxt = it.Current();
    NonScalarSymTab* symtab = ctxt->GetSymTab();
    if (symtab) {
      // We found a symbol table. Query it.
      NonScalarSym* sym = symtab->Find(wn);
      if (sym) { return sym; }
    }
  }
  return NULL;
}

void 
XlationContext::Dump(std::ostream& o, const char* pre) const
{
  o << "(";

  // FIXME: convert to member functions
  if (IsDerefAddr())                           o << " deref";
  if (XlationContext_no_newline(*this))        o << " no_newline";
  if (XlationContext_has_logical_arg(*this))   o << " logical_arg";
  if (XlationContext_no_parenthesis(*this))    o << " no_paren";
  if (XlationContext_io_stmt(*this))           o << " in_io";
  if (XlationContext_deref_io_item(*this))     o << " deref_io";
  if (XlationContext_origfmt_ioctrl(*this))    o << " varfmt";
  if (XlationContext_explicit_region(*this))   o << " region_pragma";
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
  : flags(0), symtab(NULL), wn(NULL), nextVId(0), nextEId(0)
{
}

XlationContext::Ctxt::~Ctxt()
{
}

void 
XlationContext::Ctxt::Dump(std::ostream& o) const
{
  o << "{context}";
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
