// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Open64IRInterface.cpp,v 1.11 2005/08/10 18:05:58 utke Exp $

/*! \file
  
  \brief Implementation of abstract OA interfaces for Open64/WHIRL

  \authors Nathan Tallent, Michelle Strout
  \version $Id: Open64IRInterface.cpp,v 1.11 2005/08/10 18:05:58 utke Exp $

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

#include <include/Open64BasicTypes.h>
#include "ir_reader.h" // for fdump_wn()

//*************************** User Include Files ****************************

#include "Open64IRInterface.hpp"
#include "SymTab.h"
#include "wn_attr.h"
#include "stab_attr.h"

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

std::map<OA::SymHandle,std::string> Open64IRInterface::sSymToVarStringMap;

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

  // Add calls to call list
  if (OPERATOR_is_call(opr)) {
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

/*! this method sets up sMemRef2StmtMap, sStmt2MemRefSet?, and 
    sMemRef2mreSetMap?
    Is only way to get MemRefHandle's therefore no queries should
    be logically made on MemRefHandle's before one of these
    iterators has been requested.
*/
void 
Open64IRMemRefIterator::create(OA::StmtHandle stmt)
{
  Open64IRInterface::setCurrentProcToProcContext(stmt);

  // NOTE: this could be a little more efficient
  WN* wn = (WN*)stmt.hval();
  if (!wn) { return; }

  // if haven't already determined the set of memrefs for this stmt
  // then do so by finding all the top memory references and then
  // initializing the mapping of MemRefHandle's to a set of MemRefExprs,
  // and based off that map get all the MemRefHandle's
  if (Open64IRInterface::sStmt2allMemRefsMap[stmt].empty() ) {
  
    // get all the top memory references
    list<WN*>* topMemRefs = findTopMemRefs(wn);
    for (list<WN*>::iterator it = topMemRefs->begin(); 
         it != topMemRefs->end(); ++it)
    {
      WN* memrefWN = (*it);

      // get all the sub memory references including top memory reference
      list<OA::MemRefHandle>* subMemRefList 
        = findAllMemRefsAndMapToMemRefExprs(memrefWN);

      // put those memory references in the static mapping of statements to 
      // the set of all memory references
      list<OA::MemRefHandle>::iterator mrIter;
      for (mrIter=subMemRefList->begin(); mrIter!=subMemRefList->end(); 
           mrIter++)
      {
          Open64IRInterface::sStmt2allMemRefsMap[stmt].insert(*mrIter);
          Open64IRInterface::sMemRef2StmtMap[*mrIter] = stmt;
      }
    }
  }

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
  oss << wn;
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
  oss << h.hval();
  return oss.str();
}

std::string 
Open64IRInterface::toString(const OA::ConstValHandle h) 
{
  setCurrentProcToProcContext(h);
  std::ostringstream oss;
  oss << h.hval();
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
Open64IRInterface::getCallsiteParams(OA::ExprHandle h) {
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  OA::OA_ptr<OA::IRCallsiteParamIterator> retval;
  retval = new Open64IRCallsiteParamIterator(wn);
  return retval;
}

bool Open64IRInterface::isRefParam(OA::SymHandle sym)
{
  setCurrentProcToProcContext(sym);
  // "X"  inout: C_VAR S_FORMAL_REF (flg 0x80 0x0)
  // "Y"  inout: C_VAR S_FORMAL_REF (flg 0x80 0x0)
  // "AA" in   : C_VAR S_FORMAL_REF (flg 0x80 0x20[in])
  // "BB" out  : C_VAR S_FORMAL_REF (flg 0x80 0x40[out])

  ST* st = (ST*)sym.hval();
  ST_SCLASS sclass = ST_sclass(st);
  
  if (ST_is_intent_out_argument(st)) {
    return true; // parameter: intent(out)
  }
  else if (ST_is_intent_in_argument(st)) {
    return false; // parameter: intent(in)
  }
  else if (sclass == SCLASS_FORMAL_REF) {
    return true; // pass-by-ref parameter
  }
  else if (sclass == SCLASS_FORMAL) {
    return true; // may be pass-by-ref in the source language
  }
  else {
    return false; // not a parameter at all
  }
}
               
//! return the formal parameter that an actual parameter is associated with.
OA::SymHandle 
Open64IRInterface::getFormalForActual(OA::ProcHandle caller, 
                                      OA::ExprHandle call, 
                                      OA::ProcHandle callee, 
                                      OA::ExprHandle param)
{
  // Setup context for caller
  setCurrentProcToProcContext(call);

  PU_Info* callerPU = (PU_Info*)caller.hval();
  PU_Info* calleePU = (PU_Info*)callee.hval();
  WN* callWN = (WN*)call.hval();
  WN* parmWN = (WN*)param.hval();
  WN *wn_pu, *formalWN;
  int numParamsCallee;
  
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
  if (parmIdx < 0) {
    goto fini;
  }
  
  // Given the index of the actual parameter, find the formal parameter
  PU_SetGlobalState(calleePU);
  
  wn_pu = PU_Info_tree_ptr(calleePU);
  numParamsCallee = WN_num_formals(wn_pu);  
  assert(numParamsCallee == numParamsCaller);
  formalWN = WN_formal(wn_pu, parmIdx);
  formalST = WN_st(formalWN);

 fini:  
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
  OA::OA_ptr<OA::MemRefHandleIterator> retval;
  retval = new Open64IRMemRefIterator(h);
  return retval;
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

//-------------------------------------------------------------------------
// ActivityIRInterface
//-------------------------------------------------------------------------
  
//! Return an iterator over all independent locations for given proc
OA::OA_ptr<OA::LocIterator> 
Open64IRInterface::getIndepLocIter(OA::ProcHandle h)
{
  PU_Info* pu = (PU_Info*)h.hval();
  currentProc(h);

  // Get independent variables
  OA::OA_ptr<OA::LocSet> indepSet;
  indepSet = new OA::LocSet;
  
  WN* pragmaBlk = WN_func_pragmas(PU_Info_tree_ptr(pu));
  for (WN* wn = WN_first(pragmaBlk); wn != NULL; wn = WN_next(wn)) {
    if (WN_operator(wn) != OPR_PRAGMA) {
      continue; 
    }
    
    WN_PRAGMA_ID prag = (WN_PRAGMA_ID)WN_pragma(wn);
    if (prag == WN_PRAGMA_OPENAD_INDEPENDENT) {
      ST* st = WN_st(wn);
      OA::OA_ptr<OA::Location> loc;
      loc = getLocation((OA::irhandle_t)pu, (OA::irhandle_t)st);
      indepSet->insert(loc);
    }
  }

  // if set is empty then none were specified for this procedure
  // so must put UknownLoc in set
  /*
  if (indepSet->empty()) {
    OA::OA_ptr<OA::Location> unknownLoc; 
    unknownLoc = new OA::UnknownLoc;
    indepSet->insert(unknownLoc);
  }
*/
  OA::OA_ptr<OA::LocSetIterator> indepIter;
  indepIter = new OA::LocSetIterator(indepSet);
  return indepIter;
}
  
//! Return an iterator over all dependent locations for given proc
OA::OA_ptr<OA::LocIterator> 
Open64IRInterface::getDepLocIter(OA::ProcHandle h)
{
  PU_Info* pu = (PU_Info*)h.hval();
  currentProc(h);

  // Get dependent variables
  OA::OA_ptr<OA::LocSet> depSet;
  depSet = new OA::LocSet;
  
  WN* pragmaBlk = WN_func_pragmas(PU_Info_tree_ptr(pu));
  for (WN* wn = WN_first(pragmaBlk); wn != NULL; wn = WN_next(wn)) {
    if (WN_operator(wn) != OPR_PRAGMA) {
      continue; 
    }
    
    WN_PRAGMA_ID prag = (WN_PRAGMA_ID)WN_pragma(wn);
    
    if (prag == WN_PRAGMA_OPENAD_DEPENDENT) {
      ST* st = WN_st(wn);
      OA::OA_ptr<OA::Location> loc;
      loc = getLocation((OA::irhandle_t)pu, (OA::irhandle_t)st);
      depSet->insert(loc);
    }
  }

  OA::OA_ptr<OA::LocSetIterator> depIter;
  depIter = new OA::LocSetIterator(depSet);
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
  if (OPERATOR_is_store(opr)) { // cf. findExprStmtPairs
    return OA::ReachConsts::EXPR_STMT;
  } else {
    return OA::ReachConsts::ANY_STMT;
  }
}

OA::OA_ptr<OA::ExprStmtPairIterator> 
Open64IRInterface::getExprStmtPairIterator(OA::StmtHandle h)
{ 
  setCurrentProcToProcContext(h);
  WN* wn = (WN*)h.hval();
  return findExprStmtPairs(wn);
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

//---------------------------------------------------------------------------
// LocationIRShortCircuit
//---------------------------------------------------------------------------

//! For the given symbol create a Location that indicates statically
//! overlapping locations and information about whether the location
//! is local or not, local means visible in only this procedure
//! FIXME: does Fortran90 allow nested procedures?  if so then
//! variables visible to a nested procedure should not be labeled local
OA::OA_ptr<OA::Location> 
Open64IRInterface::getLocation(OA::ProcHandle p, OA::SymHandle s)
{
    setCurrentProcToProcContext(s);
    bool isLocal, isUnique;
    bool hasNestedProc = (PU_Info_child(Current_PU_Info) != NULL);
    OA::OA_ptr<OA::NamedLoc> retval;

    if (s!=OA::SymHandle(0)) {
      isLocal = (!hasNestedProc) && (ST_level((ST*)s.hval()) == CURRENT_SYMTAB);
      isUnique = isLocal;

      retval = new OA::NamedLoc(s, isLocal);
      
      // if it is a common block variable then need to make sure the same var
      // name within the same common block indicates the other symbol handles
      // for that same var name and common block that fully overlap
      ST* st = (ST*)s.hval();
      if (Stab_Is_Based_At_Common_Block(st) || Stab_Is_In_Module(st)) 
      {
          fully_qualified_name fqn = create_fqn(s);
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

    } else {
      retval = NULL;
    }
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
  }
}


//***************************************************************************
// Helpers
//***************************************************************************

// NOTE: Could be relocated to a more general library

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
      return createExprTree(tree, WN_kid0(wn));
    }
  }
  
  // 2. Create a parent tree node for the curent WN.  Note that order
  // is important here.  *Note* OPR_ICALL and OPR_VFCALL will be
  // classified as calls instead of mem-refs.
  bool bypassRecursion = false;
  if (OPERATOR_is_call(opr)) {
    OA::ExprHandle h((OA::irhandle_t)wn);
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
      if (opr == OPR_ILOAD && WN_operator(WN_kid0(wn)) == OPR_ARRAY) {
	h = (OA::irhandle_t)WN_kid0(wn);
      }
      root = new OA::ExprTree::MemRefNode(h);
      bypassRecursion = true; // MemRefNodes are leaves
    }
    //
    // end of HACK!
  }
  else /*if ()*/ { 
    // Note: for now we just make everything else an operator
    // is expr, not a const, not a mem-ref (&& not a type conversion)
    OA::OpHandle h((OA::irhandle_t)wn);
    root = new OA::ExprTree::OpNode(h);
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
// = expr> -- return an ExprStmtPairIterator.
OA::OA_ptr<OA::ExprStmtPairIterator> 
Open64IRInterface::findExprStmtPairs(WN* wn)
{
  using namespace OA::ReachConsts;
  
  OA::OA_ptr<ExprStmtPairList> lst; lst = new ExprStmtPairList;
  OA::OA_ptr<OA::ExprStmtPairIterator> retval;
  
  OPERATOR opr = WN_operator(wn);
  if (OPERATOR_is_store(opr)) {
    // Create the ExprStmtPair and add to the list (Note: STOREs
    // represent lhs mem-refs)
 
    OA::MemRefHandle lhs;

    // special case for array references
    if (opr == OPR_ISTORE && WN_operator(WN_kid1(wn)) == OPR_ARRAY) {
      lhs = (OA::irhandle_t)WN_kid1(wn);
    } else {
      lhs = (OA::irhandle_t)wn;
    }
    OA::ExprHandle rhs((OA::irhandle_t)WN_kid0(wn));
    lst->push_back(ExprStmtPair(lhs, rhs));
  }
  retval = new Open64ExprStmtPairIterator(lst);
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


// findTopMemRefs: Given WHIRL statements (including control flow
// statements representing embedded expressions, but not statements),
// recursively find the top memory-references in the statement.  Note: Memory
// references will generally be WHIRL expressions; however STORES --
// WHIRL *statements* -- are returned to represent a left-hand-side
// reference; and indirect CALLS are returned to represent a function
// pointer reference.
list<WN*>*
Open64IRMemRefIterator::findTopMemRefs(WN* wn)
{
  list<WN*>* topMemRefs = new list<WN*>;
  findTopMemRefs(wn, *topMemRefs);
  return topMemRefs;
}


void 
Open64IRMemRefIterator::findTopMemRefs(WN* wn, list<WN*>& topMemRefs)
{
  // Base case
  if (!wn) { return; }
  
  // Base case
  OPERATOR opr = WN_operator(wn);
  switch (opr) {
    // NOTE: MLOAD, MSTORE
    
    case OPR_LDA:
    case OPR_LDMA:
    case OPR_LDID:
    case OPR_LDBITS: 
    case OPR_ILOAD:
    case OPR_ILOADX:
    case OPR_ARRAY:
    case OPR_ARRSECTION: 
    case OPR_ARRAYEXP:
      topMemRefs.push_back(wn);
      return;

    case OPR_ICALL:
    case OPR_VFCALL:
      topMemRefs.push_back(wn); // represents function reference
      break; // recur on parameters (kids 0 ... n-2) below
      
    // Special base and recursive case
    case OPR_STID: 
    case OPR_STBITS:
    case OPR_ISTORE:
    case OPR_ISTOREX:
    case OPR_ISTBITS:
      topMemRefs.push_back(wn); // represents LHS
      findTopMemRefs(WN_kid0(wn), topMemRefs); // recur on RHS
      return;
      
    case OPR_BLOCK:
    case OPR_REGION:
      return; // Do not recur into BLOCKs

    default:
      break; // fallthrough -- examine innards of control flow statements
  }

  // General recursive case
  INT kid_beg = 0;
  INT kid_end = WN_kid_count(wn) - 1;
    
  // Special case: examine only condition of control flow statements
  if (kid_end >= 0 && (OPERATOR_is_scf(opr) || OPERATOR_is_non_scf(opr))) {
    if (opr == OPR_DO_LOOP) {
      kid_beg = kid_end = 2; // loop test expression
    }
    else {
      kid_end = 0; // condition expression
    }
  }
  if (opr == OPR_ICALL || opr == OPR_VFCALL) {
    kid_end--; // kid n-2
  }
  
  for (INT kidno = kid_beg; kidno <= kid_end; ++kidno) {
    WN* kid = WN_kid(wn, kidno);
    findTopMemRefs(kid, topMemRefs);
  }
}


/*! Given a mem-ref, find all mem-ref-exprs and sub mem-refs
    and return a list of them, also maps MemRefHandle's to a set of MemRefExpr's
    describing them for OA.
*/
list<OA::MemRefHandle>*
Open64IRMemRefIterator::findAllMemRefsAndMapToMemRefExprs(WN* wn)
{
  list<OA::MemRefHandle>* memRefs;
  memRefs = new list<OA::MemRefHandle>;
  findAllMemRefsAndMapToMemRefExprs(wn, *memRefs, 0, 0);
  return memRefs;
}


/*! Given a memory-reference WN, find all MemRefHandles
    contained within and place them in 'memRefs'.  
    Also map each MemRefHandle to a set of MemRefExprs in sMemRef2mreSetMap.
    Returns the number of dereferences within the mem-ref and the location block
    used within the top-most mem-ref-expr of the mem-ref.  Outside
    callers of this routine should pass a recursion level 'lvl' of 0
    and flags 'flags' of 0.

    Note: The returned information is consumed by recursive calls and
    will not be of interest to others.  The returned information
    should be *copied* if it is to be used.)
*/
list<Open64IRMemRefIterator::MemRefExprInfo>
Open64IRMemRefIterator::findAllMemRefsAndMapToMemRefExprs(WN* wn, 
                                  list<OA::MemRefHandle>& memRefs,
	                          unsigned lvl, unsigned flags)
{
  Language = LANG_F90; // FIXME: Open64's global var Language isn't set

  enum { 
    flags_NONE              = 0x00000000,
    flags_EXPECT_ARRAY_BASE = 0x00000001, // passed down the call stack
    flags_EXPECT_FUNC_BASE  = 0x00000002, // passed down the call stack

    // FIXME: come up with a better name
    flags_STORE_PARENT     = 0x00000004  // passed down the call stack
  };

  using namespace OA;

  bool isFortran = (Language == LANG_F77 || Language == LANG_F90);
  bool isMemRefExprXXX = true;
  
  // A list of mem-ref infos, *some* of which correspond to
  // mem-ref-handles added to 'memRefs' for this WHIRL node.
  list<MemRefExprInfo> curMemRefExprInfos;  
  
  // -------------------------------------------------------
  // 0. Special base cases
  // -------------------------------------------------------
  if (!wn) { return curMemRefExprInfos; }
  
  OPERATOR opr = WN_operator(wn);
  
  // must never see within a WHIRL memory reference (cannot handle recursion)
  if (opr == OPR_BLOCK) { return curMemRefExprInfos; } 
  
  // -------------------------------------------------------
  // 1. General recursive case
  // -------------------------------------------------------

  // Find all mem-ref-expr within the current mem-ref, saving the
  // returned mem-ref-expr if they are related to the mem-ref-expr for
  // mem-ref.  Set flags to pass information about the current
  // surrounding context.
  list<MemRefExprInfo> childInfos;
  
  if (OPERATOR_is_store(opr)) {
    if (WN_kid_count(wn) >= 2) {
      unsigned mylvl = lvl + 1;
      if (opr == OPR_ISTORE && WN_operator(WN_kid1(wn)) == OPR_ARRAY) {
	mylvl = lvl;
	flags |= flags_STORE_PARENT;
	isMemRefExprXXX = false; // use info from ARRAY
      }    
      childInfos = findAllMemRefsAndMapToMemRefExprs(WN_kid1(wn), memRefs, mylvl, flags);
    }
  } 
  else if (OPERATOR_is_load(opr)) {
    if (WN_kid_count(wn) >= 1) {
      unsigned mylvl = lvl + 1;
      if (opr == OPR_ILOAD && WN_operator(WN_kid0(wn)) == OPR_ARRAY) {
	mylvl = lvl;
	isMemRefExprXXX = false; // use info from ARRAY
      }
      childInfos = findAllMemRefsAndMapToMemRefExprs(WN_kid0(wn), memRefs, mylvl, flags);
    }
  } 
  else {
    
    bool kidInfosUsedForCurrentMemRefExpr = false;
    bool kidsAreDistinctExpr = false;
    INT kid_end = WN_kid_count(wn) - 1;
    INT kid_beg = kid_end + 1; // by default do not examine kids
    
    switch(opr) {
      // Arrays: we want the return value when recuring on the array
      // reference, but do not care about it for the index expressions.
      // We do not even recur on dimension information.
      case OPR_ARRAY: // recur on array indices
      case OPR_ARRSECTION: {
        flags |= flags_EXPECT_ARRAY_BASE;
        childInfos = findAllMemRefsAndMapToMemRefExprs(WN_kid0(wn), memRefs, lvl + 1, flags);

	    kidsAreDistinctExpr = true; // index expressions are distinct
        INT dim = kid_end / 2;
        kid_beg = dim + 1; // index expr are dim+1 ... 2*dim
        break;
      }
      case OPR_ARRAYEXP: {
        childInfos = findAllMemRefsAndMapToMemRefExprs(WN_kid0(wn), memRefs, lvl + 1, flags);
	break;
      }
	
      // Calls (indirect): recur on the function pointer expression
      case OPR_ICALL:
      case OPR_VFCALL: { // recur on kid n-1
	flags |= flags_EXPECT_FUNC_BASE;
	int k = WN_kid_count(wn) - 1;
	childInfos = 
	  findAllMemRefsAndMapToMemRefExprs(WN_kid(wn, k), memRefs, lvl + 1, flags);
	break;
      }
	
    default:
      // We need to recur on children and use child mem-expr. E.g., 
      //  I4I4ILOAD 0 T<4,.predef_I4,4> T<41,anon_ptr.,8> <-- top mem ref WN
      //   U8MIN                                          <-- current WN
      //    U8U8ILOAD 0 T<41,anon_ptr.,8> T<42,anon_ptr.,8>
      //     U8U8LDID 0 <2,6,q> T<42,anon_ptr.,8>
      //    U8U8LDID 0 <2,5,r> T<41,anon_ptr.,8>
      kid_beg = 0;
      kidInfosUsedForCurrentMemRefExpr = true;
      break;
    }


    unsigned kid_lvl = lvl + 1;
    unsigned kid_flags = flags;
    if (kidsAreDistinctExpr) { // expect completely distinct expressions
      kid_lvl = 0;   // reset level 
      kid_flags = 0; // reset flags
    }
    
    for (INT kidno = kid_beg; kidno <= kid_end; ++kidno) {
      WN* kid = WN_kid(wn, kidno);
      list<MemRefExprInfo> infos = 
	findAllMemRefsAndMapToMemRefExprs(kid, memRefs, kid_lvl, kid_flags);
      if (kidInfosUsedForCurrentMemRefExpr) {
	childInfos.splice(childInfos.end(), infos);
      }
    }    
  }
  
  // By default, we ensure a null MemRefExprInfo exists
  if (childInfos.size() == 0) {
    childInfos.push_back(MemRefExprInfo(0, OA::SymHandle(0)));
  }
  
  // -------------------------------------------------------
  // 2. General base case 
  // -------------------------------------------------------

  // For each child mem-ref-expr create a mem-ref-expr based on 'wn'
  for (list<MemRefExprInfo>::iterator it = childInfos.begin(); 
       it != childInfos.end(); ++it) {
    
    MemRefExprInfo childInfo = (*it);
    unsigned childDerefs = childInfo.first;
    OA::SymHandle childSH = childInfo.second;

    // -------------------------------------------------------
    // a. Info about the MemRefExpr
    // -------------------------------------------------------

    // Sometimes -- e.g. because of the context -- a WHIRL node that
    // would typically be a mem-ref-expr should not be considered one.
    // However, we may use its info to create a location block.
    bool isMemRefExpr = isMemRefExprXXX;
    
    // Assume a source-ref-expr if level 0.  This will be corrected, if
    // necessary, below.
    OA::MemRefExpr::MemRefType hty;
    if (lvl == 0) {
      hty = (flags & flags_STORE_PARENT) ? OA::MemRefExpr::DEF: 
	                                   OA::MemRefExpr::USE;
    }

    unsigned derefs = childDerefs;
    bool isAddrOf = false;
    bool fullAccuracy = false;
    
    // Location block
    //LocBlock* locblk = NULL;
    OA::SymHandle locSH;
    bool hasNestedProc = (PU_Info_child(Current_PU_Info) != NULL);
    bool isLocal = false;
    bool isNamed = false;
    bool isUnique = false;

    // -------------------------------------------------------
    // b. Gather information about the mem-ref
    // -------------------------------------------------------
    ST* st = NULL;
    TY_IDX base_ty = 0, ref_ty = 0;
    WN_OFFSET offset = 0;
    UINT field_id = 0; 
    
    if (OPERATOR_is_load(opr) || opr == OPR_LDA || opr == OPR_LDMA) {
      base_ty = WN_GetBaseObjType(wn);
      ref_ty = WN_GetRefObjType(wn);
      if ((flags & flags_EXPECT_ARRAY_BASE) 
	  || (flags & flags_EXPECT_FUNC_BASE)) {
	isMemRefExpr = false;
      }
      offset = WN_load_offset(wn); // == WN_lda_offset()
    } 
    else if (OPERATOR_is_store(opr)) {
      if (lvl == 0) { hty = OA::MemRefExpr::DEF; }
      base_ty = WN_GetBaseObjType(wn);
      ref_ty = WN_GetRefObjType(wn);
      offset = WN_store_offset(wn);
    }
    
    if (OPERATOR_has_field_id(opr)) {
      field_id = WN_field_id(wn);
    }
    
    // special cases
    switch (opr) {
      // NOTE: MLOAD, MSTORE
      
      // LOADs represent an rvalue
      case OPR_LDA:
      case OPR_LDMA:
        st = WN_st(wn);
        if (!isFortran) {
          isAddrOf = true;
        }
        if ((flags & flags_EXPECT_ARRAY_BASE)) {
          ref_ty = (TY_Is_Pointer(ref_ty)) ? TY_pointed(ref_ty) : base_ty;
          isAddrOf = false; // implicitly dereference the address
        }
        break;
	
      case OPR_LDID:
      case OPR_LDBITS:
	st = WN_st(wn);
	break;
	
      case OPR_ILOAD:
      case OPR_ILOADX:
	if (!isFortran) { derefs++; }
	break; // use loc block obtained above from kid0
	
      // ARRAYs
      case OPR_ARRAY:
      case OPR_ARRSECTION:
	break; // use loc block obtained above from kid0
      case OPR_ARRAYEXP:
	isMemRefExpr = false;
	break; // use loc block obtained above from kid0
      
      // CALLs (indirect)
      case OPR_ICALL:
      case OPR_VFCALL:
	if (!isFortran) { derefs++; }
	break; // use loc block obtained above from kid n-1
      
      // STOREs represent an lvalue
      case OPR_STID:
      case OPR_STBITS:
	st = WN_st(wn);
	break;
      case OPR_ISTORE:
      case OPR_ISTOREX:
      case OPR_ISTBITS: {
	if (!isFortran) { derefs++; }
	break; // use loc block obtained above from kid1
      }
      
      default:
	isMemRefExpr = false;
	break;
    }
  
    // -------------------------------------------------------
    // c. Compute mem-ref-expr information and add to 'memRefs'
    // -------------------------------------------------------
    // Create location block 
    // FIXME: not as accurate as it could be
    // FIXME: What to do with alloc?
    if (st) {
      // Note: This should simulate most of the info in OPR_PARM nodes
      bool isLocalInParam = ((ST_sclass(st) == SCLASS_FORMAL || 
			      ST_sclass(st) == SCLASS_FORMAL_REF) 
			     && ST_is_intent_in_argument(st));
      
      isLocal = (!hasNestedProc &&
		 (isLocalInParam || (ST_level(st) == CURRENT_SYMTAB)));
      isNamed = (ST_sclass(st) != SCLASS_UNKNOWN &&
		 ST_sclass(st) != SCLASS_EXTERN);
      isUnique = isLocal;
      locSH = OA::SymHandle((irhandle_t)st);
    } 
    else if (childSH) {
      locSH = childSH; 
    }
    
    // Set accuracy
    if (offset == 0 && field_id == 0) { // we do not have a structure ref
      if (derefs > 0) { 
	// A plain deref always has full accuracy
	fullAccuracy = true;
      }
      if (base_ty != 0 && WN2F_Can_Assign_Types(base_ty, ref_ty)) {
	// If assigning to same object, we have full accuracy
	fullAccuracy = true;
      }
    }
    
    // Create mem-ref-expr and add to list
    if (isMemRefExpr) {
      // currently only handling named memory references
      // FIXME: need to handle malloc's at some point
      
      // if there are 0 derefs then just create a NamedRef
      OA::OA_ptr<OA::MemRefExpr> mre;
      if (derefs==0) {
        mre = new NamedRef(isAddrOf,fullAccuracy,hty,locSH);
      } else {
        // create base named reference with no address of and full accuracy
        // and then a Deref
        mre = new NamedRef(false, true, hty, locSH);
        mre = new Deref(mre,derefs);
        // if the reference isn't accurate then set partial accuracy on the deref
        if (!fullAccuracy) { mre->setPartialAccuracy(); }
      }

      // mapping of MemRefHandle to MemRefExprs
      Open64IRInterface::sMemref2mreSetMap[OA::MemRefHandle((irhandle_t)wn)].insert(mre);
      // list of MemRefHandles we are building
      memRefs.push_back(OA::MemRefHandle((irhandle_t)wn));
      
      //memRefExprs.push_back(OA::MemRefExprBasic(OA::MemRefHandle((irhandle_t)wn), 
//							    hty, locSH, derefs,
//							    isAddrOf, acc));
    } 
    
    // Save mem-ref-expr info
    curMemRefExprInfos.push_back(MemRefExprInfo(derefs, locSH));
  }
  
  return curMemRefExprInfos;
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
        cout << ",";
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
        cout << ",";
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
    for ( ; procIter.isValid(); procIter++) {
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
                sGlobalVarMap[create_fqn(sym)].insert(sym);
                if (debug) {
                    fully_qualified_name fqn = create_fqn(sym);
                    std::cout << "create_fqn(" << createCharStarForST(st) << ") = "
                              << fqn.mVar << ", " << fqn.mContext << std::endl;
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
