// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/sexpostream.h,v 1.1 2004/08/05 18:38:14 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/sexpostream.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

#ifndef sexpostream_INCLUDED_h
#define sexpostream_INCLUDED_h

//************************* System Include Files ****************************

#include <iostream>
#include <string>
#include <list> // STL

//*************************** User Include Files ****************************

//*************************** Forward Declarations ***************************

//****************************************************************************

// ---------------------------------------------------------
// sexp::ostream:
// 
// FIXME: we do not require that this be a full xml document (no state
// for dtd, etc.) since one should be able to create subdocuments that
// can be appended to larger ones.
// ---------------------------------------------------------
namespace sexp {

  namespace IOFlags {
    
    enum IOFlags_t {
      ATOM_MASK  = 0x0000ffff, // reserves x bits for atom flags
      LIST_MASK  = 0xffff0000, // reserves x bits for list flags
      
      NONE       = 0x00000000, // no flag
      
      // atom flags
      A_SQUOTE   = 0x00000001, // single quote atom
      A_DQUOTE   = 0x00000002, // double quote atom

      // list flags
      L_foofoo1  = 0x10000000, // ...
      
      L_NONEMPTY = 0x80000000  // internal use: list is not empty
    };
    
    inline bool 
    IsFlag(int flags, IOFlags_t flg) { return (flags & flg); }
    
    inline void 
    SetFlag(int& flags, IOFlags_t flg) { flags = (flags | flg); }
    
    inline void 
    ResetFlag(int& flags, IOFlags_t flg) { flags = (flags & ~flg); }
    
  }; /* namespace IOFlags */


class ostream : public std::ostream {
 public:
  ostream(std::streambuf* sb);
  virtual ~ostream();

  // ---------------------------------------------------------

  class Exception {
  public:
    Exception (const char* msg_) { msg = msg_; }
    virtual ~Exception () { }

    virtual const std::string& GetMessage() const { return msg; }
    virtual void Report(std::ostream& os) const { 
      os << "sexp::ostream::Exception: " << msg << std::endl; 
    }    
    virtual void Report() const { Report(std::cerr); }

  private: 
    std::string msg;
  };
  
  // ---------------------------------------------------------
  
  // BegList: Generate a new list [(...], using flags to override
  // default formatting (atom flags apply to all atoms in list).
  // Indentation is incremented, if necessary.
  void BegList(int flags = IOFlags::NONE)
    throw (Exception);

  // EndList: End the current list [...)].  Indentation is decremented, if
  // necessary.
  void EndList();
  
  // Atom: Output the sexp-atom 'atom', leaving the stream ready to
  // accept another sexp. Uses the atom flag to override default
  // formatting for this atom. [FIXME: escape certain chars?]
  template <class T>
    void Atom(int aflags, const T& val);

  template <class T>
    void Atom(const T& val) { Atom(IOFlags::NONE, val); }

  // Note specializations below
  

  // BegAtom and EndAtom together are equivalent to Atom.  These
  // functions are useful, e.g., when the atom needs to be
  // formed from several sub-strings.
  
  // BegAtom: Prepare the stream for the atom, using flags for formatting.
  void BegAtom(int aflags = IOFlags::NONE);
  
  // EndAtom: End the atom and prepare the stream for another sexp.
  void EndAtom();
  
  // Quote: ***
  void Quote();
  
  
  // ---------------------------------------------------------
  
  // BegComment/EndComment: Ouput an arbitrary comment at the end of
  // the current line.  Note that EndComment() necessarily ends the
  // line.
  void BegComment();
  void EndComment();

  // Comment: Output an indented, one-line comment (including
  // newline).  A previous incomplete start tag is closed.
  void Comment(const char* str);

  // ---------------------------------------------------------
  
  // EndLine: Output a new line and set prepare indentation.
  void EndLine();
  
  // Indentation: Both IndentAmnt (whitespace between the left margin
  // and the text) and the IndentStep (amount the indentation changes
  // for the next level) can be set independently.  It is
  // possible to have a negative step, but a negative amount is
  // ignored.
  void Indent();
  void IndentIncr() { indentAmnt += indentStep; }
  void IndentDecr() { indentAmnt -= indentStep; }
  bool IsIndent() { return (indentStep == 0 && indentAmnt == 0); }

  void SetIndentAmnt(int amnt) { indentAmnt = amnt; }
  void SetIndentStep(int step) { indentStep = step; }
  int GetIndentAmnt() { return indentAmnt; }
  int GetIndentStep() { return indentStep; }
  
  // FIXME Add a setIndent(sexp::ostream) to coordinate indentation settings

 protected:

 private:
  // Disable
  ostream(const ostream& x);
  ostream& operator=(const ostream& x) { return *this; }

  void AddSpaceIfNecessary(int flags);
  
 private: 
  // Stack of elements.  Contains IOFlags::IOFlags_t that apply to the
  // current list.  (Use a list instead a stack so that we can easily
  // examine contents.  The top of the stack will be the *front* of
  // the list. (push_front, pop_front).
  typedef std::list<int> SListStack; 
  
 private: 

  enum State {
    // A list of mutually exclusive states 
    INIT       = 0x00000001, // initial state, nothing has happened
    FINI       = 0x00000002, // a complete sexp

    LIST_OPENI = 0x00000004, // within list, incompleted atom
    LIST_OPEN  = 0x00000008, // within list, completed atom

    STMASK     = 0xff000000, // reserves 8 bits for state qualifiers

    // A list of state qualifiers (can co-exist with some/all of the above)
    ERR        = 0x10000000, // error
    COMMENT    = 0x20000000  // within a comment
  };
  
  enum Action {
    // A list of mutually exclusive actions, affecting context of sexp
    BEG_LIST, END_LIST,
    BEG_ATOM, END_ATOM,
    BEG_COMMENT, END_COMMENT, 
    END_LINE,
    INDENT
  };

  // Access to mutually exclusive states (do not use with state qualifiers!)
  bool IsState(State st) { return (st & state); }
  void SetState(State st) { state = ((state & STMASK) | st); }
  
  // Access to state qualifiers
  bool IsStateError() { return (state & ERR); }
  void SetStateError() { state = (state | ERR); }
  
  bool IsStateComment() { return (state & COMMENT); }
  void SetStateComment() { state = (state | COMMENT); }
  void ResetStateComment() { state = (state & ~COMMENT); }

  // Access to actions
  bool WasAction(Action a) { return (lastAction == a); }
  void SetAction(Action a) { lastAction = a; }
  
 private:
  SListStack slistStack; // represents nesting level of sexp-lists
  int curAtomFlags;      // flags for the current atom only
  unsigned int state;
  Action lastAction;     // most recent action
  
  int indentAmnt;
  int indentStep;
};

}; /* namespace sexp */


//***************************************************************************
// Definitions/specializations for sexp::ostream member template functions
//***************************************************************************

template<class T> 
void
sexp::ostream::Atom(int aflags, const T& val)
{
  // Sanity check -- rely on BegAtom()
  BegAtom(aflags);
  (*this) << val;
  EndAtom();
}

template <>
void 
sexp::ostream::Atom(int aflags, const char* const & val);


//***************************************************************************
// sexp::ostream operators that take no arguments
//***************************************************************************

namespace sexp {

typedef ostream& (*omanip)(ostream&);

inline ostream& 
operator<<(std::ostream& os, omanip f)
{ 
  ostream& sos = dynamic_cast<ostream&>(os);
  return f(sos);
}


inline ostream& 
EndList(ostream& sos)
{ 
  sos.EndList();
  return sos;
}

inline ostream& 
EndAtom(ostream& sos)
{ 
  sos.EndAtom();
  return sos;
}


inline ostream& 
BegComment(ostream& sos)
{ 
  sos.BegComment();
  return sos;
}

inline ostream& 
EndComment(ostream& sos)
{ 
  sos.EndComment();
  return sos;
}


inline ostream& 
EndLine(ostream& sos)
{ 
  sos.EndLine();
  return sos;
}

inline ostream& 
Indent(ostream& sos)
{ 
  sos.Indent();
  return sos;
}

inline ostream& 
IndentIncr(ostream& sos)
{ 
  sos.IndentIncr();
  return sos;
}

inline ostream& 
IndentDecr(ostream& sos)
{ 
  sos.IndentDecr();
  return sos;
}

}; /* namespace sexp */


//***************************************************************************
// sexp::ostream operators that take arguments
//***************************************************************************

namespace sexp {

// ---------------------------------------------------------
// BegElem, BegAtom
// ---------------------------------------------------------
struct FlagElemInfo_ {
  int flags;
};

inline ostream&
operator<<(std::ostream& os, const FlagElemInfo_ x) // ok to pass x directly
{
  ostream& sos = dynamic_cast<ostream&>(os); // FIXME
  sos.BegList(x.flags);
  return sos;
}

inline FlagElemInfo_ 
BegList(int flags)
{
  FlagElemInfo_ x;
  x.flags = flags;
  return x;
}

inline ostream&
BegList(ostream& sos)
{
  sos.BegList();
  return sos;
}

inline FlagElemInfo_ 
BegAtom(int flags)
{
  FlagElemInfo_ x;
  x.flags = flags;
  return x;
}

inline ostream&
BegAtom(ostream& sos)
{
  sos.BegAtom();
  return sos;
}


// ---------------------------------------------------------
// Atom
// ---------------------------------------------------------

template<class T> 
struct AtomInfo_ {
  int flags;
  const T* val;
};

template<class T> 
ostream& 
operator<<(std::ostream& os, const AtomInfo_<T>& x)
{
  ostream& sos = dynamic_cast<ostream&>(os); // FIXME
  sos.Atom(x.flags, *x.val);
  return sos;
}

template<class T> 
AtomInfo_<T>
Atom(int aflags, const T& val)
{
  AtomInfo_<T> x;
  x.flags = aflags;
  x.val = &val;
  return x;
}

template<class T> 
AtomInfo_<T>
Atom(const T& val)
{
  AtomInfo_<T> x;
  x.flags = IOFlags::NONE;
  x.val = &val;
  return x;
}


// ---------------------------------------------------------
// Comment
// ---------------------------------------------------------
struct CommentInfo_ {
  const char* str;
};

inline ostream&
operator<<(std::ostream& os, const CommentInfo_ x) // ok to pass x directly
{
  ostream& sos = dynamic_cast<ostream&>(os);
  sos.Comment(x.str);
  return sos;
}

inline CommentInfo_ 
Comment(const char* str_)
{
  CommentInfo_ x;
  x.str = str_;
  return x;
}

// ---------------------------------------------------------
// SetIndentAmnt
// ---------------------------------------------------------
struct IndentAmntInfo_ {
  int amnt;
};

inline ostream& 
operator<<(std::ostream& os, const IndentAmntInfo_ x) // ok to pass x directly
{
  ostream& sos = dynamic_cast<ostream&>(os);
  sos.SetIndentAmnt(x.amnt);
  return sos;
}

inline IndentAmntInfo_ 
SetIndentAmnt(int amnt_)
{
  IndentAmntInfo_ x;
  x.amnt = amnt_;
  return x;
}

// ---------------------------------------------------------
// SetIndentStep
// ---------------------------------------------------------
struct IndentStepInfo_ {
  int step;
};

inline ostream& 
operator<<(std::ostream& os, const IndentStepInfo_ x) // ok to pass x directly
{
  ostream& sos = dynamic_cast<ostream&>(os);
  sos.SetIndentStep(x.step);
  return sos;
}

inline IndentStepInfo_ 
SetIndentStep(int step_)
{
  IndentStepInfo_ x;
  x.step = step_;
  return x;
}

}; /* namespace sexp */

//****************************************************************************

#endif /* sexpostream_INLUCDED_h */
