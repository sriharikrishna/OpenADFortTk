// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/main.cxx,v 1.12 2003/09/02 15:02:20 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/main.cxx,v $
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

#include <string>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

#include "cmplrs/rcodes.h"  // return codes
#include "config_opt.h"     // Instrumentation_Enabled
#include "config_list.h"    // List_Enabled, etc.
#include "err_host.tab"	    // load all the error messages

#include "file_util.h"	    // New_Extension, Last_Pathname_Component
#include "tracing.h"        // trace routines

//*************************** User Include Files ****************************

#include "whirl2f_common.h"
#include "whirl2xaif.h"

#include <lib/support/xmlostream.h>
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
std::string XAIF_filename;

// Options (FIXME)
bool opt_dumpIR = false;
bool opt_testTypes = false;

//***************************************************************************

INT
main(int argc, char **argv)
{
  try {
    return real_main(argc, argv);
  }
  catch (xml::ostream::Exception& e) {
    e.Report(cerr);
    exit(1);
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
  // -------------------------------------------------------
  // 1. Open64 Initialization
  // -------------------------------------------------------
  Handle_Signals();
  MEM_Initialize();
  Init_Error_Handler( 100 );
  Set_Error_Line( ERROR_LINE_UNKNOWN );
  Set_Error_File( NULL );
  Set_Error_Phase("whirl2xaif");

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

  ProcessCommandLine(argc, argv);
  
  std::ofstream ofs;
  OpenFile(ofs, XAIF_filename.c_str()); // FIXME: errors
  
  // -------------------------------------------------------
  // 3. Read WHIRL IR
  // -------------------------------------------------------
  PU_Info* pu_forest = ReadIR(WHIRL_filename.c_str());
  PrepareIR(pu_forest); // FIXME (should this be part of translation?)

  // -------------------------------------------------------
  // 4. Translate WHIRL into XAIF
  // -------------------------------------------------------  
  
  cerr << ProgramName << " translates " << WHIRL_filename << " into "
       << XAIF_filename << std::endl;

  if (opt_dumpIR) { DumpIR(pu_forest); }
  ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
  whirl2xaif::TranslateIR(ofs, pu_forest);

  // FIXME: Temporary test
  if (opt_testTypes) { 
    std::string file = WHIRL_filename;
    file += ".tytst.B";
    WriteIR(file.c_str(), pu_forest); 
  }

  // FIXME: why does Writing the IR does some freeing (Arg!)
  if (!opt_testTypes) { FreeIR(pu_forest); }
  
  // -------------------------------------------------------
  // 5. Finalization
  // -------------------------------------------------------
  CloseFile(ofs);

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
      
      if (strcmp(opt, "d") == 0) { 
	opt_dumpIR = true;
	continue;
      }

#if 0 // example of option that takes an argument
      if (strcmp(opt, "I") == 0) { 
	PersistentIDsToPrint = argv[++i]; // FIXME: should test array bounds
	continue;
      }
#endif
      
      if (strcmp(opt, "t") == 0) { 
	opt_testTypes = true;
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
  XAIF_filename = New_Extension(Last_Pathname_Component(Src_File_Name), 
				".xaif");
}


//***************************************************************************
// 
//***************************************************************************

/* ====================================================================
 * FIXME: 
 * Open_Read_File()
 *    Opens the file with the given name and path for reading.
 *
 * Open_Append_File()
 *
 *    Opens the file with the given name for appending more to its
 *    end if it already exists, or to create it if it does not
 *    already exist.
 *
 * Open_Create_File()
 *
 *    Same as Open_Append_File(), but a new file is always created,
 *    possibly overwriting an existing file.
 * ====================================================================
 */

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
