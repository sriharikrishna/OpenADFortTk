// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/CmdLineParser.cxx,v 1.1 2004/02/27 00:35:36 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/CmdLineParser.cxx,v $
//
// Purpose:
//    [The purpose of this file]
//
// Description:
//    [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <stdlib.h> // <cstdlib> // for strtol
#include <string.h> // <cstring>

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

#include "CmdLineParser.h"

//*************************** Forward Declarations ***************************

using std::string;

static string INTERNAL_ERR = "Internal error: Don't abuse me!";
static string MISSING_SWITCH = "Missing switch after -";
static string UNKNOWN_SWITCH = "Unknown option switch: ";
static string INVALID_ARG = "Invalid argument to option switch: ";
static string MISSING_ARG = "Missing argument for switch: ";

//****************************************************************************

// IsDashDash
static inline bool
IsDashDash(const char* str) { return (strcmp(str, "--") == 0); }


// IsSwitch, IsLongSwitch, IsShortSwitch: Assumes str is non-NULL!  Note also
// that the test for short switch is not quite complete and depends on
// testing for a long switch first!
static inline bool
IsLongSwitch(const char* str) { return (strncmp(str, "--", 2) == 0); }

static inline bool
IsShortSwitch(const char* str) { return (*str == '-'); }

static inline bool
IsSwitch(const char* str) { return (IsLongSwitch(str) || IsShortSwitch(str)); }


// IsArg: Verifies that we should interpret 'str' as an argument.
// Should be non-NULL;
static inline bool
IsArg(const char* str) { return (!IsSwitch(str) && !IsDashDash(str)); }


//****************************************************************************

//****************************************************************************
// CmdLineParser
//****************************************************************************

CmdLineParser::OptArgDesc CmdLineParser::OptArgDesc_NULL = 
  { 0, NULL, CmdLineParser::ARG_NULL };


CmdLineParser::CmdLineParser() 
{
  Ctor();
}

CmdLineParser::CmdLineParser(const OptArgDesc* optArgDescs, 
			     int argc, const char* const argv[])
{
  Ctor();
  Parse(optArgDescs, argc, argv);
}

void
CmdLineParser::Ctor() 
{
  // nothing to do
}



CmdLineParser::~CmdLineParser() 
{ 
  Reset();
}


void
CmdLineParser::Parse(const OptArgDesc* optArgDescs, 
		     int argc, const char* const argv[])
{ 
  Reset();
  command = argv[0]; // always do first so it will be available after errors
  
  // CheckForErrors(optArgDescs);
  //   FIXME: add error checking phase:
  //   - detect duplicate option entries
  //   - invalid option entries (no switch)
  
  bool endOfOpts = false;  // are we at end of optional args?
  
  for (unsigned int i = 1; i < argc; ++i) {
    const char* str = argv[i];
    
    // -------------------------------------------------------
    // Bypass special option values
    // -------------------------------------------------------
    if (str == NULL || *str == '\0') {
      continue; // should never happen, but we ignore
    }
    
    // A '--' signifies end of optional arguments
    if (IsDashDash(str)) {
      endOfOpts = true;
      continue;
    }
    
    if (!endOfOpts && IsSwitch(str)) {
      // -------------------------------------------------------
      // An option switch (possibly needing an argument)
      // -------------------------------------------------------
      // Note: The argument may be appended to the switch or it may be
      // the next element of argv.
      
      // 1. Separate switch from any argument embedded within
      string sw;
      string arg;
      FindSwitchAndArg(str, sw, arg);
      if (sw.empty()) {
	throw Exception(MISSING_SWITCH); // must have been '-'
      }
      
      // 2. Find option descriptor from switch
      const OptArgDesc* d = FindOptDesc(optArgDescs, sw.c_str());
      if (!d) {
	throw Exception(UNKNOWN_SWITCH + sw);
      }
      
      // 3. Find argument for switch (if any) [N.B. may advance iteration!]
      if (d->kind == ARG_NONE) {
	if (!arg.empty()) {
	  string msg = INVALID_ARG + sw + "=" + arg;
	  throw Exception(msg);
	}
      } else if (d->kind == ARG_REQ || d->kind == ARG_OPT) {
	if (arg.empty()) {
	  unsigned int nexti = i + 1;
	  if (nexti < argc && argv[nexti] && IsArg(argv[nexti])) {
	    arg = argv[nexti];
	    i = nexti; // increment iteration
	  }
	} 
	if (arg.empty() && d->kind == ARG_REQ) {
	  throw Exception(MISSING_ARG + sw);
	}
      }
      
      // 4. Add to map
      AddOptArg(*d, arg);
    }
    else { 
      // -------------------------------------------------------
      // A regular argument
      // -------------------------------------------------------
      arguments.push_back(string(str));
    } 
  } 
}


//****************************************************************************

const string& 
CmdLineParser::GetCmd() const
{
  return command;
}


// IsOpt:
bool 
CmdLineParser::IsOpt(const char swShort) const
{
  string sw(1, swShort);
  return IsOpt(sw);
}

bool 
CmdLineParser::IsOpt(const char* swLong) const
{
  string sw(swLong);
  return IsOpt(sw);
}

bool 
CmdLineParser::IsOpt(const string& sw) const
{
  SwitchToArgMap::const_iterator it = switchToArgMap.find(sw);
  return (it != switchToArgMap.end());
}


// IsOptArg:
bool 
CmdLineParser::IsOptArg(const char swShort) const
{
  string sw(1, swShort);
  return IsOptArg(sw);
}

bool 
CmdLineParser::IsOptArg(const char* swLong) const
{
  string sw(swLong);
  return IsOptArg(sw);
}

bool 
CmdLineParser::IsOptArg(const string& sw) const
{
  SwitchToArgMap::const_iterator it = switchToArgMap.find(sw);
  if ((it != switchToArgMap.end()) && ((*it).second != NULL)) {
    return true;
  }
  return false;
}


// GetOptArg:
const string&
CmdLineParser::GetOptArg(const char swShort) const
{
  string sw(1, swShort);
  return GetOptArg(sw);
}

const string&
CmdLineParser::GetOptArg(const char* swLong) const
{
  string sw(swLong);
  return GetOptArg(sw);
}

const string&
CmdLineParser::GetOptArg(const string& sw) const
{
  SwitchToArgMap::const_iterator it = switchToArgMap.find(sw);
  if (it == switchToArgMap.end()) {
    // FIXME: ERROR
  }
  string* arg = (*it).second;
  if (!arg) {
    // FIXME: ERROR
  }
  return *arg;
}


unsigned int 
CmdLineParser::GetNumArgs() const
{ 
  return arguments.size(); 
}

const string& 
CmdLineParser::GetArg(unsigned int i) const
{
  return arguments[i];
}


//****************************************************************************

long
CmdLineParser::ToLong(const string& str)
{
  long value = 0;
  if (str.empty()) { throw Exception(INTERNAL_ERR); }
  
  errno = 0;
  char* endptr = NULL;
  value = strtol(str.c_str(), &endptr, 0);
  if (errno || (endptr && strlen(endptr) > 0)) {
    string msg = "Argument `" + str 
      + "' cannot be converted to integral value.";
    if (errno) { // not always set
      msg += " ";
      msg += strerror(errno);
    }
    throw Exception(msg);
  } 
  return value;
}


uint64_t
CmdLineParser::ToUInt64(const string& str)
{
  uint64_t value = 0;
  if (str.empty()) { throw Exception(INTERNAL_ERR); }
  
  errno = 0;
  char* endptr = NULL;
  value = strtoul(str.c_str(), &endptr, 0);
  if (errno || (endptr && strlen(endptr) > 0)) {
    string msg = "Argument `" + str 
      + " cannot be converted to integral value.";
    if (errno) { // not always set
      msg += " ";
      msg += strerror(errno);
    }
    throw Exception(msg);
  } 
  return value;
}


double   
CmdLineParser::ToDbl(const string& str)
{
  double value = 0;
  if (str.empty()) { throw Exception(INTERNAL_ERR); }
  
  errno = 0;
  char* endptr = NULL;
  value = strtod(str.c_str(), &endptr);
  if (errno || (endptr && strlen(endptr) > 0)) {
    string msg = "Argument `" + str + "' cannot be converted to real value.";
    if (errno) { // not always set
      msg += " ";
      msg += strerror(errno);
    }
    throw Exception(msg);
  } 
  return value;
}


//****************************************************************************

void 
CmdLineParser::Dump(std::ostream& os) const
{
  os << "Command: `" << GetCmd() << "'" << std::endl;
  
  os << "Switch to Argument map:" << std::endl;
  for (SwitchToArgMap::const_iterator it = switchToArgMap.begin();
       it != switchToArgMap.end(); ++it) {
    const string& sw = (*it).first;
    const string* arg = (*it).second;
    os << "  " << sw << " --> " << ((arg) ? *arg : "<>") << std::endl;
  }
  
  os << "Regular arguments:" << std::endl;
  for (unsigned int i = 0; i < arguments.size(); ++i) {
    os << "  " << arguments[i] << std::endl;
  }
}


void 
CmdLineParser::DDump() const
{
  Dump(std::cerr);
}


//****************************************************************************

// Reset: Clear data to prepare for parsing
void
CmdLineParser::Reset()
{
  for (SwitchToArgMap::iterator it = switchToArgMap.begin();
       it != switchToArgMap.end(); ++it) {
    string* arg = (*it).second;
    delete arg;
  }
  switchToArgMap.clear();
  arguments.clear();
}


// FindSwitchAndArg: Given an option string from argv (potentially
// containing both an option and an argument), separate the two into
// the switch and argument.  The values are assigned to 'sw' and
// 'arg'.  (Note that the switch will have no dashes.)
void
CmdLineParser::FindSwitchAndArg(const char* swString, string& sw, string& arg)
{
  // 1. Initialize and ensure we only do at most one string resize
  unsigned int len = strlen(swString);
  sw.reserve(len);
  arg.reserve(len);
  sw = "";
  arg = "";

  // 2. Find pointers for begin/end of switch and argument
  const char* swStringEnd = swString + len;
  const char* begSw = NULL, *endSw = NULL;   // end pointers are inclusive!
  const char* begArg = NULL, *endArg = NULL;
  if (IsLongSwitch(swString)) {
    // test for --foo=arg
    begArg = strchr(swString, '=');
    if (begArg) {
      begArg++;                 // starts after the '='
      endArg = swStringEnd - 1; // ends right before '\0'
    }
    begSw = swString + 2;       // bump past '--'
    endSw = (begArg) ? (begArg - 2) : (swStringEnd - 1);
  } 
  else if (IsShortSwitch(swString)) {
    // test for -f[arg]
    begArg = (len > 2) ? (swString + 2) : NULL;   // starts after '-f'
    endArg = (begArg) ? (swStringEnd - 1) : NULL; // ends right before '\0'
    begSw  = (len > 1) ? (swString + 1) : NULL;   // starts after '-'
    endSw  = begSw;                               // single character
  } 
  else {
    throw Exception("Programming Error!");
  }

  // 3. Copy switch and argument substrings
  for (const char* p = begSw; p && p <= endSw; ++p) { sw += *p; }
  for (const char* p = begArg; p && p <= endArg; ++p) { arg += *p; }
}


// FindOptDesc: Given a NULL-terminated array of OptArgDesc and an
// option switch, return a reference to the appropriate OptArgDesc.
const CmdLineParser::OptArgDesc*
CmdLineParser::FindOptDesc(const OptArgDesc* optArgDescs, const char* sw)
{
  // Note: Because there will never be very many options, we simply
  // use a linear search.
  unsigned int swLen = strlen(sw);
  bool isShort = (swLen == 1);
  for (const OptArgDesc* p = optArgDescs; *p != OptArgDesc_NULL; ++p) {
    if (isShort) {
      if (p->swShort != 0 && p->swShort == *sw) {
	return p;
      }
    } else {
      if (p->swLong && strncmp(p->swLong, sw, swLen) == 0) {
	return p;
      }
    }
  }
  return NULL;
}


// AddOptArg: Records the optional switch and argument in the
// switch->argument map.  In order to support easy lookup, both the
// long and short form of the switches are entered in the map.  
void
CmdLineParser::AddOptArg(const OptArgDesc& desc, const string& arg)
{
  if (desc.swShort != 0) {
    string swShort(1, desc.swShort);
    AddOptArg(swShort, arg);
  }
  if (desc.swLong) {
    string swLong(desc.swLong);
    AddOptArg(swLong, arg);
  }
}


// AddOptArg: If the switch has no argument, NULL is used as its value.
// In the event that the switch already exists in the map with an
// argument, we append this argument creating a colon-separated list.
void
CmdLineParser::AddOptArg(const string& sw, const string& arg)
{
  SwitchToArgMap::iterator it = switchToArgMap.find(sw);
  if (it == switchToArgMap.end()) {
    string* theArg = (arg.empty()) ? NULL : new string(arg);
    switchToArgMap.insert(make_pair(sw, theArg));
  } else {
    string* theArg = (*it).second;
    if (theArg) {
      *theArg += ":" + arg;
    }
  }
}

//****************************************************************************

