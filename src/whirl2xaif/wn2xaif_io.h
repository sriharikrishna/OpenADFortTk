// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_io.h,v 1.3 2003/07/24 14:36:15 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_io.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f_io.h
//
//***************************************************************************

#ifndef wn2xaif_io_INCLUDED
#define wn2xaif_io_INCLUDED
/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *    Utilities for translation an IOS node or an IO item within
 *    an IOS.  Note that WN2F_io_prefix_tokens will only return a
 *    valid token buffer once XlationContext_io_stmt(context) is set.
 *
 * ====================================================================
 * ====================================================================
 */

extern void WN2F_Io_initialize(void);
extern void WN2F_Io_finalize(void);

namespace whirl2xaif { /* FIXME */

extern WN2F_STATUS 
xlate_IO(xml::ostream& xos, WN *wn, XlationContext& context);

extern BOOL
xlate_IO_ITEM(xml::ostream& xos, WN *wn, XlationContext& context);

}; /* namespace whirl2xaif */

#endif /* wn2xaif_io_INCLUDED */
