// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XAIF_DOMFilters.cxx,v 1.1 2003/08/01 16:41:13 eraxxon Exp $

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
#include <xercesc/util/XMLString.hpp>

//*************************** User Include Files ****************************

#include "XAIF_DOMFilters.h"

#include <lib/support/XAIFStrings.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

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
