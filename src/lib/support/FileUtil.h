// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/FileUtil.h,v 1.1 2004/06/01 22:25:42 eraxxon Exp $

// * BeginRiceCopyright *****************************************************
// ******************************************************* EndRiceCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/FileUtil.h,v $
//
// Purpose:
//    [The purpose of this file]
//
// Description:
//    [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef FileUtil_h
#define FileUtil_h 

//************************* System Include Files ****************************

#include <string>

//*************************** User Include Files ****************************

//*************************** Forward Declarations ***************************

//****************************************************************************

namespace FileUtil {

  // FileName: Given a path, returns the filename portion.  If path is
  // NULL or ends in '/', returns the empty string. 
  // Examples:
  //   fname.ext       --> fname.ext
  //   /path/fname.ext --> fname.ext
  //   /usr/lib        --> lib
  //   /usr/           --> 
  //   /               --> 
  extern std::string
  FileName(const char* path); 
  
  // BaseName: Given a path, returns the 'basename' portion, the final
  // component of the pathname, first deleting any trailing '/'.  If path is
  // NULL or empty, returns ".".  (Note: libgen.h is not available on
  // Cygwin!)
  // Examples:
  //   fname.ext       --> fname.ext
  //   /path/fname.ext --> fname.ext
  //   /usr/lib        --> lib
  //   /usr/           --> usr
  //   /               --> /
  extern std::string
  BaseName(const char* path); 
  
  // DirName: Given a path, returns the 'dirname' portion, the pathanem
  // of the parent directory, first deleting any trailing '/'.  If path
  // is NULL or empty, returns "."; if path does not conain a '/'
  // returns ".".  ".".  (Note: libgen.h is not available on Cygwin!)
  // Examples:
  //   /path/fname.ext --> /path
  //   /usr/lib        --> /usr
  //   /usr/           --> /
  //   usr             --> .
  //   /               --> /
  //   .               --> .
  //   ..              --> .
  extern std::string
  DirName(const char* path); 
  
  
}; /* namespace FileUtil */

#endif 
