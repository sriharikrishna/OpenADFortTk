// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIDMaps.h,v 1.1 2003/08/01 15:59:36 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIDMaps.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef WhirlIDMaps_INCLUDED_h
#define WhirlIDMaps_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>
#include <map> // STL
#include <set> // STL

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

typedef UINT WNId;

typedef std::set<WNId> WNIdSet;

namespace WhirlIDMaps_hidden {
  typedef std::map<WNId, WN*> WNIdToWNBaseMap;
  typedef std::map<WN*, WNId> WNToWNIdBaseMap;
}; /* namespace WhirlIDMaps_hidden */

//***************************************************************************
// 
//***************************************************************************

// ---------------------------------------------------------
// WNIdToWNMap
// ---------------------------------------------------------

class WNIdToWNMap : public WhirlIDMaps_hidden::WNIdToWNBaseMap {
public:
  WNIdToWNMap() { }
  ~WNIdToWNMap() { }

  WN*
  Find(WNId id) 
  {
    using namespace WhirlIDMaps_hidden;

    WN* result = NULL;
    
    WNIdToWNBaseMap::iterator it = this->find(id);
    if (it != this->end()) {
      result = (*it).second;
    }
    
    return result;
  }

  void
  Insert(WNId id, WN* wn)
  {
    this->insert(make_pair(id, wn)); // do not add duplicates!
  }
  
};


class WNToWNIdMap : public WhirlIDMaps_hidden::WNToWNIdBaseMap {
public:
  
  WNToWNIdMap() { }
  ~WNToWNIdMap() { }

  WNId
  Find(WN* wn) 
  {
    using namespace WhirlIDMaps_hidden;

    WNId result = 0;
    
    WNToWNIdBaseMap::iterator it = this->find(wn);
    if (it != this->end()) {
      result = (*it).second;
    }
    
    return result;
  }

  void
  Insert(WN* wn, WNId id)
  {
    this->insert(make_pair(wn, id)); // do not add duplicates!
  }
  
};


//***************************************************************************
// 
//***************************************************************************

// CreateWhirlIDMaps: Create persistent ID <-> WN* maps.  IDs are
// guaranteed to be unique within the PU.  The user is responsible for
// freeing the returned maps.
pair<WNIdToWNMap*, WNToWNIdMap*> 
CreateWhirlIDMaps(WN* wn);

//***************************************************************************

#endif /* WhirlIDMaps_INLUCDED_h */
