// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/testers/tester.h,v 1.3 2004/02/10 15:24:11 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/testers/tester.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef tester_INCLUDED_h
#define tester_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

//*************************** Forward Declarations ***************************

//****************************************************************************

namespace whirltester {
  
  int
  TestIR(std::ostream& os, PU_Info* pu_forest);
  
  int
  TestIR_OA(std::ostream& os, PU_Info* pu_forest);
  
  int
  TestIR_whirl2f(std::ostream& os, PU_Info* pu_forest);
  
}; /* namespace tester */

//***************************************************************************

#endif // tester_INCLUDED_h
