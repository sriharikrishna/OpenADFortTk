# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/tools/multiprocess/Makefile.am,v 1.3 2005/08/29 18:34:07 utke Exp $

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
#   $Source: /Volumes/cvsrep/developer/OpenADFortTk/tools/multiprocess/Makefile.am,v $
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
# Local settings
#############################################################################

MYSCRIPTS = \
	pre.pl \
	multi-pp.pl \
	canon.pl \
	pp.pl

# deprecated: 
#   prh.pl - perl read hack
#   urh.pl - perl unread hack

MYSCRIPTLIB = \
	Lib/ADinline.pm \
	Lib/ADxaif.pm \
	Lib/PPsetup.pm \
	Lib/ADtemplate.pm \
	Lib/InsertAftImplNone.pm \
	Lib/Readhack.pm \
	Lib/Unreadhack.pm \
	Lib/Active_Chg.pm \
	Lib/MultiTemplate.pm \
	Lib/Canonicalizer.pm \
	Lib/Intrinsic.pm \
	\
	Lib/FT/FTList.pm \
	Lib/FT/FTTerm.pm \
	Lib/FT/FTUnit.pm \
	Lib/FT/FTpat.pm \
	Lib/FT/FTscan.pm \
	Lib/FT/Ffile.pm \
	Lib/FT/FortranSourceLine.pm \
	Lib/FT/add_last_decl.pm \
	Lib/FT/FTparse.pm \
	Lib/FT/FTscanTerm.pm \
	Lib/FT/FTscanUtils.pm \
	Lib/FT/FTtest.pm \
	Lib/FT/FTunparse.pm \
	Lib/FT/retain_case.pm \
	Lib/FT/Symtab.pm \
	Lib/FT/FTcontext.pm \
	Lib/FT/FSrcLine.pm \
	Lib/FT/ADtypes.pm \
	Lib/FT/FTproc.pm \
	Lib/FT/FTdecl.pm \
	Lib/FT/FTtypes.pm

#Lib/Test/Builder.pm
#Lib/Test/Class.pm
#Lib/Test/Cmd.pm
#Lib/Test/Differences.pm
#Lib/Test/Exception.pm
#Lib/Test/Harness.pm
#Lib/Test/More.pm
#Lib/Test/Pod.pm
#Lib/Test/Simple.pm
#Lib/Test/Tutorial.pod
#Lib/Test/Builder/Tester.pm
#Lib/Test/Builder/Tester/Color.pm
#Lib/Test/Builder/Tester
#Lib/Test/Cmd/Common.pm
#Lib/Test/Harness/Assert.pm
#Lib/Test/Harness/Iterator.pm
#Lib/Test/Harness/Straps.pm

#############################################################################
# Automake rules
#############################################################################

bin_SCRIPTS = $(MYSCRIPTS)

# Install these leaving the directory heirarchy intact
nobase_bin_SCRIPTS = $(MYSCRIPTLIB)

#############################################################################
# Other rules
#############################################################################
