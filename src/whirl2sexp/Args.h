// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/Args.h,v 1.1 2004/08/05 18:38:14 eraxxon Exp $
// * BeginRiceCopyright *****************************************************
// ******************************************************* EndRiceCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/Args.h,v $
//
// Purpose:
//    [The purpose of this file]
//
// Description:
//    [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef Args_h
#define Args_h

//************************* System Include Files ****************************

#include <iostream>
#include <string>

//*************************** User Include Files ****************************

#include <CmdLineParser.h>

//*************************** Forward Declarations ***************************

//***************************************************************************

class Args {
public: 
  Args() ; 
  Args(int argc, const char* const argv[]);
  ~Args(); 
  
  // Parse the command line
  void Parse(int argc, const char* const argv[]);
  
  // Version and Usage information
  void PrintVersion(std::ostream& os) const;
  void PrintUsage(std::ostream& os) const;
  
  // Error
  void PrintError(std::ostream& os, const char* msg) const;
  void PrintError(std::ostream& os, const std::string& msg) const;

  // Dump
  void Dump(std::ostream& os = std::cerr) const;
  void DDump() const;

  // Parsed Data: Command
  const std::string& GetCmd() const { return parser.GetCmd(); }

  // Parsed Data: optional arguments
  std::string sexpFileNm;
  int debug;   // default: 0 (off)
  
  // Parsed Data: arguments
  std::string whirlFileNm;

  bool myNoCleanUpFlag;
  
private:
  static CmdLineParser::OptArgDesc optArgs[];
  CmdLineParser parser;
}; 

#endif
