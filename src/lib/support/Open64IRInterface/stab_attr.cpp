// -*-Mode: C++;-*-
#include "Open64BasicTypes.h"

//*************************** User Include Files ****************************

#include "stab_attr.h"

//************************** Forward Declarations ***************************

static BOOL
Stab_Compare_Types(TY_IDX t1, TY_IDX t2, BOOL check_quals, 
		   BOOL check_pointed_quals, BOOL check_scalars,
		   BOOL ptrs_as_scalars, BOOL assign_t2_to_t1);

#define TYPE_ALLOC_N(type, count)\
   TYPE_MEM_POOL_ALLOC_N(type, Malloc_Mem_Pool, count)

#define TYPE_REALLOC_N(type, old_ptr, old_count, new_count)\
   TYPE_MEM_POOL_REALLOC_N(type, Malloc_Mem_Pool, old_ptr,\
			   old_count, new_count)

#define FREE(ptr) MEM_POOL_FREE(Malloc_Mem_Pool, ptr)

//***************************************************************************

// REMOVE/FIXME

/*-------------------- Global SYMTAB table sizes --------------------
 *
 * We record the size of certain tables in the global symtab at whirl2c
 * initialization.  This information is then used later on in whirl2c
 * finialization to reset the tables back to their original size and
 * thus undo any additions made to these tables during whirl2c.
 *
 *--------------------------------------------------------------------*/

extern void Stab_initialize(void);
extern void Stab_finalize(void);

void
Stab_initialize(void)
{
   /* Record the original size of the Ty_Table, Fld_Table, Arb_Table,
      and Tylist_Table - per PU */

} /* Stab_Initialize */

void
Stab_finalize(void)
{
   /* Should ideally reset the Ty_Table, Fld_Table, Arb_Table, 
    * Tylist_Table and strtab (?) back to their original size at the 
    * start of whirl2c.  This is should also include resetting any 
    * references to such deleted symtab entries (e.g. TY_pointed).
    * For now we do not do so.
    */

} /* Stab_finalize */


void
Stab_Reset_Referenced_Flag(SYMTAB_IDX symtab)
{
  /* Reset the ST_is_referenced() flag for all symbols and constants
   * in the given symbol table.  Note that if this is done for the
   * global symbol-table for every PU (as I believe is necessary for
   * Fortran), we have an O(n^2 + m) algorithm where "n" is the number
   * of global symbols and "m" is the number of local PU symbols.
   */
  
  ST_IDX    st_idx;
  const ST* st;
  
  FOREACH_SYMBOL(symtab, st, st_idx)
    Clear_BE_ST_w2fc_referenced(st);
  
} /* Stab_Reset_Referenced_Flag */


//***************************************************************************
// Active Information
//***************************************************************************

bool
IsActivePU(ST* pu_st)
{
  bool active = true;

  TY_IDX pu_ty = ST_pu_type(pu_st);
  TY_IDX pu_ret_ty = TY_ret_type(pu_ty);

  if (ST_is_in_module(pu_st) && !PU_is_nested_func(Pu_Table[ST_pu(pu_st)])) {
    active = false; // module
  } 
  else if (pu_ret_ty != 0 && TY_kind(pu_ret_ty) != KIND_VOID) {
    active = false; // function
  }
  
  // assume subroutines are all active
  
  return active;
}


//***************************************************************************
// Type Information
//***************************************************************************

BOOL
Stab_Identical_Types(TY_IDX t1, TY_IDX t2, BOOL check_quals, 
		     BOOL check_scalars, BOOL ptrs_as_scalars)
{
   /* Compare the two types on an equal basis. */
   return Stab_Compare_Types(t1, t2, check_quals, FALSE,
			     check_scalars, ptrs_as_scalars, FALSE);
}


BOOL
Stab_Assignment_Compatible_Types(TY_IDX t1, TY_IDX t2, BOOL check_quals, 
				 BOOL check_scalars, BOOL ptrs_as_scalars)
{
   /* Compare the two types for assignment compatibility, assuming
    * a value of type t2 will be assigned to a location of type t1. */
   return Stab_Compare_Types(t1, t2, check_quals, FALSE, 
			     check_scalars, ptrs_as_scalars, TRUE);
}

bool
WN2F_Can_Assign_Types(TY_IDX ty1, TY_IDX ty2)
{
  bool simple = Stab_Identical_Types(ty1, ty2, FALSE, /*check_quals*/
				     FALSE, /*check_scalars*/ 
				     TRUE); /*ptrs_as_scalars*/
  bool special = (TY_Is_Array(ty1) && TY_is_character(ty1) && 
		  TY_Is_Array(ty2) && TY_is_character(ty2));
  return (simple || special);
}


static BOOL
Stab_Compare_Types(TY_IDX t1, TY_IDX t2, BOOL check_quals, 
		   BOOL check_pointed_quals, BOOL check_scalars,
		   BOOL ptrs_as_scalars, BOOL assign_t2_to_t1)
{
   /* Two types compare if they have the same qualifiers, compatible
    * kinds, compatible MTYPEs, and identical substructure.  ENUM
    * types are treated as scalars.  While constructed types must
    * have identical substructure, we allow more lenient checks for
    * the top-level types:  We can turn off qualifier checks 
    * (check_quals == FALSE); we can treat all scalar values as 
    * identical (check_scalars == FALSE); and we can treat pointers
    * as scalars (ptrs_as_scalars == TRUE).
    *
    * This routine can be adopted to the particular needs of whirl2c,
    * and as such is not implemented in terms of Equivalent_Types()
    * in common/com/ttype.h.
    */
  INT i; /* Array dimensions */

  if (t1 == t2)
     return TRUE;
  else if (TY_kind(t1) == KIND_INVALID || 
	   TY_kind(t2) == KIND_INVALID ||
	   (check_quals && !Stab_Identical_Quals(t1, t2)) ||
	   (check_pointed_quals && 
	    !Stab_Assign_Compatible_Pointer_Quals(t1, t2)))
     return FALSE;
  else
  {
     switch (TY_kind(t1))
     {
     case KIND_VOID:
	return TY_kind(t2) == KIND_VOID; /* Must be identical kinds */

     case KIND_SCALAR:
	if (TY_Is_String(t1) && TY_Is_Array_Of_Chars(t2))
	   return TRUE;
	else if (ptrs_as_scalars)
	   return (TY_Is_Pointer_Or_Scalar(t2) &&
		   (!check_scalars || TY_mtype(t1) == TY_mtype(t2)));
	else
	   return (TY_Is_Scalar(t2) &&
		   (!check_scalars || TY_mtype(t1) == TY_mtype(t2)));

     case KIND_POINTER:
	/* Should we also consider MTYPE_STRING identical to a (char*)? */
	if (ptrs_as_scalars)
	   return (TY_Is_Pointer_Or_Scalar(t2) &&
		   (!check_scalars || TY_mtype(t1) == TY_mtype(t2)));
	else
	   return 
	      (TY_Is_Pointer(t2) &&
	       (TY_kind(TY_pointed(t1)) == KIND_VOID ||
		TY_kind(TY_pointed(t2)) == KIND_VOID ||
		Stab_Compare_Types(
		   TY_pointed(t1), 
		   TY_pointed(t2), 
		   !assign_t2_to_t1,/* check_quals */
		   assign_t2_to_t1,/* check_pointed_quals */
		   TRUE,           /* check_scalars */
		   FALSE,          /* ptrs_as_scalars */
		   FALSE)));       /* assign_t2_to_t1 */

     case KIND_FUNCTION:
	/* We do a very quick check to see if two function types are
	 * identical.  A more elaborate, but slower, method will check
	 * each individual parameter type (TY_parms(t1) and TY_parms(t2))
	 * for identity.
	 */
	return (TY_Is_Function(t2)                           &&
		TY_has_prototype(t1) == TY_has_prototype(t2) &&
		TY_is_varargs(t1) == TY_is_varargs(t2)       &&
		TY_parms(t1) == TY_parms(t2)                 &&
		Stab_Compare_Types(Func_Return_Type(t1), 
				   Func_Return_Type(t2),
				   TRUE,  /* check_quals */
				   FALSE, /* check_pointed_quals */
				   TRUE,  /* check_scalars */
				   FALSE, /* ptrs_as_scalars */
				   FALSE) /* assign_t2_to_t1 */
		);

     case KIND_ARRAY:
	if (TY_Is_String(t2) && TY_Is_Array_Of_Chars(t1))
	   return TRUE;
	else if (!TY_Is_Array(t2) ||
		 TY_AR_ndims(t1) != TY_AR_ndims(t2))
	   return FALSE;
	else
	{
	   for (i=0; i<TY_AR_ndims(t1); i++)
	   {
	      /* First check if one constant and the other not;
	       * then check if constants don't match; we assume
	       * dynamic bounds/strides always match since we
	       * implement them in terms of pointers in C.
	       */
	      if (TY_AR_const_lbnd(t1,i) != TY_AR_const_lbnd(t2,i) ||
		  TY_AR_const_ubnd(t1,i) != TY_AR_const_ubnd(t2,i) ||
		  TY_AR_const_stride(t1,i) != TY_AR_const_stride(t2,i))
		 return FALSE;
	      else if (TY_AR_const_lbnd(t1,i) &&
		       (TY_AR_lbnd_val(t1,i) != TY_AR_lbnd_val(t2,i)))
		 return FALSE;
	      else if (TY_AR_const_ubnd(t1,i) &&
		       (TY_AR_ubnd_val(t1,i) != TY_AR_ubnd_val(t2,i)))
		 return FALSE;
	      else if (TY_AR_const_stride(t1,i) &&
		    (TY_AR_stride_val(t1,i) != TY_AR_stride_val(t2,i)))
		 return FALSE;
	   }
	   return Stab_Compare_Types(TY_AR_etype(t1), 
				     TY_AR_etype(t2),
				     TRUE,   /* check_quals */
				     FALSE,  /* check_pointed_quals */
				     TRUE,   /* check_scalars */
				     FALSE,  /* ptrs_as_scalars */
				     FALSE); /* assign_t2_to_t1 */
	}

     case KIND_STRUCT:
	return (TY_Is_Structured(t2) &&
                TY_flist(Ty_Table[t1]) == TY_flist(Ty_Table[t2]));

     default:
	ErrMsg ( EC_Invalid_Case, "Stab_Compare_Types", __LINE__ );
	return FALSE;
     }
  }
} /* Stab_Compare_Types */


//***************************************************************************

BOOL 
Stab_Is_Element_Type_Of_Array(TY_IDX atype, TY_IDX etype)
{
   if (Stab_Assignment_Compatible_Types(etype, TY_AR_etype(atype), 
					FALSE, /*check_quals*/
					TRUE,  /*check_scalars*/
					FALSE)) /*ptrs_as_scalars*/
      return TRUE;
   else if (TY_Is_Array(TY_AR_etype(atype)))
      return Stab_Is_Element_Type_Of_Array(TY_AR_etype(atype), etype);
   else
      return FALSE;
} /* Stab_Is_Element_Type_Of_Array */


BOOL
Stab_Array_Has_Dynamic_Bounds(TY_IDX ty)
{
   INT32 dim;
   BOOL is_const = TRUE;
   
   for (dim = 0; dim < TY_AR_ndims(ty); dim++)
   {
      is_const = (is_const                  &&
		  TY_AR_const_lbnd(ty, dim) &&
		  TY_AR_const_ubnd(ty, dim) &&
		  TY_AR_const_stride(ty, dim));
   }
   return !is_const;
} /* Stab_Array_Has_Dynamic_Bounds */


BOOL
Stab_Is_Assumed_Sized_Array(TY_IDX ty)
{
   BOOL assumed_size = FALSE;

   if (TY_Is_Array(ty))
   {
      /* Only the last bound may be assumed sized.  Multi-dimensional
       * arrays in whirl are represented in row-major order (as in
       * C/C++).  Therefore, check the first dimension in the TY which
       * is the last Fortran dimension.
       */
      ARB_HANDLE arb = TY_arb(ty);
      
      if (ARB_const_lbnd(arb) && 
	  ARB_const_ubnd(arb) &&
	  (ARB_ubnd_val(arb) - ARB_lbnd_val(arb) <= 0))
      {
	 assumed_size = TRUE;
      }
      else if ((!ARB_const_lbnd(arb) && ARB_lbnd_var(arb) == (ST_IDX) 0) ||
	       (!ARB_const_ubnd(arb) && ARB_ubnd_var(arb) == (ST_IDX) 0))
      {
	 assumed_size = TRUE;
      }
   }
   return assumed_size;
} /* Stab_Is_Assumed_Sized_Array */


BOOL 
Stab_Is_Equivalenced_Struct(TY_IDX ty)
{
   FLD_ITER fld_iter = Make_fld_iter (TY_flist(Ty_Table[ty]));
   BOOL is_equivalent_fld = FALSE;

   do {
       FLD_HANDLE fld (fld_iter);
       is_equivalent_fld = FLD_equivalence (fld);
   } while (!FLD_last_field (fld_iter++) && !is_equivalent_fld);
       
   return is_equivalent_fld;
} /* Stab_Is_Equivalenced_Struct */


TY_IDX
Stab_Get_Mload_Ty(TY_IDX base, STAB_OFFSET offset, STAB_OFFSET size)
{
   /* Just try to find a field of the given size at the given offset.
    * The base should be a struct or union type Return the base
    * when it has the desired size or a size of zero (unknown size)
    */
   TY_IDX ty;
   
   Is_True(TY_Is_Structured(base),
	   ("Expected pointer to struct/union type in TY2C_Get_Mload_Ty()"));
   Is_True((INT64)TY_size(base) <= size,
	   ("Expected struct/union type >= size in TY2C_Get_Mload_Ty()"));
   
   if ((INT64)TY_size(base) == size ||
       (TY_size(base) == 0 && TY_flist(Ty_Table[base]).Is_Null ()))
   {
      /* End of recursive descent into the structure, so return
       * the base type.
       */
      ty = base;
   }
   else
   {
      /* Get the field we wish to access, then apply this algorithm
       * recursively.
       */
      Is_True(!TY_flist(Ty_Table[base]).Is_Null (),
	      ("Expected non-empty field list in TY2C_Get_Mload_Ty()"));
      
      FLD_HANDLE this_fld = TY_flist(Ty_Table[base]);
      FLD_HANDLE next_fld = FLD_next(this_fld);
      if (TY_Is_Union(base))
      {
	 /* Search for a struct or union field of the expected size */
	 while (! next_fld.Is_Null () &&
		(!TY_Is_Structured(FLD_type(this_fld)) ||
		 (INT64)TY_size(FLD_type(this_fld)) < size))
	 {
	    this_fld = next_fld;
	    next_fld = FLD_next(next_fld);
	 }
      }
      else /* TY_Is_Struct(TY_pointed(base)) */
      {
	 /* Search for a struct or union field at the expected offset */
	 while (! next_fld.Is_Null () && (INT64)FLD_ofst(next_fld) <= offset)
	 {
	    this_fld = next_fld;
	    next_fld = FLD_next(next_fld);
	 }
      }
      
      Is_True(!this_fld.Is_Null () &&
	      (INT64)FLD_ofst(this_fld) <= offset           &&
	      (INT64)FLD_ofst(next_fld) >= offset           &&
	      (TY_Is_Structured(FLD_type(this_fld))) &&
	      (INT64)TY_size(FLD_type(this_fld)) >= size, 
	      ("Could not find a field as expected in TY2C_Get_Mload_Ty()"));

      ty = Stab_Get_Mload_Ty(FLD_type(this_fld), 
			     offset-FLD_ofst(this_fld),
			     size);
   }
   return ty;
} /* Stab_Get_Mload_Ty */


//***************************************************************************
// Type creation
//***************************************************************************

extern TY_IDX
Stab_Array_Of(TY_IDX etype, mINT64 num_elts)
{
  /* Make a 1d array of (pointer?) types. Must handle 0-sized objects */
  /* and structs - Make_Array_Type doesn't like structs ...........*/

  TY_IDX  ty_idx;

  ARB_HANDLE arb = New_ARB ();

//  ARB_Init (arb, 0, num_elts - 1, TY_size(etype));

/* here,since we keep all arrays lower bound and upper bound     */
/* same with the source files,we have to change this function     */
/* set lower bound is 1 and upper bound is num_elts to consistent */
/*with our source level definition----fzhao                       */

  ARB_Init (arb, 1, num_elts , TY_size(etype));

  Set_ARB_dimension (arb,1);
  Set_ARB_last_dimen (arb);
  Set_ARB_first_dimen (arb);

  TY& ty = New_TY (ty_idx);
  TY_Init (ty, TY_size(etype) * num_elts,KIND_ARRAY, MTYPE_UNKNOWN,0);

  Set_TY_align (ty_idx, TY_size(etype));
  Set_TY_etype (ty, etype);
  Set_TY_arb (ty, arb);

  return ty_idx;
}   


//***************************************************************************
// Identifier naming utilities
//***************************************************************************

/*---------------------- Name manipulation -----------------------
 *
 *    We operate with a cyclic character buffer for identifier names,
 *    where the size of the buffer is a minimum of 1024 characters
 *    and at a maximum of 8 times the largest name encountered.  Note 
 *    that a call to any of the functions described below may allocate
 *    a new name buffer.  Name buffers are allocated from the cyclic
 *    character buffer, and a name-buffer may be reused at every 8th
 *    (MIN_NAME_SLOTS) allocation.  We guarantee that a name-buffer is 
 *    valid up until 7 subsequent name-buffer allocations, but no 
 *    longer.  After 7 subsequent name-buffer allocations, the name 
 *    buffer may be reused (overwritten) or even freed up from dynamic
 *    memory.  While the results from the calls to the functions 
 *    provided here may be used to construct identifier names, these 
 *    results should be saved off into a more permanent buffer area 
 *    once the names have been constructed.
 *----------------------------------------------------------------*/

#define MIN_NAME_SLOTS 8
#define MIN_NAME_BUF_SIZE 1024
#define MAX_NUMSTRING_SIZE 128

static char *Name_Buf;
static UINT Name_Buf_Idx = 0;  /* Next available Name_Buf character */
static UINT Name_Buf_Size = 0; /* Size of Name_Buf */

static char *buffer_to_be_freed[MIN_NAME_SLOTS];
static UINT  next_delay_slot = 0;
static UINT  delay_count[MIN_NAME_SLOTS] = {0, 0, 0, 0, 0, 0, 0, 0};
static INT   next_to_be_freed = -1;


void
Stab_Free_Namebufs(void)
{
   /* Called at the end of processing every PU.
    */
   INT i;
   
   if (next_to_be_freed > 0)
   {
      for (i=0; i < MIN_NAME_SLOTS; i++)
         if (delay_count[i] > 0)
         {
            FREE(buffer_to_be_freed[i]);
            delay_count[i] = 0;
         }
      next_to_be_freed = -1;
      next_delay_slot = 0;
   }
   if (Name_Buf_Size > 0)
   {
      FREE(Name_Buf);
      Name_Buf_Idx = Name_Buf_Size = 0;
   }
} /* Stab_Free_Namebufs */


char * 
Get_Name_Buf_Slot(UINT size)
{
   char *name_slot;
   
   /* See if it is time to free up a buffer */
   if (next_to_be_freed >= 0 && 
       delay_count[next_to_be_freed] > 0)
   {
      delay_count[next_to_be_freed]--;
      if (delay_count[next_to_be_freed] == 0)
      {
	 FREE(buffer_to_be_freed[next_to_be_freed]);
	 buffer_to_be_freed[next_to_be_freed] = NULL;
	 next_to_be_freed = (next_to_be_freed + 1) % MIN_NAME_SLOTS;
      }
   }
   
   /* See if we need a larger name-buffer */
   if (size*MIN_NAME_SLOTS > Name_Buf_Size)
   {
      /* (Re)allocate the character buffer */
      if (Name_Buf_Size > 0)
      {
	 /* Delay freeing until this function has been called
	  * MIN_NAME_SLOTS times.
	  */
	 buffer_to_be_freed[next_delay_slot] = Name_Buf;
	 delay_count[next_delay_slot] = MIN_NAME_SLOTS;
	 next_delay_slot = (next_delay_slot + 1) % MIN_NAME_SLOTS;
	 
	 /* Allocate a new buffer */
	 Name_Buf = TYPE_ALLOC_N(char, size*MIN_NAME_SLOTS);
	 Name_Buf_Size = size*MIN_NAME_SLOTS;
      }
      else
      {
	 UINT s = MIN_NAME_BUF_SIZE;

	 if (size*MIN_NAME_SLOTS > s) s = size*MIN_NAME_SLOTS;
	 Name_Buf = TYPE_ALLOC_N(char, s);
	 Name_Buf_Size = s;
      }
   }

   /* If the name does not fit in the unused part of the (cyclic)
    * buffer, then restart allocation of name slots at the beginning
    * of the buffer.
    */
   if (size + Name_Buf_Idx > Name_Buf_Size)
      Name_Buf_Idx = 0;

   /* Allocate a slot for the name within the buffer */
   name_slot = &Name_Buf[Name_Buf_Idx];
   Name_Buf_Idx += size;

   return name_slot;
} /* Get_Name_Buf_Slot */


const char * 
Num2Str(INT64 number, const char *fmt)
{
   char *new_name = Get_Name_Buf_Slot(MAX_NUMSTRING_SIZE);

   sprintf(new_name, fmt, number);
   return new_name;
} /* Num2Str */


const char * 
Ptr_as_String(const void *ptr)
{
   char *new_name = Get_Name_Buf_Slot(MAX_NUMSTRING_SIZE);
   union 
   {
      const void *ptr;
      UINT32      u32;
      UINT64      u64;
   } ptr_as_number;

   ptr_as_number.ptr = ptr;
   
   if (sizeof(void *) == sizeof(UINT32))
      sprintf(new_name, "%u", ptr_as_number.u32);
   else if (sizeof(void *) == sizeof(UINT64))
      sprintf(new_name, "%llu", ptr_as_number.u64);
   else
      Is_True(FALSE, ("Unknown pointer size in Ptr_as_String()"));
   
   return new_name;
} /* Ptr_as_String */


const char *
StrCat(const char *name1, const char *name2)
{
  /* Construct a new name by concatenating two other names.  The
   * new name will be put into a new name buffer.
   */
  INT   name1_length;
  INT   name2_length;
  char *new_name;
  
  if (name1 == NULL)
    return name2;
  else if (name2 == NULL)
    return name1;
  else if (*name1 == '\0')
    return name2;
  else if  (*name2 == '\0')
    return name1;
  else {
    name1_length = strlen(name1);
    name2_length = strlen(name2);
    new_name = Get_Name_Buf_Slot(name1_length + name2_length + 1);
    
    (void)strcpy(new_name, name1);
    (void)strcpy(&new_name[name1_length], name2);
    
    return new_name;
  }
} /* StrCat */


UINT64
Get_Hash_Value_For_Name(const char *name)
{
   /* Assume alpha-numeric characters only differ in the least
    * significant 6 bits.  Take only the rightmost characters
    * into account.
    */
   INT64       hash_value = 0;
   const char *cptr;

   if (name != NULL) 
   {
      for (cptr=name; *cptr != '\0'; cptr++)
	 hash_value = (hash_value << (INT64)6) + (INT64)*cptr;
   }  /* if */
   if (hash_value < 0)
      hash_value = -hash_value;

   return hash_value;
} /* Get_Hash_Value_For_Name */


STAB_OFFSET 
Stab_Full_Split_Offset(const ST *split_out_st)
{
   const char *name = ST_name(split_out_st);
   INT         i;
   STAB_OFFSET offset = 0;
   UINT64      digit = 1;

   for (i = strlen(name) - 1;
	i >= 0 && '0' <= name[i] && '9' >= name[i];
	i--)
   {
      offset += (STAB_OFFSET)(name[i] - '0') * digit;
      digit *= 10;
   }
   return offset;
} /* Stab_Full_Split_Offset */


/*------------- Utilities for creating temporary variables ------------
 * 
 * Maintains an array of TMPVARINFOs, such that a tmpvar can be
 * reused whenever the type matches that of an existing tempvar and
 * it is not "locked".  The array is indexed by a unique tmpvar
 * number.
 *---------------------------------------------------------------------*/

typedef struct TmpVarInfo
{
   TY_IDX      ty;
   BOOL        locked;
} TMPVARINFO;

#define TMPVAR_ALLOC_INCREMENTS 32
static TMPVARINFO *TmpVar = NULL;
static INT Next_Tmpvar_Idx = 0;
static INT Max_Tmpvar_Idx = -1;


void
Stab_Free_Tmpvars(void)
{
   /* Called at the end of processing every PU.
    */
   if (TmpVar != NULL)
   {
      FREE(TmpVar);
      TmpVar = NULL;
      Next_Tmpvar_Idx = 0;
      Max_Tmpvar_Idx = -1;
   }
} /* Stab_Free_Tmpvars */


UINT 
Stab_Lock_Tmpvar(TY_IDX ty, 
		 void (*declare_tmpvar)(TY_IDX, UINT))
{
   /* Find an available (unlocked) temporary variable of the
    * given type, and if none is available, then declare a new
    * one.
    */
   INT idx;
   
   /* See if we have an available tmpvar of a compatible type */
   for (idx = Next_Tmpvar_Idx - 1;
	(idx >= 0 &&
	 (TmpVar[idx].locked ||
	  !Stab_Identical_Types(TmpVar[idx].ty, ty, FALSE, TRUE, FALSE)));
	idx--);
   
   if (idx < 0)
   {
      /* Could not find a suitable temporary variable, so declare
       * a new one and set "idx" to index this new entry.
       */
      if (Max_Tmpvar_Idx <= 0)
      {
	 /* Need to allocate the TmpVar array */
	 TmpVar = TYPE_ALLOC_N(TMPVARINFO, TMPVAR_ALLOC_INCREMENTS);
	 Max_Tmpvar_Idx = TMPVAR_ALLOC_INCREMENTS;
      }
      if (Next_Tmpvar_Idx >= Max_Tmpvar_Idx)
      {
	 /* Need to reallocate the TmpVar array */
	 TmpVar = TYPE_REALLOC_N(TMPVARINFO, 
				 TmpVar, 
				 Next_Tmpvar_Idx,
				 Next_Tmpvar_Idx + TMPVAR_ALLOC_INCREMENTS);
	 Max_Tmpvar_Idx += TMPVAR_ALLOC_INCREMENTS;
      }
      idx = Next_Tmpvar_Idx++;
      TmpVar[idx].ty = ty;
      declare_tmpvar(ty, idx);
   }
   TmpVar[idx].locked = TRUE;
   return idx;
} /* Stab_Lock_Tmpvar */


void
Stab_Unlock_Tmpvar(UINT idx)
{
   Is_True((INT)idx < Next_Tmpvar_Idx, 
	   ("Tmpvar index out of range in Stab_Unlock_Tmpvar()"));
   
   TmpVar[idx].locked = FALSE;
} /* Stab_Unlock_Tmpvar */


