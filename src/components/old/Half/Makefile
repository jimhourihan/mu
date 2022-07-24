#  -*- mode: makefile -*-

PROJECT	  = Half
TYPE      = SHARED_LIBRARY

#
# Once our buildsystem supports PRJS or
# TYPE=HEADERS we can remove this sort of IPATHing.
# Right now IlmBaseConfig.h is kept in the Iex project.
#
IPATH     += $(SRC_ROOT)/Iex/IlmBaseConfig

ifeq ($(TYPE),SHARED_LIBRARY)
WINDOWS_AUTO_EXPORT_DLL = TRUE
CXXFLAGS_WINDOWS = -DEBUG -DOPENEXR_DLL=1 -DHALF_EXPORTS=1
endif

#OPTFLAGS  = -O3

CXXFILES  = half


include $(SRC_ROOT)/build/Makefile.master

