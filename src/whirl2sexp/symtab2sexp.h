// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/symtab2sexp.h,v 1.2 2004/08/06 17:29:53 eraxxon Exp $

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
// Translate symbol tables
//***************************************************************************

namespace whirl2sexp {

  extern void 
  TranslateGlobalSymbolTables(sexp::ostream& sos);

  extern void 
  TranslateLocalSymbolTables(sexp::ostream& sos, SYMTAB_IDX stab_lvl);

}; /* namespace whirl2sexp */


//***************************************************************************
// Translate individual tables
//***************************************************************************

namespace whirl2sexp {

  // Translate every entry of the given table at the given lexical level
  // ('stab_lvl'). 

  void 
  xlate_FILE_INFO(sexp::ostream& sos);

  void 
  xlate_ST_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl);
  void
  xlate_ST_TAB(sexp::ostream& sos, const SCOPE& scope);

  void 
  xlate_PU_TAB(sexp::ostream& sos);

  void 
  xlate_TY_TAB(sexp::ostream& sos);

  void 
  xlate_BLK_TAB(sexp::ostream& sos);

  void 
  xlate_TCON_TAB(sexp::ostream& sos);
  
  void 
  xlate_INITO_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl);

  void 
  xlate_ST_ATTR_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl);

}; /* namespace whirl2sexp */


//***************************************************************************
// Function objects to translate individual table entries
//***************************************************************************

namespace whirl2sexp {
  
  void
  xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, ST* st);
  
  void
  xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, PU* pu);
  
  void
  xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, TY* ty);

  void
  xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, BLK* blk);

  void
  xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, TCON* tcon);

  void
  xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, INITO* inito);

  void
  xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, ST_ATTR* sta);
  
  
  // xlate_SYMTAB_entry_op: a templated functor that simply calls the
  // above (overloaded) routines.
  template <class T>
  class xlate_SYMTAB_entry_op {
  public:
    xlate_SYMTAB_entry_op(sexp::ostream& sos_) : sos(sos_) { }
    ~xlate_SYMTAB_entry_op() { }
    
    void operator()(UINT32 idx, T* entry) const { 
      xlate_SYMTAB_entry(sos, idx, entry);
      sos << EndLine;
    }
    
  private:
    sexp::ostream& sos;
  };


}; /* namespace whirl2sexp */


//***************************************************************************

#endif /* symtab2sexp_h */

