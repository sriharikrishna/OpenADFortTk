// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif.i,v 1.1 2004/02/18 18:40:47 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif.i,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef wn2xaif_i
#define wn2xaif_i

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include "whirl2xaif.i"
#include "XlationContext.h"
#include <lib/support/xmlostream.h>
#include <lib/support/IntrinsicXlationTable.h>

//************************** Forward Declarations ***************************

//***************************************************************************
// Function entry handlers
//***************************************************************************

namespace whirl2xaif {
  
  extern whirl2xaif::status 
  xlate_FUNC_ENTRY(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_ALTENTRY(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_ignore(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern whirl2xaif::status 
  xlate_unknown(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
}; /* namespace whirl2xaif */


// REMOVE/FIXME: convert to operation (from opcode)
#define WN2F_expr_has_boolean_arg(opc) \
   ((opc) == OPC_BLNOT || (opc) == OPC_BLAND || (opc) == OPC_BLIOR || \
    (opc) == OPC_I4LNOT || (opc) == OPC_I4LAND || (opc) == OPC_I4LIOR)


//***************************************************************************
//
//***************************************************************************

// WNXlationTable: Maps WHIRL OPERATORs to functions designed to
// handle the translation of that particular node.  Handler functions
// have the type 'Handler'.  In the event that no specific handler is
// registered for a particular OPERATOR, a default handler is returned.
class WNXlationTable {
public:
  
  typedef whirl2xaif::status (*Handler)(xml::ostream&, WN*, XlationContext&);

public:
  WNXlationTable();
  ~WNXlationTable();

  Handler operator[](OPERATOR opr) const { Find(opr); }
  Handler Find(OPERATOR opr) const { return table[opr]; }
  
  void Dump(std::ostream& os = std::cerr) const;
  void DDump() const;

private:
  // Should not be used 
  WNXlationTable(const WNXlationTable& x) { }
  WNXlationTable& operator=(const WNXlationTable& x) { return *this; }

  struct InitEntry {
    OPERATOR opr;
    Handler  fn;
  };
  
private:
  static bool initialized;
  
  // The OPERATOR -> Handler table
  static Handler table[];
  static unsigned int tableSz;
  
  // Initialization table
  static InitEntry initTable[];
  static unsigned int initTableSz;
};

//***************************************************************************

#endif /* wn2xaif_i */
