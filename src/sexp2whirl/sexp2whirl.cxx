// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2whirl.cxx,v 1.1 2004/12/15 20:59:24 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/sexp2whirl.cxx,v $
//
// Purpose:
//   Translate S-expression WHIRL to WHIRL.
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

//*************************** Sexp Include Files ****************************

#include <sexp.h>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "sexp2whirl.h"
//#include "sexp2wn.h"
//#include "sexp2symtab.h"

#include <lib/support/WhirlGlobalStateUtils.h>

//************************** Forward Declarations ***************************

//***************************************************************************

static PU_Info*
xlate_IR(sexp_t* ir, int flags);

static PU_Info*
xlate_PUTree(sexp_t* pu_tree, int flags);

static PU_Info* 
xlate_PU(sexp_t* pu, int flags);

static WN* 
xlate_WN(sexp_t* ast, int flags);

//***************************************************************************
// Implementation of interface routines
//***************************************************************************

PU_Info*
sexp2whirl::TranslateIR(sexp_t* ir, int flags)
{
  return xlate_IR(ir, flags);
}

PU_Info* 
sexp2whirl::TranslatePUTree(sexp_t* pu_tree, int flags)
{
  return xlate_PUTree(pu_tree, flags);
}

PU_Info* 
sexp2whirl::TranslatePU(sexp_t* pu, int flags)
{
  return xlate_PU(pu, flags);
}

WN* 
sexp2whirl::TranslateWN(sexp_t* wn, int flags)
{
  return xlate_WN(wn, flags);
}


void 
sexp2whirl::DumpIR(sexp_t* ir, int flags)
{
  const int sz = 1 << 20;
  char* buf = new char[sz];
  
  int rval = print_sexp(buf, sz, ir);
  std::cout << buf << std::endl;
  delete[] buf;
}



//***************************************************************************
// Helper routines
//***************************************************************************

PU_Info*
xlate_IR(sexp_t* ir, int flags) 
{
  return NULL;
}


PU_Info*
xlate_PUTree(sexp_t* pu_tree, int flags)
{
  return NULL;
}


PU_Info*
xlate_PU(sexp_t* pu, int flags)
{  
  return NULL;
}


WN*
xlate_WN(sexp_t* ast, int flags)
{
  return NULL;
}

//***************************************************************************
