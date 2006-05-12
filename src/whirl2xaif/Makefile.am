# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Makefile.am,v 1.2 2006/05/12 16:12:23 utke Exp $

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
#   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Makefile.am,v $
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
	main.cxx \
	Args.h Args.cxx \
	\
	whirl2xaif.h whirl2xaif.i whirl2xaif.cxx \
	wn2xaif.h wn2xaif.i wn2xaif.cxx \
	wn2xaif_stmt.h wn2xaif_stmt.cxx \
	wn2xaif_expr.h wn2xaif_expr.cxx \
	wn2xaif_mem.h wn2xaif_mem.cxx \
	wn2xaif_io.h wn2xaif_io.cxx \
	st2xaif.h st2xaif.cxx \
	ty2xaif.h ty2xaif.cxx \
	XlationContext.h XlationContext.cxx \
	PUXlationContext.h PUXlationContext.cxx

MYCFLAGS   = $(OPENADFORTTK_IFLAGS) \
	@OPEN64_IFLAGS@ @OPEN64_CFLAGS@ @OA_IFLAGS@ @XERCES_IFLAGS@ \
	@HOST_CFLAGS@

MYCXXFLAGS = $(OPENADFORTTK_IFLAGS) \
	@OPEN64_IFLAGS@ @OPEN64_CXXFLAGS@ @OA_IFLAGS@ @XERCES_IFLAGS@ \
	@HOST_CXXFLAGS@

MYLDADD = \
	@HOST_LIBTREPOSITORY@ \
	$(OPENADFORTTK_LIBSUPPORT) \
	@OPEN64_LDFLAGS@ @OA_LDFLAGS@ @XERCES_LDFLAGS@ \
	-lm

# @HOST_WHIRLXAIF_LDFLAGS@

MYCLEAN = @HOST_LIBTREPOSITORY@

#############################################################################
# Automake rules
#############################################################################

bin_PROGRAMS = whirl2xaif

whirl2xaif_SOURCES  = $(MYSOURCES)
whirl2xaif_CFLAGS   = $(MYCFLAGS)
whirl2xaif_CXXFLAGS = $(MYCXXFLAGS)
whirl2xaif_LDFLAGS  = $(MYLDFLAGS)
whirl2xaif_LDADD    = $(MYLDADD)

MOSTLYCLEANFILES = $(MYCLEAN)

#############################################################################
# Common rules
#############################################################################

include $(top_srcdir)/src/Makeinclude.rules

