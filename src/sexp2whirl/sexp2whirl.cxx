// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2whirl.cxx,v 1.2 2004/12/20 15:18:13 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2whirl.cxx,v $
//
// Purpose:
//   Translate S-expression WHIRL to WHIRL.
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

#include "sexp2whirl.h"
//#include "sexp2wn.h"
#include "sexp2symtab.h"

#include <lib/support/WhirlGlobalStateUtils.h>
#include <lib/support/SexpTags.h>
#include <lib/support/sexputil.h>

//************************** Forward Declarations ***************************

//***************************************************************************

static PU_Info*
xlate_IR(sexp_t* ir, int flags);

static PU_Info*
xlate_PUForest(sexp_t* pu_forest, int flags);

static PU_Info*
xlate_PUTree(sexp_t* pu_tree, int flags);

static PU_Info* 
xlate_PU(sexp_t* pu, int flags);

static WN* 
xlate_WN(sexp_t* wn_ast, int flags);

//***************************************************************************
// Implementation of interface routines
//***************************************************************************

PU_Info*
sexp2whirl::TranslateIR(sexp_t* ir, int flags)
{
  return xlate_IR(ir, flags);
}


void 
sexp2whirl::DumpIR(sexp_t* ir, int flags)
{
  const int sz = 1 << 20;
  char* buf = new char[sz];
  
  int rval = print_sexp(buf, sz, ir);
  std::cout << buf << std::endl;
  delete[] buf;
}


//***************************************************************************
// Helper routines
//***************************************************************************

// xlate_IR: Translate the whole WHIRL_IR, return a PU_FOREST and set
// GBL_SYMTAB state.
PU_Info*
xlate_IR(sexp_t* ir, int flags) 
{
  using namespace sexp;
  
  // Sanity check
  FORTTK_ASSERT(is_list(ir), FORTTK_UNEXPECTED_INPUT);  

  sexp_t* tag = get_elem0(ir);
  const char* tagstr = get_value(tag);
  FORTTK_ASSERT(tag && strcmp(tagstr, SexpTags::WHIRL) == 0,
		FORTTK_UNEXPECTED_INPUT);

  // Translate GBL_SYMTAB and PU_FOREST
  sexp_t* gbl_symtab = get_elem1(ir);
  sexp_t* pu_forest  = get_elem2(ir);
  FORTTK_ASSERT(gbl_symtab && pu_forest, FORTTK_UNEXPECTED_INPUT);
  
  sexp2whirl::TranslateGlobalSymbolTables(gbl_symtab, flags);
  PU_Info* pu_forest_whirl = xlate_PUForest(pu_forest, flags);
  
  return pu_forest_whirl;
}


// xlate_PUForest: Translate and return a PU_FOREST, *assuming* that
// GBL_SYMTAB has already been translated.
PU_Info*
xlate_PUForest(sexp_t* pu_forest, int flags)
{
  using namespace sexp;

  // Sanity check
  FORTTK_ASSERT(is_list(pu_forest), FORTTK_UNEXPECTED_INPUT);  
  
  sexp_t* tag = get_elem0(pu_forest);
  const char* tagstr = get_value(tag);
  FORTTK_ASSERT(tag && strcmp(tagstr, SexpTags::PU_FOREST) == 0,
		FORTTK_UNEXPECTED_INPUT);

  MEM_POOL_Push(MEM_pu_nz_pool_ptr);
  MEM_POOL_Push(MEM_pu_pool_ptr);
  
  // Translate the list of PU_TREEs
  PU_Info* pu_forest_whirl = NULL;
  sexp_t* cur_pu_tree = get_elem1(pu_forest);
  if (cur_pu_tree) {
    // Translate head of the PU_TREE list
    pu_forest_whirl = xlate_PUTree(cur_pu_tree, flags);
    PU_Info* cur_pu_tree_whirl = pu_forest_whirl;
    
    // Translate rest of the PU_TREE list
    for (cur_pu_tree = get_next(cur_pu_tree) ; cur_pu_tree; 
	 cur_pu_tree = get_next(cur_pu_tree)) {
      PU_Info* pu_tree_whirl = xlate_PUTree(cur_pu_tree, flags);

      PU_Info_next(cur_pu_tree_whirl) = pu_tree_whirl;
      cur_pu_tree_whirl = pu_tree_whirl;
    }
  }
  
  return pu_forest_whirl;
}


// xlate_PUTree: Translate and return a PU_TREE (a PU and all
// children), *assuming* that GBL_SYMTAB has already been translated.
PU_Info*
xlate_PUTree(sexp_t* pu_tree, int flags)
{
  using namespace sexp;
  
  if (!pu_tree) { return NULL; }

  // Sanity check
  FORTTK_ASSERT(is_list(pu_tree), FORTTK_UNEXPECTED_INPUT);  
  
  sexp_t* tag = get_elem0(pu_tree);
  const char* tagstr = get_value(tag);
  FORTTK_ASSERT(tag && strcmp(tagstr, SexpTags::PU_TREE) == 0,
		FORTTK_UNEXPECTED_INPUT);
  
  // Translate PU
  sexp_t*  pu = get_elem1(pu_tree);
  PU_Info* pu_whirl = xlate_PU(pu, flags);
  
  // Recursively translate PUs children
  PU_Info* cur_child_whirl = NULL;
  for (sexp_t* child = get_elem2(pu_tree); child; child = get_next(child)) {
    PU_Info* child_whirl = xlate_PUTree(child, flags);
    if (cur_child_whirl) {
      PU_Info_next(cur_child_whirl) = child_whirl;
    }
    else {
      PU_Info_child(pu_whirl) = child_whirl;
    }
    cur_child_whirl = child_whirl;
  }
  
  return pu_whirl;
}


// xlate_PU: Translate and return a PU, setting PU_SYMTAB state but
// *assuming* that GBL_SYMTAB has already been translated.
PU_Info*
xlate_PU(sexp_t* pu, int flags)
{ 
  using namespace sexp;

  // Sanity check
  FORTTK_ASSERT(is_list(pu), FORTTK_UNEXPECTED_INPUT);  
  
  sexp_t* tag = get_elem0(pu);
  const char* tagstr = get_value(tag);
  FORTTK_ASSERT(tag && strcmp(tagstr, SexpTags::PU) == 0,
		FORTTK_UNEXPECTED_INPUT);

  // Translate PU_SYMTAB and WHIRL_AST
  sexp_t* pu_sym    = get_elem1(pu);
  sexp_t* pu_symtab = get_elem2(pu);
  sexp_t* wn_ast    = get_elem3(pu);
  
  SYMTAB_IDX stab_lvl = 0; // FIXME: should be able to figure this out
  sexp2whirl::TranslateLocalSymbolTables(pu_symtab, stab_lvl, flags);
  
  PU_Info* pu_whirl = TYPE_MEM_POOL_ALLOC(PU_Info, MEM_pu_pool_ptr);
  PU_Info_init(pu_whirl);
  WN* wn_ast_whirl = xlate_WN(wn_ast, flags);
  Set_PU_Info_tree_ptr(pu_whirl, wn_ast_whirl);
  
  return pu_whirl;
}


// xlate_PUTree: Translate and return a WHIRL_AST, *assuming* that
// GBL_SYMTAB and the relevant PU_SYMTABs have been translated.
WN*
xlate_WN(sexp_t* wn_ast, int flags)
{
  // sexp2whirl::TranslateWN(wn_ast);
  return NULL;
}

//***************************************************************************
