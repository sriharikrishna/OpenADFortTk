// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Exception.h,v 1.1 2004/02/27 00:33:37 eraxxon Exp $

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

#ifndef OpenAD_WHIRL_Exception_H 
#define OpenAD_WHIRL_Exception_H

//************************* System Include Files ****************************

#include <iostream>
#include <string>

//*************************** User Include Files ****************************

//*************************** Forward Declarations ***************************

//****************************************************************************

//****************************************************************************
// Exception
//****************************************************************************

namespace OpenAD_WHIRL {

  class BaseException {
  public:
    BaseException() { }
    virtual ~BaseException() { }
    
    virtual const std::string& GetMessage() const = 0;
    virtual void Report(std::ostream& os) const = 0;
    virtual void Report() const = 0;
  };

  class Exception : public BaseException {
  public:
    Exception(const char* m) : msg(m) { }
    Exception(std::string m) : msg(m) { }
    virtual ~Exception();
    
    virtual const std::string& GetMessage() const { return msg; }
    virtual void Report(std::ostream& os) const { 
      os << "OpenAD_WHIRL::Exception: " << msg << std::endl;
    }
    virtual void Report() const { Report(std::cerr); }
    
  private:
    std::string msg;
  };

} /* namespace OpenAD_WHIRL */

//****************************************************************************

#endif

