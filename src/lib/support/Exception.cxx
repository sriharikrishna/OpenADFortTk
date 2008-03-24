// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Exception.cxx,v 1.2 2004/07/30 17:50:06 eraxxon Exp $

#include "Exception.h"
#include "Diagnostics.h"

namespace fortTkSupport { 

  Exception::Exception(const char* m,
		       const char* filenm, unsigned int lineno) {
    std::string str = m;
    Ctor(str, filenm, lineno);
    Diagnostics::theMostVisitedBreakpointInHistory(filenm, lineno);
  }


  Exception::Exception(std::string m,
		       const char* filenm, unsigned int lineno) {
    Ctor(m, filenm, lineno);
    Diagnostics::theMostVisitedBreakpointInHistory(filenm, lineno);
  }


  Exception::~Exception() {
  }


  void 
  Exception::Ctor(std::string& m, 
		  const char* filenm, unsigned int lineno) {
    if (filenm && lineno != 0) {
      std::ostringstream os;
      os << "[" << filenm << ":" << lineno << "]: " << m.c_str();
      msg = os.str();
    } 
    else {
      msg = m;
    }
  }

  //***************************************************************************
    // FatalException
    //***************************************************************************

    FatalException::FatalException(const char* m,
				   const char* filenm, unsigned int lineno)
      : Exception(m, filenm, lineno) {
    }


  FatalException::FatalException(std::string m,
				 const char* filenm, unsigned int lineno)
    : Exception(m, filenm, lineno) {
  }


  FatalException::~FatalException() {
  }
  
}
