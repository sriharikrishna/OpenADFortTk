# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/test/programs/simple/Makefile,v 1.10 2004/03/31 14:17:46 eraxxon Exp $
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
F90_EXCEPTIONS1 = \
	arrays1.f90 arrays2.f90 arrays_dimensions1.f90 \
	controlflow_loop1c.f90 controlflow_loop4.f90 controlflow_switch1.f90 \
	  controlflow_loop2.f90 controlflow_loop3.f90 \
	functions1.f90 functions2.f90 functions_nested2.f90 \
	  functions_nested3.f90 intrinsics1.f90 \
	pragma1.f90 scoping1.f90 \
	types_derived1.f90 types_derived2.f90

VPATH = .

F90_MASTERS = $(shell ls *.f90)
F90_MASTERS := $(filter-out $(F90_EXCEPTIONS), $(F90_MASTERS))
F90_MASTERS1 = $(shell ls *.f90)
F90_MASTERS1 := $(filter-out $(F90_EXCEPTIONS1), $(F90_MASTERS1))

# Pipeline
MFEF90  = $(WHIRL2XAIF_OPEN64)/crayf90/sgi/mfef90
WHIRL2F = $(WHIRL2XAIF_OPEN64)/whirl2f/whirl2f
XB_BB   = $(XAIFBOOSTERROOT)/xaifBooster/algorithms/BasicBlockPreaccumulation/test/t -c $(XAIFSCHEMAROOT)/schema/examples/inlinable_intrinsics.xaif
W2X     = $(WHIRL2XAIF)/obj/$(WHIRL2XAIF_PLATFORM)/obj/whirl2xaif
X2W     = $(WHIRL2XAIF)/obj/$(WHIRL2XAIF_PLATFORM)/obj/xaif2whirl
PP      = perl $(WHIRL2XAIF)/postprocess/pp.pl

NORM    = $(WHIRL2XAIF)/test/util/normalize

OPENAD  = $(WHIRL2XAIF)/test/util/openad

#############################################################################
# Building Rules for bloop tests:
#############################################################################

all: tests

.PHONY : all

#############################################################################

tests : tests_pre tests_run tests_pipeline tests_post

tests_pre : schema

tests_run: 
	@echo "****** whirl2xaif TESTS ******"
	@echo "*** exceptions: $(F90_EXCEPTIONS) ***"
	@for f in $(F90_MASTERS) ; do \
	  fbase=`echo $${f} | sed s@.f90@@` ; \
	  echo "  *** $${f}..." ; \
	  $(MFEF90)   $${f} ; \
	  $(W2X)      $${fbase}.B    -o $${fbase}.xaif ; \
	  $(NORM)     $${fbase}.xaif ; \
	done

tests_pipeline:
	@echo "****** PIPELINE TESTS ******"
	@echo "*** exceptions: $(F90_EXCEPTIONS1) ***"
	@for f in $(F90_MASTERS1) ; do \
	  printf "  " ; \
	  $(OPENAD) -v $${f} ; \
	done

tests_post:

tests_clean:
	rm -f *.mod-whirl
	rm -f *.B

tests_pipeline_clean:
	rm -f *.xb.xaif
	rm -f *.w2f.f
	rm -f *.w2f.pp.f

schema : schema_clean
	@if [ "$(WHIRL2XAIF_PLATFORM)" = "i686-Cygwin" ]; then \
	  ln $(XAIFSCHEMAROOT)/schema/xaif*.xsd . ; \
	else \
	  ln -s $(XAIFSCHEMAROOT)/schema/xaif*.xsd . ; \
	fi

schema_clean :
	rm -r -f *.xsd

.PHONY : tests tests_pre tests_run  tests_post tests_clean schema schema_clean
.PHONY : tests_pipeline tests_pipeline_clean

#############################################################################

clean : tests_clean tests_pipeline_clean schema_clean

veryclean : clean

.PHONY : veryclean clean

#############################################################################
