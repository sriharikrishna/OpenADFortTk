// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_io.cxx,v 1.2 2003/05/16 13:21:22 eraxxon Exp $
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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_io.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f_io.cxx
//
//***************************************************************************

/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *   Translate an OPC_IO subtree into the appropriate Fortran constructs.
 *   Recursive translation of WN nodes should only use WN2F_Translate(),
 *   with exception of IO_ITEMS which are handled locally!
 *
 *   The Fortran I/O statements have the following syntax:
 *
 *      <statement_keyword> <control_list> <I/O list>
 *
 *   where
 *
 *      <statement_keyword> ::= <IOS enumeration as defined in wio.h>
 *      <control_list>      ::= <IOU, IOF, and IOC items from wio.h>
 *      <I/O list>          ::= <IOL items from wio.h>
 *
 * ====================================================================
 * ====================================================================
 */

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include "Open64BasicTypes.h" /* Open64 basic types */
#include "wio.h"
#include "wutil.h"

//*************************** User Include Files ****************************

#include "whirl2f_common.h"
#include "PUinfo.h"
#include "wn2xaif.h"
#include "st2f.h"
#include "ty2f.h"
#include "tcon2f.h"
#include "wn2xaif_io.h"
#include "wn2xaif_mem.h"

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//************************** Forward Declarations ***************************

/* A rather special IOC item to replace an IOF_LABEL item.  This
 * value is only valid when XlationContext_origfmt_ioctrl is TRUE!
 */
static UINT32       Origfmt_Ioctrl_Label;
static xml::ostream* Format_Stmts = NULL;
static xml::ostream* Ios_Prefix_Tokens = NULL;

typedef void (*IO_STMT_HANDLER)(xml::ostream&, WN *, XlationContext&);
static IO_STMT_HANDLER Ios_Handler[IOSTATEMENT_LAST+1];


#define WN_IOITEM(x) (IOITEM) WN_io_item(x)
#define WN_IOSTMT(x) (IOSTATEMENT) WN_io_statement(x)

/* several craylib/dope items represent a no-op by a zero inconst...*/

#define IS_IO_NULL_OPR(wn) ((WN_operator(wn) == OPR_INTCONST) && (WN_const_val(wn) == 0))

//***************************************************************************

/*------------------------- Io Utility Routines -----------------------*/
/*---------------------------------------------------------------------*/

static void 
WN2F_Append_IO_CtrlList(xml::ostream& xos, 
			WN          *ios,
			INT          from_kid,
			INT          to_kid,
			BOOL         use_keyword,
			XlationContext& ctxt)
{
#if 0 // FIXME
   /* Emit an IO control list (IOU, IOF, and IOC with explicit
    * keywords.
    */
   BOOL         emitted, emitted2;
   INT          ios_kid;
   xml::ostream& item_buffer;
   
   xos << "(";

   /* Should we use keyword notation? */
   if (use_keyword)
      set_XlationContext_keyword_ioctrl(ctxt);
   
   emitted = FALSE; /* No item before the next one, as of yet */
   for (ios_kid = from_kid; ios_kid <= to_kid; ios_kid++)
   {
      item_buffer = New_Token_Buffer();
      emitted2 = WN2F_io_item(item_buffer, WN_kid(ios, ios_kid), ctxt);
      if (emitted2)
      {
	 if (emitted)
	    xos << ","; /* an item emitted earlier */
	 emitted = TRUE;
      }
      Append_And_Reclaim_Token_List(xos, &item_buffer);
   }
   reset_XlationContext_origfmt_ioctrl(ctxt);

   xos << ")";
#endif
} /* WN2F_Append_IO_CtrlList */


static void 
WN2F_Append_IO_List(xml::ostream& xos, 
		    WN          *ios,
		    INT          from_kid,
		    XlationContext& ctxt)
{
   /* Emit an IOL list, starting at the given kid index and
    * continuing to the last kid.
    */
   BOOL emitted;
   INT  ios_kid;
   
   for (ios_kid = from_kid; ios_kid < WN_kid_count(ios); ios_kid++)
   {
      emitted = WN2F_io_item(xos, WN_kid(ios, ios_kid), ctxt);
      if (emitted && (ios_kid+1 < WN_kid_count(ios)))
	 xos << ",";
   }
} /* WN2F_Append_IO_List */


/*---------------------- IO Item Handler-routines ---------------------*/
/*---------------------------------------------------------------------*/

#define WN2F_IS_IOU(item) \
   (WN_IOITEM(item) >= IOU_NONE && WN_IOITEM(item) <= IOU_INTERNAL)
#define WN2F_IS_IOF(item) \
   ((WN_IOITEM(item) >= IOF_NONE && WN_IOITEM(item) <= IOF_CR_FMTSRC_DOPE))
#define WN2F_IS_IOC(item) \
   (WN_IOITEM(item) >= IOC_ACCESS && WN_IOITEM(item) <= IOC_ERRFLAG)
#define WN2F_IS_IOL(item) \
   ((WN_IOITEM(item) >= IOL_ARRAY && WN_IOITEM(item) <= IOL_VAR) || \
    (WN_IOITEM(item) == IOL_DOPE))


static void
WN2F_emit_ctrl(xml::ostream& xos, const char *p , XlationContext& ctxt)
{
  if (XlationContext_keyword_ioctrl(ctxt)) {
    Append_Token_String(xos,p);
    xos << "=";
  }
}

static BOOL
WN2F_io_unit(xml::ostream& xos, 
	     WN          *item, 
	     XlationContext& ctxt)
{
   
   BOOL emitted = TRUE; /*  if a unit specifier was emitted */
   const char * p = "UNIT";
   const BOOL issue_asterisk = XlationContext_issue_ioc_asterisk(ctxt);

   /* Any arguments assumed to be by reference unless otherwise noted */
   ctxt.SetDerefAddr();

   switch (WN_io_item(item))
   {
   case IOU_NONE: 

     if (XlationContext_cray_io(ctxt) && issue_asterisk) {
       WN2F_emit_ctrl(xos,p,ctxt);
       xos << "*";
     } else
       emitted = FALSE;  /* eg: inquire by file */

      break;
      
   case IOU_DEFAULT: /* asterisk or double astrisk */

      if (issue_asterisk){
           WN2F_emit_ctrl(xos,p,ctxt);
           if (WN_const_val(WN_kid0(item)) == 0)
	     xos << "**";
           else
	     xos << "*";
        }
       else
           emitted =FALSE;

      break;

   case IOU_EXTERNAL:    /* unit number */
   case IOU_DOPE:
   case IOU_INTERNAL:    /* substring or array reference */
      WN2F_emit_ctrl(xos,p,ctxt);
      TranslateWN(xos, WN_kid0(item), ctxt);
      break;

   default:
      ASSERT_DBG_WARN(FALSE, 
		      (DIAG_W2F_UNEXPECTED_IOU,
		       IOITEM_name(WN_IOITEM(item)), "WN2F_io_unit"));
      WN2F_emit_ctrl(xos,p,ctxt);
      Append_Token_String(xos, IOITEM_name(WN_IOITEM(item)));
      break;
   } /*switch*/

   return emitted;
} /* WN2F_io_unit */


static BOOL
WN2F_io_format(xml::ostream& xos, WN* item, XlationContext& ctxt)
{
   /* Return TRUE if a format or name-list specifier was emitted */ 
   BOOL emitted = TRUE;
   const char *p = "fmt";

   /* Any arguments assumed to be by reference unless otherwise noted */
   ctxt.SetDerefAddr();

   switch (WN_io_item(item))
   {
   case IOF_NONE:
     if (XlationContext_cray_io(ctxt) && XlationContext_fmt_io(ctxt)) {
       WN2F_emit_ctrl(xos, p, ctxt);
       xos << '*';
     } else
       emitted = FALSE;
     break;

   case IOF_ASSIGNED_VAR:

      /* The front-end should never generate these, since they are converted
       * into IOF_CHAR_EXPR items.  Should we for any reason start regenerating
       * these, this is the place where it should occur.
       */
     ASSERT_DBG_WARN(FALSE, (DIAG_W2F_UNEXPECTED_IOF,
			     IOITEM_name(WN_IOITEM(item)), "WN2F_io_format"));
     xos << IOITEM_name(WN_IOITEM(item));
#if 0
     TranslateWN(xos, WN_kid0(item), ctxt);      
#endif
     break;

   case IOF_LABEL:
      /* a FORMAT label or character-string expression */

      WN2F_emit_ctrl(xos,p,ctxt);
      if (XlationContext_origfmt_ioctrl(ctxt))
	xos << Num2Str(Origfmt_Ioctrl_Label, "%lld");
      else
	TranslateWN(xos, WN_kid0(item), ctxt);
      break;

   case IOF_CHAR_EXPR:
      /* a character-substring expression */
      WN2F_emit_ctrl(xos,p,ctxt);
      WN2F_String_Argument(xos, WN_kid0(item), /* base */
			   WN_kid1(item), /* length */ ctxt);
      break;

   case IOF_LIST_DIRECTED:
      WN2F_emit_ctrl(xos,p,ctxt);
      xos << "*";
      break;

   case IOF_NAMELIST_DIRECTED:
      WN2F_emit_ctrl(xos,"NML",ctxt);
      TranslateWN(xos, WN_kid(item,WN_kid_count(item)-1), ctxt);
      Clear_BE_ST_w2fc_referenced(WN_st(WN_kid(item,WN_kid_count(item)-1)));
/* don't dump out Namelist name and corresponding type
 * in *.w2f.f file.When call TranslateWN,the namelist name(st entry) will
 * be set "referenced".Clear the flag.--------fzhao
 */
      break;

   case IOF_UNFORMATTED:
      emitted = FALSE;
      break;

   case IOF_CR_PARSFMT:
      emitted = FALSE;
      break;
       
   case IOF_CR_FMTSRC:
   case IOF_CR_FMTSRC_DOPE:
      {
	WN * kid0 = WN_kid0(item);
	if (IS_IO_NULL_OPR(kid0))
	  emitted = FALSE;
	else
	  TranslateWN(xos, kid0, ctxt);
	break;
      }
   default:
      ASSERT_DBG_WARN(FALSE, (DIAG_W2F_UNEXPECTED_IOF,
			      IOITEM_name(WN_IOITEM(item)), "WN2F_io_format"));
      xos << IOITEM_name(WN_IOITEM(item));
      break;
   } /*switch*/

   return emitted;
} /* WN2F_io_format */

static BOOL
WN2F_io_control(xml::ostream& xos, WN* item, XlationContext& ctxt)
{
   /* Return TRUE if a control specifier was emitted.
    */
   BOOL         emitted = TRUE;
   const IOITEM item_kind = WN_IOITEM(item);
   
   switch (item_kind)
   {
   case IOC_KEY:
      /* TODO: associate this with IOC_KEY */
      ASSERT_WARN(FALSE, (DIAG_UNIMPLEMENTED, 
			  StrCat("IOC", IOITEM_name(item_kind))));
      Append_Token_String(xos, IOITEM_name(item_kind));
      xos << "=";
      xos << "<???>";
      break;
      
   case IOC_KEY_START:
   case IOC_KEY_END:
   case IOC_KEY_CHARACTER:
   case IOC_KEY_INTEGER: 
   case IOC_NML: /* TODO: remove from IOC enumeration! It is redundant */
      ASSERT_WARN(FALSE, (DIAG_UNIMPLEMENTED, 
			  StrCat("IOC", IOITEM_name(item_kind))));
      Append_Token_String(xos, IOITEM_name(item_kind));
      break;
      
   case IOC_EXIST:
   case IOC_NAMED:
   case IOC_OPENED:
      /* LOGICAL argument */
      ASSERT_FATAL(WN_kid_count(item) >= 1,
		   (DIAG_W2F_UNEXPECTED_NUM_KIDS, 
		    WN_kid_count(item), 1, "WN2F_io_control"));
      Append_Token_String(xos, IOITEM_name(item_kind));
      xos << "=";
      set_XlationContext_has_logical_arg(ctxt);
      if (TY_kind(WN_Tree_Type(WN_kid0(item))) != KIND_SCALAR)
	 ctxt.SetDerefAddr();
      TranslateWN(xos, WN_kid0(item), ctxt);
      reset_XlationContext_has_logical_arg(ctxt);
      break;
      
   case IOC_READONLY:
   case IOC_SHARED:
   case IOC_U:
      Append_Token_String(xos, IOITEM_name(item_kind));
      /* No argument */
      break;

   case IOC_VARFMT:
      emitted = FALSE;
      break;

   case IOC_VARFMT_ORIGFMT:
      /* We assume a label-number already has been assigned for
       * this FORMAT statement into Origfmt_Ioctrl_Label.  See
       * also IOF_LABEL.  Expect the string argument to be an
       * LDA of a string-constant (ST of class CONST).  Note that
       * a string-constant always is '\0' terminated.
       */
      ASSERT_DBG_WARN((WN_opc_operator(WN_kid0(item)) == OPR_LDA &&
		       ST_class(WN_st(WN_kid0(item))) == CLASS_CONST),
		      (DIAG_W2F_UNEXPECTED_IOC,
		       IOITEM_name(WN_IOITEM(item)), "WN2F_io_control"));
#if 0 //FIXME
      if (Format_Stmts == NULL)
	 Format_Stmts = New_Token_Buffer();

      reset_XlationContext_no_newline(ctxt);
      WN2F_Stmt_Newline(Format_Stmts, Num2Str(Origfmt_Ioctrl_Label, "%lld"), 
			WN_linenum(item), ctxt);
      
      Append_Token_String(Format_Stmts, "FORMAT");
      Append_Token_String(Format_Stmts, 
			  Targ_String_Address(STC_val(WN_st(WN_kid0(item)))));
#endif
      emitted = FALSE; /* Only emitted into Format_Stmts */
      break;

   case IOC_ERR:
   case IOC_EOR:
   case IOC_END:
      Append_Token_String(xos, IOITEM_name(item_kind));
      xos << "=";
      ASSERT_DBG_WARN((WN_opc_operator(WN_kid0(item)) == OPR_GOTO),
		      (DIAG_W2F_UNEXPECTED_OPC,WN_opc_operator(item),"ERR/END/EOR="));
      Append_Token_String(xos, 
			  WHIRL2F_number_as_name(WN_label_number(WN_kid0(item))));
      break;

   case IOC_CR_FLFLAG:
   case IOC_CR_EDFLAG:
   case IOC_ERRFLAG:
   case IOC_CR_EEEFLAG:
     emitted = FALSE;
     break;

   default:
      /* The usual case; an arbitrary non-logic expression argument,
       * which is usually an integral value, an array, or a character
       * string.
       */
      Append_Token_String(xos, IOITEM_name(item_kind));
      xos << "=";
      if (TY_kind(WN_Tree_Type(WN_kid0(item))) != KIND_SCALAR)
	 ctxt.SetDerefAddr();

      /* if kid count > 1, then it's a character object */
      if (WN_kid_count(item) == 1)
	TranslateWN(xos, WN_kid0(item), ctxt);
      else
	WN2F_String_Argument(xos,WN_kid0(item),WN_kid1(item),ctxt);
      break;
   }
   
   return emitted;
} /* WN2F_io_control */



// Solaris CC workaround
// WN2F_implied_do() is declared in wn2f_stmt.h and defined in wn2f_stmt.cxx
// as WN2F_STATUS WN2F_implied_do(), not void.
//

#ifdef _SOLARIS_SOLARIS
extern WN2F_STATUS
   WN2F_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt);
#else
extern void
   WN2F_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt);
#endif

static BOOL
WN2F_io_list(xml::ostream& xos, 
	     WN          *item, 
	     XlationContext& ctxt)
{
   const IOITEM item_kind = WN_IOITEM(item);

   switch (item_kind)
   {
   case IOL_VAR:
   case IOL_ARRAY:
   case IOL_CHAR_ARRAY:
   case IOL_RECORD:
      if (WN_opc_operator(WN_kid0(item)) == OPR_LDID       &&
          ST_sclass(WN_st(WN_kid0(item))) == SCLASS_FORMAL &&
          TY_Is_Pointer(WN_ty(WN_kid0(item)))              &&
          TY_Is_Pointer(TY_pointed(WN_ty(WN_kid0(item)))))
      {
         /* Work around a f77 bug
          */
         WN_set_ty(WN_kid0(item), TY_pointed(WN_ty(WN_kid0(item))));
      }
      ctxt.SetDerefAddr(); /* Assume pass-by-reference */
      TranslateWN(xos, WN_kid0(item), ctxt);
      break;

   case IOL_CHAR: 
     { 
       WN * len = WN_kid1(item);
       if (XlationContext_cray_io(ctxt))   /* typecode is kid1 */
	len = WN_kid2(item);

       WN2F_String_Argument(xos,
			    WN_kid0(item), /* base */
			    len,           /* length */
			    ctxt);
     }
     break;

   case IOL_EXPR:
      ctxt.ResetDerefAddr(); /* Assume pass-by-value */
      TranslateWN(xos, WN_kid0(item), ctxt);
      break;
      
   case IOL_IMPLIED_DO:
   case IOL_IMPLIED_DO_1TRIP:
      ctxt.ResetDerefAddr(); /* Handled specially */
      WN2F_implied_do(xos, item, ctxt); /* Defined in WN2F_stmt.c */
      break;
        
   case IOL_LOGICAL:
      set_XlationContext_has_logical_arg(ctxt);
      ctxt.ResetDerefAddr(); /* Assume pass-by-value */
      TranslateWN(xos, WN_kid0(item), ctxt);
      break;

   case IOL_DOPE:
      {
        INT32 kids = WN_kid_count(item);

        /* base address */ 

	ctxt.SetDerefAddr(); 
	TranslateWN(xos, WN_kid0(item), ctxt);
#if 0 //August 
	if (kids > 2)  /* implied do? */
        {
	  xos << "(";

	  /* Generate the subscript list - part may be in dope address, */
          /* set up several stmts ago. may just get INTCONST(0) here    */
	
	  INT32 i = 2 ;
	  while (i < kids)
          {
	    TranslateWN(xos, WN_kid(item,i), ctxt);
	      
	    if (i++ < kids-1)
	      xos << ",";
	  }
	  xos << ")";
	}
#endif
      }
      break ;

   default:
      ASSERT_DBG_WARN(FALSE, 
		      (DIAG_W2F_UNEXPECTED_IOL,
		       IOITEM_name(WN_IOITEM(item)), "WN2F_io_list"));
      Append_Token_String(xos, IOITEM_name(WN_IOITEM(item)));
      break;
   } /* switch */
   
   return TRUE;
} /* WN2F_io_list */


/*---------- IO Statement Handler-routines and Dispatch-array ---------*/
/*---------------------------------------------------------------------*/

static void 
WN2F_ios_backspace(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed a sequence of IOCs.  Always
    * use the explicit UNIT keyword, unless there is exactly one kid an
    * it is an IOU.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_BACKSPACE || WN_IOSTMT(wn) == IOS_CR_BACKSPACE, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_backspace"));
   
   xos << "BACKSPACE";
   if (WN_kid_count(wn) == 1 && WN2F_IS_IOU(WN_kid0(wn)))
      (void)WN2F_io_item(xos, WN_kid0(wn), ctxt);
   else
      WN2F_Append_IO_CtrlList(xos,
			      wn,                 /* ios */
			      0,                  /* from kid*/
			      WN_kid_count(wn)-1, /* to kid*/
			      TRUE,               /* use keyword control */
			      ctxt);

} /* WN2F_ios_backspace */


static void 
WN2F_ios_close(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed a sequence of IOCs.  Always
    * use the explicit UNIT keyword.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_CLOSE || WN_IOSTMT(wn) == IOS_CR_CLOSE, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_close"));

   xos << "CLOSE";
   WN2F_Append_IO_CtrlList(xos,
			   wn,                 /* ios */
			   0,                  /* from kid*/
			   WN_kid_count(wn)-1, /* to kid*/
			   TRUE,               /* use keyword control */
			   ctxt);
} /* WN2F_ios_close */


static void 
WN2F_ios_definefile(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed a sequence of IOCs.  Always
    * use the explicit UNIT keyword.
    */
   ASSERT_FATAL(WN_io_statement(wn) == IOS_DEFINEFILE   &&
		WN_kid_count(wn) == 5                   &&
		WN_io_item(WN_kid(wn, 1)) == IOC_MAXREC &&
		WN_io_item(WN_kid(wn, 2)) == IOC_RECL   &&
		WN_io_item(WN_kid(wn, 3)) == IOC_U      &&
		WN_io_item(WN_kid(wn, 4)) == IOC_ASSOCIATEVARIABLE,
		(DIAG_W2F_UNEXPECTED_IOS, 
		 IOSTATEMENT_name(WN_IOSTMT(wn)), 
		 "WN2F_ios_definefile"));

   xos << "DEFINE FILE";

   reset_XlationContext_keyword_ioctrl(ctxt);
   WN2F_io_unit(xos, WN_kid(wn, 0), ctxt);
   xos << "(";

   if (TY_kind(WN_Tree_Type(WN_kid0(WN_kid(wn, 1)))) != KIND_SCALAR)
      ctxt.SetDerefAddr();
   TranslateWN(xos, WN_kid0(WN_kid(wn, 1)), ctxt);
   ctxt.ResetDerefAddr();
   xos << ",";

   if (TY_kind(WN_Tree_Type(WN_kid0(WN_kid(wn, 2)))) != KIND_SCALAR)
      ctxt.SetDerefAddr();
   TranslateWN(xos, WN_kid0(WN_kid(wn, 2)), ctxt);
   ctxt.ResetDerefAddr();
   xos << ",";

   xos << "U";
   xos << ",";

   if (TY_kind(WN_Tree_Type(WN_kid0(WN_kid(wn, 4)))) != KIND_SCALAR)
      ctxt.SetDerefAddr();
   TranslateWN(xos, WN_kid0(WN_kid(wn, 4)), ctxt);
   xos << ")";
   
} /* WN2F_ios_definefile */


static void 
WN2F_ios_delete(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed a sequence of IOCs.  Always
    * use the explicit UNIT keyword.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_DELETE, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_delete"));
   
   xos << "DELETE";
   WN2F_Append_IO_CtrlList(xos,
			   wn,                 /* ios */
			   0,                  /* from kid*/
			   WN_kid_count(wn)-1, /* to kid*/
			   TRUE,               /* use keyword control */
			   ctxt);
} /* WN2F_ios_delete */


static void 
WN2F_ios_endfile(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed a sequence of IOCs.  Always
    * use the explicit UNIT keyword, unless there is exactly one kid an
    * it is an IOU.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_ENDFILE || WN_IOSTMT(wn) == IOS_CR_ENDFILE, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_endfile"));
   
   xos << "ENDFILE";
   if (WN_kid_count(wn) == 1 && WN2F_IS_IOU(WN_kid0(wn)))
      (void)WN2F_io_item(xos, WN_kid0(wn), ctxt);
   else
      WN2F_Append_IO_CtrlList(xos,
			      wn,                 /* ios */
			      0,                  /* from kid*/
			      WN_kid_count(wn)-1, /* to kid*/
			      TRUE,               /* use keyword control */
			      ctxt);

} /* WN2F_ios_endfile */


static void 
WN2F_ios_find(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed a sequence of IOCs.  Always
    * use the explicit UNIT keyword.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_FIND, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_find"));

   xos << "FIND";
   WN2F_Append_IO_CtrlList(xos,
			   wn,                 /* ios */
			   0,                  /* from kid*/
			   WN_kid_count(wn)-1, /* to kid*/
			   TRUE,               /* use keyword control */
			   ctxt);
} /* WN2F_ios_find */


static void 
WN2F_ios_inquire(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an optional IOU, followed a sequence of IOCs.
    * Always use the explicit UNIT keyword when the IOU is present.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_INQUIRE || WN_IOSTMT(wn) == IOS_CR_INQUIRE,
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_inquire"));

   xos << "INQUIRE";
   WN2F_Append_IO_CtrlList(xos,
			   wn,                 /* ios */
			   0,                  /* from kid*/
			   WN_kid_count(wn)-1, /* to kid*/
			   TRUE,               /* use keyword control */
			   ctxt);
} /* WN2F_ios_inquire */


static void 
WN2F_ios_namelist(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_NAMELIST, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_namelist"));

   xos << "NAMELIST";
   xos << "/";
   (void)WN2F_io_item(xos, WN_kid1(wn), ctxt);
   xos << "/";

   if (WN_kid_count(wn) > 2)
      WN2F_Append_IO_List(xos, wn, 2, ctxt);

} /* WN2F_ios_namelist */


static void 
WN2F_ios_open(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed a sequence of IOCs.  Always
    * use the explicit UNIT keyword.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_OPEN || WN_IOSTMT(wn) == IOS_CR_OPEN, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_open"));

   xos << "OPEN";
   WN2F_Append_IO_CtrlList(xos,
			   wn,                 /* ios */
			   0,                  /* from kid*/
			   WN_kid_count(wn)-1, /* to kid*/
			   TRUE,               /* use keyword control */
			   ctxt);
} /* WN2F_ios_open */


static void 
WN2F_ios_rewind(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed a sequence of IOCs.  Always
    * use the explicit UNIT keyword, unless there is exactly one kid
    * and it is an IOU.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_REWIND || WN_IOSTMT(wn) == IOS_CR_REWIND, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_rewind"));
   
   xos << "REWIND";
   if (WN_kid_count(wn) == 1 && WN2F_IS_IOU(WN_kid0(wn)))
      (void)WN2F_io_item(xos, WN_kid0(wn), ctxt);
   else
      WN2F_Append_IO_CtrlList(xos,
			      wn,                 /* ios */
			      0,                  /* from kid*/
			      WN_kid_count(wn)-1, /* to kid*/
			      TRUE,               /* use keyword control */
			      ctxt);
} /* WN2F_ios_rewind */


static void 
WN2F_ios_unlock(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed a sequence of IOCs.  Always
    * use the explicit UNIT keyword, unless there is exactly one kid an
    * it is an IOU.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_UNLOCK, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_unlock"));
   
   xos << "UNLOCK";
   if (WN_kid_count(wn) == 1 && WN2F_IS_IOU(WN_kid0(wn)))
      (void)WN2F_io_item(xos, WN_kid0(wn), ctxt);
   else
      WN2F_Append_IO_CtrlList(xos,
			      wn,                 /* ios */
			      0,                  /* from kid*/
			      WN_kid_count(wn)-1, /* to kid*/
			      TRUE,               /* use keyword control */
			      ctxt);

} /* WN2F_ios_unlock */


static void 
WN2F_ios_accept(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOF, followed a sequence of IOLs.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_ACCEPT, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_accept"));
   
   xos << "ACCEPT";
   (void)WN2F_io_item(xos, WN_kid0(wn), ctxt);
   if (WN_kid_count(wn) > 1)
   {
      xos << ",";
      WN2F_Append_IO_List(xos, wn, 1, ctxt);
   }
} /* WN2F_ios_accept */


static void
WN2F_ios_decode(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed by an IOF, followed by a
    * sequence of IOCs and a sequence of IOLs.  Use keywords only
    * when the IOC list is non-empty.  Note that the IOU contains
    * both the integer expression (c) and the scalar or array 
    * reference (a) in "ENCODE (c, f, a [,IOSTAT=ios][,ERR=s]) iolist".
    */
   INT  iol_kid;
   
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_DECODE, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_decode"));
   
   /* This is needed for the translation of the number of characters and
    * the buffer we decode characters from.
    */
   ctxt.SetDerefAddr();

   xos << "DECODE(";

   /* Translate the number of characters */
   ASSERT_WARN(WN_IOITEM(WN_kid0(wn)) == IOU_INTERNAL &&
	       WN_kid_count(WN_kid0(wn)) >= 2,
	       (DIAG_W2F_UNEXPECTED_IOU, 
		IOITEM_name(WN_IOITEM(WN_kid0(wn))), "WN2F_ios_decode"));
   TranslateWN(xos, WN_kid1(WN_kid0(wn)), ctxt);

   /* Translate the format */
   xos << ",";
   (void)WN2F_io_item(xos, WN_kid1(wn), ctxt);

   /* Translate the buffer we decode from */
   xos << ",";
   TranslateWN(xos, WN_kid0(WN_kid0(wn)), ctxt);

   /* Translate the EOSTAT and the ERR items */
   iol_kid = 2;
   if (WN_kid_count(wn) > 2 && WN2F_IS_IOC(WN_kid(wn, 2)))
   {
      iol_kid = 3;
      xos << ",";
      (void)WN2F_io_item(xos, WN_kid(wn, 2), ctxt);
   }
   if (WN_kid_count(wn) > 3 && WN2F_IS_IOC(WN_kid(wn, 3)))
   {
      iol_kid = 4;
      xos << ",";
      (void)WN2F_io_item(xos, WN_kid(wn, 3), ctxt);
   }
   xos << ")";
      
   /* Get the io_list */
   if (WN_kid_count(wn) > iol_kid)
      WN2F_Append_IO_List(xos, wn, iol_kid, ctxt);

} /* WN2F_ios_decode */


static void 
WN2F_ios_encode(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed by an IOF, followed by a
    * sequence of IOCs and a sequence of IOLs.  Use keywords only
    * when the IOC list is non-empty.  Note that the IOU contains
    * both the integer expression (c) and the scalar or array 
    * reference (a) in "ENCODE (c, f, a [,IOSTAT=ios][,ERR=s]) iolist".
    */
   INT  iol_kid;
   
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_ENCODE, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_ENcode"));
   
   /* This is needed for the translation of the number of characters and
    * the buffer we encode characters from.
    */
   ctxt.SetDerefAddr();

   xos << "ENCODE(";

   /* Translate the number of characters */
   ASSERT_WARN(WN_IOITEM(WN_kid0(wn)) == IOU_INTERNAL &&
	       WN_kid_count(WN_kid0(wn)) >= 2,
	       (DIAG_W2F_UNEXPECTED_IOU, 
		IOITEM_name(WN_IOITEM(WN_kid0(wn))), "WN2F_ios_encode"));
   TranslateWN(xos, WN_kid1(WN_kid0(wn)), ctxt);

   /* Translate the format */
   xos << ",";
   (void)WN2F_io_item(xos, WN_kid1(wn), ctxt);

   /* Translate the buffer we encode from */
   xos << ",";
   TranslateWN(xos, WN_kid0(WN_kid0(wn)), ctxt);

   /* Translate the EOSTAT and the ERR items */
   iol_kid = 2;
   if (WN_kid_count(wn) > 2 && WN2F_IS_IOC(WN_kid(wn, 2)))
   {
      iol_kid = 3;
      xos << ",";
      (void)WN2F_io_item(xos, WN_kid(wn, 2), ctxt);
   }
   if (WN_kid_count(wn) > 3 && WN2F_IS_IOC(WN_kid(wn, 3)))
   {
      iol_kid = 4;
      xos << ",";
      (void)WN2F_io_item(xos, WN_kid(wn, 3), ctxt);
   }
   xos << ")";
      
   /* Get the io_list */
   if (WN_kid_count(wn) > iol_kid)
      WN2F_Append_IO_List(xos, wn, iol_kid, ctxt);

} /* WN2F_ios_encode */


static void 
WN2F_ios_print(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   INT iol_kid;
   
   /* The kids should be an IOF, followed a sequence of IOLs.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_PRINT, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_print"));
   
   xos << "PRINT";

   set_XlationContext_issue_ioc_asterisk(ctxt);

   /* We do not really expect to have a unit specification for a "PRINT"
    * statement, but just in the case one occurs anyway, we skip it here.
    */
   if (WN2F_IS_IOU(WN_kid0(wn)))
      iol_kid = 2; /* kid 1 must be the format */
   else
      iol_kid = 1; /* Missing unit number */
   (void)WN2F_io_item(xos, WN_kid(wn, iol_kid-1), ctxt);
   if (WN_kid_count(wn) > iol_kid)
   {
      xos << ",";
      WN2F_Append_IO_List(xos, wn, iol_kid, ctxt);
   }

   reset_XlationContext_issue_ioc_asterisk(ctxt);

} /* WN2F_ios_print */


static void 
WN2F_ios_read(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed by an IOF, followed by a
    * sequence of IOCs and a sequence of IOLs.  Use keywords only
    * when the IOC list is non-empty.  The IOL should be a sequence
    * of addresses into which the values read should be put.  In
    * the whirl2f output these addresses must be dereferenced.
    */
   INT  iol_kid;
   BOOL use_keyword;
   
   
   xos << "READ";
   set_XlationContext_issue_ioc_asterisk(ctxt);

   /* Determine whether or not we have the "READ f [,iolist]" format.
    */
   if (WN_IOITEM(WN_kid0(wn)) == IOU_DEFAULT           && 
       WN2F_IS_IOF(WN_kid1(wn))                         &&
       WN_IOITEM(WN_kid1(wn)) != IOF_NAMELIST_DIRECTED &&
       (WN_kid_count(wn) == 2 || WN2F_IS_IOL(WN_kid(wn, 2))))
   {
      (void)WN2F_io_item(xos, WN_kid0(wn), ctxt);
      iol_kid = 2;
      if (WN_kid_count(wn) > 2)
	 xos << ",";
   }
   else
   {
      /* Determine if we should use the "unit=" or "fmt=" keyword notation,
       * and which kid is the last control specification item.
       */
      use_keyword = (WN_kid_count(wn) > 2       &&
		     WN2F_IS_IOF(WN_kid(wn, 1)) &&
		     WN2F_IS_IOC(WN_kid(wn, 2)));
      for (iol_kid = 0; 
	   (iol_kid < WN_kid_count(wn)) && !WN2F_IS_IOL(WN_kid(wn, iol_kid));
	   iol_kid++);
   
      /* Get the IOU, IOF, and IOC items */
      WN2F_Append_IO_CtrlList(xos,
			      wn,          /* ios */
			      0,           /* from kid*/
			      iol_kid-1,   /* to kid*/
			      use_keyword, /* use keyword control */
			      ctxt);
   }
      
   /* Get the io_list */
   if (iol_kid < WN_kid_count(wn))
   {
      set_XlationContext_deref_io_item(ctxt); /* Assume pass-by-reference */
      WN2F_Append_IO_List(xos, wn, iol_kid, ctxt);
   }

    reset_XlationContext_issue_ioc_asterisk(ctxt);

} /* WN2F_ios_read */


static void 
WN2F_ios_rewrite(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed by an IOF, followed by a
    * sequence of IOCs and a sequence of IOLs.  Use keywords only
    * when the IOC list is non-empty.
    */
   INT  iol_kid;
   BOOL use_keyword;
   
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_REWRITE, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_rewrite"));

   xos << "REWRITE";
   set_XlationContext_issue_ioc_asterisk(ctxt);

   /* Determine if we should use the "unit=" or "fmt=" keyword notation,
    * and which kid is the last control specification itemx.
    */
   use_keyword = (WN_kid_count(wn) > 2 &&
		  WN2F_IS_IOF(WN_kid(wn, 1)) &&
		  WN2F_IS_IOC(WN_kid(wn, 2)));
   for (iol_kid = 0; 
	(iol_kid < WN_kid_count(wn)) && !WN2F_IS_IOL(WN_kid(wn, iol_kid));
	iol_kid++);
   
   /* Get the IOU, IOF, and IOC items */
   WN2F_Append_IO_CtrlList(xos,
			   wn,          /* ios */
			   0,           /* from kid*/
			   iol_kid-1,     /* to kid*/
			   use_keyword, /* use keyword control */
			   ctxt);
   
   /* Get the io_list */
   if (iol_kid < WN_kid_count(wn))
      WN2F_Append_IO_List(xos, wn, iol_kid, ctxt);

   reset_XlationContext_issue_ioc_asterisk(ctxt);

} /* WN2F_ios_rewrite */


static void 
WN2F_ios_type(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOF, followed a sequence of IOLs.
    */
   ASSERT_WARN(WN_IOSTMT(wn) == IOS_TYPE, 
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_type"));
   
   xos << "TYPE";
   (void)WN2F_io_item(xos, WN_kid0(wn), ctxt);
   if (WN_kid_count(wn) > 1)
   {
      xos << ",";
      WN2F_Append_IO_List(xos, wn, 1, ctxt);
   }
} /* WN2F_ios_type */


static void 
WN2F_ios_write(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* The kids should be an IOU, followed by an IOF, followed by a
    * sequence of IOCs and a sequence of IOLs.  Use keywords only
    * when the IOC list is non-empty.
    */
   xos << BegElem("xaif:Intrinsic") << Attr("vertex_id", ctxt.GetNewVId())
       << Attr("name", "WRITE");

   set_XlationContext_issue_ioc_asterisk(ctxt);

   /* Determine if we should use the "unit=" or "fmt=" keyword notation,
    * and which kid is the last control specification item.
    */
   BOOL use_keyword = (WN_kid_count(wn) > 2 &&
		       WN2F_IS_IOF(WN_kid(wn, 1)) &&
		       WN2F_IS_IOC(WN_kid(wn, 2)));
   INT  iol_kid;
   for (iol_kid = 0; 
	(iol_kid < WN_kid_count(wn)) && !WN2F_IS_IOL(WN_kid(wn, iol_kid));
	iol_kid++);
   
   /* Get the IOU, IOF, and IOC items */
   WN2F_Append_IO_CtrlList(xos,
			   wn,          /* ios */
			   0,           /* from kid */
			   iol_kid-1,   /* to kid */
			   use_keyword, /* use keyword control */
			   ctxt);
   
   /* Get the io_list */
   if (iol_kid < WN_kid_count(wn))
     WN2F_Append_IO_List(xos, wn, iol_kid, ctxt);
   
   reset_XlationContext_issue_ioc_asterisk(ctxt);
   xos << EndElem;

} /* WN2F_ios_write */


/*------------------------- Cray Library routines ---------------------*/
/*---------------------------------------------------------------------*/

static void 
WN2F_ios_cr(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* Craylibs IO - write/read The kids should be an IOS, with kids of IO_ITEMS */
   INT  iol_kid;
   char * p ;

   ASSERT_WARN(WN_IOSTMT(wn) == IOS_CR_FWF || 
	       WN_IOSTMT(wn) == IOS_CR_FWU || 
               WN_IOSTMT(wn) == IOS_CR_FRF || 
	       WN_IOSTMT(wn) == IOS_CR_FRU,
	       (DIAG_W2F_UNEXPECTED_IOS, 
		IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_cr"));

   set_XlationContext_issue_ioc_asterisk(ctxt);

   /* See if this is the first/last part of a 3-call IO stmt. If so punt */
   /* - it just duplicates some detail from the main stmt.               */
   for (iol_kid = 0; iol_kid < WN_kid_count(wn); iol_kid++)
   {
     WN * item = WN_kid(wn,iol_kid);
     if (WN_io_item(item) == IOC_CR_FLFLAG)
     {
       INT32 i = (WN_const_val(WN_kid0(item)) & 3);
       if (i != 0 && i != 3)
	 return;
       else
	 break;
     }
   }

   /* decide if read/write formatted/unformatted */
   if (WN_IOSTMT(wn) == IOS_CR_FWF || WN_IOSTMT(wn) == IOS_CR_FRF)
     set_XlationContext_fmt_io(ctxt) ;

   if (WN_IOSTMT(wn) == IOS_CR_FRF || WN_IOSTMT(wn) == IOS_CR_FRU)
     p = "READ***" ;
   else 
     p = "WRITE***";

   xos << BegElem("xaif:Intrinsic") << Attr("vertex_id", ctxt.GetNewVId())
       << Attr("name", p);

   /* count items in control list */
   for (iol_kid = 0; 
	(iol_kid < WN_kid_count(wn)) && !WN2F_IS_IOL(WN_kid(wn, iol_kid));
	iol_kid++);
   
   /* Get the IOU, IOF, and IOC items */
   WN2F_Append_IO_CtrlList(xos,
			   wn,          /* ios */
			   0,           /* from kid */
			   iol_kid-1,   /* to kid */
			   FALSE,       /* use keyword control */
			   ctxt);
   
   /* Get the io_list */
   if (iol_kid < WN_kid_count(wn))
      WN2F_Append_IO_List(xos, wn, iol_kid, ctxt);

   reset_XlationContext_issue_ioc_asterisk(ctxt);

   xos << EndElem;
} /* WN2F_ios_cr */

/*------------------------- Exported routines -------------------------*/
/*---------------------------------------------------------------------*/

void WN2F_Io_initialize(void)
{
   Ios_Handler[IOS_BACKSPACE] = &WN2F_ios_backspace;
   Ios_Handler[IOS_CLOSE] = &WN2F_ios_close;
   Ios_Handler[IOS_DEFINEFILE] = &WN2F_ios_definefile;
   Ios_Handler[IOS_DELETE] = &WN2F_ios_delete;
   Ios_Handler[IOS_ENDFILE] = &WN2F_ios_endfile;
   Ios_Handler[IOS_FIND] = &WN2F_ios_find;
   Ios_Handler[IOS_INQUIRE] = &WN2F_ios_inquire;
   Ios_Handler[IOS_NAMELIST] = &WN2F_ios_namelist;
   Ios_Handler[IOS_OPEN] = &WN2F_ios_open;
   Ios_Handler[IOS_REWIND] = &WN2F_ios_rewind;
   Ios_Handler[IOS_UNLOCK] = &WN2F_ios_unlock;
   Ios_Handler[IOS_ACCEPT] = &WN2F_ios_accept;
   Ios_Handler[IOS_DECODE] = &WN2F_ios_decode;
   Ios_Handler[IOS_ENCODE] = &WN2F_ios_encode;
   Ios_Handler[IOS_PRINT] = &WN2F_ios_print;
   Ios_Handler[IOS_READ] = &WN2F_ios_read;
   Ios_Handler[IOS_REWRITE] = &WN2F_ios_rewrite;
   Ios_Handler[IOS_TYPE] = &WN2F_ios_type;
   Ios_Handler[IOS_WRITE] = &WN2F_ios_write;
   Ios_Handler[IOS_CR_FWF]   = &WN2F_ios_cr;
   Ios_Handler[IOS_CR_FRN]   = &WN2F_ios_read;  
   Ios_Handler[IOS_CR_FWN]   = &WN2F_ios_write;  
   Ios_Handler[IOS_CR_FWU]   = &WN2F_ios_cr;
   Ios_Handler[IOS_CR_FRF]   = &WN2F_ios_cr;
   Ios_Handler[IOS_CR_FRU]   = &WN2F_ios_cr;
   Ios_Handler[IOS_CR_OPEN]  = &WN2F_ios_open;
   Ios_Handler[IOS_CR_CLOSE] = &WN2F_ios_close;
   Ios_Handler[IOS_CR_REWIND] = &WN2F_ios_rewind;
   Ios_Handler[IOS_CR_INQUIRE] = &WN2F_ios_inquire;
   Ios_Handler[IOS_CR_ENDFILE] = &WN2F_ios_endfile;
   Ios_Handler[IOS_CR_BACKSPACE] = &WN2F_ios_backspace;

} /* WN2F_Io_initialize */

void WN2F_Io_finalize(void)
{
   /* Do nothing for now! */
} /* WN2F_Io_finalize */

static BOOL
Is_Cray_IO(IOSTATEMENT ios)
{
  BOOL res ;
 
  res = (ios == IOS_CR_FWF) ||
        (ios == IOS_CR_FWU) ||
        (ios == IOS_CR_FRF) ||
        (ios == IOS_CR_FRU) ||
        (ios == IOS_CR_OPEN) ||
        (ios == IOS_CR_CLOSE) ||
        (ios == IOS_CR_REWIND) ||
        (ios == IOS_CR_INQUIRE) ||
        (ios == IOS_CR_ENDFILE) ||
        (ios == IOS_CR_FRN) ||         
        (ios == IOS_CR_FWN) ||          
        (ios == IOS_CR_BACKSPACE);

  return res ;
}

#if 0
xml::ostream&
WN2F_io_prefix_tokens(void)
{
   return Ios_Prefix_Tokens;
}
#endif

WN2F_STATUS 
WN2F_io(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   INT          ios_kid;
   //FIXME xml::ostream& ios_tokens = New_Token_Buffer();

   ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_IO, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_io"));
   
   /* Should we use the string given by an IOC_VARFMT_ORIGFMT
    * for a IOF_LABEL?
    */
   for (ios_kid = 0; 
	(ios_kid < WN_kid_count(wn) &&
	 WN_io_item(WN_kid(wn, ios_kid)) != IOC_VARFMT_ORIGFMT); 
	ios_kid++);
   if (ios_kid < WN_kid_count(wn)) {
     set_XlationContext_origfmt_ioctrl(ctxt);
     Origfmt_Ioctrl_Label = W2CF_Symtab_Unique_Label();
   }

   /* Now dispatch to the appropriate handler routine for each
    * kind of IO statement, after beginning the statement on a
    * new line and setting the appropriate ctxt flags.
    */
   xos << std::endl;
   set_XlationContext_io_stmt(ctxt);
   set_XlationContext_no_newline(ctxt);
   //FIXME Ios_Prefix_Tokens = New_Token_Buffer();

   const IOSTATEMENT ios = WN_IOSTMT(wn);

   if (Is_Cray_IO(ios)) 
     set_XlationContext_cray_io(ctxt) ;

   if (Ios_Handler[ios] == NULL) {
     xos << "<<FLIST cannot handle ";
     Append_Token_String(xos, get_iostatement_name(ios));
     xos << " io statement>>";
   } else {
     Ios_Handler[ios](xos, wn, ctxt);
   }

#if 0 //FIXME
   if (Ios_Prefix_Tokens != NULL)
      Append_And_Reclaim_Token_List(xos, &Ios_Prefix_Tokens);
   Append_And_Reclaim_Token_List(xos, &ios_tokens);
   if (Format_Stmts != NULL)
      Append_And_Reclaim_Token_List(xos, &Format_Stmts);
#endif
   
   reset_XlationContext_cray_io(ctxt) ;             

   return EMPTY_WN2F_STATUS;
} /* WN2F_io */


BOOL
WN2F_io_item(xml::ostream& xos, WN* item, XlationContext& ctxt)
{
  // Returns TRUE when something (anything) was emitted for this item.
  BOOL emitted = FALSE;

  /* Any pointer-argument to an io-item should be dereferenced.  Most
   * notably, this applies for an LDA of a character string in a FMT
   * specifier, but it also applies for a variety of other arguments.
   * Such dereferences are specified within the WN2F_io routines.
   */
  if (XlationContext_deref_io_item(ctxt))
    ctxt.SetDerefAddr();
  else
    ctxt.ResetDerefAddr();
  
  if (WN2F_IS_IOU(item))
    emitted = WN2F_io_unit(xos, item, ctxt);
  else if (WN2F_IS_IOF(item))
    emitted = WN2F_io_format(xos, item, ctxt);
  else if (WN2F_IS_IOC(item))
    emitted = WN2F_io_control(xos, item, ctxt);
  else if (WN2F_IS_IOL(item))
    emitted = WN2F_io_list(xos, item, ctxt);
  else
    ASSERT_DBG_WARN(FALSE, (DIAG_W2F_UNEXPECTED_IOL, 
			    (IOITEM_name(WN_IOITEM(item)) != NULL? 
			     IOITEM_name(WN_IOITEM(item)):"unknown_name"), 
			    "WN2F_io_item"));
  
  return emitted;
} /* WN2F_io_item */

