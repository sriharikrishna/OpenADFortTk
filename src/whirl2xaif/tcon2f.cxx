// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/tcon2f.cxx,v 1.3 2003/09/05 13:01:36 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/tcon2f.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/tcon2f.cxx
//
//***************************************************************************

/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *    See tcon2f.h for a description of the exported functions and 
 *    variables.
 *
 * ====================================================================
 * ====================================================================
 */

//************************** System Include Files ***************************

#include <alloca.h>
#include <sstream> //FIXME

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

#include "whirl2f_common.h"
#include "tcon2f.h"

//************************** Forward Declarations ***************************

//***************************************************************************

/*---------------------- Exported functions -------------------*/
/*-------------------------------------------------------------*/


std::string
TCON2F_hollerith(TCON tvalue)
{
  /* Translates the given Hollerith constant into Fortran representation.
   * A hollerith constant cannot be split into substrings.
   */
  const char *strbase;
  char       *str;
  INT32       strlen;
  
  ASSERT_DBG_WARN(TCON_ty(tvalue) == MTYPE_STR,
		  (DIAG_W2F_UNEXPECTED_BTYPE, 
		   MTYPE_name(TCON_ty(tvalue)), "TCON2F_hollerith"));
  
  strlen = Targ_String_Length(tvalue);
  strbase = Targ_String_Address(tvalue);
  str = (char *) alloca(strlen + 16);
  sprintf(str, "%dH%s", strlen, strbase);
  
  return std::string(str);
} /* TCON2F_hollerith */

   
std::string
TCON2F_translate(TCON tvalue, BOOL is_logical, TY_IDX object_ty)
{
  // FIXME: double check // use stream operators

  /* Translates the given TCON to a Fortran representation.  Since
   * the tcon itself does not tell us, we must rely on the context
   * to inform us whether or not a integer constant is a logical
   * value or not.
   */
  const char  *strbase;
  char        *str;

  // FIXME: for now we use this hack to return a string
  std::ostringstream sstr;
  
  if (is_logical && MTYPE_type_class(TCON_ty(tvalue)) & MTYPE_CLASS_INTEGER) {
    // Treat it as regular integral constant, unless it has value 0 or 1.
    if (Targ_To_Host(tvalue) == 0LL)
      sstr << "false";
    else if  (Targ_To_Host(tvalue) == 1LL)
      sstr << "true";
    else
      is_logical = FALSE;
  } else { /* Only integral values can be treated as boolean */
    is_logical = FALSE; 
  }
  
  if (!is_logical) {
    switch (TCON_ty(tvalue)) {

    case MTYPE_STR: {
      // To be entirely safe, we do not assume the string contains
      // NULL terminator.
      INT32 len = Targ_String_Length(tvalue);
      const char* str = Targ_String_Address(tvalue);      
      for (int i = 0; i < len; ++i)
	sstr << str[i];
    }
    break;
      
    case MTYPE_I1:
    case MTYPE_I2:
    case MTYPE_I4:
      sstr << Targ_Print("%1d", tvalue);
      break;
      
    case MTYPE_I8:
      sstr << Targ_Print("%1lld", tvalue);
      break;
      
    case MTYPE_U1:
    case MTYPE_U2:
    case MTYPE_U4:
      sstr << Targ_Print("%1u", tvalue);
      break;
      
    case MTYPE_U8:
      sstr << Targ_Print("%1llu", tvalue);
      break;
      
    case MTYPE_F4:
      sstr << Targ_Print("%.10e", tvalue);
      break;
      
    case MTYPE_F8:
      sstr << Targ_Print("%.20e", tvalue);
      break;
      
    case MTYPE_FQ:
      sstr << Targ_Print(NULL, tvalue);
      break;
      
    case MTYPE_C4:
    case MTYPE_C8:
    case MTYPE_CQ:
      sstr << '(' << TCON2F_translate(Extract_Complex_Real(tvalue), FALSE)
	   << ',' << TCON2F_translate(Extract_Complex_Imag(tvalue), FALSE)
	   << ')';
      break;
      
    default:
      /* Only expression nodes should be handled here */
      ASSERT_DBG_WARN(FALSE, (DIAG_W2F_UNEXPECTED_BTYPE, 
			      MTYPE_name(TCON_ty(tvalue)),
			      "TCON2F_translate"));
      sstr << "<TCON>";
      break;
    }
  }
  
  return sstr.str();

} /* TCON2F_translate */

std::string
TCON2F_translate(TCON tvalue, BOOL is_logical)
{
  return TCON2F_translate(tvalue, is_logical, (TY_IDX)NULL);
} 

