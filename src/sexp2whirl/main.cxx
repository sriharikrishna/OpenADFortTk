// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/main.cxx,v 1.1 2004/12/15 17:54:53 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/main.cxx,v $
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
using std::endl;
using std::cout;
#include <string>

#include <fcntl.h> // for use in ReadWhirlSexp()
#include <errno.h> // for use in ReadWhirlSexp()

//*************************** Sexp Include Files ****************************

#include <sexp.h>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

#include "cmplrs/rcodes.h"  // return codes
#include "tracing.h"        // trace routines
#include "ir_reader.h"      // fdump_tree

//*************************** User Include Files ****************************

#include "Args.h"

#include <lib/support/Exception.h>
#include <lib/support/WhirlIO.h>

//************************** Forward Declarations ***************************

static int
real_main(int argc, char **argv);

static sexp_t*
ReadWhirlSexp(const char* filename);

static void
DumpSexp(std::ostream& os, sexp_t* sexp); // FIXME

static void 
OpenFile(std::ofstream& fs, const char* filename);

static void 
CloseFile(std::ofstream& fs);


//***************************************************************************

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
  Set_Error_Phase("sexp2whirl");
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
  Diag_Set_Phase("WHIRL to sexp: driver");
  
  Args args(argc, argv);
  FortTk_SetDiagnosticFilterLevel(args.debug);
  
  // -------------------------------------------------------
  // 3. Read S-expressions and Translate into WHIRL
  // -------------------------------------------------------
  
  sexp_t* ir_sexp = ReadWhirlSexp(args.sexpFileNm.c_str());
  
  DumpSexp(std::cout, ir_sexp);
  
  //PU_Info* ir_whirl = sexp2whirl::TranslateIR(*os, ir_sexp);  
  //WriteIR(args.whirlFileNm.c_str(), ir_whirl);
  
  // -------------------------------------------------------
  // 4. Finalization
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
// 
//***************************************************************************

static sexp_t*
ReadWhirlSexp(const char* filename)
{
  // see readtests.c (FIXME)
  int fd = open(filename, O_RDONLY);
  if (fd < 0) {
    FORTTK_DIE("Error opening " << filename << ": " << strerror(errno));
  }

  sexp_iowrap_t* iow = init_iowrap(fd);
  sexp_t* sexp = read_one_sexp(iow);
  return sexp;
}

// destroy_sexp(sx);
// sexp_cleanup();

static void
DumpSexp(std::ostream& os, sexp_t* sexp)
{
  const int sz = 1 << 20;
  char* buf = new char[sz];
  
  int rval = print_sexp(buf, sz, sexp);
  os << buf << std::endl;
  delete[] buf;
}

