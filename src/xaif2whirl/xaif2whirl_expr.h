// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_expr.h,v 1.2 2003/09/18 19:18:12 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_expr.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef xaif2whirl_expr_INCLUDED_h
#define xaif2whirl_expr_INCLUDED_h

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
TranslateExpression(const DOMElement* elem, XlationContext& ctxt);

WN*
TranslateVarRef(const DOMElement* elem, XlationContext& ctxt);

WN*
PatchWNExpr(WN* parent, INT kidno, XlationContext& ctxt);
 
}; /* namespace xaif2whirl */

//***************************************************************************

#endif // xaif2whirl_expr_INCLUDED_h
