// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/symtab2sexp.cxx,v 1.2 2004/08/06 17:29:53 eraxxon Exp $

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

//************************** Forward Declarations ***************************

using namespace whirl2sexp;
using namespace sexp; // for sexp::ostream, etc

//***************************************************************************

//***************************************************************************
// Translate symbol tables
//***************************************************************************

void 
whirl2sexp::TranslateGlobalSymbolTables(sexp::ostream& sos)
{
  // There are GLOBAL_SYMTAB_TABLES [13] number of global tables. 
  
  sos << BegList << Atom("gobal_symtab") << EndLine;

  xlate_FILE_INFO(sos);
  sos << EndLine;

  xlate_ST_TAB(sos, GLOBAL_SYMTAB);
  sos << EndLine;
  
  xlate_PU_TAB(sos);
  sos << EndLine;

  xlate_TY_TAB(sos);
  sos << EndLine;
  
  xlate_BLK_TAB(sos);
  sos << EndLine;
  
  xlate_TCON_TAB(sos);
  sos << EndLine;
  
  xlate_INITO_TAB(sos, GLOBAL_SYMTAB);
  sos << EndLine;
  
  xlate_ST_ATTR_TAB(sos, GLOBAL_SYMTAB);
  
  sos << EndList;
}


void 
whirl2sexp::TranslateLocalSymbolTables(sexp::ostream& sos, 
				       SYMTAB_IDX symtab_lvl)
{
  // There are LOCAL_SYMTAB_TABLES [5] number of global tables. 

  xlate_ST_TAB(sos, symtab_lvl);
}


// Dump_DST (stdout);

#if 0
// Global
//   FILE_INFO	File_info;
//   SYMBOL_TABLE  St_Table;
//   PU_TAB	Pu_Table;
//   TYPE_TABLE	Ty_Table;
// ?   FLD_TAB	Fld_Table
// ?   TYLIST_TAB Tylist_Table
// ?   ARB_TAB	Arb_Table
//   BLK_TAB	Blk_Table;
//   TCON_TAB	Tcon_Table;
// ?   TCON_STR_TAB ??
//   INITO_TABLE   Inito_Table;
// ? INITV_TAB	   Initv_Table;
//   ST_ATTR_TABLE St_Attr_Table;
// ? STR_TAB
// Local
//   ST, INITO, ST_ATTR
//   PREG_TABLE	 Preg_Table;
//   LABEL_TABLE Label_Table;

// Print all local symbol tables corresponding to a PU
void
Print_local_symtab (FILE *f, const SCOPE& scope)
{
  // Print the function name
  fprintf (f, "\n%sSYMTAB for %s: level %d, st %d, label %d, preg %d,"
	   " inito %d, st_attr %d\n%s\n", DBar, ST_name (scope.st),
	   PU_lexical_level (scope.st), scope.st_tab->Size () - 1,
	   scope.label_tab->Size () - 1, scope.preg_tab->Size () - 1,
	   scope.inito_tab->Size () - 1, scope.st_attr_tab->Size () - 1, DBar);
  
  For_all_entries (*scope.st_tab, print_op<ST> (f), 1);
  For_all_entries (*scope.label_tab, print_op<LABEL> (f), 1);
  For_all_entries (*scope.preg_tab, print_op<PREG> (f), 1);
  For_all_entries (*scope.inito_tab, print_op<INITO> (f), 1);
  For_all_entries (*scope.st_attr_tab, print_op<ST_ATTR> (f), 1);
}
#endif


//***************************************************************************
// Translate individual tables
//***************************************************************************

// Note: 'For_all' applies 'operator()' to every entry of the
// respective table.

void 
whirl2sexp::xlate_FILE_INFO(sexp::ostream& sos)
{
  sos << BegList << Atom("file_info");
  
  UINT gp = (UINT)FILE_INFO_gp_group(File_info);
  sos << Atom(gp) << GenBeginFlgList(File_info.flags) << EndList;
  
  sos << EndList;
}

void 
whirl2sexp::xlate_ST_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl)
{
  sos << BegList << Atom("st_tab") << EndLine;
  For_all(St_Table, stab_lvl, xlate_SYMTAB_entry_op<ST>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_ST_TAB(sexp::ostream& sos, const SCOPE& scope)
{
  sos << BegList << Atom("st_tab") << EndLine;
  For_all(*scope.st_tab, xlate_SYMTAB_entry_op<ST>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_PU_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom("pu_tab") << EndLine;
  For_all(Pu_Table, xlate_SYMTAB_entry_op<PU>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_TY_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom("ty_tab") << EndLine;
  For_all(Ty_Table, xlate_SYMTAB_entry_op<TY>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_BLK_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom("blk_tab") << EndLine;
  For_all(Blk_Table, xlate_SYMTAB_entry_op<BLK>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_TCON_TAB(sexp::ostream& sos)
{
  sos << BegList << Atom("tcon_tab") << EndLine;
  For_all(Tcon_Table, xlate_SYMTAB_entry_op<TCON>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_INITO_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl)
{
  sos << BegList << Atom("inito_tab") << EndLine;
  For_all(Inito_Table, stab_lvl, xlate_SYMTAB_entry_op<INITO>(sos));
  sos << EndList;
}

void 
whirl2sexp::xlate_ST_ATTR_TAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl)
{
  sos << BegList << Atom("st_attr_tab") << EndLine;
  For_all(St_Attr_Table, stab_lvl, xlate_SYMTAB_entry_op<ST_ATTR>(sos));
  sos << EndList;
}


#if 0
void 
whirl2sexp::xlate_PREGTAB(sexp::ostream& sos, SYMTAB_IDX stab_lvl)
{
  For_all(Preg_Table, stab_lvl, xlate_PREG_TAB(sos, stab_lvl));
}
#endif


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
  sos << BegList << Atom(stclass_nm) << Atom(stclass) << EndList;
  
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
      << Atom(A_DQUOTE, stsclass_nm) << Atom(stsclass)
      << Atom(A_DQUOTE, stexport_nm) << Atom(stexport) << EndList;
  
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

  // FIXME
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
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, TY* ty)
{
  using namespace sexp::IOFlags;
  
  sos << BegList << Atom(idx);
  
  // kind
  TY_KIND knd = TY_kind(*ty);
  const char* kndnm = Kind_Name(knd);
  sos << BegList << Atom(kndnm) << Atom(knd) << EndList;
  
  // name_idx
  STR_IDX nmidx = TY_name_idx(*ty);
  const char* nm = TY_name(*ty);
  sos << BegList << Atom(A_DQUOTE, nm) << Atom(nmidx) << EndList;
  
  // mtype, size
  TYPE_ID mty = TY_mtype(*ty);
  UINT64 sz   = TY_size(*ty);
  const char* mtynm = MTYPE_name(mty);
  sos << BegList << Atom(mtynm) << Atom(mty) << Atom(sz) << EndList;

  // flags
  UINT16 flg = TY_flags(*ty);
  
  // fld/tylist/arb, etype/pointed/pu_flags

  // FIXME: 
  //FLD_HANDLE fld = TY_fld(ty); 
  //TYLIST_IDX tyl = TY_tylist(ty);
  //ARB_HANDLE arb = TY_arb(ty);

  //TY_IDX ty_idx = TY_etype(ty);
  //TY_IDX ty_idx = TY_pointed(ty);
  //PU_IDX pu_flg = ty->Pu_flags();
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, BLK* blk)
{
  sos << BegList << Atom(idx);

#if 0  
  sos << Atom(blk->size) << Atom(blk->align)
      << GenBeginFlgList(blk->flags) << EndList
      << Atom(blk->section_idx) << Atom(blk->scninfo_idx);
#endif  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, TCON* tcon)
{
  sos << BegList << Atom(idx);
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, INITO* inito)
{
  sos << BegList << Atom(idx);
  
  // st_idx, val
  sos << GenSexpSym(inito->st_idx) << Atom(inito->val);
  
  sos << EndList;
}


void
whirl2sexp::xlate_SYMTAB_entry(sexp::ostream& sos, UINT32 idx, ST_ATTR* sta)
{
  sos << BegList << Atom(idx);
  sos << EndList;
}

//***************************************************************************

