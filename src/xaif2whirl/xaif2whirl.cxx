// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.cxx,v 1.2 2003/08/05 20:03:54 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <stdlib.h> // ANSI: cstdlib // for strtol
#include <string.h> // ANSI: cstring // for strcmp, etc.

#include <iostream>

//************************* Xerces Include Files ****************************

#include <xercesc/dom/DOMNodeIterator.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMElement.hpp>

//*************************** User Include Files ****************************

#include "xaif2whirl.h"
#include "XAIF_DOMFilters.h"
#include "XercesStrX.h"

#include <lib/support/Pro64IRInterface.h>
#include <lib/support/WhirlIDMaps.h>
#include <lib/support/XAIFStrings.h>
#include <lib/support/diagnostics.h>

//*************************** Forward Declarations ***************************

using std::cerr;
using std::endl;

static void
TranslatePU(PU_Info* pu_forest, DOMElement* cfgElem);

static void
TranslateWNPU(WN *wn_pu, DOMElement* cfgElem);

static PU_Info*
FindPUForCFG(PU_Info* pu_forest, const char* name, 
	     const char* scopeIdStr, const char* symIdStr);

static WNIdSet*
GetWNIdSet(const char* idstr);


//****************************************************************************

void
xaif2whirl::TranslateIR(PU_Info* pu_forest, DOMDocument* doc)
{
  Diag_Set_Phase("WHIRL to XAIF: translate IR");

  if (!pu_forest) { return; }

#if 0
  DOMNodeIterator* it = 
    doc->createNodeIterator(doc, DOMNodeFilter::SHOW_ELEMENT, NULL, true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    cout << XercesStrX(node->getNodeName()) << endl;
  }
  it->release();
#endif

  DOMNodeIterator* it = 
    doc->createNodeIterator(doc, DOMNodeFilter::SHOW_ALL, 
			    new XAIF_CFGElemFilter(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* elem = dynamic_cast<DOMElement*>(node);

    TranslatePU(pu_forest, elem);
  }
  it->release();
}


static void
TranslatePU(PU_Info* pu_forest, DOMElement* cfgElem)
{
  const XMLCh* name = cfgElem->getAttribute(XAIFStrings.attr_CFGsubName_x());
  const XMLCh* scopeId = cfgElem->getAttribute(XAIFStrings.attr_scopeId_x());
  const XMLCh* symId = cfgElem->getAttribute(XAIFStrings.attr_symId_x());
  
  XercesStrX nameStr = XercesStrX(name);
  XercesStrX scopeIdStr = XercesStrX(scopeId);
  XercesStrX symIdStr = XercesStrX(symId);

  cout << XercesStrX(cfgElem->getNodeName()) << ": " << nameStr 
       << " // " << scopeIdStr << ", " << symIdStr << endl;

  // -------------------------------------------------------
  // Try to find the matching PU; if so, translate XAIF->WHIRL.
  // -------------------------------------------------------
  PU_Info* pu = FindPUForCFG(pu_forest, nameStr.c_str(), scopeIdStr.c_str(),
			     symIdStr.c_str());
  if (!pu) { return; }


  // If we found the PU, translate
  RestoreOpen64PUGlobalVars(pu);

  WN *wn_pu = PU_Info_tree_ptr(pu);
  TranslateWNPU(wn_pu, cfgElem);

  SaveOpen64PUGlobalVars(pu);
}

static void
TranslateWNPU(WN *wn_pu, DOMElement* cfgElem)
{
  pair<WNIdToWNMap*, WNToWNIdMap*> wnmaps = CreateWhirlIDMaps(wn_pu);
  WNIdToWNMap* id2wnmap = wnmaps.first;

  // -------------------------------------------------------
  // Examine each basic block in the CFG
  // -------------------------------------------------------
  DOMDocument* doc = cfgElem->getOwnerDocument();
  DOMNodeIterator* it = 
    doc->createNodeIterator(cfgElem, DOMNodeFilter::SHOW_ALL, 
			    new XAIF_BBElemFilter(), true);
  for (DOMNode* node = it->nextNode(); (node); node = it->nextNode()) {
    DOMElement* elem = dynamic_cast<DOMElement*>(node);
    
    const XMLCh* annot = elem->getAttribute(XAIFStrings.attr_annot_x());
    XercesStrX annotStr = XercesStrX(annot);

    WNIdSet* idset = GetWNIdSet(annotStr.c_str());
    
    WNIdSet::iterator it;
    for (it = idset->begin(); it != idset->end(); ++it) {
      WNId curId = *it;
      WN* curWN = id2wnmap->Find(curId);
      
      IR_set_dump_order(TRUE); /* dump parent before children*/
      fprintf(stderr, "\n-----[%lu]-----\n", curId);
      fdump_tree(stderr, curWN);
    }

    delete idset;
  }
  it->release();


  delete wnmaps.first;
  delete wnmaps.second;
}

//****************************************************************************

// FindPUForCFG: Find the PU in 'pu_forest' that matches the name and
// scope/symbol ids.  If name is non-empty, the scopeId and symId
// should be non-empty.
// FIXME: this is just a linear search
static PU_Info*
FindPUForCFG(PU_Info* pu_forest, const char* name, 
	     const char* scopeIdStr, const char* symIdStr)
{
  unsigned long symId = strtol(symIdStr, (char **)NULL, 10);
  
  if (!name || name[0] == '\0'
      || !scopeIdStr || scopeIdStr[0] == '\0'
      || !symIdStr || symIdStr == '\0') {
    return NULL;
  }
  
  Pro64IRProcIterator procIt(pu_forest);
  for ( ; procIt.IsValid(); ++procIt) { 
    PU_Info* pu = (PU_Info*)procIt.Current();
    ST* st = ST_ptr(PU_Info_proc_sym(pu));
    
    if (symId == ST_index(st) && strcmp(name, ST_name(st)) == 0) {
      return pu;
    }
  }
  
  return NULL;
}

static WNIdSet*
GetWNIdSet(const char* idstr)
{
  WNIdSet* set = new WNIdSet;

  if (!idstr) { return set; }
  
  // Find the tag indicating presence of list
  const char* start = strstr(idstr, XAIFStrings.tag_IRIds());
  if (!start) { return set; }
  start += strlen(XAIFStrings.tag_IRIds()); // move pointer past tag
  
  // Parse the colon separated id list
  char* tok = strtok(const_cast<char*>(start), ":");
  while (tok != NULL) {
    
    WNId id = strtol(tok, (char **)NULL, 10);
    set->insert(id);
    
    tok = strtok((char*)NULL, ":");
  }

  return set;
}
