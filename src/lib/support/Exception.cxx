// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Exception.cxx,v 1.2 2004/07/30 17:50:06 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Exception.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

//*************************** User Include Files ****************************

#include "Exception.h"
#include "diagnostics.h"

//************************** Forward Declarations ***************************

//***************************************************************************
// Exception
//***************************************************************************

FortTk::Exception::Exception(const char* m,
			     const char* filenm, unsigned int lineno)
{
  std::string str = m;
  Ctor(str, filenm, lineno);
  FortTk_TheMostVisitedBreakpointInHistory(filenm, lineno);
}


FortTk::Exception::Exception(std::string m,
			     const char* filenm, unsigned int lineno)
{
  Ctor(m, filenm, lineno);
  FortTk_TheMostVisitedBreakpointInHistory(filenm, lineno);
}


FortTk::Exception::~Exception()
{
}


void 
FortTk::Exception::Ctor(std::string& m, 
			const char* filenm, unsigned int lineno)
{
  if (filenm && lineno != 0) {
    std::ostringstream os;
    os << "[" << filenm << ":" << lineno << "]: " << m;
    msg = os.str();
  } 
  else {
    msg = m;
  }
}

//***************************************************************************
// FatalException
//***************************************************************************

FortTk::FatalException::FatalException(const char* m,
				       const char* filenm, unsigned int lineno)
  : FortTk::Exception(m, filenm, lineno)
{
}


FortTk::FatalException::FatalException(std::string m,
				       const char* filenm, unsigned int lineno)
  : FortTk::Exception(m, filenm, lineno)
{
}


FortTk::FatalException::~FatalException()
{
}

