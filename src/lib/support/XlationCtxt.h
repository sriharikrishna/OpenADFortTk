// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/XlationCtxt.h,v 1.2 2003/10/01 16:31:45 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/XlationCtxt.h,v $
//
// Purpose:
//   Represents the context in which translation of WHIRL->XAIF occurs. 
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef XlationCtxt_INCLUDED
#define XlationCtxt_INCLUDED

//************************** System Include Files ***************************

#include <iostream>

#include <inttypes.h>

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// CtxtFlags
//***************************************************************************

// CtxtFlags: represents the current context
class CtxtFlags {
public: 
  CtxtFlags();
  virtual ~CtxtFlags();

  // -------------------------------------------------------
  // Flags for context
  // -------------------------------------------------------

  // Tests to see if *all* of the specified flags are set
  bool AreFlags(uint32_t f) const { return ((flags & f) == f); }
  
  // Tests to see if *any* of the specified flags are set
  bool IsAnyFlag(uint32_t f) const { return (flags & f); }

  void SetFlags(uint32_t f)       { flags = flags | f; }
  void ResetFlags(uint32_t f)     { flags = flags & ~f; }
  
  virtual void Dump(std::ostream& o = std::cerr) const;
  virtual void DDump() const;
  
private:
  uint32_t flags;
  
};

//***************************************************************************

#endif /* XlationCtxt_INCLUDED */
