// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/ScalarizedRefTab.h,v 1.14 2005/06/14 16:55:35 eraxxon Exp $

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

#include <set>
#include <map>
#include <string>
#include <iostream>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "BaseMap.h"
#include "Open64IRInterface.hpp"
#include "diagnostics.h"

//************************** Forward Declarations ***************************

class ScalarizedRef;

//***************************************************************************
// ScalarizedRefTab (helper types)
//***************************************************************************

// ScalarizedRefTab_Base: 
class ScalarizedRefTab_Base
{
public:
  enum TableType { 
    W2X, // A table optimized for WHIRL->XAIF lookups
    X2W  // A table optimized for XAIF->WHIRL lookups
  };

public:
  
  typedef std::set<ScalarizedRef*> ScalarizedRefPoolTy;

  ScalarizedRefPoolTy::iterator RefPoolBegin()
  { return scalarizedRefPool.begin(); }

  ScalarizedRefPoolTy::iterator RefPoolEnd()
  { return scalarizedRefPool.end(); }
  
protected:
  ScalarizedRefTab_Base();
  virtual ~ScalarizedRefTab_Base();
  
  // Insert 'x' into the ref pool if not already there
  void
  InsertIntoPool(ScalarizedRef* x)
  {
    if (scalarizedRefPool.find(x) == scalarizedRefPool.end()) {
      scalarizedRefPool.insert(x);
    }
  }

protected:
  
  // Because one scalarized ref can be associated with several actual
  // references, we need a pool in which these references are entered
  // only once.
  ScalarizedRefPoolTy scalarizedRefPool;
};


//***************************************************************************
// ScalarizedRef
//***************************************************************************

class ScalarizedRef {
  
public:
  // Constructor: if 'x' is supplied, it will be appended to the
  // symbol name
  ScalarizedRef(WN* wn_, const char* x = NULL) { Ctor(wn_, x);  }
  virtual ~ScalarizedRef();
  
  // GetName: Return a globally unique dummy symbol name
  std::string& GetName() { return name; }
  // GetWN: first occurance of reference in PU
  WN* GetWN() { return wn; }
  
  // GetId: Return an id, globally unique across instances of this class
  UINT GetId() const { return id; }
  
  virtual void Dump(std::ostream& o = std::cerr) const;
  virtual void DDump() const;

private:
  // These could make sense, but I just haven't implemented them yet
  ScalarizedRef(const ScalarizedRef& x) { }
  ScalarizedRef& operator=(const ScalarizedRef& x) { return *this; }
  
  void Ctor(WN* wn, const char* x);
  
private:
  UINT id; 
  std::string name;
  WN* wn; // first occurance of reference in PU
  
  static UINT nextId; // for globally uniqe id numbers
};


//***************************************************************************
// ScalarizedRefTab
//***************************************************************************

// ScalarizedRefTab: A dummy template that will be specialized below.
// For mapping certain non-scalar WHIRL references to dummy scalar
// variables
template <ScalarizedRefTab_Base::TableType TabTy>
class ScalarizedRefTab 
  : public ScalarizedRefTab_Base,
    public FortTk::BaseMap<void*, void*>
{
};


// ---------------------------------------------------------
// ScalarizedRefTab: Specialization for W2X
// ---------------------------------------------------------
typedef ScalarizedRefTab<ScalarizedRefTab_Base::W2X> 
  ScalarizedRefTab_W2X;

template <>
class ScalarizedRefTab<ScalarizedRefTab_Base::W2X>
  : public ScalarizedRefTab_Base,
    public FortTk::BaseMap<WN*, ScalarizedRef*> {

public:
  // Constructor allocates an empty data structure
  ScalarizedRefTab();
  ScalarizedRefTab(PU_Info* pu) { Create(pu); }
  virtual ~ScalarizedRefTab();
  
  // Create: Fills in map
  void Create(PU_Info* pu);

  // Find: 
  virtual ScalarizedRef* 
  Find(WN* x_, bool mustFind = false) const
  { return FortTk::BaseMap<WN*, ScalarizedRef*>::Find(x_, mustFind); }
  
  // Find: a version with const params for convenience
  ScalarizedRef* 
  Find(const WN* x_, bool mustFind = false) const
  {
    WN* x = const_cast<WN*>(x_);
    return FortTk::BaseMap<WN*, ScalarizedRef*>::Find(x, mustFind);
  }
  
  
  // Insert: override to manage scalar ref pool
  virtual bool 
  Insert(WN* x, ScalarizedRef* y) {
    InsertIntoPool(y);
    return FortTk::BaseMap<WN*, ScalarizedRef*>::Insert(x, y);
  }
  
  // Insert: a version with const params for convenience
  bool 
  Insert(const WN* x_, const ScalarizedRef* y_) {
    WN* x = const_cast<WN*>(x_);
    ScalarizedRef* y = const_cast<ScalarizedRef*>(y_);
    return Insert(x, y);
  }
  
  
  // Dump contents for inspection
  virtual void Dump(std::ostream& o = std::cerr) const;
  virtual void DDump() const;

  void DumpFmt(std::ostream& o = std::cerr, const char* pre = "") const;
  
protected:
  // Should not be used
  ScalarizedRefTab(const ScalarizedRefTab& x) { }
  ScalarizedRefTab& operator=(const ScalarizedRefTab& x) { return *this; }

private: 
};


// ---------------------------------------------------------
// ScalarizedRefTab: Specialization for X2W
// ---------------------------------------------------------

// It turns out that we do not really need this.


//***************************************************************************
// ScalarizedRefTabMap
//***************************************************************************

#if 0
// ScalarizedRefTab: A dummy template that will be specialized below.
// For mapping certain non-scalar WHIRL references to dummy scalar
// variables
template <ScalarizedRefTab_Base::TableType TabTy>
class ScalarizedRefTab 
  : public ScalarizedRefTab_Base,
    public FortTk::BaseMap<void*, void*>
{
};
#endif


// ---------------------------------------------------------
// ScalarizedRefTabMap: Specialization for W2X
// ---------------------------------------------------------

class ScalarizedRefTabMap_W2X 
  : public FortTk::BaseMap<PU_Info*, ScalarizedRefTab_W2X*> {

public:
  ScalarizedRefTabMap_W2X();
  ScalarizedRefTabMap_W2X(PU_Info* pu_forest) { Create(pu_forest); }
  virtual ~ScalarizedRefTabMap_W2X();
  
  void Create(PU_Info* pu_forest);
};


// ---------------------------------------------------------
// ScalarizedRefTabMap: Specialization for X2W
// ---------------------------------------------------------

// It turns out that we do not really need this.


//***************************************************************************
// Variable References and WHIRL/XAIF
//***************************************************************************

// See tech report for explanation of three categories of references.

bool 
IsRefTranslatableToXAIF(const WN* wn);

bool 
IsRefSimple(const WN* wn);
bool 
IsRefSimpleScalar(const WN* wn);
bool 
IsRefSimpleArrayElem(const WN* wn);
bool 
IsRefSimpleArray(const WN* wn);

bool
IsRefScalarizable(const WN* wn);


bool 
IsRefScalar(TY_IDX baseobj_ty, TY_IDX refobj_ty);


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

// ForAllScalarizableRefsOp: Abstract base class for the operator passed
// to the function 'ForAllScalarizableRefs(...)'.  Any caller of this
// function must define its own operator object, using this class
// as a base class and providing a definition for 'operator()'.
class ForAllScalarizableRefsOp {
public:
  ForAllScalarizableRefsOp() { }
  virtual ~ForAllScalarizableRefsOp() { }

  // Given a non-scalar reference 'wn', does something interesting.
  // Returns 0 on success; non-zero on error.
  virtual int operator()(const WN* wn) = 0;
private: 
};

void 
ForAllScalarizableRefs(const WN* wn, ForAllScalarizableRefsOp& op);



// AddToScalarizedRefTabOp: Given a ScalarizedRefTab, add references to it
class AddToScalarizedRefTabOp : public ForAllScalarizableRefsOp {
public:
  AddToScalarizedRefTabOp(ScalarizedRefTab_W2X* tab_, PU_Info* curpu_);
  virtual ~AddToScalarizedRefTabOp();
  
  ScalarizedRefTab_W2X* GetTab() { return tab; }
  
  // Given a non-scalar reference 'wn', create a dummy variable and
  // add to the map.  
  int operator()(const WN* wn);

private:
  typedef std::map<std::string, ScalarizedRef*> WorkMapTy;

private:
  ScalarizedRefTab_W2X* tab;
  PU_Info* curpu;
  
  OA::OA_ptr<Open64IRInterface> ir;
  WorkMapTy workmap;
};


//***************************************************************************

#endif 
