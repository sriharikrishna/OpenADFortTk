// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Args.cxx,v 1.10 2005/11/01 23:28:48 utke Exp $
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

//************************** Open64 Include Files ***************************

#include "Open64IRInterface/Open64BasicTypes.h"
#include "file_util.h"      // New_Extension, Last_Pathname_Component

//*************************** User Include Files ****************************

#include "Args.h"

//*************************** Forward Declarations **************************

using std::cerr;
using std::endl;
using std::string;

//***************************************************************************

TYPE_ID Args::ourDefaultMTypeInt  = MTYPE_I8;
TYPE_ID Args::ourDefaultMTypeUInt = MTYPE_U8;
TYPE_ID Args::ourDefaultMTypeReal = MTYPE_F8;

static const char* version_info = "version .289";

static const char* usage_summary =
"[options] <whirl-file> <xaif-file>\n";

static const char* usage_details =
"Given a WHIRL file and a *corresponding* XAIF file, generates new WHIRL.\n"
"By default, the output is sent to the filename formed by replacing the\n"
"extension of <xaif-file> with 'x2w.B'.\n"
"\n"
"Algorithms:\n"
"  -m, --mode=<mode> forward, reverse.  By default, assumes reverse.\n"
"  --structured-cf   Generate structured control-flow\n"
"  --unstructured-cf Generate unstructured control-flow [Default]\n"
"  --bb-patching     TEMPORARY: use basic-block patch algorithm\n"
"\n"
"Options:\n"
"  -o, --output <file> send output to <file> instead of default file\n"
"      --i4            make integers 4 byte where not specified (default 8 bytes)\n"
"      --u4            make unsigned integers 4 byte where not specified (default 8 bytes)\n"
"      --r4            make reals 4 byte where not specified (default 8 bytes)\n"
"  -V, --version       print version information\n"
"  -v, --validate      validate agains schema\n"
"  -h, --help          print this help\n"
"      --debug [lvl]   debug mode at level `lvl'\n";


#define CLP CmdLineParser

CmdLineParser::OptArgDesc Args::optArgs[] = {
  // Options
  { 'm', "mode",     CLP::ARG_REQ, CLP::DUPOPT_CLOB, NULL },
  {  0 , "structured-cf",   CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  {  0 , "unstructured-cf", CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  {  0 , "bb-patching",     CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  {  0 , "i4",              CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  {  0 , "u4",              CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  {  0 , "r4",              CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  {  0 , "types",    CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  { 'o', "output",   CLP::ARG_REQ , CLP::DUPOPT_ERR,  NULL },
  { 'V', "version",  CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
  { 'v', "validate", CLP::ARG_NONE, CLP::DUPOPT_CLOB, NULL },
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
  mode      = xaif2whirl::MODE_REVERSE;
  algorithm = xaif2whirl::ALG_UNSTRUCTURED_CF;
  validate  = false; 
  debug     = 0; // default: 0 (off)
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
    if (parser.IsOpt("validate")) { 
      validate=true;
    }
    if (parser.IsOpt("version")) { 
      PrintVersion(std::cerr);
      exit(1);
    }
    
    // Check for algorithm options
    if (parser.IsOpt("mode")) { 
      const string& arg = parser.GetOptArg("mode");
      if (arg == "forward") {
	mode = xaif2whirl::MODE_FORWARD;
      }
      else if (arg == "reverse") {
	mode = xaif2whirl::MODE_REVERSE;
      } else {
	PrintError(std::cerr, "Invalid argument to 'mode': " + arg);
	exit(1);
      }
    }
    if (parser.IsOpt("structured-cf")) { 
      algorithm = xaif2whirl::ALG_STRUCTURED_CF;
    }
    if (parser.IsOpt("unstructured-cf")) { 
      algorithm = xaif2whirl::ALG_UNSTRUCTURED_CF;
    }
    if (parser.IsOpt("bb-patching")) { 
      algorithm = xaif2whirl::ALG_BB_PATCHING;
    }

    // Check for other options    
    if (parser.IsOpt("output")) { 
      outWhirlFileNm = parser.GetOptArg("output");
    }

    if (parser.IsOpt("i4")) { 
      ourDefaultMTypeInt=MTYPE_I4;
    }
    
    if (parser.IsOpt("u4")) { 
      ourDefaultMTypeUInt=MTYPE_U4;
    }
 
    if (parser.IsOpt("r4")) { 
      ourDefaultMTypeReal=MTYPE_F4;
    }
    
    // Check for required arguments
    if (parser.GetNumArgs() != 2) {
      PrintError(std::cerr, "Invalid number of arguments!");
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

