// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/ScalarizedRefTab.h,v 1.7 2004/06/09 20:42:29 eraxxon Exp $

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
#include "Pro64IRInterface.h"
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
  
  // Return a globally unique name
  std::string& GetName() { return name; }

  // Return an id, globally unique across instances of this class
  UINT GetId() const { return id; }

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
  
  std::string name; // FIXME: 
  UINT id;
  
  static UINT nextId; // for globally uniqe id numbers
};


//***************************************************************************
// ScalarizedRef
//***************************************************************************

class ScalarizedRef {

public:
  class CreateOp {
  public:
    CreateOp() { }
    virtual ~CreateOp() { }
    
    // Given the current PU_Info*, the WN* of the first occurance of
    // this reference in the PU, and the assoc hash string, create a
    // ScalarizedRef
    virtual ScalarizedRef* 
    operator()(const PU_Info* pu, const WN* wn, const char* hstr) = 0;
    
  private: 
  };
  
  class CreateOpDefault : public CreateOp {
  public:
    CreateOpDefault() { }
    virtual ~CreateOpDefault() { }
    
    virtual ScalarizedRef* 
    operator()(const PU_Info* pu, const WN* wn, const char* hstr) 
    { return new ScalarizedRef(); }
    
  private: 
  };

  
public:
  // Constructor: if 'x' is supplied, it will be appended to the
  // symbol name
  ScalarizedRef();
  ScalarizedRef(const char* x);
  virtual ~ScalarizedRef();
  
  // GetName: Return a globally unique dummy symbol name
  std::string& GetName() { return name; }
  
  // GetId: Return an id, globally unique across instances of this class
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

class ScalarizedRefTab<ScalarizedRefTab_Base::W2X>
  : public ScalarizedRefTab_Base,
    public FortTk::BaseMap<WN*, ScalarizedRef*> {

public:
  // Constructor allocates an empty data structure
  ScalarizedRefTab();
  ScalarizedRefTab(PU_Info* pu, ScalarizedRef::CreateOp* newref = NULL)
  { Create(pu, newref); }
  virtual ~ScalarizedRefTab();
  
  // Create: Fills in map
  void Create(PU_Info* pu, ScalarizedRef::CreateOp* newref = NULL);
  
  // Find: a version with const params for convenience
  ScalarizedRef* 
  Find(const WN* x_, bool mustFind = false) const
  {
    WN* x = const_cast<WN*>(x_);
    return FortTk::BaseMap<WN*, ScalarizedRef*>::Find(x, mustFind);
  }
  
  
  // Insert: override to manage scalar ref pool
  bool 
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
  virtual void Dump(std::ostream& o = std::cerr, const char* pre = "") const;
  virtual void DDump() const;
  
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
  ScalarizedRefTabMap_W2X(PU_Info* pu_forest, 
			  ScalarizedRef::CreateOp* newref = NULL)
  { Create(pu_forest, newref); }
  virtual ~ScalarizedRefTabMap_W2X();
  
  void Create(PU_Info* pu_forest, ScalarizedRef::CreateOp* newref = NULL);
};


// ---------------------------------------------------------
// ScalarizedRefTabMap: Specialization for X2W
// ---------------------------------------------------------

// It turns out that we do not really need this.


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
  AddToScalarizedRefTabOp(ScalarizedRefTab_W2X* tab_, 
			  PU_Info* curpu_,
			  ScalarizedRef::CreateOp& newref_);
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
  ScalarizedRef::CreateOp& newrefop;
  
  Pro64IRInterface ir;
  WorkMapTy workmap;
};


//***************************************************************************

#endif 
