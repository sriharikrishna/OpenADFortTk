// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.h,v 1.14 2005/07/28 15:46:51 eraxxon Exp $

#ifndef Symbol_H 
#define Symbol_H

#include "Open64IRInterface/Open64BasicTypes.h"
#include "WhirlIDMaps.h"

namespace fortTkSupport { 

  class Symbol {
  public:
    Symbol();
    Symbol(const ST* st, WNId wnid, bool act);
    virtual ~Symbol();
  
    // -------------------------------------------------------
  
    // Return the WHIRL symbol
    ST* GetST() const { return st; }
    void SetST(const ST* x) { st = const_cast<ST*>(x); }
  
    // -------------------------------------------------------
  
    bool IsPathCollapsed() { return wnid != 0; }

    WNId GetPathVorlage() { return wnid; }
    void SetPathVorlage(WNId x) { wnid = x; }
  
    // -------------------------------------------------------
  
    // Is the symbol active in the AD sense
    bool IsActive() const { return active; }
    void SetActive(bool act) { active = act; }
  
    virtual void Dump(std::ostream& o = std::cerr) const;
    virtual void DDump() const;

  private:
    // These could make sense, but I just haven't implemented them yet
    Symbol(const Symbol& x) { }
    Symbol& operator=(const Symbol& x) { return *this; }

  private:
    ST* st;     // 
    WNId wnid;  // for a scalarized symbol
    bool active;
  };

}

#endif 
