PROJECT		= "image"
TYPE		= Types.PLUGIN
PLUGIN_DIR	= "Mu"
PLUGIN_SUFFIX	= ".so"
CXX_FILES	= ["init.cpp"]
LIBS            = ["MuImage", "tiff", "jpeg", "z"]
USES = ["jpeg", "tiff", "z"]
