// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/Args.h,v 1.1 2004/12/15 17:54:53 eraxxon Exp $

#ifndef Args_h
#define Args_h

#include <iostream>
#include <string>

#include "CmdLineParser.h"


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
  std::string whirlFileNm;
  int debug;   // default: 0 (off)
  
  // Parsed Data: arguments
  std::string sexpFileNm;
  
private:
  void Ctor();

private:
  static CmdLineParser::OptArgDesc optArgs[];
  CmdLineParser parser;
}; 

#endif
