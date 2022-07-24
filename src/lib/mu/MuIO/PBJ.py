PROJECT		= "MuIO"
TYPE		= Types.LIBRARY

#CXXFLAGS_WINDOWS += -D_POSIX_ -D_UNICODE -DUNICODE

CXX_FILES = ["IOModule.cpp", "StreamType.cpp", "OStreamType.cpp",
             "OFStreamType.cpp", "IStreamType.cpp", "IFStreamType.cpp",
             "OSStreamType.cpp", "ISStreamType.cpp", "exec-stream.cpp",
             "ProcessType.cpp"]

LIBS = ["MuLang", "Mu", "gc"] 
