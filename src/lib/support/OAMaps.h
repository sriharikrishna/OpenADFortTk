// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/OAMaps.h,v 1.4 2005/08/15 20:17:25 utke Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/OAMaps.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef OAMaps_INCLUDED_h
#define OAMaps_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//************************ OpenAnalysis Include Files ***********************

#include <OpenAnalysis/CallGraph/ManagerCallGraphStandard.hpp>
#include <OpenAnalysis/CFG/ManagerCFGStandard.hpp>
#include <OpenAnalysis/CFG/EachCFGStandard.hpp>
#include <OpenAnalysis/Alias/ManagerAliasMapBasic.hpp>
#include <OpenAnalysis/Alias/ManagerInterAliasMapBasic.hpp>
#include <OpenAnalysis/Alias/ManagerNoAddressOf.hpp>
#include <OpenAnalysis/ReachDefs/ManagerReachDefsStandard.hpp>
#include <OpenAnalysis/SideEffect/ManagerSideEffectStandard.hpp>
#include <OpenAnalysis/SideEffect/InterSideEffectStandard.hpp>
#include <OpenAnalysis/SideEffect/ManagerInterSideEffectStandard.hpp>
#include <OpenAnalysis/ReachConsts/ManagerReachConstsStandard.hpp>
#include <OpenAnalysis/UDDUChains/ManagerUDDUChainsStandard.hpp>
#include <OpenAnalysis/Activity/ManagerActiveStandard.hpp>
#include <OpenAnalysis/Activity/ManagerICFGActive.hpp>
#include <OpenAnalysis/XAIF/UDDUChainsXAIF.hpp>
#include <OpenAnalysis/XAIF/ManagerUDDUChainsXAIF.hpp>
#include <OpenAnalysis/XAIF/ManagerAliasMapXAIF.hpp>
#include <OpenAnalysis/DataFlow/ManagerParamBindings.hpp>
#include <OpenAnalysis/Alias/ManagerSymAliasSetsBottom.hpp>
#include <OpenAnalysis/Alias/ManagerInsNoPtrInterAliasMap.hpp>
#include <OpenAnalysis/ICFG/ManagerICFGStandard.hpp>
#include <OpenAnalysis/DUG/ManagerDUGStandard.hpp>
#include <OpenAnalysis/duaa/ManagerDUActive.hpp>


//*************************** User Include Files ****************************

#include "Open64IRInterface.hpp"

#include "BaseMap.h"
#include "diagnostics.h"

//************************** Forward Declarations ***************************

typedef std::list<OA::OA_ptr<OA::CFG::Interface::Node> > CFGNodeList;
typedef std::list<OA::OA_ptr<OA::DGraph::Interface::Node> > DGraphNodeList;

const char*
GetCFGVertexType(OA::OA_ptr<OA::CFG::Interface> cfg, 
                 OA::OA_ptr<OA::CFG::Interface::Node> n);

const char*
GetCFGControlFlowVertexType(WN* wstmt);

//***************************************************************************

//***************************************************************************
// PU <-> OAAnalInfo maps (global/interprocedural)
//***************************************************************************

class OAAnalInfo;

class PUToOAAnalInfoMap 
  : public FortTk::BaseMap<PU_Info*, OAAnalInfo*>
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
  OA::OA_ptr<OA::CallGraph::CallGraphStandard> GetCallGraph() 
    { return cgraph; }
  void SetCallGraph(OA::OA_ptr<OA::CallGraph::ManagerStandard> m, 
		    OA::OA_ptr<OA::CallGraph::CallGraphStandard> x) 
    { cgraphman = m; cgraph = x; }

  // Each CFG 'manager'
  OA::OA_ptr<OA::CFG::EachCFGInterface> GetCFGEach() 
    { return cfgeach; }
  void SetCFGEach(OA::OA_ptr<OA::CFG::ManagerStandard> m, 
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
  
  // Inter Alias
  OA::OA_ptr<OA::Alias::ManagerInsNoPtrInterAliasMap> GetInterAlias()
    { return interaliasmapman; }
  void SetInterAlias(OA::OA_ptr<OA::Alias::ManagerInsNoPtrInterAliasMap> m, 
		     OA::OA_ptr<OA::Alias::InterAliasMap> x) 
    { interaliasmapman = m; interAlias = x; }

  // Inter Side Effect  
  void SetSideEffect(OA::OA_ptr<OA::SideEffect::ManagerStandard> m) 
    { sideeffectman = m; }
  
  OA::OA_ptr<OA::SideEffect::InterSideEffectStandard> GetInterSideEffect()
    { return interSE; }
  void SetInterSideEffect(OA::OA_ptr<OA::SideEffect::ManagerInterSideEffectStandard> m,
			  OA::OA_ptr<OA::SideEffect::InterSideEffectStandard> x) 
    { interSEman = m; interSE = x; }

  // Activity
  OA::OA_ptr<OA::Activity::InterActive> GetInterActive() { return active; }
  void SetInterActive(OA::OA_ptr<OA::Activity::ManagerDUActive> m,
		      OA::OA_ptr<OA::Activity::InterActive> x) 
    { activeman = m; active = x; }

private:
  OA::OA_ptr<Open64IRInterface> irIF;
  
  OA::OA_ptr<OA::CallGraph::ManagerStandard> cgraphman;
  OA::OA_ptr<OA::CallGraph::CallGraphStandard> cgraph;
  
  OA::OA_ptr<OA::CFG::ManagerStandard> cfgman;
  OA::OA_ptr<OA::CFG::EachCFGInterface> cfgeach;
  
  OA::OA_ptr<OA::Alias::ManagerInsNoPtrInterAliasMap> interaliasmapman;
  OA::OA_ptr<OA::Alias::InterAliasMap> interAlias;

  OA::OA_ptr<OA::SideEffect::ManagerStandard> sideeffectman;

  OA::OA_ptr<OA::DataFlow::ParamBindings> paramBindings;
  OA::OA_ptr<OA::DataFlow::ManagerParamBindings> paramBindingsman;
  
  OA::OA_ptr<OA::SideEffect::ManagerInterSideEffectStandard> interSEman;
  OA::OA_ptr<OA::SideEffect::InterSideEffectStandard> interSE;
  
  OA::OA_ptr<OA::Activity::ManagerDUActive> activeman;
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
  OA::OA_ptr<OA::Alias::AliasMap> GetAlias() { return alias; }
  void SetAlias(OA::OA_ptr<OA::Alias::ManagerAliasMapBasic> m, 
                OA::OA_ptr<OA::Alias::AliasMap> x)
    { aliasman = m; alias = x; }
  
  // ReachDefs
  OA::OA_ptr<OA::ReachDefs::ReachDefsStandard> GetReachDefs() { return rds; }
  void SetReachDefs(OA::OA_ptr<OA::ReachDefs::ManagerStandard> m,
		            OA::OA_ptr<OA::ReachDefs::ReachDefsStandard> x) 
    { rdsman = m; rds = x; }
  
  // UDDU chains
  OA::OA_ptr<OA::UDDUChains::UDDUChainsStandard> GetUDDUChains() 
      { return udduchains; }
  void SetUDDUChains(OA::OA_ptr<OA::UDDUChains::ManagerStandard> m,
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
  
private:
  OA::OA_ptr<OA::Alias::ManagerAliasMapBasic> aliasman;
  OA::OA_ptr<OA::Alias::AliasMap> alias;
  
  OA::OA_ptr<OA::SideEffect::InterSideEffectInterface> sideEffect;
    
  OA::OA_ptr<OA::ReachDefs::ManagerStandard> rdsman;
  OA::OA_ptr<OA::ReachDefs::ReachDefsStandard> rds;
  
  OA::OA_ptr<OA::UDDUChains::ManagerStandard> udman;
  OA::OA_ptr<OA::UDDUChains::UDDUChainsStandard> udduchains;
  
  
  OA::OA_ptr<OA::XAIF::ManagerAliasMapXAIF> aliasmanXAIF;
  OA::OA_ptr<OA::XAIF::AliasMapXAIF> aliasXAIF;

  OA::OA_ptr<OA::XAIF::ManagerStandard> udmanXAIF;
  OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> udduchainsXAIF;
};

//***************************************************************************

#endif /* OAMaps_INLUCDED_h */
