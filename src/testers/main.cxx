// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/testers/main.cxx,v 1.4 2004/02/17 18:54:36 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/testers/main.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

#include <iostream>
#include <fstream>
#include <string>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

#include "cmplrs/rcodes.h"  // return codes
#include "config_opt.h"     // Instrumentation_Enabled
#include "config_list.h"    // List_Enabled, etc.
#include "err_host.tab"	    // load all the error messages
#include "ir_reader.h"      // fdump_tree

#include "file_util.h"	    // New_Extension, Last_Pathname_Component
#include "tracing.h"        // trace routines

//*************************** User Include Files ****************************

#include "tester.h"

#include <lib/support/diagnostics.h>
#include <lib/support/WhirlIO.h>

#include <OpenAnalysis/Utils/Exception.h>

//************************** Forward Declarations ***************************

static INT 
real_main(INT argc, char **argv);

static void 
OpenFile(std::ofstream& fs, const char* filename);

static void 
CloseFile(std::ofstream& fs);

static void 
ProcessCommandLine(int, char **);

//************************** Forward Declarations ***************************

std::string ProgramName;
std::string WHIRL_filename;

// Options
bool opt_ir = false;
bool opt_oa = false;
bool opt_whirl2f = false;
bool opt_dumpIR = false;

//***************************************************************************

INT
main(int argc, char **argv)
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
}

static INT
real_main(INT argc, char **argv)
{
  // -------------------------------------------------------
  // 1. Open64 Initialization
  // -------------------------------------------------------
  Handle_Signals();
  MEM_Initialize();
  Init_Error_Handler( 100 );
  Set_Error_Line( ERROR_LINE_UNKNOWN );
  Set_Error_File( NULL );
  Set_Error_Phase("whirltester");
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
  Diag_Set_Phase("WHIRL Harness");

  ProcessCommandLine(argc, argv);
  
  // -------------------------------------------------------
  // 3. Read WHIRL IR
  // -------------------------------------------------------
  PU_Info* pu_forest = ReadIR(WHIRL_filename.c_str());
  PrepareIR(pu_forest); // used in whirl2xaif, xaif2whirl

  // -------------------------------------------------------
  // 4. Do something
  // -------------------------------------------------------  
  
  if (opt_dumpIR) { 
    DumpIR(pu_forest); 
  }
  
  if (opt_ir) {
    whirltester::TestIR(std::cout, pu_forest);
  } else if (opt_oa) {
    whirltester::TestIR_OA(std::cout, pu_forest);
  } else if (opt_whirl2f) {
    whirltester::TestIR_whirl2f(std::cout, pu_forest);
  }
  
  FreeIR(pu_forest); // N.B. cannot use with WriteIR

  // -------------------------------------------------------
  // 5. Finalization
  // -------------------------------------------------------

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

      if (strcmp(opt, "ir") == 0) { 
	opt_ir = true;
	continue;
      }
      if (strcmp(opt, "oa") == 0) { 
	opt_oa = true;
	continue;
      }
      if (strcmp(opt, "w2f") == 0) { 
	opt_whirl2f = true;
	continue;
      }
      
      if (strcmp(opt, "d") == 0) { 
	opt_dumpIR = true;
	continue;
      }
      
    } else if (argv[i] != NULL) {
      // -------------------------------------------------------
      // A non-option or immediately after a '--'
      // -------------------------------------------------------
      dashdash_flag = FALSE;
      Src_File_Name = argv[i];
    } 
  }

  if (Src_File_Name == NULL) {
    ErrMsg(EC_No_Sources);
    exit(RC_USER_ERROR); // FIXME: return error
  }
  
  // WHIRL file name
  WHIRL_filename = New_Extension(Src_File_Name, IRB_FILE_EXTENSION);
  Irb_File_Name = (char*)WHIRL_filename.c_str(); // make Open64 happy
    
  // We want the output files to be created in the current directory,
  // so strip off any directory path, and substitute the suffix 
  // appropriately.
  // new_file = New_Extension(Last_Pathname_Component(Src_File_Name), ".xaif");
}


//***************************************************************************
// 
//***************************************************************************

static void 
OpenFile(std::ofstream& fs, const char* filename)
{
  using namespace std;

  fs.open(filename, ios::out | ios::trunc);
  if (!fs.is_open() || fs.fail()) {
    ErrMsg(EC_IR_Open, filename, 0/*FIXME*/);
  } 
  
#if 0//FIXME
  fs.open(filename, ios::out | ios::app);
  fs = Open_Append_File(W2F_File_Name[kind]);
#endif

}

static void
CloseFile(std::ofstream& fs)
{
  fs.close();
}
