// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMErrorHandler.cxx,v 1.1 2003/08/01 16:41:13 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMErrorHandler.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <iostream>

#include <stdlib.h>
#include <string.h>

//************************* Xerces Include Files ****************************

#include <xercesc/sax/SAXParseException.hpp>

//*************************** User Include Files ****************************

#include "XAIF_DOMErrorHandler.h"

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

//****************************************************************************

void
XAIF_DOMErrorHandler::warning(const SAXParseException&)
{
  // Ignore all warnings.
}

void 
XAIF_DOMErrorHandler::error(const SAXParseException& toCatch)
{
  errors = true;
  cerr << "Error at file \"" << XercesStrX(toCatch.getSystemId())
       << "\", line " << toCatch.getLineNumber()
       << ", column " << toCatch.getColumnNumber()
       << "\n   Message: " << XercesStrX(toCatch.getMessage()) << endl;
}

void 
XAIF_DOMErrorHandler::fatalError(const SAXParseException& toCatch)
{
  errors = true;
  cerr << "Fatal Error at file \"" << XercesStrX(toCatch.getSystemId())
       << "\", line " << toCatch.getLineNumber()
       << ", column " << toCatch.getColumnNumber()
       << "\n   Message: " << XercesStrX(toCatch.getMessage()) << endl;
}

void
XAIF_DOMErrorHandler::resetErrors()
{
  errors = false;
}

