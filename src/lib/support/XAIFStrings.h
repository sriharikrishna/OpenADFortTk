// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/XAIFStrings.h,v 1.1 2003/08/01 15:59:36 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/XAIFStrings.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef XAIFStrings_INCLUDED_h
#define XAIFStrings_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>

//************************* Xerces Include Files ****************************

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLString.hpp>

//*************************** User Include Files ****************************

//*************************** Forward Declarations ***************************

//****************************************************************************

XERCES_CPP_NAMESPACE_USE

// A class containing strings for XAIF.  
//
// FIXME: Can be instantiated even if Xerces has not been initialized.
class XAIFStringRepository
{
public: 
  enum {
    // Common attributes
    ATTR_annot = 0, // annotation
    ATTR_Vid,       // vertex_id
    ATTR_Eid,       // edge_id
    ATTR_scopeId,   // scope_id
    ATTR_symId,     // symbol_id
    
    // xaif:ControlFlowGraph
    ELEM_CFG,
    ATTR_CFGsubName, // subroutine_name
    
    // xaif:BasicBlock
    ELEM_BB,
    ELEM_BBEntry,
    ELEM_BBExit,
    ELEM_BBIf,
    ELEM_BBForLoop,
    ELEM_BBPreLoop,
    ELEM_BBPostLoop,
    
    // Special tags
    TAG_IRIds,     // Tags a colon-separated list of IR ids
    
    NUM_STRINGS // Not a valid string!
  };

public:
  XAIFStringRepository();
  ~XAIFStringRepository();
  
  // -------------------------------------------------------
  // Must be called after Xerces is initialized.  All XML strings are
  // unavailable until this has been called.
  // -------------------------------------------------------
  void XMLInitialize();

  // -------------------------------------------------------
  // General access to strings
  // -------------------------------------------------------
  
  const char* c(int i) const
  {
    if (0 <= i && i < NUM_STRINGS) { return c_strTbl[i]; }
    else { return NULL; }
  }

  XMLCh* xml(int i) const
  {
    if (0 <= i && i < NUM_STRINGS) { return x_strTbl[i]; }
    else { return NULL; }
  }

  // -------------------------------------------------------
  // Quick access to strings
  // -------------------------------------------------------
  
  // FIXME: add c string version
  // Common attributes
  const char* attr_annot() const   { return c_strTbl[ATTR_annot]; }
  XMLCh*      attr_annot_x() const { return x_strTbl[ATTR_annot]; }
  XMLCh*      attr_Vid_x() const { return x_strTbl[ATTR_Vid]; }
  XMLCh*      attr_Eid_x() const { return x_strTbl[ATTR_Eid]; }
  XMLCh*      attr_scopeId_x() const { return x_strTbl[ATTR_scopeId]; }
  XMLCh*      attr_symId_x() const { return x_strTbl[ATTR_symId]; }
  
  // xaif:ControlFlowGraph
  XMLCh*      elem_CFG_x() const { return x_strTbl[ELEM_CFG]; }
  XMLCh*      attr_CFGsubName_x() const { return x_strTbl[ATTR_CFGsubName]; }
  
  // xaif:BasicBlock
  XMLCh*      elem_BB_x() const { return x_strTbl[ELEM_BB]; }
  XMLCh*      elem_BBEntry_x() const { return x_strTbl[ELEM_BBEntry]; }
  XMLCh*      elem_BBExit_x() const { return x_strTbl[ELEM_BBExit]; }
  XMLCh*      elem_BBIf_x() const { return x_strTbl[ELEM_BBIf]; }
  XMLCh*      elem_BBForLoop_x() const { return x_strTbl[ELEM_BBForLoop]; }
  XMLCh*      elem_BBPreLoop_x() const { return x_strTbl[ELEM_BBPreLoop]; }
  XMLCh*      elem_BBPostLoop_x() const { return x_strTbl[ELEM_BBPostLoop]; }

  // Special tags
  const char* tag_IRIds() const   { return c_strTbl[TAG_IRIds]; }
  XMLCh*      tag_IRIds_x() const { return x_strTbl[TAG_IRIds]; }

private:
  static const char* c_strTbl[];
  XMLCh** x_strTbl;
};

// A global instance providing everyone access to the above info
extern XAIFStringRepository XAIFStrings;

//***************************************************************************

#endif // XAIFStrings_INCLUDED_h