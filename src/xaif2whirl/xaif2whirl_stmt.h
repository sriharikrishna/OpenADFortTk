// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_stmt.h,v 1.1 2003/09/17 19:42:16 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_stmt.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef xaif2whirl_stmt_INCLUDED_h
#define xaif2whirl_stmt_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>

//************************* Xerces Include Files ****************************

#include <xercesc/dom/DOMDocument.hpp>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "XlationContext.h"

//*************************** Forward Declarations ***************************

XERCES_CPP_NAMESPACE_USE

//****************************************************************************

namespace xaif2whirl {

// Note: These functions should only be called when 'ctxt' is properly
// initialized!

WN* 
TranslateStmt(DOMElement* stmt, XlationContext& ctxt); 
 
WN*
PatchWNStmt(WN* wn, XlationContext& ctxt);

}; /* namespace xaif2whirl */

//***************************************************************************

#endif // xaif2whirl_stmt_INCLUDED_h
