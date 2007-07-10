// -*-Mode: C++;-*-
// $Header: /home/derivs2/mstrout/CVSRepository/UseNewOA-Open64/Open64IRInterface/wn_attr.h,v 1.2 2006/03/16 03:48:55 mstrout Exp $

#ifndef wn_attr_INCLUDED
#define wn_attr_INCLUDED

#include "Open64BasicTypes.h"


  /**
   * Access-macros and access-functions for obtaining attributes of 
   * WN trees for general use in translating WN to another language
   * form (e.g. to C or Fortran).  For the most part, this module
   * supplements common/com/wn_core.h.
 *
 *
 * Macros yielding OPCODE information:
 * -----------------------------------
 *
 *   INTR_is_adrtmp:
 *      An ADRTMP intrinsic opcode.
 *
 *   INTR_is_valtmp:
 *      An VALTMP intrinsic opcode.
 *
 * Functions yielding WN subtree information
 * ----------------------------------------
 *
 * WN_intrinsic_name:
 *      The name of the function or macro representing the intrinsic.
 *      Special handling is needed when the name is NULL.
 *
 * WN_intrinsic_return_ty:
 *      Map the intrinsic code to a return type.  If no return type
 *      is known, then use the result type of the OPCODE as the
 *      return type.
 *
 * WN_intrinsic_return_to_param:
 *      TRUE when the given return type is returned through the first
 *      parameter; FALSE when returning through pregs.
 *
 * Functions yielding WN subtree information
 * ----------------------------------------
 *
 *   WN_Get_PtrAdd_Intconst:
 *      Given the two operands of an ADD expression, see if this
 *      can be considered a pointer addition, and if it is return
 *      a pointer to an INTCONST that can be normalized w.r.t. the
 *      size of the pointed_ty; if the pointed_ty has size 1, then
 *      just return the integral expression operand when this should
 *      be considered a pointer addition; otherwise return NULL when
 *      this should not be considered a pointer addition.
 *
 *   WN_Tree_Type:
 *      The TY denoting the type of a WN expression.  For typeless
 *      WNs (e.g. statements), the TY will be "void" in C terminology.
 *      Similarly, there may be expression we cannot sensibly type,
 *      e.g. for MLOADs, in which case we return an inaccurate type.
 *      For MLOADs we return the type of a field at the given offset
 *      and of the given size, provided the size is known statically;
 *      otherwise we return the base-type.
 *
 * ====================================================================
 * ====================================================================
 */

/* several craylib/dope items represent a no-op by a zero inconst...*/
#define IS_IO_NULL_OPR(wn) ((WN_operator(wn) == OPR_INTCONST) && (WN_const_val(wn) == 0))

#define WN_IOITEM(x) ((IOITEM) WN_io_item(x))
#define WN_IOSTMT(x) ((IOSTATEMENT) WN_io_statement(x))

#define IS_IO_ITEM_IOU(item) \
   (WN_IOITEM(item) >= IOU_NONE && WN_IOITEM(item) <= IOU_INTERNAL)
#define IS_IO_ITEM_IOF(item) \
   ((WN_IOITEM(item) >= IOF_NONE && WN_IOITEM(item) <= IOF_CR_FMTSRC_DOPE))
#define IS_IO_ITEM_IOC(item) \
   (WN_IOITEM(item) >= IOC_ACCESS && WN_IOITEM(item) <= IOC_ERRFLAG)
#define IS_IO_ITEM_IOL(item) \
   ((WN_IOITEM(item) >= IOL_ARRAY && WN_IOITEM(item) <= IOL_VAR) || \
    (WN_IOITEM(item) == IOL_DOPE))

//***************************************************************************


#define INTR_is_adrtmp(intrn) \
   ((intrn) == INTRN_U4I1ADRTMP || \
    (intrn) == INTRN_U4I2ADRTMP || \
    (intrn) == INTRN_U4I4ADRTMP || \
    (intrn) == INTRN_U4I8ADRTMP || \
    (intrn) == INTRN_U4F4ADRTMP || \
    (intrn) == INTRN_U4F8ADRTMP || \
    (intrn) == INTRN_U4FQADRTMP || \
    (intrn) == INTRN_U4C4ADRTMP || \
    (intrn) == INTRN_U4C8ADRTMP || \
    (intrn) == INTRN_U4CQADRTMP || \
    (intrn) == INTRN_U4VADRTMP  || \
    (intrn) == INTRN_U8I1ADRTMP || \
    (intrn) == INTRN_U8I2ADRTMP || \
    (intrn) == INTRN_U8I4ADRTMP || \
    (intrn) == INTRN_U8I8ADRTMP || \
    (intrn) == INTRN_U8F4ADRTMP || \
    (intrn) == INTRN_U8F8ADRTMP || \
    (intrn) == INTRN_U8FQADRTMP || \
    (intrn) == INTRN_U8C4ADRTMP || \
    (intrn) == INTRN_U8C8ADRTMP || \
    (intrn) == INTRN_U8CQADRTMP || \
    (intrn) == INTRN_U8VADRTMP)

#define INTR_is_valtmp(intrn) \
   ((intrn) == INTRN_I4VALTMP || \
    (intrn) == INTRN_I8VALTMP || \
    (intrn) == INTRN_F4VALTMP || \
    (intrn) == INTRN_F8VALTMP || \
    (intrn) == INTRN_FQVALTMP || \
    (intrn) == INTRN_C4VALTMP || \
    (intrn) == INTRN_C8VALTMP || \
    (intrn) == INTRN_CQVALTMP)

#define WN_Skip_Parm(arg) \
   ((arg)!=NULL && WN_operator(arg) == OPR_PARM? WN_kid0(arg) : arg)


//***************************************************************************

extern TY_IDX 
WN_Tree_Type(const WN *wn);

extern TY_IDX 
Get_Field_Type(TY_IDX base, int field_id);

//***************************************************************************

// WN_GetRefObjType, WN_GetBaseObjType: For loads/stores, these are
// types for 1) the base object and 2) the referenced object.  The
// referenced object's address is at some offset (possibly 0) from the
// base object.  Loads refer the rvalue object; stores refer to the
// lvalue object.
extern TY_IDX 
WN_GetRefObjType(const WN* wn);

extern TY_IDX 
WN_GetBaseObjType(const WN* wn);


// Calls and intrinsic calls

extern TY_IDX 
WN_Call_Type(const WN* wn);

extern TY_IDX 
WN_Call_Return_Type(const WN* wn);

extern INT
WN_Call_First_Arg_Idx(const WN* wn);

extern INT
WN_Call_Last_Arg_Idx(const WN* wn);


extern const char * 
WN_intrinsic_name(INTRINSIC intr_opc);

extern TY_IDX 
WN_intrinsic_return_ty(const WN *call);

extern BOOL 
WN_intrinsic_return_to_param(TY_IDX return_ty);


extern WN *
WN_Get_PtrAdd_Intconst(WN* wn0, WN* wn1, TY_IDX pointed_ty);

//***************************************************************************

#endif 
