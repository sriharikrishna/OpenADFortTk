// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.cxx,v 1.8 2003/06/02 13:43:22 eraxxon Exp $
// -*-C++-*-

// * BeginCopyright *********************************************************
/*
  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan
*/
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/w2f_driver.cxx
//
//***************************************************************************

//************************** System Include Files ***************************

#include <time.h>
#include <errno.h>          /* For sys_errlist */
#include <fstream>

//************************** Open64 Include Files ***************************

#include "Open64BasicTypes.h"

#include <sys/elf_whirl.h>  /* for WHIRL_REVISION */
#include "config_flist.h"   /* For FLIST command line parameters */
#include "file_util.h"      /* For Last_Pathname_Component */
#include "flags.h"          /* for OPTION_GROUP */
#include "timing.h"         /* Start/Stop Timer */

//*************************** User Include Files ****************************

#include "whirl2xaif.h"
#include "whirl2f_common.h"
#include "PUinfo.h"
#include "w2cf_parentize.h" /* For W2CF_Parent_Map and W2FC_Parentize */
#include "st2xaif.h"
#include "wn2xaif.h"
#include "wn2xaif_stmt.h"

#include "Pro64IRInterface.h"
#include <OpenAnalysis/CallGraph/CallGraph.h> //CALLGRAPH

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//***************************************************************************

// REMOVE
// statements that can be skipped in w2f translation
#define W2F_MAX_SKIP_ITEMS 128
static W2CF_SKIP_ITEM Skip[W2F_MAX_SKIP_ITEMS+1];
static INT Next_Skip_Item = 0;

/* W2F status information */
static BOOL         W2F_Initialized = FALSE;
static MEM_POOL     W2F_Parent_Pool;

/* External data set through -FLIST command-line options */
// Set in W2F_Init_Options(..)
BOOL W2F_Enabled = TRUE;          /* Invoke W2F */
BOOL W2F_Verbose = TRUE;          /* Show translation information */
BOOL W2F_No_Pragmas = FALSE;      /* By default, emit pragmas */
BOOL W2F_Emit_Prefetch = FALSE;   /* Emit comments for prefetches */
BOOL W2F_Emit_All_Regions = FALSE;/* Emit cmplr-generated regions */
BOOL W2F_Emit_Linedirs = FALSE;   /* Emit preproc line-directives */
BOOL W2F_Emit_Nested_PUs = TRUE;  /* Emit code for nested PUs (FALSE) */

/* External data set through the API or otherwise */
BOOL W2F_Only_Mark_Loads = FALSE; /* Only mark, do not translate loads */
BOOL WN2F_F90_pu = FALSE;         /* Global variable indicating F90 or F77 */

WN_MAP *W2F_Construct_Map = NULL;    /* Construct id mapping for prompf */
WN_MAP  W2F_Frequency_Map = WN_MAP_UNDEFINED; /* Frequency mapping */

//***************************************************************************

static void W2F_Enter_Global_Symbols(void);

static void W2F_Undo_Whirl_Side_Effects(void);

static BOOL Check_Initialized(const char *caller_name);
static BOOL Check_PU_Pushed(const char *caller_name);



static void 
TranslateScopeHierarchy(xml::ostream& xos, PU_Info* pu_tree, XlationContext& ctxt);

static void
TranslateScopeHierarchyPU(xml::ostream& xos, PU_Info* pu, UINT32 parentId, 
			  UINT32& nextId, XlationContext& ctxt);

static void 
TranslatePU(xml::ostream& xos, PU_Info *pu, UINT32 vertexId,
	    XlationContext& ctxt);

static void 
TranslateWNPU(xml::ostream& xos, WN* pu, XlationContext& ctxt);


static void 
DumpTranslationHeaderComment(xml::ostream& xos);

//***************************************************************************
// 
//***************************************************************************

void
whirl2xaif::TranslateIR(std::ostream& os, PU_Info *pu_tree)
{
  if (!pu_tree) { return; }
  
  Pro64IRInterface irInterface;
  xml::ostream xos(os.rdbuf());
  XlationContext ctxt;

  W2F_Init(); // FIXME
  DumpTranslationHeaderComment(xos); // FIXME

  // 1. Create CallGraph
  Pro64IRProcIterator irProcIter(pu_tree);
  ST* st = ST_ptr(PU_Info_proc_sym(pu_tree));
  CallGraph cgraph(irInterface, &irProcIter, (SymHandle)st);
  //cgraph->dump(cerr);
  
  xos << BegElem("xaif:CallGraph");
  
  TranslateScopeHierarchy(xos, pu_tree, ctxt);

  // 2. Dump CallGraph vertices
  for (CallGraph::NodesIterator nodeIt(cgraph); (bool)nodeIt; ++nodeIt) {
    CallGraph::Node* n = dynamic_cast<CallGraph::Node*>((DGraph::Node*)nodeIt);
    TranslatePU(xos, (PU_Info*)n->GetDef(), n->getID(), ctxt);
  }
  
  // 3. Dump CallGraph edges
  for (CallGraph::EdgesIterator edgesIt(cgraph); (bool)edgesIt; ++edgesIt) {
    CallGraph::Edge* e =
      dynamic_cast<CallGraph::Edge*>((DGraph::Edge*)edgesIt);
    CallGraph::Node* n1 = dynamic_cast<CallGraph::Node*>(e->source());
    CallGraph::Node* n2 = dynamic_cast<CallGraph::Node*>(e->sink());
    
    xos << BegElem("xaif:CallGraphEdge") << Attr("edge_id", ctxt.GetNewEId())
	<< Attr("source", n1->getID())
	<< Attr("target", n2->getID()) << EndElem; // FIXME: DumpGraphEdge
  }
  
  // 4. Done!
  xos << EndElem; /* xaif:CallGraph */
  
  W2F_Fini(); // FIXME
}

//***************************************************************************

static void
TranslateScopeHierarchy(xml::ostream& xos, PU_Info* pu_tree, 
			XlationContext& ctxt)
{
  // For now we implicitly create the ScopeHierarchy/ScopeGraph using
  // DFS-style iteration of PUs.  During translation of the
  // ScopeHierarchy we create a ST_TAB* to Scope vertex_id map for
  // later symbol references.

  UINT32 nextId = 0; // 0 is NULL
  StabToScopeIdMap& map = ctxt.GetStabToScopeIdMap();

  xos << BegElem("xaif:ScopeHierarchy");

  // Translate global symbol table
  UINT32 gid = ++nextId;
  map.Insert(Scope_tab[GLOBAL_SYMTAB].st_tab, gid);
  
  xos << BegElem("xaif:Scope") << Attr("vertex_id", gid) << EndAttr;
  xlate_SYMTAB(xos, GLOBAL_SYMTAB, ctxt);
  xos << EndElem << std::endl;

  // Translate each PU, descending into children first
  for (PU_Info *pu = pu_tree; pu != NULL; pu = PU_Info_next(pu)) {
    TranslateScopeHierarchyPU(xos, pu, gid, nextId, ctxt);
  }
  
  xos << EndElem; /* xaif:ScopeHierarchy */
  xos << std::endl;
}

static void
TranslateScopeHierarchyPU(xml::ostream& xos, PU_Info* pu, UINT32 parentId, 
			  UINT32& nextId, XlationContext& ctxt)
{
  RestoreOpen64PUGlobalVars(pu); 
  StabToScopeIdMap& map = ctxt.GetStabToScopeIdMap();
  
  // Translate current symbol table
  UINT32 id = ++nextId;
  map.Insert(Scope_tab[CURRENT_SYMTAB].st_tab, id);
  
  xos << BegElem("xaif:Scope") << Attr("vertex_id", id) << EndAttr;
  xlate_SYMTAB(xos, CURRENT_SYMTAB, ctxt);
  xos << EndElem << std::endl;
  
  // Generate an edge to parent
  xos << BegElem("xaif:ScopeEdge") << Attr("edge_id", ctxt.GetNewEId())
      << Attr("source", parentId) 
      << Attr("target", id) << EndElem << std::endl; // FIXME: DumpGraphEdge
  
  // Recursively translate all children
  for (PU_Info *child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    TranslateScopeHierarchyPU(xos, child, id, nextId, ctxt);
  }
  
  SaveOpen64PUGlobalVars(pu);
}

//***************************************************************************

static void
TranslatePU(xml::ostream& xos, PU_Info *pu, UINT32 vertexId,
	    XlationContext& ctxt)
{

  xos << Comment(whirl2xaif_divider_comment);

  if (pu && PU_is_mainpu(PU_Info_pu(pu))) {
    xos << Comment("*** This is the PROGRAM routine ***");
  }
  xos << BegElem("xaif:ControlFlowGraph") << Attr("vertex_id", vertexId);
  
  if (pu) {
    RestoreOpen64PUGlobalVars(pu);
    ST* st = ST_ptr(PU_Info_proc_sym(pu));
    WN *wn_pu = PU_Info_tree_ptr(pu);
    //IR_set_dump_order(TRUE /*pre*/); fdump_tree(stderr, wn_pu);

#if 0 // FIXME  
    BOOL is_user_visible_pu = 
      (CURRENT_SYMTAB == GLOBAL_SYMTAB + 1) 
      || ((Language == LANG_F90) && (CURRENT_SYMTAB == GLOBAL_SYMTAB + 2)
	  && (!Is_Set_PU_Info_flags(pu, PU_IS_COMPILER_GENERATED)));
#endif
    
    xos << Attr("subroutine_name", W2CF_Symtab_Nameof_St(st)) << EndAttr;
    TranslateWNPU(xos, wn_pu, ctxt);
    xos << EndElem;
    
    SaveOpen64PUGlobalVars(pu);

  } else {
    // FIXME: inlinable/noninlinable
    xos << EndElem;    
  }
  
  xos << std::endl;
  xos.flush();
}

static void
TranslateWNPU(xml::ostream& xos, WN *wn_pu, XlationContext& ctxt)
{
  const char* const caller_err_phase = Get_Error_Phase();
  Diag_Set_Phase("WHIRL to XAIF: translate PU");
  Start_Timer(T_W2F_CU);

  Is_True(WN_opcode(wn_pu) == OPC_FUNC_ENTRY, 
	  ("Invalid opcode for TranslateWNPU()"));

  const BOOL pu_is_pushed = (PUinfo_current_func == wn_pu);
  if (!pu_is_pushed) { W2F_Push_PU(wn_pu, WN_func_body(wn_pu)); }
  
  /* Set the flag for an F90 program unit */
  PU& pu = Pu_Table[ST_pu( WN_st(PUinfo_current_func) )]; // FIXME: 
  WN2F_F90_pu = PU_f90_lang(pu) != 0;

  TranslateWN(xos, wn_pu, ctxt);
  
  if (!pu_is_pushed) { W2F_Pop_PU(); }
  
  W2F_Undo_Whirl_Side_Effects();
  
  Stop_Timer(T_W2F_CU);
  Diag_Set_Phase(caller_err_phase);
}

//***************************************************************************

static void 
DumpTranslationHeaderComment(xml::ostream& xos)
{
  // 1. Get a string representation of the time
  char tmStr[30] = "unknown time\n";
  time_t tm = time(NULL);
  if (tm != (time_t)-1) { strcpy(tmStr, ctime(&tm)); }
  tmStr[strlen(tmStr)-1] = '\0'; // remove the trailing '\n'

  // 2. Generate header comment
  xos << Comment(whirl2xaif_divider_comment)
      << BegComment << "XAIF file translated from WHIRL at " << tmStr 
      << EndComment
      << Comment(whirl2xaif_divider_comment) << std::endl;
}

//***************************************************************************
// 
//***************************************************************************

void
W2F_Init(void)
{
  const char * const caller_err_phase = Get_Error_Phase();
  
  /* Initialize the various whirl2c subcomponents, unless they
   * are already initialized. */
  if (W2F_Initialized) {
    return; /* Already initialized */
  }

  Diag_Set_Phase("WHIRL to XAIF: Init");
  /* The processing of the FLIST group was moved out to the back-end.
   * Instead of directly using the Current_FLIST, we initiate
   * whirl2f specific variables to hold the values.
   */
  W2F_Enabled = FLIST_enabled;
  W2F_Verbose = FLIST_verbose;
  W2F_No_Pragmas = FLIST_no_pragmas;
  W2F_Emit_Prefetch = FLIST_emit_prefetch;
  W2F_Emit_Linedirs = FLIST_emit_linedirs;
  W2F_Emit_All_Regions = FLIST_emit_all_regions;
  W2F_Emit_Nested_PUs = TRUE;
  
  // Create a pool to hold the parent map for every PU, one at a time.
  MEM_POOL_Initialize(&W2F_Parent_Pool, "W2f_Parent_Pool", FALSE);
  MEM_POOL_Push(&W2F_Parent_Pool);   
  
  /* Enter the global symbols into the symbol table, since that
   * ensures these get the first priority at keeping their names 
   * unchanged (note that a w2f invented name-suffix is added to 
   * disambiguate names).  Note that we can only emit 
   * declarations locally to PUs for Fortran, but we can still 
   * keep a global symbol-table for naming purposes.
   */
  Stab_initialize_flags();
  
  W2CF_Symtab_Push(); /* Push global (i.e. first ) symbol table */
  W2F_Enter_Global_Symbols();
  
  // Initiate the various W2F modules.
  PUinfo_initialize();
  WN2F_initialize();
  
  W2F_Initialized = TRUE;
  Diag_Set_Phase(caller_err_phase);
}


void
W2F_Fini(void)
{
  Clear_w2fc_flags(); // FIXME
  
  if (!Check_Initialized("W2F_Fini"))
    return;

  PUinfo_finalize();
  WN2F_finalize();
  W2CF_Symtab_Terminate();
  Stab_finalize_flags();
    
  /* Reset all global variables */  
  W2F_Initialized = FALSE;
  W2F_Enabled = TRUE;          /* Invoke W2F */
  W2F_Verbose = TRUE;          /* Show translation information */
  W2F_No_Pragmas = FALSE;      /* By default, emit pragmas */
  W2F_Emit_Prefetch = FALSE;   /* Emit comments for prefetches */
  W2F_Emit_All_Regions = FALSE;/* Emit cmplr-generated regions */
  W2F_Emit_Linedirs = FALSE;   /* Emit preproc line-directives */
  W2F_Emit_Nested_PUs = TRUE;  
  
  W2F_Only_Mark_Loads = FALSE;
  
  MEM_POOL_Pop(&W2F_Parent_Pool);
  MEM_POOL_Delete(&W2F_Parent_Pool);
} /* W2F_Fini */


void 
W2F_Push_PU(WN *pu, WN *body_part_of_interest)
{
  if (!Check_Initialized("W2F_Push_PU"))
    return;
  
  Is_True(WN_opcode(pu) == OPC_FUNC_ENTRY, 
	  ("Invalid opcode for W2F_Push_PU()"));
  
  Stab_initialize();
  Clear_w2fc_flags();
  
  // Set up the parent mapping
  MEM_POOL_Push(&W2F_Parent_Pool);
  W2CF_Parent_Map = WN_MAP_Create(&W2F_Parent_Pool);
  W2CF_Parentize(pu);
    
  /* See if the body_part_of_interest has any part to be skipped
   * by the w2f translator. */
  if (WN_opc_operator(body_part_of_interest) == OPR_BLOCK) {
    Remove_Skips(body_part_of_interest, Skip, &Next_Skip_Item,
		 W2F_MAX_SKIP_ITEMS, FALSE /*Not C*/);
  }
  
  // Get the current PU name and ST.
  PUinfo_init_pu(pu, body_part_of_interest);
}


void 
W2F_Pop_PU(void)
{
  if (!Check_Initialized("W2F_Pop_PU") || !Check_PU_Pushed("W2F_Pop_PU"))
    return;
  
  PUinfo_exit_pu();
  
  // Restore any removed statement sequence
  if (Next_Skip_Item > 0) {
    Restore_Skips(Skip, Next_Skip_Item, FALSE /*Not C*/);
    Next_Skip_Item = 0;
  }
  
  Stab_finalize();
  
  WN_MAP_Delete(W2CF_Parent_Map);
  W2CF_Parent_Map = WN_MAP_UNDEFINED;
  MEM_POOL_Pop(&W2F_Parent_Pool);
  
  W2F_Frequency_Map = WN_MAP_UNDEFINED;
}


void
W2F_def_ST(FILE *outfile, ST *st)
{
#if 0//REMOVE
  xml::ostream& xos;
  
  if (!Check_Initialized("W2F_def_ST"))
    return;
  
  tokens = New_Token_Buffer();
  TranslateSTDecl(tokens, st);
  Write_And_Reclaim_Tokens(outfile, W2F_File[W2F_LOC_FILE], &tokens);
  W2F_Undo_Whirl_Side_Effects();
#endif
}

const char * 
W2F_Object_Name(ST *func_st)
{
  return W2CF_Symtab_Nameof_St(func_st);
}

void 
W2F_Translate_Wn(FILE *outfile, WN *wn)
{
#if 0//REMOVE
   xml::ostream&       tokens;
   XlationContext       context;
   const char * const caller_err_phase = Get_Error_Phase ();

   if (!Check_Initialized("W2F_Translate_Wn") ||
       !Check_PU_Pushed("W2F_Translate_Wn"))
      return;

   Start_Timer(T_W2F_CU);
   Diag_Set_Phase("whirl 2 xaif translation");

   tokens = New_Token_Buffer();
   (void)TranslateWN(tokens, wn, context);
   Write_And_Reclaim_Tokens(outfile, W2F_File[W2F_LOC_FILE], &tokens);
   W2F_Undo_Whirl_Side_Effects();

   Stop_Timer (T_W2F_CU);
   Diag_Set_Phase(caller_err_phase);
#endif
} /* W2F_Translate_Wn */


void 
W2F_Translate_Wn_Str(char *strbuf, UINT bufsize, WN *wn)
{
#if 0//REMOVE
   xml::ostream&       tokens;
   XlationContext       context;
   const char * const caller_err_phase = Get_Error_Phase ();

   if (!Check_Initialized("W2F_Translate_Wn_Str") ||
       !Check_PU_Pushed("W2F_Translate_Wn_Str"))
      return;

   Start_Timer (T_W2F_CU);
   Diag_Set_Phase("whirl 2 xaif translation");

   tokens = New_Token_Buffer();
   (void)TranslateWN(tokens, wn, context);
   Str_Write_And_Reclaim_Tokens(strbuf, bufsize, &tokens);
   W2F_Undo_Whirl_Side_Effects();

   Stop_Timer (T_W2F_CU);
   Diag_Set_Phase(caller_err_phase);
#endif
} /* W2F_Translate_Wn_Str */


/* ====================================================================
 *                   Undo side-effects to the incoming WHIRL
 *                   ---------------------------------------
 *
 * W2F_Undo_Whirl_Side_Effects: This subroutine must be called after
 * every translation phase which may possibly create side-effects
 * in the incoming WHIRL tree.  The translation should thus become
 * side-effect free as far as concerns the incoming WHIRL tree.
 *
 * ==================================================================== 
 */

static void
W2F_Undo_Whirl_Side_Effects(void)
{
  Stab_Free_Tmpvars();
  Stab_Free_Namebufs();
}


/* ====================================================================
 *                   Setting up the global symbol table
 *                   ----------------------------------
 *
 * W2F_Enter_Global_Symtab: Enter the global symbols into the w2f
 * symbol table.  The global symbol-table should be the top-of the
 * stack at this point.
 *
 * ==================================================================== 
 */

// function object to enter FLD names in w2f symbol table. 
// See call in W2F_Enter_Global_Symbols
struct enter_fld
{
  void operator() (UINT32 ty_idx, const TY* typ) const 
  {
    TY & ty = (TY &) typ;

    if (TY_kind(ty) == KIND_STRUCT) {
      (void)W2CF_Symtab_Nameof_Ty(ty_idx);
      
      FLD_HANDLE fld = TY_flist(ty);
      FLD_ITER fld_iter = Make_fld_iter(fld);
      do {
	FLD_HANDLE fld_rt (fld_iter);
	
	if (TY_Is_Pointer(FLD_type(fld_rt)))
	  (void)W2CF_Symtab_Nameof_Fld_Pointee(fld);
	(void)W2CF_Symtab_Nameof_Fld(fld);
	
      } while (!FLD_last_field (fld_iter++)); 
    }
  }
};

// function object to enter fn & varbl names in w2f symbol table. 
// See call in W2F_Enter_Global_Symbols.
struct enter_st 
{
  void operator() (UINT32 idx, const ST * st) const 
  {
    if ((ST_sym_class(st) == CLASS_VAR && !ST_is_not_used(st)) || 
	ST_sym_class(st) == CLASS_FUNC) {
      TY_IDX ty ;
      
      (void)W2CF_Symtab_Nameof_St(st);
      
      if (ST_sym_class(st) == CLASS_VAR)
	ty = ST_type(st);
      else
	ty = ST_pu_type(st);
      
      if (TY_Is_Pointer(ty))
	(void)W2CF_Symtab_Nameof_St_Pointee(st);
    }
  }
};

static void
W2F_Enter_Global_Symbols(void)
{
  /* Enter_Sym_Info for every struct or class type in the current 
   * symbol table, with associated fields.  Do this prior to any
   * variable declarations, just to ensure that field names and
   * common block names retain their names to the extent this is
   * possible.
   */
  For_all(Ty_Table, enter_fld());
  
  /* Enter_Sym_Info for every variable and function in the current 
   * (global) symbol table.  Note that we always invent names for the
   * pointees of Fortran pointers, since the front-end invariably
   * does not generate ST entries for these.
   */
  For_all(St_Table, GLOBAL_SYMTAB, enter_st());
  
#if 0
  // FIX constants ??
  FOR_ALL_CONSTANTS(st, const_idx) {
    if (ST_symclass(st) != CLASS_SYM_CONST)
      (void)W2CF_Symtab_Nameof_St(st);
  }
#endif
}

/* =================================================================
 * Routines for checking correct calling order of exported routines
 * =================================================================
 */

static BOOL
Check_Initialized(const char *caller_name)
{
  if (!W2F_Initialized)
    fprintf(stderr, "NOTE: Ignored call to %s(); call W2F_Init() first!\n",
	    caller_name);
  return W2F_Initialized;
}

static BOOL
Check_PU_Pushed(const char *caller_name)
{
  if (PUinfo_current_func == NULL)
    fprintf(stderr, "NOTE: Ignored call to %s(); call W2F_Push_PU() first!\n",
	    caller_name);
  return (PUinfo_current_func != NULL);
}

