// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_expr.cxx,v 1.24 2004/02/23 22:33:07 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_expr.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f_expr.cxx
//
//***************************************************************************

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "whirl2xaif.i"
#include "wn2xaif.h"
#include "wn2xaif_expr.h"
#include "wn2xaif_mem.h"
#include "ty2xaif.h"
#include "st2xaif.h"

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//************************** Forward Declarations ***************************

static whirl2xaif::status 
xlate_UnaryOpToIntrinsic(xml::ostream& xos, OPCODE opcode, TY_IDX result_ty,
			 WN* wn, XlationContext& ctxt);

static whirl2xaif::status 
xlate_BinaryOpToIntrinsic(xml::ostream& xos, OPCODE opcode, TY_IDX result_ty,
			  WN *wn0, WN *wn1, XlationContext& ctxt);

static whirl2xaif::status 
xlate_Operand(xml::ostream& xos, WN *opnd, TY_IDX assumed_ty, BOOL callByValue,
	      XlationContext& ctxt);

//***************************************************************************

/*------------------------- Value Conversions -------------------------*/
/*---------------------------------------------------------------------*/

/* Create a mapping from a pair of MTYPEs to the Fortran intrinsic
 * or builtin operation that carries out the conversion.  NULL means
 * that either the conversion is redundant and can be ignored or there
 * is no way we can do it.
 */
static const char *Conv_Op[MTYPE_LAST+1][MTYPE_LAST+1];
static bool Conv_OpInitialized = false;

typedef struct Conv_Op
{
   MTYPE       from, to;
   const char *name;
} CONV_OP;

#define NUMBER_OF_CONV_OPS sizeof(Conv_Op_Map)/sizeof(CONV_OP)

static const CONV_OP Conv_Op_Map[] = 
{
   /* from   |   to   |   op-name */

   /* Only consider conversion to ptr sized unsigned numbers 
    * valid in Fortran.
    */
   {MTYPE_I1, MTYPE_U4, "C_JZEXT"},
   {MTYPE_I2, MTYPE_U4, "C_JZEXT"},
   {MTYPE_I4, MTYPE_U4, "C_JZEXT"},
   {MTYPE_I8, MTYPE_U4, "C_JZEXT"},
   /*{MTYPE_U1, MTYPE_U4, ""},*/
   /*{MTYPE_U2, MTYPE_U4, ""},*/
   /*{MTYPE_U4, MTYPE_U4, ""},*/
   {MTYPE_U8, MTYPE_U4, "C_JZEXT"},

   {MTYPE_I1, MTYPE_U8, "C_KZEXT"},
   {MTYPE_I2, MTYPE_U8, "C_KZEXT"},
   {MTYPE_I4, MTYPE_U8, "C_KZEXT"},
   {MTYPE_I8, MTYPE_U8, "C_KZEXT"},
   /*{MTYPE_U1, MTYPE_U8, ""},*/
   /*{MTYPE_U2, MTYPE_U8, ""},*/
   /*{MTYPE_U4, MTYPE_U8, ""},*/
   /*{MTYPE_U8, MTYPE_U8, ""},*/

   /*{MTYPE_I1, MTYPE_I1, ""},*/
   {MTYPE_I2, MTYPE_I1, "C_INT1"},
   {MTYPE_I4, MTYPE_I1, "C_INT1"},
   {MTYPE_I8, MTYPE_I1, "C_INT1"},
   /*{MTYPE_U1, MTYPE_I1, ""},*/
   {MTYPE_U2, MTYPE_I1, "C_INT1"},
   {MTYPE_U4, MTYPE_I1, "C_INT1"},
   {MTYPE_U8, MTYPE_I1, "C_INT1"},
   {MTYPE_F4, MTYPE_I1, "C_INT1"},
   {MTYPE_F8, MTYPE_I1, "C_INT1"},
   {MTYPE_FQ, MTYPE_I1, "C_INT1"},

   {MTYPE_I1, MTYPE_I2, "C_INT2"},
   /*{MTYPE_I2, MTYPE_I2, ""},*/
   {MTYPE_I4, MTYPE_I2, "C_INT2"},
   {MTYPE_I8, MTYPE_I2, "C_INT2"},
   {MTYPE_U1, MTYPE_I2, "C_INT2"},
   /*{MTYPE_U2, MTYPE_I2, ""},*/
   {MTYPE_U4, MTYPE_I2, "C_INT2"},
   {MTYPE_U8, MTYPE_I2, "C_INT2"},
   {MTYPE_F4, MTYPE_I2, "C_INT2"},
   {MTYPE_F8, MTYPE_I2, "C_INT2"},
   {MTYPE_FQ, MTYPE_I2, "C_INT2"},

   {MTYPE_I1, MTYPE_I4, "C_INT"},
   {MTYPE_I2, MTYPE_I4, "C_INT"},
   /*{MTYPE_I4, MTYPE_I4, ""},*/
   {MTYPE_I8, MTYPE_I4, "C_INT"},
   {MTYPE_U1, MTYPE_I4, "C_INT"},
   {MTYPE_U2, MTYPE_I4, "C_INT"},
   /*{MTYPE_U4, MTYPE_I4, ""},*/
   {MTYPE_U8, MTYPE_I4, "C_INT"},
   {MTYPE_F4, MTYPE_I4, "C_INT"},
   {MTYPE_F8, MTYPE_I4, "C_INT"},
   {MTYPE_FQ, MTYPE_I4, "C_INT"},


   {MTYPE_I1, MTYPE_I8, "C_INT"},
   {MTYPE_I2, MTYPE_I8, "C_INT"},
   {MTYPE_I4, MTYPE_I8, "C_INT"},
   /*{MTYPE_I8, MTYPE_I8, ""},*/
   {MTYPE_U1, MTYPE_I8, "C_INT"},
   {MTYPE_U2, MTYPE_I8, "C_INT"},
   {MTYPE_U4, MTYPE_I8, "C_INT"},
   /*{MTYPE_U8, MTYPE_I8, ""},*/
   {MTYPE_F4, MTYPE_I8, "C_INT"},
   {MTYPE_F8, MTYPE_I8, "C_INT"},
   {MTYPE_FQ, MTYPE_I8, "C_INT"},

   {MTYPE_I1, MTYPE_F4, "C_REAL"},
   {MTYPE_I2, MTYPE_F4, "C_REAL"},
   {MTYPE_I4, MTYPE_F4, "C_REAL"},
   {MTYPE_I8, MTYPE_F4, "C_REAL"},
   {MTYPE_U1, MTYPE_F4, "C_REAL"},
   {MTYPE_U2, MTYPE_F4, "C_REAL"},
   {MTYPE_U4, MTYPE_F4, "C_REAL"},
   {MTYPE_U8, MTYPE_F4, "C_REAL"},
   /*{MTYPE_F4, MTYPE_F4, ""},*/
   {MTYPE_F8, MTYPE_F4, "C_REAL"},
   {MTYPE_FQ, MTYPE_F4, "C_REAL"},

   {MTYPE_I1, MTYPE_F8, "C_DBLE"},
   {MTYPE_I2, MTYPE_F8, "C_DBLE"},
   {MTYPE_I4, MTYPE_F8, "C_DBLE"},
   {MTYPE_I8, MTYPE_F8, "C_DBLE"},
   {MTYPE_U1, MTYPE_F8, "C_DBLE"},
   {MTYPE_U2, MTYPE_F8, "C_DBLE"},
   {MTYPE_U4, MTYPE_F8, "C_DBLE"},
   {MTYPE_U8, MTYPE_F8, "C_DBLE"},
   {MTYPE_F4, MTYPE_F8, "C_DBLE"},
   /*{MTYPE_F8, MTYPE_F8, ""},*/
   {MTYPE_FQ, MTYPE_F8, "C_DBLE"},

   {MTYPE_I1, MTYPE_FQ, "C_QREAL"},
   {MTYPE_I2, MTYPE_FQ, "C_QREAL"},
   {MTYPE_I4, MTYPE_FQ, "C_QREAL"},
   {MTYPE_I8, MTYPE_FQ, "C_QREAL"},
   {MTYPE_U1, MTYPE_FQ, "C_QREAL"},
   {MTYPE_U2, MTYPE_FQ, "C_QREAL"},
   {MTYPE_U4, MTYPE_FQ, "C_QREAL"},
   {MTYPE_U8, MTYPE_FQ, "C_QREAL"},
   {MTYPE_F4, MTYPE_FQ, "C_QREAL"},
   {MTYPE_F8, MTYPE_FQ, "C_QREAL"}
   /*{MTYPE_FQ, MTYPE_FQ, ""}*/
}; /* Conv_Op_Map */

static void 
WN2F_Expr_initialize(void)
{
  /* Initialize the Conv_Op array (default value is NULL) */
  for (INT i = 0; i < NUMBER_OF_CONV_OPS; i++) {
    Conv_Op[Conv_Op_Map[i].from][Conv_Op_Map[i].to] = 
      Conv_Op_Map[i].name;
  }
}

static void
WN2F_Convert(xml::ostream& xos, MTYPE from_mtype, MTYPE to_mtype)
{
   /* We emit a warning message for conversions not covered (TODO: put
    * this warning under a command-line option).  Converts the expression
    * in the given token-buffer to the given mtype.
    */
  xos << "("; // FIXMEprepend
  if (Conv_Op[from_mtype][to_mtype] == NULL) {
    ASSERT_WARN(Conv_Op[from_mtype][to_mtype] != NULL,
		(DIAG_W2F_UNEXPECTED_CVT, 
		 MTYPE_name(from_mtype), MTYPE_name(to_mtype), 
		 "WN2F_Convert"));
    xos << "WN2F_Convert"; // FIXMEprepend
  } else {
    /* Note all these are intrinsics in the mongoose compiler and
     * need not be declared.
     */
    Append_Token_String(xos, Conv_Op[from_mtype][to_mtype]); // FIXMEprepend
  }
  xos << ")";
} /* WN2F_Convert */


//***************************************************************************
// Type Conversion
//***************************************************************************

static void 
InitConvOpMap() // FIXME
{
  if (!Conv_OpInitialized) {
    WN2F_Expr_initialize();
    Conv_OpInitialized = true;
  }
}

whirl2xaif::status 
whirl2xaif::WN2F_cvt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_CVT, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_cvt"));
   InitConvOpMap();

   TranslateWN(xos, WN_kid0(wn), ctxt);

/*  Maybe we shouldn't or needn't  explicitly output these kinds of 
    convert in .w2f.f file----fzhao
*/
//   WN2F_Convert(xos, WN_desc(wn), WN_rtype(wn));

   return whirl2xaif::good;
}

whirl2xaif::status 
whirl2xaif::WN2F_cvtl(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX  rtype, dtype;
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_CVTL, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_cvtl"));
  InitConvOpMap();
  
  dtype = WN_Tree_Type(WN_kid0(wn));
  rtype = WN_Tree_Type(wn);
  
  /* Only convert if it is necessary */
  if (Conv_Op[TY_mtype(dtype)][TY_mtype(rtype)] != NULL ) {
    TranslateWN(xos, WN_kid0(wn), ctxt);
    WN2F_Convert(xos, TY_mtype(dtype), TY_mtype(rtype));
  } else {
    TranslateWN(xos, WN_kid0(wn), ctxt);
  }
  return whirl2xaif::good;
}

whirl2xaif::status 
whirl2xaif::WN2F_tas(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_TAS, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_tas"));
  
  // Just ignore TAS operators for now.  TODO: make sure this
  // is always ok.
  return TranslateWN(xos, WN_kid0(wn), ctxt);
}


//***************************************************************************
// Leaf (Other)
//***************************************************************************

// xlate_INTCONST: Translate a WHIRL integer constant into an XAIF
// constant.
whirl2xaif::status 
whirl2xaif::xlate_INTCONST(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_INTCONST, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_INTCONST"));
  
  // FIXME: use xlate_CONST
  TCON tval = Host_To_Targ(WN_rtype(wn), WN_const_val(wn));
  bool logical = XlationContext_is_logical_arg(ctxt);
  std::string val = TCON2F_translate(tval, logical);  
  const char* ty_str = (logical) ? "bool" : "integer";
  
  xos << BegElem("xaif:Constant") << Attr("vertex_id", ctxt.GetNewVId()) 
      << Attr("type", ty_str) << Attr("value", val) << EndElem;
  
  return whirl2xaif::good;
}

// xlate_CONST: Translate a WHIRL constant (string, floating point,
// etc.) into an XAIF constant.
whirl2xaif::status 
whirl2xaif::xlate_CONST(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_CONST, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_CONST"));

  TY_IDX ty_idx = ST_type(WN_st(wn));
  
  BOOL logical = (TY_is_logical(ty_idx) || XlationContext_is_logical_arg(ctxt));
  std::string val = TCON2F_translate(STC_val(WN_st(wn)), logical);

  const char* ty_str = TranslateTYToSymType(ty_idx); // FIXME: logical
  if (!ty_str) { ty_str = "***"; }  

  xos << BegElem("xaif:Constant") << Attr("vertex_id", ctxt.GetNewVId())
      << Attr("type", ty_str) << Attr("value", val) << EndElem;
  
  return whirl2xaif::good;
}


//***************************************************************************
// Expression Operators: Unary Operations
//***************************************************************************

whirl2xaif::status
whirl2xaif::xlate_UnaryOp(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  OPCODE opc = WN_opcode(wn);
  ASSERT_DBG_FATAL(WN_kid_count(wn) == 1, 
		   (DIAG_W2F_UNEXPECTED_NUM_KIDS, 
		    WN_kid_count(wn), 1, OPCODE_name(opc)));

  if (IntrinsicTable.FindXAIFInfo(WN_operator(wn), NULL)) {
    xlate_UnaryOpToIntrinsic(xos, opc, WN_Tree_Type(wn), WN_kid0(wn), ctxt);
  } else {
    ASSERT_DBG_FATAL(FALSE, (DIAG_W2F_UNEXPECTED_OPC, "xlate_UnaryOp"));
  }
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::WN2F_rsqrt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_rtype(wn));
   
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_RSQRT, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_rsqrt"));

   xos << "(1.0/SQRT(";
   set_XlationContext_no_parenthesis(ctxt);
   xlate_Operand(xos, WN_kid(wn,0), result_ty,
		 !TY_Is_Character_Reference(result_ty), ctxt);
   xos << "))";

   return whirl2xaif::good;
} /* WN2F_rsqrt */


whirl2xaif::status 
whirl2xaif::WN2F_realpart(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_REALPART, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_realpart"));
   
   switch (WN_rtype(wn))
   {
   case MTYPE_F4:
      xos << "REAL";
      break;
   case MTYPE_F8:
      xos << "DBLE";
      break;
   case MTYPE_FQ:
      xos << "QREAL";
 
      break;
   default:
      ASSERT_DBG_FATAL(FALSE, 
		       (DIAG_W2F_UNEXPECTED_BTYPE,
			MTYPE_name(WN_rtype(wn)),
			"WN2F_realpart"));
      xos << "WN2F_realpart";
      break;
   }
   xos << "(";
   TranslateWN(xos, WN_kid0(wn), ctxt);
   xos << ")";
   
   return whirl2xaif::good;
} /* WN2F_realpart */


whirl2xaif::status 
whirl2xaif::WN2F_imagpart(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_IMAGPART, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_imagpart"));
   
   switch (WN_rtype(wn))
   {
   case MTYPE_F4:
      xos << "AIMAG";
      break;
   case MTYPE_F8:
      xos << "DIMAG";
      break;
   case MTYPE_FQ:
      xos << "QIMAG";
      break;
   default:
      ASSERT_DBG_FATAL(FALSE, (DIAG_W2F_UNEXPECTED_BTYPE, 
			       MTYPE_name(WN_rtype(wn)), "WN2F_imagpart"));
      xos << "WN2F_imagpart";
      break;
   }
   xos << "(imagpart";
   TranslateWN(xos, WN_kid0(wn), ctxt);
   xos << "imagpart)";
   
   return whirl2xaif::good;
} /* WN2F_imagpart */


whirl2xaif::status 
whirl2xaif::xlate_PAREN(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_PAREN, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_PAREN"));
  
  return TranslateWN(xos, WN_kid0(wn), ctxt);
}


whirl2xaif::status 
whirl2xaif::xlate_RECIP(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_RECIP, 
		    (DIAG_W2F_UNEXPECTED_OPC, "xlate_RECIP"));

   const TY_IDX result_ty = Stab_Mtype_To_Ty(WN_rtype(wn));
   
   // Translate using a temporary DIV expression [1 / kid0(wn)]
   TYPE_ID rty = TY_mtype(result_ty);
   OPCODE opc = OPCODE_make_op(OPR_DIV, rty, MTYPE_V);

   TCON tcon;
   if (MTYPE_is_integral(rty)) {
     tcon = Host_To_Targ(rty, 1);
   } else if (MTYPE_is_float(rty)) {
     tcon = Host_To_Targ_Float(rty, 1.0);
   } else if (MTYPE_is_complex(rty)) { 
     tcon = Host_To_Targ_Complex(rty, 1, 0);
   } else {
     ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
   }
   WN* wn_one = Make_Const(tcon);
   
   xlate_BinaryOpToIntrinsic(xos, opc, result_ty, wn_one, WN_kid0(wn), ctxt);
   
   WN_DELETE_Tree(wn_one);
   
   return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::WN2F_parm(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  /* TODO: handle opcode parms properly, i.e. take some advantage
   * of the information provided in this packaging of argument 
   * expressions.  For now, just skip these nodes.
   */
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_PARM, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_parm"));
  if ( TY_is_logical(Ty_Table[WN_ty(wn)]) || 
       XlationContext_is_logical_arg(ctxt)) { //fzhao Jan
    set_XlationContext_has_logical_arg(ctxt);
    TranslateWN(xos, WN_kid0(wn), ctxt);
    reset_XlationContext_has_logical_arg(ctxt);
  } else
    TranslateWN(xos, WN_kid0(wn), ctxt);
  return whirl2xaif::good;

} /* WN2F_parm */


whirl2xaif::status 
whirl2xaif::WN2F_alloca(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_ALLOCA, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_alloca"));
  
  xos << "OPR_ALLOCA(";
  TranslateWN(xos,WN_kid0(wn),ctxt);
  xos << ")";
  
  return whirl2xaif::good;
} /* WN2F_alloca */


//***************************************************************************
// Expression Operators: Binary Operations
//***************************************************************************

whirl2xaif::status
whirl2xaif::xlate_BinaryOp(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  OPCODE opc = WN_opcode(wn);
  ASSERT_DBG_FATAL(WN_kid_count(wn) == 2, 
		   (DIAG_W2F_UNEXPECTED_NUM_KIDS, 
		    WN_kid_count(wn), 2, OPCODE_name(opc)));
  
  if (IntrinsicTable.FindXAIFInfo(WN_operator(wn), NULL)) {
    xlate_BinaryOpToIntrinsic(xos, opc, WN_Tree_Type(wn), 
			      WN_kid0(wn), WN_kid1(wn), ctxt);
  } else {
    ASSERT_DBG_FATAL(FALSE, (DIAG_W2F_UNEXPECTED_OPC, "xlate_BinaryOp"));
  }
  
  reset_XlationContext_is_logical_operation(ctxt);
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::WN2F_complex(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_COMPLEX, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_complex"));
  
  switch (WN_rtype(wn)) {
  case MTYPE_C4:
    xos << "CMPLX";
    break;
  case MTYPE_C8:
    xos << "DCMPLX";
    break;
  case MTYPE_CQ:
    xos << "QCMPLX";
    break;
  default:
    ASSERT_DBG_FATAL(FALSE, (DIAG_W2F_UNEXPECTED_BTYPE,
			     MTYPE_name(WN_rtype(wn)), "WN2F_complex"));
    xos << "WN2F_complex";
    break;
  }
  /* No need to parenthesize subexpressions */
  set_XlationContext_no_parenthesis(ctxt);
  
  xos << "("; /* getting real part */
  TranslateWN(xos, WN_kid0(wn), ctxt);
  xos << ","; /* getting imaginary part */
  TranslateWN(xos, WN_kid1(wn), ctxt);
  xos << ")";
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::WN2F_bnor(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_BNOR, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_bnor"));
  
  /* No need to parenthesize subexpressions */
  set_XlationContext_no_parenthesis(ctxt);
  
  xos << "NOT(IOR(";
  xlate_Operand(xos, WN_kid(wn,0), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << ",";
  xlate_Operand(xos, WN_kid(wn,1), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << "))";
  
  return  whirl2xaif::good;
} /* WN2F_bnor */


whirl2xaif::status 
whirl2xaif::WN2F_lshr(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_LSHR, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_lshr"));
  
  /* No need to parenthesize subexpressions */
  set_XlationContext_no_parenthesis(ctxt);
  
  xos << "ISHIFT(";
  xlate_Operand(xos, WN_kid(wn,0), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << ",-(";
  xlate_Operand(xos, WN_kid(wn,1), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << "))";
  
  return  whirl2xaif::good;
} /* WN2F_lshr */


//***************************************************************************
// Expression Operators: Ternary Operations; N-ary Operations
//***************************************************************************

whirl2xaif::status 
whirl2xaif::WN2F_select(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  /* SELECT is almost the same as the F90 MERGE intrinsic, 
     so I will output it that way for now */
  
  xos << "MERGE(";
  TranslateWN(xos, WN_kid1(wn), ctxt);
  xos << ",";  
  TranslateWN(xos, WN_kid2(wn), ctxt);
  xos << ",";  
  TranslateWN(xos, WN_kid0(wn), ctxt);  
  xos << ")";
#if 0
  ASSERT_DBG_WARN(FALSE, (DIAG_UNIMPLEMENTED, "WN2F_select"));
#endif
  
  return whirl2xaif::good;
} /* WN2F_select */


whirl2xaif::status 
whirl2xaif::WN2F_madd(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_MADD, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_madd"));
  
  xos << "(";
  xlate_Operand(xos, WN_kid(wn,1), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << "*";
  xlate_Operand(xos, WN_kid(wn,2), result_ty,
		!TY_Is_Character_Reference(result_ty),ctxt);
  xos << "+";
  xlate_Operand(xos, WN_kid(wn,0), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << ")";
  
  return  whirl2xaif::good;
} /* WN2F_madd */


whirl2xaif::status 
whirl2xaif::WN2F_msub(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_MSUB, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_msub"));
  
  xos << "(";
  xlate_Operand(xos, WN_kid(wn,1), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << "*";
  xlate_Operand(xos, WN_kid(wn,2), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << "-";
  xlate_Operand(xos, WN_kid(wn, 0), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << ")";
  
  return  whirl2xaif::good;
} /* WN2F_msub */


whirl2xaif::status 
whirl2xaif::WN2F_nmadd(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_NMADD, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_nmadd"));
  
  xos << "-(";
  xlate_Operand(xos, WN_kid(wn,1), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << "*";
  xlate_Operand(xos, WN_kid(wn,2), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << "+";
  xlate_Operand(xos, WN_kid(wn, 0), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << ")";
  
  return  whirl2xaif::good;
} /* WN2F_nmadd */


whirl2xaif::status 
whirl2xaif::WN2F_nmsub(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_NMSUB, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_nmsub"));
  
  xos << "-(";
  xlate_Operand(xos, WN_kid(wn,1), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << "*";
  xlate_Operand(xos, WN_kid(wn,2), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << "-";
  xlate_Operand(xos, WN_kid(wn, 0), result_ty,
		!TY_Is_Character_Reference(result_ty), ctxt);
  xos << ")";
  
  return  whirl2xaif::good;
} /* WN2F_nmsub */


//***************************************************************************
// Expression Operators: N-ary Operations
//***************************************************************************

static whirl2xaif::status 
WN2F_Intr_Funcall(xml::ostream& xos, WN* wn, const char* intrnNm,
		  INT begArgIdx, INT endArgIdx, BOOL callByValue, 
		  XlationContext& ctxt);

whirl2xaif::status 
whirl2xaif::xlate_INTRINSIC_OP(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // An intrinsic operator expression (function call). This call is
  // not related to the call-info generated by PUinfo.  Note that
  // either all or none of the arguments are call-by-value.
  OPERATOR opr = WN_operator(wn);
  ASSERT_DBG_FATAL(opr == OPR_INTRINSIC_OP, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_INTRINSIC_OP"));
  
  INTRINSIC intrn = WN_intrinsic(wn);
  BOOL by_value = INTRN_by_value(intrn);
  INT begArgIdx = 0; // Assume we never return to first argument
  INT endArgIdx = WN_kid_count(wn) - 1;
  
  const char* inm = INTRINSIC_basename(intrn);
  IntrinsicXlationTable::XAIFInfo* info
    = IntrinsicTable.FindXAIFInfo(opr, inm);
  ASSERT_FATAL(info, (DIAG_UNIMPLEMENTED, WN_intrinsic_name(intrn)));
  
  if ((strcmp(inm, "ADRTMP") == 0) || (strcmp(inm, "VALTMP") == 0)) {
    // Special cases:
    //   ADRTMP: Call-by-reference.  Emit the dereferenced parameter.
    //   VALTMP: Call-by-value.  Assume 'ctxt' determines when it
    //     is necessary to put a %val qualifier around the argument.
    TranslateWN(xos, WN_kid0(wn), ctxt);
  } else {
    // General case
    WN2F_Intr_Funcall(xos, wn, info->name, 
		      begArgIdx, endArgIdx, by_value, ctxt);
  }
  
  return whirl2xaif::good;
} /* xlate_INTRINSIC_OP */


static whirl2xaif::status 
WN2F_Intr_Funcall(xml::ostream& xos, WN* wn, const char* intrnNm,
		  INT begArgIdx, INT endArgIdx, BOOL callByValue, 
		  XlationContext& ctxt)
{
  /* An intrinsic operator expression to be emitted with function
   * call syntax.  All arguments are passed by value or by reference,
   * i.e. we never have some arguments passed by value and some by 
   * reference, unless we have explicit INTR_OPC_ADRTMP or 
   * INTR_OPC_VALTMP argument expressions. Note that we also
   * handle substring arguments here. 
   */
  
  /* Determine the number of implicit arguments appended to the end
   * of the argument list (i.e. string lengths).
   */
  if (WN_intrinsic(wn) == INTRN_COUNT) {
    endArgIdx--;
  }
  
  INT argIdx = begArgIdx, total_implicit_args = 0;
  TY_IDX opnd_type;
  for ( ; argIdx <= endArgIdx - total_implicit_args; argIdx++) {
    opnd_type = WN_Tree_Type(WN_kid(wn, argIdx));
    if (TY_Is_Character_Reference(opnd_type) ||
	TY_Is_Chararray_Reference(opnd_type)) {
      total_implicit_args++;
    }
  }
  
  // Emit Intrinsic name
  UINT targid = ctxt.GetNewVId();
  xos << BegElem("xaif:Intrinsic") 
      << Attr("vertex_id", targid) << Attr("name", intrnNm)
      << Attr("type", "***") << EndElem;
   
  // Emit Intrinsic argument list, skipping implicit
  // character-string-length arguments assumed to be the last ones in
  // the list (see also ST2F_func_header()).
  UINT srcid = 0;
  UINT position = 0;
  switch (WN_intrinsic(wn)) {
  case INTRN_F90INDEX: // FIXME
  case INTRN_SCAN:
  case INTRN_VERIFY: {
    for (argIdx = begArgIdx; argIdx < endArgIdx; argIdx = argIdx + 2) {
      opnd_type = WN_Tree_Type(WN_kid(wn, argIdx));
      
      position++;
      srcid = ctxt.PeekVId();
      if (TY_Is_Character_Reference(opnd_type) ||
	  TY_Is_Chararray_Reference(opnd_type)) {
	WN2F_String_Argument(xos, WN_kid(wn, argIdx) /* string base */,
			     WN_kid(wn, endArgIdx) /* string len */, ctxt);
      } else {
	xlate_Operand(xos, WN_kid(wn, argIdx), opnd_type, callByValue, ctxt);
      }
      DumpExprGraphEdge(xos, ctxt.GetNewEId(), srcid, targid, position);
    }
    
    set_XlationContext_has_logical_arg(ctxt);
    position++;
    srcid = ctxt.PeekVId();
    xlate_Operand(xos, WN_kid(wn, endArgIdx), opnd_type, callByValue, ctxt);
    reset_XlationContext_has_logical_arg(ctxt);
    DumpExprGraphEdge(xos, ctxt.GetNewEId(), srcid, targid, position);
    break;
  }
  default: {
    
    INT implicit_args = 0;
    for (argIdx = begArgIdx; argIdx <= endArgIdx - implicit_args; argIdx++) {
      opnd_type = WN_Tree_Type(WN_kid(wn, argIdx));
      
      position++;
      srcid = ctxt.PeekVId();
      if (TY_Is_Character_Reference(opnd_type) ||
	  TY_Is_Chararray_Reference(opnd_type)) {
	implicit_args++;
	INT strlIdx = (endArgIdx - (total_implicit_args - implicit_args));
	WN2F_String_Argument(xos, WN_kid(wn, argIdx) /* string base */,
			     WN_kid(wn, strlIdx) /* string len */, ctxt);
      } else {
	xlate_Operand(xos, WN_kid(wn, argIdx), opnd_type, callByValue, ctxt);
      }
      DumpExprGraphEdge(xos, ctxt.GetNewEId(), srcid, targid, position);

    }
    break;
  }
  } /* switch */
  
  return whirl2xaif::good;
} /* WN2F_Intr_Funcall */


//***************************************************************************
// Helpers
//***************************************************************************

static whirl2xaif::status
xlate_UnaryOpToIntrinsic(xml::ostream& xos, OPCODE opcode, TY_IDX result_ty,
			 WN* wn, XlationContext& ctxt)
{
  xlate_BinaryOpToIntrinsic(xos, opcode, result_ty, wn, NULL, ctxt);
  return whirl2xaif::good;
}


// xlate_BinaryOpToIntrinsic: 
static whirl2xaif::status
xlate_BinaryOpToIntrinsic(xml::ostream& xos, OPCODE opcode, TY_IDX result_ty,
			  WN* wn0, WN* wn1, XlationContext& ctxt)
{
  BOOL is_binary_op = (wn1 != NULL);
  
  // Get the expected types for the two operands, dependent on whether
  // or not we have a descriptor type.
  TY_IDX wn0_ty, wn1_ty;
  if (OPCODE_desc(opcode) == MTYPE_V) {
    wn0_ty = wn1_ty = result_ty;
  } else {
    wn0_ty = wn1_ty = Stab_Mtype_To_Ty(OPCODE_desc(opcode));
  }

  IntrinsicXlationTable::XAIFInfo* info // FIXME (perhaps pass?)
    = IntrinsicTable.FindXAIFInfo(OPCODE_operator(opcode), NULL);
  ASSERT_FATAL(info, (DIAG_A_STRING, "intrinsic lookup failed!"));
  UINT targid, srcid0, srcid1;
  
  // Operation
  targid = ctxt.GetNewVId();
  xos << BegElem("xaif:Intrinsic") << Attr("vertex_id", targid)
      << Attr("name", info->name) << Attr("type", "***") << EndElem;
  
  // First operand
  srcid0 = ctxt.PeekVId();
  xlate_Operand(xos, wn0, wn0_ty, TRUE/*call-by-value*/, ctxt);
  
  // Second operand (only for binary op)
  if (is_binary_op) {
    srcid1 = ctxt.PeekVId();
    xlate_Operand(xos, wn1, wn1_ty, TRUE/*call-by-value*/, ctxt);
  }

  // Edges
  DumpExprGraphEdge(xos, ctxt.GetNewEId(), srcid0, targid, 1);
  if (is_binary_op) { 
    DumpExprGraphEdge(xos, ctxt.GetNewEId(), srcid1, targid, 2); 
  }
  
  return whirl2xaif::good;
}


// xlate_Operand: Translate a WHIRL operand (from an operator) to XAIF.
static whirl2xaif::status
xlate_Operand(xml::ostream& xos, WN *opnd, TY_IDX assumed_ty, 
	      BOOL callByValue, XlationContext& ctxt)
{
  // Translate an operand to a function or built-in operator invocation,
  // based on whether the ctxt indicates that we have call-by-value
  // or call-by-reference.  Also, the ctxt indicates what type of
  // argument we expect. FIXME
  
  // We do not handle substring expressions here, and assume any
  // such expression will be dispatched to another. 
  ASSERT_DBG_WARN(!TY_Is_Character_Reference(assumed_ty) &&
		  !TY_Is_Chararray_Reference(assumed_ty),
		  (DIAG_W2F_UNEXPECTED_SUBSTRING_REF, "xlate_Operand()"));
  
  if (!callByValue) {
    xlate_MemRef(xos, 
		       opnd,                   /* address expression */
		       assumed_ty,             /* address type */
		       TY_pointed(assumed_ty), /* object type */
		       0,                      /* offset from address */
		       ctxt);
  } else {
    TranslateWN(xos, opnd, ctxt);
  }
  
  return whirl2xaif::good;
}

