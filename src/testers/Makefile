# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/testers/Attic/Makefile,v 1.2 2003/10/29 01:52:50 eraxxon Exp $

## * BeginCopyright *********************************************************
## *********************************************************** EndCopyright *

#############################################################################
# $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/testers/Attic/Makefile,v $
#############################################################################

#############################################################################
# Site/machine/architecture dependent configuration 
#############################################################################

include $(WHIRL2XAIF)/src/Makeinclude.config

ifndef SRCS
SRCS = .
endif

#############################################################################
# Site/machine/architecture independent configuration 
#############################################################################

.SUFFIXES: .cxx .h .d .cpp

EXE = $(WHIRL2XAIF_OBJ_PATH)/$(EXE_WHIRLTESTER)

LIBRARY = $(WHIRL2XAIF_OBJ_PATH)/$(LIB_WHIRLTESTER)

VPATH = $(SRCS)

# objects are placed wherever the compilation is done
OBJS = \
	main.o \
	tester.o

####################

# USER_* flags come from "Makeinclude.config"
CXXFLAGS := $(USER_CXXFLAGS)
CFLAGS := $(USER_CFLAGS)
IFLAGS := $(USER_C_IFLAGS) -I. -I$(VPATH) -I$(WHIRL2XAIF_INCLUDE_PATH) \
	$(OPEN64_IFLAGS) $(OA_IFLAGS) 
LDFLAGS := $(USER_C_LDFLAGS) $(OA_LDFLAGS) -lm

#FIXMEcygwin
ifneq ($(PLATFORM),i686-Cygwin)
  LDFLAGS += -ldl
endif

LIBS = $(LIBRARY) $(WHIRL2XAIF_OBJ_PATH)/$(LIB_SUPPORT) \
	$(OPEN64)/$(O64TARG)/whirl2f/be.$(DSOext)

#	$(WHIRL2XAIF_OBJ_PATH)/$(LIB_WHIRLREADER) \
#	$(WHIRL2XAIF_OBJ_PATH)/$(LIB_COMUTIL) 

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
