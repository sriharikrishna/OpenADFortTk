# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/Attic/Makefile,v 1.12 2005/01/13 14:23:23 eraxxon Exp $

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

include $(OPENADFORTTK)/src/Makeinclude.config

#############################################################################
# Site/machine/architecture independent configuration 
#############################################################################

all: exes install

exes: build_exes

.PHONY: all exes

#############################################################################


#-----------------------------------------------------------------
#  Binaries
#-----------------------------------------------------------------

EXEDIRS = whirl2xaif xaif2whirl testers

ifdef BUILD_WHIRL2SEXP_AND_SEXP2WHIRL
  EXEDIRS += whirl2sexp sexp2whirl
endif

build_exes: build_libs
	src=$(OPENADFORTTK)/src ; \
	for exe in $(EXEDIRS) ; do \
	  if [ -d $$src/$$exe ] ; then \
	    obj=$(OPENADFORTTK_OBJ_PATH)/exe-$$exe ; \
	    mkdir -p $$obj ; \
	    cd $$obj ; \
	    $(MAKE) -f $$src/$$exe/Makefile SRCS=$$src/$$exe ; \
	  fi ; \
	done

.PHONY: build_exes


#-----------------------------------------------------------------
#  Libraries
#-----------------------------------------------------------------

LIBDIRS = lib/support

build_libs: 
ifdef LIBDIRS
	src=$(OPENADFORTTK)/src ; \
	for lib in $(LIBDIRS) ; do \
	  obj=$(OPENADFORTTK_OBJ_PATH)/$$lib ; \
	  mkdir -p $$obj ; \
	  cd $$obj ; \
	  $(MAKE) -f $$src/$$lib/Makefile SRCS=$$src/$$lib ; \
	done
endif

.PHONY: build_libs


#-----------------------------------------------------------------
#  Install/Uninstall
#-----------------------------------------------------------------

# install everything
install: install_real install_post

install_real: exes

install_post: 

# uninstall everything
uninstall: clean

.PHONY: install install_real install_post uninstall


#-----------------------------------------------------------------
#  Clean build files
#-----------------------------------------------------------------

clean: veryclean

veryclean:
	if [ -n "$(OPENADFORTTK_OBJ_PATH)" \
	     -a "$(OPENADFORTTK_OBJ_PATH)" != "/" ] ; then \
	  /bin/rm -f -r $(OPENADFORTTK_OBJ_PATH); \
	fi

.PHONY: clean veryclean


#-----------------------------------------------------------------
#  Vars
#-----------------------------------------------------------------

vars: 
	@echo CXX=$(CXX)
	@echo CC=$(CC)

.PHONY: vars
