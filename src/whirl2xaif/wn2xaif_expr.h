// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_expr.h,v 1.7 2003/11/26 14:49:04 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_expr.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f_expr.h
//
//***************************************************************************

#ifndef wn2xaif_expr_INCLUDED
#define wn2xaif_expr_INCLUDED

#include "wn2xaif.h"

extern void WN2F_Expr_initialize(void);
extern void WN2F_Expr_finalize(void);

//***************************************************************************
// Expression Operators: Unary Operations
//***************************************************************************

namespace whirl2xaif {

extern WN2F_STATUS 
xlate_UnaryOp(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_PAREN(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_RECIP(xml::ostream& xos, WN *wn, XlationContext& ctxt);

}; /* namespace whirl2xaif */

//***************************************************************************
// Expression Operators: Binary Operations
//***************************************************************************

namespace whirl2xaif {

extern WN2F_STATUS 
xlate_BinaryOp(xml::ostream& xos, WN *wn, XlationContext& ctxt);

}; /* namespace whirl2xaif */

//***************************************************************************
// Leaf Operators (Other)
//***************************************************************************

namespace whirl2xaif {

extern WN2F_STATUS 
xlate_CONST(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
xlate_INTCONST(xml::ostream& xos, WN *wn, XlationContext& ctxt);

}; /* namespace whirl2xaif */


//***************************************************************************

extern WN2F_STATUS 
   xlate_INTRINSIC_OP(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_tas(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_select(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_cvt(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_cvtl(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_realpart(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_imagpart(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_complex(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_lshr(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_bnor(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_rsqrt(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_madd(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_msub(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_nmadd(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_nmsub(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_parm(xml::ostream& xos, WN *wn, XlationContext& ctxt);

extern WN2F_STATUS 
   WN2F_alloca(xml::ostream& xos, WN *wn, XlationContext& ctxt) ;

extern WN2F_STATUS 
   WN2F_dealloca(xml::ostream& xos, WN *wn, XlationContext& ctxt) ;

#endif /* wn2xaif_expr_INCLUDED */

