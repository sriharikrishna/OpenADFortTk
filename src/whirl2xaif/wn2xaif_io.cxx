// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_io.cxx,v 1.10 2003/09/05 21:41:53 eraxxon Exp $

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

#include <include/Open64BasicTypes.h> /* Open64 basic types */

//*************************** User Include Files ****************************

#include "whirl2f_common.h"
#include "PUinfo.h"
#include "wn2xaif.h"
#include "st2xaif.h"
#include "ty2xaif.h"
#include "wn2xaif_io.h"
#include "wn2xaif_mem.h"

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//************************** Forward Declarations ***************************

// xlate_IO_IOS_BACKSPACE
static void 
WN2F_ios_backspace(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_close(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_definefile(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_delete(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_endfile(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_find(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_inquire(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_namelist(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_open(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_rewind(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_unlock(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_accept(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void
WN2F_ios_decode(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_encode(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_print(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_read(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_rewrite(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_type(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_write(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
WN2F_ios_cr(xml::ostream& xos, WN *wn, XlationContext& ctxt);


static BOOL
xlate_IO_ITEM_unit(xml::ostream& xos, WN *item, XlationContext& ctxt);

static BOOL
xlate_IO_ITEM_format(xml::ostream& xos, WN* item, XlationContext& ctxt);

static BOOL
xlate_IO_ITEM_control(xml::ostream& xos, WN* item, XlationContext& ctxt);

static BOOL 
xlate_IO_ITEM_list(xml::ostream& xos, WN *item, XlationContext& ctxt);

//************************** Forward Declarations ***************************

/* A rather special IOC item to replace an IOF_LABEL item.  This
 * value is only valid when XlationContext_origfmt_ioctrl is TRUE! */
static UINT32       Origfmt_Ioctrl_Label;

#define WN_IOITEM(x) ((IOITEM) WN_io_item(x))
#define WN_IOSTMT(x) ((IOSTATEMENT) WN_io_statement(x))

/* several craylib/dope items represent a no-op by a zero inconst...*/
#define IS_IO_NULL_OPR(wn) ((WN_operator(wn) == OPR_INTCONST) && (WN_const_val(wn) == 0))

#define IS_IO_ITEM_IOU(item) \
   (WN_IOITEM(item) >= IOU_NONE && WN_IOITEM(item) <= IOU_INTERNAL)
#define IS_IO_ITEM_IOF(item) \
   ((WN_IOITEM(item) >= IOF_NONE && WN_IOITEM(item) <= IOF_CR_FMTSRC_DOPE))
#define IS_IO_ITEM_IOC(item) \
   (WN_IOITEM(item) >= IOC_ACCESS && WN_IOITEM(item) <= IOC_ERRFLAG)
#define IS_IO_ITEM_IOL(item) \
   ((WN_IOITEM(item) >= IOL_ARRAY && WN_IOITEM(item) <= IOL_VAR) || \
    (WN_IOITEM(item) == IOL_DOPE))

//***************************************************************************

typedef void (*XlateWNHandlerFunc)(xml::ostream&, WN *, XlationContext&);
static XlateWNHandlerFunc XlateWNio_HandlerTable[IOSTATEMENT_LAST+1];

void WN2F_Io_initialize(void)
{
  XlateWNio_HandlerTable[IOS_BACKSPACE] = &WN2F_ios_backspace;
  XlateWNio_HandlerTable[IOS_CLOSE] = &WN2F_ios_close;
  XlateWNio_HandlerTable[IOS_DEFINEFILE] = &WN2F_ios_definefile;
  XlateWNio_HandlerTable[IOS_DELETE] = &WN2F_ios_delete;
  XlateWNio_HandlerTable[IOS_ENDFILE] = &WN2F_ios_endfile;
  XlateWNio_HandlerTable[IOS_FIND] = &WN2F_ios_find;
  XlateWNio_HandlerTable[IOS_INQUIRE] = &WN2F_ios_inquire;
  XlateWNio_HandlerTable[IOS_NAMELIST] = &WN2F_ios_namelist;
  XlateWNio_HandlerTable[IOS_OPEN] = &WN2F_ios_open;
  XlateWNio_HandlerTable[IOS_REWIND] = &WN2F_ios_rewind;
  XlateWNio_HandlerTable[IOS_UNLOCK] = &WN2F_ios_unlock;
  XlateWNio_HandlerTable[IOS_ACCEPT] = &WN2F_ios_accept;
  XlateWNio_HandlerTable[IOS_DECODE] = &WN2F_ios_decode;
  XlateWNio_HandlerTable[IOS_ENCODE] = &WN2F_ios_encode;
  XlateWNio_HandlerTable[IOS_PRINT] = &WN2F_ios_print;
  XlateWNio_HandlerTable[IOS_READ] = &WN2F_ios_read;
  XlateWNio_HandlerTable[IOS_REWRITE] = &WN2F_ios_rewrite;
  XlateWNio_HandlerTable[IOS_TYPE] = &WN2F_ios_type;
  XlateWNio_HandlerTable[IOS_WRITE] = &WN2F_ios_write;
  XlateWNio_HandlerTable[IOS_CR_FWF]   = &WN2F_ios_cr;
  XlateWNio_HandlerTable[IOS_CR_FRN]   = &WN2F_ios_read;  
  XlateWNio_HandlerTable[IOS_CR_FWN]   = &WN2F_ios_write;  
  XlateWNio_HandlerTable[IOS_CR_FWU]   = &WN2F_ios_cr;
  XlateWNio_HandlerTable[IOS_CR_FRF]   = &WN2F_ios_cr;
  XlateWNio_HandlerTable[IOS_CR_FRU]   = &WN2F_ios_cr;
  XlateWNio_HandlerTable[IOS_CR_OPEN]  = &WN2F_ios_open;
  XlateWNio_HandlerTable[IOS_CR_CLOSE] = &WN2F_ios_close;
  XlateWNio_HandlerTable[IOS_CR_REWIND] = &WN2F_ios_rewind;
  XlateWNio_HandlerTable[IOS_CR_INQUIRE] = &WN2F_ios_inquire;
  XlateWNio_HandlerTable[IOS_CR_ENDFILE] = &WN2F_ios_endfile;
  XlateWNio_HandlerTable[IOS_CR_BACKSPACE] = &WN2F_ios_backspace;
  
} /* WN2F_Io_initialize */

void WN2F_Io_finalize(void)
{
   /* Do nothing for now! */
} /* WN2F_Io_finalize */

static BOOL
Is_Cray_IO(IOSTATEMENT ios)
{
  BOOL res ;
  res = (ios == IOS_CR_FWF) || (ios == IOS_CR_FWU) || (ios == IOS_CR_FRF) 
    || (ios == IOS_CR_FRU) || (ios == IOS_CR_OPEN) || (ios == IOS_CR_CLOSE)
    || (ios == IOS_CR_REWIND) || (ios == IOS_CR_INQUIRE) 
    || (ios == IOS_CR_ENDFILE) || (ios == IOS_CR_FRN) || (ios == IOS_CR_FWN)
    || (ios == IOS_CR_BACKSPACE);
  return res ;
}

WN2F_STATUS 
whirl2xaif::xlate_IO(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_opc_operator(wn) == OPR_IO, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_IO"));
  
  // FIXME Should we use the string given by an IOC_VARFMT_ORIGFMT for a
  // IOF_LABEL?
  INT ios_kid = 0;
  for ( ; (ios_kid < WN_kid_count(wn) &&
	   WN_io_item(WN_kid(wn, ios_kid)) != IOC_VARFMT_ORIGFMT); 
	ios_kid++);
  if (ios_kid < WN_kid_count(wn)) {
    set_XlationContext_origfmt_ioctrl(ctxt);
    Origfmt_Ioctrl_Label = W2CF_Symtab_Unique_Label();
  }
  
  /* FIXME Now dispatch to the appropriate handler routine for each kind of
   * IO statement, after beginning the statement on a new line and
   * setting the appropriate ctxt flags.  */
  set_XlationContext_io_stmt(ctxt);
  set_XlationContext_no_newline(ctxt);
  
  const IOSTATEMENT ios = WN_IOSTMT(wn);
  ASSERT_FATAL(XlateWNio_HandlerTable[ios] != NULL,
	       (DIAG_W2F_UNEXPECTED_OPC, get_iostatement_name(ios)));
  
  if (Is_Cray_IO(ios)) 
    set_XlationContext_cray_io(ctxt);
  XlateWNio_HandlerTable[ios](xos, wn, ctxt);
  reset_XlationContext_cray_io(ctxt);
  
  return EMPTY_WN2F_STATUS;
}


BOOL
whirl2xaif::xlate_IO_ITEM(xml::ostream& xos, WN* item, XlationContext& ctxt)
{
  // Returns TRUE when something (anything) was emitted for this item.
  BOOL emitted = FALSE;

  /* Any pointer-argument to an io-item should be dereferenced.  Most
   * notably, this applies for an LDA of a character string in a FMT
   * specifier, but it also applies for a variety of other arguments.
   * Such dereferences are specified within the xlate_IO routines.
   */
  if (XlationContext_deref_io_item(ctxt))
    ctxt.SetDerefAddr();
  else
    ctxt.ResetDerefAddr();
  
  if (IS_IO_ITEM_IOU(item))
    emitted = xlate_IO_ITEM_unit(xos, item, ctxt);
  else if (IS_IO_ITEM_IOF(item))
    emitted = xlate_IO_ITEM_format(xos, item, ctxt);
  else if (IS_IO_ITEM_IOC(item))
    emitted = xlate_IO_ITEM_control(xos, item, ctxt);
  else if (IS_IO_ITEM_IOL(item))
    emitted = xlate_IO_ITEM_list(xos, item, ctxt);
  else
    ASSERT_DBG_WARN(FALSE, (DIAG_W2F_UNEXPECTED_IOL, 
			    (IOITEM_name(WN_IOITEM(item)) != NULL? 
			     IOITEM_name(WN_IOITEM(item)):"unknown_name"), 
			    "xlate_IO_ITEM"));
  
  return emitted;
} /* xlate_IO_ITEM */


//***************************************************************************
// 
//***************************************************************************

static void 
xlate_IOControlList(xml::ostream& xos, WN *ios,
		    INT from_kid, INT to_kid, XlationContext& ctxt)
{
  // Emit an IO control list (IOU, IOF, and IOC)
  for (INT ios_kid = from_kid; ios_kid <= to_kid; ios_kid++) {
    xos << BegElem("xaif:Argument") << Attr("position", ios_kid+1); //FIXME
    ctxt.CreateContext();
    xlate_IO_ITEM(xos, WN_kid(ios, ios_kid), ctxt);
    ctxt.DeleteContext();
    xos << EndElem;
  }
}

static void 
xlate_IOList(xml::ostream& xos, WN *ios, INT from_kid, XlationContext& ctxt)
{
  /* Emit an IOL list, starting at the given kid index and
   * continuing to the last kid. */
  for (INT ios_kid = from_kid; ios_kid < WN_kid_count(ios); ios_kid++) {
    xos << BegElem("xaif:Argument") << Attr("position", ios_kid+1); // FIXME
    ctxt.CreateContext();
    xlate_IO_ITEM(xos, WN_kid(ios, ios_kid), ctxt);
    ctxt.DeleteContext();
    xos << EndElem;
  }
}


/*---------------------- IO Item Handler-routines ---------------------*/
/*---------------------------------------------------------------------*/

static BOOL
xlate_IO_ITEM_unit(xml::ostream& xos, WN *item, XlationContext& ctxt)
{
  /* Any arguments assumed to be by reference unless otherwise noted */
  ctxt.SetDerefAddr();
  
  switch (WN_io_item(item)) {
  case IOU_NONE: 
    xos << Comment("unit=*");
    break;
    
  case IOU_DEFAULT: /* asterisk or double astrisk */
    xos << BegComment << "unit=" 
	<< ((WN_const_val(WN_kid0(item)) == 0) ? "**" : "*") << EndComment;
    break;
    
  case IOU_EXTERNAL:    /* unit number */
  case IOU_DOPE:
  case IOU_INTERNAL:    /* substring or array reference */
    xos << "unit***=";
    TranslateWN(xos, WN_kid0(item), ctxt); // FIXME
    break;
    
  default:
    ASSERT_DBG_WARN(FALSE, (DIAG_W2F_UNEXPECTED_IOU,
			    IOITEM_name(WN_IOITEM(item)), "xlate_IO_ITEM_unit"));
    xos << BegComment << "unit=" << IOITEM_name(WN_IOITEM(item)) 
	<< EndComment;
    break;
  } /*switch*/
  
  return TRUE; // FIXME
}


static BOOL
xlate_IO_ITEM_format(xml::ostream& xos, WN* item, XlationContext& ctxt)
{
  /* Any arguments assumed to be by reference unless otherwise noted */
  ctxt.SetDerefAddr();
  
  switch (WN_io_item(item))
   {
   case IOF_NONE:
     if (XlationContext_cray_io(ctxt) && XlationContext_fmt_io(ctxt)) {
       xos << Comment("fmt=*");
     } 
     break;

   case IOF_ASSIGNED_VAR:
     /* The front-end should never generate these, since they are converted
      * into IOF_CHAR_EXPR items.  Should we for any reason start regenerating
      * these, this is the place where it should occur.
      */
     ASSERT_DBG_WARN(FALSE, 
		     (DIAG_W2F_UNEXPECTED_IOF, IOITEM_name(WN_IOITEM(item)),
		      "xlate_IO_ITEM_format"));
     xos << BegComment << "fmt=" << IOITEM_name(WN_IOITEM(item)) << EndComment;
#if 0
     TranslateWN(xos, WN_kid0(item), ctxt);
#endif
     break;

   case IOF_LABEL:
      /* a FORMAT label or character-string expression */
     if (XlationContext_origfmt_ioctrl(ctxt)) {
	xos << BegComment << "fmt=" << Num2Str(Origfmt_Ioctrl_Label, "%lld") 
	    << EndComment;
     } else {
       xos << "fmt***";
       TranslateWN(xos, WN_kid0(item), ctxt);
     }
     break;
     
   case IOF_CHAR_EXPR:
     /* a character-substring expression */
     xos << BegComment << "fmt=";
     WN2F_String_Argument(xos, WN_kid0(item), /* base */
			  WN_kid1(item), /* length */ ctxt);
     xos << EndComment;
     break;
     
   case IOF_LIST_DIRECTED:
     xos << Comment("fmt=*");
      break;

   case IOF_NAMELIST_DIRECTED:
     xos << Comment("NML=*");
     TranslateWN(xos, WN_kid(item,WN_kid_count(item)-1), ctxt);
     Clear_BE_ST_w2fc_referenced(WN_st(WN_kid(item,WN_kid_count(item)-1)));
/* don't dump out Namelist name and corresponding type
 * in *.w2f.f file.When call TranslateWN,the namelist name(st entry) will
 * be set "referenced".Clear the flag.--------fzhao
 */
      break;

   case IOF_UNFORMATTED:
      break;

   case IOF_CR_PARSFMT:
      break;
       
   case IOF_CR_FMTSRC:
   case IOF_CR_FMTSRC_DOPE:
      {
	xos << Comment("fmt***");
	WN * kid0 = WN_kid0(item);
	if (!IS_IO_NULL_OPR(kid0))
	  TranslateWN(xos, kid0, ctxt);
	break;
      }
   default:
      ASSERT_DBG_WARN(FALSE, 
		      (DIAG_W2F_UNEXPECTED_IOF, IOITEM_name(WN_IOITEM(item)),
		       "xlate_IO_ITEM_format"));
      xos << BegComment << "fmt=" << IOITEM_name(WN_IOITEM(item)) 
	  << EndComment;
      break;
   } /*switch*/

  return TRUE; // FIXME
} /* xlate_IO_ITEM_format */

static BOOL
xlate_IO_ITEM_control(xml::ostream& xos, WN* item, XlationContext& ctxt)
{
  /* Return TRUE if a control specifier was emitted. */
  const IOITEM item_kind = WN_IOITEM(item);
  
  switch (item_kind) {
  case IOC_KEY:
    /* TODO: associate this with IOC_KEY */
    ASSERT_WARN(FALSE, (DIAG_UNIMPLEMENTED, 
			StrCat("IOC", IOITEM_name(item_kind))));
    xos << BegComment << "ctr=" << IOITEM_name(item_kind) << "=<???>"
	<< EndComment;
    break;
    
  case IOC_KEY_START:
  case IOC_KEY_END:
  case IOC_KEY_CHARACTER:
  case IOC_KEY_INTEGER: 
  case IOC_NML: /* TODO: remove from IOC enumeration! It is redundant */
    ASSERT_WARN(FALSE, (DIAG_UNIMPLEMENTED, 
			StrCat("IOC", IOITEM_name(item_kind))));
    xos << BegComment << "ctr=" << IOITEM_name(item_kind) << EndComment;
    break;
    
  case IOC_EXIST:
  case IOC_NAMED:
  case IOC_OPENED:
    /* LOGICAL argument */
    ASSERT_FATAL(WN_kid_count(item) >= 1,
		 (DIAG_W2F_UNEXPECTED_NUM_KIDS, 
		  WN_kid_count(item), 1, "xlate_IO_ITEM_control"));
    xos << IOITEM_name(item_kind) << "***=";
    set_XlationContext_has_logical_arg(ctxt);
    if (TY_kind(WN_Tree_Type(WN_kid0(item))) != KIND_SCALAR)
      ctxt.SetDerefAddr();
    TranslateWN(xos, WN_kid0(item), ctxt);
    reset_XlationContext_has_logical_arg(ctxt);
    break;
    
  case IOC_READONLY:
  case IOC_SHARED:
  case IOC_U:
    xos << BegComment << "ctr=" << IOITEM_name(item_kind) << EndComment;
    break;
    
  case IOC_VARFMT:
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
		     IOITEM_name(WN_IOITEM(item)), "xlate_IO_ITEM_control"));
    reset_XlationContext_no_newline(ctxt);
    xos << "FORMAT " << Num2Str(Origfmt_Ioctrl_Label, "%lld")
	<< Targ_String_Address(STC_val(WN_st(WN_kid0(item))));
    break;
    
  case IOC_ERR:
  case IOC_EOR:
  case IOC_END:
    xos << IOITEM_name(item_kind);
    ASSERT_DBG_WARN((WN_opc_operator(WN_kid0(item)) == OPR_GOTO),
		    (DIAG_W2F_UNEXPECTED_OPC,WN_opc_operator(item),"ERR/END/EOR="));
    xos << WHIRL2F_number_as_name(WN_label_number(WN_kid0(item)));
    break;
    
  case IOC_CR_FLFLAG:
  case IOC_CR_EDFLAG:
  case IOC_ERRFLAG:
  case IOC_CR_EEEFLAG:
    break;
    
  default:
    /* The usual case; an arbitrary non-logic expression argument,
     * which is usually an integral value, an array, or a character
     * string.
     */
    xos << IOITEM_name(item_kind) << "=";
    if (TY_kind(WN_Tree_Type(WN_kid0(item))) != KIND_SCALAR)
      ctxt.SetDerefAddr();
    
    /* if kid count > 1, then it's a character object */
    if (WN_kid_count(item) == 1)
      TranslateWN(xos, WN_kid0(item), ctxt);
    else
      WN2F_String_Argument(xos,WN_kid0(item),WN_kid1(item),ctxt);
    break;
  }
  
  return TRUE;
} /* xlate_IO_ITEM_control */


extern WN2F_STATUS // REMOVE
WN2F_implied_do(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static BOOL
xlate_IO_ITEM_list(xml::ostream& xos, WN *item, XlationContext& ctxt)
{
  const IOITEM item_kind = WN_IOITEM(item);

  switch (item_kind) {
  case IOL_VAR:
  case IOL_ARRAY:
  case IOL_CHAR_ARRAY:
  case IOL_RECORD:
    if (WN_opc_operator(WN_kid0(item)) == OPR_LDID       &&
	ST_sclass(WN_st(WN_kid0(item))) == SCLASS_FORMAL &&
	TY_Is_Pointer(WN_ty(WN_kid0(item)))              &&
	TY_Is_Pointer(TY_pointed(WN_ty(WN_kid0(item))))) {
      /* Work around a f77 bug */
      WN_set_ty(WN_kid0(item), TY_pointed(WN_ty(WN_kid0(item))));
    }
    ctxt.SetDerefAddr(); /* Assume pass-by-reference */
    TranslateWN(xos, WN_kid0(item), ctxt);
    break;
    
  case IOL_CHAR: {
    WN * len = WN_kid1(item);
    if (XlationContext_cray_io(ctxt))   /* typecode is kid1 */
      len = WN_kid2(item);
    
    WN2F_String_Argument(xos, WN_kid0(item), /* base */
			 len /* length */, ctxt);
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
    
  case IOL_DOPE: {
    INT32 kids = WN_kid_count(item);
    
    /* base address */ 
    ctxt.SetDerefAddr(); 
    TranslateWN(xos, WN_kid0(item), ctxt);
#if 0 //August 
    if (kids > 2) {  /* implied do? */
      /* Generate the subscript list - part may be in dope address, */
      /* set up several stmts ago. may just get INTCONST(0) here    */
      INT32 i = 2 ;
      while (i < kids) {
	TranslateWN(xos, WN_kid(item,i), ctxt);
      }
    }
#endif
  }
  break;
  
  default:
    ASSERT_DBG_WARN(FALSE, 
		    (DIAG_W2F_UNEXPECTED_IOL,
		     IOITEM_name(WN_IOITEM(item)), "xlate_IO_ITEM_list"));
    xos << IOITEM_name(WN_IOITEM(item));
    break;
  } /* switch */
  
  return TRUE;
} /* xlate_IO_ITEM_list */


//***************************************************************************
// SGI IO
//***************************************************************************

static void 
WN2F_ios_backspace(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  /* The kids should be an IOU, followed a sequence of IOCs.  Always
   * use the explicit UNIT keyword, unless there is exactly one kid an
   * it is an IOU.
   */
  ASSERT_WARN(WN_IOSTMT(wn) == IOS_BACKSPACE 
	      || WN_IOSTMT(wn) == IOS_CR_BACKSPACE, 
	      (DIAG_W2F_UNEXPECTED_IOS, 
	       IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_backspace"));
  
  xos << "BACKSPACE";
  if (WN_kid_count(wn) == 1 && IS_IO_ITEM_IOU(WN_kid0(wn)))
    xlate_IO_ITEM(xos, WN_kid0(wn), ctxt);
  else
    xlate_IOControlList(xos, wn,
			0 /* from kid*/, WN_kid_count(wn)-1 /* to kid*/,
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
   xlate_IOControlList(xos, wn,
		       0 /* from kid*/, WN_kid_count(wn)-1 /* to kid*/,
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

   xlate_IO_ITEM_unit(xos, WN_kid(wn, 0), ctxt);
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
  xlate_IOControlList(xos, wn,
		      0 /* from kid*/, WN_kid_count(wn)-1 /* to kid*/, ctxt);
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
  if (WN_kid_count(wn) == 1 && IS_IO_ITEM_IOU(WN_kid0(wn)))
    xlate_IO_ITEM(xos, WN_kid0(wn), ctxt);
  else
    xlate_IOControlList(xos, wn,
			0 /* from kid*/, WN_kid_count(wn)-1 /* to kid*/, ctxt);
  
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
  xlate_IOControlList(xos, wn,
		      0 /* from kid*/, WN_kid_count(wn)-1 /* to kid*/, ctxt);
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
  xlate_IOControlList(xos, wn,
		      0,                  /* from kid*/
		      WN_kid_count(wn)-1, /* to kid*/
		      ctxt);
} /* WN2F_ios_inquire */


static void 
WN2F_ios_namelist(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_WARN(WN_IOSTMT(wn) == IOS_NAMELIST, 
	      (DIAG_W2F_UNEXPECTED_IOS, 
	       IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_namelist"));
  
  xos << "NAMELIST/";
  xlate_IO_ITEM(xos, WN_kid1(wn), ctxt);
  xos << "/";
  
  if (WN_kid_count(wn) > 2)
    xlate_IOList(xos, wn, 2, ctxt);

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
  xlate_IOControlList(xos, wn,
		      0 /* from kid*/, WN_kid_count(wn)-1 /* to kid*/,
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
  if (WN_kid_count(wn) == 1 && IS_IO_ITEM_IOU(WN_kid0(wn)))
    xlate_IO_ITEM(xos, WN_kid0(wn), ctxt);
  else
    xlate_IOControlList(xos, wn,
			0 /* from kid*/, WN_kid_count(wn)-1 /* to kid*/, ctxt);
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
  if (WN_kid_count(wn) == 1 && IS_IO_ITEM_IOU(WN_kid0(wn)))
    xlate_IO_ITEM(xos, WN_kid0(wn), ctxt);
  else
    xlate_IOControlList(xos, wn,
			0 /* from kid*/, WN_kid_count(wn)-1 /* to kid*/, ctxt);
  
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
  xlate_IO_ITEM(xos, WN_kid0(wn), ctxt);
  if (WN_kid_count(wn) > 1) {
    xlate_IOList(xos, wn, 1, ctxt);
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
  xlate_IO_ITEM(xos, WN_kid1(wn), ctxt);
  
  /* Translate the buffer we decode from */
  xos << ",";
  TranslateWN(xos, WN_kid0(WN_kid0(wn)), ctxt);
  
  /* Translate the EOSTAT and the ERR items */
  iol_kid = 2;
  if (WN_kid_count(wn) > 2 && IS_IO_ITEM_IOC(WN_kid(wn, 2))) {
    iol_kid = 3;
    xos << ",";
    xlate_IO_ITEM(xos, WN_kid(wn, 2), ctxt);
  }
  if (WN_kid_count(wn) > 3 && IS_IO_ITEM_IOC(WN_kid(wn, 3))) {
    iol_kid = 4;
    xos << ",";
    xlate_IO_ITEM(xos, WN_kid(wn, 3), ctxt);
  }
  xos << ")";
  
  /* Get the io_list */
  if (WN_kid_count(wn) > iol_kid)
    xlate_IOList(xos, wn, iol_kid, ctxt);
  
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
  xlate_IO_ITEM(xos, WN_kid1(wn), ctxt);
  
  /* Translate the buffer we encode from */
  xos << ",";
  TranslateWN(xos, WN_kid0(WN_kid0(wn)), ctxt);
  
  /* Translate the EOSTAT and the ERR items */
  iol_kid = 2;
  if (WN_kid_count(wn) > 2 && IS_IO_ITEM_IOC(WN_kid(wn, 2))) {
    iol_kid = 3;
    xos << ",";
    xlate_IO_ITEM(xos, WN_kid(wn, 2), ctxt);
  }
  if (WN_kid_count(wn) > 3 && IS_IO_ITEM_IOC(WN_kid(wn, 3))) {
    iol_kid = 4;
    xos << ",";
    xlate_IO_ITEM(xos, WN_kid(wn, 3), ctxt);
  }
  xos << ")";
  
  /* Get the io_list */
  if (WN_kid_count(wn) > iol_kid)
    xlate_IOList(xos, wn, iol_kid, ctxt);
  
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
  if (IS_IO_ITEM_IOU(WN_kid0(wn)))
    iol_kid = 2; /* kid 1 must be the format */
  else
    iol_kid = 1; /* Missing unit number */
  xlate_IO_ITEM(xos, WN_kid(wn, iol_kid-1), ctxt);
  if (WN_kid_count(wn) > iol_kid) {
    xlate_IOList(xos, wn, iol_kid, ctxt);
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
      IS_IO_ITEM_IOF(WN_kid1(wn))                         &&
      WN_IOITEM(WN_kid1(wn)) != IOF_NAMELIST_DIRECTED &&
      (WN_kid_count(wn) == 2 || IS_IO_ITEM_IOL(WN_kid(wn, 2)))) {
    xlate_IO_ITEM(xos, WN_kid0(wn), ctxt);
    iol_kid = 2;
    if (WN_kid_count(wn) > 2)
      xos << ",";
  } else {
    for (iol_kid = 0; 
	 (iol_kid < WN_kid_count(wn)) && !IS_IO_ITEM_IOL(WN_kid(wn, iol_kid));
	 iol_kid++);
    
    /* Get the IOU, IOF, and IOC items */
    xlate_IOControlList(xos, wn,
			0,           /* from kid*/
			iol_kid-1,   /* to kid*/
			ctxt);
  }
  
  /* Get the io_list */
  if (iol_kid < WN_kid_count(wn)) {
    set_XlationContext_deref_io_item(ctxt); /* Assume pass-by-reference */
    xlate_IOList(xos, wn, iol_kid, ctxt);
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
  
  ASSERT_WARN(WN_IOSTMT(wn) == IOS_REWRITE, 
	      (DIAG_W2F_UNEXPECTED_IOS, 
	       IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_rewrite"));
  
  xos << "REWRITE";
  set_XlationContext_issue_ioc_asterisk(ctxt);
  
  for (iol_kid = 0; 
       (iol_kid < WN_kid_count(wn)) && !IS_IO_ITEM_IOL(WN_kid(wn, iol_kid));
       iol_kid++);
  
  /* Get the IOU, IOF, and IOC items */
  xlate_IOControlList(xos, wn,
		      0,           /* from kid*/
		      iol_kid-1,     /* to kid*/
		      ctxt);
  
  /* Get the io_list */
  if (iol_kid < WN_kid_count(wn))
    xlate_IOList(xos, wn, iol_kid, ctxt);
  
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
  xlate_IO_ITEM(xos, WN_kid0(wn), ctxt);
  if (WN_kid_count(wn) > 1) {
    xlate_IOList(xos, wn, 1, ctxt);
  }
} /* WN2F_ios_type */


static void 
WN2F_ios_write(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  /* The kids should be an IOU, followed by an IOF, followed by a
   * sequence of IOCs and a sequence of IOLs.  Use keywords only
   * when the IOC list is non-empty.
   */
#if 0 // FIXME: comment out for now
  xos << BegElem("xaif:SubroutineCall") 
      << Attr("statement_id", ctxt.GetNewVId())
      << Attr("symbol_id", "WRITE***");
#endif
  xos << BegElem("xaif:Nop") << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << " [WRITE***]" << EndAttr;
  
#if 0 // FIXME: comment out for now
  set_XlationContext_issue_ioc_asterisk(ctxt);
  
  INT  iol_kid;
  for (iol_kid = 0; 
       (iol_kid < WN_kid_count(wn)) && !IS_IO_ITEM_IOL(WN_kid(wn, iol_kid));
       iol_kid++);
  
  /* Get the IOU, IOF, and IOC items */
  xlate_IOControlList(xos, wn,
		      0 /* from kid */,  iol_kid-1 /* to kid */, ctxt);
  
  /* Get the io_list */
  if (iol_kid < WN_kid_count(wn))
    xlate_IOList(xos, wn, iol_kid, ctxt);
  
  reset_XlationContext_issue_ioc_asterisk(ctxt);
#endif
  xos << EndElem;
  
} /* WN2F_ios_write */


//***************************************************************************
// Cray IO
//***************************************************************************

static void 
WN2F_ios_cr(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // Craylibs IO - write/read The kids should be an IOS, with kids of IO_ITEMS
  ASSERT_WARN(WN_IOSTMT(wn) == IOS_CR_FWF || WN_IOSTMT(wn) == IOS_CR_FWU 
	      || WN_IOSTMT(wn) == IOS_CR_FRF || WN_IOSTMT(wn) == IOS_CR_FRU,
	      (DIAG_W2F_UNEXPECTED_IOS, 
	       IOSTATEMENT_name(WN_IOSTMT(wn)), "WN2F_ios_cr"));
  
  set_XlationContext_issue_ioc_asterisk(ctxt);
  
  /* decide if read/write formatted/unformatted */
  if (WN_IOSTMT(wn) == IOS_CR_FWF || WN_IOSTMT(wn) == IOS_CR_FRF)
    set_XlationContext_fmt_io(ctxt) ;

  const char* io_op = "WRITE***";
  if (WN_IOSTMT(wn) == IOS_CR_FRF || WN_IOSTMT(wn) == IOS_CR_FRU) {
    io_op = "READ***" ;
  }

#if 0 // FIXME: comment out for now  
  xos << BegElem("xaif:SubroutineCall") 
      << Attr("statement_id", ctxt.GetNewVId())
      << Attr("symbol_id", io_op);
#endif  
  xos << BegElem("xaif:Nop") << Attr("statement_id", ctxt.GetNewVId())
      << BegAttr("annotation") << WhirlIdAnnotVal(ctxt.FindWNId(wn))
      << " [" << io_op << "]" << EndAttr;

#if 0 // FIXME: comment out for now
  /* count items in control list */
  INT iol_kid;
  for (iol_kid = 0; 
       (iol_kid < WN_kid_count(wn)) && !IS_IO_ITEM_IOL(WN_kid(wn, iol_kid));
       iol_kid++);
  
  /* Get the IOU, IOF, and IOC items */
  xlate_IOControlList(xos, wn,
		      0 /* from kid */, iol_kid-1 /* to kid */, ctxt);
  
  /* Get the io_list */
  if (iol_kid < WN_kid_count(wn))
    xlate_IOList(xos, wn, iol_kid, ctxt);
  
  reset_XlationContext_issue_ioc_asterisk(ctxt);
#endif
  
  xos << EndElem;
} /* WN2F_ios_cr */

