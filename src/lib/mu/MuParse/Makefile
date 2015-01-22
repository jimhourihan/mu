#  -*- mode: makefile -*-
# 
#  Copyright (C) 2001  Jim Hourihan
# 
#  The coded instructions herein are the sole property of Jim Hourihan
#  and may not be modified, redistributed, or used without permission.
# 


PROJECT    = MuParse
TYPE       = LIBRARY

SHOW_OUTPUT = TRUE

CXXFLAGS  += -DPLATFORM=$(PLATFORM) \
	     -DCOMPILER=$(COMPILER) \
	     -DARCH=$(ARCH) \
	     -DMU_FLEX_MINOR_VERSION=$(shell flex -V | sed 's/.*\.//g')
#             -DMU_DECLARE_YYWRAP

override YACC = /usr/local/bin/bison

MISCFILES   = 

CXXFLAGS  += -DPLATFORM=$(PLATFORM) \
	     -DCOMPILER=$(COMPILER) \
	     -DARCH=$(ARCH) 

CXXFILES   = GLRContext Grammar FlexLexer AST ASTBuild

GENFILES     = Grammar.h Grammar.cpp Grammar.c FlexLexer.cpp Lexer.cpp \
		Grammar.output 
LIBS         = MuLang Mu Half stl_ext gc

#
# Tune bison: -t adds debug support, MUYY is the prefix, YYFILTER
# adds stack variable initialization to make MSV happy (its not a bug,
# the Windows runtime environment is incorrectly throwing on an
# initialized memory usage)
#

YFLAGS     = -t 
YY         = MUGLRYY
YYFILTER   = sed -f yaccfilter.sed

include $(SRC_ROOT)/build/Makefile.master

#
# This fixes flex C++ output to be more modern (iostreams)
#

FlexLexer.cpp: Lexer.cpp
	sed -f flexfilter.sed Lexer.cpp > FlexLexer.cpp

