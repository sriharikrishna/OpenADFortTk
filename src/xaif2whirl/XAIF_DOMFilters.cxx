// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMFilters.cxx,v 1.6 2003/09/05 21:41:53 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMFilters.cxx,v $
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

#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMNodeList.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMAttr.hpp>
#include <xercesc/dom/DOMNamedNodeMap.hpp>

#include <xercesc/util/XMLString.hpp>

//*************************** User Include Files ****************************

#include "XAIF_DOMFilters.h"
#include "XercesStrX.h"

#include <lib/support/XAIFStrings.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

//****************************************************************************

static void 
XercesDumpNode(DOMNode* n, int iter);

static void 
XercesDumpTree(DOMNode* n, int ilevel);


void 
XercesDumpNode(DOMNode* n)
{
  // Iteration count starts at 0
  XercesDumpNode(n, 0);
}

void 
XercesDumpTree(DOMNode* n)
{
  // Indentation level starts at 0
  XercesDumpTree(n, 0);
}

void 
XercesDumpNode(void* n) // For *(#% debuggers
{
  XercesDumpNode((DOMNode*)n);
}

void 
XercesDumpTree(void* n) // For *(#% debuggers
{
  XercesDumpTree((DOMNode*)n);
}


static void 
XercesDumpNode(DOMNode* n, int iter)
{
  if (!n) { return; }

  // Depending on iteration, start or continue the line
  const char* prefix = (iter == 0) ? "<" : " ";
  std::cout << prefix;

  // Depending on node type, print different things
  if (n->getNodeType() == DOMNode::ATTRIBUTE_NODE) {
    DOMAttr* attr = dynamic_cast<DOMAttr*>(n);
    const XMLCh* nm = attr->getName();
    const XMLCh* val = attr->getValue();
    std::cout << XercesStrX(nm) << "='" << XercesStrX(val) << "'";
  } else {
    const XMLCh* nm = n->getNodeName();
    std::cout << XercesStrX(nm);
  }

  // Recur on certain nodes
  DOMNamedNodeMap* attrs = n->getAttributes();
  if (attrs) {
    for (XMLSize_t i = 0; i < attrs->getLength(); ++i) {
      DOMNode* attr = attrs->item(i);
      XercesDumpNode(attr, iter + 1);
    }
  }

  // End the line, if necessary
  if (iter == 0) { 
    std::cout << ">" << endl;
  }
}


static void 
XercesDumpTree(DOMNode* n, int ilevel)
{
  if (!n) { return; }

  // Dump the current node with indentation
  for (int i = ilevel; i > 0; --i) { std::cout << "  "; }
  XercesDumpNode(n);

  // Dump all children at the next indentation level
  DOMNodeList* children = n->getChildNodes();
  if (children) {
    for (XMLSize_t i = 0; i < children->getLength(); ++i) {
      DOMNode* child = children->item(i);
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) { 
	XercesDumpTree(child, ilevel + 1);
      }
    }
  }
}


DOMElement*
GetFirstChildElement(DOMNode* n)
{
  if (!n) { return NULL; }

  DOMNodeList* children = n->getChildNodes();
  if (children) {
    for (XMLSize_t i = 0; i < children->getLength(); ++i) {
      DOMNode* child = children->item(i);
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	return dynamic_cast<DOMElement*>(child);
      }
    }
  }
  return NULL;
}

DOMElement*
GetLastChildElement(DOMNode* n)
{
  if (!n) { return NULL; }

  DOMNodeList* children = n->getChildNodes();
  if (children) {
    for (int i = ((int)children->getLength() - 1); i >= 0; --i) {
      DOMNode* child = children->item(i);
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) {
	return dynamic_cast<DOMElement*>(child);
      }
    }
  }
  return NULL;
}

DOMElement*
GetChildElement(DOMNode* n, XMLCh* name)
{
  if (!n) { return NULL; }

  DOMNodeList* children = n->getChildNodes();
  if (children) {
    for (XMLSize_t i = 0; i < children->getLength(); ++i) {
      DOMNode* child = children->item(i);
      if (child->getNodeType() == DOMNode::ELEMENT_NODE
	  && XMLString::equals(name, child->getNodeName())) {
	return dynamic_cast<DOMElement*>(child);
      }
    }
  }
  return NULL;
}

unsigned int
GetChildElementCount(DOMNode* n)
{
  unsigned int cnt = 0;
  if (!n) { return cnt; }

  DOMNodeList* children = n->getChildNodes();
  if (children) {
    for (XMLSize_t i = 0; i < children->getLength(); ++i) {
      DOMNode* child = children->item(i);
      if (child->getNodeType() == DOMNode::ELEMENT_NODE) { ++cnt; }
    }
  }
  return cnt;
}

DOMElement*
GetPrevSiblingElement(DOMNode* n)
{
  if (!n) { return NULL; }

  DOMNode* node = n;
  while ( (node = node->getPreviousSibling()) ) {
    if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
      return dynamic_cast<DOMElement*>(node);
    }
  }
  return NULL;
}

DOMElement*
GetNextSiblingElement(DOMNode* n)
{
  if (!n) { return NULL; }

  DOMNode* node = n;
  while ( (node = node->getNextSibling()) ) {
    if (node->getNodeType() == DOMNode::ELEMENT_NODE) {
      return dynamic_cast<DOMElement*>(node);
    }
  }
  return NULL;
}

DOMElement*
GetNextSiblingElement(DOMNode* n, XMLCh* name)
{
  if (!n) { return NULL; }

  DOMNode* node = n;
  while ( (node = GetNextSiblingElement(node)) ) { // node must be a DOMElement
    if (XMLString::equals(name, node->getNodeName())) {
      return dynamic_cast<DOMElement*>(node);
    }
  }
  return NULL;
}


//****************************************************************************

short
XAIF_ScopeElemFilter::acceptNode(const DOMNode *node) const
{
  const XMLCh* name = node->getNodeName();
  if ( (node->getNodeType() == DOMNode::ELEMENT_NODE)
       && XMLString::equals(name, XAIFStrings.elem_Scope_x()) ) {
    return FILTER_ACCEPT;
  }
  return FILTER_SKIP;
}

//****************************************************************************

short
XAIF_SymbolElemFilter::acceptNode(const DOMNode *node) const
{
  const XMLCh* name = node->getNodeName();
  if ( (node->getNodeType() == DOMNode::ELEMENT_NODE)
       && XMLString::equals(name, XAIFStrings.elem_Symbol_x()) ) {
    return FILTER_ACCEPT;
  }
  return FILTER_SKIP;
}

//****************************************************************************

short
XAIF_CFGElemFilter::acceptNode(const DOMNode *node) const
{
  if ( (node->getNodeType() == DOMNode::ELEMENT_NODE)
       && XMLString::equals(node->getNodeName(), XAIFStrings.elem_CFG_x()) ) {
    return FILTER_ACCEPT;
  }
  return FILTER_SKIP;
}

//****************************************************************************

short
XAIF_BBElemFilter::acceptNode(const DOMNode *node) const
{
  if ( (node->getNodeType() == DOMNode::ELEMENT_NODE) && IsBB(node) ) {
    return FILTER_ACCEPT;
  }
  return FILTER_SKIP;
}


bool 
XAIF_BBElemFilter::IsBB(const DOMNode *node)
{
  const XMLCh* name = node->getNodeName();
  return (XMLString::equals(name, XAIFStrings.elem_BB_x())
	  || XMLString::equals(name, XAIFStrings.elem_BBEntry_x()) 
	  || XMLString::equals(name, XAIFStrings.elem_BBExit_x()) 
	  || XMLString::equals(name, XAIFStrings.elem_BBIf_x()) 
	  || XMLString::equals(name, XAIFStrings.elem_BBForLoop_x()) 
	  || XMLString::equals(name, XAIFStrings.elem_BBPreLoop_x())
	  || XMLString::equals(name, XAIFStrings.elem_BBPostLoop_x()));
}

//****************************************************************************

short
XAIF_BBStmtElemFilter::acceptNode(const DOMNode *node) const
{
  if ( (node->getNodeType() == DOMNode::ELEMENT_NODE) && IsStmt(node) ) {
    return FILTER_ACCEPT;
  }
  return FILTER_SKIP;
}


bool 
XAIF_BBStmtElemFilter::IsStmt(const DOMNode *node)
{
  const XMLCh* name = node->getNodeName();
  return (XMLString::equals(name, XAIFStrings.elem_Assign_x())
	  || XMLString::equals(name, XAIFStrings.elem_SubCall_x())
	  || XMLString::equals(name, XAIFStrings.elem_Marker_x())
	  || XMLString::equals(name, XAIFStrings.elem_DerivProp_x()));
}


bool 
XAIF_BBStmtElemFilter::IsMarker(const DOMNode *node)
{
  const XMLCh* name = node->getNodeName();
  return (XMLString::equals(name, XAIFStrings.elem_Marker_x()));
}

bool 
XAIF_BBStmtElemFilter::IsDerivProp(const DOMNode *node)
{
  const XMLCh* name = node->getNodeName();
  return (XMLString::equals(name, XAIFStrings.elem_DerivProp_x()));
}

//****************************************************************************

short
XAIF_DerivPropStmt::acceptNode(const DOMNode *node) const
{
  if ( (node->getNodeType() == DOMNode::ELEMENT_NODE) 
       && (IsSetDeriv(node) || IsSax(node) || IsSaxpy(node)) ) {
    return FILTER_ACCEPT;
  }
  return FILTER_SKIP;
}

bool 
XAIF_DerivPropStmt::IsSetDeriv(const DOMNode *node)
{
  const XMLCh* name = node->getNodeName();
  return (XMLString::equals(name, XAIFStrings.elem_SetDeriv_x()));
}

bool 
XAIF_DerivPropStmt::IsSax(const DOMNode *node)
{
  const XMLCh* name = node->getNodeName();
  return (XMLString::equals(name, XAIFStrings.elem_Sax_x()));
}

bool 
XAIF_DerivPropStmt::IsSaxpy(const DOMNode *node)
{
  const XMLCh* name = node->getNodeName();
  return (XMLString::equals(name, XAIFStrings.elem_Saxpy_x()));
}

//****************************************************************************
