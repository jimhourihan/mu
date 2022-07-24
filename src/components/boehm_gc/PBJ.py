PROJECT      = "boehm_gc"
TYPE         = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM = BuildTypes.CMAKE
VERSION      = "8.2.0"
LICENSE      = "MIT?"
AUTHORS      = "Hans Boehm et al"
ARCHIVE      = f"gc-{VERSION}.tar.gz"
URL          = f"https://github.com/ivmai/bdwgc/releases/download/v{VERSION}/{ARCHIVE}"
ORIGIN_TREE  = "pbj"
USES         = ["atomic_ops"]
EXPORT_LIBS  = ["gc"]

TARGET = ["$BUILD_ROOT/lib/libgc.dylib"]

