// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/xaif2whirl.h,v 1.2 2003/09/02 15:02:21 eraxxon Exp $

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

//*************************** Forward Declarations ***************************

XERCES_CPP_NAMESPACE_USE

//****************************************************************************

namespace xaif2whirl {

void
TranslateIR(PU_Info* pu_forest, DOMDocument* doc);
 
}; /* namespace xaif2whirl */

//****************************************************************************
// FIXME: move to another file

UINT 
GetIntrinsicOperandNum(const char* name);

OPERATOR 
GetIntrinsicOperator(const char* name);


#include <lib/support/WhirlIDMaps.h>

SymTabId
GetSymTabId(DOMElement* elem);

SymId
GetSymId(DOMElement* elem);

PUId
GetPUId(DOMElement* elem);

WNId
GetWNId(DOMElement* elem);

IdList<WNId>*
GetWNIdList(DOMElement* elem);


// GetId, GetIdList: Returns an id or list of ids from the given tag
// within the annotation attribute.  For the non-list version, 0 is
// returned if no id is found. For the list version, the returned list
// may be empty; the caller is responsible for freeing returned
// memory.
template <class T>
T
GetId(DOMElement* elem, const char* tag);

template <class T>
IdList<T>*
GetIdList(DOMElement* elem, const char* tag);


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

//***************************************************************************

#endif // xaif2whirl_INCLUDED_h
