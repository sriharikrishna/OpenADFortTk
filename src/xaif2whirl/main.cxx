// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/main.cxx,v 1.2 2003/08/05 20:02:29 eraxxon Exp $

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

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

#include "cmplrs/rcodes.h"  // return codes
#include "config_opt.h"     // Instrumentation_Enabled
#include "config_list.h"    // List_Enabled, etc.
#include "err_host.tab"	    // load all the error messages

#include "file_util.h"	    // New_Extension, Last_Pathname_Component
#include "tracing.h"        // trace routines

//*************************** User Include Files ****************************

#include "xaif2whirl.h"
#include "XAIF_SAXHandler.h"
#include "XAIF_DOMErrorHandler.h"

#include <lib/support/diagnostics.h>
#include <lib/support/WhirlIO.h>
#include <lib/support/XAIFStrings.h>

#include <OpenAnalysis/Utils/Exception.h>

//*************************** Forward Declarations ***************************

using std::cout;
using std::cerr;
using std::endl;


static INT
real_main(INT argc, char **argv);


static int
main_DOM(PU_Info* pu_forest, const char* xaiffilenm);

static int
main_SAX(const char* xaiffilenm);

static int
XercesInit();

static int
XercesFini();

static void
ProcessCommandLine(int argc, char **argv);

//*************************** Forward Declarations ***************************

std::string ProgramName;
std::string WHIRL_filename;
std::string XAIF_filename;

//****************************************************************************


INT
main(INT argc, char **argv)
{
  try {
    return real_main(argc, argv);
  }
  catch (Exception &e /* OpenAnalysis -- should be in namespace */) {
    e.report(cerr);
    exit(1);
  }
  catch (...) {
    cerr << "Unknown exception caught\n";
    exit(1);
  }
  // FIXME: catch badalloc?
}

static INT
real_main(INT argc, char **argv)
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

#ifdef Is_True_On
  if (Get_Trace(TKIND_ALLOC, TP_MISC)) {
    MEM_Tracing_Enable();
  }
#endif
    
  Preconfigure();         // from config.cxx...
  Configure();            // needed for WN_lower!
  Configure_Source(NULL); // Most config variables set here

  Init_Operator_To_Opcode_Table(); // FIXME

  // -------------------------------------------------------
  // 2. Local initialization (options, etc.)
  // -------------------------------------------------------
  Diag_Init();
  Diag_Set_Max_Diags(100); // Maximum 100 warnings by default
  Diag_Set_Phase("XAIF to WHIRL: driver");

  if ( (ret = XercesInit()) != 0 ) { return ret; /* FIXME */ }
  XAIFStrings.XMLInitialize();

  ProcessCommandLine(argc, argv);

  // -------------------------------------------------------
  // 3. Read WHIRL IR as basis for translation
  // -------------------------------------------------------
  PU_Info* pu_forest = ReadIR(WHIRL_filename.c_str());
  PrepareIR(pu_forest); // FIXME (should this be part of translation?)
  
  // -------------------------------------------------------
  // 4. Translate XAIF into WHIRL
  // -------------------------------------------------------  

  cerr << ProgramName << " translates (" << WHIRL_filename << ", "
       << XAIF_filename << ") into " << WHIRL_filename << std::endl;

  main_DOM(pu_forest, XAIF_filename.c_str()); // FIXME check return
  //ret = main_SAX(xmlFile);

  //WriteIR(file.c_str(), pu_forest); 
  
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
ReadXAIF_DOM(const char* xaiffilenm);


static int
main_DOM(PU_Info* pu_forest, const char* xaiffilenm)
{
  int ret = 0;
  
  // 1. Parse XAIF
  XercesDOMParser* parser = ReadXAIF_DOM(xaiffilenm);
  DOMDocument* doc = parser->getDocument();

  // 2. Translate (modify 'pu_forest')
  xaif2whirl::TranslateIR(pu_forest, doc);

  // 3. Cleanup
  delete parser;

  return ret;
}

static XercesDOMParser*
ReadXAIF_DOM(const char* xaiffilenm) 
{
  // 1. Create the parser, and then attach an error handler to the
  // parser.  
  XercesDOMParser* parser = new XercesDOMParser;

  //FIXME: parser->setValidationScheme(XercesDOMParser::Val_Always);
  parser->setDoNamespaces(true);
  parser->setDoSchema(true);
  //FIXME: parser->setValidationSchemaFullChecking(true);
  //parser->setCreateEntityReferenceNodes(true);
  
  XAIF_DOMErrorHandler* errHandler = new XAIF_DOMErrorHandler();
  parser->setErrorHandler(errHandler);
  
  // 2. Parse the XML file, catching any XML exceptions that might propogate
  // out of it.
  bool errorsOccured = false;
  try {
    parser->parse(xaiffilenm);
  }
  
  catch (const XMLException& e) {
    cerr << "An error occurred during parsing\n   Message: "
	 << XercesStrX(e.getMessage()) << endl;
    errorsOccured = true;
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
  catch (...) {
    cerr << "An error occurred during parsing\n " << endl;
    errorsOccured = true;
  }
  
  return parser;
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


//***************************************************************************
// from be/be/driver_util.c (FIXME: convert to getopts)
//***************************************************************************

/* Default file	extensions: */
#define IRB_FILE_EXTENSION ".B"	    /* WHIRL file */

// ProcessCommandLine: Process the command line arguments. Evaluate
// all flags and set up global options.
//
// Note: Src_File_Name, Irb_File_Name, Obj_File_Name are globals
static void
ProcessCommandLine(int argc, char **argv)
{
  ProgramName = Last_Pathname_Component(argv[0]);

  /* Check the command line flags: */
  INT Src_Count = 0;
  BOOL dashdash_flag = FALSE;
  char* opt;
  
  for (INT16 i = 1; i < argc; i++) {
    // -------------------------------------------------------
    // A '--' signifies no more options
    // -------------------------------------------------------
    if (argv[i] != NULL && (strcmp(argv[i], "--") == 0)) {
      dashdash_flag = TRUE;
      continue;
    }
    
    if ( !dashdash_flag && argv[i] != NULL && *(argv[i]) == '-' ) {
      // -------------------------------------------------------
      // An option (beginning with '-')
      // -------------------------------------------------------
      opt = argv[i]+1; // points to option name, skipping '-'
      
    } else if (argv[i] != NULL) {
      // -------------------------------------------------------
      // A non-option or immediately after a '--'
      // -------------------------------------------------------
      dashdash_flag = FALSE;
      if (i+1 < argc) { 
	WHIRL_filename = argv[i];
	XAIF_filename = argv[++i];
	break;
      }
    } 
  }

  if ( !(WHIRL_filename.length() > 0 && XAIF_filename.length() > 0) ) {
    ErrMsg(EC_No_Sources);
    exit(RC_USER_ERROR); // FIXME: return error
  }
  
  Irb_File_Name = (char*)WHIRL_filename.c_str(); // make Open64 happy
}
