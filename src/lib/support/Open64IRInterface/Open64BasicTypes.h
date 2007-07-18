// -*-Mode: C++;-*-
// $Header: /home/derivs2/mstrout/CVSRepository/UseNewOA-Open64/Open64IRInterface/Open64BasicTypes.h,v 1.1.1.1 2004/04/16 15:58:28 mstrout Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /home/derivs2/mstrout/CVSRepository/UseNewOA-Open64/Open64IRInterface/Open64BasicTypes.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Cf. Open64 be/whirl2c/common_include.h
//
//***************************************************************************

#ifndef Open64BasicTypes_INCLUDED
#define Open64BasicTypes_INCLUDED

//************************* System Include Files ****************************

//*************************** User Include Files ****************************

//************************** Open64 Include Files ***************************

#include "defs.h"          // Basic types, such as INT32
#include "config.h"
#include "errors.h"	   // Set_Error_Tables(), etc.
#include "erglob.h"        // For errors.h and EC definitions
#include "glob.h"          // Irb_File_Name...

#include "mempool.h"	   // MEM_Initialze(), MEM_POOL_*, etc. 
#include "cxx_memory.h"	   // CXX_NEW

#include "pu_info.h"	   // for PU_Info
#include "wn.h"            // WN nodes
#include "wn_util.h"       // WN walk, insert and copy routines
#include "wn_tree_util.h"  // WN_TREE_ITER, WN_TREE_CONTAINER
#include "wio.h"           // WHIRL I/O
#include "wutil.h"         // WHIRL intrinsic utilities
#include "intrn_info.h"    // WHIRL INTR macros     

#include "symtab.h"        // TY and ST nodes
#include "be_symtab.h"     // BE_ST flags
#include "const.h"         // FOR_ALL_CONSTANTS

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

typedef mINT64 STAB_OFFSET; // cf. be/whirl2c/wn_attr.h
typedef TYPE_ID MTYPE;      // cf. be/whirl2c/stab_attr.h 

//***************************************************************************

#endif
