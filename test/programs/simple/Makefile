# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/test/programs/simple/Makefile,v 1.4 2004/03/02 21:04:00 eraxxon Exp $
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
W2F = $(WHIRL2XAIF_OPEN64)/whirl2f/whirl2f
W2X = whirl2xaif
NORM = $(WHIRL2XAIF)/test/util/normalize

#############################################################################
# Building Rules for bloop tests:
#############################################################################

all: tests

tests : run_tests post_tests

run_tests: 
	@echo "*** EXCEPTIONS: $(F90_EXCEPTIONS) ***"
	@for f in $(F90_MASTERS) ; do \
	  f_B=`echo $${f} | sed s@.f90@.B@` ; \
	  f_xaif=`echo $${f} | sed s@.f90@.xaif@` ; \
	  echo $${f}... ; \
	  $(MFEF90) $${f} ; \
	  $(W2X) $${f_B} -o $${f_xaif} ; \
	  $(NORM) $${f_xaif} ; \
	done

run_w2f:
	@for f in $(F90_MASTERS) ; do \
	  f_B=`echo $${f} | sed s@.f90@.B@` ; \
	  $(W2F) $${f_B} ; \
	done

post_tests:
	@rm -f *.mod-whirl

.PHONY : tests run_tests post_tests

#############################################################################

clean : post_tests
	@rm -f *.B

veryclean : clean

.PHONY : veryclean clean

#############################################################################
