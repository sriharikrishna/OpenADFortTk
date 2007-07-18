// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.cxx,v 1.15 2005/07/28 15:46:51 eraxxon Exp $

#include "Open64IRInterface/Open64BasicTypes.h"
#include "Open64IRInterface/stab_attr.h"
#include "Open64IRInterface/wn_attr.h"
#include "Diagnostics.h"
#include "XAIFSymToSymbolMap.h"
#include "Symbol.h"

namespace fortTkSupport{

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

}
