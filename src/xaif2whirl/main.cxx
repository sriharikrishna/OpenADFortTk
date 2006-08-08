// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/main.cxx,v 1.28 2006/05/12 16:12:24 utke Exp $

#include <iostream>
#include <string>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/TransService.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/dom/DOMBuilder.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMException.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMNodeIterator.hpp>

#include <OpenAnalysis/Utils/Exception.hpp>

#include "Open64IRInterface/Open64BasicTypes.h"
#include "cmplrs/rcodes.h"  // return codes
#include "tracing.h"        // trace routines
#include "ir_reader.h"      // fdump_tree
#include "wn_simp.h"        // WN_Simplifier_Enable()
#include "Open64IRInterface/diagnostics.h"

#include <Exception.h>
#include "Open64IRInterface/WhirlIO.h"
#include <XAIFStrings.h>
#include "Args.h"
#include "xaif2whirl.h"
#include "XAIF_DOMErrorHandler.h"
#include "XercesStrX.h"

namespace xaif2whirl { 

  static int
  real_main(int argc, char **argv);


}

int main(int argc, char **argv) {
  try {
    return xaif2whirl::real_main(argc, argv);
  }
  catch (CmdLineParser::Exception& e) {
    e.Report(cerr); // fatal error
    exit(1);
  }
  catch (fortTkSupport::BaseException& e) {
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

namespace xaif2whirl { 

  static int
  main_DOM(PU_Info* pu_forest, const char* xaiffilenm, bool validate);

  static int
  XercesInit();

  static int
  XercesFini();

  ModeType      opt_mode      = MODE_NULL;
  AlgorithmType opt_algorithm = ALG_NULL;

  static int
  real_main(int argc, char **argv) {
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
    fortTkSupport::Diagnostics::setDiagnosticFilterLevel(args.debug);
  
    // -------------------------------------------------------
    // 3. Read WHIRL IR as basis for translation
    // -------------------------------------------------------
    PU_Info* pu_forest = ReadIR(args.inWhirlFileNm.c_str());
    PrepareIR(pu_forest); // FIXME (should this be part of translation?)
  
    // -------------------------------------------------------
    // 4. Translate XAIF into WHIRL
    // -------------------------------------------------------  
  
    ret = main_DOM(pu_forest, args.xaifFileNm.c_str(),args.validate); // FIXME check return

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
    FORTTK_MSG(1, "progress: parsing input XAIF");
    // 1. Parse XAIF
    XercesDOMParser* parser = ReadXAIF_DOM(xaiffilenm,validate);
    DOMDocument* doc = parser->getDocument();

    FORTTK_MSG(1, "progress: translating to WHIRL");
    // 2. Translate (modify 'pu_forest')
    TranslateIR(pu_forest, doc);

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

    parser->setValidationScheme(XercesDOMParser::Val_Always);
    if (validate) { 
      //parser->setValidationScheme(XercesDOMParser::Val_Always);
      FORTTK_MSG(1, "progress: parsing with schema validation");
      parser->setValidationSchemaFullChecking(true);
    }
    else {
      // it appears there is a bug in the parser that 
      // prompts failure to retrieve attributes when this is 
      // turned off.
      //parser->setValidationScheme(XercesDOMParser::Val_Never);
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

}
