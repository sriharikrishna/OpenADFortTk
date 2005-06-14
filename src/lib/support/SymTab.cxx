// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.cxx,v 1.14 2005/06/14 16:55:35 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "SymTab.h"

#include "stab_attr.h"
#include "wn_attr.h"
#include "diagnostics.h"

//************************** Forward Declarations ***************************

//***************************************************************************
// XAIFSymToSymbolMap
//***************************************************************************

XAIFSymToSymbolMap::XAIFSymToSymbolMap()
{
}

XAIFSymToSymbolMap::~XAIFSymToSymbolMap()
{
  // Clear table
  StringToSymMapIt it = strToSymMap.begin();
  for ( ; it != strToSymMap.end(); ++it) {
    delete (*it).second; // Symbol*
  }
  strToSymMap.clear();
}

Symbol*
XAIFSymToSymbolMap::Find(const char* scopeid, const char* symid) const
{
  std::string key = MakeKey(scopeid, symid);
  
  StringToSymMapItC it = strToSymMap.find(key);
  Symbol* sym = (it == strToSymMap.end()) ? NULL : (*it).second;
  return sym;
}

bool
XAIFSymToSymbolMap::Insert(const char* scopeid, const char* symid, 
			   const Symbol* sym_)
{
  std::string key = MakeKey(scopeid, symid);
  Symbol* sym = const_cast<Symbol*>(sym_); // the map uses non const types
  
  StringToSymMapVal val = StringToSymMapVal(key, sym);
  pair<StringToSymMapIt, bool> p = strToSymMap.insert(val);
  return p.second;
}

std::string 
XAIFSymToSymbolMap::MakeKey(const char* scopeid, const char* symid)
{
  // Reserve enough space for null terminators and concatination char
  std::string key;
  key.reserve(strlen(scopeid) + strlen(symid) + 3);

  key += scopeid;
  key += ".";
  key += symid;
  return key;
}

//***************************************************************************
// Symbol
//***************************************************************************

Symbol::Symbol()
  : st(NULL), active(false)
{
}

Symbol::Symbol(const ST* st_, WNId wnid_, bool act_)
{
  SetST(st_);
  SetPathVorlage(wnid_);
  SetActive(act_);
}

Symbol::~Symbol()
{
}

void 
Symbol::Dump(std::ostream& o) const
{
  o << "Symbol\n";
}

void 
Symbol::DDump() const
{
  Dump(std::cerr);
}

//***************************************************************************
// Stuff copied from SymTab.cpp in UseNewOA-Open64
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
// 
//***************************************************************************

// IsVarRefTranslatableToXAIF: Returns whether 'wn' a variable
// reference that can be translated into XAIF.  'wn' must be an
// expression; IOW it cannot be a store (=statement).
bool 
IsVarRefTranslatableToXAIF(const WN* wn)
{
  // FIXME: IsScalarRef should perhaps be is_translatable_to_xaif

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

  default:
    break; // fall through
    
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
    //WN* base = WN_kid0(wn);
    //ASSERT_FATAL(WN_operator(base) == OPR_LDA || WN_operator(base) == OPR_LDID,
    //             (DIAG_A_STRING, "Error!"));
    return true;
  }

  case OPR_ARRAYEXP: // FIXME
    return true;

  default: 
    break; // fall through
    
  } // switch

  return false;
}

// FIXME: 
/* also in ScalarizedRefTab.cxx
bool
WN2F_Can_Assign_Types(TY_IDX ty1, TY_IDX ty2)
{
  bool simple = Stab_Identical_Types(ty1, ty2, FALSE, //check_quals
				     FALSE, //check_scalars
				     TRUE); //ptrs_as_scalars
  bool special = (TY_Is_Array(ty1) && TY_is_character(ty1) && 
		  TY_Is_Array(ty2) && TY_is_character(ty2));
  return (simple || special);
}
*/


