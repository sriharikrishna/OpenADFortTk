// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIO.h,v 1.1 2003/07/24 20:26:53 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/WhirlIO.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef WhirlIO_h_INCLUDED
#define WhirlIO_h_INCLUDED

//************************** System Include Files ***************************


//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

#include "options_stack.h"	    /* for Options_Stack */ // REMOVE

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

// REMOVE
extern OPTIONS_STACK *Options_Stack; // for PU and region level pragmas

//***************************************************************************

PU_Info*
ReadIR(const char* irfilename);

void 
WriteIR(const char* irfilename, PU_Info* pu_forest);

void 
FreeIR(PU_Info *pu_forest);

void 
PrepareIR(PU_Info *pu_forest);

void 
DumpIR(PU_Info *pu_forest);

#endif /* WhirlIO_h_INCLUDED */
