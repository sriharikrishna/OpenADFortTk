// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.cxx,v 1.7 2003/09/17 19:43:26 eraxxon Exp $

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
    TY_IDX refobj_ty = WN_ty(wn);
    return (IsScalarRef(baseobj_ty, refobj_ty));
  }
  
  case OPR_ILOAD: { // memref
    TY_IDX baseobj_ty = TY_pointed(WN_load_addr_ty(wn));
    TY_IDX baseobj_ty1 = TY_pointed(WN_Tree_Type(WN_kid0(wn))); // FIXME
    assert(baseobj_ty = baseobj_ty1); // FIXME
    TY_IDX refobj_ty = WN_ty(wn);
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
    // OPR_IDNAME:
    
  case OPR_LDA:  // FIXME:
  case OPR_LDMA: // FIXME: 
    break; // can this be used to access records?
    
  case OPR_LDID:
  case OPR_LDBITS: 
  case OPR_STID:
  case OPR_STBITS: { // symref
    // For stores, only check LHS (kid1)
    TY_IDX baseobj_ty = ST_type(WN_st(wn));
    TY_IDX refobj_ty = WN_ty(wn);
    return (IsNonScalarRef(baseobj_ty, refobj_ty));
  }
  
  case OPR_ILOAD: { // memref
    TY_IDX baseobj_ty = TY_pointed(WN_load_addr_ty(wn));
    TY_IDX baseobj_ty1 = TY_pointed(WN_Tree_Type(WN_kid0(wn))); // FIXME
    assert(baseobj_ty = baseobj_ty1); // FIXME
    TY_IDX refobj_ty = WN_ty(wn);
    return (IsNonScalarRef(baseobj_ty, refobj_ty));
  }

  case OPR_ISTORE: { // memref
    // Only check LHS (kid1)
    TY_IDX baseobj_ty = TY_pointed(WN_ty(wn));
    TY_IDX refobj_ty = TY_pointed(WN_ty(wn));
    return (IsNonScalarRef(baseobj_ty, refobj_ty));
  }

  case OPR_ARRAY:
  case OPR_ARRSECTION: {
    // Arrays: 
    // Kid 0 is an LDA or LDID which represents the base of the array
    // being referenced or defined. Kids 1..n are dimensions; Kids
    // n+1..2n are the index expressions.
    WN* base = WN_kid0(wn);
    assert(WN_operator(base) == OPR_LDA || WN_operator(base) == OPR_LDID);
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
// XAIFSymToWhirlSymMap
//***************************************************************************

XAIFSymToWhirlSymMap::XAIFSymToWhirlSymMap()
{
}

XAIFSymToWhirlSymMap::~XAIFSymToWhirlSymMap()
{
  strToSTMap.clear();
}

ST*
XAIFSymToWhirlSymMap::Find(const char* scopeid, const char* symid) const
{
  std::string key = MakeKey(scopeid, symid);

  StringToSTMapItC it = strToSTMap.find(key);
  ST* st = (it == strToSTMap.end()) ? NULL : (*it).second;
  return st;
}

bool
XAIFSymToWhirlSymMap::Insert(const char* scopeid, const char* symid, 
			     const ST* st_)
{
  std::string key = MakeKey(scopeid, symid);
  ST* st = const_cast<ST*>(st_); // the map uses non const types
  
  StringToSTMapVal val = StringToSTMapVal(key, st);
  pair<StringToSTMapIt, bool> p = strToSTMap.insert(val);
  return p.second;
}

std::string 
XAIFSymToWhirlSymMap::MakeKey(const char* scopeid, const char* symid)
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
// NonScalarSym
//***************************************************************************

UINT NonScalarSym::nextId = 0; // static member

NonScalarSym::NonScalarSym()
{
  id = nextId++;
  name = cat("*nonscalarsym*", id);  
}

NonScalarSym::~NonScalarSym()
{
}

void 
NonScalarSym::Dump(std::ostream& o) const
{
  o << name;
}

void 
NonScalarSym::DDump() const
{
  Dump(std::cerr);
}

//***************************************************************************
// NonScalarSymTab
//***************************************************************************

UINT NonScalarSymTab::nextId = 0; // static member

NonScalarSymTab::NonScalarSymTab()
{
  id = nextId++;
  name = cat("*nonscalarstab*", id);
}

NonScalarSymTab::~NonScalarSymTab()
{
  // Clear table
  for (NonScalarSymTabIterator it(*this); it.IsValid(); ++it) {
    delete it.CurrentTarg(); // NonScalarSym*
  }
  wnToSymMap.clear();
}

NonScalarSym*
NonScalarSymTab::Find(const WN* wn_) const
{
  WN* wn = const_cast<WN*>(wn_); // WNToSymMap uses non const types

  WNToSymMapItC it = wnToSymMap.find(wn);
  NonScalarSym* sym = (it == wnToSymMap.end()) ? NULL : (*it).second;
  return sym;
}

bool
NonScalarSymTab::Insert(const WN* wn_, const NonScalarSym* sym_)
{
  WN* wn = const_cast<WN*>(wn_); // WNToSymMap uses non const types
  NonScalarSym* sym = const_cast<NonScalarSym*>(sym_);

  WNToSymMapVal val = WNToSymMapVal(wn, sym);
  pair<WNToSymMapIt, bool> p = wnToSymMap.insert(val);
  return p.second;
}

void
NonScalarSymTab::Dump(std::ostream& o, const char* pre) const
{
  std::string p = pre;
  std::string p1 = p + "  ";

  o << p << "{ ================== Begin NonScalar SymTab Dump ("
    << GetSize() << " Entries):\n";
  
  for (NonScalarSymTabIterator it(*this); it.IsValid(); ++it) {
    WN* wn = it.CurrentSrc();
    NonScalarSym* sym = it.CurrentTarg();
    o << p1 << wn << " --> ";
    sym->Dump(o);
    o << std::endl;
  }
  o << p << "End NonScalar SymTab Dump ================== }\n";
}

void
NonScalarSymTab::DDump() const
{
  Dump(std::cerr);
}

//***************************************************************************
// NonScalarSymTabIterator
//***************************************************************************

NonScalarSymTabIterator::NonScalarSymTabIterator(const NonScalarSymTab& x)
  : symtab(x)
{
  Reset();
}

NonScalarSymTabIterator::~NonScalarSymTabIterator()
{
}
