// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.cxx,v 1.53 2006/05/12 16:12:23 utke Exp $


#include <time.h>
#include <fstream>

#include "Open64IRInterface/Open64BasicTypes.h"
#include "Open64IRInterface/Open64IRInterface.hpp"
#include "whirl2xaif.h"
#include "wn2xaif.h"
#include "st2xaif.h"

namespace whirl2xaif { 

  fortTkSupport::IntrinsicXlationTable   
  Whirl2Xaif::ourIntrinsicTable(fortTkSupport::IntrinsicXlationTable::W2X);

  fortTkSupport::PUToOAAnalInfoMap       Whirl2Xaif::ourOAAnalMap;
  fortTkSupport::ScalarizedRefTabMap_W2X Whirl2Xaif::ourScalarizedRefTableMap;
  fortTkSupport::WNToWNIdTabMap          Whirl2Xaif::ourWNToWNIdTableMap;
  const std::string       Whirl2Xaif::ourDividerComment("********************************************************************");

  fortTkSupport::IntrinsicXlationTable& Whirl2Xaif::getIntrinsicXlationTable() { 
    return ourIntrinsicTable;
  }

  fortTkSupport::PUToOAAnalInfoMap& Whirl2Xaif::getOAAnalMap() { 
    return ourOAAnalMap;
  }

  fortTkSupport::ScalarizedRefTabMap_W2X& Whirl2Xaif::getScalarizedRefTableMap() { 
    return ourScalarizedRefTableMap;
  }

  fortTkSupport::WNToWNIdTabMap& Whirl2Xaif::getWNToWNIdTableMap() { 
    return ourWNToWNIdTableMap;
  }

  void Whirl2Xaif::translateIR(std::ostream& os, 
			       PU_Info* pu_forest,
			       const char* tmpVarPrefix) {
    using namespace OA::CallGraph;
    Diag_Set_Phase("WHIRL to XAIF: translate IR");
    if (!pu_forest) { return; }
    // -------------------------------------------------------
    // 1. Initialization (Much of this information must be collected
    // here because it is part of the CallGraph instead of a
    // ControlFlowGraph)
    // -------------------------------------------------------
    OA::OA_ptr<Open64IRInterface> irInterface;
    irInterface = new Open64IRInterface;
    Open64IRInterface::initContextState(pu_forest);
    xml::ostream xos(os.rdbuf());
    PUXlationContext ctxt("whirl2xaif::translateIR");
    dumpTranslationHeaderComment(xos); // FIXME (optional)
    // Initialize global id maps
    // NOTE: Do this first so that ids will match in back-translation
    fortTkSupport::SymTabToSymTabIdMap* stabmap = new fortTkSupport::SymTabToSymTabIdMap(pu_forest);
    ctxt.setSymTabToIdMap(stabmap);
    fortTkSupport::PUToPUIdMap* pumap = new fortTkSupport::PUToPUIdMap(pu_forest);
    ctxt.setPUToIdMap(pumap);
    ourWNToWNIdTableMap.Create(pu_forest); // Note: could make this local
    // Initialize and create inter/intra analysis information
    ourOAAnalMap.Create(pu_forest);
    ctxt.setActivity(ourOAAnalMap.GetInterActive());
    ctxt.setAlias(ourOAAnalMap.GetInterAlias());
    // Create scalarized var reference table
    ourScalarizedRefTableMap.Create(pu_forest);
    // -------------------------------------------------------
    // 2. Generate XAIF CallGraph
    // -------------------------------------------------------
    OA::OA_ptr<OA::CallGraph::CallGraph> cgraph = 
      ourOAAnalMap.GetCallGraph();
    // CallGraph header info
    xos << xml::BegElem("xaif:CallGraph")
	<< xml::Attr("xmlns:xsi", "http://www.w3.org/2001/XMLSchema-instance")
	<< xml::Attr("xmlns:xaif", "http://www.mcs.anl.gov/XAIF")
	<< xml::Attr("xsi:schemaLocation", "http://www.mcs.anl.gov/XAIF xaif.xsd")
	<< xml::Attr("program_name", "***myprog***")
	<< xml::Attr("prefix", tmpVarPrefix);
    // ScopeHierarchy
    ctxt.createXlationContext();
    translateScopeHierarchy(xos, pu_forest, ctxt);
    ctxt.deleteXlationContext();
    // Analysis Info Maps
    translateAnalMaps(xos, pu_forest, ctxt);
    // CallGraph vertices
    DGraphNodeVec* nodes = SortDGraphNodes(cgraph);
    for (DGraphNodeVec::iterator nodeIt = nodes->begin();
	 nodeIt != nodes->end(); ++nodeIt) {
      ctxt.createXlationContext();
      OA::OA_ptr<OA::DGraph::NodeInterface> ntmp = *nodeIt;
      OA::OA_ptr<Node> n = 
	ntmp.convert<Node>();
      translatePU(xos, n, n->getId(), ctxt);
      ctxt.deleteXlationContext();
    }
    delete nodes;
    // CallGraph edges
    DGraphEdgeVec* edges = SortDGraphEdges(cgraph);
    for (DGraphEdgeVec::iterator edgeIt = edges->begin(); 
	 edgeIt != edges->end(); ++edgeIt) {
      OA::OA_ptr<OA::DGraph::EdgeInterface> e = (*edgeIt);
      OA::OA_ptr<OA::DGraph::NodeInterface> n1 = e->getSource();
      OA::OA_ptr<OA::DGraph::NodeInterface> n2 = e->getSink();
      DumpCallGraphEdge(xos, ctxt.currentXlationContext().getNewEdgeId(), n1->getId(), n2->getId());
    }
    delete edges;
    // Done!
    xos << xml::EndElem; /* xaif:CallGraph */
    // -------------------------------------------------------
    // 3. Cleanup
    // -------------------------------------------------------
    delete stabmap;
    delete pumap;
  }

  void Whirl2Xaif::translateScopeHierarchy(xml::ostream& xos, 
					   PU_Info* pu_forest, 
					   PUXlationContext& ctxt) {
    // We implicitly create the ScopeHierarchy/ScopeGraph using
    // DFS-style iteration of PUs.  In addition to the global scope,
    // there is one scope for each PU.
    xos << xml::BegElem("xaif:ScopeHierarchy");
    // translate global symbol table
   fortTkSupport::SymTabId scopeId = ctxt.findSymTabId(Scope_tab[GLOBAL_SYMTAB].st_tab);
    xos << xml::BegElem("xaif:Scope") << xml::Attr("vertex_id", scopeId)
	<< SymTabIdAnnot(scopeId) << xml::EndAttrs;
    xlate_SymbolTables(xos, GLOBAL_SYMTAB, NULL, ctxt);
    xos << xml::EndElem << std::endl;
    // translate each PU, descending into children first
    for (PU_Info *pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
      translateScopeHierarchyPU(xos, pu, scopeId, ctxt);
    }
    xos << xml::EndElem; /* xaif:ScopeHierarchy */
    xos << std::endl;
  }

  void Whirl2Xaif::translateScopeHierarchyPU(xml::ostream& xos, 
					     PU_Info* pu, 
					     UINT32 parentId, 
					     PUXlationContext& ctxt) {
    PU_SetGlobalState(pu);
    // Need WHIRL<->ID maps for translating ScalarizedRefs
    fortTkSupport::WNToWNIdMap* wnmap = ourWNToWNIdTableMap.Find(pu);
    ctxt.setWNToIdMap(wnmap);
    fortTkSupport::ScalarizedRefTab_W2X* tab = ourScalarizedRefTableMap.Find(pu);
   fortTkSupport::SymTabId scopeId = ctxt.findSymTabId(Scope_tab[CURRENT_SYMTAB].st_tab);  
    // translate symbol tables 
    xos << xml::BegElem("xaif:Scope") << xml::Attr("vertex_id", scopeId) 
	<< SymTabIdAnnot(scopeId) << xml::EndAttrs;
    xlate_SymbolTables(xos, CURRENT_SYMTAB, tab, ctxt);
    xos << xml::EndElem << std::endl;
    // Generate an edge to parent
    DumpScopeGraphEdge(xos, ctxt.currentXlationContext().getNewEdgeId(), scopeId, parentId);
    xos << std::endl;
    // Recursively translate all children
    for (PU_Info *child = PU_Info_child(pu); child != NULL;
	 child = PU_Info_next(child)) {
      translateScopeHierarchyPU(xos, child, scopeId, ctxt);
    }
  }

  void Whirl2Xaif::translateAnalMaps(xml::ostream& xos, 
				     PU_Info* pu_forest, 
				     PUXlationContext& ctxt) {
    // -------------------------------------------------------
    // AliasSetList: The first element has to be there
    // -------------------------------------------------------
    xos << xml::BegElem("xaif:AliasSetList");
    xos << xml::BegElem("xaif:AliasSet") << xml::Attr("key", 0);
    xos << xml::BegElem("xaif:AliasRange") 
	<< xml::Attr("from_virtual_address", 1) 
	<< xml::Attr("to_virtual_address", 1) 
	<< xml::EndElem;
    xos << xml::EndElem; // xaif:AliasSet
    Open64IRProcIterator procIt(pu_forest);
    // iterate over processed units
    for (int procCnt = 1; procIt.isValid(); ++procIt, ++procCnt) {
      PU_Info* pu = (PU_Info*)procIt.current().hval();
      fortTkSupport::OAAnalInfo* oaAnal = ourOAAnalMap.Find(pu);
      fortTkSupport::WNToWNIdMap* wnmap = ourWNToWNIdTableMap.Find(pu);
      OA::OA_ptr<OA::XAIF::AliasMapXAIF> aliasSets = oaAnal->GetAliasXAIF();
      OA::OA_ptr<OA::XAIF::IdIterator> aliasSetIdsIter = aliasSets->getIdIterator();
      // iterate over alias sets
      for ( ; aliasSetIdsIter->isValid(); ++(*aliasSetIdsIter)) {
	xos << xml::BegElem("xaif:AliasSet") << xml::Attr("key", aliasSetIdsIter->current());
	OA::OA_ptr<OA::XAIF::LocTupleIterator> aLocTupleIter = aliasSets->getLocIterator(aliasSetIdsIter->current()); 
	// iterate over alias ranges
	for ( ; aLocTupleIter->isValid(); ++(*aLocTupleIter) ) {
	  xos << xml::BegElem("xaif:AliasRange");
	  xos << xml::Attr("from_virtual_address", aLocTupleIter->current().getLocRange().getStart());
	  xos << xml::Attr("to_virtual_address", aLocTupleIter->current().getLocRange().getEnd());
	  xos << xml::Attr("partial", !(aLocTupleIter->current().isFull()));
	  xos << xml::EndElem;
	}
	xos << xml::EndElem; // xaif:AliasSet
      }
    }
    xos << xml::EndElem; // xaif:AliasSetList
    xos << std::endl;
    // -------------------------------------------------------
    // DUUDSetList: The first two elements are the *same* for each procedure.
    // -------------------------------------------------------
    xos << xml::BegElem("xaif:DUUDSetList");
    procIt.reset();
    for (int procCnt = 1; procIt.isValid(); ++procIt, ++procCnt) {
      PU_Info* pu = (PU_Info*)procIt.current().hval();
      fortTkSupport::OAAnalInfo* oaAnal = ourOAAnalMap.Find(pu);
      fortTkSupport::WNToWNIdMap* wnmap = ourWNToWNIdTableMap.Find(pu);
      OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> udduchains = oaAnal->GetUDDUChainsXAIF();
      OA::OA_ptr<OA::XAIF::UDDUChainsXAIF::ChainIterator> chainIter 
	= udduchains->getChainIterator();
      for ( ; chainIter->isValid(); ++(*chainIter)) {
	OA::OA_ptr<OA::XAIF::UDDUChainsXAIF::ChainStmtIterator> siter 
	  = chainIter->currentChainStmtIterator();
	int chainid = chainIter->currentId(); // 0-2 are same for each proc
	if ((0 <= chainid && chainid <= 2) && procCnt != 1) { continue; }
	xos << xml::BegElem("xaif:DUUDSet") << xml::Attr("key", chainid);
	for ( ; siter->isValid(); (*siter)++ ) {
	  OA::StmtHandle stmt = siter->current();
	  WN* stmtWN = (WN*)(stmt.hval());
	  fortTkSupport::WNId stmtid = wnmap->Find(stmtWN);
	  xos << xml::BegElem("xaif:StatementId");
	  if (stmtWN == NULL) {
	    xos << xml::Attr("idRef", "");
	  }
	  else {
	    xos << xml::Attr("idRef", stmtid);
	  }
	  xos << xml::EndElem;
	}
	xos << xml::EndElem; // xaif:DUUDSet
      }
    }
    xos << xml::EndElem; // xaif:DUUDSetList
    xos << std::endl;
  }

  void Whirl2Xaif::translatePU(xml::ostream& xos, 
			       OA::OA_ptr<OA::CallGraph::Node> n, 
			       UINT32 vertexId, 
			       PUXlationContext& ctxt) {
    // FIXME: A more general test will be needed
    PU_Info* pu = (PU_Info*)n->getProc().hval();
    FORTTK_ASSERT(pu, fortTkSupport::Diagnostics::UnexpectedInput << "PU is NULL");
    translatePU(xos, pu, n->getId(), ctxt);
    xos << std::endl;
    xos.flush();
  }

  void Whirl2Xaif::translatePU(xml::ostream& xos, 
			       PU_Info *pu, 
			       UINT32 vertexId,
			       PUXlationContext& ctxt) {
    if (!pu) { return; }
    PU_SetGlobalState(pu);
    bool isCompilerGen = ((Language == LANG_F90) && 
			  (CURRENT_SYMTAB == GLOBAL_SYMTAB + 2) && 
			  Is_Set_PU_Info_flags(pu, PU_IS_COMPILER_GENERATED));
    Is_True(!isCompilerGen, ("Compiler generated PU!")); // FIXME
    // -------------------------------------------------------
    // translate the PU
    // -------------------------------------------------------
    // FIXME: how is PU_f90_lang() different from (Language == LANG_F90)?
    PU& real_pu = PU_Info_pu(pu); 
    ctxt.setF90(PU_f90_lang(real_pu) != 0); // FIXME: set F90 flag
    bool isProgram = PU_is_mainpu(real_pu);
    ST* st = ST_ptr(PU_Info_proc_sym(pu));
    WN *wn_pu = PU_Info_tree_ptr(pu);
    fortTkSupport::PUId puId = ctxt.findPUId(pu);
    ST_TAB* sttab = Scope_tab[ST_level(st)].st_tab;
   fortTkSupport::SymTabId scopeId = ctxt.findSymTabId(sttab);
   fortTkSupport::SymTabId puScopeId = ctxt.findSymTabId(Scope_tab[CURRENT_SYMTAB].st_tab);
    // Generate the CFG
    xos << xml::Comment(ourDividerComment.c_str());
    if (isProgram) { xos << xml::Comment("*** This is the PROGRAM routine ***"); }
    xos << xml::BegElem("xaif:ControlFlowGraph") 
	<< xml::Attr("vertex_id", vertexId) << xml::Attr("scope_id", scopeId)
	<< AttrSymId(st) << PUIdAnnot(puId)
	<< xml::Attr("controlflowgraph_scope_id", puScopeId)
	<< xml::EndAttrs;
    if (IsActivePU(st)) {
      translateWNPU(xos, wn_pu, ctxt);
    }
    xos << xml::EndElem; // xaif:ControlFlowGraph
  }

  void Whirl2Xaif::translateWNPU(xml::ostream& xos, 
				 WN *wn_pu, 
				 PUXlationContext& ctxt) {
    const char* const caller_err_phase = Get_Error_Phase();
    Diag_Set_Phase("WHIRL to XAIF: translate PU");
    Is_True(WN_opcode(wn_pu) == OPC_FUNC_ENTRY, ("Invalid opcode"));
    // fdump_tree(stderr, wn_pu);
    TranslateWN(xos, wn_pu, ctxt);
    Stab_Free_Tmpvars();  // FIXME: it would be nice to eventually 
    Stab_Free_Namebufs(); // remove this stuff
    Diag_Set_Phase(caller_err_phase);
  }

  void Whirl2Xaif::dumpTranslationHeaderComment(xml::ostream& xos) {
    // 1. Get a string representation of the time
    char tmStr[30] = "unknown time\n";
    time_t tm = time(NULL);
    if (tm != (time_t)-1) { strcpy(tmStr, ctime(&tm)); }
    tmStr[strlen(tmStr)-1] = '\0'; // remove the trailing '\n'
    // 2. Generate header comment
    xos << xml::Comment(ourDividerComment.c_str())
	<< xml::BegComment << "XAIF file translated from WHIRL at " << tmStr 
	<< xml::EndComment
	<< xml::Comment(ourDividerComment.c_str()) << std::endl;
  }

}
