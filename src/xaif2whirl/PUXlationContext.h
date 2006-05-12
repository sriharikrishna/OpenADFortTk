// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/PUXlationContext.h,v 1.2 2006/05/12 16:12:23 utke Exp $

#ifndef PUXlationContext_INCLUDED
#define PUXlationContext_INCLUDED

#include <list> 
#include <iostream>

#include "include/Open64BasicTypes.h"
#include "lib/support/WhirlParentize.h"
#include "lib/support/WhirlIDMaps.h"
#include "lib/support/SymTab.h"
#include "XlationContext.h"

namespace xaif2whirl {

  /**
   * PUXlationContext for xaif2whirl: Represents information about a
   * XAIF->WHIRL translation context.  Designed to convey information
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
   * For xaif2whirl, a translation context for an XAIF construct
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
     * Delete the current context and make its parent the current
     * context.  Everything (including memory) associated with the old
     * context will be deleted.
     */
    void deleteXlationContext();
  
    /** 
     * Returns the current context
     */
    XlationContext& currentXlationContext();

    // -------------------------------------------------------
    // PU level maps and data
    // -------------------------------------------------------

    WN* findParentWN(WN*);
    WN* findParentBlockWN(WN*);
    WhirlParentMap* getWNParentMap() const;
    void setWNParentMap(WhirlParentMap* aWhirlParentMapP);
  
    std::pair<ST_TAB*, PU_Info*> findSymTab(SymTabId stabId);
    SymTabIdToSymTabMap* getSymTabIdToSymTabMap() const;
    void setSymTabIdToSymTabMap(SymTabIdToSymTabMap* aSymTabIdToSymTabMapP);
  
    PU_Info* findPU(PUId aPUid);
    PUIdToPUMap* getPUIdToPUMap() const;
    void setPUIdToPUMap(PUIdToPUMap* aPUIdToPUMapP);

    WNId findWNId(WN* wn);
    WNToWNIdMap* getWNToWNIdMap() const;
    void setWNToWNIdMap(WNToWNIdMap* aWNToWNIdMapP);

    WN* findWN(WNId aWNId, bool mustFind = false);
    WNIdToWNMap* getWNIdToWNMap() const;
    void setWNIdToWNMap(WNIdToWNMap* aWNIdToWNMapP);

    Symbol* findSym(const std::string& scopeid, const std::string& symid);
    XAIFSymToSymbolMap* getXAIFSymToSymbolMap() const;
    void setXAIFSymToSymbolMap(XAIFSymToSymbolMap* aXAIFSymToSymbolMapP);
    
    // -------------------------------------------------------
    // Misc
    // -------------------------------------------------------

    void dump(std::ostream& o, const std::string& indent) const;
    void ddump() const;

    static void setPrefix(const std::string& aPrefix);
    static const std::string& getPrefix();

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
    SymTabIdToSymTabMap* mySymTabIdToSymTabMapP;

    /**
     * we don't own this
     */
    PUIdToPUMap* myPUIdToPUMapP;

    /**
     * we don't own this
     */
    WNToWNIdMap* myWNToWNIdMapP;
  
    /**
     * we don't own this
     */
    WNIdToWNMap* myWNIdToWNMapP;
  
    /**
     * we don't own this
     */
    XAIFSymToSymbolMap* myXAIFSymToSymbolMapP;

    // a globally defined prefix for all newly created symbols
    static std::string ourPrefix;

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
    void PushNewXlationContext(XlationContext::Flags_E f);

    /**
     * some string passed to the ctor to indicate who created this
     */
    std::string myOriginator;

  };

}

#endif /* XlationContext_INCLUDED */
