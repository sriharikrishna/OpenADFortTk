// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/main.cxx,v 1.1 2004/08/05 18:38:14 eraxxon Exp $

// * BeginCopyright *********************************************************
/*
  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan
*/
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/main.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/be/driver.cxx (curr.driver.cxx)
//
//***************************************************************************

//************************** System Include Files ***************************

#include <iostream>
using std::endl;
using std::cout;
#include <string>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

#include "cmplrs/rcodes.h"  // return codes
#include "tracing.h"        // trace routines
#include "ir_reader.h"      // fdump_tree

//*************************** User Include Files ****************************

#include "Args.h"
#include "whirl2sexp.h"

#include <lib/support/sexpostream.h>
#include <lib/support/Exception.h>
#include <lib/support/WhirlIO.h>

//************************** Forward Declarations ***************************

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
  catch (sexp::ostream::Exception& e) {
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
  Set_Error_Phase("whirl2sexp");
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
  std::ostream* os = InitOutputStream(args);
  FortTk_SetDiagnosticFilterLevel(args.debug);
  
  // -------------------------------------------------------
  // 3. Read WHIRL IR
  // -------------------------------------------------------
  PU_Info* pu_forest = ReadIR(args.whirlFileNm.c_str());
  PrepareIR(pu_forest); // FIXME (should this be part of translation?)

  // -------------------------------------------------------
  // 4. Translate WHIRL into S-expressions
  // -------------------------------------------------------  
  whirl2sexp::TranslateIR(*os, pu_forest);
  
  FreeIR(pu_forest); // Writing frees some of the WHIRL maps
  
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


//***************************************************************************
// 
//***************************************************************************

static std::ostream*
InitOutputStream(Args& args)
{
  if (args.sexpFileNm.empty()) {
    // Use cout
    return &(cout);
  } else {
    ofstream* ofs = new ofstream;
    OpenFile(*ofs, args.sexpFileNm.c_str());
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
