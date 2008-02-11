#include <iostream>

#include "XAIF_SAXHandler.h"
#include "xaif2whirl.h"

namespace xaif2whirl { 

  XAIF_SAXHandler::XAIF_SAXHandler(PU_Info* pu_forest, const XMLCh* implementationFeatures) :
   myPUForest_p (pu_forest),
   myPUXlationContext ("TranslateIR"),
   myParser_p (xercesc::XMLReaderFactory::createXMLReader()),
   myDOMImplementation_p (xercesc::DOMImplementationRegistry::getDOMImplementation(implementationFeatures)),
   myDOMDocument_p (NULL),
   inDOMMode (false) {
  }

  XAIF_SAXHandler::~XAIF_SAXHandler() {
    delete myParser_p;
    delete myDOMImplementation_p;
  }

  void XAIF_SAXHandler::initialize(bool validateAgainstSchema) {
    xercesc::XMLPlatformUtils::Initialize(); // per process parser init

    //myDOMImplementation_p = xercesc::DOMImplementationRegistry::getDOMImplementation(  X("Core")  );
    //myDOMImplementation_p = xercesc::DOMImplementationRegistry::getDOMImplementation(blerp);

// COPIED FROM XMLParser.cpp
    myParser_p->setFeature(xercesc::XMLUni::fgSAX2CoreValidation,validateAgainstSchema);
    myParser_p->setFeature(xercesc::XMLUni::fgXercesDynamic,false);
    // we need the following for schema processing:
    myParser_p->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces,true);
    myParser_p->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpacePrefixes,true);
    // we need the following to support default values coming from the schema:
    myParser_p->setFeature(xercesc::XMLUni::fgXercesSchema,true);
    myParser_p->setFeature(xercesc::XMLUni::fgXercesSchemaFullChecking,validateAgainstSchema);
//

    // set content and error handlers
    myParser_p->setContentHandler(this);
    static XAIF_SAXErrorHandler anErrorHandler;
    myParser_p->setErrorHandler(&anErrorHandler);

  } // end XAIF_SAXHandler::initialize()

  void XAIF_SAXHandler::parse(std::string theXMLFileName) {
    std::cout << "  -> telling my parser (SAX2XMLReader) to parse file " << theXMLFileName.c_str() << std::endl;
    try {
      myParser_p->parse(theXMLFileName.c_str());
    }
    catch (...) {
      std::cerr << "An error occurred during parsing\n " << std::endl;
    }
  } // end XAIF_SAXHandler::parse()

  void XAIF_SAXHandler::startDocument() {
      std::cout << "    -> entered startDocument" << std::endl;
  }

  void XAIF_SAXHandler::startElement(const XMLCh* const uri,
				     const XMLCh* const localname,
				     const XMLCh* const qname,
				     const xercesc::AttributeList& attrs) {

    std::cout << "  -> Entered startElement(): ";

    if (inDOMMode) {
      std::cout << "  <We are in DOM mode>" << std::endl;
      //if (qname.equals("ControlFlowGraph")) {
	//throw_exception("start of CFG element while already in DOM mode");
      //}

      // create new Element node and add it to the tree
      xercesc::DOMElement* theNewDOMElement = myDOMDocument_p->createElement(qname);
      myElementStack.top()->appendChild(theNewDOMElement);
    } // end DOM mode

    else { // SAX mode
      std::cout << "  <We are in SAX mode>" << std::endl;

      //if (qname.equals("ControlFlowGraph")) {
	inDOMMode = true;

	// create new DOMDocument with root element corresponding to the CFG element
	myDOMDocument_p = myDOMImplementation_p->createDocument(uri,	// root element namespace URI.
								qname,	// root element name
								0);	// document type object (DTD).
	myElementStack.push(myDOMDocument_p->getDocumentElement()); //push current element to the stack
      //}

      //else { // stay in SAX mode
      //}

    } // end SAX mode

  } // end XAIF_SAXHandler::startElement()

  void XAIF_SAXHandler::endElement(const XMLCh* const uri,
				   const XMLCh* const localname,
				   const XMLCh* const qname) {
    if (inDOMMode) {
      myElementStack.pop(); //remove the element from the stack

      //if (localName.equals("ControlFlowGraph")) {
	//if (!myElementStack.empty()) throw_exception ("stack not empty after popping CFG element")
  
	inDOMMode = false;

        // translate the DOM CFG subtree
	TranslateCFG (myPUForest_p, myDOMDocument_p->getDocumentElement(), myPUXlationContext);
	delete myDOMDocument_p;

      //} // end CFG element

    } // end DOM mode
    else { // in SAX mode
      //if (localName.equals("ControlFlowGraph")) {
	//throw_exception ("end of CFG reached while not in DOM mode")
      //}

    } // end SAX mode

  } // end XAIF_SAXHandler::endElement()

  void XAIF_SAXHandler::endDocument() {
      std::cout << "    -> entered endDocument" << std::endl;
  }

} // end namespace xaif2whirl

