#  -*- mode: makefile -*-

PROJECT		= system
TYPE		= PLUGIN
PLUGIN_DIR	= plugins/Mu
PLUGINSUFFIX	= .so

ifeq ($(PLATFORM),WINDOWS)
IPATH          += \
                  $(SRC_ROOT)/pub/pcre \
                  $(SRC_ROOT)/pub/win_pthreads
endif

IPATH		+= $(SRC_ROOT)/pub/gc 

CXXFILES	= init
LIBS            = MuSystem 

include $(SRC_ROOT)/build/Makefile.master
