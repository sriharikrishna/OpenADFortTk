// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMFilters.h,v 1.10 2003/10/10 17:57:32 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMFilters.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef XAIF_DOMFilters_INCLUDED_h
#define XAIF_DOMFilters_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>

//************************* Xerces Include Files ****************************

#include <xercesc/dom/DOMNodeFilter.hpp>

//*************************** User Include Files ****************************

//*************************** Forward Declarations ***************************

XERCES_CPP_NAMESPACE_USE

//****************************************************************************

// FIXME: this could be moved to a better place

// Dumps only this node
void 
XercesDumpNode(const DOMNode* n);

// Dumps the tree rooted at 'n'
void 
XercesDumpTree(const DOMNode* n);

void 
XercesDumpNode(void* n); // For *^#% debuggers

void 
XercesDumpTree(void* n); // For *^#% debuggers


DOMElement*
GetFirstChildElement(const DOMNode* n);

DOMElement*
GetLastChildElement(const DOMNode* n);

DOMElement*
GetChildElement(const DOMNode* n, const XMLCh* name);

unsigned int
GetChildElementCount(const DOMNode* n);

DOMElement*
GetPrevSiblingElement(const DOMNode* n);

DOMElement*
GetNextSiblingElement(const DOMNode* n);

DOMElement*
GetNextSiblingElement(const DOMNode* n, const XMLCh* name);

//****************************************************************************

class XAIF_ScopeElemFilter : public DOMNodeFilter
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  XAIF_ScopeElemFilter() { }
  ~XAIF_ScopeElemFilter() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the filter interface
  // -----------------------------------------------------------------------
  short acceptNode(const DOMNode *node) const;

private:
};

//****************************************************************************

class XAIF_SymbolElemFilter : public DOMNodeFilter
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  XAIF_SymbolElemFilter() { }
  ~XAIF_SymbolElemFilter() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the filter interface
  // -----------------------------------------------------------------------
  short acceptNode(const DOMNode *node) const;

private:
};

//****************************************************************************

class XAIF_CFGElemFilter : public DOMNodeFilter
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  XAIF_CFGElemFilter() { }
  ~XAIF_CFGElemFilter() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the filter interface
  // -----------------------------------------------------------------------
  short acceptNode(const DOMNode *node) const;

private:
};


class XAIF_BBElemFilter : public DOMNodeFilter
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  // if 'onlyBasicBlock' is true, only xaif:BasicBlocks are in the iteration
  XAIF_BBElemFilter(bool onlyBasicBlock_ = false)
    : onlyBasicBlock(onlyBasicBlock_) { }
  ~XAIF_BBElemFilter() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the filter interface
  // -----------------------------------------------------------------------
  short acceptNode(const DOMNode *node) const;
  
  static bool IsAnyBB(const DOMNode *node);
  static bool IsBB(const DOMNode *node);
  static bool IsBBIf(const DOMNode *node);
  static bool IsBBForLoop(const DOMNode *node);
  static bool IsBBPreLoop(const DOMNode *node);
  static bool IsBBPostLoop(const DOMNode *node);

private:
  bool onlyBasicBlock;
};


// Accepts: basic block statements and DerivativeAccumulator
class XAIF_BBStmtElemFilter : public DOMNodeFilter
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  XAIF_BBStmtElemFilter() { }
  ~XAIF_BBStmtElemFilter() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the filter interface
  // -----------------------------------------------------------------------
  short acceptNode(const DOMNode *node) const;

  static bool IsStmt(const DOMNode *node);
  static bool IsMarker(const DOMNode *node);
  static bool IsDerivProp(const DOMNode *node);

private:
};


class XAIF_DerivPropStmt : public DOMNodeFilter
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  XAIF_DerivPropStmt() { }
  ~XAIF_DerivPropStmt() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the filter interface
  // -----------------------------------------------------------------------
  short acceptNode(const DOMNode *node) const;

  static bool IsSetDeriv(const DOMNode *node);
  static bool IsSax(const DOMNode *node);
  static bool IsSaxpy(const DOMNode *node);
  static bool IsZeroDeriv(const DOMNode *node);  

private:
};


//***************************************************************************

#endif // XAIF_DOMFilters_INCLUDED_h
