// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/ScalarizedRefTab.h,v 1.4 2004/06/02 19:56:38 eraxxon Exp $

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
// PUToScalarizedRefTabMap
//***************************************************************************



//***************************************************************************
// WNToScalarizedRefTab
//***************************************************************************

class ScalarizedRef;

namespace ScalarizedRefTab_hidden {
  typedef std::map<WN*, ScalarizedRef*> WNToScalarizedRefMap;
  typedef std::map<ScalarizedRef*, WN*> ScalarizedRefToWNMap;
}; /* namespace ScalarizedRefTab_hidden */


// 'WNToScalarizedRefTab' is a special symbol table mapping certain
// non-scalar WHIRL references to dummy scalar variables


// WNToWNToScalarizedRefTab
// ScalarizedRefToWNTab

class WNToScalarizedRefTab 
  : public ScalarizedRefTab_hidden::WNToScalarizedRefMap {

public:
  // Constructor allocates an empty data structure
  WNToScalarizedRefTab();
  virtual ~WNToScalarizedRefTab();
  
  // Find:
  ScalarizedRef* 
  Find(const WN* wn_) const
  {
    WN* wn = const_cast<WN*>(wn_); // WNToSymMap uses non const types
    const_iterator it = find(wn);
    ScalarizedRef* sym = (it == end()) ? NULL : (*it).second;
    return sym;
  }
  
  // Insert: insert <'wn','sym'> pair in the map and return true; if
  // 'wn' already exists, the operation fails and returns false.
  bool 
  Insert(const WN* wn_, const ScalarizedRef* sym_) {
    WN* wn = const_cast<WN*>(wn_); // WNToSymMap uses non const types
    ScalarizedRef* sym = const_cast<ScalarizedRef*>(sym_);
    
    pair<iterator, bool> p = insert(value_type(wn, sym));
    return p.second;
  }


  // Return a globally unique name
  std::string& GetName() { return name; }

  // Return an id, globally unique across instances of this class
  UINT GetId() const { return id; }
  
  // Dump contents for inspection
  virtual void Dump(std::ostream& o = std::cerr, const char* pre = "") const;
  virtual void DDump() const;
  
protected:
  // Should not be used
  WNToScalarizedRefTab(const WNToScalarizedRefTab& x) { }
  WNToScalarizedRefTab& operator=(const WNToScalarizedRefTab& x) { return *this; }

private: 
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

#endif 
