// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/init2f.h,v 1.5 2004/02/17 22:40:34 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/init2f.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/init2f.h
//
//***************************************************************************

#ifndef init2f_INCLUDED
#define init2f_INCLUDED
/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *    INITO2F_translate:
 *       Appends a DATA statement for the ST associated with the given
 *       INITO list.  In the process, some equivalence specifications
 *       may be prepended to the Data_Stmt_Tokens.  Typical is as
 *       follows:
 *
 *           1) Upon entering a new PU block: Initialize Data_Stmt_Tokens
 *
 *           2) Upon declaring a variable: If it is initialized append
 *              the initializer to Data_Stmt_Tokens with a call to
 *	        INITO2F_translate(Data_Stmt_Tokens, inito).
 *
 *           3) Upon exiting a PU block: Append the contents of 
 *              Data_Stmt_Tokens to the PU tokens, and reclaim the
 *              Data_Stmt_Tokens xml::ostream&.
 *
 * ====================================================================
 * ====================================================================
 */

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "whirl2xaif.i"
#include <lib/support/xmlostream.h>
#include "XlationContext.h"

//************************** Forward Declarations ***************************

//***************************************************************************

extern void INITO2F_translate(xml::ostream& xos, INITO_IDX inito);

#endif /* init2f_INCLUDED */
