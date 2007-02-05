#ifndef BackSubstituteTemps_H 
#define BackSubstituteTemps_H

#include "Open64IRInterface/Open64BasicTypes.h"

namespace FortTk {

  class BackSubstituteTemps {

  public : 

    static void forPUInfoForrest(PU_Info* aPUInfoForrest_p);

  private:

    static void forPUInfoTree(PU_Info* aPUInfoTree_p);

    static void forPUInfo(PU_Info* aPUInfo_p);

  };

}

#endif
