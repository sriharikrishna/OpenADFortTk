# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Attic/Makefile,v 1.12 2004/05/11 17:48:33 eraxxon Exp $

## * BeginCopyright *********************************************************
## *********************************************************** EndCopyright *

#############################################################################
# $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Attic/Makefile,v $
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

LIBRARY = $(OPENADFORTTK_OBJ_PATH)/$(LIB_SUPPORT)

VPATH = $(SRCS)

# objects are placed wherever the compilation is done

OBJS = \
	IntrinsicXlationTable.o \
	Pro64IRInterface.o \
	SymTab.o \
	WhirlGlobalStateUtils.o \
	WhirlIDMaps.o \
	WhirlIO.o \
	WhirlParentize.o \
	stab_attr.o \
	wn_attr.o \
	\
	xmlostream.o \
	CmdLineParser.o \
	XAIFStrings.o \
	\
	XlationCtxt.o \
	diagnostics.o


####################

# USER_* flags come from "Makeinclude.config"

CXXFLAGS := $(USER_CXXFLAGS) 
CFLAGS := $(USER_CFLAGS) 
IFLAGS := $(USER_C_IFLAGS) -I. -I$(VPATH) -I$(OPENADFORTTK_INCLUDE_PATH) \
	$(OPEN64_IFLAGS) $(OA_IFLAGS) $(XERCES_IFLAGS)

#############################################################################
# Compiling Rules:
#############################################################################

install: $(LIBRARY)
	@echo "*** $(LIBRARY) is up to date. ***"

$(LIBRARY): $(OBJS) 
	$(AR) $(ARFLAGS) $(LIBRARY) $(OBJS)

clean:
	@echo "*** Cleaning $(OBJS) $(LIBRARY) ***"
	@/bin/rm -f $(OBJS) $(LIBRARY)

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
