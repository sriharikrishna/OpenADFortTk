// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.cxx,v 1.38 2004/04/29 21:33:20 eraxxon Exp $

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
#include <fstream>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//************************ OpenAnalysis Include Files ***********************

#include <OpenAnalysis/CallGraph/CallGraph.h>

//*************************** User Include Files ****************************

#include "whirl2xaif.h"
#include "wn2xaif.h"
#include "st2xaif.h"

#include <lib/support/Pro64IRInterface.h>

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//***************************************************************************

BOOL WN2F_F90_pu = FALSE; /* Global variable: F90 or F77: FIXME/REMOVE */

//***************************************************************************

static void 
TranslateScopeHierarchy(xml::ostream& xos, PU_Info* pu_forest, 
			XlationContext& ctxt);

static void
TranslateScopeHierarchyPU(xml::ostream& xos, PU_Info* pu, UINT32 parentId, 
			  XlationContext& ctxt);

static void
TranslatePU(xml::ostream& xos, CallGraph::Node* n, UINT32 vertexId,
	    XlationContext& ctxt);

static void 
TranslatePU(xml::ostream& xos, PU_Info *pu, UINT32 vertexId,
	    XlationContext& ctxt);

static void 
TranslateWNPU(xml::ostream& xos, WN* pu, XlationContext& ctxt);


static void
MassageOACallGraphIntoXAIFCallGraph(CallGraph* cg);

static void 
DumpTranslationHeaderComment(xml::ostream& xos);

//***************************************************************************
// 
//***************************************************************************

void
whirl2xaif::TranslateIR(std::ostream& os, PU_Info* pu_forest)
{
  Diag_Set_Phase("WHIRL to XAIF: translate IR");
  //IntrinsicTable.DDump();
  
  if (!pu_forest) { return; }

  // 1. Initialization
  Pro64IRInterface irInterface;
  xml::ostream xos(os.rdbuf());
  XlationContext ctxt;

  DumpTranslationHeaderComment(xos); // FIXME (optional)
  
  // Initialize global id maps
  pair<SymTabToSymTabIdMap*, SymTabIdToSymTabMap*> stabmaps =
    CreateSymTabIdMaps(pu_forest);
  ctxt.SetSymTabToIdMap(stabmaps.first);
  delete stabmaps.second;
  
  pair<PUToPUIdMap*, PUIdToPUMap*> pumaps = CreatePUIdMaps(pu_forest);
  ctxt.SetPUToIdMap(pumaps.first);
  delete pumaps.second;
  
  // 2. Create CallGraph (massage OA version into XAIF version)
  Pro64IRProcIterator irProcIter(pu_forest);
  ST* st = ST_ptr(PU_Info_proc_sym(pu_forest));
  CallGraph cgraph(irInterface, &irProcIter, (SymHandle)st);
  
  MassageOACallGraphIntoXAIFCallGraph(&cgraph);
  //cgraph->dump(cerr);
  
  // 3. Dump CallGraph header info and ScopeHierarchy
  xos << BegElem("xaif:CallGraph")
      << Attr("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance")
      << Attr("xmlns:xaif", "http://www.mcs.anl.gov/XAIF")
      << Attr("xsi:schemaLocation", "http://www.mcs.anl.gov/XAIF xaif.xsd")
      << Attr("program_name", "***myprog***")
      << Attr("prefix", "OpenAD_");
  
  ctxt.CreateContext();
  TranslateScopeHierarchy(xos, pu_forest, ctxt);
  ctxt.DeleteContext();
  
  // 4. Dump CallGraph vertices
  DGraphNodeVec* nodes = SortDGraphNodes(&cgraph);
  for (DGraphNodeVec::iterator nodeIt = nodes->begin();
       nodeIt != nodes->end(); ++nodeIt) {
    ctxt.CreateContext();
    CallGraph::Node* n = dynamic_cast<CallGraph::Node*>(*nodeIt);
    TranslatePU(xos, n, n->getId(), ctxt);
    ctxt.DeleteContext();
  }
  delete nodes;
  
  // 5. Dump CallGraph edges
  DGraphEdgeVec* edges = SortDGraphEdges(&cgraph);
  for (DGraphEdgeVec::iterator edgeIt = edges->begin(); 
       edgeIt != edges->end(); ++edgeIt) {
    CallGraph::Edge* e = dynamic_cast<CallGraph::Edge*>(*edgeIt);
    CallGraph::Node* n1 = dynamic_cast<CallGraph::Node*>(e->source());
    CallGraph::Node* n2 = dynamic_cast<CallGraph::Node*>(e->sink());
    DumpCallGraphEdge(xos, ctxt.GetNewEId(), n1->getId(), n2->getId());
  }
  delete edges;
  
  // 6. Done!
  xos << EndElem; /* xaif:CallGraph */
  
  delete stabmaps.first;
  delete pumaps.first;
}


//***************************************************************************

static void
TranslateScopeHierarchy(xml::ostream& xos, PU_Info* pu_forest, 
			XlationContext& ctxt)
{
  // We implicitly create the ScopeHierarchy/ScopeGraph using
  // DFS-style iteration of PUs.  In addition to the global scope,
  // there is one scope for each PU.

  xos << BegElem("xaif:ScopeHierarchy");
  
  // Translate global symbol table
  SymTabId scopeId = ctxt.FindSymTabId(Scope_tab[GLOBAL_SYMTAB].st_tab);
  
  xos << BegElem("xaif:Scope") << Attr("vertex_id", scopeId)
      << SymTabIdAnnot(scopeId) << EndAttrs;
  xlate_SymbolTables(xos, GLOBAL_SYMTAB, NULL, ctxt);
  xos << EndElem << std::endl;

  // Translate each PU, descending into children first
  for (PU_Info *pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
    TranslateScopeHierarchyPU(xos, pu, scopeId, ctxt);
  }
  
  xos << EndElem; /* xaif:ScopeHierarchy */
  xos << std::endl;
}


static void
TranslateScopeHierarchyPU(xml::ostream& xos, PU_Info* pu, UINT32 parentId, 
			  XlationContext& ctxt)
{
  PU_SetGlobalState(pu);
  
  // Translate current symbol table
  SymTabId scopeId = ctxt.FindSymTabId(Scope_tab[CURRENT_SYMTAB].st_tab);
  
  xos << BegElem("xaif:Scope") << Attr("vertex_id", scopeId) 
      << SymTabIdAnnot(scopeId) << EndAttrs;
  xlate_SymbolTables(xos, CURRENT_SYMTAB, NULL, ctxt);
  xos << EndElem << std::endl;
  
  // Generate an edge to parent
  DumpScopeGraphEdge(xos, ctxt.GetNewEId(), scopeId, parentId);
  xos << std::endl;
  
  // Recursively translate all children
  for (PU_Info *child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    TranslateScopeHierarchyPU(xos, child, scopeId, ctxt);
  }
}


//***************************************************************************

static void
TranslatePU(xml::ostream& xos, CallGraph::Node* n, UINT32 vertexId,
	    XlationContext& ctxt)
{
  // FIXME: A more general test will be needed
  ASSERT_FATAL(n->GetDef(), (DIAG_UNIMPLEMENTED, "Should be defined."));

  TranslatePU(xos, (PU_Info*)n->GetDef(), n->getId(), ctxt);
    
  xos << std::endl;
  xos.flush();
}


static void
TranslatePU(xml::ostream& xos, PU_Info *pu, UINT32 vertexId,
	    XlationContext& ctxt)
{
  if (!pu) { return; }
  
  PU_SetGlobalState(pu);
  
  bool isCompilerGen = ((Language == LANG_F90) && 
			(CURRENT_SYMTAB == GLOBAL_SYMTAB + 2) && 
			Is_Set_PU_Info_flags(pu, PU_IS_COMPILER_GENERATED));
  Is_True(!isCompilerGen, ("Compiler generated PU!")); // FIXME

  // FIXME: how is PU_f90_lang() different from (Language == LANG_F90)?
  PU& real_pu = PU_Info_pu(pu); 
  WN2F_F90_pu = (PU_f90_lang(real_pu) != 0); // FIXME: set F90 flag
  bool isProgram = PU_is_mainpu(real_pu);

  ST* st = ST_ptr(PU_Info_proc_sym(pu));
  WN *wn_pu = PU_Info_tree_ptr(pu);
  
  PUId puId = ctxt.FindPUId(pu);
  ST_TAB* sttab = Scope_tab[ST_level(st)].st_tab;
  SymTabId scopeId = ctxt.FindSymTabId(sttab);
  
  // Generate the CFG
  xos << Comment(whirl2xaif_divider_comment);
  if (isProgram) { xos << Comment("*** This is the PROGRAM routine ***"); }
  
  xos << BegElem("xaif:ControlFlowGraph") 
      << Attr("vertex_id", vertexId) << Attr("scope_id", scopeId)
      << AttrSymId(st) << PUIdAnnot(puId) << EndAttrs;
  TranslateWNPU(xos, wn_pu, ctxt);
  xos << EndElem; // xaif:ControlFlowGraph
}


static void
TranslateWNPU(xml::ostream& xos, WN *wn_pu, XlationContext& ctxt)
{
  const char* const caller_err_phase = Get_Error_Phase();
  Diag_Set_Phase("WHIRL to XAIF: translate PU");
  
  Is_True(WN_opcode(wn_pu) == OPC_FUNC_ENTRY, ("Invalid opcode"));
  
  // fdump_tree(stderr, wn_pu);
  TranslateWN(xos, wn_pu, ctxt);
  
  Stab_Free_Tmpvars();  // FIXME: it would be nice to eventually 
  Stab_Free_Namebufs(); // remove this stuff
  
  Diag_Set_Phase(caller_err_phase);
}


//***************************************************************************
// 
//***************************************************************************

// MassageOACallGraphIntoXAIFCallGraph: Process CallGraph to eliminate
// synthetic edges.
//   - eliminate special Open64 functions and inlinable intrinsics
//   - need to figure out what to do with non-inlinable intrinsics
//  
static void
MassageOACallGraphIntoXAIFCallGraph(CallGraph* cg)
{
  // For now we eliminate nodes without a definition.  
  
  DGraphNodeList toRemove; // holds basic blocks made empty
  
  for (CallGraph::NodesIterator it(*cg); (bool)it; ++it) {
    CallGraph::Node* n = dynamic_cast<CallGraph::Node*>((DGraph::Node*)it);
    if (!n->GetDef()) {
      IFDBG(2) {
	IRInterface& ir = cg->GetIRInterface();
	const char* nm = ir.GetSymNameFromSymHandle(n->GetSym());
	std::cout << "* Removing '" << nm << "' from CallGraph\n";
      }
      toRemove.push_back(n);
    }
  }
  
  // Remove empty basic blocks
  for (DGraphNodeList::iterator it = toRemove.begin(); 
       it != toRemove.end(); ++it) {
    DGraph::Node* n = (*it);
    cg->remove(n);
    delete n;
  }
  toRemove.clear();
}


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

#include "clone.h"          /* Open64: IPO_CLONE */
#include <lib/support/WhirlParentize.h>
#include <vector>
using std::vector;

static WN* 
FindCallToInlinedFn(const char* callee_nm, WN* wn);

void 
InlineTest(PU_Info* pu_forest)
{
  // Given a PU forest 'pu_forest'
  //   * searches for the first pu named 'inline_*'.  This is
  //     assumed to be the subroutine for inlining.
  //   * searches the program pu for the first call of this subroutine.
  //   * inlines the subroutine into the main pu
  // 
  // Limitations: can only inline subroutines that
  //   - have one return statement (or none)
  //   - are called with variables as actual parameters (as opposed to
  //     an expression like sin(x)).
  //
  // Note: if we create entirely new functions, we will need to update
  //   pu->sym_tab map.
  
  // -------------------------------------------------------
  // 1. Find inlined functions (callee) named inline_x
  // -------------------------------------------------------
  const char* calleeNm = NULL;
  PU_Info*    calleePU = NULL;
  WN*         calleeWN = NULL; // OPR_FUNC_ENTRY
  WN_MAP_TAB* calleeMaptab = NULL;
  SCOPE*      calleeStab = NULL;
  SYMTAB_IDX  calleeStabIdx = 0;
  
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();
    ST_IDX st = PU_Info_proc_sym(pu);
    const char* nm = ST_name(st);

    if (strncmp(nm, "inline_", 7) == 0) {
      calleeNm = nm;
      calleePU = pu;
      calleeWN = PU_Info_tree_ptr(calleePU);
      calleeMaptab = PU_Info_maptab(pu);
      calleeStab = Scope_tab;
      calleeStabIdx = PU_lexical_level(PU_Info_pu(pu));
      break;
    }
  } // global state set for calleePU
  
  // -------------------------------------------------------
  // 2. Find the caller, i.e. callsites to inline_x. In the MainPU
  // -------------------------------------------------------
  PU_Info*    callerPU = NULL;
  WN*         callsiteWN = NULL;
  WN_MAP_TAB* callerMaptab = NULL;
  SCOPE*      callerStab = NULL;
  SYMTAB_IDX  callerStabIdx = 0;
  
  procIt.Reset();
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();
    if (PU_is_mainpu(PU_Info_pu(pu))) {
      callerPU = pu;
      callsiteWN = FindCallToInlinedFn(calleeNm, PU_Info_tree_ptr(callerPU));
      callerMaptab = PU_Info_maptab(pu);
      callerStab = Scope_tab;
      callerStabIdx = PU_lexical_level(PU_Info_pu(pu));
      break;
    }
  } // global state set for callerPU
  
  if (!callsiteWN) {
    return;
  }

  // * Gather actual parameters (at callsite)
  INT nparam = WN_kid_count(callsiteWN);
  vector<ST*> callsiteParams(nparam);
  for (int i = 0; i < nparam; ++i) {
    WN* parm = WN_kid(callsiteWN, i);
    ST* st = WN_st(WN_kid0(parm));
    callsiteParams[i] = st;
  }
  
  // For the below, compare to
  // IPO_INLINE::Process(), ipa/main/optimize/ipo_inline.cxx.
  
  // -------------------------------------------------------
  // 1. Create a copy of the callee
  // -------------------------------------------------------
  // IPO_INLINE::Process_Callee(...)
  //   IPO_INLINE::Clone_Callee(...)
  
  // Global tables should point to callee
  PU_SetGlobalState(calleePU);
  
  // FIXME: allocates WN_mem_pool_ptr, which is used in IPO_CLONE::Copy_Node
  WN* bogus_wn = WN_CreateIntconst(OPC_I4INTCONST, 0);
  
  WN_MAP parentmap = WN_MAP_Create(MEM_pu_pool_ptr);
  IPO_SYMTAB ipo_symtab(calleeStab, callerStab, calleeStabIdx, callerStabIdx,
			MEM_pu_pool_ptr, TRUE /*same_file*/);
  IPO_CLONE cloner(callerMaptab, calleeMaptab, parentmap,
		   calleeStab, callerStab, calleeStabIdx, callerStabIdx,
		   &ipo_symtab, MEM_pu_pool_ptr, TRUE /*same_file*/, 0);  
  
  // * Copy symtabs of callee into caller's
  //cloner.Promote_Statics();
  cloner.Get_sym()->Update_Symtab(FALSE /*label_only*/);
    
  // * Clone, setting symtab indices to reference caller's tables
  WN* inlinedBodyWn = cloner.Clone_Tree(WN_func_body(calleeWN));
  
  // * Gather formals parameters (at callee)
  nparam = WN_num_formals(calleeWN);
  vector<ST*> calleeParams(nparam);
  for (int i = 0; i < nparam; ++i) {
    ST* st = WN_st(WN_formal(calleeWN, i));
    st = ipo_symtab.Get_ST(st); // get the version on the caller side
    calleeParams[i] = st;
  }
  assert(callsiteParams.size() == calleeParams.size());
  
  // -------------------------------------------------------
  // 2. Update and patch body of inlined function
  // -------------------------------------------------------
  // IPO_INLINE::Process_Callee(...)
  //   IPO_INLINE::Clone_Callee(...) and
  //   IPO_INLINE::Walk_and_Update_Callee(...)

  // Global tables should point to caller (cloned tree uses caller's symtab)
  PU_SetGlobalState(callerPU);
  
  // * Recreate parent pointers
  // W2CF_Parentize(inlinedBodyWn); // WN_Parentize() - ipo_parent.cxx
  
  // Prepare map: formal params -> actual params
  map<ST*, ST*> formals2actuals;
  for (int i = 0; i < nparam; ++i) {
    ST* formalST = calleeParams[i];
    ST* actualST = callsiteParams[i];
    formals2actuals[formalST] = actualST;
  }
  
  // * Replace any formal parameters with actual parameters
  //   Cf. IPO_INLINE::Process_Formals(...) (actually only preparation
  //   for Process_Op_Code(...)
  // * Remove RETURN in body of inlined function
  //   Cf. IPO_INLINE::Process_Op_Code(...)
  WN_TREE_CONTAINER<PRE_ORDER> wnIt(inlinedBodyWn);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  for (it = wnIt.begin(); it != wnIt.end(); ++it) {
    WN* curWN = it.Wn();
    OPERATOR opr = WN_operator(curWN);
    
    // Replace reference to a formal param with actual param
    if (OPERATOR_has_sym(opr)) {
      ST* curST = WN_st(curWN);
      ST* actualST = formals2actuals[curST];
      if (actualST) {
	WN_st_idx(curWN) = ST_st_idx(actualST);
      }
    }

    // Remove returns
    if (opr == OPR_RETURN) {
      WN* blkWN = FindParentWNBlock(inlinedBodyWn, curWN);
      WN_DELETE_FromBlock(blkWN, curWN);
      break; // should only be one, at end of block (FIXME)
    }
  }
  
  // -------------------------------------------------------
  // 3. Replace callsite with body of inlined function
  // -------------------------------------------------------
  // IPO_INLINE::Post_Process_Caller(...)
  if (WN_first (inlinedBodyWn) != NULL) {
    // Replace callsite with body of inlined function
    WN_next(WN_prev(callsiteWN)) = WN_first(inlinedBodyWn);
    WN_prev(WN_first(inlinedBodyWn)) = WN_prev(callsiteWN);
    
    WN_next(WN_last(inlinedBodyWn)) = WN_next(callsiteWN);
    WN_prev(WN_next(callsiteWN)) = WN_last(inlinedBodyWn);
  } else {
    // Replace callsite with (empty) body of inlined function
    WN_next(WN_prev(callsiteWN)) = WN_next(callsiteWN);
    WN_prev(WN_next(callsiteWN)) = WN_prev(callsiteWN);
  }

#if 0  
  WN* callerWN = PU_Info_tree_ptr(callerPU);
  dump_tree(callerWN);
#endif  
}

static WN* 
FindCallToInlinedFn(const char* calleeNm, WN* wn)
{
  WN_TREE_CONTAINER<PRE_ORDER> wnIt(wn);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  for (it = wnIt.begin(); it != wnIt.end(); ++it) {
    WN* curWN = it.Wn();
    
    OPERATOR opr = WN_operator(curWN);
    if (opr == OPR_CALL && (strcmp(ST_name(WN_st(curWN)), calleeNm) == 0)) {
      return curWN;
    }
  }
  
  return NULL;
}

//***************************************************************************
