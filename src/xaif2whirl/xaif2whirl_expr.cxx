// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/xaif2whirl_expr.cxx,v 1.1 2003/09/17 19:42:16 eraxxon Exp $

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
#include <lib/support/XAIFStrings.h>
#include <lib/support/diagnostics.h>

#include <OpenAnalysis/Utils/DGraph.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

using namespace xaif2whirl;

// Used with CreateExpressionGraph
typedef std::map<std::string, DGraph::Node*> IdToNodeMap;

class MyDGNode : public DGraph::Node {
public:
  MyDGNode(DOMElement* e_) : e(e_) { }
  virtual ~MyDGNode() { }

  DOMElement* GetElem() { return e; }
  
private:
  DOMElement* e;
};

//*************************** Forward Declarations ***************************

static WN*
xlate_Expression(DGraph* g, MyDGNode* n, XlationContext& ctxt);

static WN*
xlate_VarRef(DGraph* g, MyDGNode* n, XlationContext& ctxt);

static WN*
xlate_Constant(DOMElement* elem, XlationContext& ctxt);


static DGraph* 
CreateExpressionGraph(DOMNode* node, bool varRef = false);

//*************************** Forward Declarations ***************************

static WN*
CreateValueSelector(WN* wn);


UINT
GetIntrinsicOperandNum(const char* name);

OPERATOR
GetIntrinsicOperator(const char* name);

//****************************************************************************

// TranslateExpression: Given the first node in an expression graph... 
WN*
xaif2whirl::TranslateExpression(DOMElement* elem, XlationContext& ctxt)
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
  
  if (XMLString::equals(nameX, XAIFStrings.elem_VarRef_x())) {

    // -------------------------------------------------------
    // base case: VariableReference
    // -------------------------------------------------------
    elem = GetFirstChildElement(elem); // skip the xaif:VariableReference node
    ctxt.CreateContext(XlationContext::NOFLAG);
    WN* wn = TranslateVarRef(elem, ctxt);
    ctxt.DeleteContext();
    return wn;

  } else if (XMLString::equals(nameX, XAIFStrings.elem_Constant_x())) {

    // -------------------------------------------------------
    // base case: Constant
    // -------------------------------------------------------
    return xlate_Constant(elem, ctxt);

  } else if (XMLString::equals(nameX, XAIFStrings.elem_Intrinsic_x())) {
    
    // -------------------------------------------------------
    // recursive case: Intrinsic
    // -------------------------------------------------------
    const XMLCh* nmX = elem->getAttribute(XAIFStrings.attr_name_x());
    XercesStrX nm = XercesStrX(nmX);
    
    UINT opnd_num = GetIntrinsicOperandNum(nm.c_str());
    OPERATOR op = GetIntrinsicOperator(nm.c_str());
    
    // Gather operands for intrinsic 
    // (FIXME: this needs to be sorted by position)
    ASSERT_FATAL(n->num_incoming() == opnd_num, 
		 (DIAG_A_STRING, "Programming error."));
    std::vector<MyDGNode*> opnd(opnd_num); 

    DGraph::IncomingEdgesIterator it = DGraph::IncomingEdgesIterator(n);
    for (int i = 0; (bool)it; ++it, ++i) {
      DGraph::Edge* edge = (DGraph::Edge*)it;
      opnd[i] = dynamic_cast<MyDGNode*>(edge->source());
    }

    // Translate each operand into a WHIRL expression tree
    std::vector<WN*> opnd_wn(opnd_num); 
    for (int i = 0; i < opnd_num; ++i) {
      opnd_wn[i] = xlate_Expression(g, opnd[i], ctxt);
    }

    // Create a WHIRL expression tree for the operator and operands
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

  } else if (XMLString::equals(nameX, XAIFStrings.elem_FuncCall_x())) {

    // -------------------------------------------------------
    // recursive case: FunctionCall
    // -------------------------------------------------------
    // children are expressions
    // find number of arguments
    assert(false && "Please implement me"); 
    return NULL; // FIXME

  } else if (XMLString::equals(nameX, XAIFStrings.elem_BoolOp_x())) {

    // -------------------------------------------------------
    // recursive case: BooleanOperation
    // -------------------------------------------------------
    // children are expressions
    assert(false && "Please implement me");
    return NULL; // FIXME
  } else {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Unknown Expression element"));
  }
  
}


// TranslateVarRef: Given the first node in a variable reference
// graph, create a variable reference.
//
// If the LVALUE flag of 'ctxt' is set an address expression (lvalue)
// is returned; otherwise a rvalue is returned.  If the VARREF flag of
// 'ctxt' is already set, no value-selector is created.
WN*
xaif2whirl::TranslateVarRef(DOMElement* elem, XlationContext& ctxt)
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
  
  // If we are not already within another VarRef, select the value portion
  if (!ctxt.IsVarRef()) {
    wn = CreateValueSelector(wn);
  }  
  
  return wn;
}

static WN*
xlate_VarRef(DGraph* g, MyDGNode* n, XlationContext& ctxt)
{
  // Recursively translate the DAG (tree) rooted at this node
  DOMElement* elem = n->GetElem();
  ASSERT_FATAL(elem, (DIAG_A_STRING, "Programming error."));

  WN* wn = NULL;  

  const XMLCh* nameX = elem->getNodeName();
  if (XMLString::equals(nameX, XAIFStrings.elem_SymRef_x())) {

    // -------------------------------------------------------
    // base case: SymbolReference
    // -------------------------------------------------------    
    ST* st = GetST(elem, ctxt);
    
    if (ctxt.IsLValue()) {
      wn = WN_CreateLda(OPR_LDA, Pointer_Mtype, MTYPE_V, 0, 
			TY_pointer(ST_type(st)), st, 0);
    } else {
      // FIXME
      wn = WN_CreateLdid(OPC_F8F8LDID, 0, st, MTYPE_To_TY(MTYPE_F8));
    }

  } else if (XMLString::equals(nameX, XAIFStrings.elem_ArrayElemRef_x())) {
    
    // -------------------------------------------------------
    // recursive case: ArrayElementReference
    // -------------------------------------------------------    

    // 1. Translate the index expression for each dimension
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
    
    // 2. Translate the array symbol reference
    ASSERT_FATAL(n->num_incoming() == 1,
		 (DIAG_A_STRING, "Programming error."));
    DGraph::IncomingEdgesIterator it = DGraph::IncomingEdgesIterator(n);
    DGraph::Edge* edge = (DGraph::Edge*)it;

    MyDGNode* n1 = dynamic_cast<MyDGNode*>(edge->source());
    const XMLCh* nmX = n1->GetElem()->getNodeName();
    ASSERT_FATAL(XMLString::equals(nmX, XAIFStrings.elem_SymRef_x()),
		 (DIAG_A_STRING, "Programming error."));
    
    ctxt.CreateContext(XlationContext::LVALUE);
    WN* arraySym = xlate_VarRef(g, n1, ctxt);
    ctxt.DeleteContext();

    ST* st = WN_st(arraySym);
    TY_IDX ty = ST_type(st); // array type
    if (TY_kind(ty) == KIND_POINTER) { 
      ty = TY_pointed(ty); 
    }
    ASSERT_FATAL(TY_AR_ndims(ty) == rank,
		 (DIAG_A_STRING, "Programming error."));
    
    // 3. Create Whirl ARRAY node (cf. wn_fio.cxx:7056)
    UINT nkids = (rank * 2) + 1; // 2n + 1 where (where n == rank)
    WN* array = WN_Create(OPC_U8ARRAY, nkids);
    
    // kid 0 is the array's base address
    WN_kid0(array) = arraySym;
    
    // kids 1 to n give size of each dimension.  We use a bogus value,
    // since we only need to support translation back to source code.
    for (int i = 1; i <= rank; ++i) {
      WN_kid(array, i) = NULL;
    }
    
    // kids n + 1 to 2n give index expressions for each dimension
    for (int i = rank + 1, j = 0; i <= 2*rank; ++i, ++j) {
      WN_kid(array, i) = indices[j];
    }
    
    wn = array;
    
  } else {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Unknown Variable Reference element"));
  }
  
  return wn;
}


static WN*
xlate_Constant(DOMElement* elem, XlationContext& ctxt)
{
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

    UINT val = strtol(value.c_str(), (char **)NULL, 10);    
    TCON tcon = Host_To_Targ_Float(MTYPE_F8, (double)val);
    wn = Make_Const(tcon); // FIXME: only works for float
    //wn = WN_CreateIntconst(OPC_I8INTCONST, (INT64)val); 

  } else if (strcmp(type.c_str(), "bool") == 0) {
    assert(false); // FIXME
  } else if (strcmp(type.c_str(), "char") == 0) {
    assert(false); // FIXME
  } else if (strcmp(type.c_str(), "string") == 0) {

    UINT32 len = strlen(value.c_str());
    TCON tcon = Host_To_Targ_String(MTYPE_STR, (char*)value.c_str(), len);
    wn = Make_Const(tcon);

  }

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
CreateExpressionGraph(DOMNode* node, bool varRef)
{
  DGraph* g = new DGraph;
  IdToNodeMap m;

  // Setup variables
  XMLCh* edgeStr = NULL, *positionStr = NULL;
  if (varRef) {
    edgeStr = XAIFStrings.elem_VarRefEdge_x();
    // No position for variable references
  } else {
    edgeStr = XAIFStrings.elem_ExprEdge_x();
    positionStr = XAIFStrings.attr_position_x();
  }
  
  // -------------------------------------------------------
  // Create the graph
  // -------------------------------------------------------
  DOMNode* n = node; 
  do {
    // Only examine element nodes
    if (n->getNodeType() != DOMNode::ELEMENT_NODE) { continue; }
    
    DOMElement* e = dynamic_cast<DOMElement*>(n);
    
    const XMLCh* name = e->getNodeName();
    if (XMLString::equals(name, edgeStr)) {
      // Add an edge to the graph
      
      // Find src and target (sink) nodes
      const XMLCh* srcX = e->getAttribute(XAIFStrings.attr_source_x());
      const XMLCh* targX = e->getAttribute(XAIFStrings.attr_target_x());
      XercesStrX src = XercesStrX(srcX);
      XercesStrX targ = XercesStrX(targX);

      if (positionStr) {
	// FIXME: how best to deal with 'position'?
	// we need to sort the edges by position
      }

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
    
  } while ( (n = n->getNextSibling()) );
  
  
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

static WN*
CreateValueSelector(WN* wn)
{
  // Select the value portion of 'wn', by wrapping a function call around it
  TY_IDX fty = Make_Function_Type(MTYPE_To_TY(MTYPE_F8));
  ST* fst = Gen_Intrinsic_Function(fty, "__value__"); // create if non-existant
  
  WN* callWN = WN_Call(MTYPE_F8, MTYPE_V, 1, fst);
  WN_Set_Call_Default_Flags(callWN);
  
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

