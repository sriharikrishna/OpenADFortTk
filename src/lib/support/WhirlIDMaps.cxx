// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIDMaps.cxx,v 1.2 2003/08/11 14:24:22 eraxxon Exp $

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
#include "Pro64IRInterface.h"

//************************** Forward Declarations ***************************

//***************************************************************************

pair<WNIdToWNMap*, WNToWNIdMap*> 
CreateWhirlIdMaps(WN* wn)
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

//***************************************************************************

static void
CreatePUIdMaps_PU(PU_Info* pu, PUIdToPUMap* puIdToPUMap, UINT& nextId);

PUIdToPUMap* 
CreatePUIdMaps(PU_Info* pu_forest)
{
  static UINT nextId = 1; // FIXME: start with 2 for now!
  
  PUIdToPUMap* puIdToPUMap = new PUIdToPUMap();
  
  // Translate each PU, descending into children first
  for (PU_Info *pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
    CreatePUIdMaps_PU(pu, puIdToPUMap, nextId);
  }
  
  return puIdToPUMap;
}

static void
CreatePUIdMaps_PU(PU_Info* pu, PUIdToPUMap* puIdToPUMap, UINT& nextId)
{
  UINT32 id = ++nextId;
  puIdToPUMap->Insert(id, pu);
  
  // Recursively translate all children
  for (PU_Info *child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    CreatePUIdMaps_PU(pu, puIdToPUMap, nextId);
  }
}

