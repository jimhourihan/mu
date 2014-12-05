#  -*- mode: makefile -*-

PROJECT		= glText
TYPE		= PLUGIN
PLUGIN_DIR	= plugins/Mu
PLUGINSUFFIX	= .so
IPATH		= $(SRC_ROOT)/pub/gc

CXXFILES	= init
LIBS            = MuGLText TwkGLText FTGL TwkUtil TwkExc freetype 
LIBS_LINUX      = GLU GL 
FRAMEWORKS_DARWIN = OpenGL

include $(SRC_ROOT)/build/Makefile.master
