// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/testers/tester.cxx,v 1.5 2003/12/03 20:43:06 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/testers/tester.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <stdlib.h> // ANSI: cstdlib // for strtol
#include <string.h> // ANSI: cstring // for strcmp, etc.

#include <iostream>

//*************************** User Include Files ****************************

#include "tester.h"

#include <lib/support/Pro64IRInterface.h>

#include <OpenAnalysis/ValueNumbers/ValueNumbers.h>
#include <OpenAnalysis/ValueNumbers/ExprTree.h>

#include <lib/support/SymTab.h>
#include <lib/support/diagnostics.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

static int
TestIR_OA_ForEachWNPU(std::ostream& os, WN* wn_pu);

static void
TestIR_OA_ForEachVarRef(std::ostream& os, WN* wn, 
			Pro64IRInterface& ir, ValueNumbers& vnmap);

//****************************************************************************

static int
TestForEachPU(std::ostream& os, PU_Info* pu_forest);

static int
TestForEachWNPU(std::ostream& os, WN* wn_pu);

static int
TestForEachWN(std::ostream& os, WN* wn);

static void
RecursiveFnWN(std::ostream& os, WN* wn);

//*************************** Forward Declarations ***************************

static int
DumpExprTree(std::ostream& os, WN* wn);

//****************************************************************************

// TestIR_OA: 
int
whirltester::TestIR_OA(std::ostream& os, PU_Info* pu_forest)
{
  Diag_Set_Phase("WHIRL tester: TestIR_OA");
  
  if (!pu_forest) { return 0; }

  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    
    // The PU_Info* for this PU
    PU_Info* pu = (PU_Info*)procIt.Current();

    // The root of the WHIRL tree
    WN* wn_pu = PU_Info_tree_ptr(pu);
    
    TestIR_OA_ForEachWNPU(os, wn_pu);
  }
  return 0;
}

static int
TestIR_OA_ForEachWNPU(std::ostream& os, WN* wn_pu)
{
  WN* fbody = WN_func_body(wn_pu);

  Pro64IRInterface irInterface;
  Pro64IRStmtIterator irStmtIter(fbody);
  CFG cfg(irInterface, &irStmtIter, (SymHandle)WN_st(wn_pu), true);

  // Accumulate the ST* for parameters
  std::set<SymHandle> params;
  INT nparam = WN_num_formals(wn_pu);
  for (int i = 0; i < nparam; ++i) {
    ST* st = WN_st(WN_formal(wn_pu, i));
    params.insert((SymHandle)st);
  }
  
  ValueNumbers vnmap(cfg, params);
  TestIR_OA_ForEachVarRef(os, wn_pu, irInterface, vnmap);
}

static void
TestIR_OA_ForEachVarRef(std::ostream& os, WN* wn, 
			Pro64IRInterface& ir, ValueNumbers& vnmap)
{
  if (wn == NULL) {
    // Base case
  } 

  OPERATOR opr = WN_operator(wn);
  
  if (IsVarRefTranslatableToXAIF(wn)) {
    // Base case
    VN vn = vnmap.Find((ExprHandle)wn);
    
    os << "VN = " << vn << endl;
    ExprTree* tree = ir.GetExprTreeForExprHandle((ExprHandle)wn);
    tree->dump(os);
    delete tree;

  } else if (!OPERATOR_is_leaf(opr)) {
    
    // General recursive case
    if (WN_operator(wn) == OPR_BLOCK) {
      WN *kid = WN_first(wn);
      while (kid) {
	TestIR_OA_ForEachVarRef(os, kid, ir, vnmap);
	kid = WN_next(kid);
      }
    } else {
      for (INT kidno = 0; kidno < WN_kid_count(wn); kidno++) {
	WN* kid = WN_kid(wn, kidno);
	TestIR_OA_ForEachVarRef(os, kid, ir, vnmap);
      }
    }
  }
}


//****************************************************************************

// TestIR: 
int
whirltester::TestIR(std::ostream& os, PU_Info* pu_forest)
{
  Diag_Set_Phase("WHIRL tester: TestIR");
  
  if (!pu_forest) { return 0; }
  
  // Here is where we can do something
  TestForEachPU(os, pu_forest);

  return 0;
}

static int
TestForEachPU(std::ostream& os, PU_Info* pu_forest)
{
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    
    // The PU_Info* for this PU
    PU_Info* pu = (PU_Info*)procIt.Current();

    // The root of the WHIRL tree
    WN* wn_pu = PU_Info_tree_ptr(pu);
    
    TestForEachWNPU(os, wn_pu);
  }
  return 0;
}

static int
TestForEachWNPU(std::ostream& os, WN* wn_pu)
{
  // We may want to do something special with the top level WN (FUNC_ENTRY)
  //...
  
  // Iterate over each WN and do something
  WN_TREE_CONTAINER<PRE_ORDER> wtree(wn_pu);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  
  for (it = wtree.begin(); it != wtree.end(); ++it) {
    WN* curWN = it.Wn();

    TestForEachWN(os, curWN);
  }

  // Alternatively we may want to recursively do something with the WHIRL tree
  RecursiveFnWN(os, wn_pu);
  
  return 0;
}

static int
TestForEachWN(std::ostream& os, WN* wn)
{
  DumpExprTree(os, wn);
  return 0;
}

static void
RecursiveFnWN(std::ostream& os, WN* wn)
{
  if (wn == NULL) {
    // Base case

  } 
  
  OPERATOR opr = WN_operator(wn);

  if ( /* some test */ false ) {
    // Base case
  } else if (!OPERATOR_is_leaf(opr)) {
    
    // General recursive case
    if (WN_operator(wn) == OPR_BLOCK) {
      WN *kid = WN_first(wn);
      while (kid) {
	RecursiveFnWN(os, kid);
	kid = WN_next(kid);
      }
    } else {
      for (INT kidno = 0; kidno < WN_kid_count(wn); kidno++) {
	WN* kid = WN_kid(wn, kidno);
	RecursiveFnWN(os, kid);
      }
    }
  }
}

//****************************************************************************


static int
DumpExprTree(std::ostream& os, WN* wn)
{
  Pro64IRInterface ir;

  OPERATOR opr = WN_operator(wn);
  if (OPERATOR_is_expression(opr)) {
    ExprTree* tree = ir.GetExprTreeForExprHandle((ExprHandle)wn);
    tree->dump(os);
    delete tree;
  }
  
  return 0;
}
