PROJECT		= "io"
TYPE		= Types.PLUGIN
PLUGIN_DIR	= "Mu"
PLUGIN_SUFFIX	= ".so"
CXX_FILES	= ["init.cpp"]
LIBS            = ["MuIO"]

USE_RUN_ENV = [("MU_MODULE_PATH", "$BUILD_ROOT/Plugins/Mu")]