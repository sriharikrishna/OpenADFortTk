// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/IntrinsicXlationTable.cxx,v 1.5 2004/04/07 14:58:32 eraxxon Exp $

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
  // Intrinsics
  // -------------------------------------------------------

  // Common mathematical functions
  { { WNExpr, OPR_NEG, NULL, 1 },
                        { XAIFIntrin, "minus_scal", 1 } },
  { { WNExpr, OPR_ADD, NULL, 2 },
                        { XAIFIntrin, "add_scal_scal", 2 } },
  { { WNExpr, OPR_SUB, NULL, 2 },
                        { XAIFIntrin, "sub_scal_scal", 2 } },
  { { WNExpr, OPR_MPY, NULL, 2 },
                        { XAIFIntrin, "mul_scal_scal", 2 } },
  { { WNExpr, OPR_DIV, NULL, 2 },
                        { XAIFIntrin, "div_scal_scal", 2 } },
  { { WNCall, OPR_CALL, "SQRT", 1 },
                        { XAIFIntrin, "sqrt_scal", 1 } },
#if 0
  { { WNExpr, OPR_SQRT, NULL, 1 },
                        { XAIFIntrin, "sqrt_scal", 1 } },
#endif

  { { WNExpr, OPR_MOD, NULL, 2 },
                        { XAIFIntrin, "bogus_mod_scal_scal", 2 } },
  { { WNExpr, OPR_REM, NULL, 2 },
                        { XAIFIntrin, "bogus_rem_scal_scal", 2 } },

  { { WNCall, OPR_CALL, "SIN", 1 },
                        { XAIFIntrin, "sin_scal", 1 } },
  { { WNCall, OPR_CALL, "COS", 1 },
                        { XAIFIntrin, "cos_scal", 1 } },
  { { WNCall, OPR_CALL, "EXP", 1 },
                        { XAIFIntrin, "exp_scal", 1 } },
  { { WNCall, OPR_CALL, "LOG", 1 },
                        { XAIFIntrin, "ln_scal", 1 } },

  // Intrinsics: The WHIRL string is the INTRINSIC_basename()
  // (cf. wintrinsic.h, wutil.cxx)
  { { WNIntrinOp, OPR_INTRINSIC_OP, "EXPEXPR", 2 }, 
                        { XAIFIntrin, "pow_scal_scal", 2 } },

  { { WNIntrinOp, OPR_INTRINSIC_OP, "CEQEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_eq_scal_scal", 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "CNEEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_ne_scal_scal", 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "CGEEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_ge_scal_scal", 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "CGTEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_gt_scal_scal", 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "CLEEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_le_scal_scal", 2 } },
  { { WNIntrinOp, OPR_INTRINSIC_OP, "CLTEXPR", 2 }, 
                        { XAIFIntrin, "bogus_string_lt_scal_scal", 2 } },
  
  // Rounding, conversion
  { { WNExpr, OPR_ABS, NULL, 1 },
                        { XAIFIntrin, "bogus_abs_scal", 1 } },
  { { WNExpr, OPR_RND, NULL, 1 },
                        { XAIFIntrin, "bogus_round_scal", 1 } },
  { { WNExpr, OPR_TRUNC, NULL, 1 },
                        { XAIFIntrin, "bogus_trunc_scal", 1 } },
  { { WNExpr, OPR_CEIL, NULL, 1 },
                        { XAIFIntrin, "bogus_ceil_scal", 1 } },
  { { WNExpr, OPR_FLOOR, NULL, 1 },
                        { XAIFIntrin, "bogus_floor_scal", 1 } },

  // Logical operations
  { { WNExpr, OPR_BNOT, NULL, 1 },
                        { XAIFIntrin, "bogus_not_scal", 1 } },
  { { WNExpr, OPR_BAND, NULL, 2 },
                        { XAIFIntrin, "bogus_and_scal_scal", 2 } },
  { { WNExpr, OPR_BIOR, NULL, 2 },
                        { XAIFIntrin, "bogus_or_scal_scal", 2 } },
  { { WNExpr, OPR_BXOR, NULL, 2 },
                        { XAIFIntrin, "bogus_xor_scal_scal", 2 } },
  { { WNExpr, OPR_EQ, NULL, 2 },
                        { XAIFBoolOp, "equal", 2 } },
  { { WNExpr, OPR_NE, NULL, 2 },
                        { XAIFBoolOp, "not_equal", 2 } },
  { { WNExpr, OPR_GT, NULL, 2 },
                        { XAIFBoolOp, "greater_than", 2 } },
  { { WNExpr, OPR_GE, NULL, 2 },
                        { XAIFBoolOp, "greater_or_equal", 2 } },
  { { WNExpr, OPR_LT, NULL, 2 },
                        { XAIFBoolOp, "less_than", 2 } },
  { { WNExpr, OPR_LE, NULL, 2 },
                        { XAIFBoolOp, "less_or_equal", 2 } },

  { { WNExpr, OPR_LAND, NULL, 2 },
                        { XAIFIntrin, "bogus_land_scal_scal", 2 } },
  { { WNExpr, OPR_LIOR, NULL, 2 },
                        { XAIFIntrin, "bogus_lor_scal_scal", 2 } },
  { { WNExpr, OPR_CAND, NULL, 2 },
                        { XAIFIntrin, "bogus_cand_scal_scal", 2 } },
  { { WNExpr, OPR_CIOR, NULL, 2 },
                        { XAIFIntrin, "bogus_cor_scal_scal", 2 } },

  // Misc.
  { { WNExpr, OPR_SHL, NULL, 2 },
                        { XAIFIntrin, "bogus_shl_scal_scal", 2 } },
  { { WNExpr, OPR_ASHR, NULL, 2 },
                        { XAIFIntrin, "bogus_ashr_scal_scal", 2 } },

  { { WNExpr, OPR_MAX, NULL, 2 },
                        { XAIFIntrin, "bogus_max_scal_scal", 2 } },
  { { WNExpr, OPR_MIN, NULL, 2 },
                        { XAIFIntrin, "bogus_min_scal_scal", 2 } }
  
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
     << ((name) ? name : "<null>") 
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
	ASSERT_FATAL(false, (DIAG_A_STRING, "Invalid comparison"));
      }

    } else {
      return (e1->whirl_info.opr < e2->whirl_info.opr);
    }
    
  } else if (tt == X2W) {
    
    // 1. xaif_info.opr is the primary sorting key
    if (e1->xaif_info.opr == e2->xaif_info.opr) {
      
      // 2. xaif_info.name is the secondary sorting key
      return (strcmp(e1->xaif_info.name, e2->xaif_info.name) < 0);
      
    } else {
      return (e1->xaif_info.opr < e2->xaif_info.opr);
    }
    
  } else {
    ASSERT_FATAL(false, (DIAG_A_STRING, "Error!"));
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
    } else if (tt == IntrinsicXlationTable::X2W) {
      x->xaif_info.Dump(os);  os << " ";
      x->whirl_info.Dump(os); os << "\n";
    } else {
      ASSERT_FATAL(false, (DIAG_A_STRING, "Error!"));
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

  bool found = std::binary_search(sortedTable.begin(), sortedTable.end(),
				  toFind, lt_SortedTable(tableType));
  if (found) {
    SortedTableIt it = std::lower_bound(sortedTable.begin(), sortedTable.end(),
					toFind, lt_SortedTable(tableType));
    Entry* foundItem = *it;
    return &(foundItem->xaif_info);
  } else {
    return NULL;
  }
}

IntrinsicXlationTable::WHIRLInfo* 
IntrinsicXlationTable::FindWHIRLInfo(XAIFOpr opr, const char* name)
{
  if (tableType != X2W) { return NULL; }
  
  static Entry toFind;
  
  toFind.xaif_info.opr = opr;
  toFind.xaif_info.name = name;
  
  bool found = std::binary_search(sortedTable.begin(), sortedTable.end(),
				  toFind, lt_SortedTable(tableType));
  if (found) {
    SortedTableIt it = std::lower_bound(sortedTable.begin(), sortedTable.end(),
					toFind, lt_SortedTable(tableType));
    Entry* foundItem = *it;
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
