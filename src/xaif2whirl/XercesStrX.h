// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XercesStrX.h,v 1.1 2003/08/01 16:41:13 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XercesStrX.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef XercesStrX_INCLUDED_h
#define XercesStrX_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>

//************************* Xerces Include Files ****************************

#include <xercesc/util/XercesDefs.hpp>
#include <xercesc/util/XMLString.hpp>

//*************************** User Include Files ****************************

//*************************** Forward Declarations ***************************

//****************************************************************************

XERCES_CPP_NAMESPACE_USE
//XERCES_CPP_NAMESPACE::

// A class for transcoding of XMLCh data to local code page.
// Based on samples/SAX2Print/Sax2Print.hpp within Xerces-C++
class XercesStrX
{
public :
  XercesStrX(const XMLCh* const toTranscode)
  {
    local = XMLString::transcode(toTranscode);
  }
  
  ~XercesStrX() { XMLString::release(&local); }

  const char* c_str() const { return local; }

private :
  char* local;
};

inline std::ostream& 
operator<<(std::ostream& target, const XercesStrX& toDump)
{
  target << toDump.c_str();
  return target;
}

//***************************************************************************

#endif // XercesStrX_INCLUDED_h
