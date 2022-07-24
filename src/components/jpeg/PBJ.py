PROJECT      = "jpeg"
TYPE         = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM = BuildTypes.AUTOCONF
VERSION      = "9e"
LICENSE      = "BSD-like"
AUTHORS      = "Independent JPEG Group"
ARCHIVE      = "jpegsrc.v{0}.tar.gz".format(VERSION)
URL          = f"https://www.ijg.org/files/{ARCHIVE}"
ORIGIN_TREE  = "pbj"
EXPORT_LIBS  = ["jpeg"]
TARGET       = ["$BUILD_ROOT/lib/libjpeg.{0}.dylib".format(VERSION.split('.')[0][0]),
                "$BUILD_ROOT/lib/libjpeg.dylib",
                "$BUILD_ROOT/lib/libjpeg.a",
                "$BUILD_ROOT/lib/libjpeg.la",
                "$BUILD_ROOT/include/jconfig.h",
                "$BUILD_ROOT/include/jerror.h",
                "$BUILD_ROOT/include/jmorecfg.h",
                "$BUILD_ROOT/include/jpeglib.h"]
