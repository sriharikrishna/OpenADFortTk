// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/whirl2sexp.cxx,v 1.6 2005/01/05 20:51:21 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/whirl2sexp.cxx,v $
//
// Purpose:
//   Translate WHIRL to S-expressions.
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

#include <fstream>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "whirl2sexp.h"
#include "wn2sexp.h"
#include "symtab2sexp.h"

#include <lib/support/WhirlGlobalStateUtils.h>
#include <lib/support/SexpTags.h>

//************************** Forward Declarations ***************************

//***************************************************************************

static void
GenHeader(sexp::ostream& sos);

static void
xlate_IR(sexp::ostream& os, PU_Info* pu_forest, int flags);

static void
xlate_PUForest(sexp::ostream& sos, PU_Info* pu_forest, int flags);

static void 
xlate_PUTree(sexp::ostream& os, PU_Info* pu_tree, int flags);

static void 
xlate_PU(sexp::ostream& os, PU_Info* pu, int flags);

static void 
xlate_WN(sexp::ostream& xos, WN* wn, int flags);

//***************************************************************************
// Implementation of interface routines
//***************************************************************************

void
whirl2sexp::TranslateIR(std::ostream& os, PU_Info* pu_forest, int flags)
{
  sexp::ostream sos(os.rdbuf());
  GenHeader(sos);
  xlate_IR(sos, pu_forest, flags);
  sos.flush();
}

void 
whirl2sexp::TranslatePUTree(std::ostream& os, PU_Info* pu_tree, int flags)
{
  sexp::ostream sos(os.rdbuf());
  GenHeader(sos);
  xlate_PUTree(sos, pu_tree, flags);
  sos.flush();
}

void 
whirl2sexp::TranslatePU(std::ostream& os, PU_Info* pu, int flags)
{
  sexp::ostream sos(os.rdbuf());
  GenHeader(sos);
  xlate_PU(sos, pu, flags);
  sos.flush();
}

void 
whirl2sexp::TranslateWN(std::ostream& os, WN* wn, int flags)
{
  sexp::ostream sos(os.rdbuf());
  GenHeader(sos);
  xlate_WN(sos, wn, flags);
  sos.flush();
}


void 
whirl2sexp::DumpIR(PU_Info* pu_forest, int flags)
{
  TranslateIR(std::cout, pu_forest, flags);
}

void 
whirl2sexp::DumpPUTree(PU_Info* pu_tree, int flags)
{
  TranslatePUTree(std::cout, pu_tree, flags);
}

void 
whirl2sexp::DumpPU(PU_Info* pu, int flags)
{
  TranslatePU(std::cout, pu, flags);
}

void 
whirl2sexp::DumpWN(WN* wn, int flags)
{
  TranslateWN(std::cout, wn, flags);
}


//***************************************************************************
// Helper routines
//***************************************************************************

void
GenHeader(sexp::ostream& sos)
{
  using namespace sexp;

  sos << Comment("*** Summary ***")
      << Comment("WHIRL      ::= (whirl GBL_SYMTAB PU_FOREST)")
      << Comment("GBL_SYMTAB ::= (gbl_symtab GBL_TAB1..GBL_TABn)")
      << Comment("PU_FOREST  ::= (pu_forest PU_TREE*) !! list of PU_TREEs")
      << Comment("PU_TREE    ::= (pu_tree PU PU_TREE*) | NULL")
      << Comment("PU         ::= (pu PU_SYM PU_SYMTAB WN_AST)")
      << Comment("PU_SYMTAB  ::= (pu_symtab PU_TAB1..PU_TABn)")
      << Comment("WN_AST     ::= (WN_OPR WN_ATTRS WN_AST*) | NULL");

  sos << Comment("");

  sos << Comment("*** Symbol Table Details ***")
      << Comment("GBL_SYMTAB ::= (gbl_symtab FILE_INFO ST_TAB PU_TAB")
      << Comment("                  TY_TAB FLD_TAB TYLIST_TAB ARB_TAB")
      << Comment("                  BLK_TAB TCON_TAB INITO_TAB ST_ATTR_TAB")
      << Comment("                  STR_TAB)")
      << Comment("PU_SYMTAB  ::= (pu_symtab ST_TAB INITO_TAB ST_ATTR_TAB")
      << Comment("                  PREG_TAB LABEL_TAB")
      << Comment("")
      << Comment("FILE_INFO   ::= (file_info ...)")
      << Comment("ST_TAB      ::= (st_tab ST_TAB_NTRY*) !! also a PU_SYMTAB")
      << Comment("PU_TAB      ::= (pu_tab PU_TAB_NTRY*)")
      << Comment("TY_TAB      ::= (ty_tab TY_TAB_NTRY*)")
      << Comment("FLD_TAB     ::= (fld_tab ...)")
      << Comment("TYLIST_TAB  ::= (tylist_tab ...)")
      << Comment("ARB_TAB     ::= (arb_tab ...)")
      << Comment("BLK_TAB     ::= (blk_tab ...)")
      << Comment("TCON_TAB    ::= (tcon_tab ...)")
      << Comment("INITO_TAB   ::= (inito_tab ...)   !! also a PU_SYMTAB")
      << Comment("ST_ATTR_TAB ::= (st_attr_tab ...) !! also a PU_SYMTAB")
      << Comment("STR_TAB     ::= (str_tab ...)")
      << Comment("PREG_TAB    ::= (preg_tab ...)    !! PU_SYMTAB")
      << Comment("LABEL_TAB   ::= (label_tab ...)   !! PU_SYMTAB")
      << Comment("")
      << Comment("ST_TAB_NTRY ::= (IDX SYM_CLASS STORAGE_CLASS EXPORT_CLASS NAME_IDX/TCON TYPE/PU/BLK BASE_IDX OFFSET (FLG FLAGS FLAGS_EXT) ST_IDX)")
      << Comment("PU_TAB_NTRY ::= (IDX PROTOTYPE LEXICAL_LEVEL GP_GROUP SRC_LANG TARGET_IDX (FLG FLAGS))")
      << Comment("TY_TAB_NTRY ::= (IDX KIND NAME_IDX MTYPE SIZE (FLG FLAGS) (OTHER))")
      << Comment("")
      << Comment("ST  ::= (st HSTR SCOPE_IDX IDX)")
      << Comment("TY  ::= (ty HSTR IDX)")
      << Comment("")
      << Comment("HSTR (helper string) is a (possibly empty) quoted string.");
  
  sos << Comment("");
  
  sos << Comment("*** AST Details ***")
      << Comment("WN_OPR     ::= operator rtype dtype")
      << Comment("WN_ATTRS   ::= ((attr1 ...) (attr2 ...) (attr3 ...) ...)");
}


void
xlate_IR(sexp::ostream& sos, PU_Info* pu_forest, int flags)
{
  sos << sexp::BegList << sexp::Atom(SexpTags::WHIRL) << sexp::EndLine;
  
  whirl2sexp::TranslateGlobalSymbolTables(sos, flags);
  sos << sexp::EndLine; // end the line 

  xlate_PUForest(sos, pu_forest, flags);
  
  sos << sexp::EndList << sexp::EndLine;
}


void
xlate_PUForest(sexp::ostream& sos, PU_Info* pu_forest, int flags)
{
  sos << sexp::BegList << sexp::Atom(SexpTags::PU_FOREST) << sexp::EndLine;
  
  // Translate each PU_TREE
  for (PU_Info* pu_tree = pu_forest; 
       pu_tree != NULL; pu_tree = PU_Info_next(pu_tree)) {
    xlate_PUTree(sos, pu_tree, flags);
  }
  
  sos << sexp::EndList << sexp::EndLine;
}


void 
xlate_PUTree(sexp::ostream& sos, PU_Info* pu_tree, int flags)
{
  sos << sexp::BegList << sexp::Atom(SexpTags::PU_TREE) << sexp::EndLine;
  
  // Translate the parent PU
  xlate_PU(sos, pu_tree, flags);

  // Translate each child PU
  if (pu_tree) { 
    for (PU_Info* child = PU_Info_child(pu_tree); 
	 child != NULL; child = PU_Info_next(child)) {
      xlate_PU(sos, child, flags);
    }
  }
  
  sos << sexp::EndList << sexp::EndLine;
}


void 
xlate_PU(sexp::ostream& sos, PU_Info* pu, int flags)
{  
  if (!pu) { return; }
  
  PU_SetGlobalState(pu);
  
  //PU& real_pu = PU_Info_pu(pu); 
  //bool isProgram = PU_is_mainpu(real_pu);
  
  ST_IDX st_idx = PU_Info_proc_sym(pu);
  WN* wn_pu = PU_Info_tree_ptr(pu);
  const SCOPE& scope = Scope_tab[CURRENT_SYMTAB];
  
  sos << sexp::BegList << sexp::Atom(SexpTags::PU) << GenSexpSymRef(st_idx)
      << sexp::EndLine;
  whirl2sexp::TranslateLocalSymbolTables(sos, CURRENT_SYMTAB, flags);
  sos << sexp::EndLine;
  
  xlate_WN(sos, wn_pu, flags);
  sos << sexp::EndList << sexp::EndLine;
  
  sos.flush();
}


void 
xlate_WN(sexp::ostream& sos, WN* wn, int flags)
{
  whirl2sexp::TranslateWN(sos, wn);
}

//***************************************************************************
