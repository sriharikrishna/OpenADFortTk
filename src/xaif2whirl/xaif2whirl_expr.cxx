// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_expr.cxx,v 1.3 2003/10/01 16:32:52 eraxxon Exp $

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
#include <algorithm>

//************************* Xerces Include Files ****************************

#include <xercesc/dom/DOMNodeIterator.hpp>
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
#include <lib/support/SymTab.h> // for XAIFSymToWhirlSymMap
#include <lib/support/WhirlIDMaps.h>
#include <lib/support/wn_attr.h> // for WN_Tree_Type
#include <lib/support/stab_attr.h> // for Stab_Pointer_To
#include <lib/support/XAIFStrings.h>
#include <lib/support/diagnostics.h>

#include <OpenAnalysis/Utils/DGraph.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

using namespace xaif2whirl;

// MyDGNode: Used with CreateExpressionGraph
typedef std::map<std::string, DGraph::Node*> IdToNodeMap;

class MyDGNode : public DGraph::Node {
public:
  MyDGNode(const DOMElement* e_) : e(e_) { }
  virtual ~MyDGNode() { }

  DOMElement* GetElem() const { return const_cast<DOMElement*>(e); }
  
private:
  const DOMElement* e;
};

// lt_ExprArgument: Used to sort operands (arguments) of (to) an
// expression by the "position" attribute
struct lt_ExprArgument
{
  // return true if n1 < n2; false otherwise
  bool operator()(const MyDGNode* n1, const MyDGNode* n2) const
  {
    unsigned int pos1 = GetPositionAttr(n1->GetElem());
    unsigned int pos2 = GetPositionAttr(n2->GetElem());
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
xlate_SymbolReference(const DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_ArrayElementReference(DGraph* g, MyDGNode* n, XlationContext& ctxt);


static DGraph* 
CreateExpressionGraph(const DOMElement* elem, bool varRef = false);

//*************************** Forward Declarations ***************************

static WN*
CreateValueSelector(WN* wn);

static WN*
CreateDerivSelector(WN* wn);


UINT
GetIntrinsicOperandNum(const char* name);

OPERATOR
GetIntrinsicOperator(const char* name);

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

static WN*
xlate_Expression(DGraph* g, MyDGNode* n, XlationContext& ctxt)
{
  // Recursively translate the DAG (tree) rooted at this node
  DOMElement* elem = n->GetElem();
  ASSERT_FATAL(elem, (DIAG_A_STRING, "Programming error."));
  
  const XMLCh* nameX = elem->getNodeName();
  XercesStrX name = XercesStrX(nameX);
  
  WN* wn = NULL;
  if (XMLString::equals(nameX, XAIFStrings.elem_VarRef_x())) {

    // VariableReference
    wn = xlate_VarRef(elem, ctxt);

  } else if (XMLString::equals(nameX, XAIFStrings.elem_Constant_x())) {
    
    // Constant
    wn = xlate_Constant(elem, ctxt);

  } else if (XMLString::equals(nameX, XAIFStrings.elem_Intrinsic_x())) {
    
    // Intrinsic
    wn = xlate_Intrinsic(g, n, ctxt);
    
  } else if (XMLString::equals(nameX, XAIFStrings.elem_FuncCall_x())) {

    // FunctionCall
    wn = xlate_FunctionCall(g, n, ctxt);

  } else if (XMLString::equals(nameX, XAIFStrings.elem_BoolOp_x())) {
    
    // BooleanOperation
    wn = xlate_BooleanOperation(g, n, ctxt);
    
  } else {
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
  
  // If we are not already within another VarRef and we are within an
  // active reference, select the appropriate portion (value, deriv)
  if (!ctxt.IsVarRef()) {
    if (ctxt.IsActive_V()) {
      wn = CreateValueSelector(wn);
    } else if (ctxt.IsActive_D()) {
      wn = CreateDerivSelector(wn);
    }
  }  
  
  return wn;
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

  } else if (XMLString::equals(nameX, XAIFStrings.elem_ArrayElemRef_x())) {
    
    // ArrayElementReference
    wn = xlate_ArrayElementReference(g, n, ctxt);
    
  } else {
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

    double val = strtod(value.c_str(), (char **)NULL);
    TCON tcon = Host_To_Targ_Float(MTYPE_F8, val);
    wn = Make_Const(tcon);

  } else if (strcmp(type.c_str(), "integer") == 0) {

    unsigned int val = strtol(value.c_str(), (char **)NULL, 10);

    TCON tcon = Host_To_Targ_Float(MTYPE_F8, (double)val);
    wn = Make_Const(tcon); // requires float or complex
    //wn = WN_Type_Conversion(wn, MTYPE_I8);

    //wn = WN_CreateIntconst(OPC_I8INTCONST, (INT64)val); FIXME

  } else if (strcmp(type.c_str(), "bool") == 0) {
    
    unsigned int val = (strcmp(value.c_str(), "false") == 0) ? 0 : 1;
    wn = WN_CreateIntconst(OPC_I4INTCONST, (INT64)val); // OPC_BINTCONST
    
  } else if (strcmp(type.c_str(), "char") == 0) {
    // an intconst: cwh_stmt.cxx:349
    assert(false); // FIXME
  } else if (strcmp(type.c_str(), "string") == 0) {

    // U4U1ILOAD 0 T<43,.character.,1> T<175,anon_ptr.,8>
    //   U8LDA 0 <1,596,(1_bytes)_"S"> T<127,anon_ptr.,8>

    // cf. fei_pattern_con
    TY_IDX ty = Be_Type_Tbl(MTYPE_STRING);
    TY_IDX ty_ptr = Stab_Pointer_To(ty);
    UINT32 len = strlen(value.c_str());
    TCON tcon = Host_To_Targ_String(MTYPE_STRING, (char*)value.c_str(), len);
    ST* st = Gen_String_Sym(&tcon, ty, FALSE);

    WN* lda = WN_CreateLda(OPR_LDA, Pointer_Mtype, MTYPE_V, 0, ty_ptr, st, 0);
    wn = WN_CreateIload(OPR_ILOAD, MTYPE_U4, MTYPE_U1, 0, ty, ty_ptr, lda, 0);
    
#if 0
    ST* csym = New_Const_Sym(Enter_tcon(tcon), Be_Type_Tbl(TCON_ty(tcon)));
    wn = WN_CreateConst(opc, csym);
   // wn = Make_Const(tcon); FIXME only handles floats
#endif
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
  
  UINT opnd_num = GetIntrinsicOperandNum(nm.c_str());
  OPERATOR op = GetIntrinsicOperator(nm.c_str());
  
  // 1. Gather the operands, sorted by the "position" attribute
  ASSERT_FATAL(n->num_incoming() == opnd_num, 
	       (DIAG_A_STRING, "Programming error."));
  std::vector<MyDGNode*> opnd(opnd_num, NULL); 
  
  DGraph::IncomingEdgesIterator it = DGraph::IncomingEdgesIterator(n);
  for (int i = 0; (bool)it; ++it, ++i) {
    DGraph::Edge* edge = (DGraph::Edge*)it;
    opnd[i] = dynamic_cast<MyDGNode*>(edge->source());
  }
  
  std::sort(opnd.begin(), opnd.end(), lt_ExprArgument()); // ascending
  
  // 2. Translate each operand into a WHIRL expression tree
  std::vector<WN*> opnd_wn(opnd_num, NULL); 
  for (int i = 0; i < opnd_num; ++i) {
    opnd_wn[i] = xlate_Expression(g, opnd[i], ctxt);
  }
  
  // 3. Create a WHIRL expression tree for the operator and operands
  // FIXME: we need to verify the return type
  switch (opnd_num) {
  case 1: // unary
    return WN_Unary(op, MTYPE_F8, opnd_wn[0]);
  case 2: // binary
    return WN_Binary(op, MTYPE_F8, opnd_wn[0], opnd_wn[1]);
  case 3: // ternary
    return WN_Ternary(op, MTYPE_F8, opnd_wn[0], opnd_wn[1], opnd_wn[2]);
  default:
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  } 
}

static WN*
xlate_FunctionCall(DGraph* g, MyDGNode* n, XlationContext& ctxt)
{
  if (!g || !n) { 
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  DOMElement* elem = n->GetElem();
  
  // FIXME: children are expr; find num of args
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
  
  // FIXME: children are expressions
  assert(false && "implement");
  return NULL;
}

static WN*
xlate_SymbolReference(const DOMElement* elem, XlationContext& ctxt)
{
  if (!elem) { 
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }

  WN* wn = NULL;
  ST* st = GetST(elem, ctxt);
  TY_IDX ty = ST_type(st);
  TYPE_ID rty, dty;

  // -------------------------------------------------------
  // 
  // -------------------------------------------------------
  bool create_lda = false;
  
  // Note: Order matters in these tests
  if (ctxt.IsArray()) {
    // Do not load the address of symbol that is already a pointer
    if (TY_kind(ty) != KIND_POINTER) {
      create_lda = true;
    }
  } else if (ctxt.IsLValue()) {
    create_lda = true;
  } 

  // -------------------------------------------------------
  // (FIXME)
  // -------------------------------------------------------
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
      if (MTYPE_is_unsigned(dty)) { rty = MTYPE_U8; }
      else if (MTYPE_is_signed(dty)) { rty = MTYPE_I8; }
    }

    wn = WN_CreateLdid(OPR_LDID, rty, dty, 0, st, ty, 0);

  } 
  return wn;
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
  std::vector<WN*> indices(rank); 
  
  DOMElement* dim = GetFirstChildElement(elem);
  for (int i = 0; dim; dim = GetNextSiblingElement(dim), ++i) {
    
    const XMLCh* nmX = dim->getNodeName();
    ASSERT_FATAL(XMLString::equals(nmX, XAIFStrings.elem_Index_x()), 
		 (DIAG_A_STRING, "Programming error."));
    
    DOMElement* indexExpr = GetFirstChildElement(dim);
    WN* indexExprWN = TranslateExpression(indexExpr, ctxt);
    
    // Ensure an integer 4 type for the index expression
    indices[i] = WN_Type_Conversion(indexExprWN, MTYPE_I4);
  }
  
  // -------------------------------------------------------
  // 2. Translate the array symbol reference
  // -------------------------------------------------------
  ASSERT_FATAL(n->num_incoming() == 1,
	       (DIAG_A_STRING, "Programming error."));
  DGraph::IncomingEdgesIterator it = DGraph::IncomingEdgesIterator(n);
  DGraph::Edge* edge = (DGraph::Edge*)it;
  
  MyDGNode* n1 = dynamic_cast<MyDGNode*>(edge->source());
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
  DGraph* g = new DGraph;
  IdToNodeMap m;

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

      MyDGNode* gn1 = NULL, *gn2 = NULL; // src and targ
      
      IdToNodeMap::iterator it = m.find(std::string(src.c_str()));
      if (it != m.end()) { 
	gn1 = dynamic_cast<MyDGNode*>((*it).second); 
      }
      
      it = m.find(std::string(targ.c_str()));
      if (it != m.end()) { 
	gn2 = dynamic_cast<MyDGNode*>((*it).second); 
      }
      
      ASSERT_FATAL(gn1 && gn2, (DIAG_A_STRING, "Programming error."));
      
      DGraph::Edge* ge = new DGraph::Edge(gn1, gn2); // src, targ
      g->add(ge);
      
    } else {
      // Add a vertex to the graph
      const XMLCh* vidX = e->getAttribute(XAIFStrings.attr_Vid_x());
      XercesStrX vid = XercesStrX(vidX);
      ASSERT_FATAL(strlen(vid.c_str()) > 0, (DIAG_A_STRING, "Error."));
      
      MyDGNode* gn = new MyDGNode(e);
      g->add(gn);
      m.insert(make_pair(std::string(vid.c_str()), 
			 dynamic_cast<DGraph::Node*>(gn)));
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
static WN*
CreateValueSelector(WN* wn)
{
  WN* callWN = CreateIntrinsicCall(MTYPE_F8, "__value__", 1);
  WN_actual(callWN, 0) = CreateParm(wn, WN_PARM_BY_VALUE);
  return callWN;
}

// CreateDerivSelector: Select the deriv portion of 'wn', by wrapping
// a dummy intrinsic call around it
static WN*
CreateDerivSelector(WN* wn)
{
  WN* callWN = CreateIntrinsicCall(MTYPE_F8, "__deriv__", 1);
  WN_actual(callWN, 0) = CreateParm(wn, WN_PARM_BY_VALUE);
  return callWN;
}

//****************************************************************************

// FIXME: create tables for these
UINT 
GetIntrinsicOperandNum(const char* name)
{
  if (!name) { return 0; }
  
  if ((strcmp(name, "minus_scal") == 0) ||
      (strcmp(name, "sqr_scal") == 0)) {
    return 1;
  } else if ((strcmp(name, "add_scal_scal") == 0) ||
	     (strcmp(name, "sub_scal_scal") == 0) ||
	     (strcmp(name, "mul_scal_scal") == 0) ||
	     (strcmp(name, "div_scal_scal") == 0)) {
    return 2;
  } else {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Bad Intrinsic."));
    return 0;
  }
}

OPERATOR 
GetIntrinsicOperator(const char* name)
{
  if (!name) { return OPERATOR_UNKNOWN; }
  
  if (strcmp(name, "minus_scal") == 0) {
    return OPR_NEG;
  } else if (strcmp(name, "sqr_scal") == 0) {
    return OPR_SQRT;
  } else if (strcmp(name, "add_scal_scal") == 0) {
    return OPR_ADD;
  } else if (strcmp(name, "sub_scal_scal") == 0) {
    return OPR_SUB;
  } else if (strcmp(name, "mul_scal_scal") == 0) {
    return OPR_MPY;
  } else if (strcmp(name, "div_scal_scal") == 0) {
    return OPR_DIV;
  } else {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Bad Intrinsic."));
    return OPERATOR_UNKNOWN;
  }
}

//****************************************************************************
