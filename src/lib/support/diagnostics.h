// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/diagnostics.h,v 1.6 2004/01/25 02:40:42 eraxxon Exp $

// * BeginCopyright *********************************************************
/*
  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan
*/
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/diagnostics.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2c/diagnostics.h
//
//***************************************************************************

#ifndef diagnostics_INCLUDED
#define diagnostics_INCLUDED
/* ====================================================================
 * ====================================================================
 *
 * Description:
 *    A generic module for diagnostics reporting, where an enumeration
 *    of error codes will support options to turn warnings on or off.
 *    It possible to initialize and exit this module several times, but
 *    typically it is initiated only once (when the executable is started
 *    up) and excited only once (when the executable is exited).
 *
 *    Initialization
 *    --------------
 *
 *       Diag_Init:
 *          This module should be initialized as early as possible, and
 *          certainly before any of the other facilities provided through
 *          this interface are referenced.
 *
 *       Diag_Exit:
 *          This module should be terminated as late as possible, and
 *          certainly after all potential references to any of the other
 *          facilities provided through this interface (with possible
 *          exception of Diag_Get_Warn_Count).
 *
 *       Diag_Set_Phase:
 *          A string identifying the executable and possibly the stage
 *          of computation within this executable.  The phase name is 
 *          kept in a hidden character buffer, and it must not exceed
 *          80 characters in size (including the terminating '\0' char).
 *          By default the phase is set to be an empty string.
 *
 *       Diag_Set_File:
 *          All diagnostics messages are emitted to stderr (see <stdio.h>),
 *          and this routine will open an output file (as named) and also
 *          cause diagnostics to be streamed through to that file.
 *
 *       Diag_Set_Max_Diags:
 *          The maximum number of diagnostics messages that will be emitted
 *          before the execution is terminated (zero (0) means unlimited.
 *          Initially, unlimited.
 *          
 *       Diag_Get_Warn_Count:
 *          A counter of the number of warnings that have been emitted.
 *          Initially, zero (0).  Note that this counter will not be reset
 *          by a call to Diag_Exit().
 *          
 *
 *    User Errors
 *    -----------
 *       The arguments (diag_args) must have the format:
 *
 *          (DIAG_CODE, args)
 *
 *       where DIAG_CODE is one of the enumerated values and args is
 *       a comma separated list of values corresponding to the format
 *       directives in the diagnostic message (see diagnostics.c).
 *
 *       USER_WARNING: 
 *          Emits warnings about a condition in the original source
 *          program, in terms of line/column numbers from the original
 *          source-file.
 *       USER_WARNING: 
 *          Emits a fatal error and terminates execution without further 
 *          processing (EXIT(1)).
 *
 *
 *    Diagnostics Reporting
 *    ---------------------
 *       The arguments (diag_args) must have the format:
 *
 *          (DIAG_CODE, args)
 *
 *       where DIAG_CODE is one of the enumerated values and args is
 *       a comma separated list of values corresponding to the format
 *       directives in the diagnostic message (see diagnostics.c).
 *       When "Is_True_On" is defined, the location of the ASSERT in
 *       the compiler sources is emitted as part of the diagnostics.
 *
 *       ASSERT_WARN:
 *          Given a boolean truth expression, emit a warning diagnostics
 *          based on the diag_args when the truth-value is FALSE.
 *
 *       ASSERT_FATAL:
 *          Given a boolean truth expression, emit a fatal error 
 *          diagnostics based on the diag_args when the truth-value 
 *          is FALSE and exit with error code (1).
 *
 *       ASSERT_WARN_SRCPOS:
 *          Same as ASSERT_WARN, but will include the srcpos in the
 *          emitted diagnostic message.
 *
 *       ASSERT_FATAL_SRCPOS:
 *          Same as ASSERT_FATAL, but will include the srcpos in the
 *          emitted diagnostic message.
 *
 *       ASSERT_DBG_WARN:
 *          Same as ASSERT_WARN, but only to be emitted during the
 *          development of the tool.  I.e. customer's should never
 *          see this fatal error, and code to work around the problem
 *          must follow the assertion.
 *
 *       ASSERT_DBG_FATAL:
 *          Same as ASSERT_FATAL, but only to be emitted during the
 *          development of the tool.  I.e. customer's should never
 *          see this fatal error.
 *
 * ====================================================================
 * ====================================================================
 */

//************************* System Include Files ****************************

#include <stdio.h>		    /* for stderr */

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h> /* "srcpos.h" */

//*************************** User Include Files ****************************

//***************************************************************************

// Debug messages (from csprof)

// Debug and verbosity levels: higher level --> more info; 0 turns
// respective messages off

// Private debugging level: messages for in-house debugging [0-9]
#define DBG_LVL 0

// Public debugging level: stuff that a few users may find interesting [0-9]
extern int DBG_LVL_PUB; // default: 0

#define DBGMSG(level, ...)                                            \
  if (level <= DBG_LVL) {                                             \
    fprintf(stderr, "dbg* [%d]: ", level);                            \
    fprintf(stderr, __VA_ARGS__); fputs("\n", stderr); }

#define DBGMSG_PUB(level, ...)                                        \
  if (level <= DBG_LVL_PUB) {                                         \
    fprintf(stderr, "dbg [%d]: ", level);                             \
    fprintf(stderr, __VA_ARGS__); fputs("\n", stderr); }

#define ERRMSG(...)                                                   \
  { fputs("error", stderr);                                           \
    if (DBG_LVL) {                                                    \
      fprintf(stderr, " [%s:%d]", __FILE__, __LINE__); }              \
    fputs(": ", stderr); fprintf(stderr, __VA_ARGS__); fputs("\n", stderr); }

#define DIE(...) ERRMSG(__VA_ARGS__); { exit(1); }


#define IFDBG(level) if (level <= DBG_LVL)

#define IFDBG_PUB(level) if (level <= DBG_LVL_PUB)

//***************************************************************************


      /* ------------ Initialization and finalization -------------*/
      /* ----------------------------------------------------------*/

extern void Diag_Init(void);
extern void Diag_Exit(void);
extern void Diag_Set_Phase(const char *phase_name);
extern void Diag_Set_File(const char *filename);
extern void Diag_Set_Max_Diags(int max_allowed_diags);
extern int  Diag_Get_Warn_Count(void);


      /* -------------- Diagnostic code enumeration ---------------*/
      /* ----------------------------------------------------------*/

typedef enum Diag_Code
{
   DIAG_FIRST = 0,
   DIAG_A_STRING = 0,
   DIAG_UNKNOWN_CMD_LINE_OPTION = 1,
   DIAG_UNIMPLEMENTED = 2,
   DIAG_CANNOT_OPEN_FILE = 3,
   DIAG_CANNOT_CLOSE_FILE = 4,

   /* whirl2f statement and expression diagnostics */
   DIAG_W2F_FIRST = 100,
   DIAG_W2F_CANNOT_HANDLE_OPC = 101,            /* WN related diagnostics */
   DIAG_W2F_UNEXPECTED_OPC = 110,
   DIAG_W2F_UNEXPECTED_IOS = 111,
   DIAG_W2F_UNEXPECTED_IOU = 112,
   DIAG_W2F_UNEXPECTED_IOF = 113,
   DIAG_W2F_UNEXPECTED_IOC = 114,
   DIAG_W2F_UNEXPECTED_IOL = 115,
   DIAG_W2F_UNEXPECTED_INITV = 116,
   DIAG_W2F_UNEXPECTED_DOLOOP_BOUNDOP = 117,
   DIAG_W2F_UNEXPECTED_IMPLIED_DOLOOP = 118,
   DIAG_W2F_UNEXPECTED_RETURNSITE = 119,
   DIAG_W2F_UNEXPECTED_CALLSITE = 120,
   DIAG_W2F_UNEXPECTED_SUBSTRING_REF = 121,
   DIAG_W2F_UNEXPEXTED_RETURNREG_USE = 122,
   DIAG_W2F_UNEXPEXTED_OFFSET = 123,
   DIAG_W2F_UNEXPEXTED_NULL_PTR = 124,
   DIAG_W2F_NONEXISTENT_FLD_PATH = 125,
   DIAG_W2F_CANNOT_LDA_PREG = 126,
   DIAG_W2F_CANNOT_DEREF = 127,
   DIAG_W2F_UNEXPECTED_NUM_KIDS = 128,
   DIAG_W2F_UNEXPECTED_CVT = 129,
   DIAG_W2F_UNEXPECTED_CONTEXT = 130,

   /* whirl2f symbol-table diagnostics */
   DIAG_W2F_UNEXPECTED_TYPE_KIND = 203,          /* symtab diagnostics */
   DIAG_W2F_UNEXPECTED_TYPE_SIZE = 204,
   DIAG_W2F_UNEXPECTED_BTYPE = 205,
   DIAG_W2F_EXPECTED_PTR_TO_CHARACTER = 206,
   DIAG_W2F_EXPECTED_PTR = 207,
   DIAG_W2F_UNEXPECTED_SYMBOL = 208,
   DIAG_W2F_UNEXPECTED_SYMCLASS = 209,
   DIAG_W2F_UNEXPECTED_STORECLASS = 210,
   DIAG_W2F_UNEXPECTED_SYM_CONST = 211,
   DIAG_W2F_UNEXPECTED_PRAGMA = 212,
   DIAG_W2F_MISPLACED_PRAGMA = 213,
   DIAG_W2F_EXPECTED_IDNAME = 214,
   DIAG_W2F_INCOMPATIBLE_TYS = 215,
   DIAG_W2F_DECLARE_RETURN_PARAM = 216,
   DIAG_W2F_BUFFER_ERROR = 217,
   DIAG_W2F_LAST = 217,

   DIAG_LAST = 542
} DIAG_CODE;


      /* ------------------- Diagnostics macros -------------------*/
      /* ----------------------------------------------------------*/

#define USER_WARNING(a_truth, diag_args, wn) \
   DIAG_USER_SRCPOS(a_truth, Diag_User_Warning, diag_args, wn)

#define USER_FATAL(a_truth, diag_args, wn) \
   DIAG_USER_SRCPOS(a_truth, Diag_User_Fatal, diag_args, wn)


#ifdef Is_True_On

#define ASSERT_WARN_SRCPOS(a_truth, diag_args, wn) \
   DIAG_ASSERT_LOC_SRCPOS(a_truth, Diag_Warning, diag_args, wn)
#define ASSERT_FATAL_SRCPOS(a_truth, diag_args, wn) \
   DIAG_ASSERT_LOC_SRCPOS(a_truth, Diag_Fatal, diag_args, wn)
#define ASSERT_WARN(a_truth, diag_args) \
   DIAG_ASSERT_LOC(a_truth, Diag_Warning, diag_args)
#define ASSERT_FATAL(a_truth, diag_args) \
   DIAG_ASSERT_LOC(a_truth, Diag_Fatal, diag_args)
#define ASSERT_DBG_WARN ASSERT_WARN
#define ASSERT_DBG_FATAL ASSERT_FATAL

#else /* !defined(Is_True_On) */

#define ASSERT_WARN(a_truth, diag_args) \
   DIAG_ASSERT_NOLOC(a_truth, Diag_Warning, diag_args)
#define ASSERT_FATAL(a_truth, diag_args) \
   DIAG_ASSERT_NOLOC(a_truth, Diag_Fatal, diag_args)
# define ASSERT_DBG_WARN(a_truth, diag_args) ((void) 1)
# define ASSERT_DBG_FATAL(a_truth, diag_args) ((void) 1)

#endif /*Is_True_On*/


   /* ------- Hidden functions/macros (NEVER CALL THESE) -------*/
   /* ----------------------------------------------------------*/

#define DIAG_USER_SRCPOS(a_truth, diag_handler, diag_args, wn) \
   ((a_truth) ? \
    (void) 1 :  \
    (Diag_Set_Srcpos(WN_Get_Linenum(wn)), \
     diag_handler  diag_args))
  
#define DIAG_ASSERT_LOC(a_truth, diag_handler, diag_args) \
   ((a_truth) ? \
    (void) 1 :  \
    (Diag_Set_Location(__FILE__, __LINE__), diag_handler  diag_args))

#define DIAG_ASSERT_LOC_SRCPOS(a_truth, diag_handler, diag_args, wn) \
   ((a_truth) ? \
    (void) 1 :  \
    (Diag_Set_Location(__FILE__, __LINE__), \
     Diag_Set_Srcpos(WN_Get_Linenum(wn)), \
     diag_handler  diag_args))

#define DIAG_ASSERT_NOLOC(a_truth, diag_handler, diag_args) \
   ((a_truth) ? (void) 1 : diag_handler  diag_args)

#define DIAG_ASSERT_NOLOC_SRCPOS(a_truth, diag_handler, diag_args, wn) \
   ((a_truth) ? \
    (void) 1 : \
    (Diag_Set_Srcpos(WN_Get_Linenum(wn)), \
     diag_handler  diag_args))

extern void Diag_Set_Location(const char *file_name, int line_number);
extern void Diag_Set_Srcpos(SRCPOS srcpos);
extern void Diag_User_Warning(DIAG_CODE code, ...);
extern void Diag_User_Fatal(DIAG_CODE code, ...);
extern void Diag_Warning(DIAG_CODE code, ...);
extern void Diag_Fatal(DIAG_CODE code, ...);
extern void Diag_Warning_Srcpos(DIAG_CODE code, ...);
extern void Diag_Fatal_Srcpos(DIAG_CODE code, ...);


#endif /* diagnostics_INCLUDED */



