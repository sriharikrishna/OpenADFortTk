// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/tcon2f.cxx,v 1.2 2003/07/24 14:36:04 eraxxon Exp $

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

/*---------------------- Hidden utilities ---------------------*/
/*-------------------------------------------------------------*/
  
static char *
Remove_Trailing_Zero_Fraction(char *strbase)
{
  /* Expect the input to be of the form: "d.dddde+dd", where a '-' may 
   * occur in place of the '+', or the '+' could be omitted.  We view the
   * 'e' as any letter.
   */
  INT last, i;

   /* Get to the first digit from the right, which is non-zero.
    */
   for (last = 0; strbase[last] != '\0'; last++);
   for (i = last-1; strbase[i] == '0'; i--);

   /* Remove any unnecesary exponent part and the trailing zeros in the
    * fractional part.
    */
   if (strbase[i] < '0' || strbase[i] > '9')
   {
      while (strbase[i] < '0' || strbase[i] > '9') i--;
      while (strbase[i] == '0') i--;
      if (strbase[i] == '.')
      {
	 strbase[i+1] = '0';
	 last = i+2;
      }
      else
      {
	 last = i+1;
      }
   }
   else
   {
      INT j, remove_to;

      while (strbase[i] >= '0' && strbase[i] <= '9') i--; /* skip exp digits */
      while (strbase[i] < '0' || strbase[i] > '9') i--; /* skip exp letters */
      remove_to = i;

      while (strbase[i] == '0') i--; /* skip zero digits in the fraction */
      if (strbase[i] == '.')
	 i += 1;

      /* Move exponent part up till just after the non-zero fractional part
       */
      for (j = remove_to+1; j < last; j++)
	 strbase[++i] = strbase[j];
      last = i+1;
   }
   strbase[last] = '\0';

   return strbase;
} /* Remove_Trailing_Zero_Fraction */


static char *
TCON2F_append_string_char(char *str, char ch)
{
  BOOL escape;
  char escaped_ch;
  
  switch (ch)
  {
  case '\n':
     escaped_ch = 'n';
     escape = TRUE;
     break;
  case '\t':
     escaped_ch = 't';
     escape = TRUE;
     break;
  case '\b':
     escaped_ch = 'b';
     escape = TRUE;
     break;
  case '\r':
     escaped_ch = 'r';
     escape = TRUE;
     break;
  case '\f':
     escaped_ch = 'f';
     escape = TRUE;
     break;
  case '\v':
     escaped_ch = 'v';
     escape = TRUE;
     break;
  case '\\':
     escaped_ch = '\\';
     escape = TRUE;
     break;
  case '\'':
     escaped_ch = '"';  
     escape=FALSE;  
     break;
  default: 
     escaped_ch = ch;
     escape = FALSE;
     break;
  }
  if (escape)
     *str++ = '\\';
  *str++ = escaped_ch;

  return str;
} /* TCON2F_append_string_char */


static void 
TCON2F_Append_String_Const(std::ostream& os, 
			   const char  *orig_str, 
			   INT32        strlen)
{
   const char *str_base;
   char       *str;
   INT32       stridx;

   str_base = str = (char*)alloca(2*strlen + 3); // "'", orig_str, "'", "\0"
   *(str++) = '\'';
   for (stridx = 0; stridx < strlen; stridx++)
     str = TCON2F_append_string_char(str, orig_str[stridx]);
   while (str[-1] == '\0') str--;
   *(str++) = '\'';
   *(str++) = '\0';
   os << str_base;
} /* TCON2F_Append_String_Const */


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
  /* Translates the given TCON to a Fortran representation.  Since
   * the tcon itself does not tell us, we must rely on the context
   * to inform us whether or not a integer constant is a logical
   * value or not.
   */
  const char  *strbase;
  char        *str;
  INT32        max_strlen, strlen, stridx;
  INT32        seg_length;
  INT32        non_empty_length;

  // FIXME: for now we use this hack to return a string
  std::ostringstream sstr;
  
  if (is_logical && MTYPE_type_class(TCON_ty(tvalue)) & MTYPE_CLASS_INTEGER) {
    // Treat it as regular integral constant, unless it has value 0 or 1.
    if (Targ_To_Host(tvalue) == 0LL)
      sstr << ".FALSE.";
    else if  (Targ_To_Host(tvalue) == 1LL)
      sstr << ".TRUE.";
    else
      is_logical = FALSE;
  } else /* Only integral values can be treated as boolean */
    is_logical = FALSE; 
  

  if (!is_logical) {
    switch (TCON_ty(tvalue)) {

    case MTYPE_STR:
      max_strlen = 512; //FIXME(Get_Maximum_Linelength()*2)/3;
      strlen = Targ_String_Length(tvalue);
      strbase = Targ_String_Address(tvalue);
      if (object_ty != (TY_IDX)NULL)
	seg_length = TY_size(object_ty);
      else
	seg_length = max_strlen;
      
      str = (char*)alloca(seg_length + 1);
      
      if (object_ty != (TY_IDX)NULL) {         
	if (max_strlen > 0 && seg_length < strlen) {
	  /* We need to split the string constant into substrings */
	  // str = (char *) alloca(seg_length + 1);
	  while (strlen > seg_length) {
	    for (stridx = 0; stridx < seg_length; stridx++)
	      str[stridx] = strbase[stridx];
	    str[stridx] = '\0';
	    strbase = &strbase[stridx];
	    strlen -= seg_length;
	    non_empty_length=seg_length-1;
	    while (str[non_empty_length]==' ')
	      --non_empty_length;
	    ++non_empty_length;
	    str[non_empty_length] ='\0';

	    TCON2F_Append_String_Const(sstr, str, non_empty_length);
	    sstr << ','; 
	  }
	}
	
	non_empty_length=strlen-1;
	while (str[non_empty_length]==' ')
	  --non_empty_length;
	++non_empty_length;
	str[non_empty_length] ='\0';
	TCON2F_Append_String_Const(sstr, strbase, non_empty_length);
	
      } else {
	if (max_strlen > 0 && seg_length < strlen) {
	  /* We need to split the string constant into substrings */
	  while (strlen > seg_length) {
	    for (stridx = 0; stridx < seg_length; stridx++)
	      str[stridx] = strbase[stridx];
	    str[stridx] = '\0';
	    strbase = &strbase[stridx];
	    strlen -= seg_length;
	    TCON2F_Append_String_Const(sstr, str, seg_length);
	    sstr << "//"; /* Concatenation */
	  }
	}
	TCON2F_Append_String_Const(sstr, strbase, strlen);
      }
      break;
      
    case MTYPE_I1:
    case MTYPE_I2:
    case MTYPE_I4:
      sstr << Targ_Print("%1d", tvalue);
      break;
      
    case MTYPE_I8:
      /* here should see if the value is big enough to add "_8" *
       * otherwise should not add it,
       * will figure out a range later
       */
      /*         Append_Token_String(sstr, Targ_Print("%1lld_8", tvalue));*/
      sstr << Targ_Print("%1lld", tvalue);
      break;
      
    case MTYPE_U1:
    case MTYPE_U2:
    case MTYPE_U4:
      sstr << Targ_Print("%1u", tvalue);
      break;
      
    case MTYPE_U8:
      /* same thing to do with "MTYPE_I8 */
      /*	 Append_Token_String(sstr, Targ_Print("%1llu_8", tvalue));*/
      sstr << Targ_Print("%1llu", tvalue);
      break;
      
    case MTYPE_F4:
      str = Targ_Print("%.10e", tvalue);
      strbase = Remove_Trailing_Zero_Fraction(str);
      if (str = (char *) strchr(strbase, 'd'))
	*str = 'E';
      sstr << strbase;
      break;
      
    case MTYPE_F8:
      str = Targ_Print("%.20e", tvalue);
      strbase = Remove_Trailing_Zero_Fraction(str);
      if (str = (char *)strchr(strbase, 'E')) /* due to bug in targ_const.h */
	*str = 'D';
      else if (str = (char *)strchr(strbase, 'd'))
	*str = 'D';
      else
	strbase = StrCat(strbase, "D00");
      sstr << strbase;
      
      break;
      
    case MTYPE_FQ:
      str = Targ_Print(NULL, tvalue);
      strbase = Remove_Trailing_Zero_Fraction(str);
      if (str = (char *)strchr(strbase, 'E')) /* due to bug in targ_const.h */
	*str = 'Q';
      else if (str = (char *)strchr(strbase, 'd'))
	*str = 'Q';
      else
	strbase = StrCat(strbase, "Q00");
      sstr << strbase;
      
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
      sstr << "<aTCON>";
      break;
    } /* switch */
  } /* if */

  return sstr.str();

} /* TCON2F_translate */

std::string
TCON2F_translate(TCON tvalue, BOOL is_logical)
{
  return TCON2F_translate(tvalue, is_logical, (TY_IDX)NULL);
} 
