// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/wn2sexp.h,v 1.3 2004/12/08 22:10:06 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/wn2sexp.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef wn2sexp_h
#define wn2sexp_h

//************************** System Include Files ***************************

#include <vector> // STL
#include <list>   // STL

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "whirl2sexp.i"
#include <lib/support/sexpostream.h>

//************************** Forward Declarations ***************************

//***************************************************************************
// Commonly used WHIRL translation functions
//***************************************************************************

namespace whirl2sexp {
    
  // Note: All routines Assume that Open64 symbol table globals are
  // already set.

  // TranslateWN: Translates the given WHIRL node, emitting output to
  // 'sos'.  If 'wn' is NULL, emits an empty list.  
  extern whirl2sexp::status 
  TranslateWN(sexp::ostream& sos, WN* wn);

  // TranslateWNChildren: Given a non-NULL WHIRL node, translates its
  // children, emitting output to 'sos'.
  extern whirl2sexp::status 
  TranslateWNChildren(sexp::ostream& sos, WN* wn);
  
}; /* namespace whirl2sexp */


//***************************************************************************
// S-expressions sexp::ostream operators
//***************************************************************************

// ---------------------------------------------------------
// Shortcut for TranslateWN()
// ---------------------------------------------------------

#if 0 // Is this going to be more of an annoyance than not?

struct TranslateWNInfo_ {
  WN* val;
};

sexp::ostream&
operator<<(std::ostream& os, const TranslateWNInfo_& x)
{
  sexp::ostream& sos = dynamic_cast<sexp::ostream&>(os);
  TranslateWN(sos, x.val);
  return sos;
}

inline TranslateWNInfo_ 
TranslateWN(WN* val)
{
  TranslateWNInfo_ x;
  x.val = val;
  return x;
}

#endif

// ---------------------------------------------------------
// GenSexp*: Generate an S-expression for a given object
// ---------------------------------------------------------

struct GenSexpSymInfo_ {
  ST_IDX val;
};
struct GenSexpTyInfo_ {
  TY_IDX val;
};

struct GenSexpWNOprInfo_ {
  WN* val;
};
struct GenSexpSymRefInfo_ {
  ST_IDX val;
};
struct GenSexpTyUseInfo_ {
  TY_IDX val;
};

template <class T>
struct GenBeginFlgListInfo_ {
  T val;
};


sexp::ostream&
operator<<(std::ostream& os, const GenSexpSymInfo_& x);

inline GenSexpSymInfo_ 
GenSexpSym(ST_IDX val)
{
  GenSexpSymInfo_ x;
  x.val = val;
  return x;
}


sexp::ostream&
operator<<(std::ostream& os, const GenSexpTyInfo_& x);

inline GenSexpTyInfo_ 
GenSexpTy(TY_IDX val)
{
  GenSexpTyInfo_ x;
  x.val = val;
  return x;
}


sexp::ostream&
operator<<(std::ostream& os, const GenSexpWNOprInfo_& x);

inline GenSexpWNOprInfo_ 
GenSexpWNOpr(WN* val)
{
  GenSexpWNOprInfo_ x;
  x.val = val;
  return x;
}


sexp::ostream&
operator<<(std::ostream& os, const GenSexpSymRefInfo_& x);

inline GenSexpSymRefInfo_ 
GenSexpSymRef(ST_IDX val)
{
  GenSexpSymRefInfo_ x;
  x.val = val;
  return x;
}


sexp::ostream&
operator<<(std::ostream& os, const GenSexpTyUseInfo_& x);

inline GenSexpTyUseInfo_ 
GenSexpTyUse(TY_IDX val)
{
  GenSexpTyUseInfo_ x;
  x.val = val;
  return x;
}


// Cf. GenBeginFlgList
template <class T>
sexp::ostream&
operator<<(std::ostream& os, const GenBeginFlgListInfo_<T>& x)
{
  sexp::ostream& sos = dynamic_cast<sexp::ostream&>(os);
  
  T val = x.val;
  
  using namespace sexp;
  using namespace sexp::IOFlags;
  sos << BegList << Atom("flg") << Atom(A_HEX, val);
  // Do not end the list!
  
  return sos;
}

template <class T>
inline GenBeginFlgListInfo_<T> 
GenBeginFlgList(T val)
{
  GenBeginFlgListInfo_<T> x;
  x.val = val;
  return x;
}


//***************************************************************************

#endif /* wn2sexp_h */
