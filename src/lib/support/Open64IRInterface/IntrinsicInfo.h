// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/IntrinsicInfo.h,v 1.8 2006/05/12 16:12:22 utke Exp $

#ifndef IntrinsicInfo_H 
#define IntrinsicInfo_H

#include <map>
#include "Open64IRInterface/Open64BasicTypes.h"

class IntrinsicInfo {

public:
  
  /** 
   * for a call operator, is the called procedure an intrinsic?
   */
  static bool callIsIntrinsic(WN* aWN_p); 

  /** 
   * strips machine type information from the name
   */
  static const char* intrinsicBaseName(INTRINSIC opcode);

  /** 
   * the key
   */
  struct Key {
    Key(const OPERATOR& opr, const char* name): myWNopr(opr), myName(name) {};
    OPERATOR myWNopr;   // the WN operator
    const char* myName; // string qualifier for calls
  };

  /** 
   * the less than operator for the key needed for map
   */
  struct KeyLT {
    bool operator()(const Key& k1, const Key& k2) const; 
  };

  /** 
   * additional information
   */
  struct Info {
    Info(): myNumOp(0){};
    Info(unsigned int aNumOp): myNumOp(aNumOp){};
    unsigned int myNumOp; // number of operands to intrinsic
  };

  typedef std::map<Key,Info,KeyLT> IntrinsicMap;

  static const IntrinsicMap& getMap();

private:
  
  /** 
   * no def
   */
  IntrinsicInfo();
  
  /** 
   * no def
   */
  ~IntrinsicInfo();

  static IntrinsicMap ourIntrinsicInfoMap;
  static bool ourInitFlag;

  /** 
   * return  true if 'str' is a valid prefix for an intrinsic name; 
   * false otherwise. These prefixes are the machine types the 
   * front end attaches to the intrinsic names.
   */
  static bool lookupIntrinsicPrefix(const char* str);
  
}; 

#endif

