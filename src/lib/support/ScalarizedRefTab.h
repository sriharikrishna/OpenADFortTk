// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/ScalarizedRefTab.h,v 1.1 2004/06/01 22:21:09 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/ScalarizedRefTab.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef ScalarizedRefTab_H 
#define ScalarizedRefTab_H

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

// WN2F_Can_Assign_Types: This determines whether or not a value of
// type t1 can be used anywhere we expect a value of type t2.  When
// this condition is TRUE, yet t1 is different from t2, we expect the
// implicit Fortran type coersion to transform an object of one type
// to the other. [FIXME-orig. text]
bool
WN2F_Can_Assign_Types(TY_IDX ty1, TY_IDX ty2);


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
