// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2symtab.h,v 1.4 2005/01/07 19:00:16 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2symtab.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef sexp2symtab_h
#define sexp2symtab_h

//************************** System Include Files ***************************

//*************************** Sexp Include Files ****************************

#include <sexp.h>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// Translate symbol tables
//***************************************************************************

namespace sexp2whirl {

  extern void 
  TranslateGlobalSymbolTables(sexp_t* gbl_symtab, int flags = 0);

  extern void 
  TranslateLocalSymbolTables(sexp_t* pu_symtab, SYMTAB_IDX stab_lvl,
			     int flags = 0);

}; /* namespace sexp2whirl */


//***************************************************************************
// Translate individual tables
//***************************************************************************

namespace sexp2whirl {

  // Translate every entry of the given table at the given lexical level
  // ('stab_lvl'). 

  void 
  xlate_FILE_INFO(sexp_t* file_info);

  void 
  xlate_ST_TAB(sexp_t* st_tab, SYMTAB_IDX stab_lvl);
  void
  xlate_ST_TAB(sexp_t* st_tab, const SCOPE& scope);

  void 
  xlate_TY_TAB(sexp_t* ty_tab);

  void 
  xlate_PU_TAB(sexp_t* pu_tab);

  void 
  xlate_FLD_TAB(sexp_t* fld_tab);

  void 
  xlate_ARB_TAB(sexp_t* arb_tab);

  void 
  xlate_TYLIST_TAB(sexp_t* tylist_tab);
  
  void 
  xlate_TCON_TAB(sexp_t* tcon_tab);

  void 
  xlate_TCON_STR_TAB(sexp_t* str_tab);
  
  void 
  xlate_INITO_TAB(sexp_t* inito_tab, SYMTAB_IDX stab_lvl);

  void 
  xlate_INITV_TAB(sexp_t* initv_tab);

  void 
  xlate_BLK_TAB(sexp_t* blk_tab);

  void 
  xlate_ST_ATTR_TAB(sexp_t* st_attr_tab, SYMTAB_IDX stab_lvl);
  
  void 
  xlate_STR_TAB(sexp_t* str_tab);

  
  void 
  xlate_LABEL_TAB(sexp_t* label_tab, SYMTAB_IDX stab_lvl);
  
  void 
  xlate_PREG_TAB(sexp_t* preg_tab, SYMTAB_IDX stab_lvl);
      
}; /* namespace sexp2whirl */


//***************************************************************************
// Functions to translate individual table entries
//***************************************************************************

namespace sexp2whirl {
  
  ST*
  xlate_ST_TAB_entry(sexp_t* sx);
  
  TY*
  xlate_TY_TAB_entry(sexp_t* sx);

  PU*
  xlate_PU_TAB_entry(sexp_t* sx);

  FLD*
  xlate_FLD_TAB_entry(sexp_t* sx);

  ARB*
  xlate_ARB_TAB_entry(sexp_t* sx);
  
  TYLIST*
  xlate_TYLIST_TAB_entry(sexp_t* sx);

  TCON*
  xlate_TCON_TAB_entry(sexp_t* sx);

  INITO*
  xlate_INITO_TAB_entry(sexp_t* sx);

  INITV*
  xlate_INITV_TAB_entry(sexp_t* sx);

  BLK*
  xlate_BLK_TAB_entry(sexp_t* sx);
  
  ST_ATTR*
  xlate_ST_ATTR_TAB_entry(sexp_t* sx);
  
  LABEL*
  xlate_LABEL_TAB_entry(sexp_t* sx);

  PREG*
  xlate_PREG_TAB_entry(sexp_t* sx);
  

  // xlate_SYMTAB_entry: Templated access to translation routines
  template <typename T>
  T*
  xlate_SYMTAB_entry(sexp_t* sx)
  { FORTTK_DIE("Must not be called (template specialization must exist)"); }
  
}; /* namespace sexp2whirl */


//***************************************************************************

#endif /* sexp2symtab_h */

