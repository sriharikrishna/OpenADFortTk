// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_stmt.h,v 1.13 2004/06/28 18:52:15 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_stmt.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f_stmt.h
//
//***************************************************************************

#ifndef wn2xaif_stmt_INCLUDED
#define wn2xaif_stmt_INCLUDED

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "whirl2xaif.i"
#include "XlationContext.h"

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// Passive Statements
//***************************************************************************

namespace whirl2xaif {

  extern whirl2xaif::status 
  xlate_PassiveStmt(xml::ostream& xos, WN *wn, XlationContext& ctxt);

}; /* namespace whirl2xaif */


//***************************************************************************
// Structured Control Flow Statements
//***************************************************************************

namespace whirl2xaif {
  
  extern whirl2xaif::status 
  xlate_BLOCK(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  WN2F_region(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_DO_LOOP(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_DO_WHILE(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_WHILE_DO(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_IF(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
}; /* namespace whirl2xaif */


//***************************************************************************
// Unstructured Control Flow Statements
//***************************************************************************

namespace whirl2xaif {

  extern whirl2xaif::status 
  WN2F_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt);

  extern whirl2xaif::status
  WN2F_noio_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_GOTO(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status
  xlate_SWITCH(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status
  WN2F_casegoto(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  WN2F_compgoto(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  WN2F_agoto(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_condBR(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_RETURN(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_RETURN_VAL(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_LABEL(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
}; /* namespace whirl2xaif */


//***************************************************************************
// Calls
//***************************************************************************

namespace whirl2xaif {

  extern whirl2xaif::status 
  xlate_CALL(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_INTRINSIC_CALL(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
}; /* namespace whirl2xaif */


//***************************************************************************
// Other Statements
//***************************************************************************

namespace whirl2xaif {

  extern whirl2xaif::status 
  WN2F_eval(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_PRAGMA(xml::ostream& xos, WN *wn, XlationContext& context);
  
  extern whirl2xaif::status 
  xlate_PREFETCH(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_COMMENT(xml::ostream& xos, WN *wn, XlationContext& ctxt);

  extern whirl2xaif::status 
  WN2F_dealloca(xml::ostream& xos, WN *wn, XlationContext& ctxt) ;
  
  
  extern whirl2xaif::status
  xlate_USE(xml::ostream& xos, WN *wn, XlationContext& ctxt);  

  extern whirl2xaif::status
  WN2F_namelist_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt);  
  
  extern whirl2xaif::status
  WN2F_implicit_bnd(xml::ostream& xos, WN *wn, XlationContext& ctxt); 
  
  extern whirl2xaif::status
  WN2F_nullify_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt);

  extern whirl2xaif::status
  WN2F_interface_blk(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status
  WN2F_ar_construct(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
}; /* namespace whirl2xaif */

//***************************************************************************

#endif /* wn2xaif_stmt_INCLUDED */
