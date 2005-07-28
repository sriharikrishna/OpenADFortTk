// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.h,v 1.14 2005/07/28 15:46:51 eraxxon Exp $

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

#include "WhirlIDMaps.h"

//************************** Forward Declarations ***************************

//***************************************************************************
// Stuff copied from SymTab.cpp in UseNewOA-Open64
//***************************************************************************
bool 
IsVarRefTranslatableToXAIF(const WN* wn);


bool
IsScalarRef(TY_IDX baseobj_ty, TY_IDX refobj_ty);

bool
IsNonScalarRef(TY_IDX baseobj_ty, TY_IDX refobj_ty);

bool
IsNonScalarRef(const WN* wn);


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

// Symbol: This is hackish and ugly until we figure out what exactly we need.
class Symbol {
public:
  Symbol();
  Symbol(const ST* st, WNId wnid, bool act);
  virtual ~Symbol();
  
  // -------------------------------------------------------
  
  // Return the WHIRL symbol
  ST* GetST() const { return st; }
  void SetST(const ST* x) { st = const_cast<ST*>(x); }
  
  // -------------------------------------------------------
  
  bool IsPathCollapsed() { return wnid != 0; }

  WNId GetPathVorlage() { return wnid; }
  void SetPathVorlage(WNId x) { wnid = x; }
  
  // -------------------------------------------------------
  
  // Is the symbol active in the AD sense
  bool IsActive() const { return active; }
  void SetActive(bool act) { active = act; }
  
  virtual void Dump(std::ostream& o = std::cerr) const;
  virtual void DDump() const;

private:
  // These could make sense, but I just haven't implemented them yet
  Symbol(const Symbol& x) { }
  Symbol& operator=(const Symbol& x) { return *this; }

private:
  ST* st;     // 
  WNId wnid;  // for a scalarized symbol
  bool active;
};

//***************************************************************************

#endif 
