#  -*- mode: makefile -*-

PROJECT		= MuGLText
TYPE		= LIBRARY

ifneq ($(PLATFORM),WINDOWS)
OPTFLAGS        = -O3
endif

CXXFILES	= GLTextModule
LIBS            = MuLang Mu TwkGLText Half ftgl freetype GLU GL gc atomic

include $(SRC_ROOT)/build/Makefile.master
