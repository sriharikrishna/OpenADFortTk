// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.h,v 1.4 2003/09/18 19:18:12 eraxxon Exp $

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

//************************* Xerces Include Files ****************************

#include <xercesc/dom/DOMDocument.hpp>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "XlationContext.h"

#include <lib/support/WhirlIDMaps.h>

//*************************** Forward Declarations ***************************

XERCES_CPP_NAMESPACE_USE

//****************************************************************************

namespace xaif2whirl {

void
TranslateIR(PU_Info* pu_forest, const DOMDocument* doc);

ST*
GetST(const DOMElement* elem, XlationContext& ctxt);
 
}; /* namespace xaif2whirl */

//****************************************************************************

namespace xaif2whirl {

// GetPositionAttr: Returns the value of the position attribute, if
// available.  A valid position value is non-zero.
unsigned int
GetPositionAttr(const DOMElement* elem);

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
CreateIntrinsicCall(TYPE_ID rtype, const char* fname, unsigned int argc);

inline WN*
CreateParm(WN *arg, UINT32 flag)
{
  TYPE_ID rtype = WN_rtype(arg);
  return WN_CreateParm(rtype, arg, MTYPE_To_TY(rtype), flag);
}

//***************************************************************************

#endif // xaif2whirl_INCLUDED_h
