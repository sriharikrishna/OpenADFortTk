// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMFilters.h,v 1.5 2003/09/02 15:02:21 eraxxon Exp $

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
void 
XercesDumpNode(DOMNode* n);

DOMElement*
GetFirstChildElement(DOMNode* n);

DOMElement*
GetLastChildElement(DOMNode* n);

DOMElement*
GetChildElement(DOMNode* n, XMLCh* name);

unsigned int
GetChildElementCount(DOMNode* n);

DOMElement*
GetPrevSiblingElement(DOMNode* n);

DOMElement*
GetNextSiblingElement(DOMNode* n);

DOMElement*
GetNextSiblingElement(DOMNode* n, XMLCh* name);

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
  XAIF_BBElemFilter() { }
  ~XAIF_BBElemFilter() { }
  
  // -----------------------------------------------------------------------
  //  Implementation of the filter interface
  // -----------------------------------------------------------------------
  short acceptNode(const DOMNode *node) const;

  static bool IsBB(const DOMNode *node);

private:
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
  
private:
};


//***************************************************************************

#endif // XAIF_DOMFilters_INCLUDED_h
