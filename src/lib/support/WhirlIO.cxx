// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIO.cxx,v 1.3 2004/01/29 23:16:05 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIO.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

#include "phase.h"         // PHASE_CG
#include "be_util.h"       // Reset_Current_PU_Count(), etc
#include "stab.h"	   // ir_bread.h
#include "stblock.h"       // Create_Slink_Symbol()

#include "ir_bread.h"	   // Read_Global_Info()
#include "ir_bwrite.h"	   // Write_Global_Info(), etc.
#include "ir_reader.h"     // fdump_tree

#include "opt_alias_interface.h"  // ALIAS_MANAGER stuff
#include "region_util.h"	  // Regions_Around_Inner_Loops
#include "region_main.h"          // REGION_* driver specific routines
#include "dwarf_DST.h"	    	  // for Orig_PU_Name
#include "fb_whirl.h"		  // for FEEDBACK
#include "wn_lower.h" // FIXME
#include "iter.h"		  // PU iterator for loops

#include "mem_ctr.h"
#include "tracing.h"              //  the trace routines

//*************************** User Include Files ****************************

#include "WhirlIO.h"
#include "WhirlGlobalStateUtils.h"
#include "Pro64IRInterface.h"

#include "diagnostics.h"

//************************** Forward Declarations ***************************

// REMOVE
OPTIONS_STACK *Options_Stack; // for PU and region level pragmas

//***************************************************************************

//***************************************************************************
// ReadIR
//***************************************************************************

static void 
ReadPU(PU_Info* pu);


// ReadIR: Given a WHIRL filename, reads the entire contents into
// memory to form a PU forest (a collection of PU trees).
PU_Info*
ReadIR(const char* irfilename)
{
  Diag_Set_Phase("WHIRL IO: Load IR");

  MEM_POOL_Push(&MEM_src_pool);
  MEM_POOL_Push(&MEM_src_nz_pool);
  Set_Error_Source (Src_File_Name);

  MEM_POOL_Push(MEM_pu_nz_pool_ptr);
  MEM_POOL_Push(MEM_pu_pool_ptr);

  // -------------------------------------------------------
  // 1. Read pu tree info and global symbol table
  // -------------------------------------------------------
  
  // Push initial file level options (FIXME)
  Options_Stack = CXX_NEW(OPTIONS_STACK(&MEM_src_nz_pool), &MEM_src_nz_pool);
  Options_Stack->Push_Current_Options();
  
  // Open file, read PU info and setup symbol tables
  Open_Input_Info((char*)irfilename); // FIXME: change caller to accept const
  Initialize_Symbol_Tables(FALSE);
  New_Scope(GLOBAL_SYMTAB, Malloc_Mem_Pool, FALSE);
  PU_Info *pu_forest = Read_Global_Info(NULL);
  Initialize_Special_Global_Symbols();
  
  // -------------------------------------------------------
  // 2. Read PUs and local symbol tables
  // -------------------------------------------------------
  for (PU_Info* pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
    ReadPU(pu);
  }

  // Free_Input_Info // should we do this?

  return pu_forest;
}


void
ReadPU(PU_Info* pu)
{
  Current_PU_Info = pu;
  
  // Read program unit (Reads the PUs (WHIRL trees), symbol tables;
  // sets CURRENT_SYMTAB and Scope_tab[]).
  Read_Local_Info(MEM_pu_nz_pool_ptr, pu);
  WN *wn_pu = PU_Info_tree_ptr(pu); // made possible by Read_Local_Info()
  
  /* FIXME: Always create region pool because there are many places where
   * they can be introduced. Needed for PUs with no regions also */
  /* NOTE: part of what REGION_initialize does can be moved
   * to when the .B file is read in.   */
  REGION_Initialize(wn_pu, PU_has_region(Get_Current_PU()));

  Advance_Current_PU_Count();

  // Now recursively process the child PU's.
  for (PU_Info* child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    ReadPU(child);
  }

  WhirlGlobalStateUtils_hidden::PU_SaveGlobalState(pu);
}


//***************************************************************************
// WriteIR
//***************************************************************************

static void
WritePU(PU_Info* pu);

static void
SetPUInfoStateIR(PU_Info* pu_forest, Subsect_State state);

static void
SetPUInfoStatePU(PU_Info* pu, Subsect_State state);

static void
SetPUInfoState(PU_Info* pu, Subsect_State state);


// WriteIR: given a filename write the entire IR (a PU forest) to
// disk.  *Warning*: Writing to disk also frees part of the IR when
// compiled with BACK_END.
void 
WriteIR(const char* irfilename, PU_Info* pu_forest)
{
  Diag_Set_Phase("WHIRL IO: Write IR");

  Open_Output_Info((char*)irfilename); // FIXME change to accept const

  // -------------------------------------------------------
  // 1. Write PUs and local symbol tables
  // -------------------------------------------------------

  // It would be possible to use the standard iterator here, but in
  // order to highlight the special handling in WritePU, we do not.
  for (PU_Info* pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
    WritePU(pu);
  }

  // -------------------------------------------------------
  // 2. Write Global info
  // -------------------------------------------------------
  Write_Global_Info(pu_forest); // expects PU state to be Subsect_Written
  Close_Output_Info();
}

static void
WritePU(PU_Info* pu)
{
  PU_RestoreGlobalState(pu);
  
  Write_PU_Info(pu); // sets PU state to Subsect_Written
  
  // Recur
  for (PU_Info* child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    WritePU(child);
  }
}

// SetPUInfoStateIR: For each PU in IR 'pu_forest', sets each
// subsection to have the state 'state' if the subsection is present
// (i.e. not Subsect_Missing).
static void
SetPUInfoStateIR(PU_Info* pu_forest, Subsect_State state) 
{
  for (PU_Info* pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
    SetPUInfoStatePU(pu, state);
  }
}

// SetPUInfoStatePU: Sets the state for the PU tree: the current PU
// and all children.
static void
SetPUInfoStatePU(PU_Info* pu, Subsect_State state) 
{
  // Set the state
  SetPUInfoState(pu, state);
  
  // Recur
  for (PU_Info* child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    SetPUInfoStatePU(child, state);
  }
}

// SetPUInfoState: Set the state for the current PU
static void
SetPUInfoState(PU_Info* pu, Subsect_State state) 
{
  for (int subsec = 0; subsec < WT_SUBSECTIONS; ++subsec) {
    if (PU_Info_state(pu, subsec) != Subsect_Missing) {
      Set_PU_Info_state(pu, subsec, state);
    }
  }
}


//***************************************************************************
// FreeIR
//***************************************************************************

static void 
FreePU(PU_Info* pu);


// FreeIR: Given a PU forest, frees all memory consumed by it.
void
FreeIR(PU_Info* pu_forest)
{
  Diag_Set_Phase("WHIRL IO: Free IR");
  
  // -------------------------------------------------------
  // 1. Free PUs and local symbol tables
  // -------------------------------------------------------
  for (PU_Info* pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
    FreePU(pu);
  }
  
  // -------------------------------------------------------
  // 2. Free pu tree info and global symbol tables
  // -------------------------------------------------------
  Verify_SYMTAB(GLOBAL_SYMTAB);
  
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


static void
FreePU(PU_Info* pu)
{
  PU_RestoreGlobalState(pu);
  
  //REGION_Finalize();
  Free_Local_Info(pu); // deletes all maps
  
  // Now recursively process the child PU's.
  for (PU_Info *child = PU_Info_child(pu); child != NULL;
       child = PU_Info_next(child)) {
    FreePU(child);
  }
}


//***************************************************************************
// PrepareIR
//***************************************************************************

void 
PrepareIR(PU_Info* pu_forest)
{
  Diag_Set_Phase("WHIRL IO: Prepare IR");

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
// DumpIR
//***************************************************************************

void 
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
    fdump_tree(stderr, wn_pu);
    
    if (dumpST) {
      Print_local_symtab(stdout, Scope_tab[CURRENT_SYMTAB]);
    }
  }
}


//***************************************************************************

#if 0

// This is some code for initializing the global sections of the
// backend symtab.  It came from ReadIR(const char*).  If we ever want
// to use it, we should create a separate routine for initializing the
// BE symtab.

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

// This is for initializing local sections of the backend symtab; from
// ReadPU(PU_Info*)
  
  BE_symtab_alloc_scope_level(CURRENT_SYMTAB);
  Scope_tab[CURRENT_SYMTAB].st_tab->
    Register(*Be_scope_tab[CURRENT_SYMTAB].be_st_tab);

// Would we every want to use this 
  Set_Current_PU_For_Trace(ST_name(PU_Info_proc_sym(pu)), Current_PU_Count());

// This is for freeing the backend symtab
// From FreeIR(PU_Info*)

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

// Freeing local backend symtab, from FreePU(PU_Info*)
  SYMTAB_IDX scopelvl = PU_lexical_level(PU_Info_pu(pu));
  Scope_tab[scopelvl].st_tab->Un_register(*Be_scope_tab[scopelvl].be_st_tab);
  Be_scope_tab[scopelvl].be_st_tab->Clear();

#endif

