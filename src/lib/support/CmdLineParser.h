// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/CmdLineParser.h,v 1.1 2004/02/27 00:33:09 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/CmdLineParser.h,v $
//
// Purpose:
//    [The purpose of this file]
//
// Description:
//    [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef IntrinsicXlationTable_H 
#define IntrinsicXlationTable_H

//************************* System Include Files ****************************

#include <iostream>
#include <map>
#include <vector>
#include <string>

//*************************** User Include Files ****************************

#include <inttypes.h> /* commonly available, unlike <stdint.h> */

//*************************** Forward Declarations ***************************

//****************************************************************************

//****************************************************************************
// CmdLineParser
//****************************************************************************

// CmdLineParser: Parses arguments on the command line, argc and argv.
// Provides easy access to both optional arguments (with short or long
// specifiers) and regular arguments.  Provides functionality similar
// to getopt() and GNU's getopt_long(), but in an easier to use -- and
// in the case of getopt_long(), more portable -- package.  In
// addition, routines to convert string arguments into numerical types
// are also provided.
//
// A user creates a NULL-terminated array of option descriptors
// (OptArgDesc) indicating switch names and arguments, if any.  He
// then instantiates a CmdLineParser and parses argc/argv.  Errors are
// delivered with the exception Exception.  The parser object provides
// access to all optional and regular arguments using the interface
// routines belows.
// 
// More details:
// The command line generally has the form (but note qualifications below):
//   <command> [arguments]
//   
//   [arguments] ::= [optional_arg] | [regular_arg]
//   
//   [optional_arg] ::= -f [arg] | -f[arg]
//                    | --foo [arg] | --foo=arg
//
// An element of argv that starts with '-' or '--' (and is not exactly
// '--') signifies an option.  The option switch is the text without
// the initial dashes.  As the above shows, we support a variety of
// option styles.
//
// Features: 
//   - The '--' token forces the end of optional argument scanning and
//     iterprets everything following as a list of regular arguments.
//     This is useful for non-option arguments that begin with dashes.
//   - Unlike getopt() we do not support the deprecated use of the single
//     '-'; this is an error.  
//   - Long argument switches may be abbreviated if the abbreviation 
//     is unique. 
//   - If the same switch is passed multiple times, any arguments to
//     the switch are accumulated in a colon-separated list.
//
// Limitations:
//   - We do not currently enforce that an abbreviation will not match
//     two different switches.)  
//   - Unlike getopt(), we do not currently support short switch grouping,
//     e.g. using -abc instead of -a -b -c.  [FIXME: we can assume that 
//     only options without arguments are allowed to be grouped.]
//   - We do not check the OptArgDesc array for bogus input. [FIXME]
// 
class CmdLineParser {
public:

  // ---------------------------------------------------------
  // Structure used to describe command line options
  // ---------------------------------------------------------
  
  enum OptKind { 
    ARG_NULL, 
    ARG_NONE, // switch does not take argument
    ARG_REQ,  // switch must take an argument
    ARG_OPT   // switch takes an (optional!) argument
  };

  struct OptArgDesc {
    
    bool operator==(const OptArgDesc& x) const { 
      return (swShort == x.swShort && swLong == x.swLong && kind == x.kind);
    }
    bool operator!=(const OptArgDesc& x) const { return !(*this == x); }
    
    // Data
    const char swShort; // 0 if n/a
    const char* swLong; // NULL if n/a
    OptKind kind;
  };

  static OptArgDesc OptArgDesc_NULL; // The NULL terminator

  // ---------------------------------------------------------
  // Exception thrown when errors are encountered
  // ---------------------------------------------------------
  
  class Exception {
  public:
    Exception(const char* m) : msg(m) { }
    Exception(std::string m) : msg(m) { }
    virtual ~Exception () { }

    virtual const std::string& GetMessage() const { return msg; }
    virtual void Report(std::ostream& os) const { 
      os << "CmdLineParser::Exception: " << msg << std::endl; 
    }    
    virtual void Report() const { Report(std::cerr); }

  private: 
    std::string msg;
  };

  // ---------------------------------------------------------

public:
  // ---------------------------------------------------------
  // Constructor/Destructor
  // ---------------------------------------------------------
  CmdLineParser(); 
  CmdLineParser(const OptArgDesc* optArgDescs, 
		int argc, const char* const argv[]); 
  ~CmdLineParser();

  // -------------------------------------------------------
  // Parsing
  // -------------------------------------------------------
  
  // Parse: Given a NULL terminated array of OptArgDesc describing
  // command line arguments, parses the argv/argc into switches,
  // optional and required arguments.
  void
  Parse(const OptArgDesc* optArgDescs, 
	int argc, const char* const argv[]);
  
  // -------------------------------------------------------
  // Parsed Data: Command
  // -------------------------------------------------------

  // GetCmd: The command (will be valid even after a parse error)
  const std::string& GetCmd() const;
  
  // -------------------------------------------------------
  // Parsed Data: Optional arguments
  // -------------------------------------------------------
  
  // IsOpt: Given a short or long switch, returns whether the switch
  // has been seen.
  bool IsOpt(const char swShort) const;
  bool IsOpt(const char* swLong) const;
  bool IsOpt(const std::string& sw) const;

  // IsOptArg: Given a short or long switch, returns whether an
  // argument is associated with it.  Designed for switches that
  // optionally take arguments.
  bool IsOptArg(const char swShort) const;
  bool IsOptArg(const char* swLong) const;
  bool IsOptArg(const std::string& sw) const;  
  
  // GetOptArg: Given a short or long switch, get the argument
  // associated with it.  Assumes user has verified that an argument
  // *exists*.
  const std::string& GetOptArg(const char swShort) const;
  const std::string& GetOptArg(const char* swLong) const;
  const std::string& GetOptArg(const std::string& sw) const;

  // -------------------------------------------------------
  // Parsed Data: Arguments
  // -------------------------------------------------------
  unsigned int GetNumArgs() const;
  const std::string& GetArg(unsigned int i) const;

  // -------------------------------------------------------
  // Convert strings into other formats
  // -------------------------------------------------------
  // The input should be non-empty
  static long     ToLong(const std::string& str);
  static uint64_t ToUInt64(const std::string& str);
  static double   ToDbl(const std::string& str);
  
  // -------------------------------------------------------
  // Misc
  // -------------------------------------------------------
  void Dump(std::ostream& os = std::cerr) const;
  void DDump() const;
  
private:
  // Should not be used 
  CmdLineParser(const CmdLineParser& p) { }
  CmdLineParser& operator=(const CmdLineParser& x) { return *this; }
  
  typedef std::map<std::string, std::string*> SwitchToArgMap;
  typedef std::vector<std::string> ArgVec;

private:
  void Ctor();
  void Reset();

  // Parsing helpers
  void 
  FindSwitchAndArg(const char* swString, std::string& sw, std::string& arg);
  
  const OptArgDesc*
  FindOptDesc(const OptArgDesc* optArgDescs, const char* sw);
  
  void
  AddOptArg(const OptArgDesc& desc, const std::string& arg);
  
  void
  AddOptArg(const std::string& sw, const std::string& arg);

private:
  
  std::string command;           // comand name
  SwitchToArgMap switchToArgMap; // optional arguments
  ArgVec arguments;              // regular arguments
};

//****************************************************************************

#endif

