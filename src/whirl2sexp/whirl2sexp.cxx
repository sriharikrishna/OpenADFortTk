// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/whirl2sexp.cxx,v 1.3 2004/08/09 14:34:53 eraxxon Exp $

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

//************************** Forward Declarations ***************************

//***************************************************************************

static void
GenHeader(sexp::ostream& sos);

static void
xlate_IR(sexp::ostream& os, PU_Info* pu_forest, int flags);

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
  sos << Comment("WHIRL_IR   ::= (GBL_SYMTAB PU_FOREST)")
      << Comment("GBL_SYMTAB ::= (...)")
      << Comment("PU_FOREST  ::= (PU_TREE*)")
      << Comment("PU_TREE    ::= (PU PU_TREE*) | NULL")
      << Comment("PU_SYMTAB  ::= ...")
      << Comment("PU         ::= (PU_SYMTAB WHIRL_AST)")
      << Comment("WHIRL_AST  ::= (WN_OPR WN_ATTRS WHIRL_AST*) | NULL")
      << Comment("WN_ATTRS   ::= ((attr1 ...) (attr2 ...) (attr3 ...) ...)");
}


void
xlate_IR(sexp::ostream& sos, PU_Info* pu_forest, int flags)
{
  sos << sexp::BegList << sexp::Atom("whirl") << sexp::EndLine;

  whirl2sexp::TranslateGlobalSymbolTables(sos);
  
  if (!pu_forest) { return; }
  sos << sexp::EndLine; // end the line now that we know something comes next
  
  // Translate each PU-tree
  for (PU_Info* pu_tree = pu_forest; 
       pu_tree != NULL; pu_tree = PU_Info_next(pu_tree)) {
    xlate_PUTree(sos, pu_tree, flags);
  }
  
  sos << sexp::EndList << sexp::EndLine;
}


void 
xlate_PUTree(sexp::ostream& sos, PU_Info* pu_tree, int flags)
{
  if (!pu_tree) { return; }
  
  // Translate the parent PU
  xlate_PU(sos, pu_tree, flags);

  // Translate each child PU
  for (PU_Info* child = PU_Info_child(pu_tree); 
       child != NULL; child = PU_Info_next(child)) {
    xlate_PU(sos, child, flags);
  }
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
  
  sos << sexp::BegList << sexp::Atom("pu") << GenSexpSymRef(st_idx)
      << sexp::EndLine;
  whirl2sexp::TranslateLocalSymbolTables(sos, CURRENT_SYMTAB);
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
