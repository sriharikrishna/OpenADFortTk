// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.cxx,v 1.23 2004/02/25 16:23:29 eraxxon Exp $

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
#include "xaif2whirl_stmt.h"
#include "xaif2whirl_expr.h"

#include "XAIF_DOMFilters.h"
#include "XercesStrX.h"

#include <lib/support/Pro64IRInterface.h>
#include <lib/support/SymTab.h> // for XAIFSymToWhirlSymMap
#include <lib/support/WhirlIDMaps.h>
#include <lib/support/WhirlParentize.h>
#include <lib/support/wn_attr.h> // for WN_Tree_Type
#include <lib/support/XAIFStrings.h>
#include <lib/support/diagnostics.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

using namespace xaif2whirl;

IntrinsicXlationTable xaif2whirl::IntrinsicTable(IntrinsicXlationTable::X2W);

static void
TranslateCallGraph(PU_Info* pu_forest, const DOMDocument* doc, 
		   XlationContext& ctxt);

static XAIFSymToSymbolMap*
TranslateScopeHierarchy(const DOMDocument* doc, XlationContext& ctxt);

static void
TranslateCFG(PU_Info* pu_forest, const DOMElement* cfgElem,
	     XlationContext& ctxt);

static void
TranslateCFG(WN *wn_pu, const DOMElement* cfgElem, XlationContext& ctxt);

static void
TranslateBB(WN *wn_pu, const DOMElement* bbElem, XlationContext& ctxt);

//*************************** Forward Declarations ***************************

static void
xlate_BasicBlock(WN *wn_pu, const DOMElement* bbElem, XlationContext& ctxt);

static void
xlate_BBCondition(WN* wn_pu, const DOMElement* bbElem, XlationContext& ctxt);


static bool
FindNextStmtInterval(const DOMElement* bbElem, IdList<WNId>* bbIdList, 
		     WNIdToWNMap* wnmap, WN* blkWN,
		     DOMElement* &begXAIF, DOMElement* &endXAIF,
		     WN* &begWN, WN* &endWN);

static WN*
FindIntervalBoundary(const DOMElement* elem, IdList<WNId>* bbIdList, 
		     WNIdToWNMap* wnmap, WN* blkWN, int boundary);

static WN* 
FindWNBlock(const DOMElement* bbElem, WN* wn_pu, 
	    IdList<WNId>* idlist, WNIdToWNMap* wnmap);

static WN* 
FindSafeInsertionPoint(WN* blckWN, WN* stmtWN);

static void
RemoveFromWhirlIdMaps(WN* wn, WNToWNIdMap* wn2idmap, WNIdToWNMap* id2wnmap);

//****************************************************************************

static void
xlate_Scope(const DOMElement* elem, XAIFSymToSymbolMap* symMap, 
	    XlationContext& ctxt);

static void
xlate_SymbolTable(const DOMElement* elem, const char* scopeId, PU_Info* pu, 
		  XAIFSymToSymbolMap* symMap);

static void
xlate_Symbol(const DOMElement* elem, const char* scopeId, PU_Info* pu, 
	     XAIFSymToSymbolMap* symMap);

static ST* 
CreateST(const DOMElement* elem, SYMTAB_IDX level, const char* nm);

// FIXME: temporary
static TY_IDX
XAIFTyToWHIRLTy(const char* type);

//FIXME (Note: TYPE_ID and TY_IDX are typedef'd to the same type, so
//overloading is not possible!)
static TY_IDX MY_Make_Array_Type1 (TYPE_ID elem_ty, INT32 ndim, INT64 len);
static TY_IDX MY_Make_Array_Type (TY_IDX elem_ty, INT32 ndim, INT64 len);

// FIXME
extern bool opt_typeChangeInWHIRL;
TY_IDX ActiveTypeTyIdx; // FIXME: just for temporary testing
static void 
DeclareActiveModule();

//****************************************************************************

// TranslateIR: 
void
xaif2whirl::TranslateIR(PU_Info* pu_forest, const DOMDocument* doc)
{
  Diag_Set_Phase("XAIF to WHIRL: translate IR");
  
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
TranslateCallGraph(PU_Info* pu_forest, const DOMDocument* doc,
		   XlationContext& ctxt)
{
  // FIXME: test: add active module type
  if (opt_typeChangeInWHIRL) {
    DeclareActiveModule();
  }
  
  // FIXME: Do something about the ScopeHeirarchy
  XAIFSymToSymbolMap* symmap = TranslateScopeHierarchy(doc, ctxt);
  ctxt.SetXAIFSymToSymbolMap(symmap);
  
  // -------------------------------------------------------
  // Translate each ControlFlowGraph in the CallGraph
  // -------------------------------------------------------
  DOMDocument* d = const_cast<DOMDocument*>(doc); // Xerces can't take a const!
  DOMNodeIterator* it = 
    d->createNodeIterator((DOMNode*)doc, DOMNodeFilter::SHOW_ALL, 
			  new XAIF_CFGElemFilter(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* elem = dynamic_cast<DOMElement*>(node);

    TranslateCFG(pu_forest, elem, ctxt);
  }
  it->release();
  
  delete symmap;
}


// TranslateScopeHierarchy: 
static XAIFSymToSymbolMap*
TranslateScopeHierarchy(const DOMDocument* doc, XlationContext& ctxt)
{
  XAIFSymToSymbolMap* symMap = new XAIFSymToSymbolMap;

  // -------------------------------------------------------
  // Enter symbols for all Scopes in the ScopeHierarchy
  // -------------------------------------------------------
  DOMDocument* d = const_cast<DOMDocument*>(doc); // Xerces can't take a const!
  DOMNodeIterator* it = 
    d->createNodeIterator((DOMNode*)doc, DOMNodeFilter::SHOW_ALL, 
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
TranslateCFG(PU_Info* pu_forest, const DOMElement* cfgElem,
	     XlationContext& ctxt)
{
  // -------------------------------------------------------
  // Translate XAIF CFG to WHIRL PU.
  // -------------------------------------------------------
  PUId puid = GetPUId(cfgElem);
  PU_Info* pu = ctxt.FindPU(puid);
  if (!pu) { return; }
  
  Symbol* sym = GetSymbol(cfgElem, ctxt);
  ST* st = sym->GetST();
  cout << XercesStrX(cfgElem->getNodeName()) << ": " << ST_name(st) << endl;
  
  // If we found the PU, translate
  PU_SetGlobalState(pu);
  
  WN *wn_pu = PU_Info_tree_ptr(pu);
  TranslateCFG(wn_pu, cfgElem, ctxt);
  
#if 0
  fprintf(stderr, "\n----------------------------------------------------\n");
  fdump_tree(stderr, wn_pu);
#endif
}


// TranslateCFG: Given an XAIF CFG rooted at 'cfgElem' and its
// corresponding WHIRL tree 'wn_pu', modify the WHIRL to reflect the
// XAIF.
static void
TranslateCFG(WN *wn_pu, const DOMElement* cfgElem, XlationContext& ctxt)
{
  pair<WNToWNIdMap*, WNIdToWNMap*> wnmaps = CreateWhirlIdMaps(wn_pu);
  ctxt.SetWNToIdMap(wnmaps.first);
  ctxt.SetIdToWNMap(wnmaps.second);
  
  // -------------------------------------------------------
  // Translate each BasicBlock in the CFG
  // -------------------------------------------------------
  DOMDocument* doc = cfgElem->getOwnerDocument();
  DOMNodeIterator* it = 
    doc->createNodeIterator((DOMNode*)cfgElem, DOMNodeFilter::SHOW_ALL, 
			    new XAIF_BBElemFilter(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* elem = dynamic_cast<DOMElement*>(node);
    
    TranslateBB(wn_pu, elem, ctxt);
  }
  it->release();

  delete wnmaps.first;
  delete wnmaps.second;
}

// TranslateBB: 
static void
TranslateBB(WN *wn_pu, const DOMElement* bbElem, XlationContext& ctxt)
{
  if (XAIF_BBElemFilter::IsBB(bbElem)) {
    xlate_BasicBlock(wn_pu, bbElem, ctxt);
  } else if (XAIF_BBElemFilter::IsBBIf(bbElem)
	     || XAIF_BBElemFilter::IsBBPreLoop(bbElem)
	     || XAIF_BBElemFilter::IsBBPostLoop(bbElem)) {
    xlate_BBCondition(wn_pu, bbElem, ctxt);
  } else if (XAIF_BBElemFilter::IsBBForLoop(bbElem)) {
    // FIXME: what to do with ForLoops?
  } else {
    // skip anything else for now
  }
}

static void
xlate_BasicBlock(WN *wn_pu, const DOMElement* bbElem, XlationContext& ctxt)
{
  // -------------------------------------------------------
  // 1. Find some info now to prevent several recalculations
  // -------------------------------------------------------
  IdList<WNId>* idlist = GetWNIdList(bbElem);
  WNIdToWNMap* wnmap = ctxt.GetIdToWNMap();
  WN* blkWN = FindWNBlock(bbElem, wn_pu, idlist, wnmap);
  if (idlist->size() > 0) { 
    ASSERT_FATAL(blkWN, (DIAG_A_STRING, "Programming error."));
  }

  // -------------------------------------------------------
  // 2. Translate new statements
  // -------------------------------------------------------
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

  // -------------------------------------------------------
  // 3. Patch certain statements represented by xaif:Markers
  // -------------------------------------------------------
  for (DOMElement* stmt = GetFirstChildElement(bbElem); (stmt); 
       stmt = GetNextSiblingElement(stmt, XAIFStrings.elem_Marker_x())) {
    WNId id = GetWNId(stmt);
    if (id != 0) {
      WN* wn = wnmap->Find(id, true /* mustFind */);
      PatchWNStmt(wn, ctxt);
    }
  }
  
  // -------------------------------------------------------
  // 4. Cleanup
  // -------------------------------------------------------
  delete idlist;
}


static void
xlate_BBCondition(WN* wn_pu, const DOMElement* bbElem, XlationContext& ctxt)
{
  // -------------------------------------------------------
  // 1. Find corresponding WHIRL condition node
  // -------------------------------------------------------
  // Conveniently, XAIF 'if' or 'loop' condition is represented by the
  // WHIRL structured control flow node, i.e. the corresponding WHIRL
  // 'if' or 'loop'.
  IdList<WNId>* idlist = GetWNIdList(bbElem);

  DOMElement* cond = GetChildElement(bbElem, XAIFStrings.elem_Condition_x());
  if (cond) {
    ASSERT_FATAL(idlist->size() == 1, (DIAG_A_STRING, "Error."));
  }

  WN* wn = ctxt.FindWN(idlist->front(), true /* mustFind */);

  INT condKid = 0;
  OPERATOR opr = WN_operator(wn);
  switch (opr) {
    
  case OPR_DO_WHILE:
  case OPR_WHILE_DO:
    condKid = 0; // WN_kid0(wn) == WN_while_test(wn)
    break;

  case OPR_IF:
  case OPR_TRUEBR:
  case OPR_FALSEBR:
    condKid = 0; // WN_kid0(wn) == WN_if_test(wn)
    break;

  default: 
    ASSERT_FATAL(false, (DIAG_W2F_CANNOT_HANDLE_OPC, OPERATOR_name(opr), opr));
  }
  
  // -------------------------------------------------------
  // 2. Ensure the condition expression is patched
  // -------------------------------------------------------
  PatchWNExpr(wn, condKid /* kidno */, ctxt);
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
FindNextStmtInterval(const DOMElement* bbElem, IdList<WNId>* bbIdList, 
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
  // This skips over consecutive sequences of xaif:Markers, a
  // necessary step to obtain a correct boundary begin point.
  while (begXAIF) {
    if (XAIF_BBStmtElemFilter::IsMarker(begXAIF) && GetWNId(begXAIF) != 0) {
      begXAIF = GetNextSiblingElement(begXAIF);
    } else {
      break; // not an xaif:Marker with WhirlId annotation!
    }
  } // Note: 'begXAIF' could be NULL now indicating a NULL interval  
  begWN = FindIntervalBoundary(begXAIF, bbIdList, wnmap, blkWN, 0 /* beg */);
  
  // 2. Find ending of the interval
  if (begXAIF) {

    // See if another xaif:Marker exists containing a WhirlId
    // annotation; if not, 'endXAIF' will be NULL.  (Note that we may
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
FindIntervalBoundary(const DOMElement* elem, IdList<WNId>* bbIdList, 
		     WNIdToWNMap* wnmap, WN* blkWN, int boundary)
{
  if (!elem) {
    return NULL;
  }

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
	ASSERT_FATAL(prevWN, (DIAG_A_STRING, "Programming error."));

	wn = prevWN;
      }
    }
    if (!wn && bbIdList->size() > 0) {
      wn = wnmap->Find(bbIdList->back(), true /* mustFind */);
    }
    
  } else {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  return wn;
}


// FindWNBlock: Given an XAIF basic block element, find the
// corresponding WHIRL block.
static WN* 
FindWNBlock(const DOMElement* bbElem, WN* wn_pu, 
	    IdList<WNId>* idlist, WNIdToWNMap* wnmap)
{
  // We pass 'idlist' to avoid continual reparsing
  WN* wn = NULL;
  if (idlist->size() > 0) {
    WNId id = idlist->front();
    wn = wnmap->Find(id, true /* mustFind */);
  }
  WN* blk = FindParentWNBlock(wn_pu, wn);
  return blk;
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

Symbol*
xaif2whirl::GetSymbol(const DOMElement* elem, XlationContext& ctxt)
{
  const XMLCh* scopeIdX = elem->getAttribute(XAIFStrings.attr_scopeId_x());
  const XMLCh* symIdX = elem->getAttribute(XAIFStrings.attr_symId_x());

  XercesStrX scopeId = XercesStrX(scopeIdX);
  XercesStrX symId = XercesStrX(symIdX);

  ASSERT_FATAL(strcmp(scopeId.c_str(), "") != 0, (DIAG_A_STRING, "Error."));
  ASSERT_FATAL(strcmp(symId.c_str(), "") != 0, (DIAG_A_STRING, "Error."));
  
  return ctxt.FindSym(scopeId.c_str(), symId.c_str());
}

static void
xlate_Scope(const DOMElement* elem, XAIFSymToSymbolMap* symMap, 
	    XlationContext& ctxt)
{
  // Find the corresponding WHIRL symbol table (ST_TAB)
  SymTabId symtabId = GetSymTabId(elem);
  pair<ST_TAB*, PU_Info*> stab = ctxt.FindSymTab(symtabId);
  ASSERT_FATAL(stab.first, (DIAG_A_STRING, "Programming error."));
  
  // Find the scope id
  const XMLCh* scopeIdX = elem->getAttribute(XAIFStrings.attr_Vid_x());
  XercesStrX scopeId = XercesStrX(scopeIdX);

  // Translate the xaif:SymbolTable (the only child)
  DOMElement* symtabElem = GetFirstChildElement(elem);
  xlate_SymbolTable(symtabElem, scopeId.c_str(), stab.second, symMap);
}  

static void
xlate_SymbolTable(const DOMElement* elem, const char* scopeId, PU_Info* pu, 
		  XAIFSymToSymbolMap* symMap)
{
  // For all xaif:Symbol in the xaif:SymbolTable
  DOMDocument* doc = elem->getOwnerDocument();
  DOMNodeIterator* it = 
    doc->createNodeIterator((DOMNode*)elem, DOMNodeFilter::SHOW_ALL, 
			    new XAIF_SymbolElemFilter(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* e = dynamic_cast<DOMElement*>(node);
    xlate_Symbol(e, scopeId, pu, symMap);
  }
  it->release();
}

// xlate_Symbol: Note that symbols can only be in a global or PU
// scope; IOW, there are no block scopes.
static void
xlate_Symbol(const DOMElement* elem, const char* scopeId, PU_Info* pu, 
	     XAIFSymToSymbolMap* symMap)
{
  // 1. Initialize
  SYMTAB_IDX level = GLOBAL_SYMTAB; // Default: assume a global symbol
  if (pu) {
    // This is a PU-scoped symbol.  Restore global state for PU.
    PU_SetGlobalState(pu);
    level = CURRENT_SYMTAB; // PU_lexical_level
  }
  
  SymId symId = GetSymId(elem);
  bool active = GetActiveAttr(elem);

  const XMLCh* symNmX = elem->getAttribute(XAIFStrings.attr_symId_x());
  XercesStrX symNm = XercesStrX(symNmX);

  // 2. Find or Create WHIRL symbol
  ST* st = NULL;
  if (symId == 0) {
    // Create the symbol
    st = CreateST(elem, level, symNm.c_str());
    if (!opt_typeChangeInWHIRL) {
      active = true; // FIXME: for now we force all temps to be active
    }
  } else {
    // Find the symbol and change type if necessary
    st = &(Scope_tab[level].st_tab->Entry(symId));
    if (opt_typeChangeInWHIRL) { // FIXME
      if (active && ST_class(st) == CLASS_VAR) {
	Set_ST_type(*st, ActiveTypeTyIdx);
      }
    }
  }
  
  // 3. Create our own symbol structure and add to the map
  Symbol* sym = new Symbol(st, active);
  symMap->Insert(scopeId, symNm.c_str(), sym);
} 

// CreateST: Creates and returns a WHIRL ST* at level 'level' with
// name 'nm' using 'elem' to gather ST shape and storage class info.
static ST* 
CreateST(const DOMElement* elem, SYMTAB_IDX level, const char* nm)
{
  const XMLCh* kindX = elem->getAttribute(XAIFStrings.attr_kind_x());
  const XMLCh* typeX = elem->getAttribute(XAIFStrings.attr_type_x());
  const XMLCh* shapeX = elem->getAttribute(XAIFStrings.attr_shape_x());    

  XercesStrX kind = XercesStrX(kindX);
  XercesStrX type = XercesStrX(typeX);
  XercesStrX shape = XercesStrX(shapeX);

  bool active = GetActiveAttr(elem);
  
  assert( strcmp(kind.c_str(), "variable" ) == 0 ); // FIXME: assume only
    
  // 1. Find basic type according to 'type' and 'active'
  TY_IDX basicTy = XAIFTyToWHIRLTy(type.c_str());
  if (opt_typeChangeInWHIRL) {
    if (active) {
      basicTy = ActiveTypeTyIdx;
    } 
  }
  
  // 2. Modify basic type according to the (non-scalar) shapes
  TY_IDX ty;
  if (strcmp(shape.c_str(), "scalar") == 0) {
    ty = basicTy;
  } else {
    // Note: cf. be/com/wn_instrument.cxx:1253 for example creating vector
    INT32 ndim = 0;
    INT64 len = 1000; // FIXME: this is fixed size!!
    if (strcmp(shape.c_str(), "vector") == 0) {
      ndim = 1;
    } else {
      // FIXME: add tensors
      ASSERT_FATAL(false, (DIAG_A_STRING, "Programming error."));
    }
    ty = MY_Make_Array_Type(basicTy, ndim, len);
  }
  
  // 3. Find storage class
  ST_SCLASS sclass = SCLASS_AUTO; // default: auto implies local storage
  if (level == GLOBAL_SYMTAB) {
    sclass = SCLASS_COMMON; // SCLASS_PSTATIC; // FIXME
  }
  
  // 4. Create the new symbol
  ST* st = New_ST(level);
  ST_Init(st, Save_Str(nm), CLASS_VAR, sclass, EXPORT_LOCAL, ty);
  
  return st;
}

//****************************************************************************

static bool
GetBoolAttr(const DOMElement* elem, XMLCh* attr, bool default_val);


bool
xaif2whirl::GetActiveAttr(const DOMElement* elem)
{
  return GetBoolAttr(elem, XAIFStrings.attr_active_x(), true /* default */);
}

bool
xaif2whirl::GetDerivAttr(const DOMElement* elem)
{
  return GetBoolAttr(elem, XAIFStrings.attr_deriv_x(), false /* default */);
}

unsigned int
xaif2whirl::GetPositionAttr(const DOMElement* elem)
{
  const XMLCh* posAttrX = elem->getAttribute(XAIFStrings.attr_position_x());
  XercesStrX posAttr = XercesStrX(posAttrX);
  
  unsigned int pos = strtol(posAttr.c_str(), (char **)NULL, 10);
  return pos;
}


static bool
GetBoolAttr(const DOMElement* elem, XMLCh* attr, bool default_val)
{
  const XMLCh* aX = elem->getAttribute(attr);
  XercesStrX a = XercesStrX(aX);
  
  // boolean values can be true/false or 1/0
  bool a_bool = default_val;
  if (strlen(a.c_str()) > 0) { // if attribute exists
    if (a.c_str()[0] == '0' || (strcmp(a.c_str(), "false") == 0)) {
      a_bool = false;
    } else {
      a_bool = true;
    }
  }
  return a_bool;
}



SymTabId
xaif2whirl::GetSymTabId(const DOMElement* elem)
{
  return GetId<SymTabId>(elem, XAIFStrings.tag_SymTabId());
}

SymId
xaif2whirl::GetSymId(const DOMElement* elem)
{
  return GetId<SymId>(elem, XAIFStrings.tag_SymId());
}

PUId
xaif2whirl::GetPUId(const DOMElement* elem)
{
  return GetId<PUId>(elem, XAIFStrings.tag_PUId());
}

WNId
xaif2whirl::GetWNId(const DOMElement* elem)
{
  return GetId<WNId>(elem, XAIFStrings.tag_WHIRLId());
}

IdList<WNId>*
xaif2whirl::GetWNIdList(const DOMElement* elem)
{
  return GetIdList<WNId>(elem, XAIFStrings.tag_WHIRLId());
}


// GetId, GetIdList: <see header>
template <class T>
T
xaif2whirl::GetId(const DOMElement* elem, const char* tag)
{
  const XMLCh* annot = (elem) ? elem->getAttribute(XAIFStrings.attr_annot_x())
    : NULL;
  XercesStrX annotStr = XercesStrX(annot);
  T id = GetId<T>(annotStr.c_str(), tag);
  return id;
}

template <class T>
IdList<T>*
xaif2whirl::GetIdList(const DOMElement* elem, const char* tag)
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
xaif2whirl::GetId(const char* idstr, const char* tag)
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
  ASSERT_FATAL(endptr && strncmp(endptr, XAIFStrings.tag_End(), len) == 0,
	       (DIAG_A_STRING, "Programming error."));
  return id;
}

template <class T>
IdList<T>*
xaif2whirl::GetIdList(const char* idstr, const char* tag)
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
      ASSERT_FATAL(id != 0, (DIAG_A_STRING, "Programming error."));
      idlist->push_back(id); // we found some digits to convert
    }

    tok = strtok((char*)NULL, ":");
    if (endptr && strcmp(endptr, XAIFStrings.tag_End()) == 0) {
      // we should be done with iteration now
      ASSERT_FATAL(tok == NULL, (DIAG_A_STRING, "Programming error."));
    }
  }

  return idlist;
}

//****************************************************************************

WN*
CreateCallToIntrin(TYPE_ID rtype, const char* fname, unsigned int argc)
{
  // cf. WN* cwh_intrin_build(...)
  // cf. WN* Gen_Call_Shell(...) in be/com/wn_instrument.cxx
  
  TY_IDX ty = Make_Function_Type(MTYPE_To_TY(rtype));
  ST* st = Gen_Intrinsic_Function(ty, fname); // create if non-existant
  
  WN* callWN = WN_Call(rtype, MTYPE_V, argc, st);
  WN_Set_Call_Default_Flags(callWN); // set conservative assumptions
  
  return callWN;
}

WN*
CreateCallToIntrin(TYPE_ID rtype, const char* fname, std::vector<WN*>& args)
{
  WN* callWN = CreateCallToIntrin(rtype, fname, args.size());
  
  for (unsigned int i = 0; i < args.size(); ++i) {
    if (args[i]) { 
      // conservatively assume pass by reference
      WN_actual(callWN, i) = CreateParm(args[i], WN_PARM_BY_REFERENCE);
    }
  }
  
  return callWN;
}

WN*
CreateIntrinsicCall(OPERATOR opr, INTRINSIC intrn, 
		    TYPE_ID rtype, TYPE_ID dtype, std::vector<WN*>& args)
{
  // Collect arguments into a temporary array for WN_Create_Intrinsic().
  WN** kids = new WN*[args.size()];
  for (unsigned int i = 0; i < args.size(); ++i) {
    kids[i] = args[i];
  }
  
  WN* wn = WN_Create_Intrinsic(opr, rtype, dtype, intrn, args.size(), kids);
  
  delete[] kids;
  return wn;
}

//****************************************************************************

static TY_IDX
XAIFTyToWHIRLTy(const char* type)
{
  TY_IDX ty = 0;
  if (strcmp(type, "real") == 0) {
    ty = MTYPE_To_TY(MTYPE_F8);
  } 
  else if (strcmp(type, "integer") == 0) {
    ty = MTYPE_To_TY(MTYPE_I8); 
  } 
  else {
    // don't know about anything else yet
    ASSERT_FATAL(false, (DIAG_A_STRING, "Programming error."));
  }
  return ty;
}


static void 
DeclareActiveModule()
{
  // Cf. dra_ec.cxx / DRA_EC_Declare_Types()
  // type active
  //   sequence
  //   double precision :: v 
  //   double precision :: d
  // end type active

  // Create 'v' (value) and 'd' (deriv) fields
  FLD_HANDLE valFld = New_FLD();  
  TY_IDX valTyIdx = MTYPE_To_TY(MTYPE_F8);
  FLD_Init(valFld, Save_Str("v"), valTyIdx, 0);
  
  FLD_HANDLE derivFld = New_FLD();
  TY_IDX derivTyIdx = MTYPE_To_TY(MTYPE_F8);
  FLD_Init(derivFld, Save_Str("d"), derivTyIdx, TY_size(valTyIdx));
  Set_FLD_last_field(derivFld);
  
  // Decare a struct with above fields
  TY_IDX activeTyIdx;
  TY& activeTy = New_TY(activeTyIdx); // sets 'activeTyIdx'
  INT64 activeSz = 2 * MTYPE_byte_size(valTyIdx);
  TY_Init (activeTy, activeSz, KIND_STRUCT, MTYPE_M, Save_Str("active"));
  Set_TY_fld(activeTy, valFld); // location of first field
  Set_TY_align(activeTyIdx, 8);
  Set_TY_is_sequence(activeTy);
  Set_TY_is_external(activeTy);
  
#if 0  
  // FIXME // declare type to be "external" in the SYM_TAB
  ST* stHandleType = New_ST(GLOBAL_SYMTAB);
  ST_Init(stHandleType, Save_Str("active"), CLASS_TYPE,
	  SCLASS_UNKNOWN, EXPORT_LOCAL, activeTyIdx); 
#endif
  
  ActiveTypeTyIdx = activeTyIdx;
}


// FIXME: modify symtab.cxx if this works out
static TY_IDX
MY_Make_Array_Type1 (TYPE_ID elem_ty, INT32 ndim, INT64 len)
{
  return MY_Make_Array_Type(MTYPE_To_TY (elem_ty), ndim, len);
}

static TY_IDX
MY_Make_Array_Type (TY_IDX elem_ty, INT32 ndim, INT64 len)
{
    INT64 elem_sz = TY_size (elem_ty);
    UINT elem_align = TY_align(elem_ty);
    FmtAssert(elem_sz > 0 && elem_align > 0,
              ("Cannot make an array of %s", TY_name (elem_ty)));
    
    ARB_HANDLE arb,arb_first;
    for (UINT i = 0; i < ndim; ++i) {
       arb = New_ARB ();
       if (i==0) {
	 arb_first = arb;
       }
       ARB_Init (arb, 0, len - 1, elem_sz);
       Set_ARB_dimension (arb, ndim-i);
    }
    
    Set_ARB_last_dimen (arb);
    Set_ARB_first_dimen (arb_first);
    
    TY_IDX ty_idx;
    TY& ty = New_TY (ty_idx);
    TY_Init (ty, elem_sz * ndim * len, KIND_ARRAY, MTYPE_UNKNOWN, 0);
    Set_TY_align (ty_idx, elem_align);
    Set_TY_etype (ty, elem_ty);
    Set_TY_arb (ty, arb_first);

    return ty_idx;

} // Make_Array_Type
