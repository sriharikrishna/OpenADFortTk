// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XlationContext.h,v 1.3 2003/09/17 19:44:30 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XlationContext.h,v $
//
// Purpose:
//   Represents the context in which translation of XAIF->WHIRL occurs. 
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef XlationContext_INCLUDED
#define XlationContext_INCLUDED

//************************** System Include Files ***************************

#include <iostream>

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

#include <lib/support/XlationCtxt.h>
#include <lib/support/WhirlIDMaps.h>
#include <lib/support/SymTab.h>

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// XlationContext
//***************************************************************************

class XlationContext
{
public: 
  
  // Ctxt: represents the current context
  class Ctxt : public CtxtFlags {
  public: 
    Ctxt();
    virtual ~Ctxt();

    virtual void Dump(std::ostream& o = std::cerr) const;
    virtual void DDump() const;
    
  private:
  };

  enum Flags {
    NOFLAG           = 0x00000000,
    VARREF           = 0x00000001, // within variable reference; inherited
    LVALUE           = 0x00000002, // var ref should be an lvalue (inherited)
  };

public:
  XlationContext();
  virtual ~XlationContext();
  
  // -------------------------------------------------------
  // Context manipulation (Create, Delete...)
  // -------------------------------------------------------

  // Create a new child context and make it the current context.  One
  // can pass flags that should apply to the new context.  Note that
  // that these flags *do not* override any inherited flags.
  XlationContext& CreateContext();
  XlationContext& CreateContext(uint32_t flags_);

  // Delete the current context and make its parent the current
  // context.  Everything (including memory) associated with the old
  // context will be deleted.
  XlationContext& DeleteContext();

  // Returns the current context
  Ctxt& CurContext() const { return const_cast<Ctxt&>(ctxtstack.front()); }

  // -------------------------------------------------------
  // Flags
  // -------------------------------------------------------
  
  // Within a variable reference (inherited)
  BOOL IsVarRef() const { return CurContext().AreFlags(VARREF); }
  void SetVarRef()      { CurContext().SetFlags(VARREF); }
  void ResetVarRef()    { CurContext().ResetFlags(VARREF); }

  // variable reference should be an lvalue (inherited)
  BOOL IsLValue() const { return CurContext().AreFlags(LVALUE); }
  void SetLValue()      { CurContext().SetFlags(LVALUE); }
  void ResetLValue()    { CurContext().ResetFlags(LVALUE); }

  // -------------------------------------------------------
  // Id maps
  // -------------------------------------------------------
  
  // SymTabId -> ST_TAB* map: (We do not assume ownership of the map)
  pair<ST_TAB*, PU_Info*> FindSymTab(SymTabId stabId);
  SymTabIdToSymTabMap* GetIdToSymTabMap() const { return id2stabMap; }
  void SetIdToSymTabMap(SymTabIdToSymTabMap* x) { id2stabMap = x; }
  
  // PUId -> PU_Info* map: (We do not assume ownership of the map)
  PU_Info* FindPU(PUId puid);
  PUIdToPUMap* GetIdToPUMap() const { return id2puMap; }
  void SetIdToPUMap(PUIdToPUMap* x) { id2puMap = x; }
  
  // WN* -> WNId map: (We do not assume ownership of the map)
  WNId FindWNId(WN* wn);
  WNToWNIdMap* GetWNToIdMap() const { return wn2idMap; }
  void SetWNToIdMap(WNToWNIdMap* x) { wn2idMap = x; }
  
  // WNId -> WN* map: (We do not assume ownership of the map)
  WN* FindWN(WNId wnid, bool mustFind = false);
  WNIdToWNMap* GetIdToWNMap() const { return id2wnMap; }
  void SetIdToWNMap(WNIdToWNMap* x) { id2wnMap = x; }
  
  // XAIFSym -> WhirlSym map: (We do not assume ownership of the map)
  ST* FindSym(const char* scopeid, const char* symid);
  XAIFSymToWhirlSymMap* GetXAIFSymToWhirlSymMap() const { return xsym2wsymMap; }
  void SetXAIFSymToWhirlSymMap(XAIFSymToWhirlSymMap* x) { xsym2wsymMap = x; }
  
  // -------------------------------------------------------
  // Misc
  // -------------------------------------------------------
  
  virtual void Dump(std::ostream& o = std::cerr, const char* pre = "") const;
  virtual void DDump() const;
  

private: 
  // Disable for now
  XlationContext(const XlationContext& x) { }
  XlationContext& operator=(const XlationContext& x) { return *this; }
  
  XlationContext& Ctor(uint32_t flags_);
  
  // Use a list instead a stack so that we can easily examine
  // contents.  The top of the stack will be the *front* of the
  // list. (push_front, pop_front).
  typedef std::list<Ctxt>           CtxtStack;
  typedef CtxtStack::iterator       CtxtStackIt;
  typedef CtxtStack::const_iterator CtxtStackItC;


private:
  SymTabIdToSymTabMap* id2stabMap;
  PUIdToPUMap* id2puMap;
  WNToWNIdMap* wn2idMap;
  WNIdToWNMap* id2wnMap;
  XAIFSymToWhirlSymMap* xsym2wsymMap;

  CtxtStack ctxtstack;
};

#endif /* XlationContext_INCLUDED */
