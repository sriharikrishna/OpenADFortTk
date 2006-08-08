// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.h,v 1.14 2005/07/28 15:46:51 eraxxon Exp $

#ifndef XAIFSymToSymbolMap_H 
#define XAIFSymToSymbolMap_H

#include <map>
#include <string>
#include <iostream>

#include "WhirlIDMaps.h"

namespace fortTkSupport { 

  class Symbol;

  class XAIFSymToSymbolMap {

  public:
    // Constructor allocates an empty data structure
    XAIFSymToSymbolMap();
    virtual ~XAIFSymToSymbolMap();
  
    // Find: Returns NULL if not found
    Symbol* Find(const char* scopeid, const char* symid) const;
  
    // Insert: insert <'scopeid'+'symid', ST*> pair in the map and
    // return true; if the key already exists, the operation fails and
    // returns false.
    bool Insert(const char* scopeid, const char* symid, const Symbol* sym);
  
    // Return number of entries
    unsigned int GetSize() const { return strToSymMap.size(); }

    static std::string MakeKey(const char* scopeid, const char* symid);
  
  private:
    typedef std::map<std::string, Symbol*> StringToSymMap;
    typedef StringToSymMap::iterator       StringToSymMapIt;
    typedef StringToSymMap::const_iterator StringToSymMapItC;
    typedef StringToSymMap::value_type     StringToSymMapVal;

  private:
    StringToSymMap strToSymMap;
  };

}

#endif 
