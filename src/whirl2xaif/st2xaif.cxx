// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/st2xaif.cxx,v 1.4 2003/05/16 13:21:22 eraxxon Exp $
// -*-C++-*-

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
 * Description:
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

#include "Open64BasicTypes.h"

//*************************** User Include Files ****************************

#include "whirl2f_common.h"
#include "PUinfo.h"
#include "tcon2f.h"
#include "wn2xaif.h"
#include "ty2f.h"
#include "st2f.h"
#include "init2f.h"

#include "SymTab.h"

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//************************** Forward Declarations ***************************

/*------- Fwd refs for miscellaneous utilities ------------------------*/
/*---------------------------------------------------------------------*/

static BOOL ST2F_Is_Dummy_Procedure(ST *st) ;
static void ST2F_Declare_Return_Type(xml::ostream& xos,TY_IDX return_ty, 
				     XlationContext& ctxt);

/*------- Handlers for references to and declarations of symbols ------*/
/*---------------------------------------------------------------------*/

static void 
ST2F_ignore(xml::ostream& xos, ST *st, XlationContext& ctxt);

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
ST2F_use_error(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
ST2F_use_var(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
ST2F_use_func(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
ST2F_use_const(xml::ostream& xos, ST *st, XlationContext& ctxt);
static void 
ST2F_use_block(xml::ostream& xos, ST *st, XlationContext& ctxt);

//***************************************************************************

void 
whirl2xaif::xlate_SymbolTables(xml::ostream& xos, SYMTAB_IDX symtab_lvl, 
			       NonScalarSymTab* nonscalarsymtab, 
			       XlationContext& ctxt)
{
  //xlate_SYMTAB(xos, CURRENT_SYMTAB, ctxt);
  xlate_NonScalarSymTab(xos, nonscalarsymtab, ctxt);
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
    
#if 0 //FIXME
    const char* stname = ST_name(st);
    
    BOOL dop = (ST_sclass(st) != SCLASS_FORMAL
		&& ST_sclass(st) != SCLASS_FORMAL_REF);
    dop &= ((ST_sym_class(st) == CLASS_VAR  && !ST_is_namelist(st)) 
	    || (ST_sym_class(st) == CLASS_FUNC));

    if ((ST_sclass(stbase) == SCLASS_DGLOBAL) && ST_is_initialized(st)
	&& !Stab_No_Linkage(st) 
	&& (!TY_Is_Structured(ST_type(st)) 
	    || Stab_Is_Equivalence_Block(st))) {
      INITO_IDX inito = Find_INITO_For_Symbol(st);
      if (inito != (INITO_IDX) 0) {
	INITO2F_translate(xos, inito); // FIXME: was Data_Stmt_Tokens
	xos << std::endl;	
	return;
      }
    } else if (dop) {
      TranslateSTDecl(xos, st, ctxt);
      return;
    } 
#endif
    
    TranslateSTDecl(xos, st, ctxt);
  }
  
private:
  xml::ostream&   xos;
  SYMTAB_IDX      symtab;
  XlationContext& ctxt;
  
};

// FIXME

// WHIRL symbol table types primer.  See the WHIRL symbol table
//   documentation for more info.
//
//   SYMTAB: not actually a type, but refers to all of the tables at a
//   particular level/scope.  Besides a global scope, there is a local
//   scope for each PU.  Each scope contains a number of different
//   tables, some of which are common to all levels (e.g. ST_TAB) and
//   some of which are specific to global (e.g. PU_TAB) or local
//   levels (e.g. LABEL_TAB).
// 
//   SYMTAB_IDX: The type of an index into the scope table
//   'Scope_tab[]'.  The global scope is always at the index
//   'GLOBAL_SYMTAB'; the scope for the current lexical PU is at index
//   'CURRENT_SYMTAB'.  (This is set by the whirl reader function
//   'Read_Local_Info()'.)
//
//   ST_TAB: The type of the symbol table proper, a table that appears
//   at all lexical levels.
//
//   ST_IDX: An index into any ST_TAB within the 'Scope_tab[]'.  It is
//   two part bit field that contains an index into the ST_TAB at a
//   certain lexical level.
//
//   ST: The type of a ST_TAB entry.
//
//   Scope_tab[]: an array of SCOPE's, indexed by SYMTAB_IDX, the
//   lexical level.  A SCOPE contains pointers to all the tables for a
//   lexical level, including a ST_TAB.
//
//   St_Table[]: Essentially a class wrapper for 'Scope_tab[]' with
//   member functions for indexing both the 'Scope_tab[]' and the
//   appropriate ST_TAB with a ST_IDX. (TABLE_INDEXED_BY_LEVEL8_AND_INDEX24)
//

// FIXME: move to xlateSYMTAB.cxx
// xlate_SYMTAB: Translate a WHIRL SYMTAB (a collection of tables) to
// an XAIF symbol table.  'symtab_lvl' is an index (lexical level) in
// the current 'Scope_tab[]'.
void 
whirl2xaif::xlate_SYMTAB(xml::ostream& xos, SYMTAB_IDX symtab_lvl,
			 XlationContext& ctxt)
{
  xos << BegElem("xaif:SymbolTable") << EndAttr;

  // Note: 'For_all' applies the object's 'operator()' to every entry
  // of the respective table.
  // ST_TAB: Symbol Table: 
  For_all(St_Table, symtab_lvl, xlate_ST_TAB(xos, symtab_lvl, ctxt));
  
  xos << EndElem;
}

void
whirl2xaif::xlate_NonScalarSymTab(xml::ostream& xos, NonScalarSymTab* symtab, 
				  XlationContext& ctxt)
{
  xos << BegElem("xaif:SymbolTable") << Attr("id", symtab->GetName());
  
  xos << BegElem("xaif:Property") << Attr("id", ctxt.GetNewVId()) 
      << Attr("name", "kind") << Attr("value", "nonscalar_stab") << EndElem;
  
  for (NonScalarSymTabIterator it(*symtab); it.IsValid(); ++it) {
    WN* wn = it.CurrentSrc();
    NonScalarSym* sym = it.CurrentTarg();
    xos << BegElem("xaif:Symbol") << Attr("id", sym->GetName()) << EndElem;
  }
  
  xos << EndElem << std::endl;
}


// FIXME: REMOVE
static void
WN2F_Append_Symtab_Consts(xml::ostream& xos, SYMTAB_IDX symtab)
{
#if 0 // note: defined out in original code
  /* Declare static variables for symbolic constants */
  FOR_ALL_CONSTANTS(st, const_idx) 
  {
    /* TODO: Full support for sym_consts */
    if (tokens != NULL) {
      xos << std::endl;
      TranslateSTDecl(xos, st, ctxt);
    }
  }
#endif
}

// FIXME: REMOVE: 
static void
WN2F_Append_Symtab_Vars(xml::ostream& xos, SYMTAB_IDX symtab)
{
  /* Declare identifiers from the new symbol table, provided they
   * represent functions or variables that are either common or
   * that have been referenced/used.
   */
  XlationContext ctxt;
  For_all(St_Table, symtab, xlate_ST_TAB(xos, symtab, ctxt));
}


//***************************************************************************

typedef void (*XlateSTHandlerFunc)(xml::ostream&, ST*, XlationContext&);

static const XlateSTHandlerFunc TranslateSTDecl_HandlerTable[CLASS_COUNT] =
{
  &ST2F_ignore,      /* CLASS_UNK    == 0x00 */
  &xlate_STDecl_VAR,    /* CLASS_VAR    == 0x01 */
  &xlate_STDecl_FUNC,   /* CLASS_FUNC   == 0x02 */
  &xlate_STDecl_CONST,  /* CLASS_CONST  == 0x03 */
  &xlate_STDecl_PREG,   /* CLASS_PREG   == 0x04 */
  &xlate_STDecl_BLOCK,  /* CLASS_BLOCK  == 0x05 */
  &xlate_STDecl_NAME,   /* CLASS_NAME   == 0x06 */
  &xlate_STDecl_error,  /* CLASS_MODULE == 0x07 */
  &xlate_STDecl_TYPE,   /* CLASS_TYPE   == 0x08 */
};

static const XlateSTHandlerFunc TranslateSTUse_HandlerTable[CLASS_COUNT] =
{
  &ST2F_ignore,      /* CLASS_UNK   == 0x00 */
  &ST2F_use_var,     /* CLASS_VAR   == 0x01 */
  &ST2F_use_func,    /* CLASS_FUNC  == 0x02 */
  &ST2F_use_const,   /* CLASS_CONST == 0x03 */
  &ST2F_use_error,   /* CLASS_PREG  == 0x04 */
  &ST2F_use_block,   /* CLASS_BLOCK == 0x05 */
  &ST2F_use_error    /* CLASS_NAME  == 0x06 */
};

//***************************************************************************

void 
whirl2xaif::TranslateSTDecl(xml::ostream& xos, ST* st, XlationContext& ctxt)
{ 
  TranslateSTDecl_HandlerTable[ST_sym_class(st)](xos, st, ctxt);
} 

void 
whirl2xaif::TranslateSTUse(xml::ostream& xos, ST* st, XlationContext& ctxt)
{ 
  TranslateSTUse_HandlerTable[ST_sym_class(st)](xos, st, ctxt);
}


/*----------- hidden routines to handle ST declarations ---------------*/
/*---------------------------------------------------------------------*/
static void
ST2F_Define_Preg(const char *name, TY_IDX ty)
{
#if 0//FIXME
  /* Declare a preg of the given type, name and offset as a local
   * (register) variable in the current context.
   */
  xml::ostream decl_tokens = New_Token_Buffer();
  UINT         current_indent = Current_Indentation();
  
  Append_F77_Indented_Newline(PUinfo_local_decls, 1, NULL/*label*/);
  Append_Token_String(decl_tokens, name);
  TY2F_translate(decl_tokens, ty);
  Append_And_Reclaim_Token_List(PUinfo_local_decls, &decl_tokens);
  Set_Current_Indentation(current_indent);
#endif
}


static void 
ST2F_ignore(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
}

static void 
xlate_STDecl_error(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(FALSE, (DIAG_W2F_UNEXPECTED_SYMCLASS,
			   ST_sym_class(st), "xlate_STDecl_error"));
}

static void 
xlate_STDecl_VAR(xml::ostream& xos, ST *st, XlationContext& ctxt)
{  
  ASSERT_DBG_FATAL(ST_sym_class(st) == CLASS_VAR, 
		   (DIAG_W2F_UNEXPECTED_SYMCLASS, 
		    ST_sym_class(st), "xlate_STDecl_VAR"));
  
  if (Current_scope > GLOBAL_SYMTAB) {
    ASSERT_DBG_FATAL(!PUINFO_RETURN_TO_PARAM || st != PUINFO_RETURN_PARAM, 
		     (DIAG_W2F_DECLARE_RETURN_PARAM, "xlate_STDecl_VAR"));
    // FIXME: we don't need this
  }

  const char* st_name = W2CF_Symtab_Nameof_St(st);
  ST* base = ST_base(st);
  TY_IDX ty = ST_type(st);
  
  xos << Comment(st_name);
  xos << BegElem("xaif:Symbol") << Attr("symbol_id", (UINT)ST_index(st)) 
      << Attr("kind", "variable")
      << Attr("type", "***")
      << Attr("shape", "***") << EndElem;

  //FIXME: TY2F_translate(xos, ty, ctxt); // Add type specs

#if 0 // FIXME
  /* Declare the variable */
  
  /* don't output ST_sclass(st) == SCLASS_DGLOBAL as common block      */
  /* keep only st sclass is SCLASS_COMMON as common block output June  */
  if (Stab_Is_Common_Block(st)) { //if (ST_sclass(st) == SCLASS_COMMON) 
    TY2F_Translate_Common(xos, st_name, ST_type(st)); // Declare common block
  } else if (Stab_Is_Equivalence_Block(st)) {
    if (ST_is_return_var(st))
      TY2F_Translate_Equivalence(xos, ST_type(st), TRUE /*alt return point*/);
    else
      TY2F_Translate_Equivalence(xos, ST_type(st), FALSE /*regular equiv.*/);

  } else if (TY_Is_Pointer(ty) && !TY_is_f90_pointer(ty) 
	     && ST_sclass(st) != SCLASS_FORMAL) {

    const char* pointee_name = W2CF_Symtab_Nameof_St_Pointee(st);

    /* Declare pointee with the name specified in the symbol table */
    xos << pointee_name;
    if (TY_ptr_as_array(Ty_Table[ty]))
      TY2F_translate(xos, Stab_Array_Of(TY_pointed(ty), 0/*size*/));
    else
      TY2F_translate(xos, TY_pointed(ty));

    /* Declare the pointer object */
    xos << "POINTER(" << st_name << ',' << pointee_name << ')' << std::endl;

  } else if (ST_sclass(st) == SCLASS_FORMAL && !ST_is_value_parm(st)) {
    /* ie, regular f77 dummy argument, expect pointer TY     */
    /* To counteract the Fortran call-by-reference semantics */
    ASSERT_DBG_FATAL(TY_Is_Pointer(ty), 
		     (DIAG_W2F_UNEXPECTED_TYPE_KIND, 
		      TY_kind(ty), "xlate_STDecl_VAR"));
    if (TY_kind(TY_pointed(ST_type(st))) == KIND_FUNCTION) {
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
    TYLIST tylist_idx = TY_tylist(TY_pointed(ST_type(st)));
    TY_IDX rt = TY_IDX_ZERO;
    if (tylist_idx != (TYLIST) 0)
      rt = TYLIST_type(Tylist_Table[tylist_idx]);
    
    ST2F_Declare_Return_Type(xos, rt, ctxt);
    
  } else {
    TY2F_translate(xos, ST_type(st)); // Declare as specified in symbol table
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
      && (!TY_Is_Structured(ST_type(st)) || Stab_Is_Common_Block(st)
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
  ASSERT_DBG_FATAL(ST_sym_class(st)==CLASS_FUNC,
		   (DIAG_W2F_UNEXPECTED_SYMCLASS, 
		    ST_sym_class(st), "xlate_STDecl_FUNC"));

  const char* funcnm = W2CF_Symtab_Nameof_St(st);
  xos << Comment(funcnm);
  xos << BegElem("xaif:Symbol")  << Attr("symbol_id", (UINT)ST_index(st)) 
      << Attr("kind", "subroutine") << Attr("type", "void") << EndElem;

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
  //xos << BegComment << "preg id=" << (UINT)ST_index(st) << EndComment;
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
  ASSERT_DBG_FATAL(ST_sym_class(st)==CLASS_TYPE, 
		   (DIAG_W2F_UNEXPECTED_SYMCLASS, 
		    ST_sym_class(st), "xlate_STDecl_TYPE"));

  const char  *st_name = W2CF_Symtab_Nameof_St(st);
  TY_IDX       ty_rt = ST_type(st);

  if (Current_scope > GLOBAL_SYMTAB) 
    ASSERT_DBG_FATAL(!PUINFO_RETURN_TO_PARAM || st != PUINFO_RETURN_PARAM, 
		     (DIAG_W2F_DECLARE_RETURN_PARAM, "xlate_STDecl_TYPE"));
 
#if 0 // FIXME 
  xos << BegComment << "type id=" << (UINT)ST_index(st) << EndComment; 
  TY2F_translate(xos, ST_type(st), 1, ctxt);
#endif
}

/*---------------- hidden routines to handle ST uses ------------------*/
/*---------------------------------------------------------------------*/

static void 
ST2F_use_error(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(FALSE, (DIAG_W2F_UNEXPECTED_SYMCLASS,
			   ST_sym_class(st), "ST2F_use_error"));
}

static void 
ST2F_use_var(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(ST_sym_class(st)==CLASS_VAR, 
		   (DIAG_W2F_UNEXPECTED_SYMCLASS, 
		    ST_sym_class(st), "ST2F_use_var"));

  StabToScopeIdMap& map = ctxt.GetStabToScopeIdMap();

  TY_IDX return_ty = PUINFO_RETURN_TY; // FIXME

  /* Note that we do not trust the ST_is_return_var() flag,
   * unless the return_ty is non-void.  This is due to purple,
   * which may change a function into a subroutine.
   */
  if ((return_ty != (TY_IDX) 0 && TY_kind(return_ty) == KIND_SCALAR 
       && ST_is_return_var(st)) 
      || (PUINFO_RETURN_TO_PARAM && st == PUINFO_RETURN_PARAM)) {
    /* If we have a reference to the implicit return-variable, then
     * refer to the function return value.
     */
    xos << PUINFO_FUNC_NAME;

  } else if (Stab_Is_Based_At_Common_Or_Equivalence(st)) {
    /* Reference the corresponding field in the common block (we do this
     * only to ensure that the name referenced matches the one used for
     * the member of the common-block at the place of declaration).  Note
     * that will full splitting, the original common block can be found
     * at ST_full(ST_base(st)).
     */
    // XlationContext ctxt;  // FIXME
    WN2F_Offset_Symref(xos, ST_base(st) /*base-symbol*/,
		       Stab_Pointer_To(ST_type(ST_base(st))), /*base-type*/
		       ST_type(st) /*object-type*/, 
		       ST_ofst(st) /*object-ofst*/, ctxt);
  } else {
    // FIXME: abstract
    ST_TAB* sttab = Scope_tab[ST_level(st)].st_tab;
    UINT scopeid = map.Find(sttab);
    ASSERT_FATAL(scopeid != 0, (DIAG_UNIMPLEMENTED, 0, "ST2F_use_var"));

    xos << BegComment << "sym = " << W2CF_Symtab_Nameof_St(st) << EndComment;
    xos << BegElem("xaif:SymbolReference") 
	<< Attr("vertex_id", ctxt.GetNewVId())
	<< Attr("scope_id", scopeid)
	<< Attr("symbol_id", (UINT)ST_index(st)) << EndElem;
  }
}


static void 
ST2F_use_func(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(ST_sym_class(st)==CLASS_FUNC, 
		   (DIAG_W2F_UNEXPECTED_SYMCLASS, 
		    ST_sym_class(st), "ST2F_use_func"));
  
  xos << BegElem("***use_func") << Attr("id", ctxt.GetNewVId())
      << Attr("_type", -1) << Attr("value", W2CF_Symtab_Nameof_St(st)) 
      << EndElem;
  
  //REMOVE Set_BE_ST_w2fc_referenced(st);
}

static void 
ST2F_use_const(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(ST_sym_class(st)==CLASS_CONST,
		   (DIAG_W2F_UNEXPECTED_SYMCLASS,
		    ST_sym_class(st), "ST2F_use_const"));
  
  // A CLASS_CONST symbol never has a name, so just emit the value.
  // FIXME
  TY_IDX ty_idx = ST_type(st);
  TY& ty = Ty_Table[ty_idx];
  
  std::string val;
  if (TY_mtype(ty) == MTYPE_STR && TY_align(ty_idx) > 1) {
    val = TCON2F_hollerith(STC_val(st)); // must be a hollerith constant
  } else {
    val = TCON2F_translate(STC_val(st), TY_is_logical(ty));
  }
  
  xos << BegElem("***use_const") << Attr("id", ctxt.GetNewVId()) 
      << Attr("_type", -1) << Attr("value", val) << EndElem;
}


static void 
ST2F_use_block(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  /* with f90 at -O2, CLASS_BLOCK can appear on LDAs etc. in IO */
  /* put out something, so whirlbrowser doesn't fall over       */
  ASSERT_DBG_FATAL(ST_sym_class(st)==CLASS_BLOCK, 
		   (DIAG_W2F_UNEXPECTED_SYMCLASS, 
		    ST_sym_class(st), "ST2F_use_block"));
  
  xos << BegElem("***use_block") << Attr("id", ctxt.GetNewVId()) 
      << Attr("_type", -1) << Attr("value", ST_name(st)) << EndElem;
} 

/*------------------------ exported routines --------------------------*/
/*---------------------------------------------------------------------*/


void 
ST2F_deref_translate(xml::ostream& xos, ST *st, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(ST_sym_class(st)==CLASS_VAR && 
		   TY_Is_Pointer(ST_type(st)) &&
		   !Stab_Is_Based_At_Common_Or_Equivalence(st), 
		   (DIAG_W2F_UNEXPECTED_SYMCLASS, 
		    ST_sym_class(st), "ST2F_deref_translate"));
  
  /* Consider this a reference to the pointer value */
  xos << "{deref***} " << W2CF_Symtab_Nameof_St_Pointee(st);
  //REMOVE Set_BE_ST_w2fc_referenced(st);
}


void
whirl2xaif::xlate_Params(xml::ostream& xos, WN* wn, ST* st, ST** params, 
			 INT32 num_params, XlationContext& ctxt)
{
  StabToScopeIdMap& map = ctxt.GetStabToScopeIdMap();
  TY_IDX funtype = ST_pu_type(st);
  TY_IDX return_ty = Func_Return_Type(funtype);
  
  // Parameter name-list. Skip any implicit "length" parameters
  // associated with character strings.  Such implicit parameters
  // should be at the end of the parameter list. FIXME
  
  xos << BegElem("xaif:ArgumentList");

  INT first_param = ST2F_FIRST_PARAM_IDX(funtype);
  INT implicit_params = 0;
  UINT position = 1;
  for (INT param = first_param; 
       param < (num_params - implicit_params); 
       param++) {

    if (!ST_is_return_var(params[param])) {
      // FIXME: abstract (SymbolReference)
      ST* st = params[param];
      ST_TAB* sttab = Scope_tab[ST_level(st)].st_tab;
      UINT scopeid = map.Find(sttab);
      ASSERT_FATAL(scopeid != 0, (DIAG_UNIMPLEMENTED, 0, "xlate_Params"));
      
      xos << BegComment << "sym = " << W2CF_Symtab_Nameof_St(st) << EndComment;
      xos << BegElem("xaif:ArgumentSymbolReference") 
	  << Attr("position", position) 
	  << Attr("scope_id", scopeid)
	  << Attr("symbol_id", (UINT)ST_index(st)) << EndElem;
      
      position++;
    }
    
    if (STAB_PARAM_HAS_IMPLICIT_LENGTH(params[param])) {
      implicit_params++;
      
      /* FIXME: is function returning character_TY? if length follows */
      /* address - skip over it, but account for ',' in arg list */
      if ( ((param == first_param) && (params[param+1] != NULL))
	   && (ST_is_value_parm(params[param]) 
	       && ST_is_value_parm(params[param+1]))
	   && (return_ty != (TY_IDX)0 && TY_kind(return_ty) == KIND_VOID) ) {
	param++;
	params[param] = NULL; 
	implicit_params--;
      }
    }

  }
  
  xos << EndElem /* xaif:ArgumentList */;
}

void
ST2F_func_header(xml::ostream& xos, WN* wn,
		 ST* st,           /* Function ST entry     */
		 ST** params,      /* Array of  parameters  */
		 INT32 num_params, /* # of parms in array   */
		 BOOL is_altentry, /* Alternate entry point */
		 XlationContext& ctxt)
{
  /* Emit the header for a function definition or an alternate entry
   * point.  Note that the resultant token buffer will not have 
   * appended a newline after the function header.
   */
  INT    param, first_param, implicit_params = 0;
  TY_IDX funtype = ST_pu_type(st);
  TY_IDX return_ty;
  ST *rslt = NULL;
  BOOL needcom = 1;
  BOOL has_result = 0;
  const char * func_name = W2CF_Symtab_Nameof_St(st);
  
  ASSERT_DBG_FATAL(TY_kind(funtype) == KIND_FUNCTION,
		   (DIAG_W2F_UNEXPECTED_SYMBOL, "ST2F_func_header"));
  
  return_ty = Func_Return_Type(funtype);

  // Function keyword (ENTRY, PROGRAM, FUNCTION, SUBROUTINE)
  if (PU_is_mainpu(Get_Current_PU())) {
    xos << "PROGRAM ";
  } else if (return_ty != (TY_IDX) 0 && TY_kind(return_ty) != KIND_VOID) {
    if (is_altentry) {
      xos << "ENTRY ";
    } else {

      xos << "function ";
      if (PU_recursive(Get_Current_PU())) {
	xos << "RECURSIVE ";
      }
      
      /* Note that we cannot have functions returning pointer types
       * in Fortran, so we use the corresponding integral type
       * instead.
       */      
      if (has_result)
	has_result = 0; 
      else {
	if (TY_Is_Pointer(return_ty)) {
	  TY2F_translate(xos, Stab_Mtype_To_Ty(TY_mtype(return_ty)), ctxt);
	} else { 
	  if (TY_kind(return_ty)==KIND_ARRAY)  {
	    if (TY_is_character(TY_AR_etype(return_ty))) { 
	      ; 
	    } else { 
	      TY2F_translate(xos, TY_AR_etype(return_ty), ctxt); 
	    }
	  } else {
	    TY2F_translate(xos, return_ty, ctxt);
	  }
	}
      }
    }
  } else { /* subroutine */
    if (is_altentry) {
      xos << "ENTRY ";
    } else {
      if (ST_is_in_module(st) && !PU_is_nested_func(Pu_Table[ST_pu(st)])) {
	xos << "MODULE ";
      } else {
	if (ST_is_block_data(st)) {
	  xos << "BLOCK DATA ";
	} else {
	  xos << "SUBROUTINE ";
	}
      }
    }
  }
  
  // Function name
  xos << func_name;
  
  // Parameter name-list. Skip any implicit "length" parameters
  // associated with character strings.  Such implicit parameters
  // should be at the end of the parameter list.
  first_param = ST2F_FIRST_PARAM_IDX(funtype);
  if (params[first_param] != NULL) {
    xos << '(';
    for (param = first_param; 
	 param < num_params - implicit_params; 
	 param++) {
      if (!ST_is_return_var(params[param]))  
	xos << W2CF_Symtab_Nameof_St(params[param]);
      else {
	rslt = params[param];
	needcom = 0;
      }
      
      if (STAB_PARAM_HAS_IMPLICIT_LENGTH(params[param])) {
	implicit_params++;
	
	/* is function returning character_TY? if length follows    */
	/* address - skip over it, but account for ',' in arg list  */
	
	if ((param == first_param) && (params[param+1] != NULL)) {
	  if (ST_is_value_parm(params[param]) 
	      && ST_is_value_parm(params[param+1])) {
	    if (return_ty != (TY_IDX) 0 
		&& TY_kind(return_ty) == KIND_VOID ||TRUE) {
	      param ++ ;
	      params[param] = NULL; 
	      implicit_params--;
	    }
	  }
	}
      }
      
      if (param+implicit_params+1 < num_params && needcom)
	xos << ',';
      needcom = 1;
    }
    xos << ')';
  } else if (!PU_is_mainpu(Get_Current_PU()) &&
	     !ST_is_in_module(st) &&
	     !ST_is_block_data(st) ||           // module&&block
	     TY_kind(return_ty) != KIND_VOID) { // data cannot have "()" 
    
    // Use the "()" notation for "no parameters", except for
    // the main program definition.
    xos << "()";
  }
  
  /* need to see if the result variable has same name with the function's 
   * name,if it does,don't declare the result variable
   */  
  if (rslt !=NULL && strcasecmp(W2CF_Symtab_Nameof_St(rslt), func_name)) { 
    has_result = 1;
    xos << " result(" << W2CF_Symtab_Nameof_St(rslt) << ')';
  }
  
  xos << std::endl;


  // for use statement lookup the symbal table to get the modules name
  WN* fbody = WN_func_body(wn);
  WN* stmt = WN_first(fbody);
  int k;
  const char *st_name;
  const char *st_name1;
  
  while (stmt != NULL) {
    if (WN_operator(stmt) == OPR_USE) {
      st_name = W2CF_Symtab_Nameof_St(WN_st(stmt));
      xos << "use " << st_name;
      if (WN_rtype(stmt) == 1)
        xos << ",only:";
      else if (WN_kid_count(stmt)>0)
	xos << ",";
      
      for(k=0;k< WN_kid_count(stmt);k=k+2 ) {
	st_name = W2CF_Symtab_Nameof_St(WN_st(WN_kid(stmt,k)));
	st_name1= W2CF_Symtab_Nameof_St(WN_st(WN_kid(stmt,k+1)));

        if (k==0) { ; }
        else {  xos << ","; }

        if (strcmp(st_name,st_name1)) {
          xos << st_name << "=>" << st_name1;
        } else {
          xos << st_name;
	}
	
      }
      xos << std::endl;
    }
    stmt = WN_next(stmt);
  } 

  xos << std::endl;
  
#if 0 //FIXME
  // Emit parameter declarations
  if (!is_altentry) {
    xos << "IMPLICIT NONE" << std::endl;

    for (param = first_param; param < num_params - implicit_params; param++) {
      if (params[param] != NULL) { 
	// && TY_kind(ST_type(params[param])) != == KIND_POINTER 
	
	if (strcasecmp(W2CF_Symtab_Nameof_St(params[param]), func_name)) {
	  
	  if (ST_is_optional_argument(params[param])) {
	    xos << "OPTIONAL " << W2CF_Symtab_Nameof_St(params[param]);
	    xos << std::endl;
	  }
	  if (ST_is_intent_in_argument(params[param])) {
	    xos << "INTENT(IN) " << W2CF_Symtab_Nameof_St(params[param]);
	    xos << std::endl;
	  }
	  if (ST_is_intent_out_argument(params[param])) {
	    xos << "INTENT(OUT) " << W2CF_Symtab_Nameof_St(params[param]);
	    xos << std::endl;
	  }

	  TranslateSTDecl(xos, params[param], ctxt);
	  //xos << std::endl;
	} else if (!strcasecmp(W2CF_Symtab_Nameof_St(rslt), func_name)) {
	  TranslateSTDecl(xos, params[param], ctxt);
	  //xos << std::endl;
	}
      }
    }    
  }
#endif

} /* ST2F_func_header */

void
ST2F_Use_Preg(xml::ostream& xos,
	      TY_IDX       preg_ty,
	      PREG_IDX     preg_idx)
{
  /* Append the name of the preg to the token-list and declare the
   * preg in the current PU context unless it is already declared.
   */
  const char *preg_name;
  
  preg_ty = PUinfo_Preg_Type(preg_ty, preg_idx);
  preg_name = W2CF_Symtab_Nameof_Preg(preg_ty, preg_idx);
  
  /* Declare the preg, if it has not already been declared */
  if (!PUinfo_Is_Preg_Declared(preg_ty, preg_idx)) {
    ST2F_Define_Preg(preg_name, preg_ty);
    PUinfo_Set_Preg_Declared(preg_ty, preg_idx);
  }
  
  xos << preg_name;
} /* ST2F_Use_Preg */

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
   Append_Token_String(tmp_tokens, W2CF_Symtab_Nameof_Tempvar(idx)); /* name */
   TY2F_translate(tmp_tokens, ty);                                   /* type */
  if (ST_is_in_module(Scope_tab[Current_scope].st) &&
      !PU_is_nested_func(Pu_Table[ST_pu(Scope_tab[Current_scope].st)]))
     {
       Append_F77_Indented_Newline(tmp_tokens, 1, NULL/*label*/);
       Append_Token_String(tmp_tokens,"PRIVATE ");
       Append_Token_String(tmp_tokens, W2CF_Symtab_Nameof_Tempvar(idx));
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

  if (ST_sclass(st) == SCLASS_FORMAL && ST_is_value_parm(st))
  {
      TY_IDX ty = ST_type(st);

      if (TY_kind(ty) == KIND_POINTER)
	if (TY_kind(TY_pointed(ty)) == KIND_FUNCTION)
	  dummy = TRUE ;
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
