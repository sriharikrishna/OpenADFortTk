// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.h,v 1.6 2003/09/02 15:02:20 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SymTab.h,v $
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

#include <include/Open64BasicTypes.h>

//*************************** User Include Files ****************************

//************************** Forward Declarations ***************************

//***************************************************************************
// XAIFSymToWhirlSymMap (FIXME)
//***************************************************************************

class XAIFSymToWhirlSymMap 
{
public:
  // Constructor allocates an empty data structure
  XAIFSymToWhirlSymMap();
  virtual ~XAIFSymToWhirlSymMap();
  
  // Find: Returns NULL if not found
  ST* Find(const char* scopeid, const char* symid) const;
  
  // Insert: insert <'scopeid'+'symid', ST*> pair in the map and
  // return true; if the key already exists, the operation fails and
  // returns false.
  bool Insert(const char* scopeid, const char* symid, const ST* st);
  
  // Return number of entries
  unsigned int GetSize() const { return strToSTMap.size(); }

  static std::string MakeKey(const char* scopeid, const char* symid);
  
private:
  typedef std::map<std::string, ST*>    StringToSTMap;
  typedef StringToSTMap::iterator       StringToSTMapIt;
  typedef StringToSTMap::const_iterator StringToSTMapItC;
  typedef StringToSTMap::value_type     StringToSTMapVal;

private:
  StringToSTMap strToSTMap;
};


//***************************************************************************
// NonScalarSym
//***************************************************************************

class NonScalarSym {
public:
  NonScalarSym();
  virtual ~NonScalarSym();

  // Return a globally unique dummy symbol name
  std::string& GetName() { return name; }

  // Return an id, globally unique across instances of this class
  UINT GetId() const { return id; }

  virtual void Dump(std::ostream& o = std::cerr) const;
  virtual void DDump() const;

private:
  // These could make sense, but I just haven't implemented them yet
  NonScalarSym(const NonScalarSym& x) { }
  NonScalarSym& operator=(const NonScalarSym& x) { return *this; }

private:
  std::string name; // FIXME:
  UINT id; 
  
  static UINT nextId; // for globally uniqe id numbers
};


//***************************************************************************
// NonScalarSymTab
//***************************************************************************

// 'NonScalarSymTab' is a special symbol table for non scalar WHIRL
// references (e.g. array and record accesses).
class NonScalarSymTab {
public:
  // Constructor allocates an empty data structure
  NonScalarSymTab();
  virtual ~NonScalarSymTab();
  
  // Find: find 
  NonScalarSym* Find(const WN* wn) const;
  
  // Insert: insert <'wn','sym'> pair in the map and return true; if
  // 'wn' already exists, the operation fails and returns false.
  bool Insert(const WN* wn, const NonScalarSym* sym);
  
  // Return number of entries
  unsigned int GetSize() const { return wnToSymMap.size(); }

  // Return a globally unique name
  std::string& GetName() { return name; }

  // Return an id, globally unique across instances of this class
  UINT GetId() const { return id; }
  
  // Dump contents for inspection
  virtual void Dump(std::ostream& o = std::cerr, const char* pre = "") const;
  virtual void DDump() const;
  
  friend class NonScalarSymTabIterator;
  
protected:
  // Should not be used
  NonScalarSymTab(const NonScalarSymTab& x) { }
  NonScalarSymTab& operator=(const NonScalarSymTab& x) { return *this; }

private: 
  // A map of WN* to NonScalarSym*.
  typedef std::map<WN*, NonScalarSym*> WNToSymMap;
  typedef WNToSymMap::iterator         WNToSymMapIt;
  typedef WNToSymMap::const_iterator   WNToSymMapItC;
  typedef WNToSymMap::value_type       WNToSymMapVal;

private: 
  WNToSymMap wnToSymMap; // owns all NonScalarSym*

  std::string name; // FIXME: 
  UINT id;

  static UINT nextId; // for globally uniqe id numbers
};

//***************************************************************************
// NonScalarSymTabIterator
//***************************************************************************

// 'NonScalarSymTabIterator': iterator for symbols in a 'NonScalarSymTab'
class NonScalarSymTabIterator {
public:   
  NonScalarSymTabIterator(const NonScalarSymTab& x);
  ~NonScalarSymTabIterator();

  // Returns the current WN* or NULL
  WN* CurrentSrc() const {
    if (it != symtab.wnToSymMap.end()) { return (*it).first; }
    else { return NULL; }
  }

  // Returns the current NonScalarSym*
  NonScalarSym* CurrentTarg() const {
    if (it != symtab.wnToSymMap.end()) { return (*it).second; }
    else { return NULL; }
  }
  
  void operator++()    { ++it; } // prefix increment
  void operator++(int) { it++; } // postfix increment

  bool IsValid() const { return it != symtab.wnToSymMap.end(); } 
  bool IsEmpty() const { return it == symtab.wnToSymMap.end(); }

  // Reset and prepare for iteration again
  void Reset() { it = symtab.wnToSymMap.begin(); }

private:
  // Should not be used
  NonScalarSymTabIterator();
  NonScalarSymTabIterator(const NonScalarSymTabIterator& x);
  NonScalarSymTabIterator& operator=(const NonScalarSymTabIterator& x)
    { return *this; }

protected:
private:
  const NonScalarSymTab& symtab;
  NonScalarSymTab::WNToSymMapItC it;
};

//***************************************************************************

#endif 
