// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/whirl2f_common.cxx,v 1.4 2004/02/17 20:44:51 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/whirl2f_common.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/whirl2f_common.cxx
//
//***************************************************************************

#include <ctype.h>
#include "whirl2f_common.h"
#include "PUinfo.h"


/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 * This file is to be included in all major translating modules
 * belonging to whirl2f.  It includes all files that these modules
 * will depend on and defines some utilities that are generally
 * useful.
 *
 *    Identifier Naming
 *    -----------------
 *       We provide some utilities for creating identifier names.  For
 *       names that are generated or altered by whirl2f, these utilities
 *       can be used to prepend a reserved whirl2f prefix (e.g. "w2f$").
 *       While this moves names outside of the user's name-space, it
 *       does not prevent prefixed names from being overloaded.
 *
 *       Note that this is all fine and dandy for local names, while
 *       some extra work is required by the caller of these routines
 *       for external names.  An external name ending in '_' should
 *       be converted into a name without the '_', while an external
 *       name not ending in a '_' should be suffixed by a '$'.  This
 *       will be left to the users of the routines provided here, since
 *       we do not know whether or not a name is external in this
 *       module.
 *
 *       WHIRL2F_make_valid_name: If the given name is already a
 *          valid Fortran name, then it is simply returned.  If the name
 *          is NULL, then return NULL.  Otherwise, construct a valid
 *          Fortran identifier by removing invalid characters, thus
 *          returning a non-NULL name.
 *
 * ====================================================================
 * ====================================================================
 */

extern const char * WHIRL2F_make_valid_name(const char *name, BOOL allow_dot);


const char * 
WHIRL2F_make_valid_name(const char *name, BOOL allow_dot )
{
   /* If name==NULL, then return NULL;  otherwise, if a valid name,
    * then keep it unaltered; otherwise, construct a valid name
    * in a new Name_Buf by removing invalid characters (never return
    * NULL for this case)
    */
   const char *return_name = name;
   char       *new_name;
   INT         name_idx;
   
   if (name != NULL)
   {
      /* See if we need to construct a new name. First skip valid
       * characters (alphanumeric, '_', or '$', beginning with
       * an alphabetic or '_' character).
       */
      if (isalpha(name[0]) || name[0] == '_')
      {
	 /* See if there are any invalid characters */
	 for (name_idx = 1;
	      (isalnum(name[name_idx]) || 
	       name[name_idx] == '_'   || 
	       name[name_idx] == '$');
	      name_idx++);
      }
      else /* Incorrect first character */
      {
	 /* Skip to first alphabetic or '_' character */
	 name_idx = 0;
	 while (name[name_idx] != '\0' && 
		!isalpha(name[name_idx]) && name[name_idx] != '_')
	    name += 1;
	 return_name = name;
      }
      
      
      /* Did we find an invalid character? */
      if (name[name_idx] != '\0')
      {
	 /* Need to construct a new name.  This should be relatively rare */
	 new_name = strcpy(Get_Name_Buf_Slot(strlen(name) + 1), name);
	 return_name = new_name;
	 while (*name != '\0')
	 {
	   if ((isalnum(*name)) || 
	       (*name == '_' )  || 
	       (*name == '$' )  || 
	       (*name == '.' && allow_dot))
	   {
	       *new_name++ = *name;
	   }
	   name++;     /* Skip character (may be invalid) */
	 }
	 *new_name = '\0';
      }
   }
   return return_name;
} /* WHIRL2F_make_valid_name */

