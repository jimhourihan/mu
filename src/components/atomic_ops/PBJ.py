PROJECT      = "atomic_ops"
TYPE         = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM = BuildTypes.AUTOCONF
VERSION      = "7.6.12"
LICENSE      = "MIT?"
AUTHORS      = "Hans Boehm et al"
ARCHIVE      = f"libatomic_ops-{VERSION}.tar.gz"
URL          = f"https://github.com/ivmai/libatomic_ops/releases/download/v{VERSION}/{ARCHIVE}"
ORIGIN_TREE  = "pbj"
EXPORT_LIBS  = ["atomic_ops"]
TARGET       = ["$BUILD_ROOT/lib/libatomic_ops.a",
                "$BUILD_ROOT/lib/libatomic_ops_gpl.a"]

