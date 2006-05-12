// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/wn2xaif.i,v 1.3 2006/05/12 16:12:23 utke Exp $

#ifndef wn2xaif_i
#define wn2xaif_i

#include <include/Open64BasicTypes.h>

#include "whirl2xaif.h"
#include "XlationContext.h"
#include <lib/support/xmlostream.h>
#include <lib/support/IntrinsicXlationTable.h>

//************************** Forward Declarations ***************************

//***************************************************************************
// Function entry handlers
//***************************************************************************

namespace whirl2xaif {
  
  extern void 
  xlate_FUNC_ENTRY(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern void 
  xlate_ALTENTRY(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern void 
  xlate_ignore(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  
  extern void 
  xlate_unknown(xml::ostream& xos, WN *wn, XlationContext& ctxt);
  

// REMOVE/FIXME: convert to operation (from opcode)
#define WN2F_expr_has_boolean_arg(opc) \
   ((opc) == OPC_BLNOT || (opc) == OPC_BLAND || (opc) == OPC_BLIOR || \
    (opc) == OPC_I4LNOT || (opc) == OPC_I4LAND || (opc) == OPC_I4LIOR)


}; /* namespace whirl2xaif */

#endif /* wn2xaif_i */
