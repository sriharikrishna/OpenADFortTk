// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif.h,v 1.15 2004/02/17 22:24:11 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f.h
//
//***************************************************************************

#ifndef wn2xaif_INCLUDED
#define wn2xaif_INCLUDED
/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *   WN2F_Can_Assign_Types:
 *           This determines whether or not a value of type t1 can
 *           be used anywhere we expect a value of type t2.  When
 *           this condition is TRUE, yet t1 is different from t2,
 *           we expect the implicit Fortran type coersion to transform
 *           an object of one type to the other.
 *
 *   WN2F_Address_Of:
 *           Generates an expression to explicitly take the address 
 *           of the lvalue constituted by the tokens in the given
 *           token-buffer.
 *
 *   xlate_SymRef:
 *           Generate code to access the memory location denoted by
 *           the object type, based on the base-symbol, its given
 *           address type and the offset from the base of the symbol.
 *
 *   WN2F_Offset_Memref:
 *           Generate code to access the memory location denoted by
 *           the object type, based on the base-address expression,
 *           its given type and the offset from the base-address.
 *
 *   WN2F_initialize: This initializes any WN to Fortran translation
 *           and must always be called prior to any TranslateWN()
 *           call.
 *
 *   WN2F_finalize: This finalizes any WN to Fortran translation
 *           and should be called after all processing related
 *           to a whirl2f translation is complete.
 *
 *   TranslateWN:  Translates a WN subtree into a sequence of Fortran
 *           tokens, which are added to the given xml::ostream&.
 *
 *   WN2F_Sum_Offsets:  Sums any ADD nodes encountered in an address tree
 *
 * ====================================================================
 * ====================================================================
 */

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "whirl2f_common.h"
#include "XlationContext.h"
#include <lib/support/xmlostream.h>
#include <lib/support/WhirlIDMaps.h>
#include <lib/support/IntrinsicXlationTable.h>

//************************** Forward Declarations ***************************

//***************************************************************************
// 
//***************************************************************************

namespace whirl2xaif {

  extern IntrinsicXlationTable IntrinsicTable;

  extern void 
  WN2F_initialize(void);

  extern void 
  WN2F_finalize(void);
  
  extern whirl2xaif::status 
  TranslateWN(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
}; /* namespace whirl2xaif */


//***************************************************************************

// Declarations of top-level handler-functions for translation from
// WHIRL to XIAF. 
namespace whirl2xaif {

  extern whirl2xaif::status
  xlate_SymRef(xml::ostream& xos,
	       ST          *base_st,    /* base symbol */
  	       TY_IDX       baseptr_ty, /* type of base symbol ptr */
	       TY_IDX       ref_ty,     /* type of referenced object */
	       STAB_OFFSET  offset,     /* offset from base */
	       XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_FUNC_ENTRY(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_ALTENTRY(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_ignore(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_unknown(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
}; /* namespace whirl2xaif */


//***************************************************************************

// FIXME: 
// ForAllNonScalarRefsOp: Abstract base class for the operator passed
// to the function 'ForAllNonScalarRefs(...)'.  Any caller of this
// function must define its own operator object, using this class
// as a base class and providing a definition for 'operator()'.
class ForAllNonScalarRefsOp {
public:
  ForAllNonScalarRefsOp() { }
  virtual ~ForAllNonScalarRefsOp() { }

  // Given a non-scalar reference 'wn', does something interesting.
  // Returns 0 on success; non-zero on error.
  virtual int operator()(const WN* wn) = 0;
private: 
};


//FIXME: locate elsewhere...
#include <lib/support/SymTab.h> // FIXME

// Given a symbol table, add references to it
class AddToNonScalarSymTabOp : public ForAllNonScalarRefsOp {
public:
  AddToNonScalarSymTabOp(NonScalarSymTab* symtab_);
  ~AddToNonScalarSymTabOp() { }
  
  NonScalarSymTab* GetSymTab() { return symtab; }

  // Given a non-scalar reference 'wn', create a dummy variable and
  // add to the map.  
  int operator()(const WN* wn);

private:
  NonScalarSymTab* symtab;
};

void 
ForAllNonScalarRefs(const WN* wn, ForAllNonScalarRefsOp& op);

//***************************************************************************


    /* ---- Utilities to aid in WN to Fortran translation ---- */
    /* ------------------------------------------------------- */

// FIXME: convert to operation (from opcode)
#define WN2F_expr_has_boolean_arg(opc) \
   ((opc) == OPC_BLNOT || (opc) == OPC_BLAND || (opc) == OPC_BLIOR || \
    (opc) == OPC_I4LNOT || (opc) == OPC_I4LAND || (opc) == OPC_I4LIOR)


extern void WN2F_Address_Of(xml::ostream& xos);

extern whirl2xaif::status 
WN2F_Offset_Memref(xml::ostream& xos,
		   WN          *addr,        /* Base address */
		   TY_IDX       addr_ty,     /* type of base-address */
		   TY_IDX       object_ty,   /* type of object referenced */
		   STAB_OFFSET  addr_offset, /* offset from base */
		   XlationContext& ctxt);


extern WN_OFFSET WN2F_Sum_Offsets(WN *addr);

#endif /* wn2xaif_INCLUDED */
