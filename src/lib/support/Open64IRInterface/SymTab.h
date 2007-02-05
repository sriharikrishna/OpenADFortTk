// -*-Mode: C++;-*-
// $Header: /home/derivs2/mstrout/CVSRepository/UseNewOA-Open64/Open64IRInterface/SymTab.h,v 1.2 2006/03/16 03:48:55 mstrout Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /home/derivs2/mstrout/CVSRepository/UseNewOA-Open64/Open64IRInterface/SymTab.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef SymTab_H 
#define SymTab_H

//************************** System Include Files ***************************

#include <map>
#include <string>
#include <iostream>

//************************** Open64 Include Files ***************************

#include "Open64BasicTypes.h"

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

bool 
IsVarRefTranslatableToXAIF(const WN* wn);


bool
IsScalarRef(TY_IDX baseobj_ty, TY_IDX refobj_ty);

bool
IsNonScalarRef(TY_IDX baseobj_ty, TY_IDX refobj_ty);

bool
IsNonScalarRef(const WN* wn);


#endif 
