// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/ScalarizedRefTab.h,v 1.2 2004/06/02 02:01:28 eraxxon Exp $

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
// ScalarizedRefTab
//***************************************************************************

class ScalarizedRef;

// 'ScalarizedRefTab' is a special symbol table mapping certain
// non-scalar WHIRL references to dummy scalar variables
class ScalarizedRefTab {
public:
  // Constructor allocates an empty data structure
  ScalarizedRefTab();
  virtual ~ScalarizedRefTab();
  
  // Find: find 
  ScalarizedRef* Find(const WN* wn) const;
  
  // Insert: insert <'wn','sym'> pair in the map and return true; if
  // 'wn' already exists, the operation fails and returns false.
  bool Insert(const WN* wn, const ScalarizedRef* sym);
  
  // Return number of entries
  unsigned int GetSize() const { return wnToSymMap.size(); }

  // Return a globally unique name
  std::string& GetName() { return name; }

  // Return an id, globally unique across instances of this class
  UINT GetId() const { return id; }
  
  // Dump contents for inspection
  virtual void Dump(std::ostream& o = std::cerr, const char* pre = "") const;
  virtual void DDump() const;
  
  friend class ScalarizedRefTabIterator;
  
protected:
  // Should not be used
  ScalarizedRefTab(const ScalarizedRefTab& x) { }
  ScalarizedRefTab& operator=(const ScalarizedRefTab& x) { return *this; }

private: 
  // A map of WN* to ScalarizedRef*.
  typedef std::map<WN*, ScalarizedRef*> WNToSymMap;
  typedef WNToSymMap::iterator         WNToSymMapIt;
  typedef WNToSymMap::const_iterator   WNToSymMapItC;
  typedef WNToSymMap::value_type       WNToSymMapVal;

private: 
  WNToSymMap wnToSymMap; // owns all ScalarizedRef*

  std::string name; // FIXME: 
  UINT id;

  static UINT nextId; // for globally uniqe id numbers
};

//***************************************************************************
// ScalarizedRef
//***************************************************************************

class ScalarizedRef {
public:
  ScalarizedRef();
  virtual ~ScalarizedRef();

  // Return a globally unique dummy symbol name
  std::string& GetName() { return name; }

  // Return an id, globally unique across instances of this class
  UINT GetId() const { return id; }

  virtual void Dump(std::ostream& o = std::cerr) const;
  virtual void DDump() const;

private:
  // These could make sense, but I just haven't implemented them yet
  ScalarizedRef(const ScalarizedRef& x) { }
  ScalarizedRef& operator=(const ScalarizedRef& x) { return *this; }

private:
  std::string name; // FIXME:
  UINT id; 
  
  static UINT nextId; // for globally uniqe id numbers
};


//***************************************************************************
// ScalarizedRefTabIterator
//***************************************************************************

// 'ScalarizedRefTabIterator': iterator for symbols in a 'ScalarizedRefTab'
class ScalarizedRefTabIterator {
public:   
  ScalarizedRefTabIterator(const ScalarizedRefTab& x);
  ~ScalarizedRefTabIterator();

  // Returns the current WN* or NULL
  WN* CurrentSrc() const {
    if (it != symtab.wnToSymMap.end()) { return (*it).first; }
    else { return NULL; }
  }

  // Returns the current ScalarizedRef*
  ScalarizedRef* CurrentTarg() const {
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
  ScalarizedRefTabIterator();
  ScalarizedRefTabIterator(const ScalarizedRefTabIterator& x);
  ScalarizedRefTabIterator& operator=(const ScalarizedRefTabIterator& x)
    { return *this; }

protected:
private:
  const ScalarizedRefTab& symtab;
  ScalarizedRefTab::WNToSymMapItC it;
};

//***************************************************************************

#endif 
