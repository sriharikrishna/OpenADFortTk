// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/whirl2sexp.h,v 1.2 2004/10/06 22:10:30 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/whirl2sexp.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef whirl2xaif_h
#define whirl2xaif_h

//************************** System Include Files ***************************

#include <fstream>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include <lib/support/sexpostream.h>  /* sexp::ostream, etc */

//************************** Forward Declarations ***************************

//***************************************************************************

namespace whirl2sexp {
  
  namespace XlateFlags {
    enum Flags {
      NONE       = 0x00000000, // 
      
      FOO1       = 0x00000001, // 
      FOO2       = 0x00000002, // 
      FOO3       = 0x00000004, // 
      FOO4       = 0x00000008, // 
    };
  }
  
  
  // Translate the PU forest (should already be in memory)
  extern void 
  TranslateIR(std::ostream& os, PU_Info* pu_forest, int flags = 0);
    
  // Translate PU and any contained PUs (should already be in memory)
  extern void 
  TranslatePUTree(std::ostream& os, PU_Info* pu_tree, int flags = 0);
    
  // Translate only the current PU (should already be in memory)
  extern void 
  TranslatePU(std::ostream& os, PU_Info* pu, int flags = 0);

  // Translate the current WHIRL tree (should already be in memory)
  extern void 
  TranslateWN(std::ostream& os, WN* wn, int flags = 0);
  
  // Shortcuts to the above functions, that dump to std::cout
  extern void DumpIR(PU_Info* pu_forest, int flags);
  extern void DumpPUTree(PU_Info* pu_tree, int flags);
  extern void DumpPU(PU_Info* pu, int flags);
  extern void DumpWN(WN* wn, int flags);
  
}; /* namespace whirl2sexp */

//***************************************************************************

#endif /* whirl2sexp_h */
