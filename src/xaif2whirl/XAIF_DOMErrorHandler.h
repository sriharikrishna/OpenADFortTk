// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMErrorHandler.h,v 1.1 2003/08/01 16:41:13 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMErrorHandler.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef XAIF_DOMErrorHandler_INCLUDED_h
#define XAIF_DOMErrorHandler_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>

//************************* Xerces Include Files ****************************

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/sax/ErrorHandler.hpp>

//*************************** User Include Files ****************************

#include "XercesStrX.h"

//*************************** Forward Declarations ***************************

//****************************************************************************

XERCES_CPP_NAMESPACE_USE

class XAIF_DOMErrorHandler : public ErrorHandler
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  XAIF_DOMErrorHandler() 
    : errors(false) { }
  
  ~XAIF_DOMErrorHandler() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the error handler interface
  // -----------------------------------------------------------------------
  void warning(const SAXParseException& toCatch);
  void error(const SAXParseException& toCatch);
  void fatalError(const SAXParseException& toCatch);
  void resetErrors();

  // -----------------------------------------------------------------------
  //  Getter methods
  // -----------------------------------------------------------------------
  bool getErrors() const { return errors; }
  
private:
  bool errors; // Set if we find any errors
};

//***************************************************************************

#endif // XAIF_DOMErrorHandler_INCLUDED_h
