# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Attic/Makefile,v 1.17 2005/02/01 21:53:31 eraxxon Exp $

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

.SUFFIXES: .cxx .cpp .h .hpp .d

LIBRARY = $(OPENADFORTTK_OBJ_PATH)/$(LIB_SUPPORT)

VPATH = $(SRCS)

# objects are placed wherever the compilation is done

OBJS = \
	IntrinsicXlationTable.o \
	Pro64IRInterface.o \
	SymTab.o \
	ScalarizedRefTab.o \
	WhirlGlobalStateUtils.o \
	WhirlIDMaps.o \
	WhirlIO.o \
	WhirlParentize.o \
	stab_attr.o \
	wn_attr.o \
	\
	sexpostream.o \
	sexputil.o \
	SexpTags.o \
	xmlostream.o \
	XAIFStrings.o \
	\
	CmdLineParser.o \
	\
	Exception.o \
	XlationCtxt.o \
	diagnostics.o 


####################

# USER_* flags come from "Makeinclude.config"

CXXFLAGS := $(USER_CXXFLAGS) 
CFLAGS := $(USER_CFLAGS) 
IFLAGS := $(USER_C_IFLAGS) -I. -I$(VPATH) -I$(OPENADFORTTK_INCLUDE_PATH) \
	$(OPEN64_IFLAGS) $(OA_IFLAGS) $(XERCES_IFLAGS) $(SEXP_IFLAGS)

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

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(IFLAGS) $< -o $@

%.o : %.c
	$(CC) -c $(CFLAGS) $(IFLAGS) $< -o $@

%.cxx.pp : %.cxx
	$(CXX) -E $(CXXFLAGS) $(IFLAGS) $< > $@

%.d: %.cxx
	$(GPLUSPLUS) $(CXXFLAGS) -M $< > $@

#% :: RCS/%,v
