// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XlationContext.cxx,v 1.3 2003/09/17 19:44:30 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XlationContext.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

#include "XlationContext.h"

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// XlationContext
//***************************************************************************

XlationContext::XlationContext()
{ 
  id2puMap = NULL;
  wn2idMap = NULL;
  id2wnMap = NULL;
  xsym2wsymMap = NULL;

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
  return Ctor(NOFLAG);
}

XlationContext&
XlationContext::CreateContext(uint32_t flags_)
{
  return Ctor(flags_);
}

XlationContext&
XlationContext::Ctor(uint32_t flags_)
{
  // If available, get enclosing context
  const Ctxt* enclCtxt = NULL;
  if (ctxtstack.size() > 0) {
    enclCtxt = &(ctxtstack.front());
  }
  
  // Create new context
  ctxtstack.push_front(Ctxt());
  CurContext().SetFlags(flags_);

  // Set inherited flags from enclosing context
  Ctxt& curCtxt = CurContext();
  if (enclCtxt->AreFlags(VARREF)) { curCtxt.SetFlags(VARREF); }
  if (enclCtxt->AreFlags(LVALUE)) { curCtxt.SetFlags(LVALUE); }
  
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
// Id maps
// -------------------------------------------------------

pair<ST_TAB*, PU_Info*>
XlationContext::FindSymTab(SymTabId stabId)
{
  SymTabIdToSymTabMap* map = GetIdToSymTabMap();
  if (map) { return (map->Find(stabId)); }
  return pair<ST_TAB*, PU_Info*>(NULL, NULL);
}

PU_Info*
XlationContext::FindPU(PUId puid)
{
  PUIdToPUMap* map = GetIdToPUMap();
  if (map) { return (map->Find(puid)); }
  return NULL;
}

WNId
XlationContext::FindWNId(WN* wn)
{
  WNToWNIdMap* map = GetWNToIdMap();
  if (map) { return (map->Find(wn)); }
  return 0;
}

WN*
XlationContext::FindWN(WNId wnid, bool mustFind)
{
  WNIdToWNMap* map = GetIdToWNMap();
  if (map) { return (map->Find(wnid, mustFind)); }
  return NULL;
}

ST*
XlationContext::FindSym(const char* scopeid, const char* symid)
{
  XAIFSymToWhirlSymMap* map = GetXAIFSymToWhirlSymMap();
  if (map) { return (map->Find(scopeid, symid)); }
  return NULL;
}

// -------------------------------------------------------
// Misc
// -------------------------------------------------------

void 
XlationContext::Dump(std::ostream& o, const char* pre) const
{
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
