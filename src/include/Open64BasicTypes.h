// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/include/Open64BasicTypes.h,v 1.2 2003/05/14 01:10:12 eraxxon Exp $
// -*-C++-*-

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

#include "defs.h"          /* Basic types, such as INT32 */
#include "config.h"
#include "errors.h"	   /* Set_Error_Tables(), etc. */
#include "erglob.h"        /* For errors.h and EC definitions */

#include "pu_info.h"	   /* for PU_Info */
#include "wn.h"            /* WN nodes */
#include "symtab.h"        /* TY and ST nodes */
#include "be_symtab.h"     /* BE_ST flags */
#include "glob.h"          /* Irb_File_Name... */

#include "cxx_memory.h"	   /* CXX_NEW */

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

typedef mINT64 STAB_OFFSET; // cf. be/whirl2c/wn_attr.h
typedef TYPE_ID MTYPE;      // cf. be/whirl2c/stab_attr.h 

//***************************************************************************

#endif


