// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.cxx,v 1.60 2004/12/01 21:24:30 eraxxon Exp $

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
#include <vector>
using std::vector;
#include <set>
using std::set;
#include <list> // FIXME: TopologicalSort
using std::list;
#include <map>  // FIXME: TopologicalSort
using std::map;

//************************* Xerces Include Files ****************************

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
#include <lib/support/wn_attr.h>   // for WN_Tree_Type
#include <lib/support/stab_attr.h> 
#include <lib/support/XAIFStrings.h>
#include <lib/support/diagnostics.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

using namespace xaif2whirl;

IntrinsicXlationTable xaif2whirl::IntrinsicTable(IntrinsicXlationTable::X2W);

// FIXME
extern xaif2whirl::ModeType      opt_mode;
extern xaif2whirl::AlgorithmType opt_algorithm;

// FIXME
extern TY_IDX ActiveTypeTyIdx;            // OpenAD active pseudo type
extern TY_IDX ActiveTypeInitializedTyIdx; // OpenAD active pseudo type
TY_IDX ActiveTypeTyIdx;            
TY_IDX ActiveTypeInitializedTyIdx;

//*************************** Forward Declarations ***************************

static void
TranslateCallGraph(PU_Info* pu_forest, const DOMDocument* doc, 
                   XlationContext& ctxt);

static XAIFSymToSymbolMap*
TranslateScopeHierarchy(const DOMDocument* doc, XlationContext& ctxt);

static void
TranslateCFG(PU_Info* pu_forest, const DOMElement* cfgElem,
             XlationContext& ctxt);

//*************************** Forward Declarations ***************************

// ControlFlowGraph

static void
TranslateCFG(WN *wn_pu, const DOMElement* cfgElem, XlationContext& ctxt);

static WN*
xlate_CFG(WN* wn_pu, DGraph* cfg, MyDGNode* root, XlationContext& ctxt, 
          bool structuredCF = false);

static WN*
TranslateBasicBlock(WN *wn_pu, const DOMElement* bbElem, XlationContext& ctxt,
                    bool skipMarkeredGotoAndLabels);

//*************************** Forward Declarations ***************************

// ControlFlowGraph -- basic block patching algorithm

static void
TranslateBB_OLD(WN *wn_pu, const DOMElement* bbElem, XlationContext& ctxt);

static void
xlate_BasicBlock_OLD(WN *wn_pu, const DOMElement* bbElem, 
                     XlationContext& ctxt);
static void
xlate_BBCond_OLD(WN* wn_pu, const DOMElement* bbElem, XlationContext& ctxt);

static bool
FindNextStmtInterval(const DOMElement* bbElem, IdList<WNId>* bbIdList, 
                     WNIdToWNMap* wnmap, WN* blkWN,
                     DOMElement* &begXAIF, DOMElement* &endXAIF,
                     WN* &begWN, WN* &endWN);

static WN*
FindIntervalBoundary(const DOMElement* elem, IdList<WNId>* bbIdList, 
                     WNIdToWNMap* wnmap, WN* blkWN, int boundary);

static WN* 
FindWNBlock(const DOMElement* bbElem, IdList<WNId>* idlist, 
	    XlationContext& ctxt);

static WN* 
FindSafeInsertionPoint(WN* blckWN, WN* stmtWN);

static void
RemoveFromWhirlIdMaps(WN* wn, WNToWNIdMap* wn2idmap, WNIdToWNMap* id2wnmap);

//*************************** Forward Declarations ***************************

// Scopes and Symbols

static void
xlate_Scope(const DOMElement* elem, XAIFSymToSymbolMap* symMap, 
            XlationContext& ctxt);

static void
xlate_SymbolTable(const DOMElement* elem, const char* scopeId, PU_Info* pu, 
                  XAIFSymToSymbolMap* symMap);

static void
xlate_Symbol(const DOMElement* elem, const char* scopeId, PU_Info* pu, 
             XAIFSymToSymbolMap* symMap);

//*************************** Forward Declarations ***************************

// WHIRL Creation functions

static WN*
CreateOpenADReplacementBeg(const char* placeholder);

static WN*
CreateOpenADReplacementEnd();

static WN* 
CreateIfCondition(WN* condWN);

static ST* 
CreateST(const DOMElement* elem, SYMTAB_IDX level, const char* nm);

static ST* 
ConvertIntoGlobalST(ST* st);

static void 
DeclareActiveTypes();

static void 
ConvertToActiveType(ST* st);


static FLD_HANDLE
My_FLD_get_to_field(TY_IDX struct_ty_idx, UINT64 ofst); // FIXME

// FIXME (Note: TYPE_ID and TY_IDX are typedef'd to the same type, so
// overloading is not possible!)
static TY_IDX MY_Make_Array_Type1 (TYPE_ID elem_ty, INT32 ndim, INT64 len);
static TY_IDX MY_Make_Array_Type (TY_IDX elem_ty, INT32 ndim, INT64 len);

static TY_IDX
XAIFTyToWHIRLTy(const char* type); // FIXME: temporary

//*************************** Forward Declarations ***************************

// MyDGNode routines

unsigned int MyDGNode::nextId = 1;

// sort_CondVal: Used to sort operands of (arguments to) an expression
// by the "condition_value" attribute
struct sort_CondVal
{
  sort_CondVal(bool ascending_ = true) : ascending(ascending_) { }
  
  // return true if e1 < e2; false otherwise
  bool operator()(const MyDGEdge* e1, const MyDGEdge* e2) const
  {
    unsigned int cond1 = GetCondAttr(e1->GetElem());
    unsigned int cond2 = GetCondAttr(e2->GetElem());
    return (ascending) ? (cond1 < cond2) : (cond1 > cond2);
  }

private:
  bool ascending;
};

static DGraph* 
CreateCFGraph(const DOMElement* elem);

static list<DGraph::Node*>*
TopologicalSort(DGraph* graph);

static void
DDumpDotGraph(DGraph* graph);

static void
DumpDotGraph(std::ostream& os, DGraph* graph);

//****************************************************************************


//****************************************************************************
// Top level translation routines
//****************************************************************************

// TranslateIR: 
void
xaif2whirl::TranslateIR(PU_Info* pu_forest, const DOMDocument* doc)
{
  Diag_Set_Phase("XAIF to WHIRL: translate IR");
  //IntrinsicTable.DDump();
  
  if (!pu_forest) { return; }
  
  // -------------------------------------------------------
  // 1. Initialization
  // -------------------------------------------------------
  XlationContext ctxt;
  
  // Initialize global id maps
  SymTabIdToSymTabMap* stabmap = new SymTabIdToSymTabMap(pu_forest);
  ctxt.SetIdToSymTabMap(stabmap);
  
  PUIdToPUMap* pumap = new PUIdToPUMap(pu_forest);
  ctxt.SetIdToPUMap(pumap);
  
  // -------------------------------------------------------
  // 2. Translate
  // -------------------------------------------------------
  TranslateCallGraph(pu_forest, doc, ctxt);
  
  // -------------------------------------------------------
  // 3. Cleanup
  // -------------------------------------------------------
  delete stabmap;
  delete pumap;
}


// TranslateCallGraph: 
static void
TranslateCallGraph(PU_Info* pu_forest, const DOMDocument* doc,
                   XlationContext& ctxt)
{
  DeclareActiveTypes();
  
  // FIXME: Do something about the ScopeHeirarchy
  XAIFSymToSymbolMap* symmap = TranslateScopeHierarchy(doc, ctxt);
  ctxt.SetXAIFSymToSymbolMap(symmap);
  
  // -------------------------------------------------------
  // Translate each ControlFlowGraph in the CallGraph
  // -------------------------------------------------------
  XAIF_CFGElemFilter filt;
  for (DOMElement* elem = GetChildElement(doc->getDocumentElement(), &filt);
       (elem); elem = GetNextSiblingElement(elem, &filt)) {
    TranslateCFG(pu_forest, elem, ctxt);
  }
  
  delete symmap;
}


// TranslateScopeHierarchy: Enter symbols for all Scopes in the
// ScopeHierarchy
static XAIFSymToSymbolMap*
TranslateScopeHierarchy(const DOMDocument* doc, XlationContext& ctxt)
{
  XAIFSymToSymbolMap* symMap = new XAIFSymToSymbolMap;

  // Get the ScopeHierarchy element
  DOMElement* scopeHier = GetChildElement(doc->getDocumentElement(), 
					  XAIFStrings.elem_ScopeHierarchy_x());
  FORTTK_ASSERT(scopeHier, "Could not find " 
		<< XAIFStrings.elem_ScopeHierarchy());
  
  // For each Scope in the ScopeHierarchy, examine each symbol
  XAIF_ScopeElemFilter filt;
  for (DOMElement* elem = GetChildElement(scopeHier, &filt);
       (elem); elem = GetNextSiblingElement(elem, &filt)) {
    xlate_Scope(elem, symMap, ctxt);
  }
  
  return symMap;
}


// TranslateCFG: Translate XAIF CFG or XAIF Replacement to WHIRL
static void
TranslateCFG(PU_Info* pu_forest, const DOMElement* cfgElem,
             XlationContext& ctxt)
{
  // -------------------------------------------------------
  // Find original PU and set globals
  // -------------------------------------------------------
  PUId puid = GetPUId(cfgElem);
  PU_Info* pu = ctxt.FindPU(puid);
  if (!pu) { return; }

#if 0  
  Symbol* sym = GetSymbol(cfgElem, ctxt);
  ST* st = sym->GetST();
  cout << XercesStrX(cfgElem->getNodeName()) << ": " << ST_name(st) << endl;
#endif  
  
  // Set globals
  WN *wn_pu = PU_Info_tree_ptr(pu);
  PU_SetGlobalState(pu);

  // -------------------------------------------------------
  // Translate, modifying 'wn_pu'
  // -------------------------------------------------------

  ST* st = ST_ptr(PU_Info_proc_sym(pu));
  if (IsActivePU(st)) {
    TranslateCFG(wn_pu, cfgElem, ctxt);
  }
  
#if 0
  fprintf(stderr, "\n----------------------------------------------------\n");
  fdump_tree(stderr, wn_pu);
#endif
}


//****************************************************************************
// ControlFlowGraph
//****************************************************************************

// Structured and Unstructured CFG Translation, with special reference
// to WHIRL SWITCHes.
//
// WHIRL does not have a structured multiway branch and so Fortran
// selects are translated into a jump table and several
// label/case-specific-code/goto-select-end blocks.
// 
// Given a 'structured' WHIRL PU -- a PU without any GOTOs except for
// CASE-block-related ones -- we can translate the SWITCH into an XAIF
// structured multiway branch, complete with an EndBranch node.  (The
// modified OpenAnalysis CFG provides the needed information.)
// Assuming the XAIF retains the structured property, then the XAIF
// can be translated back into a WHIRL switch node by removing all
// original WHIRL LABELs/GOTOs and adding new LABELs/GOTOs to the
// SWITCH case blocks.  (The original code must have had only 1)
// SWITCH-related GOTOs/LABELs and 2) possibly some non-target LABELs
// generated by mfef90.  It is safe to remove (2).  It is safe to
// remove (2) because new LABELs/GOTOs will be generated.)
// 
// Given a non-structured WHIRL PU, we can translate multiway branches
// into WHIRL SWITCHes in the same way as above.  A general and simple
// solution is to replace all original LABELs (always at the beginning
// of a basic block) and GOTOs (always at the end of a basic block)
// with new ones.  This eliminates the need to develop a more complex
// mechanism (such as label remapping) to ensure newly generated
// labels to not conflict with original labels.


static WN*
xlate_CFG_BasicBlock(WN *wn_pu, MyDGNode* curBB, XlationContext& ctxt, 
		     bool skipMarkeredGotoAndLabels = true, 
		     unsigned newCurBBLbl = 0, unsigned newNextBBLbl = 0);

static WN*
xlate_CFG_BranchMulti(MyDGNode* curNode, WN* condWN, unsigned lastLbl,
		      vector<MyDGEdge*>& outedges,
		      map<MyDGNode*, unsigned>& nodeToLblMap);


// TranslateCFG: Given an XAIF CFG or XAIF Replacement rooted at
// 'cfgElem' and its corresponding WHIRL tree 'wn_pu', modify the
// WHIRL to reflect the XAIF.
static void
TranslateCFG(WN *wn_pu, const DOMElement* cfgElem, XlationContext& ctxt)
{
  // -------------------------------------------------------
  // 1. Create auxiliary data structures
  // -------------------------------------------------------
  
  // 0. WHIRL parent map
  WhirlParentMap wnParentMap(wn_pu);
  ctxt.SetWNParentMap(&wnParentMap);
  
  // 1. WHIRL<->ID maps
  WNToWNIdMap* wnmapx = new WNToWNIdMap();
  WNIdToWNMap* wnmapy = new WNIdToWNMap();
  CreateWhirlIdMaps(wn_pu, wnmapx, wnmapy);
  ctxt.SetWNToIdMap(wnmapx);
  ctxt.SetIdToWNMap(wnmapy);
  
  // -------------------------------------------------------
  // 2. Update passing style for arguments (especially used in reverse
  // mode to change active arguments to pass-by-reference)
  // -------------------------------------------------------
  DOMElement* arglst = GetChildElement(cfgElem, XAIFStrings.elem_ArgList_x());
  DOMElement* arg = (arglst) ? 
    GetChildElement(arglst, XAIFStrings.elem_ArgSymRef_x()) : NULL;
  for ( ; arg; arg = GetNextSiblingElement(arg)) {
    // find corresponding WN and symbol
    WNId id = GetWNId(arg);
    WN* parmWN = ctxt.FindWN(id, true /* mustFind */);
    Symbol* sym = GetSymbol(arg, ctxt);
    ST* parmST = sym->GetST();
    
    //bool active = GetActiveAttr(arg); 
    const XMLCh* intentX = arg->getAttribute(XAIFStrings.attr_intent_x());
    XercesStrX intent = XercesStrX(intentX);
    
    if (strcmp(intent.c_str(), "in") == 0) {
      WN_Set_Parm_In(parmWN);
      Set_ST_is_intent_in_argument(parmST);
    } 
    else if (strcmp(intent.c_str(), "out") == 0) {
      WN_Set_Parm_Out(parmWN);
      Set_ST_is_intent_out_argument(parmST);		
    } 
    else if (strcmp(intent.c_str(), "inout") == 0) {
      WN_Set_Parm_By_Reference(parmWN); // unnecessary for 'whirl2f'
      Clear_ST_is_intent_in_argument(parmST);
      Clear_ST_is_intent_out_argument(parmST);
    } 
    else {
      FORTTK_DIE("Unknown intent to argument:\n" << *arg);
    }
  }
  
  // -------------------------------------------------------
  // 3. Translate each XAIF CFG into WHIRL
  // -------------------------------------------------------
  
  // Collect the list of CFGs we need to translate.  
  list<DOMElement*> cfglist;
  if (XAIF_CFGElemFilter::IsReplaceList(cfgElem)) {
    XAIF_ElemFilter filter(XAIFStrings.elem_Replacement_x());
    for (DOMElement* e = GetChildElement(cfgElem, &filter); 
         (e); e = GetNextSiblingElement(e, &filter)) {
      cfglist.push_back(e);
    }
  }
  else {
    cfglist.push_back(const_cast<DOMElement*>(cfgElem));
  }

  // Translate
  WN* newstmtblkWN = WN_CreateBlock();
  for (list<DOMElement*>::iterator it = cfglist.begin(); 
       it != cfglist.end(); ++it) {
    DOMElement* cfgelm = (*it);
    DGraph* cfg = CreateCFGraph(cfgelm);
    
    if (opt_algorithm == ALG_BB_PATCHING) { 
      XAIF_BBElemFilter filt(false /* edges */);
      for (DOMElement* elem = GetChildElement(cfgelm, &filt);
	   (elem); elem = GetNextSiblingElement(elem, &filt)) {
	TranslateBB_OLD(wn_pu, elem, ctxt);
      }
    } 
    else {
      MyDGNode* root = dynamic_cast<MyDGNode*>(cfg->root());
      bool structuredCF = (opt_algorithm == ALG_STRUCTURED_CF);
      WN* cfgblkWN = xlate_CFG(wn_pu, cfg, root, ctxt, structuredCF);
      if (XAIF_CFGElemFilter::IsReplacement(cfgelm)) {
        const XMLCh* pX = 
	  cfgelm->getAttribute(XAIFStrings.attr_placeholder_x());
        XercesStrX p = XercesStrX(pX);
        
        WN* begWN = CreateOpenADReplacementBeg(p.c_str());
        WN* endWN = CreateOpenADReplacementEnd();
        WN_INSERT_BlockFirst(cfgblkWN, begWN);
        WN_INSERT_BlockLast(cfgblkWN, endWN);
      }
      WN_INSERT_BlockLast(newstmtblkWN, cfgblkWN);
    }
    delete cfg;
  }
  
  // -------------------------------------------------------
  // 4. Replace old WHIRL code with newly translated WHIRL
  // -------------------------------------------------------
  if (opt_algorithm != ALG_BB_PATCHING) { 
    // Delete old WHIRL
    WN* funcblk = WN_func_body(wn_pu);
    for (WN* kid = WN_first(funcblk); (kid); /* */) {
      WN* nextkid = WN_next(kid); // must find next 'kid' now!
      WN_DELETE_FromBlock(funcblk, kid);
      kid = nextkid;
    }
    
    // Splice in newly translated WHIRL 
    for (WN* kid = WN_first(newstmtblkWN); (kid); /* */) {
      WN* nextkid = WN_next(kid); // must find next 'kid' now!
      WN_EXTRACT_FromBlock(newstmtblkWN, kid);
      WN_INSERT_BlockLast(funcblk, kid);
      kid = nextkid;
    }
    WN_Delete(newstmtblkWN); // not recursive -- should be empty
  }
  
  // -------------------------------------------------------
  // 5. Cleanup
  // -------------------------------------------------------
  delete wnmapx;
  delete wnmapy;
}


// xlate_CFG: Given the original WHIRL tree, a CFG structure
// representing the XAIF CFG, and the root CFG node, translate the CFG
// into a block of WHIRL statements.  If the CFG contains only
// structured control flow, 'structured' should be true; the WHIRL
// will also contain goto-less nested and structured control flow.
// Otherwise, 'structured' should be false and the WHIRL will contain
// labels and gotos.
//
// During translation, the non-numerical WHIRL statements represented
// by xaif:Marker will be copied from the original WHIRL tree and
// placed in the returned block.  It is expected that the *caller*
// will splice the returned block containing new statements back into
// the WHIRL FUNC_ENTRY.
//
// Note: This routine will not translate any basic blocks in the CFG
// that are unreachable from 'startNode' (i.e. dead code). [FIXME unstructured]

static pair<WN*, MyDGNode*>
xlate_CFGstruct(WN* wn_pu, DGraph* cfg, MyDGNode* startNode, 
                set<DOMElement*>& xlated, XlationContext& ctxt);

static WN*
xlate_CFGunstruct(WN* wn_pu, DGraph* cfg, MyDGNode* startNode, 
                  set<DOMElement*>& xlated, XlationContext& ctxt);

static WN*
xlate_CFG(WN* wn_pu, DGraph* cfg, MyDGNode* root, XlationContext& ctxt, 
          bool structuredCF)
{
  WN* blkWN = NULL;
  set<DOMElement*> xlated;
  if (structuredCF) {
    pair<WN*, MyDGNode*> ret = xlate_CFGstruct(wn_pu, cfg, root, xlated, ctxt);
    blkWN = ret.first;
  } else {
    blkWN = xlate_CFGunstruct(wn_pu, cfg, root, xlated, ctxt);
  }
  return blkWN;
}


// xlate_CFGstruct: Helper for translating a structured CFG.  The
// algorithm uses the structured CF and recursion to implicitly create
// nested control flow.
//
// Return value: <new-WHIRL-stmt-block, ending-basic-block> (If the
// latter is NULL, it means we saw the Exit basic block)
static pair<WN*, MyDGNode*>
xlate_CFGstruct(WN* wn_pu, DGraph* cfg, MyDGNode* startNode, 
                set<DOMElement*>& xlated, XlationContext& ctxt)
{
  WN* blkWN = WN_CreateBlock();
  
  // ---------------------------------------------------
  // We must generate labels FIXME
  // ---------------------------------------------------
  static unsigned int nextLblCntr = 1; // 0 is reserved
  map<MyDGNode*, unsigned> nodeToLblMap;
  
  // Initialize label maps
  for (DGraph::NodesIterator nodeIt(*cfg); (bool)nodeIt; ++nodeIt) {
    MyDGNode* n = dynamic_cast<MyDGNode*>((DGraph::Node*)nodeIt);
    nodeToLblMap[n] = nextLblCntr++;
  }
  
  // ---------------------------------------------------
  // Translate, beginning with 'startNode'
  // ---------------------------------------------------
  bool continueIteration = true;
  bool generateLbl = false;
  MyDGNode* curNode = startNode;
  while (curNode && continueIteration) {

    DOMElement* bbElem = curNode->GetElem();
    unsigned curLbl = nodeToLblMap[curNode];
   
    if (XAIF_BBElemFilter::IsBBEntry(bbElem) ||
        XAIF_BBElemFilter::IsBBExit(bbElem) ||
        XAIF_BBElemFilter::IsBB(bbElem)) {
      // ---------------------------------------------------
      // A non-control-flow basic block
      // ---------------------------------------------------
      MyDGNode* nextNode = GetSuccessor(curNode); // at most one outgoing edge
      unsigned lbl = (generateLbl) ? curLbl : 0;
      WN* stmts = xlate_CFG_BasicBlock(wn_pu, curNode, ctxt, true, lbl);
      WN_INSERT_BlockLast(blkWN, stmts);
      generateLbl = false;
      curNode = nextNode;
    }
    else if (XAIF_BBElemFilter::IsBBBranch(bbElem)) {
      // ---------------------------------------------------
      // Begin a structured branch.  Note: in XAIF branches are
      // 'structured switches'.
      // ---------------------------------------------------
      unsigned int numOutEdges = curNode->num_outgoing();

      // 1. Translate condition expression. 
      DOMElement* cond = 
        GetChildElement(bbElem, XAIFStrings.elem_Condition_x());
      DOMElement* condexpr = GetFirstChildElement(cond);      
      WN* condWN = TranslateExpression(condexpr, ctxt);
      if (numOutEdges == 2) {
	// Because branches are 'structured switches', ensure we have
	// a boolean expression for an 'if'.
	condWN = CreateIfCondition(condWN);
      }
      
      // 2. Gather all outgoing edges, sorted by condition (specially
      // sort two-way branches into true-false order.)
      vector<MyDGEdge*> outedges(numOutEdges, NULL);
      DGraph::OutgoingEdgesIterator it = 
        DGraph::OutgoingEdgesIterator(curNode);
      for (int i = 0; (bool)it; ++it, ++i) {
        outedges[i] = dynamic_cast<MyDGEdge*>((DGraph::Edge*)it);
      }
      std::sort(outedges.begin(), outedges.end(), 
                sort_CondVal((numOutEdges != 2)));

      // 3. Translate (recursively) each child block of this branch
      vector<WN*> childblksWN(numOutEdges, NULL);
      MyDGNode* endBrNode = NULL;
      for (int i = 0; i < outedges.size(); ++i) {
        MyDGNode* n = dynamic_cast<MyDGNode*>(outedges[i]->sink());
        pair<WN*, MyDGNode*> p = xlate_CFGstruct(wn_pu, cfg, n, xlated, ctxt);
        childblksWN[i] = p.first;
        endBrNode = p.second; // will be EndBranch for structured-CF
      }
      MyDGNode* nextNode = GetSuccessor(endBrNode);
      
      // 4. Create branch control flow
      if (numOutEdges == 2) {
        WN* ifWN = WN_CreateIf(condWN, childblksWN[0], childblksWN[1]);
	WN_INSERT_BlockLast(blkWN, ifWN);
      } 
      else {
	// Find the branch-around (or last) label
	unsigned lastLbl = nodeToLblMap[nextNode];
	
	// Add a LABEL/GOTO at the front/end of each successor block
	for (int i = 0; i < outedges.size(); ++i) {
	  MyDGNode* n = dynamic_cast<MyDGNode*>(outedges[i]->sink());
	  WN* nblkWN = childblksWN[i];
	  
	  WN* lblWN = WN_CreateLabel(nodeToLblMap[n], 0 /*label_flag*/, NULL);
	  WN_INSERT_BlockFirst(nblkWN, lblWN);
	  WN* gotoWN = WN_CreateGoto(lastLbl);
	  WN_INSERT_BlockLast(nblkWN, gotoWN);
	}
	generateLbl = true; // add label to front of successor
	
	// Create SWITCH with CASEGOTOs
	WN* switchWN = xlate_CFG_BranchMulti(curNode, condWN, lastLbl,
					     outedges, nodeToLblMap);
	WN_INSERT_BlockLast(blkWN, switchWN);
	
	// Add switch blocks right after SWITCH
	for (int i = 0; i < childblksWN.size(); ++i) {
	  WN_INSERT_BlockLast(blkWN, childblksWN[i]);
	}
      }
      
      curNode = nextNode;
    }
    else if (XAIF_BBElemFilter::IsBBEndBr(bbElem)) {
      // ---------------------------------------------------
      // End a structured branch
      // ---------------------------------------------------
      continueIteration = false;
    }
    else if (XAIF_BBElemFilter::IsBBForLoop(bbElem) ||
             XAIF_BBElemFilter::IsBBPreLoop(bbElem) ||
             XAIF_BBElemFilter::IsBBPostLoop(bbElem)) {
      // ---------------------------------------------------
      // Begin a structured loop
      // ---------------------------------------------------
      
      bool isDoLoop = (XAIF_BBElemFilter::IsBBForLoop(bbElem));

      // 1. Gather children
      MyDGNode* body = GetSuccessorAlongEdge(curNode, 1);
      MyDGNode* fallthru = GetSuccessorAlongEdge(curNode, 0);
      
      // 2. Translate (recursively) loop body
      pair<WN*, MyDGNode*> p = xlate_CFGstruct(wn_pu, cfg, body, xlated, ctxt);
      WN* bodyWN = p.first;
      
      // 3. Translate condition expression (and update/init statements)
      DOMElement* cond = 
        GetChildElement(bbElem, XAIFStrings.elem_Condition_x());
      DOMElement* condexpr = GetFirstChildElement(cond);      
      WN* condWN = NULL;
      if (isDoLoop) {
	condWN = TranslateExpressionSimple(condexpr, ctxt);
      } else {
	condWN = TranslateExpression(condexpr, ctxt);
      }
      
      DOMElement *init = NULL, *update = NULL;
      WN *initWN = NULL, *updateWN = NULL;
      if (XAIF_BBElemFilter::IsBBForLoop(bbElem)) {
        // Note: initWN and updateWN are STIDs
        init = GetChildElement(bbElem, XAIFStrings.elem_LpInit_x());
        update = GetChildElement(bbElem, XAIFStrings.elem_LpUpdate_x());
        initWN = TranslateStmt(init, ctxt);
        updateWN = TranslateStmt(update, ctxt);
      }
      
      // 4. Create control flow statement
      WN* stmtWN = NULL;
      if (isDoLoop) {
        WN* idxWN = WN_CreateIdname(WN_store_offset(initWN), WN_st(initWN));
        stmtWN = WN_CreateDO(idxWN, initWN, condWN, updateWN, bodyWN, NULL);
      }
      else if (XAIF_BBElemFilter::IsBBPreLoop(bbElem)) {
        stmtWN = WN_CreateWhileDo(condWN, bodyWN);
      }
      else if (XAIF_BBElemFilter::IsBBPostLoop(bbElem)) {
        stmtWN = WN_CreateDoWhile(condWN, bodyWN);
      }
      
      WN_INSERT_BlockLast(blkWN, stmtWN);
      curNode = fallthru;
    }      
    else if (XAIF_BBElemFilter::IsBBEndLoop(bbElem)) {
      // ---------------------------------------------------
      // End a structured loop
      // ---------------------------------------------------
      continueIteration = false;
    }
    else {
      FORTTK_DIE("Unknown XAIF basic block:\n" << *bbElem);
    }
  }
  
  return make_pair(blkWN, curNode);
}


// xlate_CFGunstruct: Helper for translating an unstructured CFG.  
// 
// Note: The CFG node (MyDGNode) id forms an implicit label number for
// each basic block.  We do not worry about interfering with original
// labels because we do not keep them.
static WN*
xlate_CFGunstruct(WN* wn_pu, DGraph* cfg, MyDGNode* startNode, 
                  set<DOMElement*>& xlated, XlationContext& ctxt)
{
  WN* blkWN = WN_CreateBlock();

  // Topological sort to ensure that, e.g., the exit node is last
  list<DGraph::Node*>* topoSortedCFG = TopologicalSort(cfg);  

#if 0
  std::cerr << "TopoSort: ";
  for (list<DGraph::Node*>::iterator it = topoSortedCFG->begin(); 
       it != topoSortedCFG->end(); ++it) {
    MyDGNode* n = dynamic_cast<MyDGNode*>(*it);
    std::cerr << n->getId() << " "; 
  }
  std::cerr << std::endl;
#endif

  // ---------------------------------------------------
  // We must generate labels that do not conflict with other labels in
  // the WHIRL code.  We use two maps to remember label values.
  // ---------------------------------------------------
  static unsigned int nextLblCntr = 1; // 0 is reserved
  map<MyDGNode*, unsigned> nodeToLblMap;
  map<MyDGNode*, unsigned> nodeToLoopContLblMap;
  
  // Initialize label maps
  for (list<DGraph::Node*>::iterator it = topoSortedCFG->begin(); 
       it != topoSortedCFG->end(); ++it) {
    MyDGNode* n = dynamic_cast<MyDGNode*>(*it);
    nodeToLblMap[n] = nextLblCntr++;
    
    // See notes on translating loops below
    DOMElement* bbElem = n->GetElem();
    if (XAIF_BBElemFilter::IsBBForLoop(bbElem) ||
        XAIF_BBElemFilter::IsBBPostLoop(bbElem)) {
      nodeToLoopContLblMap[n] = nextLblCntr++;
    } 
    else if (XAIF_BBElemFilter::IsBBPreLoop(bbElem)) {
      nodeToLoopContLblMap[n] = nodeToLblMap[n];
    }
  }
  
  // ---------------------------------------------------
  // Translate in topological order
  // ---------------------------------------------------
  for (list<DGraph::Node*>::iterator it = topoSortedCFG->begin(); 
       it != topoSortedCFG->end(); ++it) {
    MyDGNode* curNode = dynamic_cast<MyDGNode*>(*it);
    DOMElement* bbElem = curNode->GetElem();
    unsigned curLbl = nodeToLblMap[curNode];
    
    if (XAIF_BBElemFilter::IsBBEntry(bbElem) ||
        XAIF_BBElemFilter::IsBBExit(bbElem) ||
        XAIF_BBElemFilter::IsBB(bbElem)) {
      // ---------------------------------------------------
      // A non-control-flow basic block
      // ---------------------------------------------------
      MyDGNode* nextNode = GetSuccessor(curNode); // at most one outgoing edge
      unsigned nextLbl = (nextNode) ? nodeToLblMap[nextNode] : 0;
      WN* stmts = xlate_CFG_BasicBlock(wn_pu, curNode, ctxt, true, 
				       curLbl, nextLbl);
      WN_INSERT_BlockLast(blkWN, stmts);
    }
    else if (XAIF_BBElemFilter::IsBBBranch(bbElem)) {
      // ---------------------------------------------------
      // A branch with possibly unstructured control flow
      // ---------------------------------------------------
      unsigned int numOutEdges = curNode->num_outgoing();

      // 1. Translate condition expression
      DOMElement* cond = 
        GetChildElement(bbElem, XAIFStrings.elem_Condition_x());
      DOMElement* condexpr = GetFirstChildElement(cond);      
      WN* condWN = TranslateExpression(condexpr, ctxt);
      if (numOutEdges == 2) {
	// Because branches are 'structured switches', ensure we have
	// a boolean expression for an 'if'.
	condWN = CreateIfCondition(condWN);
      }
      
      // 2. Gather all outgoing edges, sorted by condition (specially
      // sort two-way branches into true-false order.)
      vector<MyDGEdge*> outedges(numOutEdges, NULL);
      DGraph::OutgoingEdgesIterator it = 
        DGraph::OutgoingEdgesIterator(curNode);
      for (int i = 0; (bool)it; ++it, ++i) {
        outedges[i] = dynamic_cast<MyDGEdge*>((DGraph::Edge*)it);
      }
      std::sort(outedges.begin(), outedges.end(), 
                sort_CondVal((numOutEdges != 2)));

      // 3. Create branch control flow
      WN* lblWN = WN_CreateLabel(curLbl, 0 /*label_flag*/, NULL);
      WN_INSERT_BlockLast(blkWN, lblWN);
      if (numOutEdges == 2) {
	// Create GOTOs for each child block
	vector<WN*> childblksWN(numOutEdges, NULL);
	for (int i = 0; i < outedges.size(); ++i) {
	  MyDGNode* n = dynamic_cast<MyDGNode*>(outedges[i]->sink());
	  WN* gotoblkWN = WN_CreateBlock();
	  WN* gotoWN = WN_CreateGoto(nodeToLblMap[n]);
	  WN_INSERT_BlockFirst(gotoblkWN, gotoWN);
	  childblksWN[i] = gotoblkWN;
	}
	
	// Create IF with GOTOs
	WN* ifWN = WN_CreateIf(condWN, childblksWN[0], childblksWN[1]);
	WN_INSERT_BlockLast(blkWN, ifWN);
      } 
      else {
	unsigned lastLbl = 0; // do not know last label
	
	// Create SWITCH with CASEGOTOs
	WN* switchWN = xlate_CFG_BranchMulti(curNode, condWN, lastLbl,
					     outedges, nodeToLblMap);
	WN_INSERT_BlockLast(blkWN, switchWN);
      }
    }
    else if (XAIF_BBElemFilter::IsBBEndBr(bbElem)) {
      // ---------------------------------------------------
      // EndBranch: a dummy basic block
      // ---------------------------------------------------
      MyDGNode* nextNode = GetSuccessor(curNode); // at most one outgoing edge
      unsigned nextLbl = (nextNode) ? nodeToLblMap[nextNode] : 0;
      WN* stmts = xlate_CFG_BasicBlock(wn_pu, curNode, ctxt, true, 
				       curLbl, nextLbl);
      WN_INSERT_BlockLast(blkWN, stmts);
    }
    else if (XAIF_BBElemFilter::IsBBForLoop(bbElem) ||
             XAIF_BBElemFilter::IsBBPreLoop(bbElem) ||
             XAIF_BBElemFilter::IsBBPostLoop(bbElem)) {
      // ---------------------------------------------------
      // A loop with possibly unstructured control flow
      // ---------------------------------------------------
      
      // XAIF Loop sub-graphs
      // --------------------
      //   ForLoop ---> [loopbody nodes...] ---> EndLoop--| 
      //     Init  \                                   <--| (backedge)
      //     Cond   \
      //     Update  \------------------------------------> fallthru block
      //             
      //   PreLoop and PostLoop are the same, but without special Init
      //   and Update statements.
      // 
      // Translation into unstructured WHIRL:
      // ForLoop               PreLoop               PostLoop
      // ----------------------------------------------------------------
      // label for_loop
      // Init
      // goto for_test                               
      // label for_cntnue                            label post_loop
      // Update                                      goto loop_body
      // label for_test        label pre_loop        label post_cntnue
      // if (Cond)             if (Cond)             if (Cond)
      //   goto loop_body        goto loop_body        goto loop_body
      // else                  else                  else
      //   goto fallthru_blk     goto fallthru_blk     goto fallthru_blk
      // 
      // ----------------------------------------------------------------
      //  [fallthru subgraph]  label loop_body
      //                       ... 
      //                       goto end_loop
      //
      //            [EndLoop]  label end_loop
      //                       goto for_cntnue/pre_loop/post_cntnue
      //
      // Note: Moving Init and Update statments out of the 'loop
      // scope' is not a problem -- i.e. there won't be symbol clashes
      // -- because in WHIRL the whole procedure is actually in the same
      // lexical scope.
      
      bool isDoLoop = (XAIF_BBElemFilter::IsBBForLoop(bbElem));
      
      // 1. Gather children
      MyDGNode* bodyNode = GetSuccessorAlongEdge(curNode, 1);
      MyDGNode* fallthruNode = GetSuccessorAlongEdge(curNode, 0);
      
      // 2. Translate condition expression (and update/init statements)
      DOMElement* cond = 
        GetChildElement(bbElem, XAIFStrings.elem_Condition_x());
      DOMElement* condexpr = GetFirstChildElement(cond);
      WN* condWN = NULL;
      if (isDoLoop) {
	condWN = TranslateExpressionSimple(condexpr, ctxt);
      } else {
	condWN = TranslateExpression(condexpr, ctxt);
      }
      
      DOMElement *init = NULL, *update = NULL;
      WN *initWN = NULL, *updateWN = NULL;
      if (XAIF_BBElemFilter::IsBBForLoop(bbElem)) {
        // Note: initWN and updateWN are STIDs
        init = GetChildElement(bbElem, XAIFStrings.elem_LpInit_x());
        update = GetChildElement(bbElem, XAIFStrings.elem_LpUpdate_x());
        initWN = TranslateStmt(init, ctxt);
        updateWN = TranslateStmt(update, ctxt);
      }
      
      // 3. Create loop control flow
      // Create loop label
      WN* lblWN = WN_CreateLabel(curLbl, 0 /*label_flag*/, NULL);
      WN_INSERT_BlockLast(blkWN, lblWN);
      
      // Create other special pre-loop statements
      WN* stmtWN = NULL;
      if (isDoLoop) {
        INT32 lbl_test = nextLblCntr++;
        INT32 lbl_cntnue = nodeToLoopContLblMap[curNode];
        
        WN_INSERT_BlockLast(blkWN, initWN); // Init
        WN* gotoWN = WN_CreateGoto(lbl_test);
        WN_INSERT_BlockLast(blkWN, gotoWN);
        WN* lbl1WN = WN_CreateLabel(lbl_cntnue, 0 /*label_flag*/, NULL);
        WN_INSERT_BlockLast(blkWN, lbl1WN);
        WN_INSERT_BlockLast(blkWN, updateWN); // Update
        WN* lbl2WN = WN_CreateLabel(lbl_test, 0 /*label_flag*/, NULL);
        WN_INSERT_BlockLast(blkWN, lbl2WN);
      }
      else if (XAIF_BBElemFilter::IsBBPostLoop(bbElem)) {
        INT32 lbl_cntnue = nodeToLoopContLblMap[curNode];

        WN* gotoWN = WN_CreateGoto(nodeToLblMap[bodyNode]);
        WN_INSERT_BlockLast(blkWN, gotoWN);
        WN* lblWN = WN_CreateLabel(lbl_cntnue, 0 /*label_flag*/, NULL);
        WN_INSERT_BlockLast(blkWN, lblWN);
      }
      
      // Create 'if (Cond)'
      WN* thenblkWN = WN_CreateBlock();
      WN* elseblkWN = WN_CreateBlock();
      WN* thenWN = WN_CreateGoto(nodeToLblMap[bodyNode]);
      WN* elseWN = WN_CreateGoto(nodeToLblMap[fallthruNode]);
      WN_INSERT_BlockFirst(thenblkWN, thenWN);
      WN_INSERT_BlockFirst(elseblkWN, elseWN);
      
      WN* ifWN = WN_CreateIf(condWN, thenblkWN, elseblkWN);
      WN_INSERT_BlockLast(blkWN, ifWN);
    }
    else if (XAIF_BBElemFilter::IsBBEndLoop(bbElem)) {
      // ---------------------------------------------------
      // The loop back-branch: loop back to continue branch!
      // ---------------------------------------------------
      MyDGNode* nextNode = GetSuccessor(curNode); // at most one outgoing edge
      unsigned nextLbl = (nextNode) ? nodeToLoopContLblMap[nextNode] : 0;
      WN* stmts = xlate_CFG_BasicBlock(wn_pu, curNode, ctxt, true, 
				       curLbl, nextLbl);
      WN_INSERT_BlockLast(blkWN, stmts);
    }
    else {
      FORTTK_DIE("Unknown XAIF basic block:\n" << *bbElem);
    }
  }

  // ---------------------------------------------------
  // Cleanup
  // ---------------------------------------------------
  delete topoSortedCFG;
  
  return blkWN;
}  


// xlate_CFG_BasicBlock: Translate a non-control-flow basic block.
// Optionally skips GOTOs and LABELs within 'wn_pu'.
// Optionally adds a label at the beginning of the block and a
// 'fallthru-goto' at the end if non-zero labels are provided.
static WN*
xlate_CFG_BasicBlock(WN *wn_pu, MyDGNode* curBB, XlationContext& ctxt, 
		     bool skipMarkeredGotoAndLabels, 
		     unsigned newCurBBLbl, unsigned newNextBBLbl)
{
  DOMElement* bbElem = curBB->GetElem();

  // typically addNewGotoAndLabels is only true when
  // skipOldGotoAndLabels is also true
  bool skipOldGotoAndLabels = skipMarkeredGotoAndLabels;
  bool addNewGotoAndLabels = (newCurBBLbl != 0); 
  
  // 1. Translate (if we add our own goto's and labels, then we need
  // to throw away any original goto and label at the end and
  // beginning of the block)
  WN* stmtblk = TranslateBasicBlock(wn_pu, bbElem, ctxt, skipOldGotoAndLabels);
  
  // 2. If necessary, add a label to front and goto at end
  if (addNewGotoAndLabels) {
    WN* lblWN = WN_CreateLabel(newCurBBLbl, 0 /*label_flag*/, NULL);
    WN_INSERT_BlockFirst(stmtblk, lblWN);
    
    if (newNextBBLbl != 0) {
      WN* gotoWN = WN_CreateGoto(newNextBBLbl);
      WN_INSERT_BlockLast(stmtblk, gotoWN); 
    }
  }
  
  return stmtblk;
}


// xlate_CFG_BranchMulti: abstract translation of multi-way branches
static WN*
xlate_CFG_BranchMulti(MyDGNode* curNode, WN* condWN, unsigned lastLbl,
		      vector<MyDGEdge*>& outedges,
		      map<MyDGNode*, unsigned>& nodeToLblMap)
{
  // Case values are in ascending order; the default case (if any)
  // will be at the beginning and have a false condition attribute
  
  // Create default goto if necessary
  WN* defltWN = NULL;
  int defltIdx = -1;
  if (!GetHasConditionAttr(outedges[0]->GetElem())) {
    defltIdx = 0;
    MyDGNode* n = dynamic_cast<MyDGNode*>(outedges[0]->sink());
    unsigned gotolbl = nodeToLblMap[n];
    defltWN = WN_CreateGoto(gotolbl);
  }
  
  // Create casegoto for each block
  WN* casegotoBlkWN = WN_CreateBlock();
  int numcases = outedges.size() - (defltIdx + 1);
  for (int i = defltIdx + 1; i < outedges.size(); ++i) {
    DOMElement* elemEdge = outedges[i]->GetElem();
    MyDGNode* n = dynamic_cast<MyDGNode*>(outedges[i]->sink());
    
    INT64 caseval = GetCondAttr(elemEdge);
    WN* wn = WN_CreateCasegoto(caseval, nodeToLblMap[n]);
    WN_INSERT_BlockLast(casegotoBlkWN, wn);
  }
  
  // Create switch
  WN* switchWN = WN_CreateSwitch(numcases, condWN, casegotoBlkWN,
				 defltWN, lastLbl);
  
  return switchWN;
}


// TranslateBasicBlock: Translate a non-control-flow basic block
static WN*
TranslateBasicBlock(WN *wn_pu, const DOMElement* bbElem, XlationContext& ctxt,
                    bool skipMarkeredGotoAndLabels)
{
  WN* blkWN = WN_CreateBlock();

  // -------------------------------------------------------
  // 1. Find some info now to prevent several recalculations
  // -------------------------------------------------------
  // FIXME: use parent map -- w2x does not need to generate this id list 
  IdList<WNId>* idlist = GetWNIdList(bbElem); // FIXME
  WN* origblkWN = FindWNBlock(bbElem, idlist, ctxt);
  if (idlist->size() > 0) { 
    FORTTK_ASSERT(origblkWN, "Could not find WHIRL block for:\n" << *bbElem);
  }

  // -------------------------------------------------------
  // 2. Translate statements
  // -------------------------------------------------------
  XAIF_BBStmtElemFilter filt;
  for (DOMElement* stmt = GetChildElement(bbElem, &filt);
       (stmt); stmt = GetNextSiblingElement(stmt, &filt)) {
    WN* wn = NULL;
    if (XAIF_BBStmtElemFilter::IsMarker(stmt)) {
      bool isGotoOrLabel = (IsTagPresent(stmt, XAIFStrings.tag_StmtGoto()) ||
                            IsTagPresent(stmt, XAIFStrings.tag_StmtLabel()));
      bool skip = (isGotoOrLabel && skipMarkeredGotoAndLabels);
      if (!skip) {
        WNId id = GetWNId(stmt);
        WN* foundWN = ctxt.FindWN(id, true /* mustFind */);
        wn = WN_COPY_Tree(foundWN);
        PatchWNStmt(wn, ctxt); // FIXME
      }
    }
    else {
      wn = TranslateStmt(stmt, ctxt);
    }
    if (wn) {
      WN_INSERT_BlockLast(blkWN, wn);
    }
  }
  
  return blkWN;
}


//****************************************************************************
// ControlFlowGraph -- basic block patching algorithm
//****************************************************************************

static void
TranslateBB_OLD(WN *wn_pu, const DOMElement* bbElem, XlationContext& ctxt)
{
  if (XAIF_BBElemFilter::IsBB(bbElem)) {
      xlate_BasicBlock_OLD(wn_pu, bbElem, ctxt);
  } 
  else if (XAIF_BBElemFilter::IsBBBranch(bbElem)
           || XAIF_BBElemFilter::IsBBPreLoop(bbElem)
           || XAIF_BBElemFilter::IsBBPostLoop(bbElem)) {
    xlate_BBCond_OLD(wn_pu, bbElem, ctxt);
  } 
  else if (XAIF_BBElemFilter::IsBBForLoop(bbElem)) {
    // FIXME: what to do with ForLoops?
  } 
  else {
    // skip anything else for now
  }
}


static void
xlate_BasicBlock_OLD(WN *wn_pu, const DOMElement* bbElem, XlationContext& ctxt)
{
  // -------------------------------------------------------
  // 1. Find some info now to prevent several recalculations
  // -------------------------------------------------------
  IdList<WNId>* idlist = GetWNIdList(bbElem);
  WN* blkWN = FindWNBlock(bbElem, idlist, ctxt);
  if (idlist->size() > 0) { 
    FORTTK_ASSERT(blkWN, "Could not find WHIRL block for:\n" << *bbElem);
  }
  
  // -------------------------------------------------------
  // 2. Translate statements
  // -------------------------------------------------------  
  DOMElement* begXAIF = NULL, *endXAIF = NULL;
  WN* begWN = NULL, *endWN = NULL;
  while (FindNextStmtInterval(bbElem, idlist, ctxt.GetIdToWNMap(), blkWN,
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
      WN* wn = ctxt.FindWN(id, true /* mustFind */);
      PatchWNStmt(wn, ctxt);
    }
  }
  
  // -------------------------------------------------------
  // 4. Cleanup
  // -------------------------------------------------------
  delete idlist;
}


static void
xlate_BBCond_OLD(WN* wn_pu, const DOMElement* bbElem, XlationContext& ctxt)
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
    FORTTK_ASSERT(idlist->size() == 1, "Invalid id list:\n" << *cond);
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

  case OPR_SWITCH:
    condKid = -1;
    break; // integer expression
    
  default: 
    FORTTK_DIE(FORTTK_UNEXPECTED_OPR << OPERATOR_name(opr));
  }
  
  // -------------------------------------------------------
  // 2. Ensure the condition expression is patched
  // -------------------------------------------------------
  if (condKid >= 0) {
    PatchWNExpr(wn, condKid /* kidno */, ctxt);
  }
}


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
  } 
  else if (endXAIF) {
    begXAIF = GetNextSiblingElement(endXAIF); // successive intervals (tmp)
  } 
  else {
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
  } 
  else if (boundary == 1) {
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
        FORTTK_ASSERT(prevWN, "Internal error");

        wn = prevWN;
      }
    }
    if (!wn && bbIdList->size() > 0) {
      wn = wnmap->Find(bbIdList->back(), true /* mustFind */);
    }
  } 
  else {
    FORTTK_DIE("Internal error.");
  }
  
  return wn;
}


// FindWNBlock: Given an XAIF basic block element, find the
// corresponding WHIRL block.
static WN* 
FindWNBlock(const DOMElement* bbElem, IdList<WNId>* idlist, 
	    XlationContext& ctxt)
{
  // We pass 'idlist' to avoid continual reparsing
  WN* wn = NULL;
  if (idlist->size() > 0) {
    WNId id = idlist->front();
    wn = ctxt.FindWN(id, true /* mustFind */);
  }
  
  WN* blk = NULL;
  if (wn) {
    blk = ctxt.FindParentBlockWN(wn);
  }
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
// Scopes and Symbols
//****************************************************************************

Symbol*
xaif2whirl::GetSymbol(const DOMElement* elem, XlationContext& ctxt)
{
  const XMLCh* scopeIdX = elem->getAttribute(XAIFStrings.attr_scopeId_x());
  const XMLCh* symIdX = elem->getAttribute(XAIFStrings.attr_symId_x());

  XercesStrX scopeId = XercesStrX(scopeIdX);
  XercesStrX symId = XercesStrX(symIdX);
  
  FORTTK_ASSERT(strcmp(scopeId.c_str(), "") != 0 && 
		strcmp(symId.c_str(), "") != 0,
		"Invalid id attribute:\n" << *elem);
  
  return ctxt.FindSym(scopeId.c_str(), symId.c_str());
}


Symbol*
GetOrCreateSymbol(const char* sname, XlationContext& ctxt)
{
  // FIXME: make more general
  bool active = false;
  
  // FIXME: need to associate current PU with a scope id...
  const char* scopeId = "1"; // assume global for now
  
  XAIFSymToSymbolMap* symMap = ctxt.GetXAIFSymToSymbolMap();
  Symbol* sym = symMap->Find(scopeId, sname);
  if (!sym) {
    // FIXME: use CreateST...
    TY_IDX ty = MTYPE_To_TY(MTYPE_F8);
    SYMTAB_IDX level = GLOBAL_SYMTAB; // FIXME: coordinate with scopeId
    ST* st = New_ST(level);
    ST_Init(st, Save_Str(sname), CLASS_VAR, SCLASS_AUTO, EXPORT_LOCAL, ty);
    
    sym = new Symbol(st, 0, active);
    symMap->Insert(scopeId, sname, sym);
  }
  return sym;
}


Symbol*
GetOrCreateBogusTmpSymbol(XlationContext& ctxt)
{
  static const char* sname = "OpenAD_bogus";
  return GetOrCreateSymbol(sname, ctxt);
}


//****************************************************************************

static void
xlate_Scope(const DOMElement* elem, XAIFSymToSymbolMap* symMap, 
            XlationContext& ctxt)
{
  // Find the corresponding WHIRL symbol table (ST_TAB)
  SymTabId symtabId = GetSymTabId(elem);
  pair<ST_TAB*, PU_Info*> stab = ctxt.FindSymTab(symtabId);
  
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
  XAIF_SymbolElemFilter filt;
  for (DOMElement* e = GetChildElement(elem, &filt);
       (e); e = GetNextSiblingElement(e, &filt)) {
    xlate_Symbol(e, scopeId, pu, symMap);
  }
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
  
  // For symbols not introduced by xaifBooster, *one* of the following applies
  SymId symId = GetSymId(elem); // non-zero for a normal symbol
  WNId wnId = GetWNId(elem);    // non-zero for a scalarized symbol
  
  bool normalSym = (wnId == 0); // represents some non-scalarized symbol
  bool active = GetActiveAttr(elem);
  
  const XMLCh* symNmX = elem->getAttribute(XAIFStrings.attr_symId_x());
  XercesStrX symNm = XercesStrX(symNmX);
  
  // 2. Find or Create WHIRL symbol
  ST* st = NULL;
  if (normalSym) {
    if (symId == 0) {
      // Create the symbol
      st = CreateST(elem, level, symNm.c_str());
    } else {
      // Find the symbol and change type if necessary
      st = &(Scope_tab[level].st_tab->Entry(symId));
      if (active && ST_class(st) == CLASS_VAR) {
	ConvertToActiveType(st);
      }
    }
  } 
  
  // 3. Create our own symbol structure and add to the map
  Symbol* sym = new Symbol(st, wnId, active);
  symMap->Insert(scopeId, symNm.c_str(), sym);
} 


//****************************************************************************
// Attribute retrieval and 'annotation' attribute functions
//****************************************************************************

bool
xaif2whirl::GetBoolAttr(const DOMElement* elem, XMLCh* attr, bool default_val)
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


int
xaif2whirl::GetIntAttr(const DOMElement* elem, XMLCh* attr, int default_val)
{
  const XMLCh* aX = elem->getAttribute(attr);
  XercesStrX a = XercesStrX(aX);

  int a_int = default_val;
  if (strlen(a.c_str()) > 0) { // if attribute exists
    a_int = strtol(a.c_str(), (char **)NULL, 10);
  }
  return a_int;
}


bool
xaif2whirl::GetHasConditionAttr(const DOMElement* elem)
{
  return GetBoolAttr(elem, XAIFStrings.attr_hasCondval_x(), false /*default*/);
}


unsigned int
xaif2whirl::GetCondAttr(const DOMElement* elem)
{
  unsigned int val = 0;
  if (GetHasConditionAttr(elem)) {
    val = GetIntAttr(elem, XAIFStrings.attr_condval_x(), 0 /* default */);
  }
  return val;
}


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
  return GetIntAttr(elem, XAIFStrings.attr_position_x(), 0 /* default */);
}


bool
xaif2whirl::IsTagPresent(const DOMElement* elem, const char* tag)
{
  const XMLCh* annot = (elem) ? elem->getAttribute(XAIFStrings.attr_annot_x())
    : NULL;
  XercesStrX annotStr = XercesStrX(annot);
  return IsTagPresent(annotStr.c_str(), tag);
}


bool
xaif2whirl::IsTagPresent(const char* annotstr, const char* tag)
{
  return (strstr(annotstr, tag) != NULL);
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


std::string
xaif2whirl::GetIntrinsicKey(const DOMElement* elem)
{
  const XMLCh* annot = (elem) ? elem->getAttribute(XAIFStrings.attr_annot_x())
    : NULL;
  XercesStrX annotStr_x = XercesStrX(annot);
  const char* annotStr = annotStr_x.c_str();

  // Note: Sun wants the first arg to strstr to be char*.  Stupid.
  std::string key;
  char *start = NULL, *end = NULL;
  start = strstr(const_cast<char*>(annotStr), XAIFStrings.tag_IntrinsicKey());
  if (start) {
    start = start + strlen(annotStr);
    end = strstr(start, XAIFStrings.tag_End());
  }
  if (start && end) {
    for (char* p = start; p < end; ++p) { key += *p; }
  }
  
  return key;
}


PREG_IDX
xaif2whirl::GetPregId(const DOMElement* elem)
{
  return GetId<PREG_IDX>(elem, XAIFStrings.tag_PregId());
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
  FORTTK_ASSERT(endptr && strncmp(endptr, XAIFStrings.tag_End(), len) == 0,
		"Could not find '" << tag << "' within " << idstr);
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
      FORTTK_ASSERT(id != 0, "Found invalid " << tag << " id " << id 
		    << " within " << idstr);
      idlist->push_back(id); // we found some digits to convert
    }

    tok = strtok((char*)NULL, ":");
    if (endptr && strcmp(endptr, XAIFStrings.tag_End()) == 0) {
      // we should be done with iteration now
      FORTTK_ASSERT(tok == NULL, "Could not find end of " << tag 
		    << " within " << idstr);
    }
  }

  return idlist;
}


//****************************************************************************
// WHIRL Creation functions
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


WN* 
CreateBoolConst(unsigned int val)
{
  // We use OPR_CONST instead of OPR_INTCONST so that we can set the
  // boolean flag for a TY.  Note, however, that an OPC_??CONST cannot
  // have the boolean rtype.
  
  // Use a boolean mtype for the new ST so that it is safe to set the
  // associated TY's 'is_logical' flag.
  TCON tcon = Host_To_Targ(MTYPE_B, val); // use boolean mtype here
  ST* st = New_Const_Sym(Enter_tcon(tcon), MTYPE_To_TY(TCON_ty(tcon)));
  Set_TY_is_logical(ST_type(st));
  WN* wn = WN_CreateConst(OPC_I4CONST, st);
  return wn;
}


static WN*
CreateOpenADReplacementBeg(const char* placeholder)
{
  std::string com = "$OpenAD$ BEGIN REPLACEMENT ";
  com += placeholder;
  WN* comWN = WN_CreateComment((char*)com.c_str());
  return comWN;
}


static WN*
CreateOpenADReplacementEnd()
{
  WN* comWN = WN_CreateComment("$OpenAD$ END REPLACEMENT");
  return comWN;
}


// CreateIfCondition: Convert an expression that is a var-reference to
// a comparison.  E.g.
//   if (OpenAD_Symbol_2303) --> if (OpenAD_Symbol_2303 .ne. 0)
static WN* 
CreateIfCondition(WN* condWN)
{
  WN* newcondWN = condWN;
  
  TY_IDX ty = WN_Tree_Type(condWN);
  if (OPERATOR_is_load(WN_operator(condWN)) && !TY_is_logical(ty)) {
    WN* zeroWN = WN_Zerocon(Boolean_type); // CreateBoolConst(0);
    newcondWN = WN_NE(Boolean_type, condWN, zeroWN);
  }
  
  return newcondWN;
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
  
  // FIXME: assume only
  FORTTK_ASSERT(strcmp(kind.c_str(), "variable") == 0,
		FORTTK_UNIMPLEMENTED << "Cannot create non-variable symbols");
    
  // 1. Find basic type according to 'type' and 'active'
  TY_IDX basicTy = XAIFTyToWHIRLTy(type.c_str());
  if (active) {
    basicTy = ActiveTypeTyIdx;
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
    } 
    else {
      // FIXME: add tensors
      FORTTK_DIE(FORTTK_UNIMPLEMENTED << "Cannot translate > 2-dimensional variables");
    }
    ty = MY_Make_Array_Type(basicTy, ndim, len);
  }
  
  // 3. Find storage class and export scope 
  ST_SCLASS sclass = SCLASS_AUTO; // default: auto implies local storage
  ST_EXPORT escope = EXPORT_LOCAL_INTERNAL;
  if (level == GLOBAL_SYMTAB) {
    sclass = SCLASS_COMMON;
    escope = EXPORT_LOCAL;
  }
  
  // 4. Create the new symbol
  ST* st = New_ST(level);
  ST_Init(st, Save_Str(nm), CLASS_VAR, sclass, escope, ty);
  
  // 5. For global symbols, modify and add to a global/common block
  if (level == GLOBAL_SYMTAB) {
    //FIXME ConvertIntoGlobalST(st);
  }
  
  return st;
}


static ST* 
ConvertIntoGlobalST(ST* st)
{
  static ST* OpenADCommonBlockST = NULL;
  static TY_IDX OpenADCommonBlockTY = 0;
  static UINT64 OpenADCommonBlockOffset = 0;
  static FLD_HANDLE OpenADCommonBlockLastField = FLD_HANDLE();
  
  // Create common block ST if necessary
  bool isFirst = false;
  if (!OpenADCommonBlockST) {
    // cf. cwh_stab_common_ST()
    isFirst = true;

    INT64 sz = 0;
    TY& ty = New_TY(OpenADCommonBlockTY); // sets 'OpenADCommonBlockTY'
    TY_Init(ty, sz, KIND_STRUCT, MTYPE_M, Save_Str(".openad.common."));
    // Note: Common block fields are created below
    
    OpenADCommonBlockST = New_ST(GLOBAL_SYMTAB);
    ST_Init(OpenADCommonBlockST, Save_Str("OpenADGlobals"), CLASS_VAR, 
	    SCLASS_COMMON, EXPORT_LOCAL, OpenADCommonBlockTY);
    
    //Set_ST_base(ST& s, *OpenADCommonBlock); // base symbol at the procedure?
    //Set_ST_ofst(ST& s, UINT64 offset);
  }
  
  // Create a new field for common block type
  FLD_HANDLE fld = New_FLD();
  TY_IDX fldTy = ST_type(st);
  FLD_Init(fld, Save_Str(ST_name(st)), fldTy, OpenADCommonBlockOffset);
  if (isFirst) {
    Set_TY_fld(OpenADCommonBlockTY, fld);
  } else {
    Clear_FLD_last_field(OpenADCommonBlockLastField); // fld is now the last
  }
  Set_FLD_last_field(fld);
  OpenADCommonBlockLastField = fld;
  
  // Increase size of common block
  UINT64 sz = TY_size(ST_type(st));
  OpenADCommonBlockOffset += sz;
  Set_TY_size(OpenADCommonBlockTY, sz);
  
  // Modify/Add 'st' to common block
  Set_ST_base(*st, *OpenADCommonBlockST);
  Set_ST_ofst(*st, OpenADCommonBlockOffset);

  return st;
}


static void 
DeclareActiveTypes()
{
  // We create pseudo active types aliased to F8
  static const char* psTypeNames[] = 
    { "OpenADTy_active", "OpenADTy_active_init" };
  static unsigned psTypeNamesSZ = sizeof(psTypeNames) / sizeof(char*);
  
  static TY_IDX* psTyIdx[] = 
    { &ActiveTypeTyIdx, &ActiveTypeInitializedTyIdx };
  static unsigned psTyIdxSZ = psTypeNamesSZ;
  
  for (unsigned i = 0; i < psTypeNamesSZ; ++i) {
    TY_IDX ty_idx;
    TY& ty = New_TY(ty_idx); // sets 'ty_idx'
    TY_Init(ty, 8, KIND_SCALAR, MTYPE_F8, Save_Str(psTypeNames[i]));
    Set_TY_align(ty_idx, 8);
    Set_TY_is_external(ty);
    *(psTyIdx[i]) = ty_idx;
  }
  
#if 0
  // Creating a structure type
  
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
  TY_Init(activeTy, activeSz, KIND_STRUCT, MTYPE_M, Save_Str("active"));
  Set_TY_fld(activeTy, valFld); // location of first field
  Set_TY_align(activeTyIdx, 8);
  Set_TY_is_sequence(activeTy);
  Set_TY_is_external(activeTy);
  
  
  // Creating structure references in WHIRL
  // wn = reference that needs %d added
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
    FORTTK_DIE(FORTTK_UNEXPECTED_OPR << OPERATOR_name(opr));
  }
  return retWN;
#endif  

}


// ConvertToActiveType: Given a symbol, convert it to active type
static void 
ConvertToActiveType(ST* st)
{
  // -------------------------------------------------------
  // 1. Setup
  // -------------------------------------------------------
  // Find the type that will be replaced
  TY_IDX ty = ST_type(st);
  if (TY_kind(ty) == KIND_POINTER) { // only have one level of indirection
    ty = TY_pointed(ty);
  }

  // Get the replacement type
  TY_IDX newBaseTy = ActiveTypeTyIdx;
  if (ST_is_initialized(st)) {
    INITO_IDX inito = Find_INITO_For_Symbol(st);
    if (inito != (INITO_IDX)0) {
      newBaseTy = ActiveTypeInitializedTyIdx;
    }
  }

  // -------------------------------------------------------
  // 2. Change the type of this symbol
  // -------------------------------------------------------
  if (TY_kind(ty) == KIND_SCALAR) {
    Set_ST_type(*st, newBaseTy);
  }
  else if (TY_kind(ty) == KIND_ARRAY) {
    // just change the element type
    Set_TY_etype(ty, newBaseTy);
    // alignment, etc. should be ok
  } 
  else {
    FORTTK_DIE("Unexpected type kind: " << TY_kind(ty));
  }
  
  // -------------------------------------------------------
  // 3. If this symbol is part of a common block, patch up types in
  // the common block fields.  Note that we only need to change
  // scalars -- arrays have been effectively changed above
  // -------------------------------------------------------
  if (TY_kind(ty) == KIND_SCALAR 
      && Stab_Is_Based_At_Common_Or_Equivalence(st)) {
    TY_IDX base_ty = ST_type(ST_base(st));
    mUINT64 offset = ST_ofst(st); // offset into base symbol
    
    // find field with correct offset or symbol
    FLD_HANDLE fld = My_FLD_get_to_field(base_ty, offset);
    Set_FLD_type(fld, newBaseTy);
  }
}


// FIXME: cf. extern FLD_HANDLE FLD_get_to_field(...)
// FIXME: this is very inefficient; also we could abstract this out. 
static FLD_HANDLE 
My_FLD_get_to_field(TY_IDX struct_ty_idx, UINT64 ofst)
{
  FLD_ITER fld_iter = Make_fld_iter(TY_fld(struct_ty_idx));
  do {
    FLD_HANDLE fld(fld_iter);
    UINT64 cur_ofst = FLD_ofst(fld);
    if (cur_ofst == ofst) {
      return fld;
    }
  } while (!FLD_last_field(fld_iter++));
  
  return FLD_HANDLE();
}


// FIXME: modify symtab.cxx if this works out
static TY_IDX
MY_Make_Array_Type1 (TYPE_ID elem_ty, INT32 ndim, INT64 len)
{
  return MY_Make_Array_Type(MTYPE_To_TY (elem_ty), ndim, len);
}


// FIXME: Available in symtab_utils.h / symtab.cxx

static TY_IDX
MY_Make_Array_Type (TY_IDX elem_ty, INT32 ndim, INT64 len)
{
    INT64 elem_sz = TY_size (elem_ty);
    UINT elem_align = TY_align(elem_ty);
    FORTTK_ASSERT(elem_sz > 0 && elem_align > 0,
		  "Cannot make an array of " << TY_name(elem_ty));
    
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


static TY_IDX
XAIFTyToWHIRLTy(const char* type)
{
  TY_IDX ty = 0;
  if (strcmp(type, "real") == 0) {
    ty = MTYPE_To_TY(MTYPE_F8);
  } 
  else if (strcmp(type, "integer") == 0) {
    ty = MTYPE_To_TY(DefaultMTypeInt);
  } 
  else {
    // FIXME: don't know about anything else yet
    FORTTK_DIE(FORTTK_UNIMPLEMENTED << "Unknown XAIF type: " << type);
  }
  return ty;
}


//****************************************************************************
// MyDGNode routines
//****************************************************************************

MyDGNode*
GetSuccessor(MyDGNode* node, bool succIsOutEdge)
{
  int numSucc = (succIsOutEdge) ? node->num_outgoing() : node->num_incoming();
  if (numSucc == 0) {
    return NULL;
  }
  else if (numSucc > 1) {
    DOMElement* elem = node->GetElem();
    FORTTK_DIE("Cannot find unique successor to graph node; found " << numSucc
	       << ":\n" << *elem);
  }
  
  // We know there is one successor
  MyDGNode* succ = NULL;
  if (succIsOutEdge) {
    DGraph::SinkNodesIterator it = DGraph::SinkNodesIterator(node);
    succ = dynamic_cast<MyDGNode*>((DGraph::Node*)it);
  }
  else {
    DGraph::SourceNodesIterator it = DGraph::SourceNodesIterator(node);
    succ = dynamic_cast<MyDGNode*>((DGraph::Node*)it);
  }
  return succ;
}


MyDGNode*
GetSuccessorAlongEdge(MyDGNode* node, unsigned int condition, 
                      bool succIsOutEdge)
{
  MyDGNode* succ = NULL;
  int numSucc = (succIsOutEdge) ? node->num_outgoing() : node->num_incoming();
  
  if (succIsOutEdge) {
    DGraph::OutgoingEdgesIterator it = DGraph::OutgoingEdgesIterator(node);
    for ( ; (bool)it; ++it) {
      MyDGEdge* edge = dynamic_cast<MyDGEdge*>((DGraph::Edge*)it);
      DOMElement* e = edge->GetElem();
      
      unsigned int cond = GetCondAttr(e);
      if (condition == cond) {
        succ = dynamic_cast<MyDGNode*>(edge->sink());
        break;
      }
    }
  }
  else {
    FORTTK_DIE(FORTTK_UNIMPLEMENTED << "Transform into a template.");
  }
  return succ;
}


// CreateCFGraph: Given an XAIF control flow graph, create and
// return a CFG where CFG nodes point to XAIF CVG vertices.
static DGraph* 
CreateCFGraph(const DOMElement* cfgElem)
{
  MyDGNode::resetIds();
  DGraph* g = new DGraph;
  VertexIdToMyDGNodeMap m;
  
  // -------------------------------------------------------
  // Create the graph
  // -------------------------------------------------------
  XAIF_BBElemFilter filt;
  for (DOMElement* elem = GetChildElement(cfgElem, &filt);
       (elem); elem = GetNextSiblingElement(elem, &filt)) {
    if (XAIF_BBElemFilter::IsEdge(elem)) {
      // Add an edge to the graph. 
      
      // Find src and target (sink) nodes. 
      const XMLCh* srcX = elem->getAttribute(XAIFStrings.attr_source_x());
      const XMLCh* targX = elem->getAttribute(XAIFStrings.attr_target_x());
      XercesStrX src = XercesStrX(srcX);
      XercesStrX targ = XercesStrX(targX);

      MyDGNode* gn1 = m[std::string(src.c_str())];  // source
      MyDGNode* gn2 = m[std::string(targ.c_str())]; // target
      FORTTK_ASSERT(gn1 && gn2, "Invalid edge in CFG:\n" << *elem);

      MyDGEdge* ge = new MyDGEdge(gn1, gn2, elem); // src, targ
      g->add(ge);
    } 
    else {
      // Add a vertex to the graph
      const XMLCh* vidX = elem->getAttribute(XAIFStrings.attr_Vid_x());
      XercesStrX vid = XercesStrX(vidX);
      FORTTK_ASSERT(strlen(vid.c_str()) > 0, 
		    "Invalid vertex in CFG:\n" << *elem);

      MyDGNode* gn = new MyDGNode(elem);
      g->add(gn);
      m[std::string(vid.c_str())] = gn;
      
      // Set the graph root if necessary
      const XMLCh* name = elem->getNodeName();
      if (XMLString::equals(name, XAIFStrings.elem_BBEntry_x())) {
        g->set_root(gn);
      }
    } 
  }
  
  return g;
}


// DumpDotGraph:

static std::string
DumpDotGraph_GetNodeName(MyDGNode* n);

static void
DDumpDotGraph(DGraph* graph)
{
  DumpDotGraph(std::cerr, graph);
}

static void
DumpDotGraph(std::ostream& os, DGraph* graph)
{
  os << "digraph MyGraph {\n";
  os << "  graph [ ];\n"
     << "  node [ fontsize = \"10\" ];\n"
     << "  edge [ ];\n"
     << std::endl;
  
  for (DGraph::EdgesIterator edgesIt(*graph); (bool)edgesIt; ++edgesIt) {
    DGraph::Edge* e = (DGraph::Edge*)edgesIt;
    MyDGNode* src = dynamic_cast<MyDGNode*>(e->source());
    MyDGNode* snk = dynamic_cast<MyDGNode*>(e->sink());
    std::string srcNm = DumpDotGraph_GetNodeName(src);
    std::string snkNm = DumpDotGraph_GetNodeName(snk);
    os << "  \"" << srcNm << "\" -> \"" << snkNm << "\";\n";
  }
  os << "}" << std::endl;
}

static std::string
DumpDotGraph_GetNodeName(MyDGNode* n) 
{
  std::string name;
  
  // MyDGNode portion
  const char* nodeIdStr = Num2Str(n->getId(), "%u");
  name += nodeIdStr;

  // XAIF portion
  DOMElement* elem = n->GetElem();
  const XMLCh* xaifNameX = elem->getNodeName();
  XercesStrX   xaifName = XercesStrX(xaifNameX);
  const XMLCh* vidX = elem->getAttribute(XAIFStrings.attr_Vid_x());
  XercesStrX   vid = XercesStrX(vidX);  
  name += ", (";
  name += vid.c_str();
  name += ", ";
  name += xaifName.c_str();
  name += ")";
  
  return name;
}


// TopologicalSort: [FIXME: put in OpenAnalysis]

#define TOPOSORT_WHITE 0 /* node has not been seen */
#define TOPOSORT_GREY  1 /* seen but not all children have been visited */
#define TOPOSORT_BLACK 2 /* seen and all children have been visited */

static void 
TopoSortLocal(list<DGraph::Node*>& sorted, DGraph* g, DGraph::Node* node, 
              map<DGraph::Node*, unsigned>& visited);

static list<DGraph::Node*>*
TopologicalSort(DGraph* graph)
{
  list<DGraph::Node*>* sorted = new list<DGraph::Node*>;

  // A map to record where we are in the DFS search
  // [Could gather all nodes into a vector and then create a vector
  // based map to ensure memory locality]
  map<DGraph::Node*, unsigned> visited;
  for (DGraph::NodesIterator nodeIt(*graph); (bool)nodeIt; ++nodeIt) {
    DGraph::Node* n = (DGraph::Node*)nodeIt;
    visited[n] = TOPOSORT_WHITE;
  }
  
  // Perform a sort on the root node
  DGraph::Node* root = dynamic_cast<DGraph::Node*>(graph->root());
  TopoSortLocal(*sorted, graph, root, visited);
  
  // Now make sure we find nodes that could not be reached from the root
  for (DGraph::NodesIterator nodeIt(*graph); (bool)nodeIt; ++nodeIt) {
    DGraph::Node* n = (DGraph::Node*)nodeIt;
    if (visited[n] == TOPOSORT_WHITE) {
      TopoSortLocal(*sorted, graph, n, visited);
    }
  }
  
  return sorted;
}

static void 
TopoSortLocal(list<DGraph::Node*>& sorted, DGraph* g, DGraph::Node* node, 
              map<DGraph::Node*, unsigned>& visited)
{
  if (!node) { return; }
  
  if (visited[node] == TOPOSORT_BLACK) { return; }
  
  // Note: If node is already GREY we have a loop.  Continue
  // processing, but in a special way to avoid infinite loops.
  bool isLoop = false;
  if (visited[node] == TOPOSORT_GREY) {
    isLoop = true; 
  } else {
    visited[node] = TOPOSORT_GREY;
  }
  
  // Visit each outgoing edge, like DFS
  for (DGraph::SinkNodesIterator it(node); (bool)it; ++it) {
    DGraph::Node* n = (DGraph::Node*)it;
    if (isLoop) {
      // If we are visiting this node again in a loop, only visit
      // WHITE children to avoid infinite loops.
      if (visited[n] == TOPOSORT_WHITE) {
        TopoSortLocal(sorted, g, n, visited);
      }
    } else {
      // We want to recur on loops; do not check color
      TopoSortLocal(sorted, g, n, visited);
    }
  }
  
  // Finished visiting all children; push into sorted list
  visited[node] = TOPOSORT_BLACK;
  if (!isLoop) {
    sorted.push_front(node); 
  }
}

#undef TOPOSORT_WHITE
#undef TOPOSORT_GREY
#undef TOPOSORT_BLACK

//****************************************************************************
