// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/XAIFStrings.h,v 1.7 2003/09/05 21:41:53 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/XAIFStrings.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef XAIFStrings_INCLUDED_h
#define XAIFStrings_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>

//************************* Xerces Include Files ****************************

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLString.hpp>

//*************************** User Include Files ****************************

//*************************** Forward Declarations ***************************

//****************************************************************************

XERCES_CPP_NAMESPACE_USE

// A class containing strings for XAIF.  
class XAIFStringRepository
{
public: 
  enum {
    // -----------------------------------------------------

    // Common attributes
    ATTR_annot = 0, // annotation
    ATTR_Vid,       // vertex_id
    ATTR_Eid,       // edge_id
    ATTR_scopeId,   // scope_id
    ATTR_symId,     // symbol_id
    ATTR_source,    // source
    ATTR_target,    // target
    
    // -----------------------------------------------------

    // xaif:ScopeHierarchy, xaif:Scope, xaif:SymbolTable
    ELEM_ScopeHierarchy,
    ELEM_Scope,
    ELEM_SymTab,

    // xaif:Symbol
    ELEM_Symbol,
    ATTR_kind,
    ATTR_type,
    ATTR_shape,

    // -----------------------------------------------------

    // xaif:ControlFlowGraph
    ELEM_CFG,
    
    // xaif:BasicBlock
    ELEM_BB,
    ELEM_BBEntry,
    ELEM_BBExit,
    ELEM_BBIf,
    ELEM_BBForLoop,
    ELEM_BBPreLoop,
    ELEM_BBPostLoop,

    // Statements
    ELEM_Assign,
    ELEM_SubCall,
    ELEM_Marker,

    ELEM_AssignLHS,
    ELEM_AssignRHS,

    // Expressions
    ELEM_VarRef,
    ELEM_Constant,
    ELEM_Intrinsic,
    ELEM_FuncCall,
    ELEM_BoolOp,

    ELEM_SymRef,
    
    ELEM_ExprEdge,

    ATTR_name,
    ATTR_value,

    // DerivativePropagator
    ELEM_DerivProp,  // block

    ELEM_SetDeriv,   // stmt
    ELEM_Sax,
    ELEM_Saxpy,

    ELEM_Tgt,        // expr
    ELEM_Src,
    ELEM_AX,
    ELEM_A,
    ELEM_X,
    ELEM_Y,

    // -----------------------------------------------------

    // Special tags
    TAG_SymTabId, // Tags a colon-separated list of symbol table (ST_TAB) ids
    TAG_SymId,    // Tags a colon-separated list of symbol (ST) ids
    
    TAG_PUId,     // Tags a colon-separated list of PU ids
    TAG_WHIRLId,  // Tags a colon-separated list of WHIRL (WN) ids

    TAG_End,      // End of tag information
    
    // -----------------------------------------------------

    NUM_STRINGS // Not a valid string!
  };

public:
  XAIFStringRepository();
  ~XAIFStringRepository();
  
  // -------------------------------------------------------
  // Must be called after Xerces is initialized.  All XML strings are
  // unavailable until this has been called.
  // -------------------------------------------------------
  void XMLInitialize();

  // -------------------------------------------------------
  // General access to strings
  // -------------------------------------------------------
  
  const char* c(int i) const
  {
    if (0 <= i && i < NUM_STRINGS) { return c_strTbl[i]; }
    else { return NULL; }
  }

  XMLCh* xml(int i) const
  {
    if (0 <= i && i < NUM_STRINGS) { return x_strTbl[i]; }
    else { return NULL; }
  }

  // -------------------------------------------------------
  // Quick access to strings
  // -------------------------------------------------------
  
  // FIXME: add c string version
  // Common attributes
  const char* attr_annot() const   { return c_strTbl[ATTR_annot]; }
  XMLCh*      attr_annot_x() const { return x_strTbl[ATTR_annot]; }
  XMLCh*      attr_Vid_x() const { return x_strTbl[ATTR_Vid]; }
  XMLCh*      attr_Eid_x() const { return x_strTbl[ATTR_Eid]; }
  const char* attr_scopeId() const { return c_strTbl[ATTR_scopeId]; }
  XMLCh*      attr_scopeId_x() const { return x_strTbl[ATTR_scopeId]; }
  const char* attr_symId() const { return c_strTbl[ATTR_symId]; }
  XMLCh*      attr_symId_x() const { return x_strTbl[ATTR_symId]; }
  XMLCh*      attr_source_x() const { return x_strTbl[ATTR_source]; }
  XMLCh*      attr_target_x() const { return x_strTbl[ATTR_target]; }
  
  // -----------------------------------------------------
  
  // xaif:ScopeHierarchy, xaif:Scope, xaif:SymbolTable
  XMLCh*      elem_ScopeHierarchy_x() const { return x_strTbl[ELEM_ScopeHierarchy]; }
  XMLCh*      elem_Scope_x() const { return x_strTbl[ELEM_Scope]; }
  XMLCh*      elem_SymTab_x() const { return x_strTbl[ELEM_SymTab]; }
    
  // xaif:Symbol
  XMLCh*      elem_Symbol_x() const { return x_strTbl[ELEM_Symbol]; }
  
  const char* attr_kind() const { return c_strTbl[ATTR_kind]; }
  const char* attr_type() const { return c_strTbl[ATTR_type]; }
  const char* attr_shape() const { return c_strTbl[ATTR_shape]; }
  XMLCh*      attr_kind_x() const { return x_strTbl[ATTR_kind]; }
  XMLCh*      attr_type_x() const { return x_strTbl[ATTR_type]; }
  XMLCh*      attr_shape_x() const { return x_strTbl[ATTR_shape]; }
  
  // -----------------------------------------------------
  
  // xaif:ControlFlowGraph
  XMLCh*      elem_CFG_x() const { return x_strTbl[ELEM_CFG]; }
  
  // xaif:BasicBlock
  XMLCh*      elem_BB_x() const { return x_strTbl[ELEM_BB]; }
  XMLCh*      elem_BBEntry_x() const { return x_strTbl[ELEM_BBEntry]; }
  XMLCh*      elem_BBExit_x() const { return x_strTbl[ELEM_BBExit]; }
  XMLCh*      elem_BBIf_x() const { return x_strTbl[ELEM_BBIf]; }
  XMLCh*      elem_BBForLoop_x() const { return x_strTbl[ELEM_BBForLoop]; }
  XMLCh*      elem_BBPreLoop_x() const { return x_strTbl[ELEM_BBPreLoop]; }
  XMLCh*      elem_BBPostLoop_x() const { return x_strTbl[ELEM_BBPostLoop]; }

  // Statements
  XMLCh*      elem_Assign_x() const { return x_strTbl[ELEM_Assign]; }
  XMLCh*      elem_SubCall_x() const { return x_strTbl[ELEM_SubCall]; }
  XMLCh*      elem_Marker_x() const { return x_strTbl[ELEM_Marker]; }

  XMLCh*      elem_AssignLHS_x() const { return x_strTbl[ELEM_AssignLHS]; }
  XMLCh*      elem_AssignRHS_x() const { return x_strTbl[ELEM_AssignRHS]; }

  // Expressions
  XMLCh*      elem_VarRef_x() const { return x_strTbl[ELEM_VarRef]; }
  XMLCh*      elem_Constant_x() const { return x_strTbl[ELEM_Constant]; }
  XMLCh*      elem_Intrinsic_x() const { return x_strTbl[ELEM_Intrinsic]; }
  XMLCh*      elem_FuncCall_x() const { return x_strTbl[ELEM_FuncCall]; }
  XMLCh*      elem_BoolOp_x() const { return x_strTbl[ELEM_BoolOp]; }
  
  XMLCh*      elem_SymRef_x() const { return x_strTbl[ELEM_SymRef]; }
  
  XMLCh*      elem_ExprEdge_x() const { return x_strTbl[ELEM_ExprEdge]; }

  XMLCh*      attr_name_x() const { return x_strTbl[ATTR_name]; }
  XMLCh*      attr_value_x() const { return x_strTbl[ATTR_value]; }

  // DerivativePropagator
  XMLCh*      elem_DerivProp_x() const { return x_strTbl[ELEM_DerivProp]; }
  
  XMLCh*      elem_SetDeriv_x() const { return x_strTbl[ELEM_SetDeriv]; }
  XMLCh*      elem_Sax_x() const { return x_strTbl[ELEM_Sax]; }
  XMLCh*      elem_Saxpy_x() const { return x_strTbl[ELEM_Saxpy]; }

  XMLCh*      elem_Tgt_x() const { return x_strTbl[ELEM_Tgt]; }
  XMLCh*      elem_Src_x() const { return x_strTbl[ELEM_Src]; }
  XMLCh*      elem_AX_x() const { return x_strTbl[ELEM_AX]; }
  XMLCh*      elem_A_x() const { return x_strTbl[ELEM_A]; }
  XMLCh*      elem_X_x() const { return x_strTbl[ELEM_X]; }
  XMLCh*      elem_Y_x() const { return x_strTbl[ELEM_Y]; }
  
  // -----------------------------------------------------
  
  // Special tags
  const char* tag_SymTabId() const   { return c_strTbl[TAG_SymTabId]; }
  XMLCh*      tag_SymTabId_x() const { return x_strTbl[TAG_SymTabId]; }

  const char* tag_SymId() const   { return c_strTbl[TAG_SymId]; }
  XMLCh*      tag_SymId_x() const { return x_strTbl[TAG_SymId]; }

  const char* tag_PUId() const   { return c_strTbl[TAG_PUId]; }
  XMLCh*      tag_PUId_x() const { return x_strTbl[TAG_PUId]; }

  const char* tag_WHIRLId() const   { return c_strTbl[TAG_WHIRLId]; }
  XMLCh*      tag_WHIRLId_x() const { return x_strTbl[TAG_WHIRLId]; }

  const char* tag_End() const { return c_strTbl[TAG_End]; }
  XMLCh*      tag_End_x() const { return x_strTbl[TAG_End]; }

private:
  static const char* c_strTbl[];
  XMLCh** x_strTbl;
};

// A global instance providing everyone access to the above info
extern XAIFStringRepository XAIFStrings;

//***************************************************************************

#endif // XAIFStrings_INCLUDED_h
