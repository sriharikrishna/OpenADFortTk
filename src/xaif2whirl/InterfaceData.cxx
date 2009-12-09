#include "InterfaceData.h"
#include "Diagnostics.h"
#include "Open64IRInterface/WhirlGlobalStateUtils.h"

InterfaceData::PuIFaceRenamePairListPairListPairList InterfaceData::ourInterfacesByModule;

void InterfaceData::collect(PU_Info* aPUForrest_p) { 
  if (!aPUForrest_p) { return; }
  // Loop through all the PU_Infos 
  PU_Info* aPUInfoTree_p;
  for (aPUInfoTree_p=aPUForrest_p; aPUInfoTree_p!= NULL; aPUInfoTree_p=PU_Info_next(aPUInfoTree_p)) {
    forPUInfoTree(aPUInfoTree_p);
  }
} 

void InterfaceData::forPUInfoTree(PU_Info* aPUInfoTree_p) { 
  if (!aPUInfoTree_p) { return; }
  forPUInfo(aPUInfoTree_p);
  for (PU_Info *aPUInfosubtree_p = PU_Info_child(aPUInfoTree_p); 
       aPUInfosubtree_p != NULL; 
       aPUInfosubtree_p = PU_Info_next(aPUInfosubtree_p)) {
    forPUInfoTree(aPUInfosubtree_p);
  }
}

InterfaceData::PuIFaceRenamePairListPairListPair* 
InterfaceData::findModuleData(PU_Info* thePU_WN_p) { 
  for(PuIFaceRenamePairListPairListPairList::iterator it=ourInterfacesByModule.begin(); 
      it!=ourInterfacesByModule.end();
      ++it) { 
    if (WN_st_idx(PU_Info_tree_ptr(thePU_WN_p))==WN_st_idx(PU_Info_tree_ptr((*it).first))) { 
      return &(*it);
    }
  }
  return NULL; 
}

InterfaceData::IFaceRenamePairListPair* 
InterfaceData::findInterfaceData(PuIFaceRenamePairListPairListPair* moduleData, 
				 WN* theInterface_WN_p) { 
  for(IFaceRenamePairListPairList::iterator it=moduleData->second.begin(); 
      it!=moduleData->second.end();
      ++it) { 
    if (WN_st_idx(theInterface_WN_p)==WN_st_idx((*it).first.first)) { 
      return &(*it);
    }
  }
  return NULL; 
}

InterfaceData::RenamePair* 
InterfaceData::findSpecific(IFaceRenamePairListPair* interfaceData, 
			    WN* theInterface_WN_p) { 
  for(RenamePairList::iterator it=interfaceData->second.begin(); 
      it!=interfaceData->second.end();
      ++it) { 
    if (WN_st_idx(theInterface_WN_p)==WN_st_idx((*it).first)) { 
      return &(*it);
    }
  }
  return NULL; 
}

void InterfaceData::forPUInfo(PU_Info* aPUInfo_p) { 
  PU_SetGlobalState(aPUInfo_p);
  WN* thePU_WN_p = PU_Info_tree_ptr(aPUInfo_p);
  WN_TREE_CONTAINER<PRE_ORDER> aWNPtree(thePU_WN_p);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator aWNPtreeIterator=aWNPtree.begin();
  bool skipKids=false;
  while (aWNPtreeIterator != aWNPtree.end()) { 
    WN* curWN_p = aWNPtreeIterator.Wn();
    OPERATOR opr = WN_operator(curWN_p);
    if (opr==OPR_INTERFACE) {  // interfaces
      skipKids=true;
      PuIFaceRenamePairListPairListPair* ifDataByModule;
      if ((ifDataByModule=findModuleData(aPUInfo_p))==NULL) { 
	// don't have the module yet
	ourInterfacesByModule.push_back(PuIFaceRenamePairListPairListPair(aPUInfo_p,IFaceRenamePairListPairList()));
	ifDataByModule=findModuleData(aPUInfo_p);
      }
      IFaceRenamePairListPair* ifDataByInterface;
      if ((ifDataByInterface=findInterfaceData(ifDataByModule,curWN_p))==NULL) { 
	// don't have the interface yet
	ifDataByModule->second.push_back(IFaceRenamePairListPair(RenamePair(curWN_p,NULL),
									 RenamePairList()));
	ifDataByInterface=findInterfaceData(ifDataByModule,curWN_p);
      }
      for (int i=0; i< WN_kid_count(curWN_p); ++i) { 
	WN* specificWN_p=WN_kid(curWN_p,i);
	if (specificWN_p && WN_operator(specificWN_p)==OPR_FUNC_ENTRY) {
	  RenamePair* specificData;
	  if ((specificData=findSpecific(ifDataByInterface,specificWN_p))==0) {
	    // don't have it yet
	    ifDataByInterface->second.push_back(RenamePair(specificWN_p,NULL));
	    specificData=findSpecific(ifDataByInterface,specificWN_p);
	  }
	}
      }
    }
    // advance the iterator
    if (skipKids){
      aWNPtreeIterator.WN_TREE_next_skip();
      skipKids=false;
    }
    else
      ++aWNPtreeIterator;
  }
}

void InterfaceData::dump() { 
  PU_Info* currentPUI=Current_PU_Info;
  std::cout << "InterfaceData::dumpData: start" << std::endl; 
  for(PuIFaceRenamePairListPairListPairList::iterator mIt=ourInterfacesByModule.begin(); 
      mIt!=ourInterfacesByModule.end();
      ++mIt) { 
    PU_SetGlobalState((*mIt).first);
    std::cout << "\tPU: ";
    if (WN_st(PU_Info_tree_ptr((*mIt).first))) { 
      std::cout << ST_name(WN_st(PU_Info_tree_ptr((*mIt).first)));
    }
    else { 
      std::cout << "<NULL>";
    }
    std::cout << std::endl;
    for(IFaceRenamePairListPairList::iterator iIt=(*mIt).second.begin(); 
	iIt!=(*mIt).second.end();
	++iIt) { 
      std::cout << "\t\tIF:(old:";
      if (WN_st((*iIt).first.first)) { 
	std::cout << ST_name(WN_st((*iIt).first.first));
      }
      else { 
	std::cout << "<NULL>";
      }
      std::cout << ",new:";
      if ((*iIt).first.second) { 
	std::cout << ST_name((*iIt).first.second);
      }
      else { 
	std::cout << "<NULL>";
      }
      std::cout << ")" <<  std::endl;
      for (RenamePairList::iterator sIt=(*iIt).second.begin();
	   sIt!=(*iIt).second.end();
	   ++sIt) { 
	std::cout << "\t\t\tSpec:(old:";
	if (WN_st((*sIt).first)) { 
	  std::cout << ST_name(WN_st((*sIt).first));
	}
	else {
	  std::cout << "<NULL>";
	}
	std::cout << ",new:";
	if ((*sIt).second){ 
	  std::cout << ST_name((*sIt).second);
	}
	else { 
	  std::cout << "<NULL>";
	}
	std::cout << ")" <<  std::endl;
      }
    }
  }
  std::cout << "InterfaceData::dumpData: stop" << std::endl; 
  PU_SetGlobalState(currentPUI);
}

void InterfaceData::findAndAdjustInterface(PU_Info* pu,ST* std) { 
} 
