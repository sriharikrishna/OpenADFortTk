// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIDMaps.cxx,v 1.1 2003/08/01 15:59:36 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIDMaps.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

//*************************** User Include Files ****************************

#include "WhirlIDMaps.h"

//************************** Forward Declarations ***************************

//***************************************************************************

pair<WNIdToWNMap*, WNToWNIdMap*> 
CreateWhirlIDMaps(WN* wn)
{
  static UINT nextId = 0; // 0 reserved as NULL
  
  WNIdToWNMap* wnIdToWNMap = new WNIdToWNMap();
  WNToWNIdMap* wnToWNIdMap = new WNToWNIdMap();
  
  // Iterate over the whirl tree finding or assigning persistent ids
  WN_TREE_CONTAINER<PRE_ORDER> wtree(wn);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  
  for (it = wtree.begin(); it != wtree.end(); ++it) {
    WN* curWN = it.Wn();
    UINT curId = ++nextId;
    
    wnIdToWNMap->Insert(curId, curWN);
    wnToWNIdMap->Insert(curWN, curId);
  }
  
  return make_pair(wnIdToWNMap, wnToWNIdMap);
}

