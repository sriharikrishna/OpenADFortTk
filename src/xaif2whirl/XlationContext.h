// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XlationContext.h,v 1.2 2003/09/02 15:02:21 eraxxon Exp $

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
  XlationContext();
  virtual ~XlationContext();
  
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
  WN* FindWN(WNId wnid);
  WNIdToWNMap* GetIdToWNMap() const { return id2wnMap; }
  void SetIdToWNMap(WNIdToWNMap* x) { id2wnMap = x; }
  
  // XAIFSym -> WhirlSym map: (We do not assume ownership of the map)
  ST* FindSym(const char* scopeid, const char* symid);
  XAIFSymToWhirlSymMap* GetXAIFSymToWhirlSymMap() const { return xsym2wsymMap; }
  void SetXAIFSymToWhirlSymMap(XAIFSymToWhirlSymMap* x) { xsym2wsymMap = x; }
  
  
  virtual void Dump(std::ostream& o = std::cerr, const char* pre = "") const;
  virtual void DDump() const;
  
private: 
  // Disable for now
  XlationContext(const XlationContext& x) { }
  XlationContext& operator=(const XlationContext& x) { return *this; }
  
private:
  SymTabIdToSymTabMap* id2stabMap;
  PUIdToPUMap* id2puMap;
  WNToWNIdMap* wn2idMap;
  WNIdToWNMap* id2wnMap;
  XAIFSymToWhirlSymMap* xsym2wsymMap;
};

#endif /* XlationContext_INCLUDED */
