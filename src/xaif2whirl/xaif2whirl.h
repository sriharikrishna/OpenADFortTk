// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.h,v 1.20 2005/03/19 22:54:51 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef xaif2whirl_INCLUDED_h
#define xaif2whirl_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>
#include <vector>

//************************* Xerces Include Files ****************************

#include <xercesc/dom/DOMDocument.hpp>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//************************ OpenAnalysis Include Files ***********************

#include <OpenAnalysis/CFG/CFGStandard.hpp> // for DGraphStandard, CFG::Edge

//*************************** User Include Files ****************************

#include "XlationContext.h"

#include <lib/support/WhirlIDMaps.h>
#include <lib/support/IntrinsicXlationTable.h>

//*************************** Forward Declarations ***************************

XERCES_CPP_NAMESPACE_USE

//****************************************************************************

namespace xaif2whirl {

  enum ModeType {
    MODE_NULL,
    MODE_FORWARD,  // forward mode
    MODE_REVERSE,  // reverse mode
  };

  enum AlgorithmType {
    ALG_NULL,
    ALG_STRUCTURED_CF,   // special case
    ALG_UNSTRUCTURED_CF, // most general
    ALG_BB_PATCHING      // temporary
  };
  
  extern IntrinsicXlationTable IntrinsicTable;

  void
  TranslateIR(PU_Info* pu_forest, const DOMDocument* doc);
  
  // FIXME: relocate...
  Symbol*
  GetSymbol(const DOMElement* elem, XlationContext& ctxt);

  const TYPE_ID DefaultMTypeInt = MTYPE_I8;
  const TYPE_ID DefaultMTypeUInt = MTYPE_U8;

}; /* namespace xaif2whirl */

Symbol*
GetOrCreateSymbol(const char* sname, XlationContext& ctxt);

Symbol*
GetOrCreateBogusTmpSymbol(XlationContext& ctxt);

//****************************************************************************

namespace xaif2whirl {
  // -------------------------------------------------------
  // Generic attribute retrieval funtions
  // -------------------------------------------------------

  bool
  GetBoolAttr(const DOMElement* elem, XMLCh* attr, bool default_val);

  int
  GetIntAttr(const DOMElement* elem, XMLCh* attr, int default_val);

  // Return the value of the respective attribute.  The default values
  // are given below if the attribute is not present.

  // Default: false.
  bool
  GetHasConditionAttr(const DOMElement* elem);

  // Default: 0.
  unsigned int
  GetCondAttr(const DOMElement* elem);
  
  // Default: true.
  bool
  GetActiveAttr(const DOMElement* elem);
  
  // Default: false.
  bool
  GetDerivAttr(const DOMElement* elem);
  
  // Default: 0. A valid position value is non-zero.
  unsigned int
  GetPositionAttr(const DOMElement* elem);


  // -------------------------------------------------------
  // Get information within XAIF 'annotation' attribute
  // -------------------------------------------------------

  // Given an element or annotation string and a tag, returns whether
  // the tag is present in teh annotation attribute.
  bool
  IsTagPresent(const DOMElement* elem, const char* tag);
  
  bool
  IsTagPresent(const char* annotstr, const char* tag);

  // Get the appropriate persistant id from the element 'elem'.  See
  // detailed descriptions for generic functions below.
  SymTabId
  GetSymTabId(const DOMElement* elem);
  
  SymId
  GetSymId(const DOMElement* elem);
  
  PUId
  GetPUId(const DOMElement* elem);
  
  WNId
  GetWNId(const DOMElement* elem);
  
  IdList<WNId>*
  GetWNIdList(const DOMElement* elem);

  // Get the value of the tag IntrinsicKey
  std::string
  GetIntrinsicKey(const DOMElement* elem);

  // Get the value of the tag PregId
  PREG_IDX
  GetPregId(const DOMElement* elem);
  
  // GetId, GetIdList: Returns an id or list of ids from the given tag
  // within the annotation attribute.  For the non-list version, 0 is
  // returned if no id is found. For the list version, the returned list
  // may be empty; the caller is responsible for freeing returned
  // memory.
  template <class T>
  T
  GetId(const DOMElement* elem, const char* tag);
  
  template <class T>
  IdList<T>*
  GetIdList(const DOMElement* elem, const char* tag);
  
  
  // GetId, GetIdList: Returns an id or the list of ids from the given
  // tag within the string 'idstr'.  For the non-list version, 0 is
  // returned if no id is found.  For the list version, the returned
  // list may be empty; the caller is responsible for freeing returned
  // memory.
  template <class T>
  T
  GetId(const char* idstr, const char* tag);
  
  template <class T>
  IdList<T>*
  GetIdList(const char* idstr, const char* tag);
  
}; /* namespace xaif2whirl */

//***************************************************************************

// FIXME: move to another file

WN*
CreateCallToIntrin(TYPE_ID rtype, const char* fname, unsigned int argc);

WN*
CreateCallToIntrin(TYPE_ID rtype, const char* fname, std::vector<WN*>& args);

WN*
CreateIntrinsicCall(OPERATOR opr, INTRINSIC intrn, 
		    TYPE_ID rtype, TYPE_ID dtype, std::vector<WN*>& args);

inline WN*
CreateParm(WN *arg, UINT32 flag)
{
  TYPE_ID rtype = WN_rtype(arg);
  return WN_CreateParm(rtype, arg, MTYPE_To_TY(rtype), flag);
}

WN* 
CreateBoolConst(unsigned int val);

//***************************************************************************

class MyDGNode;

typedef std::map<std::string, OA::OA_ptr<MyDGNode> > VertexIdToMyDGNodeMap;

// ---------------------------------------------------------
// MyDGNode, MyDGEdge: Used to create graph structures from XAIF
// graphs (lists of nodes and edges)
// ---------------------------------------------------------
class MyDGNode : public OA::DGraph::DGraphStandard::Node {
public:
  MyDGNode(const DOMElement* e_) : e(e_) { Ctor(); }
  virtual ~MyDGNode() { }
  
  DOMElement* GetElem() const { return const_cast<DOMElement*>(e); }
  
  // getId: An id unique within instances of this class
  virtual unsigned int getId() const { return id; }
  // resetIds: reset id numbering
  static void resetIds() { nextId = 1; }
  
private:
  void Ctor() { id = nextId++; }
  static unsigned int nextId;
  
  const DOMElement* e;
  unsigned int id; // 0 is reserved; first instance is 1
};

class MyDGEdge : public OA::DGraph::DGraphStandard::Edge {
public:
  MyDGEdge(OA::OA_ptr<OA::DGraph::DGraphStandard::Node> source_, 
          OA::OA_ptr<OA::DGraph::DGraphStandard::Node> sink_, 
          const DOMElement* e_) 
    : OA::DGraph::DGraphStandard::Edge(source_, sink_), e(e_) { }
  virtual ~MyDGEdge() { }
  
  DOMElement* GetElem() const { return const_cast<DOMElement*>(e); }
  
private:
  const DOMElement* e;
};


// GetSuccessor: Assuming node has 0 or 1 outgoing edges, return the
// successor node.  In most graphs the successor will be along the
// outgoing edge, and this parameter defaults to true.
extern OA::OA_ptr<MyDGNode>
GetSuccessor(OA::OA_ptr<MyDGNode> node, bool succIsOutEdge = true);

extern OA::OA_ptr<MyDGNode>
GetSuccessorAlongEdge(OA::OA_ptr<MyDGNode> node, unsigned int condition, 
		      bool succIsOutEdge = true);

//***************************************************************************

#endif // xaif2whirl_INCLUDED_h
