// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/whirl2sexp.h,v 1.4 2005/08/01 19:42:17 eraxxon Exp $
#ifndef whirl2sexp_h
#define whirl2sexp_h
#include <fstream>

#include "Open64IRInterface/Open64BasicTypes.h"
#include "sexpostream.h"

namespace whirl2sexp {
  
  namespace XlateFlags {
    enum Flags {
      NONE       = 0x00000000, // 
      
      FOO1       = 0x00000001, // 
      FOO2       = 0x00000002, // 
      FOO3       = 0x00000004, // 
      FOO4       = 0x00000008  // 
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
