// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/sexputil.h,v 1.1 2004/12/20 15:17:19 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/sexputil.h,v $
//
// Purpose:
//   Utilities for use with the sexp library.  Essentially, a set of
//   wrappers for accessing data.
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef sexputil_h
#define sexputil_h

//************************** System Include Files ***************************

//*************************** Sexp Include Files ****************************

#include <sexp.h>

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

//***************************************************************************

namespace sexp {

// ---------------------------------------------------------
// sexp type (atom, list), 
// ---------------------------------------------------------

inline bool
is_atom(sexp_t* sx) 
{ 
  return (sx->ty == SEXP_VALUE); 
}
  
inline bool 
is_list(sexp_t* sx) 
{ 
  return (sx->ty == SEXP_LIST); 
}


// ---------------------------------------------------------
// Atom/value operations
// ---------------------------------------------------------

inline char* 
get_value(sexp_t* sx) 
{ 
  return sx->val; 
}

inline bool  
is_atom_basic(sexp_t* sx) 
{ 
  return (sx->aty == SEXP_BASIC); 
}
  

// ---------------------------------------------------------
// List operations
// ---------------------------------------------------------

// get_elemx: Given a list, get the nth element in the list (beginning at 0)
inline sexp_t*
get_elem(sexp_t* sx, unsigned int n) 
{ 
  sexp_t* elm = sx->list; // first element
  for (int i = 0; elm && i < n; ++i, elm = elm->next) { }
  return elm;
}

inline sexp_t*
get_elem0(sexp_t* sx) 
{ 
  return sx->list; 
}

inline sexp_t*
get_elem1(sexp_t* sx) 
{ 
  return (sx->list) ? sx->list->next : NULL; 
}
  
inline sexp_t*
get_elem2(sexp_t* sx) 
{
  return (sx->list && sx->list->next) ? sx->list->next->next : NULL; 
}

inline sexp_t*
get_elem3(sexp_t* sx) 
{
  return get_elem(sx, 3);
}


// get_next: Given an element in a list, return its immediate sibling
inline sexp_t*
get_next(sexp_t* sx) 
{
  return sx->next; 
}


  
}; /* namespace sexp */

//***************************************************************************

#endif /* sexputil_h */
