// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Args.h,v 1.7 2005/11/01 23:28:48 utke Exp $
// * BeginRiceCopyright *****************************************************
// ******************************************************* EndRiceCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Args.h,v $
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

#include <lib/support/CmdLineParser.h>
#include "xaif2whirl.h"

//*************************** Forward Declarations ***************************

//***************************************************************************

class Args {
public: 
  Args(); 
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

public:
  // Parsed Data: Command
  const std::string& GetCmd() const { return parser.GetCmd(); }
  
  // Parsed Data: optional arguments
  xaif2whirl::ModeType      mode;      // default: MODE_REVERSE
  xaif2whirl::AlgorithmType algorithm; // default: ALG_UNSTRUCTURED_CF
  int debug;                           // default: 0 (off)
  
  // Parsed Data: arguments
  std::string inWhirlFileNm;
  std::string outWhirlFileNm;
  std::string xaifFileNm;
  bool validate;
  
private:
  void Ctor();
  
private:
  static CmdLineParser::OptArgDesc optArgs[];
  CmdLineParser parser;
}; 

#endif
