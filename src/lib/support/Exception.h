// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Exception.h,v 1.3 2005/06/13 14:30:17 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Exception.h,v $
//
// Purpose:
//    [The purpose of this file]
//
// Description:
//    [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef FortTk_Exception_H 
#define FortTk_Exception_H

//************************* System Include Files ****************************

#include <iostream>
#include <sstream>
#include <string>

//*************************** User Include Files ****************************

//*************************** Forward Declarations ***************************

//****************************************************************************

// Note: Use the inteface in "Diagnostics.h"

//****************************************************************************
// Exception
//****************************************************************************

namespace FortTk {

  class BaseException {
  public:
    BaseException() { }
    virtual ~BaseException() { }
    
    virtual const std::string& GetMessage() const = 0;
    virtual void Report(std::ostream& os) const = 0;
    virtual void Report() const = 0;
  };

  // A generic FortTk exception with file/line information
  class Exception : public BaseException {
  public:
    Exception(const char* m,
	      const char* filenm = NULL, unsigned int lineno = 0);
    Exception(std::string m,
	      const char* filenm = NULL, unsigned int lineno = 0);
    virtual ~Exception();
    
    virtual const std::string& GetMessage() const { return msg; }
    virtual void Report(std::ostream& os) const { 
      os << "OpenADFortTk::Exception: " << msg << std::endl;
    }
    virtual void Report() const { Report(std::cerr); }

  private:
    void Ctor(std::string& m, 
	      const char* filenm = NULL, unsigned int lineno = 0);
    
    std::string msg;
  };

  // A fatal FortTk exception that generally should be unrecoverable
  class FatalException : public Exception {
  public:
    FatalException(const char* m,
		   const char* filenm = NULL, unsigned int lineno = 0);
    FatalException(std::string m,
		   const char* filenm = NULL, unsigned int lineno = 0);
    virtual ~FatalException();
    
    virtual void Report(std::ostream& os) const { 
      os << "OpenADFortTk::FatalException: " << GetMessage() << std::endl;
    }
    virtual void Report() const { Report(std::cerr); }

  };
  
} /* namespace FortTk */

//****************************************************************************

#endif // FortTk_Exception_H
