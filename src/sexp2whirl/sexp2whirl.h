// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2whirl.h,v 1.1 2004/12/15 20:59:24 eraxxon Exp $

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

#include <include/Open64BasicTypes.h>

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
  
  
  // Translate the whole IR, return a PU_FOREST and set GBL_SYMTAB state.
  extern PU_Info*
  TranslateIR(sexp_t* ir, int flags = 0);
    
  // Translate and return a PU_TREE (a PU and all children)
  extern PU_Info*
  TranslatePUTree(sexp_t* pu_tree, int flags = 0);
    
  // Translate and return a PU and set PU_SYMTAB state.
  extern PU_Info* 
  TranslatePU(sexp_t* pu, int flags = 0);

  // Translate and return a WHIRL_AST
  extern WN* 
  TranslateWN(sexp_t* wn, int flags = 0);
  
  // Dump to std::cout
  extern void DumpIR(sexp_t* ir, int flags);
  
}; /* namespace sexp2whirl */

//***************************************************************************

#endif /* sexp2whirl_h */
