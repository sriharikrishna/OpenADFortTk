// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/main.cxx,v 1.25 2005/11/01 23:28:48 utke Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/main.cxx,v $
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
#include <string>

//************************* Xerces Include Files ****************************

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>

// SAX
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>

// DOM
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

#include "cmplrs/rcodes.h"  // return codes
#include "tracing.h"        // trace routines
#include "ir_reader.h"      // fdump_tree
#include "wn_simp.h"        // WN_Simplifier_Enable()

//************************ OpenAnalysis Include Files ***********************

#include <OpenAnalysis/Utils/Exception.hpp>

//*************************** User Include Files ****************************

#include "Args.h"
#include "xaif2whirl.h"
#include "XAIF_SAXHandler.h"
#include "XAIF_DOMErrorHandler.h"

#include <lib/support/Exception.h>
#include <lib/support/WhirlIO.h>
#include <lib/support/XAIFStrings.h>

//*************************** Forward Declarations ***************************

using std::cout;
using std::cerr;
using std::endl;


static int
real_main(int argc, char **argv);


static int
main_DOM(PU_Info* pu_forest, const char* xaiffilenm, bool validate);

static int
main_SAX(const char* xaiffilenm);

static int
XercesInit();

static int
XercesFini();

//*************************** Forward Declarations ***************************

// Options (FIXME)
xaif2whirl::ModeType      opt_mode      = xaif2whirl::MODE_NULL;
xaif2whirl::AlgorithmType opt_algorithm = xaif2whirl::ALG_NULL;

//****************************************************************************


int
main(int argc, char **argv)
{
  try {
    return real_main(argc, argv);
  }
  catch (CmdLineParser::Exception& e) {
    e.Report(cerr); // fatal error
    exit(1);
  }
  catch (FortTk::BaseException& e) {
    e.Report(cerr);
    exit(1);
  }
  catch (OA::Exception &e) {
    e.report(cerr);
    exit(1);
  }
  catch (...) {
    cerr << "Unknown exception caught\n";
    exit(1);
  }
  // FIXME: catch badalloc?
}

static int
real_main(int argc, char **argv)
{
  int ret;

  // -------------------------------------------------------
  // 1. Open64 Initialization
  // -------------------------------------------------------
  Handle_Signals();
  MEM_Initialize();
  Init_Error_Handler( 100 );
  Set_Error_Line( ERROR_LINE_UNKNOWN );
  Set_Error_File( NULL );
  Set_Error_Phase("xaif2whirl");
  IR_set_dump_order(TRUE /*pre*/); // pre-order trees when debugging, please!
  
#ifdef Is_True_On
  if (Get_Trace(TKIND_ALLOC, TP_MISC)) {
    MEM_Tracing_Enable();
  }
#endif
    
  Preconfigure();         // from config.cxx...
  Configure();            // needed for WN_lower!
  Configure_Source(NULL); // Most config variables set here
  
  WN_Simplifier_Enable(FALSE); // turn off WHIRL expression simplifier
  Init_Operator_To_Opcode_Table(); // FIXME

  // -------------------------------------------------------
  // 2. Local initialization (options, etc.)
  // -------------------------------------------------------
  Diag_Init();
  Diag_Set_Max_Diags(100); // Maximum 100 warnings by default
  Diag_Set_Phase("XAIF to WHIRL: driver");

  if ( (ret = XercesInit()) != 0 ) { return ret; /* FIXME */ }
  XAIFStrings.XMLInitialize();

  Args args(argc, argv);
  opt_mode = args.mode; // FIXME
  opt_algorithm = args.algorithm; // FIXME
  FortTk_SetDiagnosticFilterLevel(args.debug);
  
  // -------------------------------------------------------
  // 3. Read WHIRL IR as basis for translation
  // -------------------------------------------------------
  PU_Info* pu_forest = ReadIR(args.inWhirlFileNm.c_str());
  PrepareIR(pu_forest); // FIXME (should this be part of translation?)
  
  // -------------------------------------------------------
  // 4. Translate XAIF into WHIRL
  // -------------------------------------------------------  
  
  ret = main_DOM(pu_forest, args.xaifFileNm.c_str(),args.validate); // FIXME check return
  //ret = main_SAX(xaifFileNm.c_str());

  WriteIR(args.outWhirlFileNm.c_str(), pu_forest);
  //FreeIR(pu_forest);
  
  // -------------------------------------------------------
  // 5. Finalization
  // -------------------------------------------------------

  if ( (ret = XercesFini()) != 0 ) { return ret; /* FIXME */ }

  // If we've seen errors, note them and terminate
  INT local_ecount, local_wcount;
  if ( Get_Error_Count ( &local_ecount, &local_wcount ) ) {
    Terminate(Had_Internal_Error() ? RC_INTERNAL_ERROR : 
              RC_NORECOVER_USER_ERROR);
  }

  Diag_Exit();
  Cleanup_Files(TRUE, FALSE); // Open64

  return RC_OKAY;
}


//****************************************************************************

static XercesDOMParser*
ReadXAIF_DOM(const char* xaiffilenm, bool validate);


static int
main_DOM(PU_Info* pu_forest, const char* xaiffilenm, bool validate)
{
  int ret = 0;
  
  // 1. Parse XAIF
  XercesDOMParser* parser = ReadXAIF_DOM(xaiffilenm,validate);
  DOMDocument* doc = parser->getDocument();

  // 2. Translate (modify 'pu_forest')
  xaif2whirl::TranslateIR(pu_forest, doc);

  // 3. Cleanup
  delete parser;

  return ret;
}

static XercesDOMParser*
ReadXAIF_DOM(const char* xaiffilenm, bool validate) 
{
  // 1. Create the parser, and then attach an error handler to the
  // parser.  
  XercesDOMParser* parser = new XercesDOMParser;

  if (validate) { 
    parser->setValidationScheme(XercesDOMParser::Val_Always);
    parser->setValidationSchemaFullChecking(true);
  }
  else { 
    parser->setValidationScheme(XercesDOMParser::Val_Never);
    parser->setValidationSchemaFullChecking(false);
  }
  parser->setDoNamespaces(true);
  parser->setDoSchema(true);
  parser->setCreateEntityReferenceNodes(false);
  
  XAIF_DOMErrorHandler* errHandler = new XAIF_DOMErrorHandler();
  parser->setErrorHandler(errHandler);
  
  // 2. Parse the XML file, catching any XML exceptions that might propogate
  // out of it.
  bool errorsOccured = false;
  try {
    parser->parse(xaiffilenm);
  }
  catch (const DOMException& e) {
    const unsigned int maxChars = 2047;
    XMLCh errText[maxChars + 1];
    
    cerr << "\nDOM Error during parsing: '" << xaiffilenm << "'\n"
         << "DOMException code is:  " << e.code << endl;
    
    if (DOMImplementation::loadDOMExceptionMsg(e.code, errText, maxChars))
      cerr << "Message is: " << XercesStrX(errText) << endl;
    
    errorsOccured = true;
  }
  catch (const XMLException& e) {
    cerr << "An error occurred during parsing\n   Message: "
         << XercesStrX(e.getMessage()) << endl;
    errorsOccured = true;
  }
  catch (...) {
    cerr << "An error occurred during parsing\n " << endl;
    errorsOccured = true;
  }
  FORTTK_ASSERT(!errorsOccured, "Parse Error.");
  
  return parser;
}


// Print the DOM IR
static void
PrintIR_DOM(DOMDocument* doc)
{
  DOMNodeIterator* it = 
    doc->createNodeIterator(doc, DOMNodeFilter::SHOW_ELEMENT, NULL, true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    // XercesStrX::DDumpXMLStr(node->getNodeName());
    cout << XercesStrX(node->getNodeName()) << endl;
  }
  it->release();
}

//****************************************************************************

static int 
ReadXIAF_SAX(const char* xaiffilenm);


static int
main_SAX(const char* xaiffilenm)
{
  int ret = ReadXIAF_SAX(xaiffilenm);
  return ret;
}

static int 
ReadXIAF_SAX(const char* xaiffilenm) 
{
  // 1. Create a SAX parser object and set parsing options.
  SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
  
  parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
  //parser->setFeature(XMLUni::fgXercesDynamic, true);
  parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);
  parser->setFeature(XMLUni::fgXercesSchema, true);
  parser->setFeature(XMLUni::fgXercesSchemaFullChecking, true);
  parser->setFeature(XMLUni::fgSAX2CoreNameSpacePrefixes, true);
  
  // 2. Create the handler object and install it as the document and
  // error handler for the parser. Then parse the file and catch any
  // exceptions that propogate out
  int errorCount = 0;
  try {
    XAIF_SAXHandler XAIFhandler;
    parser->setContentHandler(&XAIFhandler);
    parser->setErrorHandler(&XAIFhandler);
    parser->parse(xaiffilenm);
    errorCount = parser->getErrorCount();
  }
  catch (const XMLException& toCatch) {
    cerr << "Error: XAIF processing error:\n"
         << "\t" << XercesStrX(toCatch.getMessage()) << endl;
    // FIXME: do we have to call terminate here?
  }

  // 3. Cleanup
  delete parser;  
  
  return ((errorCount > 0) ? 4 : 0);
}

//****************************************************************************

static int
XercesInit() 
{
  // Initialize the XML4C2 system
  try {
    XMLPlatformUtils::Initialize();
  }
  catch (const XMLException& toCatch) {
    cerr << "Error: unable to initialize XAIF processor!:\n"
         << "\t" << XercesStrX(toCatch.getMessage()) << endl;
    return 1;
  }

  return 0;
}

static int
XercesFini()
{
  // Terminate the XML4C2 system
  XMLPlatformUtils::Terminate();
  return 0;
}

//****************************************************************************
