// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/ScalarizedRefTab.cxx,v 1.13 2005/01/19 22:54:53 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/ScalarizedRefTab.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

#include <sstream>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//************************ OpenAnalysis Include Files ***********************

#include <OpenAnalysis/ValueNumbers/ExprTree.h>

//*************************** User Include Files ****************************

#include "Pro64IRInterface.h"
#include "ScalarizedRefTab.h"

#include "stab_attr.h"
#include "wn_attr.h"
#include "diagnostics.h"

//************************** Forward Declarations ***************************

//***************************************************************************

// FIXME
// Create a new symbol name
static const char* cat(const char* str, UINT num)
{
// 39 bytes hold a 128-bit uint in base 10. [log(2^128)]
#define SYMBUF_SZ (32 + 39 + 1)
  static char buf[SYMBUF_SZ];
  snprintf(buf, SYMBUF_SZ, "%s%d", str, num);
  return buf;
#undef SYMBUF_SZ
}


//***************************************************************************
// ScalarizedRefTab (helper types)
//***************************************************************************

ScalarizedRefTab_Base::ScalarizedRefTab_Base()
{
}

ScalarizedRefTab_Base::~ScalarizedRefTab_Base()
{
}


//***************************************************************************
// ScalarizedRefTabMap
//***************************************************************************

ScalarizedRefTabMap_W2X::ScalarizedRefTabMap_W2X()
{
}

ScalarizedRefTabMap_W2X::~ScalarizedRefTabMap_W2X()
{
  for (iterator it = begin(); it != end(); ++it) {
    delete (*it).second; // ScalarizedRefTab_W2X*
  }
  clear();
}

void
ScalarizedRefTabMap_W2X::Create(PU_Info* pu_forest)
{ 
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();
    
    ScalarizedRefTab_W2X* tab = new ScalarizedRefTab_W2X(pu);
    Insert(pu, tab);
  }
}


//***************************************************************************
// ScalarizedRefTab
//***************************************************************************

ScalarizedRefTab<ScalarizedRefTab_Base::W2X>::
ScalarizedRefTab()
{
}

ScalarizedRefTab<ScalarizedRefTab_Base::W2X>::
~ScalarizedRefTab()
{
  // Clear table ref pool
  for (ScalarizedRefPoolTy::iterator it = scalarizedRefPool.begin();
       it != scalarizedRefPool.end(); ++it) {
    delete (*it); // ScalarizedRef*
  }
  scalarizedRefPool.clear();
  
  // Clear Table
  clear();
}


void
ScalarizedRefTab<ScalarizedRefTab_Base::W2X>::
Create(PU_Info* pu)
{ 
  WN* wn_pu = PU_Info_tree_ptr(pu);
  WN* fbody = WN_func_body(wn_pu);
  AddToScalarizedRefTabOp op(this, pu);
  ForAllScalarizableRefs(fbody, op);
}

void
ScalarizedRefTab<ScalarizedRefTab_Base::W2X>::
Dump(std::ostream& o, const char* pre) const
{
  std::string p = pre;
  std::string p1 = p + "  ";

  o << p << "{ ================== Begin ScalarizedRefTab Dump ("
    << size() << " Entries):\n";
  
  for (const_iterator it = begin(); it != end(); ++it) {
    WN* wn = (*it).first;
    ScalarizedRef* sym = (*it).second;
    o << p1 << wn << " --> ";
    sym->Dump(o);
    o << std::endl;
  }
  o << p << "End ScalarizedRefTab Dump ================== }\n";
}

void
ScalarizedRefTab<ScalarizedRefTab_Base::W2X>::
DDump() const
{
  Dump(std::cerr);
}

//***************************************************************************
// ScalarizedRef
//***************************************************************************

UINT ScalarizedRef::nextId = 0; // static member

void
ScalarizedRef::Ctor(WN* wn_, const char* x)
{
  wn = wn_;
  id = nextId++;
  name.reserve(13 + ((x) ? strlen(x) : 0));
  name = cat("scalarizedref", id);
  if (x) {
    name += x;
  }
}

ScalarizedRef::~ScalarizedRef()
{
}

void 
ScalarizedRef::Dump(std::ostream& o) const
{
  o << name;
}

void 
ScalarizedRef::DDump() const
{
  Dump(std::cerr);
}


//***************************************************************************
// 
//***************************************************************************

// IsRefTranslatableToXAIF: Returns whether 'wn' a variable
// reference that can be translated into XAIF.  'wn' must be an
// expression; IOW it cannot be a store (=statement).
bool 
IsRefTranslatableToXAIF(const WN* wn)
{
  return (IsRefSimple(wn) || IsRefScalarizable(wn));
}


// IsRefSimple: 
//   Note: WHIRL stores represent the lhs var-ref (e.g. OPR_ISTORE,
//   OPR_STID)
bool 
IsRefSimple(const WN* wn)
{
  //if (!(opr == OPR_STID || OPERATOR_is_expression(opr))) { return false; }  
  return (IsRefSimpleScalar(wn) || IsRefSimpleArrayElem(wn) 
	  || IsRefSimpleArray(wn));
}


// IsRefSimpleScalar: 
bool
IsRefSimpleScalar(const WN* wn)
{
  OPERATOR opr = WN_operator(wn);
  switch (opr) {
    
  case OPR_LDA:
  case OPR_LDMA:
  case OPR_LDID:
  case OPR_LDBITS: 
  case OPR_STID:
  case OPR_STBITS: 
  case OPR_ILOAD: 
  case OPR_ILDBITS: {
    // (for stores, only check LHS (kid1))
    TY_IDX baseobj_ty = WN_GetBaseObjType(wn);
    TY_IDX refobj_ty = WN_GetRefObjType(wn);
    if (opr == OPR_LDA || opr == OPR_LDMA) {
      // dereference the pointer (assume Fortran)
      refobj_ty = TY_pointed(refobj_ty);
    }
    return (IsRefScalar(baseobj_ty, refobj_ty));
  }
    
  default: 
    break; // fall through

  } // switch
  
  return false;
}


// IsRefSimpleArrayElem: 
bool 
IsRefSimpleArrayElem(const WN* wn)
{
  OPERATOR opr = WN_operator(wn);
  switch (opr) {
    
  case OPR_LDA:  
  case OPR_LDMA: 
  case OPR_LDID: // probably never used for this
  case OPR_STID: // probably never used for this
  case OPR_ILOAD:
  case OPR_ISTORE: {
    // yes if baseobj_ty is of type array and reference is non-scalar
    // (for stores, only check LHS (kid1))
    TY_IDX baseobj_ty = WN_GetBaseObjType(wn);
    TY_IDX refobj_ty = WN_GetRefObjType(wn);
#if 0
    if (/* array element access */) {
    FORTTK_ASSERT_WARN(WN2F_Can_Assign_Types(TY_AR_etype(baseobj_ty), 
					     refobj_ty),
		       "Incompatible types");
    }
#endif
    return (TY_Is_Array(baseobj_ty) && !IsRefScalar(baseobj_ty, refobj_ty));
  }
  
  case OPR_ARRAY:
    return true;

  default: 
    break; // fall through
    
  } // switch

  return false;
}


// IsRefSimpleArray: 
bool 
IsRefSimpleArray(const WN* wn)
{
  OPERATOR opr = WN_operator(wn);
  switch (opr) {
    
  case OPR_LDA:  
  case OPR_LDMA: 
  case OPR_LDID: {
    // yes if refobj_ty is of type array
    TY_IDX baseobj_ty = WN_GetBaseObjType(wn);
    TY_IDX refobj_ty = WN_GetRefObjType(wn);
    return (TY_Is_Array(refobj_ty));
  }
    
  case OPR_ARRSECTION: // FIXME: can we do arrsection?
  case OPR_ARRAYEXP:
    return true;

  default: 
    break; // fall through
    
  } // switch
  
  return false;
}


// IsRefScalarizable: 
bool
IsRefScalarizable(const WN* wn)
{
  OPERATOR opr = WN_operator(wn);
  switch (opr) {
    // FIXME: ILOADX, ISTOREX  /  ILDBITS, ISTBITS
    
  case OPR_LDA: 
  case OPR_LDMA: 
  case OPR_LDID: 
  case OPR_LDBITS: 
  case OPR_STID: 
  case OPR_STBITS: 
  case OPR_ILOAD: 
  case OPR_ISTORE: {
    // yes if refobj_ty is scalar and reference is non-scalar
    // (for stores, only check LHS (kid1))
    TY_IDX baseobj_ty = WN_GetBaseObjType(wn);
    TY_IDX refobj_ty = WN_GetRefObjType(wn);
    return (TY_Is_Scalar(refobj_ty) && !IsRefScalar(baseobj_ty, refobj_ty));
  }

  default: 
    break; // fall through
    
  } // switch

  return false;
}


// IsRefScalar: 
bool
IsRefScalar(TY_IDX baseobj_ty, TY_IDX refobj_ty) 
{
  if (TY_IsNonScalar(refobj_ty)) {
    // This is a reference to a non-scalar or a non-scalar within a
    // non-scalar (e.g. a record or a record within a record)
    return false; 
  } 
  else if (TY_Is_Scalar(refobj_ty)) {
    // Test whether 'baseobj_ty' is assignable to 'refobj_ty'.  If
    // not, we have a non-scalar reference (e.g. a field within a
    // structure; an element within an array).
    return (WN2F_Can_Assign_Types(baseobj_ty, refobj_ty));
  } 
  else {
    return false;
  }
}


// FIXME: 
bool
WN2F_Can_Assign_Types(TY_IDX ty1, TY_IDX ty2)
{
  bool simple = Stab_Identical_Types(ty1, ty2, FALSE, /*check_quals*/
				     FALSE, /*check_scalars*/ 
				     TRUE); /*ptrs_as_scalars*/
  bool special = (TY_Is_Array(ty1) && TY_is_character(ty1) && 
		  TY_Is_Array(ty2) && TY_is_character(ty2));
  return (simple || special);
}


//***************************************************************************
//
//***************************************************************************

void 
ForAllScalarizableRefs(const WN* wn, ForAllScalarizableRefsOp& op)
{
  // Special base case
  if (wn == NULL) { return; }

  OPERATOR opr = WN_operator(wn);
  if (IsRefScalarizable(wn)) {
    
    // Base case
    int ret = op(wn); // FIXME: what to do on error?
    
    // Special recursive case: Since WHIRL stores are statements (not
    // expressions) we need to check the RHS (kid0) of the implied
    // assignment for non-scalar references.
    if (OPERATOR_is_store(opr)) {
      ForAllScalarizableRefs(WN_kid0(wn), op);
    }

  } 
  else if (!OPERATOR_is_leaf(opr)) {
    
    // General recursive case
    if (WN_operator(wn) == OPR_BLOCK) {
      WN *kid = WN_first(wn);
      while (kid) {
	ForAllScalarizableRefs(kid, op);
	kid = WN_next(kid);
      }
    } 
    else {
      for (INT kidno = 0; kidno < WN_kid_count(wn); kidno++) {
	WN* kid = WN_kid(wn, kidno);
	ForAllScalarizableRefs(kid, op);
      }
    }
    
  }
}


AddToScalarizedRefTabOp::
AddToScalarizedRefTabOp(ScalarizedRefTab_W2X* tab_, PU_Info* curpu_)
  : tab(tab_), curpu(curpu_)
{ 
  FORTTK_ASSERT(tab_, FORTTK_UNEXPECTED_INPUT);
  ir = Pro64IRInterface();
}

AddToScalarizedRefTabOp::~AddToScalarizedRefTabOp()
{
  workmap.clear();
}


// Given a non-scalar reference 'wn', create a dummy variable and
// add to the map.  
int 
AddToScalarizedRefTabOp::operator()(const WN* wn) 
{
  // create a hash of this reference
  ExprTree *e = ir.GetExprTreeForExprHandle((ExprHandle)wn);
  ostringstream o;
  e->str(o);
  string s = o.str();
  
  // if <hash, sym> not already in workmap, insert <hash, new sym>
  ScalarizedRef* sym = NULL;
  WorkMapTy::iterator it = workmap.find(s);
  if (it == workmap.end()) {
    sym = new ScalarizedRef(const_cast<WN*>(wn));
    workmap.insert(make_pair(s, sym));
  } 
  else {
    sym = (*it).second;
  }
  
#if 0
  cout << "Ref: '" << s << "' --> "; sym->Dump(cout); cout << endl;
  fdump_tree(stdout, (WN*)wn);
#endif  

  // insert <wn, sym> in tab
  tab->Insert(wn, sym);
  return 0;
}

