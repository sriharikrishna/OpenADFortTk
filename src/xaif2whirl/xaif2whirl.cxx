// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.cxx,v 1.5 2003/08/13 22:58:53 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.cxx,v $
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
#include <xercesc/dom/DOMNodeList.hpp> // FIXME (do we still need this?)

//*************************** User Include Files ****************************

#include "xaif2whirl.h"
#include "XlationContext.h"
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

static void
TranslateCallGraph(PU_Info* pu_forest, DOMDocument* doc, XlationContext& ctxt);

static XAIFSymToWhirlSymMap*
TranslateScopeHierarchy(DOMDocument* doc, XlationContext& ctxt);

static void
TranslateCFG(PU_Info* pu_forest, DOMElement* cfgElem, XlationContext& ctxt);

static void
TranslateCFG(WN *wn_pu, DOMElement* cfgElem, XlationContext& ctxt);

static void
TranslateBB(WN *wn_pu, DOMElement* bbElem, XlationContext& ctxt);

//*************************** Forward Declarations ***************************

static WN* 
TranslateStmt(DOMElement* stmt, XlationContext& ctxt); 

//*************************** Forward Declarations ***************************

static PU_Info*
FindPUForCFG(PU_Info* pu_forest, const char* name, 
	     const char* scopeIdStr, const char* symIdStr);

static bool
FindNextStmtInterval(WN* &firstWN, WN* &lastWN, 
		     DOMElement* bbElem, XlationContext& ctxt);

static WN*
FindIntervalBoundary(DOMElement* elem, WNIdList* idlist, WNIdToWNMap* wnmap, 
		     int boundary);

static WN* 
FindParentWNBlock(WN* wn_tree, WN* wn);

static WN* 
FindSafeInsertionPoint(WN* blckWN, WN* stmtWN);

static WNIdList*
GetWNIdList(DOMElement* elem);

static WNIdList*
GetWNIdList(const char* idstr);

//****************************************************************************

static void
xlate_Scope(DOMElement* elem, XAIFSymToWhirlSymMap* symMap, 
	    XlationContext& ctxt);

//****************************************************************************

UINT 
GetIntrinsicOperandNum(const char* name);

OPERATOR 
GetIntrinsicOperator(const char* name);

//****************************************************************************

// FIXME: used with CreateExpressionGraph
typedef std::map<std::string, DGraph::Node*> IdToNodeMap;

class MyDGNode : public DGraph::Node {
public:
  MyDGNode(DOMElement* e_) : e(e_) { }
  virtual ~MyDGNode() { }

  DOMElement* GetElem() { return e; }
  
private:
  DOMElement* e;
};

//****************************************************************************

// TranslateIR: 
void
xaif2whirl::TranslateIR(PU_Info* pu_forest, DOMDocument* doc)
{
  Diag_Set_Phase("WHIRL to XAIF: translate IR");
  
  if (!pu_forest) { return; }
  
  XlationContext ctxt;

  TranslateCallGraph(pu_forest, doc, ctxt);
}


// TranslateCallGraph: 
static void
TranslateCallGraph(PU_Info* pu_forest, DOMDocument* doc, XlationContext& ctxt)
{
  // FIXME: Do something about the ScopeHeirarchy
  PUIdToPUMap* pumap = CreatePUIdMaps(pu_forest);
  ctxt.SetIdToPUMap(pumap);

  XAIFSymToWhirlSymMap* symmap = TranslateScopeHierarchy(doc, ctxt);
  ctxt.SetXAIFSymToWhirlSymMap(symmap);
  
  // -------------------------------------------------------
  // Translate each ControlFlowGraph in the CallGraph
  // -------------------------------------------------------
  DOMNodeIterator* it = 
    doc->createNodeIterator(doc, DOMNodeFilter::SHOW_ALL, 
			    new XAIF_CFGElemFilter(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* elem = dynamic_cast<DOMElement*>(node);

    TranslateCFG(pu_forest, elem, ctxt);
  }
  it->release();
  
  delete pumap;
  delete symmap;
}


// TranslateScopeHierarchy: 
static XAIFSymToWhirlSymMap*
TranslateScopeHierarchy(DOMDocument* doc, XlationContext& ctxt)
{
  XAIFSymToWhirlSymMap* symMap = new XAIFSymToWhirlSymMap;

  // -------------------------------------------------------
  // Enter symbols for all Scopes in the ScopeHierarchy
  // -------------------------------------------------------
  DOMNodeIterator* it = 
    doc->createNodeIterator(doc, DOMNodeFilter::SHOW_ALL, 
			    new XAIF_ScopeElemFilter(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* elem = dynamic_cast<DOMElement*>(node);
    xlate_Scope(elem, symMap, ctxt);
  }
  it->release();
  
  return symMap;
}


// TranslateCFG: 
static void
TranslateCFG(PU_Info* pu_forest, DOMElement* cfgElem, XlationContext& ctxt)
{
  //FIXME: 
  const XMLCh* nameX = cfgElem->getAttribute(XAIFStrings.attr_annot_x());
  const XMLCh* scopeIdX = cfgElem->getAttribute(XAIFStrings.attr_scopeId_x());
  const XMLCh* symIdX = cfgElem->getAttribute(XAIFStrings.attr_symId_x());
  
  XercesStrX name = XercesStrX(nameX);
  XercesStrX scopeId = XercesStrX(scopeIdX);
  XercesStrX symId = XercesStrX(symIdX);

  cout << XercesStrX(cfgElem->getNodeName()) << ": " << name 
       << " // " << scopeId << ", " << symId << endl;

  // -------------------------------------------------------
  // Try to find the matching PU; if so, translate XAIF CFG to WHIRL PU.
  // -------------------------------------------------------
  PU_Info* pu = FindPUForCFG(pu_forest, name.c_str(), scopeId.c_str(),
			     symId.c_str());
  if (!pu) { return; }


  // If we found the PU, translate
  RestoreOpen64PUGlobalVars(pu);

  WN *wn_pu = PU_Info_tree_ptr(pu);
  TranslateCFG(wn_pu, cfgElem, ctxt);

  SaveOpen64PUGlobalVars(pu);
}


// TranslateCFG: Given an XAIF CFG rooted at 'cfgElem' and its
// corresponding WHIRL tree 'wn_pu', modify the WHIRL to reflect the
// XAIF.
static void
TranslateCFG(WN *wn_pu, DOMElement* cfgElem, XlationContext& ctxt)
{
  pair<WNIdToWNMap*, WNToWNIdMap*> wnmaps = CreateWhirlIdMaps(wn_pu);
  ctxt.SetIdToWNMap(wnmaps.first);
  ctxt.SetWNToIdMap(wnmaps.second);
  
  // -------------------------------------------------------
  // Translate each BasicBlock in the CFG
  // -------------------------------------------------------
  DOMDocument* doc = cfgElem->getOwnerDocument();
  DOMNodeIterator* it = 
    doc->createNodeIterator(cfgElem, DOMNodeFilter::SHOW_ALL, 
			    new XAIF_BBElemFilter(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* elem = dynamic_cast<DOMElement*>(node);
    TranslateBB(wn_pu, elem, ctxt);
  }
  it->release();

  IR_set_dump_order(TRUE); /* dump parent before children*/
  fprintf(stderr, "\n----------------------------------------------------\n");
  fdump_tree(stderr, wn_pu);

  delete wnmaps.first;
  delete wnmaps.second;
}


// TranslateBB: 
static void
TranslateBB(WN *wn_pu, DOMElement* bbElem, XlationContext& ctxt)
{
  WN* firstWN = NULL, *lastWN = NULL;
  while ( FindNextStmtInterval(firstWN, lastWN, bbElem, ctxt) ) {

    // We now have an *inclusive* interval [firstWN, lastWN] of
    // statements thatw will be replaced with new statements.

    // 1a. Find the parent BLOCK (for use later)
    WN* blckWN = FindParentWNBlock(wn_pu, firstWN);

    // 1b. Find (or create) a statement just prior to the interval to
    // serve as an insertion point.
    WN* ipWN = FindSafeInsertionPoint(blckWN, firstWN);
    
    // 2. Delete all statements in the interval
    for (WN* stmtWN = firstWN; 
	 (stmtWN); 
	 stmtWN = (stmtWN == lastWN) ? NULL : WN_next(stmtWN)) {
      WN_DELETE_FromBlock(blckWN, stmtWN);
    }
    
    // 3. For each new statement, create a WHIRL node and insert it
    DOMDocument* doc = bbElem->getOwnerDocument();
    DOMNodeIterator* it = 
      doc->createNodeIterator(bbElem, DOMNodeFilter::SHOW_ALL, 
			      new XAIF_BBStmtElemFilter(), true);
    for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
      DOMElement* stmtXAIF = dynamic_cast<DOMElement*>(node);
      
      WN* stmtWN = TranslateStmt(stmtXAIF, ctxt);
      if (stmtWN) {
	WN_INSERT_BlockAfter(blckWN, ipWN, stmtWN);
	ipWN = stmtWN; // update the insertion point
      }
    }
    it->release();
  }
}

//****************************************************************************

// FIXME: This should use PU ID!!

// FindPUForCFG: Find the PU in 'pu_forest' that matches the name and
// scope/symbol ids.  If name is non-empty, the scopeId and symId
// should be non-empty.
static PU_Info*
FindPUForCFG(PU_Info* pu_forest, const char* name, 
	     const char* scopeIdStr, const char* symIdStr)
{
  if (!name || name[0] == '\0'
      || !scopeIdStr || scopeIdStr[0] == '\0'
      || !symIdStr || symIdStr == '\0') {
    return NULL;
  }

  unsigned long symId = strtol(symIdStr, (char **)NULL, 10);
  
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();
    ST* st = ST_ptr(PU_Info_proc_sym(pu));
    
    if (symId == ST_index(st) && strcmp(name, ST_name(st)) == 0) {
      return pu;
    }
  }
  
  return NULL;
}


// FindNextStmtInterval: Finds intervals of WHIRL-tagged-Nops within
// the XAIF BB 'bbElem'.  Sets the WHIRL nodes 'firstWN' and 'lastWN'
// to the WN corresponding to the first statement *after* the
// beginning xaif:Nop or *before* the last xaif:Nop, respectively.  If
// explicit intervals are not formed by xaif:Nops, implicit Nops are
// assumed to exist.
static bool
FindNextStmtInterval(WN* &firstWN, WN* &lastWN, 
		     DOMElement* bbElem, XlationContext& ctxt) 
{
  // FIXME: For the time being we assume there can only be one interval!
  bool firstInterval = (firstWN) ? false : true;
  if (!firstInterval) { return false; }
  
  WNIdToWNMap* wnmap = ctxt.GetIdToWNMap();
  
  // 1. Find the set of WHIRL nodes in this BB
  WNIdList* idlist = GetWNIdList(bbElem);
  
  // 2. Find the interval boundaries
  DOMElement* firstE = GetFirstChildElement(bbElem);
  firstWN = FindIntervalBoundary(firstE, idlist, wnmap, 0 /* beg */);
  
  DOMElement* lastE = GetLastChildElement(bbElem);
  lastWN = FindIntervalBoundary(lastE, idlist, wnmap, 1 /* end */);
  
  // 3. Cleanup
  delete idlist;
  
  return ((firstWN != NULL) && (lastWN != NULL));
}


// FindIntervalBoundary: Finds the appropriate WN* for the given
// interval boundary statement 'elem' and boundary type (begin/end). 
// If the interval boundary statement is an xaif:Nop, return the WN
// immediate after/before it for boundary type begin/end,
// respectively.  Otherwise, use 'idlist' and 'wnmap' to return the
// appropriate WN.  If NULL is returned, this is a null interval.
// 
// boundary: 0 (begin), 1 (end)
static WN*
FindIntervalBoundary(DOMElement* elem, WNIdList* bbIdList, WNIdToWNMap* wnmap, 
		     int boundary)
{
  if (!elem) {
    return NULL;
  }

  bool found = false;
  WNIdList* idlist = GetWNIdList(elem);
  WN* wn = NULL;
  
  // If the stmt is a WHIRLID-Nop, find the WN from it
  if (XAIF_BBStmtElemFilter::IsNop(elem)) {
    if (idlist->size() == 1) {
      wn = wnmap->Find(idlist->front());
      assert(wn);
      
      // move one stmt after or before this
      if (boundary == 0) {
	wn = WN_next(wn); // may become NULL
      } else {
	wn = WN_prev(wn); // may become NULL
      }
      
      found = true; // found an interval (null or non-NULL)
    }
  } 
  
  // Otherwise, use the first or last BB WHIRLID.
  if (!found && bbIdList->size() > 0) {
    if (boundary == 0) {
      wn = wnmap->Find(bbIdList->front());
    } else if (boundary == 1) {
      wn = wnmap->Find(bbIdList->back());
    }
    found = true; // found a non-NULL interval
    assert(wn);
  }
  
  delete idlist;
  return wn;
}


// FindParentWNBlock: Given two WHIRL nodes, a subtree 'wn_tree' and an
// some descendent 'wn', return the BLOCK WN that contains 'wn', or
// NULL.
// 
// FIXME: I can't see a better way of doing this since we don't have
// parent pointers.
static WN* 
FindParentWNBlock(WN* wn_tree, WN* wn)
{
  WN* blckWN = NULL;
  bool found = false;

  WN_TREE_CONTAINER<PRE_ORDER> wtree(wn_tree);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  for (it = wtree.begin(); it != wtree.end(); ++it) {
    WN* curWN = it.Wn();
    
    if (WN_operator(curWN) == OPR_BLOCK) { blckWN = curWN; }
    if (curWN == wn) { 
      found = true; 
      break;
    }
  }

  return ( (found) ? blckWN : NULL );
}


// FindSafeInsertionPoint: Given a WHIRL statement node 'stmtWN' and
// its containing block 'blckWN', find (or create) the statement just
// prior to 'stmtWN'.
static WN* 
FindSafeInsertionPoint(WN* blckWN, WN* stmtWN)
{
  WN* ipWN = NULL;

  // 1. Just return the previous statement, if available
  if ( (ipWN = WN_prev(stmtWN)) != NULL ) {
    return ipWN;
  }

  // 2. There is no previous statement so we insert a dummy stmt to
  // serve as a handle.  The compiler will be able to optimize this
  // away later.
  ipWN = WN_CreateAssert(0, WN_CreateIntconst(OPC_I4INTCONST, (INT64)1));
  WN_INSERT_BlockBefore(blckWN, stmtWN, ipWN);
  return ipWN;
}


// GetPUId: Returns the PUId attached to the node FIXME
static PUId
GetPUId(DOMElement* elem)
{
  // FIXME: we need to use real scope tags
  const XMLCh* attrX = elem->getAttribute(XAIFStrings.attr_Vid_x());
  XercesStrX attr = XercesStrX(attrX);
  
  PUId id = strtol(attr.c_str(), (char **)NULL, 10);
  return id;
}


// GetWNIdList: Returns a list of any WHIRLIDs attached to the
// annotation attribute.
//
// The returned list may be empty; the caller is responsible for
// freeing returned memory.
static WNIdList*
GetWNIdList(DOMElement* elem)
{
  const XMLCh* annot = elem->getAttribute(XAIFStrings.attr_annot_x());
  XercesStrX annotStr = XercesStrX(annot);
  WNIdList* idlist = GetWNIdList(annotStr.c_str());
  return idlist;
}


// GetWNIdList: Converts the ids in the string 'idstr' into a list of
// 'WNId'.
//
// The returned list may be empty; the caller is responsible for
// freeing returned memory.
static WNIdList*
GetWNIdList(const char* idstr)
{
  WNIdList* idlist = new WNIdList;

  if (!idstr) { return idlist; }
  
  // Find the tag indicating presence of list
  const char* start = strstr(idstr, XAIFStrings.tag_IRIds());
  if (!start) { return idlist; }
  start += strlen(XAIFStrings.tag_IRIds()); // move pointer past tag
  
  // Parse the colon separated id list
  char* tok = strtok(const_cast<char*>(start), ":");
  while (tok != NULL) {
    
    WNId id = strtol(tok, (char **)NULL, 10);
    idlist->push_back(id);
    
    tok = strtok((char*)NULL, ":");
  }

  return idlist;
}

//****************************************************************************


static WN* 
xlate_Assignment(DOMElement* elem, XlationContext& ctxt);

static WN* 
xlate_SubroutineCall(DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_AssignmentLHS(DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_AssignmentRHS(DOMElement* elem, XlationContext& ctxt);


static WN*
TranslateExpression(DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_Expression(DGraph* g, MyDGNode* n, XlationContext& ctxt);

static WN*
xlate_VarRef(DOMElement* elem, XlationContext& ctxt, bool lvalue);

static WN*
xlate_Constant(DOMElement* elem, XlationContext& ctxt);



static ST*
GetST(DOMElement* elem, XlationContext& ctxt);

DGraph* 
CreateExpressionGraph(DOMNode* node);



static WN* 
TranslateStmt(DOMElement* stmt, XlationContext& ctxt)
{
  WN* wn = NULL;
  
  const XMLCh* name = stmt->getNodeName();
  if (XMLString::equals(name, XAIFStrings.elem_Assign_x())) {
    wn = xlate_Assignment(stmt, ctxt);
  } else if (XMLString::equals(name, XAIFStrings.elem_SubCall_x())) {
    wn = xlate_SubroutineCall(stmt, ctxt);
  } else if (XMLString::equals(name, XAIFStrings.elem_Nop_x())) {
    // nothing
  } else {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  return wn;
}


static WN* 
xlate_Assignment(DOMElement* elem, XlationContext& ctxt)
{
  WN* lhs = xlate_AssignmentLHS(GetFirstChildElement(elem), ctxt);
  WN* rhs = xlate_AssignmentRHS(GetLastChildElement(elem), ctxt);

  // FIXME: ISTORE: should we try to select btwn STID and ISTORE, etc?
  // FIXME: first argument is bogus // WN_Tree_Type(rhs)
  WN* wn = WN_Istore(MTYPE_F8, 0, MTYPE_To_TY(MTYPE_F8), lhs, rhs, 0);

  //WN* wn = WN_CreateAssert(0, WN_CreateIntconst(OPC_I4INTCONST, (INT64)1));
  return wn;
}

static WN* 
xlate_SubroutineCall(DOMElement* elem, XlationContext& ctxt)
{
  WN* wn = WN_CreateAssert(0, WN_CreateIntconst(OPC_I4INTCONST, (INT64)1));
  return wn;
}

static WN*
xlate_AssignmentLHS(DOMElement* elem, XlationContext& ctxt)
{
  // VariableReferenceType
  WN* wn = xlate_VarRef(GetFirstChildElement(elem), ctxt, true);
  return wn;
}

static WN*
xlate_AssignmentRHS(DOMElement* elem, XlationContext& ctxt)
{
  // ExpressionType
  WN* wn = TranslateExpression(GetFirstChildElement(elem), ctxt);
  return wn;
}

// TranslateExpression: Given the first node in an expression graph... 
static WN*
TranslateExpression(DOMElement* elem, XlationContext& ctxt)
{
  // Slurp expression into a graph (DAG)
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
  assert(elem); // FIXME
  
  const XMLCh* nameX = elem->getNodeName();
  XercesStrX name = XercesStrX(nameX); // FIXME
  
  if (XMLString::equals(nameX, XAIFStrings.elem_VarRef_x())) {

    // -------------------------------------------------------
    // base case: variable reference
    // -------------------------------------------------------
    return xlate_VarRef(elem, ctxt, false);

  } else if (XMLString::equals(nameX, XAIFStrings.elem_Constant_x())) {

    // -------------------------------------------------------
    // base case: constant
    // -------------------------------------------------------
    return xlate_Constant(elem, ctxt);

  } else if (XMLString::equals(nameX, XAIFStrings.elem_Intrinsic_x())) {
    
    // -------------------------------------------------------
    // recursive case: intrinsic
    // -------------------------------------------------------
    const XMLCh* nmX = elem->getAttribute(XAIFStrings.attr_name_x());
    XercesStrX nm = XercesStrX(nmX);
    
    UINT opand = GetIntrinsicOperandNum(nm.c_str());
    OPERATOR opor = GetIntrinsicOperator(nm.c_str());
    
    switch (opand) {
      // unary
    case 1: {
      // WN *WN_Unary(OPERATOR opr,TYPE_ID rtype,WN *l);
      assert(false); 
      return NULL;
    }
      
      // binary
    case 2: {
      assert(n->num_incoming() == 2); // FIXME

      MyDGNode* nexpr[2]; 
      DGraph::IncomingEdgesIterator it = DGraph::IncomingEdgesIterator(n);
      for (int i = 0; (bool)it; ++it, ++i) {
	DGraph::Edge* edge = (DGraph::Edge*)it;
	nexpr[i] = dynamic_cast<MyDGNode*>(edge->source());
      }
      
      WN* e1 = xlate_Expression(g, nexpr[0], ctxt);
      WN* e2 = xlate_Expression(g, nexpr[1], ctxt);
      return WN_Binary(opor, MTYPE_F8, e1, e2);
      // FIXME is this the correct return type
    }
      
      // ternary
    case 3: {
      // WN *WN_Ternary(OPERATOR opr, TYPE_ID rtype,WN *kid0,WN *kid1,WN *kid2)
      assert(false); 
      return NULL;
    }
      
    default:
      assert(false);
    } 

  } else if (XMLString::equals(nameX, XAIFStrings.elem_FuncCall_x())) {

    // -------------------------------------------------------
    // recursive case: function call
    // -------------------------------------------------------
    // children are expressions
    // find number of arguments
    return NULL;

  } else if (XMLString::equals(nameX, XAIFStrings.elem_BoolOp_x())) {

    // -------------------------------------------------------
    // recursive case: boolean operation
    // -------------------------------------------------------
    // children are expressions
    return NULL;
  }
  
}


// FIXME the third argument should be a part of 'ctxt'
static WN*
xlate_VarRef(DOMElement* elem, XlationContext& ctxt, bool lvalue)
{
  if (!lvalue) {
    // skip the xaif:VariableReference node
    elem = GetFirstChildElement(elem);
  }
  
  const XMLCh* name = elem->getNodeName();
  //XercesStrX nameStr = XercesStrX(name);
  assert(XMLString::equals(name, XAIFStrings.elem_SymRef_x()));
  
  ST* st = GetST(elem, ctxt);

  WN* wn = NULL;
  if (lvalue) {
    // FIXME
    //wn = WN_CreateLda(OPC_F8LDA, 0, TY_pointer(ST_type(st)), st);
    wn = WN_CreateLda(OPR_LDA, Pointer_Mtype, MTYPE_V, 0, 
		      TY_pointer(ST_type(st)), st, 0);
  } else {
    // FIXME
    wn = WN_CreateLdid(OPC_F8F8LDID, 0, st, MTYPE_To_TY(MTYPE_F8));
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
  
  assert(strcmp(type.c_str(), "integer") == 0); // FIXME: ints for now
  
  UINT val = strtol(value.c_str(), (char **)NULL, 10);
  
  WN* wn = WN_CreateIntconst(OPC_I4INTCONST, (INT64)val); // int4?
  return wn;
}



static ST*
GetST(DOMElement* elem, XlationContext& ctxt)
{
  const XMLCh* scopeIdX = elem->getAttribute(XAIFStrings.attr_scopeId_x());
  const XMLCh* symIdX = elem->getAttribute(XAIFStrings.attr_symId_x());

  XercesStrX scopeId = XercesStrX(scopeIdX);
  XercesStrX symId = XercesStrX(symIdX);

  assert(strcmp(scopeId.c_str(), "") != 0);
  assert(strcmp(symId.c_str(), "") != 0);

  return ctxt.FindSym(scopeId.c_str(), symId.c_str());
}

//****************************************************************************


// CreateExpressionGraph: Given the first element in an XAIF
// expression graph, returns a DGraph where where graph nodes point to
// nodes in the DOM tree.  When walking from root to children, one
// descends incoming edges.
DGraph* 
CreateExpressionGraph(DOMNode* node)
{
  DGraph* g = new DGraph;
  IdToNodeMap m;
  
  // FIXME: for now we assume the root node is the FIRST node
  // Root: no outgoing vertices

  DOMNode* n = node; 
  do {
    // Only examine element node
    if (n->getNodeType() != DOMNode::ELEMENT_NODE) { continue; }
    
    DOMElement* e = dynamic_cast<DOMElement*>(n);
    
    const XMLCh* name = e->getNodeName();
    if (XMLString::equals(name, XAIFStrings.elem_ExprEdge_x())) {
      // Add an edge to the graph
      
      // Find src and target (sink) nodes
      const XMLCh* srcX = e->getAttribute(XAIFStrings.attr_source_x());
      const XMLCh* targX = e->getAttribute(XAIFStrings.attr_target_x());
      XercesStrX src = XercesStrX(srcX);
      XercesStrX targ = XercesStrX(targX);
      // FIXME: how best to deal with 'position' 
      // we need to sort the edges by position

      MyDGNode* gn1 = NULL, *gn2 = NULL; // src and targ
      
      IdToNodeMap::iterator it = m.find(std::string(src.c_str()));
      if (it != m.end()) { 
	gn1 = dynamic_cast<MyDGNode*>((*it).second); 
      }
      
      it = m.find(std::string(targ.c_str()));
      if (it != m.end()) { 
	gn2 = dynamic_cast<MyDGNode*>((*it).second); 
      }
      
      assert(gn1 && gn2); // FIXME
      
      DGraph::Edge* ge = new DGraph::Edge(gn1, gn2);
      g->add(ge);
      
    } else {
      // Add a vertex to the graph
      const XMLCh* vidX = e->getAttribute(XAIFStrings.attr_Vid_x());
      XercesStrX vid = XercesStrX(vidX);
      
      MyDGNode* gn = new MyDGNode(e);
      g->add(gn);
      m.insert(make_pair(std::string(vid.c_str()), gn));
    }
    
  } while ( (n = n->getNextSibling()) );
  
  return g;
}

//****************************************************************************

static void
xlate_SymbolTable(DOMElement* STElem, const char* scopeId, PU_Info* pu, 
		  XAIFSymToWhirlSymMap* symMap);

static void
xlate_Symbol(DOMElement* elem, const char* scopeId, PU_Info* pu, 
	     XAIFSymToWhirlSymMap* symMap);


static void
xlate_Scope(DOMElement* elem, XAIFSymToWhirlSymMap* symMap, 
	    XlationContext& ctxt)
{
  // FIXME: 
  // Find the corresponding WHIRL scope (only PUs for now)
  // Currently, scopes may refer to either the global scope (id = 1)
  // or PUs (id > 1). 
  PUId id = GetPUId(elem);
  PU_Info* pu = NULL;
  if (id > 1) {
    pu = ctxt.FindPU(id);
  }
  
  // FIXME
  const XMLCh* scopeIdX = elem->getAttribute(XAIFStrings.attr_Vid_x());
  XercesStrX scopeId = XercesStrX(scopeIdX);

  // Translate the xaif:SymbolTable (the only child)
  DOMElement* symtabElem = GetFirstChildElement(elem);
  xlate_SymbolTable(symtabElem, scopeId.c_str(), pu, symMap); 
}  

static void
xlate_SymbolTable(DOMElement* STElem, const char* scopeId, PU_Info* pu, 
		  XAIFSymToWhirlSymMap* symMap)
{
  // For all xaif:Symbol in the xaif:SymbolTable

  DOMDocument* doc = STElem->getOwnerDocument();
  DOMNodeIterator* it = 
    doc->createNodeIterator(STElem, DOMNodeFilter::SHOW_ALL, 
			    new XAIF_SymbolElemFilter(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* elem = dynamic_cast<DOMElement*>(node);
    xlate_Symbol(elem, scopeId, pu, symMap);
  }
  it->release();

}

// FIXME: only handles global and PU scopes
static void
xlate_Symbol(DOMElement* elem, const char* scopeId, PU_Info* pu, 
	     XAIFSymToWhirlSymMap* symMap)
{
  // 1. Initialize
  SYMTAB_IDX level = GLOBAL_SYMTAB; // Default: assume a global symbol
  if (pu) {
    // This is a PU-scoped symbol.  Restore local symbol tables
    RestoreOpen64PUGlobalVars(pu);
    level = CURRENT_SYMTAB; // PU_lexical_level
  }

  // 2. Find or Create symbol
  ST* st = NULL;

  const XMLCh* symIdX = elem->getAttribute(XAIFStrings.attr_symId_x());
  XercesStrX symId = XercesStrX(symIdX);
  static const char* tag = "SymbolTable_";//FIXME: add explicit ST tag
  
  if (strncmp(symId.c_str(), tag, strlen(tag)) == 0) {
    // Create the symbol
    st = New_ST(level);
    //string symstr = symId.c_str();
    
    const XMLCh* kindX = elem->getAttribute(XAIFStrings.attr_kind_x());
    const XMLCh* typeX = elem->getAttribute(XAIFStrings.attr_type_x());
    const XMLCh* shapeX = elem->getAttribute(XAIFStrings.attr_shape_x());

    XercesStrX kind = XercesStrX(kindX);
    XercesStrX type = XercesStrX(typeX);
    XercesStrX shape = XercesStrX(shapeX);
    
    assert( strcmp(kind.c_str(), "variable" ) == 0 ); // FIXME: assume only
    assert( strcmp(type.c_str(), "double" ) == 0 );   // scalar, doubles
    assert( strcmp(shape.c_str(), "scalar" ) == 0 );
    
    ST_Init(st, Save_Str(symId.c_str()), CLASS_VAR, SCLASS_AUTO, EXPORT_LOCAL,
	    MTYPE_To_TY(MTYPE_F8));
    
  } else {
    // Find the symbol
    UINT32 idx = strtol(symId.c_str(), (char **)NULL, 10);
    assert(idx != 0);
    st = &(Scope_tab[level].st_tab->Entry(idx));
  }
  
  // 3. Add the symbol to the map
  symMap->Insert(scopeId, symId.c_str(), st);
  
  // 4. Finalize
  if (pu) {
    SaveOpen64PUGlobalVars(pu);
  }
} 

//****************************************************************************

UINT 
GetIntrinsicOperandNum(const char* name)
{
  if (!name) { return 0; }
  
  if (strcmp(name, "mul_scal_scal") == 0) {
    return 2;
  } else if (strcmp(name, "add_scal_scal") == 0) {
    return 2;
  } else {
    assert(0); //FIXME
    return 0;
  }
}

OPERATOR 
GetIntrinsicOperator(const char* name)
{
  if (!name) { return OPERATOR_UNKNOWN; }
  
  if (strcmp(name, "mul_scal_scal") == 0) {
    return OPR_MPY;
  } else if (strcmp(name, "add_scal_scal") == 0) {
    return OPR_ADD;
  } else {
    assert(0); //FIXME
    return OPERATOR_UNKNOWN;
  }
  // OPR_SUB, OPR_MPY, OPR_DIV
}
