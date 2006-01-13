// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XlationContext.cxx,v 1.9 2006/01/12 22:07:37 utke Exp $

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

std::string XlationContext::ourPrefix;

XlationContext::XlationContext()
  : wnParentMap(NULL), id2stabMap(NULL), id2puMap(NULL), wn2idMap(NULL),
    id2wnMap(NULL), xsym2wsymMap(NULL)
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

pair<ST_TAB*, PU_Info*>
XlationContext::FindSymTab(SymTabId stabId)
{
  if (id2stabMap) { return (id2stabMap->Find(stabId, true /*mustFind*/)); }
  return pair<ST_TAB*, PU_Info*>(NULL, NULL);
}

PU_Info*
XlationContext::FindPU(PUId puid)
{
  if (id2puMap) { return (id2puMap->Find(puid)); }
  return NULL;
}

WNId
XlationContext::FindWNId(WN* wn)
{
  if (wn2idMap) { return (wn2idMap->Find(wn)); }
  return 0;
}

WN*
XlationContext::FindWN(WNId wnid, bool mustFind)
{
  if (id2wnMap) { return (id2wnMap->Find(wnid, mustFind)); }
  return NULL;
}

Symbol*
XlationContext::FindSym(const char* scopeid, const char* symid)
{
  if (xsym2wsymMap) { return (xsym2wsymMap->Find(scopeid, symid)); }
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

void XlationContext::setPrefix(const std::string& aPrefix) { 
  ourPrefix=aPrefix;
}

std::string& XlationContext::getPrefix() { 
  return ourPrefix;
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
