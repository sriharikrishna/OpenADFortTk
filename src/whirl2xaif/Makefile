# $Header: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/Makefile,v 1.2 2003/05/20 22:50:03 eraxxon Exp $
# -*-makefile-*-

## * BeginCopyright *********************************************************
## *********************************************************** EndCopyright *

#############################################################################
# $Source: /Volumes/cvsrep/developer/OpenADFortTk/src/whirl2xaif/Attic/Makefile,v $
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

EXE = $(WHIRL2XAIF_OBJ_PATH)/$(EXE_WHIRL2XAIF)

LIBRARY = $(WHIRL2XAIF_OBJ_PATH)/$(LIB_WHIRL2XAIF)

VPATH = $(SRCS)

# objects are placed wherever the compilation is done
OBJS = \
	main.o \
	whirl2xaif.o \
	\
	wn2xaif.o \
	wn2xaif_stmt.o \
	wn2xaif_expr.o \
	wn2xaif_mem.o \
	wn2xaif_io.o \
	wn2f_pragma.o \
	\
	init2f.o \
	st2f.o \
	tcon2f.o \
	ty2f.o \
	whirl2f_common.o \
	w2cf_parentize.o \
	w2cf_symtab.o \
	\
	diagnostics.o \
	PUinfo.o \
	stab_attr.o \
	wn_attr.o \
	\
	Pro64IRInterface.o \
	SymTab.o \
	XlationContext.o \
	xmlostream.o

####################

# FIXME:
XTRA_FLAGS = -DIs_True_On -DMONGOOSE_BE -DBACK_END -DBUILD_WHIRL2F

# USER_* flags come from "Makeinclude.config"
CXXFLAGS := $(USER_CXXFLAGS) $(XTRA_FLAGS)
CFLAGS := $(USER_CFLAGS)     $(XTRA_FLAGS)
IFLAGS := $(USER_C_IFLAGS) -I. -I$(VPATH) $(OPEN64_IFLAGS) $(OA_IFLAGS)
LDFLAGS := $(USER_C_LDFLAGS) $(OA_LDFLAGS) -lm -ldl

# lgen: basename

LIBS = $(LIBRARY) $(OPEN64)/$(O64TARG)/whirl2f/be.so

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
