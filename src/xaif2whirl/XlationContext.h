// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XlationContext.h,v 1.6 2004/03/29 23:41:35 eraxxon Exp $

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

// FIXME: add an elegant method for propagating flags up and down a context stack.  Also, abstract out teh context stack into its own class.  
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

  // Flags can be inherited up or down the context stack
  enum Flags {
    NOFLAG           = 0x00000000,

    // Active entities
    ACTIVE           = 0x00000001, // contains an active symref (inheritU)
    // value and deriv portion of active varrefs (inheritD)
    ACTIVE_V         = 0x00000002, // N.B.: ACTIVE must also be set; V and D
    ACTIVE_D         = 0x00000004, //   are mutually exclusive!
    
    VARREF           = 0x00000010, // within variable reference; inheritD
    LVALUE           = 0x00000020, // var ref should be an lvalue (inheritD)
    ARRAY            = 0x00000040, // an array reference (inheritD)
    ARRAYIDX         = 0x00000080, // an array index expr (inheritD)
    EXPRSIMPLE       = 0x00000100, // within a 'simple' expr (inheritD)
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

  // Within an active entity (inherited)
  bool IsActive() const { return CurContext().AreFlags(ACTIVE); }
  void SetActive()      { CurContext().SetFlags(ACTIVE); }
  void ResetActive()    { CurContext().ResetFlags(ACTIVE); }

  // Within an active.value varref (inherited)
  bool IsActive_V() const { return (CurContext().AreFlags(ACTIVE | ACTIVE_V));}
  void SetActive_V()      { CurContext().SetFlags(ACTIVE | ACTIVE_V); }
  void ResetActive_V()    { CurContext().ResetFlags(ACTIVE_V); }

  // Within an active.deriv varref (inherited)
  bool IsActive_D() const { return (CurContext().AreFlags(ACTIVE | ACTIVE_D));}
  void SetActive_D()      { CurContext().SetFlags(ACTIVE | ACTIVE_D); }
  void ResetActive_D()    { CurContext().ResetFlags(ACTIVE_D); }
  
  // Within a variable reference (inherited)
  bool IsVarRef() const { return CurContext().AreFlags(VARREF); }
  void SetVarRef()      { CurContext().SetFlags(VARREF); }
  void ResetVarRef()    { CurContext().ResetFlags(VARREF); }

  // variable reference should be an lvalue (inherited)
  bool IsLValue() const { return CurContext().AreFlags(LVALUE); }
  void SetLValue()      { CurContext().SetFlags(LVALUE); }
  void ResetLValue()    { CurContext().ResetFlags(LVALUE); }

  // An array reference (inherited)
  bool IsArray() const { return CurContext().AreFlags(ARRAY); }
  void SetArray()      { CurContext().SetFlags(ARRAY); }
  void ResetArray()    { CurContext().ResetFlags(ARRAY); }

  // An array index expression (inherited)
  bool IsArrayIdx() const { return CurContext().AreFlags(ARRAYIDX); }
  void SetArrayIdx()      { CurContext().SetFlags(ARRAYIDX); }
  void ResetArrayIdx()    { CurContext().ResetFlags(ARRAYIDX); }

  // A simple expression (e.g. Fortran loop init, update) (inherited)
  bool IsExprSimple() const { return CurContext().AreFlags(EXPRSIMPLE); }
  void SetExprSimple()      { CurContext().SetFlags(EXPRSIMPLE); }
  void ResetExprSimple()    { CurContext().ResetFlags(EXPRSIMPLE); }


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
  
  // XAIFSym -> Symbol* map: (We do not assume ownership of the map)
  Symbol* FindSym(const char* scopeid, const char* symid);
  XAIFSymToSymbolMap* GetXAIFSymToSymbolMap() const { return xsym2wsymMap; }
  void SetXAIFSymToSymbolMap(XAIFSymToSymbolMap* x) { xsym2wsymMap = x; }
  
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
  XAIFSymToSymbolMap* xsym2wsymMap;

  CtxtStack ctxtstack;
};

#endif /* XlationContext_INCLUDED */
