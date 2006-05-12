// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/main.cxx,v 1.26 2006/05/12 16:12:23 utke Exp $

#include <iostream>
using std::endl;
using std::cout;
#include <string>

#include <include/Open64BasicTypes.h>

#include "cmplrs/rcodes.h"  // return codes
#include "tracing.h"        // trace routines
#include "ir_reader.h"      // fdump_tree

#include <OpenAnalysis/Utils/Exception.hpp>

#include "Args.h"
#include "whirl2xaif.h"

#include <lib/support/xmlostream.h>
#include <lib/support/Exception.h>
#include <lib/support/WhirlIO.h>

static int
real_main(int argc, char **argv);

static std::ostream*
InitOutputStream(Args& args);

static void
FiniOutputStream(std::ostream* os);

static void 
OpenFile(std::ofstream& fs, const char* filename);

static void 
CloseFile(std::ofstream& fs);


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
  catch (xml::ostream::Exception& e) {
    e.Report(cerr);
    exit(1);
  }
  catch (OA::Exception& e) {
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
  // -------------------------------------------------------
  // 1. Open64 Initialization
  // -------------------------------------------------------
  Handle_Signals();
  MEM_Initialize();
  Init_Error_Handler( 100 );
  Set_Error_Line( ERROR_LINE_UNKNOWN );
  Set_Error_File( NULL );
  Set_Error_Phase("whirl2xaif");
  IR_set_dump_order(TRUE /*pre*/); // pre-order trees when debugging, please!
  
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
  Diag_Set_Phase("WHIRL to XAIF: driver");
  
  Args args(argc, argv);
  std::ostream* os = InitOutputStream(args);
  FortTk_SetDiagnosticFilterLevel(args.debug);
  
  // -------------------------------------------------------
  // 3. Read WHIRL IR
  // -------------------------------------------------------
  PU_Info* pu_forest = ReadIR(args.whirlFileNm.c_str());
  PrepareIR(pu_forest); // FIXME (should this be part of translation?)

  // -------------------------------------------------------
  // 4. Translate WHIRL into XAIF
  // -------------------------------------------------------  
  
  (*os) << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
  whirl2xaif::Whirl2Xaif::translateIR(*os, pu_forest, args.tmpVarPrefix.c_str());
  
  bool writeIR = false;
  if (writeIR) { 
    std::string file = "out.B"; // FIXME
    WriteIR(file.c_str(), pu_forest); 
  } 
  else {
    FreeIR(pu_forest); // Writing frees some of the WHIRL maps
  }
  
  // -------------------------------------------------------
  // 5. Finalization
  // -------------------------------------------------------
  FiniOutputStream(os);
  
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

static std::ostream*
InitOutputStream(Args& args)
{
  if (args.xaifFileNm.empty()) {
    // Use cout
    return &(cout);
  } 
  else {
    ofstream* ofs = new ofstream;
    OpenFile(*ofs, args.xaifFileNm.c_str());
    return ofs;
  }
}

static void
FiniOutputStream(std::ostream* os)
{
  if (os != &cout) {
    delete os;
  }
}


static void 
OpenFile(std::ofstream& fs, const char* filename)
{
  using namespace std;

  fs.open(filename, ios::out | ios::trunc);
  if (!fs.is_open() || fs.fail()) {
    ErrMsg(EC_IR_Open, filename, 0/*FIXME*/);
  } 
}

static void
CloseFile(std::ofstream& fs)
{
  fs.close();
}
