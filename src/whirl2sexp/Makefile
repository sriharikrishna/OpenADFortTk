# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/Attic/Makefile,v 1.1 2004/08/05 18:38:14 eraxxon Exp $

## * BeginCopyright *********************************************************
## *********************************************************** EndCopyright *

#############################################################################
# $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2sexp/Attic/Makefile,v $
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

EXE = $(OPENADFORTTK_OBJ_PATH)/$(EXE_WHIRL2SEXP)

LIBRARY = $(OPENADFORTTK_OBJ_PATH)/$(LIB_WHIRL2SEXP)

VPATH = $(SRCS)

# objects are placed wherever the compilation is done
OBJS = \
	main.o \
	Args.o \
	whirl2sexp.o \
	\
	wn2sexp.o \
	symtab2sexp.o 

# pu2sexp

####################

# USER_* flags come from "Makeinclude.config"
CXXFLAGS := $(USER_CXXFLAGS)
CFLAGS := $(USER_CFLAGS)
IFLAGS := $(USER_C_IFLAGS) -I. -I$(VPATH) -I$(OPENADFORTTK_INCLUDE_PATH) \
	$(OPEN64_IFLAGS) $(OA_IFLAGS) $(XERCES_IFLAGS)
LDFLAGS := $(USER_C_LDFLAGS) $(OA_LDFLAGS) $(XERCES_LDFLAGS) -lm

#FIXMEcygwin
ifneq ($(PLATFORM),i686-Cygwin)
  LDFLAGS += -ldl
endif

LIBS = $(LIBRARY) $(OPENADFORTTK_OBJ_PATH)/$(LIB_SUPPORT) \
	$(OPEN64TARG)/whirl2f/be.$(DSOext)

#	$(OPENADFORTTK_OBJ_PATH)/$(LIB_WHIRLREADER) \
#	$(OPENADFORTTK_OBJ_PATH)/$(LIB_COMUTIL) 

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
