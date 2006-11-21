// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/OAMaps.cxx,v 1.9 2006/01/18 15:42:12 utke Exp $


#include "Open64IRInterface/Open64IRInterface.hpp"
#include "OAMaps.h"
#include "WhirlParentize.h"
#include "XAIFStrings.h"

namespace fortTkSupport {

  // CreatePUToOAAnalInfoMap: Given a PU forest, initialize the non-NULL
  // persistent ID <-> PU_Info* maps.  PUIds are guaranteed to be unique
  // within the PU forest 'pu_forest'.
  static void
  CreatePUToOAAnalInfoMap(PU_Info* pu_forest, PUToOAAnalInfoMap* x);

  // CreateOAAnalInfo
  static void
  CreateOAAnalInfo(PU_Info* pu, PUToOAAnalInfoMap* inter, OAAnalInfo* x);

  OA::OA_ptr<OA::CFG::CFGInterface>
  CreateCFG(PU_Info* pu, OA::OA_ptr<OA::CFG::EachCFGInterface> cfgeach,
	    OA::OA_ptr<Open64IRInterface> irIF);


  static void
  MassageOACallGraphIntoXAIFCallGraph(OA::OA_ptr<OA::CallGraph::CallGraph> cg);

  static void
  AddControlFlowEndTags(PU_Info* pu, WhirlParentMap* wnParentMap, 
			OA::OA_ptr<Open64IRInterface> irIF);


  static void
  MassageOACFGIntoXAIFCFG(OA::OA_ptr<OA::CFG::CFG> cfg,
			  OA::OA_ptr<Open64IRInterface> irIF);

  static void
  collectGlobalVarActivityInfo(OA::OA_ptr<OA::Activity::InterActive> active,
			       OA::OA_ptr<Open64IRInterface> irIF,
			       PU_Info* pu_forest);


  // ***************************************************************************
  // OAAnalInfo
  // ***************************************************************************

  std::set<ST*> OAAnalInfo::ourActiveGlobalSTPSet;

  OAAnalInfo::~OAAnalInfo() 
  { 
    // OA_ptr will clean up all Managers and analysis results once
    // they are no longer referenced
  }

  void
  OAAnalInfo::Create(PU_Info* pu, PUToOAAnalInfoMap* interInfo)
  { 
    CreateOAAnalInfo(pu, interInfo, this);
  }

  // ***************************************************************************
  // PUToOAAnalInfoMap
  // ***************************************************************************

  void
  PUToOAAnalInfoMap::Create(PU_Info* pu_forest)
  {
    CreatePUToOAAnalInfoMap(pu_forest, this);
  }

  // ***************************************************************************
  // Optional routines for map creation
  // ***************************************************************************

  // CreatePUIdMaps: Create id's based on Open64IRProcIterator. 
  void
  CreatePUToOAAnalInfoMap(PU_Info* pu_forest, PUToOAAnalInfoMap* x)
  {
    if (!pu_forest) { return; }
  
    OA::OA_ptr<Open64IRInterface> irIF; irIF = new Open64IRInterface;
    Open64IRInterface::initContextState(pu_forest);
    x->SetIRInterface(irIF);

    OA::OA_ptr<Open64IRProcIterator> procIt;
    procIt = new Open64IRProcIterator(pu_forest);
  
    // Create CFGs [FIXME: and perform MemRefExprKludge]
    // first Create CFG 'manager' (compute CFG on demand)
    OA::OA_ptr<OA::CFG::ManagerCFGStandard> cfgman;
    cfgman = new OA::CFG::ManagerCFGStandard(irIF);
    OA::OA_ptr<OA::CFG::EachCFGInterface> cfgeach;
    cfgeach = new OA::CFG::EachCFGStandard(cfgman);
    FORTTK_MSG(1, "progress: CreateCFG");
    for ( ; procIt->isValid(); ++(*procIt)) { 
      PU_Info* pu = (PU_Info*)procIt->current().hval();
      OA::OA_ptr<OA::CFG::CFGInterface> cfg = CreateCFG(pu, cfgeach, irIF);
    }
    // For each proc 
    x->SetCFGEach(cfgman, cfgeach);
  
    // Inter Alias 
    FORTTK_MSG(1, "progress: inter alias: performAnalysis");
    OA::OA_ptr<OA::Alias::ManagerFIAliasAliasMap> interaliasmapman;
    interaliasmapman = new OA::Alias::ManagerFIAliasAliasMap(irIF);
    OA::OA_ptr<OA::Alias::InterAliasMap> interAlias;
    interAlias = interaliasmapman->performAnalysis(procIt);
    x->SetInterAlias(interaliasmapman, interAlias);
  
    // Create call graph
    FORTTK_MSG(1, "progress: call graph: performAnalysis");
    // Create call graph (massage OA version into XAIF version below)
    procIt->reset();
    OA::OA_ptr<OA::CallGraph::ManagerCallGraphStandard> cgraphman;
    cgraphman = new OA::CallGraph::ManagerCallGraphStandard(irIF);
    OA::OA_ptr<OA::CallGraph::CallGraph> cgraph = 
      cgraphman->performAnalysis(procIt,interAlias);
    if (0) { cgraph->dump(std::cout, irIF); }
    x->SetCallGraph(cgraphman, cgraph);
  
  
    // -------------------------------------------------------
    // Compute interprocedural analysis info
    // -------------------------------------------------------
    FORTTK_MSG(1, "progress: parameter bindings: performAnalysis");
    // ParamBindings
    OA::OA_ptr<OA::DataFlow::ManagerParamBindings> parambindman;
    parambindman = new OA::DataFlow::ManagerParamBindings(irIF);
    OA::OA_ptr<OA::DataFlow::ParamBindings> parambind
      = parambindman->performAnalysis(cgraph);

    //   // JU: begin debugging stuff
    //   procIt->reset();
    //   for ( ; procIt->isValid(); ++(*procIt)) { 
    //     OA::OA_ptr<OA::SymHandleIterator> symHandleI=parambind->getFormalIterator(procIt->current());
    //     symHandleI->reset();
    //     ST* st = ST_ptr(PU_Info_proc_sym((PU_Info*)procIt->current().hval()));
    //     const char* nm = ST_name(st);
    //     if (!symHandleI->isValid())
    //       std::cout << "Note: after performAnalysis: empty symHandleI for " << nm << std::endl;
    //     else { 
    //       for ( ; symHandleI->isValid(); ++(*symHandleI)) { 
    // 	ST* st1 = (ST*)(symHandleI->current().hval());
    // 	const char* nm1 = ST_name(st1);
    // 	std::cout << "Note: after performAnalysis: symHandleI for " 
    // 		  << nm 
    // 		  << " contains " 
    // 		  << nm1 
    // 		  <<  std::endl;
    //       }
    //     }
    //   }
    //   // JU: end debugging stuff

    x->SetParamBind(parambindman, parambind);

    // Side Effect
    FORTTK_MSG(1, "progress: side effect: performAnalysis");
    OA::OA_ptr<OA::SideEffect::ManagerSideEffectStandard> sideeffectman;
    sideeffectman = new OA::SideEffect::ManagerSideEffectStandard(irIF);

    x->SetSideEffect(sideeffectman);

    // Inter Side Effect
    FORTTK_MSG(1, "progress: inter side effect: performAnalysis");
    OA::OA_ptr<OA::SideEffect::ManagerInterSideEffectStandard> interSEman;
    interSEman = new OA::SideEffect::ManagerInterSideEffectStandard(irIF);
    OA::OA_ptr<OA::SideEffect::InterSideEffectStandard> interSE;
    interSE = interSEman->performAnalysis(cgraph, parambind,
					  interAlias, sideeffectman);

    x->SetInterSideEffect(interSEman, interSE);
  
    // ICFG
    FORTTK_MSG(1, "progress: icfg standard: performAnalysis");
    OA::OA_ptr<OA::ICFG::ManagerICFGStandard> icfgman;
    icfgman = new OA::ICFG::ManagerICFGStandard(irIF);
    OA::OA_ptr<OA::ICFG::ICFG> icfg 
      = icfgman->performAnalysis(procIt,cfgeach,cgraph);

    // Activity Analysis
    FORTTK_MSG(1, "progress: icfg activity: performAnalysis");
    OA::OA_ptr<OA::Activity::ManagerICFGActive> activeman;
    activeman = new OA::Activity::ManagerICFGActive(irIF);
    OA::OA_ptr<OA::Activity::InterActive> active;
    active = activeman->performAnalysis(icfg, 
					parambind,
					interAlias, 
					interSE);


    FORTTK_MSG(1, "ICFG Active Output");
    active->output(*irIF);   
    FORTTK_MSG(1, "**************************************");
    
    OAAnalInfo::collectGlobalSymbolActivityInfo(active,
						interAlias,
						irIF,
						pu_forest);

    x->SetInterActive(activeman, active);
    
    // -------------------------------------------------------
    // For each PU, compute intraprocedural analysis info
    // -------------------------------------------------------
    FORTTK_MSG(1, "progress: intraprocedural analysis");
    procIt->reset();
    for ( ; procIt->isValid(); ++(*procIt)) { 
      PU_Info* pu = (PU_Info*)procIt->current().hval();
      ST* st = ST_ptr(PU_Info_proc_sym(pu));
      const char* nm = ST_name(st);
      FORTTK_MSG(1, "progress: analysing SUBROUTINE " << nm );
      OAAnalInfo* info = new OAAnalInfo(pu, x);
      x->Insert(pu, info);
    }
  
    // -------------------------------------------------------
    // Post-analysis
    // -------------------------------------------------------
  
    // Now massage the Call Graph into something that XAIF can use
    FORTTK_MSG(1, "progress: call graph: massage for XAIF");
    MassageOACallGraphIntoXAIFCallGraph(cgraph);
  }


  OA::OA_ptr<OA::CFG::CFGInterface>
  CreateCFG(PU_Info* pu, OA::OA_ptr<OA::CFG::EachCFGInterface> cfgeach,
	    OA::OA_ptr<Open64IRInterface> irIF)
  {
    OA::ProcHandle proc((OA::irhandle_t)pu);

    // FIXME: This should probably be a global puinfo->parentmmap map
    WN *wn_pu = PU_Info_tree_ptr(pu);
    WhirlParentMap wnParentMap(wn_pu);

    // -------------------------------------------------------
    // CFG
    // -------------------------------------------------------  
    AddControlFlowEndTags(pu, &wnParentMap, irIF);
  
    // Force computation of CFG
    //OA::CFG::resetIds();
    OA::OA_ptr<OA::CFG::CFGInterface> cfgIF = cfgeach->getCFGResults(proc);
    OA::OA_ptr<OA::CFG::CFG> cfg = cfgIF.convert<OA::CFG::CFG>();
    if (0) { cfg->dump(std::cout, irIF); }
  
    // Massage CFG
    MassageOACFGIntoXAIFCFG(cfg, irIF);
    if (0) { cfg->dump(std::cout, irIF); }

    return cfg;
  }


  // Create OA analyses
  void
  CreateOAAnalInfo(PU_Info* pu, PUToOAAnalInfoMap* inter, OAAnalInfo* x)
  {
    OA::OA_ptr<Open64IRProcIterator> procIt;
    procIt = new Open64IRProcIterator(pu);

    OA::ProcHandle proc((OA::irhandle_t)pu);
    OA::OA_ptr<Open64IRInterface> irIF = inter->GetIRInterface();
    OA::OA_ptr<OA::CFG::CFGInterface> cfg = 
      inter->GetCFGEach()->getCFGResults(proc);
    OA::OA_ptr<OA::SideEffect::InterSideEffectStandard> interSideEffect = 
      inter->GetInterSideEffect();

    // -------------------------------------------------------
    // Compute intraprocedural analysis info
    // -------------------------------------------------------
  
    // Intra Alias
   

/*! commented out by PLM 09/13/06 
    FORTTK_MSG(1, "progress: intra alias: performAnalysis");
    OA::OA_ptr<OA::Alias::ManagerAliasMapBasic> aliasman;
    aliasman = new OA::Alias::ManagerAliasMapBasic(irIF);
    OA::OA_ptr<OA::Alias::AliasMap> alias = aliasman->performAnalysis(proc);
    if (0) { alias->dump(std::cout, irIF); }
    */
    FORTTK_MSG(1, "progress: inter alias: performAnalysis");
    OA::OA_ptr<OA::Alias::ManagerFIAliasAliasMap> interaliasmapman;
    interaliasmapman = new OA::Alias::ManagerFIAliasAliasMap(irIF);
    OA::OA_ptr<OA::Alias::InterAliasMap> interAlias;
    interAlias = interaliasmapman->performAnalysis(procIt);
    OA::OA_ptr<OA::Alias::Interface> alias;
    alias = interAlias->getAliasResults(proc);
    x->SetAlias(interaliasmapman, alias);

  
    // ReachDefs
    FORTTK_MSG(1, "progress: reach defs: performAnalysis");
    OA::OA_ptr<OA::ReachDefs::ManagerReachDefsStandard> rdman;
    rdman = new OA::ReachDefs::ManagerReachDefsStandard(irIF);
    OA::OA_ptr<OA::ReachDefs::ReachDefsStandard> rds 
      = rdman->performAnalysis(proc, cfg, alias, interSideEffect);
    x->SetReachDefs(rdman, rds);

    // UDDU chains
    FORTTK_MSG(1, "progress: uddu: performAnalysis");
    OA::OA_ptr<OA::UDDUChains::ManagerUDDUChainsStandard> udman;
    udman = new OA::UDDUChains::ManagerUDDUChainsStandard(irIF);
    OA::OA_ptr<OA::UDDUChains::UDDUChainsStandard> udduchains 
      = udman->performAnalysis(proc, alias, rds, interSideEffect);
    if (0) { udduchains->dump(std::cout, irIF); }
  
    x->SetUDDUChains(udman, udduchains);

    // -------------------------------------------------------
    // XAIF
    // -------------------------------------------------------
    FORTTK_MSG(1, "progress: alias to xaif: performAnalysis");
    OA::OA_ptr<OA::XAIF::ManagerAliasMapXAIF> aliasmanXAIF;
    aliasmanXAIF = new OA::XAIF::ManagerAliasMapXAIF(irIF);
    OA::OA_ptr<OA::XAIF::AliasMapXAIF> aliasXAIF = 
      aliasmanXAIF->performAnalysis(proc, alias);
  
    x->SetAliasXAIF(aliasmanXAIF, aliasXAIF);

    FORTTK_MSG(1, "progress: ud to xaif : performAnalysis");
    OA::OA_ptr<OA::XAIF::ManagerStandard> udmanXAIF;
    udmanXAIF = new OA::XAIF::ManagerStandard(irIF);
    OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> udduchainsXAIF 
      = udmanXAIF->performAnalysis(proc, cfg, udduchains);
    if (0) { udduchainsXAIF->dump(std::cout, irIF); }
  
    x->SetUDDUChainsXAIF(udmanXAIF, udduchainsXAIF);
  }


  // ***************************************************************************
  //
  // ***************************************************************************

  // MassageOACallGraphIntoXAIFCallGraph: Process CallGraph to eliminate
  // synthetic edges.
  //   - eliminate special Open64 functions and inlinable intrinsics
  //   - need to figure out what to do with non-inlinable intrinsics
  //  
  static void
  MassageOACallGraphIntoXAIFCallGraph(OA::OA_ptr<OA::CallGraph::CallGraph> cg)
  {
    using namespace OA::CallGraph;
  
    // -------------------------------------------------------
    // 1. For now we eliminate nodes without a definition.  
    // -------------------------------------------------------
  
    DGraphNodeList toRemove; // holds basic blocks made empty

    
    
    OA::OA_ptr<OA::DGraph::NodesIteratorInterface> it = cg->getNodesIterator();

    /*! commented out by PLM 08/26/06
    for (NodesIterator it(*cg); it.isValid(); ++it) {
    */

    for( ; it->isValid(); ++(*it))
    {
      OA::OA_ptr<OA::DGraph::NodeInterface> dn = it->current();

      OA::OA_ptr<Node> n = dn.convert<Node>();
      if (n->getProc().hval() == 0) {
	FORTTK_DIAGIF_DEV(2) {
	  ST* st = (ST*)n->getProcSym().hval();
	  std::cout << "* Removing '" << ST_name(st) << "' from CallGraph\n";
	}
	toRemove.push_back(n);
      }
    }
  
    // Remove empty basic blocks
    for (DGraphNodeList::iterator it = toRemove.begin(); 
	 it != toRemove.end(); ++it) 
      {
	OA::OA_ptr<OA::DGraph::NodeInterface> n = (*it);
	cg->removeNode(n);
      }
    toRemove.clear();
  }


  // ***************************************************************************

  // AddControlFlowEndTags: Add control flow end tags
  // FIXME: assumes fully structured control flow???
  static void
  AddControlFlowEndTags(PU_Info* pu, WhirlParentMap* wnParentMap, 
			OA::OA_ptr<Open64IRInterface> irIF)
  {
    // FIXME: we should be skipping most expression sub trees like
    // interface to NewOA.
  
    WN* wn = PU_Info_tree_ptr(pu);

    WN_TREE_CONTAINER<PRE_ORDER> wtree(wn);
    WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
    for (it = wtree.begin(); it != wtree.end(); ++it) {
      WN* curWN = it.Wn();
      OPERATOR opr = WN_operator(curWN);
    
      const char* vty = GetCFGControlFlowVertexType(curWN);
      if (!vty) { continue; }
    
      // Find structured (and some unstructured) control flow and insert
      // placehoder statement.
      if (vty == XAIFStrings.elem_BBForLoop() || 
	  vty == XAIFStrings.elem_BBPostLoop() ||
	  vty == XAIFStrings.elem_BBPreLoop()) {
	// do (...)
	//   ...
	// * EndLoop
	// enddo
	WN* blkWN = NULL;
	if (opr == OPR_DO_LOOP) { 
	  blkWN = WN_do_body(curWN); 
	} else {
	  blkWN = WN_while_body(curWN);
	}
	WN* newWN = WN_CreateComment((char*)XAIFStrings.elem_BBEndLoop());
	WN_INSERT_BlockLast(blkWN, newWN);
	irIF->setContext((OA::irhandle_t)newWN, (OA::irhandle_t)pu);
      }
      else if (vty == XAIFStrings.elem_BBBranch()) {
	WN* ipWN = NULL;
	if (opr == OPR_SWITCH) {
	  //   switch(...) [unstructured]
	  //     casegoto L2
	  //     casegoto L3
	  //   end
	  //   L2 ... L3 ...
	  //   L1 (branch-around-label: beginning of code after switch)
	  // * EndBranch
	  INT32 lbl = WN_last_label(curWN);
	  for (WN* x = WN_next(curWN); x; x = WN_next(x)) {
	    if (WN_operator(x) == OPR_LABEL && WN_label_number(x) == lbl) {
	      ipWN = x;
	      break;
	    }
	  }
	} 
	else {
	  //   if (...) { ... }  OR   if (...) goto77 [unstructured]
	  //   else { ... }         * EndBranch      
	  //   endif                                
	  // * EndBranch
	  ipWN = curWN;
	}
	if (ipWN) {
	  WN* blkWN = wnParentMap->FindBlock(ipWN);
	  WN* newWN = WN_CreateComment((char*)XAIFStrings.elem_BBEndBranch());
	  WN_INSERT_BlockAfter(blkWN, ipWN, newWN); // 'newWN' after 'ipWN'
	  irIF->setContext((OA::irhandle_t)newWN, (OA::irhandle_t)pu);
	}
      }
    }
  }


  // MassageOACFGIntoXAIFCFG: Convert an OpenAnalysis CFG into a valid
  // XAIF CFG.  
  // 
  // 1. OpenAnalysis creates basic blocks with labels at the beginning
  // and branches at the end.  E.g. for TWOWAY_CONDITIONAL and
  // MULTIWAY_CONDITIONAL statements OpenAnalysis may generate BBs such
  // as:
  //
  // Code:                   | BBs:
  //   x = 5                 |          x = 5
  //   if (x .eq. 5) then    |          if (x .eq. 5)
  //     x = 6               |       _______/\_________
  //   else                  |      /                  \   
  //     x = 7               |  x = 6                  x = 7
  //   ...                   |      \-------  ---------/   
  //                         |              \/
  //                         |            ......
  // 
  // While OA creates correct BBs, in order to create valid XAIF, the
  // first BB must be split so that the if condition can be placed
  // within xaif:If.  We create a new BB here so that the translation
  // into XAIF is easy:
  // 
  //   <xaif:BasicBlock>
  //     <xaif:Assignment...
  //     </xaif:Asignment>
  //   </xaif:BasicBlock>
  // 
  //   <xaif:Branch>
  //     <xaif:Condition...
  //     </xaif:Condition>
  //   </xaif:If>
  // 
  // 2. OpenAnalysis places the initialization and update nodes of
  // OPR_DO_LOOPs in the appropriate BB: they are virtually (but not
  // really) spliced out of the OPR_DO_LOOPs.  For example an
  // OPR_DO_LOOP node with initialization, condition, update, and a
  // block of statements may become:
  //
  //                   ....
  //                   DO_LOOP initialization
  //                              |
  //                              v
  //                      DO_LOOP condition <--------------|
  //                      _______/\________                |
  //                     /                 \               |
  //                    |            DO_LOOP statements    |
  //                    |            DO_LOOP update     ---| 
  //                    v
  //                  .....
  //
  // Because XAIF can preserve and exploit high level control strucures
  // such as OPR_DO_LOOP, we want to *remove* the initialization and
  // update statement so they can be placed in the special xaif:ForLoop
  // construct.  xaif2whirl also depends on this transformation.
  //
  // [When xaif2whirl deletes the translation interval for the first BB
  // above (for subsequent replacement), it actually deletes the whole
  // OPR_DO_LOOP node!  Testing for special conditions doesn't help much
  // because when WHIRL is created from the new XAIF, we do not know how to
  // replace the deleted loop initialization node.]
  //
  // 3. Split basic blocks with EndLoop and EndBranch tags.  EndLoop and
  // EndBranch are taged statements inserted into WHIRL so that
  // corresponding CFG nodes will identify structured loops and
  // branches.  Since EndLoops and EndBranches must be mpty BBs we must
  // split any would in them into BasicBlocks.
  // 
  static void
  MassageOACFGIntoXAIFCFG(OA::OA_ptr<OA::CFG::CFG> cfg,
			  OA::OA_ptr<Open64IRInterface> irIF)
  {
   /* commented out by PLM 08/27/06
    * using namespace OA::CFG;
    */

    typedef std::list< pair<CFGNodeList::iterator, WN*> > MySplitList;

    //DGraphNodeList workList;  
    CFGNodeList workList;  
    MySplitList toSplit; // nodes to split

    OA::OA_ptr<OA::DGraph::NodesIteratorInterface> nodeItTmp; 

    // -------------------------------------------------------
    // 1. Find BBs with conditionals and split them
    // -------------------------------------------------------

    // a. Collect all BBs with more that one stmt into 'workList'
    nodeItTmp = cfg->getNodesIterator();
    for ( ; nodeItTmp->isValid(); ++(*nodeItTmp)) {
      OA::OA_ptr<OA::DGraph::NodeInterface> dn = nodeItTmp->current();
      OA::OA_ptr<OA::CFG::NodeInterface> n = dn.convert<OA::CFG::NodeInterface>();
      if ( (n->size() > 1) ) { 
	workList.push_back(n);
      }
    }
  
    // b. Iterate over 'workList' nodes.  For each node examine the
    // statements.  If a conditional is found at the end of the BB,
    // split it.  A block will only need to be split at most once.
    for (CFGNodeList::iterator wnodeIt = workList.begin(); 
	 wnodeIt != workList.end(); ++wnodeIt) {
      OA::OA_ptr<OA::CFG::NodeInterface> n = (*wnodeIt);
      // n->longdump(cfg, std::cerr);
    
      OA::OA_ptr<OA::CFG::NodeStatementsIteratorInterface> stmtItPtr
	= n->getNodeStatementsIterator();
      for (; stmtItPtr->isValid(); ++(*stmtItPtr)) {
	OA::StmtHandle stmt = stmtItPtr->current();

    OA::CFG::IRStmtType ty = irIF->getCFGStmtType(stmt);
	if (ty == OA::CFG::STRUCT_TWOWAY_CONDITIONAL
	    || ty == OA::CFG::USTRUCT_TWOWAY_CONDITIONAL_T
	    || ty == OA::CFG::USTRUCT_TWOWAY_CONDITIONAL_F
	    || ty == OA::CFG::STRUCT_MULTIWAY_CONDITIONAL
	    || ty == OA::CFG::USTRUCT_MULTIWAY_CONDITIONAL) {
	  toSplit.push_back(make_pair(wnodeIt, (WN*)stmt.hval()));
	  break;
	}
      }
    }
  
    // c. Split blocks
    for (MySplitList::iterator it = toSplit.begin(); it != toSplit.end(); ++it) {
      CFGNodeList::iterator wnodeIt = (*it).first;
      OA::OA_ptr<OA::CFG::NodeInterface> ntmp = *wnodeIt;
      OA::OA_ptr<OA::CFG::Node> n 
	= ntmp.convert<OA::CFG::Node>();
      WN* startWN = (*it).second;
    
      OA::StmtHandle stmt((OA::irhandle_t)startWN);
      OA::OA_ptr<OA::CFG::Node> newblock = cfg->splitBlock(n, stmt);
      cfg->connect(n, newblock, OA::CFG::FALLTHROUGH_EDGE);
      //n->longdump(cfg);
      //newblock->longdump(cfg);
    }
    toSplit.clear();
  
    // d. clear 'workList'
    workList.clear();
  
  
    // -------------------------------------------------------
    // 2. Recover OPR_DO_LOOPs
    // -------------------------------------------------------
  
    // This process can create empty basic blocks
    CFGNodeList toRemove; // basic blocks made empty (slated for removal)
  
  
    nodeItTmp = cfg->getNodesIterator();
    for ( ; nodeItTmp->isValid(); ++(*nodeItTmp)) {
      OA::OA_ptr<OA::DGraph::NodeInterface> dn = nodeItTmp->current();
      OA::OA_ptr<OA::CFG::Node> n = dn.convert<OA::CFG::Node>();

      // Use CFG nodes representing the OPR_DO_LOOP condition to find
      // initialization and update information.  With this info, remove
      // the initialization and update statements from whatever BB they
      // may be in.  New basic blocks are not created.

      // FIXME: use a better classification method 
      if (GetCFGVertexType(cfg, n) == XAIFStrings.elem_BBForLoop()) {
	assert(n->size() == 1);
	OA::OA_ptr<OA::CFG::NodeStatementsIteratorInterface> stmtItPtr
	  = n->getNodeStatementsIterator();
	OA::StmtHandle loopStmt = stmtItPtr->current();
	WN* loopWN = (WN *)loopStmt.hval();

	WN* initWN = WN_start(loopWN);
	WN* updateWN = WN_step(loopWN);
      
	// FIXME: this is a terrible way of doing this, but the point is
	// to test correctness for now.
	OA::OA_ptr<OA::DGraph::NodesIteratorInterface> nodeIt1Ptr 
	  = cfg->getNodesIterator();
	for (; nodeIt1Ptr->isValid(); ++(*nodeIt1Ptr)) {
	  OA::OA_ptr<OA::DGraph::NodeInterface> dn1 = nodeIt1Ptr->current();
      OA::OA_ptr<OA::CFG::Node> n1 = dn1.convert<OA::CFG::Node>();
	  OA::OA_ptr<OA::CFG::NodeStatementsIteratorInterface> stmtIt1Ptr
	    = n1->getNodeStatementsIterator();
	  for (; stmtIt1Ptr->isValid(); ++(*stmtIt1Ptr)) {
	    OA::StmtHandle st = stmtIt1Ptr->current();
	    WN* wn = (WN*)st.hval();
	    if ((wn == initWN) || (wn == updateWN)) {
	      n1->erase(OA::StmtHandle((OA::irhandle_t)wn));
	      if (n1->size() == 0 && wn == updateWN) {
		toRemove.push_back(n1); // ONLY erase update 
	      }                         // [EndLoop] --> [update] --backedge-->
	      break;
	    }
	  }
	}
      }
    }

    // Remove empty basic blocks
    for (CFGNodeList::iterator it = toRemove.begin(); 
	 it != toRemove.end(); ++it) {
      OA::OA_ptr<OA::CFG::NodeInterface> n = *it;
    
      // Find predecessor node.  If more than one, we cannot continue
      if (n->num_incoming() > 1) {
	continue;
      } 
      OA::OA_ptr<OA::DGraph::NodesIteratorInterface> sourceItPtr
	= n->getSourceNodesIterator();
      OA::OA_ptr<OA::DGraph::NodeInterface> dpred = sourceItPtr->current();
      OA::OA_ptr<OA::CFG::Node> pred = dpred.convert<OA::CFG::Node>();
    
      // All outgoing edges of 'n' become outgoing edges of 'pred'
      OA::OA_ptr<OA::DGraph::EdgesIteratorInterface> outEdgeItPtr
	= n->getOutgoingEdgesIterator();
      for ( ; outEdgeItPtr->isValid(); ++(*outEdgeItPtr)) {
	OA::OA_ptr<OA::DGraph::EdgeInterface> de = outEdgeItPtr->current();
    OA::OA_ptr<OA::CFG::Edge> e = de.convert<OA::CFG::Edge>();
	OA::OA_ptr<OA::DGraph::NodeInterface> dsnk = e->getSink();
    OA::OA_ptr<OA::CFG::Node> snk = dsnk.convert<OA::CFG::Node>();
	cfg->connect(pred, snk, e->getType());
      }
   
      cfg->removeNode(n); // removes all outgoing and incoming edges
    }
    toRemove.clear();
  
  
    // -------------------------------------------------------
    // 3. Split basic blocks with EndLoop and EndBranch tags
    // -------------------------------------------------------
  
    // Notes:
    //  - EndBranch statments will be the first or second statment
    //   (switches) of a basic block; EndLoop at the end.
    //  - Some blocks will have to be split more than once, requiring an
    //    iterative algoritihm. E.g.
    //      EndBr
    //      Assignment
    //      EndLoop
  
    // uses 'workList'
    // uses 'toSplit'
    std::list<CFGNodeList::iterator> toRem;
  
    // a. Collect all BBs with more that one stmt into 'workList'
    nodeItTmp = cfg->getNodesIterator();
    for ( ; nodeItTmp->isValid(); ++(*nodeItTmp)) {
      OA::OA_ptr<OA::DGraph::NodeInterface> dn = nodeItTmp->current();
      OA::OA_ptr<OA::CFG::Node> n = dn.convert<OA::CFG::Node>(); 
      if ( (n->size() > 1) ) { 
	workList.push_back(n);
      }
    }
  
    // b. Iterate until 'workList' is empty (fixed-point is reached).  
    // Each node in the worklist is guaranteed to have more than one stmt.
    while (!workList.empty()) {
    
      for (CFGNodeList::iterator wnodeIt = workList.begin(); 
	   wnodeIt != workList.end(); ++wnodeIt) {
	OA::OA_ptr<OA::CFG::NodeInterface> ntmp = *wnodeIt;
	OA::OA_ptr<OA::CFG::Node> n 
	  = ntmp.convert<OA::CFG::Node>();
      
	// 1. Find split-point for this node.  If there is none, remove it
	// from 'workList'
      restart_loop:
      
	WN* bbSplitPointWN = NULL; // start of new basic block
	unsigned int stmtcount = 1;
	OA::OA_ptr<OA::CFG::NodeStatementsIteratorInterface> stmtIt
	  = n->getNodeStatementsIterator();
	for (; stmtIt->isValid(); ++(*stmtIt), ++stmtcount) {
	  OA::StmtHandle st = stmtIt->current();
	  WN* wn = (WN*)st.hval();
	
	  const char* vty = GetCFGControlFlowVertexType(wn);
	  if (vty == XAIFStrings.elem_BBEndBranch()) {
	    // If EndBranch is not the first stmt, move it to the
	    // beginning and restart the loop
	    if (stmtcount > 1) {
	      n->erase(OA::StmtHandle((OA::irhandle_t)wn));
	      n->add_front(OA::StmtHandle((OA::irhandle_t)wn));
	      goto restart_loop;
	    }
	    ++(*stmtIt); // advance iterator to find start of new basic block
	    assert(stmtIt->isValid());
	    bbSplitPointWN = (WN*)stmtIt->current().hval();
	    break;
	  }
	  else if (vty == XAIFStrings.elem_BBEndLoop()) {
	    bbSplitPointWN = wn;
	    break;
	  }
	}
      
	if (bbSplitPointWN) {
	  toSplit.push_back(make_pair(wnodeIt, bbSplitPointWN));
	} else {
	  toRem.push_back(wnodeIt);
	}
      }
        
      // 2. Split basic blocks
      for (MySplitList::iterator it = toSplit.begin(); 
	   it != toSplit.end(); ++it) {
	CFGNodeList::iterator wnodeIt = (*it).first;
	OA::OA_ptr<OA::CFG::NodeInterface> ntmp = *wnodeIt;
	OA::OA_ptr<OA::CFG::Node> n = 
	  ntmp.convert<OA::CFG::Node>();
	WN* startWN = (*it).second;
      
	OA::StmtHandle stmt((OA::irhandle_t)startWN);
	OA::OA_ptr<OA::CFG::Node> newblock = cfg->splitBlock(n, stmt);
	cfg->connect(n, newblock, OA::CFG::FALLTHROUGH_EDGE);
	//n->longdump(cfg);
	//newblock->longdump(cfg);

	// Remove BBs with less than 1 stmt; add others
	if (newblock->size() > 1) {
	  workList.push_back(newblock);
	}
	if ( !(n->size() > 1) ) {
	  toRem.push_back(wnodeIt);
	}
      }
      toSplit.clear();

      // 3. Remove nodes from 'workList'
      for (std::list<CFGNodeList::iterator>::iterator it = toRem.begin(); 
	   it != toRem.end(); ++it) {
	workList.erase(*it); // *it is type CFGNodeList::iterator
      }
      toRem.clear();
    }
  
  }

  // ***************************************************************************

  class CollectModVars_ST_TAB {
  public:
    CollectModVars_ST_TAB(std::map<std::string, ST*>* modSymNmMap_,
			  std::set<ST*>* modSymDup_)
      : modSymNmMap(modSymNmMap_), modSymDup(modSymDup_)
    { } 

    // A function object applied to every entry of a ST_TAB
    void operator()(UINT32 idx, ST* st) const 
    { 
      // If 'st' is from a module or a module variable...
      if (ST_is_in_module(st)) {
	// If 'st' is actually a module variable
	if (!ST_is_external(st)) {
	  modSymNmMap->insert(make_pair(std::string(ST_name(st)), st));
	} 
	else {
	  modSymDup->insert(st);
	}
      }
    }
  
  private:
    std::map<std::string, ST*>* modSymNmMap; // map of bona-fide modules symbols
    std::set<ST*>* modSymDup;                // 'duplicated' module symbols
  };

  // ***************************************************************************

  // GetCFGVertexType: A CFG vertex is either an Entry, Exit,
  // BasicBlock, or a special structured control flow vertex (e.g., Branch,
  // ForLoop, PreLoop, PostLoop).  The string returned is from
  // 'XAIFStrings' which means users can compare on pointer value
  // (instead of using strcmp()).
  //
  // Vertices are classified by the statements contained within.  Since
  // the classifications are mutually exclusive, a vertex should not
  // contain two statements that correspond to structured control flow.
  //
  // FIXME: we know that loop and if BBs should only have one node in
  // them. because of MassageOA...
  const char*
  GetCFGVertexType(OA::OA_ptr<OA::CFG::CFGInterface> cfg, 
		   OA::OA_ptr<OA::CFG::NodeInterface> n)
  {
    using namespace OA::CFG;

    // We know these are cheap so they can be recomputed each time we are called
    OA::OA_ptr<NodeInterface> entry = cfg->getEntry();
    OA::OA_ptr<NodeInterface> exit = cfg->getExit();
  
    if (n == entry) {
      return XAIFStrings.elem_BBEntry();
    } else if (n == exit) { 
      return XAIFStrings.elem_BBExit();
    }
  
    // FIXME: we do not need to iterate over all statements since
    // control flow statements contructs will be in their own xaif:BB.
    OA::OA_ptr<OA::CFG::NodeStatementsIteratorInterface> stmtIt
      = n->getNodeStatementsIterator();
    for (; stmtIt->isValid(); ++(*stmtIt)) {
      OA::StmtHandle st = stmtIt->current();
      WN* wstmt = (WN*)st.hval();
      const char* vty = GetCFGControlFlowVertexType(wstmt);
      if (vty) { 
	return vty; 
      }
    }
  
    return XAIFStrings.elem_BB(); // default, non-structured type
  }


  // GetCFGControlFlowVertexType: If the WHIRL statement corresponds to a
  // CFG *control flow* vertex, return that type.  Otherwise return NULL.
  // Returns strings from XAIFStrings.
  const char*
  GetCFGControlFlowVertexType(WN* wstmt)
  {
    OPERATOR opr = WN_operator(wstmt);
    switch (opr) {
    
      // In OA, loop nodes represent the *condition* (not the body).
      // For a DO_LOOP, it additionally represents the initialization
      // and update statements.
    case OPR_DO_LOOP: 
      return XAIFStrings.elem_BBForLoop();
    case OPR_DO_WHILE: 
      return XAIFStrings.elem_BBPostLoop();
    case OPR_WHILE_DO:
      return XAIFStrings.elem_BBPreLoop();

      // In OA, IF nodes represent the *condition* (not the body)
    case OPR_IF:
    case OPR_TRUEBR:   // unstructured
    case OPR_FALSEBR:  // unstructured
      return XAIFStrings.elem_BBBranch();
    case OPR_SWITCH:   // unstructured
    case OPR_COMPGOTO: // unstructured
      return XAIFStrings.elem_BBBranch();
    
      // Currently we use special comments to denote EndBranch and EndLoop
    case OPR_COMMENT: 
      {
	static const char* endbr = XAIFStrings.elem_BBEndBranch();
	static const char* endlp = XAIFStrings.elem_BBEndLoop();
	const char* com = Index_To_Str(WN_GetComment(wstmt));
	if (strcmp(com, endbr) == 0) {
	  return endbr;
	} else if (strcmp(com, endlp) == 0) {
	  return endlp;
	}
	// fall through
      }
    
    default: 
      break; // fall through
    }
  
    return NULL;
  }

  void 
  OAAnalInfo::collectGlobalSymbolActivityInfo(OA::OA_ptr<OA::Activity::InterActive> active,
					      OA::OA_ptr<OA::Alias::InterAliasMap> interAlias,
					      OA::OA_ptr<Open64IRInterface> irIF,
					      PU_Info* pu_forest) {
    // Collect module variables
    std::map<std::string, ST*> modSymNmMap; // map of bona-fide modules symbols
    std::set<ST*> modSymDup;                // 'duplicated' module symbols
    CollectModVars_ST_TAB collectModVars(&modSymNmMap, &modSymDup);
    For_all(St_Table, GLOBAL_SYMTAB, collectModVars);
    // For each 'duplicated' module variable that is active, make sure
    // the true module variable is activated.
    std::map<std::string, ST*>::iterator it = modSymNmMap.begin();
    // iterate through all global (module) variables
    for ( ; it != modSymNmMap.end(); ++it) {
      bool isActive=false;
      ST* st_p = (*it).second;

      // debug begin -----
      char* symbolName = ST_name(st_p);
      std::cout << "JU: OAAnalInfo::collectGlobalSymbolActivityInfo: for symbol name: " << symbolName << std::endl; 
      // debug end ----

      // make an memory reference expression from the given symbol
      OA::SymHandle sym = OA::SymHandle((OA::irhandle_t)st_p) ; 
      OA::OA_ptr<OA::MemRefExpr> symMRE = irIF->convertSymToMemRefExpr(sym);
      // iterate through all PUs
      OA::OA_ptr<Open64IRProcIterator> procIt;
      procIt = new Open64IRProcIterator(pu_forest);
      for ( ; procIt->isValid() && !isActive; ++(*procIt)) { 

	// debug begin -----
	ST* procST_p = ST_ptr(PU_Info_proc_sym((PU_Info*)procIt->current().hval()));
	const char* procName = ST_name(procST_p);
	std::cout << "JU: OAAnalInfo::collectGlobalSymbolActivityInfo: looking in: " << procName << " : "; 
	// debug end -----
	
	OA::OA_ptr<OA::LocIterator> symMRElocs_I = 
	  interAlias->getAliasResults(procIt->current())->getMayLocs(*symMRE,procIt->current());
	// we now have the locations that may alias the symbol and  need to compare these 
	// against the locations determined to be active by the activity analysis. 
	for ( ; symMRElocs_I->isValid() && !isActive; (*symMRElocs_I)++ ) {
	  OA::OA_ptr<OA::LocIterator> activeLoc_I = active->getActiveLocsIterator(procIt->current());
	  for ( ; activeLoc_I->isValid() && !isActive; (*activeLoc_I)++ ) {
	    if (activeLoc_I->current()->mayOverlap(*(symMRElocs_I->current()))) {
	      ourActiveGlobalSTPSet.insert(st_p);
	      isActive=true;
	      std::cout << " active "; 
	    }
	  }
	}
	std::cout << std::endl; 
      }
    }
  }

  bool 
  OAAnalInfo::isGlobalSymbolActive(ST* anST_p) {
    return (ourActiveGlobalSTPSet.find(anST_p)!=ourActiveGlobalSTPSet.end());
  } 

}
