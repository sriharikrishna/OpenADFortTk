// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/st2xaif.h,v 1.13 2004/06/03 01:37:57 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/st2xaif.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/st2f.h
//
//***************************************************************************

#ifndef st2f_INCLUDED
#define st2f_INCLUDED
/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *    TranslateSTUse:
 *       Translate a variable reference.
 *
 *    TranslateSTDecl:
 *       Translate a variable declaration
 *
 *    ST2F_deref_translate:
 *       Translate a pointer variable to its dereferenced version.
 *
 *    ST2F_Declare_Tempvar:
 *       Declares a tempvar with the given index in the local scope.
 *
 *    ST2F_FIRST_PARAM_IDX:
 *       An index to the first parameter to be explicitly declared in
 *       Fortran, given the type of the function and the type of the 
 *       first (implicit or explicit) argument.
 *
 * ====================================================================
 * ====================================================================
 */

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include <lib/support/xmlostream.h>
#include "XlationContext.h"

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// 
//***************************************************************************

namespace whirl2xaif {

  extern void 
  xlate_SymbolTables(xml::ostream& xos, SYMTAB_IDX symtab_lvl, 
		     ScalarizedRefTab_W2X* nonscalarsymtab, 
		     XlationContext& ctxt);
  
  extern void 
  xlate_SYMTAB(xml::ostream& xos, SYMTAB_IDX symtab_lvl, 
	       XlationContext& ctxt);
  
  extern void 
  xlate_ScalarizedRefTab(xml::ostream& xos, ScalarizedRefTab_W2X* symtab, 
			XlationContext& ctxt);
  
  extern void 
  TranslateSTDecl(xml::ostream& xos, ST* st, XlationContext& ctxt);
  
  extern void 
  TranslateSTUse(xml::ostream& xos, ST* st, XlationContext& ctxt);
  
}; /* namespace whirl2xaif */


#include <string>

// FIXME/REMOVE
extern std::string 
TCON2F_hollerith(TCON tvalue);

extern std::string 
TCON2F_translate(TCON tvalue, BOOL is_logical, TY_IDX object_ty);

extern std::string 
TCON2F_translate(TCON tvalue, BOOL is_logical);


extern void 
ST2F_deref_translate(xml::ostream& xos, ST* st, XlationContext& ctxt);

extern void 
ST2F_Declare_Tempvar(TY_IDX ty, UINT idx);

//-------------------------------------

// FIXME: see: wn_attr.h WN_Call_First_Arg_Idx
#define ST2F_FIRST_PARAM_IDX(funtype) \
   (Func_Return_To_Param(funtype)? \
    (Func_Return_Character(funtype)? 2 : 1) : 0)

#endif /* st2f_INCLUDED */

