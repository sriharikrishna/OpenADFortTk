// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/diagnostics.cxx,v 1.10 2005/03/19 22:54:51 eraxxon Exp $

#include "Diagnostics.h"

namespace fortTkSupport { 

  int Diagnostics::ourUserDebugLevel = 0;
  const char* Diagnostics::Unimplemented = "Unimplemented feature: ";
  const char* Diagnostics::UnexpectedInput = "Unexpected input: ";
  const char* Diagnostics::UnexpectedOpr = "Unexpected operator: ";

  void Diagnostics::setDiagnosticFilterLevel(int lvl) {
    ourUserDebugLevel = lvl;
  }

  int Diagnostics::getDiagnosticFilterLevel() {
    return ourUserDebugLevel;
  }

  void Diagnostics::theMostVisitedBreakpointInHistory(const char* filenm, unsigned int lineno) {
    // Prevent this routine from ever being inlined
    static unsigned count = 0;
    count++;
  }

}
