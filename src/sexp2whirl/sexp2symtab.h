// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2symtab.h,v 1.2 2004/12/23 16:28:07 eraxxon Exp $

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
  xlate_PU_TAB(sexp_t* pu_tab);

  void 
  xlate_TY_TAB(sexp_t* ty_tab);

  void 
  xlate_FLD_TAB(sexp_t* fld_tab);

  void 
  xlate_TYLIST_TAB(sexp_t* tylist_tab);

  void 
  xlate_ARB_TAB(sexp_t* arb_tab);
  
  void 
  xlate_BLK_TAB(sexp_t* blk_tab);

  void 
  xlate_TCON_TAB(sexp_t* tcon_tab);
  
  void 
  xlate_INITO_TAB(sexp_t* inito_tab, SYMTAB_IDX stab_lvl);

  void 
  xlate_INITV_TAB(sexp_t* initv_tab);

  void 
  xlate_ST_ATTR_TAB(sexp_t* st_attr_tab, SYMTAB_IDX stab_lvl);

  void 
  xlate_STR_TAB(sexp_t* str_tab);
  
  
  void 
  xlate_PREG_TAB(sexp_t* preg_tab, SYMTAB_IDX stab_lvl);
  
  void 
  xlate_LABEL_TAB(sexp_t* label_tab, SYMTAB_IDX stab_lvl);
    
}; /* namespace sexp2whirl */


//***************************************************************************
// Function objects to translate individual table entries
//***************************************************************************

namespace sexp2whirl {
  
  ST*
  xlate_ST_TAB_entry(sexp_t* sx);

#if 0
  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, ST* st);
#endif  
  
  PU*
  xlate_PU_TAB_entry(sexp_t* sx);

  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, TY* ty);

  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, FLD* fld);

  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, TYLIST* tyl);

  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, ARB* arb);
  
  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, BLK* blk);
  
  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, TCON* tcon);

  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, INITO* inito);

  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, INITV* initv);

  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, ST_ATTR* sta);
  
  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, PREG* preg);

  void
  xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, LABEL* lbl);
  

}; /* namespace sexp2whirl */


//***************************************************************************

#endif /* sexp2symtab_h */

