#include "Open64IRInterface/IntrinsicInfo.h"
#include "Open64IRInterface/diagnostics.h"
#include "Open64IRInterface/wn_attr.h"

IntrinsicInfo::IntrinsicMap IntrinsicInfo::ourIntrinsicInfoMap;
bool IntrinsicInfo::ourInitFlag=false;

const IntrinsicInfo::IntrinsicMap& IntrinsicInfo::getMap() { 
  if (!ourInitFlag) { 
    // Common mathematical functions
    ourIntrinsicInfoMap[Key( OPR_NEG,          NULL)      ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_ADD,          NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_SUB,          NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_MPY,          NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_DIV,          NULL)      ]=Info(2); 
    ourIntrinsicInfoMap[Key( OPR_CALL,         "SQRT")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DSQRT")   ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_SQRT,         NULL)      ]=Info(1); 
    // modulo/remainder
    ourIntrinsicInfoMap[Key( OPR_MOD,          NULL)      ]=Info(2); 
    ourIntrinsicInfoMap[Key( OPR_CALL,         "MODULO")  ]=Info(2); 
    ourIntrinsicInfoMap[Key( OPR_REM,          NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP, "AMOD")    ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP, "DMOD")    ]=Info(2); 
    ourIntrinsicInfoMap[Key( OPR_CALL,         "MOD")     ]=Info(2); 
    // trigonometric
    ourIntrinsicInfoMap[Key( OPR_CALL,         "SIN")     ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DSIN")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "COS")     ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DCOS")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "TAN")     ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DTAN")    ]=Info(1); 
    ourIntrinsicInfoMap[Key( OPR_CALL,         "ASIN")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "ACOS")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "ATAN")    ]=Info(1); 
    ourIntrinsicInfoMap[Key( OPR_CALL,         "SINH")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DSINH")   ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "COSH")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DCOSH")   ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "TANH")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DTANH")   ]=Info(1);
    // exp/log
    ourIntrinsicInfoMap[Key( OPR_CALL,         "EXP")     ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DEXP")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "LOG")     ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DLOG")    ]=Info(1); 
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP, "EXPEXPR") ]=Info(2);
    // string ops
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP, "CEQEXPR") ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP, "CNEEXPR") ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP, "CGEEXPR") ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP, "CGTEXPR") ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP, "CLEEXPR") ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP, "CLTEXPR") ]=Info(2);
    // rounding and conversion
    ourIntrinsicInfoMap[Key( OPR_ABS,          NULL)      ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "ABS")     ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DABS")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "IABS")    ]=Info(1); 
    ourIntrinsicInfoMap[Key( OPR_CALL,         "SIGN")    ]=Info(2); 
    ourIntrinsicInfoMap[Key( OPR_RND,          NULL)      ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_TRUNC,        NULL)      ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "INT")     ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "NINT")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CEIL,         NULL)      ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_FLOOR,        NULL)      ]=Info(1); 
    ourIntrinsicInfoMap[Key( OPR_CALL,         "REAL")    ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "FLOAT")   ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "DBLE")    ]=Info(1); 
    // logical (and bitwise logical) operations 
    ourIntrinsicInfoMap[Key( OPR_BNOT,         NULL)      ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_BAND,         NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_BIOR,         NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_BXOR,         NULL)      ]=Info(2); 
    ourIntrinsicInfoMap[Key( OPR_LNOT,         NULL)      ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_LAND,         NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_LIOR,         NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_CAND,         NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_CIOR,         NULL)      ]=Info(2); 
    ourIntrinsicInfoMap[Key( OPR_EQ,           NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_NE,           NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_GT,           NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_GE,           NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_LT,           NULL)      ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_LE,           NULL)      ]=Info(2); 
    // miscellaneous
    ourIntrinsicInfoMap[Key( OPR_CALL,         "LBOUND")  ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "UBOUND")  ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_INTRINSIC_OP, "F90INDEX")]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_CALL,         "LEN")     ]=Info(1);
    ourIntrinsicInfoMap[Key( OPR_SHL,           NULL)     ]=Info(2);
    ourIntrinsicInfoMap[Key( OPR_ASHR,          NULL)     ]=Info(2); 
    // max/min
    ourIntrinsicInfoMap[Key( OPR_MAX,           NULL)     ]=Info(2); 
    ourIntrinsicInfoMap[Key( OPR_MIN,           NULL)     ]=Info(2); 
  } 
  return ourIntrinsicInfoMap;
} 

bool IntrinsicInfo::callIsIntrinsic(WN* aWN_p) { 
  OPERATOR opr = WN_operator(aWN_p);
  ASSERT_FATAL(OPERATOR_is_call(opr),(DIAG_A_STRING,"IntrinsicInfo::isCallIntrinsic: unexpected input"));
  if (opr==OPR_INTRINSIC_CALL) { 
    // get the name and strip machine type information 
    const char* inm = intrinsicBaseName(WN_intrinsic(aWN_p));
    return (getMap().find(Key(opr,inm))==getMap().end()?false:true);
  }
  else if (opr==OPR_CALL) { 
    // get the name
    ST* st = WN_st(aWN_p);
    const char* funcNm = ST_name(st);
    return (getMap().find(Key(opr,funcNm))==getMap().end()? false: true);
  }
  else
    // this could be OPR_PICCALL, OPR_VFCALL, OPR_ICALL
    return false;
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
