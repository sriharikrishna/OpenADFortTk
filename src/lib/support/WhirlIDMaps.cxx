// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIDMaps.cxx,v 1.8 2005/03/19 22:54:50 eraxxon Exp $

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
#include "Open64IRInterface.hpp"

//************************** Forward Declarations ***************************

//***************************************************************************
// ST_TAB <-> SymTabId maps
//***************************************************************************

void
SymTabToSymTabIdMap::Create(PU_Info* pu_forest)
{
  CreateSymTabIdMaps(pu_forest, this, NULL);
}

void
SymTabIdToSymTabMap::Create(PU_Info* pu_forest)
{
  CreateSymTabIdMaps(pu_forest, NULL, this);
}

//***************************************************************************
// PU <-> PUId maps
//***************************************************************************

void
PUToPUIdMap::Create(PU_Info* pu_forest)
{
  CreatePUIdMaps(pu_forest, this, NULL);
}

void
PUIdToPUMap::Create(PU_Info* pu_forest)
{
  CreatePUIdMaps(pu_forest, NULL, this);
}

//***************************************************************************
// WNId <-> WN map
//***************************************************************************

void
WNToWNIdMap::Create(WN* wn)
{
  CreateWhirlIdMaps(wn, this, NULL);
}

void
WNIdToWNMap::Create(WN* wn)
{
  CreateWhirlIdMaps(wn, NULL, this);
}


WNToWNIdTabMap::~WNToWNIdTabMap()
{
  Destroy();
}

void 
WNToWNIdTabMap::Create(PU_Info* pu_forest)
{
  Open64IRProcIterator procIt(pu_forest);
  for ( ; procIt.isValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.current().hval();
    WN* wn_pu = PU_Info_tree_ptr(pu);
    
    WNToWNIdMap* tab = new WNToWNIdMap(wn_pu);
    Insert(pu, tab);
  }
}

void 
WNToWNIdTabMap::Destroy()
{
  for (iterator it = begin(); it != end(); ++it) {
    delete (*it).second; // WNToWNIdMap*
  }
  clear();
}

//***************************************************************************
// Optional routines for map creation
//***************************************************************************

// CreateSymTabIdMaps: Create id's based on Open64IRProcIterator.
// N.B. this must restore global symtab state for each pu
void
CreateSymTabIdMaps(PU_Info* pu_forest, 
		   SymTabToSymTabIdMap* x, SymTabIdToSymTabMap* y)
{
  static UINT nextId = 0; // 0 reserved as NULL
  
  // Enter global symtab
  ++nextId; // create new id
  if (x) {
    x->Insert(Scope_tab[GLOBAL_SYMTAB].st_tab, nextId);
  }
  if (y) {
    y->Insert(nextId, Scope_tab[GLOBAL_SYMTAB].st_tab, NULL);
  }
  
  // Enter all local symtabs (one symtab per PU)
  Open64IRProcIterator procIt(pu_forest);
  for ( ; procIt.isValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.current().hval();    
    
    ++nextId; // create new id
    if (x) {
      x->Insert(Scope_tab[CURRENT_SYMTAB].st_tab, nextId);
    }
    if (y) {
      y->Insert(nextId, Scope_tab[GLOBAL_SYMTAB].st_tab, pu);
    }
  }
}


// CreatePUIdMaps: Create id's based on Open64IRProcIterator. 
void
CreatePUIdMaps(PU_Info* pu_forest, PUToPUIdMap* x, PUIdToPUMap* y)
{
  static UINT nextId = 0; // 0 reserved as NULL
  
  // Enter all PUs
  Open64IRProcIterator procIt(pu_forest);
  for ( ; procIt.isValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.current().hval();    
    
    ++nextId; // create new id
    if (x) {
      x->Insert(pu, nextId);
    }
    if (y) {
      y->Insert(nextId, pu);
    }
  }
}


void
CreateWhirlIdMaps(WN* wn, WNToWNIdMap* x, WNIdToWNMap* y)
  
{
  // Note: Do not use a static id because it would then require that
  // this function be called in the same order across two different
  // runs.
  UINT nextId = 0; // 0 reserved as NULL
  
  // Iterate over the whirl tree finding or assigning persistent ids
  WN_TREE_CONTAINER<PRE_ORDER> wtree(wn);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  
  for (it = wtree.begin(); it != wtree.end(); ++it) {
    WN* curWN = it.Wn();
    UINT curId = ++nextId; // create new id

    if (x) {
      x->Insert(curWN, curId);
    }
    if (y) {
      y->Insert(curId, curWN);
    }
  }
}

//***************************************************************************
