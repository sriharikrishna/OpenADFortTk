// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/wn2xaif_pragma.cxx,v 1.2 2003/05/14 01:10:12 eraxxon Exp $
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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/wn2xaif_pragma.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f_pragma.cxx
//
//***************************************************************************

/* ====================================================================
 * ====================================================================
 *
 * Description:
 *
 *   Translate a pragma WN node to Fortran!  The corresponding header
 *   declaration for for WN2F_pragma() can be found in wn2f_pragma.h.
 *
 * ====================================================================
 * ====================================================================
 */

//************************** System Include Files ***************************

#include <alloca.h>

//************************** Open64 Include Files ***************************

#include "Open64BasicTypes.h" /* Open64 basic types */
#include "const.h"           /* For FOR_ALL_CONSTANTS */
#include "pf_cg.h"
#include "region_util.h"     /* For RID and RID_map */

//*************************** User Include Files ****************************

#include "whirl2f_common.h"
#include "w2cf_parentize.h"  /* For W2CF_Get_Parent */
#include "PUinfo.h"
#include "wn2xaif.h"
#include "st2f.h"
#include "ty2f.h"
#include "tcon2f.h"
#include "wn2f_pragma.h"

//************************** Forward Declarations ***************************

using namespace whirl2xaif;

//************************** Forward Declarations ***************************

extern BOOL    Run_w2fc_early;      /* Defined in be.so */
extern WN_MAP *W2F_Construct_Map;   /* Defined in w2f_driver.c */


#define WN_pragma_nest(wn) WN_pragma_arg1(wn)
#define WN_max_nest_level(wn) WN_pragma_arg2(wn)
#define WN_mp_schedtype(wn) (WN_PRAGMA_SCHEDTYPE_KIND)WN_pragma_arg1(wn)

#define EMIT_ARG_NUMBERS1(tokens, val1) \
   Append_Arg_Numbers((tokens), (val1), -1)

#define EMIT_ARG_NUMBERS2(tokens, val1, val2) \
   Append_Arg_Numbers((tokens), (val1), (val2))

#define PARENTHESIZE_ARG_NUMBERS1(tokens, val1) \
   (tokens) << "("; \
   EMIT_ARG_NUMBERS1((tokens), (val1)); \
   (tokens) << ")"

#define PARENTHESIZE_ARG_NUMBERS2(tokens, val1, val2) \
   (tokens) << "("; \
   EMIT_ARG_NUMBERS2((tokens), (val1), (val2)); \
   (tokens) << ")"


typedef struct Array_Distribution
{
   INT current_dimension;  /* Enumerated dimension number in C order */
   WN *base;               /* PRAGMA starting description of this dimension */
   WN *cyclic_expr;        /* XPRAGMA holding a cyclic expression (or NULL) */
   WN *dimension_bound;    /* XPRAGMA holding the bounds expression */
} ARRAY_DISTRIBUTION;


#define MAX_PRAGMAS_TO_SKIP 50
static struct Set_Of_Pragmas_To_Skip
{
   INT start, end;
   WN *array[MAX_PRAGMAS_TO_SKIP];
} Pragmas_To_Skip = {0, 0, 
		     {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
		      NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
		      NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
		      NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
		      NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}};


typedef struct Local_Preg /* Used in Get_Implicit_Locals() */
{
   ST *     st;
   PREG_IDX preg_idx;
} LOCAL_PREG;


static WN * WN2F_Prompf_Subsection = NULL;

//***************************************************************************


/* ======================= Prompf utilities ======================= */
/* ================================================================ */

//REMOVE
inline BOOL
WN2F_is_omp(const WN *pragma)
{
   return (WN_pragma_omp(pragma) ||
	   (/*W2F_Emit_Omp &&*/ WN_pragma_compiler_generated(pragma)));
}

#if 0 //REMOVE
static void 
WN2F_Start_Prompf_Construct(xml::ostream& xos, WN *pragma)
{
   INT32 construct_id = WN_MAP32_Get(*W2F_Construct_Map, pragma);

   Append_F77_Directive_Newline(tokens, sgi_comment_str);
   Append_Token_String(tokens, "start");
   Append_Token_String(tokens, Num2Str(construct_id, "%llu"));
} /* WN2F_End_Prompf_Construct */
#endif //REMOVE

#if 0 //REMOVE
static void 
WN2F_End_Prompf_Construct(xml::ostream& xos, WN *pragma)
{
   INT32 construct_id = WN_MAP32_Get(*W2F_Construct_Map, pragma);

   Append_F77_Directive_Newline(tokens, sgi_comment_str);
   Append_Token_String(tokens, "end");
   Append_Token_String(tokens, Num2Str(construct_id, "%llu"));
} /* WN2F_End_Prompf_Construct */
#endif //REMOVE

static void 
WN2F_Directive_Newline(xml::ostream& xos,
		       const char  *directive_prefix,
		       SRCPOS       srcpos)
{
  //Append_F77_Directive_Newline(xos, directive_prefix);
  xos << directive_prefix << std::endl;
#if 0
  if (W2F_File[W2F_LOC_FILE] != NULL)
    Append_Srcpos_Map(xos, srcpos);
#endif
} /* WN2F_Directive_Newline */


/* ======================= Static Functions ======================= */
/* ================================================================ */


static void 
WN2F_Append_Pragma_Preamble(xml::ostream& xos,WN * apragma)
{
  /* 
   * appends a PAR or OMP depending on the setting of
   * the omp flag on the pragma node
   *
   */
 
  if (WN2F_is_omp(apragma))
    xos << "OMP";
  else
    xos << "PAR";
}


/* we use this function instead WN2F_Append_Pragma_Preamble to generate OMP and PAR directives */
/* the directive prefix needs to be C$OMP or C$PAR, otherwise the continuation line prefix is wrong */
/* e.g. continuation line prefix is $& instead of $OMP& (radu@par.univie.ac.at) */
static void
WN2F_OMP_or_PAR_Directive_Newline(xml::ostream& xos,WN * apragma)
{
  if (WN2F_is_omp(apragma))
    WN2F_Directive_Newline(xos, "C$OMP", WN_Get_Linenum(apragma));
  else
    WN2F_Directive_Newline(xos, "C$PAR", WN_Get_Linenum(apragma));
  /* force a space after the directive prefix (radu@par.univie.ac.at) */
  /* this is not automatically emited because of MIPSpro C$ directive prefix */
  //xos << " ";
}


static void 
Append_Reduction_Operator(xml::ostream& xos,OPERATOR op)
{
  /* 
   * appends a symbol representing an OMP reduction operator.
   */

  const char * p;

  switch(op) 
    {
    case OPR_MAX:
      p = "MAX";
      break;

    case OPR_MIN:
      p = "MIN";
      break;

    case OPR_BAND:
      p = "IAND";
      break;

    case OPR_BIOR:
      p = "IOR";
      break;

    case OPR_BXOR:
      p = "IEOR";
      break;

    case OPR_LAND:
      p = ".AND.";
      break;

    case OPR_LIOR:
      p = ".OR.";
      break;

    case OPR_EQ:
      p = ".EQV.";
      break;

    case OPR_NE:
      p = ".NEQV.";
      break;

    case OPR_ADD:
      p = "+";
      break;

    case OPR_MPY:
       p = "*";
      break;

    case OPR_SUB:
      p = "-";
      break;

    default:
      p = "?" ;
  }   
  xos << p << " :";
}

static BOOL
Is_Valid_Doacross(WN *doacross)
{
   /* Return TRUE if the enclosing region has a body containing nothing
    * other than an OPR_DO_LOOP node.  Only when returning TRUE may a 
    * DOACROSS directive be emipwdtted prior to the region body.
    */
   const WN *region = W2CF_Get_Parent(W2CF_Get_Parent(doacross));
   WN *region_body;

   ASSERT_DBG_FATAL(WN_operator(region) == OPR_REGION, 
		    (DIAG_W2F_UNEXPECTED_OPC, "Is_Valid_Doacross"));

   region_body = WN_region_body(region);
   return (WN_operator(WN_first(region_body)) == OPR_DO_LOOP &&
	   WN_first(region_body) == WN_last(region_body));
} /* Is_Valid_Doacross */


static void
Put_Pragma_Start_With_Caveats(xml::ostream& xos, WN *apragma, BOOL warn)
{
  /* It may be transformations have stuffed some code before
   * a doacross, pdo or parallel do. This is not strictly allowed
   * when compiling (ie: w2f output), so warn about the 
   * misplaced items, if warn is set. eg: if ENDDO etc comes through,
   * omit the warning.
   */

  if (Is_Valid_Doacross(apragma))
    WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
#if 0 // REMOVE
  else if (W2F_Prompf_Emission)
    WN2F_Directive_Newline(xos, "CC$", WN_Get_Linenum(apragma));
#endif // REMOVE
  else
    {
      WN2F_Directive_Newline(xos,"C<misplaced>$", WN_Get_Linenum(apragma));

      if ( warn ) 
	{
	  if (WN_pragma(apragma) == WN_PRAGMA_DOACROSS)
	    ASSERT_WARN(FALSE, (DIAG_W2F_MISPLACED_PRAGMA, "DOACROSS"));
	  else if (WN_pragma(apragma) == WN_PRAGMA_PDO_BEGIN)
	    ASSERT_WARN(FALSE, (DIAG_W2F_MISPLACED_PRAGMA, "PDO"));
	  else
	    ASSERT_WARN(FALSE, (DIAG_W2F_MISPLACED_PRAGMA, "PARALLEL DO"));
	}
    }
}

static BOOL
Preg_Is_In_Clause_List(const WN *clause_list, ST *preg_st, PREG_IDX preg_idx)
{
   /* Returns TRUE when the given preg is already referenced in a LOCAL,
    * LASTLOCAL, SHARED or REDUCTION clause in the given clause list; 
    * otherwise we return FALSE.
    */
   BOOL found = FALSE;

   while (!found && clause_list != NULL)
   {
      switch (WN_pragma(clause_list))
      {
      case WN_PRAGMA_LOCAL:
      case WN_PRAGMA_LASTLOCAL:
      case WN_PRAGMA_SHARED:
      case WN_PRAGMA_FIRSTPRIVATE:
      case WN_PRAGMA_REDUCTION:
      case WN_PRAGMA_COPYPRIVATE:
	 if (WN_operator(clause_list) != OPR_XPRAGMA &&
	     WN_st(clause_list) == preg_st && 
	     WN_pragma_arg1(clause_list) == preg_idx)
	 {
	    found = TRUE;
	 }
	 break;
      default:
	 break;
      }
      clause_list = WN_next(clause_list);
   }
   return found;
} /* Preg_Is_In_Clause_List */


static void
Get_Implicit_Locals(WN_PRAGMA_ID  kind,              /* in */
		    const WN     *wn,                /* in */
		    const WN     *clauses,           /* in */
		    LOCAL_PREG  **ptr_to_local_list, /* in/out */
		    UINT         *next_local,        /* in/out */
		    UINT         *max_locals)        /* in/out */
{
   /* Puts the implicit locals into the local_list.  Every element of the
    * local list must represent a unique preg.
    */
   OPERATOR opr = WN_operator(wn);
   ST      *st;
   PREG_IDX preg_idx;

   /* Get the preg attributes (st, offset) if this is a preg reference
    */
   switch (opr)
   {
   case OPR_LDA:
      st = WN_st(wn);
      preg_idx = WN_lda_offset(wn);
      break;
   case OPR_LDID:
      st = WN_st(wn);
      preg_idx = WN_load_offset(wn);
      break;
   case OPR_STID:
      st = WN_st(wn);
      preg_idx = WN_store_offset(wn);
      break;
   default:
      st = NULL;
      preg_idx = 0;
   }

   /* Add a preg reference to the local_list.
    */
   if (st != NULL &&
       ST_sym_class(st) == CLASS_PREG &&
       !Preg_Is_In_Clause_List(clauses, st, preg_idx))
   {
      /* Unless the preg is already in the local list, add it.
       */
      INT         i;
      BOOL        found = FALSE;
      LOCAL_PREG *local_list = *ptr_to_local_list;

      for (i = 0; !found && i < *next_local; i++)
	 if (local_list[i].st == st && local_list[i].preg_idx == preg_idx)
	    found = TRUE;

      if (!found)
      {
         if (*next_local >= *max_locals)
         {
            /* Need to reallocate the local_list buffer.  Use increments
             * of 200 elements for each reallocation.
             */
            *max_locals += 200;
            local_list = TYPE_ALLOC_N(LOCAL_PREG, *max_locals);

            /* Copy old values into new list, and free up the old list.
             */
            if (*ptr_to_local_list != NULL)
            {
               for (i = 0; i < *next_local; i++)
                  local_list[i] = (*ptr_to_local_list)[i];
               FREE(*ptr_to_local_list);
            }
            *ptr_to_local_list = local_list;
         }

         /* Enter new element into the local_list.
          */
	 local_list[*next_local].st = st;
	 local_list[*next_local].preg_idx = preg_idx;
	 (*next_local)++;
      }
   }
       
   /* Look for preg references in kids
    */
   if (!OPCODE_is_leaf(WN_opcode(wn)))
   {
      if (opr == OPR_REGION)
      {
	 /* Skip a pdo or a parallel_do inside a parallel region, since
	  * such nested regions will be handled independently.
	  *
	  * NO LONGER DO THIS, SINCE WE NO LONGER DO IMPLICIT SEARCHES
          * ON SUCH NESTED CONSTRUCTS.
	  *
	  * WN *pragma = WN_first(WN_region_pragmas(wn));
	  * if (kind != WN_PRAGMA_PARALLEL_BEGIN         ||
	  *   pragma == NULL                           ||
	  *   (WN_pragma(pragma) != WN_PRAGMA_PDO_BEGIN      && /may occur /
          *    WN_pragma(pragma) != WN_PRAGMA_PARALLEL_BEGIN && /impossible?/
          *    WN_pragma(pragma) != WN_PRAGMA_PARALLEL_DO    && /impossible?/
          *    WN_pragma(pragma) != WN_PRAGMA_DOACROSS))        /impossible?/
	  *{
	  */
	 Get_Implicit_Locals(kind, WN_region_body(wn), clauses, 
			     ptr_to_local_list, next_local, max_locals);
      }
      else if (opr == OPR_BLOCK)
      {
	 const WN* kid = WN_first(wn);
	 while (kid)
	 {
	    Get_Implicit_Locals(kind, kid, clauses,
                                ptr_to_local_list, next_local, max_locals);
	    kid = WN_next(kid);
	 }
      }
      else
      {
	 INT       kidno;
	 const WN* kid;
	 for (kidno=0; kidno < WN_kid_count(wn); kidno++)
	 {
	    kid = WN_kid (wn, kidno);
	    if (kid) 
	    { 
	       Get_Implicit_Locals(kind, kid, clauses, 
                                   ptr_to_local_list, next_local, max_locals);
	    }
	 }
      }
   }
} /* Get_Implicit_Locals */


static void
Append_Implicit_Locals(xml::ostream& xos,
		       WN_PRAGMA_ID region_kind,
		       const WN    *region_body,
		       const WN    *region_clauses)
{
   /* This will append implicit LOCAL clauses to the xos, assuming
    * the regular clauses already have been appended to the tokens.
    */
   LOCAL_PREG *local_list = NULL;
   UINT        i, number_of_locals = 0, max_number_of_locals = 0;

   /* Get the list of implicit locals.
    */
   Get_Implicit_Locals(region_kind, region_body, region_clauses,
		       &local_list, &number_of_locals, &max_number_of_locals);

   /* Add make the implicit LOCAL clauses explicit in the token buffer
    */
   if (number_of_locals > 0)
   {
      if (region_clauses != NULL)
	 xos << ",";

      /* generate valid OpenMP PRIVATE clause (radu@par.univie.ac.at) */
      if(! WN2F_is_omp(region_clauses))
        xos << "local";
      else
        xos << "private";
      xos << "(";
      for (i = 0; i < number_of_locals; i++)
      {
	 if (i > 0)
	    xos << ",";

	 ST2F_Use_Preg(xos,
		       ST_type(local_list[i].st), local_list[i].preg_idx);
      }
      xos << ")";
   }

   if (local_list != NULL)
      FREE(local_list);
} /* Append_Implicit_Locals */


static BOOL
WN2F_pragma_list_nowait(WN *first_pragma)
{
   WN  *wn;
   BOOL nowait = FALSE;

   for (wn = first_pragma; !nowait && wn != NULL; wn = WN_next(wn))
      if ((WN_operator(wn) == OPR_PRAGMA || WN_operator(wn) == OPR_XPRAGMA) &&
	  WN_pragma(wn) == WN_PRAGMA_NOWAIT)
         nowait = TRUE;

   return nowait;
} /* WN2F_pragma_list_nowait */


static void
WN2F_Append_Value_Reference(xml::ostream& xos, WN *expression)
{
   XlationContext context;

   /* Emit memory reference
    */
   if (TY_Is_Pointer(WN_Tree_Type(expression)))
      context.SetDerefAddr();
   (void)WN2F_translate(xos, expression, context);
} // WN2F_Append_Value_Reference


static void
WN2F_Prepend_Value_Reference(xml::ostream& xos, WN *expression)
{
   XlationContext context;
   //FIXME xml::ostream& expr_xos = New_Token_Buffer();

   /* Emit memory reference
    */
   if (TY_Is_Pointer(WN_Tree_Type(expression)))
     context.SetDerefAddr();
   WN2F_translate(xos, expression, context);
   
   ///*FIXMEprepend*/ Append_And_Reclaim_Token_List(tokens, &expr_tokens);

} // WN2F_Prepend_Value_Reference


/* enhanced to emit proper OpenMP schedule clauses (radu@par.univie.ac.at) */
static void
Append_MP_Schedtype(xml::ostream& xos, WN *clause)
{
   switch (WN_mp_schedtype(clause))
   {
   case WN_PRAGMA_SCHEDTYPE_RUNTIME:
      xos << "runtime";
      break;
   case WN_PRAGMA_SCHEDTYPE_SIMPLE:
      if(WN2F_is_omp(clause))
	xos << "static";
      else
	xos << "simple";
      break;
   case WN_PRAGMA_SCHEDTYPE_INTERLEAVE:
      xos << "interleaved";
      break;
   case WN_PRAGMA_SCHEDTYPE_DYNAMIC:
      xos << "dynamic";
      break;
   case WN_PRAGMA_SCHEDTYPE_GSS:
      if(WN2F_is_omp(clause))
        xos << "guided";
      else
	xos << "gss";
      break;
   case WN_PRAGMA_SCHEDTYPE_PSEUDOLOWERED:
      xos << "pseudolowered";
      break;
   default:
      ASSERT_DBG_FATAL(FALSE, 
		       (DIAG_W2F_UNEXPECTED_OPC, "Append_MP_Schedtype"));
      break;
   }
} /* Append_MP_Schedtype */


static void
Append_Arg_Numbers(xml::ostream& xos,
                   INT32        val1,
                   INT32        val2)
{
   if (val1 != -1)
      Append_Token_String(xos, WHIRL2F_number_as_name(val1));

   if (val2 != -1)
   {
      xos << ",";
      Append_Token_String(xos, WHIRL2F_number_as_name(val2));
   }
} /* Append_Arg_Numbers */

         
static void
Append_Prefetch_Attributes(xml::ostream& xos, 
                           WN          *prefetch,
                           INT32        size)
{
   INT pflag = WN_prefetch_flag(prefetch);

   /* Emit memory reference
    */
   xos << "=";
   WN2F_Append_Value_Reference(xos, WN_kid0(prefetch));

   /* Emit stride and level clauses
    */
   xos << ",";
   if (PF_GET_STRIDE_1L(pflag) > 0)
   {
      if (PF_GET_STRIDE_2L(pflag) > 0)
      {
         Append_Token_String(xos, 
            StrCat("stride=",
            StrCat(WHIRL2F_number_as_name(PF_GET_STRIDE_1L(pflag)),
            StrCat(",",
                        WHIRL2F_number_as_name(PF_GET_STRIDE_2L(pflag))))));
         xos << ",";
         xos << "level=1,2";
      }
      else
      {
         Append_Token_String(xos, 
            StrCat("stride=",
                            WHIRL2F_number_as_name(PF_GET_STRIDE_1L(pflag))));
         xos << ",";
         xos << "level=1";
      }
   }
   else if (PF_GET_STRIDE_2L(pflag) > 0)
   {
      Append_Token_String(xos, 
            StrCat("stride=,",
                            WHIRL2F_number_as_name(PF_GET_STRIDE_2L(pflag))));
         xos << ",";
         xos << "level=,2";
   }
   else
   {
      xos << "stride=";
      xos << ",";
      xos << "level=";
   }

   /* Emit a kind clause
    */
   xos << ",";
   if (PF_GET_READ(pflag))
      xos << "kind=rd";
   else
      xos << "kind=wr";

   /* Emit a size clause
    */
   if (size > 0)
   {
      xos << ",";
      Append_Token_String(xos, 
         StrCat("size=", WHIRL2F_number_as_name(size)));
   }
} /* Append_Prefetch_Attributes */


static void
Append_Distribution(xml::ostream& xos, WN **apragma, WN_PRAGMA_ID id)
{
   INT32               dim, num_dims;
   ARRAY_DISTRIBUTION  distr[MAX_PRAGMAS_TO_SKIP];
   WN                 *wn = *apragma;
   XlationContext        context;

   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_PRAGMA, 
		    (DIAG_W2F_UNEXPECTED_OPC, "Append_Distribution"));

   /* Accumulate the distribution kind for each dimension.
    */
   for (num_dims = 0; 
	(WN_operator(wn) == OPR_PRAGMA &&
	 WN_pragma(wn) == id               &&
	 num_dims == WN_pragma_index(wn));
	num_dims++)
   {
      /* In reverese order of pragma sequence */
      distr[num_dims].current_dimension = WN_pragma_index(wn);
      distr[num_dims].base = wn;
      if (WN_pragma_distr_type(wn) == DISTRIBUTE_CYCLIC_EXPR)
         distr[num_dims].cyclic_expr = wn = WN_next(wn);
      distr[num_dims].dimension_bound = wn = WN_next(wn);
      wn = WN_next(wn);
   }

   /* Skip two stores, which are generated purely for dependency analysis
    * purposes.
    */
   if (WN_operator(wn)==OPR_STID && ST_class(WN_st(wn))==CLASS_PREG)
   {
      wn = WN_next(wn);
      if (WN_operator(wn)==OPR_STID && ST_class(WN_st(wn))==CLASS_PREG)
         wn = WN_next(wn);
   }
   *apragma = wn;

   /* Translate the sequence of distribution kinds, in Fortran order, i.e.
    * in reverse order from WHIRL representation.
    */
   xos << "(";
   for (dim = num_dims-1; dim >= 0; dim--)
   {
      switch (WN_pragma_distr_type(distr[dim].base))
      {
      case DISTRIBUTE_STAR:
         xos << "*";
         break;

      case DISTRIBUTE_BLOCK:
         xos << "block";
         break;

      case DISTRIBUTE_CYCLIC_EXPR:
         xos << "cyclic";
         xos << "(";
         WN2F_translate(xos, WN_kid0(distr[dim].cyclic_expr), context);
         xos << ")";
         break;

      case DISTRIBUTE_CYCLIC_CONST:
         xos << "cyclic";
         PARENTHESIZE_ARG_NUMBERS1(xos, WN_pragma_preg(distr[dim].base));
         break;

      default:
         xos << "unknown_distribution";
         break;
      }

      if (dim > 0)
         xos << ",";

   } /* For each dimension */
   xos << ")";

} /* Append_Distribution */


static void
Append_A_Clause_Symbol(xml::ostream& xos, WN *clause, WN_OFFSET ofst)
{
  ST * const st = WN_st(clause);

  if (ST_class(st) == CLASS_PREG) {
    INT32 preg_num = WN_pragma_arg1(clause);
    
    ST2F_Use_Preg(xos, ST_type(st), preg_num);
  } else {
    const TY_IDX base_ty = ST_type(st);
    XlationContext ctxt;
    
    WN2F_Offset_Symref(xos, st,                  /* base variable */
		       Stab_Pointer_To(base_ty), /* base addr */
		       base_ty,                  /* type of reference */
		       ofst,                     /* base offset */
		       ctxt);
  }
}


static void
Append_Clause_Symbols(xml::ostream& xos,
		      WN_PRAGMA_ID id,
		      WN         **next)
{
   /* Loop through the pragmas, and emit a ',' separated list
    * of the ST attributes for all contiguous pragmas with the 
    * given "id".  Terminate upon reaching a pragma with a
    * different "id" or the end of the pragma list. Set *next to
    * point to the next node after the last one processed here.
    */
   WN  *clause;

   ASSERT_DBG_FATAL(WN_operator(*next) == OPR_PRAGMA, 
		    (DIAG_W2F_UNEXPECTED_OPC, "Append_Clause_Symbols"));

   xos << "(";
   for (clause = *next;
	(clause != NULL && 
	 WN_operator(clause) == OPR_PRAGMA && 
	 WN_pragma(clause) == id);
	clause = WN_next(clause))
   {
      if (clause != *next)
	 xos << ",";

      Append_A_Clause_Symbol(xos,  clause, 0);
   }
   xos << ")";
   *next = clause;
} /* Append_Clause_Symbols */


static void
Append_Reduction_Clause(xml::ostream& xos,
			WN_PRAGMA_ID id,
			WN         **next)
{
   /* Loop through the pragmas, and emit a ',' separated list
    * of the reduction operator and ST attributes for all 
    * contiguous pragmas with the given "id".  
    */
   WN  *       clause;
   WN  * const first_clause = *next;

   ASSERT_DBG_FATAL(WN_operator(first_clause) == OPR_PRAGMA, 
		    (DIAG_W2F_UNEXPECTED_OPC, "Append_Reduction_Clause"));

   xos << "reduction (";
   for (clause = first_clause;
	(clause != NULL && 
	 WN_operator(clause) == OPR_PRAGMA && 
	 WN_pragma(clause) == id);
	clause = WN_next(clause))
   {
      if (WN2F_is_omp(clause) &&  
	  WN_pragma(clause) == WN_PRAGMA_REDUCTION &&
	  WN_pragma_arg2(clause) != OPERATOR_UNKNOWN) 
      {
	 if (first_clause != clause) 
	    xos << "), reduction (";
	 Append_Reduction_Operator(xos, (OPERATOR) WN_pragma_arg2(clause));
	 
      } 
      else if (clause != first_clause) 
	 xos << ",";
      
      Append_A_Clause_Symbol(xos, clause, 0);
   }

   xos << ")";
   *next = clause;

} /* Append_Reduction_Clause */


static void
Append_Clause_Expressions(xml::ostream& xos,
			  WN_PRAGMA_ID id,
			  WN         **next,
			  BOOL         reverse_order = FALSE)
{
   /* Loop through the pragmas, and emit a ',' separated list
    * of the ST attributes for all contiguous pragmas with the 
    * given "id".  Terminate upon reaching a pragma with a
    * different "id" or the end of the pragma list. Set *next to
    * point to the next node after the last one processed here.
    */
   WN *         clause;
   WN * const   first_clause = *next;

   ASSERT_DBG_FATAL(WN_operator(first_clause) == OPR_XPRAGMA, 
		    (DIAG_W2F_UNEXPECTED_OPC, "Append_Clause_Expressions"));

   xos << "(";
   for (clause = first_clause;
	(clause != NULL && 
	 WN_operator(clause) == OPR_XPRAGMA && 
	 WN_pragma(clause) == id);
	clause = WN_next(clause))
   {
     if (clause != first_clause) {
       if (reverse_order) {
	 //FIXME Prepend_Token_Special(xos,  ',');
       } else {
	 xos << ",";
       }
     }
     

      if (id == WN_PRAGMA_ONTO && 
	  WN_operator(WN_kid0(clause)) == OPR_INTCONST &&
	  WN_const_val(WN_kid0(clause)) == 0)
      {
	 /* Special case!
	  */
	if (reverse_order) {
	  //FIXME Prepend_Token_Special(xos,  '*');
	} else {
	  xos << "*";
	}
      }
      else
      {
	 if (reverse_order)
	    WN2F_Prepend_Value_Reference(xos, WN_kid0(clause));
	 else
	    WN2F_Append_Value_Reference(xos, WN_kid0(clause));
      }
   } // for each clause
   xos << ")";
   *next = clause;
} /* Append_Clause_Expressions */

	
static void
Append_Array_Segment(xml::ostream& xos,
		     WN_PRAGMA_ID id,
		     WN         **next)
{
   /* Loop through the pragmas, and emit a ',' separated list
    * of the ST attributes for all contiguous pragmas with the 
    * given "id".  Terminate upon reaching a pragma with a
    * different "id" or the end of the pragma list. Set *next to
    * point to the next node after the last one processed here.
    */
   WN *clause;

   ASSERT_DBG_FATAL(WN_operator(*next) == OPR_XPRAGMA,
		    (DIAG_W2F_UNEXPECTED_OPC, "Append_Array_Segment"));

   xos << "(";
   for (clause = *next;
	(clause != NULL && 
	 WN_operator(clause) == OPR_XPRAGMA && 
	 WN_pragma(clause) == id);
	clause = WN_next(clause))
   {
      if (clause != *next)
	 xos << ",";

      Append_A_Clause_Symbol(xos,  clause, 0);
      xos << "(";
      EMIT_ARG_NUMBERS1(xos, 1);
      xos << ":";
      WN2F_Append_Value_Reference(xos, WN_kid0(clause));
      xos << ")";
   }
   xos << ")";

   *next = clause;
} /* Append_Array_Segment */

	    
static void
Append_Nest_Clauses(xml::ostream& xos, 
		    const WN    *nest_region, 
		    INT          nest_levels,
		    XlationContext& ctxt)
{
#if 0//FIXME
   BOOL         pattern_error = FALSE;
   INT          nest;
   ST          *idx_var;
   TY_IDX       idx_ty;
   const WN    *next_stmt = nest_region;
   WN_PRAGMA_ID nest_kind = WN_PRAGMA_UNDEFINED;
   xml::ostream& nest_tokens = New_Token_Buffer();

   ASSERT_DBG_FATAL(next_stmt != NULL &&
		    WN_operator(next_stmt) == OPR_REGION &&
		    WN_first(WN_region_pragmas(next_stmt)) != NULL,
		    (DIAG_W2F_UNEXPECTED_OPC, "Append_Nest_Clauses"));

   nest_kind = 
      (WN_PRAGMA_ID)WN_pragma(WN_first(WN_region_pragmas(next_stmt)));

   Append_Token_String(nest_tokens, "nest");
   Append_Token_Special(nest_tokens, '(');
   reset_XlationContext(ctxt);
   for (nest = 1; !pattern_error && nest <= nest_levels; nest++)
   {
      /* Get the next nested loop, assuming next_stmt at this point
       * refers to a region.
       */
      next_stmt = WN_first(WN_region_body(next_stmt));
      while (next_stmt != NULL && WN_operator(next_stmt) != OPR_DO_LOOP)
	 next_stmt = WN_next(next_stmt);

      if (next_stmt == NULL)
	 pattern_error = TRUE;
      else
      {
	 /* Write out the index variable (or preg).
	  */
	 idx_var = WN_st(WN_index(next_stmt));
	 idx_ty = ST_type(idx_var);
	 if (ST_class(idx_var) == CLASS_PREG)
	 {
	    ST2F_Use_Preg(nest_tokens, 
			  idx_ty, 
			  WN_idname_offset(WN_index(next_stmt)));
	 }
	 else
	 {
	    WN2F_Offset_Symref(nest_tokens,
			       idx_var,                 /* base variable */
			       Stab_Pointer_To(idx_ty), /* base addr */
			       idx_ty,                  /* type of ref */
			       0,                       /* base offset */
			       ctxt);
	 }
	 
	 /* Emit separator, and search for the next nested region, if 
	  * any is expected.
	  */
	 if (nest < nest_levels)
	 {
	    Append_Token_Special(nest_tokens, ',');

	    next_stmt = WN_first(WN_do_body(next_stmt));
	    while (next_stmt != NULL && 
		   WN_operator(next_stmt) != OPR_REGION)
	       next_stmt = WN_next(next_stmt);

	    if (next_stmt == NULL                              ||
		WN_first(WN_region_pragmas(next_stmt)) == NULL ||
		WN_pragma(WN_first(WN_region_pragmas(next_stmt))) != 
		nest_kind)
	       pattern_error = TRUE;
	 }
      }
   }
   Append_Token_Special(nest_tokens, ')');

   if (!pattern_error)
      Append_And_Reclaim_Token_List(tokens, &nest_tokens);
#endif
} /* Append_Nest_Clauses */


static void
Skip_Pragma_Clauses(WN         **clause_list,  
                    XlationContext& ctxt)
{
   /* Also change Append_Pragma_Clauses() when changing this.
    */
   WN  *clause = *clause_list;
   BOOL more;

   more = (clause != NULL && 
	   (WN_operator(clause) == OPR_PRAGMA ||
	    WN_operator(clause) == OPR_XPRAGMA));

   while (more)
   {
      switch (WN_pragma(clause))
      {
      case WN_PRAGMA_AFFINITY:
      case WN_PRAGMA_DATA_AFFINITY:
      case WN_PRAGMA_THREAD_AFFINITY:
      case WN_PRAGMA_CHUNKSIZE:
      case WN_PRAGMA_IF:
      case WN_PRAGMA_LASTLOCAL:
      case WN_PRAGMA_LOCAL:
      case WN_PRAGMA_MPSCHEDTYPE:
      case WN_PRAGMA_ORDERED:
      case WN_PRAGMA_REDUCTION:
      case WN_PRAGMA_SHARED:
      case WN_PRAGMA_ONTO:
      case WN_PRAGMA_LASTTHREAD:
      case WN_PRAGMA_MPNUM:
      case WN_PRAGMA_SYNC_DOACROSS:
      case WN_PRAGMA_FIRSTPRIVATE:
/* there is no FLUSH clause in OpenMP */
/* we fake this clause in order to treat FLUSH directive the same as the others (radu@par.univie.ac.at) */
      case WN_PRAGMA_FLUSH:
         clause = WN_next(clause);
         break;

      default:
	 more = FALSE;
	 break;
      } /* switch */

      more = (more &&
	      clause != NULL && 
	      (WN_operator(clause) == OPR_PRAGMA ||
	       WN_operator(clause) == OPR_XPRAGMA));
   } /* for each attribute pragma */

   *clause_list = clause;
} /* Skip_Pragma_Clauses */

      
static void 
Skip_Ignored_Clauses(WN *following_clauses, WN **next_clause)
{
   BOOL skipped = TRUE;

   while (skipped && *next_clause != following_clauses)
   {
      switch (WN_pragma(*next_clause))
      {
      case WN_PRAGMA_DATA_AFFINITY:
      case WN_PRAGMA_THREAD_AFFINITY:
      case WN_PRAGMA_MPNUM:
      case WN_PRAGMA_SYNC_DOACROSS:
	 *next_clause = WN_next(*next_clause);
	 break;
      default:
	 skipped = FALSE;
	 break;
      }
   }
} /* Skip_Ignored_Clauses */


static void
Append_Pragma_Clauses(xml::ostream& xos, 
		      WN         **clause_list,  
		      XlationContext& ctxt)
{
   /* Loop through the sequence of pragmas, emitting those representing
    * attributes to another (already emitted) pragma.  Terminate upon
    * reaching a non-attribute pragma or the end of the pragma list.
    * Also change Skip_Pragma_Clauses() when changing this.  Update the
    * clause_list, such that it denotes the item following the last one
    * processed here.
    */
   WN         *next;
   WN         *clause = *clause_list;
   WN         *wn_after_clauses = *clause_list;

   Skip_Pragma_Clauses(&wn_after_clauses, ctxt);
   while (clause != wn_after_clauses)
   {
      BOOL ignored_clause = FALSE;

      next = clause;
      switch (WN_pragma(clause))
      {
      case WN_PRAGMA_DATA_AFFINITY:
      case WN_PRAGMA_THREAD_AFFINITY:
      case WN_PRAGMA_MPNUM:
      case WN_PRAGMA_SYNC_DOACROSS:
      case WN_PRAGMA_DEFAULT:
	 ignored_clause = TRUE;
	 break; /* Ignore and do not follow with comma */

      case WN_PRAGMA_AFFINITY:
	 xos << "affinity";
	 Append_Clause_Expressions(xos, WN_PRAGMA_AFFINITY, &clause);

	 xos << "=";
	 if (WN_pragma(clause) == WN_PRAGMA_DATA_AFFINITY)
	    xos << "data";
	 else if (WN_pragma(clause) == WN_PRAGMA_THREAD_AFFINITY)
	    xos << "thread";
	 else
	     ASSERT_DBG_FATAL(FALSE, 
			      (DIAG_W2F_UNEXPECTED_OPC, 
			       "Append_Pragma_Clauses"));

         /* Process the expression associated with the thread/data affinity
          * pragma.
          */
	 xos << "(";
	 WN2F_Append_Value_Reference(xos, WN_kid0(clause));
	 xos << ")";
	 clause = WN_next(clause);
	 break;

      case WN_PRAGMA_CHUNKSIZE:
	 xos << "chunk";
	 xos << "=";
	 Append_Clause_Expressions(xos, WN_PRAGMA_CHUNKSIZE, &clause);
	 break;

      case WN_PRAGMA_IF:
	 xos << "if";
	 Append_Clause_Expressions(xos, WN_PRAGMA_IF, &clause);
	 break;

      case WN_PRAGMA_LASTLOCAL:
	 if (WN2F_is_omp(clause))
	    xos << "lastprivate";
	 else
	    xos << "lastlocal";
	 Append_Clause_Symbols(xos, WN_PRAGMA_LASTLOCAL, &clause);
	 break;

      case WN_PRAGMA_LOCAL:
	 if (WN2F_is_omp(clause))
	    xos << "private";
	 else
	    xos << "local";
	 if (WN_operator(clause) == OPR_XPRAGMA)
	 {
	    Append_Array_Segment(xos, WN_PRAGMA_LOCAL, &clause);
	 }
	 else
	 {
	    Append_Clause_Symbols(xos, WN_PRAGMA_LOCAL, &clause);
	 }
	 break;

      case WN_PRAGMA_MPSCHEDTYPE:
	 /* Can be both a clause and a pragma */
	 if (WN2F_is_omp(clause))
	 {
	    xos << "schedule";
	    xos << "(";
	    Append_MP_Schedtype(xos, clause);
	    if (WN_next(clause) != NULL &&
		WN_pragma(WN_next(clause)) == WN_PRAGMA_CHUNKSIZE)
	    {
	       clause = WN_next(clause);
	       xos << ",";
	       WN2F_Append_Value_Reference(xos, WN_kid0(clause));
	    }
	    xos << ")";
	    clause = WN_next(clause);
	 }
	 else
	 {
	    xos << "mp_schedtype";
	    xos << "=";
	    Append_MP_Schedtype(xos, clause);
	 }
	 break;

      case WN_PRAGMA_ORDERED:
	 if (WN2F_is_omp(clause))
	     xos << "ordered";
	 else 
	     xos << "(ordered)";
	 break;

      case WN_PRAGMA_REDUCTION:
	 if (WN_operator(clause) == OPR_XPRAGMA)
	 {
	    xos << "reduction";
	    Append_Clause_Expressions(xos, WN_PRAGMA_REDUCTION, &clause);
	 }
	 else
	 {
	   Append_Reduction_Clause(xos, WN_PRAGMA_REDUCTION, &clause);
	 }
	 break;

      case WN_PRAGMA_SHARED:
	 xos << "shared";
	 Append_Clause_Symbols(xos, WN_PRAGMA_SHARED, &clause);
	 break;

      case WN_PRAGMA_ONTO:
	 xos << "onto";
         Append_Clause_Expressions(xos, WN_PRAGMA_ONTO, &clause,
				   TRUE/*reverse_order*/);
	 break;

      case WN_PRAGMA_LASTTHREAD:
	 xos << "lastthread";
	 Append_Clause_Symbols(xos, WN_PRAGMA_LASTTHREAD, &clause);
	 break;

      case WN_PRAGMA_FIRSTPRIVATE:
	 xos << "firstprivate";
	 Append_Clause_Symbols(xos, WN_PRAGMA_FIRSTPRIVATE, &clause);
	 break;

/* there is no FLUSH clause in OpenMP */
/* we fake this clause in order to treat FLUSH directive the same as the others (radu@par.univie.ac.at) */
      case WN_PRAGMA_FLUSH:
	 Append_Clause_Symbols(xos, WN_PRAGMA_FLUSH, &clause);
	 break;

      default:
	 ASSERT_WARN(FALSE,
		     (DIAG_W2F_UNEXPECTED_PRAGMA, " Append_Pragma_Clauses"));
	 break;
      } /* switch */

      /* See if we have already advanced to the next pragma, e.g. as a result
       * of calling Append_Clause_Expressions() or Append_Clause_Symbols(),
       * and if not so, then advance to the next pragma.
       */
      if (next == clause)
         clause = WN_next(clause);

      Skip_Ignored_Clauses(wn_after_clauses, &clause);
      if (clause != wn_after_clauses && !ignored_clause)
	    xos << ","; /* separate by commas */
   } /* for each attribute pragma */

   *clause_list = clause;
} /* Append_Pragma_Clauses */


static void
Emit_To_PUinfo_Pragmas(WN **next, XlationContext& ctxt)
{
#if 0 //FIXME
   /* This is a special handler for pragmas that must be taken out of
    * a statement list ctxt and instead must be appended to the 
    * PUinfo_pragmas list.
    */
   xml::ostream& xos = New_Token_Buffer();

   ASSERT_DBG_FATAL(WN_operator(*next) == OPR_PRAGMA ||
		    WN_operator(*next) == OPR_XPRAGMA, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_pragma"));

   switch (WN_pragma(*next))
   {
   case WN_PRAGMA_DISTRIBUTE:
      WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(*next));
      xos << "DISTRIBUTE";
      Append_A_Clause_Symbol(xos, *next, 0/*ofst*/);
      Append_Distribution(xos, next, WN_PRAGMA_DISTRIBUTE);
      Append_Pragma_Clauses(xos, next, ctxt);
      break;

   case WN_PRAGMA_DISTRIBUTE_RESHAPE:
      WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(*next));
      xos << "DISTRIBUTE RESHAPE";
      Append_A_Clause_Symbol(xos, *next, 0/*ofst*/);
      Append_Distribution(xos, next, WN_PRAGMA_DISTRIBUTE_RESHAPE);
      Append_Pragma_Clauses(xos, next, ctxt);
      break;

   default:
      ASSERT_WARN(FALSE,
                  (DIAG_W2F_UNEXPECTED_PRAGMA, "Emit_To_PUinfo_Pragmas"));
      break;
   }
   /*FIXMEprepend*/ Append_And_Reclaim_Token_List(PUinfo_pragmas, &tokens);
#endif
} /* Emit_To_PUinfo_Pragmas */


static WN *
Get_Enclosing_Parallel_Region(const WN *construct)
{
   WN *found_parallel = NULL;

   construct = W2CF_Get_Parent(construct);
   while (found_parallel == NULL && construct != NULL)
   {
      if (WN_operator(construct) == OPR_REGION)
      {
	 WN *pragma = WN_first(WN_region_pragmas(construct));
	 if (WN_pragma(pragma) == WN_PRAGMA_PARALLEL_BEGIN)
	    found_parallel = pragma;
      }
      construct = W2CF_Get_Parent(construct);
   }
   return found_parallel;
} /* Get_Enclosing_Parallel_Region */


static void
WN2F_process_pragma(xml::ostream& xos, WN **next, XlationContext& ctxt)
{
   /* This procedure will translate the "next" pragma and and any associated
    * clauses, such that "next" end up pointing to the WN* after the pragma
    * and clauses.
    */
   WN       *apragma = *next;
   WN       *this_pragma = apragma;
   WN       *first_clause;
   const WN *surrounding_region;

   ASSERT_DBG_FATAL(WN_operator(apragma) == OPR_PRAGMA ||
		    WN_operator(apragma) == OPR_XPRAGMA, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_process_pragma"));

   switch (WN_pragma(apragma))
   {
   case WN_PRAGMA_INLINE_DEPTH:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "INLINE_DEPTH";
      xos << "=";
      EMIT_ARG_NUMBERS1(xos, WN_pragma_arg1(apragma));
      break;

   case WN_PRAGMA_AGGRESSIVE_INNER_LOOP_FISSION:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "AGGRESSIVE INNER LOOP FISSION";
      break;

   case WN_PRAGMA_FISSION:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "FISSION";
      PARENTHESIZE_ARG_NUMBERS1(xos, WN_pragma_arg1(apragma));
      break;

   case WN_PRAGMA_FISSIONABLE:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "FISSIONABLE";
      break;

   case WN_PRAGMA_FUSE:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "FUSE";
      PARENTHESIZE_ARG_NUMBERS2(xos, 
                                WN_pragma_arg1(apragma),
                                WN_pragma_arg2(apragma));
      break;

   case WN_PRAGMA_FUSEABLE:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "FUSABLE";
      break;

   case WN_PRAGMA_NO_FISSION:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "NO FISSION";
      break;

   case WN_PRAGMA_NO_FUSION:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "NO FUSION";
      break; 

   case WN_PRAGMA_INTERCHANGE:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "INTERCHANGE";
      Append_Clause_Symbols(xos, (WN_PRAGMA_ID)WN_pragma(apragma),
                            &apragma);
      break;

   case WN_PRAGMA_NO_INTERCHANGE:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "NO INTERCHANGE";
      break;

   case WN_PRAGMA_BLOCKING_SIZE:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "BLOCKING SIZE";
      PARENTHESIZE_ARG_NUMBERS2(xos, 
                                WN_pragma_arg1(apragma),
                                WN_pragma_arg2(apragma));
      break;

   case WN_PRAGMA_NO_BLOCKING:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "NO BLOCKING";
      break;

   case WN_PRAGMA_UNROLL:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "UNROLL";
      PARENTHESIZE_ARG_NUMBERS2(xos, WN_pragma_arg1(apragma), 
                                WN_pragma_arg2(apragma));
      break;

   case WN_PRAGMA_BLOCKABLE:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "BLOCKABLE";
      Append_Clause_Symbols(xos, (WN_PRAGMA_ID)WN_pragma(apragma),
                            &apragma);
      break;

   case WN_PRAGMA_PREFETCH:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "PREFETCH";
      PARENTHESIZE_ARG_NUMBERS2(xos, WN_pragma_arg1(apragma),
                                WN_pragma_arg2(apragma));
      break;

   case WN_PRAGMA_PREFETCH_MANUAL:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "PREFETCH_MANUAL";
      PARENTHESIZE_ARG_NUMBERS1(xos, WN_pragma_arg1(apragma));
      break;

   case WN_PRAGMA_PREFETCH_REF:
      if (WN_next(apragma) != NULL && 
          WN_operator(WN_next(apragma)) == OPR_PREFETCH)
      {
         WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
         xos << "PREFETCH_REF";
         Append_Prefetch_Attributes(xos, WN_next(apragma),
                                    WN_pragma_arg2(apragma));
      }
      break;

   case WN_PRAGMA_PREFETCH_REF_DISABLE:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "PREFETCH_REF_DISABLE";
      xos << "=";
      Append_A_Clause_Symbol(xos, apragma, 0/*ofst*/);
      if (WN_pragma_arg2(apragma) > 0)
      {
         xos << ",";
         xos << "size";
         xos << "=";
         EMIT_ARG_NUMBERS1(xos, WN_pragma_arg2(apragma));
      }         
      break;
      
   case WN_PRAGMA_DISTRIBUTE:
      Emit_To_PUinfo_Pragmas(&apragma, ctxt);
      break;
      
   case WN_PRAGMA_REDISTRIBUTE:
      WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      xos << "REDISTRIBUTE";
      Append_A_Clause_Symbol(xos, apragma, 0/*ofst*/);
      Append_Distribution(xos, &apragma, WN_PRAGMA_REDISTRIBUTE);
      Append_Pragma_Clauses(xos, &apragma, ctxt);
      break;
      
   case WN_PRAGMA_DISTRIBUTE_RESHAPE:
      Emit_To_PUinfo_Pragmas(&apragma, ctxt);
      break;
      
   case WN_PRAGMA_DYNAMIC:
      WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      xos << "DYNAMIC";
      Append_A_Clause_Symbol(xos, apragma, 0/*ofst*/);
      break;

   case WN_PRAGMA_IVDEP:
      WN2F_Directive_Newline(xos, "CDIR$", WN_Get_Linenum(apragma));
      xos << "IVDEP";
      break;

   case WN_PRAGMA_DOACROSS:
      /* Ignore deeper nests.
       */
      if (WN_pragma_nest(apragma) <= 0 && 
	  !Ignore_Synchronized_Construct(apragma, ctxt))
      {
	 surrounding_region = W2CF_Get_Parent(W2CF_Get_Parent(apragma));
	 first_clause = WN_next(apragma);

	 Put_Pragma_Start_With_Caveats(xos,apragma,TRUE);
         xos << "DOACROSS";
	 if (WN_max_nest_level(apragma) > 1)
	    Append_Nest_Clauses(xos, 
				surrounding_region, 
				WN_max_nest_level(apragma),
				ctxt);
	 apragma = first_clause;
	 Append_Pragma_Clauses(xos, &apragma, ctxt);
	 Append_Implicit_Locals(xos, 
				WN_PRAGMA_DOACROSS, 
				WN_region_body(surrounding_region),
				first_clause);
      }
      else
      {
	 apragma = WN_next(apragma);
         Skip_Pragma_Clauses(&apragma, ctxt);
      }
      break;

   case WN_PRAGMA_MPSCHEDTYPE:
      /* Can be both a clause and a pragma.
       */
      WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      if (WN2F_is_omp(apragma))
      {
	 xos << "SCHEDULE";
	 xos << "(";
	 Append_MP_Schedtype(xos, apragma);
	 if (WN_next(apragma) != NULL &&
	     WN_pragma(WN_next(apragma)) == WN_PRAGMA_CHUNKSIZE)
	 {
	    apragma = WN_next(apragma);
	    xos << ",";
	    WN2F_Append_Value_Reference(xos, WN_kid0(apragma));
	 }
	 xos << ")";
	 apragma = WN_next(apragma);
      }
      else
      {
	 xos << "MP_SCHEDTYPE";
	 xos << "=";
	 Append_MP_Schedtype(xos, apragma);
      }
      break;

   case WN_PRAGMA_BARRIER:
#if 0 // REMOVE
      if (W2F_Prompf_Emission)
	 WN2F_Start_Prompf_Construct(xos, apragma);
#endif // REMOVE
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma) ;
      xos << "BARRIER";
#if 0 // REMOVE
      if (W2F_Prompf_Emission)
	 WN2F_End_Prompf_Construct(xos, apragma);
#endif // REMOVE
      break;

   case WN_PRAGMA_COPYIN:
      WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      if (WN2F_is_omp(apragma))
        WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Append_Pragma_Preamble(xos,apragma) ;
      xos << "COPYIN";
      if (WN_operator(apragma) == OPR_XPRAGMA)
         Append_Clause_Expressions(xos,
				   (WN_PRAGMA_ID)WN_pragma(apragma),
                                   &apragma);
      else {
         /* A common symbol */
         xos << "/";
	 ST2F_use_translate(xos, WN_st(apragma), ctxt);
         xos << "/";
      }
      break;

   case WN_PRAGMA_CRITICAL_SECTION_BEGIN:
#if 0 // REMOVE
      if (W2F_Prompf_Emission)
	 WN2F_Start_Prompf_Construct(xos, apragma);
#endif //REMOVE
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma) ;
      if (WN2F_is_omp(apragma))
	  xos << "CRITICAL";
      else
	  xos << "CRITICAL SECTION";
      if (WN_operator(apragma) == OPR_XPRAGMA)
	 Append_Clause_Expressions(xos,
				   (WN_PRAGMA_ID)WN_pragma(apragma),
                                   &apragma);
      break;

   case WN_PRAGMA_CRITICAL_SECTION_END:
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma) ;
      if (WN2F_is_omp(apragma))
	  xos << "END CRITICAL";
      else
	  xos << "END CRITICAL SECTION";
#if 0 // REMOVE
      if (W2F_Prompf_Emission)
	 WN2F_End_Prompf_Construct(xos, apragma);
#endif // REMOVE
      break;

   case WN_PRAGMA_ORDERED_BEGIN:
#if 0 // REMOVE
      if (W2F_Prompf_Emission)
	 WN2F_Start_Prompf_Construct(xos, apragma);
#endif // REMOVE
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma) ;
      xos << "ORDERED";
      if (WN_operator(apragma) == OPR_XPRAGMA)
	 Append_Clause_Expressions(xos,
				   (WN_PRAGMA_ID)WN_pragma(apragma),
                                   &apragma);
      break;

   case WN_PRAGMA_ORDERED_END:
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma) ;
      xos << "END ORDERED";
#if 0 // REMOVE
      if (W2F_Prompf_Emission)
	 WN2F_End_Prompf_Construct(xos, apragma);
#endif // REMOVE
      break;

   case WN_PRAGMA_ATOMIC:
#if 0 // REMOVE
      if (W2F_Prompf_Emission)
	 WN2F_Start_Prompf_Construct(xos, apragma);
#endif // REMOVE
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma) ;
      xos << "ATOMIC";
      if (WN_operator(apragma) == OPR_XPRAGMA)
	 Append_Clause_Expressions(xos,
				   (WN_PRAGMA_ID)WN_pragma(apragma),
                                   &apragma);
#if 0 // REMOVE
      if (W2F_Prompf_Emission)
	 WN2F_End_Prompf_Construct(xos, this_pragma);
#endif // REMOVE
      break;

   case WN_PRAGMA_PARALLEL_BEGIN:
      /* Ignore deeper nests.
       */
      if (!Ignore_Synchronized_Construct(apragma, ctxt))
      {
	 surrounding_region = W2CF_Get_Parent(W2CF_Get_Parent(apragma));
	 first_clause = WN_next(apragma);
      
	 WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
	 //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
	 //WN2F_Append_Pragma_Preamble(xos,apragma) ;
	 xos << "PARALLEL";
	 apragma = first_clause;
	 Append_Pragma_Clauses(xos, &apragma, ctxt);
	 Append_Implicit_Locals(xos, 
				WN_PRAGMA_PARALLEL_BEGIN, 
				WN_region_body(surrounding_region),
				first_clause);
      }
      break;

   case WN_PRAGMA_PARALLEL_DO:
      /* Ignore deeper nests.
       */
      if (WN_pragma_nest(apragma) <= 0 &&
	  !Ignore_Synchronized_Construct(apragma, ctxt))
      {
	 surrounding_region = W2CF_Get_Parent(W2CF_Get_Parent(apragma));
	 first_clause = WN_next(apragma);
	 WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
	 //Put_Pragma_Start_With_Caveats(xos,apragma,TRUE);
	 //WN2F_Append_Pragma_Preamble(xos,apragma) ;
         xos << "PARALLEL DO";

	 if (WN_max_nest_level(apragma) > 1)
	    Append_Nest_Clauses(xos, 
				surrounding_region,
				WN_max_nest_level(apragma),
				ctxt);
	 apragma = first_clause;
         Append_Pragma_Clauses(xos, &apragma, ctxt);
	 Append_Implicit_Locals(xos, 
				WN_PRAGMA_PARALLEL_DO, 
				WN_region_body(surrounding_region),
				first_clause);
      }
      else
      {
	 apragma = WN_next(apragma);
         Skip_Pragma_Clauses(&apragma, ctxt);
      }
      break;

   case WN_PRAGMA_PDO_BEGIN:
      /* Ignore deeper nests.
       */
      if (WN_pragma_nest(apragma) <= 0 &&
	  !Ignore_Synchronized_Construct(apragma, ctxt))
      {
	 surrounding_region = W2CF_Get_Parent(W2CF_Get_Parent(apragma));
	 first_clause = WN_next(apragma);

	 WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
	 //Put_Pragma_Start_With_Caveats(xos,apragma,TRUE);
	 //WN2F_Append_Pragma_Preamble(xos,apragma) ;
	 if (WN2F_is_omp(apragma)) 
	   xos << "DO";
	 else
	   xos << "PDO";

	 if (WN_max_nest_level(apragma) > 1)
	    Append_Nest_Clauses(xos, 
				surrounding_region,
				WN_max_nest_level(apragma),
				ctxt);
	 apragma = first_clause;
         Append_Pragma_Clauses(xos, &apragma, ctxt);

	 /* Turn this off for now, since we also need to avoid declaring
	  * as local variables declared as shared in the enclosing
	  * parallel region.
	  *
	  * Append_Implicit_Locals(xos, 
	  *		WN_PRAGMA_PDO_BEGIN,
	  *		WN_region_body(surrounding_region),
	  *		first_clause);
	  */
      }
      else
      {
	 apragma = WN_next(apragma);
         Skip_Pragma_Clauses(&apragma, ctxt);
      }
      break;

      /* region construct => construct id on region..*/

   case WN_PRAGMA_PARALLEL_SECTIONS:
   case WN_PRAGMA_PSECTION_BEGIN:
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma);
      if (WN2F_is_omp(apragma)) 
	 xos << "PARALLEL SECTIONS";
      else
	 xos << "PSECTIONS";
      apragma = WN_next(apragma);
      Append_Pragma_Clauses(xos, &apragma, ctxt);
      break;

   case WN_PRAGMA_SECTION:
#if 0 // REMOVE
      if (W2F_Prompf_Emission)
      {
	 if (WN2F_Prompf_Subsection != NULL)
	 {
	    // End a the previous SECTION directive seen!
	    //
	    WN2F_End_Prompf_Construct(xos, WN2F_Prompf_Subsection);
	 }
	 WN2F_Prompf_Subsection = apragma;
	 WN2F_Start_Prompf_Construct(xos, apragma);
      }
#endif // REMOVE
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma);
      xos << "SECTION";
      break;

   case WN_PRAGMA_PARALLEL_WORKSHARE:
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma);
      xos << "PARALLEL WORKSHARE";
      apragma = WN_next(apragma);
      Append_Pragma_Clauses(xos, &apragma, ctxt);
      break;

   case WN_PRAGMA_WORKSHARE:
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma) ;
      xos << "WORKSHARE";
      break;

      /* region construct => construct id on region..*/

   case WN_PRAGMA_SINGLE_PROCESS_BEGIN:
      if (!Ignore_Synchronized_Construct(apragma, ctxt))
      {
	 WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
	 //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
	 //WN2F_Append_Pragma_Preamble(xos,apragma) ;
	 if (WN2F_is_omp(apragma))
	   xos << "SINGLE";
	 else
	   xos << "SINGLE PROCESS";
	 apragma = WN_next(apragma);
	 Append_Pragma_Clauses(xos, &apragma, ctxt);
      }
      break;

      /* region construct => construct id on region..*/

    case WN_PRAGMA_MASTER_BEGIN:
      if (!Ignore_Synchronized_Construct(apragma, ctxt))
      {
         WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
	 //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
	 //WN2F_Append_Pragma_Preamble(xos,apragma) ;
	 if (WN2F_is_omp(apragma))
	   xos << "MASTER";
	 else
	   xos << "MASTER PROCESS";
      }
      break;

    case WN_PRAGMA_FLUSH:
      WN2F_OMP_or_PAR_Directive_Newline(xos,apragma);
      //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      //WN2F_Append_Pragma_Preamble(xos,apragma) ;
      xos << "FLUSH";
      apragma = WN_next(apragma);
      Append_Pragma_Clauses(xos, &apragma, ctxt);
      break;

   case WN_PRAGMA_NUMTHREADS:
      /* Should only appear for C, but if we ever see it, we also emit
       * it for Fortran.
       */
      WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      xos << "NUMTHREADS";
      Append_Clause_Expressions(xos,
				(WN_PRAGMA_ID)WN_pragma(apragma),
                                &apragma);
      break;

   case WN_PRAGMA_PAGE_PLACE:
      WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(apragma));
      xos << "PAGE_PLACE";
      Append_Clause_Expressions(xos,
				(WN_PRAGMA_ID)WN_pragma(apragma),
                                &apragma);
      break;

   case WN_PRAGMA_NORECURRENCE:
      WN2F_Directive_Newline(xos, "CDIR$", WN_Get_Linenum(apragma));
      xos << "NO RECURRENCE";
      break;

   case WN_PRAGMA_NEXT_SCALAR:
      WN2F_Directive_Newline(xos, "CDIR$", WN_Get_Linenum(apragma));
      xos << "NEXT SCALAR";
      break;

   case WN_PRAGMA_KAP_CONCURRENTIZE:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "CONCURRENTIZE";
      break;

   case WN_PRAGMA_KAP_NOCONCURRENTIZE:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "NO CONCURRENTIZE";
      break;

   case WN_PRAGMA_KAP_ASSERT_PERMUTATION:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "ASSERT PERMUTATION";
      Append_A_Clause_Symbol(xos, apragma, 0/*ofst*/);
      break;

   case WN_PRAGMA_CRI_CNCALL:
   case WN_PRAGMA_KAP_ASSERT_CONCURRENT_CALL:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      xos << "ASSERT CONCURRENT CALL";
      break;

   case WN_PRAGMA_KAP_ASSERT_DO:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      if (WN_pragma_arg1(apragma) == ASSERT_DO_CONCURRENT)
	 xos << "ASSERT DO (CONCURRENT)";
      else
	 xos << "ASSERT DO (SERIAL)";
      break;

   case WN_PRAGMA_KAP_ASSERT_DOPREFER:
      WN2F_Directive_Newline(xos, "C*$*", WN_Get_Linenum(apragma));
      if (WN_pragma_arg1(apragma) == ASSERT_DO_CONCURRENT)
	 xos << "ASSERT DO PREFER (CONCURRENT)";
      else
	 xos << "ASSERT DO PREFER (SERIAL)";
      break;

      
   default:
      /* The others are always clauses that are processed as part of other
       * pragmas, or they are not to be emitted.
       */
      break;

   } /* switch on pragma cases */

   /* See if we have already advanced to the next pragma, e.g. as a result
    * of calling Append_Pragma_Clauses() or Append_Clause_Symbols(),
    * and if not so, then advance to the next pragma.
    */
   if (apragma == *next)
      *next = WN_next(apragma);
   else
      *next = apragma;

} /* WN2F_process_pragma */


/* ====================== Exported Functions ====================== */
/* ================================================================ */


BOOL
WN2F_Skip_Pragma_Stmt(WN *wn)
{
   /* This assumes that any pragma related nodes to be skipped will be
    * accessed in sequence, and that this routine will be called at most
    * once per such node.
    */
   BOOL found = (Pragmas_To_Skip.array[Pragmas_To_Skip.start] == wn);

   if (found)
   {
      if (Pragmas_To_Skip.end - Pragmas_To_Skip.start == 1)
      {
	 Pragmas_To_Skip.start = Pragmas_To_Skip.end = 0;
	 Pragmas_To_Skip.array[0] = NULL;
      }
      else
      {
	 Pragmas_To_Skip.start++;
      }
   }
   return found;
} /* WN2F_Skip_Pragma_Stmt */


WN2F_STATUS
WN2F_pragma(xml::ostream& xos, WN *wn, XlationContext& ctxt)
{
   WN *skip;
   WN *next = wn;

   ASSERT_DBG_FATAL(WN_operator(wn) == OPR_PRAGMA ||
		    WN_operator(wn) == OPR_XPRAGMA, 
		    (DIAG_W2F_UNEXPECTED_OPC, "WN2F_pragma"));

   WN2F_process_pragma(xos, &next, ctxt);

   ASSERT_FATAL(Pragmas_To_Skip.end == 0,
		(DIAG_W2F_BUFFER_ERROR,
		 "Unexpected index for Pragmas_To_Skip in WN2F_pragma()"));

   /* For pragmas inlined in code, we need to keep track of the pragmas
    * that have already been processed.
    */
   for (skip = WN_next(wn); skip != next; skip = WN_next(skip))
   {
      ASSERT_FATAL(Pragmas_To_Skip.end < MAX_PRAGMAS_TO_SKIP,
		   (DIAG_W2F_BUFFER_ERROR,
		    "Too many pragmas in sequence in WN2F_pragma()"));

      Pragmas_To_Skip.array[Pragmas_To_Skip.end++] = skip;
   }

   return EMPTY_WN2F_STATUS;
} /* WN2F_pragma */


WN2F_STATUS 
WN2F_pragma_list_begin(xml::ostream& xos,
                       WN          *first_pragma,
                       XlationContext& ctxt)
{
  // This is called for a region or a func_entry, which has a separate
  // block to hold a pragma-list.
  WN *next_pragma = first_pragma;
  
  while (next_pragma != NULL) {
    if (WN_operator(next_pragma) == OPR_PRAGMA ||
	WN_operator(next_pragma) == OPR_XPRAGMA)
      WN2F_process_pragma(xos, &next_pragma, ctxt);
    else
      next_pragma = WN_next(next_pragma);
  }
  return EMPTY_WN2F_STATUS;
} /* WN2F_pragma_list_begin */


WN2F_STATUS 
WN2F_pragma_list_end(xml::ostream& xos, 
                     WN          *first_pragma,
                     XlationContext& ctxt)
{
   /* This is called for a region or a func_entry, which has a separate
    * block to hold a pragma-list.
    */
   BOOL emitted = TRUE;

   /* Skip code inserted into the pragma region (may occur for C++, so
    * why not for other languages?).
    */
   while (first_pragma != NULL                  &&
	  WN_operator(first_pragma) != OPR_PRAGMA &&
	  WN_operator(first_pragma) != OPR_XPRAGMA)
   {
      first_pragma = WN_next(first_pragma);
   }

   if (first_pragma != NULL)
   {
      ASSERT_DBG_FATAL(WN_operator(first_pragma) == OPR_PRAGMA ||
                       WN_operator(first_pragma) == OPR_XPRAGMA, 
                       (DIAG_W2F_UNEXPECTED_OPC, "WN2F_pragma_list_end"));

      switch (WN_pragma(first_pragma))
      {
      case WN_PRAGMA_PARALLEL_BEGIN:
	 if (!Ignore_Synchronized_Construct(first_pragma, ctxt))
	 {
            WN2F_OMP_or_PAR_Directive_Newline(xos,first_pragma);
	    //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(first_pragma));
	    //WN2F_Append_Pragma_Preamble(xos,first_pragma);
	    xos << "END PARALLEL";
	 }
         break;

      case WN_PRAGMA_DOACROSS:
      case WN_PRAGMA_PARALLEL_DO:
	 break;
	 
      case WN_PRAGMA_PDO_BEGIN:
	 if (WN_pragma_nest(first_pragma) <= 0 &&
	     !Ignore_Synchronized_Construct(first_pragma, ctxt))
	 {
            WN2F_OMP_or_PAR_Directive_Newline(xos,first_pragma);
	    //Put_Pragma_Start_With_Caveats(xos,first_pragma,FALSE);
	    //WN2F_Append_Pragma_Preamble(xos,first_pragma);
	    if (WN2F_is_omp(first_pragma)) 
	      xos << "END DO";
	    else
	      xos << "END PDO";
	 }
         break;

      case WN_PRAGMA_PARALLEL_SECTIONS:
      case WN_PRAGMA_PSECTION_BEGIN:
         WN2F_OMP_or_PAR_Directive_Newline(xos,first_pragma);
         //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(first_pragma));
	 //WN2F_Append_Pragma_Preamble(xos,first_pragma);
         // correctly end the OpenMP PARALLEL SECTIONS (radu@par.univie.ac.at)
	 if (WN2F_is_omp(first_pragma))
	 {
            xos << "END PARALLEL SECTIONS";
	    if (WN2F_Prompf_Subsection != NULL) {
	      // End a the last SECTION directive seen!

	      // REMOVE WN2F_End_Prompf_Construct(xos, WN2F_Prompf_Subsection);
	       WN2F_Prompf_Subsection = NULL;
	    }

	 }
         else
            xos << "END PSECTION";
         break;

      case WN_PRAGMA_PARALLEL_WORKSHARE:
         WN2F_OMP_or_PAR_Directive_Newline(xos,first_pragma);
	 //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(first_pragma));
	 //WN2F_Append_Pragma_Preamble(xos,first_pragma);
	 xos << "END PARALLEL WORKSHARE";
         break;

      case WN_PRAGMA_WORKSHARE:
         WN2F_OMP_or_PAR_Directive_Newline(xos,first_pragma);
	 //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(first_pragma));
	 //WN2F_Append_Pragma_Preamble(xos,first_pragma);
	 xos << "END WORKSHARE";
         break;

      case WN_PRAGMA_SINGLE_PROCESS_BEGIN:
	 if (!Ignore_Synchronized_Construct(first_pragma, ctxt))
	 {
            WN2F_OMP_or_PAR_Directive_Newline(xos,first_pragma);
	    //WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(first_pragma));
	    //WN2F_Append_Pragma_Preamble(xos,first_pragma);
	    if (WN2F_is_omp(first_pragma)) 
	      xos << "END SINGLE";
	    else 
	      xos << "END SINGLE PROCESS";
            /* append clause COPYPRIVATE (radu@par.univie.ac.at) */
	    WN *wn = first_pragma;
	    while(wn != NULL)
	      if ((WN_operator(wn) == OPR_PRAGMA || WN_operator(wn) == OPR_XPRAGMA) &&
		  WN_pragma(wn) == WN_PRAGMA_COPYPRIVATE)
              {
		xos << "copyprivate";
		Append_Clause_Symbols(xos, WN_PRAGMA_COPYPRIVATE, &wn);
	      }
	      else
                wn = WN_next(wn);
	 }
         break;

      case WN_PRAGMA_MASTER_BEGIN:
	 if (!Ignore_Synchronized_Construct(first_pragma, ctxt))
	 {
	    WN2F_Directive_Newline(xos, "C$", WN_Get_Linenum(first_pragma));
            WN2F_OMP_or_PAR_Directive_Newline(xos,first_pragma);
	    //WN2F_Append_Pragma_Preamble(xos,first_pragma);
	    //xos << "END MASTER";
	 }
         break;

      default:
         emitted = FALSE;
         break; /* Not a region that needs an END pragma */
      }

      if (emitted && WN2F_pragma_list_nowait(first_pragma))
         xos << "nowait";
   }
   return EMPTY_WN2F_STATUS;
} /* WN2F_pragma_list_end */


BOOL
Ignore_Synchronized_Construct(WN          *construct_pragma,  
			      XlationContext& ctxt)
{
   /* This can be TRUE for DOACROSS, PARALLEL, and any paralellization
    * related construct that may occur within a parallel region.
    * It only applies for prompf/mplist (i.e. when Run_w2fc_early).
    */
   BOOL ignore_construct;

   Is_True(WN_operator(construct_pragma) == OPR_PRAGMA,
	   ("Unexpected WHIRL tree in Ignore_Synchronized_Construct"));

   if (!Run_w2fc_early)
   {
      ignore_construct = FALSE;
   }
   else
   {
      if (WN_pragma(construct_pragma) != WN_PRAGMA_DOACROSS)
	 construct_pragma = Get_Enclosing_Parallel_Region(construct_pragma);

      if (construct_pragma == NULL)
	 ignore_construct = FALSE;
      else
      {
	 WN *clause = WN_next(construct_pragma);
	 WN *beyond_last_clause = clause;

	 Skip_Pragma_Clauses(&beyond_last_clause, ctxt);
	 while (clause != beyond_last_clause && 
		WN_pragma(clause) != WN_PRAGMA_SYNC_DOACROSS)
	    clause = WN_next(clause);
	 ignore_construct = (clause != beyond_last_clause);
      }
   }
   return ignore_construct;
} /* Ignore_Synchronized_Construct */

