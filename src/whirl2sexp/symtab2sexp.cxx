// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/symtab2sexp.cxx,v 1.1 2004/08/05 18:38:14 eraxxon Exp $

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/symtab2sexp.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "wn2sexp.h"
#include "symtab2sexp.h"

//************************** Forward Declarations ***************************

using namespace whirl2sexp;
using namespace sexp; // for sexp::ostream, etc

//************************** Forward Declarations ***************************

//      Print_local_symtab (stdout, Scope_tab[level]);
//	Print_global_symtab (stdout);
//	Dump_DST (stdout);

static void 
xlate_ST_ignore(sexp::ostream& sos, ST *st);

static void 
xlate_STDecl_error(sexp::ostream& sos, ST *st);
static void 
xlate_STDecl_VAR(sexp::ostream& sos, ST *st);
static void 
xlate_STDecl_FUNC(sexp::ostream& sos, ST *st);
static void 
xlate_STDecl_CONST(sexp::ostream& sos, ST *st);
static void 
xlate_STDecl_PREG(sexp::ostream& sos, ST *st);
static void 
xlate_STDecl_BLOCK(sexp::ostream& sos, ST *st);
static void 
xlate_STDecl_NAME(sexp::ostream& sos, ST *st);
static void 
xlate_STDecl_TYPE(sexp::ostream& sos, ST *st);

//***************************************************************************

#include <alloca.h>
#include <sstream> //FIXME

//***************************************************************************

// usage: xlate_SymbolTables(sos, CURRENT_SYMTAB, symtab);

void 
whirl2sexp::xlate_SymbolTables(sexp::ostream& sos, SYMTAB_IDX symtab_lvl)
{
  //  sos << BegElem("sexp:SymbolTable") << EndAttrs;
  
  xlate_SYMTAB(sos, symtab_lvl);
}


// FIXME: move to xlateSYMTAB.cxx
class xlate_ST_TAB {
public:
  xlate_ST_TAB(sexp::ostream& sos_, SYMTAB_IDX symtab_) 
    : sos(sos_), symtab(symtab_)
  { } 

  // A function object applied to every entry of a ST_TAB
  void operator()(UINT32 idx, ST* st) const 
  { 
    TranslateSTDecl(sos, st);
  }
  
private:
  sexp::ostream&   sos;
  SYMTAB_IDX      symtab;
};


// FIXME: move to xlateSYMTAB.cxx
// xlate_SYMTAB: Translate a WHIRL SYMTAB (a collection of tables) to
// an SEXP symbol table.  'symtab_lvl' is an index (lexical level) in
// the current 'Scope_tab[]'.
void 
whirl2sexp::xlate_SYMTAB(sexp::ostream& sos, SYMTAB_IDX symtab_lvl)
{
  // 'For_all' applies 'operator()' to every entry of St_Table.
  For_all(St_Table, symtab_lvl, xlate_ST_TAB(sos, symtab_lvl));
}

#if 0
void 
whirl2sexp::xlate_PREGTAB(sexp::ostream& sos, SYMTAB_IDX symtab_lvl)
{
  // 'For_all' applies 'operator()' to every entry of Preg_Table.
  For_all(Preg_Table, symtab_lvl, xlate_PREG_TAB(sos, symtab_lvl));
}
#endif


//***************************************************************************

#if 0
static const XlateSTHandlerFunc XlateSTDecl_HandlerTable[CLASS_COUNT] =
{
  &xlate_ST_ignore,     /* CLASS_UNK    == 0 */
  &xlate_STDecl_VAR,    /* CLASS_VAR    == 1 */
  &xlate_STDecl_FUNC,   /* CLASS_FUNC   == 2 */
  &xlate_STDecl_CONST,  /* CLASS_CONST  == 3 */
  &xlate_STDecl_PREG,   /* CLASS_PREG   == 4 */
  &xlate_STDecl_BLOCK,  /* CLASS_BLOCK  == 5 */
  &xlate_STDecl_NAME,   /* CLASS_NAME   == 6 */
  &xlate_STDecl_error,  /* CLASS_MODULE == 7 */
  &xlate_STDecl_TYPE,   /* CLASS_TYPE   == 8 */
  &xlate_STDecl_CONST,  /* CLASS_PARAMETER  == 9 */
};

static const TY2F_HANDLER_FUNC TY2F_Handler[KIND_LAST/*TY_KIND*/] = {
   &TY2F_invalid,   /* KIND_INVALID */
   &TY2F_scalar,    /* KIND_SCALAR */
   &TY2F_array,     /* KIND_ARRAY */
   &TY2F_struct,    /* KIND_STRUCT */
   &TY2F_pointer,   /* KIND_POINTER */
   &TY2F_invalid,   /* KIND_FUNCTION */
   &TY2F_void,      /* KIND_VOID */
};

#endif

//***************************************************************************
// 
//***************************************************************************

