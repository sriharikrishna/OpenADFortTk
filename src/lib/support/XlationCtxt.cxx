// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/XlationCtxt.cxx,v 1.1 2003/09/17 19:45:05 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/XlationCtxt.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

#include <stdio.h>

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

#include "XlationCtxt.h"

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// CtxtFlags
//***************************************************************************

CtxtFlags::CtxtFlags()
  : flags(0)
{
}

CtxtFlags::~CtxtFlags()
{
}

void 
CtxtFlags::Dump(std::ostream& o) const
{
  o << "{context}";
}

void 
CtxtFlags::DDump() const
{
  Dump(std::cerr);
}

