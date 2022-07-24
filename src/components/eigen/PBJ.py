PROJECT      = "eigen"
TYPE         = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM = BuildTypes.CMAKE
VERSION      = "3.4.0"
LICENSE      = "MPL2"
AUTHORS      = "Benoît Jacob, Gaël Guennebaud, et al"
ARCHIVE      = "eigen-3.4.0.tar.gz"
URL          = "http://bitbucket.org/eigen/eigen/get/3.3.7.tar.gz"
TARGET       = ["$BUILD_ROOT/include/eigen3"]
ORIGIN_TREE  = "pbj"

USE_CXX_FLAGS = ["-I$BUILD_ROOT/include/eigen3"]
USE_MXX_FLAGS = USE_CXX_FLAGS
USE_C_FLAGS   = USE_CXX_FLAGS
USE_M_FLAGS   = USE_C_FLAGS

#CONFIGURE_OPTIONS = ["-DCMAKE_BUILD_TYPE=Release"]
#CMAKE_MAKE_OPTIONS = 
