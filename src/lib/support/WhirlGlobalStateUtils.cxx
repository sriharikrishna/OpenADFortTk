// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlGlobalStateUtils.cxx,v 1.1 2004/01/29 23:17:00 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlGlobalStateUtils.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <cassert>

//*************************** User Include Files ****************************

#include "WhirlGlobalStateUtils.h"

#include "diagnostics.h"

//************************** Forward Declarations ***************************

//***************************************************************************

PUToScopedSymTabMap PUToScopeTabMap;

//***************************************************************************

// PU_RestoreGlobalState: 
void
PU_RestoreGlobalState(PU_Info* pu)
{
  // 'pu' must be in memory (change some global pointers around)
  assert(PU_Info_state(pu, WT_TREE) == Subsect_InMem); // Subsect_Written?
  Current_Map_Tab = PU_Info_maptab(pu);
  Current_pu = &PU_Info_pu(pu);
  CURRENT_SYMTAB = PU_lexical_level(*Current_pu);
  Scope_tab = PUToScopeTabMap.Find(pu);
  assert(Scope_tab);
}

//***************************************************************************

// PU_SaveGlobalState: <see header comments>
//
// The only state we need to save is the lexical scope table (SCOPE*).
// We do this by creating a copy of the lexical table for each PU.
// Each lexical table contains several pointers to the various tables
// the comprise the symbols tables.  Because the pointers are simply
// copied, THE ACTUAL ST TABLES MAY BE SHARED; THEY ARE NOT
// DUPLICATED.  The global symbol table will be shared accros all PUs;
// nested PUs will share symbol tables from the outer scopes.
//
// N.B. This function will likely create a small memory leak.  Because
// each PU will be given its own lexical table, there will be no owner
// for the lexical table created in Initialize_Symbol_Tables().
//
// See the following:
//   ipa/main/analyze/ipa_cg.cxx :
//     read_pu_including_parents(..)
//     IPA_NODE::Scope(..)
//     IPA_NODE::Set_Scope(..)
//   be/com/clone.cxx
//     IPO_SYMTAB::New_Symtab(..)
void
WhirlGlobalStateUtils_hidden::PU_SaveGlobalState(PU_Info* pu)
{
  // We assume that the global state has already been properly prepared.

  // Create a scope table large enough for this lexical level and
  // insert it into the map. Note: we intentionally do not set
  // 'Scope_tab' to this copy in order to stave off the likely memory
  // leak as long as possible.
  INT size = (PU_lexical_level(*Current_pu) + 1) * sizeof(SCOPE);
  SCOPE* new_scope_tab = (SCOPE*)MEM_POOL_Alloc(Malloc_Mem_Pool, size);
  memcpy(new_scope_tab, Scope_tab, size);
  PUToScopeTabMap.Insert(pu, new_scope_tab);
}

//***************************************************************************

PUToScopedSymTabMap::PUToScopedSymTabMap() 
{ 
}

PUToScopedSymTabMap::~PUToScopedSymTabMap() 
{
  using namespace WhirlGlobalStateUtils_hidden;
  
  for (PUToScopedSymTabBaseMap::iterator it = this->begin();
       it != this->end(); ++it) {
    SCOPE* scopetab = (*it).second;
    MEM_POOL_FREE(Malloc_Mem_Pool, scopetab);
  }
}

//***************************************************************************

#if 0

// The following were the former versions of these functions.  The
// user called Restore before using a pu and Save after using it.  If
// this was not strictly followed very bad things could happen because
// only the local symbol table was saved, using a gross hack.  I
// couldn't get it to handle nested PUs.  

// When using multiple PUs at a time, this should be called to
// prepare the global symbol table pointers the current PU.
void 
RestoreOpen64PUGlobalVars(PU_Info* pu);

// When using multiple PUs at a time, this should be called to save
// the global symbol table pointer for later use.
void
SaveOpen64PUGlobalVars(PU_Info* pu);



// cf. wn_mp.cxx 1278 ; dra_clone.cxx:974
// PU_Info_symtab_ptr(pu)

// (PU_lexical_level (&St_Table[PU_Info_proc_sym (pu)]))
// Scope_tab[CURRENT_SYMTAB].st = WN_get_proc_sym(pu);

// Callgraph: ipa_cg.cxx (1053)

void 
RestoreOpen64PUGlobalVars(PU_Info* pu)
{
  ST_IDX st = PU_Info_proc_sym(pu);
  DBGMSG(2, "** Restoring Open64 global vars for '%s' **", ST_name(st));
  
  // The PU is in memory (change some global pointers around)
  assert(PU_Info_state(pu, WT_TREE) == Subsect_InMem);
  Current_Map_Tab = PU_Info_maptab(pu);
  Current_pu = &PU_Info_pu(pu);
  CURRENT_SYMTAB = PU_lexical_level(*Current_pu);
  
  Restore_Local_Symtab(pu);
  // Can we make this restore itself and all its parents?
}

void
SaveOpen64PUGlobalVars(PU_Info* pu)
{
  ST_IDX st = PU_Info_proc_sym(pu);
  DBGMSG(2, "** Saving Open64 global vars for '%s' **", ST_name(st));
  
  Set_PU_Info_symtab_ptr(pu, NULL);
  Save_Local_Symtab(CURRENT_SYMTAB, pu);
  // Can we make this save itself and all its parents?
}

#endif

//***************************************************************************
