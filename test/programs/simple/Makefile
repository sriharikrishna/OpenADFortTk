# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/test/programs/simple/Makefile,v 1.2 2004/02/11 14:41:31 eraxxon Exp $
# -*-makefile-*-
## * BeginRiceCopyright *****************************************************
## 
## ******************************************************* EndRiceCopyright *

#############################################################################
# Makefile
#############################################################################

include $(WHIRL2XAIF)/test/Makeinclude.config

#############################################################################
# Configuration for bloop tests:
#############################################################################

.SUFFIXES: .f90
F90_EXCEPTIONS = types_derived1.f90 types_derived2.f90

VPATH = .

F90_MASTERS = $(shell ls *.f90)
F90_MASTERS := $(filter-out $(F90_EXCEPTIONS), $(F90_MASTERS))

MFEF90 = $(WHIRL2XAIF_OPEN64)/crayf90/sgi/mfef90
W2X = whirl2xaif
NORM = $(WHIRL2XAIF)/test/util/normalize

#############################################################################
# Building Rules for bloop tests:
#############################################################################

all: tests

tests : run_tests post_tests

run_tests: 
	echo "*** EXCEPTIONS: $(F90_EXCEPTIONS) ***"
	for f in $(F90_MASTERS) ; do \
	  f_B=`echo $${f} | sed s@.f90@.B@` ; \
	  f_xaif=`echo $${f} | sed s@.f90@.xaif@` ; \
	  $(MFEF90) $${f} ; \
	  $(W2X) $${f_B} ; \
	  $(NORM) $${f_xaif} ; \
	done

post_tests:
	rm -f *.mod-whirl

.PHONY : tests run_tests post_tests

#############################################################################

clean : post_tests
	rm -f *.B

veryclean : clean

.PHONY : veryclean clean

#############################################################################
