// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/XAIF_SAXHandler.cxx,v 1.1 2003/08/01 16:41:13 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/XAIF_SAXHandler.cxx,v $
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

//************************* Xerces Include Files ****************************

#include <xercesc/util/XMLUniDefs.hpp>
#include <xercesc/sax2/Attributes.hpp>

//*************************** User Include Files ****************************

#include "XAIF_SAXHandler.h"

//*************************** Forward Declarations ***************************

using std::cout;
using std::cerr;
using std::endl;

//****************************************************************************


// ---------------------------------------------------------------------------
// XAIF_SAXHandler: Constructors and Destructor
// ---------------------------------------------------------------------------

XAIF_SAXHandler::XAIF_SAXHandler()
  : indentAmnt(0), indentStep(2)
{
}

XAIF_SAXHandler::~XAIF_SAXHandler()
{
}


// ---------------------------------------------------------------------------
// XAIF_SAXHandler: Overrides of the SAX DocumentHandler interface
// ---------------------------------------------------------------------------

void 
XAIF_SAXHandler::startDocument()
{
}

void 
XAIF_SAXHandler::endDocument()
{
}

void 
XAIF_SAXHandler::startElement(const XMLCh* const uri,
			      const XMLCh* const localname,
			      const XMLCh* const qname,
			      const Attributes& attributes)
{
  //if (XMLString::equals(localname, elemProfile)) {
  Indent(cout);
  cout << "<" << XercesStrX(qname) << ">" << endl;
  IndentIncr();
}


void
XAIF_SAXHandler::endElement(const XMLCh* const uri,
			    const XMLCh* const localname,
			    const XMLCh* const qname)
{
  IndentDecr();
  Indent(cout);
  cout << "</" << XercesStrX(qname) << ">" << endl;
}


void 
XAIF_SAXHandler::characters(const XMLCh* const chars, 
			    const unsigned int length)
{

}


void 
XAIF_SAXHandler::ignorableWhitespace(const XMLCh* const chars,
				     const unsigned int length)
{

}


void 
XAIF_SAXHandler::processingInstruction(const XMLCh* const target,
				       const XMLCh* const data)
{

}


// ---------------------------------------------------------------------------
// XAIF_SAXHandler: Overrides of the SAX ErrorHandler interface
// ---------------------------------------------------------------------------

void 
XAIF_SAXHandler::error(const SAXParseException& e)
{
  cerr << "\nError at file " << XercesStrX(e.getSystemId())
       << ", line " << e.getLineNumber()
       << ", char " << e.getColumnNumber()
       << "\n  Message: " << XercesStrX(e.getMessage()) << endl;
}

void 
XAIF_SAXHandler::fatalError(const SAXParseException& e)
{
  cerr << "\nFatal Error at file " << XercesStrX(e.getSystemId())
       << ", line " << e.getLineNumber()
       << ", char " << e.getColumnNumber()
       << "\n  Message: " << XercesStrX(e.getMessage()) << endl;
}

void 
XAIF_SAXHandler::warning(const SAXParseException& e)
{
  cerr << "\nWarning at file " << XercesStrX(e.getSystemId())
       << ", line " << e.getLineNumber()
       << ", char " << e.getColumnNumber()
       << "\n  Message: " << XercesStrX(e.getMessage()) << endl;
}


// ---------------------------------------------------------------------------
// XAIF_SAXHandler: Overrides of the SAX DTDHandler interface
// ---------------------------------------------------------------------------

void 
XAIF_SAXHandler::unparsedEntityDecl(const XMLCh* const name, 
					 const XMLCh* const publicId,
					 const XMLCh* const systemId,
					 const XMLCh* const notationName)
{
  // Not used at this time
}


void 
XAIF_SAXHandler::notationDecl(const XMLCh* const name, 
			      const XMLCh* const publicId, 
			      const XMLCh* const systemId)
{
  // Not used at this time
}

// ---------------------------------------------------------------------------
//
// ---------------------------------------------------------------------------

void 
XAIF_SAXHandler::Indent(std::ostream& os)
{
  for (int i = 0; i < indentAmnt; ++i) {
    os << ' ';
  }
}


