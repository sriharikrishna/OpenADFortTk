// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2symtab.cxx,v 1.2 2004/12/23 16:28:07 eraxxon Exp $

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

#include "sexp2wn.h"
#include "sexp2symtab.h"

#include <lib/support/SexpTags.h>
#include <lib/support/sexputil.h>

//************************** Forward Declarations ***************************

using namespace sexp2whirl;


//***************************************************************************
// Translate symbol tables
//***************************************************************************

void 
sexp2whirl::TranslateGlobalSymbolTables(sexp_t* gbl_symtab, int flags)
{
  using namespace sexp;
  
  if (!gbl_symtab) { return; }

  // Sanity check
  FORTTK_ASSERT(is_list(gbl_symtab), FORTTK_UNEXPECTED_INPUT);  
  
  sexp_t* tag_sx = get_elem0(gbl_symtab);
  const char* tagstr = get_value(tag_sx);
  FORTTK_ASSERT(tag_sx && strcmp(tagstr, SexpTags::GBL_SYMTAB) == 0,
		FORTTK_UNEXPECTED_INPUT);
  
  // Initialize WHIRL symbol tables
  Initialize_Symbol_Tables(TRUE);
  New_Scope(GLOBAL_SYMTAB, Malloc_Mem_Pool, TRUE);
  
  // Translate global tables
  sexp_t* file_info_sx = get_elem1(gbl_symtab);
  xlate_FILE_INFO(file_info_sx);
  
  sexp_t* st_tab_sx = get_next(file_info_sx);
  xlate_ST_TAB(st_tab_sx, GLOBAL_SYMTAB);
  
  sexp_t* pu_tab_sx = get_next(st_tab_sx);
  xlate_PU_TAB(pu_tab_sx);
  
#if 0
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

  // Initialize_Special_Global_Symbols();

}


void 
sexp2whirl::TranslateLocalSymbolTables(sexp_t* pu_symtab, SYMTAB_IDX stab_lvl,
				       int flags)
{
  using namespace sexp;
  
  if (!pu_symtab) { return; }
  
  // Sanity check
  FORTTK_ASSERT(is_list(pu_symtab), FORTTK_UNEXPECTED_INPUT);  
  
  sexp_t* tag_sx = get_elem0(pu_symtab);
  const char* tagstr = get_value(tag_sx);
  FORTTK_ASSERT(tag_sx && strcmp(tagstr, SexpTags::PU_SYMTAB) == 0,
		FORTTK_UNEXPECTED_INPUT);
  
  // Initialize WHIRL symbol tables
  New_Scope(stab_lvl, Malloc_Mem_Pool, TRUE);

  // Translate local tables
  sexp_t* st_tab_sx = get_elem1(pu_symtab);
  xlate_ST_TAB(st_tab_sx, stab_lvl);
  
#if 0
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


// FIXME: see ir_bread.cxx:231 for global tables
//            ir_bread.cxx:305 for local tables

void 
sexp2whirl::xlate_FILE_INFO(sexp_t* file_info)
{
  
}

void 
sexp2whirl::xlate_ST_TAB(sexp_t* st_tab, SYMTAB_IDX stab_lvl)
{
  using namespace sexp;
  
  // Sanity check
  FORTTK_ASSERT(is_list(st_tab), FORTTK_UNEXPECTED_INPUT);  
  
  sexp_t* tag_sx = get_elem0(st_tab);
  const char* tagstr = get_value(tag_sx);
  FORTTK_ASSERT(tag_sx && strcmp(tagstr, SexpTags::ST_TAB) == 0,
		FORTTK_UNEXPECTED_INPUT);
  
  // Translate each entry [FIXME: translate in blocks using templated forall]
  for (sexp_t* entry = get_elem1(st_tab); entry; entry = get_next(entry)) {
    ST* st = xlate_ST_TAB_entry(entry);
    Scope_tab[stab_lvl].st_tab->Transfer(st, 1);
  }
}

void 
sexp2whirl::xlate_ST_TAB(sexp_t* st_tab, const SCOPE& scope)
{
  
}

void 
sexp2whirl::xlate_PU_TAB(sexp_t* pu_tab)
{
  using namespace sexp;
  
  // Sanity check
  FORTTK_ASSERT(is_list(pu_tab), FORTTK_UNEXPECTED_INPUT);  
  
  sexp_t* tag_sx = get_elem0(pu_tab);
  const char* tagstr = get_value(tag_sx);
  FORTTK_ASSERT(tag_sx && strcmp(tagstr, SexpTags::PU_TAB) == 0,
		FORTTK_UNEXPECTED_INPUT);
  
  // Translate each entry [FIXME: translate in blocks using templated forall]
  for (sexp_t* entry = get_elem1(pu_tab); entry; entry = get_next(entry)) {
    PU* pu = xlate_PU_TAB_entry(entry);
    Pu_Table.Transfer(pu, 1);
  }
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

ST*
sexp2whirl::xlate_ST_TAB_entry(sexp_t* sx)
{
  using namespace sexp;

  ST* st = TYPE_MEM_POOL_ALLOC(ST, MEM_pu_pool_ptr);
  
  // sym_class, storage_class, export_class
  sexp_t* stclass_sx = get_elem1(sx);
  const char* stclass_nm = get_value(stclass_sx);
  ST_CLASS stclass = Name_To_Class(stclass_nm);
  Set_ST_sym_class(*st, stclass);
  
  sexp_t* stsclass_sx = get_next(stclass_sx);
  const char* stsclass_nm = get_value(stsclass_sx);
  ST_SCLASS stsclass = Name_To_Sclass(stsclass_nm);
  Set_ST_sclass(*st, stsclass);

  sexp_t* stexport_sx = get_next(stsclass_sx);
  const char* stexport_nm = get_value(stexport_sx);
  ST_EXPORT stexport = Name_To_Export(stexport_nm);
  Set_ST_export(*st, stexport);
  
  // name_idx/tcon
  sexp_t* name_idx_sx = get_next(stexport_sx);
  sexp_t* nmidx_sx = get_elem1(name_idx_sx);
  STR_IDX nmidx = get_value_ui32(nmidx_sx); // or TCON_IDX
  Set_ST_name_idx(*st, nmidx);              // or TCON_IDX
    
  // type/pu/blk
  sexp_t* typublk_sx = get_next(name_idx_sx);  
  if (stclass == CLASS_FUNC) {
    PU_IDX stpu = get_value_ui32(typublk_sx);
    Set_ST_pu(*st, stpu);
  }
  else if (stclass == CLASS_BLOCK) {
    BLK_IDX stblk = get_value_ui32(typublk_sx);
    Set_ST_blk(*st, stblk);
  }
  else {
    TY_IDX sttype = GetWhirlTy(typublk_sx);
    Set_ST_type(*st, sttype);
  }
  
  // base_idx, offset
  sexp_t* basest_sx = get_next(typublk_sx);
  ST_IDX stbase_idx  = GetWhirlSym(basest_sx);
  Set_ST_base_idx(*st, stbase_idx);
  
  sexp_t* oset_sx = get_next(basest_sx);
  UINT64 oset = get_value_ui64(oset_sx);
  Set_ST_ofst(*st, oset);

  // flags/flags_ext
  sexp_t* flags_sx = get_next(oset_sx);
  sexp_t* flag1_sx = GetBeginFlgList(flags_sx);
  sexp_t* flag2_sx = get_next(flag1_sx);
  st->flags = get_value_ui32(flag1_sx);
  st->flags_ext = get_value_ui64(flag2_sx); // FIXME: flag parsing
  
  // st_idx
  sexp_t* st_idx_sx = get_next(flags_sx);
  ST_IDX st_idx = GetWhirlSym(st_idx_sx);
  Set_ST_st_idx(*st, st_idx);
  
  return st;
}


PU*
sexp2whirl::xlate_PU_TAB_entry(sexp_t* sx)
{
  using namespace sexp;
  
  PU* pu = TYPE_MEM_POOL_ALLOC(PU, MEM_pu_pool_ptr);
  
  // prototype
  sexp_t* ty_idx_sx = get_elem1(sx);
  TY_IDX ty_idx = GetWhirlTy(ty_idx_sx);
  Set_PU_prototype(*pu, ty_idx);
  
  // lexical_level
  sexp_t* lvl_sx = get_next(ty_idx_sx);
  SYMTAB_IDX lvl = (SYMTAB_IDX)get_value_ui32(lvl_sx);
  Set_PU_lexical_level(*pu, lvl);
    
  // gp_group
  sexp_t* gp_sx = get_next(lvl_sx);
  UINT8 gp = (UINT8)get_value_ui32(gp_sx);
  Set_PU_gp_group(*pu, gp);
  
  // src_lang
  sexp_t* srclang_sx = get_next(gp_sx);
  mUINT8 srclang = (mUINT8)get_value_ui32(srclang_sx);
  pu->src_lang = srclang; // FIXME: flag parsing

  // target_idx
  sexp_t* targidx_sx = get_next(srclang_sx);
  TARGET_INFO_IDX targidx = get_value_ui32(targidx_sx);
  Set_PU_target_idx(*pu, targidx);
  
  // flags
  sexp_t* flags_sx = get_next(targidx_sx);
  sexp_t* flag1_sx = GetBeginFlgList(flags_sx);
  pu->flags = get_value_ui64(flag1_sx); // FIXME: flag parsing
  
  return pu;
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

