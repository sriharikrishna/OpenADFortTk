// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Args.cxx,v 1.2 2004/02/28 16:41:09 eraxxon Exp $
// * BeginRiceCopyright *****************************************************
// ******************************************************* EndRiceCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Args.cxx,v $
//
// Purpose:
//    [The purpose of this file]
//
// Description:
//    [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

//*************************** User Include Files ****************************

#include <include/Open64BasicTypes.h> // FIXME 
#include "file_util.h"      // New_Extension, Last_Pathname_Component

#include "Args.h"

//*************************** Forward Declarations **************************

using std::cerr;
using std::endl;
using std::string;

//***************************************************************************

static const char* version_info = "version .289";

static const char* usage_summary =
"[options] <whirl-file> <xaif-file>\n";

static const char* usage_details =
"Given a WHIRL file and a *corresponding* XAIF file, generates new WHIRL.\n"
"By default, the output is sent to the filename formed by replacing the\n"
"extension of <xaif-file> with 'x2w.B'.\n"
"\n"
"Options:\n"
"      --types         change 'active' type within WHIRL\n"
"\n"
"  -o, --output <file> send output to <file> instead of default file\n"
"  -V, --version       print version information\n"
"  -h, --help          print this help\n"
"      --debug [lvl]   debug mode at level `lvl'\n";


#define CLP CmdLineParser

CmdLineParser::OptArgDesc Args::optArgs[] = {
  // Options
  {  0 , "types",    CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  { 'o', "output",   CLP::ARG_REQ , CLP::DUPOPT_ERR,  NULL },
  { 'V', "version",  CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  { 'h', "help",     CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  {  0 , "debug",    CLP::ARG_OPT,  CLP::DUPOPT_CLOB, NULL },
  CmdLineParser::OptArgDesc_NULL
};

#undef CLP

//***************************************************************************
// Args
//***************************************************************************

Args::Args()
{
  Ctor();
}

Args::Args(int argc, const char* const argv[])
{
  Ctor();
  Parse(argc, argv);
}

void
Args::Ctor()
{
  changeActiveTyInWHIRL = false;
  debug = 0;      // default: 0 (off)
}

Args::~Args()
{
}


void 
Args::PrintVersion(std::ostream& os) const
{
  os << GetCmd() << ": " << version_info << endl;
}


void 
Args::PrintUsage(std::ostream& os) const
{
  os << "Usage: " << GetCmd() << " " << usage_summary << endl
     << usage_details << endl;
} 


void 
Args::PrintError(std::ostream& os, const char* msg) const
{
  os << GetCmd() << ": " << msg << endl
     << "Try `" << GetCmd() << " --help' for more information." << endl;
}

void 
Args::PrintError(std::ostream& os, const std::string& msg) const
{
  PrintError(os, msg.c_str());
}


void
Args::Parse(int argc, const char* const argv[])
{
  try {
    // -------------------------------------------------------
    // Parse the command line
    // -------------------------------------------------------
    parser.Parse(optArgs, argc, argv);
    
    // -------------------------------------------------------
    // Sift through results, checking for semantic errors
    // -------------------------------------------------------
    
    // Special options that should be checked first
    if (parser.IsOpt("debug")) { 
      debug = 1; 
      if (parser.IsOptArg("debug")) {
	const string& arg = parser.GetOptArg("debug");
	debug = (int)CmdLineParser::ToLong(arg);
      }
    }
    if (parser.IsOpt("help")) { 
      PrintUsage(std::cerr); 
      exit(1);
    }
    if (parser.IsOpt("version")) { 
      PrintVersion(std::cerr);
      exit(1);
    }
    
    // Check for other options
    if (parser.IsOpt("types")) { 
      changeActiveTyInWHIRL = true;
    }
    if (parser.IsOpt("output")) { 
      outWhirlFileNm = parser.GetOptArg("output");
    }
    
    // Check for required arguments
    if (parser.GetNumArgs() != 2) {
      PrintError(std::cerr, "Missing a required argument!");
      exit(1);
    }
    inWhirlFileNm = parser.GetArg(0);
    xaifFileNm = parser.GetArg(1);
  } 
  catch (CmdLineParser::ParseError& e) {
    PrintError(std::cerr, e.GetMessage());
    exit(1);
  }

  // -------------------------------------------------------
  // Postprocess
  // -------------------------------------------------------
  if (outWhirlFileNm.empty()) {
    // FIXME: should we place in current directory?
    outWhirlFileNm = New_Extension(xaifFileNm.c_str(), ".x2w.B");
  }
}


void 
Args::Dump(std::ostream& os) const
{
  parser.Dump(os);
}

void 
Args::DDump() const
{
  Dump(std::cerr);
}
