// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XercesStrX.h,v 1.3 2003/12/19 21:06:52 eraxxon Exp $

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
  // Note: toTranscode can be NULL.
  XercesStrX(const XMLCh* const toTranscode)
  {
    local = XMLString::transcode(toTranscode);
  }
  
  ~XercesStrX() { XMLString::release(&local); }

  const char* c_str() const { return local; }

  // For debugging
  static void DumpXMLStr(std::ostream& os, const XMLCh* const xmlstr);
  static void DDumpXMLStr(const XMLCh* const xmlstr);

private :
  char* local;
};


inline std::ostream& 
operator<<(std::ostream& os, const XMLCh* const toDump)
{
  XercesStrX::DumpXMLStr(os, toDump);
  return os;
}

inline std::ostream& 
operator<<(std::ostream& os, const XercesStrX& toDump)
{
  os << toDump.c_str();
  return os;
}

//***************************************************************************

#endif // XercesStrX_INCLUDED_h
