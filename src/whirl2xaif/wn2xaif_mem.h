// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_mem.h,v 1.3 2003/05/23 18:33:48 eraxxon Exp $
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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_mem.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f_load_store.h
//
//***************************************************************************

#ifndef wn2xaif_mem_INCLUDED
#define wn2xaif_mem_INCLUDED

#include "wn2xaif.h"

namespace whirl2xaif { // FIXME

extern 
WN2F_STATUS xlate_LDA(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
extern 
WN2F_STATUS xlate_LDID(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern 
WN2F_STATUS xlate_ILOAD(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern 
WN2F_STATUS xlate_STID(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern 
WN2F_STATUS xlate_ISTORE(xml::ostream& xos, WN *wn, XlationContext& ctxt);

}; /* namespace whirl2xaif */


extern WN2F_STATUS
   xlate_ISTOREX(xml::ostream& xos, WN *wn, XlationContext& ctxt);
extern WN2F_STATUS
   WN2F_pstore(xml::ostream& xos, WN *wn, XlationContext& ctxt);
extern WN2F_STATUS 
   WN2F_mstore(xml::ostream& xos, WN *wn, XlationContext& ctxt);
extern WN2F_STATUS
   WN2F_pstid(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   xlate_ILOADX(xml::ostream& xos, WN *wn, XlationContext& ctxt);
extern WN2F_STATUS 
   WN2F_mload(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS
   xlate_ARRAY(xml::ostream& xos, WN *wn, XlationContext& ctxt);
extern WN2F_STATUS
   WN2F_arrayexp(xml::ostream& xos, WN *wn, XlationContext& ctxt);
extern WN2F_STATUS
   WN2F_arrsection(xml::ostream& xos, WN *wn, XlationContext& ctxt);
extern WN2F_STATUS
   WN2F_triplet(xml::ostream& xos, WN *wn, XlationContext& ctxt);
extern WN2F_STATUS
   WN2F_src_triplet(xml::ostream& xos, WN *wn, XlationContext& ctxt);
extern WN2F_STATUS
   WN2F_where(xml::ostream& xos, WN *wn, XlationContext& ctxt);


extern void WN2F_array_bounds(xml::ostream& xos, 
			      WN *wn, 
			      TY_IDX array_ty,
			      XlationContext& ctxt) ;
extern void WN2F_arrsection_bounds(xml::ostream& xos,
				   WN *wn,
				   TY_IDX array_ty,
				   XlationContext& ctxt) ;

extern void WN2F_String_Argument(xml::ostream&  tokens,
				 WN           *base,
				 WN           *length,
				 XlationContext& ctxt);


extern BOOL WN2F_Is_Address_Preg(WN * wn ,TY_IDX ptr_ty) ;

#endif /* wn2xaif_mem_INCLUDED */

