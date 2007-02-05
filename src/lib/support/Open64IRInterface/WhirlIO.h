// -*-Mode: C++;-*-
// $Header: /home/derivs2/mstrout/CVSRepository/UseNewOA-Open64/Open64IRInterface/WhirlIO.h,v 1.1.1.1 2004/04/16 15:58:28 mstrout Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /home/derivs2/mstrout/CVSRepository/UseNewOA-Open64/Open64IRInterface/WhirlIO.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef WhirlIO_h_INCLUDED
#define WhirlIO_h_INCLUDED

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include "Open64BasicTypes.h"

//*************************** User Include Files ****************************

#include "WhirlGlobalStateUtils.h"

//************************** Forward Declarations ***************************

//***************************************************************************

// ReadIR: Given a WHIRL filename, reads the entire contents into
// memory to form a PU forest (a collection of PU trees).  Prepares
// both the regular symbol tables and the back end symbol tables.
PU_Info*
ReadIR(const char* irfilename);

// WriteIR: given a filename write the entire IR (a PU forest) to
// disk.  *Warning*: Writing to disk also frees part of the IR when
// compiled with BACK_END.
void 
WriteIR(const char* irfilename, PU_Info* pu_forest);

// FreeIR: Given a PU forest, frees all memory consumed by it.
void 
FreeIR(PU_Info *pu_forest);

void 
PrepareIR(PU_Info *pu_forest);

void 
DumpIR(PU_Info *pu_forest);

//***************************************************************************

#endif /* WhirlIO_h_INCLUDED */
