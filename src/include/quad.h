// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/include/quad.h,v 1.1 2005/01/07 18:54:06 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/include/quad.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef FortTk_quad_INCLUDED
#define FortTk_quad_INCLUDED

//************************* System Include Files ****************************

//*************************** User Include Files ****************************

//************************** Open64 Include Files ***************************

#include <../../common/com/targ_const.h> // QUAD_TYPE

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

namespace FortTk {

  // Used to translate the bits within TCONs. We can safely assume 64
  // bit values are available on modern platforms.  This is used
  // simply to convey bits, so we are not concerned with little/big
  // endian issues.
  struct uint128_t {
    
    uint128_t() : hi(0), lo(0) { }
    ~uint128_t() { }
    
    uint128_t(uint128_t& v) : hi(v.hi), lo(v.lo) { }
    uint128_t(QUAD_TYPE& v) { *this = v; }
    
    uint64_t hi;
    uint64_t lo;
  };
  
  inline uint128_t& 
  assign(uint128_t& qd1, QUAD_TYPE& qd2) {
    qd1.hi = *( ((uint64_t*)&qd2) + 1 ); // high 64 bits
    qd1.lo = *( (uint64_t*)&qd2 );       // low 64 bits
    return qd1;
  }
  
  inline QUAD_TYPE& 
  assign(QUAD_TYPE& qd1, uint128_t& qd2) {
    *( ((uint64_t*)&qd1) + 1 ) = qd2.hi; // high 64 bits
    *( (uint64_t*)&qd1 )       = qd2.lo; // low 64 bits
    return qd1;
  }

}; /* namespace FortTk */

//***************************************************************************

#endif
