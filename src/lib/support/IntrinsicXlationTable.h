// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/IntrinsicXlationTable.h,v 1.1 2003/11/13 14:54:27 eraxxon Exp $

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
//    See, in particular, the comments associated with 'DCPIProfile'.
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
//   WNEntry                        XAIFEntry
//   -------                        _________
//   
//                        /-------> SubCall (using WHIRL name)
//                       /--------> FuncCall (using WHIRL name)
//                      /
// * OPR_CALL  <------------------> * Intrinsic, using XAIF name
// 
// * OPR_INTRINSIC_OP <-----------> * Intrinsic, using XAIF name
// 
// * OPR_TRUNC <------------------> * Intrinsic, using XAIF name
//   et al.
//
class IntrinsicXlationTable {
public:
  
  enum TableType { 
    W2X, // A table optimized for WHIRL->XAIF lookups
    X2W  // A table optimized for XIAF->WHIRL lookups
  };

  // XAIFOpr is the analog of the WHIRL 'OPERATOR'.  It is not really
  // needed at this point.
  enum XAIFOpr {
    SubCall,
    FuncCall,
    Intrinsic
  };

  static const char* XAIFOpr2Str(XAIFOpr opr);

  struct WHIRLInfo {
    OPERATOR opr;       // the WN operator (call or intrinsic)
    const char* name;   // string qualifier for calls
    unsigned int numop; // number of operands to intrinsic

    void Dump(std::ostream& os = std::cerr) const;
    void DDump() const;
  };
  
  struct XAIFInfo {
    XAIFOpr opr;        // the XAIF 'operator'
    const char* name;   // intrinsic name (if applicable)
    unsigned int numop; // number of operands to intrinsic

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
  WHIRLInfo* FindWHIRLInfo(XAIFOpr opr, const char* name);

  void Dump(std::ostream& os = std::cerr) const;
  void DDump() const;

private:
  // Should not be used 
  IntrinsicXlationTable(const IntrinsicXlationTable& p) { }
  IntrinsicXlationTable& operator=(const IntrinsicXlationTable& p) { return *this; }

private:

  class lt_SortedTable {
  public:
    lt_SortedTable(TableType tt_) : tt(tt_) { }
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

