// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_io.h,v 1.7 2006/05/12 16:12:23 utke Exp $

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

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include "Open64IRInterface/Open64BasicTypes.h"

//*************************** User Include Files ****************************

#include "whirl2xaif.h"
#include "PUXlationContext.h"

//************************** Forward Declarations ***************************

//***************************************************************************

namespace whirl2xaif {

  extern void 
  xlate_IO(xml::ostream& xos, WN *wn, PUXlationContext& context);
  
  extern BOOL
  xlate_IO_ITEM(xml::ostream& xos, WN *wn, PUXlationContext& context);

}; /* namespace whirl2xaif */

//***************************************************************************

#endif /* wn2xaif_io_INCLUDED */

