// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIDMaps.cxx,v 1.3 2003/09/02 15:02:20 eraxxon Exp $

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

// CreateSymTabIdMaps: Created id's based on Pro64IRProcIterator.
// N.B. this must use symtab saving/restoring.
pair<SymTabToSymTabIdMap*, SymTabIdToSymTabMap*>
CreateSymTabIdMaps(PU_Info* pu_forest)
{
  static UINT nextId = 0; // 0 reserved as NULL

  SymTabToSymTabIdMap* stabToStabIdMap = new SymTabToSymTabIdMap();
  SymTabIdToSymTabMap* stabIdToStabMap = new SymTabIdToSymTabMap();

  // Enter global symtab
  ++nextId; // create new id
  stabToStabIdMap->Insert(Scope_tab[GLOBAL_SYMTAB].st_tab, nextId);
  stabIdToStabMap->Insert(nextId, Scope_tab[GLOBAL_SYMTAB].st_tab, NULL);

  // Enter all local symtabs (one symtab per PU)
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();    
    
    ++nextId; // create new id
    stabToStabIdMap->Insert(Scope_tab[CURRENT_SYMTAB].st_tab, nextId);
    stabIdToStabMap->Insert(nextId, Scope_tab[GLOBAL_SYMTAB].st_tab, pu);
  }
  
  return make_pair(stabToStabIdMap, stabIdToStabMap);
}

//***************************************************************************

static void
CreatePUIdMaps_PU(PU_Info* pu, PUToPUIdMap* puToPUIdMap, 
		  PUIdToPUMap* puIdToPUMap, UINT& nextId);

// CreatePUIdMaps: Create id's based on DFS.  We manually iterate over
// the PU forest (as opposed to using 'Pro64IRProcIterator') so that
// there are no save/restore symtab side effects.
pair<PUToPUIdMap*, PUIdToPUMap*>
CreatePUIdMaps(PU_Info* pu_forest)
{
  static UINT nextId = 0; // 0 reserved as NULL
  
  PUToPUIdMap* puToPUIdMap = new PUToPUIdMap();
  PUIdToPUMap* puIdToPUMap = new PUIdToPUMap();
  
  // Translate each PU, descending into children first
  for (PU_Info *pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
    CreatePUIdMaps_PU(pu, puToPUIdMap, puIdToPUMap, nextId);
  }
  
  return make_pair(puToPUIdMap, puIdToPUMap);
}

static void
CreatePUIdMaps_PU(PU_Info* pu, PUToPUIdMap* puToPUIdMap, 
		  PUIdToPUMap* puIdToPUMap, UINT& nextId)
{
  UINT32 id = ++nextId; // create new id
  puToPUIdMap->Insert(pu, id);
  puIdToPUMap->Insert(id, pu);
  
  // Recursively translate all children
  for (PU_Info *child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    CreatePUIdMaps_PU(pu, puToPUIdMap, puIdToPUMap, nextId);
  }
}

//***************************************************************************

pair<WNToWNIdMap*, WNIdToWNMap*> 
CreateWhirlIdMaps(WN* wn)
{
  static UINT nextId = 0; // 0 reserved as NULL
  
  WNToWNIdMap* wnToWNIdMap = new WNToWNIdMap();
  WNIdToWNMap* wnIdToWNMap = new WNIdToWNMap();
  
  // Iterate over the whirl tree finding or assigning persistent ids
  WN_TREE_CONTAINER<PRE_ORDER> wtree(wn);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  
  for (it = wtree.begin(); it != wtree.end(); ++it) {
    WN* curWN = it.Wn();
    UINT curId = ++nextId; // create new id
    
    wnToWNIdMap->Insert(curWN, curId);
    wnIdToWNMap->Insert(curId, curWN);
  }
  
  return make_pair(wnToWNIdMap, wnIdToWNMap);
}

//***************************************************************************
