// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_expr.cxx,v 1.7 2003/05/23 18:33:48 eraxxon Exp $
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

#include "Open64BasicTypes.h"

//*************************** User Include Files ****************************

#include "wn2xaif_expr.h"
#include "whirl2f_common.h"

#include "PUinfo.h"
#include "tcon2f.h"
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

static WN2F_STATUS 
xlate_OpToIntrinsic(xml::ostream& xos, OPCODE opcode, WN *wn0, WN *wn1, 
		    XlationContext& ctxt);

static WN2F_STATUS 
xlate_Operand(xml::ostream& xos, WN *opnd, TY_IDX assumed_ty, 
	      BOOL call_by_value, XlationContext& ctxt);

static WN2F_STATUS 
DumpExprEdge(xml::ostream& xos, UINT eid, UINT srcid, UINT targid, UINT pos);

//***************************************************************************

/*---- Fortran names for binary and unary arithmetic operations -------*/
/*---------------------------------------------------------------------*/


/* The builtin Fortran operations will begin with a special character
 * or an alphabetic character, where those beginning with an alphabetic
 * character will be applied like functions and all others will be
 * applied in usual infix format.  When a name begins with '_', it is
 * a whirl2f special symbol to be applied like a function.  It will
 * be implemented in a library made available to be linked in with 
 * compiled whirl2f code.
 */
#define WN2F_IS_ALPHABETIC(opc) \
   ((Opc_Fname[opc][0]>='a' && Opc_Fname[opc][0]<='z') || \
    (Opc_Fname[opc][0]>='A' && Opc_Fname[opc][0]<='Z') || \
    (Opc_Fname[opc][0]=='_'))

#define WN2F_IS_INFIX_OP(opc) \
   (Opc_Fname[opc]!=NULL && !WN2F_IS_ALPHABETIC(opc))

#define WN2F_IS_FUNCALL_OP(opc) \
   (Opc_Fname[opc]!=NULL && WN2F_IS_ALPHABETIC(opc))


/* Mapping from opcodes to Fortran names for arithmetic/logical 
 * operations.  An empty (NULL) name will occur for non-
 * arithmetic/logical opcodes, which must be handled by special
 * handler-functions.  This mapping is dynamically initialized,
 * based on Fname_Map[], in WN2F_Expr_Initialize().
 */
#define NUMBER_OF_OPCODES (OPCODE_LAST+1)
static const char *Opc_Fname[NUMBER_OF_OPCODES];
   

typedef struct Fname_PartialMap
{
   OPCODE      opc;
   const char *fname;
} FNAME_PARTIALMAP;

#define NUMBER_OF_FNAME_PARTIALMAPS \
   sizeof(Fname_Map) / sizeof(FNAME_PARTIALMAP)

// whirlop; xaifexp; xaifname

// FIXME: Convert this to a with an extra value to determine whether
// this is a whirlf funccall or known operator.

// FIXME: convert this to OPR_ as opposed to OPC_ stuff
static const FNAME_PARTIALMAP Fname_Map[] =
{
  // Unary Operator
  {OPC_U8NEG, ".UnaryMinus"},
  {OPC_FQNEG, ".UnaryMinus"},
  {OPC_I8NEG, ".UnaryMinus"},
  {OPC_U4NEG, ".UnaryMinus"},
  {OPC_CQNEG, ".UnaryMinus"},
  {OPC_F8NEG, ".UnaryMinus"},
  {OPC_C8NEG, ".UnaryMinus"},
  {OPC_I4NEG, ".UnaryMinus"},
  {OPC_F4NEG, ".UnaryMinus"},
  {OPC_C4NEG, ".UnaryMinus"},

  {OPC_I4ABS, "ABS"},
  {OPC_F4ABS, "ABS"},
  {OPC_FQABS, "ABS"},
  {OPC_I8ABS, "ABS"},
  {OPC_F8ABS, "ABS"},
  {OPC_F4SQRT, "SQRT"},
  {OPC_C4SQRT, "SQRT"},
  {OPC_FQSQRT, "SQRT"},
  {OPC_CQSQRT, "SQRT"},
  {OPC_F8SQRT, "SQRT"},
  {OPC_C8SQRT, "SQRT"},
  {OPC_I4F4RND, "JNINT"},
  {OPC_I4FQRND, "JIQNNT"},
  {OPC_I4F8RND, "JIDNNT"},
  {OPC_U4F4RND, "JNINT"},
  {OPC_U4FQRND, "JIQNNT"},
  {OPC_U4F8RND, "JIDNNT"},
  {OPC_I8F4RND, "KNINT"},
  {OPC_I8FQRND, "KIQNNT"},
  {OPC_I8F8RND, "KIDNNT"},
  {OPC_U8F4RND, "KNINT"},
  {OPC_U8FQRND, "KIQNNT"},
  {OPC_U8F8RND, "KIDNNT"},
  {OPC_I4F4TRUNC, "JINT"},
  {OPC_I4FQTRUNC, "JIQINT"},
  {OPC_I4F8TRUNC, "JIDINT"},
  {OPC_U4F4TRUNC, "JINT"},
  {OPC_U4FQTRUNC, "JIQINT"},
  {OPC_U4F8TRUNC, "JIDINT"},
  {OPC_I8F4TRUNC, "KINT"},
  {OPC_I8FQTRUNC, "KIQINT"},
  {OPC_I8F8TRUNC, "KIDINT"},
  {OPC_U8F4TRUNC, "KINT"},
  {OPC_U8FQTRUNC, "KIQINT"},
  {OPC_U8F8TRUNC, "KIDINT"},
  {OPC_I4F4CEIL, "CEILING"},
  {OPC_I4FQCEIL, "CEILING"},
  {OPC_I4F8CEIL, "CEILING"},
  {OPC_I8F4CEIL, "CEILING"},
  {OPC_I8FQCEIL, "CEILING"},
  {OPC_I8F8CEIL, "CEILING"},
  {OPC_I4F4FLOOR, "FLOOR"},
  {OPC_I4FQFLOOR, "FLOOR"},
  {OPC_I4F8FLOOR, "FLOOR"},
  {OPC_I8F4FLOOR, "FLOOR"},
  {OPC_I8FQFLOOR, "FLOOR"},
  {OPC_I8F8FLOOR, "FLOOR"},
  {OPC_I4BNOT, "NOT"},
  {OPC_U8BNOT, "NOT"},
  {OPC_I8BNOT, "NOT"},
  {OPC_U4BNOT, "NOT"},
// >> WHIRL 0.30: replace OPC_LNOT by OPC_B and OPC_I4 variant
// TODO WHIRL 0.30: get rid of OPC_I4 variant
  {OPC_BLNOT, ".Not"},
  {OPC_I4LNOT, ".Not"},
// << WHIRL 0.30: replace OPC_LNOT by OPC_B and OPC_I4 variant
  {OPC_U8ADD, ".Add"}, // xaif binary op
  {OPC_FQADD, ".Add"}, // xaif binary op
  {OPC_I8ADD, ".Add"}, // xaif binary op
  {OPC_U4ADD, ".Add"}, // xaif binary op
  {OPC_CQADD, ".Add"}, // xaif binary op
  {OPC_F8ADD, ".Add"}, // xaif binary op
  {OPC_C8ADD, ".Add"}, // xaif binary op
  {OPC_I4ADD, ".Add"}, // xaif binary op
  {OPC_F4ADD, ".Add"}, // xaif binary op
  {OPC_C4ADD, ".Add"}, // xaif binary op
  {OPC_U8SUB, ".Subtract"}, // xaif binary op
  {OPC_FQSUB, ".Subtract"}, // xaif binary op
  {OPC_I8SUB, ".Subtract"}, // xaif binary op
  {OPC_U4SUB, ".Subtract"}, // xaif binary op
  {OPC_CQSUB, ".Subtract"}, // xaif binary op
  {OPC_F8SUB, ".Subtract"}, // xaif binary op
  {OPC_C8SUB, ".Subtract"}, // xaif binary op
  {OPC_I4SUB, ".Subtract"}, // xaif binary op
  {OPC_F4SUB, ".Subtract"}, // xaif binary op
  {OPC_C4SUB, ".Subtract"}, // xaif binary op
  {OPC_U8MPY, ".Multiply"}, // xaif binary op
  {OPC_FQMPY, ".Multiply"}, // xaif binary op
  {OPC_I8MPY, ".Multiply"}, // xaif binary op
  {OPC_U4MPY, ".Multiply"}, // xaif binary op
  {OPC_CQMPY, ".Multiply"}, // xaif binary op
  {OPC_F8MPY, ".Multiply"}, // xaif binary op
  {OPC_C8MPY, ".Multiply"}, // xaif binary op
  {OPC_I4MPY, ".Multiply"}, // xaif binary op
  {OPC_F4MPY, ".Multiply"}, // xaif binary op
  {OPC_C4MPY, ".Multiply"}, // xaif binary op
  {OPC_U8DIV, ".Divide"},
  {OPC_FQDIV, ".Divide"},
  {OPC_I8DIV, ".Divide"},
  {OPC_U4DIV, ".Divide"},
  {OPC_CQDIV, ".Divide"},
  {OPC_F8DIV, ".Divide"},
  {OPC_C8DIV, ".Divide"},
  {OPC_I4DIV, ".Divide"},
  {OPC_F4DIV, ".Divide"},
  {OPC_C4DIV, ".Divide"},
  {OPC_I4MOD, "MOD"},
  {OPC_U8MOD, "MOD"},
  {OPC_I8MOD, "MOD"},
  {OPC_U8MOD, "MOD"},
  {OPC_U4MOD, "MOD"},
  {OPC_I4REM, "MOD"},
  {OPC_U8REM, "MOD"},
  {OPC_I8REM, "MOD"},
  {OPC_U4REM, "MOD"},
  {OPC_I4MAX, "MAX"},
  {OPC_U8MAX, "MAX"},
  {OPC_F4MAX, "MAX"},
  {OPC_FQMAX, "MAX"},
  {OPC_I8MAX, "MAX"},
  {OPC_U4MAX, "MAX"},
  {OPC_F8MAX, "MAX"},
  {OPC_I4MIN, "MIN"},
  {OPC_U8MIN, "MIN"},
  {OPC_F4MIN, "MIN"},
  {OPC_FQMIN, "MIN"},
  {OPC_I8MIN, "MIN"},
  {OPC_U4MIN, "MIN"},
  {OPC_F8MIN, "MIN"},
  {OPC_I4BAND, ".IAnd"},
  {OPC_U8BAND, ".IAnd"},
  {OPC_I8BAND, ".IAnd"},
  {OPC_U4BAND, ".IAnd"},
  {OPC_I4BIOR, ".IOr"},
  {OPC_U8BIOR, ".IOr"},
  {OPC_I8BIOR, ".IOr"},
  {OPC_U4BIOR, ".IOr"},
  {OPC_I4BXOR, "IEOR"},
  {OPC_U8BXOR, "IEOR"},
  {OPC_I8BXOR, "IEOR"},
  {OPC_U4BXOR, "IEOR"},
// >> WHIRL 0.30: replaced OPC_{LAND,LIOR,CAND,CIOR} by OPC_B and OPC_I4 variants
// TODO WHIRL 0.30: get rid of OPC_I4 variants
  {OPC_BLAND, ".And"},
  {OPC_I4LAND, ".And"},
  {OPC_BLIOR, ".Or"},
  {OPC_I4LIOR, ".Or"},
  {OPC_BCAND, ".And"},
  {OPC_I4CAND, ".And"},
  {OPC_BCIOR, ".Or"},
  {OPC_I4CIOR, ".Or"},
// << WHIRL 0.30: replaced OPC_{LAND,LIOR,CAND,CIOR} by OPC_B and OPC_I4 variants
  {OPC_I4SHL, "ISHIFT"},
  {OPC_U8SHL, "ISHIFT"},
  {OPC_I8SHL, "ISHIFT"},
  {OPC_U4SHL, "ISHIFT"},
  {OPC_I4ASHR, "IASHR"},
  {OPC_U8ASHR, "IASHR"},
  {OPC_I8ASHR, "IASHR"},
  {OPC_U4ASHR, "IASHR"},
// >> WHIRL 0.30: replaced OPC_T1{EQ,NE,GT,GE,LT,LE} by OPC_B and OPC_I4 variants
// TODO WHIRL 0.30: get rid of OPC_I4 variants
  {OPC_BU8EQ, ".Equal"},
  {OPC_BFQEQ, ".Equal"},
  {OPC_BI8EQ, ".Equal"},
  {OPC_BU4EQ, ".Equal"},
  {OPC_BCQEQ, ".Equal"},
  {OPC_BF8EQ, ".Equal"},
  {OPC_BC8EQ, ".Equal"},
  {OPC_BI4EQ, ".Equal"},
  {OPC_BF4EQ, ".Equal"},
  {OPC_BC4EQ, ".Equal"},
  {OPC_BU8NE, ".NotEqual"},
  {OPC_BFQNE, ".NotEqual"},
  {OPC_BI8NE, ".NotEqual"},
  {OPC_BU4NE, ".NotEqual"},
  {OPC_BCQNE, ".NotEqual"},
  {OPC_BF8NE, ".NotEqual"},
  {OPC_BC8NE, ".NotEqual"},
  {OPC_BI4NE, ".NotEqual"},
  {OPC_BF4NE, ".NotEqual"},
  {OPC_BC4NE, ".NotEqual"},
  {OPC_BI4GT, ".GreaterThan"},
  {OPC_BU8GT, ".GreaterThan"},
  {OPC_BF4GT, ".GreaterThan"},
  {OPC_BFQGT, ".GreaterThan"},
  {OPC_BI8GT, ".GreaterThan"},
  {OPC_BU4GT, ".GreaterThan"},
  {OPC_BF8GT, ".GreaterThan"},
  {OPC_BI4GE, ".GreaterOrEqual"},
  {OPC_BU8GE, ".GreaterOrEqual"},
  {OPC_BF4GE, ".GreaterOrEqual"},
  {OPC_BFQGE, ".GreaterOrEqual"},
  {OPC_BI8GE, ".GreaterOrEqual"},
  {OPC_BU4GE, ".GreaterOrEqual"},
  {OPC_BF8GE, ".GreaterOrEqual"},
  {OPC_BI4LT, ".LessThan"},
  {OPC_BU8LT, ".LessThan"},
  {OPC_BF4LT, ".LessThan"},
  {OPC_BFQLT, ".LessThan"},
  {OPC_BI8LT, ".LessThan"},
  {OPC_BU4LT, ".LessThan"},
  {OPC_BF8LT, ".LessThan"},
  {OPC_BI4LE, ".LessOrEqual"},
  {OPC_BU8LE, ".LessOrEqual"},
  {OPC_BF4LE, ".LessOrEqual"},
  {OPC_BFQLE, ".LessOrEqual"},
  {OPC_BI8LE, ".LessOrEqual"},
  {OPC_BU4LE, ".LessOrEqual"},
  {OPC_BF8LE, ".LessOrEqual"},
  {OPC_I4U8EQ, ".Equal"},
  {OPC_I4FQEQ, ".Equal"},
  {OPC_I4I8EQ, ".Equal"},
  {OPC_I4U4EQ, ".Equal"},
  {OPC_I4CQEQ, ".Equal"},
  {OPC_I4F8EQ, ".Equal"},
  {OPC_I4C8EQ, ".Equal"},
  {OPC_I4I4EQ, ".Equal"},
  {OPC_I4F4EQ, ".Equal"},
  {OPC_I4C4EQ, ".Equal"},
  {OPC_I4U8NE, ".NotEqual"},
  {OPC_I4FQNE, ".NotEqual"},
  {OPC_I4I8NE, ".NotEqual"},
  {OPC_I4U4NE, ".NotEqual"},
  {OPC_I4CQNE, ".NotEqual"},
  {OPC_I4F8NE, ".NotEqual"},
  {OPC_I4C8NE, ".NotEqual"},
  {OPC_I4I4NE, ".NotEqual"},
  {OPC_I4F4NE, ".NotEqual"},
  {OPC_I4C4NE, ".NotEqual"},
  {OPC_I4I4GT, ".GreaterThan"},
  {OPC_I4U8GT, ".GreaterThan"},
  {OPC_I4F4GT, ".GreaterThan"},
  {OPC_I4FQGT, ".GreaterThan"},
  {OPC_I4I8GT, ".GreaterThan"},
  {OPC_I4U4GT, ".GreaterThan"},
  {OPC_I4F8GT, ".GreaterThan"},
  {OPC_I4I4GE, ".GreaterOrEqual"},
  {OPC_I4U8GE, ".GreaterOrEqual"},
  {OPC_I4F4GE, ".GreaterOrEqual"},
  {OPC_I4FQGE, ".GreaterOrEqual"},
  {OPC_I4I8GE, ".GreaterOrEqual"},
  {OPC_I4U4GE, ".GreaterOrEqual"},
  {OPC_I4F8GE, ".GreaterOrEqual"},
  {OPC_I4I4LT, ".LessThan"},
  {OPC_I4U8LT, ".LessThan"},
  {OPC_I4F4LT, ".LessThan"},
  {OPC_I4FQLT, ".LessThan"},
  {OPC_I4I8LT, ".LessThan"},
  {OPC_I4U4LT, ".LessThan"},
  {OPC_I4F8LT, ".LessThan"},
  {OPC_I4I4LE, ".LessOrEqual"},
  {OPC_I4U8LE, ".LessOrEqual"},
  {OPC_I4F4LE, ".LessOrEqual"}, 
  {OPC_I4FQLE, ".LessOrEqual"},
  {OPC_I4I8LE, ".LessOrEqual"},
  {OPC_I4U4LE, ".LessOrEqual"},
  {OPC_I4F8LE, ".LessOrEqual"}
// << WHIRL 0.30: replaced OPC_T1{EQ,NE,GT,GE,LT,LE} by OPC_B and OPC_I4 variants
}; /* Fname_Map */


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
   {MTYPE_I1, MTYPE_U4, "JZEXT"},
   {MTYPE_I2, MTYPE_U4, "JZEXT"},
   {MTYPE_I4, MTYPE_U4, "JZEXT"},
   {MTYPE_I8, MTYPE_U4, "JZEXT"},
   /*{MTYPE_U1, MTYPE_U4, ""},*/
   /*{MTYPE_U2, MTYPE_U4, ""},*/
   /*{MTYPE_U4, MTYPE_U4, ""},*/
   {MTYPE_U8, MTYPE_U4, "JZEXT"},

   {MTYPE_I1, MTYPE_U8, "KZEXT"},
   {MTYPE_I2, MTYPE_U8, "KZEXT"},
   {MTYPE_I4, MTYPE_U8, "KZEXT"},
   {MTYPE_I8, MTYPE_U8, "KZEXT"},
   /*{MTYPE_U1, MTYPE_U8, ""},*/
   /*{MTYPE_U2, MTYPE_U8, ""},*/
   /*{MTYPE_U4, MTYPE_U8, ""},*/
   /*{MTYPE_U8, MTYPE_U8, ""},*/

   /*{MTYPE_I1, MTYPE_I1, ""},*/
   {MTYPE_I2, MTYPE_I1, "INT1"},
   {MTYPE_I4, MTYPE_I1, "INT1"},
   {MTYPE_I8, MTYPE_I1, "INT1"},
   /*{MTYPE_U1, MTYPE_I1, ""},*/
   {MTYPE_U2, MTYPE_I1, "INT1"},
   {MTYPE_U4, MTYPE_I1, "INT1"},
   {MTYPE_U8, MTYPE_I1, "INT1"},
   {MTYPE_F4, MTYPE_I1, "INT1"},
   {MTYPE_F8, MTYPE_I1, "INT1"},
   {MTYPE_FQ, MTYPE_I1, "INT1"},

   {MTYPE_I1, MTYPE_I2, "INT2"},
   /*{MTYPE_I2, MTYPE_I2, ""},*/
   {MTYPE_I4, MTYPE_I2, "INT2"},
   {MTYPE_I8, MTYPE_I2, "INT2"},
   {MTYPE_U1, MTYPE_I2, "INT2"},
   /*{MTYPE_U2, MTYPE_I2, ""},*/
   {MTYPE_U4, MTYPE_I2, "INT2"},
   {MTYPE_U8, MTYPE_I2, "INT2"},
   {MTYPE_F4, MTYPE_I2, "INT2"},
   {MTYPE_F8, MTYPE_I2, "INT2"},
   {MTYPE_FQ, MTYPE_I2, "INT2"},

   {MTYPE_I1, MTYPE_I4, "INT"},
   {MTYPE_I2, MTYPE_I4, "INT"},
   /*{MTYPE_I4, MTYPE_I4, ""},*/
   {MTYPE_I8, MTYPE_I4, "INT"},
   {MTYPE_U1, MTYPE_I4, "INT"},
   {MTYPE_U2, MTYPE_I4, "INT"},
   /*{MTYPE_U4, MTYPE_I4, ""},*/
   {MTYPE_U8, MTYPE_I4, "INT"},
   {MTYPE_F4, MTYPE_I4, "INT"},
   {MTYPE_F8, MTYPE_I4, "INT"},
   {MTYPE_FQ, MTYPE_I4, "INT"},


   {MTYPE_I1, MTYPE_I8, "INT"},
   {MTYPE_I2, MTYPE_I8, "INT"},
   {MTYPE_I4, MTYPE_I8, "INT"},
   /*{MTYPE_I8, MTYPE_I8, ""},*/
   {MTYPE_U1, MTYPE_I8, "INT"},
   {MTYPE_U2, MTYPE_I8, "INT"},
   {MTYPE_U4, MTYPE_I8, "INT"},
   /*{MTYPE_U8, MTYPE_I8, ""},*/
   {MTYPE_F4, MTYPE_I8, "INT"},
   {MTYPE_F8, MTYPE_I8, "INT"},
   {MTYPE_FQ, MTYPE_I8, "INT"},

   {MTYPE_I1, MTYPE_F4, "REAL"},
   {MTYPE_I2, MTYPE_F4, "REAL"},
   {MTYPE_I4, MTYPE_F4, "REAL"},
   {MTYPE_I8, MTYPE_F4, "REAL"},
   {MTYPE_U1, MTYPE_F4, "REAL"},
   {MTYPE_U2, MTYPE_F4, "REAL"},
   {MTYPE_U4, MTYPE_F4, "REAL"},
   {MTYPE_U8, MTYPE_F4, "REAL"},
   /*{MTYPE_F4, MTYPE_F4, ""},*/
   {MTYPE_F8, MTYPE_F4, "REAL"},
   {MTYPE_FQ, MTYPE_F4, "REAL"},

   {MTYPE_I1, MTYPE_F8, "DBLE"},
   {MTYPE_I2, MTYPE_F8, "DBLE"},
   {MTYPE_I4, MTYPE_F8, "DBLE"},
   {MTYPE_I8, MTYPE_F8, "DBLE"},
   {MTYPE_U1, MTYPE_F8, "DBLE"},
   {MTYPE_U2, MTYPE_F8, "DBLE"},
   {MTYPE_U4, MTYPE_F8, "DBLE"},
   {MTYPE_U8, MTYPE_F8, "DBLE"},
   {MTYPE_F4, MTYPE_F8, "DBLE"},
   /*{MTYPE_F8, MTYPE_F8, ""},*/
   {MTYPE_FQ, MTYPE_F8, "DBLE"},

   {MTYPE_I1, MTYPE_FQ, "QREAL"},
   {MTYPE_I2, MTYPE_FQ, "QREAL"},
   {MTYPE_I4, MTYPE_FQ, "QREAL"},
   {MTYPE_I8, MTYPE_FQ, "QREAL"},
   {MTYPE_U1, MTYPE_FQ, "QREAL"},
   {MTYPE_U2, MTYPE_FQ, "QREAL"},
   {MTYPE_U4, MTYPE_FQ, "QREAL"},
   {MTYPE_U8, MTYPE_FQ, "QREAL"},
   {MTYPE_F4, MTYPE_FQ, "QREAL"},
   {MTYPE_F8, MTYPE_FQ, "QREAL"}
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
   INT  map;

   /* Reset the Opc_Fname array.  This has already been
    * implicitly done by declaring it as static:
    *
    *    OPCODE   opc;
    *    for (opc = 0; opc < NUMBER_OF_OPCODES; opc++)
    *       Opc_Fname[opc] = NULL;
    *
    * Initialize the Opc_Fname array:
    */
   for (map = 0; map < NUMBER_OF_FNAME_PARTIALMAPS; map++) {
     Opc_Fname[Fname_Map[map].opc] = Fname_Map[map].fname;
   }

   /* Initialize the Conv_Op array (default value is NULL) */
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
  
  if (WN2F_IS_INFIX_OP(WN_opcode(wn))) {
    xlate_UnaryOpToIntrinsic(xos, WN_opcode(wn), WN_Tree_Type(wn), 
			     WN_kid0(wn), ctxt);
  } else if (WN2F_IS_FUNCALL_OP(WN_opcode(wn))) {
    xlate_OpToIntrinsic(xos, WN_opcode(wn), WN_kid0(wn), NULL, ctxt);
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
xlate_PAREN(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_PAREN, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_PAREN"));
  
  return TranslateWN(xos, WN_kid0(wn), ctxt);
}

WN2F_STATUS
WN2F_ceil(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_CEIL, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_ceil"));
   ASSERT_DBG_FATAL(WN_kid_count(wn) == 1, 
		    (DIAG_W2F_UNEXPECTED_NUM_KIDS, 
		     WN_kid_count(wn), 1, WN_opc_name(wn)));

   /* Special handling for opcodes that do not have an intrinsic
    * counterpart in compiler versions < v7.00. TODO: define this one.
    */
   //REMOVE ASSERT_DBG_WARN(!W2F_Ansi_Format, (DIAG_W2F_UNEXPECTED_OPC, "WN2F_ceil"));
   
   xlate_OpToIntrinsic(xos, WN_opcode(wn), WN_kid0(wn), NULL, ctxt);

   return EMPTY_WN2F_STATUS;
} /* WN2F_ceil */

WN2F_STATUS
WN2F_floor(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_FLOOR, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_floor"));
   ASSERT_DBG_FATAL(WN_kid_count(wn) == 1, 
		    (DIAG_W2F_UNEXPECTED_NUM_KIDS, 
		     WN_kid_count(wn), 1, WN_opc_name(wn)));

   /* Special handling for opcodes that do not have an intrinsic
    * counterpart in compiler versions < v7.00. TODO: define this one.
    */
   //REMOVE ASSERT_DBG_WARN(!W2F_Ansi_Format, (DIAG_W2F_UNEXPECTED_OPC, "WN2F_floor"));

   xlate_OpToIntrinsic(xos, WN_opcode(wn), WN_kid0(wn), NULL, ctxt);

   return EMPTY_WN2F_STATUS;
} /* WN2F_floor */

WN2F_STATUS 
WN2F_recip(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_opc_rtype(wn));
   
   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_RECIP, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_recip"));

   xos << "(";
   if (TY_mtype(result_ty) == MTYPE_FQ || TY_mtype(result_ty) == MTYPE_CQ)
      xos << "1Q00";
   else if (TY_mtype(result_ty) == MTYPE_F8 || TY_mtype(result_ty) == MTYPE_C8)
      xos << "1D00";
   else
      xos << "1E00";

   xos << "/";
   xlate_Operand(xos, WN_kid(wn,0), result_ty,
		 !TY_Is_Character_Reference(result_ty), ctxt);
   xos << ")";

   return EMPTY_WN2F_STATUS;
} /* WN2F_recip */

WN2F_STATUS 
WN2F_rsqrt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   TY_IDX const result_ty = Stab_Mtype_To_Ty(WN_opc_rtype(wn));
   
   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_RSQRT, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_rsqrt"));

   xos << "(";
   xos << "1.0";
   xos << "/";
   xos << "SQRT";
   xos << "(";
   set_XlationContext_no_parenthesis(ctxt);
   xlate_Operand(xos, WN_kid(wn,0), result_ty,
		 !TY_Is_Character_Reference(result_ty), ctxt);
   xos << ")";
   xos << ")";

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
            XlationContext_is_logical_arg(ctxt)) //fzhao Jan
      {
        set_XlationContext_has_logical_arg(ctxt);
        TranslateWN(xos, WN_kid0(wn), ctxt);
         reset_XlationContext_has_logical_arg(ctxt);
       }
    else
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
  
  // FIXME: tag whether we have an infix/func like op, but otherwise,
  // we don't care.
  if (WN2F_IS_INFIX_OP(WN_opcode(wn))) {
    xlate_BinaryOpToIntrinsic(xos, WN_opcode(wn), WN_Tree_Type(wn), 
			      WN_kid0(wn), WN_kid1(wn), ctxt);
  } else if (WN2F_IS_FUNCALL_OP(WN_opcode(wn))) {
    xlate_OpToIntrinsic(xos, WN_opcode(wn), 
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

   switch (WN_opc_rtype(wn))
   {
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
      ASSERT_DBG_FATAL(FALSE, 
		       (DIAG_W2F_UNEXPECTED_BTYPE,
			MTYPE_name(WN_opc_rtype(wn)),
			"WN2F_complex"));
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
WN2F_ashr(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   TY_IDX const rty = Stab_Mtype_To_Ty(WN_rtype(wn));

   ASSERT_DBG_FATAL(WN_kid_count(wn) == 2, 
		    (DIAG_W2F_UNEXPECTED_NUM_KIDS, 
		     WN_kid_count(wn), 2, WN_opc_name(wn)));

#if 0// REMOVE
   if (W2F_Ansi_Format)
   {
      /* Special handling for opcodes that do not have an intrinsic
       * counterpart in compiler versions < v7.00.
       */
      switch (WN_opcode(wn))
      {
      case OPC_I4ASHR:
	 xos << "I4ASHR";
	 break;
      case OPC_U8ASHR:
	 xos << "U8ASHR";
	 break;
      case OPC_I8ASHR:
	 xos << "I8ASHR";
	 break;
      case OPC_U4ASHR:
	 xos << "I4ASHR";
	 break;
      default:
	 ASSERT_DBG_FATAL(FALSE, 
			  (DIAG_W2F_UNEXPECTED_OPC, "WN2F_ashr"));
	 break;
      }

      /* No need to parenthesize subexpressions */
      set_XlationContext_no_parenthesis(ctxt);

      xos << "(";
      xlate_Operand(xos, WN_kid0(wn), rty, TRUE, /* call-by-value */ ctxt);
      xos << ",";
      xlate_Operand(xos, WN_kid1(wn), rty, TRUE, /* call-by-value */ ctxt);
      xos << ")";
   }
   else
#endif
   {
     /* Has an intrinsic counterpart in compiler versions >= v7.00.
      */
     ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_ASHR, 
		      (DIAG_W2F_UNEXPECTED_OPC, "WN2F_ashr"));
     xlate_OpToIntrinsic(xos, WN_opcode(wn), WN_kid0(wn), WN_kid1(wn), ctxt);
   }
   
   return EMPTY_WN2F_STATUS;
} /* WN2F_ashr */

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
  xlate_Operand(xos, WN_kid(wn, 0), result_ty,
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
   switch (WN_intrinsic(wn))
   {      
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
      WN2F_Intr_Infix(xos, 
		      "**", WN_kid0(wn), WN_kid1(wn), by_value, ctxt);
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
      WN2F_Intr_Funcall(xos, wn, 
			WN_intrinsic_name((INTRINSIC) WN_intrinsic(wn)),
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

  TCON tval = Host_To_Targ(WN_opc_rtype(wn), WN_const_val(wn));
  std::string val = TCON2F_translate(tval, XlationContext_is_logical_arg(ctxt));

  xos << BegElem("xaif:Constant") << Attr("vertex_id", ctxt.GetNewVId()) 
      << Attr("type", "integer") << Attr("value", val) << EndElem;
  
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

  const char* ty_str = TranslateTYToSymType(ty_idx);
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

  UINT targid, srcid0, srcid1;

  // Operation
  targid = ctxt.GetNewVId();
  xos << BegElem("xaif:Intrinsic") << Attr("vertex_id", targid)
      << Attr("name", Opc_Fname[opcode]) << Attr("type", "***") << EndElem;
  
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

// xlate_OpToIntrinsic: Translate a WHIRL unary or binary operator to a
// XAIF function call.  'wn1' should be NULL for a WHIRL unary operator.
// FIXME: Only string argument are passed by reference; all other
// argument types are passed by value.
static WN2F_STATUS
xlate_OpToIntrinsic(xml::ostream& xos, OPCODE opcode, WN *wn0, WN *wn1, 
		    XlationContext& ctxt)
{
  const BOOL binary_op = (wn1 != NULL);
  
  TY_IDX rty = Stab_Mtype_To_Ty(OPCODE_rtype(opcode));
  TY_IDX dty = Stab_Mtype_To_Ty(OPCODE_desc(opcode));
  
  // If there is no descriptor type, assume the operands should be
  // of the same type as the result.  The assumed type of the argument
  // will be the dty.
  if (TY_kind(dty) == KIND_VOID) { dty = rty; }
  
  // Operation
  xos << Comment("OpToIntrinsic (was FuncCall -- FIXME)");
  xos << BegElem("xaif:Intrinsic") << Attr("vertex_id", ctxt.GetNewVId())
      << Attr("name", Opc_Fname[opcode]);
  
  /* No need to parenthesize subexpressions */ // FIXME
  set_XlationContext_no_parenthesis(ctxt);
  
  // First operand, or only operand for unary operation
  xos << "{--" << std::endl;
  xlate_Operand(xos, wn0, dty, TRUE/*call-by-value*/, ctxt);
  xos << "--}" << std::endl;
  
  // Second operand
  if (binary_op) {
    xos << "{--" << std::endl;
    xlate_Operand(xos, wn1, dty, TRUE/*call-by-value*/, ctxt);
    xos << "--}" << std::endl;
  }
  
  return EMPTY_WN2F_STATUS;
}

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
