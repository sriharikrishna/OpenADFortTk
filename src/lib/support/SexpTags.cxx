// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SexpTags.cxx,v 1.5 2005/02/01 22:02:28 eraxxon Exp $

// * BeginCopyright *********************************************************
// *********************************************************** EndCopyright *

//***************************************************************************
//
// File:
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/SexpTags.cxx,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
//***************************************************************************

//************************* System Include Files ****************************

#include <string>

//*************************** User Include Files ****************************

#include "SexpTags.h"

//*************************** Forward Declarations ***************************

//****************************************************************************

namespace SexpTags {

  const char* WHIRL       = "whirl";
  const char* PU_FOREST   = "pu_forest";
  const char* PU_TREE     = "pu_tree";
  const char* PU          = "pu";
  
  const char* GBL_SYMTAB  = "gbl_symtab";
  const char* PU_SYMTAB   = "pu_symtab";
  
  const char* FILE_INFO   = "file_info";
  const char* ST_TAB      = "st_tab";
  const char* TY_TAB      = "ty_tab";
  const char* PU_TAB      = "pu_tab";
  const char* FLD_TAB     = "fld_tab";
  const char* ARB_TAB     = "arb_tab";
  const char* TYLIST_TAB  = "tylist_tab";
  const char* TCON_TAB    = "tcon_tab";
  const char* TCON_STR_TAB = "tcon_str_tab";
  const char* INITO_TAB   = "inito_tab";
  const char* INITV_TAB   = "initv_tab";
  const char* BLK_TAB     = "blk_tab";
  const char* ST_ATTR_TAB = "st_attr_tab";
  const char* STR_TAB     = "str_tab";
  const char* PREG_TAB    = "preg_tab";
  const char* LABEL_TAB   = "label_tab";
  
  const char* ST          = "st";
  const char* TY          = "ty";
  const char* FLG         = "flg";
  const char* OFLG        = "oflg";
  
};

//****************************************************************************


static const char* BLANK_LINE =
";;\n";

static const char* GRAMMAR_SUMMARY =
";; *** Summary ***\n"
";; WHIRL      ::= (whirl GBL_SYMTAB PU_FOREST)\n"
";; GBL_SYMTAB ::= (gbl_symtab GBL_TAB1..GBL_TABn)        ; n is fixed\n"
";; PU_FOREST  ::= (pu_forest PU_TREE*)                   ; list of PU_TREEs\n"
";; PU_TREE    ::= (pu_tree PU PU_TREE*) | NULL\n"
";; PU         ::= (pu PU_SYM PU_SYMTAB WN_AST)\n"
";; PU_SYMTAB  ::= (pu_symtab PU_TAB1..PU_TABm)           ; m is fixed\n"
";; WN_AST     ::= (WN_OPR WN_ATTRS WN_AST*) | NULL\n";

static const char* GRAMMAR_SYMTAB_DETAILS =
";; *** Symbol Table Details ***\n"
";; GBL_SYMTAB ::= (gbl_symtab\n"
";;                   FILE_INFO       ; file information\n"
";;                   ST_TAB          ; symbol table (global)\n"
";;                     ST_ATTR_TAB   ;   misc. attributes for ST_TAB\n"
";;                   PU_TAB          ; program-unit table\n"
";;                   TY_TAB          ; type table\n"
";;                     FLD_TAB       ;   field table (structured types)\n"
";;                     ARB_TAB       ;   array-bound table\n"
";;                     TYLIST_TAB    ;   function prototypes\n"
";;                   TCON_TAB        ; constant table\n"
";;                     TCON_STR_TAB  ;   string constant table\n"
";;                   INITO_TAB       ; initial values for init'd objects\n"
";;                     INITV_TAB     ;   values for scalar components\n"
";;                   BLK_TAB         ; layout info for block of data \n"
";;                   STR_TAB         ; string table\n"
";;                   )\n"
";; PU_SYMTAB  ::= (pu_symtab\n"
";;                   ST_TAB          ; symbol table (local)\n"
";;                     ST_ATTR_TAB   ;   misc. attributes for ST_TAB\n"
";;                   LABEL_TAB       ; label table\n"
";;                   PREG_TAB        ; psuedo-register table\n"
";;                   INITO_TAB       ; initial values for init'd objects\n"
";;                   )\n"
";;\n"
";; FILE_INFO   ::= (file_info ...)\n"
";;\n"
";; ST_TAB      ::= (st_tab ST_TAB_NTRY*)\n"
";; ST_TAB_NTRY ::= (IDX SYM_CLASS STORAGE_CLASS EXPORT_CLASS\n"
";;                  NAME_IDX/TCON TYPE/PU/BLK BASE_IDX OFFSET\n"
";;                  FLAGS FLAGS_EXT ST_IDX)\n"
";;\n"
";; ST_ATTR_TAB ::= (st_attr_tab ST_ATTR_TAB_NTRY*)\n"
";; ST_ATTR_TAB_NTRY ::= (IDX ST_IDX KIND REG_ID/SECTION_NAME)\n"
";;\n"
";; PU_TAB      ::= (pu_tab PU_TAB_NTRY*)\n"
";; PU_TAB_NTRY ::= (IDX PROTOTYPE LEXICAL_LEVEL GP_GROUP SRC_LANG\n"
";;                  TARGET_IDX FLAGS)\n"
";;\n"
";; TY_TAB      ::= (ty_tab TY_TAB_NTRY*)\n"
";; TY_TAB_NTRY ::= (IDX KIND NAME_IDX MTYPE SIZE FLAGS\n"
";;                  ARB/FLD/TYLIST ETYPE/POINTED/PU_FLAGS)\n"
";;\n"
";; FLD_TAB     ::= (fld_tab ...)\n"
";; ARB_TAB     ::= (arb_tab ...)\n"
";; TYLIST_TAB  ::= (tylist_tab ...)\n"
";; TCON_TAB    ::= (tcon_tab ...)\n"
";; TCON_STR_TAB ::= (tcon_str_tab ...)\n"
";; INITO_TAB   ::= (inito_tab ...)\n"
";; INITV_TAB   ::= (initv_tab ...)\n"
";; BLK_TAB     ::= (blk_tab ...)\n"
";; STR_TAB     ::= (str_tab ...)\n"
";; PREG_TAB    ::= (preg_tab ...)\n"
";; LABEL_TAB   ::= (label_tab ...)\n"
";;\n"
";; ST  ::= (st HSTR SCOPE_IDX IDX)\n"
";; TY  ::= (ty HSTR IDX)\n"
";;\n"
";; HSTR (helper string) is a (possibly empty) quoted string.\n";

// Other notes:
// - indices aways begin with 1 (never 0)


static const char* GRAMMAR_AST_DETAILS =
";; *** AST Details ***\n"
";; WN_OPR     ::= OPERATOR RTYPE DTYPE\n"
";; WN_ATTRS   ::= ((ATTR1 ...) (ATTR2 ...) (ATTR3 ...) ...)\n";


const char* 
SexpTags::get_grammar_summary()
{
  return GRAMMAR_SUMMARY;
}


const char* 
SexpTags::get_grammar()
{
  static std::string str;
  if (str.size() == 0) {
    str += GRAMMAR_SUMMARY;
    str += BLANK_LINE;
    str += GRAMMAR_SYMTAB_DETAILS;
    str += BLANK_LINE;
    str += GRAMMAR_AST_DETAILS;
  }
  
  return str.c_str();
}
