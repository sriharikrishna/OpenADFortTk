#include <set>
#include "CleanUpWhirl.h"
#include "diagnostics.h"
#include "WhirlGlobalStateUtils.h"

PU_Info* CleanUpWhirl::findModulePU(PU_Info* aPUInfoForest_p,
				    ST* moduleName_ST_p) { 
  PU_Info* aPUInfoTree_p;
  for (aPUInfoTree_p=aPUInfoForest_p; aPUInfoTree_p!= NULL; aPUInfoTree_p=PU_Info_next(aPUInfoTree_p)) {
    if (aPUInfoTree_p->proc_sym==ST_st_idx(*moduleName_ST_p))
      return aPUInfoTree_p;
  }
  DIE("findModulePU: no module %s\n",ST_name(moduleName_ST_p));
}
		

void CleanUpWhirl::forPUInfoForest(PU_Info* aPUInfoForest_p) { 
  if (!aPUInfoForest_p) { return; }
  /* Loop through all the PU_Infos */
  PU_Info* aPUInfoTree_p;
  for (aPUInfoTree_p=aPUInfoForest_p; aPUInfoTree_p!= NULL; aPUInfoTree_p=PU_Info_next(aPUInfoTree_p)) {
    forPUInfoTree(aPUInfoTree_p,
		  aPUInfoForest_p);
  }
} 

void CleanUpWhirl::forPUInfoTree(PU_Info* aPUInfoTree_p,
				 PU_Info* aTopPUInfo_p) { 
  if (!aPUInfoTree_p) { return; }
  forPUInfo(aPUInfoTree_p,
	    aTopPUInfo_p);
  for (PU_Info *aPUInfosubtree_p = PU_Info_child(aPUInfoTree_p); 
       aPUInfosubtree_p != NULL; 
       aPUInfosubtree_p = PU_Info_next(aPUInfosubtree_p)) {
    forPUInfoTree(aPUInfosubtree_p,
		  aTopPUInfo_p);
  }
}

ST* CleanUpWhirl::findModuleSymbol(ST* moduleName_ST_p,
				   ST* dummyLocal_ST_p,
				   PU_Info* aTopPUInfo_p) { 
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
  // haven't found it yet.  This can be the case if the module variable is actually 
  // a fortran "PARAMETER" i.e. a constant for which the name won't match
  // because its name in the global symbol table is the constant value. 
  // we should try to find the PU of the module and look it up there. 
  PU_Info* theModulePU=findModulePU(aTopPUInfo_p,moduleName_ST_p);
  const char* dummyLocalName=ST_name(dummyLocal_ST_p);
  // temporarily reset the global state
  PU_Info* currentPUI=Current_PU_Info;
  PU_SetGlobalState(theModulePU);
  // level should be 2 here
  level=2;
  for (INT i = 1; 
       i < ST_Table_Size(level) ; 
       ++i) { 
    // get the symbol from the table
    ST* an_ST_p=&(St_Table(level,i));
    // std::cout << "looking at " << ST_name(an_ST_p) << std::endl; 
    if (strcmp(ST_name(an_ST_p),dummyLocalName)==0) { // must match the name
      PU_SetGlobalState(currentPUI);
      return &(St_Table(1,ST_st_idx(*an_ST_p)));
    }
  }
  PU_SetGlobalState(currentPUI);
  DIE("findModuleSymbol: no symbol %s in module %s\n",ST_name(dummyLocal_ST_p),ST_name(moduleName_ST_p));
  return 0; 	
} 

// in use statements the front-end generates
// references to bogus local symbol table 
// entries instead of the proper entries in the 
// global symbol table. We replace these references.
void CleanUpWhirl::forPUInfo(PU_Info* aPUInfo_p,
			     PU_Info* aTopPUInfo_p) { 
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
      for (INT kidIdx = 0; kidIdx < WN_kid_count(curWN_p); kidIdx+=2) {
	// for each symbol listed in the code after the use
	// the symbol is repeated identical if it is not renamed
	// or else the first in the pair is the new name
	// with which we reference the module name listed as the second one.
	const char* renameName=ST_name(WN_st(WN_kid(curWN_p,kidIdx)));
	const char* moduleName=ST_name(WN_st(WN_kid(curWN_p,kidIdx+1)));
	if (!strcmp(renameName,moduleName)) {
	  // is not a rename, fix up the first kid as well to be consistent
	  WN* useOldKid_WN_p = WN_kid(curWN_p, kidIdx);
	  ST* dummyLocal_ST_p=WN_st(useOldKid_WN_p);
	  ST* properModule_ST_p=findModuleSymbol(moduleName_ST_p,
						 dummyLocal_ST_p,
						 aTopPUInfo_p);
	  if (properModule_ST_p) { 
	    WN_kid(curWN_p,kidIdx)=WN_CreateIdname(WN_idname_offset(useOldKid_WN_p),properModule_ST_p);
	    toBeDeletedSet.insert(useOldKid_WN_p);
	  }
	}
	// always fix up the second kid
	WN* useOldKid_WN_p = WN_kid(curWN_p, kidIdx+1);
	ST* dummyLocal_ST_p=WN_st(useOldKid_WN_p);
	ST* properModule_ST_p=findModuleSymbol(moduleName_ST_p,
					       dummyLocal_ST_p,
					       aTopPUInfo_p);
	if (properModule_ST_p) { 
	  WN_kid(curWN_p,kidIdx+1)=WN_CreateIdname(WN_idname_offset(useOldKid_WN_p),properModule_ST_p);
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

