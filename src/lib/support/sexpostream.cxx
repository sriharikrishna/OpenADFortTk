// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/sexpostream.cxx,v 1.2 2004/08/06 17:29:33 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/sexpostream.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

//*************************** User Include Files ****************************

#include "sexpostream.h"

//*************************** Forward Declarations ***************************

//****************************************************************************

/*
  A table showing possible state movements.  The state-state table
  indicates whether it is possible to move from one state (in the left
  margin) to another state.  Given an initial state (in the left
  margin), the state-action table indicates the possible resulting
  states after an action

        States                         Actions
       |--------------------------------------------------------------------
       |          ..LIST_..     | Beg  Beg  End   End  Beg  End
       |INIT FINI OP_I OPEN ERR | Lst  Atom Atom  Lst  Com  Com
       |-------------------------------------------------------------------- 
  INIT |no   no   yes  yes  yes | OPEN ERR  ERR   ERR  CO?  ER?
  FINI |no   no   yes  yes  yes | OPEN ERR  ERR   ERR  CO?  ER?
  ERR  |no   no   no   no   no  | .    .    .     .    .    .  
  OP_I |no   no   err  yes  yes | ERR  ERR  OPEN  ERR  CO?  ER?
  OPEN |no   yes  yes  yes  yes | OPEN OP_I ERR   FINI CO?  ER?
       |                        |                 OPEN
  COM  |                        | ERR  ERR  ERR   ERR  ER?  <>

 */

// For a comments to public member functions, see the interface file.

sexp::ostream::ostream(std::streambuf* sb)
  : std::ostream(sb)
{
  curAtomFlags = IOFlags::NONE;
  state = 0;

  SetState(INIT);
  indentAmnt = 0;
  indentStep = 2;
}

sexp::ostream::~ostream()
{
}

void
sexp::ostream::BegList(int flags)
  throw (sexp::ostream::Exception)
{
  using namespace IOFlags;

  // Sanity check 
  if (IsState(LIST_OPENI)) {
    SetStateError();
    throw Exception("BegList: Within an atom!");
  }
  
  if (slistStack.size() != 0) {
    int& f = slistStack.front();
    AddSpaceIfNecessary(f);
    SetFlag(f, L_NONEMPTY);
  }

  // FIXME: check flags
  
  (*this) << '(';
  IndentIncr();
  
  slistStack.push_front(flags);
  SetState(LIST_OPEN);
  SetAction(BEG_LIST);
}

void
sexp::ostream::EndList()
{
  using namespace IOFlags;
    
  // Sanity check
  if (!IsState(LIST_OPEN)) {
    SetStateError();
    throw Exception("EndList: Cannot end list!");
  } 

  int& flags = slistStack.front();
  
  IndentDecr();
  (*this) << ")";
  
  // Check flags...
  
  // Determine the appropriate state after an element has been closed
  slistStack.pop_front();
  if (slistStack.size() == 0) { 
    SetState(FINI);
  } 
  else {
    SetState(LIST_OPEN);
  }
  SetAction(END_LIST);
}

// Atom: specialization for 'const char*'
template <>
void 
sexp::ostream::Atom(int aflags, const char* const & val)
{
  // Sanity check -- rely on BegAtom()
  BegAtom(aflags);
  (*this) << ((val) ? val : "");
  EndAtom();
}

void
sexp::ostream::BegAtom(int aflags)
{
  using namespace IOFlags;
  
  // Sanity check
  if (!IsState(LIST_OPEN)) {
    SetStateError();
    throw Exception("BegAtom: No currently open list!");
  }

  int& flags = slistStack.front();

  AddSpaceIfNecessary(flags);
  SetFlag(flags, L_NONEMPTY);
  
  // Check flags (note that there can be two sets of atom flags)
  if (IsFlag(aflags, A_SQUOTE) || IsFlag(flags, A_SQUOTE)) {
    (*this) << "'";
  }
  if (IsFlag(aflags, A_DQUOTE) || IsFlag(flags, A_DQUOTE)) {
    (*this) << '"';
  }
  if (IsFlag(aflags, A_OCT) || IsFlag(flags, A_OCT)) {
    (*this) << std::oct << "0";
  }
  if (IsFlag(aflags, A_HEX) || IsFlag(flags, A_HEX)) {
    (*this) << std::hex << "0x";
  }
  
  curAtomFlags = aflags;
  SetState(LIST_OPENI);
  SetAction(BEG_ATOM);
}

void
sexp::ostream::EndAtom()
{
  using namespace IOFlags;

  // Sanity check
  if (!IsState(LIST_OPENI)) {
    SetStateError();
    throw Exception("EndAtom: No currently open atom!");
  }
  
  // Check flags (note that there can be two sets of atom flags)
  int& flags = slistStack.front();
  if (IsFlag(curAtomFlags, A_DQUOTE) || IsFlag(flags, A_DQUOTE)) {
    (*this) << '"';
  }
  if (IsFlag(curAtomFlags, A_OCT) || IsFlag(flags, A_OCT) ||
      IsFlag(curAtomFlags, A_HEX) || IsFlag(flags, A_HEX)) {
    (*this) << std::dec;
  }
  
  curAtomFlags = IOFlags::NONE;
  SetState(LIST_OPEN);
  SetAction(END_ATOM);
}


//****************************************************************************

void
sexp::ostream::BegComment()
{
  // Sanity check
  if (IsStateComment()) {
    SetStateError();
    throw Exception("BegComment: Already within a comment!");    
  }
  
  (*this) << ";; ";

  SetStateComment();
  SetAction(BEG_COMMENT);
}

void
sexp::ostream::EndComment()
{
  // Sanity check
  if (!IsStateComment()) {
    SetStateError();
    throw Exception("EndComment: Not within a comment!");
  }
  
  SetAction(END_COMMENT); // N.B.: this should come before EndLine()
  EndLine();
  ResetStateComment();
}

void
sexp::ostream::Comment(const char* str)
{
  // Sanity check -- rely on BegComment()
  
  BegComment();
  (*this) << str;
  EndComment();
}

//****************************************************************************

void
sexp::ostream::EndLine()
{
  (*this) << "\n";
  SetAction(END_LINE); // N.B.: this should come before Indent()
  Indent();
}

void
sexp::ostream::Indent()
{
  for (int i = 0; i < indentAmnt; ++i) {
    (*this) << ' ';
  }
  SetAction(INDENT);
}

//****************************************************************************

void
sexp::ostream::AddSpaceIfNecessary(int flags)
{
  using namespace IOFlags;
  
  // short-circuit if we just ended a line or indented
  if (WasAction(END_LINE) || WasAction(INDENT)) {
    return;
  }
  
  if (IsFlag(flags, L_NONEMPTY)) {
    (*this) << ' ';
  }
}
