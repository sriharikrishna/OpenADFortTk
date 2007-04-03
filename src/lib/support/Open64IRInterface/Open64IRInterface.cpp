// -*-Mode: C++;-*-
// $Header$

/*! \file
  
  \brief Implementation of abstract OA interfaces for Open64/WHIRL

  \authors Nathan Tallent, Michelle Strout
  \version $Id$

  Copyright ((c)) 2002, Rice University 
  All rights reserved.
  See ../../../Rice.copyright for details.

*/

static bool debug = false;

//************************** System Include Files ***************************

#include <list>
#include <climits>
#include <cassert>
//using std::list;

//************************ OpenAnalysis Include Files ***********************

//************************** Open64 Include Files ***************************

#include "Open64BasicTypes.h"
#include "ir_reader.h" // for fdump_wn()

//*************************** User Include Files ****************************

#include "Open64IRInterface.hpp"
#include "SymTab.h"
#include "wn_attr.h"
#include "stab_attr.h"
#include "IntrinsicInfo.cpp"

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// Static Class Members
//***************************************************************************
std::map<OA::IRHandle,OA::ProcHandle> Open64IRInterface::sProcContext;
PU_Info* Open64IRInterface::sProgContext = NULL;
//PU_Info* Open64IRInterface::sCurrentProc = NULL;
bool Open64IRInterface::sContextInit = false;

std::map<OA::StmtHandle,std::set<OA::MemRefHandle> > 
    Open64IRInterface::sStmt2allMemRefsMap;

std::map<OA::MemRefHandle,OA::StmtHandle> Open64IRInterface::sMemRef2StmtMap;

std::map<OA::MemRefHandle,set<OA::OA_ptr<OA::MemRefExpr> > > 
    Open64IRInterface::sMemref2mreSetMap;

std::map<OA::SymHandle,OA::ProcHandle> Open64IRInterface::sCallSymToProc;

std::map<fully_qualified_name,
         std::set<OA::SymHandle> > Open64IRInterface::sGlobalVarMap;

std::map<fully_qualified_name,std::map<OA::ProcHandle,OA::SymHandle> >
      Open64IRInterface::sFQNToProcToLocalSymMap;

std::map<OA::SymHandle,fully_qualified_name> Open64IRInterface::sSymToFQNMap;

std::map<OA::SymHandle,std::string> Open64IRInterface::sSymToVarStringMap;

std::map<OA::ExprHandle,OA::CallHandle> Open64IRInterface::sParamToCallMap;

std::map<OA::ProcHandle,std::set<OA::SymHandle> > 
    Open64IRInterface::sProcToSymRefSetMap;

//***************************************************************************
// Iterators
//***************************************************************************

//---------------------------------------------------------------------------
// Open64IRProcIterator
//---------------------------------------------------------------------------

Open64IRProcIterator::Open64IRProcIterator(PU_Info* pu_forest)
{
  if (pu_forest) {
    // Builds in a DFS order
    for (PU_Info *pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
      build_pu_list(pu);
    }
  }
  
  reset();
}

Open64IRProcIterator::~Open64IRProcIterator()
{
}

void
Open64IRProcIterator::operator++()
{
  // Advance current PU
  ++pulist_iter;
  prepare_current_pu();
}

void
Open64IRProcIterator::reset()
{
  // Reset
  pulist_iter = pulist.begin();
  prepare_current_pu();
}

void 
Open64IRProcIterator::prepare_current_pu()
{
  if (isValid()) {
    PU_Info *pu = (*pulist_iter);
    PU_SetGlobalState(pu);
  }
}

void 
Open64IRProcIterator::build_pu_list(PU_Info* pu)
{
  pulist.push_back(pu);
  
  // Now recursively process the child PU's.
  for (PU_Info *child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    build_pu_list(child);
  }
}


//---------------------------------------------------------------------------
// Open64IRStmtIterator
//---------------------------------------------------------------------------
Open64IRStmtIterator::Open64IRStmtIterator(OA::ProcHandle h)
{
  create(h);
  reset();
  mValid = true;
}

Open64IRStmtIterator::~Open64IRStmtIterator()
{
}
     
OA::StmtHandle 
Open64IRStmtIterator::current() const
{
  if (mValid) { 
    return (*mStmtIter); 
  } else { 
    return OA::StmtHandle(0); 
  }
}

void 
Open64IRStmtIterator::operator++()
{
  if (mValid) {
    mStmtIter++;
  }
}

void 
Open64IRStmtIterator::reset()
{
  mStmtIter = mStmtList.begin();
  mEnd = mStmtList.end();
  mBegin = mStmtList.begin();
}

void 
Open64IRStmtIterator::create(OA::ProcHandle h)
{
  // NOTE: for now we just create a new list.  we could save some
  // memory and use the WHIRL pre-order iterator directly.
  PU_Info* pu = (PU_Info*)h.hval();
  if (!pu) { return; }
  
  PU_SetGlobalState(pu);
  
  WN* wn_pu = PU_Info_tree_ptr(pu);
  
  WN_TREE_CONTAINER<PRE_ORDER> wtree(wn_pu);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  for (it = wtree.begin(); it != wtree.end(); /* */) {
    WN* curWN = it.Wn();
    OPERATOR opr = WN_operator(curWN);
    
    // Decide whether to record 'wn' as a statement
    bool isCF = 
      (!(opr == OPR_FUNC_ENTRY || opr == OPR_BLOCK || opr == OPR_REGION)
       && OPERATOR_is_scf(opr) || OPERATOR_is_non_scf(opr));
    if (OPERATOR_is_stmt(opr) || isCF) {
      //std::cerr << "iterating: " << OPERATOR_name(opr) << std::endl;
      mStmtList.push_back(OA::StmtHandle((OA::irhandle_t)curWN));
    }

    // Decide how to advance iteration.  For non-compound non-control-
    // flow statements, we want to advance to curWN's siblings instead
    // of examining its child expressions. This is both more efficient and
    // prevents incorrectly classifying embedded CALLs as statements!
    bool isPlainStmt = OPERATOR_is_stmt(opr)
      && !(OPERATOR_is_scf(opr) || OPERATOR_is_non_scf(opr));
    if (isPlainStmt) {
      it.WN_TREE_next_skip();
    } else {
      ++it;
    }
  }
}


//---------------------------------------------------------------------------
// Open64IRCallsiteIterator
//---------------------------------------------------------------------------
Open64IRCallsiteIterator::Open64IRCallsiteIterator(WN *wn)
{
  if (wn && !OPERATOR_is_not_executable(WN_operator(wn))) {
    build_func_call_list(wn);
  }
  
  reset();
}

Open64IRCallsiteIterator::~Open64IRCallsiteIterator()
{
}

void 
Open64IRCallsiteIterator::build_func_call_list(WN *wn)
{
  if (!wn) { return; }
  
  OPERATOR opr = WN_operator(wn);

  // Add calls to call list but filter out calls to intrinsics
  if (OPERATOR_is_call(opr) && !(IntrinsicInfo::isIntrinsic(wn)) ) {
    wnlist.push_back(wn);
  }
  
  // Recur on subexpressions
  for (INT kidno = 0; kidno < WN_kid_count(wn); kidno++) {
    WN* kid = WN_kid(wn, kidno);
    build_func_call_list(kid);
  }
}

//---------------------------------------------------------------------------
// Callsite Parameter Iterator
//---------------------------------------------------------------------------
Open64IRCallsiteParamIterator::Open64IRCallsiteParamIterator(WN *wn)
{
  OPERATOR opr = WN_operator(wn);
  assert(OPERATOR_is_call(opr));

  // FIXME: should we test for a return value at the front?
  
  // Note: each kid is an OPR_PARM
  mINT16 numactuals = WN_num_actuals(wn);
  INT first_arg_idx = 0;

  // Gather all parameter expressions
  for (INT kidno = first_arg_idx; kidno < numactuals; kidno++) {
    WN* kid = WN_kid(wn, kidno);
    wnlist.push_back(kid);
  }
  
  reset();
}

//---------------------------------------------------------------------------
// Memory Reference Iterator
//---------------------------------------------------------------------------
Open64IRMemRefIterator::Open64IRMemRefIterator(OA::StmtHandle h)
{
  create(h);
  reset();
  mValid = true;
}
        
OA::MemRefHandle 
Open64IRMemRefIterator::current() const
{
  if (mValid) { 
    return (*mMemRefIter); 
  } else { 
    return OA::MemRefHandle(0); 
  }
}

void 
Open64IRMemRefIterator::operator++()
{
  if (mValid) {
    mMemRefIter++;
  }
}

void 
Open64IRMemRefIterator::reset()
{
  mMemRefIter = mMemRefList.begin();
  mEnd = mMemRefList.end();
  mBegin = mMemRefList.begin();
}

/*! this method sets up sMemRef2StmtMap, sStmt2MemRefSet, and 
    sMemRef2mreSetMap
    Is only way to get MemRefHandle's therefore no queries should
    be logically made on MemRefHandle's before one of these
    iterators has been requested.
*/
void 
Open64IRMemRefIterator::create(OA::StmtHandle stmt)
{
  // loop through MemRefHandle's for this statement and for now put them
  // into our own list
  std::set<OA::MemRefHandle>::iterator setIter;
  for (setIter=Open64IRInterface::sStmt2allMemRefsMap[stmt].begin(); 
       setIter!=Open64IRInterface::sStmt2allMemRefsMap[stmt].end(); setIter++) 
  {
    mMemRefList.push_back(*setIter);
  }
}


//---------------------------------------------------------------------------
// Open64IRSymIterator
//---------------------------------------------------------------------------
class insert_ST {
public:
  insert_ST(std::list<ST*>& symlist_)
    : symlist(symlist_)
  { } 
  
  // A function object applied to every entry of a ST_TAB
  void operator()(UINT32 idx, ST* st) const 
  { 
    symlist.push_back(st);
  }
  
private:
  std::list<ST*>& symlist;
};


Open64IRSymIterator::Open64IRSymIterator(PU_Info* pu)
{
  create(pu);
  reset();
}


void
Open64IRSymIterator::create(PU_Info* pu)
{
  if (!pu) { return; }
  
  PU_SetGlobalState(pu);
  
  // The global symbol table contains symbols that may not have been
  // lexically visible in the original source code.  For example,
  // given two procedures, one uses a common block and the other
  // doesn't, but the common block symbols are placed in the global
  // symbol table even though the second procedure never lexically saw
  // them.  (The same is true for modules.)  Thus, we are careful to
  // only insert globabl symbosl *referenced* in the AST.

  // 1. Iterate through the non-global lexical symbol tables.  These
  // tables should truly correspond to lexically visible symbols.
  for (SYMTAB_IDX lvl = CURRENT_SYMTAB; lvl > GLOBAL_SYMTAB; --lvl) {
    // Scope_tab[lvl].st_tab;
    For_all(St_Table, lvl, insert_ST(symlist));
  }
  
  // 2. Enter global symbols referenced in the AST
  WN *wn_pu = PU_Info_tree_ptr(pu);

  WN_TREE_CONTAINER<PRE_ORDER> wtree(wn_pu);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  for (it = wtree.begin(); it != wtree.end(); ++it) {
    WN* curWN = it.Wn();
    
    // If the node has a global symbol, push it in the list
    OPERATOR opr = WN_operator(curWN);
    if (OPERATOR_has_sym(opr)) {
      ST* st = WN_st(curWN);
      if (ST_level(st) == GLOBAL_SYMTAB) {
        symlist.push_back(st);
      }
    }
  }

}

//---------------------------------------------------------------------------
// Open64PtrAssignPairStmtIterator
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Open64ParamBindPtrAssignIterator
//---------------------------------------------------------------------------

//***************************************************************************
// Abstract Interfaces
//***************************************************************************

Open64IRInterface::Open64IRInterface()
{
}


Open64IRInterface::~Open64IRInterface()
{
}

//---------------------------------------------------------------------------
// IRHandlesIRInterface
//---------------------------------------------------------------------------

std::string 
Open64IRInterface::toString(const OA::ProcHandle h)
{ 
  PU_Info* pu = (PU_Info*)h.hval();
  
  std::ostringstream oss;
  //oss << pu;
  if (h==OA::ProcHandle(0)) {
    oss << "ProcHandle(0)";
  } else {
    oss << toString(getSymHandle(h));
  }
  return oss.str();
}

std::string 
Open64IRInterface::toString(const OA::StmtHandle h)
{ 
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  
  std::ostringstream oss;
  if (wn==0) {
    oss << "StmtHandle(0)";
  } else {
    DumpWN(wn, oss);
  }
  return oss.str();
}

std::string 
Open64IRInterface::toString(const OA::ExprHandle h) 
{
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();

  std::ostringstream oss;
  if (wn==0) {
    oss << "ExprHandle(0)";
  } else {
    DumpWN(wn, oss);
  }
  return oss.str();
}

std::string 
Open64IRInterface::toString(const OA::OpHandle h) 
{
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();

  std::ostringstream oss;
  if (wn==0) {
    oss << "OpHandle(0)";
  } else {
    //    DumpWN(wn, oss);
    //oss << OPCODE_name(WN_opcode(wn));
    
    OPERATOR opr = WN_operator(wn);
    string op;
    switch (opr) {
      // Unary expression operations.
    case OPR_CVT:
    case OPR_CVTL:
    case OPR_TAS:
      oss << OPCODE_name(WN_opcode(wn)) << "(";
      //    DumpWN(WN_kid0(wn), os);
      oss << ")";
      break;
    case OPR_PARM:
      if (WN_flag(wn) & WN_PARM_BY_REFERENCE)
        oss << "&"; 
      //DumpWN(WN_kid0(wn), os);
      break;
    case OPR_ABS:
      oss << "ABS(";
      //DumpWN(WN_kid0(wn), os);
      oss << ")";
      break;
    case OPR_SQRT:
      oss << "SQRT(";
      //DumpWN(WN_kid0(wn), os);
      oss << ")";
      break;
    case OPR_RSQRT:
      oss << "RSQRT(";
      //DumpWN(WN_kid0(wn), os);
      oss << ")";
      break;
    case OPR_RECIP:
      oss << "RECIP(";
      //DumpWN(WN_kid0(wn), os);
      oss << ")";
      break;
    case OPR_PAREN:
      oss << "(";
      //DumpWN(WN_kid0(wn), os);
      oss << ")";
      break;
    case OPR_RND:
      oss << "RND(";
      //DumpWN(WN_kid0(wn), os);
      oss << ")";
      break;
    case OPR_TRUNC:
      oss << "TRUNC(";
      //DumpWN(WN_kid0(wn), os);
      oss << ")";
      break;
    case OPR_CEIL:
      oss << "CEIL(";
      //DumpWN(WN_kid0(wn), os);
      oss << ")";
      break;
    case OPR_FLOOR:
      oss << "FLOOR(";
      //DumpWN(WN_kid0(wn), os);
      oss << ")";
      break;
    case OPR_NEG:
      op = "-";
      goto print_generic_unary;
    case OPR_BNOT:
      op = "~";
      goto print_generic_unary;
    case OPR_LNOT:
      op = "!";
      goto print_generic_unary;
    print_generic_unary:
      oss << op;
      //DumpWN(WN_kid0(wn), os);
      break;

      // Binary expression operations.
    case OPR_ADD:
      op = "+";
      goto print_generic_binary;
    case OPR_SUB:
      op = "-";
      goto print_generic_binary;
    case OPR_MPY:
      op = "*";
      goto print_generic_binary;
    case OPR_DIV:
      op = "/";
      goto print_generic_binary;
    case OPR_MOD:
      oss << "MOD(";
      //DumpWN(WN_kid0(wn), os);
      //oss << ",";
      //DumpWN(WN_kid1(wn), os);
      oss << ")";
      break;
    case OPR_REM:
      op = "%";
      goto print_generic_binary;
    case OPR_EQ:
      op = "==";
      goto print_generic_binary;
    case OPR_NE:
      op = "!=";
      goto print_generic_binary;
    case OPR_GE:
      op = ">=";
      goto print_generic_binary;
    case OPR_LE:
      op = "<=";
      goto print_generic_binary;
    case OPR_GT:
      op = '>';
      goto print_generic_binary;
    case OPR_LT:
      op = '<';
      goto print_generic_binary;
    case OPR_MAX:
      oss << "MAX(";
      //DumpWN(WN_kid0(wn), os);
      //oss << ",";
      //DumpWN(WN_kid1(wn), os);
      oss << ")";
      break;
    case OPR_MIN:
      oss << "MIN(";
      //DumpWN(WN_kid0(wn), os);
      oss << ",";
      //DumpWN(WN_kid1(wn), os);
      oss << ")";
      break;
    case OPR_SHL:
      op = "<<";
      goto print_generic_binary;
    case OPR_ASHR:
    case OPR_LSHR:
      op = ">>";
      goto print_generic_binary;
    case OPR_LAND:
      op = "&&";
      goto print_generic_binary;
    case OPR_LIOR:
      op = "||";
      goto print_generic_binary;
    case OPR_BAND:
      op = "&";
      goto print_generic_binary;
    case OPR_BIOR:
      op = "|";
      goto print_generic_binary;
    case OPR_BXOR:
      op = "^";
    print_generic_binary:
      //DumpWN(WN_kid0(wn), os);
      oss << op;
      //DumpWN(WN_kid1(wn), os);
      break;
      
      // Ternary operations.
    case OPR_SELECT:
      //DumpWN(WN_kid0(wn), os);
      oss << " ? "; 
      //DumpWN(WN_kid1(wn), os);
      oss << " : "; 
      //DumpWN(WN_kid2(wn), os);
      break;
    case OPR_MADD:
      oss << "(";
      //DumpWN(WN_kid0(wn), os);
      oss << "*";
      //DumpWN(WN_kid1(wn), os);
      oss << ")+";
      //DumpWN(WN_kid2(wn), os);
      break;
    case OPR_MSUB:
      oss << "(";
      //DumpWN(WN_kid0(wn), os);
      oss << "*";
      //DumpWN(WN_kid1(wn), os);
      oss << ")-";
      //DumpWN(WN_kid2(wn), os);
      break;
    case OPR_NMADD:
      oss << "-((";
      //DumpWN(WN_kid0(wn), os);
      oss << "*";
      //DumpWN(WN_kid1(wn), os);
      oss << ")+";
      //DumpWN(WN_kid2(wn), os);
      oss << ")";
      break;
    case OPR_NMSUB:
      oss << "-((";
      //DumpWN(WN_kid0(wn), os);
      oss << "*";
      //DumpWN(WN_kid1(wn), os);
      oss << ")-";
      //DumpWN(WN_kid2(wn), os);
      oss << ")";
      break;
      
      /* Don't know about these ...  
    // N-ary operations.
    case OPR_ARRAY: {
      int ndims = WN_kid_count(wn) >> 1;
      DumpWN(WN_kid0(wn), os);
      os << "(";
      for (int i = 0; i < ndims; i++) {
        DumpWN(WN_kid(wn, i+ndims+1), os);
        if (i < ndims-1) 
          os << ",";
      }
      os << ")";
      break;
    }
    case OPR_TRIPLET: // Output as LB:UB:STRIDE
      DumpWN(WN_kid0(wn), os);
      os << ":";
      DumpWN(WN_kid2(wn), os);
      os << ":";
      DumpWN(WN_kid1(wn), os);
      break; 
    case OPR_ARRAYEXP:
      DumpWN(WN_kid0(wn), os);
      break; 
    case OPR_ARRSECTION: {
      int ndims = WN_kid_count(wn) >> 1;
      DumpWN(WN_kid0(wn), os);
      os << "(";
      for (int i = 0; i < ndims; i++) {
        DumpWN(WN_kid(wn, i+ndims+1), os);
        if (i < ndims-1) 
          os << ",";
      }
      os << ")";
      break;
    }
      * Don't know about the above ...
      */

    default:
      DumpWN(wn, oss);
      break;
    }
  }
  return oss.str();
}

std::string 
Open64IRInterface::toString(const OA::MemRefHandle h)
{
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  std::ostringstream oss;
  DumpWNMemRef(wn, oss);
  return oss.str();
}

std::string 
Open64IRInterface::toString(const OA::SymHandle h) 
{
  ST* st = (ST*)h.hval();
  std::string symnm; 
  if (st) {
    setCurrentProcToProcContext(h);
    symnm = createCharStarForST(st);
    PU_Info* origPU = Current_PU_Info;
    if(origPU != NULL) {
     ST_IDX idx = PU_Info_proc_sym(origPU);
     std::string procname = ST_name(idx);
     symnm = procname + "::" + symnm;
    }

  } else {
    symnm = "<no-symbol>";
  }
  return symnm;
}

std::string 
Open64IRInterface::toString(const OA::ConstSymHandle h) 
{
  setCurrentProcToProcContext(h);
  std::ostringstream oss;
  //  oss << h.hval();

  WN* wn = (WN*)h.hval();
  if (wn==0) {
    oss << "ConstSymHandle(0)";
  } else {
    DumpWN(wn, oss);
  }

  return oss.str();
}

std::string 
Open64IRInterface::toString(const OA::ConstValHandle h) 
{
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();

  std::ostringstream oss;
  //oss << h.hval();

  if (wn==0) {
    oss << "ConstValHandle(0)";
  } else {
    DumpWN(wn, oss);
  }
  
  return oss.str();
}

std::string 
Open64IRInterface::toString(const OA::CallHandle h) 
{
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();

  std::ostringstream oss;
  if (wn==0) {
    oss << "CallHandle(0)";
  } else {
    DumpWN(wn, oss);
  }
  return oss.str();
}


void 
Open64IRInterface::dump(OA::StmtHandle stmt, std::ostream& os)
{ 
  setCurrentProcToProcContext(stmt);
  WN* wn = (WN*)stmt.hval();
  if (wn==0) {
    os << "StmtHandle(0)";
  } else {
    DumpWN(wn, os);
  }
  os << std::endl;
}

void 
Open64IRInterface::dump(OA::MemRefHandle h, std::ostream& os)
{
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();

  os << "hval = " << h.hval() << ", ";
  
  OPERATOR opr = WN_operator(wn);
  // STOREs represent the left-hand-side memory-ref
  if (OPERATOR_is_store(opr)) {
    if (WN_kid_count(wn) > 1) {
      DumpWN(WN_kid1(wn), os); // left-hand-side (FIXME: add offset!)
    } else {
      std::string n = toString(OA::SymHandle((OA::irhandle_t)WN_st(wn)));
      os << n;
    } 
  } else {
    DumpWN(wn, os);
  }
  os << std::endl;
}


//---------------------------------------------------------------------------
// CallGraphIRInterface
//---------------------------------------------------------------------------

OA::OA_ptr<OA::IRStmtIterator> 
Open64IRInterface::getStmtIterator(OA::ProcHandle h)
{
  OA::OA_ptr<OA::IRStmtIterator> retval;
  retval = new Open64IRStmtIterator(h);
  return retval;
}

OA::SymHandle 
Open64IRInterface::getProcSymHandle(OA::ProcHandle h) 
{
  PU_Info* pu = (PU_Info*)h.hval(); 
  ST* st = NULL;
  if (pu) {
    PU_Info* origPU = Current_PU_Info;
    if (pu != Current_PU_Info) { 
      PU_SetGlobalState(pu); 
    }
    
    st = ST_ptr(PU_Info_proc_sym(pu)); // WN_st(PU_Info_tree_ptr(pu));
    
    if (Current_PU_Info != origPU) { 
      PU_SetGlobalState(origPU); 
    }
  }
  return (OA::irhandle_t)st;
}

OA::OA_ptr<OA::IRCallsiteIterator>
Open64IRInterface::getCallsites(OA::StmtHandle h)
{
  setCurrentProcToProcContext(h);
  WN* wn = (WN *)h.hval();
  OA::OA_ptr<OA::IRCallsiteIterator> retval;
  retval =  new Open64IRCallsiteIterator(wn);
  return retval;
}

//---------------------------------------------------------------------------
// CallGraphDFProblemIRInterface
//---------------------------------------------------------------------------
// !Get IRCallsiteParamIterator for a callsite. 
OA::OA_ptr<OA::IRCallsiteParamIterator> 
Open64IRInterface::getCallsiteParams(OA::CallHandle h) {
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  OA::OA_ptr<OA::IRCallsiteParamIterator> retval;
  retval = new Open64IRCallsiteParamIterator(wn);
  return retval;
}

bool Open64IRInterface::isRefParam(OA::SymHandle sym)
{
  // "X"  inout: C_VAR S_FORMAL_REF (flg 0x80 0x0)
  // "Y"  inout: C_VAR S_FORMAL_REF (flg 0x80 0x0)
  // "AA" in   : C_VAR S_FORMAL_REF (flg 0x80 0x20[in])
  // "BB" out  : C_VAR S_FORMAL_REF (flg 0x80 0x40[out])

  // save off the current context and then switch to one for this sym
  OA::ProcHandle currContext = getCurrentProcContext();
  setCurrentProcToProcContext(sym);

  ST* st = (ST*)sym.hval();
  ST_SCLASS sclass = ST_sclass(st);
  bool retval;
  
  if (ST_is_intent_out_argument(st)) {
    retval = true; // parameter: intent(out)
  }
  else if (ST_is_intent_in_argument(st)) {
    retval = true; // parameter: intent(in)
    //return true; // when modeling reference params with ptrs, on 1/9/06
                 // Jean came up with example where need to model intent(in)
                 // as pass by reference, MMS
                 // yeah but I can't find this example!!
  }
  else if (sclass == SCLASS_FORMAL_REF) {
    retval = true; // pass-by-ref parameter
  }
  else if (sclass == SCLASS_FORMAL) {
    // FIXME: this is going to be wrong for C, but flags aren't set to
    // indicate fortran correctly and when pass arrays by ref for some
    // reason the formal isn't set to SCLASS_FORMAL_REF in Whirl
    retval = true; // may be pass-by-ref in the source language
  }
  else {
    retval = false; // not a parameter at all
  }

  // reset the context
  setCurrentProcContext(currContext);
  return retval;
}
               
//! return the formal parameter that an actual parameter is associated with.
OA::SymHandle 
Open64IRInterface::getFormalForActual(OA::ProcHandle caller, 
                                      OA::CallHandle call, 
                                      OA::ProcHandle callee, 
                                      OA::ExprHandle param) {
  // Setup context for caller
  setCurrentProcToProcContext(call);

  PU_Info* callerPU = (PU_Info*)caller.hval();
  PU_Info* calleePU = (PU_Info*)callee.hval();
  WN* callWN = (WN*)call.hval();
  WN* parmWN = (WN*)param.hval();



  //debugging ...
  //{ std::cout << "getFormalForActual:  caller='"
  //            << toString(caller) << "' called='"
  //            << toString(callee)<< std::endl;
  //}

  assert(callerPU && calleePU);
  ST* formalST = NULL; // sym for corresponding formal parameter
  
  // Find the index of the actual parameter within the call node
  int numParamsCaller = WN_kid_count(callWN);
  int parmIdx = -1;
  for (int kidno = 0; kidno < numParamsCaller; ++kidno) {
    WN* kid = WN_kid(callWN, kidno);
    if (kid == parmWN) {
      parmIdx = kidno;
      break;
    }
  }

  if(parmIdx >= 0) {
  // Given the index of the actual parameter, find the formal parameter
  PU_SetGlobalState(calleePU);
  
  WN* wn_pu = PU_Info_tree_ptr(calleePU);
 
  /*! PLM Important node regarding Optional Parameters:
      Reference :http://www.sesp.cse.clrc.ac.uk/Publications/felib90_design/design/node6.html 

      Occasionally, not all arguments are required every time a 
      procedure is used. Therefore some arguments may be specified 
      as optional, using the OPTIONAL attribute:
   
      SUBROUTINE sub1(a, b, c, d) 
         INTEGER, INTENT(INOUT):: a, b 
         REAL, INTENT(IN), OPTIONAL :: c, d 
           ... 
      END SUBROUTINE sub1 

      Here a and b are always required when calling sub1. 
      The arguments c and d are optional and so sub1 may be
      referenced by:

      CALL sub1( a, b ) 
      CALL sub1( a, b, c, d ) 
      CALL sub1( a, b, c ) 

      Note that the order in which arguments appear is important
      (unless keyword arguments are used) so that it is not possible
      to call sub1 with argument d but no argument c.

      CALL sub1( a, b, d )   ! illegal 

      Optional arguments must come after all arguments associated 
      by position in a referencing statement and require an explicit
      interface.
  */

  assert(parmIdx <= WN_num_formals(wn_pu));

  /*! PLM : Places where explicit formal to actual matching needed.

    * For functions excluding following cases:
        1. PURE INTEGER FUNCTION
        2. ELEMENTAL REAL
        3. RECURSIVE FUNCTIONS WITH RESULT 
           (mentioned explicitely in the prototype) 
            WHERE RESULT IS SCALAR VARIABLE
        4. RECURSIVE FUNCTIONS WITHOUT RESULT
           (mentioned explicitely in the prototype)

      Return type is one of the member of formal Parameter list.
      It appears as the first argument in the formal Parameter list.
      We need to match actual to formal starting from ParmIdx=1.
   
    * In case of Subroutine, we do not have Return-Type and therefore,
      We need to match actual to formal starting from ParmIdx=0. 

    The algorithm is as Follows:
    - In the list of formal argument of callee proc, 
         - Get the ST entry for the first argument.
         - If the ST entry of the first argument is of "Return" type. 
              start mapping from argument(1) in the parameter list
         - else 
              start mapping from argument(0) in the parameter list.
   */

  WN* maybeReturnVar = WN_formal(wn_pu, 0);
  ST* returnVarST    = WN_st(maybeReturnVar);
  bool isReturnVar = ST_is_return_var (*returnVarST) ;

  WN  *formalWN=0;
  if(isReturnVar == true) {
     formalWN = WN_formal(wn_pu, parmIdx+1);
  } else {
     formalWN = WN_formal(wn_pu, parmIdx);
  }

  formalST = WN_st(formalWN);
  assert(formalST);

  /*! PLM more details:
      in case of Indirect Function Calls
      (e.g.  using function pointers),  function pointer is also one of
      the member of parameter list.
  */
  }
 
  // Reset context for caller
  PU_SetGlobalState(callerPU);
  
  return (OA::irhandle_t)formalST;
}

//---------------------------------------------------------------------------
// CFGIRInterfaceDefault
//---------------------------------------------------------------------------

OA::OA_ptr<OA::IRRegionStmtIterator>
Open64IRInterface::procBody(OA::ProcHandle h)
{
  PU_Info* pu = (PU_Info*)h.hval();
  currentProc(h);
  WN* wn_pu = PU_Info_tree_ptr(pu);
  //WN* wn_pu = (WN*)h.hval();
  assert(WN_operator(wn_pu) == OPR_FUNC_ENTRY);
  
  WN* wn = WN_func_body(wn_pu);
  OA::OA_ptr<Open64IRRegionStmtIterator> retval;
  retval = new Open64IRRegionStmtIterator(wn);
  return retval;
}

//----------------------------------------------------------
// Statements: General
//----------------------------------------------------------

// Translate a whirl statement type into a IRStmtType.
OA::CFG::IRStmtType
Open64IRInterface::getCFGStmtType(OA::StmtHandle h) 
{
  //setCurrentProcToProcContext(h); // not setting up context for hierarchical stmts
  OA::CFG::IRStmtType ty;
  WN *wn = (WN *)h.hval();
  OPERATOR opr = WN_operator(wn);

  //
  // There are currently three IRStmtTypes that are not returned by this
  // function-- BREAK, LOOP_CONTINUE and STRUCT_MULTIWAY_CONDITIONAL.
  // That is, Whirl does not appear to have a structured switch statement or
  // high-level forms of break or loop continue.
  //

  switch (opr) {

  // Return statements.
  case OPR_RETURN:
  case OPR_RETURN_VAL:
    ty = OA::CFG::RETURN;
    break;

  // Top-tested loops.
  case OPR_DO_LOOP:
  case OPR_WHILE_DO:
    ty = OA::CFG::LOOP;
    break;

  // End-tested loop.
  case OPR_DO_WHILE:
    ty = OA::CFG::END_TESTED_LOOP;
    break;

  // Structured IF-statement.
  case OPR_IF:
    ty = OA::CFG::STRUCT_TWOWAY_CONDITIONAL;
    break;

  // Unconditional jump.
  case OPR_GOTO:
    ty = OA::CFG::UNCONDITIONAL_JUMP;
    break;

  // Unconditional jump (indirect).
  case OPR_AGOTO:
    ty = OA::CFG::UNCONDITIONAL_JUMP_I;
    break;

  // Unstructured two-way branches.
  case OPR_TRUEBR:
    ty = OA::CFG::USTRUCT_TWOWAY_CONDITIONAL_T;
    break;

  case OPR_FALSEBR:
    ty = OA::CFG::USTRUCT_TWOWAY_CONDITIONAL_F;
    break;

  // Unstructured multi-way branch.
  case OPR_COMPGOTO:  // FIXME: Also, OPR_XGOTO?
  case OPR_SWITCH:
    ty = OA::CFG::USTRUCT_MULTIWAY_CONDITIONAL;
    break;

  // Alternate entry point.
  case OPR_ALTENTRY:
    ty = OA::CFG::ALTERNATE_PROC_ENTRY;
    break;

  // A block of statements.
    //case OPR_FUNC_ENTRY: // FIXME
  case OPR_BLOCK:
    ty = OA::CFG::COMPOUND;
    break;

  // Simple statements.   // FIXME: Is this all of them?
  case OPR_CALL:
  case OPR_ICALL:
  case OPR_PICCALL:
  case OPR_VFCALL:
  case OPR_INTRINSIC_CALL:
  case OPR_PRAGMA:
  case OPR_XPRAGMA:
  case OPR_ASM_STMT:
  case OPR_EVAL:
  case OPR_PREFETCH:
  case OPR_PREFETCHX:
  case OPR_COMMENT:
  case OPR_AFFIRM:
  case OPR_FORWARD_BARRIER:	// FIXME: ???
  case OPR_BACKWARD_BARRIER:	// FIXME: ???
  case OPR_LABEL:
  case OPR_WHERE:
  case OPR_IO:			// FIXME: Internal control flow possible?
  case OPR_LDID:
  case OPR_STID:
  case OPR_ILOAD:
  case OPR_ISTORE:
  case OPR_ILOADX:
  case OPR_ISTOREX:
  case OPR_MLOAD:
  case OPR_MSTORE:
  case OPR_LDBITS:
  case OPR_STBITS:
  case OPR_ILDBITS:
  case OPR_ISTBITS:
  case OPR_USE: // FIXME: how are these ordered?
  case OPR_INTERFACE: 
  //case OPR_PSTID: FIXME: want this to fail because don't handle pointers yet
    ty = OA::CFG::SIMPLE;
    break;

  // Bother.
  default: 
    // FIXME: OPR_ASSERT, OPR_GOTO_OUTER_BLOCK, OPR_TRAP, 
    //  OPR_REGION, OPR_REGION_EXIT
    fprintf(stderr, "*** Open64IRInterface: Unknown WHIRL operator %s ***.\n", 
	    OPERATOR_name(opr));
    dump_wn(wn);
    assert(0);
    break;
  }
  return ty;
}

OA::StmtLabel
Open64IRInterface::getLabel(OA::StmtHandle h)
{
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();

  if (WN_operator (wn) == OPR_LABEL) {
    return (OA::irhandle_t) WN_label_number (wn);
  } else {
    return 0;
  }
}

OA::OA_ptr<OA::IRRegionStmtIterator>
Open64IRInterface::getFirstInCompound(OA::StmtHandle h)
{
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();
  OA::OA_ptr<OA::IRRegionStmtIterator> retval;
  retval = new Open64IRRegionStmtIterator (WN_first (wn));
  return retval;
}


//----------------------------------------------------------
// Loops
//----------------------------------------------------------

OA::OA_ptr<OA::IRRegionStmtIterator>
Open64IRInterface::loopBody(OA::StmtHandle h)
{
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();
  WN *body_wn = 0;

  switch (WN_operator (wn)) {
  case OPR_DO_LOOP:
    body_wn = WN_do_body (wn);
    break;
  case OPR_WHILE_DO:
  case OPR_DO_WHILE:
    body_wn = WN_while_body (wn);
    break;
  default:
    // FIXME: Any other statement types here?
    assert(0);
    break;
  }

  OA::OA_ptr<OA::IRRegionStmtIterator> retval;
  retval = new Open64IRRegionStmtIterator (body_wn);
  return retval;
}

OA::StmtHandle
Open64IRInterface::loopHeader(OA::StmtHandle h)
{
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();

  // This is called for all top-tested loops, but only OPR_DO_LOOP has
  // an initialization statement.
  if (WN_operator (wn) == OPR_DO_LOOP) {
    return (OA::irhandle_t) WN_start (wn);
  } else if (WN_operator (wn) == OPR_WHILE_DO) {
    return 0;
  } else {
    assert(0);
  }
}

OA::StmtHandle
Open64IRInterface::getLoopIncrement(OA::StmtHandle h)
{
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();

  // This is called for all top-tested loops, but only OPR_DO_LOOP has
  // an initialization statement.
  if (WN_operator (wn) == OPR_DO_LOOP) {
    return (OA::irhandle_t) WN_step (wn);
  } else if (WN_operator (wn) == OPR_WHILE_DO) {
    return 0;
  } else {
    assert(0);
  }
}

bool
Open64IRInterface::loopIterationsDefinedAtEntry(OA::StmtHandle h)
{
  //setCurrentProcToProcContext(h);
  //WN *wn = (WN *) h.hval();

  // In Whirl, only an OPR_DO_LOOP is specified to have Fortran semantics,
  // which means the increment is a loop-invariant expression.  However,
  // Open64 already enforces the restrictions, so we don't have to do
  // anything special here (i.e., always return false).
  return false;
}

OA::ExprHandle
Open64IRInterface::getLoopCondition(OA::StmtHandle h)
{
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();
  WN *expr_wn = 0;

  switch (WN_operator (wn)) {
  case OPR_DO_LOOP:
    expr_wn = WN_end (wn);
    break;
  case OPR_WHILE_DO:
  case OPR_DO_WHILE:
    expr_wn = WN_while_test (wn);
    break;
  default:
    assert(0);
    break;
  }

  return (OA::irhandle_t) expr_wn;
}

//----------------------------------------------------------
// Structured two-way conditionals
//----------------------------------------------------------

OA::OA_ptr<OA::IRRegionStmtIterator>
Open64IRInterface::trueBody(OA::StmtHandle h)
{
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();
  OA::OA_ptr<OA::IRRegionStmtIterator> retval;

  if (WN_operator (wn) == OPR_IF) {
    retval = new Open64IRRegionStmtIterator (WN_then (wn));
    return retval;
  } else {
    assert(0);
  }
}


OA::OA_ptr<OA::IRRegionStmtIterator>
Open64IRInterface::elseBody(OA::StmtHandle h)
{
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();
  OA::OA_ptr<OA::IRRegionStmtIterator> retval;

  if (WN_operator (wn) == OPR_IF) {
    retval = new Open64IRRegionStmtIterator (WN_else (wn));
    return retval;
  } else {
    assert(0);
  }
}


OA::ExprHandle
Open64IRInterface::getCondition(OA::StmtHandle h)
{
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();
  WN *expr_wn = 0;

  if (WN_operator (wn) == OPR_IF) {
    expr_wn = WN_if_test (wn);
  } else if (WN_operator (wn) == OPR_TRUEBR
             || WN_operator (wn) == OPR_FALSEBR) {
    expr_wn = WN_kid0 (wn);
  } else {
    assert(0);
  }
  return (OA::irhandle_t) expr_wn;
}


//----------------------------------------------------------
// Structured multiway conditionals
//----------------------------------------------------------

int
Open64IRInterface::numMultiCases(OA::StmtHandle h)
{
  // Whirl does not have a structured switch statement.
  assert(0);
  return 0;
}

OA::OA_ptr<OA::IRRegionStmtIterator>
Open64IRInterface::multiBody(OA::StmtHandle h, int bodyIndex)
{
  // Whirl does not have a structured switch statement.
  assert(0);
  OA::OA_ptr<OA::IRRegionStmtIterator> retval; retval = NULL;
  return retval;
}

bool
Open64IRInterface::isBreakImplied(OA::StmtHandle multicond)
{
  // Whirl does not have a structured switch statement.
  assert(0);
  return false;
}

bool
Open64IRInterface::isCatchAll(OA::StmtHandle h, int bodyIndex)
{
  // Whirl does not have a structured switch statement.
  assert(0);
  return false;
}

OA::OA_ptr<OA::IRRegionStmtIterator>
Open64IRInterface::getMultiCatchall(OA::StmtHandle h)
{
  // Whirl does not have a structured switch statement.
  assert(0);
  OA::OA_ptr<OA::IRRegionStmtIterator> retval; retval = NULL;
  return retval;
}

OA::ExprHandle
Open64IRInterface::getSMultiCondition(OA::StmtHandle h, int bodyIndex)
{
  // Whirl does not have a structured switch statement.
  assert(0);
  return (OA::irhandle_t) 0;
}

OA::ExprHandle 
Open64IRInterface::getSMultiTest(OA::StmtHandle h)
{
  // Whirl does not have a structured switch statement.
  assert(0);
  return (OA::irhandle_t) 0;
}

#if 0 // deprecated
OA::ExprHandle
Open64IRInterface::getMultiExpr(OA::StmtHandle h)
{
  // Whirl does not have a structured switch statement.
  assert(0);
  return (OA::irhandle_t) 0;
}
#endif

//----------------------------------------------------------
// Unstructured two-way conditionals
//----------------------------------------------------------

OA::StmtLabel
Open64IRInterface::getTargetLabel(OA::StmtHandle h, int n)
{
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();

  if (WN_operator (wn) == OPR_GOTO
      || WN_operator (wn) == OPR_TRUEBR
      || WN_operator (wn) == OPR_FALSEBR) {
    return (OA::irhandle_t) WN_label_number (wn);
  } else {
    assert(0);
  }
}

//----------------------------------------------------------
// Unstructured multi-way conditionals
//----------------------------------------------------------

// Given an unstructured multi-way branch, return the number of targets.
// The count does not include the optional default/catchall target.
int
Open64IRInterface::numUMultiTargets(OA::StmtHandle h)
{ 
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();

  // FIXME: Support also OPR_XGOTO?
  OPERATOR opr = WN_operator(wn);
  if (opr == OPR_COMPGOTO || opr == OPR_SWITCH) {
    return WN_num_entries(wn);
  } else {
    assert(0);
  }
}

// Given an unstructured multi-way branch, return the label of the target
// statement at 'targetIndex'. The n targets are indexed [0..n-1]. 
OA::StmtLabel
Open64IRInterface::getUMultiTargetLabel(OA::StmtHandle h, int targetIndex)
{
  //setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  OA::StmtLabel target_label = 0;
  WN* curr_goto = NULL;

  // Whirl has a number of multiway branches: OPR_SWITCH, OPR_COMPGOTO,
  // and OPR_XGOTO. SWITCH and COMPGOTO are redundant in the sense that
  // SWITCH could be used for any COMPGOTO. Nevertheless, we have to handle
  // them all.
  // FIXME: XGOTO is a lowered form of COMPGOTO which isn't handled here yet. 
  OPERATOR opr = WN_operator(wn);
  assert(opr == OPR_COMPGOTO || opr == OPR_SWITCH);
  if (opr == OPR_COMPGOTO) {
    assert(WN_operator(WN_kid1(wn)) == OPR_BLOCK);
    curr_goto = WN_first(WN_kid1(wn));
  } else {
    assert(WN_operator(WN_switch_table(wn)) == OPR_BLOCK);
    curr_goto = WN_first(WN_switch_table(wn));
  }
  
  // For COMPGOTO, kid 1 is an OPR_BLOCK which contains the dispatch
  // table as a list of OPR_GOTOs to the corresponding targets. SWITCH
  // is similar, except its table is a list of OPR_CASEGOTOs.
  //
  // Below is somewhat inefficient, but the method wants random access to the
  // targets, while Whirl blocks have to be traversed sequentially.
  int curr_idx = 0;
  for ( ; (curr_goto); curr_goto = WN_next(curr_goto), ++curr_idx) {
    if (curr_idx == targetIndex) {
      assert(WN_operator(curr_goto) == OPR_GOTO 
	     || WN_operator(curr_goto) == OPR_CASEGOTO);
      target_label = (OA::StmtLabel) WN_label_number(curr_goto);
      break;
    }
  }
  assert(curr_idx == targetIndex); // Ensure target is found...
  
  return target_label;
}

// Given an unstructured multi-way branch, return the label of the optional
// default/catchall target. Return 0 if no default target.
OA::StmtLabel
Open64IRInterface::getUMultiCatchallLabel (OA::StmtHandle h)
{ 
  //setCurrentProcToProcContext(h);
  WN *wn = (WN *) h.hval();
  WN *target = 0;

  // FIXME: Support also OPR_XGOTO?
  if (WN_operator(wn) == OPR_COMPGOTO) {
    target = WN_kid2(wn);
  } else if (WN_operator(wn) == OPR_SWITCH) {
    target = WN_switch_default(wn);
  } else {
    assert(0);
  }

  if (target) {
    assert(WN_operator(target) == OPR_GOTO);
    return (OA::StmtLabel) WN_label_number(target);
  } else {
    return 0;
  }
}

// Given an unstructured multi-way branch, return the condition expression
// corresponding to target 'targetIndex'. The n targets are indexed [0..n-1].
// For OPR_SWITCH, return an OPR_CASEGOTO; for OPR_COMPGOTO, return OPR_GOTO.
OA::ExprHandle
Open64IRInterface::getUMultiCondition (OA::StmtHandle h, int targetIndex)
{
  //setCurrentProcToProcContext(h);
  // Cf. GetUMultiTargetLabel (no need for assertions here)
  WN* wn = (WN*)h.hval();
  WN* curr_goto = NULL;
  OA::ExprHandle condExpr = 0;

  OPERATOR opr = WN_operator(wn);
  if (opr == OPR_COMPGOTO) {
    curr_goto = WN_first(WN_kid1(wn));
  } else {
    curr_goto = WN_first(WN_switch_table(wn));
  }
  
  int curr_idx = 0;
  for ( ; (curr_goto); curr_goto = WN_next(curr_goto), ++curr_idx) {
    if (curr_idx == targetIndex) {
      condExpr = (OA::irhandle_t)curr_goto; // OPR_CASEGOTO or OPR_GOTO
      break;
    }
  }
  return condExpr;
}

OA::ExprHandle 
Open64IRInterface::getUMultiTest(OA::StmtHandle h) {

  //setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  WN *expr_wn = 0;
    
  if (WN_operator(wn)==OPR_SWITCH) {
    expr_wn = WN_switch_test (wn);
  } else {
    std::cout << "Not a SWITCH in getUMultiTest " << std::endl;
    std::cout.flush();
    //return (OA::irhandle_t) 0; // user will have to check in case not switch
    assert (0);
  }

  return (OA::irhandle_t) expr_wn;

}

//---------------------------------------------------------------------------
// AliasIRInterfaceDefault
//---------------------------------------------------------------------------

OA::OA_ptr<OA::MemRefHandleIterator> 
Open64IRInterface::getMemRefIterator(OA::StmtHandle h) 
{
  setCurrentProcToProcContext(h);
  
  // if haven't already determined the set of memrefs for this stmt
  // initializing the mapping of MemRefHandle's to a set of MemRefExprs,
  // and based off that map get all the MemRefHandle's
  if (sStmt2allMemRefsMap[h].empty() ) {
      
    // first loop through call sites for this statement
    // to create a map of actual parameters (OPR_PARMs WNs)
    // to the call handle
    OA::OA_ptr<OA::IRCallsiteIterator> callIter = getCallsites(h);
    for ( ; callIter->isValid(); (*callIter)++ ) {
        OA::CallHandle call = callIter->current();
        OA::OA_ptr<OA::IRCallsiteParamIterator> paramIter 
            = getCallsiteParams(call);
        for ( ; paramIter->isValid(); (*paramIter)++ ) {
            OA::ExprHandle param = paramIter->current();
            sParamToCallMap[param] = call;
        }
    }
 
    findAllMemRefsAndMapToMemRefExprs(h,(WN*)h.hval(),0);
  }

  OA::OA_ptr<OA::MemRefHandleIterator> retval;
  retval = new Open64IRMemRefIterator(h);
  return retval;
}

// Given WHIRL statements (including control flow
// statements representing embedded expressions, but not statements),
// recursively find the memory-references in the statement and create
// OA::MemRefExprs to model them to OA.  Note: Memory
// references will generally be WHIRL expressions; however STORES --
// WHIRL *statements* -- are returned to represent a left-hand-side
// reference; and indirect CALLS are returned to represent a function
// pointer reference.
// Also map each MemRefHandle to a set of MemRefExprs in sMemRef2mreSetMap
// and map each stmt to all MemRefHandles for that statement 
// in sStmt2allMemRefsMap.
void Open64IRInterface::findAllMemRefsAndMapToMemRefExprs(OA::StmtHandle stmt,
        WN* wn, unsigned lvl)
{

  if (debug) {
      std::cout << "======== findAllMemRefsAndMapToMemRefExprs" << std::endl;
      std::cout << "\tWN =";
      Open64IRInterface::DumpWNMemRef(wn,std::cout);
      std::cout << std::endl;
      std::cout << "\tfdump_tree = " << std::endl;
      fdump_tree(stdout,wn);
      std::cout << std::endl;
  }

  // flags to pass down recursive call stack
  enum { 
    flags_NONE              = 0x00000000,

    flags_HAVE_STORE_PARENT = 0x00000004, 

    flags_MODEL_PASS_BY_REF = 0x00000008,
 
    flags_EXPECT_STRCT_BASE = 0x00000010,

  };


  // If we know the language is F90 or FORTRAN then we can get more
  // precise MemRefExprs
  Language = LANG_F90; // FIXME: Open64's global var Language isn't set
  
  using namespace OA;

  bool isFortran = (Language == LANG_F77 || Language == LANG_F90);

  // Base case
  if (!wn) { return; }
  
  OPERATOR opr = WN_operator(wn);
    
  // -------------------------------------------------------
  // Gather information about this mem-ref
  // -------------------------------------------------------
  TY_IDX base_ty = 0, ref_ty = 0;
  WN_OFFSET offset = 0;
  UINT field_id = 0; 
  if (OPERATOR_is_load(opr) || opr == OPR_LDA || opr == OPR_LDMA) {
      offset = WN_load_offset(wn); // == WN_lda_offset()
  }
  // Set accuracy
  bool fullAccuracy = false;
  // These only work on loads and stores
  // FIXME: asserts in wn_attr.cpp code on MLOADS
  if (opr!=OPR_MLOAD && opr!=OPR_MSTORE && 
      (OPERATOR_is_store(opr) || OPERATOR_is_load(opr) 
      || opr==OPR_LDA || opr==OPR_LDMA)) 
  {
      base_ty = WN_GetBaseObjType(wn);
      ref_ty = WN_GetRefObjType(wn);
      if (OPERATOR_has_field_id(opr)) {
          field_id = WN_field_id(wn);
      }
      if (offset == 0 && field_id == 0) { // we do not have a structure ref
        if (base_ty != 0 && WN2F_Can_Assign_Types(base_ty, ref_ty)) {
          // If assigning to same object, we have full accuracy
          fullAccuracy = true;
        }
      }
  } 

  // Determination of these is the same for most, exceptions dealt with
  // in the big switch stmt
  MemRefExpr::MemRefType hty;
  if (lvl==0 && (OPERATOR_is_store(opr))) {
      
      hty = MemRefExpr::DEF;
  } else {



      hty = MemRefExpr::USE;
  }
  bool isAddrOf = false;
  
  // -------------------------------------------------------
  // Gather information from children and generate MRE(s)
  // -------------------------------------------------------
  WN* subMemRef;
  // Large switch statement based on operator that current node represents
  switch (opr) {
    // NOTE: MLOAD, MSTORE?  FIXME?: we don't handle these, should we?

    case OPR_MPY:
    case OPR_INTRINSIC_OP:
    case OPR_ADD:
    case OPR_SUB:
    case OPR_DIV:
    case OPR_CVT:
    case OPR_LE:
    case OPR_LT:
    case OPR_GE:
    case OPR_EQ:
    case OPR_TRUNC:
    case OPR_LIOR:
    case OPR_RECIP:
    case OPR_PAREN:
    case OPR_NEG:
     {
         for (INT kidno=0; kidno<=WN_kid_count(wn)-1; kidno++)
         {

           findAllMemRefsAndMapToMemRefExprs(stmt, WN_kid(wn,kidno),lvl);
         }

     }
     break;
     
    case OPR_LDID:
    case OPR_LDBITS: 
      {
         // 1. createAndMapNamedRef with hty=USE
         // 2. createAndMapNamedRef will no longer treat arrays any different
         //    than scalars.  
         // 3. If a variables is a reference parameter then a 
         //    deref is created. 
         // 4. How About fullAccuracy ?  Should it be fullAccuracy = full ?                      
         isAddrOf = false;
         hty = MemRefExpr::USE;
         fullAccuracy = true;
      
         createAndMapNamedRef(stmt, wn, WN_st(wn), isAddrOf, fullAccuracy, hty);
      } 
      break;

    case OPR_STID:
    case OPR_STBITS:
      {  
         // 1. createAndMapNamedRef with hty=DEF
         // 2. recurse on RHS
         // 3. How About fullAccuracy ? Should it be fullAccuracy = full ?
         assert(OPERATOR_is_store(opr));
         hty = MemRefExpr::DEF;
         fullAccuracy = true;
         createAndMapNamedRef(stmt, wn, WN_st(wn), isAddrOf, fullAccuracy, hty );
         findAllMemRefsAndMapToMemRefExprs(stmt, WN_kid0(wn),lvl); 
      }
      break;

    case OPR_ARRAY:
    case OPR_ARRSECTION:
      {
         // 1. if topMemRefHandle is LDA  (Patterns 4, 
         //     - steal the MemRefExpr and set addressOf to false 
         //     (similar to ILOAD logic)
         //     - set partial accuracy on stolen MemRefExpr
         // 2. else
         //     - changes MemRefExpr for topMemRefHandle to partial accuracy
       
         findAllMemRefsAndMapToMemRefExprs(stmt, WN_kid0(wn),lvl);

         OA::MemRefHandle m = findTopMemRefHandle(wn);
         if( WN_operator((WN *)m.hval()) == OPR_LDA ) {

           // PLM 1/23/07 
           // changed according to the new pattern 
           // pattern 4 and pattern 5 and pattern 6
    
           OA_ptr<MemRefExpr> newmre;
           newmre = *(sMemref2mreSetMap[m].begin());
           sMemref2mreSetMap[m].erase(newmre);

           if(newmre->isaRefOp()) {
              OA::OA_ptr<OA::RefOp> refOp = newmre.convert<OA::RefOp>();
              assert(!refOp.ptrEqual(0));
              if(refOp->isaAddressOf()) {
                 newmre = refOp->getMemRefExpr();
              }
           } 


           OA::OA_ptr<OA::SubSetRef> subset_mre;
           OA::OA_ptr<OA::MemRefExpr> nullMRE;
           OA::OA_ptr<OA::MemRefExpr> composed_mre;

           subset_mre = new OA::SubSetRef(
                                 OA::MemRefExpr::USE,
                                 nullMRE
                                );

           newmre = subset_mre->composeWith(newmre->clone());

           sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
           sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));
           

         } else if(WN_operator((WN *)m.hval()) == OPR_LDID ) {

             // PLM 1/23/07 
             // changed according to the new pattern, 
             // pattern 1 and pattern 3
             OA_ptr<MemRefExpr> newmre;
             newmre = *(sMemref2mreSetMap[m].begin());
             sMemref2mreSetMap[m].erase(newmre);
 
             OA::OA_ptr<OA::SubSetRef> subset_mre;
             OA::OA_ptr<OA::MemRefExpr> nullMRE;
             OA::OA_ptr<OA::MemRefExpr> composed_mre;

             subset_mre = new OA::SubSetRef(
                                  OA::MemRefExpr::USE,
                                  nullMRE
                                 );

             newmre = subset_mre->composeWith(newmre->clone());

             sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
             sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));
          
         } 

         // reset flags and lvl for index expressions because they 
         // are separate
         //flags = 0; 
         lvl = 0;
         // index expr are dim+1 ... 2*dim, dim = WN_kid_count(wn)-1 / 2
         for (INT kidno=(WN_kid_count(wn)-1)/2 +1;
             kidno<=WN_kid_count(wn)-1; kidno++)
         {
           findAllMemRefsAndMapToMemRefExprs(stmt, WN_kid(wn,kidno),lvl);
         }

      }
      break;

    case OPR_ARRAYEXP:
      {
        // 1. just recurse on kid0
        // *. don't actually create an MRE for this wn
        findAllMemRefsAndMapToMemRefExprs(stmt, WN_kid0(wn), lvl);
      }
      break;

    case OPR_LDA:
    case OPR_LDMA:
      {
        // if accessing an array the no address taken
        // FIXME: what if indirectly accessing an array in C?
        // if ((flags & flags_EXPECT_ARRAY_BASE)) {
        // ref_ty = (TY_Is_Pointer(ref_ty)) ? TY_pointed(ref_ty) : base_ty;
        // isAddrOf = false; // implicitly dereference the address
        // fullAccuracy = false;  // don't know what part of array referencing
        // }

        // 1. creates NamedRef with createNamedRef 
        // 2. then does an addressOf set
        // *. LDA never shows up on a symbol for a reference parameter.

        fullAccuracy = true;  
        isAddrOf = true;
        createAndMapNamedRef(stmt, wn, WN_st(wn), isAddrOf, fullAccuracy, hty);
        if (!isFortran) { isAddrOf = true; }
      }
      break;

    case OPR_ILOAD:
    case OPR_ILOADX:
      {
          
        // 1. If ILOAD has a LDID with sym of type ARRAY or STRUCT, ARRAY, 
        //    ARRSECTION, or STRCTFIELD  topMemRefHandle, then it steals the 
        //    MemRefExpr from the topMemRefHandle.  
        // 2. For LDA it steals and sets the addressOf to false.  
        // 3. For everything else (LDID with a scalar sym type) it creates a 
        //    Deref and points to topMemRefHandle's MemRefExpr.
        
          // default settings 
          hty = MemRefExpr::USE;

          // recurse on LHS
          WN *subMemRef = WN_kid0(wn);
          findAllMemRefsAndMapToMemRefExprs(stmt,subMemRef, lvl+1);

          // get top MemRefHandle
          OA::MemRefHandle m = findTopMemRefHandle(wn);

          // PLM 1/23/07
          // changed according to the new pattern, Pattern 1
          if( (WN_operator((WN *)m.hval()) == OPR_ARRAY) ||
              (WN_operator((WN *)m.hval()) == OPR_ARRSECTION) ||
              (WN_operator((WN *)m.hval()) == OPR_STRCTFLD) ) {
           
               OA_ptr<MemRefExpr> newmre;
               newmre = *(sMemref2mreSetMap[m].begin());
               sMemref2mreSetMap[m].erase(newmre);
               newmre->setMemRefType(hty);
               sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
               sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));
 
          } else if( WN_operator((WN *)m.hval()) == OPR_LDID ) {
               // LDID
  
               OA_ptr<MemRefExpr> newmre;
               newmre = *(sMemref2mreSetMap[m].begin());
               sMemref2mreSetMap[m].erase(newmre);
               newmre->setMemRefType(hty);
               sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
               sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));

             } else if( WN_operator((WN *)m.hval()) == OPR_LDA ) {
               // LDID

               OA_ptr<MemRefExpr> newmre;
               newmre = *(sMemref2mreSetMap[m].begin());
               sMemref2mreSetMap[m].erase(newmre);

               if(newmre->isaRefOp()) {


                  OA_ptr<RefOp> refOp = newmre.convert<RefOp>();
                  newmre = refOp->getMemRefExpr();

               } else {
                  assert(0);
               }

               sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
               sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));

             }
 
       } 

       break;

    case OPR_ISTOREX:
    case OPR_ISTBITS:
    case OPR_ISTORE:
       {
           
         // 1. recurse on LHS
         // 2. If ISTORE has a LDID with sym of type ARRAY or STRUCT, ARRAY,
         //    ARRSECTION, or STRCTFIELD  topMemRefHandle, then it steals the
         //    MemRefExpr from the topMemRefHandle.
         // 3. For LDA it steals and sets the addressOf to false.
         // 4. For everything else (LDID with a scalar sym type) it creates a
         //    Deref and points to topMemRefHandle's MemRefExpr.
         // 5. recurse on RHS

          assert(OPERATOR_is_store(opr));
          // default settings 
          hty = MemRefExpr::DEF;


          // recurse on LHS
          WN *subMemRef = WN_kid1(wn);
          findAllMemRefsAndMapToMemRefExprs(stmt,subMemRef, lvl+1);

          // get top MemRefHandle 
          OA::MemRefHandle m = findTopMemRefHandle(wn);

          if( m == MemRefHandle(0) ) {
              return; 
          }
          
          // PLM 1/23/07
          // changed according to the new pattern, Pattern 2
          if( (WN_operator((WN *)m.hval()) == OPR_ARRAY) ||
              (WN_operator((WN *)m.hval()) == OPR_ARRSECTION) ||
              (WN_operator((WN *)m.hval()) == OPR_STRCTFLD) ) {

               OA_ptr<MemRefExpr> newmre;
               newmre = *(sMemref2mreSetMap[m].begin());
               sMemref2mreSetMap[m].erase(newmre);
               newmre->setMemRefType(hty);
               if(newmre->isaRefOp()) {
                  OA::OA_ptr<OA::RefOp> refOp = newmre.convert<OA::RefOp>();
                  refOp->getMemRefExpr()->setMemRefType(hty);
               }
               sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
               sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));
          }

          // Recurse on RHS
          findAllMemRefsAndMapToMemRefExprs(stmt,WN_kid0(wn),lvl+1);

        }
        break;

    case OPR_INTRINSIC_CALL:
    case OPR_CALL:
        {
        
          /*  
          // 1. change the MemRefExpr for all of the parameters' 
          //    topMemRefHandle 
          //    by composing it with a Deref.  It should be a full accuracy 
          //    Deref so that the addressOf computations cancel out.
          //    ??? I did not understand why do we need Deref here ?

          // recur on parameters (kids 0 ... n-1) to find other MemRefHandles
          for (INT kidno=0; kidno<=WN_kid_count(wn)-1; kidno++) {

            WN* subMemRef = WN_kid(wn,kidno);
            findAllMemRefsAndMapToMemRefExprs(stmt, subMemRef, lvl+1, flags);
            //OA::MemRefHandle m = findTopMemRefHandle(subMemRef);
            //fullAccuracy = true;
            //createAndMapDerefs(stmt,wn, (WN*)m.hval(), isAddrOf, 
            //fullAccuracy, hty);
          }
          */



          for (INT kidno=0; kidno<=WN_kid_count(wn)-1; kidno++) {
            WN* subMemRef = WN_kid(wn,kidno);
            findAllMemRefsAndMapToMemRefExprs(stmt, subMemRef, lvl+1);
             if (IntrinsicInfo::isIntrinsic(wn))  {
                 // We are modeling intrinsic calls as pass by value.
                 // get the topMemRefHandle for all kids
                 // create a Deref and composeWith the MemRefExpr for
                 // the top MemRefHandle, reassign the
                 // new MemRefExpr to the top MemRefHandle.
                 // let mre be the mre from the top MemRefHandle

                 OA::MemRefHandle m = findTopMemRefHandle(subMemRef);
                 if( m != MemRefHandle(0) ) {

                 OA_ptr<MemRefExpr> mre;
                 mre = *(sMemref2mreSetMap[m].begin());
                 OA::OA_ptr<OA::MemRefExpr> clone_mre = mre->clone();

                 if(mre->isaRefOp()) {
                    OA::OA_ptr<OA::RefOp> refop = mre.convert<OA::RefOp>();
                    if(!refop->isaAddressOf()) {

                         // set accuracy to false
                         OA::OA_ptr<OA::SubSetRef> subset_mre;
                         OA::OA_ptr<OA::MemRefExpr> nullMRE;
                         OA::OA_ptr<OA::MemRefExpr> composed_mre;

                         subset_mre = new OA::SubSetRef(
                                         OA::MemRefExpr::USE,
                                         nullMRE
                                        );

                         mre = subset_mre->composeWith(mre->clone());

                         OA::OA_ptr<OA::AddressOf> address_mre;
                         address_mre = new OA::AddressOf(
                                              OA::MemRefExpr::USE,
                                              nullMRE);
                         OA::OA_ptr<OA::MemRefExpr> tmp_mre = mre->clone();
                         mre = address_mre->composeWith(tmp_mre);
                         
                    } else {
                         isAddrOf = false;
                         fullAccuracy = false;
                         hty = OA::MemRefExpr::USE;
                         int numDerefs = 1;
                         OA::OA_ptr<OA::Deref> deref_mre;
                         OA::OA_ptr<OA::MemRefExpr> nullMRE;
                         deref_mre = new OA::Deref(
                               hty,
                               nullMRE,
                               numDerefs);
                         OA::OA_ptr<OA::MemRefExpr> tmp_mre = mre->clone();
                         mre = deref_mre->composeWith(tmp_mre);

                    }
                 } else {

                         isAddrOf = false;
                         fullAccuracy = false;
                         hty = OA::MemRefExpr::USE;
                         int numDerefs = 1;

                         OA::OA_ptr<OA::Deref> deref_mre;
                         OA::OA_ptr<OA::MemRefExpr> nullMRE;
                         deref_mre = new OA::Deref(
                               hty,
                               nullMRE,
                               numDerefs);
                         OA::OA_ptr<OA::MemRefExpr> tmp_mre = mre->clone();
                         mre = deref_mre->composeWith(tmp_mre);

                 }

                 /*
                 In an intrinsic call, we treat parameters as pass-by-value. 
                 Therefore, the findAllMemRefExpr code should remove the MemRefExprs
                 associated with OPR_PARM and its child when at an intrinsic call node.                 
                 */

                 if(mre->isaUnnamed()) {
                    WN* paramnode = (WN *)m.hval();
                    WN* paramkid =  WN_kid0(paramnode);

                    sMemref2mreSetMap.erase(m);
                    sStmt2allMemRefsMap[stmt].erase(m);

                    OA::MemRefHandle param_mh = findTopMemRefHandle(paramkid);
                    OA_ptr<MemRefExpr> sub_mre;

                    sub_mre = *(sMemref2mreSetMap[param_mh].begin());

                    if(sub_mre->isaUnnamed()) {
                       sMemref2mreSetMap.erase(param_mh);
                       sStmt2allMemRefsMap[stmt].erase(param_mh);
                    }

                 } else {
                   sMemref2mreSetMap[m].erase(clone_mre);
                   sMemref2mreSetMap[m].insert(mre);
                 }
               }
              }
           }
        }
        break;

     case OPR_PARM:
        {
            
            // 1. If there is no topMemRefHandle, then will need to make one 
            //    and do the UnnamedRef thing which is now in the default case
            // 2. else takes the MemRefExpr away from the topMemRefHandle and 
            //    sets the addressTaken
            findAllMemRefsAndMapToMemRefExprs(stmt, WN_kid0(wn), lvl+1);
            

            OA::MemRefHandle m = findTopMemRefHandle(wn);
            //WN*  subMemRef = (WN*)m.hval();


            if( m == OA::MemRefHandle(0) ) {

                  bool addressTaken = false;
                  bool accuracy = true;
                  OA::MemRefExpr::MemRefType mrType = OA::MemRefExpr::DEF;
                  OA::OA_ptr<OA::MemRefExpr> lhs_tmp_mre;

                  lhs_tmp_mre = new OA::UnnamedRef(mrType, stmt);

                  sMemref2mreSetMap[MemRefHandle((irhandle_t)WN_kid0(wn))].insert(lhs_tmp_mre);
                  sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)WN_kid0(wn)));  
                  OA::OA_ptr<OA::MemRefExpr> tmp_mre;
                  OA::OA_ptr<OA::MemRefExpr> opr_param_mre;
                  tmp_mre = *(sMemref2mreSetMap[MemRefHandle((irhandle_t)WN_kid0(wn))].begin());

                  OA::OA_ptr<OA::AddressOf> address_mre;
                  OA::OA_ptr<OA::MemRefExpr> nullMRE;


                  address_mre = new OA::AddressOf(
                                              OA::MemRefExpr::USE,
                                              nullMRE);

                  opr_param_mre = address_mre->composeWith(tmp_mre->clone());

                  opr_param_mre->setMemRefType(OA::MemRefExpr::USE);
                  sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(opr_param_mre);
                  sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));
                  
            } else {
                OA_ptr<MemRefExpr> newmre;

                if( (WN_operator((WN *)m.hval()) == OPR_ARRAY) ||
                    (WN_operator((WN *)m.hval()) == OPR_MLOAD) ) {
                      // PLM 1/23/07 checked for patten 8

                      newmre = *(sMemref2mreSetMap[m].begin());
                      //sMemref2mreSetMap.erase(m);
                      //sStmt2allMemRefsMap[stmt].erase(m);
                      sMemref2mreSetMap[m].erase(newmre);

                      OA::OA_ptr<OA::AddressOf> address_mre;
                      OA::OA_ptr<OA::MemRefExpr> nullMRE;

                      address_mre = new OA::AddressOf(
                                              OA::MemRefExpr::USE,
                                              nullMRE);

                      newmre = address_mre->composeWith(newmre);

                      sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
                      sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));
                 } else if( WN_operator( (WN *)m.hval() ) == OPR_ILOAD ) {

                      // PLM 1/23/07 checked for pattern 7

                          newmre = *(sMemref2mreSetMap[m].begin());
                          sMemref2mreSetMap[m].erase(newmre);
                          sStmt2allMemRefsMap[stmt].erase(m);

                          OA::OA_ptr<OA::AddressOf> address_mre;
                          OA::OA_ptr<OA::MemRefExpr> nullMRE;

                          address_mre = new OA::AddressOf(
                                              OA::MemRefExpr::USE,
                                              nullMRE);

                          newmre = address_mre->composeWith(newmre);
                      
                          sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
                       
                          sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));

                 } else if( WN_operator( (WN *)m.hval() ) == OPR_LDA) {

                      // PLM 1/23/07 
                      // checked for pattern 9 and pattern 10

                      newmre = *(sMemref2mreSetMap[m].begin());
                      //sMemref2mreSetMap.erase(m);
                      //sStmt2allMemRefsMap[stmt].erase(m);

                      OA::OA_ptr<OA::AddressOf> address_mre;
                      OA::OA_ptr<OA::MemRefExpr> nullMRE;

                      address_mre = new OA::AddressOf(
                                              OA::MemRefExpr::USE,
                                              nullMRE);

                      newmre = address_mre->composeWith(newmre);
                      sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
                      sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));
                      // PLM 1/23/07 no done yet.
                      // call recursive routine that removes
                      // mapping for all subtrees.

                 } else if( WN_operator( (WN *)m.hval() ) == OPR_LDID ) {
                     

                      // PLM 1/23/07
                      // checked for pattern 11 and pattern 12

                      newmre = *(sMemref2mreSetMap[m].begin());
                      sMemref2mreSetMap[m].erase(newmre);

                      OA::OA_ptr<OA::AddressOf> address_mre;
                      OA::OA_ptr<OA::MemRefExpr> nullMRE;

                      address_mre = new OA::AddressOf(
                                              OA::MemRefExpr::USE,
                                              nullMRE);

                      
                      newmre = address_mre->composeWith(newmre);
                      sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
                      sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));


                 }
            }

        } 
        break;

    case OPR_MLOAD:
        {
         // 1. if topMemRefHandle is LDA  (Patterns 4,
         //     - steal the MemRefExpr and set addressOf to false
         //     (similar to ILOAD logic)
         //     - set partial accuracy on stolen MemRefExpr
         // 2. else
         //     - changes MemRefExpr for topMemRefHandle to partial accuracy

         findAllMemRefsAndMapToMemRefExprs(stmt, WN_kid0(wn),lvl);

         OA::MemRefHandle m = findTopMemRefHandle(wn);
         if( WN_operator((WN *)m.hval()) == OPR_LDA ) {

           // PLM 1/23/07
           // changed according to the new pattern
           // pattern 4 and pattern 5 and pattern 6

           OA_ptr<MemRefExpr> newmre;
           newmre = *(sMemref2mreSetMap[m].begin());
           sMemref2mreSetMap[m].erase(newmre);

           if(newmre->isaRefOp()) {
              OA::OA_ptr<OA::RefOp> refOp = newmre.convert<OA::RefOp>();
              assert(!refOp.ptrEqual(0));
              if(refOp->isaAddressOf()) {
                 newmre = refOp->getMemRefExpr();
              }
           }


           OA::OA_ptr<OA::SubSetRef> subset_mre;
           OA::OA_ptr<OA::MemRefExpr> nullMRE;
           OA::OA_ptr<OA::MemRefExpr> composed_mre;

           subset_mre = new OA::SubSetRef(
                                 OA::MemRefExpr::USE,
                                 nullMRE
                                );

           newmre = subset_mre->composeWith(newmre->clone());

           sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(newmre);
           sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));
         }
        }
        break;
        
    case OPR_MSTORE:
        {
            assert(0);
        }     
      break;

    // function references
    case OPR_ICALL:
    case OPR_VFCALL:
        { 
            assert(0);
        }
      break;


    case OPR_STRCTFLD:
      //  U8U8STRCTFLD T<11,.predef_F8,8> T<29,MYTYPE,8> <field_id:1> <--MRE
      //   U8LDA 0 <2,2,TYPED_Y> T<31,anon_ptr.,8>
      // we are in a strct field like  x%v
      // what comes below refers to x via an LDA
      // unless x is a pointer we don't want to see it. 
      {
          
        // get symbol for array
        ST* st = findBaseSymbol(WN_kid0(wn));
        fullAccuracy = false;
        createAndMapNamedRef(stmt, wn, st, isAddrOf, fullAccuracy, hty);
      }
      break;

    case OPR_BLOCK:
    case OPR_REGION:
      {
      }
      return; // Do not recur into BLOCKs

    case OPR_DO_LOOP:
      {
          
         
         // loop test expression          
         findAllMemRefsAndMapToMemRefExprs(stmt,WN_kid(wn,2),lvl);
      }
      break;

    case OPR_CASEGOTO:
      {
      }
      return; // only constants in here

    // General recursive case
    default:


      // Special case: examine only condition of control flow statements
      if (OPERATOR_is_scf(opr) || OPERATOR_is_non_scf(opr)) {
          findAllMemRefsAndMapToMemRefExprs(stmt,WN_kid(wn,0),lvl);
          // General case: recur on parameters (kids 0 ... n-1) 
      } 

      // some asserts to catch cases I don't expect to land here
      assert(!OPERATOR_is_store(opr));
      assert(!OPERATOR_is_load(opr));
      break; 
  }

}

ST* Open64IRInterface::findBaseSymbol(WN* wn)
{
  ST* retval = NULL;
  OPERATOR opr = WN_operator(wn);
  switch (opr) {
    case OPR_ARRAYEXP:
    case OPR_ARRAY:
    case OPR_ARRSECTION:
        retval = findBaseSymbol(WN_kid0(wn));
        break;
    case OPR_LDID:
    case OPR_LDBITS:
    case OPR_LDA:
    case OPR_LDMA:
        retval = WN_st(wn);
        break;
    default:
        assert(0);  // don't expect to get here
  }
  return retval;
}



void Open64IRInterface::createAndMapDerefs(OA::StmtHandle stmt,
    WN* wn, WN* subMemRef, bool isAddrOf, bool fullAccuracy,
    OA::MemRefExpr::MemRefType hty)
{
    using namespace OA;
    // get all MREs for subMemRef
    set<OA_ptr<MemRefExpr> >::iterator mreIter;
    for (mreIter=sMemref2mreSetMap[MemRefHandle((irhandle_t)subMemRef)].begin();
         mreIter!=sMemref2mreSetMap[MemRefHandle((irhandle_t)subMemRef)].end();
         mreIter++ )
    {
        OA_ptr<MemRefExpr> submre = *mreIter;
        OA_ptr<MemRefExpr> mre;

        int numDerefs = 1;
        OA::OA_ptr<OA::Deref> deref_mre;
        OA::OA_ptr<OA::MemRefExpr> nullMRE;
        deref_mre = new OA::Deref(
                               OA::MemRefExpr::USE,  
                               nullMRE,
                               numDerefs);
        OA::OA_ptr<OA::MemRefExpr> tmp_mre = mre->clone();
        mre = deref_mre->composeWith(submre);

        
        if (isAddrOf) {

            OA::OA_ptr<OA::AddressOf> address_mre;
            OA::OA_ptr<OA::MemRefExpr> nullMRE;

            address_mre = new OA::AddressOf(
                                            OA::MemRefExpr::USE,
                                            nullMRE);


            mre = address_mre->composeWith(mre);

        }
        sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(mre);
        sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));
    }
}





OA::OA_ptr<OA::MemRefExpr> 
           Open64IRInterface::convertSymToMemRefExpr(OA::SymHandle sym)
{
    OA::OA_ptr<OA::MemRefExpr> mre;
    bool isAddrOf = false;
    bool fullAccuracy = false;
    OA::MemRefExpr::MemRefType hty;
    hty = OA::MemRefExpr::USE;

    if (isRefParam(sym)) {

          mre = new OA::NamedRef(hty, sym);
          mre = new OA::Deref(hty, mre, 1);
          
    } else {

          mre = new OA::NamedRef(hty, sym);
    }

    return mre;
}




void Open64IRInterface::createAndMapNamedRef(OA::StmtHandle stmt, WN* wn,
    ST* st, bool isAddrOf, bool fullAccuracy, OA::MemRefExpr::MemRefType hty)
{
    using namespace OA;
    OA::OA_ptr<OA::MemRefExpr> mre;

    // get symbol handle, need to use representative if a global or
    // module var.  Going to use first sym in set as representative.
    SymHandle sym = SymHandle((irhandle_t)st);
    if (Stab_Is_Based_At_Common_Block(st) || Stab_Is_In_Module(st)) {
        std::set<SymHandle>::iterator setIter;
        fully_qualified_name fqn = sSymToFQNMap[sym];
        // store the local incarnation of the global sym for this procedure
        sFQNToProcToLocalSymMap[fqn][getCurrentProcContext()] = sym;
        // use the first symhandle in the set as a representative
        setIter = sGlobalVarMap[fqn].begin();
        sym = *setIter;
    }


     // Michelle:  
     // Jean says the newer version of Open64 does not need 
     // the sSymToFQNMap anymore, you may need to upgrade Open64,
     //  talk to Jean about it
    
     // modeling accesses to reference parameters as derefs to pointers
     // if (isRefParam(sym) && TY_kind(ST_type(st))==KIND_SCALAR) {


     mre = new NamedRef(hty, sym);

     if(fullAccuracy == false) {
        OA::OA_ptr<OA::SubSetRef> subset_mre;
        OA::OA_ptr<OA::MemRefExpr> nullMRE;
        OA::OA_ptr<OA::MemRefExpr> composed_mre;

        subset_mre = new OA::SubSetRef(
                                 hty,
                                 nullMRE
                                );

        mre = subset_mre->composeWith(mre->clone());
     }

    
     if( isAddrOf == true ) {
         
         OA::OA_ptr<OA::AddressOf> address_mre;
         OA::OA_ptr<OA::MemRefExpr> nullMRE;
         address_mre = new OA::AddressOf(
                                         hty,
                                         nullMRE);
         mre = address_mre->composeWith(mre);
      } 

      // will still get a NamedRef from this call 
      // if isAddrOf is true, which would be the case 
      // if we were passing a formal parameter as an actual
      if( isRefParam(sym) ) {            
          mre = new Deref(hty, mre, 1);

      } 
      
      // one case where we end up here is when passing an
      // array as a parameter another is if we are just 
      // accessing a scalar that is not a reference parameter

    sMemref2mreSetMap[MemRefHandle((irhandle_t)wn)].insert(mre);
    sStmt2allMemRefsMap[stmt].insert(MemRefHandle((irhandle_t)wn));
} 





OA::Alias::IRStmtType 
Open64IRInterface::getAliasStmtType(OA::StmtHandle h)
{
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  if (!wn) { return OA::Alias::ANY_STMT; }
  
  OPERATOR opr = WN_operator(wn);
  if (OPERATOR_is_store(opr)) {
    TY_IDX lhsref_ty = WN_GetRefObjType(wn);
    TY_IDX rhsref_ty = WN_Tree_Type(WN_kid0(wn));
    //TY& ty = Ty_Table[lhsref_ty];
    if (TY_Is_Pointer(lhsref_ty) || TY_Is_Pointer(rhsref_ty)) {
      return OA::Alias::PTR_ASSIGN_STMT;
    }
  }
  
#if 0  
  WN_TREE_CONTAINER<PRE_ORDER> wtree(wn);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  for (it = wtree.begin(); it != wtree.end(); ++it) {
    WN* curWN = it.Wn();

    OPERATOR cur_opr = WN_operator(curWN);
    if (cur_opr != OPR_INTRINSIC_CALL && OPERATOR_is_call(cur_opr)) {
      TY_IDX return_ty = WN_Call_Return_Type(wn);
      if (TY_kind(return_ty) == KIND_VOID) {
	return OA::Alias::PROC_CALL;
      } else {
	return OA::Alias::STMT_WITH_FUNC_CALL;
      }
    }
  }
#endif
  
  return OA::Alias::ANY_STMT;
}

OA::OA_ptr<OA::Alias::ParamBindPtrAssignIterator>
Open64IRInterface::getParamBindPtrAssignIterator(OA::CallHandle call)
{   
    // FIXME: for now just assuming Fortran
    bool isFortran = true;

    // Setup context for caller
    setCurrentProcToProcContext(call);

    OA::OA_ptr<Open64ParamBindPtrAssignIterator> retval;
    retval = new Open64ParamBindPtrAssignIterator;

    // start at 0 because that is how Open64 starts counting
    int count = 0;
    // iterate over all the parameters for this call site
    // and count off parameters
    
    OA::OA_ptr<OA::IRCallsiteParamIterator> paramIter = getCallsiteParams(call);
    for ( ; paramIter->isValid(); (*paramIter)++ ) {

        
        OA::ExprHandle param = paramIter->current();
        OA::OA_ptr<OA::ExprTree> eTreePtr = getExprTree(param);
        OA::EvalToMemRefVisitor evalVisitor;
        eTreePtr->acceptVisitor(evalVisitor);
        
        if ( evalVisitor.isMemRef() ) {
            
          OA::MemRefHandle memref = evalVisitor.getMemRef();

          // get the MREs for this memref
          OA::OA_ptr<OA::MemRefExprIterator> mreIter 
              = getMemRefExprIterator(memref);
          for ( ; mreIter->isValid(); (*mreIter)++ ) {
              OA::OA_ptr<OA::MemRefExpr> mre = mreIter->current();

              // if there is an address computation them we have a
              // pointer assignment happening at parameter bind time
              
              if(mre->isaRefOp()) {
                OA::OA_ptr<OA::RefOp> refop = mre.convert<OA::RefOp>();
                if(refop->isaAddressOf()) {
                   retval->insertParamBindPair(count,mre);
                }

              // if it is a named ref to a reference param in 
              // the caller then we also have a ParamBindPair
              } else if (mre->isaNamed()) {
                  OA::OA_ptr<OA::NamedRef> nref = mre.convert<OA::NamedRef>();
                  OA::SymHandle sym = nref->getSymHandle();
                  if (isRefParam(sym)) {
                      retval->insertParamBindPair(count,mre);
                  }
              }
          } 
          count++;
        } // iterate over actuals
    }
    return retval;
}

OA::SymHandle Open64IRInterface::getFormalSym(OA::ProcHandle proc, int formalID)
{
    PU_Info* procPU = (PU_Info*)proc.hval();
    OA::SymHandle retval;

    PU_SetGlobalState(procPU);
  
    WN* wn_pu = PU_Info_tree_ptr(procPU);
    int numParamsProc = WN_num_formals(wn_pu);  
    if (formalID >= numParamsProc) {
        retval = OA::SymHandle(0);
    } else {
        WN* formalWN = WN_formal(wn_pu, formalID);
        if (!formalWN) {
            retval = OA::SymHandle(0);
        } else {
            ST* formalST = WN_st(formalWN);
            retval = (OA::irhandle_t)formalST;
        }
    }

    return retval;
}

//! Given a procedure call create a memory reference expression
//! to describe that call.  For example, a normal call is
//! a NamedRef.  A call involving a function ptr is a Deref.
OA::OA_ptr<OA::MemRefExpr> 
Open64IRInterface::getCallMemRefExpr(OA::CallHandle h)
{ 
    // FIXME: this is not sufficient for function pointers
    OA::OA_ptr<OA::MemRefExpr> retval; 
    OA::SymHandle sym = getSymHandle(h);
    retval = new OA::NamedRef(OA::MemRefExpr::USE,sym);
    return retval; 
}


//-------------------------------------------------------------------------
// ActivityIRInterface
//-------------------------------------------------------------------------
  
//! Return an iterator over all independent locations for given proc
OA::OA_ptr<OA::MemRefExprIterator> 
Open64IRInterface::getIndepMemRefExprIter(OA::ProcHandle h)
{
  PU_Info* pu = (PU_Info*)h.hval();
  currentProc(h);
  OA::OA_ptr<OA::MemRefExpr> mre;
  
  // Get independent variables
  OA::OA_ptr<std::list<OA::OA_ptr<OA::MemRefExpr> > > indepList;
  indepList = new std::list<OA::OA_ptr<OA::MemRefExpr> >;
  
  WN* pragmaBlk = WN_func_pragmas(PU_Info_tree_ptr(pu));
  for (WN* wn = WN_first(pragmaBlk); wn != NULL; wn = WN_next(wn)) {
    if (WN_operator(wn) != OPR_PRAGMA) {
      continue; 
    }
    
    WN_PRAGMA_ID prag = (WN_PRAGMA_ID)WN_pragma(wn);

    if (prag == WN_PRAGMA_OPENAD_INDEPENDENT) {
      ST* st = WN_st(wn);
      OA::SymHandle sym = OA::SymHandle((OA::irhandle_t)st);
      bool isAddrOf, fullAccuracy;
      OA::MemRefExpr::MemRefType hty;
      
      isAddrOf = false;
      hty = OA::MemRefExpr::USE;

      switch (TY_kind(ST_type(st))) {
      case KIND_SCALAR:
        if (debug) {
          std::cout << "KIND_SCALAR: Sym(" << toString(sym) << ")\n";
        }       
        fullAccuracy = true;
        break;
      case KIND_ARRAY:
        if (debug) {
          std::cout << "KIND_ARRAY: Sym(" << toString(sym) << ")\n";
        }
        fullAccuracy = false;
        break;
      case KIND_STRUCT:
        if (debug) {
          std::cout << "KIND_STRUCT: Sym(" << toString(sym) << ")\n";
        }       
        fullAccuracy = false;
        break;
      case KIND_POINTER:
        if (debug) {
          std::cout << "KIND_POINTER: Sym(" << toString(sym) << ")\n";
        }
        fullAccuracy = false;  // arrays are appearing as KIND_POINTER
        break;
      case KIND_FUNCTION:
        if (debug) {
          std::cout << "KIND_FUNCTION: Sym(" << toString(sym) << ")\n";
        }
        assert(0);
        // this type not handled correctly yet
        fullAccuracy = false;
        break;
      case KIND_VOID:
        if (debug) {
          std::cout << "KIND_VOID: Sym(" << toString(sym) << ")\n";
        }
        assert(0);
        // this type not handled correctly yet
        fullAccuracy = false;
        break;
      case KIND_INVALID:
        if (debug) {
          std::cout << "KIND_INVALID: Sym(" << toString(sym) << ")\n";
        }
        assert(0);
        //this type not handled correctly yet
        fullAccuracy = false;
        break;
      default:
        if (debug) {
          std::cout << "KIND_??? hit default: Sym(" << toString(sym) << ")\n";
        }
        assert(0);
        // shouldn't get here
        fullAccuracy = false;
        break;
      }
     
      // if the symbol is a reference parameter, then the MemRefExpr
      // for an access to the symbol needs a deref
      if (isRefParam(sym)) {

        mre = new OA::NamedRef(OA::MemRefExpr::USE, sym);
        mre = new OA::Deref(OA::MemRefExpr::USE, mre, 1);

        if(fullAccuracy == true) {
           OA::OA_ptr<OA::SubSetRef> subset_mre;
           OA::OA_ptr<OA::MemRefExpr> nullMRE;
           OA::OA_ptr<OA::MemRefExpr> composed_mre;
           subset_mre = new OA::SubSetRef(
                                 OA::MemRefExpr::USE,
                                 nullMRE
                                );

           mre = subset_mre->composeWith(mre->clone());
        }

      } else {
        // one case where we end up here is when passing an array as a parameter
        // another is if we are just accessing a scalar that is not a 
        // reference parameter

        mre = new OA::NamedRef(OA::MemRefExpr::USE, sym);

        if(fullAccuracy == true) {
           OA::OA_ptr<OA::SubSetRef> subset_mre;
           OA::OA_ptr<OA::MemRefExpr> nullMRE;
           OA::OA_ptr<OA::MemRefExpr> composed_mre;
           subset_mre = new OA::SubSetRef(
                                 OA::MemRefExpr::USE,
                                 nullMRE
                                );

           mre = subset_mre->composeWith(mre->clone());
        }

      }

      indepList->push_back(mre);
    }
  }

  OA::OA_ptr<OA::MemRefExprIterator> indepIter;
  indepIter = new Open64MemRefExprIterator(indepList);
  return indepIter;

}
  
//! Return an iterator over all dependent MemRefExpr's for given proc
OA::OA_ptr<OA::MemRefExprIterator> 
Open64IRInterface::getDepMemRefExprIter(OA::ProcHandle h)
{

  PU_Info* pu = (PU_Info*)h.hval();
  currentProc(h);
  OA::OA_ptr<OA::MemRefExpr> mre;

  // Get dependent variables
  OA::OA_ptr<std::list<OA::OA_ptr<OA::MemRefExpr> > > depList;
  depList = new std::list<OA::OA_ptr<OA::MemRefExpr> >;
  
  WN* pragmaBlk = WN_func_pragmas(PU_Info_tree_ptr(pu));
  for (WN* wn = WN_first(pragmaBlk); wn != NULL; wn = WN_next(wn)) {
    if (WN_operator(wn) != OPR_PRAGMA) {
      continue; 
    }
    
    WN_PRAGMA_ID prag = (WN_PRAGMA_ID)WN_pragma(wn);
    
    if (prag == WN_PRAGMA_OPENAD_DEPENDENT) {
      ST* st = WN_st(wn);
      OA::SymHandle sym = OA::SymHandle((OA::irhandle_t)st);
      bool isAddrOf, fullAccuracy;
      OA::MemRefExpr::MemRefType hty;

      isAddrOf = false;
      hty = OA::MemRefExpr::USE;

      switch (TY_kind(ST_type(st))) {
      case KIND_SCALAR:
        if (debug) {
          std::cout << "KIND_SCALAR: Sym(" << toString(sym) << ")\n";
        }       
        fullAccuracy = true;
        break;
      case KIND_ARRAY:
        if (debug) {
          std::cout << "KIND_ARRAY: Sym(" << toString(sym) << ")\n";
        }
        fullAccuracy = false;
        break;
      case KIND_STRUCT:
        if (debug) {
          std::cout << "KIND_STRUCT: Sym(" << toString(sym) << ")\n";
        }       
        fullAccuracy = false;
        break;
      case KIND_POINTER:
        if (debug) {
          std::cout << "KIND_POINTER: Sym(" << toString(sym) << ")\n";
        }
        fullAccuracy = false;  // arrays are appearing as KIND_POINTER
        break;
      case KIND_FUNCTION:
        if (debug) {
          std::cout << "KIND_FUNCTION: Sym(" << toString(sym) << ")\n";
        }
        assert(0);
        // this type not handled correctly yet
        fullAccuracy = false;
        break;
      case KIND_VOID:
        if (debug) {
          std::cout << "KIND_VOID: Sym(" << toString(sym) << ")\n";
        }
        assert(0);
        // this type not handled correctly yet
        fullAccuracy = false;
        break;
      case KIND_INVALID:
        if (debug) {
          std::cout << "KIND_INVALID: Sym(" << toString(sym) << ")\n";
        }
        assert(0);
        //this type not handled correctly yet
        fullAccuracy = false;
        break;
      default:
        if (debug) {
          std::cout << "KIND_??? hit default: Sym(" << toString(sym) << ")\n";
        }
        assert(0);
        // shouldn't get here
        fullAccuracy = false;
        break;
      }


      // if the symbol is a reference parameter, then the MemRefExpr
      // for an access to the symbol needs a deref
      if (isRefParam(sym)) {

        mre = new OA::NamedRef(OA::MemRefExpr::USE, sym);
        mre = new OA::Deref(OA::MemRefExpr::USE, mre, 1);

        if(fullAccuracy == true) {
           OA::OA_ptr<OA::SubSetRef> subset_mre;
           OA::OA_ptr<OA::MemRefExpr> nullMRE;
           OA::OA_ptr<OA::MemRefExpr> composed_mre;
           subset_mre = new OA::SubSetRef(
                                 OA::MemRefExpr::USE,
                                 nullMRE
                                );

           mre = subset_mre->composeWith(mre->clone());
        }
          
      } else {
        // one case where we end up here is when passing an array as a parameter
        // another is if we are just accessing a scalar that is not a
        // reference parameter

        mre = new OA::NamedRef(OA::MemRefExpr::USE, sym);

        if(fullAccuracy == true) {
           OA::OA_ptr<OA::SubSetRef> subset_mre;
           OA::OA_ptr<OA::MemRefExpr> nullMRE;
           OA::OA_ptr<OA::MemRefExpr> composed_mre;
           subset_mre = new OA::SubSetRef(
                                 OA::MemRefExpr::USE,
                                 nullMRE
                                );

           mre = subset_mre->composeWith(mre->clone());
        }

      }

      depList->push_back(mre);
    }
  }

  OA::OA_ptr<OA::MemRefExprIterator> depIter;
  depIter = new Open64MemRefExprIterator(depList);
  return depIter;
}
 
//! Given a statement, return its Activity::IRStmtType
OA::Activity::IRStmtType Open64IRInterface::getActivityStmtType(OA::StmtHandle h)
{ 
    setCurrentProcToProcContext(h);
    if (getReachConstsStmtType(h)==OA::ReachConsts::EXPR_STMT) {
        return OA::Activity::EXPR_STMT;
    } else {
        return OA::Activity::ANY_STMT;
    }
}

int Open64IRInterface::getSizeInBytes(OA::SymHandle h)
{
    setCurrentProcToProcContext(h);
    return TY_size(ST_type((ST*)h.hval()));
}

//---------------------------------------------------------------------------
// ReachDefsIRInterface
//---------------------------------------------------------------------------

OA::OA_ptr<OA::IRSymIterator>
Open64IRInterface::getRefSymIterator(OA::ProcHandle h)
{
  PU_Info* pu = (PU_Info*)h.hval();
  OA::OA_ptr<OA::IRSymIterator> retval;
  retval = new Open64IRSymIterator(pu);
  return retval;
}

//! Return a list of all def  memory reference handles that appear
//! in the given statement.
//! User is responsible for deleting the list
OA::OA_ptr<OA::MemRefHandleIterator>
Open64IRInterface::getDefMemRefs(OA::StmtHandle stmt)
{
  setCurrentProcToProcContext(stmt);
  OA::OA_ptr<std::list<OA::MemRefHandle> > retList;
  retList = new std::list<OA::MemRefHandle>;
  
  // get iterator over memory references for this statement
  // and only put DEFs in the list
  OA::OA_ptr<OA::MemRefHandleIterator> mIter = getMemRefIterator(stmt);
  for ( ; mIter->isValid(); (*mIter)++ ) {
    OA::MemRefHandle memref = mIter->current();

    // loop over memory reference expressions for this memref handle
    set<OA::OA_ptr<OA::MemRefExpr> >::iterator mreIter;
    for (mreIter = sMemref2mreSetMap[memref].begin();
         mreIter != sMemref2mreSetMap[memref].end(); mreIter++ ) 
    {
        OA::OA_ptr<OA::MemRefExpr> mre = *mreIter;

        //! ================================================
        //! only map those MREs that do not involve an addressOf operation
        //! added by PLM 09/14/06
        //! ================================================

        if(mre->isaRefOp()) {
           OA::OA_ptr<OA::RefOp> refop = mre.convert<OA::RefOp>();
           if(refop->isaAddressOf()) {
              continue; 
           }
        }

        if (mre->isDef()) {
          retList->push_back(memref);
          break;
        }
    }
  }

  OA::OA_ptr<Open64MemRefHandleIterator> retval;
  retval = new Open64MemRefHandleIterator(retList);
  return retval;
}

//! Return a list of all the memory reference handles that appear
//! in the given statement.
//! User is responsible for deleting the list
OA::OA_ptr<OA::MemRefHandleIterator>
Open64IRInterface::getAllMemRefs(OA::StmtHandle stmt)
{
  setCurrentProcToProcContext(stmt);
  OA::OA_ptr<std::list<OA::MemRefHandle> > retList; 
  retList = new std::list<OA::MemRefHandle>;
  
  // get iterator over memory references for this statement
  // and for now just copy the list
  OA::OA_ptr<OA::MemRefHandleIterator> mIter = getMemRefIterator(stmt);
  for ( ; mIter->isValid(); (*mIter)++ ) {
    OA::MemRefHandle memref = mIter->current();
    retList->push_back(memref);
  }

  OA::OA_ptr<Open64MemRefHandleIterator> retval;
  retval = new Open64MemRefHandleIterator(retList);
  return retval;
}
  
//---------------------------------------------------------------------------
// UDDUChainsIRInterface
//---------------------------------------------------------------------------

//! Return a list of all use memory reference handles that appear
//! in the given statement.
//! User is responsible for deleting the list
OA::OA_ptr<OA::MemRefHandleIterator>
Open64IRInterface::getUseMemRefs(OA::StmtHandle stmt)
{
  setCurrentProcToProcContext(stmt);
  OA::OA_ptr<std::list<OA::MemRefHandle> > retList; 
  retList = new std::list<OA::MemRefHandle>;

  // get iterator over memory references for this statement
  // and only put USES in the list
  OA::OA_ptr<OA::MemRefHandleIterator> mIter = getMemRefIterator(stmt);
  for ( ; mIter->isValid(); (*mIter)++ ) {
    OA::MemRefHandle memref = mIter->current();
    
    // loop over memory reference expressions for this memref handle
    set<OA::OA_ptr<OA::MemRefExpr> >::iterator mreIter;
    for (mreIter = sMemref2mreSetMap[memref].begin();
         mreIter != sMemref2mreSetMap[memref].end(); mreIter++ ) 
    {
        OA::OA_ptr<OA::MemRefExpr> mre = *mreIter;
        
        
        //! ================================================ 
        //! only map those MREs that do not involve an addressOf operation
        //! added by PLM 09/14/06 
        //! ================================================ 

        if(mre->isaRefOp()) {
           OA::OA_ptr<OA::RefOp> refop = mre.convert<OA::RefOp>();
           if(refop->isaAddressOf()) {
              continue;
           }
        }
          
        if (mre->isUse()) {
          retList->push_back(memref);
          break;
        }
    }
  }

  OA::OA_ptr<Open64MemRefHandleIterator> retval;
  retval = new Open64MemRefHandleIterator(retList);
  return retval;
}


//---------------------------------------------------------------------------
// ReachConstsIRInterface (and Open64ConstVal)
//---------------------------------------------------------------------------

OA::OA_ptr<OA::ConstValBasicInterface> 
Open64ConstVal::eval(OPERATOR opr, 
		     const OA::OA_ptr<OA::ConstValBasicInterface> op2) const
{
  OA::OA_ptr<OA::ConstValBasicInterface> retval;  retval = NULL;

  // Cannot eval without a specific type; return an opaque const object
  // return new Open64ConstVal();

  // returning NULL  -  NULL is recognizable, 
  //                    whereas new Open64ConstVal() is not

  return retval;
}

OA::OA_ptr<OA::ConstValBasicInterface> 
Open64IntegerConstVal::eval(OPERATOR opr, 
    const OA::OA_ptr<OA::ConstValBasicInterface> op2_) const
{
  int val = 0;
  OA::OA_ptr<OA::ConstValBasicInterface> retval;

  // if opr is a unary op, op2_ will be NULL
  if (op2_.ptrEqual(NULL)) {

    // right now, only works for opr==OPR_PARM
    switch (opr) {
    case OPR_PARM: 
      /*
        val = this->getIntegerVal();
        retval = new Open64IntegerConstVal(val);
      */
      // shouldn't get here anymore

      std::cout << "In OPR_PARM of eval in Open64IRInterface.cpp (error)\n";
      std::cout.flush();
      exit(555);
      
      break;
    default:
      retval = NULL;
    }
    return retval;
  }

  OA::OA_ptr<const Open64ConstVal> op2 = op2_.convert<const Open64ConstVal>();
  assert(op2->isaInteger());
  
  switch (opr) {
  case OPR_ADD:
    val = this->getIntegerVal() + op2->getIntegerVal();
    retval = new Open64IntegerConstVal(val);
    break;
  case OPR_SUB:
    val = this->getIntegerVal() - op2->getIntegerVal();
    retval = new Open64IntegerConstVal(val);
    break;
  case OPR_MPY:
    val = this->getIntegerVal() * op2->getIntegerVal();
    retval = new Open64IntegerConstVal(val);
    break;
  case OPR_DIV:
    val = this->getIntegerVal() / op2->getIntegerVal();
    retval = new Open64IntegerConstVal(val);
    break;
    
  default:
    //    return new Open64ConstVal();

    // NULL is recognizable, new Open64ConstVal() is not
    retval = NULL;
  }
  
  return retval;
}

OA::ReachConsts::IRStmtType 
Open64IRInterface::getReachConstsStmtType(OA::StmtHandle h)
{
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  if (!wn) { return OA::ReachConsts::NONE; }
  
  OPERATOR opr = WN_operator(wn);
  if (OPERATOR_is_store(opr)) { // cf. findAssignPairs
    return OA::ReachConsts::EXPR_STMT;
  } else {
    return OA::ReachConsts::ANY_STMT;
  }
}

OA::OA_ptr<OA::AssignPairIterator> 
Open64IRInterface::getAssignPairIterator(OA::StmtHandle h)
{ 
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  return findAssignPairs(wn);
}

OA::OA_ptr<OA::ConstValBasicInterface> 
Open64IRInterface::evalOp(OA::OpHandle op, 
			  OA::OA_ptr<OA::ConstValBasicInterface> operand1, 
			  OA::OA_ptr<OA::ConstValBasicInterface> operand2)
{ 
  WN* wn = (WN*)op.hval();
  OA::OA_ptr<OA::ConstValBasicInterface> retval;
  if (operand1.ptrEqual(NULL)) {retval = NULL; return retval;}
  const OA::OA_ptr<Open64ConstVal> op1 = operand1.convert<Open64ConstVal>();  
  return op1->eval(WN_operator(wn), operand2);
}

OA::OA_ptr<OA::ConstValBasicInterface> 
Open64IRInterface::getConstValBasic(OA::ConstSymHandle c) 
{ 
  setCurrentProcToProcContext(c);
  ST* st = (ST*)c.hval();  
  return getConstValBasicFromST(st);
}

OA::OA_ptr<OA::ConstValBasicInterface> 
Open64IRInterface::getConstValBasic(OA::ConstValHandle c)
{ 
  setCurrentProcToProcContext(c);
  OA::OA_ptr<OA::ConstValBasicInterface> cvb; cvb = NULL;
  
  WN* wn = (WN*)c.hval();
  if (!wn) { return cvb; }
  
  OPERATOR opr = WN_operator(wn);
  if (opr == OPR_CONST) {
    ST* st = WN_st(wn);
    cvb = getConstValBasicFromST(st);
  }
  else if (opr == OPR_INTCONST) {
    INT64 val = WN_const_val(wn);
    if (val < INT_MIN || val > INT_MAX) {
    // cvb = new Open64ConstVal(); // no current representation for this
      cvb = NULL;
    } else {
      cvb = new Open64IntegerConstVal((int)val);
    }
  }
  else {
    assert(0); // throw an assertion
  }
  
  return cvb;
}

//! temporary routine to find things out
// should be removed after testing
int
Open64IRInterface::returnOpEnumValInt(OA::OpHandle op)
{ 
  setCurrentProcToProcContext(op);
  WN* wn = (WN*)op.hval();
  OPERATOR opr = WN_operator(wn); 
  return (int)opr;
}


//! Return a stmt handle for the given memory reference handle
OA::StmtHandle 
Open64IRInterface::getStmtFromMemRef(OA::MemRefHandle h) {

  // if haven't seen this MemRefHandle yet will assert in this call
  setCurrentProcToProcContext(h);

  return sMemRef2StmtMap[h];
}

//! Temporary routine for testing MPICFG
// given a ConstValBasicInterface, print out value if any
std::string 
Open64IRInterface::toString(OA::OA_ptr<OA::ConstValBasicInterface> cvPtr)
{
  std::ostringstream oss;
  if (cvPtr.ptrEqual(NULL)) {
    oss << "no value, null ConstValBasicInterface*";
  } else {
    const OA::OA_ptr<Open64ConstVal> op1 = cvPtr.convert<Open64ConstVal>();
    if (op1->isaInteger()) {
      oss << op1->getIntegerVal();
    } else {
      oss << "not an integer value";
    }
  }
  return oss.str();
  
}

//! Temporary routine for testing ReachConsts
// Given an unsigned int, return a ConstValBAsicInterface for it
OA::OA_ptr<OA::ConstValBasicInterface> 
Open64IRInterface::getConstValBasic (unsigned int val) {
  OA::OA_ptr<OA::ConstValBasicInterface>  retval;
  retval = new Open64IntegerConstVal((int)val);
  return retval;
}

//---------------------------------------------------------------------------
// LinearityIRInterface.hpp
//---------------------------------------------------------------------------

//! gets the operation type and returns a LinOpType
OA::Linearity::LinOpType
Open64IRInterface::getLinearityOpType(OA::OpHandle op)
{ 
  setCurrentProcToProcContext(op);

  OA::Linearity::LinOpType opt;
  
  
  WN* wn = (WN*)op.hval();
  OPERATOR opr = WN_operator(wn); 

switch (opr) {
  // Unary expression operations.
  case OPR_NEG:
      opt = OA::Linearity::OPR_LINEAR;
      break;
      
  // Binary expression operations.
  case OPR_ADD:
  case OPR_SUB:
      opt = OA::Linearity::OPR_ADDSUB;
      break;
  case OPR_MPY:
  case OPR_DIV:
      opt = OA::Linearity::OPR_MPYDIV;
      break;
  case OPR_CALL:
//    os << createCharStarForST(WN_st (wn)) << "(";
    opt = OA::Linearity::OPR_NONLINEAR;
    break;
  case OPR_INTRINSIC_CALL:
  case OPR_INTRINSIC_OP:
//    os << INTRINSIC_name ((INTRINSIC) WN_intrinsic (wn)) << "(";
    opt = OA::Linearity::OPR_NONLINEAR;
    break;
  default:
    opt = OA::Linearity::OPR_NONLINEAR;
    break;
  }

  
  return opt;
  //return (int)opr;
}

OA::Linearity::IRStmtType 
Open64IRInterface::getLinearityStmtType(OA::StmtHandle h)
{
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  if (!wn) { return OA::Linearity::NONE; }
  
  OPERATOR opr = WN_operator(wn);
  if (OPERATOR_is_store(opr)) { // cf. findAssignPairs
    return OA::Linearity::EXPR_STMT;
  } else {
    return OA::Linearity::ANY_STMT;
  }
}

//---------------------------------------------------------------------------
// InterSideEffectIRInterface.hpp
//---------------------------------------------------------------------------

/*! 
   Note: This routine uses sSymToVarStringMap, which is initialized in
   initProcContext
*/
OA::OA_ptr<OA::SideEffect::SideEffectStandard> 
Open64IRInterface::getSideEffect(OA::ProcHandle callerProc, 
                                 OA::SymHandle calleeSym)
{
  setCurrentProcToProcContext(calleeSym);
  // create a new (waiting to be filled) SideEffectStandard as member
  OA::OA_ptr<OA::SideEffect::SideEffectStandard> retSideEffect;
  retSideEffect= new OA::SideEffect::SideEffectStandard();
 

  currentProc(callerProc);
  
  // see if symbol matches one of the procedures we want to have
  // optimistic results for
  std::set<std::string> noSideEffectProcs;
  sSymToVarStringMap[OA::SymHandle(0)] = "<no-symbol>";
  noSideEffectProcs.insert("<no-symbol>");
  noSideEffectProcs.insert("_END");
  noSideEffectProcs.insert("ABS");
  noSideEffectProcs.insert("LOG");
  noSideEffectProcs.insert("FLOAT");
  noSideEffectProcs.insert("SQRT");
  // hacks for NPB
  noSideEffectProcs.insert("randlc_");
  noSideEffectProcs.insert("timer_clear_");
  noSideEffectProcs.insert("timer_stop_");
  noSideEffectProcs.insert("timer_start_");
  noSideEffectProcs.insert("timer_read_");
  noSideEffectProcs.insert("print_results_");
  noSideEffectProcs.insert("print_timers_");
  noSideEffectProcs.insert("ctimer_");
  noSideEffectProcs.insert("integr_");
  // Other Intrinsics
  noSideEffectProcs.insert("DINT");
  noSideEffectProcs.insert("DSQRT");
  noSideEffectProcs.insert("DBLE");
  noSideEffectProcs.insert("DABS");
  noSideEffectProcs.insert("DFLOAT");
  noSideEffectProcs.insert("EXP");
  noSideEffectProcs.insert("DEXP");
  noSideEffectProcs.insert("vranlc_");
  noSideEffectProcs.insert("COS");
  noSideEffectProcs.insert("SIN");
  noSideEffectProcs.insert("DIMAG");
  noSideEffectProcs.insert("DCONJG");
  noSideEffectProcs.insert("DLOG");
  noSideEffectProcs.insert("REAL");
    
  if (noSideEffectProcs.find(sSymToVarStringMap[calleeSym])
      != noSideEffectProcs.end() )
  {
    // empty out all the sets
    retSideEffect->emptyLMOD();
    retSideEffect->emptyMOD();
    retSideEffect->emptyLDEF();
    retSideEffect->emptyDEF();
    retSideEffect->emptyLUSE();
    retSideEffect->emptyUSE();
    retSideEffect->emptyLREF();
    retSideEffect->emptyREF();

  }
  
  return retSideEffect;

}

//---------------------------------------------------------------------------
// ExprTreeIRShortCircuit
//---------------------------------------------------------------------------

//! Given an ExprHandle, return an ExprTree* 
//! The user must free the expr tree  
OA::OA_ptr<OA::ExprTree> 
Open64IRInterface::getExprTree(OA::ExprHandle h) 
{ 
  setCurrentProcToProcContext(h);

  WN* wn = (WN*)h.hval();
  return createExprTree(wn);
}

//! returns true if given symbol is a parameter 
bool Open64IRInterface::isParam(OA::SymHandle anOASymbolHandle){ 
  ST* anOpen64Symbol_p = (ST*)anOASymbolHandle.hval();
  return (((ST_sclass(anOpen64Symbol_p)==SCLASS_FORMAL) 
           || 
           (ST_sclass(anOpen64Symbol_p)==SCLASS_FORMAL_REF))
          &&
          (ST_level(anOpen64Symbol_p) == CURRENT_SYMTAB)); 
  // BK:  added the &&(CURRENT_SYMTAB) to distinguish between parameters
  //      in a global/enclosing subroutine versus a local parameters
  //      now:  answers false for the former, and still true for the latter
} 

//---------------------------------------------------------------------------
// LocationIRShortCircuit
//---------------------------------------------------------------------------

//! For the given symbol create a Location that indicates statically
//! overlapping locations and information about whether the location
//! is local or not, local means visible in only this procedure
//! If the symbol is not visible within the current procedure then
//! a null location is returned.
//! FIXME: does Fortran90 allow nested procedures?  if so then
//! variables visible to a nested procedure should not be labeled local
OA::OA_ptr<OA::Location> 
Open64IRInterface::getLocation(OA::ProcHandle p, OA::SymHandle s)
{
    OA::OA_ptr<OA::NamedLoc> retval;
    if (s==OA::SymHandle(0)) {
        retval = NULL;
        return retval;
    }

    if (debug) {
      std::cout << std::endl << "mIR->toString(p) = " << toString(p) 
              << ", <hval=" << p.hval() << std::endl;
      std::cout << "mIR->toString(s) = " << toString(s) 
              << ", <hval=" << s.hval() << std::endl;
    }
    // save off old context 
    OA::ProcHandle currContext = getCurrentProcContext();

    // change to context for the sym so can determine if it is global
    setCurrentProcToProcContext(s);

    // if this symbol is global then it is a representative for all the 
    // symbols in each different procedure for the same global
    // need to get symbol specific to this procedure
    ST* st = (ST*)s.hval();
    if (Stab_Is_Based_At_Common_Block(st) || Stab_Is_In_Module(st)) {
        fully_qualified_name fqn = sSymToFQNMap[s];
        s = sFQNToProcToLocalSymMap[fqn][p];
        // need context for this procedure now
        setCurrentProcContext(p);
    }
    
    bool isLocal, isUnique;
    bool hasNestedProc = (PU_Info_child(Current_PU_Info) != NULL);

    // check that SymHandle isn't null
    if (s!=OA::SymHandle(0)) {
      // make sure the symbol is visible within procedure
      if (sProcToSymRefSetMap[p].find(s)==sProcToSymRefSetMap[p].end()) {
        retval = NULL;
      } else {

        isLocal = (!hasNestedProc) && (ST_level((ST*)s.hval()) == CURRENT_SYMTAB);
        isUnique = isLocal;

        retval = new OA::NamedLoc(s, isLocal);
        
        // if it is a common block variable then need to make sure the same var
        // name within the same common block indicates the other symbol handles
        // for that same var name and common block that fully overlap
        if (Stab_Is_Based_At_Common_Block(st) || Stab_Is_In_Module(st)) 
        {
          fully_qualified_name fqn = sSymToFQNMap[s];
          if (sGlobalVarMap[fqn].empty()) {
            assert(0); // this symbol should have been put in there
                       // around line 3233
          }

          retval = new OA::NamedLoc(s, isLocal);

          // indicate that all of the symbols in sGlobalVarMap with the same
          // fully qualified name overlap with this location
          std::set<OA::SymHandle>::iterator setIter;
          for (setIter = sGlobalVarMap[fqn].begin(); 
               setIter!=sGlobalVarMap[fqn].end(); setIter++)
          {
              OA::SymHandle overlapSym = *setIter;
              //std::cout << " sym (hval=" <<  overlapSym.hval() 
              //          << ") = " << toString(*setIter) << std::endl;
              retval->addFullOverlap(*setIter);
          }
        } 
      }

    } else {
      retval = NULL;
    }
    // reset the context
    setCurrentProcContext(currContext);

    return retval;
}


//! Given a MemRefHandle return an iterator over all
//! MemRefExprs that describe this memory reference
OA::OA_ptr<OA::MemRefExprIterator> 
Open64IRInterface::getMemRefExprIterator(OA::MemRefHandle memref)
{
    // will assert if haven't seen MemRefHandle yet
    setCurrentProcToProcContext(memref);

    OA::OA_ptr<std::list<OA::OA_ptr<OA::MemRefExpr> > > retList;
    retList = new std::list<OA::OA_ptr<OA::MemRefExpr> >;

    // iterate over set of MemRefExpr's associated with
    // the given MemRefHandle and put them in our list
    set<OA::OA_ptr<OA::MemRefExpr> >::iterator mreIter;
    

    for (mreIter = sMemref2mreSetMap[memref].begin();
         mreIter != sMemref2mreSetMap[memref].end(); mreIter++ ) 
    {
        retList->push_back(*mreIter);
    }
    
    OA::OA_ptr<Open64MemRefExprIterator> retval;
    retval = new Open64MemRefExprIterator(retList);
    return retval;
}

//-------------------------------------------------------------------------
// ICFGIRInterface
//-------------------------------------------------------------------------

//! Given the callee symbol returns the callee proc handle
OA::ProcHandle Open64IRInterface::getProcHandle(OA::SymHandle sym)
{
    return Open64IRInterface::sCallSymToProc[sym];
}
  
//---------------------------------------------------------------------------
// XAIFIRInterface
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Context state
//---------------------------------------------------------------------------

void
Open64IRInterface::initContextState(PU_Info* pu_forest)
{
  // if context hasn't already been set for this program then call
  // helper routine that sets up context
  if (Open64IRInterface::sContextInit==false) { 
    Open64IRProcIterator procIt(pu_forest);
    Open64IRInterface::initProcContext(pu_forest, procIt);
    Open64IRInterface::initCallSymToProcMap(procIt);
    Open64IRInterface::initProcToSymRefSetMap(procIt);
  }
}


//***************************************************************************
// Helpers
//***************************************************************************

// NOTE: Could be relocated to a more general library

// This function will Call itself recursively until it finds
// MemRefHandle mapped to sMemref2mreSetMap. 
// For the case where ParamBinding returns &0:S2:0:anon_ptr
// and we are looking for MemRefHandle = S2:0:anon_ptr mapped
// to sMemref2mreSetMap. Please notice corresponding changes in
// createExprTree in the switch option : OPERATOR_is_load(opr).


OA::MemRefHandle Open64IRInterface::findTopMemRefHandle(WN *wn)
{
  OA::MemRefHandle h = OA::MemRefHandle(0);

  if (wn==0) {
    return OA::MemRefHandle(0);
  }
  h = (OA::irhandle_t)wn;
  
  if(h == OA::MemRefHandle(0)) {
     return OA::MemRefHandle(0);
  }

  if(sMemref2mreSetMap.find(h) == sMemref2mreSetMap.end()) {

      if(WN_operator(wn) == OPR_ISTORE)
      {
         wn  =  WN_kid1(wn);
      } else if ( (WN_operator(wn) == OPR_ILOAD) ||
              (WN_operator(wn) == OPR_LDID)  ||
              (WN_operator(wn) == OPR_STID)  ||
              (WN_operator(wn) == OPR_ARRAY) ||
              (WN_operator(wn) == OPR_ARRAYEXP) ||
              (WN_operator(wn) == OPR_LDA) ||
              (WN_operator(wn) == OPR_CALL) ||
              (WN_operator(wn) == OPR_INTRINSIC_CALL) ||
              (WN_operator(wn) == OPR_ISTORE) ||
              (WN_operator(wn) == OPR_ARRSECTION) ||
              (WN_operator(wn) == OPR_PARM) ||
              (WN_operator(wn) == OPR_STRCTFLD) ||
              (WN_operator(wn) == OPR_MLOAD) )
      {
         wn =  WN_kid0(wn);
      } else {
         // INTCONST, Parameter as expression
        return OA::MemRefHandle(0);
      }

      h=findTopMemRefHandle(wn);
  } else {
      return h; 
  }

 return h;
}


// createExprTree: Given 'wn' return a possibly empty expression tree.
OA::OA_ptr<OA::ExprTree>
Open64IRInterface::createExprTree(WN* wn)
{
  OA::OA_ptr<OA::ExprTree> exprTree;
  exprTree = new OA::ExprTree;
  createExprTree(exprTree, wn);
  return exprTree;
}


// createExprTree: Given a tree container 'tree' and 'wn', builds tree
// nodes for wn, adds them to 'tree' and returns the root node of the
// newly created tree nodes
OA::OA_ptr<OA::ExprTree::Node>
Open64IRInterface::createExprTree(OA::OA_ptr<OA::ExprTree> tree, WN* wn)
{

    
  OA::OA_ptr<OA::ExprTree::Node> root; root = NULL;
  if (!wn) { return root; }
  
  // 1. Sanity checking.  (In the context of expressions, OPR_STID
  // represents the LHS of the assignment.)
  OPERATOR opr = WN_operator(wn);
  if ( !(opr == OPR_STID || OPERATOR_is_call(opr) 
	 || OPERATOR_is_expression(opr)) ) {
    return root;
  }

  // 1a. FIXME: For now, eliminate PARM nodes from tree.
  if (opr == OPR_PARM) {
    if (WN_kid_count(wn) == 0) {
      return root;
    } 
    else {
      // dont want to recurse because we want only top MemRefHandle 

      OA::MemRefHandle h((OA::irhandle_t)wn);
      
      if (sMemref2mreSetMap.find(h)!=sMemref2mreSetMap.end()) {
        root = new OA::ExprTree::MemRefNode(h);
        tree->addNode(root);
        return root;  
      }
      else {
        return createExprTree(tree, WN_kid0(wn));
      }  
    }
  }
  
  // 2. Create a parent tree node for the curent WN.  Note that order
  // is important here.  *Note* OPR_ICALL and OPR_VFCALL will be
  // classified as calls instead of mem-refs.
  bool bypassRecursion = false;
  if (IntrinsicInfo::isIntrinsic(wn)) {
    OA::OpHandle h((OA::irhandle_t)wn);
    root = new OA::ExprTree::OpNode(h);
  }
  else if (OPERATOR_is_call(opr)) {
    OA::CallHandle h((OA::irhandle_t)wn);
    root = new OA::ExprTree::CallNode(h);
  }
  else if (opr == OPR_CONST || opr == OPR_INTCONST) {
    OA::ConstValHandle h((OA::irhandle_t)wn);
    root = new OA::ExprTree::ConstValNode(h);
  }
  else if (OPERATOR_has_sym(opr) && ST_class(WN_st(wn)) == CLASS_CONST) {
    OA::ConstSymHandle h((OA::irhandle_t)WN_st(wn));
    root = new OA::ExprTree::ConstSymNode(h);
  }
  else if (opr == OPR_STID || OPERATOR_is_load(opr)
	   || opr == OPR_ARRAY || opr == OPR_ARRSECTION 
	   || opr == OPR_ARRAYEXP) {
    OA::MemRefHandle h((OA::irhandle_t)wn);
    // HACK! ALERT! BK:
    // mfef90 is not distributing the constant values beyond the
    // main procudure to all subroutines.  Until this is fixed in 
    // mfef90, we need to cause all memrefs that refer to the
    // constant named MPI_COMM_WORLD with the constant value 91 (this
    // is the value from the mpif.h file we are using with our 
    // experiment application programs.
    //
    // before HACK, there was just the following line:
    //   root = new ExprTree::MemRefNode(h);
    //
    string strMemRef;
    {
      WN* wn = (WN*)h.hval();
      std::ostringstream oss;
      DumpWNMemRef(wn, oss);
      strMemRef = oss.str();
    }
    string strMWC = "MPI_COMM_WORLD";
    if (strMemRef.compare(0,strMWC.length(),strMWC) == 0) {
      INT64 i64value = (INT64)91;
      WN* wnic = WN_CreateIntconst(OPC_I4INTCONST,i64value);
      OA::ConstValHandle cvh((OA::irhandle_t)wnic);
      root = new OA::ExprTree::ConstValNode(cvh);
    } 
    else {
      // special case for ILOAD - ARRAY idiom

       /*! OPR_ILOAD can get WN_kid0 = OPR_LDA instead of OPR_ARRAY
           and we need irhandle to its kid0. e.g.
           (PARM U8 V ((oflg 0x8001) (ty ".predef_F8" 11 8))
             (ILOAD F8 F8 (0 0 (ty ".predef_F8" 11 8) (ty "anon_ptr." 34 8))
               (LDA U8 V ((st "S2" 2 20) 0 (ty "anon_ptr." 39 8) 0))))   

            In this case, MemRefHandle(wn) where wn=ILOAD will give us 
            &0:S2:0:anon_ptr and MemRefHandle to WN_kid0(wn) where wn=ILOAD
            will give us MemRefHandle to S2:0:anon_ptr.
            Please refer rung_kutta.f example for the case 
            fun_(&H3:0:.predef_F8+T:0:.predef_F8, &0:NEW_Y_1:0:anon_ptr., 
                  &0:S2:0:anon_ptr., &N:0:.predef_I4) where we missed
            paramBinding Pairs because we did not find MemRefHandle for 
            &0:S2:0:anon_ptr in the sMemref2mreSetMap.
            findToMemRefHandle will call itself recursively to get correct 
            MemRefHandle in sMemref2mreSetMap.
            opr=OPR_ILOAD conditional is modifies as follows.
            PLM 10/05/06

           if (opr == OPR_ILOAD && WN_operator(WN_kid0(wn)) == OPR_ARRAY) {
        	  h = (OA::irhandle_t)WN_kid0(wn);
           }
      */  
      if (opr == OPR_ILOAD) {
         OA::MemRefHandle m = findTopMemRefHandle(wn);
         WN* wn = (WN*)m.hval();
         if (wn!=0) {
            root = new OA::ExprTree::MemRefNode(m);
         } else {
            root = new OA::ExprTree::MemRefNode(h);
         }
       } else {
         root = new OA::ExprTree::MemRefNode(h);
       }
        
      bypassRecursion = true; // MemRefNodes are leaves
    }

    //
    // end of HACK!
  }
  else /*if ()*/ { 
    
    // We had a problem where we did not get ParamBinding pairs for 
    // the formal parameters passed as actuals in the expression.
    // e.g. foo(n+1, k)
    // In order to deal with this problem we made changes as below
    // Before : 
    //                  + (OpNode)
    //               /     \
    // (MemRefNode)n        1 (ConstNode) 
    // After
    //                  + (MemRefNode)
    //               /     \
    // (MemRefNode)n        1 (ConstNode)
    // This is just a temporary change. This will be replaced by Assignment pairs
    // in the future. 
    
    if(!(sMemref2mreSetMap[OA::MemRefHandle((OA::irhandle_t)wn)].empty())) {
       OA::MemRefHandle h((OA::irhandle_t)wn);
       root = new OA::ExprTree::MemRefNode(h);
    } else { 
       OA::OpHandle h((OA::irhandle_t)wn);
       root = new OA::ExprTree::OpNode(h);
    }
  }
  //else {
  //  root = Node();
  //}
  tree->addNode(root);
  
  // 3. Create sub trees for each child and link them to the parent
  // node (we know this will never be OPR_BLOCK)
  if (!bypassRecursion) {
    if ( !(OPERATOR_is_leaf(opr) || opr == OPR_STID) ) {
      for (INT kidno = 0; kidno < WN_kid_count(wn); kidno++) {
        WN* kid_wn = WN_kid(wn, kidno);
        OA::OA_ptr<OA::ExprTree::Node> child = createExprTree(tree, kid_wn);
        if (! child.ptrEqual(NULL)) {
          tree->connect(root, child);
        }
      }
    }
  }
  
  return root;
}


#if 0 // eraxxon: save this for possible later use
// createExprTree: Given a tree container 'tree' and 'wn', builds tree
// nodes for wn, adds them to 'tree' and returns the root node of the
// newly created tree nodes
OA::OA_ptr<OA::ExprTree::Node>
Open64IRInterface::createExprTree(OA::OA_ptr<OA::ExprTree::ExprTree> tree, WN* wn)
{
  using namespace OA::ExprTree;

  OA::OA_ptr<ExprTree::Node> root; root = NULL;
  if (!wn) { return root; }
  
  // 1. Sanity checking.  (In the context of expressions, OPR_STID
  // represents the LHS of the assignment.)
  OPERATOR opr = WN_operator(wn);
  if ( !(opr == OPR_STID || OPERATOR_is_call(opr) 
	 || OPERATOR_is_expression(opr)) ) {
    return root;
  }
  
  // 1a. FIXME: For now, eliminate PARM nodes from tree.
  if (opr == OPR_PARM) {
    if (WN_kid_count(wn) == 0) {
      return root;
    } 
    else {
      return createExprTree(tree, WN_kid0(wn));
    }
  }
  
  // 2. Create a parent tree node for the curent WN.  Note that order
  // is important here.  *Note* OPR_ICALL and OPR_VFCALL will be
  // classified as calls instead of mem-refs.
  if (OPERATOR_is_call(opr)) {
    OA::ExprHandle h((OA::irhandle_t)wn);
    root = new ExprTree::CallNode(h);
  }
  else if (opr == OPR_CONST || opr == OPR_INTCONST) {
    OA::ConstValHandle h((OA::irhandle_t)wn);
    root = new ExprTree::ConstValNode(h);
  }
  else if (OPERATOR_has_sym(opr) && ST_class(WN_st(wn)) == CLASS_CONST) {
    OA::ConstSymHandle h((OA::irhandle_t)WN_st(wn));
    root = new ExprTree::ConstSymNode(h);
  }
  else if (opr == OPR_STID || OPERATOR_is_load(opr)
	   || opr == OPR_ARRAY || opr == OPR_ARRSECTION 
	   || opr == OPR_ARRAYEXP) {
    OA::MemRefHandle h((OA::irhandle_t)wn);
    // HACK! ALERT! BK:
    // mfef90 is not distributing the constant values beyond the
    // main procudure to all subroutines.  Until this is fixed in 
    // mfef90, we need to cause all memrefs that refer to the
    // constant named MPI_COMM_WORLD with the constant value 91 (this
    // is the value from the mpif.h file we are using with our 
    // experiment application programs.
    //
    // before HACK, there was just the following line:
    //   root = new ExprTree::MemRefNode(h);
    //
    string strMemRef;
    {
      WN* wn = (WN*)h.hval();
      std::ostringstream oss;
      DumpWNMemRef(wn, oss);
      strMemRef = oss.str();
    }
    string strMWC = "MPI_COMM_WORLD";
    if (strMemRef.compare(0,strMWC.length(),strMWC) == 0) {
      INT64 i64value = (INT64)91;
      WN* wnic = WN_CreateIntconst(OPC_I4INTCONST,i64value);
      OA::ConstValHandle cvh((OA::irhandle_t)wnic);
      root = new ExprTree::ConstValNode(cvh);
    } else {
      root = new ExprTree::MemRefNode(h);
    }
    //
    // end of HACK!

  }
  else /*if ()*/ { 
    // Note: for now we just make everything else an operator
    // is expr, not a const, not a mem-ref (&& not a type conversion)
    OA::OpHandle h((OA::irhandle_t)wn);
    root = new ExprTree::OpNode(h);
  }
  //else {
  //  root = Node();
  //}
  tree->addNode(root);
  
  // 3. Create sub trees for each child and link them to the parent
  // node (we know this will never be OPR_BLOCK)
  if ( !(OPERATOR_is_leaf(opr) || opr == OPR_STID) ) {
    for (INT kidno = 0; kidno < WN_kid_count(wn); kidno++) {
      WN* kid_wn = WN_kid(wn, kidno);
      
      OA::OA_ptr<ExprTree::Node> child = createExprTree(tree, kid_wn);
      tree->connect(root, child);
    }
  }
  
  return root;
}
#endif


// Given an assignment statement --- an EXPR_STMT in the form <target
// = expr> -- return an AssignPairIterator.
OA::OA_ptr<OA::AssignPairIterator> 
Open64IRInterface::findAssignPairs(WN* wn)
{
  using namespace OA::ReachConsts;
  
  OA::OA_ptr<AssignPairList> lst; lst = new AssignPairList;
  OA::OA_ptr<OA::AssignPairIterator> retval;
  
  OPERATOR opr = WN_operator(wn);
  if (OPERATOR_is_store(opr)) {
    // Create the AssignPair and add to the list (Note: STOREs
    // represent lhs mem-refs)
 
    OA::MemRefHandle lhs;

    lhs = (OA::irhandle_t)wn;

    OA::ExprHandle rhs((OA::irhandle_t)WN_kid0(wn));
    lst->push_back(AssignPair(lhs, rhs));
  }
  retval = new Open64AssignPairIterator(lst);
  return retval;
}


// Given a ST of CLASS_CONST, return a ConstValBasicInterface representation.
OA::OA_ptr<OA::ConstValBasicInterface>
Open64IRInterface::getConstValBasicFromST(ST* st)
{
  OA::OA_ptr<OA::ConstValBasicInterface> cvb; cvb = NULL;
  if (!st) { return cvb; }
  
  TCON& tcon = ST_tcon_val(st);
  TYPE_ID mty = TCON_ty(tcon);
  
  //if (MTYPE_is_complex(mty)) { }
  //else if (MTYPE_is_float(mty)) { double x = Targ_To_Host_Float(tcon); }
  if (MTYPE_is_integral(mty)) {
    INT64 val = Targ_To_Host(tcon);
    if (val < INT_MIN || val > INT_MAX) {
      cvb = NULL; // no current representation for this
    } else {
      cvb = new Open64IntegerConstVal((int)val);
    }
  }
  else {
    cvb = NULL; // no current representation for this
  }

  return cvb;
}

bool Open64IRInterface::isPassByReference(WN* opr_parm_wn) 
{
    bool retval;
    assert(opr_parm_wn!=0);

    OA::ExprHandle opr_parm = ((OA::irhandle_t)opr_parm_wn);

    // if this is a call to an undefined function then just return true
    // to be conservatively correct, don't know if the parameter is a
    // reference or not
    OA::ProcHandle callee = getProcHandle( 
                                getSymHandle( sParamToCallMap[opr_parm]));
    if (callee == OA::ProcHandle(0)) {
        return true;
    }

    // get the formal symbol for this actual parameter
    // we stored which call this is associated with mapped
    // to the wn for the opr_parm
    OA::SymHandle formal = getFormalForActual(
                              sProcContext[opr_parm],
                              sParamToCallMap[opr_parm],
                              callee,
                              opr_parm );

    // the symbol table entry for the formal parameter
    setCurrentProcToProcContext(formal);

    // FIXME: this might be overly conservative in C programs
    // because of how isRefParam is implemented
    if (isRefParam(formal)) {
        retval= true;
    } else {
        retval= false;
    }
 
    // set context back to caller
    setCurrentProcToProcContext(opr_parm);
    return retval;
}


/*!
   constant symbols get their strings from the TCON table?
*/
char* Open64IRInterface::createCharStarForST(ST* st)
{
    char* nm = NULL;

    if (ST_class(st) == CLASS_CONST) {
        TCON& tcon = STC_val(st);
        if (TCON_ty(tcon) == MTYPE_STR) {
            STR_IDX idx = TCON_str_idx(tcon);
        } else {
            nm = Targ_Print(NULL, tcon);
        }
    } else { nm = ST_name(st); }

    if (nm==NULL) {
        nm = "<no-symbol>";
    }

    return nm;
}

//---------------------------------------------------------------------------
// Visualize Whirl expressions in a compact way.
//
// This is strictly for debugging. It does not attempt, for example, to
// properly parenthesize expressions, etc.
//---------------------------------------------------------------------------

void
Open64IRInterface::DumpWN(WN* wn, ostream& os)
{
  if (!wn) { os << "NULL"; return; }

  // Printing scope of WN i.e. Name of the procedure 
  // it belongs to
  /*
  PU_Info* origPU = Current_PU_Info;
  if(origPU != NULL) {
     ST_IDX idx = PU_Info_proc_sym(origPU);
     char* procname = ST_name(idx);
     std::cout << std::endl << "ProcName" << procname << std::endl;
  }
  */
  
  OPERATOR opr = WN_operator(wn);
  string op;
  switch (opr) {

  // Leaf operations and memory operations.
  case OPR_LDA:
    // Perhaps strange, but Whirl has the notion of the address of a
    // constant.  The FORTRAN call foo(2) in Whirl is foo(OPR_LDA(2)).
    if (ST_sym_class(WN_st(wn)) == CLASS_CONST) {
      os << Targ_Print(NULL, WN_val(wn));
    } else {
      DumpWNLeaf(wn, os);
    }
    break;
  case OPR_IDNAME:
  case OPR_LDMA:
  case OPR_LDID:
    DumpWNLeaf(wn, os);
    break;
  case OPR_ILOAD:
  case OPR_ILOADX:
    DumpWNMemRefLeaf(wn, os);
    DumpWN(WN_kid0(wn), os);
    break;
    
  case OPR_CONST:
    os << Targ_Print(NULL, WN_val(wn));
    break;
  case OPR_INTCONST:
    os << WN_const_val(wn);
    break;

  case OPR_ISTORE:
  case OPR_ISTOREX:
    DumpWN(WN_kid1(wn), os);
    os << " = ";
    DumpWN(WN_kid0(wn), os);
    break;
  case OPR_STID:
    DumpWNLeaf(wn, os);
    os << " = ";
    DumpWN(WN_kid0(wn), os);
    break;

  // Unary expression operations.
  case OPR_CVT:
  case OPR_CVTL:
  case OPR_TAS:
    os << OPCODE_name(WN_opcode(wn)) << "(";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_PARM:
    if (WN_flag(wn) & WN_PARM_BY_REFERENCE)
      os << "&"; 
    DumpWN(WN_kid0(wn), os);
    break;
  case OPR_ABS:
    os << "ABS(";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_SQRT:
    os << "SQRT(";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_RSQRT:
    os << "RSQRT(";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_RECIP:
    os << "RECIP(";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_PAREN:
    os << "(";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_RND:
    os << "RND(";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_TRUNC:
    os << "TRUNC(";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_CEIL:
    os << "CEIL(";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_FLOOR:
    os << "FLOOR(";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_NEG:
    op = "-";
    goto print_generic_unary;
  case OPR_BNOT:
    op = "~";
    goto print_generic_unary;
  case OPR_LNOT:
    op = "!";
    goto print_generic_unary;
print_generic_unary:
    os << op;
    DumpWN(WN_kid0(wn), os);
    break;

  // Binary expression operations.
  case OPR_ADD:
    op = "+";
    goto print_generic_binary;
  case OPR_SUB:
    op = "-";
    goto print_generic_binary;
  case OPR_MPY:
    op = "*";
    goto print_generic_binary;
  case OPR_DIV:
    op = "/";
    goto print_generic_binary;
  case OPR_MOD:
    os << "MOD(";
    DumpWN(WN_kid0(wn), os);
    os << ",";
    DumpWN(WN_kid1(wn), os);
    os << ")";
    break;
  case OPR_REM:
    op = "%";
    goto print_generic_binary;
  case OPR_EQ:
    op = "==";
    goto print_generic_binary;
  case OPR_NE:
    op = "!=";
    goto print_generic_binary;
  case OPR_GE:
    op = ">=";
    goto print_generic_binary;
  case OPR_LE:
    op = "<=";
    goto print_generic_binary;
  case OPR_GT:
    op = '>';
    goto print_generic_binary;
  case OPR_LT:
    op = '<';
    goto print_generic_binary;
  case OPR_MAX:
    os << "MAX(";
    DumpWN(WN_kid0(wn), os);
    os << ",";
    DumpWN(WN_kid1(wn), os);
    os << ")";
    break;
  case OPR_MIN:
    os << "MIN(";
    DumpWN(WN_kid0(wn), os);
    os << ",";
    DumpWN(WN_kid1(wn), os);
    os << ")";
    break;
  case OPR_SHL:
    op = "<<";
    goto print_generic_binary;
  case OPR_ASHR:
  case OPR_LSHR:
    op = ">>";
    goto print_generic_binary;
  case OPR_LAND:
    op = "&&";
    goto print_generic_binary;
  case OPR_LIOR:
    op = "||";
    goto print_generic_binary;
  case OPR_BAND:
    op = "&";
    goto print_generic_binary;
  case OPR_BIOR:
    op = "|";
    goto print_generic_binary;
  case OPR_BXOR:
    op = "^";
print_generic_binary:
    DumpWN(WN_kid0(wn), os);
    os << op;
    DumpWN(WN_kid1(wn), os);
    break;

  // Ternary operations.
  case OPR_SELECT:
    DumpWN(WN_kid0(wn), os);
    os << " ? "; 
    DumpWN(WN_kid1(wn), os);
    os << " : "; 
    DumpWN(WN_kid2(wn), os);
    break;
  case OPR_MADD:
    os << "(";
    DumpWN(WN_kid0(wn), os);
    os << "*";
    DumpWN(WN_kid1(wn), os);
    os << ")+";
    DumpWN(WN_kid2(wn), os);
    break;
  case OPR_MSUB:
    os << "(";
    DumpWN(WN_kid0(wn), os);
    os << "*";
    DumpWN(WN_kid1(wn), os);
    os << ")-";
    DumpWN(WN_kid2(wn), os);
    break;
  case OPR_NMADD:
    os << "-((";
    DumpWN(WN_kid0(wn), os);
    os << "*";
    DumpWN(WN_kid1(wn), os);
    os << ")+";
    DumpWN(WN_kid2(wn), os);
    os << ")";
    break;
  case OPR_NMSUB:
    os << "-((";
    DumpWN(WN_kid0(wn), os);
    os << "*";
    DumpWN(WN_kid1(wn), os);
    os << ")-";
    DumpWN(WN_kid2(wn), os);
    os << ")";
    break;

  // N-ary operations.
  case OPR_ARRAY: {
    int ndims = WN_kid_count(wn) >> 1;
    DumpWN(WN_kid0(wn), os);
    os << "(";
    for (int i = 0; i < ndims; i++) {
      DumpWN(WN_kid(wn, i+ndims+1), os);
      if (i < ndims-1) 
        os << ",";
    }
    os << ")";
    break;
  }
  case OPR_TRIPLET: // Output as LB:UB:STRIDE
    DumpWN(WN_kid0(wn), os);
    os << ":";
    DumpWN(WN_kid2(wn), os);
    os << ":";
    DumpWN(WN_kid1(wn), os);
    break; 
  case OPR_ARRAYEXP:
    DumpWN(WN_kid0(wn), os);
    break; 
  case OPR_ARRSECTION: {
    int ndims = WN_kid_count(wn) >> 1;
    DumpWN(WN_kid0(wn), os);
    os << "(";
    for (int i = 0; i < ndims; i++) {
      DumpWN(WN_kid(wn, i+ndims+1), os);
      if (i < ndims-1) 
        os << ",";
    }
    os << ")";
    break;
  }

  // Control flow constructs
  case OPR_DO_LOOP:
    // In OA, the DO_LOOP node represents the loop condition.
    os << "do_loop (";
    DumpWN(WN_end(wn), os);
    os << ")"; 
    break;
  case OPR_DO_WHILE:
    // In OA, the DO_WHILE node represents the loop condition.
    os << "do_while (";
    DumpWN(WN_while_test(wn), os);
    os << ")"; 
    break;
  case OPR_WHILE_DO:
    // In OA, the WHILE_DO node represents the loop condition.
    os << "while_do ("; 
    DumpWN(WN_while_test(wn), os);
    os << ")";
    break;
  case OPR_IF:
    // In OA, the IF node represents the condition.
    os << "if ("; 
    DumpWN(WN_if_test(wn), os);
    os << ")"; 
    break;
  case OPR_TRUEBR:
    // In OA, the TRUEBR node represents the condition.
    os << "truebr ("; 
    DumpWN(WN_kid0(wn), os);
    os << "), L" << WN_label_number(wn); 
    break;
  case OPR_FALSEBR:
    // In OA, the FALSEBR node represents the condition.
    os << "falsebr (";
    DumpWN(WN_kid0(wn), os);
    os << "), L" << WN_label_number(wn); 
    break;
  case OPR_RETURN:
    os << "return";
    break;
  case OPR_RETURN_VAL:
    os << "return (";
    DumpWN(WN_kid0(wn), os);
    os << ")";
    break;
  case OPR_CALL:
    os << createCharStarForST(WN_st (wn)) << "(";
    for (int kid = 0; kid < WN_kid_count(wn); kid++) {
      DumpWN(WN_kid(wn, kid), os);
      if (kid < WN_kid_count(wn)-1)
        os << ", ";
    } // for kids
    os << ")";
    break;
  case OPR_INTRINSIC_CALL:
  case OPR_INTRINSIC_OP:
    os << INTRINSIC_name ((INTRINSIC) WN_intrinsic (wn)) << "(";
    for (int kid = 0; kid < WN_kid_count(wn); kid++) {
      DumpWN(WN_kid(wn, kid), os);
      if (kid < WN_kid_count(wn)-1)
        os << ", ";
    } // for kids
    os << ")";
    break;
  default:
    fdump_wn(stdout, wn); // or fdump_tree()
    break;
  }
}


void 
Open64IRInterface::DumpWNLeaf(WN* wn, ostream& os) 
{
  if (!wn) { return; }
  DumpWNMemRefLeaf(wn, os);
}


// DumpWNMemRef: Dump a mem-ref in a form that allows a hash to be
// done on the output string.  (This implies that WHIRL operators must
// not be part of the output.)  Note that STOREs represent the
// left-hand-side memory-ref.  This function is similar to DumpWN but
// contains special handling for STORES.
void 
Open64IRInterface::DumpWNMemRef(WN* wn, ostream& os)
{
  if (!wn) { return; }
  
  OPERATOR opr = WN_operator(wn);
  if (OPERATOR_is_store(opr)) {
    if (WN_kid_count(wn) > 1) {
      DumpWN(WN_kid1(wn), os); // left-hand-side
    }
    else {
      DumpWNMemRefLeaf(wn, os);
    }
  } 
  else {
    DumpWN(wn, os);
  }
}


void 
Open64IRInterface::DumpWNMemRefLeaf(WN* wn, ostream& os) 
{
  if (!wn) { return; }

  OPERATOR opr = WN_operator(wn);
  if (OPERATOR_has_sym(opr)) {
    os << createCharStarForST(WN_st(wn)) << ":";
  } 
  if (OPERATOR_has_offset(opr)) {
    os << WN_offset(wn) << ":";
  }
  if (OPERATOR_has_1ty(opr)) {
    os << TY_name(WN_ty(wn));
  }
}


/*! creates a mapping of call symbol handles to the associated proc handle
 */
void Open64IRInterface::initCallSymToProcMap(Open64IRProcIterator &procIter)
{
    // create an instance of Open64IRInterface so that we have access
    // to all methods
    Open64IRInterface tempIR;
    
    // Iterate over procedures in program
    OA::ProcHandle proc;
    for (procIter.reset(); procIter.isValid(); procIter++) {
        proc = procIter.current();
        OA::SymHandle sym = tempIR.getSymHandle(proc);
        Open64IRInterface::sCallSymToProc[sym] = proc;
    }
}

/*! creates a mapping of procedure handles to the set of symbols
    referenced in that procedure
    // get a set of all referenced symbols in this procedure
    // Using this to approximate what is visible in F90 because Open64
    // module scoping is messed up and all module variables are put
    // in the global scope
 */
void Open64IRInterface::initProcToSymRefSetMap(Open64IRProcIterator &procIter)
{
    // create an instance of Open64IRInterface so that we have access
    // to all methods
    Open64IRInterface tempIR;
    
    // Iterate over procedures in program
    OA::ProcHandle proc;
    for (procIter.reset(); procIter.isValid(); procIter++) {
        proc = procIter.current();
        OA::OA_ptr<OA::IRSymIterator> symIter = tempIR.getRefSymIterator(proc);
        std::set<OA::SymHandle> refSet;
        for ( ; symIter->isValid(); (*symIter)++ ) {
            sProcToSymRefSetMap[proc].insert(symIter->current());
        }
    }
}


	
/*! 
   Determines the current context for given handle and makes sure that
   Open64 is properly set up to answer the query on the handle
*/
void Open64IRInterface::setCurrentProcToProcContext(OA::IRHandle h) 
{
    if (h.hval()!=0) {
      PU_Info *pu = (PU_Info*)sProcContext[h].hval();
      assert(pu!=NULL);
      // have to check what Open64 thinks is current context
      if ( Current_PU_Info  != pu && pu != NULL ) {
        PU_SetGlobalState(pu);
      }
    }
}

OA::ProcHandle Open64IRInterface::getCurrentProcContext()
{
    return (OA::irhandle_t)Current_PU_Info;
}

void Open64IRInterface::setCurrentProcContext(OA::ProcHandle proc)
{
    PU_Info *pu = (PU_Info*)proc.hval();
    // have to check what Open64 thinks is current context
    if ( Current_PU_Info  != pu && pu != NULL ) {
        PU_SetGlobalState(pu);
    }
}

/*! Helper class to initProcContext.  Finds all handles within
    an expression and maps them to the given procedure context.
*/
/*
class InitContextVisitor : public OA::ExprTreeVisitor {
  public:
    InitContextVisitor(OA::ProcHandle proc) : mProc(proc) {}
    ~InitContextVisitor() {}

    void visitExprTreeBefore(OA::ExprTree&) {}
    void visitExprTreeAfter(OA::ExprTree&) {}
    
    //---------------------------------------
    // method for each ExprTree::Node subclass
    //---------------------------------------
    // default base class so that visitors can handle unknown
    // node sub-classes in a generic fashion
    void visitNode(OA::ExprTree::Node&) {}

    void visitOpNode(OA::ExprTree::OpNode& n)
    {
        Open64IRInterface::sProcContext[n.getHandle()] = mProc;

        // visit each child
        OA::OA_ptr<OA::ExprTree::Node> cetNodePtr;
        OA::ExprTree::ChildNodesIterator cNodesIter(n);
        for ( ; cNodesIter.isValid(); cNodesIter++ ) {
            cetNodePtr = cNodesIter.current();
            cetNodePtr->acceptVisitor(*this);
        }

    }

    void visitCallNode(OA::ExprTree::CallNode& n)
    {
        // do nothing because have other routines that saw all calls
        // in a statement
    }

    void visitMemRefNode(OA::ExprTree::MemRefNode& n)
    {
        // do nothing because have other routines that saw all mem refs
        // in a statement
    }

    void visitConstSymNode(OA::ExprTree::ConstSymNode& n)
    {
        Open64IRInterface::sProcContext[n.getHandle()] = mProc;
    }

    void visitConstValNode(OA::ExprTree::ConstValNode& n)
    {
        Open64IRInterface::sProcContext[n.getHandle()] = mProc;
    }

  private:
    OA::ProcHandle mProc;
};
*/


/*! only call if the symbol is in a module or a common block
*/
fully_qualified_name Open64IRInterface::create_fqn(OA::SymHandle sym)
{
    fully_qualified_name retval; 
    static const char* aDummyModuleName("Dummy_module");

    ST* st = (ST*)sym.hval();
    assert(Stab_Is_Based_At_Common_Block(st) || Stab_Is_In_Module(st));
    
    if (Stab_Is_Based_At_Common_Block(st)) {
        ST* tempst = st;
        while (!Stab_Is_Common_Block(tempst)) {
            tempst = ST_base(tempst);
        }
        ST* base_st = tempst;

        // make a pair for fully-qualified name
        retval = fully_qualified_name(createCharStarForST(st), createCharStarForST(base_st));
        //retval = (fully_qualified_name)std::make_pair(ST_name(st), 
        //                                              ST_name(base_st));

    // this is true if this symbol is part of module
    } 
    else if (Stab_Is_In_Module(st) ) {
        ST* tempst = st;
// FIXME: can't find the module name
//         while (!Stab_Is_Module(tempst)) {
// 	  // here we try to get down to the module name
// 	  tempst = ST_base(tempst);
//         }
//        ST* base_st = tempst;
     // make a pair for fully-qualified name
	// consisting of the symbol and the module name
	// FIXME: find the right module name
        //retval = (fully_qualified_name)std::make_pair(ST_name(st),
        //                                              aDummyModuleName);
        retval = fully_qualified_name(createCharStarForST(st), aDummyModuleName);
    }

    return retval;
}

/*! 
    maps all handles to a procedure handle that indicates their context
    assumes that all handles except for SymHandle's and ProcHandle's
    are only valid in one procedure context.
*/
void Open64IRInterface::initProcContext(PU_Info* pu_forest, 
                                        Open64IRProcIterator &procIter)
{
    // create an instance of Open64IRInterface so that we have access
    // to all methods
    Open64IRInterface tempIR;
    
    // Indicate that context has been initialized
    sContextInit = true;
    
    // should not be setting up context on more than one program
    assert(sProgContext==NULL || sProgContext==pu_forest);
    sProgContext = pu_forest;

    // Iterate over procedures in program
    bool globalSymsVisitFlag = false;
    OA::ProcHandle proc;
    procIter.reset();
    for (; procIter.isValid(); procIter++) {
        proc = procIter.current();
        PU_Info* pu = (PU_Info*)proc.hval();
        WN *wn_pu = PU_Info_tree_ptr(pu);
	
        // 1. Add Whirl symbols to map

        // NOTE: Do not use tempIR.getVisibleSymIterator(proc) or it
        // will kill performance.  Instead just get symbols at the
        // global level once and for each procedure just get symbols
        // on all levels higher than global
        std::list<ST*> symlist;
        int stopLevel;
        if ( globalSymsVisitFlag==false ) {
            stopLevel = GLOBAL_SYMTAB;
            globalSymsVisitFlag = true;
        } else { 
            stopLevel = GLOBAL_SYMTAB+1;
        }
        // inserts all symbols at corresponding symbol table levels
        // into symlist
        for (SYMTAB_IDX lvl = CURRENT_SYMTAB; lvl >= stopLevel; --lvl) {
            For_all(St_Table, lvl, insert_ST(symlist));
        }
        std::list<ST*>::iterator symIter;
        for (symIter = symlist.begin(); symIter!=symlist.end(); symIter++ ) { 
            ST* st = *symIter;
            OA::SymHandle sym((OA::irhandle_t)st);

            // set the procedure context for the symbol
            sProcContext[sym] = proc;
            if (debug) {
                std::cout << "symbol = " << createCharStarForST(st) 
                          << ", sProcContext[" << sym.hval() << "] = " 
                          << proc.hval() << std::endl;
            }

            // store the string for the symbol
            const char* nm = createCharStarForST(st);
            sSymToVarStringMap[sym] = nm;

            // store symbols based on fully qualified name as well
            // if they are module or common block variables
            if (Stab_Is_Based_At_Common_Block(st) || Stab_Is_In_Module(st)) 
            {
                fully_qualified_name fqn = create_fqn(sym);
                sGlobalVarMap[fqn].insert(sym);
                sSymToFQNMap[sym] = fqn;
                if (debug) {
                    std::cout << "create_fqn(" << createCharStarForST(st) << ") = "
                              << fqn.mVar << ", " << fqn.mContext << std::endl;
                    std::cout << "\tsym = " << tempIR.toString(sym)
                              << ", hval= " << sym.hval()
                              << ", st = " << (unsigned int)st << std::endl;
                    std::cout << "\tproc = " << tempIR.toString(proc)
                              << ", hval= " << proc.hval();
                }
            }
        }

        // 2. Add Whirl AST nodes to map
        WN_TREE_CONTAINER<PRE_ORDER> wtree(wn_pu);
        WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
        for (it = wtree.begin(); it != wtree.end(); ++it) {
            WN* curWN = it.Wn();
            OA::IRHandle h((OA::irhandle_t)curWN);
            sProcContext[h] = proc;
            if (debug) {
                std::cout << "sProcContext[" << h.hval() << "] = " 
                          << proc.hval() << std::endl;
            }
        }
    }

    // the last procedure is the one that is the currentProc context
    //sCurrentProc = (PU_Info*)proc.hval();
}
