// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/XAIFStrings.cxx,v 1.15 2004/03/24 13:32:33 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/XAIFStrings.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <iostream>

#include <stdlib.h>
#include <string.h>

//************************* Xerces Include Files ****************************

//*************************** User Include Files ****************************

#include "XAIFStrings.h"

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

//****************************************************************************

XAIFStringRepository XAIFStrings;

//****************************************************************************

// Note: The order must match the enumeration!
const char* XAIFStringRepository::c_strTbl[] = {
  // -----------------------------------------------------
  
  // Common attributes
  "annotation",
  "vertex_id",
  "edge_id",
  "scope_id",
  "symbol_id",
  
  "active",
  "deriv",
  
  "source",
  "target",
  
  // -----------------------------------------------------

  // xaif:ScopeHierarchy, xaif:Scope, xaif:SymbolTable
  "xaif:ScopeHierarchy",
  "xaif:Scope",
  "xaif:SymbolTable",

  // xaif:Symbol
  "xaif:Symbol",
  "kind",
  "type",
  "shape",
  
  // -----------------------------------------------------
  
  // xaif:ControlFlowGraph
  "xaif:ControlFlowGraph",
  
  "xaif:ControlFlowEdge",
  
  // xaif:BasicBlock
  "xaif:BasicBlock",
  "xaif:Entry",
  "xaif:Exit",
  "xaif:Branch",
  "xaif:ForLoop",
  "xaif:PreLoop",
  "xaif:PostLoop",
  
  "xaif:EndBranch",
  "xaif:EndLoop",
  
  "xaif:Condition",
  
  // Statements
  "xaif:Assignment",
  "xaif:SubroutineCall",
  "xaif:InlinableSubroutineCall",
  "xaif:Marker",
  
  "xaif:AssignmentLHS",
  "xaif:AssignmentRHS",
  
  "xaif:Argument",
  "xaif:ArgumentSubstitute",
  
  "subroutine_name",
  
  // Expressions
  "xaif:VariableReference",
  "xaif:Constant",
  "xaif:Intrinsic",
  "xaif:FunctionCall",
  "xaif:BooleanOperation",

  "xaif:ExpressionEdge",

  "name",
  "value",
  "position",
  
  // Variable Reference Expressions
  "xaif:SymbolReference",
  "xaif:ArrayElementReference",
  
  "xaif:Index",
  
  "xaif:VariableReferenceEdge",

  // DerivativeAccumulator
  "xaif:DerivativePropagator", // block
  
  "xaif:SetDeriv",             // stmt
  "xaif:ZeroDeriv",
  "xaif:Sax",
  "xaif:Saxpy",
  
  "xaif:Tgt",                  // expr
  "xaif:Src",
  "xaif:AX",
  "xaif:A",
  "xaif:X",
  "xaif:Y",
  
  // -----------------------------------------------------
  
  // Special tags
  "{SymTab_Id#",
  "{Sym_Id#",
  "{PU_Id#",
  "{WHIRL_Id#",
  "}"
};

//****************************************************************************

XAIFStringRepository::XAIFStringRepository()
{ 
  x_strTbl = new XMLCh*[NUM_STRINGS];
  for (int i = 0; i < NUM_STRINGS; ++i) {
    x_strTbl[i] = NULL;
  }
}

void
XAIFStringRepository::XMLInitialize()
{ 
  for (int i = 0; i < NUM_STRINGS; ++i) {
    const char* str = c_strTbl[i];
    unsigned int len = strlen(str);
    
    x_strTbl[i] = new XMLCh[len + 1];
    XMLString::transcode(str, x_strTbl[i], len);
  }
}

XAIFStringRepository::~XAIFStringRepository()
{
  for (int i = 0; i < NUM_STRINGS; ++i) {
    delete[] x_strTbl[i];
  }
  delete[] x_strTbl;
}
