// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_stmt.cxx,v 1.38 2004/06/28 18:52:15 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_stmt.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f_stmt.cxx
//
//***************************************************************************

//************************** System Include Files ***************************

#include <alloca.h>
#include <sstream> //FIXME

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "wn2xaif.h"
#include "wn2xaif_stmt.h"
#include "wn2xaif_mem.h"
#include "wn2xaif_io.h"
#include "st2xaif.h"
#include "ty2xaif.h"

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//************************** Forward Declarations ***************************

//***************************************************************************

static BOOL WN2F_Skip_Stmt(WN *wn) { return FALSE; /* FIXME */ }


//***************************************************************************
// Passive Statements
//***************************************************************************

whirl2xaif::status 
whirl2xaif::xlate_PassiveStmt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  OPERATOR opr = WN_operator(wn);
  
  // Short-circuit handling of the following:
  // NOTE: we could incorporate these two routines into this one
  switch (opr) {
  case OPR_GOTO:
    return xlate_GOTO(xos, wn, ctxt);
  case OPR_LABEL:
    return xlate_LABEL(xos, wn, ctxt);
  case OPR_IO: 
    return xlate_IO(xos, wn, ctxt);
  default:
    break;
  }

  // FIXME: cleanup AGOTO, RETURN, RETURN_VAL, PRAGMA, COMMENT, USE
  //  INTRN_CASSIGNSTMT, INTRN_STOP, INTRN_STOP_F90, IO
  
  xos << BegElem(XAIFStrings.elem_Marker()) 
      << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << " [passive: " << OPERATOR_name(opr) << "]" << EndAttr
      << EndElem;
  
  return whirl2xaif::good;
}


//***************************************************************************
// Structured Control Flow Statements: translation of these is
//   superceded by construction of the control flow graph.
//***************************************************************************

whirl2xaif::status 
whirl2xaif::xlate_BLOCK(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_BLOCK, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_BLOCK"));

  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::WN2F_region(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  Is_True(WN_operator(wn) == OPR_REGION, 
	  ("Invalid operator for WN2F_region()"));  
  Is_True(WN_operator(WN_region_body(wn)) == OPR_BLOCK, 
	  ("Expected OPR_BLOCK as body of OPR_REGION in WN2F_region()"));

  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));

#if 0 // FIXME REMOVE: See whirl2f for full version 
  // WN_region_pragmas(wn)
  set_XlationContext_explicit_region(ctxt);
  
  for (WN* stmt = WN_first(WN_region_body(wn)); stmt != NULL;
       stmt = WN_next(stmt)) {
    if (!WN2F_Skip_Stmt(stmt))
      TranslateWN(xos, stmt, ctxt);
  }
#endif
  
  return whirl2xaif::good;
} /* WN2F_region */


whirl2xaif::status 
whirl2xaif::xlate_DO_LOOP(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_DO_LOOP,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_DO_LOOP"));
  
  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::xlate_DO_WHILE(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_DO_WHILE,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_DO_WHILE"));

  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::xlate_WHILE_DO(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_WHILE_DO,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_WHILE_DO"));
  
  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::xlate_IF(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_IF,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_IF"));
  
  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return whirl2xaif::good;
}


//***************************************************************************
// Unstructured Control Flow Statements
//***************************************************************************

whirl2xaif::status 
whirl2xaif::WN2F_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // REMOVE
  ASSERT_DBG_FATAL(XlationContext_io_stmt(ctxt),
		   (DIAG_W2F_UNEXPECTED_CONTEXT, "WN2F_implied_do"));
  
  /* This is a fortran implied do_loop, which can only occur as an
   * an OPR_IO_ITEM.  We should always be able to regenerate
   * an implied do-loop from this WHIRL tree, and we should safely
   * be able to assert that XlationContext_io_stmt is TRUE.  Strictly
   * speaking this can be viewed as an expression, rather than as a
   * statement, but due to the commonality with regular do-loops
   * we handle it in this module.
   */
  
  /* Start an implied do-loop expression */
  xos << '(';
  
  /* Generate all the expression trees, separated by commas */
  for (INT kid = 4; kid < WN_kid_count(wn); kid++) {
    BOOL emitted = xlate_IO_ITEM(xos, WN_kid(wn, kid), ctxt);
    if (emitted)
      xos << ",";
  }
  
  /* Generate the loop expression */
  ST* idx_name = WN_st(WN_index(wn));
  xlate_SymRef(xos, idx_name,                      /* base-symbol */
		     Stab_Pointer_To(ST_type(idx_name)), /* base-type */
		     ST_type(idx_name),                  /* object-type */
		     0,                                  /* object-ofst */
		     ctxt);
  xos << '=';
  TranslateWN(xos, WN_start(wn), ctxt);
  xos << ',';
  TranslateWN(xos, WN_end(wn), ctxt);
  xos << ',';
  TranslateWN(xos, WN_step(wn), ctxt);
  
  /* Terminate the implied do-loop expression */
  xos << ')';
  
  return whirl2xaif::good;
} /* WN2F_implied_do */


whirl2xaif::status
whirl2xaif::WN2F_noio_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  xos << "(";
  TranslateWN(xos,WN_kid0(wn),ctxt);
  xos << ",";
  TranslateWN(xos,WN_kid1(wn),ctxt);
  xos << "=";
  
  INT numkids = 5;
  for (INT kid = 2;kid<numkids; kid++) {
    TranslateWN(xos,WN_kid(wn,kid),ctxt);
    if (kid < numkids-1)
      xos << ",";
  }
  
  xos << ")";
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::xlate_GOTO(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_GOTO || 
		   WN_operator(wn) == OPR_REGION_EXIT,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_GOTO"));
  
  xos << BegElem(XAIFStrings.elem_Marker()) 
      << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") 
      << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << StmtGotoAnnotVal(WN_label_number(wn)) << EndAttr
      << EndElem;
  
  return whirl2xaif::good;
}


whirl2xaif::status
whirl2xaif::xlate_SWITCH(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_SWITCH,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_SWITCH"));

  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return whirl2xaif::good;
}


whirl2xaif::status
whirl2xaif::WN2F_casegoto(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // REMOVE
  ST *st;
  st = WN_st(wn);
  
  xos << std::endl;
  //  xos << "CASE";
  xos << "IF (";
  TranslateSTUse(xos, st, ctxt);
  std::string val = TCON2F_translate(Host_To_Targ(MTYPE_I4,WN_const_val(wn)),
				     FALSE);
  xos << " .EQ. " << val << ')' << " GO TO " << WN_label_number(wn);
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::WN2F_compgoto(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // REMOVE
  WN         *goto_stmt;
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_COMPGOTO, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_compgoto"));
  ASSERT_DBG_FATAL(WN_operator(WN_compgoto_table(wn)) == OPR_BLOCK,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN_compgoto_table"));
  
  /* Calculate the computed goto for the given cases */
  if (WN_compgoto_num_cases(wn) > 0) {
    xos << std::endl << "GO TO(";
    goto_stmt = WN_first(WN_compgoto_table(wn));
    for (INT32 goto_entry = 0;
	 goto_entry < WN_compgoto_num_cases(wn); 
	 goto_entry++) {
      ASSERT_DBG_FATAL(WN_operator(goto_stmt) == OPR_GOTO,
		       (DIAG_W2F_UNEXPECTED_OPC, "COMPGOTO entry"));
      xos << WN_label_number(goto_stmt);
      if (goto_entry+1 < WN_compgoto_num_cases(wn))
	xos << ',';
      goto_stmt = WN_next(goto_stmt);
    }
    xos << "),";
    
    /* Need to add one to the controlling expression, since it is
     * zero-based in WHIRL and 1-based in Fortran.
     */
    TranslateWN(xos, WN_compgoto_idx(wn), ctxt);
    xos << "+1";
  }
  
  /* Handle the default case as just a regular goto statement */
  if (WN_compgoto_has_default_case(wn))
    xlate_GOTO(xos, WN_kid(wn,2), ctxt);
  
  return whirl2xaif::good;
} /* WN2F_compgoto */


whirl2xaif::status 
whirl2xaif::WN2F_agoto(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // REMOVE
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_AGOTO,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_agoto"));

  xos << BegElem(XAIFStrings.elem_Marker())
      << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << " [***FIXME: agoto]" << EndAttr
      << EndElem;

  xos << std::endl << "GO TO";
  TranslateWN(xos, WN_kid0(wn), ctxt); // FIXME
  
  return whirl2xaif::good;
} /* WN2F_agoto */


whirl2xaif::status 
whirl2xaif::xlate_condBR(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_TRUEBR || 
		   WN_operator(wn) == OPR_FALSEBR,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_condBR"));
  
  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::xlate_RETURN(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_RETURN,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_RETURN"));
  
  xos << BegElem(XAIFStrings.elem_Marker()) 
      << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << " [return]" << EndAttr
      << EndElem;
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::xlate_RETURN_VAL(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_RETURN_VAL,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_RETURN_VAL"));
  
  xos << BegElem(XAIFStrings.elem_Marker()) 
      << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << " [return_val]" << EndAttr
      << EndElem;
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::xlate_LABEL(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_LABEL, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_LABEL"));
  
  xos << BegElem(XAIFStrings.elem_Marker())
      << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") 
      << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << StmtLabelAnnotVal(WN_label_number(wn)) << EndAttr
      << EndElem;
  
  return whirl2xaif::good;
}


//***************************************************************************
// Calls
//***************************************************************************

whirl2xaif::status 
whirl2xaif::xlate_CALL(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // XAIF distinguishes between a subroutine call (statement) and
  // function call (expression).
  
  // FIXME: this is a nearly incomprehensible function.  I've cleaned
  // it up a little, but it needs a lot more work.

  /* Generates a function-call and ensures that the return value
   * is returned into the appropriate context, be it a variable
   * or a register.  Note that intrinsic calls are dispatched to
   * this function from xlate_INTRINSIC_CALL() when appropriate.
   * Make sure the handling of instrinsic ops in wn2f_expr.c is
   * kept up to date with changes that occur here.
   */
  
  // We can't handle ICALLs yet
  OPERATOR opr = WN_operator(wn); 
  ASSERT_DBG_FATAL(opr != OPR_ICALL, (DIAG_W2F_UNEXPECTED_OPC, "OPR_ICALL"));

  // -------------------------------------------------------
  // Gather info...
  // -------------------------------------------------------
  TY_IDX return_ty = WN_Call_Return_Type(wn);
  INT first_arg_idx = WN_Call_First_Arg_Idx(wn);
  INT last_arg_idx = WN_Call_Last_Arg_Idx(wn);
  BOOL is_user_call = FALSE;
  BOOL is_allocate_stmt = FALSE; 
  
  if (opr == OPR_CALL) {
    is_user_call = TRUE;
    const char* nm = ST_name(WN_st(wn));
    if (strcmp(nm, "_ALLOCATE") == 0) {
      is_allocate_stmt = TRUE;
    } else if (strcmp(nm, "_DEALLOCATE") == 0) {
      set_XlationContext_has_no_arr_elmt(ctxt);
      is_allocate_stmt = TRUE;
    } else if (strcmp(nm, "PRESENT") == 0) {
      set_XlationContext_has_no_arr_elmt(ctxt);
    }
  } else if (opr == OPR_PICCALL) {
    is_user_call = TRUE;
  }
  
  // -------------------------------------------------------
  //
  // -------------------------------------------------------
  int xlate_as = 0; // 0: subroutine; 1: function; 2: intrinsic 
  UINT targid = 0; // (FIXME)

  if (opr == OPR_INTRINSIC_CALL) {
    // xlate_INTRINSIC_CALL() has already handled certain intrinsics (FIXME)
    // ... only consider returns through a first non-string parameter here

    const char* inm = INTRINSIC_basename(WN_intrinsic(wn));
    IntrinsicXlationTable::XAIFInfo* info 
      = IntrinsicTable.FindXAIFInfo(opr, inm);
    ASSERT_FATAL(info, (DIAG_UNIMPLEMENTED, 0, "Missing intrinsic!"));

    xlate_as = 2; // intrinsic
    targid = ctxt.GetNewVId();
    xos << BegElem("xaif:Intrinsic") 
	<< Attr("vertex_id", targid) << Attr("name", info->name)
	<< Attr("type", "***") << EndElem;

  } else {
    // Could translate as an XAIF SubroutineCall, FunctionCall or Intrinsic

    // OPR_ICALL: TranslateWN(xos, WN_kid(wn, WN_kid_count(wn) - 1), ctxt);
    ST* st = WN_st(wn);
    ST_TAB* sttab = Scope_tab[ST_level(st)].st_tab;
    SymTabId scopeid = ctxt.FindSymTabId(sttab);
    ASSERT_FATAL(scopeid != 0, (DIAG_UNIMPLEMENTED, 0, "xlate_CALL"));
    const char* funcNm = ST_name(st);

    IntrinsicXlationTable::XAIFInfo* info
      = IntrinsicTable.FindXAIFInfo(opr, funcNm);
    if (info) {
      // Intrinsic
      xlate_as = 2; // intrinsic
      targid = ctxt.GetNewVId();
      xos << BegElem("xaif:Intrinsic")
	  << Attr("vertex_id", targid) << Attr("name", info->name)
	  << Attr("type", "***");
      if (info->key) { xos << IntrinsicKeyAnnot(info->key); }
      xos << EndElem;
    } else if (return_ty != (TY_IDX)0 && TY_kind(return_ty) != KIND_VOID) {
      // FunctionCall
      xlate_as = 1; // function
      xos << BegElem("xaif:FunctionCall") 
	  << Attr("vertex_id", ctxt.GetNewVId())
	  << Attr("scope_id", scopeid) << AttrSymId(st);
    } else {
      // SubroutineCall
      xlate_as = 0; // subroutine
      xos << BegElem("xaif:SubroutineCall")
	  << Attr("statement_id", ctxt.GetNewVId())
	  << Attr("scope_id", scopeid) << AttrSymId(st);
    }
  }

  // -------------------------------------------------------  
  // Determine the number of implicit arguments appended to the end
  // of the argument list (i.e. string lengths).

  INT total_implicit_args = 0;
  TY_IDX arg_ty, kid_ty, parm_ty;


  TYPE_ID fmtry;
  
  for (INT arg_idx = first_arg_idx, total_implicit_args = 0; 
       arg_idx <= last_arg_idx - total_implicit_args; 
       arg_idx++) {
    if (WN_kid(wn, arg_idx) != NULL) {
      OPCODE tempopc = WN_opcode(WN_kid(wn, arg_idx));
      WN* kidofparm = WN_kid0(WN_kid(wn, arg_idx));
      if (WN_operator(kidofparm) != OPR_CALL && 
	  WN_operator(kidofparm) != OPR_INTRINSIC_CALL) {

	arg_ty = WN_Tree_Type(WN_kid(wn, arg_idx));	
	parm_ty = WN_ty(WN_kid(wn,arg_idx));
	
	if (TY_Is_Pointer(arg_ty)) {
	  fmtry = TY_mtype(TY_pointed(arg_ty));
	} else {
	  fmtry = TY_mtype(arg_ty); 
	}
	
	if (fmtry == MTYPE_M) {
	  if (TY_Is_Pointer(parm_ty)) { // FIXME: hack to handle KIND_STRUCT
	    fmtry = TY_pointed(parm_ty);
	    fmtry = TY_mtype(fmtry);
	  }
	}
	
	if ((TY_Is_Character_Reference(arg_ty) 
	     || TY_Is_Chararray_Reference(arg_ty) 
	     || ((TY_Is_Pointer(arg_ty)
		  && TY_mtype(TY_pointed(arg_ty))==MTYPE_M)
		 && (TY_Is_Character_Reference(parm_ty) 
		     || TY_Is_Chararray_Reference(parm_ty))))
	    && !is_allocate_stmt) {
	  total_implicit_args++;
	}
      } else { /*the argument is function call
		* if the return value is Chararray or Character Reference:
		*/
	if (WN_operator(kidofparm) == OPR_CALL) {
	  kid_ty = PU_prototype (Pu_Table[ST_pu(WN_st(kidofparm))]);
	  if (Func_Return_Character (kid_ty))
	    total_implicit_args++; 
	  
	} else {
	  if (WN_operator(kidofparm) == OPR_INTRINSIC_CALL &&
	      WN_intrinsic(kidofparm) == INTRN_CONCATEXPR)
	    total_implicit_args++;
	}
      }
    }
  }

  
  // Append the argument list to the function reference, skipping
  // implicit character-string-length arguments assumed to be the
  // last ones in the list (see also ST2F_func_header()).  Note
  // that we should not need to use any special-casing for 
  // ADRTMP or VALTMP OPR_INTRINSIC_OP nodes, as these should be
  // handled appropriately by TranslateWN().
  BOOL has_stat = FALSE;
  BOOL first_nonemptyarg = FALSE;
  INT implicit_args;
  UINT position = 0; // invalid position id

  UINT srcid = 0; // used for intrinsics (FIXME)

  for (INT arg_idx = first_arg_idx, implicit_args = 0; 
       arg_idx <= last_arg_idx - implicit_args; 
       arg_idx++) {

    if (WN_kid(wn, arg_idx) != NULL) {
      WN* kidofparm = WN_kid0(WN_kid(wn, arg_idx));
      if (WN_operator(kidofparm) != OPR_CALL)
	arg_ty = WN_Tree_Type(WN_kid(wn, arg_idx));
      else
	arg_ty = PU_prototype (Pu_Table[ST_pu(WN_st(kidofparm))]);

      
      position++; // we have seen a valid argument
      if (xlate_as == 0 || xlate_as == 1) { 
	// SubroutineCall, FunctionCall
	xos << BegElem("xaif:Argument");
	if (xlate_as == 0) { xos << Attr("position", position); }
	ctxt.CreateContext(XlationContext::VARREF, wn);// implicit for Argument
      }


      // FIXME
      if (opr == OPR_INTRINSIC_CALL &&
	  INTRN_by_value(WN_intrinsic(wn))) {
	/* Call-by value, but argument should be emitted without the
	 * %val() qualifier. */
	first_nonemptyarg = TRUE;

	srcid = ctxt.PeekVId(); // used for intrinsics
	TranslateWN(xos, WN_kid(wn, arg_idx), ctxt);

      } else if ((WN_operator(kidofparm) != OPR_CALL 
		  && (TY_Is_Character_Reference(arg_ty)  
		      || ((TY_Is_Pointer(arg_ty)
			   && TY_mtype(TY_pointed(arg_ty))==MTYPE_M)
			  && (TY_Is_Character_Reference(parm_ty) 
			      || TY_Is_Chararray_Reference(parm_ty)))) 
		  || WN_operator(kidofparm)==OPR_CALL 
		  && Func_Return_Character(arg_ty) )
		 && !is_allocate_stmt) {
	/* Handle substring arguments here.  These are always assumed
	 * to be passed by reference. For a function result, the length
	 * follows the address - does this look like char fn result?
	 * can't tell, but make good guess..
	 */
	INT len_idx;
	INT cur_idx = arg_idx;
	
	implicit_args++;
	
	if ((is_user_call) && (cur_idx == first_arg_idx) 
	    && (cur_idx == first_arg_idx) 
	    && (WN_kid_count(wn) >= cur_idx + 2) 
	    && (WN_kid(wn,cur_idx+1) != NULL) 
	    && (WN_Parm_By_Value(WN_kid(wn,cur_idx + 1))) 
	    && ((return_ty != 0) && (TY_kind(return_ty) == KIND_VOID))) {
	  len_idx = cur_idx + 1;
	} else {
	  len_idx = last_arg_idx - (total_implicit_args - implicit_args);
	}
	if ( !(first_nonemptyarg && !has_stat) )
	  has_stat = FALSE;
	
	first_nonemptyarg = TRUE;
	WN2F_String_Argument(xos, WN_kid(wn, cur_idx), /* string base */
			     WN_kid(wn, len_idx), /* string length */
			     ctxt);

      } else if (!TY_Is_Pointer(arg_ty) || 
		 (WN_operator(WN_kid(wn, arg_idx)) == OPR_INTRINSIC_OP &&
		  INTR_is_valtmp(WN_intrinsic(WN_kid(wn, arg_idx))))) {
	// Need to explicitly note this as a value parameter.
	if (WN_operator(kidofparm) == OPR_INTRINSIC_CALL &&
	    WN_intrinsic(kidofparm) == INTRN_CONCATEXPR)
	  implicit_args++; 
	  /*parser always generate an extra arg for concat operator*/
	  
	if ( !(first_nonemptyarg && !has_stat) )
	  has_stat = FALSE;
	first_nonemptyarg = TRUE;
	srcid = ctxt.PeekVId(); // used for intrinsics
	TranslateWN(xos, WN_kid(wn, arg_idx), ctxt);


      } else { /* TY_Is_Pointer(arg_ty) */
	/* There is also an implicit string length when the argument
	 * is an array of character strings. */
	if (TY_Is_Chararray_Reference(arg_ty) && !is_allocate_stmt)
	  implicit_args++;
	
	/* Assume call-by-reference parameter passing */
	if ( !(first_nonemptyarg && !has_stat) )
	  has_stat = FALSE;
	
	first_nonemptyarg = TRUE;
	srcid = ctxt.PeekVId(); // used for intrinsics
	xlate_MemRef(xos, 
			   WN_kid(wn, arg_idx), /* address expression */
			   arg_ty,              /* address type */
			   TY_pointed(arg_ty),  /* object type */
			   0,                   /* offset from address */
			   ctxt);
      }
      
      if ((arg_idx+implicit_args) == (last_arg_idx-1)) { 
	if (opr == OPR_CALL && is_allocate_stmt) {
	  if (WN_operator(WN_kid0(WN_kid(wn, last_arg_idx))) == OPR_LDA) {
	    // xos << ",";
	    xos << "STAT=";
	    has_stat=TRUE;
	  } else {
	    arg_idx++;
	  }
	}
      }
      
      if (xlate_as == 0 || xlate_as == 1) { 
	// SubroutineCall, FunctionCall
	ctxt.DeleteContext(); // end VARREF context
	xos << EndElem; // End Argument
      } else {
	// Intrinsic: create an edge
	DumpExprGraphEdge(xos, ctxt.GetNewEId(), srcid, targid, position);
      }
      
    }
  }
  
  reset_XlationContext_has_no_arr_elmt(ctxt);
  
  if (xlate_as == 0 || xlate_as == 1) {
    xos << EndElem; // SubroutineCall or FunctionCall
  }
  
  return whirl2xaif::good;
} /* xlate_CALL */


whirl2xaif::status 
whirl2xaif::xlate_INTRINSIC_CALL(xml::ostream& xos, WN *wn,
				 XlationContext& ctxt)
{
  // Handles all intrinsics that are translated into XAIF statements
  
  WN   *arg_expr;
  TY_IDX arg_ty;
  INT  str_kid, length_kid, first_length_kid;
  BOOL regular_call = FALSE; /* Specially treated intrinsic call? */
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_INTRINSIC_CALL, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_INTRINSIC_CALL"));
  
  switch (WN_intrinsic(wn)) {
  case INTRN_CONCATEXPR:    
    /* In the context of an IO statement, emit the concatenation
     * but disregard the temporary result buffer. */
    
    /* Determine the range of kids denoting the base of the string-
     * arguments and the the length of these strings respectively. */
    str_kid = 1;
    length_kid = first_length_kid = (WN_kid_count(wn) + 2)/2;
    
    /* Emit the concatenation operations */
    WN2F_String_Argument(xos, 
			 WN_kid(wn, str_kid),    /* base of string1 */
			 WN_kid(wn, length_kid), /* length of string1 */
			 ctxt);
    while ((++str_kid) < first_length_kid) {
      length_kid++;
      xos << "//";
      WN2F_String_Argument(xos, 
			   WN_kid(wn, str_kid),    /* base of stringN */
			   WN_kid(wn, length_kid), /* length of stringN */
			   ctxt);
    }
    break;

  case INTRN_CASSIGNSTMT: 
    // string assignment
    // kid 0, 2: base of and length of destination; kid 1, 3: same, for source
    //WN2F_String_Argument(xos, WN_kid(wn,0), WN_kid(wn,2), ctxt);
    //WN2F_String_Argument(xos, WN_kid(wn,1), WN_kid(wn,3), ctxt);
    xos << BegElem(XAIFStrings.elem_Marker()) 
	<< Attr("statement_id", ctxt.GetNewVId())
	<< BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
	<< " [cassignstmt]" << EndAttr << EndElem;
    break;
    
  case INTRN_STOP:
  case INTRN_STOP_F90:
    // Either the F90 or F77 stop
    xos << BegElem(XAIFStrings.elem_Marker()) 
	<< Attr("statement_id", ctxt.GetNewVId())
	<< BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
	<< " [stop]" << EndAttr << EndElem;
    break;
    
  default:
    regular_call = TRUE;
    xlate_CALL(xos, wn, ctxt);
    break;
  }
  
  return whirl2xaif::good;
} /* xlate_INTRINSIC_CALL */


//***************************************************************************
// Other Statements
//***************************************************************************

whirl2xaif::status
whirl2xaif::WN2F_eval(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* This generates code that will not recompile.  Short of
    * some kind of surrounding statement there is no way to do 
    * this in Fortran-77.
    */
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_EVAL, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_eval"));

   xos << "CALL _EVAL(";
   TranslateWN(xos, WN_kid0(wn), ctxt);
   xos << ')';

   return whirl2xaif::good;
} /* WN2F_eval */


whirl2xaif::status
whirl2xaif::xlate_PRAGMA(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_PRAGMA ||
		   WN_operator(wn) == OPR_XPRAGMA, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_PRAGMA"));

  // switch (WN_pragma(apragma))

  xos << BegElem(XAIFStrings.elem_Marker()) 
      << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << " [pragma]" << EndAttr << EndElem;

  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::xlate_PREFETCH(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_PREFETCH ||
		   WN_operator(wn) == OPR_PREFETCHX, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_PREFETCH"));
  
  return whirl2xaif::good;
}


whirl2xaif::status 
whirl2xaif::xlate_COMMENT(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_opcode(wn) == OPC_COMMENT,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_COMMENT"));
  
  // Note: Index_To_Str(WN_GetComment(wn)) returns comment text
  xos << BegElem(XAIFStrings.elem_Marker()) 
      << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << " [comment]" << EndAttr << EndElem;
  
  return whirl2xaif::good;
}

whirl2xaif::status 
whirl2xaif::WN2F_dealloca(xml::ostream& xos, WN *wn, XlationContext& ctxt)
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
   
  return whirl2xaif::good;
} /* WN2F_dealloca */


whirl2xaif::status
whirl2xaif::xlate_USE(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_USE,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_USE"));
  
  const char* nm = ST_name(WN_st(wn));
  xos << BegElem(XAIFStrings.elem_Marker()) 
      << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << " [use " << nm << "]" << EndAttr << EndElem;
  
  return whirl2xaif::good;
}


whirl2xaif::status
whirl2xaif::WN2F_namelist_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  const char *st_name =  ST_name(WN_st(wn));
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_NAMELIST,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_namelist_stmt"));
  if (ST_is_external(WN_st(wn))) {
    ;
  } else {
    xos << "NAMELIST /" << st_name << " /";
    int k ;
    for(k=0;k< WN_kid_count(wn);k++ ) {
      st_name = ST_name(WN_st(WN_kid(wn,k)));
      Set_BE_ST_w2fc_referenced(WN_st(WN_kid(wn,k)));
      if (k==0)
	;
      else
	xos << ",";
      xos << st_name;
    }
  }
  
  return whirl2xaif::good;
} //WN2F_namelist_stmt


whirl2xaif::status
whirl2xaif::WN2F_implicit_bnd(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  xos << "[+-+]";
  return whirl2xaif::good;
}


whirl2xaif::status
whirl2xaif::WN2F_nullify_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  int k ;  
  const char *st_name;
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_NULLIFY,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_nullify_stmt"));

  xos << "NULLIFY (";
  
  for(k=0;k< WN_kid_count(wn);k++ ) {
    st_name = ST_name(WN_st(WN_kid(wn,k)));
    Set_BE_ST_w2fc_referenced(WN_st(WN_kid(wn,k)));
    if (k!=0)
      xos << ",";
    xos << st_name;
    
  }
  xos << ")";
  
  return whirl2xaif::good;
} //WN2F_namelist_stmt


whirl2xaif::status
whirl2xaif::WN2F_interface_blk(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  int           k ;
  ST            **param_st;
  ST            *st = WN_st(wn);
  ST            *rslt = NULL;
  INT           param,num_params;
  INT           first_param;
  TY_IDX        return_ty;
  INT           implicit = 0 ;
  
    
  const char *intface_name = ST_name(st);
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_INTERFACE,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_interface_blk"));
  if (ST_is_external(WN_st(wn))) {
    ;
  } else {
   xos << std::endl;
    xos << "interface ";
    
    if (ST_is_assign_interface(st)) {
      xos << "assignment (";
    }
    
    if (ST_is_operator_interface(st) || ST_is_u_operator_interface(st)){
      xos << "operator (";
    }
    
    if (ST_is_u_operator_interface(st)) 
      xos << ".";

#if 0    
static const char unnamed_interface[] = "unnamed interface"; 
    if (strcmp(intface_name,unnamed_interface)) 
      Append_Token_String(xos, intface_name);
#endif
    
    if (ST_is_u_operator_interface(st))
      xos << ".";
    
    if (ST_is_assign_interface(st) ||
	ST_is_operator_interface(st) ||
	ST_is_u_operator_interface(st))
      xos << ")";
    
    xos << '\n';
    
    for(k=0;k< WN_kid_count(wn);k++ ) { // each kid is OPR_FUNC_ENTRY wn
      num_params = WN_kid_count(WN_kid(wn,k));
      param_st = (ST **)alloca((num_params + 1) * sizeof(ST *));
      for (param = 0; param < num_params; param++) {
	param_st[param] = WN_st(WN_formal(WN_kid(wn,k), param));
      }
      
      st = &St_Table[WN_entry_name(WN_kid(wn,k))];
      TY_IDX       funtype = ST_pu_type(st);
      
      return_ty = Func_Return_Type(funtype);
      
      if (ST_is_in_module(st) ) {
	xos << "module procedure ";
	Append_Token_String(xos, ST_name(st));     
      } else {
	if (return_ty != (TY_IDX) 0 && TY_kind(return_ty) != KIND_VOID) {
          xos << "FUNCTION";
	  
          if (PU_recursive(Get_Current_PU())) {
	    //Prepend_Token_String(xos, "RECURSIVE");
	    xos << "RECURSIVE";
	  }
	  
	  /* Note that we cannot have functions returning pointer types
	   * in Fortran, so we use the corresponding integral type
	   * instead.
	   */
          if (TY_Is_Pointer(return_ty))
	    TY2F_translate(xos, Stab_Mtype_To_Ty(TY_mtype(return_ty)), ctxt);
          else {
	    if (TY_kind(return_ty)==KIND_ARRAY && !TY_is_character(return_ty))
	      TY2F_translate(xos,TY_AR_etype(return_ty), ctxt);
	    else
	      TY2F_translate(xos, return_ty, ctxt);
	  }
	  
	} else { /* subroutine */
	  xos << "SUBROUTINE";
	}
	
	Append_Token_String(xos, ST_name(st));
	
	/* Emit the parameter name-list, if one is present, and skip any
	 * implicit "length" parameters associated with character strings.
	 * Such implicit parameters should be at the end of the parameter list.
	 */
	
	first_param = ST2F_FIRST_PARAM_IDX(funtype);
	BOOL isFirstArg = TRUE; /* become FALSE after first argument has been emitted */
	/* (radu@par.univie.ac.at) */
	if (param_st[first_param] != NULL) {
	  xos << "(";
	  for (param = first_param;
	       param < num_params;
	       param++)
	    {
	      if (implicit){
		param_st[param] = NULL;
		implicit = 0;
	      } else {
		if (STAB_PARAM_HAS_IMPLICIT_LENGTH(param_st[param])) 
		  implicit = 1;
		if (!ST_is_return_var(param_st[param])) {
		  /* separate argument with a comma, if not the first one */
		  /* (radu@par.univie.ac.at) */
		  if (isFirstArg == FALSE)
		    xos << ",";
		  else
		    isFirstArg = FALSE;
		  Append_Token_String(xos,
				      ST_name(param_st[param]));
		  
		  /* Bug: next and last param may be implicit */
		  /* this causes the argument list to end with a comma (radu@par.univie.ac.at) */
		  /* if (param+1 < num_params)
		     /*     xos << ","; */
                   } else
		     rslt = param_st[param];
		
	      }
	    }
	  xos << ")";
	} else {
          /* Use the "()" notation for "no parameters" */
	  xos << "()";
	}
	
	if (rslt !=NULL && strcasecmp(ST_name(st), 
				      ST_name(rslt)) != 0) {
	  /* append the RESULT option only if it is different from the function name */
	  /* (radu@par.univie.ac.at) */
	  xos << "result(";
	  Append_Token_String(xos, ST_name(rslt));
	  xos << ")";
	}
	/* Emit parameter declarations, indented and on a new line */
	
	for (param = first_param; param < num_params ; param++)
	  
	  if (param_st[param] != NULL) {
	    xos << std::endl;
	    TranslateSTDecl(xos, param_st[param], ctxt);
	    if (ST_is_optional_argument(param_st[param])) {
	      xos << std::endl;
	      xos << "OPTIONAL ";
	      Append_Token_String(xos, ST_name(param_st[param]));
	    }
	    if (ST_is_intent_in_argument(param_st[param])) {
	      xos << std::endl;
	      xos << "INTENT(in) ";
	      Append_Token_String(xos, ST_name(param_st[param]));
	    }
	    if (ST_is_intent_out_argument(param_st[param])) {
	      xos << std::endl;
	      xos << "INTENT(out) ";
	      Append_Token_String(xos, ST_name(param_st[param]));
	    }
	  }
	
	xos << "\n";
	xos << std::endl;	
	
	if (return_ty != (TY_IDX) 0 && TY_kind(return_ty) != KIND_VOID)
	  xos << "END FUNCTION";
	else /* subroutine */
	  xos << "END SUBROUTINE";
      }
      
      xos << "\n";
    }

    xos << std::endl;    
    xos << "end interface ";
    xos << std::endl;    
  }
  
  return whirl2xaif::good;
} //WN2F_interface_blk

whirl2xaif::status
whirl2xaif::WN2F_ar_construct(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  xos << "(/";
  for (INT kid = 0; kid < WN_kid_count(wn); kid++) {
    TranslateWN(xos,WN_kid(wn,kid), ctxt);
    if (kid < WN_kid_count(wn)-1)
      xos << ",";
  }
  xos << "/)";
  
  return whirl2xaif::good;
}

