// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.h,v 1.9 2006/05/12 16:12:23 utke Exp $


#ifndef whirl2xaif_h
#define whirl2xaif_h

#include <fstream>

#include "include/Open64BasicTypes.h"

#include "lib/support/xmlostream.h"
#include "lib/support/IntrinsicXlationTable.h"
#include "lib/support/OAMaps.h"
#include "lib/support/ScalarizedRefTab.h"
#include "lib/support/WhirlIDMaps.h"
#include "lib/support/stab_attr.h"
#include "lib/support/wn_attr.h"
#include "lib/support/diagnostics.h"
#include "PUXlationContext.h"

namespace whirl2xaif {
  
  class Whirl2Xaif {
  public : 
    static void translateIR(std::ostream& os, 
			    PU_Info* pu_forest,
			    const char* tmpVarPrefix);

    static fortTkSupport::IntrinsicXlationTable& getIntrinsicXlationTable();
    static PUToOAAnalInfoMap& getOAAnalMap();
    static fortTk::ScalarizedRefTabMap_W2X& getScalarizedRefTableMap();
    static WNToWNIdTabMap& getWNToWNIdTableMap();

    static void backSubstituteLoopBoundsPU_InfoForrest(PU_Info* aPU_InfoForrest_p);

  private:

    /** 
     * no def
     */
    Whirl2Xaif();

    static fortTkSupport::IntrinsicXlationTable ourIntrinsicTable;
    static const std::string ourDividerComment;
    static PUToOAAnalInfoMap ourOAAnalMap;
    static fortTk::ScalarizedRefTabMap_W2X ourScalarizedRefTableMap;
    static WNToWNIdTabMap ourWNToWNIdTableMap;

    static void translateScopeHierarchy(xml::ostream& xos, 
					PU_Info* pu_forest, 
					PUXlationContext& ctxt);

    static void translateScopeHierarchyPU(xml::ostream& xos, 
					  PU_Info* pu, 
					  UINT32 parentId, 
					  PUXlationContext& ctxt);

    static void translateAnalMaps(xml::ostream& xos, 
				  PU_Info* pu_forest, 
				  PUXlationContext& ctxt);

    static void translatePU(xml::ostream& xos, 
			    OA::OA_ptr<OA::CallGraph::CallGraphStandard::Node> n, 
			    UINT32 vertexId, 
			    PUXlationContext& ctxt);

    static void translatePU(xml::ostream& xos, 
			    PU_Info *pu, 
			    UINT32 vertexId,
			    PUXlationContext& ctxt);

    static void translateWNPU(xml::ostream& xos, 
			      WN* pu, 
			      PUXlationContext& ctxt);

    static void dumpTranslationHeaderComment(xml::ostream& xos);

    static void backSubstituteLoopBoundsPU_InfoTree(PU_Info* aPU_InfoTree_p);

    static void backSubstituteLoopBoundsPU_Info(PU_Info* aPU_Info_p);

  };

}

#endif 
