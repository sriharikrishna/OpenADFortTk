// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_mem.cxx,v 1.18 2004/02/11 14:44:43 mfagan Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif_mem.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f_load_store.cxx
//
//***************************************************************************

/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *   Translate a WN load/store subtree to Fortran by means of an inorder 
 *   recursive descent traversal of the WHIRL IR.  Note that the routines
 *   handle statements and expressions are in separate source files.
 *   Recursive translation of WN nodes should only use WN2F_Translate()!
 *
 * ====================================================================
 * ====================================================================
 */

//************************** System Include Files ***************************

#include <sstream> //FIXME
#include <cassert> //FIXME

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h> /* Open64 basic types */
#include "pf_cg.h"

//*************************** User Include Files ****************************

#include "wn2xaif_mem.h"
#include "whirl2f_common.h"
#include "PUinfo.h"
#include "wn2xaif.h"
#include "st2xaif.h"
#include "ty2xaif.h"

//************************** Forward Declarations ***************************

using namespace whirl2xaif;
using namespace xml; // for xml::ostream, etc

//************************** Forward Declarations ***************************

static WN2F_STATUS 
DumpVarRefEdge(xml::ostream& xos, UINT eid, UINT srcid, UINT targid);

static void 
WN2F_Block(xml::ostream& xos, ST * st, STAB_OFFSET off, XlationContext& ctxt);

static WN *WN2F_ZeroInt_Ptr = NULL;
static WN *WN2F_OneInt_Ptr = NULL;

#define WN2F_INTCONST_ZERO\
   (WN2F_ZeroInt_Ptr == NULL? WN2F_ZeroInt_Ptr = WN2F_Initiate_ZeroInt() \
                            : WN2F_ZeroInt_Ptr)
#define WN2F_INTCONST_ONE\
   (WN2F_OneInt_Ptr == NULL? WN2F_OneInt_Ptr = WN2F_Initiate_OneInt() \
                            : WN2F_OneInt_Ptr)

static void 
WN2F_Arrsection_Slots(xml::ostream& xos, WN *wn, XlationContext& ctxt, BOOL parens);

static void 
xlate_ArrayIndices(xml::ostream& xos, WN *wn, XlationContext& ctxt);

//***************************************************************************

/*------------------------- Utility Functions ------------------------*/
/*--------------------------------------------------------------------*/

static WN *
WN2F_Initiate_ZeroInt(void)
{
  static char ZeroInt [sizeof (WN)];
  WN       *wn = (WN*) &ZeroInt;
  OPCODE    opcode = OPCODE_make_op(OPR_INTCONST, MTYPE_I4, MTYPE_V);
  
  bzero(wn, sizeof(WN));
  WN_set_opcode(wn, opcode);
  WN_set_kid_count(wn, 0);
  WN_map_id(wn) =  WN_MAP_UNDEFINED;
  WN_const_val(wn) = 0LL;
  return wn;
} /* WN2F_Initiate_ZeroInt */

static WN *
WN2F_Initiate_OneInt(void)
{
  static char OneInt [sizeof (WN)];
  WN       *wn = (WN*) &OneInt;
  OPCODE    opcode = OPCODE_make_op(OPR_INTCONST, MTYPE_I4, MTYPE_V);
  
  bzero(wn, sizeof(WN));
  WN_set_opcode(wn, opcode);
  WN_set_kid_count(wn, 0);
  WN_map_id(wn) =  WN_MAP_UNDEFINED;
  WN_const_val(wn) = 1LL;
  return wn;
} /* WN2F_Initiate_ZeroInt */


static void
WN2F_Substring(xml::ostream& xos, 
	       INT64        string_size,
	       WN          *lower_bnd,
	       WN          *substring_size,
	       XlationContext& ctxt)
{
   /* Given a substring offset from the base of a character string 
    * (lower_bnd), the size of the whole string, and the size of the
    * substring, generate the notation necessary as a suffix to the
    * string reference to denote the substring.
    */
   if (WN_operator(lower_bnd) != OPR_INTCONST      ||
       WN_const_val(lower_bnd) != 0                    ||
       WN_operator(substring_size) != OPR_INTCONST ||
       WN_const_val(substring_size) != string_size)
   {
      /* Need to generate substring expression "(l+1:l+size)" */
      xos << "(";
      set_XlationContext_no_parenthesis(ctxt);
      TranslateWN(xos, lower_bnd, ctxt);
      reset_XlationContext_no_parenthesis(ctxt);
      xos << ":";
      if (WN_operator(lower_bnd) != OPR_INTCONST ||
	  WN_const_val(lower_bnd) != 0)
      {
	 TranslateWN(xos, lower_bnd, ctxt);
	 xos << "+";
      }
      TranslateWN(xos, substring_size, ctxt);
      xos << ")";
   }
} /* WN2F_Substring */


static void
WN2F_Get_Substring_Info(WN **base,        /* Possibly OPR_ARRAY node (in/out)*/
			TY_IDX *string_ty,/* The string type (out) */
			WN **lower_bnd,   /* The lower bound index (out) */
		        WN **length )
{
   /* There are two possibilities concerning the array base expressions.
    * It can be a pointer to a complete character-string (array) or it
    * can be a pointer to a character within a character-string (single
    * character).  In the first instance, the offset off the base of 
    * string is zero.  In the latter case, the offset is given by the
    * array indexing operation.
    */
   TY_IDX ptr_ty = WN_Tree_Type(*base);

   *string_ty = TY_pointed(ptr_ty);

   if (TY_size(*string_ty) == 1 && !TY_Is_Array(*string_ty)
       && WN_operator(*base) == OPR_ARRAY) {
      /* Let the base of the string be denoted as the base of the array
       * expression.
       */
      *string_ty = TY_pointed(WN_Tree_Type(WN_kid0(*base)));
      *lower_bnd = WN_array_index(*base, 0);
      *length    = WN_kid1(*base);
      *base = WN_kid0(*base);
   }
   else if (WN_operator(*base) == OPR_ARRAY &&
	    TY_Is_Array(*string_ty)             &&
	    TY_AR_ndims(*string_ty) == 1        &&
	    TY_Is_Character_String(*string_ty)  &&
	    !TY_ptr_as_array(Ty_Table[ptr_ty])) {
      /* Presumably, the lower bound is given by the array operator */
      *lower_bnd = WN_array_index(*base, 0);
      *length    = WN_kid1(*base);
      *base = WN_kid0(*base);
   }
   else {
      *lower_bnd = WN2F_INTCONST_ZERO;
      *length    = WN2F_INTCONST_ZERO;
   }
} /* WN2F_Get_Substring_Info */

static WN *
WN2F_Find_Base(WN *addr)
{
  /* utility to find base of address tree */
  WN *res = addr;

  switch (WN_operator(addr)) {
    case OPR_ARRAY: 
    case OPR_ILOAD:
    res=WN_kid0(addr);
    break;

    case OPR_ADD:
      if (WN_operator(WN_kid0(addr)) == OPR_INTCONST)
	res = WN2F_Find_Base(WN_kid1(addr));
      else
	res = WN2F_Find_Base(WN_kid0(addr));
    break;

  default:
    res = addr;
    break;
  }
  return res;
}

extern BOOL
WN2F_Is_Address_Preg(WN * ad ,TY_IDX ptr_ty)
{
  /* Does this look like a preg or variable being used as an address ? */
  /* These are propagated by opt/pfa                                   */

  BOOL is_somewhat_address_like = TY_kind(ptr_ty) == KIND_POINTER;
  
  if (TY_kind(ptr_ty) == KIND_SCALAR) {
    TYPE_ID tid = TY_mtype(ptr_ty);
    is_somewhat_address_like |= (MTYPE_is_pointer(tid)) || (tid == MTYPE_I8) || (tid == MTYPE_I4) ;
  }

  if (is_somewhat_address_like) {
    WN * wn = WN2F_Find_Base(ad);
    if (WN_operator(wn) == OPR_LDID) {
      ST * st = WN_st(wn) ;
      if (ST_class(st) == CLASS_PREG)
	return TRUE ;
      
      if (ST_class(st) == CLASS_VAR) {
	if (TY_kind(ptr_ty) == KIND_SCALAR)
	  return TRUE;
	
	if (TY_kind(WN_ty(wn)) == KIND_SCALAR) {
	  TYPE_ID wtid = TY_mtype(WN_ty(wn));
	  
	  /* Looks like a Cray pointer (I4/I8) ? */
	  if ((wtid == MTYPE_I8)|| (wtid == MTYPE_I4))
	    if (ad != wn)
	      return TRUE ;
	  
	  /* Looks like a VAR with a U4/U8? used  */
	  /* only with offsets, or FORMALs would  */
	  /* qualify, if intrinsic mtype          */
	  if (MTYPE_is_pointer(wtid))
	    if (TY_kind(ST_type(st)) != KIND_SCALAR)
	      return TRUE;
	}
      }
    }
  }
  return FALSE;
}


//***************************************************************************
// Loads (In WHIRL, loads are expressions.)
//***************************************************************************

WN2F_STATUS 
whirl2xaif::xlate_LDA(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_LDA, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_LDA"));
  ASSERT_DBG_FATAL(ST_class(WN_st(wn)) != CLASS_PREG, 
		   (DIAG_W2F_CANNOT_LDA_PREG));
  
  // The referenced object's address is at some offset from the base
  // object.  These are types for 1) the base object and a pointer to
  // it 2) the referenced object.
  ST* base_st = WN_st(wn); // symbol for base object
  TY_IDX base_ty = ST_type(base_st);
  if (TY_is_f90_pointer(base_ty)) { base_ty = TY_pointed(base_ty); }
  TY_IDX baseptr_ty = Stab_Pointer_To(base_ty);

  // Sometimes we need to deal with buggy WHIRL code, where the type
  // associated with an LDA is not a pointer type.  For such cases
  // we infer a type; it may be wrong but it is the best we can do.
  TY_IDX ref_ty = (TY_Is_Pointer(WN_ty(wn))) ? TY_pointed(WN_ty(wn)) : base_ty;
    
  ctxt.CurContext().SetWN(wn);
  ctxt.ResetDerefAddr();
  set_XlationContext_has_no_arr_elmt(ctxt);
  xlate_SymRef(xos, base_st, baseptr_ty, ref_ty, WN_lda_offset(wn), ctxt);
  reset_XlationContext_has_no_arr_elmt(ctxt);
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
whirl2xaif::xlate_LDID(xml::ostream& xos, WN* wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_LDID, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_LDID"));

  // The referenced object's address is at some offset from the base
  // object.  These are types for 1) the base object and a pointer to
  // it 2) the referenced object.
  TY_IDX base_ty = ST_type(WN_st(wn));
  TY_IDX baseptr_ty;
  TY_IDX ref_ty = WN_ty(wn);
  
  if (ST_class(WN_st(wn)) == CLASS_PREG) {
    ST2F_Use_Preg(xos, base_ty, WN_load_offset(wn)); // FIXME if WN_load_offset(wn) == -1
  } else {

    // FIXME: Stab_Pointer_To, et. al. create types!!!
    if (ctxt.IsDerefAddr() && TY_Is_Pointer(base_ty)) {
      // Expect the loaded type to be a pointer to the type of object
      // to be dereferenced.  The only place (besides declaration sites)
      // where we expect to specially handle ptr_as_array objects.
      if (TY_ptr_as_array(Ty_Table[ref_ty])) {
	ref_ty = Stab_Array_Of(TY_pointed(ref_ty), 0/*size*/);
      } else {
	ref_ty = TY_pointed(ref_ty);
      }
      
      // There are two possibilities for the base type: A regular 
      // pointer or a pointer to be treated as a pointer to an array.
      // In either case, 'baseptr_ty' is a pointer to the 
      // derefenced base type. 
      //
      // Note that this does not handle a pointer to a struct to be
      // treated as an array of structs, where the object type and
      // offset denote a member of the struct, since xlate_SymRef() 
      // cannot access a struct member through an array access.
      if (TY_ptr_as_array(Ty_Table[base_ty])) {
	base_ty = Stab_Array_Of(TY_pointed(base_ty), 0/*size*/);
      } else {
	base_ty = TY_pointed(base_ty); // baseptr_ty = base_ty;
      }
    } 
    baseptr_ty = Stab_Pointer_To(base_ty);
    
#if 0 // REMOVE
    else {
      // Either not a dereference, or possibly a dereference off a 
      // record/map/common/equivalence field.  The base symbol is
      // not a pointer, and any dereferencing on a field will occur
      // in xlate_SymRef().
      baseptr_ty = Stab_Pointer_To(base_ty);
      ref_ty = WN_ty(wn);
    }
#endif
#if 0
    if (!ctxt.IsDerefAddr() && STAB_IS_POINTER_REF_PARAM(WN_st(wn))) {
      // Since we do not wish to dereference a load of a reference 
      // parameter, this must mean we are taking the address of the
      // parameter.
    }
#endif
    ctxt.CurContext().SetWN(wn);
    set_XlationContext_has_no_arr_elmt(ctxt); // FIXME why?
    xlate_SymRef(xos, WN_st(wn), baseptr_ty, ref_ty, WN_load_offset(wn), ctxt);
    reset_XlationContext_has_no_arr_elmt(ctxt);
  }

  return EMPTY_WN2F_STATUS;
} 


WN2F_STATUS 
whirl2xaif::xlate_ILOAD(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // Note that we handle this just like we do the lhs of an ISTORE.
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_ILOAD, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_ILOAD"));

  // The referenced object's address is at some offset from the base
  // object.  These are types for 1) the base object and a pointer to
  // it 2) the referenced object.
  WN* baseptr = WN_kid0(wn); // address expression as WN
  TY_IDX baseptr_ty = WN_load_addr_ty(wn); // == WN_Tree_Type(baseptr)
  TY_IDX base_ty = TY_pointed(baseptr_ty); 
  TY_IDX ref_ty = WN_ty(wn);

  // Translate into a reference (dereference address???)
  ctxt.CurContext().SetWN(wn);
  if (WN_operator(baseptr) == OPR_LDA || WN_operator(baseptr) == OPR_LDID)
    set_XlationContext_has_no_arr_elmt(ctxt); // FIXME
  
  WN2F_Offset_Memref(xos, baseptr, baseptr_ty, ref_ty,
		     WN_load_offset(wn), ctxt);

  reset_XlationContext_has_no_arr_elmt(ctxt);

  return EMPTY_WN2F_STATUS;
}

WN2F_STATUS 
xlate_ILOADX(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_WARN(FALSE, (DIAG_UNIMPLEMENTED, "xlate_ILOADX"));
  xos << WN_opc_name(wn);  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
WN2F_mload(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // This should only appear the as the rhs of an ISTORE.  Treat
  // it just like an ILOAD.
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_MLOAD, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_mload"));
  // FIXME:
    
  /* Get the type of the base from which we are loading */
  TY_IDX base_ty = WN_Tree_Type(WN_kid0(wn));
  if (!TY_Is_Pointer(base_ty))
    base_ty = WN_ty(wn);
  
  /* Get the object to be loaded */
  WN2F_Offset_Memref(xos, WN_kid0(wn), /* base-symbol */
		     base_ty, /* base-type */
		     TY_pointed(WN_ty(wn)), /* object-type */
		     WN_load_offset(wn), /* object-ofst */ ctxt);

  return EMPTY_WN2F_STATUS;
}


//***************************************************************************
// Stores (In WHIRL, stores are statements.)
//***************************************************************************

// xlate_STID: Translate a WHIRL STID node to an XAIF assignment
WN2F_STATUS 
whirl2xaif::xlate_STID(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_STID, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_STID"));

  // For LHS (the storage container):
  // The referenced object's address is at some offset from the base
  // object.  These are types for 1) the base object and a pointer to
  // it 2) the referenced object.
  ST* base_st = WN_st(wn); // symbol for base object
  TY_IDX base_ty = ST_type(base_st);
  TY_IDX baseptr_ty = Stab_Pointer_To(base_ty);
  TY_IDX ref_ty = WN_ty(wn);
  
  // Assignment
  if (!ctxt.IsAssign()) {
    xos << BegElem(XAIFStrings.elem_Assign())
	<< Attr("statement_id", ctxt.GetNewVId());
  }
  
  // LHS of assignment
  WN* lhs = wn; // OPR_STID represents the LHS of the assignment
  // Change alias to du_ud MWF
  // ----------------------------
  xos << BegElem(XAIFStrings.elem_AssignLHS()) 
      << Attr("du_ud", ctxt.FindVN(lhs)) << EndAttrs;
  ctxt.CreateContext(XlationContext::VARREF, wn); // implicit for LHS
  
  if (ST_class(base_st) == CLASS_PREG) { // FIXME
    ST2F_Use_Preg(xos, base_ty, WN_store_offset(wn));
  } else {
    xlate_SymRef(xos, base_st, baseptr_ty, ref_ty, WN_store_offset(wn), ctxt);
  }
  
  ctxt.DeleteContext();
  xos << EndElem;
  
  // RHS of assignment
  BOOL logical = TY_is_logical(Ty_Table[ref_ty]); // FIXME
  xos << BegElem(XAIFStrings.elem_AssignRHS()) << EndAttrs;
  ctxt.CreateContext(XlationContext::NOFLAG, wn);
  if (logical) { set_XlationContext_has_logical_arg(ctxt); } // FIXME
  TranslateWN(xos, WN_kid0(wn), ctxt);
  if (logical) { reset_XlationContext_has_logical_arg(ctxt); } // FIXME
  ctxt.DeleteContext();
  xos << EndElem;

  if (!ctxt.IsAssign()) {
    xos << EndElem /* elem_Assign() */;
  }
  
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
whirl2xaif::xlate_ISTORE(xml::ostream& xos, WN* wn, XlationContext& ctxt)
{
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_ISTORE, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_ISTORE"));

  // For LHS (the storage container):
  // The referenced object's address is at some offset from the base
  // object.  These are types for 1) the base object and a pointer to
  // it 2) the referenced object.
  WN* baseptr = WN_kid1(wn); // address expression as WN
  TY_IDX baseptr_ty = WN_ty(wn); // == WN_Tree_Type(baseptr)
  TY_IDX base_ty = TY_pointed(baseptr_ty); 
  TY_IDX ref_ty = TY_pointed(WN_ty(wn)); // FIXME: no direct way to get this

  assert(baseptr_ty == WN_Tree_Type(baseptr)); // FIXME
  
  // Assignment
  if (!ctxt.IsAssign()) {
    xos << BegElem(XAIFStrings.elem_Assign()) 
	<< Attr("statement_id", ctxt.GetNewVId());
  }
  
  // LHS of assignment (dereference address)
  // Change alias to du_ud MWF
  // ----------------------------
  WN* lhs = baseptr;
  xos << BegElem(XAIFStrings.elem_AssignLHS()) 
      << Attr("du_ud", ctxt.FindVN(lhs)) << EndAttrs;
  ctxt.CreateContext(XlationContext::VARREF, wn); // implicit for LHS
  
  if (WN_operator(baseptr) == OPR_LDA || WN_operator(baseptr) == OPR_LDID) {
    set_XlationContext_has_no_arr_elmt(ctxt);
  }
  WN2F_Offset_Memref(xos, baseptr, baseptr_ty, ref_ty, WN_store_offset(wn),
		     ctxt);
  reset_XlationContext_has_no_arr_elmt(ctxt); 

  ctxt.DeleteContext();
  xos << EndElem;

  // RHS of assignment
  xos << BegElem(XAIFStrings.elem_AssignRHS()) << EndAttrs;
  ctxt.CreateContext(XlationContext::NOFLAG, wn);
  TranslateWN(xos, WN_kid0(wn), ctxt);
  ctxt.DeleteContext();
  xos << EndElem;

  if (!ctxt.IsAssign()) {
    xos << EndElem /* elem_Assign() */;
  }
  
  return EMPTY_WN2F_STATUS;
}

WN2F_STATUS 
xlate_ISTOREX(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  ASSERT_DBG_WARN(FALSE, (DIAG_UNIMPLEMENTED, "xlate_ISTOREX"));
  xos << std::endl << WN_opc_name(wn);
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS 
WN2F_mstore(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  /* Note that we make the assumption that this is just like an 
   * ISTORE, and handle it as though it were.  We do not handle
   * specially assignment-forms where the lhs is incompatible with
   * the rhs, since we assume this will never happen for Fortran
   * and we cannot easily get around this like we do in C (i.e.
   * with cast expressions. (FIXME)
   */
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_MSTORE, 
		   (DIAG_W2F_UNEXPECTED_OPC, "WN2F_mstore"));
#if 0
  ASSERT_DBG_WARN(WN_operator(WN_kid0(wn)) == OPR_MLOAD,
		  (DIAG_W2F_UNEXPECTED_OPC, "rhs of WN2F_mstore"));
  
  //TODO: scalar expression allowed, but array/structure assignment assumed
  // with constant ie: should put out doloop?... call OFFSET_Memref?
#endif

  /* Get the base address into which we are storing a value */
  TY_IDX base_ty = WN_Tree_Type(WN_kid1(wn));
  if (!TY_Is_Pointer(base_ty))
    base_ty = WN_ty(wn);
  
  /* Get the lhs of the assignment (dereference address) */
  xos << std::endl; 
  WN2F_Offset_Memref(xos, WN_kid1(wn), /* base-symbol */
		     base_ty, /* base-type */ 
		     TY_pointed(WN_ty(wn)), /* object-type */
		     WN_store_offset(wn),   /* object-ofst */ ctxt);
  
   // Assign the rhs to the lhs.
  xos << "mstore=" << std::endl;
  
  /* The rhs */
  TranslateWN(xos, WN_kid0(wn), ctxt);

  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS
WN2F_pstid(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_PSTID,
                    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_pstid"));

   /* Get the lhs of the assignment */
   xos << std::endl;
   if (ST_class(WN_st(wn)) == CLASS_PREG) {
     ST2F_Use_Preg(xos, ST_type(WN_st(wn)), WN_store_offset(wn));
   } else if (ST_sym_class(WN_st(wn))==CLASS_VAR 
	      && ST_is_not_used(WN_st(wn))) {
     /* This is a redundant assignment statement, so determined
      * by IPA, so just assign it to a temporary variable
      * instead.
      */
     UINT tmp_idx = Stab_Lock_Tmpvar(WN_ty(wn), &ST2F_Declare_Tempvar);
     Append_Token_String(xos, W2CF_Symtab_Nameof_Tempvar(tmp_idx));
     Stab_Unlock_Tmpvar(tmp_idx);
   } else {
     xlate_SymRef(xos,
		  WN_st(wn),                        /* base-symbol */
		  Stab_Pointer_To(ST_type(WN_st(wn))),/* base-type */
		  WN_ty(wn),                        /* object-type */
		  WN_store_offset(wn),              /* object-ofst */
		  ctxt);
   }
   
   // Assign the rhs to the lhs.
   xos << "pstid=>";

   /* The rhs */
   if (TY_is_logical(Ty_Table[WN_ty(wn)])) {
     set_XlationContext_has_logical_arg(ctxt);
     TranslateWN(xos, WN_kid0(wn), ctxt);
     reset_XlationContext_has_logical_arg(ctxt);
   } else
     TranslateWN(xos, WN_kid0(wn), ctxt);

   return EMPTY_WN2F_STATUS;
} /* WN2F_pstid */


extern WN2F_STATUS
WN2F_pstore(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   TY_IDX        base_ty;
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_PSTORE,
                    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_pstore"));

   /* Get the base address into which we are storing a value */
   base_ty = WN_Tree_Type(WN_kid1(wn));
   if (!TY_Is_Pointer(base_ty))
      base_ty = WN_ty(wn);

   /* Get the lhs of the assignment (dereference address) */
   xos << std::endl;
   set_XlationContext_has_no_arr_elmt(ctxt);
   
   WN2F_Offset_Memref(xos,
		      WN_kid1(wn),           /* base-symbol */
		      base_ty,               /* base-type */
		      TY_pointed(WN_ty(wn)), /* object-type */
		      WN_store_offset(wn),   /* object-ofst */
		      ctxt);
   reset_XlationContext_has_no_arr_elmt(ctxt);

   // Assign the rhs to the lhs.
   xos << "pstore=>";

   /* The rhs */
   if (TY_is_logical(Ty_Table[TY_pointed(WN_ty(wn))])) {
     set_XlationContext_has_logical_arg(ctxt);
     TranslateWN(xos, WN_kid0(wn), ctxt);
     reset_XlationContext_has_logical_arg(ctxt);
   } else {
     TranslateWN(xos, WN_kid0(wn), ctxt);
   }
   
   return EMPTY_WN2F_STATUS;
} /* WN2F_pstore */

//***************************************************************************
// 
//***************************************************************************

WN2F_STATUS
xlate_ARRAY(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  /* Note that array indices have been normalized to assume the
   * array is based at index zero.  Since a base at index 1 is
   * the default for Fortran, we denormalize to base 1 here. */
  BOOL deref = ctxt.IsDerefAddr();
  
  ASSERT_DBG_FATAL(WN_operator(wn) == OPR_ARRAY, 
		   (DIAG_W2F_UNEXPECTED_OPC, "xlate_ARRAY"));
  
  // Only allow taking the address of an array element for F90!
#if 0
  ASSERT_DBG_WARN(deref, (DIAG_UNIMPLEMENTED, 
			  "taking the address of an array element"));
#endif

  bool newContext = false; // FIXME: abstract (symref, memref)
  // Change alias to du_ud MWF
  // ----------------------------
  if (!ctxt.IsVarRef()) {
    xos << BegElem(XAIFStrings.elem_VarRef())
	<< Attr("vertex_id", ctxt.GetNewVId())
	<< Attr("du_ud", ctxt.FindVN(wn));
    ctxt.CreateContext(XlationContext::VARREF, wn); // FIXME: do we need wn?
    newContext = true; 
  }

  /* Get the array or, for ptr-as-array types, the element type */  
  WN* kid = WN_kid0(wn);
  TY_IDX ptr_ty = WN_Tree_Type(kid);
  
  if (WN2F_Is_Address_Preg(kid, ptr_ty)) {
    /* a preg or sym has been used as an address, usually after
       optimization don't know base type, or anything else so use
       OPR_ARRAY to generate bounds */
    TranslateWN(xos, kid, ctxt);
    xlate_ArrayIndices(xos, wn, ctxt);
    // FIXME
  } else {
    TY_IDX array_ty = W2F_TY_pointed(ptr_ty, "base of OPC_ARRAY");
    
    if (WN_operator(kid) == OPR_LDID 
	&& ST_sclass(WN_st(kid)) == SCLASS_FORMAL 
	&& !ST_is_value_parm(WN_st(kid))
	&& WN_element_size(wn) == TY_size(array_ty)
	&& WN_num_dim(wn) == 1
	&& WN_operator(WN_array_index(wn, 0)) == OPR_INTCONST 
	&& WN_const_val(WN_array_index(wn, 0)) == 0 
	&& !TY_ptr_as_array(Ty_Table[WN_ty(kid)])
	&& (!TY_Is_Array(array_ty) 
	    || TY_size(TY_AR_etype(array_ty)) < TY_size(array_ty))) {
      // This array access is just a weird representation for an implicit
      // reference parameter dereference.  Ignore the array indexing.
      TranslateWN(xos, kid, ctxt);

    } else if (!TY_ptr_as_array(Ty_Table[ptr_ty]) 
	       && TY_Is_Character_String(array_ty) ) {
      /* We assume that substring accesses are treated in the handling
       * of intrinsic functions, except when the substrings are to be
       * handled as integral types and thus are encountered here. */
      WN2F_String_Argument(xos, wn, WN2F_INTCONST_ONE, ctxt);
    } else { 
      // A regular array access

      // Array base
      UINT srcid = ctxt.PeekVId();
      TranslateWN(xos, kid, ctxt); // still use ctxt.IsDerefAddr()
      ctxt.ResetDerefAddr();

      // Array indexing
      UINT targid = ctxt.PeekVId();
      WN2F_array_bounds(xos, wn, array_ty, ctxt);
      
      DumpVarRefEdge(xos, ctxt.GetNewEId(), srcid, targid);
    }
  }
  
  if (newContext) {
    ctxt.DeleteContext();
    xos << EndElem /* elem_VarRef() */;
  }
  
  return EMPTY_WN2F_STATUS;
} /* xlate_ARRAY */


WN2F_STATUS
WN2F_arrsection(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   /* Note that array indices have been normalized to assume the
    * array is based at index zero.  Since a base at index 1 is
    * the default for Fortran, we denormalize to base 1 here.
    */
   BOOL  deref = ctxt.IsDerefAddr();
   WN    * kid;
   TY_IDX ptr_ty;
   TY_IDX array_ty;


   // FIXME: this was ARRAY not ARRSECTION
   //ASSERT_DBG_FATAL(WN_operator(wn) == OPR_ARRAY,
   //                 (DIAG_W2F_UNEXPECTED_OPC, "xlate_ARRAY"));
   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_ARRSECTION,
                    (DIAG_W2F_UNEXPECTED_OPC, "xlate_ARRSECTION"));


   /* Only allow taking the address of an array element for F90!
    *
    */
#if 0
   ASSERT_DBG_WARN(deref, (DIAG_UNIMPLEMENTED,
			   "taking the address of an array element"));
#endif

   /* Get the array or, for ptr-as-array types, the element type */
   kid    = WN_kid0(wn);
   ptr_ty = WN_Tree_Type(kid);

   if (WN2F_Is_Address_Preg(kid,ptr_ty)) {
     /* a preg or sym has been used as an address, usually after
	optimization don't know base type, or anything else so use
	OPR_ARRAY to generate bounds */

     TranslateWN(xos, kid, ctxt);
     WN2F_Arrsection_Slots(xos,wn,ctxt,TRUE);
   }
   else {
     array_ty = W2F_TY_pointed(ptr_ty, "base of OPC_ARRAY");
    
     if (WN_operator(kid) == OPR_LDID       &&

         ST_sclass(WN_st(kid)) == SCLASS_FORMAL &&
         !ST_is_value_parm(WN_st(kid))          &&
         WN_element_size(wn) == TY_size(array_ty)       &&
         WN_num_dim(wn) == 1                            &&
         WN_operator(WN_array_index(wn, 0)) == OPR_INTCONST &&
         WN_const_val(WN_array_index(wn, 0)) == 0       &&
         !TY_ptr_as_array(Ty_Table[WN_ty(kid)])           &&
         (!TY_Is_Array(array_ty) ||
          TY_size(TY_AR_etype(array_ty)) < TY_size(array_ty))) {
         /* This array access is just a weird representation for an implicit
          * reference parameter dereference.  Ignore the array indexing.
          */

       TranslateWN(xos, kid, ctxt);
     }
     else if (!TY_ptr_as_array(Ty_Table[ptr_ty]) && TY_Is_Character_String(array_ty))
     {
         /* We assume that substring accesses are treated in the handling
          * of intrinsic functions, except when the substrings are to be
          * handled as integral types and thus are encountered here.
          */
#if 0
       if (!WN2F_F90_pu) {
         xos << "ichar";
         xos << "(";
       }
# endif 

       WN2F_String_Argument(xos, wn, WN2F_INTCONST_ONE, ctxt);
# if 0
       if (!WN2F_F90_pu)
         xos << ")";
# endif

     }
     else { /* A regular array access */
       /* Get the base of the object to be indexed into, still using
	* ctxt.IsDerefAddr().
	*/
       TranslateWN(xos, kid, ctxt);
       ctxt.ResetDerefAddr();
       
       if ( XlationContext_has_no_arr_elmt(ctxt))
	 ;
       else
	 WN2F_arrsection_bounds(xos,wn,array_ty,ctxt);
     }
   }
   return EMPTY_WN2F_STATUS;
} /* WN2F_arrsection */


WN2F_STATUS
WN2F_where(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  xos << "WHERE(";
  TranslateWN(xos, WN_kid0(wn), ctxt);
  xos << ")";
  TranslateWN(xos, WN_kid1(wn), ctxt);
  xos << "END WHERE";
  TranslateWN(xos, WN_kid2(wn), ctxt);
  return EMPTY_WN2F_STATUS;
}


WN2F_STATUS
WN2F_arrayexp(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  TranslateWN(xos, WN_kid0(wn), ctxt);
  return EMPTY_WN2F_STATUS;
}


/*
|*                                                                           *|
|* for array section triplet node,kid0 is lower bound,it should plus 1LL for *|
|* adjusted bound,upper bound=kid0+k1*k2                                     *|
|* kid0 evaluates to the starting integer value of the progression.	     *|
|* kid1 evaluates to an integer value that gives the stride in the           *|
|*   progression                                                             *|
|* kid2 evaluates to the number of values in the progression       	     *|
|*                                                                           *|
*/
 
WN2F_STATUS
WN2F_triplet(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  WN      *kid0;
  WN      *kid1;
  WN      *kid2;
  kid0=WN_kid0(wn);
  kid1=WN_kid1(wn);
  kid2=WN_kid2(wn);
  TranslateWN(xos, kid0, ctxt);
  if ((WN_operator(kid2) == OPR_INTCONST) &&
      (WN_const_val(kid2)==INT_MIN) )
    xos << ":";
  else  {
    xos << ":";
    if (WN_operator(kid0) == OPR_INTCONST &&
	WN_operator(kid1) == OPR_INTCONST &&
	WN_operator(kid2) == OPR_INTCONST) {
      std::string val;
      if ((WN_const_val(kid0)+WN_const_val(kid2)*WN_const_val(kid1))>=INT_MAX)
	val = TCON2F_translate(Host_To_Targ(MTYPE_I8, WN_const_val(kid0)+
					    WN_const_val(kid2)*
					    WN_const_val(kid1)),
			       FALSE);
      else    
	val = TCON2F_translate(Host_To_Targ(MTYPE_I4, WN_const_val(kid0)+
					    WN_const_val(kid2)*
					    WN_const_val(kid1)),
			       FALSE);
      xos << val;
      
    } 
    else 
      if (WN_operator(kid0) == OPR_INTCONST &&
	  WN_operator(kid1) == OPR_INTCONST ) {
	if (WN_const_val(kid1)==1) {
	  if (WN_const_val(kid0)== 0) {
	    TranslateWN(xos, kid2, ctxt);
	  }
	  else {
	    TranslateWN(xos, kid1, ctxt);
	    xos << "+";
	    TranslateWN(xos, kid2, ctxt); }
	}
	else {
	  if (WN_const_val(kid0)== 0){
            TranslateWN(xos, kid1, ctxt);
	    xos << "*";
	    TranslateWN(xos, kid2, ctxt); }
	  else {
	    TranslateWN(xos, kid0, ctxt);
	    xos << "+";
	    TranslateWN(xos, kid1, ctxt);
	    xos << "*";
	    TranslateWN(xos, kid2, ctxt); }
	}
      }
      else 
	if (WN_operator(kid1) == OPR_INTCONST &&
	    WN_operator(kid2) == OPR_INTCONST) {
	  TranslateWN(xos, kid0, ctxt);
	  xos << "+";
	  
	  std::string val;
          if ((WN_const_val(kid1)*WN_const_val(kid2))>=INT_MAX)
	    val = TCON2F_translate(Host_To_Targ(MTYPE_I8,   
						WN_const_val(kid1)*
						WN_const_val(kid2)),
				   FALSE);
          else 
	    val = TCON2F_translate(Host_To_Targ(MTYPE_I4,   
						WN_const_val(kid1)*
						WN_const_val(kid2)),
				   FALSE);
	}
	else 
          if (WN_operator(kid0) == OPR_INTCONST &&
              WN_operator(kid2) == OPR_INTCONST) {
	    if (WN_const_val(kid2)==1) {
	      if (WN_const_val(kid0)== 0) {
		TranslateWN(xos, kid1, ctxt);
	      }
	      else {
		TranslateWN(xos, kid0, ctxt);
		xos << "+";
		TranslateWN(xos, kid1, ctxt); 
	      }
            }
            else {
	      if (WN_const_val(kid0)== 0){
		TranslateWN(xos, kid2, ctxt);
		xos << "*";
		TranslateWN(xos, kid1, ctxt); }
	      else {
		TranslateWN(xos, kid0, ctxt);
		xos << "+";
		TranslateWN(xos, kid1, ctxt);
		xos << "*";
		TranslateWN(xos, kid2, ctxt); }
	    }
	  }
           else 
	     if (WN_operator(kid0) == OPR_INTCONST){ 
	       if (WN_const_val(kid0)==0) {
		 TranslateWN(xos, kid1, ctxt);
		 xos << "*";
		 TranslateWN(xos, kid2, ctxt);}
	       else {
                 TranslateWN(xos, kid0, ctxt);
                 xos << "+";
                 TranslateWN(xos, kid1, ctxt);
                 xos << "*";
                 TranslateWN(xos, kid2, ctxt);
	       }
	     }
	     else 
	       if (WN_operator(kid1) == OPR_INTCONST){
		 TranslateWN(xos, kid0, ctxt);
		 xos << "+";
		 if (WN_const_val(kid1)==1){
		   TranslateWN(xos, kid2, ctxt);}
                 else {
		   TranslateWN(xos, kid1, ctxt);
		   xos << "*";
		   TranslateWN(xos, kid2, ctxt);
		 }
	       }
	       else
		 if (WN_operator(kid2) == OPR_INTCONST) {
		   TranslateWN(xos, kid0, ctxt);
		   xos << "+";
		   if (WN_const_val(kid2)==1)
		     TranslateWN(xos, kid1, ctxt);
		   else
		     {
		       TranslateWN(xos, kid2, ctxt);
		       xos << "*";
		       TranslateWN(xos, kid1, ctxt);
		     }
		 }
    if ((WN_operator(kid1) == OPR_INTCONST) && 
	(WN_const_val(kid1)==1))  {
    } else {
      xos << ":";
      TranslateWN(xos, kid1, ctxt);
    } 
  }  
  return EMPTY_WN2F_STATUS;
  
}


WN2F_STATUS
WN2F_src_triplet(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  WN      *kid0;
  WN      *kid1;
  WN      *kid2;
  kid0=WN_kid0(wn);
  kid1=WN_kid1(wn);
  kid2=WN_kid2(wn);
  TranslateWN(xos, kid0, ctxt);
  xos << ":";
  TranslateWN(xos, kid1, ctxt); 
  
  if (WN_operator(kid2) == OPR_INTCONST &&
      WN_const_val(kid2) == 1)
    ;
  else {
    xos << ":";
    TranslateWN(xos, kid2, ctxt); 
  }
  
  return EMPTY_WN2F_STATUS;  
}

void
WN2F_Arrsection_Slots(xml::ostream& xos, WN *wn, XlationContext& ctxt, BOOL parens)
{
  INT32 dim;
  WN * kidz;
  INT32 co_dim;
  INT32 array_dim;
  TY_IDX ttyy;
  ST * st;
  ARB_HANDLE arb_base;
  WN* kid;

  /* Gets bounds from the slots of an OPC_ARRSECTION node  */

  /* Append the "denormalized" indexing expressions in reverse order
   * of the way they occur in the indexing expression, since Fortran
   * employs column-major array layout, meaning the leftmost indexing
   * expression represents array elements laid out in contiguous
   * memory locations.
   */

  kidz = WN_kid0(wn);
  st  =  WN_st(kidz);
  ttyy = ST_type(st);
  if (TY_Is_Pointer(ttyy))  //Sept temp use
    ttyy=TY_pointed(ttyy);
  if (TY_is_f90_pointer(ttyy))
    ttyy = TY_pointed(ttyy);
  
  arb_base = TY_arb(ttyy);
  
  dim =  ARB_dimension(arb_base);
  co_dim = ARB_co_dimension(arb_base);
  if (co_dim <= 0)
    co_dim = 0;
  
  if (dim >  WN_num_dim(wn) ) {
    array_dim = dim-co_dim;
    co_dim = 0;
  } else {
    dim =  WN_num_dim(wn);
    array_dim = dim;
  }
  
  if (WN_operator(WN_array_index(wn, WN_num_dim(wn)-1))==OPR_SRCTRIPLET) 
    kid = WN_kid2(WN_array_index(wn, WN_num_dim(wn)-1));
  
  if (array_dim>0) {
    if (parens) {
      xos << "(";
      set_XlationContext_no_parenthesis(ctxt);
    }
# if 0 /* original code without thinking about co_array */
    for (dim = WN_num_dim(wn)-1; dim >= 0; dim--) {
      if (WN_operator(WN_array_index(wn, dim))==OPR_SRCTRIPLET) {
	TranslateWN(xos, WN_array_index(wn, dim), ctxt);    
      } else {
	TranslateWN(xos, WN_array_index(wn, dim), ctxt);
      }
      if (dim > 0)
	xos << ",";
    }
# endif
    for (dim = WN_num_dim(wn)-1; dim >= co_dim; dim--) {
      if (WN_operator(WN_array_index(wn, dim))==OPR_SRCTRIPLET) {
	TranslateWN(xos, WN_array_index(wn, dim), ctxt);
      } else {
	TranslateWN(xos, WN_array_index(wn, dim), ctxt);
      }
      if (dim > co_dim)
	xos << ",";
    }
    if (parens)
      xos << ")";
  }
  
  if (co_dim > 0) {
    
    if (parens)
      xos << "[";
    
    for (dim = co_dim-1; dim >= 0; dim--) {
      if (WN_operator(WN_array_index(wn, dim))==OPR_SRCTRIPLET) {
	TranslateWN(xos, WN_array_index(wn, dim), ctxt);
      } else {
	TranslateWN(xos, WN_array_index(wn, dim), ctxt);
      }
      if (dim > 0)
	xos << ",";
    }
    
    if (parens)
      xos << "]";
  }
}

void
xlate_ArrayIndices(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
  // FIXME: do not handle co dimentions
  
  /* get array's rank and co_rank information from kid0 of wn
   * kid0 should be OPR_LDA */
  INT32 array_dim;
  WN* kid = WN_kid0(wn);
  if (WN_operator(kid) == OPR_LDA) {
    ST* st = WN_st(kid);
    TY_IDX ty = ST_type(st);
    
    if (TY_Is_Pointer(ty))
      ty = TY_pointed(ty);
    if (TY_is_f90_pointer(ty))
      ty = TY_pointed(ty);
    
    ARB_HANDLE arb_base = TY_arb(ty);
    array_dim = ARB_dimension(arb_base);
  } else {
    array_dim = WN_num_dim(wn);
  }
  
  /* Append indexing expressions in reverse order of the way they
   * occur in the indexing expression, since Fortran employs
   * column-major array layout, meaning the leftmost indexing
   * expression represents array elements laid out in contiguous
   * memory locations. */
  xos << BegElem(XAIFStrings.elem_ArrayElemRef()) 
      << Attr("vertex_id", ctxt.GetNewVId());
  for (INT32 dim = array_dim - 1; dim >= 0; --dim) {
    xos << BegElem(XAIFStrings.elem_Index());
    ctxt.CreateContext(); 
    ctxt.ResetVarRef(); // elem_Index() contains ExpressionType
    TranslateWN(xos, WN_array_index(wn, dim), ctxt);
    ctxt.DeleteContext();
    xos << EndElem;
  }
  xos << EndElem;
}

void
WN2F_array_bounds(xml::ostream& xos, WN *wn, TY_IDX array_ty,XlationContext& ctxt)
{
  // FIXME: referenced in ty2xaif.cxx

  if (TY_is_f90_pointer(array_ty)) // FIXME (should this be moved up?)
    array_ty = TY_pointed(array_ty); //Sept
  
  // (TY_Is_Array(array_ty) && TY_AR_ndims(array_ty) >= WN_num_dim(wn)) 
  ASSERT_DBG_WARN((TY_AR_ndims(array_ty) == WN_num_dim(wn)),
		  (DIAG_UNIMPLEMENTED, "array dimension mismatch"));
  ASSERT_DBG_WARN((TY_size(TY_AR_etype(array_ty)) == WN_element_size(wn)) 
		  || WN_element_size(wn) < 0 
		  || TY_size(TY_AR_etype(array_ty)) == 0,
		  (DIAG_UNIMPLEMENTED, 
		   "access/declaration mismatch in array element size"));
  
  xlate_ArrayIndices(xos, wn, ctxt);
}

void
WN2F_arrsection_bounds(xml::ostream& xos, WN *wn, TY_IDX array_ty,XlationContext& ctxt)
{
  /* This prints the array subscript expression. It was part of
   * xlate_ARRAY, but was split so it could be used for bounds
   * of structure components.
   */
  if (TY_is_f90_pointer(array_ty))
    array_ty = TY_pointed(array_ty);//Sept
  
  if (TY_Is_Array(array_ty) && TY_AR_ndims(array_ty) >= WN_num_dim(wn)) {
    /* Cannot currently handle differing element sizes at place of
     * array declaration versus place of array access (TODO?). */
    
    ASSERT_DBG_WARN((TY_size(TY_AR_etype(array_ty)) == WN_element_size(wn)) ||
		    WN_element_size(wn) < 0 ||
		    TY_size(TY_AR_etype(array_ty)) == 0,
		    (DIAG_UNIMPLEMENTED,
		     "access/declaration mismatch in array element size"));
    
    WN2F_Arrsection_Slots(xos,wn,ctxt,TRUE);
    
  } else { /* Normalize array access to assume a single dimension */
    Is_True(FALSE, (""));
    ASSERT_DBG_WARN(!TY_Is_Array(array_ty) || TY_AR_ndims(array_ty) == 1,
		    (DIAG_UNIMPLEMENTED,
		     "access/declaration mismatch in array dimensions"));
    //FIXME: WN2F_Normalize_Idx_To_Onedim(xos, wn, ctxt);
  }
  
}

/*----------- Character String Manipulation Translation ---------------*/
/*---------------------------------------------------------------------*/

// FIXME: I don't think we nee this...
void
WN2F_String_Argument(xml::ostream& xos, WN* base_parm, WN* length,
		     XlationContext& ctxt)
{
  /* Append the xos denoting the substring expression represented
   * by the base-expression.
   *
   * There are two possibilities concerning the array base 
   * expressions.  It can be a pointer to a complete character-
   * string (array) or it can be a pointer to a character within 
   * a character-string (single character).  In the first instance,
   * the offset off the base of string is zero.  In the latter 
   * case, the offset is given by the array indexing operation.
   *
   * NOTE: In some cases (notably for IO_ITEMs), we may try to 
   * derive a substring off an OPC_VINTRINSIC_CALL node or a
   * VCALL node.  This should only happend when the returned value
   * is the first argument and the length is the second argument.
   */
  WN   *base = WN_Skip_Parm(base_parm);
  WN   *base1 = WN_Skip_Parm(base_parm);
  WN   *lower_bnd;
  WN   *length_new;
  WN   *arg_expr;
  TY_IDX str_ty;
  INT64 str_length;
  
  /* Skip any INTR_ADRTMP and INTR_VALTMP nodes */
  if (WN_operator(base) == OPR_INTRINSIC_OP &&
      (INTR_is_adrtmp(WN_intrinsic(base)) || 
       INTR_is_valtmp(WN_intrinsic(base)))) {
    base = WN_kid0(base);
  }
  
  if (WN_operator(base) == OPR_CVTL) {
    /* probably CHAR(INT) within IO stmt. convert via CHAR & process
       rest elsewhere */
    xos << "(char";
    TranslateWN(xos,WN_kid0(base),ctxt);
    xos << ')';
    return;
  }
  
  
  /* Handle VCALLs specially, since the string information is given
   * by the first two arguments to the call.  Note that we can 
   * always assume a lower bound of zero for these, as we never 
   * generate code for the return-address.  This should only occur
   * within an IO stmt.  Note that the type of VCALLs must be 
   * accessed in the ctxt of an ADRTMP or VALTMP.
   */
  if (WN_opcode(base) == OPC_VCALL ||
      WN_opcode(base) == OPC_VINTRINSIC_CALL) {
    arg_expr  = WN_Skip_Parm(WN_kid1(base));
    lower_bnd = WN2F_INTCONST_ZERO;
    
    /* fixed size string? */
    if (WN_operator(arg_expr) == OPR_INTCONST)
      str_length = WN_const_val(arg_expr);
    else
      str_length = -1 ;  
    
    ctxt.SetDerefAddr();
    TranslateWN(xos, base, ctxt);
    ctxt.ResetDerefAddr();
    
  } else {
    /* A regular address expression as base */    
    WN2F_Get_Substring_Info(&base, &str_ty, &lower_bnd, &length_new);
    
    /* Was this a character component of an array of derived type? */
    /* eg: vvv(2)%ccc(:)(1:5) - offset to ccc is added above base, */
    /* ADD(8,ARRAY(2,LDA VVV)) with array section for CCC on top   */
    /* of the ADD, and the substring above the array section. Take */
    /* the substring off the top, and process the rest             */    
    if (TY_kind(str_ty) == KIND_STRUCT) {
      FLD_PATH_INFO *fld_path ;
      FLD_HANDLE fld;
      TY_IDX  ty_idx ; 
      
      TY & ty = New_TY(ty_idx);
      
      TY_Init (ty, 1, KIND_SCALAR, MTYPE_U1, Save_Str(".w2fch."));
      Set_TY_is_character(ty);
      
      fld_path = TY2F_Get_Fld_Path(str_ty, 
				   ty_idx,
				   WN2F_Sum_Offsets(base));
      
      fld = TY2F_Last_Fld(fld_path);
      TY2F_Free_Fld_Path(fld_path);
      
      /* call memref for FLD offset, otherwise the ADD is */
      /* just another binary op                           */
      WN2F_Offset_Memref(xos, WN_kid0(base), WN_Tree_Type(base),
			 FLD_type(fld), 0, ctxt);
    } else {
      str_length = TY_size(str_ty);
      
      /* with optimization, may not have useful address TY 
       * when TreeType will return array of U1 from SubstringInfo */
      
      ASSERT_DBG_WARN(TY_Is_Character_String(str_ty) 
		      || TY_Is_Array_Of_UChars(str_ty),
		      (DIAG_W2F_EXPECTED_PTR_TO_CHARACTER,
		       "WN2F_String_Argument"));

      /* Get the string base and substring notation for the argument.  */
      ctxt.SetDerefAddr();
      TranslateWN(xos, base, ctxt);
      ctxt.ResetDerefAddr();
    }
# if 0
    /* need to take a look see when we need dump out substring--fzhao Jan*/ 
    if (WN_operator(base) != OPR_CALL &&
	WN_operator(base) != OPR_LDA &&
	(WN_operator(base1) != OPR_ARRAY ||
	 WN_operator(base1)==OPR_ARRAY &&
	 WN_operator(base)==OPR_ARRAY ))
# endif
      if (length_new != WN2F_INTCONST_ZERO 
	  && !XlationContext_has_no_arr_elmt(ctxt))
	WN2F_Substring(xos, str_length, lower_bnd,
		       // WN_Skip_Parm(length),
		       length_new, ctxt);
// fzhao Feb#endif
    return;
  }
} /* WN2F_String_Argument */


static WN2F_STATUS 
DumpVarRefEdge(xml::ostream& xos, UINT eid, UINT srcid, UINT targid)
{
  xos << BegElem(XAIFStrings.elem_VarRefEdge()) << Attr("edge_id", eid)
      << Attr("source", srcid) << Attr("target", targid)
      << EndElem;
  return EMPTY_WN2F_STATUS;
}
