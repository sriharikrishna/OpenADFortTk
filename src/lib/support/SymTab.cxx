// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.cxx,v 1.6 2003/09/02 15:02:20 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.cxx,v $
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

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "SymTab.h"

//************************** Forward Declarations ***************************

//***************************************************************************

// FIXME
// Create a new symbol name
static const char* cat(const char* str, UINT num)
{
// 39 bytes hold a 128-bit uint in base 10. [log(2^128)]
#define SYMBUF_SZ (32 + 39 + 1)
  static char buf[SYMBUF_SZ];
  snprintf(buf, SYMBUF_SZ, "%s%d", str, num);
  return buf;
#undef SYMBUF_SZ
}

//***************************************************************************
// XAIFSymToWhirlSymMap
//***************************************************************************

XAIFSymToWhirlSymMap::XAIFSymToWhirlSymMap()
{
}

XAIFSymToWhirlSymMap::~XAIFSymToWhirlSymMap()
{
  strToSTMap.clear();
}

ST*
XAIFSymToWhirlSymMap::Find(const char* scopeid, const char* symid) const
{
  std::string key = MakeKey(scopeid, symid);

  StringToSTMapItC it = strToSTMap.find(key);
  ST* st = (it == strToSTMap.end()) ? NULL : (*it).second;
  return st;
}

bool
XAIFSymToWhirlSymMap::Insert(const char* scopeid, const char* symid, 
			     const ST* st_)
{
  std::string key = MakeKey(scopeid, symid);
  ST* st = const_cast<ST*>(st_); // the map uses non const types
  
  StringToSTMapVal val = StringToSTMapVal(key, st);
  pair<StringToSTMapIt, bool> p = strToSTMap.insert(val);
  return p.second;
}

std::string 
XAIFSymToWhirlSymMap::MakeKey(const char* scopeid, const char* symid)
{
  // Reserve enough space for null terminators and concatination char
  std::string key;
  key.reserve(strlen(scopeid) + strlen(symid) + 3);

  key += scopeid;
  key += ".";
  key += symid;
  return key;
}

//***************************************************************************
// NonScalarSym
//***************************************************************************

UINT NonScalarSym::nextId = 0; // static member

NonScalarSym::NonScalarSym()
{
  id = nextId++;
  name = cat("*nonscalarsym*", id);  
}

NonScalarSym::~NonScalarSym()
{
}

void 
NonScalarSym::Dump(std::ostream& o) const
{
  o << name;
}

void 
NonScalarSym::DDump() const
{
  Dump(std::cerr);
}

//***************************************************************************
// NonScalarSymTab
//***************************************************************************

UINT NonScalarSymTab::nextId = 0; // static member

NonScalarSymTab::NonScalarSymTab()
{
  id = nextId++;
  name = cat("*nonscalarstab*", id);
}

NonScalarSymTab::~NonScalarSymTab()
{
  // Clear table
  for (NonScalarSymTabIterator it(*this); it.IsValid(); ++it) {
    delete it.CurrentTarg(); // NonScalarSym*
  }
  wnToSymMap.clear();
}

NonScalarSym*
NonScalarSymTab::Find(const WN* wn_) const
{
  WN* wn = const_cast<WN*>(wn_); // WNToSymMap uses non const types

  WNToSymMapItC it = wnToSymMap.find(wn);
  NonScalarSym* sym = (it == wnToSymMap.end()) ? NULL : (*it).second;
  return sym;
}

bool
NonScalarSymTab::Insert(const WN* wn_, const NonScalarSym* sym_)
{
  WN* wn = const_cast<WN*>(wn_); // WNToSymMap uses non const types
  NonScalarSym* sym = const_cast<NonScalarSym*>(sym_);

  WNToSymMapVal val = WNToSymMapVal(wn, sym);
  pair<WNToSymMapIt, bool> p = wnToSymMap.insert(val);
  return p.second;
}

void
NonScalarSymTab::Dump(std::ostream& o, const char* pre) const
{
  std::string p = pre;
  std::string p1 = p + "  ";

  o << p << "{ ================== Begin NonScalar SymTab Dump ("
    << GetSize() << " Entries):\n";
  
  for (NonScalarSymTabIterator it(*this); it.IsValid(); ++it) {
    WN* wn = it.CurrentSrc();
    NonScalarSym* sym = it.CurrentTarg();
    o << p1 << wn << " --> ";
    sym->Dump(o);
    o << std::endl;
  }
  o << p << "End NonScalar SymTab Dump ================== }\n";
}

void
NonScalarSymTab::DDump() const
{
  Dump(std::cerr);
}

//***************************************************************************
// NonScalarSymTabIterator
//***************************************************************************

NonScalarSymTabIterator::NonScalarSymTabIterator(const NonScalarSymTab& x)
  : symtab(x)
{
  Reset();
}

NonScalarSymTabIterator::~NonScalarSymTabIterator()
{
}
