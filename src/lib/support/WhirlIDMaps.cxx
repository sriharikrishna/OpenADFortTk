// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIDMaps.cxx,v 1.6 2004/06/09 21:59:31 eraxxon Exp $

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
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();
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

// CreateSymTabIdMaps: Create id's based on Pro64IRProcIterator.
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
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();    
    
    ++nextId; // create new id
    if (x) {
      x->Insert(Scope_tab[CURRENT_SYMTAB].st_tab, nextId);
    }
    if (y) {
      y->Insert(nextId, Scope_tab[GLOBAL_SYMTAB].st_tab, pu);
    }
  }
}


// CreatePUIdMaps: Create id's based on Pro64IRProcIterator. 
void
CreatePUIdMaps(PU_Info* pu_forest, PUToPUIdMap* x, PUIdToPUMap* y)
{
  static UINT nextId = 0; // 0 reserved as NULL
  
  // Enter all PUs
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();    
    
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
  static UINT nextId = 0; // 0 reserved as NULL
  
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
