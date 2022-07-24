PROJECT      = Modules.boost # this is the name "boost" 
TYPE         = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM = BuildTypes.BOOST
VARIABLES    = ["CXX_VERSION", "CXX_LIBRARY"] # e.g. "c++17" and "libc++"
VERSION      = "1.76.0" ## VFXPLATFORM 2022, NOTE: 1.78 has a stupid bug so avoid it
ARCHIVE      = "boost_{0}.tar.gz".format(VERSION.replace('.', '_'))
URL          = "https://dl.bintray.com/boostorg/release/{0}/source/boost_{1}.tar.gz".format(VERSION, VERSION.replace('.','_'))
USES         = ["z"]
ORIGIN_TREE  = "pbj"

# > pbj --internal list-boost-targets
# will produce these two lists

a = ['stacktrace_basic', 'math_tr1', 'container', 'context', 'math_c99f',
     'iostreams', 'thread', 'program_options', 'coroutine', 'timer', 'contract',
     'type_erasure', 'log_setup', 'atomic', 'random', 'date_time',
     'test_exec_monitor', 'stacktrace_noop', 'system', 'exception', 'math_c99',
     'prg_exec_monitor', 'math_tr1f', 'wave', 'log', 'graph', 'regex',
     'wserialization', 'unit_test_framework', 'filesystem', 'chrono',
     'serialization']

so = ['wave', 'thread', 'math_c99f', 'iostreams', 'wserialization',
      'contract', 'prg_exec_monitor', 'graph', 'container', 'random',
      'math_tr1f', 'stacktrace_basic', 'regex', 'program_options',
      'type_erasure', 'log_setup', 'serialization', 'unit_test_framework',
      'timer', 'filesystem', 'stacktrace_noop', 'log', 'math_tr1', 'atomic',
      'date_time', 'system', 'math_c99', 'chrono', 'context']

c = ["fiber", "fiber_numa", "graph_parallel", "headers", "locale", #"math",
     "math_c99l", "math_tr1l", "mpi", "stacktrace_addr2line",
     "stacktrace_backtrace", "stacktrace_windbg", "stacktrace_windbg_cached"]

EXPORT_LIBS = list(map(lambda x: f"boost_{x}", so))

a_targets     = list(map(lambda x: "$BUILD_ROOT/lib/libboost_{0}.a".format(x), a))
dylib_targets = list(map(lambda x: "$BUILD_ROOT/lib/libboost_{0}.dylib".format(x), so))
cmake_targets = list(map(lambda x, v=VERSION: "$BUILD_ROOT/lib/cmake/boost_{0}-{1}".format(x, v), a + so + c))
cmake_targets += ["$BUILD_ROOT/lib/cmake/Boost-{0}".format(VERSION),
                  "$BUILD_ROOT/lib/cmake/BoostDetectToolset-{0}.cmake".format(VERSION)]
TARGET        = a_targets + dylib_targets + ["$BUILD_ROOT/include/boost"] + cmake_targets

#
#   Boost specific stuff
#

BOOST_B2_CXXFLAGS                 = ["-DBOOST_COROUTINES_NO_DEPRECATION_WARNING=1"]
BOOST_BOOTSTRAP_WITHOUT_LIBRARIES = ["python"]


if PBJ.PLATFORM == "DARWIN":
        BOOST_TOOLSET            = "clang"
        BOOST_BOOTSTRAP_CXXFLAGS = ["-std=$CXX_VERSION", "-stdlib=$CXX_LIBRARY"]
        BOOST_B2_CXXFLAGS       += ["-std=$CXX_VERSION", "-stdlib=$CXX_LIBRARY"]
        BOOST_B2_LINKFLAGS       = ["-stdlib=$CXX_LIBRARY"]

elif PBJ.PLATFORM == "LINUX":
        BOOST_TOOLSET            = "gcc"
        BOOST_BOOTSTRAP_CXXFLAGS = []
        BOOST_B2_LINKFLAGS       = []

USE_LINK_FLAGS = ["-rpath $BUILD_ROOT/lib"]
