// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/FileUtil.cxx,v 1.1 2004/06/01 22:25:42 eraxxon Exp $

// * BeginRiceCopyright *****************************************************
// ******************************************************* EndRiceCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/FileUtil.cxx,v $
//
// Purpose:
//    [The purpose of this file]
//
// Description:
//    [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <string.h> // <cstring>

//*************************** User Include Files ****************************

#include "FileUtil.h"

//*************************** Forward Declarations **************************

using std::string;

//***************************************************************************

string
FileUtil::FileName(const char* path); 
{
  string filenm;
  
  if (!path) { return filenm; }

  const char* lastSlash = strrchr(path, '/');
  if (lastSlash) {
    // We have either a valid or invalid filename:
    //   valid:   "/foo" || ".../foo"
    //   invlaid: "/"    || ".../"
    filenm = (lastSlash + 1); 
  } else {
    // path contains no slashes; we have the basename
    filenm = path; 
  } 
  return filenm; 
} 


string
FileUtil::BaseName(const char* path); 
{
  string basenm = ".";
  
  if (!path) { return basenm; }

  // Scan past any trailing '/'
  const char* end = path + (strlen(path) - 1); // point to last character
  while (end != path && *end == '/') { --end; }

  const char* lastSlash = strrchr(end, '/');
  if (lastSlash) {
    // copy the basename portion
    if (lastSlash == path) { // path = "/"
      basenm = "/";
    } else {
      basenm.reserve(end - lastSlash + 1);
      for (const char* p = lastSlash; p <= end; ++p) { 
	basenm += *p;
      }
    }
  } 
  return basenm; 
} 


string
FileUtil::DirName(const char* path) 
{
  string parentdirnm = "."; 

  if (!path) { return parentdirnm; }
  
  // Scan past any trailing '/'
  const char* end = path + (strlen(path) - 1); // point to last character
  while (end != path && *end == '/') { --end; }
  
  const char* lastSlash = strrchr(end, '/');
  if (lastSlash) {
    // copy the dirname portion
    if (lastSlash == path) { // path = "/"
      parentdirnm = "/";
    } else {
      parentdirnm.reserve(lastSlash - path);
      for (const char* p = path; p < lastSlash; ++p) { 
	parentdirnm += *p;
      }
    }
  }
  return parentdirnm;
}

