// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/PUXlationContext.cxx,v 1.2 2006/05/12 16:12:23 utke Exp $

#include <stdio.h>

#include "PUXlationContext.h"
#include "Open64IRInterface/SymTab.h"
#include "Diagnostics.h"
#include "whirl2xaif.h"

namespace whirl2xaif { 
  
  PUXlationContext::PUXlationContext(const std::string& anOriginator) : 
    myWNParentMapP(NULL), 
    myStab2idMapP(NULL), 
    myPU2idMapP(NULL), 
    myWN2idMapP(NULL),
    myScalarizedRefTab_W2Xp(NULL),
    myOriginator(anOriginator),
    myF90Flag(false) {
    myXlationContextStack.push_front(XlationContext(0));
  }

  PUXlationContext::~PUXlationContext() {
    // clear the stack
    myXlationContextStack.clear(); 
  }

  void PUXlationContext::createXlationContext() {
    PushNewXlationContext(XlationContext::NOFLAG, NULL);
  }

  void PUXlationContext::createXlationContext(XlationContext::Flags_E f) {
    PushNewXlationContext(f, NULL);
  }

  void PUXlationContext::createXlationContext(XlationContext::Flags_E f, WN* aWNp) {
    PushNewXlationContext(f, aWNp);
  }

  void PUXlationContext::PushNewXlationContext(XlationContext::Flags_E f, WN* aWNp) {
    if (myXlationContextStack.empty()) 
      // this should never happen
      FORTTK_DIE("PUXlationContext::PushNewXlationContext: empty context stack");
    const XlationContext& parentXlationContext = myXlationContextStack.front();
    myXlationContextStack.push_front(XlationContext(myXlationContextStack.size()));
    currentXlationContext().inheritFlags(parentXlationContext);
    if (aWNp)
      currentXlationContext().setWN(aWNp);
    currentXlationContext().setFlag(f);
  }

  void PUXlationContext::deleteXlationContext() {
    if (myXlationContextStack.size() > 1) {
      // maintain invariant that there is at least one context
      myXlationContextStack.pop_front();
    }
  }

  XlationContext& PUXlationContext::currentXlationContext() { 
    return myXlationContextStack.front(); 
  }

  WN* PUXlationContext::getMostRecentWN() {
    WN* theWNp=0;
    for (XlationContextStack::iterator it=myXlationContextStack.begin();
	 it!=myXlationContextStack.end();
	 ++it) {
      if (it->hasWN()) { 
	theWNp=it->getWN();
	break;
      }
    }
    if (!theWNp)
      FORTTK_DIE("PUXlationContext::getMostRecentWN: none found");
    return theWNp;
  }

  WN* PUXlationContext::findParentWN(WN* wn) {
    if (!myWNParentMapP)
      FORTTK_DIE("PUXlationContext::FindParentWN: myWNParentMapP not set");
    if(!wn)
      FORTTK_DIE("PUXlationContext::FindParentWN: null pointer passed");
    return (myWNParentMapP->Find(wn));
  }

  WN* PUXlationContext::findParentBlockWN(WN* wn) {
    if (!myWNParentMapP)
      FORTTK_DIE("PUXlationContext::FindParentBlockWN: myWNParentMapP not set");
    if(!wn)
      FORTTK_DIE("PUXlationContext::FindParentBlockWN: null pointer passed");
    return (myWNParentMapP->FindBlock(wn)); 
  }

  fortTkSupport::WhirlParentMap* PUXlationContext::getWNParentMap() const { 
    if (!myWNParentMapP)
      FORTTK_DIE("PUXlationContext::getWNParentMap: myWNParentMapP not set");
    return myWNParentMapP; 
  }

  void PUXlationContext::setWNParentMap(fortTkSupport::WhirlParentMap* aWhirlParentMapP) { 
    if (!aWhirlParentMapP)
      FORTTK_DIE("PUXlationContext::setWNParentMap: null pointer passed");
    // JU: this appears to be reset, HMMM
    if (myWNParentMapP) {
      if (myWNParentMapP==aWhirlParentMapP) { 
	FORTTK_MSG(2,"PUXlationContext::setWNParentMap: already set to the same");
      }
      else { 
	FORTTK_MSG(2,"PUXlationContext::setWNParentMap: already set to " 
		    << myWNParentMapP 
		    << " new " 
		    << aWhirlParentMapP);
      }
    }
    myWNParentMapP = aWhirlParentMapP; 
  }

 fortTkSupport::SymTabId PUXlationContext::findSymTabId(ST_TAB* stab) {
    if (!myStab2idMapP)
      FORTTK_DIE("PUXlationContext::findSymTabId: myStab2idMapP not set");
    if (!stab)
      FORTTK_DIE("PUXlationContext::findSymTabId: null pointer passed");
    return (myStab2idMapP->Find(stab, true /*mustfind*/)); 
  }

  fortTkSupport::SymTabToSymTabIdMap* PUXlationContext::getSymTabToIdMap() const { 
    if (!myStab2idMapP)
      FORTTK_DIE("PUXlationContext::getSymTabToIdMap: myStab2idMapP not set");
    return myStab2idMapP; 
  }

  void PUXlationContext::setSymTabToIdMap(fortTkSupport::SymTabToSymTabIdMap* aSymTabToSymTabIdMapP) { 
    if (!aSymTabToSymTabIdMapP)
      FORTTK_DIE("PUXlationContext::setSymTabToIdMap: null pointer passed");
    if (myStab2idMapP)
      FORTTK_DIE("PUXlationContext::setSymTabToIdMap: already set");
    myStab2idMapP = aSymTabToSymTabIdMapP; 
  }
  
  fortTkSupport::PUId PUXlationContext::findPUId(PU_Info* pu) {
    if (!myPU2idMapP)
      FORTTK_DIE("PUXlationContext::findPUId: myPU2idMapP not set");
    if (!pu)
      FORTTK_DIE("PUXlationContext::findPUId: null pointer passed");
    return (myPU2idMapP->Find(pu));
  }

  fortTkSupport::PUToPUIdMap* PUXlationContext::getPUToIdMap() const { 
    if (!myPU2idMapP)
      FORTTK_DIE("PUXlationContext::getPUToIdMap: myPU2idMapP not set");
    return myPU2idMapP; 
  }

  void PUXlationContext::setPUToIdMap(fortTkSupport::PUToPUIdMap* aPUToPUIdMapP) {
    if (!aPUToPUIdMapP)
      FORTTK_DIE("PUXlationContext::setPUToIdMap: null pointer passed");
    if (myPU2idMapP)
      FORTTK_DIE("PUXlationContext::setPUToIdMap: already set");
    myPU2idMapP = aPUToPUIdMapP; 
  }

  fortTkSupport::WNId PUXlationContext::findWNId(WN* wn) {
    if (!myWN2idMapP)
      FORTTK_DIE("PUXlationContext::findWNId: myWN2idMapP not set");
    if (!wn)
      FORTTK_DIE("PUXlationContext::findWNId: null pointer passed");
    return myWN2idMapP->Find(wn);
  }

  fortTkSupport::WNToWNIdMap* PUXlationContext::getWNToIdMap() const { 
    if (!myWN2idMapP)
      FORTTK_DIE("PUXlationContext::getWNToIdMap: myWN2idMapP not set");
    return myWN2idMapP; 
  }

  void PUXlationContext::setWNToIdMap(fortTkSupport::WNToWNIdMap* aWNToWNIdMapP) { 
    if (!aWNToWNIdMapP)
      FORTTK_DIE("PUXlationContext::setWNToIdMap: null pointer passed");
    // JU: this is being reset hmm
    if (myWN2idMapP) { 
      if (myWN2idMapP==aWNToWNIdMapP) { 
	FORTTK_MSG(2,"PUXlationContext::setWNToIdMap: already set to the same");
      }
      else { 
	FORTTK_MSG(2,"PUXlationContext::setWNToIdMap: already set to " 
		    << myWN2idMapP  
		    << " new " 
		    << aWNToWNIdMapP);
      }
    }
    myWN2idMapP = aWNToWNIdMapP; 
  }

  int PUXlationContext::findUDDUChainId(WN* wnexpr) {
    if (myUdduchains.ptrEqual(NULL)) 
      FORTTK_DIE("PUXlationContext::findUDDUChainId: myUdduchains not set");
    if (!wnexpr) 
      FORTTK_DIE("PUXlationContext::findUDDUChainId: null pointer passed");
    OA::MemRefHandle h((OA::irhandle_t)wnexpr);
    return myUdduchains->getUDDUChainId(h);
  }

  OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> PUXlationContext::getUDDUChains() const { 
    if (myUdduchains.ptrEqual(NULL)) 
      FORTTK_DIE("PUXlationContext::getUDDUChains: myUdduchains not set");
    return myUdduchains; 
  }

  void PUXlationContext::setUDDUChains(OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> aUdduchainsMap) { 
    if (aUdduchainsMap.ptrEqual(NULL)) 
      FORTTK_DIE("PUXlationContext::setUDDUChains: uninitialized OA pointer passed");
    // JU: this is being reset hmm
    if (!myUdduchains.ptrEqual(NULL)) {
      if (myUdduchains.ptrEqual(aUdduchainsMap)) { 
	FORTTK_MSG(2,"PUXlationContext::setUDDUChains: already set to the same");
      }
      else { 
	FORTTK_MSG(2,"PUXlationContext::setUDDUChains: already set to "
		    << myUdduchains 
		    << " new " 
		    << aUdduchainsMap);
      }
    }
    myUdduchains = aUdduchainsMap; 
  }

  fortTkSupport::ScalarizedRef* PUXlationContext::findScalarizedRef(WN* wn) {
    if (!myScalarizedRefTab_W2Xp)
      FORTTK_DIE("PUXlationContext::findScalarizedRef: myScalarizedRefTab_W2Xp not set");
    if (!wn)
      FORTTK_DIE("PUXlationContext::findScalarizedRef: null pointer passed");
    return myScalarizedRefTab_W2Xp->Find(wn);
  }

  void PUXlationContext::setScalarizedRefTab(fortTkSupport::ScalarizedRefTab_W2X* aScalarizedRefTab_W2Xp) { 
    if (!aScalarizedRefTab_W2Xp)
      FORTTK_DIE("PUXlationContext::setScalarizedRefTab: null pointer passed");
    // JU: this is being reset hmm
    if (myScalarizedRefTab_W2Xp) { 
      if (myScalarizedRefTab_W2Xp==aScalarizedRefTab_W2Xp) { 
	FORTTK_MSG(2,"PUXlationContext::setScalarizedRefTab: already set to the same");
      }
      else { 
	FORTTK_MSG(2,"PUXlationContext::setScalarizedRefTab: already set to "
		    << myScalarizedRefTab_W2Xp
		    << " new " 
		    << aScalarizedRefTab_W2Xp);
      }
    }
    myScalarizedRefTab_W2Xp = aScalarizedRefTab_W2Xp; 
  }

  fortTkSupport::ScalarizedRefTab_W2X* PUXlationContext::getScalarizedRefTab() const { 
    if (!myScalarizedRefTab_W2Xp)
      FORTTK_DIE("PUXlationContext::getScalarizedRefTab: not set");
    return myScalarizedRefTab_W2Xp; 
  }

  int PUXlationContext::isActiveSym(ST* st) { 
    if(myActivity.ptrEqual(NULL))
      FORTTK_DIE("PUXlationContext::IsActiveSym: myActivity not set");
    if (!st)
      FORTTK_DIE("PUXlationContext::IsActiveSym: null pointer passed");
    // see if this is a module variable
    if (ST_is_in_module(st) && !ST_is_external(st)) { 
      // try to find it in the global set
      if (fortTkSupport::OAAnalInfo::isGlobalSymbolActive(st))
	return true; 
      // else look in the local information
    }
    OA::SymHandle sym = OA::SymHandle((OA::irhandle_t)st) ; 
    OA::OA_ptr<Open64IRInterface> theIR=Whirl2Xaif::getOAAnalMap().GetIRInterface();
    OA::OA_ptr<OA::MemRefExpr> symMRE = theIR->convertSymToMemRefExpr(sym);
    OA::ProcHandle proc((OA::irhandle_t)Current_PU_Info);
    OA::OA_ptr<OA::LocIterator> symMRElocs_I = myAlias->getAliasResults(proc)->getMayLocs(*symMRE,proc);
    // we now have the locations that may alias the symbol and  need to compare these 
    // against the locations determined to be active by the activity analysis. 
    for ( ; symMRElocs_I->isValid(); (*symMRElocs_I)++ ) {
      OA::OA_ptr<OA::LocIterator> activeLoc_I = myActivity->getActiveLocsIterator(proc);
      for ( ; activeLoc_I->isValid(); (*activeLoc_I)++ ) {
	if (activeLoc_I->current()->mayOverlap(*(symMRElocs_I->current()))) {
	  return true;
	}
      }
    }
    // didn't find it in all the active locations
    return false;
  }

  int PUXlationContext::isActiveStmt(PU_Info* pu, WN* wn) { 
    if(myActivity.ptrEqual(NULL))
      FORTTK_DIE("PUXlationContext::IsActiveStmt: myActivity not set");
    if (!pu || !wn)
      FORTTK_DIE("PUXlationContext::IsActiveStmt: null pointer passed");
    return myActivity->isActive(OA::ProcHandle((OA::irhandle_t)pu),
				OA::StmtHandle((OA::irhandle_t)wn)); 
  }

  int PUXlationContext::isActiveVarRef(PU_Info* pu, WN* wn) { 
    if(myActivity.ptrEqual(NULL))
      FORTTK_DIE("PUXlationContext::IsActiveVarRef: myActivity not set");
    if (!pu || !wn)
      FORTTK_DIE("PUXlationContext::IsActiveVarRef: null pointer passed");
    return myActivity->isActive(OA::ProcHandle((OA::irhandle_t)pu),
				OA::MemRefHandle((OA::irhandle_t)wn)); 
  }

  void PUXlationContext::setActivity(OA::OA_ptr<OA::Activity::InterActive> anActivityMap) { 
    if(anActivityMap.ptrEqual(NULL))
      FORTTK_DIE("PUXlationContext::SetActivity: null OA_ptr passed");
    if(!myActivity.ptrEqual(NULL))
      FORTTK_DIE("PUXlationContext::SetActivity: already set");
    myActivity = anActivityMap; 
  }

  void PUXlationContext::setAlias(OA::OA_ptr<OA::Alias::InterAliasMap> anAliasMap) { 
    if(anAliasMap.ptrEqual(NULL))
      FORTTK_DIE("PUXlationContext::SetAlias: null OA_ptr passed");
    if(!myAlias.ptrEqual(NULL))
      FORTTK_DIE("PUXlationContext::SetAlias: already set");
    myAlias = anAliasMap; 
  }

  void PUXlationContext::dump(std::ostream& o, const std::string& indent) const {
    o << "(myOriginator=" << myOriginator.c_str() << " ";
    o << ")\n";
    for (XlationContextStack::const_iterator it=myXlationContextStack.begin();
	 it!=myXlationContextStack.end();
	 ++it) 
      it->dump(o,indent+"  ");
  }

  void PUXlationContext::ddump() const {
    dump(std::cerr,"");
  }
  
  bool PUXlationContext::isF90() const { 
    return myF90Flag;
  }

  void PUXlationContext::setF90(bool aFlag) { 
    myF90Flag=aFlag;
  }

}
