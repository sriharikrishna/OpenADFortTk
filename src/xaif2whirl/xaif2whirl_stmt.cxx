// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_stmt.cxx,v 1.6 2003/11/26 14:49:04 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_stmt.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <stdlib.h> // ANSI: cstdlib // for strtol
#include <string.h> // ANSI: cstring // for strcmp, etc.

#include <iostream>

//************************* Xerces Include Files ****************************

#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMElement.hpp>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "xaif2whirl.h"
#include "xaif2whirl_stmt.h"
#include "xaif2whirl_expr.h"

#include "XAIF_DOMFilters.h"
#include "XercesStrX.h"

#include <lib/support/Pro64IRInterface.h>
#include <lib/support/SymTab.h> // for XAIFSymToWhirlSymMap
#include <lib/support/WhirlIDMaps.h>
#include <lib/support/wn_attr.h> // for WN_Tree_Type
#include <lib/support/XAIFStrings.h>
#include <lib/support/diagnostics.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

using namespace xaif2whirl;

static WN* 
xlate_Assignment(const DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_AssignmentLHS(const DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_AssignmentRHS(const DOMElement* elem, XlationContext& ctxt);


static WN* 
xlate_SubroutineCall(const DOMElement* elem, XlationContext& ctxt);


static WN* 
xlate_DerivativePropagator(const DOMElement* elem, XlationContext& ctxt);


static WN* 
xlate_SetDeriv(const DOMElement* elem, XlationContext& ctxt);

static WN* 
xlate_ZeroDeriv(const DOMElement* elem, XlationContext& ctxt);

static WN* 
xlate_Saxpy(const DOMElement* elem, XlationContext& ctxt, bool saxpy);

//****************************************************************************

static void
PatchWN_IO(WN* wn, XlationContext& ctxt);

static void
PatchWN_IO_cray(WN* wn, XlationContext& ctxt);

static void
PatchWN_IO_ITEM_list(WN* wn, XlationContext& ctxt);


static WN*
CreateAssignment(WN* lhs, WN* rhs);

static WN*
CreateZeroConst(TYPE_ID ty);

//****************************************************************************

WN* 
xaif2whirl::TranslateStmt(const DOMElement* stmt, XlationContext& ctxt)
{
  WN* wn = NULL;
  
  const XMLCh* name = stmt->getNodeName();
  if (XMLString::equals(name, XAIFStrings.elem_Assign_x())) {
    wn = xlate_Assignment(stmt, ctxt);
  } else if (XMLString::equals(name, XAIFStrings.elem_SubCall_x())) {
    wn = xlate_SubroutineCall(stmt, ctxt);
  } else if (XMLString::equals(name, XAIFStrings.elem_Marker_x())) {
    // nothing
  } else if (XMLString::equals(name, XAIFStrings.elem_DerivProp_x())) {
    wn = xlate_DerivativePropagator(stmt, ctxt);
  } else {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  return wn;
}


static WN* 
xlate_Assignment(const DOMElement* elem, XlationContext& ctxt)
{
  DOMElement* lhs_elem = GetChildElement(elem, XAIFStrings.elem_AssignLHS_x());
  DOMElement* rhs_elem = GetChildElement(elem, XAIFStrings.elem_AssignRHS_x());

  ctxt.CreateContext(XlationContext::NOFLAG);
  WN* lhs = xlate_AssignmentLHS(lhs_elem, ctxt);
  WN* rhs = xlate_AssignmentRHS(rhs_elem, ctxt);
  ctxt.DeleteContext();
  
  WN* wn = CreateAssignment(lhs, rhs);
  return wn;
}

static WN*
xlate_AssignmentLHS(const DOMElement* elem, XlationContext& ctxt)
{
  // VariableReferenceType
  bool deriv = GetDerivAttr(elem);
  uint32_t flg = (deriv) ? XlationContext::ACTIVE_D : XlationContext::ACTIVE_V;
  
  DOMElement* varref = GetFirstChildElement(elem);
  
  ctxt.CreateContext(flg | XlationContext::LVALUE);
  WN* wn = TranslateVarRef(varref, ctxt);
  ctxt.DeleteContext();
  return wn;
}

static WN*
xlate_AssignmentRHS(const DOMElement* elem, XlationContext& ctxt)
{
  // ExpressionType
  DOMElement* child = GetFirstChildElement(elem);
  ctxt.CreateContext(XlationContext::NOFLAG);
  WN* wn = TranslateExpression(child, ctxt);
  ctxt.DeleteContext();
  return wn;
}


static WN* 
xlate_SubroutineCall(const DOMElement* elem, XlationContext& ctxt)
{
  // -------------------------------------------------------
  // 1. Gather the arguments, sorted by "position" attribute and
  // translate them into a WHIRL expression tree.
  // -------------------------------------------------------
  unsigned int numArgs = GetChildElementCount(elem);
  std::vector<WN*> args_wn(numArgs, NULL);
  for (DOMElement* arg = GetFirstChildElement(elem); (arg); 
       arg = GetNextSiblingElement(arg) ) {

    // VariableReferenceType
    const XMLCh* nmX = arg->getNodeName();
    ASSERT_FATAL(XMLString::equals(nmX, XAIFStrings.elem_Argument_x()), 
		 (DIAG_A_STRING, "Programming error."));
    
    unsigned int pos = GetPositionAttr(arg); // 1-based
    ASSERT_FATAL(1 <= pos && pos <= numArgs, (DIAG_A_STRING, "Error."));
    
    // Note: We do *not* check the deriv flag; any active variable
    // references should be passed as is.
    uint32_t flg = XlationContext::ACTIVE_D;
    
    DOMElement* argExpr = GetFirstChildElement(arg);
    
    ctxt.CreateContext(flg);
    WN* argExprWN = TranslateVarRef(argExpr, ctxt);
    ctxt.DeleteContext();
    args_wn[pos - 1] = argExprWN;
  }
  
  // -------------------------------------------------------
  // 2. Create function call
  // -------------------------------------------------------
  TYPE_ID rtype = MTYPE_V; // void type for subroutine call
  Symbol* sym = GetSymbol(elem, ctxt);
  
  WN* callWN = WN_Call(rtype, MTYPE_V, numArgs, sym->GetST());
  WN_Set_Call_Default_Flags(callWN); // set conservative assumptions
  
  for (int i = 0; i < numArgs; ++i) {
    if (args_wn[i]) { 
      // conservatively assume pass by reference
      WN_actual(callWN, i) = CreateParm(args_wn[i], WN_PARM_BY_REFERENCE);
    }
  }
  
  return callWN;
}


// Must not return an empty block
static WN* 
xlate_DerivativePropagator(const DOMElement* elem, XlationContext& ctxt)
{
  WN* blckWN = WN_CreateBlock();
  
  // Accumulate derivative propagator statements and add to block
  DOMDocument* doc = elem->getOwnerDocument();
  DOMNodeIterator* it = 
    doc->createNodeIterator((DOMNode*)elem, DOMNodeFilter::SHOW_ALL, 
			    new XAIF_DerivPropStmt(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* stmt = dynamic_cast<DOMElement*>(node);
    
    WN* wn = NULL;
    if (XAIF_DerivPropStmt::IsSetDeriv(stmt)) {
      wn = xlate_SetDeriv(stmt, ctxt);
    } else if (XAIF_DerivPropStmt::IsZeroDeriv(stmt) ) {
      wn = xlate_ZeroDeriv(stmt, ctxt);
    } else if (XAIF_DerivPropStmt::IsSax(stmt)) {
      wn = xlate_Saxpy(stmt, ctxt, false);
    } else if (XAIF_DerivPropStmt::IsSaxpy(stmt) ) {
      wn = xlate_Saxpy(stmt, ctxt, true);
    } else {
      ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
    }
    
    WN_INSERT_BlockLast(blckWN, wn);
  }
  it->release();
  
  // Do not return an empty block
  if (WN_first(blckWN) == NULL)  {
    WN_Delete(blckWN);
    blckWN = NULL;
  }

  return blckWN;
}


// xlate_SetDeriv
static WN* 
xlate_SetDeriv(const DOMElement* elem, XlationContext& ctxt)
{
  DOMElement* tgt = GetChildElement(elem, XAIFStrings.elem_Tgt_x());
  DOMElement* src = GetChildElement(elem, XAIFStrings.elem_Src_x());
  
  // Note: This should always be ACTIVE_D (FIXME)
  bool deriv = GetDerivAttr(tgt);
  uint32_t flg = (deriv) ? XlationContext::ACTIVE_D : XlationContext::ACTIVE_V;
  ctxt.CreateContext(flg);
  WN* tgtWN = TranslateVarRef(GetFirstChildElement(tgt), ctxt);
  ctxt.DeleteContext();

  // Note: This should always be ACTIVE_D (FIXME)
  deriv = GetDerivAttr(src);
  flg = (deriv) ? XlationContext::ACTIVE_D : XlationContext::ACTIVE_V;
  ctxt.CreateContext(flg);
  WN* srcWN = TranslateVarRef(GetFirstChildElement(src), ctxt);
  ctxt.DeleteContext();
  
  WN* callWN = CreateCallToIntrin(MTYPE_V, "setderiv", 2);  
  WN_actual(callWN, 0) = CreateParm(tgtWN, WN_PARM_BY_REFERENCE);
  WN_actual(callWN, 1) = CreateParm(srcWN, WN_PARM_BY_VALUE);

  return callWN;
}

// xlate_ZeroDeriv: 
static WN* 
xlate_ZeroDeriv(const DOMElement* elem, XlationContext& ctxt)
{
  WN* x = xlate_AssignmentLHS(elem, ctxt); // functionally equivalent
  
  WN* callWN = CreateCallToIntrin(MTYPE_V, "zero_deriv", 1);
  WN_actual(callWN, 0) = CreateParm(x, WN_PARM_BY_REFERENCE);

  return callWN;
}

// xlate_Saxpy: handles calls to both
//   saxpy(a,x,y): Y=A1*X1+A2*X2+...+Y
//   sax(a,x,y)  : Y=A1*X1+A2*X2+...
static WN* 
xlate_Saxpy(const DOMElement* elem, XlationContext& ctxt, bool saxpy)
{
  // -------------------------------------------------------
  // 1. Create WHIRL expressions for sax(py) parameters
  // -------------------------------------------------------
  // FIXME: could be a list. We ensure there is no list for now.
  ASSERT_FATAL(GetChildElementCount(elem) == 2, 
	       (DIAG_A_STRING, "Programming error."));
  
  DOMElement* AX = GetChildElement(elem, XAIFStrings.elem_AX_x());
  DOMElement* A = GetChildElement(AX, XAIFStrings.elem_A_x());
  DOMElement* X = GetChildElement(AX, XAIFStrings.elem_X_x());
  DOMElement* Y = GetChildElement(elem, XAIFStrings.elem_Y_x());
  
  // A
  WN* a_wn = TranslateExpression(GetFirstChildElement(A), ctxt);
  
  // X
  bool deriv = GetDerivAttr(X);
  uint32_t flg = (deriv) ? XlationContext::ACTIVE_D : XlationContext::ACTIVE_V;
  ctxt.CreateContext(flg);
  WN* x_wn = TranslateVarRef(GetFirstChildElement(X), ctxt);
  ctxt.DeleteContext();
  
  // Y
  deriv = GetDerivAttr(Y);
  flg = (deriv) ? XlationContext::ACTIVE_D : XlationContext::ACTIVE_V;
  ctxt.CreateContext(flg);
  WN* y_wn = TranslateVarRef(GetFirstChildElement(Y), ctxt);
  ctxt.DeleteContext();
  
  // -------------------------------------------------------
  // 2. Create a WHIRL call with the above expressions as paramaters
  // -------------------------------------------------------
  const char* fnm = (saxpy) ? "saxpy" : "sax";
  MTYPE rtype = MTYPE_V;
  WN* callWN = CreateCallToIntrin(rtype, fnm, 3);
  
  WN_actual(callWN, 0) = CreateParm(a_wn, WN_PARM_BY_VALUE);
  WN_actual(callWN, 1) = CreateParm(x_wn, WN_PARM_BY_VALUE);
  WN_actual(callWN, 2) = CreateParm(y_wn, WN_PARM_BY_REFERENCE);
  
  return callWN;
}

//****************************************************************************

WN*
xaif2whirl::PatchWNStmt(WN* wn, XlationContext& ctxt)
{
  OPERATOR opr = WN_operator(wn);
  if (opr == OPR_IO) {
    PatchWN_IO(wn, ctxt);
  }
}

static void
PatchWN_IO(WN* wn, XlationContext& ctxt)
{  
  // FIXME: only handle cray read/write for now
  PatchWN_IO_cray(wn, ctxt);
}

static void
PatchWN_IO_cray(WN* wn, XlationContext& ctxt)
{
  IOSTATEMENT iostmt = WN_io_statement(wn);
  ASSERT_WARN(iostmt == IOS_CR_FWF || iostmt == IOS_CR_FWU 
	      || iostmt == IOS_CR_FRF || iostmt == IOS_CR_FRU,
	      (DIAG_W2F_UNEXPECTED_IOS, IOSTATEMENT_name(iostmt), 
	       "PatchWN_IO_cray"));
  
  // Iterate over IO_ITEMs and translate IOLs (io lists)
  for (INT kidno = 0; kidno < WN_kid_count(wn); ++kidno) {
    WN* kid = WN_kid(wn, kidno);
    if (IS_IO_ITEM_IOL(kid)) {
      PatchWN_IO_ITEM_list(kid, ctxt);
    }
  }
}

static void
PatchWN_IO_ITEM_list(WN* wn, XlationContext& ctxt)
{
  // cf. xlate_IO_ITEM_list
  
  IOITEM kind = WN_io_item(wn);
  switch (kind) {
  case IOL_VAR:        // skip
  case IOL_ARRAY:      // skip
  case IOL_CHAR_ARRAY: // skip
  case IOL_RECORD:     // skip
  case IOL_CHAR:       // skip
    break;

  case IOL_EXPR: // patch
    PatchWNExpr(wn, 0 /* kid */, ctxt);
    break;
    
  case IOL_IMPLIED_DO:
  case IOL_IMPLIED_DO_1TRIP:
    assert(false); // FIXME
    break;
    
  case IOL_LOGICAL: // skip
  case IOL_DOPE:    // skip
    break;
  
  default:
    ASSERT_DBG_WARN(FALSE, (DIAG_W2F_UNEXPECTED_IOL,
			    IOITEM_name(kind), "xlate_IO_ITEM_list"));
    break;
  }
}

//****************************************************************************

static WN*
CreateAssignment(WN* lhs, WN* rhs)
{
  // We always use ISTORE (instead of e.g. STID) for generality.  This
  // will not be an issue because the intension is for this WHIRL to
  // be translated to source code.
  
  // FIXME: first argument is bogus // WN_Tree_Type(rhs)
  TY_IDX ty = Make_Pointer_Type(MTYPE_To_TY(MTYPE_F8));
  WN* wn = WN_Istore(MTYPE_F8, 0, ty, lhs, rhs, 0);
  return wn;
}


static WN*
CreateZeroConst(TYPE_ID ty)
{
  return Make_Const(Targ_Conv(ty, Host_To_Targ(MTYPE_I4, 0)));
}
