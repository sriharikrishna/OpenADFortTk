// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2symtab.cxx,v 1.4 2005/01/07 19:00:16 eraxxon Exp $

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

#include <include/quad.h>
#include <lib/support/SexpTags.h>
#include <lib/support/sexputil.h>

//************************** Forward Declarations ***************************

using namespace sexp2whirl;


//***************************************************************************
// Helper templates
//***************************************************************************

template <typename T, UINT block_size>
void
xlate_SYMTAB(SEGMENTED_ARRAY<T, block_size>& table, 
	     sexp_t* tab_sx, const char* table_nm)
{
  using namespace sexp;
  
  // Sanity check
  FORTTK_ASSERT(tab_sx && is_list(tab_sx), FORTTK_UNEXPECTED_INPUT);
  
  sexp_t* tag_sx = get_elem0(tab_sx);
  const char* tagstr = get_value(tag_sx);
  FORTTK_ASSERT(tag_sx && strcmp(tagstr, table_nm) == 0,
		FORTTK_UNEXPECTED_INPUT);
  
  // Translate each entry
  for (sexp_t* entry = get_elem1(tab_sx); entry; entry = get_next(entry)) {
    // FIXME: translate in blocks
    T* x = xlate_SYMTAB_entry<T>(entry);
    table.Transfer(x, 1);
  }
}


template <typename T, UINT block_size>
void
xlate_SYMTAB(RELATED_SEGMENTED_ARRAY<T, block_size>& table,
	     sexp_t* tab_sx, const char* table_nm)
{
  using namespace sexp;
    
  // Sanity check
  FORTTK_ASSERT(tab_sx && is_list(tab_sx), FORTTK_UNEXPECTED_INPUT);  
  
  sexp_t* tag_sx = get_elem0(tab_sx);
  const char* tagstr = get_value(tag_sx);
  FORTTK_ASSERT(tag_sx && strcmp(tagstr, table_nm) == 0,
		FORTTK_UNEXPECTED_INPUT);
  
  // Translate each entry
  for (sexp_t* entry = get_elem1(tab_sx); entry; entry = get_next(entry)) {
    // FIXME: translate in blocks
    T* x = xlate_SYMTAB_entry<T>(entry);
    table.Transfer(x, 1);
  }
}


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
  Initialize_Symbol_Tables(TRUE /*reserve_index_zero*/);
  New_Scope(GLOBAL_SYMTAB, Malloc_Mem_Pool, TRUE /*reserve_index_zero*/);
  
  // Translate global tables
  sexp_t* file_info_sx = get_elem1(gbl_symtab);
  xlate_FILE_INFO(file_info_sx);
  
  sexp_t* st_tab_sx = get_next(file_info_sx);
  xlate_ST_TAB(st_tab_sx, GLOBAL_SYMTAB);
  
  sexp_t* ty_tab_sx = get_next(st_tab_sx);
  xlate_TY_TAB(ty_tab_sx);

  sexp_t* pu_tab_sx = get_next(ty_tab_sx);
  xlate_PU_TAB(pu_tab_sx);

  sexp_t* fld_tab_sx = get_next(pu_tab_sx);
  xlate_FLD_TAB(fld_tab_sx);

  sexp_t* arb_tab_sx = get_next(fld_tab_sx);
  xlate_ARB_TAB(arb_tab_sx);

  sexp_t* tlist_tab_sx = get_next(arb_tab_sx);
  xlate_TYLIST_TAB(tlist_tab_sx);

  sexp_t* tcon_tab_sx = get_next(tlist_tab_sx);
  xlate_TCON_TAB(tcon_tab_sx);

  sexp_t* tcon_str_tab_sx = get_next(tcon_tab_sx);
  xlate_TCON_STR_TAB(tcon_str_tab_sx);

  sexp_t* inito_tab_sx = get_next(tcon_str_tab_sx);
  xlate_INITO_TAB(inito_tab_sx, GLOBAL_SYMTAB);

  sexp_t* initv_tab_sx = get_next(inito_tab_sx);
  xlate_INITV_TAB(initv_tab_sx);

  sexp_t* blk_tab_sx = get_next(initv_tab_sx);
  xlate_BLK_TAB(blk_tab_sx);

  sexp_t* st_attr_tab_sx = get_next(blk_tab_sx);
  xlate_ST_ATTR_TAB(st_attr_tab_sx, GLOBAL_SYMTAB);

  sexp_t* str_tab_sx = get_next(st_attr_tab_sx);
  xlate_STR_TAB(str_tab_sx);

  // Special initialization of WHIRL symbol tables
  Initialize_Special_Global_Symbols();
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

  sexp_t* label_tab_sx = get_next(st_tab_sx);
  xlate_LABEL_TAB(label_tab_sx, stab_lvl);

  sexp_t* preg_tab_sx = get_next(label_tab_sx);
  xlate_PREG_TAB(preg_tab_sx, stab_lvl);

  sexp_t* inito_tab_sx = get_next(preg_tab_sx);
  xlate_INITO_TAB(inito_tab_sx, stab_lvl);

  sexp_t* st_attr_tab_sx = get_next(inito_tab_sx);
  xlate_ST_ATTR_TAB(st_attr_tab_sx, stab_lvl);
}


//***************************************************************************
// Translate individual tables
//***************************************************************************

void 
sexp2whirl::xlate_FILE_INFO(sexp_t* file_info)
{
  using namespace sexp;

  // Sanity check
  FORTTK_ASSERT(file_info && is_list(file_info), FORTTK_UNEXPECTED_INPUT);
  
  sexp_t* tag_sx = get_elem0(file_info);
  const char* tagstr = get_value(tag_sx);
  FORTTK_ASSERT(tag_sx && strcmp(tagstr, SexpTags::FILE_INFO) == 0,
		FORTTK_UNEXPECTED_INPUT);
  
  // gp_group
  sexp_t* gp_sx = get_elem1(file_info);
  mUINT8 gp = (mUINT8)get_value_ui32(gp_sx);
  Set_FILE_INFO_gp_group(File_info, gp);

  // flags
  sexp_t* flags_sx = get_next(gp_sx);
  sexp_t* flag1_sx = GetBeginFlgList(flags_sx);
  mUINT32 flags = get_value_ui32(flag1_sx);
  File_info.flags = flags;
}


void 
sexp2whirl::xlate_ST_TAB(sexp_t* st_tab, SYMTAB_IDX stab_lvl)
{
  // RELATED_SEGMENTED_ARRAY
  xlate_SYMTAB(*Scope_tab[stab_lvl].st_tab, st_tab, SexpTags::ST_TAB);
}


void 
sexp2whirl::xlate_ST_TAB(sexp_t* st_tab, const SCOPE& scope)
{
  FORTTK_DIE(FORTTK_UNIMPLEMENTED);
}


void 
sexp2whirl::xlate_TY_TAB(sexp_t* ty_tab)
{
  xlate_SYMTAB(Ty_tab /*Ty_Table*/, ty_tab, SexpTags::TY_TAB);
}


void 
sexp2whirl::xlate_PU_TAB(sexp_t* pu_tab)
{
  xlate_SYMTAB(Pu_Table, pu_tab, SexpTags::PU_TAB);
}


void 
sexp2whirl::xlate_FLD_TAB(sexp_t* fld_tab)
{
  xlate_SYMTAB(Fld_Table, fld_tab, SexpTags::FLD_TAB);
}


void 
sexp2whirl::xlate_ARB_TAB(sexp_t* arb_tab)
{
  xlate_SYMTAB(Arb_Table, arb_tab, SexpTags::ARB_TAB);
}


void 
sexp2whirl::xlate_TYLIST_TAB(sexp_t* tylist_tab)
{
  xlate_SYMTAB(Tylist_Table, tylist_tab, SexpTags::TYLIST_TAB);
}


void 
sexp2whirl::xlate_TCON_TAB(sexp_t* tcon_tab)
{
  xlate_SYMTAB(Tcon_Table, tcon_tab, SexpTags::TCON_TAB);
}


void 
sexp2whirl::xlate_TCON_STR_TAB(sexp_t* str_tab)
{
  // Initialize_TCON_strtab(1024);
  // for each entry: extern UINT32 Save_StrN (const char *s1, UINT32 len);
  // FIXME
}


void 
sexp2whirl::xlate_INITO_TAB(sexp_t* inito_tab, SYMTAB_IDX stab_lvl)
{
  // RELATED_SEGMENTED_ARRAY
  xlate_SYMTAB(*Scope_tab[stab_lvl].inito_tab, inito_tab, SexpTags::INITO_TAB);
}


void 
sexp2whirl::xlate_INITV_TAB(sexp_t* initv_tab)
{
  xlate_SYMTAB(Initv_Table, initv_tab, SexpTags::INITV_TAB);
}


void 
sexp2whirl::xlate_BLK_TAB(sexp_t* blk_tab)
{
  xlate_SYMTAB(Blk_Table, blk_tab, SexpTags::BLK_TAB);
}


void 
sexp2whirl::xlate_ST_ATTR_TAB(sexp_t* st_attr_tab, SYMTAB_IDX stab_lvl)
{
  // RELATED_SEGMENTED_ARRAY
  xlate_SYMTAB(*Scope_tab[stab_lvl].st_attr_tab, st_attr_tab, 
	       SexpTags::ST_ATTR_TAB);
}


void 
sexp2whirl::xlate_STR_TAB(sexp_t* str_tab)
{
  // Initialize_TCON_strtab(1024);
  // for each entry: Save_Str(char*)
  // FIXME
}


void 
sexp2whirl::xlate_LABEL_TAB(sexp_t* label_tab, SYMTAB_IDX stab_lvl)
{
  // RELATED_SEGMENTED_ARRAY
  xlate_SYMTAB(*Scope_tab[stab_lvl].label_tab, label_tab, SexpTags::LABEL_TAB);
}


void 
sexp2whirl::xlate_PREG_TAB(sexp_t* preg_tab, SYMTAB_IDX stab_lvl)
{
  // RELATED_SEGMENTED_ARRAY
  xlate_SYMTAB(*Scope_tab[stab_lvl].preg_tab, preg_tab, SexpTags::PREG_TAB);
}


//***************************************************************************
// Functions to translate individual table entries
//***************************************************************************

// Specializations of xlate_SYMTAB_entry
namespace sexp2whirl {

  template <>
  ST* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_ST_TAB_entry(sx); }
  
  template <>
  TY* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_TY_TAB_entry(sx); }
  
  template <>
  PU* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_PU_TAB_entry(sx); }
  
  template <>
  FLD* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_FLD_TAB_entry(sx); }
  
  template <>
  ARB* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_ARB_TAB_entry(sx); }
  
  template <>
  TYLIST* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_TYLIST_TAB_entry(sx); }
  
  template <>
  TCON* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_TCON_TAB_entry(sx); }
  
  template <>
  INITO* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_INITO_TAB_entry(sx); }
  
  template <>
  INITV* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_INITV_TAB_entry(sx); }
  
  template <>
  BLK* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_BLK_TAB_entry(sx); }
  
  template <>
  ST_ATTR* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_ST_ATTR_TAB_entry(sx); }
  
  template <>
  LABEL* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_LABEL_TAB_entry(sx); }
  
  template <>
  PREG* xlate_SYMTAB_entry(sexp_t* sx) { return xlate_PREG_TAB_entry(sx); }

}; /* namespace sexp2whirl */



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


TY*
sexp2whirl::xlate_TY_TAB_entry(sexp_t* sx)
{
  using namespace sexp;
  
  TY* ty = TYPE_MEM_POOL_ALLOC(TY, MEM_pu_pool_ptr);
  
  // kind
  sexp_t* knd_sx = get_elem1(sx);
  const char* knd_nm = get_value(knd_sx);
  TY_KIND knd = Name_To_Kind(knd_nm);
  Set_TY_kind(*ty, knd);
  
  // name_idx
  sexp_t* name_idx_sx = get_next(knd_sx);
  sexp_t* nmidx_sx = get_elem1(name_idx_sx);
  STR_IDX nmidx = get_value_ui32(nmidx_sx);
  Set_TY_name_idx(*ty, nmidx);
  
  // mtype, size
  sexp_t* mty_sx = get_next(name_idx_sx);
  const char* mty_nm = get_value(mty_sx);
  TYPE_ID mty = Name_To_Mtype(mty_nm);
  Set_TY_mtype(*ty, mty);
  
  sexp_t* sz_sx = get_next(mty_sx);
  UINT64 sz = get_value_ui64(sz_sx);
  Set_TY_size(*ty, sz);
  
  // flags
  sexp_t* flags_sx = get_next(sz_sx);
  sexp_t* flag1_sx = GetBeginFlgList(flags_sx);
  UINT16 flg = (UINT16)get_value_ui32(flag1_sx); // FIXME: flag parsing
  Set_TY_flags(*ty, flg);
  
  // arb/fld/tylist:         ARRAY, STRUCT, FUNCTION  (respectively)
  // etype/pointed/pu_flags: ARRAY, POINTER, FUNCTION (respectively)
  sexp_t* olist_sx = get_next(flags_sx);
  if (knd == KIND_ARRAY) {
    sexp_t* arb_sx = get_elem0(olist_sx);
    ARB_IDX arb = get_value_ui32(arb_sx);
    ty->Set_arb(arb);
    
    sexp_t* ety_sx = get_elem1(olist_sx);
    TY_IDX ety = GetWhirlTy(ety_sx);
    ty->Set_etype(ety);
  }
  else if (knd == KIND_STRUCT) {
    sexp_t* fld_sx = get_elem0(olist_sx);
    FLD_IDX fld = get_value_ui32(fld_sx);
    ty->Set_fld(fld);    
  }
  else if (knd == KIND_POINTER) {
    sexp_t* basety_sx = get_elem0(olist_sx);
    TY_IDX basety = get_value_ui32(basety_sx);
    Set_TY_pointed(*ty, basety);
  } 
  else if (knd == KIND_FUNCTION) {
    sexp_t* tyl_sx = get_elem0(olist_sx);
    TYLIST_IDX tyl = get_value_ui32(tyl_sx);
    Set_TY_tylist(*ty, tyl);
    
    sexp_t* flgs_sx = get_elem1(olist_sx);
    sexp_t* flg1_sx = GetBeginFlgList(flgs_sx);
    PU_IDX flg = get_value_ui32(flg1_sx);
    ty->u2.pu_flags = flg;
  }
  
  return ty;
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


FLD*
sexp2whirl::xlate_FLD_TAB_entry(sexp_t* sx)
{
  using namespace sexp;
  
  FLD* fld = TYPE_MEM_POOL_ALLOC(FLD, MEM_pu_pool_ptr);
  
  // N.B. We cannot use the Set_FLD_xxx routines because they require
  // a FLD_HANDLE, something that is both annoying and impossible (the
  // FLD_HANDLE constructor assumes 'fld' is already *in* the table).
  
  // name_idx
  sexp_t* name_idx_sx = get_elem1(sx);
  sexp_t* nmidx_sx = get_elem1(name_idx_sx);
  STR_IDX nmidx = get_value_ui32(nmidx_sx);
  fld->name_idx = nmidx;

  // type
  sexp_t* ty_idx_sx = get_next(name_idx_sx);
  TY_IDX ty_idx = GetWhirlTy(ty_idx_sx);
  fld->type = ty_idx;
  
  // ofst, bsize, bofst
  sexp_t* ofst_sx = get_next(ty_idx_sx);
  UINT64 ofst = get_value_ui64(ofst_sx);
  fld->ofst = ofst;

  sexp_t* bsz_sx = get_next(ofst_sx);
  UINT8 bsz = (UINT8)get_value_ui32(bsz_sx);
  fld->bsize = bsz;
  
  sexp_t* bofst_sx = get_next(bsz_sx);
  UINT8 bofst = (UINT8)get_value_ui32(bofst_sx);
  fld->bofst = bofst;
  
  // flags
  sexp_t* flags_sx = get_next(bofst_sx);
  sexp_t* flag1_sx = GetBeginFlgList(flags_sx);
  fld->flags = (UINT16)get_value_ui32(flag1_sx);

  // st
  sexp_t* st_sx = get_next(flags_sx);
  ST_IDX st = GetWhirlSym(st_sx);
  fld->st = st;
  
  return fld;
}


ARB*
sexp2whirl::xlate_ARB_TAB_entry(sexp_t* sx)
{
  using namespace sexp;
  
  ARB* arb = TYPE_MEM_POOL_ALLOC(ARB, MEM_pu_pool_ptr);

  // N.B. We cannot use the Set_ARB_xxx routines because they require
  // a ARB_HANDLE, something that is both annoying and impossible (the
  // ARB_HANDLE constructor assumes 'arb' is already *in* the table).
  
  // flags, dimension, co_dimension
  sexp_t* flags_sx = get_elem1(sx);
  sexp_t* flag1_sx = GetBeginFlgList(flags_sx);
  arb->flags = (UINT16)get_value_ui32(flag1_sx);
  
  sexp_t* dim_sx = get_next(flags_sx);
  UINT16 dim = (UINT16)get_value_ui32(dim_sx);
  arb->dimension = dim;
  
  sexp_t* codim_sx = get_next(dim_sx);
  UINT16 codim = (UINT16)get_value_ui32(codim_sx);
  arb->co_dimension = codim;

  // lbnd_val/(lbnd_var, lbnd_unused)
  sexp_t* lbnd_sx = get_next(codim_sx);
  if (arb->flags & ARB_CONST_LBND) {
    sexp_t* val_sx = get_elem1(lbnd_sx);
    INT64 val = get_value_i64(val_sx);
    arb->Set_lbnd_val(val);
  }
  else {
    ST_IDX st_idx = GetWhirlSym(lbnd_sx);
    arb->Set_lbnd_var(st_idx);
  }
  
  // ubnd_val/(ubnd_var, ubnd_unused)
  sexp_t* ubnd_sx = get_next(lbnd_sx);
  if (arb->flags & ARB_CONST_UBND) {
    sexp_t* val_sx = get_elem1(ubnd_sx);
    INT64 val = get_value_i64(val_sx);
    arb->Set_ubnd_val(val);
  }
  else {
    ST_IDX st_idx = GetWhirlSym(ubnd_sx);
    arb->Set_ubnd_var(st_idx);
  }

  // stride_val/(stride_var, stride_unused)
  sexp_t* stride_sx = get_next(ubnd_sx);
  if (arb->flags & ARB_CONST_STRIDE) {
    sexp_t* val_sx = get_elem1(stride_sx);
    INT64 val = get_value_i64(val_sx);
    arb->Set_stride_val(val);
  }
  else {
    ST_IDX st_idx = GetWhirlSym(stride_sx);
    arb->Set_stride_var(st_idx);
  }
  
  return arb;
}


TYLIST*
sexp2whirl::xlate_TYLIST_TAB_entry(sexp_t* sx)
{
  using namespace sexp;
  
  TYLIST* tyl = TYPE_MEM_POOL_ALLOC(TYLIST, MEM_pu_pool_ptr);
  
  sexp_t* ty_idx_sx = get_elem1(sx);
  TY_IDX ty_idx = GetWhirlTy(ty_idx_sx);
  Set_TYLIST_type(*tyl, ty_idx);
  
  return tyl;
}


TCON*
sexp2whirl::xlate_TCON_TAB_entry(sexp_t* sx)
{
  // see osprey1.0/common/com/targ_const.h
  using namespace sexp;
  
  TCON* tcon = TYPE_MEM_POOL_ALLOC(TCON, MEM_pu_pool_ptr);
  
  FortTk::uint128_t qd; // 16 byte value, a tcon has two of these
  
  // ty
  sexp_t* mty_sx = get_elem1(sx);
  const char* mty_nm = get_value(mty_sx);
  TYPE_ID mty = Name_To_Mtype(mty_nm);
  Set_TCON_ty(*tcon, mty);
  
  // flags
  sexp_t* flags_sx = get_next(mty_sx);
  sexp_t* flag1_sx = GetBeginFlgList(flags_sx);
  UINT32 flg = get_value_ui32(flag1_sx); // FIXME: flag parsing
  tcon->flags = flg;
  
  // vals [quad]
  sexp_t* vals_sx = get_next(flags_sx);
  qd.hi = get_value_ui64(get_elem0(vals_sx));
  qd.lo = get_value_ui64(get_elem1(vals_sx));
  FortTk::assign(tcon->vals.qval, qd);
  
  // cmplxval [quad]
  sexp_t* cmplxval_sx = get_next(vals_sx);
  qd.hi = get_value_ui64(get_elem0(cmplxval_sx));
  qd.lo = get_value_ui64(get_elem1(cmplxval_sx));
  FortTk::assign(tcon->cmplxval.qival, qd);
  
  return tcon;
}


INITO*
sexp2whirl::xlate_INITO_TAB_entry(sexp_t* sx)
{
  // see osprey1.0/common/com/irbdata_defs.h
  using namespace sexp;
  
  INITO* inito = TYPE_MEM_POOL_ALLOC(INITO, MEM_pu_pool_ptr);

  // st_idx
  sexp_t* st_idx_sx = get_elem1(sx);
  ST_IDX st_idx = GetWhirlSym(st_idx_sx);
  inito->st_idx = st_idx;

  // val
  sexp_t* val_sx = get_next(st_idx_sx);
  INITV_IDX val = get_value_ui32(val_sx);
  inito->val = val;
  
  return inito;
}


INITV*
sexp2whirl::xlate_INITV_TAB_entry(sexp_t* sx)
{
  // see osprey1.0/common/com/irbdata_defs.h
  using namespace sexp;
  
  INITV* initv = TYPE_MEM_POOL_ALLOC(INITV, MEM_pu_pool_ptr);
  
  // next
  sexp_t* next_sx = get_elem1(sx);
  INITV_IDX next = get_value_ui32(next_sx);
  initv->next = next;

  // kind
  sexp_t* kind_sx = get_next(next_sx);
  INITVKIND kind = (INITVKIND)get_value_i32(kind_sx);
  initv->kind = kind;
  
  // repeat1
  sexp_t* repeat1_sx = get_next(kind_sx);
  UINT16 repeat1 = (UINT16)get_value_ui32(repeat1_sx);
  initv->repeat1 = repeat1;

  // st/lab/lab1/mtype/tc/blk/pad
  sexp_t* st_sx = get_next(repeat1_sx);
  UINT32 st = get_value_ui32(st_sx);
  initv->u.sto.st = st;
  
  // ofst/st2/repeat2/unused
  sexp_t* ofst_sx = get_next(st_sx);
  INT32 ofst = get_value_i32(ofst_sx);
  initv->u.sto.ofst = ofst;
  
  return initv;
}


BLK*
sexp2whirl::xlate_BLK_TAB_entry(sexp_t* sx)
{
  using namespace sexp;
  
  BLK* blk = TYPE_MEM_POOL_ALLOC(BLK, MEM_pu_pool_ptr);
  
  // size
  sexp_t* size_sx = get_elem1(sx);
  UINT64 size = get_value_ui64(size_sx);
  blk->Set_size(size);
  
  // align
  sexp_t* align_sx = get_next(size_sx);
  UINT16 align = (UINT16)get_value_ui32(size_sx);
  blk->Set_align(align);

  // flags
  sexp_t* flags_sx = get_next(align_sx);
  sexp_t* flag1_sx = GetBeginFlgList(flags_sx);
  UINT16 flags = (UINT16)get_value_ui32(flag1_sx);
  blk->Set_flags(flags);

  // section_idx
  sexp_t* scn_idx_sx = get_next(flags_sx);
  UINT16 scn_idx = (UINT16)get_value_ui32(scn_idx_sx);
  blk->Set_section_idx(scn_idx);
  
  // scninfo_idx
  sexp_t* scninfo_idx_sx = get_next(scn_idx_sx);
  UINT16 scninfo_idx = (UINT16)get_value_ui32(scninfo_idx_sx);
  blk->Set_scninfo_idx(scninfo_idx);
  
  return blk;
}


ST_ATTR*
sexp2whirl::xlate_ST_ATTR_TAB_entry(sexp_t* sx)
{
  using namespace sexp;
  
  ST_ATTR* st_attr = TYPE_MEM_POOL_ALLOC(ST_ATTR, MEM_pu_pool_ptr);
  
  // st_idx
  sexp_t* st_idx_sx = get_elem1(sx);
  ST_IDX st_idx = GetWhirlSym(st_idx_sx);
  Set_ST_ATTR_st_idx(*st_attr, st_idx);
  
  // kind
  sexp_t* knd_sx = get_next(st_idx_sx);
  ST_ATTR_KIND knd = (ST_ATTR_KIND)get_value_i32(knd_sx);
  st_attr->kind = knd;
  
  // reg_id/section_name
  sexp_t* reg_id_sx = get_next(knd_sx);
  PREG_NUM reg_id = get_value_ui32(reg_id_sx);
  Set_ST_ATTR_reg_id(*st_attr, reg_id);
  
  return st_attr;
}


LABEL*
sexp2whirl::xlate_LABEL_TAB_entry(sexp_t* sx)
{
  using namespace sexp;
  
  LABEL* label = TYPE_MEM_POOL_ALLOC(LABEL, MEM_pu_pool_ptr);
  
  // name_idx
  sexp_t* name_idx_sx = get_elem1(sx);
  sexp_t* nmidx_sx = get_elem1(name_idx_sx);
  STR_IDX nmidx = get_value_ui32(nmidx_sx);
  Set_LABEL_name_idx(*label, nmidx);
  
  // kind
  sexp_t* knd_sx = get_next(name_idx_sx);
  LABEL_KIND knd = (LABEL_KIND)get_value_i32(knd_sx);
  Set_LABEL_KIND(*label, knd);

  // flags
  sexp_t* flags_sx = get_next(knd_sx);
  sexp_t* flag1_sx = GetBeginFlgList(flags_sx);
  UINT32 flg = get_value_ui32(flag1_sx);
  label->flags = flg;
  
  return label;
}


PREG*
sexp2whirl::xlate_PREG_TAB_entry(sexp_t* sx)
{
  using namespace sexp;
  
  PREG* preg = TYPE_MEM_POOL_ALLOC(PREG, MEM_pu_pool_ptr);

  // name_idx
  sexp_t* name_idx_sx = get_elem1(sx);
  sexp_t* nmidx_sx = get_elem1(name_idx_sx);
  STR_IDX nmidx = get_value_ui32(nmidx_sx);
  Set_PREG_name_idx(*preg, nmidx);
  
  return preg;
}


//***************************************************************************

