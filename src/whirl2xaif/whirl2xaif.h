// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.h,v 1.7 2004/02/17 22:24:11 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/whirl2xaif.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef whirl2xaif_h
#define whirl2xaif_h

//************************** System Include Files ***************************

#include <fstream>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include <lib/support/xmlostream.h>  /* xml::ostream, etc */

//************************** Forward Declarations ***************************

//***************************************************************************

namespace whirl2xaif {
  
  extern void 
  TranslateIR(std::ostream& os, PU_Info *pu_forest);
  
}; /* namespace whirl2xaif */

//***************************************************************************

#endif /* whirl2xaif_h */
