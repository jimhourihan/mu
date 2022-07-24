PROJECT		= "MuImage"
TYPE		= Types.LIBRARY

CXX_FILES	= ["ImageModule.cpp",  "ImageType.cpp", "PixelsType.cpp"]
LIBS            = ["MuLang", "Mu", "tiff", "jpeg", "gc"]
USES = ["tiff", "jpeg"]

