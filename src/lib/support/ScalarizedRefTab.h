// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/ScalarizedRefTab.h,v 1.6 2004/06/03 13:15:36 eraxxon Exp $

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


//***************************************************************************
// ScalarizedRefTab (helper types)
//***************************************************************************


// ScalarizedRefTab_Base: 
// Note: FromTy and ToTy should be pointers!
class ScalarizedRefTab_Base
{
public:
  enum TableType { 
    W2X, // A table optimized for WHIRL->XAIF lookups
    X2W  // A table optimized for XAIF->WHIRL lookups
  };

protected:
  ScalarizedRefTab_Base();
  virtual ~ScalarizedRefTab_Base();
  
  // Return a globally unique name
  std::string& GetName() { return name; }

  // Return an id, globally unique across instances of this class
  UINT GetId() const { return id; }

protected:
  
  std::string name; // FIXME: 
  UINT id;
  
  static UINT nextId; // for globally uniqe id numbers
};


// ScalarizedRefTab_Map: abstract map routines
// Note: FromTy and ToTy should be pointers!
template <class FromTy, class ToTy>
class ScalarizedRefTab_Map : public std::map<FromTy, ToTy>
{
public:
  ScalarizedRefTab_Map() { }
  virtual ~ScalarizedRefTab_Map() { }
  
  // Find: Given x, find y if x --> y.
  ToTy 
  Find(const FromTy x) const
  {
    typename std::map<FromTy, ToTy>::const_iterator it = find(x);
    ToTy y = (it == end()) ? NULL : (*it).second;
    return y;
  }
  
  // Insert: insert the <x,y> pair in the map and return true; if
  // x is already a member, the operation fails and returns false.
  bool 
  Insert(FromTy x, ToTy y) {
    pair<typename std::map<FromTy, ToTy>::iterator, bool> p = 
      insert(make_pair(x, y)); // std::map<FromTy, ToTy>::value_type
    return p.second;
  }
  
protected:
};


//***************************************************************************
// ScalarizedRefTab
//***************************************************************************

class ScalarizedRef;

// ScalarizedRefTab: A dummy template that will be specialized below.
// For mapping certain non-scalar WHIRL references to dummy scalar
// variables
template <ScalarizedRefTab_Base::TableType TabTy>
class ScalarizedRefTab 
  : public ScalarizedRefTab_Base,
    public ScalarizedRefTab_Map<void*, void*>
{
};


// ---------------------------------------------------------
// ScalarizedRefTab: Specialization for W2X
// ---------------------------------------------------------
typedef ScalarizedRefTab<ScalarizedRefTab_Base::W2X> 
  ScalarizedRefTab_W2X;

class ScalarizedRefTab<ScalarizedRefTab_Base::W2X>
  : public ScalarizedRefTab_Base,
    public ScalarizedRefTab_Map<WN*, ScalarizedRef*> {

public:
  // Constructor allocates an empty data structure
  ScalarizedRefTab();
  virtual ~ScalarizedRefTab();
  
  // Create: Fills in map
  void
  Create(PU_Info* pu);
  
  // Find: a version with const params for convenience
  ScalarizedRef* 
  Find(const WN* x_) const
  {
    WN* x = const_cast<WN*>(x_);
    return ScalarizedRefTab_Map<WN*, ScalarizedRef*>::Find(x);
  }
  
  // Insert: a version with const params for convenience
  bool 
  Insert(const WN* x_, const ScalarizedRef* y_) {
    WN* x = const_cast<WN*>(x_);
    ScalarizedRef* y = const_cast<ScalarizedRef*>(y_);
    return ScalarizedRefTab_Map<WN*, ScalarizedRef*>::Insert(x, y);
  }
  
  
  // Dump contents for inspection
  virtual void Dump(std::ostream& o = std::cerr, const char* pre = "") const;
  virtual void DDump() const;
  
protected:
  // Should not be used
  ScalarizedRefTab(const ScalarizedRefTab& x) { }
  ScalarizedRefTab& operator=(const ScalarizedRefTab& x) { return *this; }

private: 
};


//***************************************************************************
// ScalarizedRefTabMap
//***************************************************************************

// ---------------------------------------------------------
// ScalarizedRefTabMap: Specialization for W2X
// ---------------------------------------------------------

class ScalarizedRefTabMap_W2X 
  : public ScalarizedRefTab_Map<PU_Info*, ScalarizedRefTab_W2X*> {
  
  // FIXME: delete memory ***

  void
  Create(PU_Info* pu_forest);
  
};

#if 0
class ScalarizedRefTabMap_X2W 
  : public ScalarizedRefTab_Map<PU_Info*, ScalarizedRefTab_X2W*> {
    
}
#endif


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
// 
//***************************************************************************

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
// 
//***************************************************************************

// ForAllNonScalarRefsOp: Abstract base class for the operator passed
// to the function 'ForAllNonScalarRefs(...)'.  Any caller of this
// function must define its own operator object, using this class
// as a base class and providing a definition for 'operator()'.
class ForAllNonScalarRefsOp {
public:
  ForAllNonScalarRefsOp() { }
  virtual ~ForAllNonScalarRefsOp() { }

  // Given a non-scalar reference 'wn', does something interesting.
  // Returns 0 on success; non-zero on error.
  virtual int operator()(const WN* wn) = 0;
private: 
};

void 
ForAllNonScalarRefs(const WN* wn, ForAllNonScalarRefsOp& op);



// AddToScalarizedRefTabOp: Given a ScalarizedRefTab, add references to it
class AddToScalarizedRefTabOp : public ForAllNonScalarRefsOp {
public:
  AddToScalarizedRefTabOp(ScalarizedRefTab_W2X* symtab_);
  ~AddToScalarizedRefTabOp() { }
  
  ScalarizedRefTab_W2X* GetSymTab() { return symtab; }

  // Given a non-scalar reference 'wn', create a dummy variable and
  // add to the map.  
  int operator()(const WN* wn);

private:
  ScalarizedRefTab_W2X* symtab;
};


//***************************************************************************

#endif 
