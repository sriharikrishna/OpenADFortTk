// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XlationContext.cxx,v 1.1 2003/08/13 23:01:05 eraxxon Exp $

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
}

XlationContext::~XlationContext()
{
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
XlationContext::FindWN(WNId wnid)
  {
  WNIdToWNMap* map = GetIdToWNMap();
  if (map) { return (map->Find(wnid)); }
  return NULL;
}

ST*
XlationContext::FindSym(const char* scopeid, const char* symid)
{
  XAIFSymToWhirlSymMap* map = GetXAIFSymToWhirlSymMap();
  if (map) { return (map->Find(scopeid, symid)); }
  return NULL;
}


void 
XlationContext::Dump(std::ostream& o, const char* pre) const
{
}

void 
XlationContext::DDump() const
{
  Dump(std::cerr);
}

