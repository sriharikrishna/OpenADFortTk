// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XercesStrX.cxx,v 1.1 2003/12/19 21:06:24 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/XercesStrX.cxx,v $
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

//************************* Xerces Include Files ****************************

//*************************** User Include Files ****************************

#include "XercesStrX.h"

//*************************** Forward Declarations ***************************

//****************************************************************************

void 
XercesStrX::DumpXMLStr(std::ostream& os, const XMLCh* const xmlstr)
{
  XercesStrX toDump(xmlstr);
  os << toDump.c_str();
  os.flush();
}

void
XercesStrX::DDumpXMLStr(const XMLCh* const xmlstr)
{
  DumpXMLStr(std::cout, xmlstr);
}

//***************************************************************************

