// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.cxx,v 1.3 2003/08/08 20:04:36 eraxxon Exp $

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
#include <lib/support/WhirlIDMaps.h>
#include <lib/support/XAIFStrings.h>
#include <lib/support/diagnostics.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

static void
TranslateCallGraph(PU_Info* pu_forest, DOMDocument* doc, XlationContext& ctxt);

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


void
xaif2whirl::TranslateIR(PU_Info* pu_forest, DOMDocument* doc)
{
  Diag_Set_Phase("WHIRL to XAIF: translate IR");
  
  if (!pu_forest) { return; }
  
  XlationContext ctxt;

  TranslateCallGraph(pu_forest, doc, ctxt);
}


static void
TranslateCallGraph(PU_Info* pu_forest, DOMDocument* doc, XlationContext& ctxt)
{
  // FIXME: Do something about the ScopeHeirarchy

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
}


static void
TranslateCFG(PU_Info* pu_forest, DOMElement* cfgElem, XlationContext& ctxt)
{
  //FIXME: 
  const XMLCh* name = cfgElem->getAttribute(XAIFStrings.attr_annot_x());
  const XMLCh* scopeId = cfgElem->getAttribute(XAIFStrings.attr_scopeId_x());
  const XMLCh* symId = cfgElem->getAttribute(XAIFStrings.attr_symId_x());
  
  XercesStrX nameStr = XercesStrX(name);
  XercesStrX scopeIdStr = XercesStrX(scopeId);
  XercesStrX symIdStr = XercesStrX(symId);

  cout << XercesStrX(cfgElem->getNodeName()) << ": " << nameStr 
       << " // " << scopeIdStr << ", " << symIdStr << endl;

  // -------------------------------------------------------
  // Try to find the matching PU; if so, translate XAIF CFG to WHIRL PU.
  // -------------------------------------------------------
  PU_Info* pu = FindPUForCFG(pu_forest, nameStr.c_str(), scopeIdStr.c_str(),
			     symIdStr.c_str());
  if (!pu) { return; }


  // If we found the PU, translate
  RestoreOpen64PUGlobalVars(pu);

  WN *wn_pu = PU_Info_tree_ptr(pu);
  TranslateCFG(wn_pu, cfgElem, ctxt);

  SaveOpen64PUGlobalVars(pu);
}


// Given an XAIF CFG rooted at 'cfgElem' and its corresponding WHIRL
// tree 'wn_pu', modify the WHIRL to reflect the XAIF.
static void
TranslateCFG(WN *wn_pu, DOMElement* cfgElem, XlationContext& ctxt)
{
  pair<WNIdToWNMap*, WNToWNIdMap*> wnmaps = CreateWhirlIDMaps(wn_pu);
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


static void
TranslateBB(WN *wn_pu, DOMElement* bbElem, XlationContext& ctxt)
{
  WNIdToWNMap* wnmap = ctxt.GetIdToWNMap();

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


// FindPUForCFG: Find the PU in 'pu_forest' that matches the name and
// scope/symbol ids.  If name is non-empty, the scopeId and symId
// should be non-empty.
// FIXME: this is just a linear search
static PU_Info*
FindPUForCFG(PU_Info* pu_forest, const char* name, 
	     const char* scopeIdStr, const char* symIdStr)
{
  unsigned long symId = strtol(symIdStr, (char **)NULL, 10);
  
  if (!name || name[0] == '\0'
      || !scopeIdStr || scopeIdStr[0] == '\0'
      || !symIdStr || symIdStr == '\0') {
    return NULL;
  }
  
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
  
  // 2. Find the interval boundariesn
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


WN* 
xlate_Assignment(DOMElement* elem, XlationContext& ctxt);

WN* 
xlate_SubroutineCall(DOMElement* elem, XlationContext& ctxt);

WN*
xlate_AssignmentLHS(DOMElement* elem, XlationContext& ctxt);

WN*
xlate_AssignmentRHS(DOMElement* elem, XlationContext& ctxt);


static WN* 
TranslateStmt(DOMElement* stmt, XlationContext& ctxt)
{
  WN* wn = NULL;
  
  const XMLCh* name = stmt->getNodeName();
  if (XMLString::equals(name, XAIFStrings.elem_Assign_x())) {
    wn = xlate_SubroutineCall(stmt, ctxt);
  } else if (XMLString::equals(name, XAIFStrings.elem_SubCall_x())) {
    wn = xlate_Assignment(stmt, ctxt);
  } else if (XMLString::equals(name, XAIFStrings.elem_Nop_x())) {
    // nothing
  } else {
    ASSERT_FATAL(FALSE, (DIAG_A_STRING, "Programming error."));
  }
  
  return wn;
}


WN* 
xlate_Assignment(DOMElement* elem, XlationContext& ctxt)
{
  xlate_AssignmentLHS(elem, ctxt);
  xlate_AssignmentRHS(elem, ctxt);
  WN* wn = WN_CreateAssert(0, WN_CreateIntconst(OPC_I4INTCONST, (INT64)1));
  return wn;
}

WN* 
xlate_SubroutineCall(DOMElement* elem, XlationContext& ctxt)
{
  WN* wn = WN_CreateAssert(0, WN_CreateIntconst(OPC_I4INTCONST, (INT64)1));
  return wn;
}

WN*
xlate_AssignmentLHS(DOMElement* elem, XlationContext& ctxt)
{
  return NULL;
}

WN*
xlate_AssignmentRHS(DOMElement* elem, XlationContext& ctxt)
{
  return NULL;
}


#if 0
TranslateVarRef

TranslateExpression(WHIRL*, exprgraph, context);
// "VariableReference|Constant|Intrinsic|FunctionCall|BooleanOperation"
#endif
