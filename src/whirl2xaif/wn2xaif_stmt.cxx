// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_stmt.cxx,v 1.4 2003/05/20 22:50:04 eraxxon Exp $
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

#include "Open64BasicTypes.h" /* Open64 basic types */
#include "const.h"            /* For FOR_ALL_CONSTANTS */
#include "pf_cg.h"
#include "region_util.h"      /* For RID and RID_map */
#include "be_symtab.h"
#include "intrn_info.h"       /* INTR macros */     

//*************************** User Include Files ****************************

#include "whirl2f_common.h"
#include "w2cf_parentize.h"
#include "PUinfo.h"
#include "wn2xaif.h"
#include "st2f.h"
#include "ty2f.h"
#include "tcon2f.h"
#include "wn2xaif_stmt.h"
#include "wn2xaif_mem.h"
#include "wn2xaif_io.h"
#include "wn2f_pragma.h"
#include "init2f.h"

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//************************** Forward Declarations ***************************

extern WN_MAP  W2F_Frequency_Map;   /* Defined in w2f_driver.c */
extern WN_MAP *W2F_Construct_Map;   /* Defined in w2f_driver.c */

//***************************************************************************

/*----------------- Call and return site utilities --------------------*/
/*---------------------------------------------------------------------*/

/* Lists of return and call sites for the current PU,
 * initialized by means of "PUinfo.h" facilities.
 */
static RETURNSITE *WN2F_Next_ReturnSite = NULL;

/*-------- The initializers and handlers statement translation --------*/
/*---------------------------------------------------------------------*/

BOOL 
WN2F_Skip_Stmt(WN *stmt)
{
  return FALSE; // REMOVE
}


// find and emit any COMMONS that are initialized.
// used by WN2F_Append_Block_Data below.
struct WN2F_emit_commons {
public:
  WN2F_emit_commons(xml::ostream& xos_) : xos(xos_) { }
  
  void operator() (UINT32,  ST* st)
  {
    //XlationContext& ctxt1 = ctxt; // FIXME (bug in gcc 3.0.4 it seems)
    if (ST_sclass(st) == SCLASS_DGLOBAL) {
      if(ST_is_initialized(st))  {
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

// Create a BLOCK DATA if any COMMONs in the global symbol
// table are initialized. BLOCK DATA names are lost, but
// that's ok - all (global) initializations that appeared
// in the file are here.

// REMOVE
void
WN2F_Append_Block_Data(xml::ostream& tokens)
{
#if 0//FIXME
  xml::ostream& Decl_Stmt_Tokens;

  Decl_Stmt_Tokens = New_Token_Buffer() ;
  Data_Stmt_Tokens = New_Token_Buffer() ;
  PUinfo_local_decls = New_Token_Buffer() ;

  For_all(St_Table,GLOBAL_SYMTAB,WN2F_emit_commons(Decl_Stmt_Tokens)) ;

  if (!Is_Empty_Token_Buffer(Decl_Stmt_Tokens)) 
    {
      Append_F77_Indented_Newline(tokens, 1, NULL);
      Append_Token_String(tokens, "BLOCK DATA");

# if 0
      Append_F77_Indented_Newline(tokens, 1, NULL);
      Append_Token_String(tokens, "IMPLICIT NONE");
# endif

      xos << "**** Variables ****\n"; //COMMENT
      Append_F77_Indented_Newline(tokens, 1, NULL);
      Append_And_Reclaim_Token_List(tokens, &Decl_Stmt_Tokens);

      Append_And_Reclaim_Token_List(tokens,&PUinfo_local_decls);
  
      if (!Is_Empty_Token_Buffer(Data_Stmt_Tokens)) {
	xos << "**** statements ****\n";//COMMENT
	Append_And_Reclaim_Token_List(tokens, &Data_Stmt_Tokens);
      }

      Append_F77_Indented_Newline(tokens, 1, NULL) ;
      Append_Token_String(tokens, "END") ;
      Append_Token_Special(tokens, '\n');
    }
#endif
}


WN2F_STATUS 
WN2F_block(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  WN          *stmt;
  WN          *induction_step = NULL;
  const BOOL   is_pu_block = ctxt.IsNewPU();
  const BOOL   add_induction_step = XlationContext_insert_induction(ctxt);
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_BLOCK, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_block"));
  
  // FIXME: This is not currently called
  std::ostringstream xos_stmtstr;
  xml::ostream xos_stmt(xos_stmtstr.rdbuf());

  if (add_induction_step) {
    induction_step = XlationContext_induction_stmt(ctxt);
    reset_XlationContext_induction_step(ctxt);
  }
  
  if (is_pu_block) {
    //FIXME: WN2F_Enter_PU_Block();
    ctxt.ResetNewPU();
  }
  
  /* Translate statements and determine variable usage */
  for (stmt = WN_first(wn); stmt != NULL; stmt = WN_next(stmt)) {
    if (!WN2F_Skip_Stmt(stmt)) {
      if (induction_step != NULL && WN_next(stmt) == NULL 
	  && WN_operator(stmt) == OPR_LABEL) {
	/* Add induction step before loop-label */
	TranslateWN(xos_stmt, induction_step, ctxt);
	induction_step = NULL;
      }
      TranslateWN(xos_stmt, stmt, ctxt);
    }
  }
  
  /* Append the induction-step as the last statement in the block */
  if (induction_step != NULL)
    TranslateWN(xos_stmt, induction_step, ctxt);
  
  if (is_pu_block) {
    //FIXME WN2F_Exit_PU_Block(xos, xos_stmt);
  } else {
    xos << xos_stmtstr.str();
  }
  return EMPTY_WN2F_STATUS;
} /* WN2F_block */


WN2F_STATUS 
WN2F_region(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* Emit region #pragma, the WN_region_pragmas(wn), and the 
    * WN_region_body(wn).
    */
   WN  *stmt;
   RID *rid;
   BOOL good_rid; 
   
   Is_True(WN_operator(wn) == OPR_REGION, 
	   ("Invalid operator for WN2F_region()"));

   Is_True(WN_operator(WN_region_body(wn)) == OPR_BLOCK, 
	   ("Expected OPR_BLOCK as body of OPR_REGION in WN2F_region()"));

   good_rid = RID_map >= 0;
   if (good_rid) 
     rid = (RID *)WN_MAP_Get(RID_map, wn);
   if (W2F_Emit_All_Regions ||
       (!W2F_No_Pragmas && good_rid && 
        (rid == NULL          ||              /* == RID_TYPE_pragma */
         RID_type(rid) == RID_TYPE_pragma)))  /* User defined region */
   {
     xos << "C*$*" << std::endl;
     xos << "REGION BEGIN";

     set_XlationContext_explicit_region(ctxt);

      if (!W2F_No_Pragmas)
         WN2F_pragma_list_begin(xos, 
                                WN_first(WN_region_pragmas(wn)),
                                ctxt);

      for (stmt = WN_first(WN_region_body(wn));
	   stmt != NULL;
	   stmt = WN_next(stmt))
      {
	 if (!WN2F_Skip_Stmt(stmt))
	   TranslateWN(xos, stmt, ctxt);
      }

      if (!W2F_No_Pragmas)
         WN2F_pragma_list_end(xos,
                              WN_first(WN_region_pragmas(wn)),
                              ctxt);

      xos << "C*$*" << std::endl;
      xos << "REGION END";

   }
   else
   {
      reset_XlationContext_explicit_region(ctxt);

      /* Emit the pragmas that are associated with regions and that have
       * a corresponding pragma in the source language.
       */
      if (!W2F_No_Pragmas)
         WN2F_pragma_list_begin(xos, 
                                WN_first(WN_region_pragmas(wn)),
                                ctxt);

      /* Emit the body of the region, making the actual region 
       * markings and associated pragmas completely transparent.
       */
      for (stmt = WN_first(WN_region_body(wn));
	   stmt != NULL;
	   stmt = WN_next(stmt))
      {
	 if (!WN2F_Skip_Stmt(stmt))
	    (void)TranslateWN(xos, stmt, ctxt);
      }

      /* Close the region, if necessary, based on the kind of region
       * we have as determined by the first pragma in the list.
       */
      if (!W2F_No_Pragmas)
         WN2F_pragma_list_end(xos,
                              WN_first(WN_region_pragmas(wn)),
                              ctxt);
   } /* if emit pragma */

   return EMPTY_WN2F_STATUS;
} /* WN2F_region */


WN2F_STATUS 
WN2F_compgoto(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   WN         *goto_stmt;
   INT32       goto_entry;
   const char *label_num;

   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_COMPGOTO, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_compgoto"));
   ASSERT_DBG_FATAL(WN_operator(WN_compgoto_table(wn)) == OPR_BLOCK,
		    (DIAG_W2F_UNEXPECTED_OPC, "WN_compgoto_table"));

   /* Calculate the computed goto for the given cases */
   if (WN_compgoto_num_cases(wn) > 0)
   {
     xos << std::endl << "GO TO(";
      goto_stmt = WN_first(WN_compgoto_table(wn));
      for (goto_entry = 0;
	   goto_entry < WN_compgoto_num_cases(wn); 
	   goto_entry++)
      {
	 ASSERT_DBG_FATAL(WN_operator(goto_stmt) == OPR_GOTO,
			  (DIAG_W2F_UNEXPECTED_OPC, "COMPGOTO entry"));
	 label_num = WHIRL2F_number_as_name(WN_label_number(goto_stmt));
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
      WN2F_goto(xos, WN_kid(wn,2), ctxt);

   return EMPTY_WN2F_STATUS;
} /* WN2F_compgoto */


WN2F_STATUS 
WN2F_do_loop(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
#if 0 // REMOVE
   /* It is somewhat complicated to always translate this correctly
    * back to Fortran, dependent on the form of the test-for-termination
    * and the idx-variable-increment expressions.  When we deem it too
    * complicated to be coped with, we generate a DO WHILE expression 
    * instead.  This is an area we can probably always improve with more
    * work.
    */
   STAB_OFFSET    idx_ofst;
   ST            *idx_var;
   WN            *step_size;
   DO_LOOP_BOUND *bound;
   WN            *loop_info;
   
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_DO_LOOP,
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_do_loop"));
   ASSERT_DBG_FATAL(WN_operator(WN_start(wn)) == OPR_STID,
		    (DIAG_W2F_UNEXPECTED_OPC, "WN_start"));
   ASSERT_DBG_FATAL(WN_operator(WN_do_body(wn)) == OPR_BLOCK,
		    (DIAG_W2F_UNEXPECTED_OPC, "WN_do_body"));


   loop_info = WN_do_loop_info(wn);

   /* Whether or not we can generate a DO loop depends on the forms
    * of WN_end(wn) and WN_step(wn), so the first thing we need to
    * do is to accumulate some information about these.
    */
   idx_var = WN_st(WN_index(wn));
   idx_ofst = WN_idname_offset(WN_index(wn));
   step_size = WN2F_Get_DoLoop_StepSize(WN_step(wn), idx_var, idx_ofst);
   bound = WN2F_Get_DoLoop_Bound(WN_end(wn), idx_var, idx_ofst, step_size);
   
   if (bound != NULL)
   {
      /* Generate a DO LOOP statement */
     xos << std::endl << "DO";
      //REMOVE set_XlationContext_emit_stid(ctxt);
      if (!XlationContext_no_newline(ctxt))
      {
	 set_XlationContext_no_newline(ctxt);
	 (void)TranslateWN(xos, WN_start(wn), ctxt);
	 reset_XlationContext_no_newline(ctxt);
      }
      else
      {
	 (void)TranslateWN(xos, WN_start(wn), ctxt);
      }
      //REMOVE reset_XlationContext_emit_stid(ctxt);
      xos << ',';

      TranslateWN(xos, bound, ctxt); // WN2F_Translate_DoLoop_Bound(...)
      xos << ',';

      TranslateWN(xos, step_size, ctxt);
      TranslateWN(xos, WN_do_body(wn), ctxt);
      xos << std::endl << "END DO";
   }
   else /* Generate a DO WHILE loop */
   {
      (void)TranslateWN(xos, WN_start(wn), ctxt);
      xos << std::endl << "DO WHILE(";
      set_XlationContext_has_logical_arg(ctxt);
      set_XlationContext_no_parenthesis(ctxt);
      (void)TranslateWN(xos, WN_end(wn), ctxt);
      reset_XlationContext_no_parenthesis(ctxt);
      reset_XlationContext_has_logical_arg(ctxt);
      xos << ')';

      set_XlationContext_induction_step(ctxt, WN_step(wn));
      (void)TranslateWN(xos, WN_do_body(wn), ctxt);

      xos << std::endl;
      xos << std::endl << "END DO";
   }
#endif
   return EMPTY_WN2F_STATUS;
} /* WN2F_do_loop */


WN2F_STATUS 
WN2F_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* This is a fortran implied do_loop, which can only occur as an
    * an OPR_IO_ITEM.  We should always be able to regenerate
    * an implied do-loop from this WHIRL tree, and we should safely
    * be able to assert that XlationContext_io_stmt is TRUE.  Strictly
    * speaking this can be viewed as an expression, rather than as a
    * statement, but due to the commonality with regular do-loops
    * we handle it in this module.
    */
   INT   kid;
   BOOL  emitted;
   ST   *idx_name;
   
   ASSERT_DBG_FATAL(XlationContext_io_stmt(ctxt) &&
		    XlationContext_no_newline(ctxt),
		    (DIAG_W2F_UNEXPECTED_CONTEXT, "WN2F_implied_do"));

   /* Start an implied do-loop expression */
   xos << '(';

   /* Generate all the expression trees, separated by commas */
   for (kid = 4; kid < WN_kid_count(wn); kid++) {
     emitted = xlate_IO_ITEM(xos, WN_kid(wn, kid), ctxt);
     if (emitted)
       xos << ",";
   }

   /* Generate the loop expression */
   idx_name = WN_st(WN_index(wn));
   WN2F_Offset_Symref(xos, idx_name,                      /* base-symbol */
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
WN2F_do_while(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   const char *tmpvar_name;
   UINT        tmpvar_idx;
   TY_IDX      logical_ty;
   
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_DO_WHILE,
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_do_while"));

   /* The base-type of the logical expression.  Note that TY_is_logical()
    * will only hold true when the TY is resolved from a WN_ty or ST_ty
    * attribute, not when it is resolved from an MTYPE (descriptor or
    * result type).
    */
   logical_ty = WN_Tree_Type(WN_while_test(wn));
   

   xos << std::endl;
   xos << "whirl2f:: DO loop with termination test after first iteration\n";
   // Comment

   /* termination test initialization (in temporary variable) */
   tmpvar_idx = Stab_Lock_Tmpvar(logical_ty, &ST2F_Declare_Tempvar);
   tmpvar_name = W2CF_Symtab_Nameof_Tempvar(tmpvar_idx);
   Append_Token_String(xos, tmpvar_name);
   xos << "=";
   xos << ".TRUE.";
   
   /* loop header */
   xos << std::endl;
   xos << "DO WHILE(" << tmpvar_name << ')';

   /* loop body and termination test initialization (in temporary variable) */
   (void)TranslateWN(xos, WN_while_body(wn), ctxt);
   xos << std::endl;
   Append_Token_String(xos, tmpvar_name);
   xos << "=";
   set_XlationContext_has_logical_arg(ctxt);
   (void)TranslateWN(xos, WN_while_test(wn), ctxt);
   reset_XlationContext_has_logical_arg(ctxt);

   /* Close the loop and allow reuse of the termination test 
    * temporary variable.
    */
   xos << std::endl;
   xos << "END DO";
   Stab_Unlock_Tmpvar(tmpvar_idx);

   return EMPTY_WN2F_STATUS;
} /* WN2F_do_while */


WN2F_STATUS 
WN2F_while_do(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_WHILE_DO,
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_while_do"));

   /* Termination test */
   xos << std::endl << "DO WHILE(";
   set_XlationContext_has_logical_arg(ctxt);
   TranslateWN(xos, WN_while_test(wn), ctxt);
   reset_XlationContext_has_logical_arg(ctxt);
   xos << ')';

   /* loop body */
   TranslateWN(xos, WN_while_body(wn), ctxt);

   /* close the loop */
   xos << std::endl << "END DO";

   return EMPTY_WN2F_STATUS;
} /* WN2F_while_do */


WN2F_STATUS 
WN2F_if(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_IF,
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_if"));

   /* Ignore if-guards inserted by lno, since these are redundant
    * in High WHIRL.
    */
   if (WN_Is_If_Guard(wn)) {
     /* Emit only the THEN body, provided it is non-empty */
     if (WN_operator(WN_then(wn)) != OPR_BLOCK || 
	 WN_first(WN_then(wn)) != NULL) {
       TranslateWN(xos, WN_then(wn), ctxt);
     }
   } else { /* Not a redundant guard (from whirl2f perspective) */
     /* IF header */
     xos << std::endl;
     xos << "IF(";
     set_XlationContext_has_logical_arg(ctxt);
     TranslateWN(xos, WN_if_test(wn), ctxt);
     reset_XlationContext_has_logical_arg(ctxt);
     xos << ") THEN";
     
     /* THEN body */
     TranslateWN(xos, WN_then(wn), ctxt);
     
     /* ELSE body */
     if (!WN_else_is_empty(wn)) {
       xos << std::endl << "ELSE";
       TranslateWN(xos, WN_else(wn), ctxt);
     }
     
     /* if closing */
     xos << std::endl << "ENDIF";
   }
   
   return EMPTY_WN2F_STATUS;
} /* WN2F_if */


WN2F_STATUS 
WN2F_goto(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_GOTO || 
		    WN_operator(wn) == OPR_REGION_EXIT,
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_goto"));

   xos << std::endl << "GO TO" << WHIRL2F_number_as_name(WN_label_number(wn));
   
   return EMPTY_WN2F_STATUS;
} /* WN2F_goto */


WN2F_STATUS 
WN2F_agoto(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_AGOTO,
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_agoto"));

   xos << std::endl << "GO TO";
   TranslateWN(xos, WN_kid0(wn), ctxt);
   
   return EMPTY_WN2F_STATUS;
} /* WN2F_agoto */


WN2F_STATUS 
WN2F_condbr(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_TRUEBR || 
		    WN_operator(wn) == OPR_FALSEBR,
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_condbr"));

   xos << std::endl << "IF(";
   set_XlationContext_has_logical_arg(ctxt);
   if (WN_operator(wn) == OPR_FALSEBR) {
     xos << ".NOT. (";
     TranslateWN(xos, WN_condbr_cond(wn), ctxt);
     xos << ')';
   } else { /* WN_operator(wn) == OPR_TRUEBR */
     TranslateWN(xos, WN_condbr_cond(wn), ctxt);
   }
   reset_XlationContext_has_logical_arg(ctxt);
   xos << ") GO TO" << WHIRL2F_number_as_name(WN_label_number(wn));
   
   return EMPTY_WN2F_STATUS;
} /* WN2F_condbr */

WN2F_STATUS 
WN2F_return(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* Ensures that the return value resides in the implicit
    * return variable (PUINFO_FUNC_NAME), and returns control
    * from the current PU (PUinfo_current_func).
    */

  if (WN2F_Next_ReturnSite ==NULL) //when will this  happen??  fzhao
    return EMPTY_WN2F_STATUS;

  ST* result_var = (ST *)RETURNSITE_return_var(WN2F_Next_ReturnSite);
  const WN* result_store = RETURNSITE_store1(WN2F_Next_ReturnSite);
  const STAB_OFFSET var_offset = RETURNSITE_var_offset(WN2F_Next_ReturnSite);
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_RETURN,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_return"));
  
  ASSERT_DBG_FATAL(RETURNSITE_return(WN2F_Next_ReturnSite) == wn,
		   (DIAG_W2F_UNEXPECTED_RETURNSITE, "WN2F_return()"));
  
   /* Do not emit a return statement for the main program unit.
    */
  if (PU_is_mainpu(Get_Current_PU()) || 
      strcmp(ST_name(WN_entry_name(PUinfo_current_func)), "MAIN__") == 0) {
    WN2F_Next_ReturnSite = RETURNSITE_next(WN2F_Next_ReturnSite);
    return EMPTY_WN2F_STATUS;
  }
   /* Save off the return-value, unless there is no return-value or
    * it already resides where we expect it to be.
    */
#if 0 //REMOVE/FIXME
   if ( REMOVE !PUINFO_RETURN_TO_PARAM                &&
	PUINFO_RETURN_TY != (TY_IDX) 0         && 
	TY_kind(PUINFO_RETURN_TY) != KIND_VOID &&
	 RETURN_PREG_mtype(PUinfo_return_preg, 0) != MTYPE_V) 
#endif
   if (false)
   {
      /* Note that we make more assumptions here than in the case
       * of whirl2c.  In particular, we always assume assignment
       * compatibility between the return-variable and the location
       * of the found return-value.
       */
      if (result_var != NULL)
      {
	 if (ST_class(result_var) == CLASS_PREG || 
	     !ST_is_return_var(result_var))
	 {
	    /* PUinfo_init_pu() revealed that the return value is present
	     * in a variable or non-return-register.  Now, move the value to
	     * this return location.
		     */
		    TY_IDX rv_ty = ST_type(result_var);

	    if (TY_kind(rv_ty) != KIND_STRUCT) 
	    {
	      ASSERT_WARN(WN2F_Can_Assign_Types(rv_ty, PUINFO_RETURN_TY),
			  (DIAG_W2F_INCOMPATIBLE_TYS, "WN2F_return"));
	    }

	    /* Assign the return value to PUINFO_FUNC_ST */
	    xos << std::endl;
	    TranslateSTUse(xos, PUINFO_FUNC_ST, ctxt);
	    xos << '=';
	    if (ST_class(result_var) == CLASS_PREG)
	      ST2F_Use_Preg(xos, ST_type(result_var),var_offset);
	    else
	      WN2F_Offset_Symref(xos, result_var, /* base variable */
				 Stab_Pointer_To(ST_type(result_var)),
				 /* expected type of base address */
				 PUINFO_RETURN_TY,
				 /* type of object to be loaded */
				 var_offset, ctxt);
	 }
      }
      else if (result_store != NULL)
      {
	 /* We have a store (an STID) into the return register, so just
	  * assign the rhs into PUINFO_FUNC_NAME.
	  */
	 ASSERT_DBG_FATAL(WN_operator(result_store) == OPR_STID,
			  (DIAG_W2F_UNEXPECTED_OPC, "WN2F_return"));
	 ASSERT_WARN(WN2F_Can_Assign_Types(WN_Tree_Type(WN_kid0(result_store)),
					   PUINFO_RETURN_TY),
		     (DIAG_W2F_INCOMPATIBLE_TYS, "WN2F_return"));
	 
	 /* Assign object being stored to PUINFO_FUNC_NAME */
	 xos << std::endl;
	 TranslateSTUse(xos, PUINFO_FUNC_ST, ctxt);
	 xos << '=';
	 TranslateWN(xos, WN_kid0(result_store), ctxt);
      }
      else if (RETURN_PREG_num_pregs(PUinfo_return_preg) == 1 &&
	       TY_Is_Preg_Type(PUINFO_RETURN_TY))
      {
	 /* There is a single return register holding the return value,
	  * so return a reference to this register.
	  */
	 const MTYPE    preg_mtype = RETURN_PREG_mtype(PUinfo_return_preg, 0);
	 TY_IDX const   preg_ty  = Stab_Mtype_To_Ty(preg_mtype);
	 const PREG_IDX preg_num = RETURN_PREG_offset(PUinfo_return_preg, 0);

	 ASSERT_WARN(WN2F_Can_Assign_Types(preg_ty, PUINFO_RETURN_TY),
		     (DIAG_W2F_INCOMPATIBLE_TYS, "WN2F_return"));

	 xos << std::endl;
	 TranslateSTUse(xos, PUINFO_FUNC_ST, ctxt);
	 xos << "=";
	 ST2F_Use_Preg(xos, preg_ty, preg_num);
      }
      else /* Our most difficult case */
      {
	 /* The return-value is in two registers and we have not been
	  * able to determine that it also resides in a variable.  
	  * TODO: 
	  * This could be handled by equivalencing the return-variable with
	  * a type corresponding to the two registers, for then to assign
	  * the register-values to the components of this equivalent
	  * return value.  For now, do nothing but warn about this case!
	  */
# if 0 //Maybe it's all right---fzhao
	 ASSERT_WARN(FALSE,
		     (DIAG_UNIMPLEMENTED, "WN2F_return from two registers"));
#endif

      } /* if */
   } /* if (need to store return value) */
	   
   /* Return control */
   xos << std::endl;
   xos << "RETURN";

   WN2F_Next_ReturnSite = RETURNSITE_next(WN2F_Next_ReturnSite);
   return EMPTY_WN2F_STATUS;
} /* WN2F_return */

WN2F_STATUS 
WN2F_return_val(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  Is_True(WN_operator(wn) == OPR_RETURN_VAL,
	  ("Invalid operator for WN2F_return_val()"));
  xos << std::endl << "RETURN";
  if (WN_operator(WN_kid0(wn)) != OPR_LDID) {
    TranslateWN(xos, WN_kid0(wn), ctxt);
  }
  return EMPTY_WN2F_STATUS;
}

WN2F_STATUS 
xlate_LABEL(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_LABEL, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_LABEL"));
  
  const char *label = WHIRL2F_number_as_name(WN_label_number(wn));
  xos << BegComment << "CONTINUE label=" << label << EndComment;
  
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
  // function call (expression.
  
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
      ctxt.CreateContext();

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
WN2F_prefetch(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  /* Prefetch information is currently added in a comment */
  INT pflag;
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_PREFETCH ||
		   WN_operator(wn) == OPR_PREFETCHX, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_prefetch"));
  
  /* Ensure array references are dereferenced and a comment line is begun */
  ctxt.SetDerefAddr();
  xos << std::endl;
  
  /* Get the prefetch identifier and address expression */
  if (WN_operator(wn) == OPR_PREFETCH) {
    Append_Token_String(xos, StrCat("PREFETCH(", Ptr_as_String(wn), ")"));
    
    (void)TranslateWN(xos, WN_kid0(wn), ctxt);
    
    xos << StrCat("OFFS=", WHIRL2F_number_as_name(WN_offset(wn)));
  } else { /* (WN_operator(wn) == OPR_PREFETCHX) */
    xos << StrCat("PREFETCH(", Ptr_as_String(wn),")");
      
    TranslateWN(xos, WN_kid0(wn), ctxt);
    xos << "+";
    TranslateWN(xos, WN_kid1(wn), ctxt);
  }
  
  /* Emit the prefetch flags information (pf_cg.h) on a separate line */
  pflag = WN_prefetch_flag(wn);
  //FIXME Set_Current_Indentation(Current_Indentation()+3);
  xos << std::endl;
  xos << (PF_GET_READ(pflag)? "read" : "write")
      << " strid1=" << WHIRL2F_number_as_name(PF_GET_STRIDE_1L(pflag))
      << " strid2=" << WHIRL2F_number_as_name(PF_GET_STRIDE_2L(pflag))
      << " conf=" << WHIRL2F_number_as_name(PF_GET_CONFIDENCE(pflag));
  //FIXME Set_Current_Indentation(Current_Indentation()-3);
  
  return EMPTY_WN2F_STATUS;
} /* WN2F_prefetch */


WN2F_STATUS
WN2F_eval(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* This generates code that will not recompile.  Short of
    * some kind of surrounding statement there is no way to do 
    * this in Fortran-77.
    */
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_EVAL, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_eval"));

   xos << std::endl;
   xos << "CALL _EVAL(";
   set_XlationContext_has_logical_arg(ctxt);
   set_XlationContext_no_parenthesis(ctxt);
   (void)TranslateWN(xos, WN_kid0(wn), ctxt);
   xos << ')';

   return EMPTY_WN2F_STATUS;
} /* WN2F_eval */

//**********************************************
WN2F_STATUS
WN2F_use_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  const char *st_name = W2CF_Symtab_Nameof_St(WN_st(wn));
// const char *st_name1;
#if 0
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_USE,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_use_stmt"));

  int k ;
  xos << std::endl;
  xos << "use";
  Append_Token_String(xos, st_name);
  if (WN_rtype(wn) == 1)
    xos << ",only:";
  else 
    xos << ",";
  
  for(k=0;k< WN_kid_count(wn);k=k+2 ) {
    st_name = W2CF_Symtab_Nameof_St(WN_st(WN_kid(wn,k)));
    st_name1= W2CF_Symtab_Nameof_St(WN_st(WN_kid(wn,k+1)));
    if (k==0)
      ;
    else
      xos << ","; 
    if (strcmp(st_name,st_name1)) {
      Append_Token_String(xos,st_name);
      xos << "=>"; 
      Append_Token_String(xos, st_name1);
    }
    else 
      Append_Token_String(xos,st_name);
  }
  
  // (void)TranslateWN(xos, WN_kid0(wn), ctxt);
# endif
     
  return EMPTY_WN2F_STATUS;
} //WN2F_use_stmt

//**********************************************
WN2F_STATUS
WN2F_namelist_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   int k ;

   const char *st_name =  W2CF_Symtab_Nameof_St(WN_st(wn));
    ASSERT_DBG_FATAL(WN_operator(wn) == OPR_NAMELIST,
                     (DIAG_W2F_UNEXPECTED_OPC, "WN2F_namelist_stmt"));
   if (ST_is_external(WN_st(wn)))
    {
      ;
     } else {
       xos << std::endl;
       xos << "NAMELIST /";
       Append_Token_String(xos, st_name);
       xos << " /";

       for(k=0;k< WN_kid_count(wn);k++ )

       { st_name = W2CF_Symtab_Nameof_St(WN_st(WN_kid(wn,k)));
        Set_BE_ST_w2fc_referenced(WN_st(WN_kid(wn,k)));
        if (k==0)
           ;
        else
          xos << ",";
          Append_Token_String(xos,st_name);

       }
   }

   return EMPTY_WN2F_STATUS;
} //WN2F_namelist_stmt


//**********************************************
WN2F_STATUS
WN2F_implicit_bnd(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  xos << " ";
  return EMPTY_WN2F_STATUS;
}

// OPC_SWITCH only appears in very high level whirl

WN2F_STATUS
WN2F_switch(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  WN *stmt;
  WN *kid1wn;
  
  //Append_F77_Indented_Newline(xos, 1/*empty-lines*/, NULL/*label*/);
  //  xos << "SELECT CASE (";
  //(void)TranslateWN(xos, WN_condbr_cond(wn), ctxt);
  // xos << ")";
  
  kid1wn = WN_kid1(wn);
  
  for (stmt = WN_first(kid1wn); stmt != NULL; stmt = WN_next(stmt))
    {
      if (!WN2F_Skip_Stmt(stmt))
	{
	  if (WN_operator(stmt) == OPR_CASEGOTO)
	    WN_st_idx(stmt) = WN_st_idx(WN_kid0(wn));
	}
    }
  
  (void)TranslateWN(xos, WN_kid1(wn), ctxt);
  if (WN_kid_count(wn) == 3)
    (void)TranslateWN(xos, WN_kid2(wn), ctxt);
  //  Append_F77_Indented_Newline(xos, 1/*empty-lines*/, NULL/*label*/);
  //  xos << "END SELECT ";
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS
WN2F_casegoto(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
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


//**********************************************
WN2F_STATUS
WN2F_nullify_stmt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  int k ;
  
  const char *st_name;
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_NULLIFY,
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_nullify_stmt"));

  xos << std::endl;
  xos << "NULLIFY (";
  
  for(k=0;k< WN_kid_count(wn);k++ ) {
    st_name = W2CF_Symtab_Nameof_St(WN_st(WN_kid(wn,k)));
    Set_BE_ST_w2fc_referenced(WN_st(WN_kid(wn,k)));
    if (k==0)
      ;
    else
      xos << ",";
    Append_Token_String(xos,st_name);
    
  }
  xos << ")";
  
  return EMPTY_WN2F_STATUS;
} //WN2F_namelist_stmt

//**********************************************
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
  INT kid;
  
   xos << "(";
   xos << "/";
   for (kid = 0; kid < WN_kid_count(wn); kid++) {

      (void)TranslateWN(xos,WN_kid(wn,kid), ctxt);
      if (kid < WN_kid_count(wn)-1)
         xos << ",";
    }


   xos << "/";
   xos << ")";

   return EMPTY_WN2F_STATUS;
 
}

WN2F_STATUS
WN2F_noio_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   INT kid;
   INT numkids = 5;
   xos << "(";
   (void)TranslateWN(xos,WN_kid0(wn),ctxt);
   xos << ",";
   (void)TranslateWN(xos,WN_kid1(wn),ctxt);
   xos << "=";
   
   for (kid = 2;kid<numkids; kid++) {
      (void)TranslateWN(xos,WN_kid(wn,kid),ctxt);
     if (kid < numkids-1)
       xos << ",";
    }

   xos << ")";
   return EMPTY_WN2F_STATUS;
}

