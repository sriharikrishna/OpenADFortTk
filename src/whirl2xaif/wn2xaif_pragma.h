// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/wn2xaif_pragma.h,v 1.2 2003/05/20 22:50:04 eraxxon Exp $
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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/wn2xaif_pragma.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f_pragma.h
//
//***************************************************************************

#ifndef wn2xaif_pragma_INCLUDED
#define wn2xaif_pragma_INCLUDED

/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *    WN2F_pragma:
 *       Translates a pragma present in a body of statements.
 *
 *    WN2F_pragma_list_begin:
 *       Translates the list of pragmas associated with PU or a
 *       region.
 *
 *    WN2F_pragma_list_end:
 *       Completes the translation initiated with a call to 
 *       WN2F_pragma_list_begin(), after the body of the PU or region
 *       has been translated.
 *
 * ====================================================================
 * ====================================================================
 */

#include "Open64BasicTypes.h"

#include "xmlostream.h"

extern BOOL WN2F_Skip_Pragma_Stmt(WN *wn);

extern 
WN2F_STATUS WN2F_pragma(xml::ostream& xos, WN *wn, XlationContext& context);


WN2F_STATUS 
   WN2F_pragma_list_begin(xml::ostream& xos,
                          WN          *first_pragma,
                          XlationContext& context);

WN2F_STATUS 
   WN2F_pragma_list_end(xml::ostream& xos, 
                        WN          *first_pragma,
                        XlationContext& context);

BOOL
Ignore_Synchronized_Construct(WN          *construct_pragma,  
			      XlationContext& context);

#endif /* wn2xaif_pragma_INCLUDED */


