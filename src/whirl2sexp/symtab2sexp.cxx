// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/symtab2sexp.cxx,v 1.5 2004/12/20 15:18:30 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/symtab2sexp.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "wn2sexp.h"
#include "symtab2sexp.h"

#include <lib/support/SexpTags.h>

//************************** Forward Declarations ***************************

using namespace whirl2sexp;
using namespace sexp; // for sexp::ostream, etc


//***************************************************************************
// Translate symbol tables
//***************************************************************************

void 
whirl2sexp::TranslateGlobalSymbolTables(sexp::ostream& sos, int flags)
{
  // There are GLOBAL_SYMTAB_TABLES [13] number of global tables. 
  //   FILE_INFO     (File_info)
  //   SYMBOL_TABLE  (St_Table)
  //   PU_TAB        (Pu_Table)
  //   TYPE_TABLE    (Ty_Table)
  // -   FLD_TAB     (Fld_Table)
  // -   TYLIST_TAB  (Tylist_Table)
  // -   ARB_TAB     (Arb_Table)
  //   BLK_TAB       (Blk_Table)
  //   TCON_TAB      (Tcon_Table)
  //   INITO_TABLE   (Inito_Table)
  // - INITV_TAB     (Initv_Table)
  //   ST_ATTR_TABLE (St_Attr_Table)
  // ? STR_TABLE     (Str_Table) (strtab.cxx)
  // ?   TCON_STR_TAB
  
  sos << BegList << Atom(SexpTags::GBL_SYMTAB) << EndLine;

  xlate_FILE_INFO(sos);
  sos << EndLine;

  xlate_ST_TAB(sos, GLOBAL_SYMTAB);
  sos << EndLine;
  
  xlate_PU_TAB(sos);
  sos << EndLine;

  xlate_TY_TAB(sos);
  sos << EndLine;

  xlate_FLD_TAB(sos);
  sos << EndLine;

  xlate_TYLIST_TAB(sos);
  sos << EndLine;

  xlate_ARB_TAB(sos);
  sos << EndLine;
  
  xlate_BLK_TAB(sos);
  sos << EndLine;
  
  xlate_TCON_TAB(sos);
  sos << EndLine;
  
  xlate_INITO_TAB(sos, GLOBAL_SYMTAB);
  sos << EndLine;
  
  xlate_ST_ATTR_TAB(sos, GLOBAL_SYMTAB);
  sos << EndLine;
  
  xlate_STR_TAB(sos);

  // Dump_DST (stdout); (cf. ir_a2b.cxx)
  
  sos << EndList;
}


void 
whirl2sexp::TranslateLocalSymbolTables(sexp::ostream& sos, SYMTAB_IDX stab_lvl,
				       int flags)
{
  // There are LOCAL_SYMTAB_TABLES [5] number of global tables. 
  //   ST
  //   INITO
  //   ST_ATTR
  //   PREG_TABLE  (Preg_Table)
  //   LABEL_TABLE (Label_Table)

  sos << BegList << Atom(SexpTags::PU_SYMTAB) << EndLine;
  
  xlate_ST_TAB(sos, stab_lvl);
  sos << EndLine;

  xlate_INITO_TAB(sos, stab_lvl);
  sos << EndLine;
  
  xlate_ST_ATTR_TAB(sos, stab_lvl);
  sos << EndLine;
  
  xlate_PREG_TAB(sos, stab_lvl);
  sos << EndLine;

  xlate_LABEL_TAB(sos, stab_lvl);
  
  sos << EndList;
}


//***************************************************************************
// Translate individual tables
//***************************************************************************

// Note: 'For_all' applies 'operator()' to every entry of the
// respective table.

void 
whirl2sexp::xlate_FILE_INFO(sexp::ostream& sos)
{
  sos << BegList << Atom(SexpTags::FILE_INFO);
  
  UINT gp = (UINT)FILE_INFO_gp_group(File_info);
  sos << Atom(gp) << GenBeginFlgList(File_info.flags) << EndList;
  
  sos << EndList;
}

void 
whirl2sexp::xlate_ST_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl)
{
  sos << BegList << Atom(SexpTags::ST_TAB) << EndLine;
  For_all(St_Table, stab_lvl, xlate_SYMTAB_entry_op<ST>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_ST_TAB(sexp::ostream& sos, const SCOPE& scope)
{
  sos << BegList << Atom(SexpTags::ST_TAB) << EndLine;
  For_all(*scope.st_tab, xlate_SYMTAB_entry_op<ST>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_PU_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom(SexpTags::PU_TAB) << EndLine;
  For_all(Pu_Table, xlate_SYMTAB_entry_op<PU>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_TY_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom(SexpTags::TY_TAB) << EndLine;
  For_all(Ty_Table, xlate_SYMTAB_entry_op<TY>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_FLD_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom(SexpTags::FLD_TAB) << EndLine;
  For_all(Fld_Table, xlate_SYMTAB_entry_op<FLD>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_TYLIST_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom(SexpTags::TYLIST_TAB) << EndLine;
  For_all(Tylist_Table, xlate_SYMTAB_entry_op<TYLIST>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_ARB_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom(SexpTags::ARB_TAB) << EndLine;
  For_all(Arb_Table, xlate_SYMTAB_entry_op<ARB>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_BLK_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom(SexpTags::BLK_TAB) << EndLine;
  For_all(Blk_Table, xlate_SYMTAB_entry_op<BLK>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_TCON_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom(SexpTags::TCON_TAB) << EndLine;
  For_all(Tcon_Table, xlate_SYMTAB_entry_op<TCON>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_INITO_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl)
{
  sos << BegList << Atom(SexpTags::INITO_TAB) << EndLine;
  For_all(Inito_Table, stab_lvl, xlate_SYMTAB_entry_op<INITO>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_INITV_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom(SexpTags::INITV_TAB) << EndLine;
  For_all(Initv_Table, xlate_SYMTAB_entry_op<INITV>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_ST_ATTR_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl)
{
  sos << BegList << Atom(SexpTags::ST_ATTR_TAB) << EndLine;
  For_all(St_Attr_Table, stab_lvl, xlate_SYMTAB_entry_op<ST_ATTR>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_STR_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom(SexpTags::STR_TAB) << EndLine; 
  
  // see osprey1.0/common/com/strtab.h
  // const char* str = Index_To_Str(STR_IDX idx);
  // extern UINT32 STR_Table_Size ();
  
  sos << EndList;
}



void 
whirl2sexp::xlate_PREG_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl)
{
  sos << BegList << Atom(SexpTags::PREG_TAB) << EndLine;
  // osprey1.0/common/com/symtab_utils.h defines this without 'stab_lvl' arg!
  //For_all(Preg_Table, stab_lvl, xlate_SYMTAB_entry_op<PREG>(sos));
  For_all_entries(*Scope_tab[stab_lvl].preg_tab, 
		  xlate_SYMTAB_entry_op<PREG>(sos), 1);
  sos << EndList;
}

void 
whirl2sexp::xlate_LABEL_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl)
{
  sos << BegList << Atom(SexpTags::LABEL_TAB) << EndLine;
  // osprey1.0/common/com/symtab_utils.h defines this without 'stab_lvl' arg!
  //For_all(Label_Table, stab_lvl, xlate_SYMTAB_entry_op<LABEL>(sos));
  For_all_entries(*Scope_tab[stab_lvl].label_tab, 
		  xlate_SYMTAB_entry_op<LABEL>(sos), 1);
  sos << EndList;
}


//***************************************************************************
// Function objects to translate individual table entries
//***************************************************************************

void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, ST* st)
{
  using namespace sexp::IOFlags;
  
  sos << BegList << Atom(idx);
  
  // sym_class
  ST_CLASS stclass = ST_class(st);
  const char* stclass_nm = Class_Name(stclass);
  sos << Atom(stclass_nm);
  
  // name_idx/tcon
  STR_IDX nmidx = ST_name_idx(st); // or TCON_IDX  
  const char* nm = (stclass != CLASS_CONST) ? ST_name(st) : NULL;
  sos << BegList << Atom(A_DQUOTE, nm) << Atom(nmidx) << EndList;
  
  // storage_class, export class
  ST_SCLASS stsclass = ST_sclass(st);
  ST_EXPORT stexport = ST_export(st);
  const char* stsclass_nm = Sclass_Name(stsclass);
  const char* stexport_nm = Export_Name(stexport);
  sos << BegList << Atom("xclass") 
      << Atom(stsclass_nm) << Atom(stexport_nm) << EndList;
  
  // type/pu/blk
  if (stclass == CLASS_FUNC) {
    PU_IDX stpu = ST_pu(st);
    sos << Atom(stpu); // FIXME
  }
  else if (stclass == CLASS_BLOCK) {
    BLK_IDX stblk = ST_blk(st);
    sos << Atom(stblk); // FIXME
  }
  else {
    TY_IDX sttype = ST_type(st);
    sos << GenSexpTy(sttype);
  }
  
  // base_idx, offset
  ST_IDX stbase_idx = ST_base_idx(st);
  UINT64 oset = ST_ofst(st);
  sos << GenSexpSym(stbase_idx) << Atom(oset);
  
  // flags/flags_ext
  sos << GenBeginFlgList(st->flags) << Atom(A_HEX, st->flags_ext) << EndList;
  
  // st_idx
  ST_IDX st_idx = ST_st_idx(st);
  sos << GenSexpSym(st_idx);
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, PU* pu)
{
  sos << BegList << Atom(idx);

  TY_IDX ty_idx = PU_prototype(*pu);
  UINT lvl = (UINT)PU_lexical_level(*pu);
  UINT gp = (UINT)PU_gp_group(*pu);
  UINT64 srclang = PU_src_lang(*pu);
  TARGET_INFO_IDX targidx = PU_target_idx(*pu);

  sos << GenSexpTy(ty_idx) 
      << Atom(lvl) << Atom(gp) << Atom(srclang) << Atom(targidx) 
      << GenBeginFlgList(pu->flags) << EndList;
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, TY* typ)
{
  using namespace sexp::IOFlags;

  TY& ty = *typ;
  
  sos << BegList << Atom(idx);
  
  // kind
  TY_KIND knd = TY_kind(ty);
  const char* kndnm = Kind_Name(knd);
  sos << Atom(kndnm);
  
  // name_idx
  STR_IDX nmidx = TY_name_idx(ty);
  const char* nm = TY_name(ty);
  sos << BegList << Atom(A_DQUOTE, nm) << Atom(nmidx) << EndList;
  
  // mtype, size
  TYPE_ID mty = TY_mtype(ty);
  UINT64 sz   = TY_size(ty);
  const char* mtynm = Mtype_Name(mty);
  sos << Atom(mtynm) << Atom(sz);
  
  // flags
  UINT16 flg = TY_flags(ty);
  sos << GenBeginFlgList(flg) << EndList;
  
  // arb/fld/tylist:         ARRAY, STRUCT, FUNCTION  (respectively)
  // etype/pointed/pu_flags: ARRAY, POINTER, FUNCTION (respectively)
  if (knd == KIND_ARRAY) {
    ARB_HANDLE arb = TY_arb(ty); // FIXME more info
    TY_IDX ety = TY_etype(ty);
    sos << Atom(arb.Idx()) << GenSexpTy(ety);
  }
  else if (knd == KIND_STRUCT) {
    FLD_HANDLE fld = TY_fld(ty); // FIXME more info
    sos << Atom(fld.Idx()) << Atom(0);
  }
  else if (knd == KIND_POINTER) {
    TY_IDX basety = TY_pointed(ty);
    sos << Atom(0) << GenSexpTy(basety);
  } 
  else if (knd == KIND_FUNCTION) {
    TYLIST_IDX tyl = TY_tylist(ty);
    PU_IDX flg = ty.Pu_flags();
    sos << Atom(tyl) << GenBeginFlgList(flg) << EndList;
  }
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, FLD* fld)
{
  using namespace sexp::IOFlags;
  
  FLD_HANDLE fldh(fld, (FLD_IDX)idx);
  
  sos << BegList << Atom(idx);
  
  // name_idx
  STR_IDX nmidx = FLD_name_idx(fldh);
  const char* nm = FLD_name(fldh);
  sos << BegList << Atom(A_DQUOTE, nm) << Atom(nmidx) << EndList;
  
  // type, ofst, bsize, bofst, flags, st
  TY_IDX ty_idx = fld->type; // FLD_type(fldh) is not a simple accessor!
  sos << GenSexpTy(ty_idx);
  
  UINT64 ofst = FLD_ofst(fldh);
  UINT8 bsz = FLD_bsize(fldh);
  UINT8 bofst = FLD_bofst(fldh);
  sos << Atom(ofst) << Atom(bsz) << Atom(bofst);
  
  UINT16 flg = FLD_flags(fldh);
  sos << GenBeginFlgList(flg) << EndList;
  
  ST_IDX st_idx = FLD_st(fldh);
  sos << GenSexpSym(st_idx);
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, TYLIST* tyl)
{
  sos << BegList << Atom(idx);
  
  TY_IDX ty_idx = TYLIST_type(*tyl);
  sos << GenSexpTy(ty_idx);
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, ARB* arb)
{
  using namespace sexp::IOFlags;
  
  ARB_HANDLE arbh(arb, (ARB_IDX)idx);
  
  sos << BegList << Atom(idx);
  
  // flags, dimension, co_dimension
  UINT16 flg = ARB_flags(arbh);
  UINT16 dim = ARB_dimension(arbh);
  UINT16 codim = ARB_co_dimension(arbh);
  sos << GenBeginFlgList(flg) << EndList << Atom(dim) << Atom(codim);
  
  // lbnd_val/(lbnd_var, lbnd_unused)
  if (ARB_const_lbnd(arbh)) {
    INT64 val = ARB_lbnd_val(arbh);
    sos << BegList << Atom("const") << Atom(val) << EndList;
  } 
  else {
    ST_IDX st_idx = ARB_lbnd_var(arbh);
    sos << GenSexpSym(st_idx);
  }
  
  // ubnd_val/(ubnd_var, ubnd_unused)
  if (ARB_const_ubnd(arbh)) {
    INT64 val = ARB_ubnd_val(arbh);
    sos << BegList << Atom("const") << Atom(val) << EndList;
  }
  else {
    ST_IDX st_idx = ARB_ubnd_var(arbh);
    sos << GenSexpSym(st_idx);
  }
  
  // stride_val/(stride_var, stride_unused)
  if (ARB_const_stride(arbh)) {
    INT64 val = ARB_stride_val(arbh);
    sos << BegList << Atom("const") << Atom(val) << EndList;
  }
  else {
    ST_IDX st_idx = ARB_stride_var(arbh);
    sos << GenSexpSym(st_idx);
  }
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, BLK* blk)
{
  sos << BegList << Atom(idx);

  sos << Atom(blk->Size()) << Atom(blk->Align())
      << GenBeginFlgList(blk->Flags()) << EndList
      << Atom(blk->Section_idx()) << Atom(blk->Scninfo_idx());

  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, TCON* tcon)
{
  // see osprey1.0/common/com/targ_const.h
  using namespace sexp::IOFlags;

  sos << BegList << Atom(idx);
  
  whirl2sexp::uint128_t qd; // 16 byte value, a tcon has two of these
  
  TYPE_ID mty = TCON_ty(*tcon);
  UINT32 flg = tcon->flags;
  const char* mtynm = Mtype_Name(mty);
  sos << Atom(mtynm) << GenBeginFlgList(flg) << EndList;
  
  qd = tcon->vals.qval;      // uses operator=
  sos << Atom(A_HEX, qd.hi) << Atom(A_HEX, qd.lo);
  
  qd = tcon->cmplxval.qival; // uses operator=
  sos << Atom(A_HEX, qd.hi) << Atom(A_HEX, qd.lo);
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, INITO* inito)
{
  // see osprey1.0/common/com/irbdata_defs.h
  sos << BegList << Atom(idx);
  
  // st_idx, val
  sos << GenSexpSym(inito->st_idx) << Atom(inito->val);
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, INITV* initv)
{
  // see osprey1.0/common/com/irbdata_defs.h
  sos << BegList << Atom(idx);
  
  // next, kind, repeat1
  sos << Atom(initv->next) << Atom(initv->kind) << Atom(initv->repeat1);
  
  // st/lab/lab1/mtype/tc/blk/pad, ofst/st2/repeat2/unused
  sos << Atom(initv->St()) << Atom(initv->Ofst());
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, ST_ATTR* sta)
{
  sos << BegList << Atom(idx);
  
  // st_idx, kind
  ST_IDX st_idx = ST_ATTR_st_idx(*sta);
  ST_ATTR_KIND knd = ST_ATTR_kind(*sta);
  sos << GenSexpSym(st_idx) << Atom(knd);  // FIXME: need a name for knd?
  
  // reg_id/section_name
  PREG_NUM val = ST_ATTR_reg_id(*sta);
  sos << Atom(val);
  
  sos << EndList;
}



void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, PREG* preg)
{
  using namespace sexp::IOFlags;
  
  sos << BegList << Atom(idx);
  
  STR_IDX nmidx = PREG_name_idx(*preg);
  const char* nm = PREG_name(*preg);
  sos << BegList << Atom(A_DQUOTE, nm) << Atom(nmidx) << EndList;
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, LABEL* lbl)
{
  using namespace sexp::IOFlags;

  sos << BegList << Atom(idx);
  
  // name_idx
  STR_IDX nmidx = LABEL_name_idx(*lbl);
  const char* nm = LABEL_name(*lbl);
  sos << BegList << Atom(A_DQUOTE, nm) << Atom(nmidx) << EndList;
    
  // kind, flags
  UINT32 knd = (UINT32)LABEL_kind(*lbl);
  UINT32 flg = (UINT32)lbl->flags;
  sos << Atom(knd) << GenBeginFlgList(flg) << EndList;
  
  sos << EndList;
}


//***************************************************************************

