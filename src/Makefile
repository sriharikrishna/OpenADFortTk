# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/Attic/Makefile,v 1.2 2003/07/24 20:31:05 eraxxon Exp $

## * BeginCopyright *********************************************************
## *********************************************************** EndCopyright *

#############################################################################
# $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/Attic/Makefile,v $
#############################################################################

# FIXME
# Environment options (exported variables):
#   - pass RELEASE=1 to compile a binary for release (no debugging info and 
#     with basic optimization)
#   - pass PURE=1 to create a purified library

#FIXME
#############################################################################
# Site/machine/architecture dependent configuration 
#############################################################################

include $(WHIRL2XAIF)/src/Makeinclude.config

#############################################################################
# Site/machine/architecture independent configuration 
#############################################################################

all: exes install

exes: build_whirl2xaif

.PHONY: all exes

#############################################################################


#-----------------------------------------------------------------
#  Binaries
#-----------------------------------------------------------------

build_whirl2xaif: libs
	src=$(WHIRL2XAIF)/src/whirl2xaif ; \
	obj=$(WHIRL2XAIF_OBJ_PATH)/exewhirl2xaif ; \
	mkdir -p $$obj ; \
	cd $$obj ; \
	$(MAKE) -f $$src/Makefile SRCS=$$src

.PHONY: build_whirl2xaif


#-----------------------------------------------------------------
#  Libraries
#-----------------------------------------------------------------

LIBDIRS = lib/support
#libcomutil libwhirlreader

libs: 
ifdef LIBDIRS
	src=$(WHIRL2XAIF)/src ; \
	for lib in $(LIBDIRS) ; do \
	  obj=$(WHIRL2XAIF_OBJ_PATH)/$$lib ; \
	  mkdir -p $$obj ; \
	  cd $$obj ; \
	  $(MAKE) -f $$src/$$lib/Makefile SRCS=$$src/$$lib ; \
	done
endif

.PHONY: libs


#-----------------------------------------------------------------
#  Install/Uninstall
#-----------------------------------------------------------------

# install everything
install: exes

# uninstall everything
uninstall: clean

.PHONY: install uninstall


#-----------------------------------------------------------------
#  Clean build files
#-----------------------------------------------------------------

clean: veryclean

veryclean:
	if [ -n "$(WHIRL2XAIF_OBJ_PATH)" \
	     -a "$(WHIRL2XAIF_OBJ_PATH)" != "/" ] ; then \
	  /bin/rm -f -r $(WHIRL2XAIF_OBJ_PATH); \
	fi

.PHONY: clean veryclean


#-----------------------------------------------------------------
#  Vars
#-----------------------------------------------------------------

vars: 
	@echo CXX=$(CXX)
	@echo CC=$(CC)

.PHONY: vars
