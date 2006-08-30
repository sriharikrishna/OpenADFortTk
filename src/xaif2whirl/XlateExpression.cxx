// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XlateExpression.cxx,v 1.2 2006/05/12 16:12:23 utke Exp $

#include <stdlib.h> // ANSI: cstdlib // for strtol
#include <string.h> // ANSI: cstring // for strcmp, etc.
#include <iostream>
#include <vector>
#include <algorithm>

#include "xercesc/dom/DOMDocument.hpp"
#include "xercesc/dom/DOMNode.hpp"
#include "xercesc/dom/DOMElement.hpp"

#include "Open64IRInterface/Open64BasicTypes.h"
#include "Open64IRInterface/Open64IRInterface.hpp"
#include "Open64IRInterface/SymTab.h"
#include "Open64IRInterface/wn_attr.h"
#include "Open64IRInterface/stab_attr.h"

#include "ScalarizedRefTab.h"
#include "WhirlIDMaps.h"
#include "XAIFStrings.h"
#include "Diagnostics.h"

#include "xaif2whirl.h"
#include "XlateExpression.h"
#include "XAIF_DOMFilters.h"
#include "XercesStrX.h"

namespace xaif2whirl { 
  extern TY_IDX ActiveTypeTyIdx;            // FIXME
  extern TY_IDX ActiveTypeInitializedTyIdx; // FIXME

  WN* XlateExpression::translateExpression(const DOMElement* elem, 
					   PUXlationContext& ctxt) {
    FORTTK_ASSERT(elem, fortTkSupport::Diagnostics::UnexpectedInput);
    // Slurp expression into a graph (DAG) and translate it
    OA::OA_ptr<OA::DGraph::DGraphImplement> g = createExpressionGraph(elem);
    OA::OA_ptr<OA::DGraph::NodeInterface> root = g->getRoot();
    OA::OA_ptr<MyDGNode> n = root.convert<MyDGNode>();
    WN* wn = xlate_Expression(g, n, ctxt);
    return wn;
  }

  WN* XlateExpression::translateExpressionSimple(const DOMElement* elem,
						 PUXlationContext& ctxt) {
    ctxt.createXlationContext(XlationContext::EXPRSIMPLE);
    WN* wn = translateExpression(elem, ctxt);
    ctxt.deleteXlationContext();
    return wn;
  }

  WN* XlateExpression::translateVarRef(const DOMElement* elem, 
				       PUXlationContext& ctxt) {
    FORTTK_ASSERT(elem, fortTkSupport::Diagnostics::UnexpectedInput);
    // Slurp expression into a graph (DAG) and translate it
    ctxt.createXlationContext(XlationContext::VARREF);
    OA::OA_ptr<OA::DGraph::DGraphImplement> g = 
      createExpressionGraph(elem, true /* varRef */);
    OA::OA_ptr<OA::DGraph::NodeInterface> root = g->getRoot();
    OA::OA_ptr<MyDGNode> n = root.convert<MyDGNode>();
    WN* wn = xlate_VarRef(g, n, ctxt);
    ctxt.deleteXlationContext();
    // If we are not already within another VarRef and we translated an
    // active symbol, select the appropriate portion of the active type
    if (!ctxt.currentXlationContext().isFlag(XlationContext::VARREF)) {
      if (ctxt.currentXlationContext().isFlag(XlationContext::ACTIVETYPE)) { 
	if (ctxt.currentXlationContext().isFlag(XlationContext::VALUESELECTOR)) {
	  wn = createValueSelector(wn); // active
	} else if (ctxt.currentXlationContext().isFlag(XlationContext::DERIVSELECTOR)) {
	  wn = createDerivSelector(wn); // deriv
	}
	ctxt.currentXlationContext().unsetFlag(XlationContext::ACTIVETYPE); // halt up-inheritance
      }
    }  
    return wn;
  }

  std::pair<ST*, WN_OFFSET> XlateExpression::translateVarRefSimple(const DOMElement* elem, 
								   PUXlationContext& ctxt) {
    FORTTK_ASSERT(elem, fortTkSupport::Diagnostics::UnexpectedInput);
    // This must be a plain XAIF symbol reference (a one-vertex graph)
    const XMLCh* nameX = elem->getNodeName();
    if ( !(XMLString::equals(nameX, XAIFStrings.elem_SymRef_x()) &&
	   GetNextSiblingElement(elem) == NULL) ) {
      FORTTK_DIE("Expected a simple var ref but found:\n" << *elem);
    }
    ctxt.createXlationContext(XlationContext::NOFLAG);
    pair<ST*, WN_OFFSET> stpair = xlate_SymbolReferenceSimple(elem, ctxt);
    ctxt.deleteXlationContext();
    return stpair;
  }

  WN* XlateExpression::patchWNExpr(WN* parent, 
				   INT kidno, 
				   PUXlationContext& ctxt) {
    // Simple Base cases
    if (!parent) { return NULL; }
    WN* wn = WN_kid(parent, kidno);
    if (!wn) { return NULL; }
    OPERATOR opr = WN_operator(wn);
    if (!OPERATOR_is_expression(opr)) { return parent; }
    // Base case: a variable reference
    if (fortTkSupport::ScalarizedRef::isRefTranslatableToXAIF(wn)) {
      TY_IDX ty = WN_GetBaseObjType(wn);
      if (TY_kind(ty) == KIND_ARRAY) {
	ty = TY_etype(ty);
      }
      if (ty == ActiveTypeTyIdx || ty == ActiveTypeInitializedTyIdx) {
	WN* newwn = createValueSelector(wn);
	WN_kid(parent, kidno) = newwn;
      }
    }
    else {
      // Recursive case
      for (INT i = 0; i < WN_kid_count(wn); ++i) {
	patchWNExpr(wn, i /* kid */, ctxt);
      }
    }
    return parent;
  }

  WN* XlateExpression::translateConstant(const DOMElement* elem, 
					 PUXlationContext& ctxt) {
    FORTTK_ASSERT(elem, fortTkSupport::Diagnostics::UnexpectedInput);
    const XMLCh* typeX = elem->getAttribute(XAIFStrings.attr_type_x());
    const XMLCh* valX = elem->getAttribute(XAIFStrings.attr_value_x());
    XercesStrX type = XercesStrX(typeX);
    XercesStrX value = XercesStrX(valX);
    WN* wn = NULL;
    if ((strcmp(type.c_str(), "real") == 0) ||
	(strcmp(type.c_str(), "double") == 0)) {
      // Floating point constant
      double val = strtod(value.c_str(), (char **)NULL);
      TCON tcon = Host_To_Targ_Float(MTYPE_F8, val);
      wn = Make_Const(tcon);
    } 
    else if (strcmp(type.c_str(), "integer") == 0) {
      // Integer constant: Note that we have turned off WHIRL's
      // expression simplifier, which can cause problems with our code.
      // Also note that certain special expressions need an I4INTCONST.
      // E.g.: array indices, loop updates.
      INT64 val = strtol(value.c_str(), (char **)NULL, 10);
      if (ctxt.currentXlationContext().isFlag(XlationContext::ARRAYIDX) || 
	  ctxt.currentXlationContext().isFlag(XlationContext::EXPRSIMPLE)) {
	wn = WN_CreateIntconst(OPC_I4INTCONST, (INT32)val);
      } else {
	// the WHIRL simplifier messes up int CONST nodes
	//TCON tcon = Host_To_Targ(DefaultMTypeInt, val);
	//wn = Make_Const(tcon); 
	OPCODE opc = OPCODE_make_op(OPR_INTCONST, DefaultMTypeInt, MTYPE_V);
	wn = WN_CreateIntconst(opc, val);
      }
    } 
    else if (strcmp(type.c_str(), "bool") == 0) {
      // Boolean constant: boolean values can be true/false or 1/0.
      unsigned int val = 1;
      const char* v = value.c_str();    
      if ((strcmp(v, "false") == 0) || (strcmp(v, "0") == 0)) {
	val = 0;
      }
      wn = CreateBoolConst(val);
    } 
    else if (strcmp(type.c_str(), "char") == 0) {
      // Character constant. Cf. cwh_stmt.cxx:349
      // wn = WN_CreateIntconst(OPC_I4INTCONST, (INT64)val);
      FORTTK_DIE(fortTkSupport::Diagnostics::Unimplemented << "creation of character constant");
    } 
    else if (strcmp(type.c_str(), "string") == 0) {
      // String constant. A string constant reference to "S" looks like:
      //   U4U1ILOAD 0 T<43,.character.,1> T<175,anon_ptr.,8>
      //     U8LDA 0 <1,596,(1_bytes)_"S"> T<127,anon_ptr.,8>
      // cf. fei_pattern_con(..) in cwh_stab.cxx
      TY_IDX ty = MTYPE_To_TY(MTYPE_STRING);
      TY_IDX ty_ptr = Stab_Pointer_To(ty);
      UINT32 len = strlen(value.c_str());
      TCON tcon = Host_To_Targ_String(MTYPE_STRING, (char*)value.c_str(), len);
      ST* st = Gen_String_Sym(&tcon, ty, FALSE);
      TYPE_ID rty = TY_mtype(ty_ptr); // Pointer_Mtype
      WN* lda = WN_CreateLda(OPR_LDA, rty, MTYPE_V, 0, ty_ptr, st, 0);
      wn = WN_CreateIload(OPR_ILOAD, MTYPE_U4, MTYPE_U1, 0, ty, ty_ptr, lda, 0);
    }
    return wn;
  }

  WN* XlateExpression::xlate_Intrinsic(OA::OA_ptr<OA::DGraph::DGraphImplement> g, 
				       OA::OA_ptr<MyDGNode> n, 
				       PUXlationContext& ctxt) {
    FORTTK_ASSERT(!g.ptrEqual(NULL) && !n.ptrEqual(NULL), fortTkSupport::Diagnostics::UnexpectedInput);
    DOMElement* elem = n->GetElem();
    const XMLCh* nmX = elem->getAttribute(XAIFStrings.attr_name_x());
    XercesStrX nm = XercesStrX(nmX);
    std::string key = GetIntrinsicKey(elem);
    WN* wn = xlate_ExprOpUsingIntrinsicTable(fortTkSupport::IntrinsicXlationTable::XAIFIntrin, 
					     nm.c_str(), 
					     key.c_str(), 
					     g, 
					     n, 
					     ctxt);
    return wn;
  }

  WN* XlateExpression::xlate_Expression(OA::OA_ptr<OA::DGraph::DGraphImplement> g, 
					OA::OA_ptr<MyDGNode> n, 
					PUXlationContext& ctxt) {
    // Recursively translate the DAG (tree) rooted at this node
    DOMElement* elem = n->GetElem();
    const XMLCh* nameX = elem->getNodeName();
    XercesStrX name = XercesStrX(nameX);
    WN* wn = NULL;
    if (XMLString::equals(nameX, XAIFStrings.elem_VarRef_x())) {
      // VariableReference
      wn = xlate_VarRef(elem, ctxt);
    } 
    else if (XMLString::equals(nameX, XAIFStrings.elem_Constant_x())) {
      // Constant
      wn = translateConstant(elem, ctxt);
    } 
    else if (XMLString::equals(nameX, XAIFStrings.elem_Intrinsic_x())) {
      // Intrinsic
      wn = xlate_Intrinsic(g, n, ctxt);
    } 
    else if (XMLString::equals(nameX, XAIFStrings.elem_FuncCall_x())) {
      // FunctionCall
      wn = xlate_FunctionCall(g, n, ctxt);
    } 
    else if (XMLString::equals(nameX, XAIFStrings.elem_BoolOp_x())) {
      // BooleanOperation
      wn = xlate_BooleanOperation(g, n, ctxt);
    } 
    else {
      FORTTK_DIE("Unknown XAIF expression:\n" << *elem);
    }
    return wn;
  }

  WN* XlateExpression::xlate_VarRef(const DOMElement* elem, PUXlationContext& ctxt) {
    FORTTK_ASSERT(elem, fortTkSupport::Diagnostics::UnexpectedInput);
    // VariableReferenceType
    bool deriv = GetDerivAttr(elem);
    // skip the xaif:VariableReference node
    DOMElement* varref = GetFirstChildElement(elem); 
    ctxt.createXlationContext((deriv) ? XlationContext::DERIVSELECTOR : XlationContext::VALUESELECTOR);
    WN* wn = translateVarRef(varref, ctxt);
    ctxt.deleteXlationContext();
    return wn;
  }

  WN* XlateExpression::xlate_VarRef(OA::OA_ptr<OA::DGraph::DGraphImplement> g, 
				    OA::OA_ptr<MyDGNode> n, 
				    PUXlationContext& ctxt) {
    FORTTK_ASSERT(!g.ptrEqual(NULL) && !n.ptrEqual(NULL), fortTkSupport::Diagnostics::UnexpectedInput);
    // Recursively translate the DAG (tree) rooted at this node
    DOMElement* elem = n->GetElem();
    FORTTK_ASSERT(elem, "Internal error: var-ref graph contains null DOM elem.");
    WN* wn = NULL;  
    const XMLCh* nameX = elem->getNodeName();
    if (XMLString::equals(nameX, XAIFStrings.elem_SymRef_x())) {
      // SymbolReference
      wn = xlate_SymbolReference(elem, ctxt);
    } 
    else if (XMLString::equals(nameX, XAIFStrings.elem_ArrayElemRef_x())) {
      // ArrayElementReference
      wn = xlate_ArrayElementReference(g, n, ctxt);
    } 
    else {
      FORTTK_DIE("Unknown XAIF variable reference:\n" << *elem);
    }
    return wn;
  }

  WN* XlateExpression::xlate_FunctionCall(OA::OA_ptr<OA::DGraph::DGraphImplement> g, 
					  OA::OA_ptr<MyDGNode> n,
					  PUXlationContext& ctxt) {
    FORTTK_ASSERT(!g.ptrEqual(NULL) && !n.ptrEqual(NULL), fortTkSupport::Diagnostics::UnexpectedInput);
    DOMElement* elem = n->GetElem();
    // FIXME: children are expr; find num of args (use Intrinsic function above)
    FORTTK_DIE(fortTkSupport::Diagnostics::Unimplemented << "xaif:FunctionCall");
    return NULL;
  }

  WN* XlateExpression::xlate_BooleanOperation(OA::OA_ptr<OA::DGraph::DGraphImplement> g, 
					      OA::OA_ptr<MyDGNode> n,
					      PUXlationContext& ctxt) {
    FORTTK_ASSERT(!g.ptrEqual(NULL) && !n.ptrEqual(NULL), fortTkSupport::Diagnostics::UnexpectedInput);
    DOMElement* elem = n->GetElem();
    const XMLCh* nmX = elem->getAttribute(XAIFStrings.attr_name_x());
    XercesStrX nm = XercesStrX(nmX);
    WN* wn = xlate_ExprOpUsingIntrinsicTable(fortTkSupport::IntrinsicXlationTable::XAIFBoolOp, 
					     nm.c_str(), 
					     NULL, 
					     g, 
					     n, 
					     ctxt);
    return wn;
  }

  struct XAIFEdgePositionCompare {
    // return true if e1 < e2; false otherwise
    bool operator()(const OA::OA_ptr<MyDGEdge> e1, 
		    const OA::OA_ptr<MyDGEdge> e2) const {
      unsigned int pos1 = GetPositionAttr(e1->GetElem());
      unsigned int pos2 = GetPositionAttr(e2->GetElem());
      return (pos1 < pos2);
    }
  };

  WN* XlateExpression::xlate_ExprOpUsingIntrinsicTable(const fortTkSupport::IntrinsicXlationTable::XAIFOpr xopr, 
						       const char* xoprNm, 
						       const char* xIntrinKey,
						       OA::OA_ptr<OA::DGraph::DGraphImplement> g, 
						       OA::OA_ptr<MyDGNode> n, 
						       PUXlationContext& ctxt) {
    using namespace OA::DGraph;
    fortTkSupport::IntrinsicXlationTable::WHIRLInfo* info = 
      IntrinsicTable.findWHIRLInfo(xopr, xoprNm, xIntrinKey);
    // 1. Gather the operands, sorted by the "position" attribute
    FORTTK_ASSERT(n->num_incoming() == info->numop, 
		  "Internal error: inconsistent number of intrinsic arguments '"
		  << xoprNm  << "-" << xIntrinKey << "'");
    OA::OA_ptr<MyDGEdge> tmp; tmp = NULL;
    vector<OA::OA_ptr<MyDGEdge> > opnd_edge(info->numop, tmp);
    OA::OA_ptr<EdgesIteratorInterface> itPtr 
      = n->getIncomingEdgesIterator();
    for (int i = 0; itPtr->isValid(); ++(*itPtr), ++i) {
      OA::OA_ptr<OA::DGraph::EdgeInterface> etmp = itPtr->current();
      opnd_edge[i] = etmp.convert<MyDGEdge>();
    }
    std::sort(opnd_edge.begin(), opnd_edge.end(),XAIFEdgePositionCompare()); // ascending
    // 2. Translate each operand into a WHIRL expression tree
    vector<WN*> opnd_wn(info->numop, NULL); 
    for (unsigned i = 0; i < info->numop; ++i) {
      OA::OA_ptr<NodeInterface> ntmp = opnd_edge[i]->source();
      OA::OA_ptr<MyDGNode> opnd = ntmp.convert<MyDGNode>();
      opnd_wn[i] = xlate_Expression(g, opnd, ctxt);
    }       
    // Here promote all arguments up to 8 bytes; we assume canonicalized
    // argument forms
    // FIXME: for now we promote reals to 8; demote ints to 4; we could
    // selectively do this...
    for (unsigned i = 0; i < opnd_wn.size(); ++i) {
      // FIXME: could use rtype for operator
      TY_IDX ty = WN_Tree_Type(opnd_wn[i]);
      TYPE_ID rty = TY_mtype(ty);      
      // Pointers and character strings often look like integers to the
      // test below
      if (TY_Is_Pointer(ty) || TY_Is_Character_String(ty)) { continue; }
      TYPE_ID newrty = MTYPE_UNKNOWN;
      if (MTYPE_is_integral(rty)) {
	newrty = getMType(MTYPE_CLASS_INTEGER, 4);
      }
      else if (MTYPE_is_float(rty)) {
	newrty = getMType(MTYPE_CLASS_FLOAT, 8);
      }
      // WN_set_rtype(opnd_wn[i], newrty);
      if (newrty != MTYPE_UNKNOWN && newrty != rty) {
	opnd_wn[i] = WN_Cvt(rty, newrty, opnd_wn[i]);
      }
    }
    // 3. Translate into either WHIRL OPR_CALL or a WHIRL expression operator
    WN* wn = NULL;
    switch (info->oprcl) {
    case fortTkSupport::IntrinsicXlationTable::WNCall: {
      TYPE_ID rtype = MTYPE_F8; // FIXME
      wn = CreateCallToIntrin(rtype, info->name, opnd_wn);
      break;
    }
    case fortTkSupport::IntrinsicXlationTable::WNIntrinCall:
    case fortTkSupport::IntrinsicXlationTable::WNIntrinOp: {          
      TYPE_ID rtype = MTYPE_F8; // FIXME
      TYPE_ID dtype = MTYPE_V;  // FIXME
      INTRINSIC intrn = getWNIntrinsic(info->name, opnd_wn, NULL);
      wn = CreateIntrinsicCall(info->opr, intrn, rtype, dtype, opnd_wn);
      break;
    }
    case fortTkSupport::IntrinsicXlationTable::WNExpr: {
      // Find the opcode for the expression
      OPCODE opc = getWNExprOpcode(info->opr, opnd_wn);
      // Create a WHIRL expression tree for the operator and operands
      switch (info->numop) {
      case 1: // unary
	wn = WN_CreateExp1(opc, opnd_wn[0]); break;
      case 2: // binary
	wn = WN_CreateExp2(opc, opnd_wn[0], opnd_wn[1]); break;
      case 3: // ternary
	wn = WN_CreateExp3(opc, opnd_wn[0], opnd_wn[1], opnd_wn[2]); break;
      default:
	FORTTK_DIE("Incorrect number of operands for WHIRL expr: " 
		   << info->numop);
      } 
      break;
    }
    default:
      FORTTK_DIE("Invalid WNOprClass class: " << info->oprcl);
    }
    return wn;
  }

  WN* XlateExpression::xlate_SymbolReference(const DOMElement* elem, 
					     PUXlationContext& ctxt) {
    FORTTK_ASSERT(elem, fortTkSupport::Diagnostics::UnexpectedInput);
    // -------------------------------------------------------
    // 0. Setup; Possibly redirect processing
    // -------------------------------------------------------
    WN* wn = NULL;
    fortTkSupport::Symbol* sym = GetSymbol(elem, ctxt);
    if (sym->IsActive()) {
      ctxt.currentXlationContext().setFlag(XlationContext::ACTIVETYPE); // N.B. inherited up the ctxt stack
    }
    // redirect handling if access path was collapsed (includes scalarization)
    if (sym->IsPathCollapsed()) {
      WN* pathVorlage = ctxt.findWN(sym->GetPathVorlage(), true /* mustFind */);
      return xlate_SymbolReferenceCollapsedPath(elem, pathVorlage, ctxt);
    }
    ST* st = sym->GetST();
    TY_IDX ty = ST_type(st);
    TYPE_ID rty, dty;
    WN_OFFSET oset = 0;
    // -------------------------------------------------------
    // 1. Determine which type of load to use
    // -------------------------------------------------------
    bool create_lda = false;
    // Note: Order matters in these tests
    if (ST_class(st) != CLASS_PREG) { // never create a pointer to a preg
      if (ctxt.currentXlationContext().isFlag(XlationContext::ARRAY)) {
	// Do not load the address of symbol that is already a pointer
	if (TY_kind(ty) != KIND_POINTER) {
	  create_lda = true;
	}
      } 
      else if (ctxt.currentXlationContext().isFlag(XlationContext::LVALUE)) {
	create_lda = true;
      } 
    }
    // -------------------------------------------------------
    // 2. Create the reference
    // -------------------------------------------------------
    if (create_lda) {
      // OPR_LDA
      TY_IDX ty_ptr = Stab_Pointer_To(ty);
      rty = TY_mtype(ty_ptr); // Pointer_Mtype
      wn = WN_CreateLda(OPR_LDA, rty, MTYPE_V, oset, ty_ptr, st, 0);
    } 
    else {
      // OPR_LDID
      rty = dty = TY_mtype(ty);
      if (TY_kind(ty) == KIND_ARRAY) { // FIXME more special cases?
	rty = dty = TY_mtype(TY_etype(ty));
      }
      // FIXME: take care of small integer types
      if (MTYPE_byte_size(dty) < 4) {
	if (MTYPE_is_unsigned(dty)) { rty = DefaultMTypeUInt; }
	else if (MTYPE_is_signed(dty)) { rty = DefaultMTypeInt; }
      }
      if (ST_class(st) == CLASS_PREG) {
	oset = GetPregId(elem);
      }
      wn = WN_CreateLdid(OPR_LDID, rty, dty, oset, st, ty, 0);
    } 
    return wn;
  }

  std::pair<ST*, WN_OFFSET> XlateExpression::xlate_SymbolReferenceSimple(const DOMElement* elem,
									 PUXlationContext& ctxt) {
    fortTkSupport::Symbol* sym = GetSymbol(elem, ctxt);
    ST* st = sym->GetST();
    WN_OFFSET oset = 0;
    if (ST_class(st) == CLASS_PREG) {
      oset = GetPregId(elem);
    }
    return make_pair(st, oset);
  }

  WN* XlateExpression::xlate_SymbolReferenceCollapsedPath(const DOMElement* elem, 
							  WN* pathVorlageWN,
							  PUXlationContext& ctxt) {
    OPERATOR opr = WN_operator(pathVorlageWN);
    bool create_lda = (ctxt.currentXlationContext().isFlag(XlationContext::LVALUE)); // FIXME  
    WN* wn = NULL;  
    switch (opr) {
    case OPR_STID: 
    case OPR_STBITS: {
      // Create an LDID
      TY_IDX ty_idx = WN_GetRefObjType(pathVorlageWN);
      TYPE_ID rty = TY_mtype(ty_idx); // OPCODE_rtype(WN_opcode())
      TYPE_ID dty = TY_mtype(ty_idx); // OPCODE_dtype(WN_opcode())
      ST* st = WN_st(pathVorlageWN);
      WN_OFFSET ofst = WN_offset(pathVorlageWN);
      UINT fid = WN_field_id(pathVorlageWN);
#if 0 // FIXME
      if (!TY_Is_Pointer(ty_idx)) {
	ty_idx = Stab_Pointer_To(ty_idx);
      }
      TYPE_ID rty = TY_mtype(ty_idx);
      wn = WN_CreateLda(OPR_LDA, rty, MTYPE_V, ofst, ty_idx, st, fid);
#endif
      wn = WN_CreateLdid(OPR_LDID, rty, dty, ofst, st, ty_idx, fid);
      break;
    }
    case OPR_ISTORE: 
    case OPR_ISTBITS: {
      // Create an ILOAD (copy ISTORE.kid1 to ILOAD.kid0)
      WN* addr = WN_COPY_Tree(WN_kid1(pathVorlageWN));
      TY_IDX refty = WN_GetRefObjType(pathVorlageWN);
      TY_IDX ptrty = WN_ty(pathVorlageWN);
      TYPE_ID mty = TY_mtype(refty);
      WN_OFFSET ofst = WN_offset(pathVorlageWN); 
      if (OPERATOR_has_offset(WN_operator(addr))) {
	ofst += WN_offset(addr); // ISTORE.offset + ISTORE.kid1.offset
      }
      UINT fid = WN_field_id(pathVorlageWN);
      wn = WN_CreateIload(OPR_ILOAD, mty, mty, ofst, refty, ptrty, addr, fid);
      break;
    }
    case OPR_LDA:
    case OPR_LDMA:
    case OPR_LDID:
    case OPR_LDBITS: 
    case OPR_ILOAD: 
    case OPR_ILDBITS:
      wn = WN_COPY_Tree(pathVorlageWN);
      break;
    default: 
      break; // fall through
    } // switch
    FORTTK_ASSERT(wn, fortTkSupport::Diagnostics::Unimplemented << "Unable to recreate collapsed scalarized path.");
    //if (!create_lda) {
    //}
    return wn;
  }

  WN* XlateExpression::xlate_ArrayElementReference(OA::OA_ptr<OA::DGraph::DGraphImplement> g, 
						   OA::OA_ptr<MyDGNode> n, 
						   PUXlationContext& ctxt) {
    FORTTK_ASSERT(!g.ptrEqual(NULL) && !n.ptrEqual(NULL), fortTkSupport::Diagnostics::UnexpectedInput);
    DOMElement* elem = n->GetElem();
    // -------------------------------------------------------
    // 1. Translate the index expression for each dimension
    // -------------------------------------------------------
    unsigned int rank = GetChildElementCount(elem);
    vector<WN*> indices(rank); 
    DOMElement* dim = GetFirstChildElement(elem);
    for (int i = 0; dim; dim = GetNextSiblingElement(dim), ++i) {
      const XMLCh* nmX = dim->getNodeName();
      FORTTK_ASSERT(XMLString::equals(nmX, XAIFStrings.elem_Index_x()), 
		    "Expected " << XAIFStrings.elem_Index() << "; found:\n"
		    << *dim);
      DOMElement* indexExpr = GetFirstChildElement(dim);
      ctxt.createXlationContext(XlationContext::ARRAYIDX);
      WN* indexExprWN = translateExpression(indexExpr, ctxt);
      ctxt.deleteXlationContext();
      // Ensure an integer 4 type for the index expression
      indices[i] = WN_Type_Conversion(indexExprWN, MTYPE_I4);
    }
    // -------------------------------------------------------
    // 2. Translate the array symbol reference
    // -------------------------------------------------------
    OA::OA_ptr<MyDGNode> n1 = GetSuccessor(n, false /* succIsOutEdge */);
    const XMLCh* nmX = n1->GetElem()->getNodeName();
    FORTTK_ASSERT(XMLString::equals(nmX, XAIFStrings.elem_SymRef_x()),
		  "Expected " << XAIFStrings.elem_SymRef() << "; found:\n"
		  << *(n1->GetElem()));
    ctxt.createXlationContext(XlationContext::ARRAY);
    WN* arraySym = xlate_VarRef(g, n1, ctxt);
    ctxt.deleteXlationContext();
    ST* st = WN_st(arraySym);
    TY_IDX ty = ST_type(st);
    if (TY_kind(ty) == KIND_POINTER) { 
      ty = TY_pointed(ty); 
    }
    FORTTK_ASSERT(TY_AR_ndims(ty) == (INT32)rank,
		  "Internal error: mismatched array dimensions");
    // -------------------------------------------------------
    // 3. Create Whirl ARRAY node (cf. wn_fio.cxx:1.3:7055)
    // -------------------------------------------------------
    UINT nkids = (rank * 2) + 1; // 2n + 1 where (where n == rank)
    WN* arrWN = WN_Create(OPR_ARRAY, MTYPE_U8, MTYPE_V, nkids);
    // kid 0 is the array's base address
    WN_kid0(arrWN) = arraySym;
    // kids 1 to n give size of each dimension.  We use a bogus value,
    // since we only need to support translation back to source code.
    for (unsigned i = 1; i <= rank; ++i) {
      WN_kid(arrWN, i) = WN_CreateIntconst(OPC_I4INTCONST, 0);
    }
    // kids n + 1 to 2n give index expressions for each dimension.  
    // N.B. Reverse the order of index expressions since we are
    // translating Fortran.  FIXME: should we change whirl2xaif and this
    // to not reverse the indices?
    for (unsigned i = 2*rank, j = 0; i >= (rank + 1); --i, ++j) {
      WN_kid(arrWN, i) = indices[j];
    }
    // -------------------------------------------------------
    // 4. Wrap the ARRAY in an ILOAD
    // -------------------------------------------------------
    TY_IDX ety = TY_etype(ty);
    TYPE_ID emty = TY_mtype(ety);
    TY_IDX eptrty = Stab_Pointer_To(ety);
    WN* wn = WN_CreateIload(OPR_ILOAD, emty, emty, 0, ety, eptrty, arrWN, 0);
    return wn;
  }

  OA::OA_ptr<OA::DGraph::DGraphImplement> XlateExpression::createExpressionGraph(const DOMElement* elem, 
										bool varRef) {
    using namespace OA::DGraph;
    MyDGNode::resetIds();
    OA::OA_ptr<DGraphImplement> g; g = new DGraphImplement();
    VertexIdToMyDGNodeMap m;
    // Setup variables
    XMLCh* edgeStr = NULL;
    if (varRef) {
      edgeStr = XAIFStrings.elem_VarRefEdge_x();
    } else {
      edgeStr = XAIFStrings.elem_ExprEdge_x();
    }
    // -------------------------------------------------------
    // Create the graph (only examine element nodes)
    // -------------------------------------------------------
    DOMElement* e = const_cast<DOMElement*>(elem);
    do {
      const XMLCh* name = e->getNodeName();
      if (XMLString::equals(name, edgeStr)) {
	// Add an edge to the graph.  N.B.: we ignore the 'position'
	// attribute during creation of the graph.
	// Find src and target (sink) nodes. 
	const XMLCh* srcX = e->getAttribute(XAIFStrings.attr_source_x());
	const XMLCh* targX = e->getAttribute(XAIFStrings.attr_target_x());
	XercesStrX src = XercesStrX(srcX);
	XercesStrX targ = XercesStrX(targX);
	OA::OA_ptr<MyDGNode> gn1 = m[std::string(src.c_str())];  // source
	OA::OA_ptr<MyDGNode> gn2 = m[std::string(targ.c_str())]; // target
	FORTTK_ASSERT(!gn1.ptrEqual(NULL) && !gn2.ptrEqual(NULL), "Invalid edge in expression graph:\n" << *e);
	OA::OA_ptr<MyDGEdge> ge; ge = new MyDGEdge(gn1, gn2, e); // src, targ
	g->addEdge(ge);
      } 
      else {
	// Add a vertex to the graph
	const XMLCh* vidX = e->getAttribute(XAIFStrings.attr_Vid_x());
	XercesStrX vid = XercesStrX(vidX);
	FORTTK_ASSERT(strlen(vid.c_str()) > 0, 
		      "Invalid vertex in expression graph:\n" << *e);
	OA::OA_ptr<MyDGNode> gn; gn = new MyDGNode(e);
	g->addNode(gn);
	m[std::string(vid.c_str())] = gn;
      } 
    } while ( (e = GetNextSiblingElement(e)) );
    // -------------------------------------------------------
    // Find the root node
    // -------------------------------------------------------
    // Since the graph is connected, the root node is the first (only)
    // node without outgoing edges.
    


    
    
    /*! commented out by PLM 08/30/06, I dont think I need to set RootNode in the Graph 
    OA::OA_ptr<NodeInterface> root; root = NULL;
    DGraph::NodesIterator nIt(*g);
    for ( ; nIt.isValid(); ++nIt) {
      OA::OA_ptr<NodeInterface> node = nIt.current();
      if (node->num_outgoing() == 0) {
	root = node;
	break;
      }
    }
    FORTTK_ASSERT(!root.ptrEqual(NULL), 
		  "Unable to find root of expression graph:\n" << *elem);
    g->setRoot(root);
    */
    return g;
  }

  WN* XlateExpression::createValueSelector(WN* wn) {
    TYPE_ID rty = getRType(wn);
    WN* callWN = CreateCallToIntrin(rty, "__value__", 1);
    WN_actual(callWN, 0) = CreateParm(wn, WN_PARM_BY_VALUE);
    return callWN;
  }

  WN* XlateExpression::createDerivSelector(WN* wn) {
    TYPE_ID rty = getRType(wn);
    WN* callWN = CreateCallToIntrin(rty, "__deriv__", 1);
    WN_actual(callWN, 0) = CreateParm(wn, WN_PARM_BY_VALUE);
    return callWN;
  }

  TYPE_ID XlateExpression::getRType(WN* wn) {
    TY_IDX ty_idx = WN_Tree_Type(wn);
    TYPE_ID rty = MTYPE_UNKNOWN;
    if (TY_kind(ty_idx) == KIND_ARRAY || TY_kind(ty_idx) == KIND_STRUCT) {
      rty = MTYPE_M;
    } else {
      rty = TY_mtype(ty_idx);
    }
    // FIXME: pointer types
    FORTTK_ASSERT(rty != MTYPE_UNKNOWN, "Error finding rtype of WN expr"); 
    return rty;
  }

  TYPE_ID XlateExpression::getRTypeFromOpands(vector<WN*>& opands) {
    int opands_num = opands.size();
    FORTTK_ASSERT(opands_num > 0, fortTkSupport::Diagnostics::UnexpectedInput);
    // 1. Gather types for operands
    vector<TY_IDX> opands_ty(opands_num);
    vector<TYPE_ID> opands_mty(opands_num);
    for (int i = 0; i < opands_num; ++i) {
      TY_IDX ty = WN_Tree_Type(opands[i]);
      opands_ty[i] = ty;
      opands_mty[i] = TY_mtype(ty);
      // FIXME: old: opands_mty[i] = WN_rtype(opands[i]);
    }
    // 2. Find an appropriate mtype for operands
    TYPE_ID mty = opands_mty[0];
    for (int i = 1; i < opands_num; ++i) {
      mty = getRTypeFromOpands(mty, opands_mty[i]);
    }
    return mty;
  }

  TYPE_ID XlateExpression::getRTypeFromOpands(TYPE_ID ty1, TYPE_ID ty2) {
    // -------------------------------------------------------
    // 1. If both types are same, the answer is easy
    // -------------------------------------------------------
    if (ty1 == ty2) {
      return ty1;
    } 
    // -------------------------------------------------------
    // 2. We have different types.
    // -------------------------------------------------------
    // 2a. If we have different, but compatible classes --> class promotion
    unsigned int cl1 = MTYPE_type_class(ty1);
    unsigned int cl2 = MTYPE_type_class(ty2);
    unsigned int cl = 0; // the new class
    if (cl1 == cl2) {
      cl = cl1;
    }
    // (u)int, float --> float
    if ( ((cl1 == MTYPE_CLASS_INTEGER || cl1 == MTYPE_CLASS_UNSIGNED_INTEGER) 
	  && (cl2 == MTYPE_CLASS_FLOAT))
	 ||
	 ((cl2 == MTYPE_CLASS_INTEGER || cl2 == MTYPE_CLASS_UNSIGNED_INTEGER)
	  && (cl1 == MTYPE_CLASS_FLOAT)) ) {
      cl = MTYPE_CLASS_FLOAT;
    }
    // int, uint --> [error]
    // !complex_float, complex_float --> [error]
    // !str, str --> [error]
    if (cl == 0) {
      return ty1; // FIXME: what to do here?
    }
    // 2b. If we have different sizes --> size promotion (choose larger)
    unsigned int sz1 = MTYPE_byte_size(ty1);
    unsigned int sz2 = MTYPE_byte_size(ty2);
    unsigned int sz = MAX(sz1, sz2); // the new size
    // 2c. Combine class and size information. 
    TYPE_ID ty = getMType(cl, sz);
    return ty;
  }

  TYPE_ID XlateExpression::getMType(unsigned int cl, unsigned int bytesz) {
    TYPE_ID ty = MTYPE_UNKNOWN;
    for (TYPE_ID i = MTYPE_FIRST; i <= MTYPE_LAST; ++i) {
      if ((MTYPE_type_class(i) == cl) && (MTYPE_byte_size(i) == bytesz)) {
	ty = i;
	break;
      }
    }
    return ty;
  }

  OPCODE XlateExpression::getWNExprOpcode(OPERATOR opr, vector<WN*>& opands) {
    // 1. Find mtype suggested from operands
    TYPE_ID mty = getRTypeFromOpands(opands);
    // 2. Find a dtype (operator dependent) FIXME/FIXME
    TYPE_ID dty = MTYPE_V; // typical dtype for intrinsics
    if (opr == OPR_TRUNC || 
	opr == OPR_EQ || opr == OPR_NE || opr == OPR_GT || opr == OPR_GE ||
	opr == OPR_LT || opr == OPR_LE) {
      dty = mty;
    } 
    // 3. Find a rtype (operator dependent)
    // FIXME: we need a better way; do we need a cvt? FIXME
    // Is_Valid_Opcode, Is_Valid_Opcode_Parts
    TYPE_ID rty = mty;
    if (opr == OPR_SQRT && MTYPE_is_integral(rty)) {
      // sqrt: f, z
      rty = getMType(MTYPE_CLASS_FLOAT, MTYPE_byte_size(rty));
    } 
    else if (opr == OPR_TRUNC || opr == OPR_MOD || opr == OPR_REM) {
      // trunc, mod, rem: i
      rty = getMType(MTYPE_CLASS_INTEGER, MTYPE_byte_size(rty));
    } 
    else if (opr == OPR_EQ || opr == OPR_NE || opr == OPR_GT || opr == OPR_GE ||
	     opr == OPR_LT || opr == OPR_LE) {
      rty = getMType(MTYPE_CLASS_INTEGER, 4);
    }
    OPCODE opc = OPCODE_make_op(opr, rty, dty);
    return opc;
  }

  INTRINSIC XlateExpression::getWNIntrinsic(const char* intrnNm, vector<WN*>& opands, TYPE_ID* dtype) {
    // 1. Find dtype suggested from operands
    TYPE_ID mty = getRTypeFromOpands(opands);
    // FIXME *** make part of an intrinsic table ***
    // per Nathan the situation is that there is 
    // a method to translate the whirl intrinsic enumerations 
    // into a  name but whirl doesn't have a function to 
    // translate the name back. Some of the backtranslation 
    // is done by looking at the intrinsics table in 
    // IntrinsicXlationTable.cxx but the following
    // are of type WNIntrinOp and 
    // don't have a backtranslation entry.
    // see also in Open64 common/com:
    // intrn_info.cxx, wutil.cxx
    INTRINSIC intrn = INTRINSIC_INVALID;
    if (strcmp(intrnNm, "EXPEXPR") == 0) {
      intrn = INTRN_F8EXPEXPR;
      if (dtype) { *dtype = MTYPE_F8; }
    }
    else if (strcmp(intrnNm, "CEQEXPR") == 0) {
      intrn = INTRN_CEQEXPR;
      if (dtype) { *dtype = MTYPE_I4; }
    }
    else if (strcmp(intrnNm, "CNEEXPR") == 0) {
      intrn = INTRN_CNEEXPR;
      if (dtype) { *dtype = MTYPE_I4; }
    }
    else if (strcmp(intrnNm, "AMOD") == 0) {
      intrn = INTRN_F4MOD;
      if (dtype) { *dtype = MTYPE_F4; }
    }
    FORTTK_ASSERT(intrn != INTRINSIC_INVALID, 
		  "Unknown intrinsic '" << intrnNm << "'");
    return intrn;
  }
}
