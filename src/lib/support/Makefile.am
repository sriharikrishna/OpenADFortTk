# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Makefile.am,v 1.3 2006/05/12 16:12:22 utke Exp $

## * BeginRiceCopyright *****************************************************
## 
## Copyright ((c)) 2002, Rice University 
## All rights reserved.
## 
## Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions are
## met:
## 
## * Redistributions of source code must retain the above copyright
##   notice, this list of conditions and the following disclaimer.
## 
## * Redistributions in binary form must reproduce the above copyright
##   notice, this list of conditions and the following disclaimer in the
##   documentation and/or other materials provided with the distribution.
## 
## * Neither the name of Rice University (RICE) nor the names of its
##   contributors may be used to endorse or promote products derived from
##   this software without specific prior written permission.
## 
## This software is provided by RICE and contributors "as is" and any
## express or implied warranties, including, but not limited to, the
## implied warranties of merchantability and fitness for a particular
## purpose are disclaimed. In no event shall RICE or contributors be
## liable for any direct, indirect, incidental, special, exemplary, or
## consequential damages (including, but not limited to, procurement of
## substitute goods or services; loss of use, data, or profits; or
## business interruption) however caused and on any theory of liability,
## whether in contract, strict liability, or tort (including negligence
## or otherwise) arising in any way out of the use of this software, even
## if advised of the possibility of such damage. 
## 
## ******************************************************* EndRiceCopyright *

#############################################################################
#
# File:
#   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Makefile.am,v $
#
# Description:
#   *Process with automake to produce Makefile.in*
#
#   Note: All local variables are prefixed with MY to prevent name
#   clashes with automatic automake variables.
#
#############################################################################

# We do not want the standard GNU files (NEWS README AUTHORS ChangeLog...)
AUTOMAKE_OPTIONS = foreign

#############################################################################
# Common settings
#############################################################################

include $(top_srcdir)/src/Makeinclude.config

#############################################################################
# Local settings
#############################################################################

MYSOURCES = \
Open64IRInterface/Open64BasicTypes.h \
Open64IRInterface/Open64IRInterface.cpp Open64IRInterface/Open64IRInterface.hpp \
Open64IRInterface/IntrinsicInfo.cpp Open64IRInterface/IntrinsicInfo.h \
Open64IRInterface/SymTab.cpp Open64IRInterface/SymTab.h \
Open64IRInterface/WhirlGlobalStateUtils.cpp Open64IRInterface/WhirlGlobalStateUtils.h \
Open64IRInterface/WhirlIO.cpp Open64IRInterface/WhirlIO.h \
Open64IRInterface/diagnostics.cpp Open64IRInterface/diagnostics.h \
Open64IRInterface/stab_attr.cpp Open64IRInterface/stab_attr.h \
Open64IRInterface/wn_attr.cpp Open64IRInterface/wn_attr.h \
\
BaseMap.h \
CmdLineParser.h CmdLineParser.cxx \
Exception.h Exception.cxx \
Diagnostics.h Diagnostics.cxx  \
IntrinsicXlationTable.h IntrinsicXlationTable.cxx \
OAMaps.h OAMaps.cxx \
quad.h \
ScalarizedRef.h ScalarizedRef.cxx \
ScalarizedRefTab.h ScalarizedRefTab.cxx \
BackSubstituteTemps.h BackSubstituteTemps.cxx \
sexpostream.h sexpostream.cxx \
SexpTags.h SexpTags.cxx \
sexputil.h sexputil.cxx \
Symbol.h Symbol.cxx \
WhirlIDMaps.h WhirlIDMaps.cxx \
WhirlParentize.h WhirlParentize.cxx \
XAIFStrings.h XAIFStrings.cxx \
XAIFSymToSymbolMap.h  XAIFSymToSymbolMap.cxx \
xmlostream.h xmlostream.cxx 

MYCFLAGS   = $(OPENADFORTTK_IFLAGS) \
	@OPEN64_IFLAGS@ @OPEN64_CFLAGS@ \
	@OA_IFLAGS@ @XERCES_IFLAGS@ @OPT_SEXP_IFLAGS@ \
	@HOST_CFLAGS@

MYCXXFLAGS = $(OPENADFORTTK_IFLAGS) \
	@OPEN64_IFLAGS@ @OPEN64_CXXFLAGS@ \
	@OA_IFLAGS@ @XERCES_IFLAGS@ @OPT_SEXP_IFLAGS@ \
	@HOST_CXXFLAGS@

if IS_HOST_AR
  MYAR = @HOST_AR@
else
  MYAR = $(AR) cru
endif

MYLIBADD = @HOST_LIBTREPOSITORY@

MYCLEAN = @HOST_LIBTREPOSITORY@

#############################################################################
# Automake rules
#############################################################################

noinst_LIBRARIES = libsupport.a

libsupport_a_SOURCES  = $(MYSOURCES)
libsupport_a_CFLAGS   = $(MYCFLAGS)
libsupport_a_CXXFLAGS = $(MYCXXFLAGS)
libsupport_a_AR       = $(MYAR)
libsupport_a_LIBADD   = $(MYLIBADD)

MOSTLYCLEANFILES = $(MYCLEAN)

#############################################################################
# Common rules
#############################################################################

include $(top_srcdir)/src/Makeinclude.rules

