// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2symtab.cxx,v 1.1 2004/12/20 15:17:43 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2symtab.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

//*************************** Sexp Include Files ****************************

#include <sexp.h>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

//#include "sexp2wn.h"
#include "sexp2symtab.h"

//************************** Forward Declarations ***************************

using namespace sexp2whirl;


//***************************************************************************
// Translate symbol tables
//***************************************************************************

void 
sexp2whirl::TranslateGlobalSymbolTables(sexp_t* gbl_symtab, int flags)
{

#if 0  
  xlate_FILE_INFO(sos);
  xlate_ST_TAB(sos, GLOBAL_SYMTAB);
  xlate_PU_TAB(sos);
  xlate_TY_TAB(sos);
  xlate_FLD_TAB(sos);
  xlate_TYLIST_TAB(sos);
  xlate_ARB_TAB(sos);
  xlate_BLK_TAB(sos);
  xlate_TCON_TAB(sos);
  xlate_INITO_TAB(sos, GLOBAL_SYMTAB);
  xlate_ST_ATTR_TAB(sos, GLOBAL_SYMTAB);
  xlate_STR_TAB(sos);
#endif

}


void 
sexp2whirl::TranslateLocalSymbolTables(sexp_t* pu_symtab, SYMTAB_IDX stab_lvl,
				       int flags)
{
#if 0
  xlate_ST_TAB(sos, stab_lvl);
  xlate_INITO_TAB(sos, stab_lvl);
  xlate_ST_ATTR_TAB(sos, stab_lvl);
  xlate_PREG_TAB(sos, stab_lvl);
  xlate_LABEL_TAB(sos, stab_lvl);
#endif
}


//***************************************************************************
// Translate individual tables
//***************************************************************************

// Note: 'For_all' applies 'operator()' to every entry of the
// respective table.

void 
sexp2whirl::xlate_FILE_INFO(sexp_t* file_info)
{

}

void 
sexp2whirl::xlate_ST_TAB(sexp_t* st_tab, SYMTAB_IDX stab_lvl)
{

}

void 
sexp2whirl::xlate_ST_TAB(sexp_t* st_tab, const SCOPE& scope)
{

}

void 
sexp2whirl::xlate_PU_TAB(sexp_t* pu_tab)
{

}

void 
sexp2whirl::xlate_TY_TAB(sexp_t* ty_tab)
{

}

void 
sexp2whirl::xlate_FLD_TAB(sexp_t* fld_tab)
{

}

void 
sexp2whirl::xlate_TYLIST_TAB(sexp_t* tylist_tab)
{

}

void 
sexp2whirl::xlate_ARB_TAB(sexp_t* arb_tab)
{

}

void 
sexp2whirl::xlate_BLK_TAB(sexp_t* blk_tab)
{

}

void 
sexp2whirl::xlate_TCON_TAB(sexp_t* tcon_tab)
{

}

void 
sexp2whirl::xlate_INITO_TAB(sexp_t* inito_tab, SYMTAB_IDX stab_lvl)
{

}

void 
sexp2whirl::xlate_INITV_TAB(sexp_t* initv_tab)
{

}

void 
sexp2whirl::xlate_ST_ATTR_TAB(sexp_t* st_attr_tab, SYMTAB_IDX stab_lvl)
{

}

void 
sexp2whirl::xlate_STR_TAB(sexp_t* str_tab)
{

}



void 
sexp2whirl::xlate_PREG_TAB(sexp_t* preg_tab, SYMTAB_IDX stab_lvl)
{

}

void 
sexp2whirl::xlate_LABEL_TAB(sexp_t* label_tab, SYMTAB_IDX stab_lvl)
{

}


//***************************************************************************
// Function objects to translate individual table entries
//***************************************************************************

void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, ST* st)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, PU* pu)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, TY* typ)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, FLD* fld)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, TYLIST* tyl)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, ARB* arb)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, BLK* blk)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, TCON* tcon)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, INITO* inito)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, INITV* initv)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, ST_ATTR* sta)
{

}



void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, PREG* preg)
{

}


void
sexp2whirl::xlate_SYMTAB_entry(sexp_t* sx, UINT32 idx, LABEL* lbl)
{

}


//***************************************************************************

