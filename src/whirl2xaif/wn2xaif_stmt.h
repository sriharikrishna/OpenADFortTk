// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_stmt.h,v 1.6 2003/06/02 13:43:23 eraxxon Exp $
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
/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *    WN2F_Stmt_Initialize:  
 *       First thing to do in the handler for a func_entry, which
 *       will setup the state for statement translation.
 *
 *    WN2F_Stmt_Finalize:
 *       Last thing we need to do.
 *
 * ====================================================================
 * ====================================================================
 */

/* Some statements can be skipped, based on previous analysis of
 * call and return sites (e.g. storing to/from return registers).
 */
extern BOOL WN2F_Skip_Stmt(WN *stmt);

extern WN2F_STATUS 
xlate_BLOCK(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
WN2F_region(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
WN2F_compgoto(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_DO_LOOP(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
WN2F_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_DO_WHILE(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_WHILE_DO(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_IF(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_GOTO(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
WN2F_agoto(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_condBR(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_RETURN(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_RETURN_VAL(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_LABEL(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS
WN2F_pstore(xml::ostream& xos, WN *wn, XlationContext& ctxt); 



extern WN2F_STATUS 
WN2F_intrinsic_call(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_CALL(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS
WN2F_use_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt);  

extern WN2F_STATUS
WN2F_implicit_bnd(xml::ostream& xos, WN *wn, XlationContext& ctxt); 

extern WN2F_STATUS
WN2F_namelist_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt);  

extern WN2F_STATUS
WN2F_interface_blk(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS
WN2F_switch(xml::ostream& xos, WN *wn, XlationContext& ctxt);  

extern WN2F_STATUS
WN2F_casegoto(xml::ostream& xos, WN *wn, XlationContext& ctxt);  

extern WN2F_STATUS 
xlate_PREFETCH(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
WN2F_eval(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS
WN2F_nullify_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS
WN2F_ar_construct(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS
WN2F_noio_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt);

#endif /* wn2xaif_stmt_INCLUDED */
