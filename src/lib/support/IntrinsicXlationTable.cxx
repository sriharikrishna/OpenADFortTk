// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/IntrinsicXlationTable.cxx,v 1.22 2005/01/18 19:45:11 utke Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/IntrinsicXlationTable.cxx,v $
//
// Purpose:
//    [The purpose of this file]
//
// Description:
//    [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <stdlib.h>  // for bsearch() and qsort()
#include <algorithm> 

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

#include "IntrinsicXlationTable.h"
#include "wn_attr.h" // for WN_intrinsic_name()
#include "diagnostics.h"

//*************************** Forward Declarations ***************************

using std::endl;
using std::hex;
using std::dec;


//****************************************************************************

//****************************************************************************
// IntrinsicXlationTable
//****************************************************************************

#define TABLE_SZ \
  (sizeof(IntrinsicXlationTable::table) / sizeof(IntrinsicXlationTable::Entry))


IntrinsicXlationTable::Entry IntrinsicXlationTable::table[] = {

  // -------------------------------------------------------
  // WHIRL calls, expressions and intrinsics that correspond to XAIF
  // Intrinsics.  
  //
  // For OPR_INTRINSIC_OP, the WHIRL string is the INTRINSIC_basename()
  // (cf. wintrinsic.h, wutil.cxx)
  // -------------------------------------------------------

  // Common mathematical functions
  { { WNExpr, OPR_NEG, NULL, 1 },
                        { XAIFIntrin, "minus_scal", NULL, 1 } },
  { { WNExpr, OPR_ADD, NULL, 2 },
                        { XAIFIntrin, "add_scal_scal", NULL, 2 } },
  { { WNExpr, OPR_SUB, NULL, 2 },
                        { XAIFIntrin, "sub_scal_scal", NULL, 2 } },
  { { WNExpr, OPR_MPY, NULL, 2 },
                        { XAIFIntrin, "mul_scal_scal", NULL, 2 } },
  { { WNExpr, OPR_DIV, NULL, 2 },
                        { XAIFIntrin, "div_scal_scal", NULL, 2 } },

  { { WNCall, OPR_CALL, "SQRT", 1 },
                        { XAIFIntrin, "sqrt_scal", "0_SQRT", 1 } },
  { { WNCall, OPR_CALL, "DSQRT", 1 },
                        { XAIFIntrin, "sqrt_scal", "1_DSQRT", 1 } },
  { { WNExpr, OPR_SQRT, NULL, 1 },
                        { XAIFIntrin, "sqrt_scal", "2_SQRT", 1 } },

  { { WNExpr, OPR_MOD, NULL, 2 },
                        { XAIFIntrin, "bogus_modulo_scal_scal", "0_MODULO", 2 } },

  /* is a call to MODULE semantically teh same as OPR_MOD? */
  { { WNCall, OPR_CALL, "MODULO", 2 },
                        { XAIFIntrin, "bogus_modulo_scal_scal", "1_MODULO", 1 } },


  { { WNExpr, OPR_REM, NULL, 2 },
                        { XAIFIntrin, "mod_scal_scal", "0_MOD", 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "AMOD", 2 }, 
                        { XAIFIntrin, "mod_scal_scal", "1_AMOD", 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "DMOD", 2 }, 
                        { XAIFIntrin, "mod_scal_scal", "2_DMOD", 2 } },

  { { WNCall, OPR_CALL, "SIN", 1 },
                        { XAIFIntrin, "sin_scal", "0_SIN", 1 } },
  { { WNCall, OPR_CALL, "DSIN", 1 },
                        { XAIFIntrin, "sin_scal", "1_DSIN", 1 } },
  { { WNCall, OPR_CALL, "COS", 1 },
                        { XAIFIntrin, "cos_scal", "0_COS", 1 } },
  { { WNCall, OPR_CALL, "DCOS", 1 },
                        { XAIFIntrin, "cos_scal", "1_DCOS", 1 } },
  { { WNCall, OPR_CALL, "TAN", 1 },
                        { XAIFIntrin, "tan_scal", "0_TAN", 1 } },
  { { WNCall, OPR_CALL, "DTAN", 1 },
                        { XAIFIntrin, "tan_scal", "1_DTAN", 1 } },

  { { WNCall, OPR_CALL, "ASIN", 1 },
                        { XAIFIntrin, "arcsin_scal", "0_ASIN", 1 } },
  { { WNCall, OPR_CALL, "ACOS", 1 },
                        { XAIFIntrin, "arccos_scal", "0_ACOS", 1 } },
  { { WNCall, OPR_CALL, "ATAN", 1 },
                        { XAIFIntrin, "arctan_scal", "0_ATAN", 1 } },
  
  // hyperbolic fns

  { { WNCall, OPR_CALL, "EXP", 1 },
                        { XAIFIntrin, "exp_scal", "0_EXP", 1 } },
  { { WNCall, OPR_CALL, "DEXP", 1 },
                        { XAIFIntrin, "exp_scal", "1_DEXP", 1 } },
  { { WNCall, OPR_CALL, "LOG", 1 },
                        { XAIFIntrin, "ln_scal", "0_LOG", 1 } },
  { { WNCall, OPR_CALL, "DLOG", 1 },
                        { XAIFIntrin, "ln_scal", "1_DLOG", 1 } }, 

  { { WNIntrinOp, OPR_INTRINSIC_OP, "EXPEXPR", 2 }, 
                        { XAIFIntrin, "pow_scal_scal", NULL, 2 } },

  { { WNIntrinOp, OPR_INTRINSIC_OP, "CEQEXPR", 2 }, 
                        { XAIFIntrin, "string_eq_scal_scal", NULL, 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "CNEEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_ne_scal_scal", NULL, 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "CGEEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_ge_scal_scal", NULL, 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "CGTEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_gt_scal_scal", NULL, 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "CLEEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_le_scal_scal", NULL, 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "CLTEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_lt_scal_scal", NULL, 2 } },
  
  // Rounding, conversion
  { { WNExpr, OPR_ABS, NULL, 1 },
                        { XAIFIntrin, "abs_scal", "0_ABS", 1 } },
  { { WNCall, OPR_CALL, "ABS", 1 },
                        { XAIFIntrin, "abs_scal", "1_ABS", 1 } },
  { { WNCall, OPR_CALL, "DABS", 1 },
                        { XAIFIntrin, "abs_scal", "2_DABS", 1 } },
  { { WNCall, OPR_CALL, "IABS", 1 },
                        { XAIFIntrin, "iabs_scal", "0_IABS", 1 } },

  { { WNCall, OPR_CALL, "SIGN", 2 },
                        { XAIFIntrin, "sign_scal_scal", "0_SIGN", 2 } },

  { { WNExpr, OPR_RND, NULL, 1 },
                        { XAIFIntrin, "bogus_round_scal", NULL, 1 } },
  { { WNExpr, OPR_TRUNC, NULL, 1 },
                        { XAIFIntrin, "int_scal", NULL, 1 } },
  { { WNExpr, OPR_CEIL, NULL, 1 },
                        { XAIFIntrin, "bogus_ceil_scal", NULL, 1 } },
  { { WNExpr, OPR_FLOOR, NULL, 1 },
                        { XAIFIntrin, "bogus_floor_scal", NULL, 1 } },

  { { WNCall, OPR_CALL, "REAL", 1 },
                        { XAIFIntrin, "real_int_scal", NULL, 1 } },
  { { WNCall, OPR_CALL, "DBLE", 1 },
                        { XAIFIntrin, "bogus_dble_scal", NULL, 1 } },

  { { WNCall, OPR_CALL, "NINT", 1 },
                        { XAIFIntrin, "nint_scal", "0_NINT", 1 } },

  // Logical (and bitwise logical) operations

  { { WNExpr, OPR_BNOT, NULL, 1 },
                        { XAIFBoolOp, "not", "1_not_bitwise", 1 } },
  { { WNExpr, OPR_BAND, NULL, 2 },
                        { XAIFBoolOp, "and", "1_and_bitwise", 2 } },
  { { WNExpr, OPR_BIOR, NULL, 2 },
                        { XAIFBoolOp, "or", "1_or_bitwise", 2 } },
  { { WNExpr, OPR_BXOR, NULL, 2 },
                        { XAIFBoolOp, "xor", "1_xor_bitwise", 2 } },

  { { WNExpr, OPR_LNOT, NULL, 1 },
                        { XAIFBoolOp, "not", "0_not_logical", 1 } },
  { { WNExpr, OPR_LAND, NULL, 2 },
                        { XAIFIntrin, "and", "0_and_logical", 2 } },
  { { WNExpr, OPR_LIOR, NULL, 2 },
                        { XAIFIntrin, "or", "0_or_logical", 2 } },
  { { WNExpr, OPR_CAND, NULL, 2 },
                        { XAIFIntrin, "bogus_cand_scal_scal", NULL, 2 } },
  { { WNExpr, OPR_CIOR, NULL, 2 },
                        { XAIFIntrin, "bogus_cor_scal_scal", NULL, 2 } },

  { { WNExpr, OPR_EQ, NULL, 2 },
                        { XAIFBoolOp, "equal", NULL, 2 } },
  { { WNExpr, OPR_NE, NULL, 2 },
                        { XAIFBoolOp, "not_equal", NULL, 2 } },
  { { WNExpr, OPR_GT, NULL, 2 },
                        { XAIFBoolOp, "greater_than", NULL, 2 } },
  { { WNExpr, OPR_GE, NULL, 2 },
                        { XAIFBoolOp, "greater_or_equal", NULL, 2 } },
  { { WNExpr, OPR_LT, NULL, 2 },
                        { XAIFBoolOp, "less_than", NULL, 2 } },
  { { WNExpr, OPR_LE, NULL, 2 },
                        { XAIFBoolOp, "less_or_equal", NULL, 2 } },


  // Misc.
  { { WNExpr, OPR_SHL, NULL, 2 },
                        { XAIFIntrin, "bogus_shl_scal_scal", NULL, 2 } },
  { { WNExpr, OPR_ASHR, NULL, 2 },
                        { XAIFIntrin, "bogus_ashr_scal_scal", NULL, 2 } },

  { { WNExpr, OPR_MAX, NULL, 2 },
                        { XAIFIntrin, "bogus_max_scal_scal", NULL, 2 } },
  { { WNExpr, OPR_MIN, NULL, 2 },
                        { XAIFIntrin, "bogus_min_scal_scal", NULL, 2 } }
  
};

unsigned int IntrinsicXlationTable::tableSz = TABLE_SZ;

#undef TABLE_SZ

//****************************************************************************

#if 0
IntrinsicXlationTable::WHIRLInfo::WHIRLInfo()
  : oprcl(WNOprClass_UNKNOWN), opr(0), name(NULL), numop(0)
{
}

IntrinsicXlationTable::XAIFInfo::XAIFInfo()
  : opr(XAIFOpr_UNKNOWN), name(NULL), numop(0)
{
}
#endif

//****************************************************************************

const char* 
IntrinsicXlationTable::ToString(WNOprClass oprcl)
{
  switch (oprcl) {
    case WNCall:       return "WNCall";
    case WNIntrinCall: return "WNIntrinCall";
    case WNIntrinOp:   return "WNIntrinOp";
    case WNExpr:       return "WNExpr";
    default:           return "<invalid-WNOprClass>";
  }
  return NULL; // should never reach
}

const char* 
IntrinsicXlationTable::ToString(XAIFOpr opr)
{
  switch (opr) {
    case XAIFSubCall:  return "XAIFSubCall";
    case XAIFFuncCall: return "XAIFFuncCall";
    case XAIFIntrin:   return "XAIFIntrinsic";
    case XAIFBoolOp:   return "XAIFBoolOp";
    default:           return "<invalid-XAIFOpr>";
  }
  return NULL; // should never reach
}

void
IntrinsicXlationTable::WHIRLInfo::Dump(std::ostream& os) const
{
  os << "{ " 
     << ToString(oprcl) << ", " 
     << OPERATOR_name(opr) << ", "
     << ((name) ? name : "<null>") << ", "
     << numop 
     << " }";
}

void
IntrinsicXlationTable::WHIRLInfo::DDump() const
{
  Dump(std::cerr);
}

void
IntrinsicXlationTable::XAIFInfo::Dump(std::ostream& os) const
{
  os << "{ " 
     << ToString(opr) << ", " 
     << ((name) ? name : "<null>") << ", " 
     << ((key) ? key : "<null>") << ", " 
     << numop 
     << " }";
}

void
IntrinsicXlationTable::XAIFInfo::DDump() const
{
  Dump(std::cerr);
}

//****************************************************************************

bool 
IntrinsicXlationTable::lt_SortedTable::
operator()(const Entry* e1, const Entry* e2) const
{
  if (tt == W2X) {
    // 1. whirl_info.opr is the primary sorting key
    if (e1->whirl_info.opr == e2->whirl_info.opr) {
      
      // Either 1) both whirl_info.oprcl will be equal or 2) one will
      // be 'WNOprClass_UNKNOWN' (the search item)
      WNOprClass cl = (e1->whirl_info.oprcl == WNOprClass_UNKNOWN) ? 
	e2->whirl_info.oprcl : e1->whirl_info.oprcl;

      switch (cl) {
      case WNCall:
      case WNIntrinCall:
      case WNIntrinOp:
	// 2. whirl_info.name is the secondary sorting key
	return (strcmp(e1->whirl_info.name, e2->whirl_info.name) < 0);
      case WNExpr:
	// 2. There is no secondary sorting key
	return false; // e1 and e2 are equal
      default:
	FORTTK_DIE("Internal IntrinsicXlationTable error: Unknown WNOprClass: "
		   << cl);
      }
    } 
    else {
      return (e1->whirl_info.opr < e2->whirl_info.opr);
    }
  } 
  else if (tt == X2W) {
    // 1. xaif_info.opr is the primary sorting key
    if (e1->xaif_info.opr == e2->xaif_info.opr) {
      // 2. xaif_info.name is the secondary sorting key
      int cmp = (strcmp(e1->xaif_info.name, e2->xaif_info.name));
      if (!ignoreXaifKey && cmp == 0) {
	// 3. xaif_info.key, if available, is the tertiary sorting key
	if (e1->xaif_info.key && e2->xaif_info.key) {
	  return (strcmp(e1->xaif_info.key, e2->xaif_info.key) < 0);
	}
	else if (e1->xaif_info.key) /* && !e2->xaif_info.key */ {
	  return false; // e1 > e2
	}
	else if (e2->xaif_info.key) /* && !e1->xaif_info.key */ {
	  return true; // e1 < e2
	}
	// fall-through
      } 
      return (cmp < 0);
    } 
    else {
      return (e1->xaif_info.opr < e2->xaif_info.opr);
    }
  } 
  else {
    FORTTK_DIE("Internal IntrinsicXlationTable error: Unknown TableType: " 
	       << tt);
  }
}

//****************************************************************************

class PrintEntry 
  : public std::unary_function<IntrinsicXlationTable::Entry*, void> {

public:
  PrintEntry(std::ostream& os_, IntrinsicXlationTable::TableType tt_)
    : os(os_), tt(tt_) { }
  ~PrintEntry() { }
  
  void 
  operator() (IntrinsicXlationTable::Entry* x) 
  {
    if (tt == IntrinsicXlationTable::W2X) {
      x->whirl_info.Dump(os); os << " ";
      x->xaif_info.Dump(os);  os << "\n";
    } 
    else if (tt == IntrinsicXlationTable::X2W) {
      x->xaif_info.Dump(os);  os << " ";
      x->whirl_info.Dump(os); os << "\n";
    } 
    else {
      FORTTK_DIE("Internal IntrinsicXlationTable error: Unknown TableType: " 
		 << tt);
    }
  }

private:
  std::ostream& os;
  IntrinsicXlationTable::TableType tt;
};

//****************************************************************************

IntrinsicXlationTable::IntrinsicXlationTable(TableType tt) 
  : tableType(tt), sortedTable(SortedTable(tableSz))
{
  // Initialize 'sortedTable'
  for (unsigned int i = 0; i < tableSz; ++i) {
    Entry* e = &table[i];
    sortedTable[i] = e;
  }

  // Sort 'sortedTable' (ascending)
  std::sort(sortedTable.begin(), sortedTable.end(), lt_SortedTable(tableType));
}

IntrinsicXlationTable::~IntrinsicXlationTable() 
{ 
}

IntrinsicXlationTable::XAIFInfo*
IntrinsicXlationTable::FindXAIFInfo(OPERATOR opr, const char* name)
{
  if (tableType != W2X) { return NULL; }

  static Entry toFind;
  toFind.whirl_info.oprcl = WNOprClass_UNKNOWN;
  toFind.whirl_info.opr = opr;
  toFind.whirl_info.name = name;
  
  lt_SortedTable lt(tableType);
  SortedTableIt it = std::lower_bound(sortedTable.begin(), sortedTable.end(),
				      toFind, lt);
  if (it != sortedTable.end() && !lt(*it, toFind) && !lt(toFind, *it)) {
    Entry* foundItem = *it; // should only be one match
    return &(foundItem->xaif_info);
  } else {
    return NULL;
  }
}

IntrinsicXlationTable::WHIRLInfo* 
IntrinsicXlationTable::FindWHIRLInfo(XAIFOpr opr, const char* name, 
				     const char* key)
{
  if (tableType != X2W) { return NULL; }
  
  static Entry toFind;  
  toFind.xaif_info.opr = opr;
  toFind.xaif_info.name = name;
  toFind.xaif_info.key = (key && key[0] == '\0') ? NULL : key;
  bool ignoreKey = (toFind.xaif_info.key == NULL);
  
  lt_SortedTable lt(tableType, ignoreKey);
  SortedTableIt it = std::lower_bound(sortedTable.begin(), sortedTable.end(), 
				      toFind, lt);
  if (it != sortedTable.end() && !lt(*it, toFind) && !lt(toFind, *it)) {
    Entry* foundItem = *it; // may be multiple matches if key is NULL
    return &(foundItem->whirl_info);
  } else {
    return NULL;
  }
}

void 
IntrinsicXlationTable::Dump(std::ostream& os) const
{
  os << "Begin Intrinsic Table\n";
  std::for_each(sortedTable.begin(), sortedTable.end(), 
		PrintEntry(os, tableType));
  os << "End Intrinsic Table\n";
}

void 
IntrinsicXlationTable::DDump() const
{
  Dump(std::cerr);
}

//****************************************************************************

bool
LookupIntrinsicPrefix(const char* str);

const char* 
INTRINSIC_basename(INTRINSIC intrn)
{
  const char* opc_str = WN_intrinsic_name(intrn); // INTRINSIC_name(intrn);
  const char* opc_str_base = opc_str;
#define PREFIX_LN 2
  
  // Test for two-character prefixes (up to two)
  char buf[PREFIX_LN+1];
  for (int i = 0; i < 2; ++i) {
    // If a prefix begins 'opc_str_base', shift pointer
    strncpy(buf, opc_str_base, PREFIX_LN); buf[PREFIX_LN] = '\0';
    bool pfix = LookupIntrinsicPrefix(buf);
    if (pfix) { 
      opc_str_base += PREFIX_LN; 
    } else {
      break; // no need to continue
    }
  }
  
  // Special case: test for one-character prefix
  strncpy(buf, opc_str_base, 1); buf[1] = '\0';
  bool pfix = LookupIntrinsicPrefix(buf);
  if (pfix) {
    // an exception
    if ( !(strcmp(opc_str_base, "VALTMP") == 0) ) {
      opc_str_base++;
    }
  }
    
  return opc_str_base;
#undef PREFIX_LN
}


#define TABLE_ELEM_SZ sizeof(const char*)
#define TABLE_SZ      (sizeof(prefixTable) / TABLE_ELEM_SZ)

static const char* prefixTable[] = {
  
  "V",                    // void
  "I1", "I2", "I4", "I8", // integer
  "U1", "U2", "U4", "U8", // unsigned integer
  "F4", "F8", "FQ",       // floating point
  "C4", "C8", "CQ"        // comples
  
  // "C_" - C intrinsics
  // "S_" - UPC intrinsics
}; 

static bool prefixTableSorted = false;
static unsigned int prefixTableElemSz = TABLE_ELEM_SZ;
static unsigned int prefixTableSz = TABLE_SZ;

#undef TABLE_ELEM_SZ
#undef TABLE_SZ


extern "C" typedef int (*compare_fn_t)(const void *, const void *);

extern "C" int prefixTableCmp(const char** e1, const char** e2)
{
  return strcmp(*e1, *e2);
}

// Return true if 'str' is a valid prefix for an intrinsic name; false
// otherwise.
bool
LookupIntrinsicPrefix(const char* str)
{
  // Sort on demand
  if (!prefixTableSorted) {
    qsort(prefixTable, prefixTableSz, prefixTableElemSz, 
	  (compare_fn_t)prefixTableCmp);
    prefixTableSorted = true;
  }
  
  // Search for entry
  void* e = bsearch(&str, prefixTable, prefixTableSz, prefixTableElemSz,
		    (compare_fn_t)prefixTableCmp);
  return (e != NULL);
}

//****************************************************************************
