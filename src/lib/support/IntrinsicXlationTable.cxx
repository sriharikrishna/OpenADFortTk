// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/IntrinsicXlationTable.cxx,v 1.1 2003/11/13 14:54:26 eraxxon Exp $

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

#include <algorithm>

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

#include "IntrinsicXlationTable.h"
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
   sizeof(IntrinsicXlationTable::table) / sizeof(IntrinsicXlationTable::Entry)


IntrinsicXlationTable::Entry IntrinsicXlationTable::table[] = {

  // -------------------------------------------------------
  // WHIRL calls and intrinsics that correspond to XAIF Intrinsics
  // -------------------------------------------------------

  // Common mathematical functions
  { { OPR_NEG, NULL, 1 },   { Intrinsic, "minus_scal", 1 } },
  { { OPR_ADD, NULL, 2 },   { Intrinsic, "add_scal_scal", 2 } },
  { { OPR_SUB, NULL, 2 },   { Intrinsic, "sub_scal_scal", 2 } },
  { { OPR_MPY, NULL, 2 },   { Intrinsic, "mul_scal_scal", 2 } },
  { { OPR_DIV, NULL, 2 },   { Intrinsic, "div_scal_scal", 2 } },
  { { OPR_SQRT, NULL, 1 },  { Intrinsic, "sqrt_scal", 1 } },

  { { OPR_MOD, NULL, 2 },   { Intrinsic, "bogus_mod_scal_scal", 2 } },
  { { OPR_REM, NULL, 2 },   { Intrinsic, "bogus_rem_scal_scal", 2 } },

  { { OPR_CALL, "SIN", 1 }, { Intrinsic, "sin_scal", 1 } },
  { { OPR_CALL, "COS", 1 }, { Intrinsic, "cos_scal", 1 } },
  { { OPR_CALL, "EXP", 1 }, { Intrinsic, "exp_scal", 1 } },
  { { OPR_CALL, "LOG", 1 }, { Intrinsic, "ln_scal", 1 } },

  { { OPR_INTRINSIC_OP, "EXPEXPR", 1 }, { Intrinsic, "pow_scal_scal", 1 } },
  // FIXME: INTRN_I4EXPEXPR (wintrinsic.h)
  
  // Rounding, conversion
  { { OPR_ABS, NULL, 1 },   { Intrinsic, "bogus_abs_scal", 1 } },
  { { OPR_RND, NULL, 1 },   { Intrinsic, "bogus_round_scal", 1 } },
  { { OPR_TRUNC, NULL, 1 }, { Intrinsic, "bogus_trunc_scal", 1 } },
  { { OPR_CEIL, NULL, 1 },  { Intrinsic, "bogus_ceil_scal", 1 } },
  { { OPR_FLOOR, NULL, 1 }, { Intrinsic, "bogus_floor_scal", 1 } },

  // Logical operations
  { { OPR_BNOT, NULL, 1 },  { Intrinsic, "bogus_not_scal", 1 } },
  { { OPR_BAND, NULL, 2 },  { Intrinsic, "bogus_and_scal_scal", 2 } },
  { { OPR_BIOR, NULL, 2 },  { Intrinsic, "bogus_or_scal_scal", 2 } },
  { { OPR_BXOR, NULL, 2 },  { Intrinsic, "bogus_xor_scal_scal", 2 } },
  { { OPR_EQ, NULL, 2 },    { Intrinsic, "bogus_eq_scal_scal", 2 } },
  { { OPR_NE, NULL, 2 },    { Intrinsic, "bogus_neq_scal_scal", 2 } },
  { { OPR_GT, NULL, 2 },    { Intrinsic, "bogus_gt_scal_scal", 2 } },
  { { OPR_GE, NULL, 2 },    { Intrinsic, "bogus_gteq_scal_scal", 2 } },
  { { OPR_LT, NULL, 2 },    { Intrinsic, "bogus_lt_scal_scal", 2 } },
  { { OPR_LE, NULL, 2 },    { Intrinsic, "bogus_lteq_scal_scal", 2 } },

  { { OPR_LAND, NULL, 2 },  { Intrinsic, "bogus_land_scal_scal", 2 } },
  { { OPR_LIOR, NULL, 2 },  { Intrinsic, "bogus_lor_scal_scal", 2 } },
  { { OPR_CAND, NULL, 2 },  { Intrinsic, "bogus_cand_scal_scal", 2 } },
  { { OPR_CIOR, NULL, 2 },  { Intrinsic, "bogus_cor_scal_scal", 2 } },

  // Misc.
  { { OPR_SHL, NULL, 2 },   { Intrinsic, "bogus_shl_scal_scal", 2 } },
  { { OPR_ASHR, NULL, 2 },  { Intrinsic, "bogus_ashr_scal_scal", 2 } },

  { { OPR_MAX, NULL, 2 },   { Intrinsic, "bogus_max_scal_scal", 2 } },
  { { OPR_MIN, NULL, 2 },   { Intrinsic, "bogus_min_scal_scal", 2 } }
  
};

unsigned int IntrinsicXlationTable::tableSz = TABLE_SZ;

#undef TABLE_SZ

//****************************************************************************

const char* 
IntrinsicXlationTable::XAIFOpr2Str(XAIFOpr opr)
{
  switch (opr) {
    case SubCall:   return "SubCall";
    case FuncCall:  return "FuncCall";
    case Intrinsic: return "Intrinsic";
    default:   return "<invalid-XAIFOpr>";
  }
  return NULL; // should never reach
}

void
IntrinsicXlationTable::WHIRLInfo::Dump(std::ostream& os) const
{
  os << "{ " 
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
     << XAIFOpr2Str(opr) << ", " 
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
    
    if (e1->whirl_info.opr == e2->whirl_info.opr) {
      
      if (e1->whirl_info.name && e2->whirl_info.name) {
	return (strcmp(e1->whirl_info.name, e2->whirl_info.name) < 0); 
      } else if (!e1->whirl_info.name && !e2->whirl_info.name) {
	return false; // equality
      } else {
	ASSERT_FATAL(false, (DIAG_A_STRING, "Invalid comparison"));
      }

    } else {
      return (e1->whirl_info.opr < e2->whirl_info.opr);
    }
    
  } else if (tt == X2W) {
    
    if (e1->xaif_info.opr == e2->xaif_info.opr) {
      
      if (e1->xaif_info.name && e2->xaif_info.name) {
	return (strcmp(e1->xaif_info.name, e2->xaif_info.name) < 0);
      } else if (!e1->xaif_info.name && !e2->xaif_info.name) {
	return false; // equality
      } else {
	ASSERT_FATAL(false, (DIAG_A_STRING, "Invalid comparison"));
      }
      
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

