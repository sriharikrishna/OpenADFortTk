# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/test/programs/simple/Makefile,v 1.7 2004/03/19 16:55:09 eraxxon Exp $
# -*-makefile-*-
## * BeginRiceCopyright *****************************************************
## 
## ******************************************************* EndRiceCopyright *

#############################################################################
# Makefile
#############################################################################

include $(WHIRL2XAIF)/test/Makeinclude.config

#############################################################################
# Configuration
#############################################################################

.SUFFIXES: .f90
F90_EXCEPTIONS =

VPATH = .

F90_MASTERS = $(shell ls *.f90)
F90_MASTERS := $(filter-out $(F90_EXCEPTIONS), $(F90_MASTERS))

# Pipeline
MFEF90  = $(WHIRL2XAIF_OPEN64)/crayf90/sgi/mfef90
WHIRL2F = $(WHIRL2XAIF_OPEN64)/whirl2f/whirl2f
XB_BB   = $(XAIFBOOSTERROOT)/xaifBooster/algorithms/BasicBlockPreaccumulation/test/t -c ${XAIFSCHEMAROOT}/schema/examples/inlinable_intrinsics.xaif
W2X     = $(WHIRL2XAIF)/obj/$(WHIRL2XAIF_PLATFORM)/obj/whirl2xaif
X2W     = $(WHIRL2XAIF)/obj/$(WHIRL2XAIF_PLATFORM)/obj/xaif2whirl
PP      = perl $(WHIRL2XAIF)/postprocess/pp.pl

NORM    = $(WHIRL2XAIF)/test/util/normalize

#############################################################################
# Building Rules for bloop tests:
#############################################################################

all: tests

.PHONY : all

#############################################################################

tests : tests_pre tests_run tests_post

tests_pre : schema

tests_run: 
	@echo "*** EXCEPTIONS: $(F90_EXCEPTIONS) ***"
	@for f in $(F90_MASTERS) ; do \
	  fbase=`echo $${f} | sed s@.f90@@` ; \
	  echo $${f}... ; \
	  $(MFEF90) $${f} ; \
	  $(W2X) $${fbase}.B -o $${fbase}.xaif ; \
	  $(NORM) $${fbase}.xaif ; \
	done

#pipeline :
#	$(MFEF90)   $(prog).F
#	$(W2X)      $(prog).B -o $(prog).xaif
#	$(XB_BB) -i $(prog).xaif -o $(prog).xb.xaif
#	$(X2W)      $(prog).B $(prog).xb.xaif -o $(prog).xb.x2w.B
#	$(WHIRL2F)  $(prog).xb.x2w.B
#	$(PP)       $(prog).xb.x2w.w2f.f

tests_post:

tests_clean:
	rm -f *.mod-whirl
	rm -f *.B

schema : schema_clean
	@if [ "$(WHIRL2XAIF_PLATFORM)" = "i686-Cygwin" ]; then \
	  ln $(XAIFSCHEMAROOT)/schema/xaif*.xsd . ; \
	else \
	  ln -s $(XAIFSCHEMAROOT)/schema/xaif*.xsd . ; \
	fi

schema_clean :
	rm -r -f *.xsd

.PHONY : tests tests_pre tests_run tests_post tests_clean schema schema_clean

#############################################################################

clean : tests_clean schema_clean

veryclean : clean

.PHONY : veryclean clean

#############################################################################
