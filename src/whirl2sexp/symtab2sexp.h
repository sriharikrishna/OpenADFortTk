// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/symtab2sexp.h,v 1.1 2004/08/05 18:38:14 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/symtab2sexp.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef symtab2sexp_h
#define symtab2sexp_h

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include <lib/support/sexpostream.h>

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// 
//***************************************************************************

namespace whirl2sexp {

  extern void 
  xlate_SymbolTables(sexp::ostream& sos, SYMTAB_IDX symtab_lvl);
  
  extern void 
  xlate_SYMTAB(sexp::ostream& sos, SYMTAB_IDX symtab_lvl);
  
  extern void 
  TranslateSTDecl(sexp::ostream& sos, ST* st);
  
  extern void 
  TranslateSTUse(sexp::ostream& sos, ST* st);
  
}; /* namespace whirl2sexp */


#endif /* symtab2sexp_h */

