// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.h,v 1.8 2003/10/10 17:21:37 eraxxon Exp $

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

bool 
IsVarRefTranslatableToXAIF(const WN* wn);


bool
IsScalarRef(TY_IDX baseobj_ty, TY_IDX refobj_ty);

bool
IsNonScalarRef(TY_IDX baseobj_ty, TY_IDX refobj_ty);

bool
IsNonScalarRef(const WN* wn);

bool
WN2F_Can_Assign_Types(TY_IDX ty1, TY_IDX ty2);


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
// NonScalarSymTab
//***************************************************************************

class NonScalarSym;

// 'NonScalarSymTab' is a special symbol table for non scalar WHIRL
// references (e.g. array and record accesses).
class NonScalarSymTab {
public:
  // Constructor allocates an empty data structure
  NonScalarSymTab();
  virtual ~NonScalarSymTab();
  
  // Find: find 
  NonScalarSym* Find(const WN* wn) const;
  
  // Insert: insert <'wn','sym'> pair in the map and return true; if
  // 'wn' already exists, the operation fails and returns false.
  bool Insert(const WN* wn, const NonScalarSym* sym);
  
  // Return number of entries
  unsigned int GetSize() const { return wnToSymMap.size(); }

  // Return a globally unique name
  std::string& GetName() { return name; }

  // Return an id, globally unique across instances of this class
  UINT GetId() const { return id; }
  
  // Dump contents for inspection
  virtual void Dump(std::ostream& o = std::cerr, const char* pre = "") const;
  virtual void DDump() const;
  
  friend class NonScalarSymTabIterator;
  
protected:
  // Should not be used
  NonScalarSymTab(const NonScalarSymTab& x) { }
  NonScalarSymTab& operator=(const NonScalarSymTab& x) { return *this; }

private: 
  // A map of WN* to NonScalarSym*.
  typedef std::map<WN*, NonScalarSym*> WNToSymMap;
  typedef WNToSymMap::iterator         WNToSymMapIt;
  typedef WNToSymMap::const_iterator   WNToSymMapItC;
  typedef WNToSymMap::value_type       WNToSymMapVal;

private: 
  WNToSymMap wnToSymMap; // owns all NonScalarSym*

  std::string name; // FIXME: 
  UINT id;

  static UINT nextId; // for globally uniqe id numbers
};

//***************************************************************************
// NonScalarSym
//***************************************************************************

class NonScalarSym {
public:
  NonScalarSym();
  virtual ~NonScalarSym();

  // Return a globally unique dummy symbol name
  std::string& GetName() { return name; }

  // Return an id, globally unique across instances of this class
  UINT GetId() const { return id; }

  virtual void Dump(std::ostream& o = std::cerr) const;
  virtual void DDump() const;

private:
  // These could make sense, but I just haven't implemented them yet
  NonScalarSym(const NonScalarSym& x) { }
  NonScalarSym& operator=(const NonScalarSym& x) { return *this; }

private:
  std::string name; // FIXME:
  UINT id; 
  
  static UINT nextId; // for globally uniqe id numbers
};


//***************************************************************************
// NonScalarSymTabIterator
//***************************************************************************

// 'NonScalarSymTabIterator': iterator for symbols in a 'NonScalarSymTab'
class NonScalarSymTabIterator {
public:   
  NonScalarSymTabIterator(const NonScalarSymTab& x);
  ~NonScalarSymTabIterator();

  // Returns the current WN* or NULL
  WN* CurrentSrc() const {
    if (it != symtab.wnToSymMap.end()) { return (*it).first; }
    else { return NULL; }
  }

  // Returns the current NonScalarSym*
  NonScalarSym* CurrentTarg() const {
    if (it != symtab.wnToSymMap.end()) { return (*it).second; }
    else { return NULL; }
  }
  
  void operator++()    { ++it; } // prefix increment
  void operator++(int) { it++; } // postfix increment

  bool IsValid() const { return it != symtab.wnToSymMap.end(); } 
  bool IsEmpty() const { return it == symtab.wnToSymMap.end(); }

  // Reset and prepare for iteration again
  void Reset() { it = symtab.wnToSymMap.begin(); }

private:
  // Should not be used
  NonScalarSymTabIterator();
  NonScalarSymTabIterator(const NonScalarSymTabIterator& x);
  NonScalarSymTabIterator& operator=(const NonScalarSymTabIterator& x)
    { return *this; }

protected:
private:
  const NonScalarSymTab& symtab;
  NonScalarSymTab::WNToSymMapItC it;
};

//***************************************************************************

#endif 
