// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/include/Open64BasicTypes.h,v 1.7 2004/06/23 16:51:13 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/include/Open64BasicTypes.h,v $
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

#include <../../common/com/defs.h>   // Basic types, such as INT32
#include <../../common/com/config.h>
#include <../../common/com/erglob.h> // <errors.h> Set_Error_Tables(); EC defs
#include <../../common/com/glob.h>   // Irb_File_Name...

#include <../../common/util/mempool.h>	  // MEM_Initialze(), MEM_POOL_*, etc. 
#include <../../common/util/cxx_memory.h> // CXX_NEW

#include <../../common/com/pu_info.h>	   // for PU_Info
#include <../../common/com/wn.h>           // WN nodes
#include <../../common/com/wn_util.h>      // WN walk, insert, copy routines
#include <../../common/com/wn_tree_util.h> // WN_TREE_ITER, WN_TREE_CONTAINER
#include <../../common/com/wio.h>          // WHIRL I/O
#include <../../common/com/wutil.h>        // WHIRL intrinsic utilities
#include <../../common/com/intrn_info.h>   // WHIRL INTR macros     

#include <../../common/com/symtab.h>  // TY and ST nodes
#include <../../common/com/const.h>   // FOR_ALL_CONSTANTS
#include <../../be/com/be_symtab.h>   // BE_ST flags

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

typedef mINT64 STAB_OFFSET; // cf. be/whirl2c/wn_attr.h
typedef TYPE_ID MTYPE;      // cf. be/whirl2c/stab_attr.h 

//***************************************************************************

#endif
