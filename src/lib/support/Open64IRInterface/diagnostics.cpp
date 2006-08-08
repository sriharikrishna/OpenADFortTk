// -*-Mode: C++;-*-
// $Header: /home/derivs2/mstrout/CVSRepository/UseNewOA-Open64/Open64IRInterface/diagnostics.cpp,v 1.1.1.1 2004/04/16 15:58:28 mstrout Exp $

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
//   $Source: /home/derivs2/mstrout/CVSRepository/UseNewOA-Open64/Open64IRInterface/diagnostics.cpp,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2c/diagnostics.cxx
//
//***************************************************************************

/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *    This hides the error diagnostics machinery, such that we
 *    can define our own or rely on some existing facilities.
 *
 *    For now, we just implement a simple error diagnostics scheme
 *    which does not rely on any other existing scheme.
 *
 * ====================================================================
 * ====================================================================
 */

//************************* System Include Files ****************************

#include <stdarg.h>
#include <errno.h>		    /* for sys_errlist */
#include <stdio.h>		    /* for stderr */

//************************** Open64 Include Files ***************************

#include "Open64IRInterface/Open64BasicTypes.h"
#include "file_util.h" 

//*************************** User Include Files ****************************

#include "Open64IRInterface/diagnostics.h"

//***************************************************************************

int DBG_LVL_PUB = 0;

static char        Diag_Phase_Name[80] = "";
static FILE       *Diag_File = NULL;
static int         Diag_Max_Diags = 10;  /* Default */
static int         Diag_Warn_Count = 0;
static const char *Diag_File_Location = NULL;
static int         Diag_Line_Location = 0;

static const char *Diag_Msg[DIAG_LAST+1];


void
Diag_Init(void)
{
   int diag;

   /* Initiate the Diag_Msg[] table to a standard error message.
    */
   for (diag = DIAG_FIRST; diag <= DIAG_LAST; diag++)
      Diag_Msg[diag] = "*** Unknown diagnostics code ***";
   
   /* Initiate the Diag_Msg[] table for well-defined error codes.
    */
   Diag_Msg[DIAG_A_STRING] = "%s";
   Diag_Msg[DIAG_UNIMPLEMENTED] = "TODO: Unimplemented feature: %s";
   Diag_Msg[DIAG_UNKNOWN_CMD_LINE_OPTION] = "Unknown command-line option: %s";
   Diag_Msg[DIAG_CANNOT_OPEN_FILE] = "Cannot open file (%s), errno=%d";
   Diag_Msg[DIAG_CANNOT_CLOSE_FILE] = "Cannot close file (%s), errno=%d";
   
   Diag_Msg[DIAG_W2F_CANNOT_HANDLE_OPC] = 
      "cannot handle opcode %s (%d)";
   Diag_Msg[DIAG_W2F_UNEXPECTED_OPC] = 
      "unexpected opcode in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_IOS] = 
      "unexpected IO statement kind %s in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_IOU] = 
      "unexpected IO unit kind %s in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_IOF] = 
      "unexpected IO format kind %s in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_IOC] = 
      "unexpected IO control kind %s in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_IOL] = 
      "unexpected IO list kind %s in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_INITV] = 
      "unexpected INITV kind %d in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_DOLOOP_BOUNDOP] = 
      "unexpected opcode (%s) for DO loop bound in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_IMPLIED_DOLOOP] = 
      "unexpected form of implied do-loop in %s(); Cannot calculate bounds";
   Diag_Msg[DIAG_W2F_UNEXPECTED_RETURNSITE] =
      "RETURNSITE out of sequence in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_CALLSITE] =
      "CALLSITE out of sequence in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_SUBSTRING_REF] =
      "Unexpected (sub)string reference in %s()";
   Diag_Msg[DIAG_W2F_UNEXPEXTED_RETURNREG_USE] =
      "Unexpected usage of return-registers detected in %s()";
   Diag_Msg[DIAG_W2F_UNEXPEXTED_OFFSET] =
      "Unexpected offset (%d) for memory location in %s()";
   Diag_Msg[DIAG_W2F_UNEXPEXTED_NULL_PTR] =
      "Unexpected NULL value for %s in %s()";
   Diag_Msg[DIAG_W2F_NONEXISTENT_FLD_PATH] =
      "Non-existent path to an FLD of the given object type in %s()";
   Diag_Msg[DIAG_W2F_CANNOT_LDA_PREG] =
      "Cannot take the address of a pseudo-register";
   Diag_Msg[DIAG_W2F_CANNOT_DEREF] =
      "Cannot dereference pointer variable in %s(); No pointee specification";
   Diag_Msg[DIAG_W2F_UNEXPECTED_NUM_KIDS] =
      "Unexpected number of kids (%d), expected %d kids for %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_CVT] =
      "unexpected conversion from %s to %s in %s()"; /* Use MTYPE_name() */
   Diag_Msg[DIAG_W2F_UNEXPECTED_CONTEXT] =
      "unexpected context of translation for %s()";

   Diag_Msg[DIAG_W2F_UNEXPECTED_TYPE_KIND] = 
      "unexpected TY_kind (%d) in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_TYPE_SIZE] = 
      "unexpected TY_size (%d) in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_BTYPE] = 
      "unexpected TY_btype (%s) in %s()"; /* Use MTYPE_name() */
   Diag_Msg[DIAG_W2F_EXPECTED_PTR_TO_CHARACTER] = 
      "expected pointer to character operands in %s()";
   Diag_Msg[DIAG_W2F_EXPECTED_PTR] = 
      "expected pointer TY in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_SYMBOL] = 
      "unexpected form of symbol in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_SYMCLASS] = 
      "unexpected ST_symclass (%d) in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_STORECLASS] = 
      "unexpected ST_sclass (%d) in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_SYM_CONST] = 
      "unexpected symbolic constant in %s()";
   Diag_Msg[DIAG_W2F_UNEXPECTED_PRAGMA] = 
      "unexpected pragma kind in %s()";
   Diag_Msg[DIAG_W2F_MISPLACED_PRAGMA] = 
      "pragma %s will be misplaced in output, and will be emitted as comment";
   Diag_Msg[DIAG_W2F_EXPECTED_IDNAME] = 
      "expected OPC_IDNAME in %s()";
   Diag_Msg[DIAG_W2F_INCOMPATIBLE_TYS] = 
      "incompatible types in %s()";
   Diag_Msg[DIAG_W2F_DECLARE_RETURN_PARAM] = 
      "should not declare return parameter: %s()";
   Diag_Msg[DIAG_W2F_BUFFER_ERROR] = 
      "Error in buffer access: %s";

   Diag_Warn_Count = 0;
} /* Diag_Init */


void
Diag_Exit(void)
{
  /* Close the diagnostics file if one is open */
  if (Diag_File != NULL) {
    fclose (Diag_File);
    Diag_File = NULL;
  }
}


void 
Diag_Set_Phase(const char *phase_name)
{
  Set_Error_Phase(phase_name); /* Initiate the common error handler */
  (void)strcpy(Diag_Phase_Name, phase_name);
}


void 
Diag_Set_File(const char *filename)
{
   /* Initiate the common error handler */
   Set_Error_File(filename);

   /* Close the diagnostics file if one already is open */
   if (Diag_File != NULL)
   {
      fclose(Diag_File);
      Diag_File = NULL;
   }
   
   if (filename != NULL)
   {
      /* Delete the named file if it exists: */
      if (Is_File(filename))
	 unlink(filename);
     
      Diag_File = fopen(filename, "a");
      if (Diag_File == NULL)
	 fprintf(stderr, "Cannot open error-file: \"%s\"\n", filename);
      else if (Same_File(Diag_File, stderr))
      {
	 fclose(Diag_File);
	 Diag_File = NULL;
	 fprintf(stderr, "Cannot open stderr as alternate error file\n");
      }
   }
   else
      fprintf(stderr,
	      "Attempt to open name-less file as error file is ignored\n");
}


void
Diag_Set_Max_Diags(int max_allowed_diags)
{
  Diag_Max_Diags = max_allowed_diags;
}


int 
Diag_Get_Warn_Count(void)
{
  return Diag_Warn_Count;
}


//***************************************************************************

void 
Diag_Set_Location(const char *file_name, int line_number)
{
  Diag_File_Location = file_name;
  Diag_Line_Location = line_number;
}


void 
Diag_Warning(DIAG_CODE code, ...)
{
   char    diag_char[512];
   va_list arg_ptr;
  
   if (Diag_Max_Diags > Diag_Warn_Count)
   {
      if (Diag_File_Location != NULL)
	 (void)sprintf(&diag_char[0], 
		       "%s(%s:%d): WARNING %d: %s\n", 
		       Diag_Phase_Name, 
		       Diag_File_Location, Diag_Line_Location, 
		       code,
		       Diag_Msg[code]);
      else
	 (void)sprintf(&diag_char[0], 
		       "%s: WARNING %d: %s\n", 
		       Diag_Phase_Name, code, Diag_Msg[code]);
      
      va_start(arg_ptr, code);
      vfprintf(stderr, &diag_char[0], arg_ptr);
      va_end(arg_ptr);

      Diag_Warn_Count++;
   }
} /* Diag_Warning */


void 
Diag_Fatal(DIAG_CODE code, ...)
{
  char    diag_char[512];
  va_list arg_ptr;
  
  if (Diag_File_Location != NULL) {
    sprintf(&diag_char[0], "%s(%s:%d): FATAL ERROR: %s\n", 
	    Diag_Phase_Name, 
	    Diag_File_Location, Diag_Line_Location, 
	    Diag_Msg[code]);
  } else {
    sprintf(&diag_char[0], "%s: FATAL ERROR: %s\n", 
	    Diag_Phase_Name, Diag_Msg[code]);
  }
  
  va_start(arg_ptr, code);
  vfprintf(stderr, &diag_char[0], arg_ptr);
  va_end(arg_ptr);
  
  exit(1);
} /* Diag_Fatal */

