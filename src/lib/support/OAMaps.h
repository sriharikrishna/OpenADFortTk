// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/OAMaps.h,v 1.4 2005/08/15 20:17:25 utke Exp $

#ifndef OAMaps_INCLUDED_h
#define OAMaps_INCLUDED_h

#include <iostream>

#include "Open64IRInterface/Open64BasicTypes.h"

//************************ OpenAnalysis Include Files ***********************

#include <OpenAnalysis/CallGraph/ManagerCallGraph.hpp>

#include <OpenAnalysis/CallGraph/CallGraph.hpp>
#include <OpenAnalysis/CallGraph/CallGraphInterface.hpp>
#include <OpenAnalysis/CFG/ManagerCFG.hpp>
#include <OpenAnalysis/CFG/EachCFGStandard.hpp>
#include <OpenAnalysis/Alias/ManagerAliasMapBasic.hpp>
#include <OpenAnalysis/Alias/ManagerInterAliasMapBasic.hpp>
// #include <OpenAnalysis/Alias/ManagerNoAddressOf.hpp>
// replacing the above with:
#include <OpenAnalysis/Alias/ManagerFIAliasAliasMap.hpp>

#include <OpenAnalysis/ReachDefs/ManagerReachDefsStandard.hpp>
#include <OpenAnalysis/SideEffect/ManagerSideEffectStandard.hpp>
#include <OpenAnalysis/SideEffect/InterSideEffectStandard.hpp>
#include <OpenAnalysis/SideEffect/ManagerInterSideEffectStandard.hpp>
//#include <OpenAnalysis/ReachConsts/ManagerReachConstsStandard.hpp>
#include <OpenAnalysis/UDDUChains/ManagerUDDUChainsStandard.hpp>
#include <OpenAnalysis/Activity/ManagerActiveStandard.hpp>
#include <OpenAnalysis/Activity/ManagerICFGActive.hpp>
#include <OpenAnalysis/XAIF/UDDUChainsXAIF.hpp>
#include <OpenAnalysis/XAIF/ManagerUDDUChainsXAIF.hpp>
#include <OpenAnalysis/XAIF/ManagerAliasMapXAIF.hpp>
#include <OpenAnalysis/DataFlow/ManagerParamBindings.hpp>
  // #include <OpenAnalysis/Alias/ManagerSymAliasSetsBottom.hpp>
  // #include <OpenAnalysis/Alias/ManagerInsNoPtrInterAliasMap.hpp>
#include <OpenAnalysis/ICFG/ManagerICFG.hpp>


//*************************** User Include Files ****************************

#include "Open64IRInterface/Open64IRInterface.hpp"

#include "BaseMap.h"
#include "Diagnostics.h"

namespace fortTkSupport {

//************************** Forward Declarations ***************************

typedef std::list<OA::OA_ptr<OA::CFG::NodeInterface> > CFGNodeList;
typedef std::list<OA::OA_ptr<OA::DGraph::NodeInterface> > DGraphNodeList;

const char*
GetCFGVertexType(OA::OA_ptr<OA::CFG::CFGInterface> cfg, 
                 OA::OA_ptr<OA::CFG::NodeInterface> n);

const char*
GetCFGControlFlowVertexType(WN* wstmt);

//***************************************************************************

//***************************************************************************
// PU <-> OAAnalInfo maps (global/interprocedural)
//***************************************************************************

class OAAnalInfo;

class PUToOAAnalInfoMap 
  : public fortTkSupport::BaseMap<PU_Info*, OAAnalInfo*>
{
public:  
  PUToOAAnalInfoMap() { }
  PUToOAAnalInfoMap(PU_Info* pu_forest) { Create(pu_forest); }
  virtual ~PUToOAAnalInfoMap() { }

  void Create(PU_Info* pu_forest);

  // IRInterface
  OA::OA_ptr<Open64IRInterface> GetIRInterface() { return irIF; }
  void SetIRInterface(OA::OA_ptr<Open64IRInterface> x) { irIF = x; }

  // CallGraph  
  OA::OA_ptr<OA::CallGraph::CallGraph> GetCallGraph() 
    { return cgraph; }
  void SetCallGraph(OA::OA_ptr<OA::CallGraph::ManagerCallGraphStandard> m, 
		    OA::OA_ptr<OA::CallGraph::CallGraph> x) 
    { cgraphman = m; cgraph = x; }

  // Each CFG 'manager'
  OA::OA_ptr<OA::CFG::EachCFGInterface> GetCFGEach() 
    { return cfgeach; }
  void SetCFGEach(OA::OA_ptr<OA::CFG::ManagerCFGStandard> m, 
		  OA::OA_ptr<OA::CFG::EachCFGInterface> x) 
    { cfgman = m; cfgeach = x; }

  // Parameter Bindings
  OA::OA_ptr<OA::DataFlow::ParamBindings> GetParamBindings() { 
    return paramBindings; 
  }
  void SetParamBind(OA::OA_ptr<OA::DataFlow::ManagerParamBindings> m, 
		     OA::OA_ptr<OA::DataFlow::ParamBindings> x) { 
    paramBindingsman = m; 
    paramBindings = x; 
  }
  
  OA::OA_ptr<OA::Alias::InterAliasMap> GetInterAlias() { return interAlias; }
  void SetInterAlias(OA::OA_ptr<OA::Alias::ManagerFIAliasAliasMap> m, 
		     OA::OA_ptr<OA::Alias::InterAliasMap> x) 
    { interaliasmapman = m; interAlias = x; }

  // Inter Side Effect  
  void SetSideEffect(OA::OA_ptr<OA::SideEffect::ManagerSideEffectStandard> m) 
    { sideeffectman = m; }
  
  OA::OA_ptr<OA::SideEffect::InterSideEffectStandard> GetInterSideEffect()
    { return interSE; }
  void SetInterSideEffect(OA::OA_ptr<OA::SideEffect::ManagerInterSideEffectStandard> m,
			  OA::OA_ptr<OA::SideEffect::InterSideEffectStandard> x) 
    { interSEman = m; interSE = x; }

  // Activity
  OA::OA_ptr<OA::Activity::InterActive> GetInterActive() { return active; }
  void SetInterActive(OA::OA_ptr<OA::Activity::ManagerICFGActive> m,
		      OA::OA_ptr<OA::Activity::InterActive> x) 
    { activeman = m; active = x; }

private:
  OA::OA_ptr<Open64IRInterface> irIF;
  
  OA::OA_ptr<OA::CallGraph::ManagerCallGraphStandard> cgraphman;
  OA::OA_ptr<OA::CallGraph::CallGraph> cgraph;
  
  OA::OA_ptr<OA::CFG::ManagerCFGStandard> cfgman;
  OA::OA_ptr<OA::CFG::EachCFGInterface> cfgeach;
  
  OA::OA_ptr<OA::Alias::ManagerFIAliasAliasMap> interaliasmapman;
  OA::OA_ptr<OA::Alias::InterAliasMap> interAlias;

  OA::OA_ptr<OA::SideEffect::ManagerSideEffectStandard> sideeffectman;

  OA::OA_ptr<OA::DataFlow::ParamBindings> paramBindings;
  OA::OA_ptr<OA::DataFlow::ManagerParamBindings> paramBindingsman;
  
  OA::OA_ptr<OA::SideEffect::ManagerInterSideEffectStandard> interSEman;
  OA::OA_ptr<OA::SideEffect::InterSideEffectStandard> interSE;
  
  OA::OA_ptr<OA::Activity::ManagerICFGActive> activeman;
  OA::OA_ptr<OA::Activity::InterActive> active;  
};


//***************************************************************************
// OAAnalInfo
//***************************************************************************

// OAAnalInfo: OpenAnalysis Analyses info
class OAAnalInfo
{
public:
  OAAnalInfo() { }
  OAAnalInfo(PU_Info* pu, PUToOAAnalInfoMap* interInfo) 
    { Create(pu, interInfo); }
  ~OAAnalInfo();
  
  void Create(PU_Info* pu, PUToOAAnalInfoMap* interInfo);

  // Intra Alias
  OA::OA_ptr<OA::Alias::Interface> GetAlias() { return alias; }
  /*! commented out by PLM 09/13/06
  void SetAlias(OA::OA_ptr<OA::Alias::ManagerAliasMapBasic> m, 
                OA::OA_ptr<OA::Alias::AliasMap> x)
    { aliasman = m; alias = x; }
    */
 void SetAlias(OA::OA_ptr<OA::Alias::ManagerFIAliasAliasMap> m,
                OA::OA_ptr<OA::Alias::Interface> x)
    { aliasman = m; alias = x; }


  
  // ReachDefs
  OA::OA_ptr<OA::ReachDefs::ReachDefsStandard> GetReachDefs() { return rds; }
  void SetReachDefs(OA::OA_ptr<OA::ReachDefs::ManagerReachDefsStandard> m,
		            OA::OA_ptr<OA::ReachDefs::ReachDefsStandard> x) 
    { rdsman = m; rds = x; }
  
  // UDDU chains
  OA::OA_ptr<OA::UDDUChains::UDDUChainsStandard> GetUDDUChains() 
      { return udduchains; }
  void SetUDDUChains(OA::OA_ptr<OA::UDDUChains::ManagerUDDUChainsStandard> m,
                     OA::OA_ptr<OA::UDDUChains::UDDUChainsStandard> x) 
    { udman = m; udduchains = x; }
  
    
  // XAIF
  OA::OA_ptr<OA::XAIF::AliasMapXAIF> GetAliasXAIF() { return aliasXAIF; }
  void SetAliasXAIF(OA::OA_ptr<OA::XAIF::ManagerAliasMapXAIF> m,
		    OA::OA_ptr<OA::XAIF::AliasMapXAIF> x)
    { aliasmanXAIF = m; aliasXAIF = x; }
  
  OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> GetUDDUChainsXAIF() 
    { return udduchainsXAIF; }
  void SetUDDUChainsXAIF(OA::OA_ptr<OA::XAIF::ManagerStandard> m,
			 OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> x) 
    { udmanXAIF = m; udduchainsXAIF = x; }
  
  static bool isGlobalSymbolActive(ST* anST_p);


  static void collectGlobalSymbolActivityInfo(OA::OA_ptr<OA::Activity::InterActive> active,
					      OA::OA_ptr<OA::Alias::InterAliasMap> interAlias,
					      OA::OA_ptr<Open64IRInterface> irIF,
					      PU_Info* pu_forest); 

private:

  OA::OA_ptr<OA::Alias::ManagerFIAliasAliasMap> aliasman;
  OA::OA_ptr<OA::Alias::Interface> alias;
  
  OA::OA_ptr<OA::SideEffect::InterSideEffectInterface> sideEffect;
    
  OA::OA_ptr<OA::ReachDefs::ManagerReachDefsStandard> rdsman;
  OA::OA_ptr<OA::ReachDefs::ReachDefsStandard> rds;
  
  OA::OA_ptr<OA::UDDUChains::ManagerUDDUChainsStandard> udman;
  OA::OA_ptr<OA::UDDUChains::UDDUChainsStandard> udduchains;
  
  
  OA::OA_ptr<OA::XAIF::ManagerAliasMapXAIF> aliasmanXAIF;
  OA::OA_ptr<OA::XAIF::AliasMapXAIF> aliasXAIF;

  OA::OA_ptr<OA::XAIF::ManagerStandard> udmanXAIF;
  OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> udduchainsXAIF;

  static std::set<ST*> ourActiveGlobalSTPSet;

};

//***************************************************************************

}

#endif 
