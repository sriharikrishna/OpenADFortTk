// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIDMaps.h,v 1.5 2003/09/05 21:41:52 eraxxon Exp $

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
#include <map>  // STL
#include <set>  // STL
#include <list> // STL

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

typedef UINT SymTabId;
typedef UINT SymId;
typedef UINT PUId;
typedef UINT WNId;

//***************************************************************************

// A list of ids: Should only be used with scalar id types above
template <class T>
class IdList : public std::list<T> {
public:
  IdList() { }
  ~IdList() { }

  // Returns 0 if not found
  T Find(T id) 
  {
    typename std::list<T>::iterator it;
    for (it = this->begin(); it != this->end(); ++it) {
      T val = *it;
      if (id == val) { return val; }
    }
    return 0;
  }
  
};


//***************************************************************************
// Creation of maps
//***************************************************************************

class SymTabIdToSymTabMap;
class SymTabToSymTabIdMap;

class PUIdToPUMap;
class PUToPUIdMap;

class WNIdToWNMap;
class WNToWNIdMap;

// CreateSymTabIdMaps: Create persistent ID <-> ST_TAB* maps.
// STTABIds are guaranteed to be unique within the PU forest
// 'pu_forest'. (The global symbol table is included.)  The user is
// responsible for freeing the returned maps.
pair<SymTabToSymTabIdMap*, SymTabIdToSymTabMap*>
CreateSymTabIdMaps(PU_Info* pu_forest);

// CreatePUIdMaps: Create persistent ID <-> PU_Info* maps.  PUIds are
// guaranteed to be unique within the PU forest 'pu_forest'.  The user
// is responsible for freeing the returned maps. 
pair<PUToPUIdMap*, PUIdToPUMap*>
CreatePUIdMaps(PU_Info* pu_forest);

// CreateWhirlIDMaps: Create persistent ID <-> WN* maps.  WNIds are
// guaranteed to be unique within the WHIRL tree at 'wn' (usually a
// PU).  The user is responsible for freeing the returned maps.
pair<WNToWNIdMap*, WNIdToWNMap*>
CreateWhirlIdMaps(WN* wn);


//***************************************************************************
// ST_TAB <-> SymTabId maps
//***************************************************************************

namespace SymTabMaps_hidden {
  typedef std::map<ST_TAB*, SymTabId> SymTabToSymTabIdBaseMap;
  typedef std::map<SymTabId, pair<ST_TAB*, PU_Info*> > SymTabIdToSymTabBaseMap;
}; /* namespace SymTabMaps_hidden */


class SymTabToSymTabIdMap : public SymTabMaps_hidden::SymTabToSymTabIdBaseMap {
public:
  
  SymTabToSymTabIdMap() { }
  ~SymTabToSymTabIdMap() { }

  SymTabId
  Find(ST_TAB* wn)
  {
    using namespace SymTabMaps_hidden;

    SymTabId result = 0;
    
    SymTabToSymTabIdBaseMap::iterator it = this->find(wn);
    if (it != this->end()) {
      result = (*it).second;
    }
    
    return result;
  }

  void
  Insert(ST_TAB* stab, SymTabId id)
  {
    this->insert(make_pair(stab, id)); // do not add duplicates!
  }
  
};

// SymTabIdToSymTabMap: In WHIRL, all ST_TAB* are associated with a
// specific PU_Info*, except the global ST_TAB*.  Because of the way
// the symbol table is implemented, it is ually not easy to access the
// symbol table with the ST_TAB*: one needs the corresponding
// PU_Info*.  Consequently, we map a SymTabId to a pair.  When
// entering the global the global ST_TAB* in the map, PU_Info* should
// be NULL.
class SymTabIdToSymTabMap : public SymTabMaps_hidden::SymTabIdToSymTabBaseMap {
public:
  SymTabIdToSymTabMap() { }
  ~SymTabIdToSymTabMap() { }

  pair<ST_TAB*, PU_Info*>
  Find(SymTabId id) 
  {
    using namespace SymTabMaps_hidden;

    pair<ST_TAB*, PU_Info*> result(NULL, NULL);
    
    SymTabIdToSymTabBaseMap::iterator it = this->find(id);
    if (it != this->end()) {
      result = (*it).second;
    }
    
    return result;
  }

  void
  Insert(SymTabId id, ST_TAB* stab, PU_Info* pu)
  {
    this->insert(make_pair(id, make_pair(stab, pu))); // do not add duplicates!
  }
  
};


//***************************************************************************
// ST <-> SymId maps
//***************************************************************************

// Note: Instead of creating ST* <-> to SymId maps, we currently use a
// ST's index -- ST_index(ST*) -- in the symbol table as a persistent
// id.  While this is correct, it would be nice to add an interface
// map, even if the map is really only the identity function without
// any state.


//***************************************************************************
// PU <-> PUId maps
//***************************************************************************

namespace PUMaps_hidden {
  typedef std::map<PU_Info*, PUId> PUToPUIdBaseMap;
  typedef std::map<PUId, PU_Info*> PUIdToPUBaseMap;
}; /* namespace PUMaps_hidden */


class PUToPUIdMap : public PUMaps_hidden::PUToPUIdBaseMap {
public:
  
  PUToPUIdMap() { }
  ~PUToPUIdMap() { }

  PUId
  Find(PU_Info* pu) 
  {
    using namespace PUMaps_hidden;

    PUId result = 0;
    
    PUToPUIdBaseMap::iterator it = this->find(pu);
    if (it != this->end()) {
      result = (*it).second;
    }
    
    return result;
  }

  void
  Insert(PU_Info* pu, PUId id)
  {
    this->insert(make_pair(pu, id)); // do not add duplicates!
  }
  
};

class PUIdToPUMap : public PUMaps_hidden::PUIdToPUBaseMap {
public:
  PUIdToPUMap() { }
  ~PUIdToPUMap() { }

  PU_Info*
  Find(PUId id) 
  {
    using namespace PUMaps_hidden;

    PU_Info* result = NULL;
    
    PUIdToPUBaseMap::iterator it = this->find(id);
    if (it != this->end()) {
      result = (*it).second;
    }
    
    return result;
  }

  void
  Insert(PUId id, PU_Info* pu)
  {
    this->insert(make_pair(id, pu)); // do not add duplicates!
  }
  
};


//***************************************************************************
// WNId <-> WN map
//***************************************************************************

namespace WhirlMaps_hidden {
  typedef std::map<WN*, WNId> WNToWNIdBaseMap;
  typedef std::map<WNId, WN*> WNIdToWNBaseMap;
}; /* namespace WhirlMaps_hidden */


class WNToWNIdMap : public WhirlMaps_hidden::WNToWNIdBaseMap {
public:
  
  WNToWNIdMap() { }
  ~WNToWNIdMap() { }

  WNId
  Find(WN* wn) 
  {
    using namespace WhirlMaps_hidden;

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

class WNIdToWNMap : public WhirlMaps_hidden::WNIdToWNBaseMap {
public:
  WNIdToWNMap() { }
  ~WNIdToWNMap() { }

  WN*
  Find(WNId id) 
  {
    using namespace WhirlMaps_hidden;

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

//***************************************************************************

#endif /* WhirlIDMaps_INLUCDED_h */
