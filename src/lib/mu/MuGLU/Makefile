#  -*- mode: makefile -*-

PROJECT		= MuGLU
TYPE		= LIBRARY

ifneq ($(PLATFORM),WINDOWS)
OPTFLAGS        = -O3
endif

CXXFILES	= GLUModule
LIBS            = MuLang Mu GLU GL gc atomic

include $(SRC_ROOT)/build/Makefile.master
