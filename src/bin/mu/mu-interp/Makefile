#  -*- mode: makefile -*-

PROJECT	     = mu-interp
WRAPPER	     = mu-interp.wrapper
TYPE	     = EXECUTABLE_WITH_PLUGINS

CXXFILES     = main
LIBS_DARWIN  = readline mx dl pthread
LIBS_LINUX   = readline ncurses dl pthread rt
LIBS_WINDOWS = pcre win_pthreads win_posix MuQt MuImage MuAutoDoc MuSystem MuIO QtUiTools $(QTLIBS) cxcore cv tiff jpeg z 
#LIBS_WINDOWS = pcre win_pthreads win_posix 
LIBS	     = MuLang Mu Half stl_ext arg gc 

FRAMEWORKS_DARWIN = System

IPATH += $(QTDIR)/include/QtCore

CXXFLAGS_LINUX  += -DMU_USE_READLINE
CXXFLAGS_DARWIN += -DMU_USE_READLINE
CXXFLAGS_WINDOWS += -DLINKED_MODULES

ifneq ($(PLATFORM),WINDOWS)
MODULES = mu_math_linear mu_system mu_autodoc mu_io mu_test mu_encoding \
mu_gl mu_glText mu_glu
endif

include $(SRC_ROOT)/build/Makefile.master

run_runall:
	./runall
