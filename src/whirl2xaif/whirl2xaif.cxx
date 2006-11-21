// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.cxx,v 1.53 2006/05/12 16:12:23 utke Exp $


#include <time.h>
#include <fstream>

#include "include/Open64BasicTypes.h"
#include "lib/support/Open64IRInterface.hpp"
#include "whirl2xaif.h"
#include "wn2xaif.h"
#include "st2xaif.h"

namespace whirl2xaif { 

  fortTkSupport::IntrinsicXlationTable   
  Whirl2Xaif::ourIntrinsicTable(fortTkSupport::IntrinsicXlationTable::W2X);

  PUToOAAnalInfoMap       Whirl2Xaif::ourOAAnalMap;
  fortTk::ScalarizedRefTabMap_W2X Whirl2Xaif::ourScalarizedRefTableMap;
  WNToWNIdTabMap          Whirl2Xaif::ourWNToWNIdTableMap;
  const std::string       Whirl2Xaif::ourDividerComment("********************************************************************");

  fortTkSupport::IntrinsicXlationTable& Whirl2Xaif::getIntrinsicXlationTable() { 
    return ourIntrinsicTable;
  }

  PUToOAAnalInfoMap& Whirl2Xaif::getOAAnalMap() { 
    return ourOAAnalMap;
  }

  fortTk::ScalarizedRefTabMap_W2X& Whirl2Xaif::getScalarizedRefTableMap() { 
    return ourScalarizedRefTableMap;
  }

  WNToWNIdTabMap& Whirl2Xaif::getWNToWNIdTableMap() { 
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
    SymTabToSymTabIdMap* stabmap = new SymTabToSymTabIdMap(pu_forest);
    ctxt.setSymTabToIdMap(stabmap);
    PUToPUIdMap* pumap = new PUToPUIdMap(pu_forest);
    ctxt.setPUToIdMap(pumap);
    ourWNToWNIdTableMap.Create(pu_forest); // Note: could make this local
    // Initialize and create inter/intra analysis information
    ourOAAnalMap.Create(pu_forest);
    ctxt.setActivity(ourOAAnalMap.GetInterActive());
    // Create scalarized var reference table
    ourScalarizedRefTableMap.Create(pu_forest);
    // -------------------------------------------------------
    // 2. Generate XAIF CallGraph
    // -------------------------------------------------------
    OA::OA_ptr<OA::CallGraph::CallGraphStandard> cgraph = 
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
      OA::OA_ptr<OA::DGraph::Interface::Node> ntmp = *nodeIt;
      OA::OA_ptr<CallGraphStandard::Node> n = 
	ntmp.convert<CallGraphStandard::Node>();
      translatePU(xos, n, n->getId(), ctxt);
      ctxt.deleteXlationContext();
    }
    delete nodes;
    // CallGraph edges
    DGraphEdgeVec* edges = SortDGraphEdges(cgraph);
    for (DGraphEdgeVec::iterator edgeIt = edges->begin(); 
	 edgeIt != edges->end(); ++edgeIt) {
      OA::OA_ptr<OA::DGraph::Interface::Edge> e = (*edgeIt);
      OA::OA_ptr<OA::DGraph::Interface::Node> n1 = e->source();
      OA::OA_ptr<OA::DGraph::Interface::Node> n2 = e->sink();
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
    SymTabId scopeId = ctxt.findSymTabId(Scope_tab[GLOBAL_SYMTAB].st_tab);
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
    WNToWNIdMap* wnmap = ourWNToWNIdTableMap.Find(pu);
    ctxt.setWNToIdMap(wnmap);
    fortTk::ScalarizedRefTab_W2X* tab = ourScalarizedRefTableMap.Find(pu);
    SymTabId scopeId = ctxt.findSymTabId(Scope_tab[CURRENT_SYMTAB].st_tab);  
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
      OAAnalInfo* oaAnal = ourOAAnalMap.Find(pu);
      WNToWNIdMap* wnmap = ourWNToWNIdTableMap.Find(pu);
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
      OAAnalInfo* oaAnal = ourOAAnalMap.Find(pu);
      WNToWNIdMap* wnmap = ourWNToWNIdTableMap.Find(pu);
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
	  WNId stmtid = wnmap->Find(stmtWN);
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
			       OA::OA_ptr<OA::CallGraph::CallGraphStandard::Node> n, 
			       UINT32 vertexId, 
			       PUXlationContext& ctxt) {
    // FIXME: A more general test will be needed
    PU_Info* pu = (PU_Info*)n->getProc().hval();
    FORTTK_ASSERT(pu, FORTTK_UNEXPECTED_INPUT << "PU is NULL");
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
    PUId puId = ctxt.findPUId(pu);
    ST_TAB* sttab = Scope_tab[ST_level(st)].st_tab;
    SymTabId scopeId = ctxt.findSymTabId(sttab);
    SymTabId puScopeId = ctxt.findSymTabId(Scope_tab[CURRENT_SYMTAB].st_tab);
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

  void Whirl2Xaif::backSubstituteLoopBoundsPU_InfoForrest(PU_Info* aPU_InfoForrest_p) { 
    Diag_Set_Phase("WHIRL to XAIF: backSubstituteLoopBounds");
    if (!aPU_InfoForrest_p) { return; }
    /* Loop thru all the PU_Infos */
    PU_Info* aPU_InfoTree_p;
    for (aPU_InfoTree_p=aPU_InfoForrest_p; aPU_InfoTree_p!= NULL; aPU_InfoTree_p=PU_Info_next(aPU_InfoTree_p)) {
      backSubstituteLoopBoundsPU_InfoTree(aPU_InfoTree_p);
    }
  } 

  void Whirl2Xaif::backSubstituteLoopBoundsPU_InfoTree(PU_Info* aPU_InfoTree_p) { 
    if (!aPU_InfoTree_p) { return; }
    backSubstituteLoopBoundsPU_Info(aPU_InfoTree_p);
    for (PU_Info *aPU_Infosubtree_p = PU_Info_child(aPU_InfoTree_p); 
	 aPU_Infosubtree_p != NULL; 
	 aPU_Infosubtree_p = PU_Info_next(aPU_Infosubtree_p)) {
      backSubstituteLoopBoundsPU_InfoTree(aPU_Infosubtree_p);
    }
  }

  void Whirl2Xaif::backSubstituteLoopBoundsPU_Info(PU_Info* aPU_Info_p) { 
    typedef std::map<ST*,WN*> STPtoWNPmap;
    STPtoWNPmap tempMap; 
    bool skipKids=false;
    PU_SetGlobalState(aPU_Info_p);
    WN* wn_pu = PU_Info_tree_ptr(aPU_Info_p);
    WN* parentWN_p=0;
    WN_TREE_CONTAINER<PRE_ORDER> aWNPtree(wn_pu);
    WN_TREE_CONTAINER<PRE_ORDER>::iterator aWNPtreeIterator=aWNPtree.begin();
    while (aWNPtreeIterator != aWNPtree.end()) { 
      WN* curWN_p = aWNPtreeIterator.Wn();
      OPERATOR opr = WN_operator(curWN_p);
      if (opr==OPR_STID) {  // definitions
	if (ST_is_temp_var(WN_st(curWN_p))) {
	  ST* tempST_p=WN_st(curWN_p);
	  // is it not in the set? 
	  if (tempMap.find(tempST_p) == tempMap.end()) { //not found
	    // add it
	    tempMap.insert(std::pair<ST*,WN*>(tempST_p,WN_kid0(curWN_p)));
	    const char* tmpName = ST_name(tempST_p); 
	    ST* puST_p = ST_ptr(PU_Info_proc_sym(aPU_Info_p));
	    const char* puName = ST_name(puST_p);
	    FORTTK_MSG(2, "Whirl2Xaif::backSubstituteLoopBoundsPU_Info: recorded temporary " << tmpName << "  defined in " << puName);
	  }
	  else { // this should not happen since these are supposed to be single assignment
	    const char* tmpName = ST_name(tempST_p); 
	    ST* puST_p = ST_ptr(PU_Info_proc_sym(aPU_Info_p));
	    const char* puName = ST_name(puST_p);
	    FORTTK_MSG(0, "Whirl2Xaif::backSubstituteLoopBoundsPU_Info: recorded temporary " << tmpName << " is redefined in " << puName);
	  }
	}
      }
      if (opr==OPR_LDID){ // uses
	// if we refer to a temp variable
	if (ST_is_temp_var(WN_st(curWN_p))) { 
	  // that variable should have been added to the set
	  // so find it: 
	  ST* tempST_p=WN_st(curWN_p);
	  STPtoWNPmap::iterator mapIter=tempMap.find(tempST_p);
	  if (mapIter==tempMap.end()) { //not found
	    // this shouldn't happen since we expect to have all of the definitions
	    const char* tmpName = ST_name(tempST_p); 
	    ST* puST_p = ST_ptr(PU_Info_proc_sym(aPU_Info_p));
	    const char* puName = ST_name(puST_p);
	    FORTTK_DIE("Whirl2Xaif::backSubstituteLoopBoundsPU_Info: no definition for temporary " << tmpName << " in " << puName);
	  }
	  // make sure the parent is set by now
	  if (!aWNPtreeIterator.Get_parent_wn())
	    FORTTK_DIE("Whirl2Xaif::backSubstituteLoopBoundsPU_Info: no parent set");
	  // replace the current node within the parent
	  WN_kid(aWNPtreeIterator.Get_parent_wn(),aWNPtreeIterator.Get_kid_index()) = WN_COPY_Tree((*mapIter).second);
	  skipKids=true;
	  const char* tmpName = ST_name(tempST_p); 
	  ST* puST_p = ST_ptr(PU_Info_proc_sym(aPU_Info_p));
	  const char* puName = ST_name(puST_p);
	  FORTTK_MSG(2, "JU: Whirl2Xaif::backSubstituteLoopBoundsPU_Info: substituted temporary " << tmpName << "  in " << puName);
	}
      } 
      // advance the iterator
      if (skipKids || opr==OPR_XPRAGMA){
	// XPRAGMAs may refer to temporaries before they are assigned
	aWNPtreeIterator.WN_TREE_next_skip();
	skipKids=false;
      }
      else
	++aWNPtreeIterator;
    } // end while
  } 

}
