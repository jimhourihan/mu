#  -*- mode: makefile -*-


PROJECT		= MuGL
TYPE		= LIBRARY

ifneq ($(PLATFORM),WINDOWS)
OPTFLAGS        = -O3
endif

CXXFILES	= GLModule
LIBS            = MuLang Mu GL gc atomic

LIBS_WINDOWS    =  glew


include $(SRC_ROOT)/build/Makefile.master
