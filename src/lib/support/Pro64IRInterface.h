// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Attic/Pro64IRInterface.h,v 1.5 2003/07/24 20:20:03 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Attic/Pro64IRInterface.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//-----------------------------------------------------------------------------
//
// A Pro64-specific derivation of the IR interface.
//
// FIXME: Just started, work in progress.
//
// First draft by Jason Eckhardt
//
//-----------------------------------------------------------------------------

#ifndef Pro64IRInterface_h
#define Pro64IRInterface_h

//************************** System Include Files ***************************

#include <cassert>
#include <list>
#include <string>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>
#include "ir_reader.h" // For dump_wn(). //FIXME

//*************************** User Include Files ****************************

#include <OpenAnalysis/Utils/DGraph.h>
#include <OpenAnalysis/Interface/IRInterface.h>

// IRInterface types: Use OA_IRHANDLETYPE_VOIDPTR
//   ProcHandle - PU_Info*
//   StmtHandle - WN*
//   ExprHandle - WN*
//   LeafHandle - WN*
//   StmtLabel  - INT32
//   SymHandle  - ST*

//*************************** Forward Declarations ***************************

//***************************************************************************

void 
RestoreOpen64PUGlobalVars(PU_Info *pu);

void
SaveOpen64PUGlobalVars(PU_Info *pu);

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

// Iterates in PU_Info* pu_forest in DFS order
class Pro64IRProcIterator : public IRProcIterator {
public:
  Pro64IRProcIterator(PU_Info* pu_forest);
  ~Pro64IRProcIterator() { }
  
  ProcHandle Current() { return (ProcHandle)(*pulist_iter); }
  bool IsValid () { return (pulist_iter != pulist.end()); }
  void operator++();
  
  void Reset();

private:
  void prepare_current_pu();
  std::list<PU_Info*> pulist; // list of PUs (functions)
  std::list<PU_Info*>::iterator pulist_iter;
  void build_pu_list(PU_Info* pu);
};

class Pro64IRStmtIterator: public IRStmtIterator {
public:
  Pro64IRStmtIterator(WN *wn) : start_wn(wn), curr_wn(NULL) { Reset(); }
  ~Pro64IRStmtIterator() { }

  StmtHandle Current () { return (StmtHandle)curr_wn; }
  bool IsValid () { return (curr_wn != 0); }
  void operator++ () { curr_wn = WN_next (curr_wn) ? WN_next (curr_wn) : 0; }

  void Reset() { curr_wn = start_wn; }

private:
  WN *start_wn;
  WN *curr_wn;
};

class Pro64IRUseDefIterator: public IRUseDefIterator {
public:
  Pro64IRUseDefIterator(WN *n, int uses_or_defs);
  Pro64IRUseDefIterator() { assert (0); }
  ~Pro64IRUseDefIterator() { }

  LeafHandle Current () { return 0; }
  bool IsValid () { return false; }
  void operator++ () { };

  void Reset() { }
	
private:
};

class Pro64IRCallsiteIterator : public IRCallsiteIterator {
public:
  Pro64IRCallsiteIterator(WN *wn);
  ~Pro64IRCallsiteIterator() { }
  
  ExprHandle Current() { return (StmtHandle)(*wnlist_iter); }
  bool IsValid () { return (wnlist_iter != wnlist.end()); }
  void operator++() { ++wnlist_iter; }

  void Reset();
  
private:
  std::list<WN*> wnlist; // a list of function call nodes
  std::list<WN*>::iterator wnlist_iter;
  void build_func_call_list(WN *wn);
};

class Pro64IRCallsiteParamIterator : public IRCallsiteParamIterator {
public:
  Pro64IRCallsiteParamIterator(WN *wn);
  ~Pro64IRCallsiteParamIterator() { }
  
  ExprHandle Current() { return (StmtHandle)(*wnlist_iter); }
  bool IsValid () { return (wnlist_iter != wnlist.end()); }
  void operator++() { ++wnlist_iter; }

  void Reset();
  
private:
  std::list<WN*> wnlist; // a list of function call nodes
  std::list<WN*>::iterator wnlist_iter;
};

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------

class Pro64IRInterface : public IRInterface {
public:
  Pro64IRInterface () { /*FIXME*/ }
  ~Pro64IRInterface () { }

  //--------------------------------------------------------
  // Procedures and call sites
  //--------------------------------------------------------
  IRProcType GetProcType(ProcHandle h) { assert(0); return ProcType_ILLEGAL; }
  IRStmtIterator *ProcBody(ProcHandle h);
  IRCallsiteIterator *GetCallsites(StmtHandle h);
  IRCallsiteParamIterator *GetCallsiteParams(ExprHandle h);
  bool IsParamProcRef(ExprHandle h) { assert(0); return false; }
  bool IsCallThruProcParam(ExprHandle h) { assert(0); return false; }

  //--------------------------------------------------------
  // Statements: General
  //--------------------------------------------------------
  IRStmtType GetStmtType (StmtHandle h);
  StmtLabel GetLabel (StmtHandle h);
  IRStmtIterator *GetFirstInCompound (StmtHandle h);

  //--------------------------------------------------------
  // Loops
  //--------------------------------------------------------
  IRStmtIterator *LoopBody (StmtHandle h);
  StmtHandle LoopHeader (StmtHandle h);
  bool LoopIterationsDefinedAtEntry (StmtHandle h);
  ExprHandle GetLoopCondition (StmtHandle h); 
  StmtHandle GetLoopIncrement (StmtHandle h);

  //--------------------------------------------------------
  // Invariant: a two-way conditional or a multi-way conditional MUST provide
  // provide either a target, or a target label
  //--------------------------------------------------------

  //--------------------------------------------------------
  // Structured two-way conditionals
  //--------------------------------------------------------
  IRStmtIterator *TrueBody (StmtHandle h);
  IRStmtIterator *ElseBody (StmtHandle h);

  //--------------------------------------------------------
  // Structured multiway conditionals
  //--------------------------------------------------------
  int NumMultiCases (StmtHandle h);
  // condition for multi body 
  ExprHandle GetSMultiCondition (StmtHandle h, int bodyIndex);
  // multi-way beginning expression
  ExprHandle GetMultiExpr (StmtHandle h);
  IRStmtIterator *MultiBody (StmtHandle h, int bodyIndex);
  bool IsBreakImplied (StmtHandle multicond);
  IRStmtIterator *GetMultiCatchall (StmtHandle h);

  //--------------------------------------------------------
  // Unstructured two-way conditionals: 
  //--------------------------------------------------------
  StmtLabel  GetTargetLabel (StmtHandle h, int n);
  ExprHandle GetCondition (StmtHandle h);

  //--------------------------------------------------------
  // Unstructured multi-way conditionals
  //--------------------------------------------------------
  int NumUMultiTargets (StmtHandle h);
  StmtLabel GetUMultiTargetLabel (StmtHandle h, int targetIndex);
  StmtLabel GetUMultiCatchallLabel (StmtHandle h);
  ExprHandle GetUMultiCondition (StmtHandle h, int targetIndex);

  //--------------------------------------------------------
  // Obtain uses and defs
  //--------------------------------------------------------
  IRUseDefIterator *GetUses (StmtHandle h);
  IRUseDefIterator *GetDefs (StmtHandle h);

  //--------------------------------------------------------
  // Symbol Handles
  //--------------------------------------------------------  

  SymHandle GetProcSymHandle(ProcHandle h) {
    PU_Info* pu = (PU_Info*)h; 
    ST* st = ST_ptr(PU_Info_proc_sym(pu));
    return (SymHandle)st;
  }

  SymHandle GetSymHandle(ExprHandle h) {
    WN* wn = (WN *)h; 
    ST* st = ((OPERATOR_has_sym(WN_operator(wn))) ? WN_st(wn) : NULL);
    return (SymHandle)st;
  }

  const char *GetSymNameFromSymHandle (SymHandle sh) {
    ST *st = (ST *) sh;
    return ((st) ? (char *)ST_name(st) : "<no-symbol>"); 
  }

  //--------------------------------------------------------
  // Debugging
  //--------------------------------------------------------  
  void PrintLeaf (LeafHandle vh, ostream & os);
  void Dump (StmtHandle stmt, ostream& os);

private:
  // Dump Whirl subtree in a compact, friendly format.
  void dump_wn_subtree (WN *, ostream &);
};



#endif // Pro64IRInterface_h
