// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2wn.cxx,v 1.1 2004/12/20 15:17:43 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2wn.cxx,v $
//
// Purpose:
//   Translate S-expression WHIRL AST nodes to WHIRL AST nodes.
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

#include <stdlib.h>

//*************************** Sexp Include Files ****************************

#include <sexp.h>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "sexp2wn.i"
#include "sexp2wn.h"

//************************** Forward Declarations ***************************

using namespace sexp2whirl;


//***************************************************************************
// Translate any WN
//***************************************************************************

// TranslateWN: see header. 
WN* 
sexp2whirl::TranslateWN(sexp_t* sx)
{   
  // The task of translation is dispatched to the appropriate handler
  // registered in the handler table.
  static WNXlationTable handlerTable;
  
  if (!sx) { 
    return NULL; 
  }
  
  OPERATOR opr = GetWNOperator(sx);
  FORTTK_DEVMSG(3, "Translating " << OPERATOR_name(opr));
  
  // Dispatch to the appropriate handler for this construct.
  return handlerTable[opr](sx);
}


// TranslateWNChildren: see header.
WN* 
sexp2whirl::TranslateWNChildren(sexp_t* sx)
{   
  FORTTK_ASSERT(sx, FORTTK_UNEXPECTED_INPUT); 

#if 0  
  INT nkids = WN_kid_count(wn);
  for (INT kidno = 0; kidno < nkids; ++kidno) {
    WN* kidwn = WN_kid(wn, kidno);
    TranslateWN(sos, kidwn);
    if (kidno < nkids - 1) {
      sos << EndLine; // do not output after last call
    }
  }
#endif
  
  return NULL;
}


//***************************************************************************
// S-expressions sexp::ostream operators
//***************************************************************************

#if 0

// Cf. GenSexpSym
sexp::ostream&
operator<<(std::ostream& os, const GenSexpSymInfo_& x)
{
  sexp::ostream& sos = dynamic_cast<sexp::ostream&>(os);

  ST_IDX st_idx = x.val;
  UINT lvl = (UINT)ST_IDX_level(st_idx);
  UINT idx = (UINT)ST_IDX_index(st_idx);

  sos << BegList << Atom("st") << Atom(lvl) << Atom(idx) << EndList;
  
  return sos;
}


// Cf. GenSexpTy
sexp::ostream&
operator<<(std::ostream& os, const GenSexpTyInfo_& x)
{
  sexp::ostream& sos = dynamic_cast<sexp::ostream&>(os);

  TY_IDX ty_idx = x.val;
  const char* nm = TY_name(ty_idx);
  
  using namespace sexp::IOFlags;
  sos << BegList << Atom("ty") << Atom(A_DQUOTE, nm) << Atom(ty_idx) 
      << EndList;
  
  return sos;
}
#endif



// GetWNOperator
OPERATOR
sexp2whirl::GetWNOperator(sexp_t* sx)
{
  return OPR_FUNC_ENTRY; // FIXME
}


// GetWNOpcode
OPCODE
sexp2whirl::GetWNOpcode(sexp_t* sx)
{
  return OPC_FUNC_ENTRY; // FIXME
}


#if 0
// Cf. GenSexpSymRef
sexp::ostream&
operator<<(std::ostream& os, const GenSexpSymRefInfo_& x)
{
  sexp::ostream& sos = dynamic_cast<sexp::ostream&>(os);

  ST_IDX st_idx = x.val;
  ST* st = (st_idx != 0) ? &St_Table[st_idx] : NULL;

  const char* nm = NULL;
  UINT lvl = 0;
  UINT idx = 0;
  if (st) {
    nm = ST_name(st);
    lvl = (UINT)ST_level(st);
    idx = (UINT)ST_index(st);
  } 
  
  using namespace sexp::IOFlags;
  sos << BegList << Atom("st") << Atom(A_DQUOTE, nm) << Atom(lvl) << Atom(idx)
      << EndList;
  
  return sos;
}


// Cf. GenSexpTyUse
sexp::ostream&
operator<<(std::ostream& os, const GenSexpTyUseInfo_& x)
{
  sexp::ostream& sos = dynamic_cast<sexp::ostream&>(os);

  TY_IDX ty_idx = x.val;
  TY* ty = (ty_idx != 0) ? &Ty_Table[ty_idx] : NULL;
  
  const char* nm = NULL;
  UINT idx = 0;
  UINT algn = 0;
  if (ty) {
    nm = TY_name(ty_idx);
    idx = TY_id(ty_idx);
    algn = TY_align(ty_idx);
  } 
  
  using namespace sexp::IOFlags;
  sos << BegList 
      << Atom("ty") << Atom(A_DQUOTE, nm) << Atom(idx) << Atom(algn)
      << EndList;
  
  return sos;
}


// Cf. GenBeginFlgList
#endif

//***************************************************************************
// Structured Control Flow Statements: translation of these is
//   superceded by construction of the control flow graph.
//***************************************************************************

WN*
sexp2whirl::xlate_FUNC_ENTRY(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_BLOCK(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_REGION(sexp_t* sx)
{
  FORTTK_DIE(FORTTK_UNIMPLEMENTED);
  return NULL;
}


WN* 
sexp2whirl::xlate_structured_cf(sexp_t* sx)
{
  return NULL;
}


//***************************************************************************
// Unstructured Control Flow Statements
//***************************************************************************

WN*
sexp2whirl::xlate_IMPLIED_DO(sexp_t* sx)
{
  FORTTK_DIE(FORTTK_UNIMPLEMENTED);
  return NULL;
}


WN* 
sexp2whirl::xlate_GOTOx_LABEL(sexp_t* sx)
{  
  return NULL;
}


WN*
sexp2whirl::xlate_multiBR(sexp_t* sx)
{
  return NULL;
}


WN*
sexp2whirl::xlate_CASEGOTO(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_AGOTO(sexp_t* sx)
{
  FORTTK_DIE(FORTTK_UNIMPLEMENTED);
  return NULL;
}


WN*
sexp2whirl::xlate_ALTENTRY(sexp_t* sx)
{
  FORTTK_DIE(FORTTK_UNIMPLEMENTED);  
  return NULL;
}


WN* 
sexp2whirl::xlate_condBR(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_RETURNx(sexp_t* sx)
{
  return NULL;
}


//***************************************************************************
// Calls
//***************************************************************************

WN* 
sexp2whirl::xlate_xCALL(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_IO(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_IO_ITEM(sexp_t* sx)
{
  return NULL;
}


//***************************************************************************
// Other Statements
//***************************************************************************

WN*
sexp2whirl::xlate_misc_stmt(sexp_t* sx)
{
  return NULL;
}


WN*
sexp2whirl::xlate_xPRAGMA(sexp_t* sx)
{
  return NULL;
}


//***************************************************************************
// Loads (In WHIRL, loads are expressions.)
// Stores (In WHIRL, stores are statements.)
//***************************************************************************

WN* 
sexp2whirl::xlate_LDA_LDMA(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_LDID_STID(sexp_t* sx)
{
  return NULL;
} 


WN* 
sexp2whirl::xlate_IDNAME(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_xLOADx_xSTOREx(sexp_t* sx)
{
  return NULL;
}


WN*
sexp2whirl::xlate_PSTID(sexp_t* sx)
{
  FORTTK_DIE(FORTTK_UNIMPLEMENTED);
  return NULL;
}


WN*
sexp2whirl::xlate_PSTORE(sexp_t* sx)
{
  FORTTK_DIE(FORTTK_UNIMPLEMENTED);
  return NULL;
}


//***************************************************************************
// Array Operators (N-ary Operations)
//***************************************************************************

WN*
sexp2whirl::xlate_ARRAYx(sexp_t* sx)
{
  return NULL;
}


//***************************************************************************
// Type Conversion
//***************************************************************************

WN* 
sexp2whirl::xlate_CVT_CVTL(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_TAS(sexp_t* sx)
{
  return NULL;
}


//***************************************************************************
// Leaf (Other)
//***************************************************************************

WN* 
sexp2whirl::xlate_INTCONST(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_CONST(sexp_t* sx)
{  
  return NULL;
}


//***************************************************************************
// Expression Operators: Unary Operations
//***************************************************************************

WN*
sexp2whirl::xlate_UnaryOp(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_PARM(sexp_t* sx)
{
  return NULL;
}


WN* 
sexp2whirl::xlate_ALLOCA(sexp_t* sx)
{
  FORTTK_DIE(FORTTK_UNIMPLEMENTED);
  return NULL;
}


//***************************************************************************
// Expression Operators: Binary Operations
//***************************************************************************

WN*
sexp2whirl::xlate_BinaryOp(sexp_t* sx)
{
  return NULL;
}


//***************************************************************************
// Expression Operators: Ternary Operations; N-ary Operations
//***************************************************************************

WN*
sexp2whirl::xlate_TernaryOp(sexp_t* sx)
{
  return NULL;
}


//***************************************************************************
// WNXlationTable
//***************************************************************************

WN*
sexp2whirl::xlate_unknown(sexp_t* sx)
{
  // Warn about opcodes we cannot translate, but keep translating.
  OPERATOR opr = GetWNOperator(sx);
  
  FORTTK_DEVMSG(0, FORTTK_UNEXPECTED_OPR << OPERATOR_name(opr));
  return NULL;
}


#define TABLE_SZ (OPERATOR_LAST + 1)
#define INIT_TABLE_SZ \
  (sizeof(WNXlationTable::initTable) / sizeof(WNXlationTable::InitEntry))


bool WNXlationTable::initialized = false;

WNXlationTable::Handler WNXlationTable::table[TABLE_SZ];
unsigned int WNXlationTable::tableSz = TABLE_SZ;

WNXlationTable::InitEntry WNXlationTable::initTable[] = {
  
  // Note: Organization generally corresponds to that in
  // Open64/documentation/whirl.tex
  
  // Structured control flow
  { OPR_FUNC_ENTRY,           &xlate_FUNC_ENTRY },
  { OPR_BLOCK,                &xlate_BLOCK },
  { OPR_REGION,               &xlate_REGION },
  { OPR_DO_LOOP,              &xlate_structured_cf },
  { OPR_DO_WHILE,             &xlate_structured_cf },
  { OPR_WHILE_DO,             &xlate_structured_cf },
  { OPR_IF,                   &xlate_structured_cf },
  
  // Other control flow
  { OPR_IMPLIED_DO,           &xlate_IMPLIED_DO },
  { OPR_GOTO,                 &xlate_GOTOx_LABEL },
  { OPR_GOTO_OUTER_BLOCK,     &xlate_GOTOx_LABEL },
  { OPR_SWITCH,               &xlate_multiBR },
  { OPR_CASEGOTO,             &xlate_CASEGOTO },
  { OPR_COMPGOTO,             &xlate_multiBR },
  { OPR_AGOTO,                &xlate_AGOTO },
  { OPR_REGION_EXIT,          &xlate_GOTOx_LABEL },
  { OPR_ALTENTRY,             &xlate_ALTENTRY },
  { OPR_TRUEBR,               &xlate_condBR },
  { OPR_FALSEBR,              &xlate_condBR },
  { OPR_RETURN,               &xlate_RETURNx },
  { OPR_RETURN_VAL,           &xlate_RETURNx },
  { OPR_LABEL,                &xlate_GOTOx_LABEL },

  // Statements: Calls
  { OPR_CALL,                 &xlate_xCALL },
  { OPR_ICALL,                &xlate_xCALL },
  { OPR_VFCALL,               &xlate_xCALL },
  { OPR_PICCALL,              &xlate_xCALL },
  { OPR_INTRINSIC_CALL,       &xlate_xCALL },
  { OPR_IO,                   &xlate_IO },

  // Statements: Other
  { OPR_EVAL,                 &xlate_misc_stmt },
  { OPR_PRAGMA,               &xlate_xPRAGMA },
  { OPR_XPRAGMA,              &xlate_xPRAGMA },
  { OPR_PREFETCH,             &xlate_misc_stmt },
  { OPR_PREFETCHX,            &xlate_misc_stmt },
  { OPR_COMMENT,              &xlate_misc_stmt },
  { OPR_TRAP,                 &xlate_misc_stmt },
  { OPR_ASSERT,               &xlate_misc_stmt },
  { OPR_AFFIRM,               &xlate_misc_stmt },
  { OPR_FORWARD_BARRIER,      &xlate_misc_stmt },
  { OPR_BACKWARD_BARRIER,     &xlate_misc_stmt },
  { OPR_DEALLOCA,             &xlate_misc_stmt },

  { OPR_USE,                  &xlate_misc_stmt },
  { OPR_NAMELIST,             &xlate_misc_stmt },
  { OPR_IMPLICIT_BND,         &xlate_misc_stmt },  
  { OPR_NULLIFY,              &xlate_misc_stmt },
  { OPR_INTERFACE,            &xlate_misc_stmt },
  { OPR_ARRAY_CONSTRUCT,      &xlate_misc_stmt },
  
  // Memory Access (or assignment and variable references)
  { OPR_LDA,                  &xlate_LDA_LDMA },  // Leaf
  { OPR_LDMA,                 &xlate_LDA_LDMA },  // Leaf
  { OPR_IDNAME,               &xlate_IDNAME },    // Leaf; like a mem-ref
  { OPR_LDID,                 &xlate_LDID_STID },
  { OPR_STID,                 &xlate_LDID_STID },
  { OPR_ILOAD,                &xlate_xLOADx_xSTOREx },
  { OPR_ILOADX,               &xlate_xLOADx_xSTOREx },
  { OPR_MLOAD,                &xlate_xLOADx_xSTOREx },

  { OPR_ISTORE,               &xlate_xLOADx_xSTOREx },
  { OPR_ISTOREX,              &xlate_xLOADx_xSTOREx },
  { OPR_MSTORE,               &xlate_xLOADx_xSTOREx },

  { OPR_PSTID,                &xlate_PSTID },   // Pseudo-registers 
  { OPR_PSTORE,               &xlate_PSTORE },

  // Type conversion
  { OPR_CVT,                  &xlate_CVT_CVTL },
  { OPR_CVTL,                 &xlate_CVT_CVTL },
  { OPR_TAS,                  &xlate_TAS },
  
  // Expressions: Unary operations
  { OPR_INTCONST,             &xlate_INTCONST }, // Leaf
  { OPR_CONST,                &xlate_CONST },    // Leaf

  { OPR_NEG,                  &xlate_UnaryOp },
  { OPR_ABS,                  &xlate_UnaryOp },
  { OPR_SQRT,                 &xlate_UnaryOp },
  { OPR_RSQRT,                &xlate_UnaryOp },
  { OPR_RECIP,                &xlate_UnaryOp },
  { OPR_REALPART,             &xlate_UnaryOp }, // OPR_FIRSTPART
  { OPR_IMAGPART,             &xlate_UnaryOp }, // OPR_SECONDPART
  { OPR_PAREN,                &xlate_UnaryOp },
  { OPR_RND,                  &xlate_UnaryOp },
  { OPR_TRUNC,                &xlate_UnaryOp },
  { OPR_CEIL,                 &xlate_UnaryOp },
  { OPR_FLOOR,                &xlate_UnaryOp },
  { OPR_BNOT,                 &xlate_UnaryOp },
  { OPR_LNOT,                 &xlate_UnaryOp },
  // FIXME: LOWPART, HIGHPART, MINPART, MAXPART, ILDA, EXTRACT_BITS
  { OPR_PARM,                 &xlate_PARM },
  // FIXME: ASM_INPUT
  { OPR_ALLOCA,               &xlate_ALLOCA },

  // Expressions: Binary operations
  { OPR_COMPLEX,              &xlate_BinaryOp }, // OPR_PAIR
  { OPR_ADD,                  &xlate_BinaryOp },
  { OPR_SUB,                  &xlate_BinaryOp },
  { OPR_MPY,                  &xlate_BinaryOp },
  // FIXME: HIGHMPY, XMPY
  { OPR_DIV,                  &xlate_BinaryOp },
  { OPR_MOD,                  &xlate_BinaryOp },
  { OPR_REM,                  &xlate_BinaryOp },
  // FIXME: DIVREM
  { OPR_MAX,                  &xlate_BinaryOp },
  { OPR_MIN,                  &xlate_BinaryOp },
  // FIXME: MINMAX
  { OPR_EQ,                   &xlate_BinaryOp },
  { OPR_NE,                   &xlate_BinaryOp },
  { OPR_GE,                   &xlate_BinaryOp },
  { OPR_GT,                   &xlate_BinaryOp },
  { OPR_LE,                   &xlate_BinaryOp },
  { OPR_LT,                   &xlate_BinaryOp },
  { OPR_BAND,                 &xlate_BinaryOp },
  { OPR_BIOR,                 &xlate_BinaryOp },
  { OPR_BNOR,                 &xlate_BinaryOp },
  { OPR_BXOR,                 &xlate_BinaryOp },
  { OPR_LAND,                 &xlate_BinaryOp },
  { OPR_LIOR,                 &xlate_BinaryOp },
  { OPR_CAND,                 &xlate_BinaryOp },
  { OPR_CIOR,                 &xlate_BinaryOp },
  { OPR_SHL,                  &xlate_BinaryOp },
  { OPR_ASHR,                 &xlate_BinaryOp },
  { OPR_LSHR,                 &xlate_BinaryOp },
  // FIXME: COMPOSE_BITS, RROTATE, COMMA, RCOMMA
  
  // Expressions: Ternary operations
  { OPR_SELECT,               &xlate_TernaryOp },
  // FIXME: CSELECT
  { OPR_MADD,                 &xlate_TernaryOp },
  { OPR_MSUB,                 &xlate_TernaryOp },
  { OPR_NMADD,                &xlate_TernaryOp },
  { OPR_NMSUB,                &xlate_TernaryOp },

  // Expressions: N-ary operations
  { OPR_ARRAY,                &xlate_ARRAYx },
  { OPR_INTRINSIC_OP,         &xlate_xCALL },
  { OPR_IO_ITEM,              &xlate_IO_ITEM },
  { OPR_TRIPLET,              &xlate_TernaryOp },
  { OPR_SRCTRIPLET,           &xlate_TernaryOp },
  { OPR_ARRAYEXP,             &xlate_ARRAYx },
  { OPR_ARRSECTION,           &xlate_ARRAYx },
  { OPR_WHERE,                &xlate_TernaryOp },
  
  
  { OPERATOR_UNKNOWN,         &xlate_unknown } // just for convenience
};

unsigned int WNXlationTable::initTableSz = INIT_TABLE_SZ;

#undef TABLE_SZ
#undef INIT_TABLE_SZ


WNXlationTable::WNXlationTable()
{
  // Initialize table with default handler
  for (int i = 0; i < tableSz; ++i) {
    table[i] = &xlate_unknown;
  }
  
  // Initialize the table using 'initTable'
  for (int i = 0; i < initTableSz; ++i) {
    table[initTable[i].opr] = initTable[i].fn;
  }
  
  initialized = true; // could use to this initialize on demand
}

WNXlationTable::~WNXlationTable()
{
}

