# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/Makefile,v 1.9 2005/03/22 20:30:25 utke Exp $

## * BeginCopyright *********************************************************
## *********************************************************** EndCopyright *

#############################################################################
# $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/xaif2whirl/Attic/Makefile,v $
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

EXE = $(OPENADFORTTK_OBJ_PATH)/$(EXE_XAIF2WHIRL)

LIBRARY = $(OPENADFORTTK_OBJ_PATH)/$(LIB_XAIF2WHIRL)

VPATH = $(SRCS)

# objects are placed wherever the compilation is done
OBJS = \
	main.o \
	Args.o \
	xaif2whirl.o \
	xaif2whirl_stmt.o \
	xaif2whirl_expr.o \
	\
	XlationContext.o \
	\
	XAIF_SAXHandler.o \
	XAIF_DOMErrorHandler.o \
	XAIF_DOMFilters.o \
	XercesStrX.o


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

# lgen: basename

LIBS = $(LIBRARY) $(OPENADFORTTK_OBJ_PATH)/$(LIB_SUPPORT) 

#	$(OPENADFORTTK_OBJ_PATH)/$(LIB_WHIRLREADER) \
#	$(OPENADFORTTK_OBJ_PATH)/$(LIB_COMUTIL) 

#############################################################################
# Compiling Rules:
#############################################################################

all: $(LIBRARY) $(EXE)

$(EXE): $(LIBS) $(BE_LIB_PATH)/libbe.$(DSOext)
ifdef PURE
	$(PURIFY) \
	  $(CXX) $(PURE_LDFLAGS) -o $(EXE) $(CXXFLAGS) $(LIBS) -L$(BE_LIB_PATH) -lbe $(LDFLAGS)
	@echo "*** Purified $(EXE) is up to date. ***"
else
	$(CXX) -o $(EXE) $(CXXFLAGS) $(LIBS) -L$(BE_LIB_PATH) -lbe $(LDFLAGS) 
	@echo "*** $(EXE) is up to date. ***"
endif

$(BE_LIB_PATH)/libbe.$(DSOext): $(BE_LIB_PATH)/be.$(DSOext)
	cp $< $@

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
