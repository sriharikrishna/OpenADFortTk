// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/XAIF_SAXHandler.h,v 1.1 2003/08/01 16:41:13 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/XAIF_SAXHandler.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef XAIF_SAXHandler_INCLUDED_h
#define XAIF_SAXHandler_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>

//************************* Xerces Include Files ****************************

#include <xercesc/sax2/DefaultHandler.hpp>

//*************************** User Include Files ****************************

#include "XercesStrX.h"

//*************************** Forward Declarations ***************************

//****************************************************************************

XERCES_CPP_NAMESPACE_USE
//XERCES_CPP_NAMESPACE::

class XAIF_SAXHandler : public DefaultHandler
{
public:
  // -----------------------------------------------------------------------
  // Constructors and Destructor
  // -----------------------------------------------------------------------
  XAIF_SAXHandler();
  ~XAIF_SAXHandler();
  
  // -----------------------------------------------------------------------
  // Implementations of the SAX DocumentHandler interface
  // -----------------------------------------------------------------------
  void startDocument();  
  void endDocument();

  // uri: universal resource id string 
  // localname: unqualified element name
  // qname: qualified element name
  // attributes: attribute list
  void startElement(const XMLCh* const uri,
		    const XMLCh* const localname,
		    const XMLCh* const qname,
		    const Attributes& attributes);

  void endElement(const XMLCh* const uri,
		  const XMLCh* const localname,
		  const XMLCh* const qname);
  
  void characters(const XMLCh* const chars, 
		  const unsigned int length);
  
  void ignorableWhitespace(const XMLCh* const chars, 
			   const unsigned int length);
  
  void processingInstruction(const XMLCh* const target, 
			     const XMLCh* const data);

  // -----------------------------------------------------------------------
  // Implementations of the SAX ErrorHandler interface
  // -----------------------------------------------------------------------
  void warning(const SAXParseException& exception);
  void error(const SAXParseException& exception);
  void fatalError(const SAXParseException& exception);
  
  // -----------------------------------------------------------------------
  // Implementation of the SAX DTDHandler interface
  // -----------------------------------------------------------------------
  void notationDecl(const XMLCh* const name,
		    const XMLCh* const publicId,
		    const XMLCh* const systemId);

  void unparsedEntityDecl(const XMLCh* const name,
			  const XMLCh* const publicId,
			  const XMLCh* const systemId,
			  const XMLCh* const notationName);
  
private:

  // For debugging output:
  void IndentIncr() { indentAmnt += indentStep; }
  void IndentDecr() { indentAmnt -= indentStep; }
  void Indent(std::ostream& os);

private:
  // used for printing out elements
  int indentAmnt;
  int indentStep;
};

//***************************************************************************

#endif // XAIF_SAXHandler_INCLUDED_h
