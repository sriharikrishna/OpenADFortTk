// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIDMaps.cxx,v 1.4 2004/01/29 23:16:05 eraxxon Exp $

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

// CreateSymTabIdMaps: Create id's based on Pro64IRProcIterator.
// N.B. this must restore global symtab state for each pu
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

// CreatePUIdMaps: Create id's based on Pro64IRProcIterator. 
pair<PUToPUIdMap*, PUIdToPUMap*>
CreatePUIdMaps(PU_Info* pu_forest)
{
  static UINT nextId = 0; // 0 reserved as NULL
  
  PUToPUIdMap* puToPUIdMap = new PUToPUIdMap();
  PUIdToPUMap* puIdToPUMap = new PUIdToPUMap();
  
  // Enter all PUs
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();    
    
    ++nextId; // create new id
    puToPUIdMap->Insert(pu, nextId);
    puIdToPUMap->Insert(nextId, pu);
  }
  
  return make_pair(puToPUIdMap, puIdToPUMap);
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
