// -*-Mode: C++;-*-
// $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/whirl2f_common.h,v 1.11 2004/02/17 22:40:34 eraxxon Exp $

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
//   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/whirl2f_common.h,v $
//
// Purpose:
//   [The purpose of this file]
//
// Description:
//   [The set of functions, macros, etc. defined in the file]
//
// Based on Open64 be/whirl2f/whirl2xaif.i
//
//***************************************************************************

#ifndef whirl2xaif_i
#define whirl2xaif_i

//************************** System Include Files ***************************

//************************** Open64 Include Files ***************************

//*************************** User Include Files ****************************

#include <lib/support/stab_attr.h>
#include <lib/support/wn_attr.h>
#include <lib/support/w2cf_symtab.h>

#include <lib/support/WhirlIDMaps.h>
#include <lib/support/xmlostream.h>
#include <lib/support/XAIFStrings.h>
#include <lib/support/diagnostics.h>

//************************** Forward Declarations ***************************

#define whirl2xaif_divider_comment \
  "********************************************************************"

//***************************************************************************

namespace whirl2xaif {
  
  enum status {
    good,
    bad
  };
  
}; /* namespace whirl2xaif */

//***************************************************************************
// Some helpful utility xml::ostream operators
//***************************************************************************

// ---------------------------------------------------------
// AttrSymId
// ---------------------------------------------------------

struct AttrSymTab_ {
  const ST* st;
};

inline ostream&
operator<<(std::ostream& os, const AttrSymTab_& x) 
{
  xml::ostream& xos = dynamic_cast<xml::ostream&>(os); // FIXME

  const char* st_name = ST_name(x.st); // W2CF_Symtab_Nameof_St(st);
  SymId st_id = (SymId)ST_index(x.st);
  
  xos << xml::BegAttr(XAIFStrings.attr_symId())
      << st_name << "_" << st_id
      << xml::EndAttr;

  return xos;
}

// AttrAnnot: Given a tag and a value, generate a complete annotiation
// attribute
inline AttrSymTab_
AttrSymId(ST* st_)
{
  AttrSymTab_ x;
  x.st = st_;
  return x;
}

// ---------------------------------------------------------
// AttrAnnot, AttrAnnotVal
// ---------------------------------------------------------
template<class T> 
struct AttrAnnotInfo_ {
  bool completeAttr;
  const char* tag;
  const T* val;
};

template<class T> 
ostream&
operator<<(std::ostream& os, const AttrAnnotInfo_<T>& x) 
{
  xml::ostream& xos = dynamic_cast<xml::ostream&>(os); // FIXME

  if (x.completeAttr) {
    xos << xml::BegAttr(XAIFStrings.attr_annot());
  }

  xos << x.tag << *x.val << XAIFStrings.tag_End();
  
  if (x.completeAttr) {
    xos << xml::EndAttr;
  }

  return xos;
}

// AttrAnnot: Given a tag and a value, generate a complete annotiation
// attribute
template<class T> 
AttrAnnotInfo_<T> 
AttrAnnot(const char* tag_, const T& val_)
{
  AttrAnnotInfo_<T> x;
  x.completeAttr = true;
  x.tag = tag_;
  x.val = &val_;
  return x;
}

// AttrAnnotVal: Given a tag and a value, generate only the
// annotiation attribute value
template<class T> 
AttrAnnotInfo_<T>
AttrAnnotVal(const char* tag_, const T& val_)
{
  AttrAnnotInfo_<T> x;
  x.completeAttr = false;
  x.val = &val_;
  x.tag = tag_;
  return x;
}

// *AttrAnnot: Given a value, generate a complete annotiation
// attribute with appropriate tag
template<class T> 
AttrAnnotInfo_<T> 
SymTabIdAnnot(const T& val_) 
{
  return AttrAnnot(XAIFStrings.tag_SymTabId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
SymIdAnnot(const T& val_) 
{
  return AttrAnnot(XAIFStrings.tag_SymId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
PUIdAnnot(const T& val_) 
{
  return AttrAnnot(XAIFStrings.tag_PUId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
WhirlIdAnnot(const T& val_) 
{
  return AttrAnnot(XAIFStrings.tag_WHIRLId(), val_);
}

// *AttrAnnotVal: Given a tag and a value, generate only the
// annotiation attribute value with the appropriate tag
template<class T> 
AttrAnnotInfo_<T>
SymTabIdAnnotVal(const T& val_)
{
  return AttrAnnotVal(XAIFStrings.tag_SymTabId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
SymIdAnnotVal(const T& val_)
{
  return AttrAnnotVal(XAIFStrings.tag_SymId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
PUIdAnnotVal(const T& val_)
{
  return AttrAnnotVal(XAIFStrings.tag_PUId(), val_);
}

template<class T> 
AttrAnnotInfo_<T>
WhirlIdAnnotVal(const T& val_)
{
  return AttrAnnotVal(XAIFStrings.tag_WHIRLId(), val_);
}

//***************************************************************************

#endif /* whirl2xaif_i */
