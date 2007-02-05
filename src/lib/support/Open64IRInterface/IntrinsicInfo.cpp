#include "IntrinsicInfo.h"
#include "diagnostics.h"
#include "wn_attr.h"

IntrinsicInfo::IntrinsicMap IntrinsicInfo::ourIntrinsicInfoMap;
bool IntrinsicInfo::ourInitFlag=false;

const IntrinsicInfo::IntrinsicMap& IntrinsicInfo::getMap() { 
  if (!ourInitFlag) { 
    // Common mathematical functions
    ourIntrinsicInfoMap[Key( OPR_NEG,           NULL)         ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_ADD,           NULL)         ]=Info(2,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_SUB,           NULL)         ]=Info(2,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_MPY,           NULL)         ]=Info(2,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_DIV,           NULL)         ]=Info(2,FLOAT_INTR); 
    ourIntrinsicInfoMap[Key( OPR_CALL,          "SQRT")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DSQRT")      ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_SQRT,          NULL)         ]=Info(1,FLOAT_INTR); 
    // modulo/remainder
    ourIntrinsicInfoMap[Key( OPR_MOD,           NULL)         ]=Info(2,FLOAT_INTR); 
    ourIntrinsicInfoMap[Key( OPR_CALL,          "MODULO")     ]=Info(2,FLOAT_INTR); 
    ourIntrinsicInfoMap[Key( OPR_REM,           NULL)         ]=Info(2,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP,  "AMOD")       ]=Info(2,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP,  "DMOD")       ]=Info(2,FLOAT_INTR); 
    ourIntrinsicInfoMap[Key( OPR_CALL,          "MOD")        ]=Info(2,FLOAT_INTR); 
    // trigonometric
    ourIntrinsicInfoMap[Key( OPR_CALL,          "SIN")        ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DSIN")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "COS")        ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DCOS")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "TAN")        ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DTAN")       ]=Info(1,FLOAT_INTR); 
    ourIntrinsicInfoMap[Key( OPR_CALL,          "ASIN")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "ACOS")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "ATAN")       ]=Info(1,FLOAT_INTR); 
    ourIntrinsicInfoMap[Key( OPR_CALL,          "SINH")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DSINH")      ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "COSH")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DCOSH")      ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "TANH")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DTANH")      ]=Info(1,FLOAT_INTR);
    // exp/log
    ourIntrinsicInfoMap[Key( OPR_CALL,          "EXP")        ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DEXP")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "LOG")        ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DLOG")       ]=Info(1,FLOAT_INTR); 
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP,  "EXPEXPR")    ]=Info(2,FLOAT_INTR);
    // string ops
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP,  "CEQEXPR")    ]=Info(2,STRING_INTR);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP,  "CNEEXPR")    ]=Info(2,STRING_INTR);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP,  "CGEEXPR")    ]=Info(2,STRING_INTR);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP,  "CGTEXPR")    ]=Info(2,STRING_INTR);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP,  "CLEEXPR")    ]=Info(2,STRING_INTR);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP,  "CLTEXPR")    ]=Info(2,STRING_INTR);
    // string assignment
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_CALL,"CASSIGNSTMT")]=Info(1,STRING_INTR);
    // string length
    ourIntrinsicInfoMap[Key( OPR_CALL,          "LEN")        ]=Info(1,STRING_INTR);
    // rounding and conversion
    ourIntrinsicInfoMap[Key( OPR_ABS,           NULL)         ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "ABS")        ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DABS")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "IABS")       ]=Info(1,INTEGER_INTR); 
    ourIntrinsicInfoMap[Key( OPR_CALL,          "SIGN")       ]=Info(2,FLOAT_INTR); 
    ourIntrinsicInfoMap[Key( OPR_RND,           NULL)         ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_TRUNC,         NULL)         ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "INT")        ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "NINT")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CEIL,          NULL)         ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_FLOOR,         NULL)         ]=Info(1,FLOAT_INTR); 
    ourIntrinsicInfoMap[Key( OPR_CALL,          "REAL")       ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "FLOAT")      ]=Info(1,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "DBLE")       ]=Info(1,FLOAT_INTR); 
    // logical (and bitwise logical) operations 
    ourIntrinsicInfoMap[Key( OPR_BNOT,          NULL)         ]=Info(1,BOOL_INTR);
    ourIntrinsicInfoMap[Key( OPR_BAND,          NULL)         ]=Info(2,BOOL_INTR);
    ourIntrinsicInfoMap[Key( OPR_BIOR,          NULL)         ]=Info(2,BOOL_INTR);
    ourIntrinsicInfoMap[Key( OPR_BXOR,          NULL)         ]=Info(2,BOOL_INTR); 
    ourIntrinsicInfoMap[Key( OPR_LNOT,          NULL)         ]=Info(1,BOOL_INTR);
    ourIntrinsicInfoMap[Key( OPR_LAND,          NULL)         ]=Info(2,BOOL_INTR);
    ourIntrinsicInfoMap[Key( OPR_LIOR,          NULL)         ]=Info(2,BOOL_INTR);
    ourIntrinsicInfoMap[Key( OPR_CAND,          NULL)         ]=Info(2,BOOL_INTR);
    ourIntrinsicInfoMap[Key( OPR_CIOR,          NULL)         ]=Info(2,BOOL_INTR); 
    // comparison operations
    ourIntrinsicInfoMap[Key( OPR_EQ,            NULL)         ]=Info(2,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_NE,            NULL)         ]=Info(2,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_GT,            NULL)         ]=Info(2,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_GE,            NULL)         ]=Info(2,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_LT,            NULL)         ]=Info(2,FLOAT_INTR);
    ourIntrinsicInfoMap[Key( OPR_LE,            NULL)         ]=Info(2,FLOAT_INTR); 
    // max/min
    ourIntrinsicInfoMap[Key( OPR_MAX,            NULL)        ]=Info(2,FLOAT_INTR); 
    ourIntrinsicInfoMap[Key( OPR_MIN,            NULL)        ]=Info(2,FLOAT_INTR); 
    // array operations
    ourIntrinsicInfoMap[Key( OPR_CALL,          "LBOUND")     ]=Info(2,ARRAY_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "UBOUND")     ]=Info(2,ARRAY_INTR);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP,  "F90INDEX")   ]=Info(2,ARRAY_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "MAXVAL")     ]=Info(2,ARRAY_INTR);
    ourIntrinsicInfoMap[Key( OPR_CALL,          "MINVAL")     ]=Info(2,ARRAY_INTR);
    // shifting operations
    ourIntrinsicInfoMap[Key( OPR_SHL,            NULL)        ]=Info(2,INTEGER_INTR);
    ourIntrinsicInfoMap[Key( OPR_ASHR,           NULL)        ]=Info(2,INTEGER_INTR); 
    // compiler internal routine for cleanup at the end of PROGRAM
    ourIntrinsicInfoMap[Key( OPR_CALL,          "_END")       ]=Info(0,COMPILER_INTERNAL_INTR);
  } 
  return ourIntrinsicInfoMap;
} 

bool IntrinsicInfo::lookupIntrinsicInfo(WN* aWN_p, const IntrinsicInfo::Info* anInfo) { 
  OPERATOR opr = WN_operator(aWN_p);
  IntrinsicMap::const_iterator finder;
  if (opr==OPR_INTRINSIC_CALL) { 
    // get the name and strip machine type information 
    const char* inm = intrinsicBaseName(WN_intrinsic(aWN_p));
    finder=getMap().find(Key(opr,inm));
    if (finder==getMap().end()) { 
      DIE("IntrinsicInfo::isIntrinsic: no entry for OPR_INTRINSIC_CALL %s ",inm);
    }
  }
  else if (opr==OPR_INTRINSIC_OP) { 
    // get the name and strip machine type information
    const char* inm = intrinsicBaseName(WN_intrinsic(aWN_p));
    finder=getMap().find(Key(opr,inm));
    if (finder==getMap().end()) {
      DIE("IntrinsicInfo::isIntrinsic: no entry for OPR_INTRINSIC_OP %s ",inm);
    }
  }
  else if (opr==OPR_CALL) { 
    // get the name
    ST* st = WN_st(aWN_p);
    const char* funcNm = ST_name(st);
    // if we don't find it in the table we either forgot to add an entry
    // or the call is not to an intrinsic
    finder=getMap().find(Key(opr,funcNm));
  }
  else { 
    // the rest is for the OPERATORs without discriminating name which we 
    // hopefully have complete
    finder=getMap().find(Key(opr,NULL));
  }
  if (finder!=getMap().end())
    anInfo=&((*finder).second);
  return finder!=getMap().end();
} 

bool IntrinsicInfo::isIntrinsic(WN* aWN_p) { 
  const Info* anInfo_p;
  return lookupIntrinsicInfo(aWN_p,anInfo_p);
}

const IntrinsicInfo::Info& IntrinsicInfo::getIntrinsicInfo(WN* aWN_p) { 
  const Info* anInfo_p;
  if(!lookupIntrinsicInfo(aWN_p,anInfo_p))
    DIE("IntrinsicInfo::getIntrinsicInfo: not a known intrinsic");
  return *anInfo_p;
}

bool IntrinsicInfo::KeyLT::operator()(const IntrinsicInfo::Key& k1, const IntrinsicInfo::Key& k2) const {
  if (k1.myWNopr<k2.myWNopr)
    return true;
  else if (k1.myWNopr>k2.myWNopr)
    return false;
  else if (k1.myWNopr==OPR_CALL)
    return strcmp(k1.myName, k2.myName) < 0;
  else
    return false;
}

const char* IntrinsicInfo::intrinsicBaseName(INTRINSIC intrn) {
  // almost none of the Open64 code uses std::string
  const char* opc_str = WN_intrinsic_name(intrn); // INTRINSIC_name(intrn);
  const char* opc_str_base = opc_str;
  const int prefixLength(2);
  // Test for two-character prefixes (up to two)
  char buf[prefixLength+1];
  for (int i = 0; i < 2; ++i) {
    // If a prefix begins 'opc_str_base', shift pointer
    strncpy(buf, opc_str_base, prefixLength); 
    buf[prefixLength] = '\0';
    bool pfix = lookupIntrinsicPrefix(buf);
    if (pfix) { 
      opc_str_base += prefixLength; 
    } else {
      break; // no need to continue
    }
  }
  // Special case: test for one-character prefix
  strncpy(buf, opc_str_base, 1); 
  buf[1] = '\0';
  bool pfix = lookupIntrinsicPrefix(buf);
  if (pfix) {
    // an exception
    if ( !(strcmp(opc_str_base, "VALTMP") == 0) ) {
      opc_str_base++;
    }
  }
  return opc_str_base;
}

extern "C" int prefixTableCmp(const char** e1, const char** e2) {
  return strcmp(*e1, *e2);
}

extern "C" typedef int (*compare_fn_t)(const void *, const void *);

bool IntrinsicInfo::lookupIntrinsicPrefix(const char* str){ 
  static const char* prefixTable[] = {
    "V",                    // void
    "I1", "I2", "I4", "I8", // integer
    "U1", "U2", "U4", "U8", // unsigned integer
    "F4", "F8", "FQ",       // floating point
    "C4", "C8", "CQ"        // complex
    // "C_" - C intrinsics
    // "S_" - UPC intrinsics
  }; 
  static unsigned int prefixTableElemSz = sizeof(const char*);
  static unsigned int prefixTableSz = (sizeof(prefixTable) / sizeof(const char*));
  static bool prefixTableSorted = false;
  // first sort it 
  if (!prefixTableSorted) {
    qsort(prefixTable, 
	  prefixTableSz, 
	  prefixTableElemSz, 
	  (compare_fn_t)prefixTableCmp);
    prefixTableSorted = true;
  }
  // Search for entry str
  void* e = bsearch(&str, 
		    prefixTable, 
		    prefixTableSz, 
		    prefixTableElemSz,
		    (compare_fn_t)prefixTableCmp);
  return (e != NULL);
}
