// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.cxx,v 1.9 2003/09/16 14:30:58 eraxxon Exp $

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

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

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

static bool
FindNextStmtInterval(DOMElement* bbElem, IdList<WNId>* bbIdList, 
		     WNIdToWNMap* wnmap, WN* blkWN,
		     DOMElement* &begXAIF, DOMElement* &endXAIF,
		     WN* &begWN, WN* &endWN);

static WN*
FindIntervalBoundary(DOMElement* elem, IdList<WNId>* bbIdList, 
		     WNIdToWNMap* wnmap, WN* blkWN, int boundary);

static WN* 
FindWNBlock(DOMElement* bbElem, WN* wn_pu, 
	    IdList<WNId>* idlist, WNIdToWNMap* wnmap);

static WN* 
FindParentWNBlock(WN* wn_tree, WN* wn);

static WN* 
FindSafeInsertionPoint(WN* blckWN, WN* stmtWN);

static void
RemoveFromWhirlIdMaps(WN* wn, WNToWNIdMap* wn2idmap, WNIdToWNMap* id2wnmap);

//****************************************************************************

static void
xlate_Scope(DOMElement* elem, XAIFSymToWhirlSymMap* symMap, 
	    XlationContext& ctxt);

static ST*
GetST(DOMElement* elem, XlationContext& ctxt);

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
  
  // 1. Initialization
  XlationContext ctxt;
  
  // Initialize global id maps
  pair<SymTabToSymTabIdMap*, SymTabIdToSymTabMap*> stabmaps =
    CreateSymTabIdMaps(pu_forest);
  ctxt.SetIdToSymTabMap(stabmaps.second);
  delete stabmaps.first;
  
  pair<PUToPUIdMap*, PUIdToPUMap*> pumaps = CreatePUIdMaps(pu_forest);
  delete pumaps.first;
  ctxt.SetIdToPUMap(pumaps.second);
    
  // 2. Translate
  TranslateCallGraph(pu_forest, doc, ctxt);
  
  // 3. Cleanup
  delete stabmaps.second;
  delete pumaps.second;
}


// TranslateCallGraph: 
static void
TranslateCallGraph(PU_Info* pu_forest, DOMDocument* doc, XlationContext& ctxt)
{
  // FIXME: Do something about the ScopeHeirarchy
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
  // -------------------------------------------------------
  // Translate XAIF CFG to WHIRL PU.
  // -------------------------------------------------------
  PUId puid = GetPUId(cfgElem);
  PU_Info* pu = ctxt.FindPU(puid);
  if (!pu) { return; }
  
  ST* st = GetST(cfgElem, ctxt);
  cout << XercesStrX(cfgElem->getNodeName()) << ": " << ST_name(st) << endl;
  
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
  pair<WNToWNIdMap*, WNIdToWNMap*> wnmaps = CreateWhirlIdMaps(wn_pu);
  ctxt.SetWNToIdMap(wnmaps.first);
  ctxt.SetIdToWNMap(wnmaps.second);
  
  // -------------------------------------------------------
  // Translate each BasicBlock in the CFG
  // -------------------------------------------------------
  DOMDocument* doc = cfgElem->getOwnerDocument();
  DOMNodeIterator* it = 
    doc->createNodeIterator(cfgElem, DOMNodeFilter::SHOW_ALL, 
			    new XAIF_BBElemFilter(true /* BB */), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* elem = dynamic_cast<DOMElement*>(node);
    
    // FIXME: for now only translate xaif:BasicBlock.  What to do
    // about loop condition/initialization variables?
    TranslateBB(wn_pu, elem, ctxt);
  }
  it->release();

#if 0
  IR_set_dump_order(TRUE); /* dump parent before children*/
  fprintf(stderr, "\n----------------------------------------------------\n");
  fdump_tree(stderr, wn_pu);
#endif

  delete wnmaps.first;
  delete wnmaps.second;
}


// TranslateBB: 
static void
TranslateBB(WN *wn_pu, DOMElement* bbElem, XlationContext& ctxt)
{
  // Find some info now to prevent several recalculations
  IdList<WNId>* idlist = GetWNIdList(bbElem);
  WNIdToWNMap* wnmap = ctxt.GetIdToWNMap();
  WN* blkWN = FindWNBlock(bbElem, wn_pu, idlist, wnmap);
  if (idlist->size() > 0) { assert(blkWN && "Error!"); }

  // Translate
  DOMElement* begXAIF = NULL, *endXAIF = NULL;
  WN* begWN = NULL, *endWN = NULL;
  while (FindNextStmtInterval(bbElem, idlist, wnmap, blkWN,
			      begXAIF, endXAIF, begWN, endWN)) {
    
    // We now have two non-NULL intervals.  [begWN, endWN] represents
    // the WHIRL statements that will be replaced with the XAIF
    // statements [begXAIF, endXAIF]
    
    // 1. Find (or create) a statement just prior to the interval to
    // serve as an insertion point.
    WN* ipWN = FindSafeInsertionPoint(blkWN, begWN);

    // 2. Delete all WHIRL statements within [begWN, endWN]
    WN* it1End = WN_next(endWN); // result may be NULL
    for (WN* wn = begWN; (wn != it1End); wn = WN_next(wn)) {
      // Remove from persistent id maps (to assist debugging)
      RemoveFromWhirlIdMaps(wn, ctxt.GetWNToIdMap(), ctxt.GetIdToWNMap());
      WN_DELETE_FromBlock(blkWN, wn);
    }
    
    // 3. For each new XAIF statement within [begXAIF, endXAIF],
    // create a WHIRL node and insert it
    DOMElement* it2End = GetNextSiblingElement(endXAIF); // result may be NULL
    for (DOMElement* stmt = begXAIF; (stmt != it2End); 
	 stmt = GetNextSiblingElement(stmt)) {
      
      WN* wn = TranslateStmt(stmt, ctxt);
      if (!wn) { continue; }

      // Find the soon-to-be new insertion point
      WN* newIP = (WN_operator(wn) == OPR_BLOCK) ? WN_last(wn) : wn;

      // If 'wn' is a OPR_BLOCK, the block is automatically deleted
      WN_INSERT_BlockAfter(blkWN, ipWN, wn); 
      ipWN = newIP; // update the new insertion point
    }
  }

  // Cleanup
  delete idlist;
}

//****************************************************************************

// FindNextStmtInterval: Finds the next translation interval within
// the XAIF BB 'bbElem' given the current interval.  The current
// interval's status is defined by [begXAIF, endXAIF] both of which
// are NULL when no interval yet exists.  The function finds two new
// intervals, the XAIF statements [begXAIF, endXAIF] and their
// corresponding WHIRL statements [begWN, endWN].  Returns true if an
// interval has been found and the interval boundaries appropriately
// updated; otherwise, returns false.  Note that in the latter case,
// original interval boundaries are not necessary preserved.
//
// Intervals within the BB are created by the presence of xaif:Marker
// elements that contain a WhirlId annotation, but xaif:Marker's are
// not actually within the interval.  If no explicit xaif:Marker
// begins or ends the BB, its existence is assumed.  Consequently, for
// non-NULL intervals, 'begXAIF' and 'endXAIF' will never point to an
// xaif:Marker element with annotation attribute and will never be
// NULL.
static bool
FindNextStmtInterval(DOMElement* bbElem, IdList<WNId>* bbIdList, 
		     WNIdToWNMap* wnmap, WN* blkWN,
		     DOMElement* &begXAIF, DOMElement* &endXAIF,
		     WN* &begWN, WN* &endWN)
{
  // 1. Find beginning of the interval
  if (!begXAIF) {
    begXAIF = GetFirstChildElement(bbElem);   // first interval (tmp)
  } else if (endXAIF) {
    begXAIF = GetNextSiblingElement(endXAIF); // successive intervals (tmp)
  } else {
    begXAIF = NULL;                           // no more intervals exist
  }  
  
  // If 'begXAIF' is non-NULL, it points to a temporary beginning
  // point.  From this point, find the first non-xaif:Marker element.
  // This skips over consequtive sequences of xaif:Markers, a
  // necessary step to obtain a correct boundary begin point.
  if (begXAIF) {
    while ( (begXAIF = GetNextSiblingElement(begXAIF)) ) {
      if ( !(XAIF_BBStmtElemFilter::IsMarker(begXAIF) 
	     && GetWNId(begXAIF) != 0) ) {
	break; // not an xaif:Marker with WhirlId annotation!
      }
    }
  } // Note: 'begXAIF' could be NULL now indicating a NULL interval
  begWN = FindIntervalBoundary(begXAIF, bbIdList, wnmap, blkWN, 0 /* beg */);
  
  // 2. Find ending of the interval
  if (begXAIF) {

    // See if another xaif:Marker exists containing a WhirlId
    // annotation; if not 'endXAIF' will be NULL.  (Note that we may
    // encounter an xaif:Marker without the annotation.)
    endXAIF = begXAIF; // of course, we start from the beginning!
    while ( (endXAIF = 
	     GetNextSiblingElement(endXAIF, XAIFStrings.elem_Marker_x())) ) {
      if (GetWNId(endXAIF) != 0) {
	break; // found!
      }
    }
    
    // If 'endXAIF' is non-NULL, it points to the first xaif:Marker
    // after 'begXAIF'.  If it is NULL, we use the very last element
    // (which must be a non-xaif:Marker).
    if (endXAIF) {
      endXAIF = GetPrevSiblingElement(endXAIF);
    } else {
      endXAIF = GetLastChildElement(bbElem);
    }
    endWN = FindIntervalBoundary(endXAIF, bbIdList, wnmap, blkWN, 1 /* end */);
    
  } else {
    endXAIF = NULL;
    endWN = NULL;
  }  
  
  return (begXAIF && begWN);
}


// FindIntervalBoundary: Finds the appropriate WN* for the given
// interval boundary statement 'elem' and boundary type (begin/end).
// The boundary is assumed to be of the form [beg, end], where beg and
// end are never xaif:Marker statements.  N.B.: It is assumed that
// this function is called for the begin interval *before* being
// called for the end interval.
//
// boundary: 0 (begin), 1 (end)
//
// For begin and end boundaries: If 'elem' is non-NULL the
// corrresponding WN* should never be NULL.  If 'elem' is NULL, the
// interval is NULL.
static WN*
FindIntervalBoundary(DOMElement* elem, IdList<WNId>* bbIdList, 
		     WNIdToWNMap* wnmap, WN* blkWN, int boundary)
{
  if (!elem) {
    return NULL;
  }

  // FIXME: Abstract this out
  WN* wn = NULL;
  if (boundary == 0) {
    
    // For begin boundaries: If the previous element is an xaif:Marker
    // with WhirlId annotation, use it to find the WN*; otherwise try
    // to use 'bbIdList' to return the first WN* in the list.
    DOMElement* adj = GetPrevSiblingElement(elem);
    if (adj && XAIF_BBStmtElemFilter::IsMarker(adj)) {
      WNId id = GetWNId(adj);
      if (id != 0) {
	wn = wnmap->Find(id, true /* mustFind */);

	// We used 'adj' (instead of 'elem') to find 'wn'.  Correct
	// the interval boundary by moving in the opposite direction.
	WN* nextWN = WN_next(wn); // Result may be NULL! (see above)

	if (nextWN) {
	  wn = nextWN;
	} else {
	  // The interval corresponding to 'elem' is the NULL interval
	  // after 'wn'.  We must create a dummy WN* to represent it
	  // with [beg, end) notation.
	  WN* newWN = WN_CreateAssert(0, WN_CreateIntconst(OPC_I4INTCONST, 
							   (INT64)1));
	  WN_INSERT_BlockAfter(blkWN, wn, newWN);
	  wn = newWN; // set 'wn' to the new node
	}
      }
    }
    if (!wn && bbIdList->size() > 0) {
      wn = wnmap->Find(bbIdList->front(), true /* mustFind */);
    }

  } else if (boundary == 1) {
    
    // For end boundaries: If the next element is an xaif:Marker
    // with WhirlId annotation, use it to find the WN*; otherwise try
    // to use 'bbIdList' to return the last WN* in the list.
    DOMElement* adj = GetNextSiblingElement(elem);
    if (adj && XAIF_BBStmtElemFilter::IsMarker(adj)) {
      WNId id = GetWNId(adj);
      if (id != 0) {
	wn = wnmap->Find(id, true /* mustFind */);

	// We used 'adj' (instead of 'elem') to find 'wn'.  Correct
	// the interval boundary by moving in the opposite direction.
	WN* prevWN = WN_prev(wn); // never NULL b/c of insertion above!
	assert(prevWN && "Programming Error");

	wn = prevWN;
      }
    }
    if (!wn && bbIdList->size() > 0) {
      wn = wnmap->Find(bbIdList->back(), true /* mustFind */);
    }
    
  } else {
    assert(false && "Programming Error!");
  }
  
  return wn;
}


// FindWNBlock: Given an XAIF basic block element, find the
// corresponding WHIRL block.
static WN* 
FindWNBlock(DOMElement* bbElem, WN* wn_pu, 
	    IdList<WNId>* idlist, WNIdToWNMap* wnmap)
{
  // We pass 'idlist' to avoid continual reparsing
  WN* wn = NULL;
  if (idlist->size() > 0) {
    wn = wnmap->Find(idlist->front(), true /* mustFind */);
  }
  WN* blk = FindParentWNBlock(wn_pu, wn);
  return blk;
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
  if (!wn_tree || !wn) { return NULL; }

  OPERATOR opr = WN_operator(wn_tree);
  if (!OPERATOR_is_scf(opr)) {
    // 'wn_tree' is not structured control flow and cannot contain blocks
    return NULL;
  } else {

    WN* blkWN = NULL;
    if (opr == OPR_BLOCK) {
      
      // Test to see if 'wn' is a child of 'wn_tree'
      WN *kid = WN_first(wn_tree);
      while (kid) {
	
	// Test this child
	if (kid == wn) {
	  return wn_tree; // we found the parent block|
	} 

	// Recursively test 
	if ( (blkWN = FindParentWNBlock(kid, wn)) ) {
	  return blkWN;
	}

	kid = WN_next(kid);
      }
    } else {
      
      // Recur on for non-block structured control flow
      for (INT kidno = 0; kidno < WN_kid_count(wn_tree); kidno++) {
	WN* kid = WN_kid(wn_tree, kidno);
	if ( (blkWN = FindParentWNBlock(kid, wn)) ) {
	  return blkWN;
	}
      }

    }

    return NULL; // not found
  }
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
  // serve as a handle.  whirl2f should ignore this.  (If not, a
  // compiler will be able to optimize this away.)
  ipWN = WN_CreateAssert(0, WN_CreateIntconst(OPC_I4INTCONST, (INT64)1));
  WN_INSERT_BlockBefore(blckWN, stmtWN, ipWN);
  return ipWN;
}


// RemoveFromWhirlIdMaps: Remove 'wn' and all of its descendents from
// the WhirlId maps.
static void
RemoveFromWhirlIdMaps(WN* wn, WNToWNIdMap* wn2idmap, WNIdToWNMap* id2wnmap)
{
  WN_TREE_CONTAINER<PRE_ORDER> wtree(wn);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  for (it = wtree.begin(); it != wtree.end(); ++it) {
    WN* curWN = it.Wn();

    WNId curId = 0;
    WNToWNIdMap::iterator it1 = wn2idmap->find(curWN);
    if (it1 != wn2idmap->end()) {
      curId = (*it1).second;
      wn2idmap->erase(it1);
    }
    id2wnmap->erase(curId);
  }
}

//****************************************************************************

static WN* 
xlate_Assignment(DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_AssignmentLHS(DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_AssignmentRHS(DOMElement* elem, XlationContext& ctxt);


static WN* 
xlate_SubroutineCall(DOMElement* elem, XlationContext& ctxt);


static WN* 
xlate_DerivativePropagator(DOMElement* elem, XlationContext& ctxt);

static WN* 
xlate_Saxpy(DOMElement* elem, XlationContext& ctxt, bool saxpy);


static WN*
TranslateExpression(DOMElement* elem, XlationContext& ctxt);

static WN*
xlate_Expression(DGraph* g, MyDGNode* n, XlationContext& ctxt);

static WN*
TranslateVarRef(DOMElement* elem, XlationContext& ctxt, bool lvalue);

static WN*
xlate_VarRef(DGraph* g, MyDGNode* n, XlationContext& ctxt, bool lvalue);

static WN*
xlate_Constant(DOMElement* elem, XlationContext& ctxt);


static WN*
CreateParm(WN *arg, UINT32 flag);


static DGraph* 
CreateExpressionGraph(DOMNode* node, bool varRef = false);


static WN* 
TranslateStmt(DOMElement* stmt, XlationContext& ctxt)
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
xlate_Assignment(DOMElement* elem, XlationContext& ctxt)
{
  DOMElement* lhs_elem = GetChildElement(elem, XAIFStrings.elem_AssignLHS_x());
  DOMElement* rhs_elem = GetChildElement(elem, XAIFStrings.elem_AssignRHS_x());
  
  WN* lhs = xlate_AssignmentLHS(lhs_elem, ctxt);
  WN* rhs = xlate_AssignmentRHS(rhs_elem, ctxt);
  
  // We always use ISTORE (instead of e.g. STID) for generality.  This
  // will not be an issue because the intension is for this WHIRL to
  // be translated to source code.
  // FIXME: first argument is bogus // WN_Tree_Type(rhs)
  TY_IDX ty = Make_Pointer_Type(MTYPE_To_TY(MTYPE_F8));
  WN* wn = WN_Istore(MTYPE_F8, 0, ty, lhs, rhs, 0);

  return wn;
}

static WN*
xlate_AssignmentLHS(DOMElement* elem, XlationContext& ctxt)
{
  // VariableReferenceType
  DOMElement* child = GetFirstChildElement(elem);
  WN* wn = TranslateVarRef(child, ctxt, true);
  return wn;
}

static WN*
xlate_AssignmentRHS(DOMElement* elem, XlationContext& ctxt)
{
  // ExpressionType
  DOMElement* child = GetFirstChildElement(elem);
  WN* wn = TranslateExpression(child, ctxt);
  return wn;
}


static WN* 
xlate_SubroutineCall(DOMElement* elem, XlationContext& ctxt)
{
  TYPE_ID rtype = MTYPE_V; // MTYPE_F8

  // 1. Translate arguments
  unsigned int numArgs = GetChildElementCount(elem);
  std::vector<WN*> args(numArgs, NULL);
  
  for (DOMElement* arg = GetFirstChildElement(elem); (arg); 
       arg = GetNextSiblingElement(arg) ) {
    
    const XMLCh* nmX = arg->getNodeName();
    ASSERT_FATAL(XMLString::equals(nmX, XAIFStrings.elem_Argument_x()), 
		 (DIAG_A_STRING, "Programming error."));
    
    const XMLCh* posX = arg->getAttribute(XAIFStrings.attr_position_x());
    XercesStrX posStr = XercesStrX(posX);
    UINT pos = strtol(posStr.c_str(), (char **)NULL, 10); // 1-based
    // FIXME: remove second test to accomodate missing constant arguments
    ASSERT_FATAL(1 <= pos /* && pos <= numArgs */, 
		 (DIAG_A_STRING, "Programming error."));

    WN* argWN = TranslateVarRef(arg, ctxt, false /* lvalue */);
    args[pos - 1] = argWN;
  }
  
  // 2. Create function call
  ST* st = GetST(elem, ctxt);
  WN* callWN = WN_Call(rtype, MTYPE_V, numArgs, st);
  
  WN_Set_Call_Default_Flags(callWN); // FIXME
  WN_Set_Call_Parm_Mod(callWN);
  
  // FIXME: do we need to handle paramaters differently?
  for (int i = 0; i < numArgs; ++i) {
    if (args[i]) {
      WN_actual(callWN, i) = CreateParm(args[i], WN_PARM_BY_REFERENCE);
    }
  }
  
  return callWN;
}


// Must not return an empty block
static WN* 
xlate_DerivativePropagator(DOMElement* elem, XlationContext& ctxt)
{
  WN* blckWN = WN_CreateBlock();
  
  // Accumulate derivative propagator statements and add to block
  DOMDocument* doc = elem->getOwnerDocument();
  DOMNodeIterator* it = 
    doc->createNodeIterator(elem, DOMNodeFilter::SHOW_ALL, 
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
  
  return blckWN;
}


static WN* 
xlate_Saxpy(DOMElement* elem, XlationContext& ctxt, bool saxpy)
{
  // FIXME: better sax/saxpy abstraction
  // saxpy_a_a(a,x,y) and sax_a_a(a,x,y)
  const char* fn = (saxpy) ? "saxpy_a_a" : "sax_a_a";

  // FIXME: could be a list. We ensure there is no list for now.
  ASSERT_FATAL(GetChildElementCount(elem) == 2, 
	       (DIAG_A_STRING, "Programming error."));

  DOMElement* AX = GetChildElement(elem, XAIFStrings.elem_AX_x());
  DOMElement* A = GetChildElement(AX, XAIFStrings.elem_A_x());
  DOMElement* X = GetChildElement(AX, XAIFStrings.elem_X_x());
  DOMElement* Y = GetChildElement(elem, XAIFStrings.elem_Y_x());

  WN* a_wn = TranslateExpression(GetFirstChildElement(A), ctxt);
  WN* x_wn = TranslateVarRef(X, ctxt, false);
  WN* y_wn = TranslateVarRef(Y, ctxt, false);

  // ------------------------------------------- // FIXME
  // WN *call = Gen_Call_Shell(name, rtype, 3); // wn_instrument.cxx
  
  TY_IDX ty = Make_Function_Type(MTYPE_To_TY(MTYPE_V));
  ST* st = Gen_Intrinsic_Function(ty, const_cast<char*>(fn)); // create if non-existant

  Clear_PU_no_side_effects(Pu_Table[ST_pu(st)]); // FIXME
  Clear_PU_is_pure(Pu_Table[ST_pu(st)]);
  Set_PU_no_delete(Pu_Table[ST_pu(st)]);


  WN* callWN = WN_Call(MTYPE_V, MTYPE_V, 3, st);

  WN_Set_Call_Default_Flags(callWN);
  WN_Set_Call_Parm_Mod(callWN);
  // ---------------------------------------------
  
  WN_actual(callWN, 0) = CreateParm(a_wn, WN_PARM_BY_VALUE);
  WN_actual(callWN, 1) = CreateParm(x_wn, WN_PARM_BY_REFERENCE);
  WN_actual(callWN, 2) = CreateParm(y_wn, WN_PARM_BY_REFERENCE);
  
  return callWN;
}


// TranslateExpression: Given the first node in an expression graph... 
static WN*
TranslateExpression(DOMElement* elem, XlationContext& ctxt)
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
    // base case: variable reference
    // -------------------------------------------------------
    return TranslateVarRef(elem, ctxt, false);

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
    // recursive case: function call
    // -------------------------------------------------------
    // children are expressions
    // find number of arguments
    assert(false && "Please implement me"); 
    return NULL; // FIXME

  } else if (XMLString::equals(nameX, XAIFStrings.elem_BoolOp_x())) {

    // -------------------------------------------------------
    // recursive case: boolean operation
    // -------------------------------------------------------
    // children are expressions
    assert(false && "Please implement me");
    return NULL; // FIXME
  } else {
    assert(false && "Unknown Expression element");
  }
  
}


// TranslateVarRef: Given the first node in a variable reference graph... 
// FIXME the third argument should be a part of 'ctxt'
static WN*
TranslateVarRef(DOMElement* elem, XlationContext& ctxt, bool lvalue)
{
  if (!elem) {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  if (!lvalue) {
    // skip the xaif:VariableReference node
    elem = GetFirstChildElement(elem);
  }
  
  // Slurp expression into a graph (DAG) and translate it
  DGraph* g = CreateExpressionGraph(elem, true /* varRef */);
  MyDGNode* n = dynamic_cast<MyDGNode*>(g->root());
  WN* wn = xlate_VarRef(g, n, ctxt, lvalue);
  delete g;
  
  
  // ------------------------------------------- // FIXME
  // wrap a fcall around this...
  TY_IDX fty = Make_Function_Type(MTYPE_To_TY(MTYPE_F8));
  ST* fst = Gen_Intrinsic_Function(fty, "__value__"); // create if non-existant
  
  WN* callWN = WN_Call(MTYPE_F8, MTYPE_V, 1, fst);
  WN_Set_Call_Default_Flags(callWN);
  
  WN_actual(callWN, 0) = CreateParm(wn, WN_PARM_BY_VALUE);
  // ---------------------------------------------
  
  return callWN;
}

static WN*
xlate_VarRef(DGraph* g, MyDGNode* n, XlationContext& ctxt, bool lvalue)
{
  // Recursively translate the DAG (tree) rooted at this node
  DOMElement* elem = n->GetElem();
  ASSERT_FATAL(elem, (DIAG_A_STRING, "Programming error."));

  WN* wn = NULL;  

  const XMLCh* nameX = elem->getNodeName();
  if (XMLString::equals(nameX, XAIFStrings.elem_SymRef_x())) {
    
    ST* st = GetST(elem, ctxt);
    
    if (lvalue) {
      // FIXME
      //wn = WN_CreateLda(OPC_F8LDA, 0, TY_pointer(ST_type(st)), st);
      wn = WN_CreateLda(OPR_LDA, Pointer_Mtype, MTYPE_V, 0, 
			TY_pointer(ST_type(st)), st, 0);
    } else {
      // FIXME
      wn = WN_CreateLdid(OPC_F8F8LDID, 0, st, MTYPE_To_TY(MTYPE_F8));
    }

  } else if (XMLString::equals(nameX, XAIFStrings.elem_ArrayElemRef_x())) {
    
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

      // FIXME: ensure an integer type...
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
    
    WN* arraySym = xlate_VarRef(g, n1, ctxt, true);
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
    assert(false && "Unknown Variabe Reference element");
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

static WN*
CreateParm(WN *arg, UINT32 flag)
{
  TYPE_ID rtype = WN_rtype(arg);
  return WN_CreateParm(rtype, arg, MTYPE_To_TY(rtype), flag);
}

// Gen_Call_Shell

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
      assert(strcmp(vid.c_str(), "") != 0); // FIXME: ints for now
      
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
  
  assert(root);
  g->set_root(root);
  
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
  // Find the corresponding WHIRL symbol table (ST_TAB)
  SymTabId symtabId = GetSymTabId(elem);
  pair<ST_TAB*, PU_Info*> stab = ctxt.FindSymTab(symtabId);
  assert(stab.first);
  
  // Find the scope id
  const XMLCh* scopeIdX = elem->getAttribute(XAIFStrings.attr_Vid_x());
  XercesStrX scopeId = XercesStrX(scopeIdX);

  // Translate the xaif:SymbolTable (the only child)
  DOMElement* symtabElem = GetFirstChildElement(elem);
  xlate_SymbolTable(symtabElem, scopeId.c_str(), stab.second, symMap);
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
  
  SymId symId = GetSymId(elem);

  const XMLCh* symNmX = elem->getAttribute(XAIFStrings.attr_symId_x());
  XercesStrX symNm = XercesStrX(symNmX);

  // 2. Find or Create symbol
  ST* st = NULL;
  if (symId == 0) {  // check temporary tag FIXME
    
    // Create the symbol
    const XMLCh* kindX = elem->getAttribute(XAIFStrings.attr_kind_x());
    const XMLCh* typeX = elem->getAttribute(XAIFStrings.attr_type_x());
    const XMLCh* shapeX = elem->getAttribute(XAIFStrings.attr_shape_x());
    
    XercesStrX kind = XercesStrX(kindX);
    XercesStrX type = XercesStrX(typeX);
    XercesStrX shape = XercesStrX(shapeX);
    
    assert( strcmp(kind.c_str(), "variable" ) == 0 ); // FIXME: assume only
    assert( strcmp(type.c_str(), "real" ) == 0 );     // scalar, reals
    assert( strcmp(shape.c_str(), "scalar" ) == 0 );
    
    st = New_ST(level);
    ST_Init(st, Save_Str(symNm.c_str()), CLASS_VAR, SCLASS_AUTO, EXPORT_LOCAL,
	    MTYPE_To_TY(MTYPE_F8));
    
  } else {
    // Find the symbol
    st = &(Scope_tab[level].st_tab->Entry(symId));
  }
  
  // 3. Add the symbol to the map
  symMap->Insert(scopeId, symNm.c_str(), st);
  
  // 4. Finalize
  if (pu) {
    SaveOpen64PUGlobalVars(pu);
  }
} 

//****************************************************************************

// FIXME: move to another place and create tables for these
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
  // OPR_SUB, OPR_MPY, OPR_DIV
}


//****************************************************************************

// FIXME: move to another place
SymTabId
GetSymTabId(DOMElement* elem)
{
  return GetId<SymTabId>(elem, XAIFStrings.tag_SymTabId());
}

SymId
GetSymId(DOMElement* elem)
{
  return GetId<SymId>(elem, XAIFStrings.tag_SymId());
}

PUId
GetPUId(DOMElement* elem)
{
  return GetId<PUId>(elem, XAIFStrings.tag_PUId());
}

WNId
GetWNId(DOMElement* elem)
{
  return GetId<WNId>(elem, XAIFStrings.tag_WHIRLId());
}

IdList<WNId>*
GetWNIdList(DOMElement* elem)
{
  return GetIdList<WNId>(elem, XAIFStrings.tag_WHIRLId());
}


// GetId, GetIdList: <see header>
template <class T>
T
GetId(DOMElement* elem, const char* tag)
{
  const XMLCh* annot = (elem) ? elem->getAttribute(XAIFStrings.attr_annot_x())
    : NULL;
  XercesStrX annotStr = XercesStrX(annot);
  T id = GetId<T>(annotStr.c_str(), tag);
  return id;
}

template <class T>
IdList<T>*
GetIdList(DOMElement* elem, const char* tag)
{
  const XMLCh* annot = (elem) ? elem->getAttribute(XAIFStrings.attr_annot_x())
    : NULL;
  XercesStrX annotStr = XercesStrX(annot);
  IdList<T>* idlist = GetIdList<T>(annotStr.c_str(), tag);
  return idlist;
}


// GetId, GetIdList: <see header>
template <class T>
T
GetId(const char* idstr, const char* tag)
{
  T id = 0;
  if (!idstr) { return id; }

  // Find the tag indicating presence of id
  const char* start = strstr(idstr, tag);
  if (!start) { return id; }
  start += strlen(tag); // move pointer past tag
  
  char* endptr = NULL;
  id = strtol(start, &endptr, 10);

  unsigned int len = strlen(XAIFStrings.tag_End());
  assert(endptr && strncmp(endptr, XAIFStrings.tag_End(), len) == 0);
  return id;
}

template <class T>
IdList<T>*
GetIdList(const char* idstr, const char* tag)
{
  IdList<T>* idlist = new IdList<T>;

  if (!idstr) { return idlist; }
  
  // Find the tag indicating presence of list
  const char* start = strstr(idstr, tag);
  if (!start) { return idlist; }
  start += strlen(tag); // move pointer past tag
  
  // Parse the colon separated id list.  The list is ended by
  // XAIFStrings.tag_End()
  char* tok = strtok(const_cast<char*>(start), ":");
  while (tok != NULL) {
    
    char* endptr = NULL;
    T id = strtol(tok, &endptr, 10);
    if (endptr != tok) { 
      assert(id != 0);
      idlist->push_back(id); // we found some digits to convert
    }

    tok = strtok((char*)NULL, ":");
    if (endptr && strcmp(endptr, XAIFStrings.tag_End()) == 0) {
      assert(tok == NULL); // we should be done with iteration now
    }
  }

  return idlist;
}

//****************************************************************************
