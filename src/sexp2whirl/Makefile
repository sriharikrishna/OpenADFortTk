# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/Attic/Makefile,v 1.4 2005/01/12 20:01:01 eraxxon Exp $

## * BeginCopyright *********************************************************
## *********************************************************** EndCopyright *

#############################################################################
# $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/sexp2whirl/Attic/Makefile,v $
#############################################################################

#############################################################################
# Site/machine/architecture dependent configuration 
#############################################################################

include $(OPENADFORTTK)/src/Makeinclude.config

ifndef SRCS
SRCS = .
endif

#############################################################################
# Site/machine/architecture independent configuration 
#############################################################################

.SUFFIXES: .cxx .h .d .cpp

EXE = $(OPENADFORTTK_OBJ_PATH)/$(EXE_SEXP2WHIRL)

LIBRARY = $(OPENADFORTTK_OBJ_PATH)/$(LIB_SEXP2WHIRL)

VPATH = $(SRCS)

# objects are placed wherever the compilation is done
OBJS = \
	main.o \
	Args.o \
	sexp2whirl.o \
	\
	sexp2wn.o \
	sexp2symtab.o

####################

# USER_* flags come from "Makeinclude.config"
CXXFLAGS := $(USER_CXXFLAGS)
CFLAGS := $(USER_CFLAGS)
IFLAGS := $(USER_C_IFLAGS) -I. -I$(VPATH) -I$(OPENADFORTTK_INCLUDE_PATH) \
	$(OPEN64_IFLAGS) $(SEXP_IFLAGS)
LDFLAGS := $(USER_C_LDFLAGS) $(OA_LDFLAGS) $(SEXP_LDFLAGS) -lm

#FIXMEcygwin
ifneq ($(PLATFORM),i686-Cygwin)
  LDFLAGS += -ldl
endif

LIBS = $(LIBRARY) $(OPENADFORTTK_OBJ_PATH)/$(LIB_SUPPORT) \
	$(OPEN64TARG)/whirl2f/be.$(DSOext)

#############################################################################
# Compiling Rules:
#############################################################################

all: $(LIBRARY) $(EXE)

$(EXE): $(LIBS)
ifdef PURE
	$(PURIFY) \
	  $(CXX) $(PURE_LDFLAGS) -o $(EXE) $(CXXFLAGS) $(LIBS) $(LDFLAGS)
	@echo "*** Purified $(EXE) is up to date. ***"
else
	$(CXX) -o $(EXE) $(CXXFLAGS) $(LIBS) $(LDFLAGS) 
	@echo "*** $(EXE) is up to date. ***"
endif


$(LIBRARY): $(OBJS)
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJS)
	@echo "*** $(LIBRARY) is up to date. ***"

clean:
	@echo "*** Cleaning $(OBJS) $(LIBRARY) $(EXE) ***"
	@/bin/rm -f $(OBJS) $(LIBRARY) $(EXE)

#include $(SRCS)/Makedepend

%.o : %.cxx
	$(CXX) -c $(CXXFLAGS) $(IFLAGS) $< -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

%.cpp : %.cxx
	$(CXX) -E $(CXXFLAGS) $(IFLAGS) $< > $@

%.d: %.cxx
	$(GPLUSPLUS) $(CXXFLAGS) -M $< > $@

#% :: RCS/%,v
