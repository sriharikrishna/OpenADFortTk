// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/BaseMap.h,v 1.2 2004/06/30 23:45:00 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/BaseMap.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef BaseMap_H 
#define BaseMap_H

//************************** System Include Files ***************************

#include <map>

//*************************** User Include Files ****************************

#include "diagnostics.h"

//************************** Forward Declarations ***************************

//***************************************************************************
// BaseMap
//***************************************************************************

namespace FortTk {

// BaseMap: abstract map routines
// Note: FromTy and ToTy should be pointers (or unsigned integers)!
template <class FromTy, class ToTy>
class BaseMap : public std::map<FromTy, ToTy>
{
public:
  BaseMap() { }
  virtual ~BaseMap() { }
  
  // Find: Given x, find y if x --> y.
  virtual ToTy 
  Find(const FromTy x, bool mustFind = false) const
  {
    typename std::map<FromTy, ToTy>::const_iterator it = find(x);
    ToTy y = (it == end()) ? 0 /*NULL*/ : (*it).second;
    
    if (mustFind && y == 0 /*NULL*/) {
      ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Could not find entry!"));
    }
    
    return y;
  }
  
  // Insert: insert the <x,y> pair in the map and return true; if
  // x is already a member, the operation fails and returns false.
  virtual bool 
  Insert(FromTy x, ToTy y) {
    pair<typename std::map<FromTy, ToTy>::iterator, bool> p = 
      insert(make_pair(x, y)); // std::map<FromTy, ToTy>::value_type
    return p.second;
  }
  
  // Dump: Dump that integer values in the map
  virtual void Dump(std::ostream& o = std::cerr) const {
    o << "{ Map:\n";
    for (typename std::map<FromTy, ToTy>::const_iterator it = begin(); 
	 it != end(); ++it) {
      o << "(" << it->first << " --> " << it->second << ")\n";
    }
    o << "}\n";
    o.flush();
  }
  
  virtual void DDump() const {
    Dump(std::cerr);
  }

protected:
};

} // FortTk

//***************************************************************************

#endif 
