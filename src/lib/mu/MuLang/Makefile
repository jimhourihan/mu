#  -*- mode: makefile -*-
# 
#  Copyright (C) 2001  Jim Hourihan
# 
#  The coded instructions herein are the sole property of Jim Hourihan
#  and may not be modified, redistributed, or used without permission.
# 


PROJECT    = MuLang
TYPE       = LIBRARY

CXXFLAGS  += -DPLATFORM=$(PLATFORM) \
	     -DCOMPILER=$(COMPILER) \
	     -DARCH=$(ARCH) \
	     -DMU_FLEX_MINOR_VERSION=$(shell $(LEX) -V | sed -e 's/^.*\.//' -e 's/\(^[0-9]*\).*$$/\1/') \
	     -DMU_FLEX_APPLE=$(shell $(LEX) -V | grep Apple | wc -l | sed 's/ //g') 
#             -DMU_DECLARE_YYWRAP

MODULEFILES = Runtime Math MathUtil 
TYPEFILES   = Float Double Void Bool String Exception DynamicArray \
	      FixedArray Regex Short Byte Char Vector Int Name Int64 \
              Half

MISCFILES   = MuLangContext MuLangLanguage \
	      ObjectInterface DynamicArray FixedArray Noise \
	      TypePattern VectorTypeModifier InteractiveSession

CXXFLAGS  += -DPLATFORM=$(PLATFORM) \
	     -DCOMPILER=$(COMPILER) \
	     -DARCH=$(ARCH) 

CXXFILES   = $(MISCFILES) \
	     $(addsuffix Module,$(MODULEFILES)) \
	     $(addsuffix Type,$(TYPEFILES))

YACCFILES       = Grammar
GENFILES        = $(metasrc_dir)/FlexLexer.cpp  

LIBS         = Mu Half stl_ext gc

#
# Tune bison: -t adds debug support, MUYY is the prefix, YYFILTER
# adds stack variable initialization to make MSV happy (its not a bug,
# the Windows runtime environment is incorrectly throwing on an
# initialized memory usage)
#

YFLAGS     = -t 
YY         = MUYY
YYFILTER   = sed -f yaccfilter.sed

include $(SRC_ROOT)/build/Makefile.master

#
# This fixes flex C++ output to be more modern (iostreams)
#

$(metasrc_dir)/FlexLexer.cpp: $(metasrc_dir)/Lexer.cpp
	$(MKDIR) $(dir $@) ; sed -f flexfilter.sed $< > $@


