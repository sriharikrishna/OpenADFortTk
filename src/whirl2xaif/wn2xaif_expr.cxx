// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_expr.cxx,v 1.15 2003/11/13 14:55:36 eraxxon Exp $

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

/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *   Translate a WN expression subtree to Fortran by means of an inorder 
 *   recursive descent traversal of the WHIRL IR.  Note that the routines
 *   to handle statements and loads/stores are in separate source files.
 *   Recursive translation of WN nodes should only use WN2F_Translate()!
 *
 * ====================================================================
 * ====================================================================
 */

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "wn2xaif_expr.h"
#include "whirl2f_common.h"

#include "PUinfo.h"
#include "wn2xaif.h"
#include "ty2xaif.h"
#include "st2xaif.h"
#include "wn2xaif_mem.h"

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//************************** Forward Declarations ***************************

static WN2F_STATUS 
xlate_UnaryOpToIntrinsic(xml::ostream& xos, OPCODE opcode, TY_IDX result_ty,
			 WN* wn, XlationContext& ctxt);

static WN2F_STATUS 
xlate_BinaryOpToIntrinsic(xml::ostream& xos, OPCODE opcode, TY_IDX result_ty,
			  WN *wn0, WN *wn1, XlationContext& ctxt);

#if 0 // REMOVE
static WN2F_STATUS 
xlate_OpToIntrinsic(xml::ostream& xos, OPCODE opcode, WN *wn0, WN *wn1, 
		    XlationContext& ctxt);
#endif

static WN2F_STATUS 
xlate_Operand(xml::ostream& xos, WN *opnd, TY_IDX assumed_ty, 
	      BOOL call_by_value, XlationContext& ctxt);

static WN2F_STATUS 
DumpExprEdge(xml::ostream& xos, UINT eid, UINT srcid, UINT targid, UINT pos);

//***************************************************************************

/*------------------------- Value Conversions -------------------------*/
/*---------------------------------------------------------------------*/

/* Create a mapping from a pair of MTYPEs to the Fortran intrinsic
 * or builtin operation that carries out the conversion.  NULL means
 * that either the conversion is redundant and can be ignored or there
 * is no way we can do it.
 */
static const char *Conv_Op[MTYPE_LAST+1][MTYPE_LAST+1];

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
WN2F_Convert(xml::ostream& xos,
	     MTYPE        from_mtype,
	     MTYPE        to_mtype)
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


/*------------------------- Utility Functions -------------------------*/
/*---------------------------------------------------------------------*/

static WN2F_STATUS 
WN2F_Intr_Funcall(xml::ostream& xos, 
		  WN          *wn,
		  const char  *func_name,
		  INT          first_arg_idx,
		  INT          last_arg_idx,
		  BOOL         call_by_value,
		  XlationContext& ctxt)
{
   /* An intrinsic operator expression to be emitted with function
    * call syntax.  All arguments are passed by value or by reference,
    * i.e. we never have some arguments passed by value and some by 
    * reference, unless we have explicit INTR_OPC_ADRTMP or 
    * INTR_OPC_VALTMP argument expressions. Note that we also
    * handle substring arguments here. 
    */
   INT arg_idx, implicit_args, total_implicit_args;
   TY_IDX opnd_type;

   /* Determine the number of implicit arguments appended to the end
    * of the argument list (i.e. string lengths).
    */
   if  (WN_intrinsic(wn)==INTRN_COUNT)
         last_arg_idx--;

   for (arg_idx = first_arg_idx, total_implicit_args = 0; 
	arg_idx <= last_arg_idx - total_implicit_args; 
	arg_idx++) {
     opnd_type = WN_Tree_Type(WN_kid(wn, arg_idx));
     if (TY_Is_Character_Reference(opnd_type) ||
	 TY_Is_Chararray_Reference(opnd_type)) {
       total_implicit_args++;
     }
   }
   
   /* Append the function-name */
   if  (WN_intrinsic(wn)==INTRN_LENTRIM) {
     xos << "LEN_TRIM";
   } else {
     if (WN_intrinsic(wn)==INTRN_F90INDEX)
       xos << "INDEX";
     else
       Append_Token_String(xos, func_name);
   }
   
   /* Append the argument list to the function reference, skipping
    * implicit character-string-length arguments assumed to be the
    * last ones in the list (see also ST2F_func_header()).
    */
   xos << "(";
   set_XlationContext_no_parenthesis(ctxt);

   switch (WN_intrinsic(wn)) {
   case INTRN_F90INDEX:
   case INTRN_SCAN:
   case INTRN_VERIFY:
     for (arg_idx = first_arg_idx;
	  arg_idx < last_arg_idx ;
	  arg_idx=arg_idx+2) {
       opnd_type = WN_Tree_Type(WN_kid(wn, arg_idx));
       
       if (TY_Is_Character_Reference(opnd_type) ||
	   TY_Is_Chararray_Reference(opnd_type)) {
	 WN2F_String_Argument(xos,
			      WN_kid(wn, arg_idx), /* string base */
			      WN_kid(wn, last_arg_idx), /* string length */
                              ctxt);
       } else {
	 xlate_Operand(xos, WN_kid(wn, arg_idx), opnd_type, 
		       call_by_value, ctxt);
       }
       
       if ((arg_idx) < WN_kid_count(wn) - 1)
	 xos << ",";
     }

     set_XlationContext_has_logical_arg(ctxt);
 
     xlate_Operand(xos, WN_kid(wn, last_arg_idx), opnd_type,
		   call_by_value, ctxt);

     reset_XlationContext_has_logical_arg(ctxt);
     
     
     break;

   default:

     for (arg_idx = first_arg_idx, implicit_args = 0; 
	  arg_idx <= last_arg_idx - implicit_args; 
	  arg_idx++) {
       opnd_type = WN_Tree_Type(WN_kid(wn, arg_idx));
       
       if (TY_Is_Character_Reference(opnd_type) ||
	   TY_Is_Chararray_Reference(opnd_type)) {
	 implicit_args++;
	 WN2F_String_Argument(xos,
			      WN_kid(wn, arg_idx), /* string base */
			      WN_kid(wn, 
				     last_arg_idx - 
				     (total_implicit_args - 
				      implicit_args)), /* string length */
			      ctxt);
	 if ((arg_idx+implicit_args) < WN_kid_count(wn) - 1)
	   xos << ",";
       } else {
	 
	 if ((WN_intrinsic(wn)==INTRN_SUM||   
	      INTRN_MAXVAL||
	      INTRN_PRODUCT) && 
	     (WN_opc_operator(WN_kid0(WN_kid(wn,arg_idx)))== OPR_INTCONST) &&
	     (WN_const_val(WN_kid0(WN_kid(wn,arg_idx)))==0)) {
	   
	 } else {
	   xlate_Operand(xos, WN_kid(wn, arg_idx), opnd_type,
			 call_by_value, ctxt);
	   
	   // if ((arg_idx+implicit_args) < WN_kid_count(wn) - 1) 
	   if ((arg_idx+implicit_args) < last_arg_idx) 
	     if ((WN_intrinsic(wn)==INTRN_SUM ||
		  INTRN_MAXVAL||
		  INTRN_PRODUCT) &&
		 (WN_opc_operator(WN_kid0(WN_kid(wn,arg_idx+1))) 
		  == OPR_INTCONST) &&
		 (WN_const_val(WN_kid0(WN_kid(wn,arg_idx+1)))==0)) {
	       
	     } else {
	       xos << ",";
	     }
	 }
       }
     }
     break;
   }
   xos << ")";
   
   /* TODO: See if we need to cast the resultant value */
   
   return EMPTY_WN2F_STATUS;
} /* WN2F_Intr_Funcall */


static WN2F_STATUS
WN2F_Intr_Infix(xml::ostream& xos, 
		const char  *op_name,
		WN          *opnd0,   /* NULL for unary operation */
		WN          *opnd1,
		BOOL         call_by_value,
		XlationContext& ctxt)
{
   /* An intrinsic operator expression to be emitted with infix operator
    * syntax.  Note that we have already determined what the two arguments
    * are, and any implicit argument have already been ignored.
    */
   const BOOL parenthesize = !XlationContext_no_parenthesis(ctxt);
   const BOOL binary_op = (opnd0 != NULL);

   /* Ensure that subexpressions are parenthesized */
   reset_XlationContext_no_parenthesis(ctxt);
   
   if (parenthesize)
     xos << std::endl << "{infix ";

   if (binary_op)
     xlate_Operand(xos, opnd0, WN_Tree_Type(opnd0), call_by_value, ctxt);
   Append_Token_String(xos, op_name);
   xlate_Operand(xos, opnd1, WN_Tree_Type(opnd1), call_by_value, ctxt);

   if (parenthesize)
     xos << std::endl << "infix}";

   return EMPTY_WN2F_STATUS;
} /* WN2F_Intr_Infix */


static WN2F_STATUS
WN2F_Binary_Substr_Op(xml::ostream& xos, 
		      WN          *op_wn,   /* Top-level expression */
		      const char  *op_name, /* The builtin operator */
		      XlationContext& ctxt)
{
  /* Similar to xlate_BinaryOpToIntrinsic, but we expect the arguments to be
   * string expressions.
   */
  const BOOL parenthesize = !XlationContext_no_parenthesis(ctxt);
  
  /* Ensure that subexpressions are parenthesized */
  reset_XlationContext_no_parenthesis(ctxt);
  
  if (parenthesize)
    xos << std::endl << "{bsubsr ";

  WN2F_String_Argument(xos, WN_kid(op_wn, 0), /* string base */
		       WN_kid(op_wn, 2), /* string length */ ctxt);
  Append_Token_String(xos, op_name);
  WN2F_String_Argument(xos, WN_kid(op_wn, 1), /* string base */
		       WN_kid(op_wn, 3), /* string length */ ctxt);
  if (parenthesize)
    xos << std::endl << "bsubstr}";

  return EMPTY_WN2F_STATUS;
} /* WN2F_Binary_Substr_Op */


/*------------------------- Exported Functions ------------------------*/
/*---------------------------------------------------------------------*/

void WN2F_Expr_initialize(void)
{
   /* Initialize the Conv_Op array (default value is NULL) */
   INT  map;
   for (map = 0; map < NUMBER_OF_CONV_OPS; map++) {
     Conv_Op[Conv_Op_Map[map].from][Conv_Op_Map[map].to] = 
       Conv_Op_Map[map].name;
   }
} /* WN2F_Expr_initialize */


void WN2F_Expr_finalize(void)
{
   /* Nothing to do for now */
}



//***************************************************************************
// Type Conversions
//***************************************************************************

WN2F_STATUS 
WN2F_cvt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_CVT, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_cvt"));

   TranslateWN(xos, WN_kid0(wn), ctxt);

/*  Maybe we shouldn't or needn't  explicitly output these kinds of 
    convert in .w2f.f file----fzhao
*/
//   WN2F_Convert(xos, WN_opc_dtype(wn), WN_opc_rtype(wn));

   return EMPTY_WN2F_STATUS;
}

WN2F_STATUS 
WN2F_cvtl(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX  rtype, dtype;
  
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_CVTL, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_cvtl"));
  
  dtype = WN_Tree_Type(WN_kid0(wn));
  rtype = WN_Tree_Type(wn);
  
  /* Only convert if it is necessary */
  if (Conv_Op[TY_mtype(dtype)][TY_mtype(rtype)] != NULL ) {
    TranslateWN(xos, WN_kid0(wn), ctxt);
    WN2F_Convert(xos, TY_mtype(dtype), TY_mtype(rtype));
  } else {
    TranslateWN(xos, WN_kid0(wn), ctxt);
  }
  return EMPTY_WN2F_STATUS;
}

WN2F_STATUS 
WN2F_tas(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_TAS, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_tas"));
  
  // Just ignore TAS operators for now.  TODO: make sure this
  // is always ok.
  return TranslateWN(xos, WN_kid0(wn), ctxt);
}


//***************************************************************************
// Expression Operators: Unary Operations
//***************************************************************************

WN2F_STATUS
whirl2xaif::xlate_UnaryOp(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_kid_count(wn) == 1, 
		   (DIAG_W2F_UNEXPECTED_NUM_KIDS, 
		    WN_kid_count(wn), 1, WN_opc_name(wn)));

  if (IntrinsicTable.FindXAIFInfo(WN_operator(wn), NULL)) {
    xlate_UnaryOpToIntrinsic(xos, WN_opcode(wn), WN_Tree_Type(wn), 
			     WN_kid0(wn), ctxt);
  } else {
    ASSERT_DBG_FATAL(FALSE, (DIAG_W2F_UNEXPECTED_OPC, "xlate_UnaryOp"));
  }
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
WN2F_realpart(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_REALPART, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_realpart"));
   
   switch (WN_opc_rtype(wn))
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
			MTYPE_name(WN_opc_rtype(wn)),
			"WN2F_realpart"));
      xos << "WN2F_realpart";
      break;
   }
   xos << "(";
   TranslateWN(xos, WN_kid0(wn), ctxt);
   xos << ")";
   
   return EMPTY_WN2F_STATUS;
} /* WN2F_realpart */


WN2F_STATUS 
WN2F_imagpart(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_IMAGPART, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_imagpart"));
   
   switch (WN_opc_rtype(wn))
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
			       MTYPE_name(WN_opc_rtype(wn)), "WN2F_imagpart"));
      xos << "WN2F_imagpart";
      break;
   }
   xos << "(imagpart";
   TranslateWN(xos, WN_kid0(wn), ctxt);
   xos << "imagpart)";
   
   return EMPTY_WN2F_STATUS;
} /* WN2F_imagpart */


WN2F_STATUS 
whirl2xaif::xlate_PAREN(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_PAREN, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_PAREN"));
  
  return TranslateWN(xos, WN_kid0(wn), ctxt);
}


WN2F_STATUS 
whirl2xaif::xlate_RECIP(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_RECIP, 
		    (DIAG_W2F_UNEXPECTED_OPC, "xlate_RECIP"));

   const TY_IDX result_ty = Stab_Mtype_To_Ty(WN_opc_rtype(wn));
   
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
   
   return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
WN2F_rsqrt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_opc_rtype(wn));
   
   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_RSQRT, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_rsqrt"));

   xos << "(1.0/SQRT(";
   set_XlationContext_no_parenthesis(ctxt);
   xlate_Operand(xos, WN_kid(wn,0), result_ty,
		 !TY_Is_Character_Reference(result_ty), ctxt);
   xos << "))";

   return EMPTY_WN2F_STATUS;
} /* WN2F_rsqrt */


WN2F_STATUS 
WN2F_parm(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* TODO: handle opcode parms properly, i.e. take some advantage
    * of the information provided in this packaging of argument 
    * expressions.  For now, just skip these nodes.
    */
   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_PARM, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_parm"));
   if ( TY_is_logical(Ty_Table[WN_ty(wn)]) || 
	XlationContext_is_logical_arg(ctxt)) { //fzhao Jan
     set_XlationContext_has_logical_arg(ctxt);
     TranslateWN(xos, WN_kid0(wn), ctxt);
     reset_XlationContext_has_logical_arg(ctxt);
   } else
     TranslateWN(xos, WN_kid0(wn), ctxt);
   return EMPTY_WN2F_STATUS;

} /* WN2F_parm */


WN2F_STATUS 
WN2F_alloca(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_ALLOCA, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_alloca"));

   xos << "OPR_ALLOCA(";
   TranslateWN(xos,WN_kid0(wn),ctxt);
   xos << ")";

   return EMPTY_WN2F_STATUS;
} /* WN2F_alloca */


WN2F_STATUS 
WN2F_dealloca(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  INT16 n,i;

   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_DEALLOCA, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_dealloca"));

   n = WN_kid_count(wn);

   xos << std::endl << "CALL OPR_DEALLOCA(";
   i = 0 ;
   while (i < n) {
     TranslateWN(xos,WN_kid(wn,i),ctxt);
     if (++i < n)
       xos << ",";
   }
   xos << ")";

   return EMPTY_WN2F_STATUS;
} /* WN2F_dealloca */


//***************************************************************************
// Expression Operators: Binary Operations
//***************************************************************************

extern WN2F_STATUS
whirl2xaif::xlate_BinaryOp(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_kid_count(wn) == 2, 
		   (DIAG_W2F_UNEXPECTED_NUM_KIDS, 
		    WN_kid_count(wn), 2, WN_opc_name(wn)));
  
  if (IntrinsicTable.FindXAIFInfo(WN_operator(wn), NULL)) {
    xlate_BinaryOpToIntrinsic(xos, WN_opcode(wn), WN_Tree_Type(wn), 
			      WN_kid0(wn), WN_kid1(wn), ctxt);
  } else {
    ASSERT_DBG_FATAL(FALSE, (DIAG_W2F_UNEXPECTED_OPC, "xlate_BinaryOp"));
  }
  
  reset_XlationContext_is_logical_operation(ctxt);
  
  return EMPTY_WN2F_STATUS;
}

WN2F_STATUS 
WN2F_complex(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_COMPLEX, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_complex"));
  
  switch (WN_opc_rtype(wn)) {
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
			     MTYPE_name(WN_opc_rtype(wn)), "WN2F_complex"));
    xos << "WN2F_complex";
    break;
  }
  /* No need to parenthesize subexpressions */
  set_XlationContext_no_parenthesis(ctxt);
  
  xos << "("; /* getting real part */
  (void)TranslateWN(xos, WN_kid0(wn), ctxt);
  xos << ","; /* getting imaginary part */
  (void)TranslateWN(xos, WN_kid1(wn), ctxt);
  xos << ")";
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
WN2F_lshr(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_opc_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_LSHR, 
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
  
  return  EMPTY_WN2F_STATUS;
} /* WN2F_lshr */


WN2F_STATUS 
WN2F_bnor(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_opc_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_BNOR, 
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
  
  return  EMPTY_WN2F_STATUS;
} /* WN2F_bnor */


//***************************************************************************
// Expression Operators: Ternary Operations; N-ary Operations
//***************************************************************************

WN2F_STATUS 
WN2F_select(xml::ostream& xos, WN *wn, XlationContext& ctxt)
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
  
  return EMPTY_WN2F_STATUS;
} /* WN2F_select */

WN2F_STATUS 
WN2F_madd(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_opc_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_MADD, 
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
  
  return  EMPTY_WN2F_STATUS;
} /* WN2F_madd */


WN2F_STATUS 
WN2F_msub(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_opc_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_MSUB, 
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
  
  return  EMPTY_WN2F_STATUS;
} /* WN2F_msub */


WN2F_STATUS 
WN2F_nmadd(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_opc_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_NMADD, 
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
  
  return  EMPTY_WN2F_STATUS;
} /* WN2F_nmadd */


WN2F_STATUS 
WN2F_nmsub(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_opc_rtype(wn));
  
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_NMSUB, 
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
  
  return  EMPTY_WN2F_STATUS;
} /* WN2F_nmsub */


// Intrinsics
WN2F_STATUS 
WN2F_intrinsic_op(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  /* An intrinsic operator expression.  Generate the call as is,
   * regardless how the return value is returned, since we know
   * the consumer of the value is the surrounding expression.  This
   * call is not related to the call-info generated by PUinfo.
   * Note that either all or none of the arguments are call-by-value.
   */
  INT   first_arg_idx, last_arg_idx;
  BOOL  by_value;
  
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_INTRINSIC_OP, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_intrinsic_op"));
  
  by_value = INTRN_by_value(WN_intrinsic(wn));
  last_arg_idx = WN_kid_count(wn) - 1;
  first_arg_idx = 0; /* Assume we never return to first argument */
  
  /* Switch on WN_intrinsic(wn) to handle builtin fortran opcodes.
   */
  switch (WN_intrinsic(wn)) {
  case INTRN_I4EXPEXPR: 
  case INTRN_I8EXPEXPR:
  case INTRN_F4EXPEXPR:
  case INTRN_F8EXPEXPR:
  case INTRN_FQEXPEXPR:
  case INTRN_C4EXPEXPR:
  case INTRN_C8EXPEXPR:
  case INTRN_CQEXPEXPR:
  case INTRN_F4I4EXPEXPR:
  case INTRN_F4I8EXPEXPR:
  case INTRN_F8I4EXPEXPR:
  case INTRN_F8I8EXPEXPR:
  case INTRN_FQI4EXPEXPR:
  case INTRN_FQI8EXPEXPR:
  case INTRN_C4I4EXPEXPR:
  case INTRN_C4I8EXPEXPR:
  case INTRN_C8I4EXPEXPR:
  case INTRN_C8I8EXPEXPR:
  case INTRN_CQI4EXPEXPR:
  case INTRN_CQI8EXPEXPR:
    WN2F_Intr_Infix(xos, "**", WN_kid0(wn), WN_kid1(wn), by_value, ctxt);
    break;
    
   case INTRN_CEQEXPR:
     WN2F_Binary_Substr_Op(xos, wn, ".EQ.", ctxt);
     break;
  case INTRN_CNEEXPR:
    WN2F_Binary_Substr_Op(xos, wn, ".NE.", ctxt);
    break;
  case INTRN_CGEEXPR:
    WN2F_Binary_Substr_Op(xos, wn, ".GE.", ctxt);
    break;
  case INTRN_CGTEXPR:
    WN2F_Binary_Substr_Op(xos, wn, ".GT.", ctxt);
    break;
   case INTRN_CLEEXPR:
     WN2F_Binary_Substr_Op(xos, wn, ".LE.", ctxt);
     break;
  case INTRN_CLTEXPR:
    WN2F_Binary_Substr_Op(xos, wn, ".LT.", ctxt);
    break;
    
  case INTRN_U4I1ADRTMP: 
  case INTRN_U4I2ADRTMP: 
  case INTRN_U4I4ADRTMP:
  case INTRN_U4I8ADRTMP: 
  case INTRN_U4F4ADRTMP: 
  case INTRN_U4F8ADRTMP: 
  case INTRN_U4FQADRTMP:
  case INTRN_U4C4ADRTMP: 
  case INTRN_U4C8ADRTMP:
  case INTRN_U4CQADRTMP:
  case INTRN_U4VADRTMP :
  case INTRN_U8I1ADRTMP:
  case INTRN_U8I2ADRTMP:
  case INTRN_U8I4ADRTMP:
  case INTRN_U8I8ADRTMP: 
  case INTRN_U8F4ADRTMP: 
  case INTRN_U8F8ADRTMP: 
  case INTRN_U8FQADRTMP:
  case INTRN_U8C4ADRTMP: 
  case INTRN_U8C8ADRTMP: 
  case INTRN_U8CQADRTMP:
  case INTRN_U8VADRTMP:
    /* Implicit call by reference.  Emit the dereferenced parameter.
     */
    TranslateWN(xos, WN_kid0(wn), ctxt);
    break;
    
  case INTRN_I4VALTMP:
  case INTRN_I8VALTMP: 
  case INTRN_F4VALTMP: 
  case INTRN_F8VALTMP: 
  case INTRN_FQVALTMP:
  case INTRN_C4VALTMP: 
  case INTRN_C8VALTMP:
  case INTRN_CQVALTMP:
    /* Call-by-value.  Assume the ctxt determines when it is
     * necessary to put a %val qualifier around the argument.
     */
    TranslateWN(xos, WN_kid0(wn), ctxt);
    break;     
    
  default:
    WN2F_Intr_Funcall(xos, wn, WN_intrinsic_name((INTRINSIC) WN_intrinsic(wn)),
		      first_arg_idx, last_arg_idx, by_value, ctxt);
    break;
  } /*switch*/
  
  /* TODO: See if we need to cast the resultant value.
   * TY * return_ty = 
   *         WN_intrinsic_return_ty(WN_opcode(wn), WN_intrinsic(wn));
   */
  
  return EMPTY_WN2F_STATUS;
} /* WN2F_intrinsic_op */


//***************************************************************************
// Leaf Operators (Other)
//***************************************************************************

// xlate_INTCONST: Translate a WHIRL integer constant into an XAIF
// constant.
WN2F_STATUS 
whirl2xaif::xlate_INTCONST(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_INTCONST, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_INTCONST"));
  
  // FIXME: use xlate_CONST
  TCON tval = Host_To_Targ(WN_opc_rtype(wn), WN_const_val(wn));
  bool logical = XlationContext_is_logical_arg(ctxt);
  std::string val = TCON2F_translate(tval, logical);  
  const char* ty_str = (logical) ? "bool" : "integer";
  
  xos << BegElem("xaif:Constant") << Attr("vertex_id", ctxt.GetNewVId()) 
      << Attr("type", ty_str) << Attr("value", val) << EndElem;
  
  return EMPTY_WN2F_STATUS;
}

// xlate_CONST: Translate a WHIRL constant (string, floating point,
// etc.) into an XAIF constant.
WN2F_STATUS 
whirl2xaif::xlate_CONST(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_CONST, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_CONST"));

  TY_IDX ty_idx = ST_type(WN_st(wn));
  
  BOOL logical = (TY_is_logical(ty_idx) || XlationContext_is_logical_arg(ctxt));
  std::string val = TCON2F_translate(STC_val(WN_st(wn)), logical);

  const char* ty_str = TranslateTYToSymType(ty_idx); // FIXME: logical
  if (!ty_str) { ty_str = "***"; }  

  xos << BegElem("xaif:Constant") << Attr("vertex_id", ctxt.GetNewVId())
      << Attr("type", ty_str) << Attr("value", val) << EndElem;
  
  return EMPTY_WN2F_STATUS;
}


//***************************************************************************
// Helpers
//***************************************************************************

static WN2F_STATUS
xlate_UnaryOpToIntrinsic(xml::ostream& xos, OPCODE opcode, TY_IDX result_ty,
			 WN* wn, XlationContext& ctxt)
{
  xlate_BinaryOpToIntrinsic(xos, opcode, result_ty, wn, NULL, ctxt);
  return EMPTY_WN2F_STATUS;
}


// xlate_BinaryOpToIntrinsic: 
static WN2F_STATUS
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
  DumpExprEdge(xos, ctxt.GetNewEId(), srcid0, targid, 1);
  if (is_binary_op) { DumpExprEdge(xos, ctxt.GetNewEId(), srcid1, targid, 2); }
  
  return EMPTY_WN2F_STATUS;
}


#if 0 // FIXME REMOVE

// xlate_OpToIntrinsic: Translate a WHIRL unary or binary operator to a
// XAIF function call.  'wn1' should be NULL for a WHIRL unary operator. 
//
// FIXME: right now, this is essentially the same as
// xlate_BinaryOpToIntrinsic.
//
// FIXME: Only string argument are passed by reference; all other
// argument types are passed by value.
static WN2F_STATUS
xlate_OpToIntrinsic(xml::ostream& xos, OPCODE opcode, WN *wn0, WN *wn1, 
		    XlationContext& ctxt)
{
  const BOOL is_binary_op = (wn1 != NULL);
  
  TY_IDX rty = Stab_Mtype_To_Ty(OPCODE_rtype(opcode));
  TY_IDX dty = Stab_Mtype_To_Ty(OPCODE_desc(opcode));
  
  // If there is no descriptor type, assume the operands should be
  // of the same type as the result.  The assumed type of the argument
  // will be the dty.
  if (TY_kind(dty) == KIND_VOID) { dty = rty; }

  UINT targid, srcid0, srcid1;
  
  // Operation
  targid = ctxt.GetNewVId();
  xos << Comment("OpToIntrinsic (FIXME: FuncCall)");
  xos << BegElem("xaif:Intrinsic") << Attr("vertex_id", targid)
      << Attr("name", GET_OPC_FNAME(opcode)) << EndElem;
  
  // First operand, or only operand for unary operation
  srcid0 = ctxt.PeekVId();
  xlate_Operand(xos, wn0, dty, TRUE/*call-by-value*/, ctxt);
  
  // Second operand (only for binary op)
  if (is_binary_op) {
    srcid1 = ctxt.PeekVId();
    xlate_Operand(xos, wn1, dty, TRUE/*call-by-value*/, ctxt);
  }

  // Edges
  DumpExprEdge(xos, ctxt.GetNewEId(), srcid0, targid, 1);
  if (is_binary_op) { DumpExprEdge(xos, ctxt.GetNewEId(), srcid1, targid, 2); }
  
  return EMPTY_WN2F_STATUS;
}

#endif


// xlate_Operand: Translate a WHIRL operand (from an operator) to XAIF.  On success returns the non-zero 'vertex_id' used for the XAIF 
static WN2F_STATUS
xlate_Operand(xml::ostream& xos, WN *opnd, TY_IDX assumed_ty, 
	      BOOL call_by_value, XlationContext& ctxt)
{
  // Translate an operand to a function or built-in operator invocation,
  // based on whether the ctxt indicates that we have call-by-value
  // or call-by-reference.  Also, the ctxt indicates what type of
  // argument we expect. FIXME
  
  // We do not handle substring expressions here, and assume any
  // such expression will be dispatched to a specialty routine
  // such as WN2F_Intr_Infix_SubstrExpr(). FIXME
  ASSERT_DBG_WARN(!TY_Is_Character_Reference(assumed_ty) &&
		  !TY_Is_Chararray_Reference(assumed_ty),
		  (DIAG_W2F_UNEXPECTED_SUBSTRING_REF, "xlate_Operand()"));
  
  if (!call_by_value) {
    WN2F_Offset_Memref(xos, 
		       opnd,                   /* address expression */
		       assumed_ty,             /* address type */
		       TY_pointed(assumed_ty), /* object type */
		       0,                      /* offset from address */
		       ctxt);
  } else {
    TranslateWN(xos, opnd, ctxt);
  }
  
  return EMPTY_WN2F_STATUS;
}


static WN2F_STATUS 
DumpExprEdge(xml::ostream& xos, UINT eid, UINT srcid, UINT targid, UINT pos)
{
  xos << BegElem("xaif:ExpressionEdge") << Attr("edge_id", eid) 
      << Attr("source", srcid) << Attr("target", targid)
      << Attr("position", pos) << EndElem;
  return EMPTY_WN2F_STATUS;
}
