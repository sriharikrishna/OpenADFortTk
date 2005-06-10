// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/st2xaif.cxx,v 1.42 2005/06/10 15:59:06 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/st2xaif.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/st2f.cxx
//
//***************************************************************************

/* ====================================================================
 * ====================================================================
 *
 * Revision history:
 *  07-May-95 - Original Version
 *
 * Description: FIXME
 *
 *    See st2f.h for a description of the exported functions and 
 *    variables.  This module translates ST nodes into variable and
 *    function declarations (TranslateSTDecl), and gets the 
 *    lvalue for a variable or function when directly referenced in
 *    an expression (TranslateSTUse).  We provide a special 
 *    interface to deal with pseudo registers (pregs), but some 
 *    symbols must be handled by the context in which they appear,
 *    since this context uniquely determines the reference (e.g. 
 *    labels has label-numbers in the WN tree).
 *
 *    Possibly necessary TODO: sym_consts are only partially
 *    supported at the moment.
 *
 *    Fortran pointers are represented by two declarations, where
 *    one declares the pointer object (which is allocated memory)
 *    and one denotes the pointer dereference which also serves to
 *    specify the type of object to which is pointed:
 *
 *        INTEGER*4 a(12)
 *        POINTER(p, a)
 *
 *    Only "p" occurs in the WHIRL symbol table.  We have to derive
 *    "a" from "p" (with a name derived from "p").  The w2cf_symtab.h
 *    facilities coordinates this for us.
 *
 *    It is crucial that names with external linkage are generated 
 *    with the same name between compilation units.  For this reason
 *    we give file-scope variables precedence in name-ownership (i.e.
 *    they are entered first into the symbol-table).  If, despite this
 *    effort, there are clashes between names with static and external 
 *    linkage, the generated code may not be compilable or correctly
 *    executable.  TODO: Emit warning about this.
 * 
 * ====================================================================
 * ====================================================================
 */

//************************** System Include Files ***************************

#include <ctype.h>
#include <sstream> //FIXME

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "wn2xaif.h"
#include "st2xaif.h"
#include "ty2xaif.h"

#include <lib/support/SymTab.h>

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//************************** Forward Declarations ***************************

/*------- Fwd refs for miscellaneous utilities ------------------------*/
/*---------------------------------------------------------------------*/

static BOOL ST2F_Is_Dummy_Procedure(ST *st) ;
static void ST2F_Declare_Return_Type(xml::ostream& xos,TY_IDX return_ty, 
				     XlationContext& ctxt);

// Symbol declarations and uses

static void 
xlate_ST_ignore(xml::ostream& xos, ST *st, XlationContext& ctxt);

static void 
xlate_STDecl_error(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
xlate_STDecl_VAR(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
xlate_STDecl_FUNC(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
xlate_STDecl_CONST(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
xlate_STDecl_PREG(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
xlate_STDecl_BLOCK(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
xlate_STDecl_NAME(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
xlate_STDecl_TYPE(xml::ostream& xos, ST *st, XlationContext& ctxt);

static void 
xlate_STUse_error(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
xlate_STUse_VAR(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
xlate_STUse_CONST(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
xlate_STUse_BLOCK(xml::ostream& xos, ST *st, XlationContext& ctxt);

//***************************************************************************

#include <alloca.h>
#include <sstream> //FIXME

std::string
TCON2F_hollerith(TCON tvalue)
{
  /* Translates the given Hollerith constant into Fortran representation.
   * A hollerith constant cannot be split into substrings.
   */
  const char *strbase;
  char       *str;
  INT32       strlen;
  
  FORTTK_ASSERT_WARN(TCON_ty(tvalue) == MTYPE_STR,
		     "Unexpected type " << MTYPE_name(TCON_ty(tvalue)));
  
  strlen = Targ_String_Length(tvalue);
  strbase = Targ_String_Address(tvalue);
  str = (char *) alloca(strlen + 16);
  sprintf(str, "%dH%s", strlen, strbase);
  
  return std::string(str);
} /* TCON2F_hollerith */

   
std::string
TCON2F_translate(TCON tvalue, BOOL is_logical, TY_IDX object_ty)
{
  // Note: It would be nice to simply use C++ stream formatting
  // instead of Targ_Print(..), but a TCON is a (complex) union whose
  // interpretation technically depends on the target.

  // Since Targ_Print(..) prints floating points with Fortran
  // exponents (i.e. the exponent of a double is preceeded by 'd'
  // instead of an 'e'), we massage its output.

  // FIXME: for now we use this hack to return a string
  std::ostringstream sstr;
  char* floatstr = NULL;
  
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
      floatstr = Targ_Print("%.10e", tvalue);
      break;
      
    case MTYPE_F8:
      floatstr = Targ_Print("%.20e", tvalue);
      break;
      
    case MTYPE_FQ:
      floatstr = Targ_Print(NULL, tvalue);
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
      FORTTK_DIE("Unexpected type " << MTYPE_name(TCON_ty(tvalue)));
      break;
    }
  }

  if (floatstr) {
    char* exp = NULL;
    if (exp = strchr(floatstr, 'd')) {
      *exp = 'e';
    }
    sstr << floatstr;
  }
  
  return sstr.str();

} /* TCON2F_translate */

std::string
TCON2F_translate(TCON tvalue, BOOL is_logical)
{
  return TCON2F_translate(tvalue, is_logical, (TY_IDX)NULL);
} 


//***************************************************************************

// usage: xlate_SymbolTables(xos, CURRENT_SYMTAB, symtab, ctxt);

void 
whirl2xaif::xlate_SymbolTables(xml::ostream& xos, SYMTAB_IDX symtab_lvl, 
			       ScalarizedRefTab_W2X* nonscalarsymtab, 
			       XlationContext& ctxt)
{
  xos << BegElem("xaif:SymbolTable") << EndAttrs;

  xlate_SYMTAB(xos, symtab_lvl, ctxt);
  xlate_ScalarizedRefTab(xos, nonscalarsymtab, ctxt);
  
  xos << EndElem;
}

void 
whirl2xaif::xlate_ArrayBounds(xml::ostream& xos, 
			      TY_IDX ty_idx, 
			      XlationContext& ctxt) { 
  if (TY_kind(ty_idx) == KIND_ARRAY) {
    if (! TY_is_character(ty_idx)) { 
      bool assumeBoundsAllConst=false;
      for (int i=0; i<TY_AR_ndims(ty_idx); i++) {
	if (TY_AR_const_lbnd(ty_idx,i) && TY_AR_const_ubnd(ty_idx,i)) { 
	  xos << BegElem("xaif:DimensionBounds") 
	      << Attr("lower", TY_AR_lbnd_val(ty_idx,i))
	      << Attr("upper", TY_AR_ubnd_val(ty_idx,i))
	      << EndElem;
	  if (!assumeBoundsAllConst && i==0)
	    assumeBoundsAllConst=true;
	  if (!assumeBoundsAllConst && i>0)
	    FORTTK_DIE("Cannot handle mixed constant and variable array bounds");
	}
	else 
	  if (assumeBoundsAllConst)
	    FORTTK_DIE("Cannot handle mixed constant and variable array bounds");
      }
    }
  } 
} 

// FIXME: move to xlateSYMTAB.cxx
class xlate_ST_TAB {
public:
  xlate_ST_TAB(xml::ostream& xos_, SYMTAB_IDX symtab_, XlationContext& ctxt_) 
    : xos(xos_), symtab(symtab_), ctxt(ctxt_)
  { } 

  // A function object applied to every entry of a ST_TAB
  void operator()(UINT32 idx, ST* st) const 
  { 
    TranslateSTDecl(xos, st, ctxt);
  }
  
private:
  xml::ostream&   xos;
  SYMTAB_IDX      symtab;
  XlationContext& ctxt;  
};


// FIXME: move to xlateSYMTAB.cxx
// xlate_SYMTAB: Translate a WHIRL SYMTAB (a collection of tables) to
// an XAIF symbol table.  'symtab_lvl' is an index (lexical level) in
// the current 'Scope_tab[]'.
void 
whirl2xaif::xlate_SYMTAB(xml::ostream& xos, SYMTAB_IDX symtab_lvl,
			 XlationContext& ctxt)
{
  // 'For_all' applies 'operator()' to every entry of St_Table.
  For_all(St_Table, symtab_lvl, xlate_ST_TAB(xos, symtab_lvl, ctxt));
}

#if 0
void 
whirl2xaif::xlate_PREGTAB(xml::ostream& xos, SYMTAB_IDX symtab_lvl,
			  XlationContext& ctxt)
{
  // 'For_all' applies 'operator()' to every entry of Preg_Table.
  For_all(Preg_Table, symtab_lvl, xlate_PREG_TAB(xos, symtab_lvl, ctxt));
}
#endif


void
whirl2xaif::xlate_ScalarizedRefTab(xml::ostream& xos, 
				   ScalarizedRefTab_W2X* symtab, 
				   XlationContext& ctxt)
{
  if (!symtab) { return; }
  
  for (ScalarizedRefTab_W2X::ScalarizedRefPoolTy::iterator it 
	 = symtab->RefPoolBegin(); 
       it != symtab->RefPoolEnd(); ++it) {
    ScalarizedRef* sym = (*it);
    
    WN* wn = sym->GetWN();
    TY_IDX ty = WN_Tree_Type(wn);
    const char* ty_str = TranslateTYToSymType(ty);
    if (!ty_str) { ty_str = "***"; }
    
    int active = (strcmp(ty_str, "real") == 0 // FIXME: see xlate_STDecl_VAR
		  || strcmp(ty_str, "complex") == 0) ? 1 : 0; 
    
    xos << BegElem("xaif:Symbol") << Attr("symbol_id", sym->GetName()) 
	<< Attr("kind", "variable") << Attr("type", ty_str) 
	<< Attr("shape", "scalar") << WhirlIdAnnot(ctxt.FindWNId(wn))
	<< Attr("active", active) << EndElem;
  }
}


//***************************************************************************

typedef void (*XlateSTHandlerFunc)(xml::ostream&, ST*, XlationContext&);

static const XlateSTHandlerFunc XlateSTDecl_HandlerTable[CLASS_COUNT] =
{
  &xlate_ST_ignore,     /* CLASS_UNK    == 0 */
  &xlate_STDecl_VAR,    /* CLASS_VAR    == 1 */
  &xlate_STDecl_FUNC,   /* CLASS_FUNC   == 2 */
  &xlate_STDecl_CONST,  /* CLASS_CONST  == 3 */
  &xlate_STDecl_PREG,   /* CLASS_PREG   == 4 */
  &xlate_STDecl_BLOCK,  /* CLASS_BLOCK  == 5 */
  &xlate_STDecl_NAME,   /* CLASS_NAME   == 6 */
  &xlate_STDecl_error,  /* CLASS_MODULE == 7 */
  &xlate_STDecl_TYPE,   /* CLASS_TYPE   == 8 */
  &xlate_STDecl_CONST,  /* CLASS_PARAMETER  == 9 */
};

static const XlateSTHandlerFunc XlateSTUse_HandlerTable[CLASS_COUNT] =
{
  &xlate_ST_ignore,     /* CLASS_UNK   == 0 */
  &xlate_STUse_VAR,     /* CLASS_VAR   == 1 */
  &xlate_STUse_error,   /* CLASS_FUNC  == 2 */
  &xlate_STUse_CONST,   /* CLASS_CONST == 3 */
  &xlate_STUse_error,   /* CLASS_PREG  == 4 */
  &xlate_STUse_BLOCK,   /* CLASS_BLOCK == 5 */
  &xlate_STUse_error,   /* CLASS_NAME  == 6 */
  &xlate_STDecl_error,  /* CLASS_MODULE == 7 */
  &xlate_STDecl_error,  /* CLASS_TYPE   == 8 */
  &xlate_STDecl_error,  /* CLASS_PARAMETER  == 9 */
};

//***************************************************************************

void 
whirl2xaif::TranslateSTDecl(xml::ostream& xos, ST* st, XlationContext& ctxt)
{ 
  XlateSTDecl_HandlerTable[ST_sym_class(st)](xos, st, ctxt);
} 

void 
whirl2xaif::TranslateSTUse(xml::ostream& xos, ST* st, XlationContext& ctxt)
{ 
  XlateSTUse_HandlerTable[ST_sym_class(st)](xos, st, ctxt);
}

static void 
xlate_ST_ignore(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
}

static void 
xlate_STDecl_error(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  FORTTK_DIE("Unknown ST_CLASS " << ST_class(st));
}

static void 
xlate_STDecl_VAR(xml::ostream& xos, ST *st, XlationContext& ctxt)
{  
  FORTTK_ASSERT(ST_class(st) == CLASS_VAR, FORTTK_UNEXPECTED_INPUT);

  const char* st_name = ST_name(st);
  ST* base = ST_base(st);
  TY_IDX ty = ST_type(st);
  
  bool translatenow = false;
  if (Stab_Is_Common_Block(st)) {
    TY2F_Translate_Common(xos, st_name, ty); 
  } else if (ST_sclass(st) == SCLASS_FORMAL && !ST_is_value_parm(st)) {
    // A procedure parameter (we expect a pointer TY to counteract the
    // Fortran call-by-reference semantics)
    FORTTK_ASSERT(TY_Is_Pointer(ty), "Unexpected type " << TY_kind(ty));
    
    TY_IDX base_ty = TY_pointed(ty);
    if (TY_Is_Pointer(base_ty) && TY_ptr_as_array(Ty_Table[base_ty])) {
      /* FIXME: Handle ptr as array parameters */ 
      ty = Stab_Array_Of(TY_pointed(base_ty), 0/*size*/);
    } else {
      ty = base_ty;
    }
    translatenow = true;
    
  } else {
    translatenow = true;
  }

  if (translatenow) { // FIXME
    const char* ty_str = TranslateTYToSymType(ty);
    if (!ty_str) { ty_str = "***"; }
    
    const char* shape_str = TranslateTYToSymShape(ty);
    if (!shape_str) { shape_str = "***"; }
#if 0    
    int active = (strcmp(ty_str, "real") == 0 // FIXME: see xlate_STDecl_VAR
		  || strcmp(ty_str, "complex") == 0) ? 1 : 0; 
#endif
    int active = (ctxt.IsActiveSym(st)) ? 1 : 0;
    if (strcmp(ty_str, "integer") == 0) {
      active = false;
      static const char* txt1 = "unactivating the activated symbol '";
      static const char* txt2 = "' of integral type";
      if (CURRENT_SYMTAB == GLOBAL_SYMTAB) {
	FORTTK_MSG(0, "warning: within global scope: " << txt1 << ST_name(st) 
		   << txt2);
      }
      else {
	ST_IDX pu_st = PU_Info_proc_sym(Current_PU_Info);
	FORTTK_MSG(0, "warning: within " << ST_name(pu_st) << ": "
		   << txt1 << ST_name(st) << txt2);
      }
    }

    
    SymId st_id = (SymId)ST_index(st);
    xos << BegElem("xaif:Symbol") << AttrSymId(st)
	<< Attr("kind", "variable") << Attr("type", ty_str)
	<< Attr("shape", shape_str) << SymIdAnnot(st_id)
	<< Attr("active", active) <<  EndAttrs;
    xlate_ArrayBounds(xos, ty, ctxt);
    xos << EndElem;
  }

  //FIXME: TY2F_translate(xos, ty, ctxt); // Add type specs

#if 0 // FIXME
  /* Declare the variable */
  
  if (Stab_Is_Common_Block(st)) {
    TY2F_Translate_Common(xos, st_name, ty); 
  } else if (Stab_Is_Equivalence_Block(st)) {
    if (ST_is_return_var(st))
      TY2F_Translate_Equivalence(xos, ty, TRUE /*alt return point*/);
    else
      TY2F_Translate_Equivalence(xos, ty, FALSE /*regular equiv.*/);
  } else if (TY_Is_Pointer(ty) && !TY_is_f90_pointer(ty) 
	     && ST_sclass(st) != SCLASS_FORMAL) {

    const char* drefName = ST_name(st); // prepend "deref_"
    
    /* Declare pointee with the name specified in the symbol table */
    xos << "deref_" << drefName;
    if (TY_ptr_as_array(Ty_Table[ty]))
      TY2F_translate(xos, Stab_Array_Of(TY_pointed(ty), 0/*size*/));
    else
      TY2F_translate(xos, TY_pointed(ty));

    /* Declare the pointer object */
    xos << "POINTER(" << st_name << ',' << "deref_" << drefName << ')' 
	<< std::endl;

  } else if (ST_sclass(st) == SCLASS_FORMAL && !ST_is_value_parm(st)) {
    /* ie, regular f77 dummy argument, expect pointer TY     */
    /* To counteract the Fortran call-by-reference semantics */
    // a parameter
    FORTTK_ASSERT(TY_Is_Pointer(ty), "Unexpected type " << TY_kind(ty));
    if (TY_kind(TY_pointed(ty)) == KIND_FUNCTION) {
      xos << "EXTERNAL ";
    } else {
      TY_IDX ty1;
      TY_IDX ty2 = TY_pointed(ty);      
      if (TY_Is_Pointer(ty2) && TY_ptr_as_array(Ty_Table[ty2])) {
	/* Handle ptr as array parameters */
	ty1 = Stab_Array_Of(TY_pointed(ty2), 0/*size*/);
      } else {
	ty1 = TY_pointed(ty);
      }
      TY2F_translate(xos, ty1);
    }
    xos << st_name << "-1-" << std::endl;

  } else if (ST2F_Is_Dummy_Procedure(st)) {
    TYLIST tylist_idx = TY_tylist(TY_pointed(ty));
    TY_IDX rt = TY_IDX_ZERO;
    if (tylist_idx != (TYLIST) 0)
      rt = TYLIST_type(Tylist_Table[tylist_idx]);
    
    ST2F_Declare_Return_Type(xos, rt, ctxt);
    
  } else {
    TY2F_translate(xos, ty); // Declare as specified in symbol table
  }

  xos << " " << st_name;
  
  if (ST_is_allocatable(st)) {
    xos << "ALLOCATABLE" << ST_name(st) << std::endl;
  }
  if (ST_is_private(st)) {
    xos << "PRIVATE" << ST_name(st) << std::endl;
  }
  if (ST_is_my_pointer(st)) {
    xos << "POINTER" << ST_name(st) << std::endl;
  }
  if (ST_is_f90_target(st)) {
    xos << "TARGET" << ST_name(st) << std::endl;
  }
  
  /* Save it's value between calls, if so specified, unless it is
   * an equivalence, in which case it is implicitly SAVE.
   */
  if (!Stab_Is_Equivalence_Block(st) &&
      (ST_sclass(st) == SCLASS_FSTATIC || ST_sclass(st) == SCLASS_PSTATIC)) {
    xos << "SAVE" << st_name << std::endl;
  }

  INITO_IDX    inito;
 INITPRO:
  /* Generate a DATA statement for initializers */
  if (ST_is_initialized(st) && !Stab_No_Linkage(st)  
      && (!TY_Is_Structured(ty) || Stab_Is_Common_Block(st)
	  || Stab_Is_Equivalence_Block(st))) {
    inito = Find_INITO_For_Symbol(st);
    if (inito != (INITO_IDX)0)
      INITO2F_translate(xos, inito); // Data_Stmt_Tokens
  }
#endif

}

static void 
xlate_STDecl_FUNC(xml::ostream& xos, ST* st, XlationContext& ctxt)
{
  // This only makes sense for "external" functions in Fortran,
  // while we should not do anything for other functions.
  FORTTK_ASSERT(ST_class(st) == CLASS_FUNC, FORTTK_UNEXPECTED_INPUT);

  SymId st_id = (SymId)ST_index(st);
  xos << BegElem("xaif:Symbol") << AttrSymId(st)
      << Attr("kind", "subroutine") << Attr("type", "void")
      << SymIdAnnot(st_id) << EndElem;

#if 0 // REMOVE
  // Specify the function return type, unless it is void
  TY_IDX return_ty = Func_Return_Type(ST_pu_type(st));
  ST2F_Declare_Return_Type(xos, return_ty, ctxt);  
#endif
}

static void 
xlate_STDecl_CONST(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  //xos << BegComment << "const id=" << (UINT)ST_index(st) << EndComment;
}

static void 
xlate_STDecl_PREG(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  TY_IDX ty = ST_type(st);
  const char* ty_str = TranslateTYToSymType(ty);
  if (!ty_str) { 
    return; // skip [FIXME -- better hope this is not used!]
  }
  
  SymId st_id = (SymId)ST_index(st);
  xos << BegElem("xaif:Symbol") << AttrSymId(st)
      << Attr("kind", "variable") << Attr("type", ty_str)
      << Attr("shape", "scalar") << SymIdAnnot(st_id)
      << Attr("active", 0) << EndElem;
}

static void 
xlate_STDecl_BLOCK(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  //xos << BegComment << "block id=" << (UINT)ST_index(st) << EndComment;
}

static void 
xlate_STDecl_NAME(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  //xos << BegComment << "name id=" << (UINT)ST_index(st) << EndComment;
}

static void 
xlate_STDecl_TYPE(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  FORTTK_ASSERT(ST_class(st) == CLASS_TYPE, FORTTK_UNEXPECTED_INPUT);

  const char  *st_name = ST_name(st);
  TY_IDX       ty_rt = ST_type(st);
 
#if 0 // FIXME 
  xos << BegComment << "type id=" << (UINT)ST_index(st) << EndComment; 
  TY2F_translate(xos, ST_type(st), 1, ctxt);
#endif
}

//***************************************************************************
// 
//***************************************************************************

static void 
xlate_STUse_error(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  FORTTK_DIE("Unknown ST_CLASS " << ST_class(st));
}

static void 
xlate_STUse_VAR(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  FORTTK_ASSERT(ST_class(st) == CLASS_VAR, FORTTK_UNEXPECTED_INPUT);

  // Note: for functions, check that st is a return var using
  //   ST_is_return_var(st)) (cf. whirl2f)

#if 0 // FIXME xlate_SymRef moves from 'base' to 'field' (cannot reciprocate)
  if (Stab_Is_Based_At_Common_Or_Equivalence(st)) {
    /* Reference the corresponding field in the common block (we do this
     * only to ensure that the name referenced matches the one used for
     * the member of the common-block at the place of declaration).  Note
     * that will full splitting, the original common block can be found
     * at ST_full(ST_base(st)).
     */
    xlate_SymRef(xos, ST_base(st) /*base-symbol*/,
		 Stab_Pointer_To(ST_type(ST_base(st))), /*base-type*/
		 ST_type(st) /*object-type*/, 
		 ST_ofst(st) /*object-ofst*/, ctxt);
  }
  //else {
#endif
  
  // FIXME: abstract
  ST_TAB* sttab = Scope_tab[ST_level(st)].st_tab;
  SymTabId scopeid = ctxt.FindSymTabId(sttab);
  
  xos << BegElem("xaif:SymbolReference") 
      << Attr("vertex_id", ctxt.GetNewVId())
      << Attr("scope_id", scopeid) << AttrSymId(st) << EndElem;
}


static void 
xlate_STUse_CONST(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  FORTTK_ASSERT(ST_class(st) == CLASS_CONST, FORTTK_UNEXPECTED_INPUT);
  
  // A CLASS_CONST symbol never has a name, so just emit the value.
  TY_IDX ty_idx = ST_type(st);
  TY& ty = Ty_Table[ty_idx];
  
  std::string val;
  if (TY_mtype(ty) == MTYPE_STR && TY_align(ty_idx) > 1) {
    val = TCON2F_hollerith(STC_val(st)); // must be a hollerith constant
  } else {
    val = TCON2F_translate(STC_val(st), TY_is_logical(ty));
  }
  
  const char* ty_str = TranslateTYToSymType(ty_idx);
  if (!ty_str) { ty_str = "***"; }  

  xos << BegElem("xaif:Constant") << Attr("vertex_id", ctxt.GetNewVId()) 
      << Attr("type", ty_str) << Attr("value", val) << EndElem;
}


static void 
xlate_STUse_BLOCK(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  /* with f90 at -O2, CLASS_BLOCK can appear on LDAs etc. in IO */
  /* put out something, so whirlbrowser doesn't fall over       */
  FORTTK_ASSERT(ST_class(st) == CLASS_BLOCK, FORTTK_UNEXPECTED_INPUT);
  
  xos << BegElem("***use_block") << Attr("id", ctxt.GetNewVId()) 
      << Attr("_type", -1) << Attr("value", ST_name(st)) << EndElem;
} 


//***************************************************************************
// 
//***************************************************************************

/*------------------------ exported routines --------------------------*/

void 
ST2F_deref_translate(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  FORTTK_ASSERT(ST_sym_class(st)==CLASS_VAR && 
		TY_Is_Pointer(ST_type(st)) &&
		!Stab_Is_Based_At_Common_Or_Equivalence(st), 
		FORTTK_UNEXPECTED_INPUT << ST_class(st));
  
  /* reference to the pointer value; cf. W2CF_Symtab_Nameof_St_Pointee */
  xos << "{deref***} " << "deref_" << ST_name(st);
}


void 
ST2F_Declare_Tempvar(TY_IDX ty, UINT idx)
{
#if 0 // FIXME
   xml::ostream& tmp_tokens = New_Token_Buffer();
   UINT         current_indent = 0; //FIXME Current_Indentation();

   Append_F77_Indented_Newline(PUinfo_local_decls, 1, NULL/*label*/);
   if (TY_Is_Pointer(ty))
   {
      /* Assume we never need to dereference the pointer, or else we
       * need to maintain a map from tmp_idx->pointee_idx (new temporary
       * for pointee_idx), so declare this temporary variable to be of
       * an integral type suitable for a pointer value.
       */
      ty = Stab_Mtype_To_Ty(Pointer_Mtype);
   }
   tmp_tokens << "tmp" << idx; /* name */
   TY2F_translate(tmp_tokens, ty);                                   /* type */
  if (ST_is_in_module(Scope_tab[Current_scope].st) &&
      !PU_is_nested_func(Pu_Table[ST_pu(Scope_tab[Current_scope].st)]))
     {
       Append_F77_Indented_Newline(tmp_tokens, 1, NULL/*label*/);
       Append_Token_String(tmp_tokens,"PRIVATE ");
       tmp_tokens << "tmp" << idx;
     }

   Append_And_Reclaim_Token_List(PUinfo_local_decls, &tmp_tokens);
   Set_Current_Indentation(current_indent);
#endif
} /* ST2F_Declare_Tempvar */


static BOOL
ST2F_Is_Dummy_Procedure(ST *st)
{
  /* Does this ST represent a dummy procedure ? */
  BOOL dummy = FALSE;
  if (ST_sclass(st) == SCLASS_FORMAL && ST_is_value_parm(st)) {
    TY_IDX ty = ST_type(st);
    if (TY_kind(ty) == KIND_POINTER
	&& TY_kind(TY_pointed(ty)) == KIND_FUNCTION) {
	dummy = TRUE;
    }
  }
  return dummy;
}


static void
ST2F_Declare_Return_Type(xml::ostream& xos, TY_IDX return_ty, 
			 XlationContext& ctxt)
{
  // The TY represents a dummy procedure or a function return type
  if ( (return_ty != (TY_IDX)0) && (TY_kind(return_ty) != KIND_VOID) ) {
    /* Use integral type for pointer returns */
    if (TY_Is_Pointer(return_ty))
      TY2F_translate(xos, Stab_Mtype_To_Ty(TY_mtype(return_ty)), ctxt);
    else
      TY2F_translate(xos, return_ty, ctxt);
  }
}


// Find and emit any COMMONS that are initialized.
//   For_all(St_Table,GLOBAL_SYMTAB,WN2F_emit_commons(xos));
struct WN2F_emit_commons {
public:
  WN2F_emit_commons(xml::ostream& xos_) : xos(xos_) { }
  
  void operator() (UINT32,  ST* st)
  {
    //XlationContext& ctxt1 = ctxt; // FIXME (bug in gcc 3.0.4 it seems)
    if (ST_sclass(st) == SCLASS_DGLOBAL) {
      if (ST_is_initialized(st))  {
	if (!Has_Base_Block(st) || ST_class(ST_base_idx(st)) == CLASS_BLOCK) {
	  TranslateSTDecl(xos, st, ctxt);
	}
      }
    }
  }

private:
  xml::ostream& xos;
  XlationContext ctxt;//FIXME
};
