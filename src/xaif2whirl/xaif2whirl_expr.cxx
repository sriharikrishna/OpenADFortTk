// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_expr.cxx,v 1.20 2004/05/04 23:52:06 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_expr.cxx,v $
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
#include <vector>
using std::vector;
#include <algorithm>

//************************* Xerces Include Files ****************************

#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMElement.hpp>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "xaif2whirl.h"
#include "xaif2whirl_expr.h"

#include "XAIF_DOMFilters.h"
#include "XercesStrX.h"

#include <lib/support/Pro64IRInterface.h>
#include <lib/support/SymTab.h>    // for XAIFSymToWhirlSymMap
#include <lib/support/WhirlIDMaps.h>
#include <lib/support/wn_attr.h>   // for WN_Tree_Type
#include <lib/support/stab_attr.h> // for Stab_Pointer_To
#include <lib/support/XAIFStrings.h>
#include <lib/support/diagnostics.h>

//*************************** Forward Declarations ***************************

// FIXME
extern bool opt_typeChangeInWHIRL;
extern TY_IDX ActiveTypeTyIdx; 

using std::cerr;
using std::endl;

using namespace xaif2whirl;

// sort_Position: Used to sort operands of (arguments to) an expression
// by the "position" attribute
struct sort_Position
{
  // return true if e1 < e2; false otherwise
  bool operator()(const MyDGEdge* e1, const MyDGEdge* e2) const
  {
    unsigned int pos1 = GetPositionAttr(e1->GetElem());
    unsigned int pos2 = GetPositionAttr(e2->GetElem());
    return (pos1 < pos2);
  }
};

//*************************** Forward Declarations ***************************

static WN*
xlate_Expression(DGraph* g, MyDGNode* n, XlationContext& ctxt);

static WN*
xlate_VarRef(const DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_VarRef(DGraph* g, MyDGNode* n, XlationContext& ctxt);

static WN*
xlate_Constant(const DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_Intrinsic(DGraph* g, MyDGNode* n, XlationContext& ctxt);

static WN*
xlate_FunctionCall(DGraph* g, MyDGNode* n, XlationContext& ctxt);

static WN*
xlate_BooleanOperation(DGraph* g, MyDGNode* n, XlationContext& ctxt);

static WN*
xlate_ExprOpUsingIntrinsicTable(IntrinsicXlationTable::XAIFOpr xopr, 
				const char* xoprNm, const char* xIntrinKey,
				DGraph* g, MyDGNode* n, XlationContext& ctxt);

static WN*
xlate_SymbolReference(const DOMElement* elem, XlationContext& ctxt);

static ST*
xlate_SymbolReferenceSimple(const DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_ArrayElementReference(DGraph* g, MyDGNode* n, XlationContext& ctxt);


static DGraph* 
CreateExpressionGraph(const DOMElement* elem, bool varRef = false);

//*************************** Forward Declarations ***************************

static WN*
CreateValueSelector(WN* wn);

static WN*
CreateDerivSelector(WN* wn);


static TYPE_ID
GetRType(WN* wn);

static TYPE_ID
GetRTypeFromOpands(vector<WN*>& opands);

static TYPE_ID
GetRTypeFromOpands(TYPE_ID ty1, TYPE_ID ty2);

static TYPE_ID
GetMType(unsigned int cl, unsigned int bytesz);

static OPCODE
GetWNExprOpcode(OPERATOR opr, vector<WN*>& opands);

static INTRINSIC
GetWNIntrinsic(const char* intrnNm, vector<WN*>& opands, TYPE_ID* dtype);

//****************************************************************************


// TranslateExpression: Given the first node in an expression graph... 
WN*
xaif2whirl::TranslateExpression(const DOMElement* elem, XlationContext& ctxt)
{
  if (!elem) {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  // Slurp expression into a graph (DAG) and translate it
  DGraph* g = CreateExpressionGraph(elem);
  MyDGNode* n = dynamic_cast<MyDGNode*>(g->root());
  WN* wn = xlate_Expression(g, n, ctxt);
  delete g;

  return wn;
}


// TranslateExpressionSimple: Translates certain XAIF expressions into
// special WHIRL expressions in order to conform to WHIRL
// requirements.
WN*
xaif2whirl::TranslateExpressionSimple(const DOMElement* elem, 
				      XlationContext& ctxt)
{
  ctxt.CreateContext(XlationContext::EXPRSIMPLE);
  WN* wn = TranslateExpression(elem, ctxt);
  ctxt.DeleteContext();
  
  return wn;
}


static WN*
xlate_Expression(DGraph* g, MyDGNode* n, XlationContext& ctxt)
{
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
    wn = xlate_Constant(elem, ctxt);
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
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Unknown Expression element"));
  }

  return wn;
}


static WN*
xlate_VarRef(const DOMElement* elem, XlationContext& ctxt)
{
  if (!elem) { 
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  // VariableReferenceType
  bool deriv = GetDerivAttr(elem);
  uint32_t flg = (deriv) ? XlationContext::ACTIVE_D : XlationContext::ACTIVE_V;
  
  // skip the xaif:VariableReference node
  DOMElement* varref = GetFirstChildElement(elem); 
  
  ctxt.CreateContext(flg);
  WN* wn = TranslateVarRef(varref, ctxt);
  ctxt.DeleteContext();
  
  return wn;
}


// TranslateVarRef: Given the first node in a variable reference
// graph, create a variable reference.
//
// If the LVALUE flag of 'ctxt' is set an address expression (lvalue)
// is returned; otherwise a rvalue is returned.  If this is the
// outermost part of an active varref, creates a value/deriv selector.
WN*
xaif2whirl::TranslateVarRef(const DOMElement* elem, XlationContext& ctxt)
{
  if (!elem) {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  // Slurp expression into a graph (DAG) and translate it
  ctxt.CreateContext(XlationContext::VARREF);
  DGraph* g = CreateExpressionGraph(elem, true /* varRef */);
  MyDGNode* n = dynamic_cast<MyDGNode*>(g->root());
  WN* wn = xlate_VarRef(g, n, ctxt);
  ctxt.DeleteContext();
  delete g;
  
  // If we are not already within another VarRef and we translated an
  // active symbol, select the appropriate portion of the active type
  if (!ctxt.IsVarRef()) {
    if (ctxt.IsActive_V()) {
      wn = CreateValueSelector(wn); // active
    } else if (ctxt.IsActive_D()) {
      wn = CreateDerivSelector(wn); // deriv
    }
    ctxt.ResetActive(); // halt up-inheritance
  }  
  
  return wn;
}


// TranslateSimpleVarRef: Given the first node in a simple variable
// reference graph, create a variable reference.  No value/deriv
// selector can be created.
ST*
xaif2whirl::TranslateVarRefSimple(const DOMElement* elem, XlationContext& ctxt)
{
  if (!elem) {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  // This must be a plain XAIF symbol reference (a one-vertex graph)
  const XMLCh* nameX = elem->getNodeName();
  if ( !(XMLString::equals(nameX, XAIFStrings.elem_SymRef_x()) &&
	 GetNextSiblingElement(elem) == NULL) ) {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "XAIF error..."));
  }
  
  ctxt.CreateContext(XlationContext::NOFLAG);
  ST* st = xlate_SymbolReferenceSimple(elem, ctxt);
  ctxt.DeleteContext();
  
  return st;
}


static WN*
xlate_VarRef(DGraph* g, MyDGNode* n, XlationContext& ctxt)
{
  if (!g || !n) { 
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  // Recursively translate the DAG (tree) rooted at this node
  DOMElement* elem = n->GetElem();
  ASSERT_FATAL(elem, (DIAG_A_STRING, "Programming error."));
  
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
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Unknown Variable Reference element"));
  }
  
  return wn;
}


static WN*
xlate_Constant(const DOMElement* elem, XlationContext& ctxt)
{
  if (!elem) { 
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }

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
    if (ctxt.IsArrayIdx() || ctxt.IsExprSimple()) {
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
    assert(false); // FIXME
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


static WN*
xlate_Intrinsic(DGraph* g, MyDGNode* n, XlationContext& ctxt)
{
  if (!g || !n) {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  DOMElement* elem = n->GetElem();
  const XMLCh* nmX = elem->getAttribute(XAIFStrings.attr_name_x());
  XercesStrX nm = XercesStrX(nmX);
  
  std::string key = GetIntrinsicKey(elem);

  IntrinsicXlationTable::XAIFOpr xopr = IntrinsicXlationTable::XAIFIntrin;
  WN* wn = xlate_ExprOpUsingIntrinsicTable(xopr, nm.c_str(), key.c_str(), 
					   g, n, ctxt);
  return wn;
}


static WN*
xlate_FunctionCall(DGraph* g, MyDGNode* n, XlationContext& ctxt)
{
  if (!g || !n) { 
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  DOMElement* elem = n->GetElem();
  
  // FIXME: children are expr; find num of args (use Intrinsic function above)
  assert(false && "implement"); 
  return NULL;
}


static WN*
xlate_BooleanOperation(DGraph* g, MyDGNode* n, XlationContext& ctxt)
{
  if (!g || !n) { 
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }

  DOMElement* elem = n->GetElem();
  const XMLCh* nmX = elem->getAttribute(XAIFStrings.attr_name_x());
  XercesStrX nm = XercesStrX(nmX);
  
  IntrinsicXlationTable::XAIFOpr xopr = IntrinsicXlationTable::XAIFBoolOp;
  WN* wn = xlate_ExprOpUsingIntrinsicTable(xopr, nm.c_str(), NULL, g, n, ctxt);
  return wn;
}


// xlate_ExprOpUsingIntrinsicTable: abstract similarities betweeen
// translation of XAIF Intrinsic, FunctionCall, BooleanOperation.  The
// XAIF operator will become either a special WHIRL node or some type
// of WHIRL call.
static WN*
xlate_ExprOpUsingIntrinsicTable(IntrinsicXlationTable::XAIFOpr xopr, 
				const char* xoprNm, const char* xIntrinKey,
				DGraph* g, MyDGNode* n, XlationContext& ctxt)
{
  IntrinsicXlationTable::WHIRLInfo* info = 
    IntrinsicTable.FindWHIRLInfo(xopr, xoprNm, xIntrinKey);
  if (!info) {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Bad Intrinsic."));
  }
  
  // 1. Gather the operands, sorted by the "position" attribute
  ASSERT_FATAL(n->num_incoming() == info->numop, 
	       (DIAG_A_STRING, "Programming error."));
  vector<MyDGEdge*> opnd_edge(info->numop, NULL);
  DGraph::IncomingEdgesIterator it = DGraph::IncomingEdgesIterator(n);
  for (int i = 0; (bool)it; ++it, ++i) {
    opnd_edge[i] = dynamic_cast<MyDGEdge*>((DGraph::Edge*)it);
  }
  std::sort(opnd_edge.begin(), opnd_edge.end(), sort_Position()); // ascending
  
  // 2. Translate each operand into a WHIRL expression tree
  vector<WN*> opnd_wn(info->numop, NULL); 
  for (int i = 0; i < info->numop; ++i) {
    MyDGNode* opnd = dynamic_cast<MyDGNode*>(opnd_edge[i]->source());
    opnd_wn[i] = xlate_Expression(g, opnd, ctxt);
  }
  
  // FIXME:: Here promote all arguments up to 8 bytes
  
  // 3. Translate into either WHIRL OPR_CALL or a WHIRL expression operator
  WN* wn = NULL;
  switch (info->oprcl) {
  case IntrinsicXlationTable::WNCall: {
    TYPE_ID rtype = MTYPE_F8; // FIXME
    wn = CreateCallToIntrin(rtype, info->name, opnd_wn);
    break;
  }
  case IntrinsicXlationTable::WNIntrinCall:
  case IntrinsicXlationTable::WNIntrinOp: {
    TYPE_ID rtype = MTYPE_F8; // FIXME
    TYPE_ID dtype = MTYPE_V;  // FIXME
    INTRINSIC intrn = GetWNIntrinsic(info->name, opnd_wn, NULL);
    wn = CreateIntrinsicCall(info->opr, intrn, rtype, dtype, opnd_wn);
    break;
  }
  case IntrinsicXlationTable::WNExpr: {
    // Find the opcode for the expression
    OPCODE opc = GetWNExprOpcode(info->opr, opnd_wn);
    
    // Create a WHIRL expression tree for the operator and operands
    switch (info->numop) {
    case 1: // unary
      wn = WN_CreateExp1(opc, opnd_wn[0]); break;
    case 2: // binary
      wn = WN_CreateExp2(opc, opnd_wn[0], opnd_wn[1]); break;
    case 3: // ternary
      wn = WN_CreateExp3(opc, opnd_wn[0], opnd_wn[1], opnd_wn[2]); break;
    default:
      ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
    } 
    break;
  }
  default:
    ASSERT_FATAL(false, (DIAG_A_STRING, "Invalid operator class"));
  }
  
  return wn;
}


// xlate_SymbolReferenceSimple: Translate a symbol reference.  May an
// active flag in 'ctxt' that is inherited *up* the context stack.
// N.B.: For PREGS we *do not* create a LDA
static WN*
xlate_SymbolReference(const DOMElement* elem, XlationContext& ctxt)
{
  if (!elem) { 
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }

  WN* wn = NULL;
  Symbol* sym = GetSymbol(elem, ctxt);
  ST* st = sym->GetST();
  TY_IDX ty = ST_type(st);
  TYPE_ID rty, dty;
  
  if (sym->IsActive()) {
    ctxt.SetActive(); // N.B. inherited up the ctxt stack
  }

  // -------------------------------------------------------
  // 1. Determine which type of load to use
  // -------------------------------------------------------
  bool create_lda = false;
  
  // Note: Order matters in these tests
  if (ST_class(st) != CLASS_PREG) { // never create a pointer to a preg
    if (ctxt.IsArray()) {
      // Do not load the address of symbol that is already a pointer
      if (TY_kind(ty) != KIND_POINTER) {
	create_lda = true;
      }
    } 
    else if (ctxt.IsLValue()) {
      create_lda = true;
    } 
  }

  // -------------------------------------------------------
  // 2. Create the reference
  // -------------------------------------------------------
  
  // Patch up types for active ty FIXME_CHANGE_TYPES_IN_WHIRL
  if (TY_kind(ty) == KIND_STRUCT && ty == ActiveTypeTyIdx) {
    rty = dty = MTYPE_F8;
    ty = MTYPE_To_TY(rty); // must also change ty of loaded item
  }

  if (create_lda) {
    // OPR_LDA
    TY_IDX ty_ptr = Stab_Pointer_To(ty);
    rty = TY_mtype(ty_ptr); // Pointer_Mtype
    wn = WN_CreateLda(OPR_LDA, rty, MTYPE_V, 0, ty_ptr, st, 0);
  } else {
    
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

    wn = WN_CreateLdid(OPR_LDID, rty, dty, 0, st, ty, 0);
    
  } 
  return wn;
}


// xlate_SymbolReferenceSimple: Translate a simple symbol reference.
// Do not set an active flag.
static ST*
xlate_SymbolReferenceSimple(const DOMElement* elem, XlationContext& ctxt)
{
  Symbol* sym = GetSymbol(elem, ctxt);
  ST* st = sym->GetST();
  return st;
}


static WN*
xlate_ArrayElementReference(DGraph* g, MyDGNode* n, XlationContext& ctxt)
{
  if (!g || !n) { 
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }

  DOMElement* elem = n->GetElem();
  
  // -------------------------------------------------------
  // 1. Translate the index expression for each dimension
  // -------------------------------------------------------
  unsigned int rank = GetChildElementCount(elem);
  vector<WN*> indices(rank); 
  
  DOMElement* dim = GetFirstChildElement(elem);
  for (int i = 0; dim; dim = GetNextSiblingElement(dim), ++i) {
    
    const XMLCh* nmX = dim->getNodeName();
    ASSERT_FATAL(XMLString::equals(nmX, XAIFStrings.elem_Index_x()), 
		 (DIAG_A_STRING, "Programming error."));
    
    DOMElement* indexExpr = GetFirstChildElement(dim);

    ctxt.CreateContext(XlationContext::ARRAYIDX);
    WN* indexExprWN = TranslateExpression(indexExpr, ctxt);
    ctxt.DeleteContext();

    // Ensure an integer 4 type for the index expression
    indices[i] = WN_Type_Conversion(indexExprWN, MTYPE_I4);
  }
  
  // -------------------------------------------------------
  // 2. Translate the array symbol reference
  // -------------------------------------------------------
  MyDGNode* n1 = GetSuccessor(n, false /* succIsOutEdge */);
  const XMLCh* nmX = n1->GetElem()->getNodeName();
  ASSERT_FATAL(XMLString::equals(nmX, XAIFStrings.elem_SymRef_x()),
	       (DIAG_A_STRING, "Programming error."));
  
  ctxt.CreateContext(XlationContext::ARRAY);
  WN* arraySym = xlate_VarRef(g, n1, ctxt);
  ctxt.DeleteContext();
  
  ST* st = WN_st(arraySym);
  TY_IDX ty = ST_type(st); // array type
  if (TY_kind(ty) == KIND_POINTER) { 
    ty = TY_pointed(ty); 
  }
  ASSERT_FATAL(TY_AR_ndims(ty) == rank,
	       (DIAG_A_STRING, "Programming error."));
  
  // -------------------------------------------------------
  // 3. Create Whirl ARRAY node (cf. wn_fio.cxx:7056)
  // -------------------------------------------------------
  UINT nkids = (rank * 2) + 1; // 2n + 1 where (where n == rank)
  WN* array = WN_Create(OPC_U8ARRAY, nkids);
  
  // kid 0 is the array's base address
  WN_kid0(array) = arraySym;
  
  // kids 1 to n give size of each dimension.  We use a bogus value,
  // since we only need to support translation back to source code.
  for (int i = 1; i <= rank; ++i) {
    WN_kid(array, i) = WN_CreateIntconst(OPC_I4INTCONST, 0);
  }
  
  // kids n + 1 to 2n give index expressions for each dimension.  
  // N.B. Reverse the order of index expressions since we are
  // translating Fortran.  FIXME: should we change whirl2xaif and this
  // to not reverse the indices?
  for (int i = 2*rank, j = 0; i >= (rank + 1); --i, ++j) {
    WN_kid(array, i) = indices[j];
  }

  WN* wn = array;
  return wn;
}


//****************************************************************************

// CreateExpressionGraph: Given the first element in an XAIF
// expression or variable reference graph, returns a DGraph where
// where graph nodes point to nodes in the DOM tree.  Variable
// reference graphs are special cases of an expression graph.
//
// When walking a top-down graph from root to children, one descends
// *incoming* edges.  Here is an example expression:
//
//     mult    <==   x * (y + z)
//     ^ ^
//    /   \
//   x   plus
//       ^ ^
//      /   \
//     y     z
//
// Here is an example variable reference:
//  
//  ArrayElementReference        <==   A[1, i]
//    Index: Constant: 1
//    Index: SymbolReference: i
//        ^ 
//        |
//  SymbolReference: A
//    
static DGraph* 
CreateExpressionGraph(const DOMElement* elem, bool varRef)
{
  MyDGNode::resetIds();
  DGraph* g = new DGraph;
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

      MyDGNode* gn1 = m[std::string(src.c_str())];  // source
      MyDGNode* gn2 = m[std::string(targ.c_str())]; // target
      ASSERT_FATAL(gn1 && gn2, (DIAG_A_STRING, "Programming error."));
      
      MyDGEdge* ge = new MyDGEdge(gn1, gn2, e); // src, targ
      g->add(ge);
      
    } else {
      // Add a vertex to the graph
      const XMLCh* vidX = e->getAttribute(XAIFStrings.attr_Vid_x());
      XercesStrX vid = XercesStrX(vidX);
      ASSERT_FATAL(strlen(vid.c_str()) > 0, (DIAG_A_STRING, "Error."));
      
      MyDGNode* gn = new MyDGNode(e);
      g->add(gn);
      m[std::string(vid.c_str())] = gn;
    } 
    
  } while ( (e = GetNextSiblingElement(e)) );
  
  
  // -------------------------------------------------------
  // Find the root node
  // -------------------------------------------------------
  
  // Since the graph is connected, the root node is the first (only)
  // node without outgoing edges.
  DGraph::Node* root = NULL;
  DGraph::NodesIterator nIt = DGraph::NodesIterator(*g);
  for ( ; (bool)nIt; ++nIt) {
    DGraph::Node* node = (DGraph::Node*)nIt;
    if (node->num_outgoing() == 0) {
      root = node;
      break;
    }
  }
  
  ASSERT_FATAL(root, (DIAG_A_STRING, "Programming error."));
  g->set_root(root);
  
  return g;
}


//****************************************************************************

// PatchWNExpr: Descends through the expression rooted at
// WN_kid(parent, kidno), modifying variable references with a
// value-component selector.
//
// This function purposefully only operates on expressions (as
// opposed to arbitrary WHIRL trees) because statements have to be
// processed specially.
WN*
xaif2whirl::PatchWNExpr(WN* parent, INT kidno, XlationContext& ctxt)
{
  // Simple Base cases
  if (!parent) { return NULL; }
  
  WN* wn = WN_kid(parent, kidno);
  if (!wn) { return NULL; }
  
  OPERATOR opr = WN_operator(wn);
  if (!OPERATOR_is_expression(opr)) { return parent; }
  
  // Base case: a variable reference
  if (IsVarRefTranslatableToXAIF(wn)) {

    // FIXME: only patch floating point references?
    TY_IDX ty = WN_Tree_Type(wn);
    if (MTYPE_is_float(TY_mtype(ty))) {
      WN* newwn = CreateValueSelector(wn);
      WN_kid(parent, kidno) = newwn;
    }
    
  } else {
    // Recursive case
    for (INT i = 0; i < WN_kid_count(wn); ++i) {
      PatchWNExpr(wn, i /* kid */, ctxt);
    }
  }
  
  return parent;
}


//****************************************************************************

// CreateValueSelector: Select the value portion of 'wn', by wrapping
// a dummy intrinsic call around it
// N.B.: This creates a OPR_CALL node, which is not an expression.
static WN*
CreateValueSelector(WN* wn)
{
  if (!opt_typeChangeInWHIRL) {
    TYPE_ID rty = GetRType(wn);
    WN* callWN = CreateCallToIntrin(rty, "__value__", 1);
    WN_actual(callWN, 0) = CreateParm(wn, WN_PARM_BY_VALUE);
    return callWN;
  } else {
    return wn;
  }
}


// CreateDerivSelector: Select the deriv portion of 'wn', by wrapping
// a dummy intrinsic call around it
// N.B.: This creates a OPR_CALL node, which is not an expression.
static WN*
CreateDerivSelector(WN* wn)
{
  if (!opt_typeChangeInWHIRL) {
    TYPE_ID rty = GetRType(wn);
    WN* callWN = CreateCallToIntrin(rty, "__deriv__", 1);
    WN_actual(callWN, 0) = CreateParm(wn, WN_PARM_BY_VALUE);
    return callWN;
  } else {
    WN* retWN = wn;
    // LDID: update the offset field
    // ILOAD: update the offset field
    OPERATOR opr = WN_operator(wn);
    if (opr == OPR_LDA) {
      STAB_OFFSET offset = WN_lda_offset(wn) + 8;
      WN_lda_offset(wn) = offset;
    } 
    else if (opr == OPR_LDID || opr == OPR_ILOAD) {
      STAB_OFFSET offset = WN_load_offset(wn) + 8;
      WN_load_offset(wn) = offset;
    } 
    else if (opr == OPR_ARRAY) {
      // ARRAY: Place an ADD around the ARRAY with the offset
      WN* offsetWN = WN_CreateIntconst(OPC_U8INTCONST, 8);
      retWN = WN_CreateExp2(OPC_U8ADD, wn, offsetWN);
    } 
    else {
      ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
    }
    return retWN;
  }
}


//****************************************************************************

static TYPE_ID
GetRType(WN* wn)
{
  TY_IDX ty_idx = WN_Tree_Type(wn);
  
  TYPE_ID rty = MTYPE_UNKNOWN;
  if (TY_kind(ty_idx) == KIND_ARRAY || TY_kind(ty_idx) == KIND_STRUCT) {
    rty = MTYPE_M;
  } else {
    rty = TY_mtype(ty_idx);
  }

  // FIXME: pointer types?
  assert(rty != MTYPE_UNKNOWN);
  
  return rty;
}


static TYPE_ID
GetRTypeFromOpands(vector<WN*>& opands)
{
  int opands_num = opands.size();
  ASSERT_FATAL(opands_num > 0, (DIAG_A_STRING, "Programming error."));
  
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
    mty = GetRTypeFromOpands(mty, opands_mty[i]);
  }
  
  return mty;
}


static TYPE_ID
GetRTypeFromOpands(TYPE_ID ty1, TYPE_ID ty2)
{
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
  TYPE_ID ty = GetMType(cl, sz);
  return ty;
}


// GetMType: Scan Machine_Types table for the right type.
static TYPE_ID
GetMType(unsigned int cl, unsigned int bytesz)
{
  TYPE_ID ty = MTYPE_UNKNOWN;
  for (TYPE_ID i = MTYPE_FIRST; i <= MTYPE_LAST; ++i) {
    if ((MTYPE_type_class(i) == cl) && (MTYPE_byte_size(i) == bytesz)) {
      ty = i;
      break;
    }
  }
  return ty;
}


static OPCODE
GetWNExprOpcode(OPERATOR opr, vector<WN*>& opands)
{
  // 1. Find mtype suggested from operands
  TYPE_ID mty = GetRTypeFromOpands(opands);

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
    rty = GetMType(MTYPE_CLASS_FLOAT, MTYPE_byte_size(rty));
  } 
  else if (opr == OPR_TRUNC) {
    // trunc: i
    rty = GetMType(MTYPE_CLASS_INTEGER, MTYPE_byte_size(rty));
  } 
  else if (opr == OPR_EQ || opr == OPR_NE || opr == OPR_GT || opr == OPR_GE ||
	   opr == OPR_LT || opr == OPR_LE) {
    rty = GetMType(MTYPE_CLASS_INTEGER, 4);
  }
  
  OPCODE opc = OPCODE_make_op(opr, rty, dty);
  return opc;
}


static INTRINSIC
GetWNIntrinsic(const char* intrnNm, vector<WN*>& opands, TYPE_ID* dtype)
{
  // 1. Find dtype suggested from operands
  TYPE_ID mty = GetRTypeFromOpands(opands);
  
  // FIXME 
  INTRINSIC intrn = INTRINSIC_INVALID;
  if (strcmp(intrnNm, "EXPEXPR") == 0) {
    intrn = INTRN_F8EXPEXPR; // FIXME
  }
  
  if (dtype) {
    *dtype = MTYPE_F8; // FIXME
  }

  ASSERT_FATAL(intrn != INTRINSIC_INVALID, 
	       (DIAG_A_STRING, "Unknown Intrinsic."));
  return intrn;
}

//****************************************************************************
