// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.h,v 1.10 2004/06/01 22:21:45 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef SymTab_H 
#define SymTab_H

//************************** System Include Files ***************************

#include <map>
#include <string>
#include <iostream>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

//***************************************************************************
// XAIFSymToSymbolMap (FIXME)
//***************************************************************************

class Symbol;

class XAIFSymToSymbolMap 
{
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

//***************************************************************************
// Symbol
//***************************************************************************

class Symbol {
public:
  Symbol();
  Symbol(const ST* st, bool act);
  virtual ~Symbol();

  // Return the WHIRL symbol
  ST* GetST() const { return st; }
  ST* SetST(const ST* st_) { st = const_cast<ST*>(st_); }

  // Is the symbol active in the AD sense
  bool IsActive() const { return active; }
  bool SetActive(bool act) { active = act; }
  
  virtual void Dump(std::ostream& o = std::cerr) const;
  virtual void DDump() const;

private:
  // These could make sense, but I just haven't implemented them yet
  Symbol(const Symbol& x) { }
  Symbol& operator=(const Symbol& x) { return *this; }

private:
  ST* st;
  bool active;
};

//***************************************************************************

#endif 
