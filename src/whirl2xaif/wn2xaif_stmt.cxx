// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_stmt.cxx,v 1.14 2003/08/25 13:58:02 eraxxon Exp $

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

/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *   Translate a WN statement subtree to Fortran by means of an inorder 
 *   recursive descent traversal of the WHIRL IR.  Note that the routines
 *   handle expressions and loads/stores are in separate source files.
 *   Recursive translation of WN nodes should only use WN2F_Translate()!
 *
 *   Conventions:
 *
 *       + Newline characters or comments are prepended to a stmt in
 *         the translation of that stmt.
 *
 *
 * ====================================================================
 * ====================================================================
 */

//************************** System Include Files ***************************

#include <alloca.h>
#include <sstream> //FIXME

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h> /* Open64 basic types */
#include "pf_cg.h"
#include "region_util.h"      /* For RID and RID_map */

//*************************** User Include Files ****************************

#include "whirl2f_common.h"
#include "w2cf_parentize.h"
#include "PUinfo.h"
#include "wn2xaif.h"
#include "st2xaif.h"
#include "ty2xaif.h"
#include "tcon2f.h"
#include "wn2xaif_stmt.h"
#include "wn2xaif_mem.h"
#include "wn2xaif_io.h"
#include "wn2xaif_pragma.h"
#include "init2f.h"

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//************************** Forward Declarations ***************************

extern WN_MAP  W2F_Frequency_Map;   /* Defined in w2f_driver.c */
extern WN_MAP *W2F_Construct_Map;   /* Defined in w2f_driver.c */

//***************************************************************************

/* Lists of return and call sites for the current PU,
 * initialized by means of "PUinfo.h" facilities. */
static RETURNSITE *WN2F_Next_ReturnSite = NULL;


// Find and emit any COMMONS that are initialized.
//   For_all(St_Table,GLOBAL_SYMTAB,WN2F_emit_commons(xos));
struct WN2F_emit_commons {
public:
  WN2F_emit_commons(xml::ostream& xos_) : xos(xos_) { }
  
  void operator() (UINT32,  ST* st)
  {
    //XlationContext& ctxt1 = ctxt; // FIXME (bug in gcc 3.0.4 it seems)
    if (ST_sclass(st) == SCLASS_DGLOBAL) {
      if (ST_is_initialized(st))  {
	if (!Has_Base_Block(st) || ST_class(ST_base_idx(st)) == CLASS_BLOCK) {
	  TranslateSTDecl(xos, st, ctxt);
	}
      }
    }
  }

private:
  xml::ostream& xos;
  XlationContext ctxt;//FIXME
};

//***************************************************************************
// 
//***************************************************************************

WN2F_STATUS 
xlate_BLOCK(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_BLOCK, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_BLOCK"));

  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return EMPTY_WN2F_STATUS;
}

BOOL WN2F_Skip_Stmt(WN *wn) { return FALSE; /* FIXME */ }

WN2F_STATUS 
WN2F_region(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  Is_True(WN_operator(wn) == OPR_REGION, 
	  ("Invalid operator for WN2F_region()"));  
  Is_True(WN_operator(WN_region_body(wn)) == OPR_BLOCK, 
	  ("Expected OPR_BLOCK as body of OPR_REGION in WN2F_region()"));

  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));

#if 0 // REMOVE: See whirl2f for full version 
  // WN_region_pragmas(wn)
  set_XlationContext_explicit_region(ctxt);
  
  for (WN* stmt = WN_first(WN_region_body(wn)); stmt != NULL;
       stmt = WN_next(stmt)) {
    if (!WN2F_Skip_Stmt(stmt))
      TranslateWN(xos, stmt, ctxt);
  }
#endif
  
  return EMPTY_WN2F_STATUS;
} /* WN2F_region */


WN2F_STATUS 
WN2F_compgoto(xml::ostream& xos, WN *wn, XlationContext& ctxt)
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
      const char* label_num = WHIRL2F_number_as_name(WN_label_number(goto_stmt));
      xos << label_num;
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
  
  return EMPTY_WN2F_STATUS;
} /* WN2F_compgoto */


WN2F_STATUS 
xlate_DO_LOOP(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_DO_LOOP,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_DO_LOOP"));
  
  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
WN2F_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // REMOVE
  ASSERT_DBG_FATAL(XlationContext_io_stmt(ctxt) &&
		   XlationContext_no_newline(ctxt),
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
  
  return EMPTY_WN2F_STATUS;
} /* WN2F_implied_do */


WN2F_STATUS 
xlate_DO_WHILE(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_DO_WHILE,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_DO_WHILE"));

  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
xlate_WHILE_DO(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_WHILE_DO,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_WHILE_DO"));
  
  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
xlate_IF(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_IF,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_IF"));
  
  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
xlate_GOTO(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_GOTO || 
		   WN_operator(wn) == OPR_REGION_EXIT,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_GOTO"));
  
  xos << BegElem("xaif:Nop") << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIDAnnotationVal(ctxt.FindWNId(wn))
      << " [goto " << WN_label_number(wn) << "]" << EndAttr
      << EndElem;
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
WN2F_agoto(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // REMOVE
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_AGOTO,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_agoto"));

  xos << BegElem("xaif:Nop") << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIDAnnotationVal(ctxt.FindWNId(wn))
      << " [***FIXME: agoto]" << EndAttr
      << EndElem;

  xos << std::endl << "GO TO";
  TranslateWN(xos, WN_kid0(wn), ctxt); // FIXME
  
  return EMPTY_WN2F_STATUS;
} /* WN2F_agoto */


WN2F_STATUS 
xlate_condBR(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_TRUEBR || 
		   WN_operator(wn) == OPR_FALSEBR,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_condBR"));
  
  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return EMPTY_WN2F_STATUS;
}

WN2F_STATUS 
xlate_RETURN(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_RETURN,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_RETURN"));
  
  xos << BegElem("xaif:Nop") << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIDAnnotationVal(ctxt.FindWNId(wn))
      << " [return]" << EndAttr
      << EndElem;
  
  return EMPTY_WN2F_STATUS;
}

WN2F_STATUS 
xlate_RETURN_VAL(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  Is_True(WN_operator(wn) == OPR_RETURN_VAL,
	  ("Invalid operator for xlate_RETURN_VAL()"));
  
  ASSERT_FATAL(FALSE, (DIAG_UNIMPLEMENTED, "Should not be called."));
  
  return EMPTY_WN2F_STATUS;
}

WN2F_STATUS 
xlate_LABEL(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_LABEL, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_LABEL"));
  
  xos << BegElem("xaif:Nop") << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIDAnnotationVal(ctxt.FindWNId(wn))
      << " [label " << WN_label_number(wn) << "]" << EndAttr
      << EndElem;
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
WN2F_intrinsic_call(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   WN   *arg_expr;
   TY_IDX arg_ty;
   INT   str_kid, length_kid, first_length_kid;
   BOOL regular_call = FALSE; /* Specially treated intrinsic call? */

   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_INTRINSIC_CALL, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_intrinsic_call"));

   switch (WN_intrinsic(wn))
   {
   case INTRN_CONCATEXPR:

      /* In the context of an IO statement, emit the concatenation
       * but disregard the temporary result buffer.
       */
      
      /* Determine the range of kids denoting the base of the string-
       * arguments and the the length of these strings respectively.
       */
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
      xos << std::endl;
      WN2F_String_Argument(xos,
			   WN_kid(wn,0), /* base of destination */
			   WN_kid(wn,2), /* length of base */
			   ctxt);
      xos << "=";
      WN2F_String_Argument(xos, 
			   WN_kid(wn,1), /* base of source */
			   WN_kid(wn,3), /* length of source */
			   ctxt);
      break;

   case INTRN_STOP:
   case INTRN_STOP_F90:
      xos << std::endl;
      // Since this could be either the F90 stop or the F77 stop
      // output the STOP explicitly
      xos << "STOP";

      /* Get the string argument type, where the second argument is
       * expected to be the string-length.
       */
      arg_ty = WN_Tree_Type(WN_kid0(wn));
      arg_expr = WN_Skip_Parm(WN_kid1(wn));
      ASSERT_DBG_WARN(WN_operator(arg_expr) == OPR_INTCONST , 
		      (DIAG_W2F_UNEXPECTED_OPC, 
		       "for INTRN_STOP in WN2F_intrinsic_call"));

      /* Only emit the string argument if it is of length > 0 */
      if (WN_const_val(arg_expr) > 0LL)
      {
	 WN2F_Offset_Memref(xos, 
			    WN_kid0(wn),        /* address expression */
			    arg_ty,             /* address type */
			    TY_pointed(arg_ty), /* object type */
			    0,                  /* offset from address */
			    ctxt);
      }
      break;
     
   default:
      regular_call = TRUE;
      xos << std::endl;
      xlate_CALL(xos, wn, ctxt);
      break;
   }

   return EMPTY_WN2F_STATUS;
} /* WN2F_intrinsic_call */


WN2F_STATUS 
xlate_CALL(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // XAIF distinguishes between a subroutine call (statement) and
  // function call (expression).
  
  /* Generates a function-call and ensures that the return value
   * is returned into the appropriate context, be it a variable
   * or a register.  Note that intrinsic calls are dispatched to
   * this function from WN2F_intrinsic_call() when appropriate.
   * Make sure the handling of instrinsic ops in wn2f_expr.c is
   * kept up to date with changes that occur here.
   */
  
  // We can't handle ICALLs yet
  ASSERT_DBG_FATAL(WN_operator(wn) != OPR_ICALL, 
		   (DIAG_W2F_UNEXPECTED_OPC, "OPR_ICALL"));

  // -------------------------------------------------------
  // Gather info...
  TY_IDX return_ty = 0;
  BOOL is_user_call = FALSE;
  BOOL is_allocate_stmt = FALSE; 
  BOOL return_to_param; // REMOVE
  INT first_arg_idx, last_arg_idx;
  
  if (WN_operator(wn) == OPR_INTRINSIC_CALL) {
    return_to_param = WN_intrinsic_return_to_param(return_ty);
    return_ty = WN_intrinsic_return_ty(WN_opcode(wn), 
				       (INTRINSIC) WN_intrinsic(wn), wn);
    first_arg_idx = (return_to_param? 1 : 0);   
    last_arg_idx = WN_kid_count(wn) - 1;
    
  } else {
    // Only two things vary for CALL, ICALL, and PICCALL nodes: the
    // method used to get the function type and the last_arg_idx.
    TY_IDX func_ty;
    if (WN_operator(wn) == OPR_CALL) {
      is_user_call = TRUE;
      func_ty = ST_pu_type(WN_st(wn));
      last_arg_idx = WN_kid_count(wn) - 1;
      
      if (strcmp(ST_name(WN_st(wn)),"_ALLOCATE") == 0) {
	is_allocate_stmt = TRUE;
      } else if (strcmp(ST_name(WN_st(wn)),"_DEALLOCATE") == 0) {
	set_XlationContext_has_no_arr_elmt(ctxt);
	is_allocate_stmt = TRUE;
      } 
      if (strcmp(ST_name(WN_st(wn)),"PRESENT") == 0) {
	set_XlationContext_has_no_arr_elmt(ctxt);
      }

    } else if (WN_operator(wn) == OPR_ICALL) {
      func_ty = WN_ty(wn);
      last_arg_idx = WN_kid_count(wn) - 2;
    } else { /* (WN_operator(wn) == OPR_PICCALL) */
      is_user_call = TRUE;
      func_ty = ST_type(WN_st(wn));
      last_arg_idx = WN_kid_count(wn) - 2;
    }

    return_to_param = Func_Return_To_Param(func_ty);
    return_ty = Func_Return_Type(func_ty);
    first_arg_idx = ST2F_FIRST_PARAM_IDX(func_ty);
  }

  // -------------------------------------------------------
  StabToScopeIdMap& map = ctxt.GetStabToScopeIdMap();

  if (WN_operator(wn) == OPR_INTRINSIC_CALL) {
    /* FIXME: Note that all intrinsics that return a CHARACTER string
     * will have been treated specially in WN2F_intrinsic_call(),
     * so we need only consider returns through a first non-
     * string parameter here.
     */
    xos << BegElem("xaif:Intrinsic***") << Attr("vertex_id", ctxt.GetNewVId())
	<< Attr("name", WN_intrinsic_name((INTRINSIC)WN_intrinsic(wn)))
	<< EndElem;
  } else {
    // OPR_ICALL: TranslateWN(xos, WN_kid(wn, WN_kid_count(wn) - 1), ctxt);
    ST* st = WN_st(wn);
    ST_TAB* sttab = Scope_tab[ST_level(st)].st_tab;
    UINT scopeid = map.Find(sttab);
    ASSERT_FATAL(scopeid != 0, (DIAG_UNIMPLEMENTED, 0, "xlate_CALL"));

    xos << BegComment << "sym = " << W2CF_Symtab_Nameof_St(st) << EndComment;

    if (return_ty != (TY_IDX)0 && TY_kind(return_ty) != KIND_VOID) {
      // A function call
      xos << BegElem("xaif:FunctionCall") 
	  << Attr("vertex_id", ctxt.GetNewVId())
	  << Attr("scope_id", scopeid)
	  << Attr("symbol_id", (UINT)ST_index(st));
    } else {
      // A subroutine (FIXME)
      xos << BegElem("xaif:SubroutineCall")
	  << Attr("statement_id", ctxt.GetNewVId())
	  << Attr("scope_id", scopeid)
	  << Attr("symbol_id", (UINT)ST_index(st));
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
	  fmtry = TY_pointed(parm_ty);
	  fmtry = TY_mtype(fmtry);
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
  set_XlationContext_no_parenthesis(ctxt);
  BOOL has_stat = FALSE;
  BOOL first_nonemptyarg = FALSE;
  INT implicit_args;
  UINT position = 1;

  for (INT arg_idx = first_arg_idx, implicit_args = 0; 
       arg_idx <= last_arg_idx - implicit_args; 
       arg_idx++) {

    if (WN_kid(wn, arg_idx) != NULL) {
      WN* kidofparm = WN_kid0(WN_kid(wn, arg_idx));
      if (WN_operator(kidofparm) != OPR_CALL)
	arg_ty = WN_Tree_Type(WN_kid(wn, arg_idx));
      else
	arg_ty = PU_prototype (Pu_Table[ST_pu(WN_st(kidofparm))]);
            
      xos << BegElem("xaif:Argument") << Attr("position", position++);
      ctxt.CreateContext(XlationContext::VARREF, wn); // implicit for Argument

      // FIXME
      if (WN_operator(wn) == OPR_INTRINSIC_CALL &&
	  INTRN_by_value(WN_intrinsic(wn))) {
	/* Call-by value, but argument should be emitted without the
	 * %val() qualifier. */
	first_nonemptyarg = TRUE;
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
	WN2F_Offset_Memref(xos, 
			   WN_kid(wn, arg_idx), /* address expression */
			   arg_ty,              /* address type */
			   TY_pointed(arg_ty),  /* object type */
			   0,                   /* offset from address */
			   ctxt);
      }
      
      if ((arg_idx+implicit_args) == (last_arg_idx-1)) { 
	if (WN_operator(wn) == OPR_CALL && is_allocate_stmt) {
	  if (WN_opc_operator(WN_kid0(WN_kid(wn, last_arg_idx))) == OPR_LDA) {
	    // xos << ",";
	    xos << "STAT=";
	    has_stat=TRUE;
	  } else {
	    arg_idx++;
	  }
	}
      }

      ctxt.DeleteContext();
      xos << EndElem;
    }
  }
  
  reset_XlationContext_no_parenthesis(ctxt);
  reset_XlationContext_has_no_arr_elmt(ctxt);
  
  if (WN_operator(wn) != OPR_INTRINSIC_CALL) {
    xos << EndElem;
  }
  
  return EMPTY_WN2F_STATUS;
} /* xlate_CALL */


WN2F_STATUS 
xlate_PREFETCH(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_PREFETCH ||
		   WN_operator(wn) == OPR_PREFETCHX, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_PREFETCH"));
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS
WN2F_eval(xml::ostream& xos, WN *wn, XlationContext& ctxt)
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

   return EMPTY_WN2F_STATUS;
} /* WN2F_eval */


WN2F_STATUS
WN2F_use_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_USE,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_use_stmt"));

  const char *st_name = W2CF_Symtab_Nameof_St(WN_st(wn));
  xos << "===***>use" << st_name;

#if 0
  if (WN_rtype(wn) == 1)
    xos << ",only:";
  else 
    xos << ",";
  
  for(int k=0; k< WN_kid_count(wn); k=k+2 ) {
    st_name = W2CF_Symtab_Nameof_St(WN_st(WN_kid(wn,k)));
    const char *st_name1 = W2CF_Symtab_Nameof_St(WN_st(WN_kid(wn,k+1)));
    if (k!=0)
      xos << ","; 
    xos << st_name << "=>" << st_name1;
  }
  
  // TranslateWN(xos, WN_kid0(wn), ctxt);
# endif
     
  return EMPTY_WN2F_STATUS;
} //WN2F_use_stmt


WN2F_STATUS
WN2F_namelist_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  const char *st_name =  W2CF_Symtab_Nameof_St(WN_st(wn));
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_NAMELIST,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_namelist_stmt"));
  if (ST_is_external(WN_st(wn))) {
    ;
  } else {
    xos << "NAMELIST /" << st_name << " /";
    int k ;
    for(k=0;k< WN_kid_count(wn);k++ ) {
      st_name = W2CF_Symtab_Nameof_St(WN_st(WN_kid(wn,k)));
      Set_BE_ST_w2fc_referenced(WN_st(WN_kid(wn,k)));
      if (k==0)
	;
      else
	xos << ",";
      xos << st_name;
    }
  }
  
  return EMPTY_WN2F_STATUS;
} //WN2F_namelist_stmt


WN2F_STATUS
WN2F_implicit_bnd(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  xos << "[+-+]";
  return EMPTY_WN2F_STATUS;
}

// OPC_SWITCH only appears in very high level whirl
WN2F_STATUS
WN2F_switch(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // REMOVE
  WN *stmt;
  WN *kid1wn;
  
  xos << "SELECT CASE (";
  TranslateWN(xos, WN_condbr_cond(wn), ctxt);
  xos << ")";
  
  kid1wn = WN_kid1(wn);
  
  for (stmt = WN_first(kid1wn); stmt != NULL; stmt = WN_next(stmt)) {
    if (!WN2F_Skip_Stmt(stmt)) {
      if (WN_operator(stmt) == OPR_CASEGOTO)
	WN_st_idx(stmt) = WN_st_idx(WN_kid0(wn));
    }
  }
  
  TranslateWN(xos, WN_kid1(wn), ctxt);
  if (WN_kid_count(wn) == 3)
    TranslateWN(xos, WN_kid2(wn), ctxt);
  xos << "END SELECT ";
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS
WN2F_casegoto(xml::ostream& xos, WN *wn, XlationContext& ctxt)
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
  xos << " .EQ. " << val << ')' 
      << " GO TO " << WHIRL2F_number_as_name(WN_label_number(wn));
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS
WN2F_nullify_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  int k ;  
  const char *st_name;
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_NULLIFY,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_nullify_stmt"));

  xos << "NULLIFY (";
  
  for(k=0;k< WN_kid_count(wn);k++ ) {
    st_name = W2CF_Symtab_Nameof_St(WN_st(WN_kid(wn,k)));
    Set_BE_ST_w2fc_referenced(WN_st(WN_kid(wn,k)));
    if (k!=0)
      xos << ",";
    xos << st_name;
    
  }
  xos << ")";
  
  return EMPTY_WN2F_STATUS;
} //WN2F_namelist_stmt


WN2F_STATUS
WN2F_interface_blk(xml::ostream& xos, WN *wn, XlationContext& ctxt)
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
	Append_Token_String(xos, W2CF_Symtab_Nameof_St(st));     
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
	
	Append_Token_String(xos, W2CF_Symtab_Nameof_St(st));
	
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
				      W2CF_Symtab_Nameof_St(param_st[param]));
		  
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
	
	if (rslt !=NULL && strcasecmp(W2CF_Symtab_Nameof_St(st), 
				      W2CF_Symtab_Nameof_St(rslt)) != 0) {
	  /* append the RESULT option only if it is different from the function name */
	  /* (radu@par.univie.ac.at) */
	  xos << "result(";
	  Append_Token_String(xos, W2CF_Symtab_Nameof_St(rslt));
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
	      Append_Token_String(xos, W2CF_Symtab_Nameof_St(param_st[param]));
	    }
	    if (ST_is_intent_in_argument(param_st[param])) {
	      xos << std::endl;
	      xos << "INTENT(in) ";
	      Append_Token_String(xos, W2CF_Symtab_Nameof_St(param_st[param]));
	    }
	    if (ST_is_intent_out_argument(param_st[param])) {
	      xos << std::endl;
	      xos << "INTENT(out) ";
	      Append_Token_String(xos, W2CF_Symtab_Nameof_St(param_st[param]));
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
  
  return EMPTY_WN2F_STATUS;
} //WN2F_interface_blk

WN2F_STATUS
WN2F_ar_construct(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  xos << "(/";
  for (INT kid = 0; kid < WN_kid_count(wn); kid++) {
    TranslateWN(xos,WN_kid(wn,kid), ctxt);
    if (kid < WN_kid_count(wn)-1)
      xos << ",";
  }
  xos << "/)";
  
  return EMPTY_WN2F_STATUS;
}

WN2F_STATUS
WN2F_noio_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt)
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
  return EMPTY_WN2F_STATUS;
}

