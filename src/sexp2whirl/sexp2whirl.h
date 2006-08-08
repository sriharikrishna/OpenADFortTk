// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2whirl.h,v 1.3 2005/01/05 20:51:10 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2whirl.h,v $
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

//*************************** Sexp Include Files ****************************

#include <sexp.h>

//************************** Open64 Include Files ***************************

#include "Open64IRInterface/Open64BasicTypes.h"

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

//***************************************************************************

namespace sexp2whirl {
  
  namespace XlateFlags {
    enum Flags {
      NONE       = 0x00000000, // 
      
      FOO1       = 0x00000001, // 
      FOO2       = 0x00000002, // 
      FOO3       = 0x00000004, // 
      FOO4       = 0x00000008, // 
    };
  };
  
  
  // Translate the whole WHIRL_IR, return a PU_FOREST and set GBL_SYMTAB state.
  extern PU_Info*
  TranslateIR(sexp_t* ir, int flags = 0);

  
  // Dump to std::cout
  extern void DumpIR(sexp_t* ir, int flags);

  // Convert to a diagnostic message string 
  extern const char* ErrIR(sexp_t* ir, int flags = 0);
  
}; /* namespace sexp2whirl */

//***************************************************************************

#endif /* sexp2whirl_h */
