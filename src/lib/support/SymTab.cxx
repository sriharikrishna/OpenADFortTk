// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.cxx,v 1.3 2003/07/24 14:36:04 eraxxon Exp $

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

#include "Open64BasicTypes.h"

//*************************** User Include Files ****************************

#include "SymTab.h"

//************************** Forward Declarations ***************************

//***************************************************************************

// FIXME
static const char* cat(const char* str, UINT num)
{
  // 39 bytes hold a 128-bit uint in base 10. [log(2^128)]
#define SYMBUF_SZ (32 + 39 + 1)
  static char buf[SYMBUF_SZ];
  
  // Create a new symbol name
  snprintf(buf, SYMBUF_SZ, "%s%d", str, num);
  return buf;
#undef SYMBUF_SZ
}

//***************************************************************************
// 
//***************************************************************************

StabToScopeIdMap::StabToScopeIdMap()
{

}

StabToScopeIdMap::~StabToScopeIdMap()
{
  stabToScopeIdMap.clear();
}

UINT
StabToScopeIdMap::Find(const ST_TAB* sttab_) const
{
  ST_TAB* sttab = const_cast<ST_TAB*>(sttab_); // the map uses non const types
  
  STTABToScopeIdMapItC it = stabToScopeIdMap.find(sttab);
  UINT id = (it == stabToScopeIdMap.end()) ? 0 : (*it).second;
  return id;
}

bool
StabToScopeIdMap::Insert(const ST_TAB* sttab_, const UINT id)
{
  ST_TAB* sttab = const_cast<ST_TAB*>(sttab_); // the map uses non const types
  
  STTABToScopeIdMapVal val = STTABToScopeIdMapVal(sttab, id);
  pair<STTABToScopeIdMapIt, bool> p = stabToScopeIdMap.insert(val);
  return p.second;
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
