// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/IntrinsicXlationTable.h,v 1.7 2004/06/03 01:37:56 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/IntrinsicXlationTable.h,v $
//
// Purpose:
//    [The purpose of this file]
//
// Description:
//    [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef IntrinsicXlationTable_H 
#define IntrinsicXlationTable_H

//************************* System Include Files ****************************

#include <iostream>
#include <vector>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

//*************************** Forward Declarations ***************************

const char* INTRINSIC_basename(INTRINSIC opcode);

//****************************************************************************

//****************************************************************************
// IntrinsicXlationTable
//****************************************************************************

// IntrinsicXlationTable: There is not a trivial correspondence
// between WHIRL and XAIF function/subroutine calls and intrinsics.
// We use this table to determine how translation between WHIRL <->
// XAIF should proceed.
// 
// These are the types of relationships that currently exist in
// translation.  The starred (*) relationships are explicitly included
// in the table.  
// 
//   WHIRL                          XAIF     
//   -----                          ----     
//   
//                        /-------> SubCall (using WHIRL name)
//                       /--------> FuncCall (using WHIRL name)
//                      /
// * OPR_CALL  <------------------> * Intrinsic, using XAIF name
//
// * OPR_INTRINSIC_CALL <---------> * Intrinsic, using XAIF name
//
// * OPR_INTRINSIC_OP <-----------> * Intrinsic, using XAIF name
// 
// * OPR_TRUNC <------------------> * Intrinsic, using XAIF name
//   et al.
// 
// * OPR_EQ    <------------------> * BooleanOp, using XAIF name
//
class IntrinsicXlationTable {
public:
  
  enum TableType { 
    W2X, // A table optimized for WHIRL->XAIF lookups
    X2W  // A table optimized for XAIF->WHIRL lookups
  };

  // WNOprClass: Three completely different kinds of WHIRL operators
  // are translated into an XAIF intrinsic and vice-versa.
  enum WNOprClass {
    WNCall,       // A WHIRL function or subroutine call
    WNIntrinCall, // A WHIRL intrinsics call
    WNIntrinOp,   // A WHIRL intrinsics operation
    WNExpr,       // A WHIRL expression

    WNOprClass_UNKNOWN // special, reserved for searching table
  };

  static const char* ToString(WNOprClass oprcl);
  
  // XAIFOpr is the analog of the WHIRL 'OPERATOR'.  It is not really
  // needed at this point.
  enum XAIFOpr {
    XAIFSubCall,
    XAIFFuncCall,
    XAIFIntrin,
    XAIFBoolOp,
    
    XAIFOpr_UNKNOWN   // special, reserved for searching table
  };

  static const char* ToString(XAIFOpr opr);

  struct WHIRLInfo {
    WNOprClass oprcl;   // class of the WN operator
    OPERATOR opr;       // the WN operator
    const char* name;   // string qualifier for calls
    unsigned int numop; // number of operands to intrinsic

    //WHIRLInfo();
    void Dump(std::ostream& os = std::cerr) const;
    void DDump() const;
  };
  
  struct XAIFInfo {
    // N.B.: 'key' serves two purposes at the moment.  First it
    // disambiguates multiple WHIRL constructs that translate into the
    // same XAIF intrinsic (e.g. calls to SIN or DSIN); during
    // WHIRL->XAIF, the key will be placed in the xaif:Intrinsic's
    // annotation attribute.  Second, during XAIF->WHIRL if an
    // ambiguous xaif:Intrinsic is found (e.g. sin_scal without its
    // annotation attribute), the key assigns a priority (based on
    // strcmp()) that defines the default WHIRL construct to use.
    
    XAIFOpr opr;        // the XAIF 'operator'
    const char* name;   // intrinsic name
    const char* key;    // disambiguates otherwise identical xaif intrinsics
    unsigned int numop; // number of operands to intrinsic

    //XAIFInfo();
    void Dump(std::ostream& os = std::cerr) const;
    void DDump() const;
  };

  struct Entry {
    WHIRLInfo whirl_info;
    XAIFInfo xaif_info;
  };

public:
  IntrinsicXlationTable(TableType tt);
  ~IntrinsicXlationTable();

  XAIFInfo* FindXAIFInfo(OPERATOR opr, const char* name);
  WHIRLInfo* FindWHIRLInfo(XAIFOpr opr, const char* name, const char* key);

  void Dump(std::ostream& os = std::cerr) const;
  void DDump() const;

private:
  // Should not be used 
  IntrinsicXlationTable(const IntrinsicXlationTable& p) { }
  IntrinsicXlationTable& operator=(const IntrinsicXlationTable& p) { return *this; }

private:

  class lt_SortedTable {
  public:
    lt_SortedTable(TableType tt_) 
      : tt(tt_), ignoreXaifKey(false) { }
    lt_SortedTable(TableType tt_, bool ignoreXaifKey_) 
      : tt(tt_), ignoreXaifKey(ignoreXaifKey_) { }
    ~lt_SortedTable() { }

    // return true if e1 < e2; false otherwise
    bool operator()(const Entry* e1, const Entry* e2) const;

    // required for binary_search(..), lower_bound(..) on GCC 3.3 (?!)
    bool operator()(Entry*& e1, const Entry& e2) {
      return operator()(dynamic_cast<Entry*>(e1), 
			dynamic_cast<const Entry*>(&e2));
    }
    bool operator()(const Entry& e1, Entry*& e2) {
      return operator()(dynamic_cast<const Entry*>(&e1), 
			dynamic_cast<Entry*>(e2));
    }
    
    // required for binary_search(..), lower_bound(..) on GCC 3.3 (?!)
    bool operator()(const Entry& e1, const Entry& e2) {
      return operator()(dynamic_cast<const Entry*>(&e1), 
			dynamic_cast<const Entry*>(&e2));
    }
    bool operator()(const Entry*& e1, const Entry*& e2) {
      return operator()(dynamic_cast<const Entry*>(e1), 
			dynamic_cast<const Entry*>(e2));
    }
    
  private:
    // Disable
    lt_SortedTable() { }
    
  private:
    TableType tt; // sorting type
    bool ignoreXaifKey; // only meaningful in X2W mode
  };
  
  typedef std::vector<Entry*>     SortedTable;
  typedef SortedTable::iterator   SortedTableIt;
  typedef SortedTable::value_type SortedTableVal;

private:
  
  TableType tableType;
  SortedTable sortedTable;
  
  static Entry table[];
  static unsigned int tableSz;
};

//****************************************************************************

#endif

