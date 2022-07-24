PROJECT	= "mu-interp"
TYPE	= Types.EXECUTABLE_WITH_PLUGINS

CXX_FLAGS = "-DMU_USE_READLINE"
CXX_FILES = ["main.cpp"]

USES = ["boost"]

LIBS = [ "MuLang", "Mu", "Imath", "stl_ext", "boost_program_options",
         "gc", "readline", "mx", "dl", "pthread"]

MODULES = ["mu_image", "mu_system", "mu_io", "mu_encoding", "mu_autodoc",
           "mu_math_linear"]

FRAMEWORKS = ["System"]


