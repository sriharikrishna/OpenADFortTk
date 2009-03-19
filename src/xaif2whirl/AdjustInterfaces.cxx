#include "AdjustInterfaces.h"
#include "Diagnostics.h"
#include "Open64IRInterface/WhirlGlobalStateUtils.h"

void AdjustInterfaces::doIt() { 
  if (!myPUInfoForest_p) { return; }
  // Loop through all the PU_Infos 
  PU_Info* aPUInfoTree_p;
  for (aPUInfoTree_p=myPUInfoForest_p; aPUInfoTree_p!= NULL; aPUInfoTree_p=PU_Info_next(aPUInfoTree_p)) {
    forPUInfoTree(aPUInfoTree_p);
  }
} 

void AdjustInterfaces::forPUInfoTree(PU_Info* aPUInfoTree_p) { 
  if (!aPUInfoTree_p) { return; }
  forPUInfo(aPUInfoTree_p);
  for (PU_Info *aPUInfosubtree_p = PU_Info_child(aPUInfoTree_p); 
       aPUInfosubtree_p != NULL; 
       aPUInfosubtree_p = PU_Info_next(aPUInfosubtree_p)) {
    forPUInfoTree(aPUInfosubtree_p);
  }
}

void AdjustInterfaces::forPUInfo(PU_Info* aPUInfo_p) { 
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
      WN* interfaceFuncWN_p=WN_kid0(curWN_p);
      ST* puName_ST_p=WN_st(interfaceFuncWN_p); 
      for (INT kidIdx = 0; kidIdx < WN_kid_count(interfaceFuncWN_p); kidIdx+=2) {
	ST* dummyLocal_ST_p=WN_st(WN_kid(interfaceFuncWN_p, kidIdx));
	TY_IDX properPUTypeIndex=findPUSymbolType(puName_ST_p,
						  dummyLocal_ST_p);
	if (properPUTypeIndex && properPUTypeIndex!=ST_type(dummyLocal_ST_p)){
	  // do the surgery on the type info 
	  Set_ST_type(dummyLocal_ST_p,properPUTypeIndex);
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

TY_IDX AdjustInterfaces::findPUSymbolType(ST* puName_ST_p,
					  ST* dummyLocal_ST_p) { 
  TY_IDX theTypeIndex=0;
  PU_Info* thePU=findPU(puName_ST_p);
  if (!thePU)
    return theTypeIndex; 
  const char* dummyLocalName=ST_name(dummyLocal_ST_p);
  const char* puName=ST_name(puName_ST_p);
  // temporarily reset the global state
  PU_Info* currentPUI=Current_PU_Info;
  PU_SetGlobalState(thePU);
  // level should be 2 here
  INT level=2;
  for (INT i = 1; 
       i < ST_Table_Size(level) ; 
       ++i) { 
    // get the symbol from the table
    ST* an_ST_p=&(St_Table(level,i));
    // std::cout << "looking at " << ST_name(an_ST_p) << std::endl; 
    if (strcmp(ST_name(an_ST_p),dummyLocalName)==0) { // must match the name
      theTypeIndex=ST_type(an_ST_p);
      PU_SetGlobalState(currentPUI);
      return theTypeIndex;
    }
  }
  PU_SetGlobalState(currentPUI);
  FORTTK_ASSERT_WARN(0, "AdjustInterfaces::findPUSymbol: symbol " << dummyLocalName << " referenced in " << puName << " not found in the derinition");
  return theTypeIndex; 	
} 

PU_Info* AdjustInterfaces::findPU(ST* puName_ST_p) { 
  PU_Info* aPUInfoTree_p;
  for (aPUInfoTree_p=myPUInfoForest_p; aPUInfoTree_p!= NULL; aPUInfoTree_p=PU_Info_next(aPUInfoTree_p)) {
    if (aPUInfoTree_p->proc_sym==ST_st_idx(*puName_ST_p))
      return aPUInfoTree_p;
  }
  FORTTK_ASSERT_WARN(0,"AdjustInterfaces::findPU: cannot find definition for interface " << ST_name(puName_ST_p));
  return 0; 
}
		
