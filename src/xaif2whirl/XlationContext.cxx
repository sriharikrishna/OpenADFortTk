// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XlationContext.cxx,v 1.6 2004/03/29 23:41:35 eraxxon Exp $

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

  // Down inheritance: Set flags that inherit from enclosing context
  Ctxt& curCtxt = CurContext();
  if (enclCtxt->AreFlags(ACTIVE_V)) { curCtxt.SetFlags(ACTIVE_V); }
  if (enclCtxt->AreFlags(ACTIVE_D)) { curCtxt.SetFlags(ACTIVE_D); }
  if (enclCtxt->AreFlags(VARREF)) { curCtxt.SetFlags(VARREF); }
  if (enclCtxt->AreFlags(LVALUE)) { curCtxt.SetFlags(LVALUE); }
  if (enclCtxt->AreFlags(ARRAY)) { curCtxt.SetFlags(ARRAY); }
  if (enclCtxt->AreFlags(ARRAYIDX)) { curCtxt.SetFlags(ARRAYIDX); }
  if (enclCtxt->AreFlags(EXPRSIMPLE)) { curCtxt.SetFlags(EXPRSIMPLE); }

  return (*this);
}

// DeleteContext: Delete the context, maintaining invariant that there
// is at least one context
XlationContext&
XlationContext::DeleteContext()
{
  if (ctxtstack.size() > 1) {
    // There are at least 2 items on the stack.
    
    // Get the current and parent contexts.
    CtxtStackIt it = ctxtstack.begin();
    Ctxt& curCtxt = (*it); // CurContext() or ctxtstack.front()
    Ctxt& parCtxt = (*(++it));
    
    // Up inheritance: Set flags that inherit from descending context
    if (curCtxt.AreFlags(ACTIVE)) { parCtxt.SetFlags(ACTIVE); }
    
    // Delete the current context
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

Symbol*
XlationContext::FindSym(const char* scopeid, const char* symid)
{
  XAIFSymToSymbolMap* map = GetXAIFSymToSymbolMap();
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
