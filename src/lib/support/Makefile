# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Attic/Makefile,v 1.6 2003/09/17 19:43:09 eraxxon Exp $

## * BeginCopyright *********************************************************
## *********************************************************** EndCopyright *

#############################################################################
# $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/lib/support/Attic/Makefile,v $
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

LIBRARY = $(WHIRL2XAIF_OBJ_PATH)/$(LIB_SUPPORT)

VPATH = $(SRCS)

# objects are placed wherever the compilation is done

OBJS = \
	Pro64IRInterface.o \
	WhirlIO.o \
	WhirlIDMaps.o \
	\
	wn_attr.o \
	stab_attr.o \
	w2cf_symtab.o \
	SymTab.o \
	\
	xmlostream.o \
	XAIFStrings.o \
	\
	XlationCtxt.o \
	diagnostics.o


####################

# USER_* flags come from "Makeinclude.config"

CXXFLAGS := $(USER_CXXFLAGS) 
CFLAGS := $(USER_CFLAGS) 
IFLAGS := $(USER_C_IFLAGS) -I. -I$(VPATH) -I$(WHIRL2XAIF_INCLUDE_PATH) \
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
