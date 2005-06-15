# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/Makefile.am,v 1.1 2005/06/10 17:44:32 eraxxon Exp $

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
#   $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/Makefile.am,v $
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
	sexp2whirl.h sexp2whirl.i sexp2whirl.cxx \
	sexp2wn.h sexp2wn.i sexp2wn.cxx \
	sexp2symtab.h sexp2symtab.cxx

MYCFLAGS   = $(OPENADFORTTK_IFLAGS) \
	@OPEN64_IFLAGS@ @OPEN64_CFLAGS@ @OA_IFLAGS@ @OPT_SEXP_IFLAGS@ \
	@HOST_CFLAGS@

MYCXXFLAGS = $(OPENADFORTTK_IFLAGS) \
	@OPEN64_IFLAGS@ @OPEN64_CXXFLAGS@ @OA_IFLAGS@ @OPT_SEXP_IFLAGS@ \
	@HOST_CXXFLAGS@

MYLDADD = \
	@HOST_LIBTREPOSITORY@ \
	$(OPENADFORTTK_LIBSUPPORT) \
	@OPEN64_LDFLAGS@ @OA_LDFLAGS@ @OPT_SEXP_LDFLAGS@ \
	-lm

# @HOST_WHIRLSEXP_LDFLAGS@

MYCLEAN = @HOST_LIBTREPOSITORY@

#############################################################################
# Automake rules
#############################################################################

bin_PROGRAMS = sexp2whirl

sexp2whirl_SOURCES  = $(MYSOURCES)
sexp2whirl_CFLAGS   = $(MYCFLAGS)
sexp2whirl_CXXFLAGS = $(MYCXXFLAGS)
sexp2whirl_LDFLAGS  = $(MYLDFLAGS)
sexp2whirl_LDADD    = $(MYLDADD)

MOSTLYCLEANFILES = $(MYCLEAN)

#############################################################################
# Common rules
#############################################################################

include $(top_srcdir)/src/Makeinclude.rules
