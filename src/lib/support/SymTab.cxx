// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.cxx,v 1.11 2004/06/01 22:21:45 eraxxon Exp $

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

#include "stab_attr.h"
#include "wn_attr.h"
#include "diagnostics.h"

//************************** Forward Declarations ***************************

//***************************************************************************
// XAIFSymToSymbolMap
//***************************************************************************

XAIFSymToSymbolMap::XAIFSymToSymbolMap()
{
}

XAIFSymToSymbolMap::~XAIFSymToSymbolMap()
{
  // Clear table
  StringToSymMapIt it = strToSymMap.begin();
  for ( ; it != strToSymMap.end(); ++it) {
    delete (*it).second; // Symbol*
  }
  strToSymMap.clear();
}

Symbol*
XAIFSymToSymbolMap::Find(const char* scopeid, const char* symid) const
{
  std::string key = MakeKey(scopeid, symid);
  
  StringToSymMapItC it = strToSymMap.find(key);
  Symbol* sym = (it == strToSymMap.end()) ? NULL : (*it).second;
  return sym;
}

bool
XAIFSymToSymbolMap::Insert(const char* scopeid, const char* symid, 
			   const Symbol* sym_)
{
  std::string key = MakeKey(scopeid, symid);
  Symbol* sym = const_cast<Symbol*>(sym_); // the map uses non const types
  
  StringToSymMapVal val = StringToSymMapVal(key, sym);
  pair<StringToSymMapIt, bool> p = strToSymMap.insert(val);
  return p.second;
}

std::string 
XAIFSymToSymbolMap::MakeKey(const char* scopeid, const char* symid)
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
// Symbol
//***************************************************************************

Symbol::Symbol()
  : st(NULL), active(false)
{
}

Symbol::Symbol(const ST* st, bool act)
{
  SetST(st);
  SetActive(act);
}

Symbol::~Symbol()
{
}

void 
Symbol::Dump(std::ostream& o) const
{
  o << "Symbol\n";
}

void 
Symbol::DDump() const
{
  Dump(std::cerr);
}

