// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/main.cxx,v 1.5 2003/06/02 13:43:22 eraxxon Exp $
// -*-C++-*-

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

#include "Open64BasicTypes.h"

#include <cmplrs/rcodes.h>
#include "config_opt.h"             /* for Instrumentation_Enabled */
#include "config_list.h"	    /* for List_Enabled, etc. */
#include "err_host.tab"		    /* load all the error messages */
//REMOVE #include "erauxdesc.h"	    /* for BE error messages */

#include "phase.h"		    /* for PHASE_CG */
#include "be_util.h"       /* for Reset_Current_PU_Count(), etc */
#include "stab.h"		    /* for ir_bread.h */
#include "stblock.h"                /* for Create_Slink_Symbol() */
#include "ir_bread.h"		    /* for Read_Global_Info() */
#include "ir_bwrite.h"		    /* for Write_Global_Info(), etc. */
#include "file_util.h"		    /* for New_Extension () */
#include "opt_alias_interface.h"    /* for ALIAS_MANAGER stuff */
#include "region_util.h"	  /* for Regions_Around_Inner_Loops */
#include "region_main.h"   /* for REGION_* driver specific routines */
#include "tracing.h"                /* For the trace routines */
#include "ir_reader.h"              /* For fdump_tree */
#include "dwarf_DST.h"	    	    /* for Orig_PU_Name */
#include "fb_whirl.h"		    /* for FEEDBACK */
#include "iter.h"		   /* PU iterator for loops */

#include "options_stack.h"	    /* for Options_Stack */
#include "mem_ctr.h"

#include "wn_lower.h" // FIXME
//#include "w2f_weak.h" // REMOVE

//*************************** User Include Files ****************************

#include "whirl2f_common.h"
#include "whirl2xaif.h"
#include "xmlostream.h"

#include "Pro64IRInterface.h" // FIXME for RestoreOpen64PUGlobalVars()
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

static PU_Info* 
LoadIR();
static void 
FreeIR(PU_Info *pu_forest);

static void 
PrepareIR(PU_Info *pu_forest);

static void 
DumpIR(PU_Info *pu_forest);

//************************** Forward Declarations ***************************

// Options (FIXME)
// Src_File_Name, Irb_File_Name, Obj_File_Name
const char* ProgramName = NULL;
char WHIRL_filename[PATH_MAX+1] = "";
char XAIF_filename[PATH_MAX+1] = "";

bool opt_dumpIR = false;

//************************** Forward Declarations ***************************

// REMOVE
static OPTIONS_STACK *Options_Stack; // for PU and region level pragmas

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
  // 3. Load WHIRL IR and translate
  // -------------------------------------------------------
  PU_Info* pu_forest = NULL;
  pu_forest = LoadIR();
  
  // if verbose and if translating to file...
  cerr << ProgramName << " translates " << WHIRL_filename << " into "
       << XAIF_filename << " based on source " << Src_File_Name << std::endl;
  
  PrepareIR(pu_forest); // FIXME (should this be part of translate?)
  
  if (opt_dumpIR) { DumpIR(pu_forest); }
  whirl2xaif::TranslateIR(ofs, pu_forest);
  
  FreeIR(pu_forest);
  
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
// 
//***************************************************************************

static void LoadPU(PU_Info* pu);
static void FreePU(PU_Info* pu);

static PU_Info*
LoadIR()
{
  Diag_Set_Phase("WHIRL to XAIF: Load IR");

  MEM_POOL_Push(&MEM_src_pool);
  MEM_POOL_Push(&MEM_src_nz_pool);
  Set_Error_Source (Src_File_Name);

  MEM_POOL_Push(MEM_pu_nz_pool_ptr);
  MEM_POOL_Push(MEM_pu_pool_ptr);

  // -------------------------------------------------------
  // 1. Read pu tree info and global symbol table (FIXME: always do this?)
  // -------------------------------------------------------
  
  // Push initial file level options
  Options_Stack = CXX_NEW(OPTIONS_STACK(&MEM_src_nz_pool), &MEM_src_nz_pool);
  Options_Stack->Push_Current_Options();
  
  if (Read_Global_Data) {
    // get input from two separate files
    Irb_File = (FILE *)Open_Global_Input(Global_File_Name);
    Irb_File = (FILE *)Open_Local_Input(Irb_File_Name);
  } else {
    Irb_File = (FILE *)Open_Input_Info(Irb_File_Name);
  }
  
  Initialize_Symbol_Tables(FALSE);
  New_Scope(GLOBAL_SYMTAB, Malloc_Mem_Pool, FALSE);
  PU_Info *pu_forest = Read_Global_Info(NULL); // FIXME 
  Initialize_Special_Global_Symbols();

#if 0 // FIXME
  // initialize the BE symtab. Note that w2cf relies on the BE_ST 
  // during Phase_Init and Phase_Fini (do we still need this? REMOVE)
  BE_symtab_initialize_be_scopes();
  BE_symtab_alloc_scope_level(GLOBAL_SYMTAB);
  for (SYMTAB_IDX scopelvl = 0; scopelvl <= GLOBAL_SYMTAB; ++scopelvl) {
    // No need to deal with levels that don't have st_tab's. Currently
    // this should be only zero.
    if (Scope_tab[scopelvl].st_tab != NULL) {
      Scope_tab[scopelvl].st_tab->Register(*Be_scope_tab[scopelvl].be_st_tab);
    } else {
      Is_True(scopelvl == 0, ("Nonexistent st_tab for level %d", scopelvl));
    }
  }
#endif
  
  // -------------------------------------------------------
  // 2. Read PUs and local symbol tables (FIXME: may not need to do this)
  // -------------------------------------------------------
  for (PU_Info *pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
    LoadPU(pu);
  }

  return pu_forest;
}

static void
FreeIR(PU_Info *pu_forest)
{
  Diag_Set_Phase("WHIRL to XAIF: Free IR");
  
  // -------------------------------------------------------
  // 1. Free PUs and local symbol tables (FIXME: may not need to do this)
  // -------------------------------------------------------
  for (PU_Info *pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
    FreePU(pu);
  }
  
  // -------------------------------------------------------
  // 2. Free pu tree info and global symbol tables (FIXME: always do this?)
  // -------------------------------------------------------
  CURRENT_SYMTAB = GLOBAL_SYMTAB; // FIXME
  Verify_SYMTAB(CURRENT_SYMTAB); /* Verifies global SYmtab */

#if 0 // FIXME  
  // free the BE symtabs. w2cf requires BE_ST in Phase_Fini */
  for (SYMTAB_IDX scopelvl = GLOBAL_SYMTAB; scopelvl >= 0; --scopelvl) {
    // No need to deal with levels that don't have st_tab's. Currently
    // this should be only zero.
    if (Scope_tab[scopelvl].st_tab != NULL) {
      Scope_tab[scopelvl].st_tab->
	Un_register(*Be_scope_tab[scopelvl].be_st_tab);
      Be_scope_tab[scopelvl].be_st_tab->Clear();
    } else {
      Is_True(scopelvl == 0, ("Nonexistent st_tab for level %d", scopelvl));
    }
  }
  BE_symtab_free_be_scopes();
#endif

  // mem cleanup
  MEM_POOL_Pop(MEM_pu_nz_pool_ptr);
  MEM_POOL_Pop(MEM_pu_pool_ptr);

  MEM_POOL_Pop( &MEM_src_pool );
  MEM_POOL_Pop( &MEM_src_nz_pool );
#ifdef Is_True_On
  if (Get_Trace (TKIND_ALLOC, TP_MISC)) {
    fprintf (TFile, "\n%s\tMemory allocation information after be\n", DBar);
    MEM_Trace();
  }
#endif
}


void
LoadPU(PU_Info *pu)
{
  Current_PU_Info = pu;
  
  // Read program unit (Reads the PUs (WHIRL trees), symbol tables;
  // sets CURRENT_SYMTAB and Scope_tab[]).
  Read_Local_Info(MEM_pu_nz_pool_ptr, pu);
  
#if 0 // FIXME: Be_scope_tab needs to be changed when another PU is read
  BE_symtab_alloc_scope_level(CURRENT_SYMTAB);
  Scope_tab[CURRENT_SYMTAB].st_tab->
    Register(*Be_scope_tab[CURRENT_SYMTAB].be_st_tab);
#endif

  WN *wn_pu = PU_Info_tree_ptr(pu); // made possible by Read_Local_Info()
  
  //REMOVE Set_Current_PU_For_Trace(ST_name(PU_Info_proc_sym(pu)), Current_PU_Count());

  /* Always create region pool because there are many places where
   * they can be introduced. Needed for PUs with no regions also */
  /* NOTE: part of what REGION_initialize does can be moved
   * to when the .B file is read in.  (FIXME) */
  REGION_Initialize(wn_pu, PU_has_region(Get_Current_PU()));

  Advance_Current_PU_Count();

  // Now recursively process the child PU's.
  for (PU_Info *child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    LoadPU(child);
  }

  SaveOpen64PUGlobalVars(pu);
}


static void
FreePU(PU_Info* pu) // FIXME: unload
{
  RestoreOpen64PUGlobalVars(pu);

  REGION_Finalize();
  
#if 0 // FIXME
  SYMTAB_IDX scopelvl = PU_lexical_level(PU_Info_pu(pu));
  Scope_tab[scopelvl].st_tab->Un_register(*Be_scope_tab[scopelvl].be_st_tab);
  Be_scope_tab[scopelvl].be_st_tab->Clear();
#endif

  Free_Local_Info(pu); // deletes all maps
  
  // Now recursively process the child PU's.
  for (PU_Info *child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    FreePU(child);
  }
}

//***************************************************************************

static void 
PrepareIR(PU_Info* pu_forest)
{
  Diag_Set_Phase("WHIRL to XAIF: Prepare IR");

  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();
    WN* wn_pu = PU_Info_tree_ptr(pu);
    
    Create_Slink_Symbol(); // FIXME: do we need?
    Lower_Init(); // Open64 Lowerer
    
    // RETURN_VAL (for C)
    //wn_pu = WN_Lower(wn_pu, LOWER_CALL, NULL, "Lowering CALLS");
    //wn_pu = WN_Lower(wn_pu, LOWER_IO_STATEMENT, NULL, "Lowering IO");
    
#if 0
    // FIXME: this can affect CFGs (removing duplicate RETURNs)
    // (causes a problem on simple7.f90)
    if (WHIRL_Return_Val_On || WHIRL_Mldid_Mstid_On) {
      Is_True(WHIRL_Return_Val_On && WHIRL_Mldid_Mstid_On, ("FIXME"));
      wn_pu = WN_Lower(wn_pu, LOWER_RETURN_VAL | LOWER_MLDID_MSTID, NULL,
		       "RETURN_VAL & MLDID/MSTID lowering");
      // what about: LOWER_MP for nested PUs
    }
    Verify_SYMTAB(CURRENT_SYMTAB);
#endif
    
    Lowering_Finalize();
  }
}

//***************************************************************************
// 
//***************************************************************************

static void 
DumpIR(PU_Info* pu_forest)
{
  bool dumpST = false;
  IR_set_dump_order(TRUE); // Preorder dump

  if (dumpST) {
    // Global 
    Print_global_symtab(stdout);
  }

  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();  
    WN* wn_pu = PU_Info_tree_ptr(pu);
    
    //IR_put_func(wn_pu, NULL);
    fdump_tree(stderr, wn_pu); // FIXME
    
    if (dumpST) {
      Print_local_symtab(stdout, Scope_tab[CURRENT_SYMTAB]);
    }
  }
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
