#include "BackSubstituteTemps.h"
#include "Diagnostics.h"
#include "Open64IRInterface/WhirlGlobalStateUtils.h"

namespace FortTk {

  void BackSubstituteTemps::forPUInfoForrest(PU_Info* aPUInfoForrest_p) { 
    if (!aPUInfoForrest_p) { return; }
    /* Loop thru all the PU_Infos */
    PU_Info* aPUInfoTree_p;
    for (aPUInfoTree_p=aPUInfoForrest_p; aPUInfoTree_p!= NULL; aPUInfoTree_p=PU_Info_next(aPUInfoTree_p)) {
      forPUInfoTree(aPUInfoTree_p);
    }
  } 

  void BackSubstituteTemps::forPUInfoTree(PU_Info* aPUInfoTree_p) { 
    if (!aPUInfoTree_p) { return; }
    forPUInfo(aPUInfoTree_p);
    for (PU_Info *aPUInfosubtree_p = PU_Info_child(aPUInfoTree_p); 
	 aPUInfosubtree_p != NULL; 
	 aPUInfosubtree_p = PU_Info_next(aPUInfosubtree_p)) {
      forPUInfoTree(aPUInfosubtree_p);
    }
  }

  void BackSubstituteTemps::forPUInfo(PU_Info* aPUInfo_p) { 
    typedef std::map<ST*,WN*> STPtoWNPmap;
    STPtoWNPmap tempMap; 
    bool skipKids=false;
    PU_SetGlobalState(aPUInfo_p);
    WN* wn_pu = PU_Info_tree_ptr(aPUInfo_p);
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
	    ST* puST_p = ST_ptr(PU_Info_proc_sym(aPUInfo_p));
	    const char* puName = ST_name(puST_p);
	    FORTTK_MSG(2, "BackSubstituteTemps::forPUInfo: recorded temporary " << tmpName << "  defined in " << puName);
	  }
	  else { // this should not happen since these are supposed to be single assignment
	    const char* tmpName = ST_name(tempST_p); 
	    ST* puST_p = ST_ptr(PU_Info_proc_sym(aPUInfo_p));
	    const char* puName = ST_name(puST_p);
	    FORTTK_MSG(0, "BackSubstituteTemps::forPUInfo: recorded temporary " << tmpName << " is redefined in " << puName);
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
	    ST* puST_p = ST_ptr(PU_Info_proc_sym(aPUInfo_p));
	    const char* puName = ST_name(puST_p);
	    FORTTK_DIE("BackSubstituteTemps::forPUInfo: no definition for temporary " << tmpName << " in " << puName);
	  }
	  // make sure the parent is set by now
	  if (!aWNPtreeIterator.Get_parent_wn())
	    FORTTK_DIE("BackSubstituteTemps::forPUInfo: no parent set");
	  // replace the current node within the parent
	  WN_kid(aWNPtreeIterator.Get_parent_wn(),aWNPtreeIterator.Get_kid_index()) = WN_COPY_Tree((*mapIter).second);
	  skipKids=true;
	  const char* tmpName = ST_name(tempST_p); 
	  ST* puST_p = ST_ptr(PU_Info_proc_sym(aPUInfo_p));
	  const char* puName = ST_name(puST_p);
	  FORTTK_MSG(2, "JU: BackSubstituteTemps::forPUInfo: substituted temporary " << tmpName << "  in " << puName);
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
