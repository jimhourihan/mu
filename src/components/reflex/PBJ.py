PROJECT      = "reflex"
TYPE         = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM = BuildTypes.AUTOCONF
VERSION      = "3.2.3"
LICENSE      = "BSD"
AUTHORS      = "Robert van Engelen"
ARCHIVE      = f"RE-flex-{VERSION}.tar.gz"
URL          = "https://github.com/Genivia/RE-flex"
GIT_COMMIT   = "v" + VERSION
ORIGIN_TREE  = "pbj"
EXPORT_LIBS  = ["reflex"]
#USES         = ["boost"]
TARGET       = ["$BUILD_ROOT/lib/libreflex.a",
                "$BUILD_ROOT/bin/reflex",
                "$BUILD_ROOT/share/man/man1/reflex.1",
                "$BUILD_ROOT/include/reflex"]

USE_LINK_FLAGS = ["-lreflex"]
