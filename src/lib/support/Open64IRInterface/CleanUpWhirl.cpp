#include <set>
#include "CleanUpWhirl.h"
#include "diagnostics.h"
#include "WhirlGlobalStateUtils.h"

void CleanUpWhirl::forPUInfoForest(PU_Info* aPUInfoForest_p) { 
  if (!aPUInfoForest_p) { return; }
  /* Loop thru all the PU_Infos */
  PU_Info* aPUInfoTree_p;
  for (aPUInfoTree_p=aPUInfoForest_p; aPUInfoTree_p!= NULL; aPUInfoTree_p=PU_Info_next(aPUInfoTree_p)) {
    forPUInfoTree(aPUInfoTree_p);
  }
} 

void CleanUpWhirl::forPUInfoTree(PU_Info* aPUInfoTree_p) { 
  if (!aPUInfoTree_p) { return; }
  forPUInfo(aPUInfoTree_p);
  for (PU_Info *aPUInfosubtree_p = PU_Info_child(aPUInfoTree_p); 
       aPUInfosubtree_p != NULL; 
       aPUInfosubtree_p = PU_Info_next(aPUInfosubtree_p)) {
    forPUInfoTree(aPUInfosubtree_p);
  }
}

ST* findModuleSymbol(ST* moduleName_ST_p,
		     ST* dummyLocal_ST_p) { 
  INT level=ST_level(moduleName_ST_p); 
  // level should be the same as the module name symbol, i.e. 1 
  for (INT i = 1; 
       i < ST_Table_Size(level) ; 
       ++i) { 
    // get the symbol from the table
    ST* an_ST_p=&(St_Table(level,i));
    if ((ST_sclass(an_ST_p)==SCLASS_MODULE) // must be module storage class 
	&& 
	(moduleName_ST_p== ST_base(an_ST_p)) // must be the same module symbol
	&& 
	(strcmp(ST_name(an_ST_p),ST_name(dummyLocal_ST_p))==0)) // must match the name
      return an_ST_p;
  }
  DIE("findModuleSymbol: no symbol %s in module %s\n",ST_name(dummyLocal_ST_p),ST_name(moduleName_ST_p));
  return 0; 	
} 

// in use statements the front-end generates
// references to bogus local symbol table 
// entries instead of the proper entries in the 
// global symbol table. We replace these references.
void CleanUpWhirl::forPUInfo(PU_Info* aPUInfo_p) { 
  PU_SetGlobalState(aPUInfo_p);
  WN* thePU_WN_p = PU_Info_tree_ptr(aPUInfo_p);
  WN_TREE_CONTAINER<PRE_ORDER> aWNPtree(thePU_WN_p);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator aWNPtreeIterator=aWNPtree.begin();
  std::set<WN*> toBeDeletedSet;
  bool skipKids=false;
  while (aWNPtreeIterator != aWNPtree.end()) { 
    WN* curWN_p = aWNPtreeIterator.Wn();
    OPERATOR opr = WN_operator(curWN_p);
    if (opr==OPR_USE) {  // use statements
      skipKids=true;
      ST* moduleName_ST_p=WN_st(curWN_p); 
      for (INT kidIdx = 0; kidIdx < WN_kid_count(curWN_p); kidIdx++) {
	WN* useOldKid_WN_p = WN_kid(curWN_p, kidIdx);
	ST* dummyLocal_ST_p=WN_st(useOldKid_WN_p);
	ST* properModule_ST_p=findModuleSymbol(moduleName_ST_p,
					       dummyLocal_ST_p);
	if (properModule_ST_p) { 
	  WN_kid(curWN_p,kidIdx)=WN_CreateIdname(WN_idname_offset(useOldKid_WN_p),properModule_ST_p);
	  toBeDeletedSet.insert(useOldKid_WN_p);
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
  // postpone the deletion to avoid possibly upsetting the iterator
  for (std::set<WN*>::iterator i = toBeDeletedSet.begin();
       i!=toBeDeletedSet.end();
       ++i) 
    WN_Delete(*i);
} 

