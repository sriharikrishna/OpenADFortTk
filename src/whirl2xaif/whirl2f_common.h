// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/whirl2f_common.h,v 1.8 2004/02/17 18:53:48 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/whirl2f_common.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/whirl2f_common.h
//
//***************************************************************************

#ifndef whirl2f_common_INCLUDED

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

#include <lib/support/stab_attr.h>
#include <lib/support/wn_attr.h>
#include <lib/support/w2cf_symtab.h>
#include <lib/support/XAIFStrings.h>
#include <lib/support/diagnostics.h>

//***************************************************************************

typedef mUINT32 WN2F_STATUS;
#define EMPTY_WN2F_STATUS (WN2F_STATUS)0

//***************************************************************************

#define whirl2xaif_divider_comment \
  "********************************************************************"

//***************************************************************************

// Ensure that we never refer to Cur_PU_Name (glob.h).  Use PU_Info
// facilities instead.
#define Cur_PU_Name You_should_not_use("Cur_PU_Name")

//***************************************************************************

#endif /* whirl2f_common_INCLUDED */
