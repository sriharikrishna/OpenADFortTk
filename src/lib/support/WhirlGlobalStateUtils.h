// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlGlobalStateUtils.h,v 1.1 2004/01/29 23:17:00 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlGlobalStateUtils.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//
//   A WHIRL PU -- program unit, representing a procedure or function
//   -- is not a self-contained encapsulation.  For example, it does
//   not own its own scoped symbol table; instead, the latter resides
//   in a *global* variable named Scope_tab[].  When working at the
//   intra-procedural level this is not a problem, but when performing
//   inter-procedural tasks it is a great inconvenience.  This is
//   because nodes in the WHIRL tree contain symbol table indices, not
//   pointers.  If the tables in the global Scope_tab[] do not
//   correspond to the current PU, then the WHIRL for that PU contains
//   bogus symbol table indices.  Thus, when writing inter-procedural
//   routines, the global symbol table variables must be *manually
//   set* to point to the correct tables. The following scheme models
//   that used in Open64's inter-procedural analysis.  The main
//   difference and advantage is that it is *separate* from the IPA
//   and can thus be used any time one wishes to work with multiple
//   PUs.
// 
//   The basic scheme is to create a scoped symbol table for each PU
//   and store this in a PU->scope_symbol_table map.  This map is
//   automatically populated by the WHIRL reader.  Although the map
//   can be queried, users will most often prepare the global state
//   for a given pu by calling PU_RestoreGlobalState(pu).
//
//  (Note: It would be preferable to have a PU_Info* store its own
//  lexical scope table.  This would require moderate revisions of
//  Open64, would would clean up some exceedingly ugly code.)
//
//***************************************************************************

#ifndef WhirlGlobalStateUtils_INCLUDED_h
#define WhirlGlobalStateUtils_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>
#include <map>  // STL

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "diagnostics.h"

//************************** Forward Declarations ***************************

class PUToScopedSymTabMap;

// The global map of PU_Info* to lexical scope tables (SCOPE*).  It
// assumes ownership of all scope tables inserted into it.
extern PUToScopedSymTabMap PUToScopeTabMap;

//***************************************************************************

// PU_RestoreGlobalState: Restores all global state for 'pu'.  This
// function may be called as many times as neceessary. 
//   - Current_Map_Tab
//   - Current_pu
//   - CURRENT_SYMTAB
//   - Scope_tab
void
PU_RestoreGlobalState(PU_Info* pu);

//***************************************************************************

namespace WhirlGlobalStateUtils_hidden {

  typedef std::map<PU_Info*, SCOPE*> PUToScopedSymTabBaseMap;


  // Save global state so that it can be restored with
  // PU_RestoreGlobalState().  Assumes that all global state for 'pu'
  // is correctly set.  This should only be called *once* for each PU.
  void
  PU_SaveGlobalState(PU_Info* pu);
  
}; /* namespace WhirlGlobalStateUtils_hidden */


class PUToScopedSymTabMap 
  : public WhirlGlobalStateUtils_hidden::PUToScopedSymTabBaseMap {

public:
  
  PUToScopedSymTabMap();
  ~PUToScopedSymTabMap();
  
  SCOPE*
  Find(PU_Info* pu)
  {
    using namespace WhirlGlobalStateUtils_hidden;

    SCOPE* result = 0;
    
    PUToScopedSymTabBaseMap::iterator it = this->find(pu);
    if (it != this->end()) {
      result = (*it).second;
    }
    
    return result;
  }
  
  void
  Insert(PU_Info* pu, SCOPE* symtab)
  {
    this->insert(make_pair(pu, symtab)); // do not add duplicates!
  }
  
};

//***************************************************************************

#endif /* WhirlGlobalStateUtils_INCLUDED_h */