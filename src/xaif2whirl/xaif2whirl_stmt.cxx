// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_stmt.cxx,v 1.3 2003/10/01 16:32:52 eraxxon Exp $

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
xlate_Saxpy(const DOMElement* elem, XlationContext& ctxt, bool saxpy);

//****************************************************************************

static void
PatchWN_IO(WN* wn, XlationContext& ctxt);

static void
PatchWN_IO_cray(WN* wn, XlationContext& ctxt);

static void
PatchWN_IO_ITEM_list(WN* wn, XlationContext& ctxt);

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
  bool active = GetActiveAttr(elem);
  uint32_t flg = (active) ? XlationContext::ACTIVE : XlationContext::NOFLAG;

  DOMElement* lhs_elem = GetChildElement(elem, XAIFStrings.elem_AssignLHS_x());
  DOMElement* rhs_elem = GetChildElement(elem, XAIFStrings.elem_AssignRHS_x());

  ctxt.CreateContext(flg);
  WN* lhs = xlate_AssignmentLHS(lhs_elem, ctxt);
  WN* rhs = xlate_AssignmentRHS(rhs_elem, ctxt);
  ctxt.DeleteContext();
  
  // We always use ISTORE (instead of e.g. STID) for generality.  This
  // will not be an issue because the intension is for this WHIRL to
  // be translated to source code.
  // FIXME: first argument is bogus // WN_Tree_Type(rhs)
  TY_IDX ty = Make_Pointer_Type(MTYPE_To_TY(MTYPE_F8));
  WN* wn = WN_Istore(MTYPE_F8, 0, ty, lhs, rhs, 0);

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
  bool active = GetActiveAttr(elem);
  uint32_t flg = (active) ? XlationContext::ACTIVE : XlationContext::NOFLAG;
  ctxt.CreateContext(flg);
  
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
    ASSERT_FATAL(1 <= pos /* && pos <= numArgs */, 
		 (DIAG_A_STRING, "Error."));
    // FIXME: removed second test to accomodate missing constant arguments
    
    bool drv = GetDerivAttr(arg);
    uint32_t flg = (drv) ? XlationContext::ACTIVE_D : XlationContext::ACTIVE_V;

    DOMElement* argExpr = GetFirstChildElement(arg);
    
    ctxt.CreateContext(flg);
    WN* argExprWN = TranslateVarRef(argExpr, ctxt);
    ctxt.DeleteContext();
    args_wn[pos - 1] = argExprWN;
  }
  
  // -------------------------------------------------------
  // 2. Create function call
  // -------------------------------------------------------
  TYPE_ID rtype = MTYPE_V; // MTYPE_F8 for FuncCall
  ST* st = GetST(elem, ctxt);
  WN* callWN = WN_Call(rtype, MTYPE_V, numArgs, st);
  
  WN_Set_Call_Default_Flags(callWN); // FIXME
  WN_Set_Call_Parm_Mod(callWN);
  
  for (int i = 0; i < numArgs; ++i) {
    if (args_wn[i]) { // FIXME: do we need to handle paramaters differently?
      WN_actual(callWN, i) = CreateParm(args_wn[i], WN_PARM_BY_REFERENCE);
    }
  }
  
  ctxt.DeleteContext();
  return callWN;
}


// Must not return an empty block
static WN* 
xlate_DerivativePropagator(const DOMElement* elem, XlationContext& ctxt)
{
  ctxt.CreateContext(XlationContext::ACTIVE);
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
      assert(false && "Please implement me"); // FIXME
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

  ctxt.DeleteContext();
  return blckWN;
}

// xlate_Saxpy: handles calls to both
//   saxpy_a_a(a,x,y): Y=A1*X1+A2*X2+...+Y
//   sax_a_a(a,x,y)  : Y=A1*X1+A2*X2+...
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
  const char* fnm = (saxpy) ? "saxpy_a_a" : "sax_a_a";
  MTYPE rtype = MTYPE_V;
  WN* callWN = CreateIntrinsicCall(rtype, fnm, 3);
  
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
