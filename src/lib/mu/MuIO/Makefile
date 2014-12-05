#  -*- mode: makefile -*-

PROJECT		= MuIO
TYPE		= LIBRARY

CXXFLAGS_WINDOWS += -D_POSIX_ -D_UNICODE -DUNICODE

CXXFILES	= IOModule StreamType OStreamType OFStreamType \
		  IStreamType IFStreamType OSStreamType ISStreamType \
	          exec-stream ProcessType

LIBS = MuLang Mu gc 

include $(SRC_ROOT)/build/Makefile.master
