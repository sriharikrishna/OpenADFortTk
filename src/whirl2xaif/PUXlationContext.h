// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/PUXlationContext.h,v 1.2 2006/05/12 16:12:23 utke Exp $

#ifndef PUXlationContext_INCLUDED
#define PUXlationContext_INCLUDED

#include <list> 
#include <iostream>

#include "include/Open64BasicTypes.h"
#include "lib/support/WhirlParentize.h"
#include "lib/support/WhirlIDMaps.h"
#include "lib/support/OAMaps.h"
#include "lib/support/SymTab.h"
#include "lib/support/ScalarizedRefTab.h"
#include "XlationContext.h"

namespace whirl2xaif {

  /**
   * PUXlationContext for whirl2xaif: Represents information about a
   * WHIRL->XAIF translation context.  Designed to convey information
   * about a parent context to children contexts.
   * 
   * PUXlationContext maintains an internal stack of XlationContexts,
   * allowing users to 1) create new child contexts (push), 2) destroy
   * and return to parent contexts (pop) and 3) query the current
   * context.  The current translation context provides information
   * about the containing WHIRL context.  There should always be at
   * least one context on the stack.  (Upon creation, one context exists
   * on the stack.)  Because this class is designed to represent
   * information about one procedure (WHIRL PU) at a time, information
   * that applies for a whole PU is located outside instead of inside
   * the stack.
   *
   * For whirl2xaif, a translation context for an XAIF construct
   * corresponds to its parent construct.  Thus there will be one
   * translation context on the stack for every 'indendation' level.
   * Context flags indicate significant facts about the parent construct
   * and will typically correspond to XAIF concepts (as opposed to
   * WHIRL).
   */

  class PUXlationContext {
  public: 

    /**
     * the originator is some name that we can use 
     * for debugging purposes
     */
    PUXlationContext(const std::string& anOriginator);

    ~PUXlationContext();

    // -------------------------------------------------------
    // stacked XlationContext manipulation (Create, Delete...)
    // -------------------------------------------------------
  
    /**
     * Create a new child context and make it the current context.
     */
    void createXlationContext();

    /**
     * Create a new child context and make it the current context.
     * We pass flags that should apply to the new context.  Note that
     * that these flags *do not* override any inherited flags.
     */
    void createXlationContext(XlationContext::Flags_E f);

    /**
     * Create a new child context and make it the current context.
     * We pass flags that should apply to the new context.  Note that
     * that these flags *do not* override any inherited flags.
     * Also pass along a whirl node.
     */
    void createXlationContext(XlationContext::Flags_E f, WN* aWNp);
  
    /** 
     * Delete the current context and make its parent the current
     * context.  Everything (including memory) associated with the old
     * context will be deleted.
     */
    void deleteXlationContext();
  
    /** 
     * Returns the current context
     */
    XlationContext& currentXlationContext();

    /**
     * get WN* the most recent non-NULL WN.
     */
    WN* getMostRecentWN();

    // -------------------------------------------------------
    // PU level maps and data
    // -------------------------------------------------------

    WN* findParentWN(WN*);
    WN* findParentBlockWN(WN*);
    WhirlParentMap* getWNParentMap() const;
    void setWNParentMap(WhirlParentMap* aWhirlParentMapP);
  
    SymTabId findSymTabId(ST_TAB* stab);
    SymTabToSymTabIdMap* getSymTabToIdMap() const;
    void setSymTabToIdMap(SymTabToSymTabIdMap* aSymTabToSymTabIdMapP);
  
    PUId findPUId(PU_Info* pu);
    PUToPUIdMap* getPUToIdMap() const;
    void setPUToIdMap(PUToPUIdMap* aPUToPUIdMapP);

    WNId findWNId(WN* wn);
    WNToWNIdMap* getWNToIdMap() const;
    void setWNToIdMap(WNToWNIdMap* x);

    int findUDDUChainId(WN* wnexpr);
    OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> getUDDUChains() const; 
    void setUDDUChains(OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> x);

    fortTk::ScalarizedRef* findScalarizedRef(WN* wn);
    fortTk::ScalarizedRefTab_W2X* getScalarizedRefTab() const;
    void setScalarizedRefTab(fortTk::ScalarizedRefTab_W2X* aScalarizedRefTab_W2Xp);
  
    int isActiveSym(ST* st);
    int isActiveStmt(PU_Info* pu, WN* wn);
    int isActiveVarRef(PU_Info* pu, WN* wn); 
    void setActivity(OA::OA_ptr<OA::Activity::InterActive> anActivityMap);

    // -------------------------------------------------------
    // Misc
    // -------------------------------------------------------

    void dump(std::ostream& o, const std::string& indent) const;
    void ddump() const;

    bool isF90() const;

    void setF90(bool aFlag);

  private: 
    /**
     * no def
     */
    PUXlationContext(const XlationContext& x);

    /**
     * no def
     */
    PUXlationContext();

    /**
     * no def
     */
    PUXlationContext& operator=(const PUXlationContext& x);
  
    /**
     * we don't own this
     */
    WhirlParentMap* myWNParentMapP;

    /**
     * we don't own this
     */
    SymTabToSymTabIdMap* myStab2idMapP;

    /**
     * we don't own this
     */
    PUToPUIdMap* myPU2idMapP;

    /**
     * we don't own this
     */
    WNToWNIdMap* myWN2idMapP;
  
    /**
     * we don't own this
     */
    OA::OA_ptr<OA::Activity::InterActive> myActivity;
  
    /**
     * we don't own this
     */
    OA::OA_ptr<OA::XAIF::UDDUChainsXAIF> myUdduchains;

    /**
     * we don't own this
     */
    fortTk::ScalarizedRefTab_W2X* myScalarizedRefTab_W2Xp;

  
    /** Use a list instead a stack so that we can easily examine
     *  contents.  The top of the stack will be the *front* of the
     * list. (push_front, pop_front).
     */
    typedef std::list<XlationContext> XlationContextStack;

    /**
     *  the context stack, we own all the entries in it
     */
    XlationContextStack myXlationContextStack;

    /**
     * this makes a new XlationContext
     * and pushes it on top
     */
    void PushNewXlationContext(XlationContext::Flags_E f, WN* aWNp);

    /**
     * some string passed to the ctor to indicate who created this
     */
    std::string myOriginator;

    bool myF90Flag;

  };

}

#endif /* XlationContext_INCLUDED */
