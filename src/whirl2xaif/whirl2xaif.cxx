// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.cxx,v 1.45 2004/06/11 19:46:01 eraxxon Exp $

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

IntrinsicXlationTable whirl2xaif::IntrinsicTable(IntrinsicXlationTable::W2X);

ScalarizedRefTabMap_W2X whirl2xaif::ScalarizedRefTableMap;
WNToWNIdTabMap          whirl2xaif::WNToWNIdTableMap;

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
  
  // -------------------------------------------------------
  // 1. Initialization
  // -------------------------------------------------------
  Pro64IRInterface irInterface;
  xml::ostream xos(os.rdbuf());
  XlationContext ctxt;

  DumpTranslationHeaderComment(xos); // FIXME (optional)
  
  // Initialize global id maps
  SymTabToSymTabIdMap* stabmap = new SymTabToSymTabIdMap(pu_forest);
  ctxt.SetSymTabToIdMap(stabmap);
  
  PUToPUIdMap* pumap = new PUToPUIdMap(pu_forest);
  ctxt.SetPUToIdMap(pumap);

  WNToWNIdTableMap.Create(pu_forest); // Note: could make this local
  
  // Create scalarized var reference table.  Note: At the moment we
  // must create all tables in memory because they must be available
  // for the ScopeHeirarchy.  
  ScalarizedRefTableMap.Create(pu_forest);
  
  // -------------------------------------------------------
  // 2. Create and dump CallGraph
  // -------------------------------------------------------

  // Create CallGraph (massage OA version into XAIF version)
  Pro64IRProcIterator irProcIter(pu_forest);
  ST* st = ST_ptr(PU_Info_proc_sym(pu_forest));
  CallGraph cgraph(irInterface, &irProcIter, (SymHandle)st);
  
  MassageOACallGraphIntoXAIFCallGraph(&cgraph);
  //cgraph->dump(cerr);
  
  // Dump CallGraph header info and ScopeHierarchy
  xos << BegElem("xaif:CallGraph")
      << Attr("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance")
      << Attr("xmlns:xaif", "http://www.mcs.anl.gov/XAIF")
      << Attr("xsi:schemaLocation", "http://www.mcs.anl.gov/XAIF xaif.xsd")
      << Attr("program_name", "***myprog***")
      << Attr("prefix", "OpenAD_");
  
  ctxt.CreateContext();
  TranslateScopeHierarchy(xos, pu_forest, ctxt);
  ctxt.DeleteContext();
  
  // Dump CallGraph vertices
  DGraphNodeVec* nodes = SortDGraphNodes(&cgraph);
  for (DGraphNodeVec::iterator nodeIt = nodes->begin();
       nodeIt != nodes->end(); ++nodeIt) {
    ctxt.CreateContext();
    CallGraph::Node* n = dynamic_cast<CallGraph::Node*>(*nodeIt);
    TranslatePU(xos, n, n->getId(), ctxt);
    ctxt.DeleteContext();
  }
  delete nodes;
  
  // Dump CallGraph edges
  DGraphEdgeVec* edges = SortDGraphEdges(&cgraph);
  for (DGraphEdgeVec::iterator edgeIt = edges->begin(); 
       edgeIt != edges->end(); ++edgeIt) {
    CallGraph::Edge* e = dynamic_cast<CallGraph::Edge*>(*edgeIt);
    CallGraph::Node* n1 = dynamic_cast<CallGraph::Node*>(e->source());
    CallGraph::Node* n2 = dynamic_cast<CallGraph::Node*>(e->sink());
    DumpCallGraphEdge(xos, ctxt.GetNewEId(), n1->getId(), n2->getId());
  }
  delete edges;
  
  // Done!
  xos << EndElem; /* xaif:CallGraph */


  // -------------------------------------------------------
  // 3. Cleanup
  // -------------------------------------------------------
  
  delete stabmap;
  delete pumap;
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
  
  // We need WHIRL<->ID maps for translating ScalarizedRefs
  WNToWNIdMap* wnmap = WNToWNIdTableMap.Find(pu);
  ctxt.SetWNToIdMap(wnmap);
  
  ScalarizedRefTab_W2X* tab = ScalarizedRefTableMap.Find(pu);
  SymTabId scopeId = ctxt.FindSymTabId(Scope_tab[CURRENT_SYMTAB].st_tab);  

  // Translate symbol tables 
  xos << BegElem("xaif:Scope") << Attr("vertex_id", scopeId) 
      << SymTabIdAnnot(scopeId) << EndAttrs;
  xlate_SymbolTables(xos, CURRENT_SYMTAB, tab, ctxt);
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

  // -------------------------------------------------------
  // Translate the PU
  // -------------------------------------------------------
  
  // FIXME: how is PU_f90_lang() different from (Language == LANG_F90)?
  PU& real_pu = PU_Info_pu(pu); 
  WN2F_F90_pu = (PU_f90_lang(real_pu) != 0); // FIXME: set F90 flag
  bool isProgram = PU_is_mainpu(real_pu);

  ST* st = ST_ptr(PU_Info_proc_sym(pu));
  WN *wn_pu = PU_Info_tree_ptr(pu);
  
  PUId puId = ctxt.FindPUId(pu);
  ST_TAB* sttab = Scope_tab[ST_level(st)].st_tab;
  SymTabId scopeId = ctxt.FindSymTabId(sttab);

  SymTabId puScopeId = ctxt.FindSymTabId(Scope_tab[CURRENT_SYMTAB].st_tab);
  
  // Generate the CFG
  xos << Comment(whirl2xaif_divider_comment);
  if (isProgram) { xos << Comment("*** This is the PROGRAM routine ***"); }
  
  xos << BegElem("xaif:ControlFlowGraph") 
      << Attr("vertex_id", vertexId) << Attr("scope_id", scopeId)
      << AttrSymId(st) << PUIdAnnot(puId)
      << Attr("controlflowgraph_scope_id", puScopeId)
      << EndAttrs;
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

#if 0
  static char buf[32]; // easily hold a 64 bit number
  WNId id = curwnmap->Find(const_cast<WN*>(wn), true /*mustFind*/);
  
  sprintf(buf, "%u", id);
  std::string s = XAIFStrings.tag_WHIRLId();
  s += buf;
  s += XAIFStrings.tag_End();
#endif

//***************************************************************************
