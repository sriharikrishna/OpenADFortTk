# -*-Mode: makefile;-*-
# $Header: /Volumes/cvsrep/developer/OpenADFortTk/test/lib/support/Makefile,v 1.2 2004/05/11 17:48:34 eraxxon Exp $

## * BeginCopyright *********************************************************
## *********************************************************** EndCopyright *

#############################################################################
# $Source: /Volumes/cvsrep/developer/OpenADFortTk/test/lib/support/Makefile,v $
#############################################################################

#############################################################################
# Site/machine/architecture dependent configuration 
#############################################################################

include $(OPENADFORTTK)/test/Makeinclude.config

ifndef SRCS
SRCS = .
endif

#############################################################################
# Site/machine/architecture independent configuration 
#############################################################################

.SUFFIXES: .cxx .h .d .cpp

TESTS = $(notdir $(shell ls $(SRCS)/*.test.cxx))

EXES = $(patsubst %.test.cxx, %.test, $(TESTS))
  #$(OPENADFORTTK_OBJ_PATH)

VPATH = $(SRCS)

# objects are placed wherever the compilation is done
OBJS = 

####################

# USER_* flags come from "Makeinclude.config"
CXXFLAGS := $(USER_CXXFLAGS)
CFLAGS := $(USER_CFLAGS)
IFLAGS := $(USER_C_IFLAGS) -I. -I$(VPATH) -I$(OPENADFORTTK_INCLUDE_PATH) \
          $(BOOST_IFLAGS)
LDFLAGS := $(USER_C_LDFLAGS) -lm

LIBS = $(OPENADFORTTK_OBJ_PATH)/$(LIB_SUPPORT)

#############################################################################
# Compiling Rules:
#############################################################################

all: $(EXES)

$(EXES): $(LIBS)
	$(CXX) $(CXXFLAGS) $(IFLAGS) -o $@ $(SRCS)/$@.cxx $(LIBS) $(LDFLAGS)
	@echo "*** $(EXES) are up to date. ***"

clean:
	@echo "*** Cleaning $(EXES) ***"
	@/bin/rm -f $(EXES)

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
