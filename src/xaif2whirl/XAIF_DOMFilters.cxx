// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMFilters.cxx,v 1.4 2003/08/25 13:58:02 eraxxon Exp $

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

void 
XercesDumpNode(DOMNode* n, int iter);

void 
XercesDumpNode(DOMNode* n)
{
  XercesDumpNode(n, 0);
}

void 
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


DOMElement*
GetFirstChildElement(DOMNode* n)
{
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
	  || XMLString::equals(name, XAIFStrings.elem_Nop_x())
	  || XMLString::equals(name, XAIFStrings.elem_DerivAccum_x()));
}


bool 
XAIF_BBStmtElemFilter::IsNop(const DOMNode *node)
{
  const XMLCh* name = node->getNodeName();
  return (XMLString::equals(name, XAIFStrings.elem_Nop_x()));
}

bool 
XAIF_BBStmtElemFilter::IsDerivAccum(const DOMNode *node)
{
  const XMLCh* name = node->getNodeName();
  return (XMLString::equals(name, XAIFStrings.elem_DerivAccum_x()));
}

//****************************************************************************

short
XAIF_Derivative::acceptNode(const DOMNode *node) const
{
  if ( (node->getNodeType() == DOMNode::ELEMENT_NODE) && IsDeriv(node) ) {
    return FILTER_ACCEPT;
  }
  return FILTER_SKIP;
}

bool 
XAIF_Derivative::IsDeriv(const DOMNode *node)
{
  const XMLCh* name = node->getNodeName();
  return (XMLString::equals(name, XAIFStrings.elem_Deriv_x()));
}

//****************************************************************************
