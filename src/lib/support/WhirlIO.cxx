// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIO.cxx,v 1.8 2004/02/26 14:24:02 eraxxon Exp $

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

#include "ir_bread.h"	   // Read_Global_Info(), etc.
#include "ir_bwrite.h"	   // Write_Global_Info(), etc.
#include "ir_reader.h"     // fdump_tree
#include "tracing.h"       // trace routines

#include "be_util.h"       // Advance_/Reset_Current_PU_Count(), etc

//#include "region_util.h"   // REGION ids and region-id (RID) map
//#include "region_main.h"   // REGION_* routines
//#include "options_stack.h" // Options_Stack (cf. be/driver.cxx)

#include "wn_lower.h"      // WHIRL lowerer
#include "stblock.h"       // Create_Slink_Symbol()

//*************************** User Include Files ****************************

#include "WhirlIO.h"
#include "WhirlGlobalStateUtils.h"
#include "Pro64IRInterface.h"

#include "diagnostics.h"

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// ReadIR
//***************************************************************************

static void 
ReadPU(PU_Info* pu);


// ReadIR:
PU_Info*
ReadIR(const char* irfilename)
{
  Diag_Set_Phase("WHIRL IO: Load IR");

  MEM_POOL_Push(&MEM_src_pool);
  MEM_POOL_Push(&MEM_src_nz_pool);
  Set_Error_Source(Src_File_Name);

  MEM_POOL_Push(MEM_pu_nz_pool_ptr);
  MEM_POOL_Push(MEM_pu_pool_ptr);

  // -------------------------------------------------------
  // 1. Read pu tree info and global symbol table
  // -------------------------------------------------------
  
  // Open file, read PU info and setup symbol tables
  Open_Input_Info(irfilename);
  Initialize_Symbol_Tables(FALSE);
  New_Scope(GLOBAL_SYMTAB, Malloc_Mem_Pool, FALSE);
  PU_Info *pu_forest = Read_Global_Info(NULL);
  Initialize_Special_Global_Symbols();
  
  // -------------------------------------------------------
  // 2. Read PUs and local symbol tables
  // -------------------------------------------------------
  // Perform our own iteration to ensure correctness and safety
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


// WriteIR
void 
WriteIR(const char* irfilename, PU_Info* pu_forest)
{
  Diag_Set_Phase("WHIRL IO: Write IR");

  Open_Output_Info(irfilename);

  // -------------------------------------------------------
  // 1. Write PUs and local symbol tables
  // -------------------------------------------------------
  // Perform our own iteration to ensure correctness and safety
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
  PU_SetGlobalState(pu);
  
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


// FreeIR: 
void
FreeIR(PU_Info* pu_forest)
{
  Diag_Set_Phase("WHIRL IO: Free IR");
  
  // -------------------------------------------------------
  // 1. Free PUs and local symbol tables
  // -------------------------------------------------------
  // Perform our own iteration to ensure correctness and safety
  for (PU_Info* pu = pu_forest; pu != NULL; pu = PU_Info_next(pu)) {
    FreePU(pu);
  }
  
  // -------------------------------------------------------
  // 2. Free pu tree info and global symbol tables
  // -------------------------------------------------------
  Verify_SYMTAB(GLOBAL_SYMTAB);
  
  MEM_POOL_Pop(MEM_pu_nz_pool_ptr);
  MEM_POOL_Pop(MEM_pu_pool_ptr);
  
  MEM_POOL_Pop(&MEM_src_pool);
  MEM_POOL_Pop(&MEM_src_nz_pool);
  
#ifdef Is_True_On
  if (Get_Trace (TKIND_ALLOC, TP_MISC)) {
    fprintf (TFile, "\n%s\tMemory allocation info\n", DBar);
    MEM_Trace();
  }
#endif
}


static void
FreePU(PU_Info* pu)
{
  PU_SetGlobalState(pu);
  
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
  // from ReadPU()
  Set_Current_PU_For_Trace(ST_name(PU_Info_proc_sym(pu)), Current_PU_Count());


  // Note: REGION stuff will not be useful when reading the whole IR,
  // because the map is only for one PU.  May need this process PU for
  // lowering.
  // --> from ReadPU(), before Advance_Current_PU_Count()
  // Create region mempool and id map. (Used in lowering?)
  REGION_Initialize(wn_pu, PU_has_region(Get_Current_PU()));
  // --> from FreePU(), before Free_Local_Info()
  REGION_Finalize();
#endif

