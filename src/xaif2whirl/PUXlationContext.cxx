// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/PUXlationContext.cxx,v 1.2 2006/05/12 16:12:23 utke Exp $

#include <stdio.h>

#include "PUXlationContext.h"
#include "lib/support/SymTab.h"
#include "lib/support/diagnostics.h"

namespace xaif2whirl { 

  std::string PUXlationContext::ourPrefix;

  PUXlationContext::PUXlationContext(const std::string& anOriginator) : 
    myWNParentMapP(NULL), 
    mySymTabIdToSymTabMapP(NULL), 
    myPUIdToPUMapP(NULL), 
    myWNToWNIdMapP(NULL),
    myWNIdToWNMapP(NULL),
    myXAIFSymToSymbolMapP(NULL),
    myOriginator(anOriginator) {
    myXlationContextStack.push_front(XlationContext());
  }

  PUXlationContext::~PUXlationContext() {
    // clear the stack
    myXlationContextStack.clear(); 
  }

  void PUXlationContext::createXlationContext() {
    PushNewXlationContext(XlationContext::NOFLAG);
  }

  void PUXlationContext::createXlationContext(XlationContext::Flags_E f) {
    PushNewXlationContext(f);
  }

  void PUXlationContext::PushNewXlationContext(XlationContext::Flags_E f) {
    if (myXlationContextStack.empty()) 
      // this should never happen
      FORTTK_DIE("PUXlationContext::PushNewXlationContext: empty context stack");
    const XlationContext& parentXlationContext = myXlationContextStack.front();
    myXlationContextStack.push_front(XlationContext());
    currentXlationContext().inheritFlagsDown(parentXlationContext);
    currentXlationContext().setFlag(f);
  }

  void PUXlationContext::deleteXlationContext() {
    if (myXlationContextStack.size() > 1) {
      // maintain invariant that there is at least one context
      (++(myXlationContextStack.begin()))->inheritFlagsUp(*(myXlationContextStack.begin()));
      myXlationContextStack.pop_front();
    }
  }

  XlationContext& PUXlationContext::currentXlationContext() { 
    return myXlationContextStack.front(); 
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

  WhirlParentMap* PUXlationContext::getWNParentMap() const { 
    if (!myWNParentMapP)
      FORTTK_DIE("PUXlationContext::getWNParentMap: myWNParentMapP not set");
    return myWNParentMapP; 
  }

  void PUXlationContext::setWNParentMap(WhirlParentMap* aWhirlParentMapP) { 
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

  std::pair<ST_TAB*, PU_Info*>  PUXlationContext::findSymTab(SymTabId stabId) {
    if (!mySymTabIdToSymTabMapP)
      FORTTK_DIE("PUXlationContext::findSymTab: mySymTabIdToSymTabMapP not set");
    return (mySymTabIdToSymTabMapP->Find(stabId, true /*mustfind*/)); 
  }

  SymTabIdToSymTabMap* PUXlationContext::getSymTabIdToSymTabMap() const { 
    if (!mySymTabIdToSymTabMapP)
      FORTTK_DIE("PUXlationContext::getSymTabIdToSymTabMap: mySymTabIdToSymTabMapP not set");
    return mySymTabIdToSymTabMapP; 
  }

  void PUXlationContext::setSymTabIdToSymTabMap(SymTabIdToSymTabMap* aSymTabIdToSymTabMapP) { 
    if (!aSymTabIdToSymTabMapP)
      FORTTK_DIE("PUXlationContext::setSymTabIdToSymTabMap: null pointer passed");
    if (mySymTabIdToSymTabMapP)
      FORTTK_DIE("PUXlationContext::setSymTabIdToSymTabMap: already set");
    mySymTabIdToSymTabMapP = aSymTabIdToSymTabMapP; 
  }
  
  PU_Info* PUXlationContext::findPU(PUId aPUId) {
    if (!myPUIdToPUMapP)
      FORTTK_DIE("PUXlationContext::findPU: myPUIdToPUMapP not set");
    return (myPUIdToPUMapP->Find(aPUId));
  }

  PUIdToPUMap* PUXlationContext::getPUIdToPUMap() const { 
    if (!myPUIdToPUMapP)
      FORTTK_DIE("PUXlationContext::getPUToPUIdMap: myPUIdToPUMapP not set");
    return myPUIdToPUMapP; 
  }

  void PUXlationContext::setPUIdToPUMap(PUIdToPUMap* aPUIdToPUMapP) {
    if (!aPUIdToPUMapP)
      FORTTK_DIE("PUXlationContext::setPUIdToPUMap: null pointer passed");
    if (myPUIdToPUMapP)
      FORTTK_DIE("PUXlationContext::setPUIdToPUMap: already set");
    myPUIdToPUMapP = aPUIdToPUMapP; 
  }

  WNId PUXlationContext::findWNId(WN* aWNp) {
    if (!myWNToWNIdMapP)
      FORTTK_DIE("PUXlationContext::findWNId: myWNToWNIdMapP not set");
    if (!aWNp)
      FORTTK_DIE("PUXlationContext::findWNId: null pointer passed");
    return myWNToWNIdMapP->Find(aWNp);
  }

  WNToWNIdMap* PUXlationContext::getWNToWNIdMap() const { 
    if (!myWNToWNIdMapP)
      FORTTK_DIE("PUXlationContext::getWNToWNIdMap: myWNToWNIdMapP not set");
    return myWNToWNIdMapP; 
  }

  void PUXlationContext::setWNToWNIdMap(WNToWNIdMap* aWNToWNIdMapP) { 
    if (!aWNToWNIdMapP)
      FORTTK_DIE("PUXlationContext::setWNToWNIdMap: null pointer passed");
    // JU: this is being reset hmm
    if (myWNToWNIdMapP) {
      if (myWNToWNIdMapP==aWNToWNIdMapP) { 
	FORTTK_MSG(2,"PUXlationContext::setWNToWNIdMap: already set to the same");
      }
      else { 
	FORTTK_MSG(2,"PUXlationContext::setWNToWNIdMap: already set to " 
		   << myWNToWNIdMapP  
		   << " new " 
		   << aWNToWNIdMapP);
      }
    }
    myWNToWNIdMapP = aWNToWNIdMapP; 
  }

  WN* PUXlationContext::findWN(WNId aWNId, bool mustFind) {
    if (!myWNIdToWNMapP)
      FORTTK_DIE("PUXlationContext::findWN: myWNIdToWNMapP not set");
    return myWNIdToWNMapP->Find(aWNId,mustFind);
  }

  WNIdToWNMap* PUXlationContext::getWNIdToWNMap() const { 
    if (!myWNIdToWNMapP)
      FORTTK_DIE("PUXlationContext::getWNIdToWNMap: myWNIdToWNMapP not set");
    return myWNIdToWNMapP; 
  }

  void PUXlationContext::setWNIdToWNMap(WNIdToWNMap* aWNIdToWNMapP) { 
    if (!aWNIdToWNMapP)
      FORTTK_DIE("PUXlationContext::setWNIdToWNMap: null pointer passed");
    // JU: this is being reset hmm
    if (myWNIdToWNMapP) {
      if (myWNIdToWNMapP==aWNIdToWNMapP) { 
	FORTTK_MSG(2,"PUXlationContext::setWNIdToWNMap: already set to the same");
      }
      else { 
	FORTTK_MSG(2,"PUXlationContext::setWNIdToWNMap: already set to " 
		   << myWNIdToWNMapP  
		   << " new " 
		   << aWNIdToWNMapP);
      }
    }
    myWNIdToWNMapP = aWNIdToWNMapP; 
  }

  Symbol* PUXlationContext::findSym(const std::string& scopeid, 
				    const std::string& symid) { 
    if(!myXAIFSymToSymbolMapP)
      FORTTK_DIE("PUXlationContext::findSym: myXAIFSymToSymbolMapP not set");
    return (myXAIFSymToSymbolMapP->Find(scopeid.c_str(), symid.c_str())); 
  }
 
  XAIFSymToSymbolMap* PUXlationContext::getXAIFSymToSymbolMap() const { 
    if(!myXAIFSymToSymbolMapP)
      FORTTK_DIE("PUXlationContext::getXAIFSymToSymbolMap: myXAIFSymToSymbolMapP not set");
    return myXAIFSymToSymbolMapP;
  } 

  void PUXlationContext::setXAIFSymToSymbolMap(XAIFSymToSymbolMap* aXAIFSymToSymbolMapP) { 
    if (!aXAIFSymToSymbolMapP)
      FORTTK_DIE("PUXlationContext::setXAIFSymToSymbolMap: null pointer passed");
    if (myXAIFSymToSymbolMapP)
      FORTTK_DIE("PUXlationContext::setXAIFSymToSymbolMap: already set");
    myXAIFSymToSymbolMapP = aXAIFSymToSymbolMapP; 
  } 

  void PUXlationContext::setPrefix(const std::string& aPrefix) { 
    ourPrefix=aPrefix;
  }

  const std::string& PUXlationContext::getPrefix() {
    return ourPrefix;
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

}
