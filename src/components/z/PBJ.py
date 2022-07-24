PROJECT      = "z"
TYPE         = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM = BuildTypes.AUTOCONF
VERSION      = "1.2.12"
LICENSE      = "ZLIB"
AUTHORS      = "Jean-loup Gailly and Mark Adler"
ARCHIVE      = f"zlib-{VERSION}.tar.gz"
URL          = f"https://zlib.net/{ARCHIVE}"
ORIGIN_TREE  = "pbj"
EXPORT_LIBS  = ["z"]
TARGET       = [f"$BUILD_ROOT/lib/libz.{VERSION}.dylib",
                "$BUILD_ROOT/lib/libz.{0}.dylib".format(VERSION.split('.')[0]),
                "$BUILD_ROOT/lib/libz.a",
                "$BUILD_ROOT/lib/libz.dylib",
                "$BUILD_ROOT/include/zlib.h",
                "$BUILD_ROOT/include/zconf.h"]
