// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/ScalarizedRefTab.cxx,v 1.7 2004/06/09 20:42:29 eraxxon Exp $

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

UINT ScalarizedRefTab_Base::nextId = 0; // static member

ScalarizedRefTab_Base::ScalarizedRefTab_Base()
{
  id = nextId++;
  name = cat("*nonscalarstab*", id);
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
ScalarizedRefTabMap_W2X::Create(PU_Info* pu_forest, 
				ScalarizedRef::CreateOp* newref)
{ 
  ScalarizedRef::CreateOpDefault defnewref;
  if (!newref) {
    newref = &defnewref;
  }
  
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();
    
    ScalarizedRefTab_W2X* tab = new ScalarizedRefTab_W2X(pu, newref);
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
Create(PU_Info* pu, ScalarizedRef::CreateOp* newref)
{ 
  ScalarizedRef::CreateOpDefault defnewref;
  if (!newref) {
    newref = &defnewref;
  }
  
  WN* wn_pu = PU_Info_tree_ptr(pu);
  WN* fbody = WN_func_body(wn_pu);
  AddToScalarizedRefTabOp op(this, pu, *newref);
  ForAllNonScalarRefs(fbody, op);
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

ScalarizedRef::ScalarizedRef()
{
  id = nextId++;
  name = cat("scalarizedref", id);
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

// IsVarRefTranslatableToXAIF: Returns whether 'wn' a variable
// reference that can be translated into XAIF.  'wn' must be an
// expression; IOW it cannot be a store (=statement).
bool 
IsVarRefTranslatableToXAIF(const WN* wn)
{
  OPERATOR opr = WN_operator(wn);
  if (!OPERATOR_is_expression(opr)) { return false; }
  
  switch (opr) {
    // FIXME 
    // ILOADX, ISTOREX
    // ILDBITS, ISTBITS
    // MLOAD, MSTORE: memref
    // OPR_IDNAME:
    
  case OPR_LDA:
  case OPR_LDMA:
    return true; // FIXME: can this be used in some evil way?
    
  case OPR_LDID:
  case OPR_LDBITS: { // symref
    TY_IDX baseobj_ty = ST_type(WN_st(wn));
    TY_IDX refobj_ty = WN_Tree_Type(wn);
    return (IsScalarRef(baseobj_ty, refobj_ty));
  }
  
  case OPR_ILOAD: { // memref
    TY_IDX baseobj_ty = TY_pointed(WN_load_addr_ty(wn));
    TY_IDX refobj_ty = WN_Tree_Type(wn);
    return (IsScalarRef(baseobj_ty, refobj_ty));
  }
  
  case OPR_ARRAY:
  case OPR_ARRSECTION: // FIXME: can we do arrsection?
  case OPR_ARRAYEXP:
    return true;
    
  } // switch

  return false;
}


bool
IsScalarRef(TY_IDX baseobj_ty, TY_IDX refobj_ty) 
{
  if (TY_IsNonScalar(refobj_ty)) {
    // This is a reference to a non-scalar or a non-scalar within a
    // non-scalar (e.g. a record or a record within a record)
    return false; 
  } else if (TY_Is_Scalar(refobj_ty)) {
    // Test whether 'baseobj_ty' is assignable to 'refobj_ty'.  If
    // not, we have a non-scalar reference (e.g. a field within a
    // structure; an element within an array).
    return (WN2F_Can_Assign_Types(baseobj_ty, refobj_ty));
  } else {
    return false;
  }
}

bool
IsNonScalarRef(TY_IDX baseobj_ty, TY_IDX refobj_ty) 
{
  return (!IsScalarRef(baseobj_ty, refobj_ty));
}

// NOTE: for store OPERATORs, only the LHS is checked
bool
IsNonScalarRef(const WN* wn)
{
  // FIXME: redefine to be !IsVarRefTranslatableToXAIF

  OPERATOR opr = WN_operator(wn);
  switch (opr) {
    // FIXME 
    // ILOADX, ISTOREX
    // ILDBITS, ISTBITS
    // MLOAD, MSTORE: memref
    
  case OPR_LDA:  // FIXME:
  case OPR_LDMA: // FIXME: 
    break; // can this be used to access records?
    
  case OPR_LDID:
  case OPR_LDBITS: 
  case OPR_STID:
  case OPR_STBITS: { // symref
    // For stores, only check LHS (kid1)
    TY_IDX baseobj_ty = WN_GetBaseObjType(wn);
    TY_IDX refobj_ty = WN_GetRefObjType(wn);
    return (IsNonScalarRef(baseobj_ty, refobj_ty));
  }
  
  case OPR_ILOAD: 
  case OPR_ISTORE: { // memref
    // For stores, only check LHS (kid1)
    TY_IDX baseobj_ty = WN_GetBaseObjType(wn);
    TY_IDX refobj_ty = WN_GetRefObjType(wn);
    return (IsNonScalarRef(baseobj_ty, refobj_ty));
  }

  case OPR_ARRAY:
  case OPR_ARRSECTION: {
    // Arrays: 
    // Kid 0 is an LDA or LDID which represents the base of the array
    // being referenced or defined. Kids 1..n are dimensions; Kids
    // n+1..2n are the index expressions.
    WN* base = WN_kid0(wn);
    ASSERT_FATAL(WN_operator(base) == OPR_LDA || WN_operator(base) == OPR_LDID,
		 (DIAG_A_STRING, "Error!"));
    return true;
  }

  case OPR_ARRAYEXP: // FIXME
    return true;
    
  } // switch

  return false;
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

//FIXME: op should not be const because we call op(), which is non const.
void 
ForAllNonScalarRefs(const WN* wn, ForAllNonScalarRefsOp& op)
{
  // Special base case
  if (wn == NULL) { return; }

  OPERATOR opr = WN_operator(wn);
  if (IsNonScalarRef(wn)) {
    
    // Base case
    int ret = op(wn); // FIXME: what to do on error?
    
    // Special recursive case: Since WHIRL stores are statements (not
    // expressions) we need to check the RHS (kid0) of the implied
    // assignment for non-scalar references.
    if (OPERATOR_is_store(opr)) {
      ForAllNonScalarRefs(WN_kid0(wn), op);
    }

  } else if (!OPERATOR_is_leaf(opr)) {
    
    // General recursive case
    if (WN_operator(wn) == OPR_BLOCK) {
      WN *kid = WN_first(wn);
      while (kid) {
	ForAllNonScalarRefs(kid, op);
	kid = WN_next(kid);
      }
    } else {
      for (INT kidno = 0; kidno < WN_kid_count(wn); kidno++) {
	WN* kid = WN_kid(wn, kidno);
	ForAllNonScalarRefs(kid, op);
      }
    }
    
  }
}


AddToScalarizedRefTabOp::
AddToScalarizedRefTabOp(ScalarizedRefTab_W2X* tab_, 
			PU_Info* curpu_,
			ScalarizedRef::CreateOp& newref_)
  : tab(tab_), curpu(curpu_), newrefop(newref_)
{ 
  ASSERT_FATAL(tab, (DIAG_A_STRING, "Programming Error."));
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
    sym = newrefop(curpu, wn, s.c_str());
    workmap.insert(make_pair(s, sym));
  } else {
    sym = (*it).second;
  }
  
#if 0
  cout << "Ref: '" << s << "' --> "; sym->Dump(cout); cout << endl;
  fdump_tree(stdout, (WN*)wn);
#endif  

  // insert <wn, sym> in tab
  tab->Insert(wn, sym);
}

