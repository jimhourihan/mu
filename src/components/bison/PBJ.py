PROJECT      = "bison"
TYPE         = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM = BuildTypes.AUTOCONF
VERSION      = "3.8"
LICENSE      = "GPL"
AUTHORS      = "GNU"
ARCHIVE      = f"bison-{VERSION}.tar.gz"
URL          = f"https://ftp.gnu.org/gnu/bison/{ARCHIVE}"
ORIGIN_TREE  = "pbj"
TARGET       = ["$BUILD_ROOT/bin/bison",
                "$BUILD_ROOT/bin/yacc",
                "$BUILD_ROOT/lib/liby.a"
                "$BUILD_ROOT/share/info/bison.info",
                "$BUILD_ROOT/share/bison"]

