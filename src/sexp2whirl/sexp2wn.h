// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2wn.h,v 1.2 2004/12/23 16:28:07 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2wn.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef sexp2wn_h
#define sexp2wn_h

//************************** System Include Files ***************************

#include <vector> // STL
#include <list>   // STL

//*************************** Sexp Include Files ****************************

#include <sexp.h>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "sexp2whirl.i"

//************************** Forward Declarations ***************************

//***************************************************************************
// Commonly used WHIRL translation functions
//***************************************************************************

namespace sexp2whirl {
    
  // Note: All routines Assume that Open64 symbol table globals are
  // already set.

  // TranslateWN: Translates the given WHIRL node, emitting output to
  // 'sos'.  If 'wn' is NULL, emits an empty list.  
  extern WN* 
  TranslateWN(sexp_t* sx);

  // TranslateWNChildren: Given a non-NULL WHIRL node, translates its
  // children, emitting output to 'sos'.
  extern WN* 
  TranslateWNChildren(sexp_t* sx);
  
}; /* namespace sexp2whirl */


//***************************************************************************
// Commonly used routines for extracting information from S-expressions
//***************************************************************************

namespace sexp2whirl {
  
  ST_IDX 
  GetWhirlSym(sexp_t* sx);
  
  TY_IDX
  GetWhirlTy(sexp_t* sx);
  
  OPERATOR
  GetWhirlOpr(sexp_t* sx);
  
  OPCODE
  GetWhirlOpc(sexp_t* sx);
  
  ST_IDX
  GetWhirlSymRef(sexp_t* sx);
  
  TY_IDX
  GetWhirlTyUse(sexp_t* sx);
  
  sexp_t*
  GetBeginFlgList(sexp_t* sx);
  
}; /* namespace sexp2whirl */


//***************************************************************************

#endif /* sexp2wn_h */
