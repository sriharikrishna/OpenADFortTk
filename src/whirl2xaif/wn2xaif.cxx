// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif.cxx,v 1.61 2004/06/02 18:51:05 eraxxon Exp $

// * BeginCopyright *********************************************************
/*
  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan
*/
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif.cxx,v $
//
// Purpose:
//   Translate WHIRL to XAIF.
//
// Description:
//   
//   Some conventions:
//     + Newline characters or comments are prepended to a stmt in
//       the translation of that stmt.
//
// Based on Open64 be/whirl2f/wn2f.cxx
//
//***************************************************************************

//************************** System Include Files ***************************

#include <alloca.h>
#include <stdlib.h> // ANSI: cstdlib // for strtol

#include <string>   // STL
#include <set>      // STL
#include <vector>   // STL

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//************************ OpenAnalysis Include Files ***********************

#include <OpenAnalysis/CFG/CFG.h>
#include <OpenAnalysis/ValueNumbers/ValueNumbers.h>
#include <lib/support/Pro64IRInterface.h>

//*************************** User Include Files ****************************

#include "wn2xaif.i"
#include "wn2xaif.h"
#include "wn2xaif_stmt.h"
#include "wn2xaif_expr.h"
#include "wn2xaif_mem.h"
#include "wn2xaif_io.h"
#include "st2xaif.h"
#include "ty2xaif.h"

#include <lib/support/SymTab.h>
#include <lib/support/ScalarizedRefTab.h>

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

IntrinsicXlationTable whirl2xaif::IntrinsicTable(IntrinsicXlationTable::W2X);

//************************** Forward Declarations ***************************

// AddToWNToScalarizedRefTabOp: Given a WNToScalarizedRefTab, add references to it
class AddToWNToScalarizedRefTabOp : public ForAllNonScalarRefsOp {
public:
  AddToWNToScalarizedRefTabOp(WNToScalarizedRefTab* symtab_);
  ~AddToWNToScalarizedRefTabOp() { }
  
  WNToScalarizedRefTab* GetSymTab() { return symtab; }

  // Given a non-scalar reference 'wn', create a dummy variable and
  // add to the map.  
  int operator()(const WN* wn);

private:
  WNToScalarizedRefTab* symtab;
};


//************************** Forward Declarations ***************************

static void
xlate_EntryPoint(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static set<SymHandle>* 
GetParamSymHandleSet(WN* wn_pu);

static const char*
xlate_intent(WN* parm);

static void
xlate_BBStmt(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
xlate_CFCondition(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
xlate_LoopInitialization(xml::ostream& xos, WN *wn, XlationContext& ctxt);

static void 
xlate_LoopUpdate(xml::ostream& xos, WN *wn, XlationContext& ctxt);


static void
AddControlFlowEndTags(WN* wn, WhirlParentMap* wnParentMap);

static void
MassageOACFGIntoXAIFCFG(CFG* cfg);

static void
DumpCFGraphEdge(xml::ostream& xos, UINT eid, CFG::Edge* edge);

//*************************** Forward Declarations ***************************

static const char*
GetCFGVertexType(CFG* cfg, CFG::Node* n);

static const char*
GetCFGControlFlowVertexType(WN* wstmt);

static std::string
GetIDsForStmtsInBB(CFG::Node* node, XlationContext& ctxt);

static pair<bool, INT64>
GetCFGEdgeCondVal(const CFG::Edge* edge);

// lt_CFGEdge: Used to sort CFG::Edges by src, sink and condition value.
struct lt_CFGEdge
{
  // return true if e1 < e2; false otherwise
  bool operator()(const CFG::Edge* e1, const CFG::Edge* e2) const
  {
    unsigned int src1 = e1->source()->getId();
    unsigned int src2 = e2->source()->getId();
    if (src1 == src2) { 
      unsigned int sink1 = e1->sink()->getId();
      unsigned int sink2 = e2->sink()->getId();
      if (sink1 == sink2) {
	pair<bool, INT64> ret1 = GetCFGEdgeCondVal(e1);
	bool hasCondVal1 = ret1.first;
	INT64 condVal1 = ret1.second;

	pair<bool, INT64> ret2 = GetCFGEdgeCondVal(e2);
	bool hasCondVal2 = ret2.first;
	INT64 condVal2 = ret2.second;
	
	if (hasCondVal1 && hasCondVal2) {
	  return (condVal1 < condVal2);
	} 
	else if (hasCondVal1 /* && !hasCondVal2 */) {
	  return false;  // e1 > e2
	}
	else if (hasCondVal2 /* && !hasCondVal1 */) {
	  return true; // e1 < e2
	}
	else /* !hasCondVal1 && !hasCondVal2 */ {
	  return false; // e1 == e2
	}
      } 
      else { 
	return (sink1 < sink2); 
      }
    } 
    else {
      return (src1 < src2);
    }
  }

private:

};

//***************************************************************************
// 
//***************************************************************************

// TranslateWN: see header. The task of translation is dispatched to
// the appropriate handler registered in the handler table.
whirl2xaif::status 
whirl2xaif::TranslateWN(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{   
  static WNXlationTable handlerTable;

  if (!wn) { return whirl2xaif::good; }
  
  OPERATOR opr = WN_operator(wn);
  
#if 0
  //xos << BegComment << "Translating " << OPERATOR_name(opr) << EndComment;
  WNId id = ctxt.FindWNId(wn);
#endif
  
  // Determine whether we are in a context where we expect this
  // expression to have logically valued arguments, or whether we are
  // entering a context where we expect this expression to be a
  // logically valued argument.
  OPCODE opc = WN_opcode(wn);
  if (OPCODE_is_boolean(opc) && WN2F_expr_has_boolean_arg(opc)) { 
    // We expect logical operands to this operator.  Note that this
    // may also be a logical argument, so
    // XlationContext_is_logical_arg(ctxt) may also be true.
    set_XlationContext_has_logical_arg(ctxt);
  } else if (XlationContext_has_logical_arg(ctxt)) { 
    // This is a logical argument.  This is the only place where we
    // should need to check whether this is expected to be a logical
    // valued expression. I.e. the only place where we apply
    // XlationContext_has_logical_arg(context).  However, it may be
    // set at other places (e.g. in wn2f_stmt.c).
    reset_XlationContext_has_logical_arg(ctxt);
    set_XlationContext_is_logical_arg(ctxt);
  } else {
    reset_XlationContext_has_logical_arg(ctxt);
    reset_XlationContext_is_logical_arg(ctxt);
  }
  
  // Dispatch to the appropriate handler for this construct.
  return handlerTable[opr](xos, wn, ctxt);
}


//***************************************************************************
// Function entry handlers
//***************************************************************************

// xlate_FUNC_ENTRY: Given the root of a WHIRL tree, and an
// appropriate context 'ctxt', emits XAIF for the tree to the 'xos'
// stream.  Assumes that Open64 symbol table globals are already set.
whirl2xaif::status
whirl2xaif::xlate_FUNC_ENTRY(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_FUNC_ENTRY, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_FUNC_ENTRY"));
  
  WN* fbody = WN_func_body(wn);

  // -------------------------------------------------------
  // Collect auxillary data
  // -------------------------------------------------------

  // 0. WHIRL parent map
  WhirlParentMap wnParentMap(wn);
  ctxt.SetWNParentMap(&wnParentMap);

  // 1. Non-scalar symbol table
  WNToScalarizedRefTab* symtab = new WNToScalarizedRefTab(); // FIXME
  AddToWNToScalarizedRefTabOp op(symtab);
  ForAllNonScalarRefs(fbody, op); //FIXME
  ctxt.SetWNToScalarizedRefTab(symtab);
  
  // 2. WHIRL<->ID maps
  pair<WNToWNIdMap*, WNIdToWNMap*> wnmaps = CreateWhirlIdMaps(wn);
  delete wnmaps.second;
  ctxt.SetWNToIdMap(wnmaps.first);
  
  AddControlFlowEndTags(wn, &wnParentMap); // FIXME

  // 3. OpenAnalysis CFG
  Pro64IRInterface irInterface;
  Pro64IRStmtIterator irStmtIter(fbody);
  CFG::resetIds();
  CFG cfg(irInterface, &irStmtIter, (SymHandle)WN_st(wn), true);
  if (0) { cfg.dump(); }

  // 4. OpenAnalysis UJ numbers
  set<SymHandle>* params = GetParamSymHandleSet(wn);
  UJNumbers vnmap(cfg, *params);
  delete params;
  ctxt.SetWNToValNum(&vnmap);

  // 5. Massage CFG (wait until after Uwe numbers have been computed)
  MassageOACFGIntoXAIFCFG(&cfg);
  if (0) { cfg.dump(); }

  // -------------------------------------------------------
  // Translate the function header
  // -------------------------------------------------------
  xlate_EntryPoint(xos, wn, ctxt); 
  xos << std::endl;

  // -------------------------------------------------------
  // Translate CFG (et al.) to XAIF
  // -------------------------------------------------------
  ctxt.CreateContext(XlationContext::NOFLAG, wn);
  
  // Dump CFG vertices (basic blocks) in sorted order ('normalized')
  // Note: It might seem that instead of sorting, we could simply use
  // DGraph::DFSIterator.  However, procedures can have unreachable
  // code that will not be found with a DFS.  A simple example of this
  // is that WHIRL often has two OPR_RETURNs at the end of a
  // procedure.
#if 0 // FIXME
  DGraphNodeVec* nodes = SortDGraphNodes(&cfg);
  for (DGraphNodeVec::iterator nodeIt = nodes->begin(); 
       nodeIt != nodes->end(); ++nodeIt) {
#endif
  
  // try a BFS iterator.  too bad for dead code. (actually DFS-- BFS
  // not yet implmented) -- toposort FIXME
  std::set<DGraph::Node*> usedNodes;
  for (DGraph::DFSIterator nodeIt(cfg); (bool)nodeIt; ++nodeIt) {
    CFG::Node* n = dynamic_cast<CFG::Node*>((DGraph::Node*)nodeIt);
    usedNodes.insert(n);
    // n->longdump(&cfg, std::cerr); std::cerr << endl;
    
    const char* vtype = GetCFGVertexType(&cfg, n);    
    SymTabId scopeId = ctxt.FindSymTabId(Scope_tab[CURRENT_SYMTAB].st_tab);
    std::string ids = GetIDsForStmtsInBB(n, ctxt);
      
    // 1. BB element begin tag
    xos << BegElem(vtype) << Attr("vertex_id", n->getId());
    if (vtype == XAIFStrings.elem_BB()) {
      xos << Attr("scope_id", scopeId);
    }
    xos << WhirlIdAnnot(ids);
    
    // 2. BB element contents
    ctxt.CreateContext();
    for (CFG::NodeStatementsIterator stmtIt(n); (bool)stmtIt; ++stmtIt) {
      WN* wstmt = (WN *)((StmtHandle)stmtIt);
      xlate_BBStmt(xos, wstmt, ctxt);
    }
    ctxt.DeleteContext();
    
    // 3. BB element end tag
    xos << EndElem << std::endl;
  }
#if 0
  delete nodes;
#endif
  
  // Dump CFG edges (only those within the XAIF graph)
  CFGEdgeVec* edges = SortCFGEdges(&cfg);
  for (CFGEdgeVec::iterator edgeIt = edges->begin(); 
       edgeIt != edges->end(); ++edgeIt) {
    CFG::Edge* e = (*edgeIt);
    DGraph::Node* src = e->source();
    DGraph::Node* snk = e->sink();
    if (usedNodes.find(src) != usedNodes.end() && 
	usedNodes.find(snk) != usedNodes.end()) {
      DumpCFGraphEdge(xos, ctxt.GetNewEId(), e);
    }
  }
  delete edges;
  
  // -------------------------------------------------------
  // Cleanup
  // -------------------------------------------------------
  ctxt.DeleteContext();
  delete symtab;
  delete wnmaps.first;
  
  return whirl2xaif::good;
}


// xlate_ALTENTRY:
whirl2xaif::status
whirl2xaif::xlate_ALTENTRY(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // Similar to a FUNC_ENTRY, but without the function body.
  ASSERT_DBG_FATAL(WN_opcode(wn) == OPC_ALTENTRY,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_ALTENTRY"));
  
  // Translate the function entry point (FIXME)
  xlate_EntryPoint(xos, wn, ctxt);
  
  return whirl2xaif::good;
}


// xlate_ignore:
whirl2xaif::status
whirl2xaif::xlate_ignore(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  return whirl2xaif::good;
}


// xlate_unknown:
whirl2xaif::status
whirl2xaif::xlate_unknown(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // Warn about opcodes we cannot translate, but keep translating.
  OPERATOR opr = WN_operator(wn);
  ASSERT_WARN(FALSE, (DIAG_W2F_CANNOT_HANDLE_OPC, OPERATOR_name(opr), opr));
  
  xos << BegComment << "*** Unknown WHIRL operator: " << OPERATOR_name(opr)
      << " ***" << EndComment;
  
  return whirl2xaif::good;
}


//***************************************************************************
// Variable references: xlate_SymRef, xlate_MemRef
//***************************************************************************

// Helper for xlate_MemRef
/* just used to maintain the state of the recursions when */
/* marking FLDs in nested addresses                       */
class LOC_INFO {
private:
  FLD_PATH_INFO * _flds_left;   /* points to tail of fld_path */
  STAB_OFFSET _off;             /* offset of last FLD used in fld_path */
  BOOL   _base_is_array;        /* was ST of address an array? */
  
public:
  WN * _nested_addr;
  
  LOC_INFO(FLD_PATH_INFO * path)
    : _flds_left(path), _off(0), _base_is_array(FALSE), _nested_addr(NULL) { }
  
  void WN2F_Find_And_Mark_Nested_Address(WN * addr);
};


// xlate_PregRef: [FIXME: can we abstract witih xlate_SymRef]
whirl2xaif::status
whirl2xaif::xlate_PregRef(xml::ostream& xos, ST* st, TY_IDX preg_ty, 
			  PREG_IDX preg_idx, XlationContext& ctxt)
{
  bool closeVarRef = false;
  if (!ctxt.IsVarRef()) {
    xos << BegElem(XAIFStrings.elem_VarRef())
	<< Attr("vertex_id", ctxt.GetNewVId())
	<< Attr("du_ud", ctxt.FindVN(ctxt.GetWN_MR()));
    closeVarRef = true; 
  }

  ST_TAB* sttab = Scope_tab[ST_level(st)].st_tab;
  SymTabId scopeid = ctxt.FindSymTabId(sttab);

  xos << BegElem("xaif:SymbolReference") 
      << Attr("vertex_id", ctxt.GetNewVId())
      << Attr("scope_id", scopeid) << AttrSymId(st) << EndElem;
  
  if (closeVarRef) {
    xos << EndElem /* elem_VarRef() */;
  }
  
  return whirl2xaif::good;
}


// xlate_SymRef: see header.
whirl2xaif::status
whirl2xaif::xlate_SymRef(xml::ostream& xos, 
			 ST* base_st,        // base symbol
			 TY_IDX baseptr_ty,  // type of base symbol ptr
			 TY_IDX ref_ty,      // type of referenced object
			 STAB_OFFSET offset, // offset within 'base_st'
			 XlationContext& ctxt)
{
  // FIXME: ugly, ugly, ugly
  /* The base symbol 'base_st' will be treated as having a lvalue
   * (address) type of 'baseptr_ty', except when "deref" is TRUE, when
   * the rvalue of 'base_st' is assumed to have the 'base_ty'
   * and must either explicitly (for POINTER variables) or implicitly
   * (for pass by reference arguments) be dereferenced.

   * Note that a compatible 'base_ty' and 'ref_ty' simply translates
   * into a reference to the given 'base_st'.  In all other cases we
   * expect 'ref_ty' to be a field or offset within the 'base_ty'
   * (structure or array).
   *
   * Note that we must have special handling for common-blocks and
   * equivalences.  Note that "base_ty" may be different from
   * "Stab_Pointer_To(ST_type(base_st))", both for "deref" cases and 
   * ptr_as_array variables.  */

  TY_IDX base_ty = TY_pointed(baseptr_ty); 


  // -------------------------------------------------------
  // 
  // -------------------------------------------------------

  /* Do the symbol translation from the base of BASED symbols */
  if (Stab_Is_Based_At_Common_Or_Equivalence(base_st)) {
    offset += ST_ofst(base_st); /* offset of based symbol */
    base_st = ST_base(base_st); /* replace based symbol with its base */
    
    base_ty = ST_type(base_st);
    baseptr_ty = Stab_Pointer_To(base_ty);
    //Set_BE_ST_w2fc_referenced(base_st);
  }
  
  /* Do the symbol translation from the base of fully split common symbols */
  if (ST_is_split_common(base_st)) {
    //Clear_BE_ST_w2fc_referenced(base_st); // no split base, just user COMMON
    base_st = ST_full(base_st);
    //Set_BE_ST_w2fc_referenced(base_st);
    base_ty = ST_type(base_st);
    
    if (TY_Is_Pointer(base_ty))
      base_ty = TY_pointed(base_ty);
    
    if (TY_is_f90_pointer(base_ty)) //Sept
      base_ty = TY_pointed(base_ty);
    
    baseptr_ty = Stab_Pointer_To(base_ty);
  }
  
  // -------------------------------------------------------
  // If we are not already within xaif:VariableReference... (FIXME: abstract)
  // -------------------------------------------------------
  bool constant = (ST_class(base_st) == CLASS_CONST);
  bool newContext = false;
  if (!constant && !ctxt.IsVarRef()) {
    xos << BegElem(XAIFStrings.elem_VarRef())
	<< Attr("vertex_id", ctxt.GetNewVId())
	<< Attr("du_ud", ctxt.FindVN(ctxt.GetWN_MR()));
    ctxt.CreateContext(XlationContext::VARREF); // FIXME: do we need wn?
    newContext = true; 
  }

  
  // -------------------------------------------------------
  //
  // -------------------------------------------------------

  /* Select variable-reference translation function */
  const BOOL deref_val = ctxt.IsDerefAddr();
  void (*translate_var_ref)(xml::ostream&, ST*, XlationContext&);

  if (deref_val && (ST_sclass(base_st) != SCLASS_FORMAL) 
      && TY_Is_Pointer(ST_type(base_st)) 
      && !TY_is_f90_pointer(ST_type(base_st))) {
    /* An explicit dereference */
    translate_var_ref = &ST2F_deref_translate;
  } else {
    /* A direct reference or an implicit dereference */
    translate_var_ref = &TranslateSTUse;
  }

  
  // FIXME: for now, make sure this is only used for data refs 
  if (ST_class(base_st) == CLASS_FUNC) {
    //assert(false && "symref FIXME");
    std::cerr << "xlate_SymRef: translating function ref\n";
  } else if (ST_class(base_st) == CLASS_BLOCK) { // FIXME
    TranslateSTUse(xos, base_st, ctxt);
    xos << "+ " << Num2Str(offset, "%lld");
  }
  
  if (IsScalarRef(base_ty, ref_ty)) {
    
    // 1. Reference to a scalar symbol (==> offset into 'base_st' is zero)
    // FIXME: what about FUNCTIONS?
    ASSERT_WARN(offset == 0, (DIAG_W2F_UNEXPEXTED_OFFSET, offset, 
			      "xlate_SymRef"));
    translate_var_ref(xos, base_st, ctxt);
    
  } else if (TY_Is_Array(base_ty)) {

    // 2. Array reference (non-scalar) 
#if 0 // FIXME
    ASSERT_DBG_WARN(WN2F_Can_Assign_Types(TY_AR_etype(base_ty), ref_ty),
		    (DIAG_W2F_INCOMPATIBLE_TYS, "xlate_SymRef"));
#endif
    
    // FIXME: Call 'xlate_non_scalar_ref'.  Get a dummy variable.  As
    // properties translate the exact reference.
    translate_var_ref(xos, base_st, ctxt);
    
    //if (TY_Is_Character_String(base_ty)) { } 
    if (!XlationContext_has_no_arr_elmt(ctxt)) {
      TY2F_Translate_ArrayElt(xos, base_ty, offset); // FIXME
      reset_XlationContext_has_no_arr_elmt(ctxt);
    }
    
  } else {
    
    // 3. Structure (non-scalar)
    
    // call 'xlate_derivedtype_ref'
    // Get the dummy variable (need the parent wn) FIXME
    ScalarizedRef* sym = ctxt.FindScalarizedRef(ctxt.GetWN_MR());
    if (sym) {
      xos << BegElem("xaif:NONSCALAR") << Attr("id", sym->GetName())
	  << EndAttrs;
    }
    
    /* We only dereference a field when the base need not be 
     * dereferenced.  We never need to have both dereferenced, 
     * since pointers cannot occur in RECORDS and common/
     * equivalence blocks cannot be referenced through pointer 
     * identifiers. */
    FLD_PATH_INFO *fld_path = NULL;
    BOOL deref_fld;
    if ( !(TY_IsRecord(ref_ty) /* && FIXME*/) ) {
      deref_fld = (deref_val && !TY_Is_Pointer(ST_type(base_st))) ? TRUE:FALSE;
      if (deref_fld) { ref_ty = Stab_Pointer_To(ref_ty); }
      fld_path = TY2F_Get_Fld_Path(base_ty, ref_ty, offset);
    }
    
    if (fld_path == NULL) {
      translate_var_ref(xos, base_st, ctxt);
    } else if (Stab_Is_Common_Block(base_st)) {
      // Common block reference (do not translate as field ref)
      // FIXME: make sure the fld_path is length 1 
      ST_IDX st_idx = fld_path->fld.Entry()->st;
      ST* st = (st_idx != 0) ? ST_ptr(st_idx) : NULL;
      if (st) {
	translate_var_ref(xos, st, ctxt);
      } else { // FIXME
	TY2F_Translate_Fld_Path(xos, fld_path, deref_fld, 
				// (Stab_Is_Common_Block(base_st) || 
				//  Stab_Is_Equivalence_Block(base_st)),
				TRUE, FALSE/*as_is*/, ctxt);
      }

    } else {
      
      // Structure: 
      /* Base the path at the 'base_st' object, and separate it from
       * the remainder of the path with the field selection operator. */
      translate_var_ref(xos, base_st, ctxt);
      TY2F_Fld_Separator(xos);
      TY2F_Translate_Fld_Path(xos, fld_path, deref_fld, 
				// (Stab_Is_Common_Block(base_st) || 
				//  Stab_Is_Equivalence_Block(base_st)),
			      FALSE, FALSE/*as_is*/, ctxt);
    }
    if (fld_path) { TY2F_Free_Fld_Path(fld_path); }

    if (sym) { xos << EndElem; }
  }

  if (newContext) {
    ctxt.DeleteContext();
    xos << EndElem /* elem_VarRef() */;
  }
  
  return whirl2xaif::good;
} /* xlate_SymRef */


// xlate_MemRef: 
whirl2xaif::status
whirl2xaif::xlate_MemRef(xml::ostream& xos, 
			 WN*    addr,        // base-address expr
			 TY_IDX addr_ty,     // type of base-address
			 TY_IDX ref_ty,      // type of referenced object
			 STAB_OFFSET offset, // offset from base-address
			 XlationContext& ctxt)
{
  /* Given an address expression and an offset from this address,
   * append a Fortran expression to "xos" to reference an object of
   * type 'ref_ty' at this offset address.  In effect, we dereference
   * the address to 'ref_ty'.
    
   FIXME
   * is a dereferencing operation on the base-address. The resultant
   * value (e.g. after a struct-field access) may be further
   * dereferenced.
   *
   * The address expression is unconditionally treated as an expression
   * of the addr_ty.
   *
   * For non-zero offsets, or when "!WN2F_Can_Assign_Types(ref_ty,
   * TY_pointed(addr_ty))", we expect the base-address to denote the
   * address of a structure or an array, where an object of the given 
   * ref_ty can be found at the given offset.
   *
   * Since Fortran does not have an explicit (only implicit) dereference
   * operation we cannot first calculate the address and then 
   * dereference. This constrains the kind of expression we may handle
   * here.  Note that equivalences and common-blocks always should be 
   * accessed through an LDID or an LDA(?) node.  */

  TY_IDX base_ty = TY_pointed(addr_ty);
  const BOOL deref_fld = ctxt.IsDerefAddr();
  
  
  // -------------------------------------------------------
  //
  // -------------------------------------------------------
  bool constant = (WN_operator(addr) == OPR_LDA 
		   && ST_class(WN_st(addr)) == CLASS_CONST);
  bool newContext = false; 
  if (!constant && !ctxt.IsVarRef()) {
    xos << BegElem(XAIFStrings.elem_VarRef())
	<< Attr("vertex_id", ctxt.GetNewVId())
	<< Attr("du_ud", ctxt.FindVN(ctxt.GetWN_MR()));
    ctxt.CreateContext(XlationContext::VARREF); // FIXME: do we need wn?
    newContext = true; 
  }


  // -------------------------------------------------------
  //
  // -------------------------------------------------------
  
  // FIXME: for now, make sure this is only used for data refs 
  if (TY_kind(base_ty) == KIND_FUNCTION) {
    assert(false && "memref FIXME");
  }


  /* Prepare to dereference the base-address expression */
  ctxt.SetDerefAddr();
  
  if (WN2F_Is_Address_Preg(addr, addr_ty)) { // FIXME
    /* Optimizer may put address PREGS into ARRAYs */
    /* and high level type is more or less useless */
    /* just go with WN tree ADDs etc.              */
    TranslateWN(xos, addr, ctxt);    
    if (offset != 0) {
      xos << '+' << offset /* "%lld" */;
    }
  } else {
    
    if (IsScalarRef(base_ty, ref_ty)) { // FIXME
      ASSERT_WARN(offset == 0, (DIAG_W2F_UNEXPEXTED_OFFSET, offset,
				"xlate_MemRef"));
      TranslateWN(xos, addr, ctxt);
    } else if (TY_Is_Array(base_ty)) { 
      
      // 2. Array reference (non-scalar) 
#if 0 // FIXME
      ASSERT_DBG_WARN(WN2F_Can_Assign_Types(TY_AR_etype(base_ty), ref_ty),
		      (DIAG_W2F_INCOMPATIBLE_TYS, "xlate_MemRef"));
#endif
	
      if (TY_Is_Character_String(base_ty)) {
	TranslateWN(xos, addr, ctxt); /* String lvalue */
	if (!XlationContext_has_no_arr_elmt(ctxt))
	  TY2F_Translate_ArrayElt(xos, base_ty, offset);
      } else {
	TranslateWN(xos, addr, ctxt); /* Array lvalue */
	if (!XlationContext_has_no_arr_elmt(ctxt))
	  TY2F_Translate_ArrayElt(xos, base_ty, offset);
	else
	  reset_XlationContext_has_no_arr_elmt(ctxt);
      }
      
    } else if ((WN_operator(addr) == OPR_LDA || WN_operator(addr) == OPR_LDID) 
	       && (TY_kind(base_ty) != KIND_STRUCT)
	       && (Stab_Is_Common_Block(WN_st(addr)) 
		   || Stab_Is_Equivalence_Block(WN_st(addr)))) {
      
      // 3. A common-block or equivalence-block, both of which we
      // handle only in xlate_SymRef().
      ASSERT_WARN(WN2F_Can_Assign_Types(ST_type(WN_st(addr)), base_ty) ,
		  (DIAG_W2F_INCOMPATIBLE_TYS, "xlate_SymRef"));
      
      if (WN_operator(addr) == OPR_LDA)
	ctxt.ResetDerefAddr();
      xlate_SymRef(xos, WN_st(addr), addr_ty, ref_ty,
			 offset + WN_lda_offset(addr) /*offset*/, ctxt);
    } else { 
      // 4. Field access (Neither common-block nor equivalence)
      // Find the path to the field we wish to access and append
      // this path to the base-object reference.
      
      /* Get any offset given by an address ADDition node.  The type
       * of the addition, as given by WN_Tree_Type(), is the type
       * of base-object within which we are accessing, so the addr_ty
       * is already set up correctly to handle the combined offsets.
       */
      WN* wn = ctxt.GetWN();
      ScalarizedRef* sym = ctxt.FindScalarizedRef(wn);
      if (sym) {
	xos << BegElem("xaif:NONSCALAR") << Attr("id", sym->GetName())
	    << EndAttrs;
      }
      
      WN_OFFSET tmp = WN2F_Sum_Offsets(addr);
      if (tmp < TY_size(TY_pointed(addr_ty)))
	offset += tmp;
      else 
	offset = tmp;
      
      FLD_PATH_INFO* fld_path = TY2F_Get_Fld_Path(base_ty, ref_ty, offset);
      ASSERT_DBG_WARN(fld_path != NULL, (DIAG_W2F_NONEXISTENT_FLD_PATH, 
					 "xlate_MemRef"));
      
      /* May have ARRAY(ADD(ARRAY(LDA),CONST)) or some such. */
      /* The deepest ARRAY (with the address) is handled     */
      /* by the xlate_ARRAY processing, but the others        */
      /* are field references with array components.         */
      LOC_INFO det(fld_path);
      det.WN2F_Find_And_Mark_Nested_Address(addr);
      addr = det._nested_addr;
      
      /* Get the base expression to precede the path */
      TranslateWN(xos, addr, ctxt);
      TY2F_Fld_Separator(xos);
      
      /* Append the path-name, perhaps w/o array subscripts. */
      if (fld_path != NULL) {
	TY2F_Translate_Fld_Path(xos, fld_path, deref_fld, 
				FALSE/*common*/, FALSE/*as_is*/, ctxt);
	TY2F_Free_Fld_Path(fld_path);
      } else {
	xos << "field-at-offset=" << offset /* %lld */;
      }

      if (sym) { xos << EndElem; }
    }    
  }

  if (newContext) {
    ctxt.DeleteContext();
    xos << EndElem /* elem_VarRef() */;
  }

  return whirl2xaif::good;
} /* xlate_MemRef */


void 
LOC_INFO::WN2F_Find_And_Mark_Nested_Address(WN * addr)
{
  /* If this address expression contains nested ARRAY nodes */
  /* (and isn't a character expression), the ARRAYs refer   */
  /* to structure components, eg: aaa(1).kkk(3) yields      */
  /* ARRAY(ADD(const,ARRAY(LDA)). Add a pointer to the      */
  /* array elements of the fld path, associating each with  */
  /* corresponding OPC_ARRAY. TY2F_Translate_Fld_Path will  */
  /* write the subscript list.                              */

  /* In general, just the lowest LDID/LDA remains to be     */
  /* processed, however if the lowest ARRAY node is not a   */
  /* fld, and belongs to the address ST, then return that   */
  /* ARRAY.                                                 */
  OPERATOR opr = WN_operator(addr);
  switch (opr)
  {
  case OPR_ARRAY: 
  case OPR_ARRAYEXP: 
  case OPR_ARRSECTION:
    {
     WN * kid;     

     if (WN_operator(addr)==OPR_ARRAYEXP)
        addr = WN_kid0(addr);

      kid = WN_kid0(addr);
      WN2F_Find_And_Mark_Nested_Address(kid);

      if ((_flds_left && _flds_left->arr_elt) &&
	  (!(_base_is_array)))
      {
	_flds_left-> arr_wn = addr;
	_flds_left = TY2F_Point_At_Path(_flds_left,_off);
      } 
      else 
	_nested_addr = addr;

      _base_is_array = FALSE;
    }
    break;


  case OPR_ADD:
    {
      WN * cnst = WN_kid0(addr);
      WN * othr = WN_kid1(addr);

      if (WN_operator(cnst) != OPR_INTCONST) 
      {
	cnst = WN_kid1(addr);
	othr = WN_kid0(addr);
      }
      WN2F_Find_And_Mark_Nested_Address(othr);
      _off = WN_const_val(cnst);
      _flds_left = TY2F_Point_At_Path(_flds_left,_off);
      _base_is_array = FALSE;
    }
    break;

  case OPR_LDID:
    _off = 0;
    _nested_addr = addr;
    _flds_left = TY2F_Point_At_Path(_flds_left,_off);
    _base_is_array = ((TY_kind(WN_ty(addr)) == KIND_POINTER) && 
		      (TY_kind(TY_pointed(WN_ty(addr))) == KIND_ARRAY));
    break;

  case OPR_LDA:
    _off = WN_lda_offset(addr);
    _nested_addr = addr;
    _flds_left = TY2F_Point_At_Path(_flds_left,_off);
    _base_is_array = ((TY_kind(WN_ty(addr)) == KIND_POINTER) && 
		      (TY_kind(TY_pointed(WN_ty(addr))) == KIND_ARRAY));
    break;

  case OPR_ILOAD:
    _off = 0;
    _nested_addr = addr;
    _flds_left = TY2F_Point_At_Path(_flds_left,0);
    _base_is_array = ((TY_kind(WN_ty(addr)) == KIND_POINTER) && 
		      (TY_kind(TY_pointed(WN_ty(addr))) == KIND_ARRAY));
    break;

  default:
    ASSERT_WARN(0, (DIAG_W2F_CANNOT_HANDLE_OPC, OPERATOR_name(opr), opr));
    break;
  }
  return;
}


WN_OFFSET
WN2F_Sum_Offsets(WN *addr)
{
  /* Accumulate any offsets (ADDs) in this address   */
  /* tree. Used for computing Fld paths              */
  BOOL sum = 0;

  switch (WN_operator(addr)) {
  case OPR_ARRAY: 
  case OPR_ARRAYEXP:
  case OPR_ARRSECTION:
    if (WN_operator(addr)==OPR_ARRAYEXP)
      addr = WN_kid0(addr);
    
    sum += WN2F_Sum_Offsets(WN_kid0(addr));
    break;
    
  case OPR_ADD:
    sum += WN2F_Sum_Offsets(WN_kid0(addr));
    sum += WN2F_Sum_Offsets(WN_kid1(addr));
    break;
    
  case OPR_INTCONST:
    sum = WN_const_val(addr);
    break;
  }
  return sum;
}


void 
WN2F_Address_Of(xml::ostream& xos)
{
  //REMOVE Prepend_Token_Special(xos, '(');
  //REMOVE Prepend_Token_String(xos, "loc%");
  xos << "loc%()"; // FIXME
}


//***************************************************************************
// 
//***************************************************************************

DGraphNodeVec*
SortDGraphNodes(DGraph* g)
{
  DGraphNodeVec* vec = new DGraphNodeVec(g->num_nodes());

  DGraph::NodesIterator it(*g);
  for (int i = 0; (bool)it; ++it, ++i) {
    (*vec)[i] = (DGraph::Node*)it;
  }
  
  // Sort by id (ascending)
  std::sort(vec->begin(), vec->end(), BaseGraph::lt_Node());
  
  return vec;
}


DGraphEdgeVec*
SortDGraphEdges(DGraph* g)
{
  DGraphEdgeVec* vec = new DGraphEdgeVec(g->num_edges());

  DGraph::EdgesIterator it(*g);
  for (int i = 0; (bool)it; ++it, ++i) {
    (*vec)[i] = (DGraph::Edge*)it;
  }
  
  // Sort by source/target node ids (ascending)
  std::sort(vec->begin(), vec->end(), DGraph::lt_Edge()); 
  
  return vec;
}


CFGEdgeVec*
SortCFGEdges(CFG* g)
{
  CFGEdgeVec* vec = new CFGEdgeVec(g->num_edges());

  DGraph::EdgesIterator it(*g);
  for (int i = 0; (bool)it; ++it, ++i) {
    (*vec)[i] = dynamic_cast<CFG::Edge*>((DGraph::Edge*)it);
  }
  
  // Sort by source/target node ids (ascending)
  std::sort(vec->begin(), vec->end(), lt_CFGEdge()); 
  
  return vec;
}


// DumpGraphEdge: see header.
void 
DumpGraphEdge(xml::ostream& xos, const char* nm, 
	      UINT eid, UINT srcid, UINT targid, UINT pos)
{
  xos << BegElem(nm) 
      << Attr("edge_id", eid) 
      << Attr("source", srcid) << Attr("target", targid);
  if (pos >= 1) {
    xos << Attr("position", pos);
  }
  xos << EndElem;
}


// DumpCFGraphEdge: Dump a CFG edge
static void
DumpCFGraphEdge(xml::ostream& xos, UINT eid, CFG::Edge* edge)
{
  CFG::Node* n1 = dynamic_cast<CFG::Node*>(edge->source());
  CFG::Node* n2 = dynamic_cast<CFG::Node*>(edge->sink());
  
  pair<bool, INT64> ret = GetCFGEdgeCondVal(edge);
  bool hasCondVal = ret.first;
  INT64 condVal = ret.second;

  xos << BegElem("xaif:ControlFlowEdge") 
      << Attr("edge_id", eid) 
      << Attr("source", n1->getId()) << Attr("target", n2->getId());
  if (hasCondVal) {
    xos << Attr("has_condition_value", "true")
	<< Attr("condition_value", condVal);
  }
  xos << EndElem;
}

//***************************************************************************
//
//***************************************************************************

//FIXME: op should not be const because we call op(), which is non const.
void 
ForAllNonScalarRefs(const WN* wn, ForAllNonScalarRefsOp& op)
{
  // Special base case
  if (wn == NULL) { return; }

  OPERATOR opr = WN_operator(wn);
  if (IsNonScalarRef(wn)) {
    
    // Base case
    int ret = op(wn); // FIXME: what to do on error?
    
    // Special recursive case: Since WHIRL stores are statements (not
    // expressions) we need to check the RHS (kid0) of the implied
    // assignment for non-scalar references.
    if (OPERATOR_is_store(opr)) {
      ForAllNonScalarRefs(WN_kid0(wn), op);
    }

  } else if (!OPERATOR_is_leaf(opr)) {
    
    // General recursive case
    if (WN_operator(wn) == OPR_BLOCK) {
      WN *kid = WN_first(wn);
      while (kid) {
	ForAllNonScalarRefs(kid, op);
	kid = WN_next(kid);
      }
    } else {
      for (INT kidno = 0; kidno < WN_kid_count(wn); kidno++) {
	WN* kid = WN_kid(wn, kidno);
	ForAllNonScalarRefs(kid, op);
      }
    }
    
  }
}


AddToWNToScalarizedRefTabOp::AddToWNToScalarizedRefTabOp(WNToScalarizedRefTab* symtab_)
{ 
  symtab = symtab_;
  assert(symtab != NULL);
}


// Given a non-scalar reference 'wn', create a dummy variable and
// add to the map.  
int 
AddToWNToScalarizedRefTabOp::operator()(const WN* wn) 
{
  // Base case
#if 0 // FIXME
  fprintf(stderr, "----------\n");
  fdump_tree(stderr, wn); // FIXME: append this to a symtab somewhere
#endif
  
  ScalarizedRef* sym = new ScalarizedRef();
  bool ret = symtab->Insert(wn, sym);
  return (ret) ? 0 : 1;
}


//***************************************************************************
// Helpers
//***************************************************************************

// xlate_EntryPoint: Translates a function entry or alternate entry
// point, with parameter declarations.  
// FIXME: XAIF doesn't support alt-entry.
static void
xlate_EntryPoint(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  OPERATOR opr = WN_operator(wn);
  ASSERT_DBG_FATAL(opr == OPR_ALTENTRY || opr == OPR_FUNC_ENTRY,
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_EntryPoint"));
  
  ST* func_st = &St_Table[WN_entry_name(wn)];
  TY_IDX func_ty = ST_pu_type(func_st);
  TY_IDX return_ty = Func_Return_Type(func_ty);
  
  // Accumulate the parameter ST entries  // FIXME: GetParamSymHandleSet
  INT nparam = (opr == OPR_ALTENTRY) ? WN_kid_count(wn) : WN_num_formals(wn);
  ST** params_st = (ST **)alloca((nparam + 1) * sizeof(ST *));  
  for (INT parm = 0; parm < nparam; parm++) {
    params_st[parm] = WN_st(WN_formal(wn, parm));
  }
  params_st[nparam] = NULL; // terminate the list

  // Parameter name-list. Skip any implicit "length" parameters
  // associated with character strings.  Such implicit parameters
  // should be at the end of the parameter list. FIXME
  xos << BegElem("xaif:ArgumentList");
  
  INT first_parm = ST2F_FIRST_PARAM_IDX(func_ty);
  INT implicit_parms = 0;
  UINT position = 1;
  for (INT parm = first_parm; parm < (nparam - implicit_parms); parm++) {

    WN* parm_wn = WN_formal(wn, parm);    
    ST* parm_st = params_st[parm]; //WN_st(parm_wn);
    
    if (!ST_is_return_var(parm_st)) {
      ST_TAB* sttab = Scope_tab[ST_level(parm_st)].st_tab;
      SymTabId scopeid = ctxt.FindSymTabId(sttab);
      xos << BegElem("xaif:ArgumentSymbolReference")
	  << Attr("position", position) 
	  << Attr("scope_id", scopeid) << AttrSymId(parm_st)
	  << Attr("intent", xlate_intent(parm_wn))
	  << WhirlIdAnnot(ctxt.FindWNId(parm_wn))
	  << EndElem;
      position++;
    }
    
    if (STAB_PARAM_HAS_IMPLICIT_LENGTH(parm_st)) {
      implicit_parms++;
      
      /* FIXME: is function returning character_TY? if length follows */
      /* address - skip over it, but account for ',' in arg list */
      if ( ((parm == first_parm) && (params_st[parm+1] != NULL)) 
	   && (ST_is_value_parm(parm_st) 
	       && ST_is_value_parm(params_st[parm+1]))
	   && (return_ty != (TY_IDX)0 && TY_kind(return_ty) == KIND_VOID) ) {
	parm++;
	params_st[parm] = NULL; 
	implicit_parms--;
      }
    }
  }
  
  xos << EndElem /* xaif:ArgumentList */;
}


// GetParamSymHandleSet: Return a set of SymHandles representing the
// parameters of the OPR_FUNC_ENTRY.
static set<SymHandle>* 
GetParamSymHandleSet(WN* wn_pu)
{
  // Accumulate the ST* for parameters
  set<SymHandle>* params = new set<SymHandle>;
  INT nparam = WN_num_formals(wn_pu);
  for (int i = 0; i < nparam; ++i) {
    ST* st = WN_st(WN_formal(wn_pu, i));
    params->insert((SymHandle)st);
  }
  return params;
}

static const char*
xlate_intent(WN* parm)
{
  // Note: WN_parm flags are typically not set 
  // WN_parm_flag(parm), WN_Parm_Dummy(parm)
  ST* st = WN_st(parm);
  if (ST_is_intent_in_argument(st) || WN_Parm_In(parm)) {
    return "in";
  } 
  else if (ST_is_intent_out_argument(st) || WN_Parm_Out(parm)) {
    return "out";
  }
  else { // WN_Parm_By_Reference(parm)
    return "inout"; 
  }
}

// xlate_BBStmt: Given a statement within an XAIF basic block,
// properly translate it.
static void
xlate_BBStmt(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  if (!wn) { return; }
  
  // If a structured statement, it must be translated specially.
  // Otherwise simply dispatch to TranslateWN(...).
  const char* vty = GetCFGControlFlowVertexType(wn);
  OPERATOR opr = WN_operator(wn);
  const char* opr_str = OPERATOR_name(opr);
  
  if (vty == XAIFStrings.elem_BBForLoop()) {
    xlate_LoopInitialization(xos, WN_start(wn), ctxt);
    xlate_CFCondition(xos, WN_end(wn), ctxt);
    xlate_LoopUpdate(xos, WN_step(wn), ctxt);
  } 
  else if (vty == XAIFStrings.elem_BBPostLoop() ||
	   vty == XAIFStrings.elem_BBPreLoop()) {
    xlate_CFCondition(xos, WN_while_test(wn), ctxt);
  }
  else if (vty == XAIFStrings.elem_BBBranch()) {
    WN* condWN = NULL;
    if (opr == OPR_IF || opr == OPR_TRUEBR || opr == OPR_FALSEBR) {
      condWN = WN_if_test(wn);
    } else if (opr == OPR_SWITCH || opr == OPR_COMPGOTO) {
      condWN = WN_switch_test(wn);
    }
    ASSERT_FATAL(condWN, (DIAG_UNIMPLEMENTED, "Programming Error."));
    xlate_CFCondition(xos, condWN, ctxt);
  } 
  else if (vty == XAIFStrings.elem_BBEndBranch() ||
	   vty == XAIFStrings.elem_BBEndLoop()) {
    // skip bogus comment statement
  }
  else {
    TranslateWN(xos, wn, ctxt);
  }
}




// xlate_CFCondition: Translate the BB's control flow condition (Loops, Ifs)
static void 
xlate_CFCondition(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  xos << BegElem("xaif:Condition");
  ctxt.CreateContext();
  TranslateWN(xos, wn, ctxt);
  ctxt.DeleteContext();
  xos << EndElem;
}


// xlate_LoopInitialization: 
static void 
xlate_LoopInitialization(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  xos << BegElem("xaif:Initialization");
  ctxt.CreateContext(XlationContext::ASSIGN); // implicit for this element
  TranslateWN(xos, wn, ctxt);
  ctxt.DeleteContext();
  xos << EndElem;
}

// xlate_LoopUpdate: 
static void 
xlate_LoopUpdate(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  xos << BegElem("xaif:Update"); 
  ctxt.CreateContext(XlationContext::ASSIGN); // implicit for this element
  TranslateWN(xos, wn, ctxt);
  ctxt.DeleteContext();
  xos << EndElem;
}


//***************************************************************************

// AddControlFlowEndTags: Add control flow end tags
// FIXME: assumes fully structured control flow???
static void
AddControlFlowEndTags(WN* wn, WhirlParentMap* wnParentMap)
{
  // FIXME: we should be skipping most expression sub trees like
  // interface to NewOA.
  
  WN_TREE_CONTAINER<PRE_ORDER> wtree(wn);
  WN_TREE_CONTAINER<PRE_ORDER>::iterator it;
  for (it = wtree.begin(); it != wtree.end(); ++it) {
    WN* curWN = it.Wn();
    OPERATOR opr = WN_operator(curWN);
    
    const char* vty = GetCFGControlFlowVertexType(curWN);
    if (!vty) { continue; }
    
    // Find structured (and some unstructured) control flow and insert
    // placehoder statement.
    if (vty == XAIFStrings.elem_BBForLoop() || 
	vty == XAIFStrings.elem_BBPostLoop() ||
	vty == XAIFStrings.elem_BBPreLoop()) {
      // do (...)
      //   ...
      // * EndLoop
      // enddo
      WN* blkWN = NULL;
      if (opr == OPR_DO_LOOP) { 
	blkWN = WN_do_body(curWN); 
      } else {
	blkWN = WN_while_body(curWN);
      }
      WN* newWN = WN_CreateComment((char*)XAIFStrings.elem_BBEndLoop());
      WN_INSERT_BlockLast(blkWN, newWN);
    }
    else if (vty == XAIFStrings.elem_BBBranch()) {
      WN* ipWN = NULL;
      if (opr == OPR_SWITCH) {
	//   switch(...) [unstructured]
	//     casegoto L2
	//     casegoto L3
	//   end
	//   L2 ... L3 ...
	//   L1 (beginning of code after switch)
	// * EndBranch
	INT32 lbl = WN_last_label(curWN);
	for (WN* x = WN_next(curWN); x; x = WN_next(x)) {
	  if (WN_operator(x) == OPR_LABEL && WN_label_number(x) == lbl) {
	    ipWN = x;
	    break;
	  }
	}
      } 
      else {
	//   if (...) { ... }  OR   if (...) goto77 [unstructured]
	//   else { ... }         * EndBranch      
	//   endif                                
	// * EndBranch
	ipWN = curWN;
      }
      if (ipWN) {
	WN* blkWN = wnParentMap->FindBlock(ipWN);
	WN* newWN = WN_CreateComment((char*)XAIFStrings.elem_BBEndBranch());
	WN_INSERT_BlockAfter(blkWN, ipWN, newWN); // 'newWN' after 'ipWN'
      }
    }
  }
}


// MassageOACFGIntoXAIFCFG: Convert an OpenAnalysis CFG into a valid
// XAIF CFG.  
// 
// 1. OpenAnalysis creates basic blocks with labels at the beginning
// and branches at the end.  E.g. for TWOWAY_CONDITIONAL and
// MULTIWAY_CONDITIONAL statements OpenAnalysis may generate BBs such
// as:
//
// Code:                   | BBs:
//   x = 5                 |          x = 5
//   if (x .eq. 5) then    |          if (x .eq. 5)
//     x = 6               |       _______/\_________
//   else                  |      /                  \
//     x = 7               |  x = 6                  x = 7
//   ...                   |      \-------  ---------/
//                         |              \/
//                         |            ......
// 
// While OA creates correct BBs, in order to create valid XAIF, the
// first BB must be split so that the if condition can be placed
// within xaif:If.  We create a new BB here so that the translation
// into XAIF is easy:
// 
//   <xaif:BasicBlock>
//     <xaif:Assignment...
//     </xaif:Asignment>
//   </xaif:BasicBlock>
// 
//   <xaif:Branch>
//     <xaif:Condition...
//     </xaif:Condition>
//   </xaif:If>
// 
// 2. OpenAnalysis places the initialization and update nodes of
// OPR_DO_LOOPs in the appropriate BB: they are virtually (but not
// really) spliced out of the OPR_DO_LOOPs.  For example an
// OPR_DO_LOOP node with initialization, condition, update, and a
// block of statements may become:
//
//                   ....
//                   DO_LOOP initialization
//                              |
//                              v
//                      DO_LOOP condition <--------------|
//                      _______/\________                |
//                     /                 \               |
//                    |            DO_LOOP statements    |
//                    |            DO_LOOP update     ---| 
//                    v
//                  .....
//
// Because XAIF can preserve and exploit high level control strucures
// such as OPR_DO_LOOP, we want to *remove* the initialization and
// update statement so they can be placed in the special xaif:ForLoop
// construct.  xaif2whirl also depends on this transformation.
//
// [When xaif2whirl deletes the translation interval for the first BB
// above (for subsequent replacement), it actually deletes the whole
// OPR_DO_LOOP node!  Testing for special conditions doesn't help much
// because when WHIRL is created from the new XAIF, we do not know how to
// replace the deleted loop initialization node.]
//
static void
MassageOACFGIntoXAIFCFG(CFG* cfg)
{
  IRInterface& irInterface = cfg->GetIRInterface();

  // -------------------------------------------------------
  // 1. Find BBs with conditionals and split them
  // -------------------------------------------------------
  
  // Iterate over BB nodes.  For each node with more than one
  // statement, examine the statements.  If a conditional is found at
  // the end of the BB, split it.  (The CFG iterator should handle the
  // creation of new nodes in the middle of iteration.)
  for (CFG::NodesIterator nodeIt(*cfg); (bool)nodeIt; ++nodeIt) {
    CFG::Node* n = dynamic_cast<CFG::Node*>((DGraph::Node*)nodeIt);
    // n->longdump(cfg, std::cerr);
    
    if (n->size() > 1) {
      for (CFG::NodeStatementsIterator stmtIt(n); (bool)stmtIt; ++stmtIt) {
	StmtHandle stmt = (StmtHandle)stmtIt;
	
	IRStmtType ty = irInterface.GetStmtType(stmt);
	if (ty == STRUCT_TWOWAY_CONDITIONAL
	    || ty == USTRUCT_TWOWAY_CONDITIONAL_T
	    || ty == USTRUCT_TWOWAY_CONDITIONAL_F
	    || ty == STRUCT_MULTIWAY_CONDITIONAL
	    || ty == USTRUCT_MULTIWAY_CONDITIONAL) {
	  CFG::Node* newblock = cfg->splitBlock(n, stmt);
	  cfg->connect(n, newblock, CFG::FALLTHROUGH_EDGE);
	  break;
	}
      }
    }
  }

  // -------------------------------------------------------
  // 2. Recover OPR_DO_LOOPs
  // -------------------------------------------------------
  
  // This process can create empty basic blocks
  DGraphNodeList toRemove; // holds basic blocks made empty

  for (CFG::NodesIterator nodeIt(*cfg); (bool)nodeIt; ++nodeIt) {
    CFG::Node* n = dynamic_cast<CFG::Node*>((DGraph::Node*)nodeIt);

    // Use CFG nodes representing the OPR_DO_LOOP condition to find
    // initialization and update information.  With this info, remove
    // the initialization and update statements from whatever BB they
    // may be in.  New basic blocks are not created.

    // FIXME: use a better classification method 
    if (GetCFGVertexType(cfg, n) == XAIFStrings.elem_BBForLoop()) {
      assert(n->size() == 1);
      CFG::NodeStatementsIterator stmtIt(n); 
      WN* loopWN = (WN *)((StmtHandle)stmtIt);

      WN* initWN = WN_start(loopWN);
      WN* updateWN = WN_step(loopWN);
      
      // FIXME: this is a terrible way of doing this, but the point is
      // to test correctness for now.
      for (CFG::NodesIterator nodeIt1(*cfg); (bool)nodeIt1; ++nodeIt1) {
	CFG::Node* n1 = dynamic_cast<CFG::Node*>((DGraph::Node*)nodeIt1);

	for (CFG::NodeStatementsIterator stmtIt1(n1); (bool)stmtIt1;
	     ++stmtIt1) {
	  WN* wn = (WN *)((StmtHandle)stmtIt1);
	  if ((wn == initWN) || (wn == updateWN)) {
	    n1->erase((StmtHandle)wn);
	    if (n1->size() == 0 && wn == updateWN) {
	      toRemove.push_back(n1); // ONLY erase update 
	    }                         // [EndLoop] --> [update] --backedge-->
	    break;
	  }
	}
      }
    }
  }

  // Remove empty basic blocks
  for (DGraphNodeList::iterator it = toRemove.begin(); 
       it != toRemove.end(); ++it) {
    DGraph::Node* n = (*it);
    
    // Find predecessor node.  If more than one, we cannot continue
    if (n->num_incoming() > 1) {
      continue;
    }
    DGraph::SourceNodesIterator sourceIt(n);
    CFG::Node* pred = dynamic_cast<CFG::Node*>((DGraph::Node*)(sourceIt));
    
    // All outgoing edges of 'n' become outgoing edges of 'pred'
    for (DGraph::OutgoingEdgesIterator outEdgeIt(n); 
	 (bool)outEdgeIt; ++outEdgeIt) {
      CFG::Edge* e = dynamic_cast<CFG::Edge*>((DGraph::Edge*)outEdgeIt);
      CFG::Node* snk = dynamic_cast<CFG::Node*>(e->sink());
      cfg->connect(pred, snk, e->getType());
    }
    
    cfg->remove(n); // removes all outgoing and incoming edges
    delete n;
  }
  toRemove.clear();

  
  // -------------------------------------------------------
  // 3. Split basic blocks with EndLoop and EndBranch tags (FIXME)
  // -------------------------------------------------------

  // EndBranch statments will be at the beginning of any basic block;
  // EndLoop at the end.
  for (CFG::NodesIterator nodeIt(*cfg); (bool)nodeIt; ++nodeIt) {
    CFG::Node* n = dynamic_cast<CFG::Node*>((DGraph::Node*)nodeIt);
    
    if (n->size() > 1) {
      for (CFG::NodeStatementsIterator stmtIt(n); (bool)stmtIt; ++stmtIt) {
	WN* wn = (WN*)((StmtHandle)stmtIt);

	const char* vty = GetCFGControlFlowVertexType(wn);
	WN* startWN = NULL; // start of new basic block
	if (vty == XAIFStrings.elem_BBEndBranch()) {
	  ++stmtIt; // advance iterator to find start of new basic block
	  assert((bool)stmtIt);
	  startWN = (WN*)((StmtHandle)stmtIt);
	}
	else if (vty == XAIFStrings.elem_BBEndLoop()) {
	  startWN = wn;
	}
	
	if (startWN) {
	  CFG::Node* newblock = cfg->splitBlock(n, (StmtHandle)startWN);
	  cfg->connect(n, newblock, CFG::FALLTHROUGH_EDGE);
	  break;
	}
      }
    }
  }
  
}


//***************************************************************************

// GetCFGVertexType: A CFG vertex is either an Entry, Exit,
// BasicBlock, or a special structured control flow vertex (e.g., Branch,
// ForLoop, PreLoop, PostLoop).  The string returned is from
// 'XAIFStrings' which means users can compare on pointer value
// (instead of using strcmp()).
//
// Vertices are classified by the statements contained within.  Since
// the classifications are mutually exclusive, a vertex should not
// contain two statements that correspond to structured control flow.
//
// FIXME: we know that loop and if BBs should only have one node in
// them. because of MassageOA...
static const char*
GetCFGVertexType(CFG* cfg, CFG::Node* n)
{
  // We know these are cheap so they can be recomputed each time we are called
  CFG::Node* entry = cfg->Entry();
  CFG::Node* exit = cfg->Exit();
  
  if (n == entry) {
    return XAIFStrings.elem_BBEntry();
  } else if (n == exit) { 
    return XAIFStrings.elem_BBExit();
  }
  
  // FIXME: we do not need to iterate over all statements since
  // control flow statements contructs will be in their own xaif:BB.
  for (CFG::NodeStatementsIterator stmtIt(n); (bool)stmtIt; ++stmtIt) {
    WN* wstmt = (WN *)((StmtHandle)stmtIt);
    const char* vty = GetCFGControlFlowVertexType(wstmt);
    if (vty) { 
      return vty; 
    }
  }
  
  return XAIFStrings.elem_BB(); // default, non-structured type
}


// GetCFGControlFlowVertexType: If the WHIRL statement corresponds to a
// CFG *control flow* vertex, return that type.  Otherwise return NULL.
// Returns strings from XAIFStrings.
static const char*
GetCFGControlFlowVertexType(WN* wstmt) // FIXME
{
  OPERATOR opr = WN_operator(wstmt);
  switch (opr) {
    
    // In OA, loop nodes represent the *condition* (not the body).
    // For a DO_LOOP, it additionally represents the initialization
    // and update statements.
  case OPR_DO_LOOP: 
    return XAIFStrings.elem_BBForLoop();
  case OPR_DO_WHILE: 
    return XAIFStrings.elem_BBPostLoop();
  case OPR_WHILE_DO:
    return XAIFStrings.elem_BBPreLoop();

    // In OA, IF nodes represent the *condition* (not the body)
  case OPR_IF:
  case OPR_TRUEBR:   // unstructured
  case OPR_FALSEBR:  // unstructured
    return XAIFStrings.elem_BBBranch();
  case OPR_SWITCH:   // unstructured
  case OPR_COMPGOTO: // unstructured
    return XAIFStrings.elem_BBBranch();
    
    // Currently we use special comments to denote EndBranch and EndLoop
  case OPR_COMMENT: 
    {
      static const char* endbr = XAIFStrings.elem_BBEndBranch();
      static const char* endlp = XAIFStrings.elem_BBEndLoop();
      const char* com = Index_To_Str(WN_GetComment(wstmt));
      if (strcmp(com, endbr) == 0) {
	return endbr;
      } else if (strcmp(com, endlp) == 0) {
	return endlp;
      }
      // fall through
    }
  }
  
  return NULL;
}


// GetIDsForStmtsInBB: Returns a colon separated list for ids of
// statements within the basic block.  In the event that a statement
// id maps to zero, it is *not* included in the list.
static std::string
GetIDsForStmtsInBB(CFG::Node* node, XlationContext& ctxt)
{
  std::string idstr;
  bool emptystr = true;
  
  for (CFG::NodeStatementsIterator stmtIt(node); (bool)stmtIt; ++stmtIt) {
    WN* wstmt = (WN *)((StmtHandle)stmtIt);
    WNId id = ctxt.FindWNId(wstmt);
    
    // Skip statements without a valid id
    if (id == 0) { continue; }

    const char* str = Num2Str(id, "%lld");
    //std::cout << id << " --> " << str << " // ";
    
    if (!emptystr) {
      idstr += ":";
    }
    idstr += str;
    emptystr = false;
  }
 
  return idstr;
}


// GetCFGEdgeCondVal: Given a CFG edge, returns a pair indicating
// whether the edge has a condition value, and if so, its value.
// (There is no reserved NULL value for the condition value; it should
// only be used when the first part of the pair is true!)
static pair<bool, INT64>
GetCFGEdgeCondVal(const CFG::Edge* edge)
{
  CFG::EdgeType ety = edge->getType();
  WN* eexpr = (Pro64ExprHandle)edge->getExpr();
  
  bool hasCondVal = false;
  INT64 condVal = 0;
  if (ety == CFG::TRUE_EDGE) {
    hasCondVal = true;
    condVal = 1;
  } 
  else if (ety == CFG::MULTIWAY_EDGE && eexpr) {
    hasCondVal = true;
    OPERATOR opr = WN_operator(eexpr);
    if (opr == OPR_CASEGOTO) { // from an OPR_SWITCH
      condVal = WN_const_val(eexpr);
    } 
    else if (opr == OPR_GOTO) { // from an OPR_COMPGOTO
      // to find condVal, must find parent COMPGOTO and then find the
      // index of this GOTO in the jumptable.
      ASSERT_FATAL(false, (DIAG_UNIMPLEMENTED, "Unimplemented."));
    } else {
      ASSERT_FATAL(false, (DIAG_UNIMPLEMENTED, "Programming Error."));
    }
  }
  return pair<bool, INT64>(hasCondVal, condVal);
}


//***************************************************************************
// WNXlationTable
//***************************************************************************

#define TABLE_SZ (OPERATOR_LAST + 1)
#define INIT_TABLE_SZ \
  (sizeof(WNXlationTable::initTable) / sizeof(WNXlationTable::InitEntry))


bool WNXlationTable::initialized = false;

WNXlationTable::Handler WNXlationTable::table[TABLE_SZ];
unsigned int WNXlationTable::tableSz = TABLE_SZ;

WNXlationTable::InitEntry WNXlationTable::initTable[] = {
  
  // Note: Organization generally corresponds to that in
  // Open64/documentation/whirl.tex
  
  // Structured control flow
  { OPR_FUNC_ENTRY,           &xlate_FUNC_ENTRY },
  { OPR_BLOCK,                &xlate_BLOCK },
  { OPR_REGION,               &WN2F_region },
  { OPR_REGION_EXIT,          &xlate_GOTO },
  { OPR_DO_LOOP,              &xlate_DO_LOOP },
  { OPR_DO_WHILE,             &xlate_DO_WHILE },
  { OPR_WHILE_DO,             &xlate_WHILE_DO },
  { OPR_IF,                   &xlate_IF },
  
  // Other control flow
  { OPR_IMPLIED_DO,           &WN2F_noio_implied_do },
  { OPR_GOTO,                 &xlate_GOTO },
  { OPR_SWITCH,               &xlate_SWITCH },
  { OPR_CASEGOTO,             &WN2F_casegoto },
  { OPR_COMPGOTO,             &WN2F_compgoto },
  { OPR_AGOTO,                &WN2F_agoto },
  { OPR_ALTENTRY,             &xlate_ALTENTRY },
  { OPR_TRUEBR,               &xlate_condBR },
  { OPR_FALSEBR,              &xlate_condBR },
  { OPR_RETURN,               &xlate_RETURN },
  { OPR_RETURN_VAL,           &xlate_RETURN_VAL },
  { OPR_LABEL,                &xlate_LABEL },

  // Statements: Calls
  { OPR_CALL,                 &xlate_CALL },
  { OPR_ICALL,                &xlate_CALL },
  { OPR_PICCALL,              &xlate_CALL },
  { OPR_INTRINSIC_CALL,       &xlate_INTRINSIC_CALL },
  { OPR_IO,                   &xlate_IO },

  // Statements: Other
  { OPR_EVAL,                 &WN2F_eval },
  { OPR_PRAGMA,               &xlate_PRAGMA },
  { OPR_XPRAGMA,              &xlate_PRAGMA },
  { OPR_PREFETCH,             &xlate_PREFETCH },
  { OPR_PREFETCHX,            &xlate_PREFETCH },
  { OPR_COMMENT,              &xlate_COMMENT },
  { OPR_TRAP,                 &xlate_ignore }, // FIXME
  { OPR_ASSERT,               &xlate_ignore }, // FIXME
  { OPR_FORWARD_BARRIER,      &xlate_ignore }, // FIXME
  { OPR_BACKWARD_BARRIER,     &xlate_ignore }, // FIXME
  { OPR_DEALLOCA,             &WN2F_dealloca },

  { OPR_USE,                  &xlate_USE },
  { OPR_NAMELIST,             &WN2F_namelist_stmt },
  { OPR_IMPLICIT_BND,         &WN2F_implicit_bnd },  
  { OPR_NULLIFY,              &WN2F_nullify_stmt },
  { OPR_INTERFACE,            &WN2F_interface_blk },
  { OPR_ARRAY_CONSTRUCT,      &WN2F_ar_construct },
  
  // Memory Access (or assignment and variable references)
  { OPR_LDA,                  &xlate_LDA },    // Leaf
  { OPR_LDID,                 &xlate_LDID },
  { OPR_STID,                 &xlate_STID },
  { OPR_ILOAD,                &xlate_ILOAD },
  { OPR_ILOADX,               &xlate_ILOADX },
  { OPR_MLOAD,                &WN2F_mload },
  { OPR_ISTORE,               &xlate_ISTORE },
  { OPR_ISTOREX,              &xlate_ISTOREX },
  { OPR_MSTORE,               &WN2F_mstore },

  { OPR_PSTID,                &WN2F_pstid },   // Pseudo-registers 
  { OPR_PSTORE,               &WN2F_pstore }, 

  // Type conversion
  { OPR_CVT,                  &WN2F_cvt },
  { OPR_CVTL,                 &WN2F_cvtl },
  { OPR_TAS,                  &WN2F_tas },
  
  // Expressions: Unary operations
  { OPR_INTCONST,             &xlate_INTCONST }, // Leaf
  { OPR_CONST,                &xlate_CONST },    // Leaf

  { OPR_NEG,                  &xlate_UnaryOp },
  { OPR_ABS,                  &xlate_UnaryOp },
  { OPR_SQRT,                 &xlate_UnaryOp },
  { OPR_RSQRT,                &WN2F_rsqrt },
  { OPR_RECIP,                &xlate_RECIP },
  { OPR_REALPART,             &WN2F_realpart }, // OPR_FIRSTPART
  { OPR_IMAGPART,             &WN2F_imagpart }, // OPR_SECONDPART
  { OPR_PAREN,                &xlate_PAREN },
  { OPR_RND,                  &xlate_UnaryOp },
  { OPR_TRUNC,                &xlate_UnaryOp },
  { OPR_CEIL,                 &xlate_UnaryOp },
  { OPR_FLOOR,                &xlate_UnaryOp },
  { OPR_BNOT,                 &xlate_UnaryOp },
  { OPR_LNOT,                 &xlate_UnaryOp },
  { OPR_PARM,                 &WN2F_parm },
  { OPR_ALLOCA,               &WN2F_alloca },

  // Expressions: Binary operations
  { OPR_COMPLEX,              &WN2F_complex }, // OPR_PAIR
  { OPR_ADD,                  &xlate_BinaryOp },
  { OPR_SUB,                  &xlate_BinaryOp },
  { OPR_MPY,                  &xlate_BinaryOp },
  { OPR_DIV,                  &xlate_BinaryOp },
  { OPR_MOD,                  &xlate_BinaryOp },
  { OPR_REM,                  &xlate_BinaryOp },
  { OPR_MAX,                  &xlate_BinaryOp },
  { OPR_MIN,                  &xlate_BinaryOp },
  { OPR_EQ,                   &xlate_BinaryOp },
  { OPR_NE,                   &xlate_BinaryOp },
  { OPR_GE,                   &xlate_BinaryOp },
  { OPR_GT,                   &xlate_BinaryOp },
  { OPR_LE,                   &xlate_BinaryOp },
  { OPR_LT,                   &xlate_BinaryOp },
  { OPR_BAND,                 &xlate_BinaryOp },
  { OPR_BIOR,                 &xlate_BinaryOp },
  { OPR_BNOR,                 &WN2F_bnor },
  { OPR_BXOR,                 &xlate_BinaryOp },
  { OPR_LAND,                 &xlate_BinaryOp },
  { OPR_LIOR,                 &xlate_BinaryOp },
  { OPR_CAND,                 &xlate_BinaryOp },
  { OPR_CIOR,                 &xlate_BinaryOp },
  { OPR_SHL,                  &xlate_BinaryOp },
  { OPR_ASHR,                 &xlate_BinaryOp },
  { OPR_LSHR,                 &WN2F_lshr },
  
  // Expressions: Ternary operations
  { OPR_SELECT,               &WN2F_select },
  { OPR_MADD,                 &WN2F_madd },
  { OPR_MSUB,                 &WN2F_msub },
  { OPR_NMADD,                &WN2F_nmadd },
  { OPR_NMSUB,                &WN2F_nmsub },

  // Expressions: N-ary operations
  { OPR_ARRAY,                &xlate_ARRAY },
  { OPR_INTRINSIC_OP,         &xlate_INTRINSIC_OP },
  { OPR_TRIPLET,              &WN2F_triplet },
  { OPR_SRCTRIPLET,           &WN2F_src_triplet },
  { OPR_ARRAYEXP,             &WN2F_arrayexp },
  { OPR_ARRSECTION,           &WN2F_arrsection },
  { OPR_WHERE,                &WN2F_where },
  
  
  { OPERATOR_UNKNOWN,         &xlate_unknown } // just for convenience
};

unsigned int WNXlationTable::initTableSz = INIT_TABLE_SZ;

#undef TABLE_SZ
#undef INIT_TABLE_SZ


WNXlationTable::WNXlationTable()
{
  // Initialize table with default handler
  for (int i = 0; i < tableSz; ++i) {
    table[i] = &xlate_unknown;
  }
  
  // Initialize the table using 'initTable'
  for (int i = 0; i < initTableSz; ++i) {
    table[initTable[i].opr] = initTable[i].fn;
  }
  
  initialized = true; // could use to this initialize on demand
}

WNXlationTable::~WNXlationTable()
{
}

