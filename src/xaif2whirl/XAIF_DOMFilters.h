// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMFilters.h,v 1.16 2004/07/30 17:52:16 eraxxon Exp $

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
XercesPrintNode(std::ostream& os, const DOMNode* n);

// Dumps the tree rooted at 'n'
void
XercesPrintTree(std::ostream& os, const DOMNode* n);


std::ostream& 
operator<<(std::ostream& os, const DOMElement& elem);


// Shortcut for XercesPrintNode
void 
XercesDumpNode(const DOMNode* n);

// Shortcut for XercesPrintTree
void 
XercesDumpTree(const DOMNode* n);

void 
XercesDumpNode(void* n); // For *^#% debuggers

void 
XercesDumpTree(void* n); // For *^#% debuggers



// Useful for either finding one element or iterating over all the
// children of a node.  Much more efficient than the Xerces DOM
// iterators.

#if 0 
  // Sample DOMNodeIterator iteration (inspects all nodes in the subtree)
  DOMDocument* doc = bbElem->getOwnerDocument();
  DOMNodeIterator* it = 
    doc->createNodeIterator((DOMNode*)bbElem, DOMNodeFilter::SHOW_ALL, 
                            new XAIF_BBStmtElemFilter(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* stmt = dynamic_cast<DOMElement*>(node);
    // ...
  }
  it->release();
#endif

DOMElement*
GetFirstChildElement(const DOMNode* n);

DOMElement*
GetLastChildElement(const DOMNode* n);

DOMElement*
GetChildElement(const DOMNode* n, const XMLCh* name);

DOMElement*
GetChildElement(const DOMNode* n, const DOMNodeFilter* filter);

unsigned int
GetChildElementCount(const DOMNode* n);

DOMElement*
GetPrevSiblingElement(const DOMNode* n);

DOMElement*
GetNextSiblingElement(const DOMNode* n);

DOMElement*
GetNextSiblingElement(const DOMNode* n, const XMLCh* name);

DOMElement*
GetNextSiblingElement(const DOMNode* n, const DOMNodeFilter* filter);


//****************************************************************************

class XAIF_ElemFilter : public DOMNodeFilter
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  XAIF_ElemFilter(const XMLCh* name) : mName(name) { }
  ~XAIF_ElemFilter() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the filter interface
  // -----------------------------------------------------------------------
  short acceptNode(const DOMNode *node) const;

private:
  const XMLCh* mName;
};

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
  XAIF_CFGElemFilter(bool cfgOrReplaceList_ = true) 
    : cfgOrReplaceList(cfgOrReplaceList_) { }
  ~XAIF_CFGElemFilter() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the filter interface
  // -----------------------------------------------------------------------
  short acceptNode(const DOMNode *node) const;
  
  static bool IsCFG(const DOMNode *node);
  static bool IsReplaceList(const DOMNode *node);
  
  static bool IsReplacement(const DOMNode *node);
  
private:
  bool cfgOrReplaceList;
};


class XAIF_BBElemFilter : public DOMNodeFilter
{
public:
  // -----------------------------------------------------------------------
  //  Constructors and Destructor
  // -----------------------------------------------------------------------
  // if 'onlyBasicBlock' is true, only xaif:BasicBlocks are in the iteration
  XAIF_BBElemFilter(bool edges = true)
    : includeEdges(edges) { }
  ~XAIF_BBElemFilter() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the filter interface
  // -----------------------------------------------------------------------
  short acceptNode(const DOMNode *node) const;
  
  static bool IsAnyBB(const DOMNode *node);
  static bool IsBBEntry(const DOMNode *node);
  static bool IsBBExit(const DOMNode *node);
  static bool IsBB(const DOMNode *node);
  static bool IsBBBranch(const DOMNode *node);
  static bool IsBBEndBr(const DOMNode *node);
  static bool IsBBForLoop(const DOMNode *node);
  static bool IsBBPreLoop(const DOMNode *node);
  static bool IsBBPostLoop(const DOMNode *node);
  static bool IsBBEndLoop(const DOMNode *node);

  static bool IsEdge(const DOMNode *node);

private:
  bool includeEdges;
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

  static bool IsAnyStmt(const DOMNode *node);
  
  static bool IsAssign(const DOMNode *node);
  static bool IsSubCall(const DOMNode *node);
  static bool IsInlinableSubCall(const DOMNode *node);
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
