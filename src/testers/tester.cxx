// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/testers/tester.cxx,v 1.1 2003/09/05 21:45:50 eraxxon Exp $

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

// #include <lib/support/WhirlIDMaps.h>
#include <lib/support/diagnostics.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

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
  OPERATOR opr = WN_operator(wn);
  if (wn == NULL) {
    // Base case

#if 0
  } else if ( /* some test */ ) {
#endif

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


#include <OpenAnalysis/ValueNumbers/ExprTree.h>

static int
DumpExprTree(std::ostream& os, WN* wn)
{
  OPERATOR opr = WN_operator(wn);
  if (OPERATOR_is_expression(opr)) {
    ExprTree* tree = GetExprTreeForExprHandle((ExprHandle)wn);
    tree->dump(os);
    delete tree;
  }
  
  return 0;
}
