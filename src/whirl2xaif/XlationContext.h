// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/XlationContext.h,v 1.10 2003/09/02 15:02:20 eraxxon Exp $

// * BeginCopyright *********************************************************
/*
  Copyright (C) 2000, 2001 Silicon Graphics, Inc.  All Rights Reserved.

  This program is free software; you can redistribute it and/or modify it
  under the terms of version 2 of the GNU General Public License as
  published by the Free Software Foundation.

  This program is distributed in the hope that it would be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  

  Further, this software is distributed without any warranty that it is
  free of the rightful claim of any third person regarding infringement 
  or the like.  Any license provided herein, whether implied or 
  otherwise, applies only to this software file.  Patent licenses, if 
  any, provided herein do not apply to combinations of this program with 
  other software, or any other product whatsoever.  

  You should have received a copy of the GNU General Public License along
  with this program; if not, write the Free Software Foundation, Inc., 59
  Temple Place - Suite 330, Boston MA 02111-1307, USA.

  Contact information:  Silicon Graphics, Inc., 1600 Amphitheatre Pky,
  Mountain View, CA 94043, or:

  http://www.sgi.com

  For further information regarding this notice, see:

  http://oss.sgi.com/projects/GenInfo/NoticeExplan
*/
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/XlationContext.h,v $
//
// Purpose:
//   Represents the context in which translation of WHIRL->XAIF occurs. 
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/wn2f.h
//
//***************************************************************************

#ifndef XlationContext_INCLUDED
#define XlationContext_INCLUDED

//************************** System Include Files ***************************

#include <list> // STL
#include <iostream>

//************************** Open64 Include Files ***************************

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

#include <lib/support/WhirlIDMaps.h>
#include <lib/support/SymTab.h>

//************************** Forward Declarations ***************************

//***************************************************************************

//***************************************************************************
// XlationContext
//***************************************************************************

// XlationContext: maintains an internal stack of translation
//   contexts, allowing users to 1) create new child contexts (push), 2)
//   destroy and return to parent contexts (pop) and 3) query the
//   current context.  The current translation context provides
//   information about how to interpret the present WHIRL data.  There 
//   should always be at least one context on the stack.

// For whirl2xaif: A translation context for an XAIF construct
// corresponds to its parent construct.  Thus there will be one
// translation context on the stack for every 'indendation' level.
// Context flags indicate significant facts about the parent construct
// and will typically correspond to XAIF concepts (as opposed to
// WHIRL).

// Upon creation, one context exists on the stack.
// FIXME: put in whirl2xaif namespace?
class XlationContext
{
public: 
  
  // Ctxt: represents the current context
  class Ctxt {
  public: 
    Ctxt();
    virtual ~Ctxt();

    // Flags for context
    BOOL AreFlags(mUINT32 f) const { return (flags & f); }
    void SetFlags(mUINT32 f)       { flags = flags | f; }
    void ResetFlags(mUINT32 f)     { flags = flags & ~f; }

    // FIXME: move according to notes below
    // Non Scalar Symbol table for context (this class does not assume
    // ownership of symbol tables)
    NonScalarSymTab* GetSymTab() const { return symtab; }
    void SetSymTab(NonScalarSymTab* x) { symtab = x; }

    WNToWNIdMap* GetWNMap() const { return wnmap; }
    void SetWNMap(WNToWNIdMap* x) { wnmap = x; }
    
    
    // WHIRL node for context (this class does not assume ownership of WN*)
    WN*  GetWN() const { return wn; }
    void SetWN(WN* x) { wn = x; }

    // Ids for vertices and edges within the translated graphs.
    // Ids are unique within the context; id > 0.  
    UINT GetNewVId() { return ++nextVId; }
    UINT GetVId() const { return nextVId; } // return current id; 0 for invalid
    UINT PeekVId() const { return nextVId + 1; } // return a peek of next id
    
    UINT GetNewEId() { return ++nextEId; }
    UINT GetEId() const { return nextEId; } // return current id; 0 for invalid
    UINT PeekEId() const { return nextEId + 1; } // return a peek of next id

    virtual void Dump(std::ostream& o = std::cerr) const;
    virtual void DDump() const;
    
  private:
    mUINT32 flags;
    WN*     wn;

    UINT nextVId; // next unique vertex id for this context
    UINT nextEId; // next unique edge id for this context
    
    // FIXME: Move into a specialized derived class such as CtxtX (extended)
    NonScalarSymTab* symtab;
    WNToWNIdMap* wnmap; 
  };
  
  
public:
  XlationContext();
  virtual ~XlationContext();

  // -------------------------------------------------------
  // Context manipulation (Create, Delete...)
  // -------------------------------------------------------

  // Create a new child context and make it the current context
  XlationContext& CreateContext();
  XlationContext& CreateContext(mUINT32 flags_);
  XlationContext& CreateContext(mUINT32 flags_, 
				NonScalarSymTab* symtab_, WNToWNIdMap* wnmap_);
  XlationContext& CreateContext(mUINT32 flags_, WN* wn_);

  // Delete the current context and make its parent the current
  // context.  Everything (including memory) associated with the old
  // context will be deleted.
  XlationContext& DeleteContext();

  // Returns the current context
  Ctxt& CurContext() const { return const_cast<Ctxt&>(ctxtstack.front()); }

  // -------------------------------------------------------
  // Id generation
  // -------------------------------------------------------

  // GetNewId: Ids for vertices and edges within the translated
  // graphs.  Returns a new id (id > 0), guaranteed to be unique
  // within the context.
  UINT GetNewVId() { return CurContext().GetNewVId(); }
  UINT GetVId() const { return CurContext().GetVId(); } // FIXME
  UINT PeekVId() const { return CurContext().PeekVId(); }

  UINT GetNewEId() { return CurContext().GetNewEId(); }
  UINT GetEId() const { return CurContext().GetEId(); } // FIXME
  UINT PeekEId() const { return CurContext().PeekEId(); }

  // -------------------------------------------------------
  // Id maps
  // -------------------------------------------------------

  // ST_TAB* -> SymTabId map: (We do not assume ownership of the map)
  SymTabId FindSymTabId(ST_TAB* stab);
  SymTabToSymTabIdMap* GetSymTabToIdMap() const { return stab2idMap; }
  void SetSymTabToIdMap(SymTabToSymTabIdMap* x) { stab2idMap = x; }
  
  // PU_Info* -> PUId map: (We do not assume ownership of the map)
  PUId FindPUId(PU_Info* pu);
  PUToPUIdMap* GetPUToIdMap() const { return pu2idMap; }
  void SetPUToIdMap(PUToPUIdMap* x) { pu2idMap = x; }

  // WN* -> WNId map
  WNId FindWNId(WN* wn);

  // -------------------------------------------------------
  // Misc
  // -------------------------------------------------------

  // Searches for symbol tables and queries them for 'wn'.  The symbol
  // table search begins at the current context and continues to
  // parents.
  NonScalarSym* FindNonScalarSym(WN* wn);

  WN* GetWN() { return CurContext().GetWN(); }

  virtual void Dump(std::ostream& o = std::cerr, const char* pre = "") const;
  virtual void DDump() const;

  friend class XlationContextIterator;

public:
  // FIXME: these refer to the current context; they support the
  // crusty old implementation of W2F_CONTEXT
  mUINT32 flags;
  
  enum Flags {
    NOFLAG           = 0x00000000,
    DEREF_ADDR       = 0x00000004,
    VARREF           = 0x00000008  // within xaif:VariableReference; inherited
#define XlationContext_NO_NEWLINE              0x00000100
#define XlationContext_HAS_LOGICAL_ARG         0x00000200
#define XlationContext_IS_LOGICAL_ARG          0x00000400
#define XlationContext_IS_LOGICAL_OPERATION    0x00000800
#define XlationContext_NO_PARENTHESIS          0x00001000

#define XlationContext_IO_STMT                 0x00004000
#define XlationContext_DEREF_IO_ITEM           0x00008000
#define XlationContext_ORIGFMT_IOCTRL          0x00010000
#define XlationContext_FMT_IO                  0x00020000
#define XlationContext_CRAY_IO                 0x00040000
#define XlationContext_ISSUE_IOC_UNIT_ASTERISK 0x00080000

#define XlationContext_EXPLICIT_REGION         0x00100000
#define XlationContext_HAS_NO_ARR_ELMT         0x00200000
    
  };

#define reset_XlationContext(c) ((c).flags = 0U)
  
  // Indicates that we expect to dereference an address expression.
  // LDA or ARRAY nodes should not be translated unless this flag has
  // been set, other than when we can use an "address of" operator
  // in Fortran.
  BOOL IsDerefAddr() const { return (flags & DEREF_ADDR); }
  void SetDerefAddr()      { flags = flags | DEREF_ADDR; }
  void ResetDerefAddr()    { flags = flags & ~DEREF_ADDR; } // Clear
  
  // Within a xaif:VariableReference (inherited)
  BOOL IsVarRef() const { return CurContext().AreFlags(VARREF); }
  void SetVarRef()      { CurContext().SetFlags(VARREF); }
  //void ResetVarRef() { CurContext().ResetFlags(VARREF); }

  // Indicates that we should not start the next statement on a new
  // line.  This only needs to be taken into account for statement
  // types where it is an issue.
#define XlationContext_no_newline(c) ((c).flags & XlationContext_NO_NEWLINE)
#define set_XlationContext_no_newline(c)\
   ((c).flags = (c).flags | XlationContext_NO_NEWLINE)
#define reset_XlationContext_no_newline(c)\
   ((c).flags = (c).flags & ~XlationContext_NO_NEWLINE)

  // This flag indicates that we are in a context where we expect the
  // arguments to the current expression to evaluate to logically typed
  // values.
#define XlationContext_has_logical_arg(c)\
   ((c).flags & XlationContext_HAS_LOGICAL_ARG)
#define set_XlationContext_has_logical_arg(c)\
   ((c).flags = (c).flags | XlationContext_HAS_LOGICAL_ARG)
#define reset_XlationContext_has_logical_arg(c)\
   ((c).flags = (c).flags & ~XlationContext_HAS_LOGICAL_ARG)

  // This flag indicates that we are in a context where we expect the
  // current expression to evaluate to a logically typed arg.
#define XlationContext_is_logical_arg(c)\
   ((c).flags & XlationContext_IS_LOGICAL_ARG)
#define set_XlationContext_is_logical_arg(c)\
   ((c).flags = (c).flags | XlationContext_IS_LOGICAL_ARG)
#define reset_XlationContext_is_logical_arg(c)\
   ((c).flags = (c).flags & ~XlationContext_IS_LOGICAL_ARG)

  // this flag indicates that we need to print out logical
  // operations such as .eqv. instead of arith operations like .eq.
#define XlationContext_is_logical_operation(c)\
   ((c).flags & XlationContext_IS_LOGICAL_OPERATION)
#define set_XlationContext_is_logical_operation(c)\
   ((c).flags = (c).flags | XlationContext_IS_LOGICAL_OPERATION)
#define reset_XlationContext_is_logical_operation(c)\
   ((c).flags = (c).flags & ~XlationContext_IS_LOGICAL_OPERATION)

  // This flag indicates that we are in a context where we need not
  // enclose a Fortran expression in parenthesis (subexpressions may
  // still be enclosed in parenthesis.
#define XlationContext_no_parenthesis(c)\
   ((c).flags & XlationContext_NO_PARENTHESIS)
#define set_XlationContext_no_parenthesis(c)\
   ((c).flags = (c).flags | XlationContext_NO_PARENTHESIS)
#define reset_XlationContext_no_parenthesis(c)\
   ((c).flags = (c).flags & ~XlationContext_NO_PARENTHESIS)


  // This flag indicates whether or not we are inside a Fortran IO statement.
#define XlationContext_io_stmt(c)\
   ((c).flags & XlationContext_IO_STMT)
#define set_XlationContext_io_stmt(c)\
   ((c).flags = (c).flags | XlationContext_IO_STMT)
#define reset_XlationContext_io_stmt(c)\
   ((c).flags = (c).flags & ~XlationContext_IO_STMT)

  // This flag indicates whether or not to dereference IO_ITEMS.
#define XlationContext_deref_io_item(c)\
   ((c).flags & XlationContext_DEREF_IO_ITEM)
#define set_XlationContext_deref_io_item(c)\
   ((c).flags = (c).flags | XlationContext_DEREF_IO_ITEM)
#define reset_XlationContext_deref_io_item(c)\
   ((c).flags = (c).flags & ~XlationContext_DEREF_IO_ITEM)

  // This flag indicates whether or not to replace an OPC_LABEL
  // item with an IOC_VARFMT_ORIGFMT item.
#define XlationContext_origfmt_ioctrl(c)\
   ((c).flags & XlationContext_ORIGFMT_IOCTRL)
#define set_XlationContext_origfmt_ioctrl(c)\
   ((c).flags = (c).flags | XlationContext_ORIGFMT_IOCTRL)
#define reset_XlationContext_origfmt_ioctrl(c)\
   ((c).flags = (c).flags & ~XlationContext_ORIGFMT_IOCTRL)

  // this flag indicates that formatted IO is being processed 
  // It allows interpretation of craylibs IO_NONE specifiers
#define XlationContext_fmt_io(c)\
   ((c).flags & XlationContext_FMT_IO)
#define set_XlationContext_fmt_io(c)\
   ((c).flags = (c).flags | XlationContext_FMT_IO)
#define reset_XlationContext_fmt_io(c)\
   ((c).flags = (c).flags & ~XlationContext_FMT_IO)

  // this flag indicates that IO processing deals with craylibs
  // not f77 mips libs.
#define XlationContext_cray_io(c)\
   ((c).flags & XlationContext_CRAY_IO)
#define set_XlationContext_cray_io(c)\
   ((c).flags = (c).flags | XlationContext_CRAY_IO)
#define reset_XlationContext_cray_io(c)\
   ((c).flags = (c).flags & ~XlationContext_CRAY_IO)
  
  // add a flag to see if we need issue default UNIT in io stmts
  // in READ/WRITE/PRINT stmts,must have UNIT=*
  // but in other stmt such as INQUIRE if there already
  // is FILE,issue UNIT=* will cause problems
#define XlationContext_issue_ioc_asterisk(c)\
   ((c).flags & XlationContext_ISSUE_IOC_UNIT_ASTERISK)
#define set_XlationContext_issue_ioc_asterisk(c)\
   ((c).flags = (c).flags | XlationContext_ISSUE_IOC_UNIT_ASTERISK)
#define reset_XlationContext_issue_ioc_asterisk(c)\
   ((c).flags = (c).flags & ~XlationContext_ISSUE_IOC_UNIT_ASTERISK)


  // This flag indicates whether or not a pragma directive can apply
  // to an explicit region.  A pragma directive that can only apply
  // to an explicit region in source-code must be ignored if the 
  // region to which it belongs is not emitted.
#define XlationContext_explicit_region(c)\
   ((c).flags & XlationContext_EXPLICIT_REGION)
#define set_XlationContext_explicit_region(c)\
   ((c).flags = (c).flags | XlationContext_EXPLICIT_REGION)
#define reset_XlationContext_explicit_region(c)\
   ((c).flags = (c).flags & ~XlationContext_EXPLICIT_REGION)

#define XlationContext_has_no_arr_elmt(c)\
   ((c).flags & XlationContext_HAS_NO_ARR_ELMT)
#define set_XlationContext_has_no_arr_elmt(c)\
   ((c).flags = (c).flags | XlationContext_HAS_NO_ARR_ELMT)
#define reset_XlationContext_has_no_arr_elmt(c)\
   ((c).flags = (c).flags & ~XlationContext_HAS_NO_ARR_ELMT)

private: 
  // Disable for now
  XlationContext(const XlationContext& x) { }
  XlationContext& operator=(const XlationContext& x) { return *this; }
  
  XlationContext& Ctor(mUINT32 flags_, WN* wn_,
		       NonScalarSymTab* symtab_, WNToWNIdMap* wnmap_);
  
  // Use a list instead a stack so that we can easily examine
  // contents.  The top of the stack will be the *front* of the
  // list. (push_front, pop_front).
  typedef std::list<Ctxt>           CtxtStack;
  typedef CtxtStack::iterator       CtxtStackIt;
  typedef CtxtStack::const_iterator CtxtStackItC;

private:
  SymTabToSymTabIdMap* stab2idMap;
  PUToPUIdMap* pu2idMap;

  CtxtStack ctxtstack;
};

//***************************************************************************
// XlationContextIterator
//***************************************************************************

// 'XlationContextIterator': iterator for the context stack within an
// XlationContext.  Iteration begins with the innermost context (top
// of the stack).
class XlationContextIterator {
public:   
  XlationContextIterator(const XlationContext& x);
  ~XlationContextIterator();

  // Returns the current Ctxt* or NULL
  XlationContext::Ctxt* Current() const {
    if (it != xctxt.ctxtstack.end()) { 
      return const_cast<XlationContext::Ctxt*>( &(*it) ); 
    } else { 
      return NULL; 
    }
  }

  void operator++()    { ++it; } // prefix increment
  void operator++(int) { it++; } // postfix increment

  bool IsValid() const { return it != xctxt.ctxtstack.end(); } 
  bool IsEmpty() const { return it == xctxt.ctxtstack.end(); }

  // Reset and prepare for iteration again
  void Reset() { it = xctxt.ctxtstack.begin(); }

private:
  // Should not be used
  XlationContextIterator();
  XlationContextIterator(const XlationContextIterator& x);
  XlationContextIterator& operator=(const XlationContextIterator& x)
    { return *this; }

protected:
private:
  const XlationContext& xctxt;
  XlationContext::CtxtStackItC it;
};

//***************************************************************************

#endif /* XlationContext_INCLUDED */
