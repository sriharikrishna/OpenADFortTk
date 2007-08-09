#ifndef CleanUpWhirl_H_INCLUDED 
#define CleanUpWhirl_H_INCLUDED

#include "Open64IRInterface/Open64BasicTypes.h"

/**
 * clean up whirl problems we 
 * cannot fix in the front-end 
 * because of ordering issues in 
 * the processing of one PU at a time
 */
class CleanUpWhirl {

 public : 

  static void forPUInfoForest(PU_Info* aPUInfoForest_p);

 private:

  static void forPUInfoTree(PU_Info* aPUInfoTree_p);
  
  static void forPUInfo(PU_Info* aPUInfo_p);

};

#endif
