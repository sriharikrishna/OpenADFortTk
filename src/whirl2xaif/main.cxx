// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/main.cxx,v 1.10 2003/07/24 20:30:04 eraxxon Exp $

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

#include <limits.h> /* for 'PATH_MAX' */

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
Process_Command_Line (INT, char **);

//************************** Forward Declarations ***************************

// Options (FIXME)
// Src_File_Name, Irb_File_Name, Obj_File_Name
const char* ProgramName = NULL; // FIXME: change to std::string
char WHIRL_filename[PATH_MAX+1] = "";
char XAIF_filename[PATH_MAX+1] = "";

bool opt_dumpIR = false;
bool opt_testPersistentIDs = false;      // FIXME
const char* PersistentIDsToPrint = NULL; // write persistent ids if 
bool opt_testTypes = false;

//***************************************************************************

INT
main(INT argc, char **argv)
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
  // 1. Initialize Open64 
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
  
  Diag_Init(); // non-Open64
  Diag_Set_Max_Diags(100); /* Maximum 100 warnings by default */
  Diag_Set_Phase("WHIRL to XAIF: driver");
  
  // -------------------------------------------------------
  // 2. Get options
  // -------------------------------------------------------
  Preconfigure(); // REMOVE config.cxx
  Process_Command_Line(argc, argv);
  Configure(); // --need for WN_lower-- config.cxx
  Configure_Source(NULL); //REMOVE config.cxx //Most config variables set here
  
  Init_Operator_To_Opcode_Table(); // FIXME
  
  std::ofstream ofs;
  OpenFile(ofs, XAIF_filename); // FIXME: errors
  
  // -------------------------------------------------------
  // 3. Read WHIRL IR and translate
  // -------------------------------------------------------
  PU_Info* pu_forest = NULL;
  pu_forest = ReadIR(Src_File_Name);
  
  // if verbose and if translating to file...
  cerr << ProgramName << " translates " << WHIRL_filename << " into "
       << XAIF_filename << " based on source " << Src_File_Name << std::endl;
  
  PrepareIR(pu_forest); // FIXME (should this be part of translate?)
  
  if (opt_dumpIR) { DumpIR(pu_forest); }
  ofs << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\n";
  whirl2xaif::TranslateIR(ofs, pu_forest);

  // FIXME: Temporary test
  if (opt_testTypes) { 
    std::string file = Src_File_Name;
    file += ".tytst.B";
    WriteIR(file.c_str(), pu_forest); 
  }

  // FIXME: why does Writing the IR does some freeing (Arg!)
  if (!opt_testTypes) { FreeIR(pu_forest); }
  
  // -------------------------------------------------------
  // 4. 
  // -------------------------------------------------------
  CloseFile(ofs);

  // If we've seen errors, note them and terminate
  INT local_ecount, local_wcount;
  if ( Get_Error_Count ( &local_ecount, &local_wcount ) ) {
    Terminate(Had_Internal_Error() ? RC_INTERNAL_ERROR : 
	      RC_NORECOVER_USER_ERROR);
  }
  Cleanup_Files(TRUE, FALSE); // Open64

  Diag_Exit(); // non-Open64

  return RC_OKAY;
}


//***************************************************************************
// from be/be/driver_util.c
//***************************************************************************

/* Default file	extensions: */
#define IRB_FILE_EXTENSION ".B"	    /* WHIRL file */

/*
 * Process_Command_Line
 *
 * Process the command line arguments.	Evaluate all flags and set up
 * global options. 
 */
static void
Process_Command_Line (INT argc, char **argv)
{
  INT Src_Count = 0;
  ProgramName = Last_Pathname_Component (argv[0]);

  /* Check the command line flags: */
  BOOL dashdash_flag = FALSE;
  char* opt;
  
  for (INT16 i = 1; i < argc; i++) {
    if (argv[i] != NULL && (strcmp(argv[i], "--") == 0)) {
      dashdash_flag = TRUE;
      continue;
    }
    
    if ( !dashdash_flag && argv[i] != NULL && *(argv[i]) == '-' ) {
      opt = argv[i]+1;	    /* Pointer to next flag character */
      
      if (strcmp(opt, "d") == 0) { 
	opt_dumpIR = true;
	continue;
      }

      if (strcmp(opt, "i") == 0) { 
	opt_testPersistentIDs = true;
	continue;
      }

      if (strcmp(opt, "I") == 0) { 
	PersistentIDsToPrint = argv[++i]; // FIXME: should test array bounds
	continue;
      }
      
      if (strcmp(opt, "t") == 0) { 
	opt_testTypes = true;
	continue;
      }
      
    } else if (argv[i] != NULL) {
      dashdash_flag = FALSE;
      Src_Count++;
      Src_File_Name = argv[i];
    } 
  }

  if (Src_Count == 0) {
    ErrMsg ( EC_No_Sources );
    exit (RC_USER_ERROR); // FIXME: return error
  }

  // Irb_File_Name
  Irb_File_Name = New_Extension(Src_File_Name, IRB_FILE_EXTENSION);

  // We want the output files to be created in the current directory,
  // so strip off any directory path, and substitute the suffix 
  // appropriately.
  char* fname = New_Extension(Last_Pathname_Component(Src_File_Name), ".xaif");

  strncpy(WHIRL_filename, Irb_File_Name, PATH_MAX);
  strncpy(XAIF_filename, fname, PATH_MAX);
  Irb_File_Name = WHIRL_filename; // FIXME: make Open64 happy
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
