PROJECT           = "tiff"
TYPE              = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM      = BuildTypes.CMAKE # it has autoconf but fails with recent clang
VERSION           = "4.3.0"
LICENSE           = "BSD-like"
AUTHORS           = "Sam Leffler and Silicon Graphics"
ARCHIVE           = f"tiff-{VERSION}.tar.gz"
URL               = f"https://download.osgeo.org/libtiff/tiff-{VERSION}.tar.gz"
ORIGIN_TREE       = "pbj"
USES              = ["z", "jpeg"]
#CONFIGURE_OPTIONS = ["--with-jpeg-lib-dir=$BUILD_ROOT/lib",
#                     "--with-jpeg-include-dir=$BUILD_ROOT/include",
#                     "--with-zlib-lib-dir=$BUILD_ROOT/lib",
#                     "--with-zlib-include-dir=$BUILD_ROOT/include"]
EXPORT_LIBS       = ["tiff"]
TARGET            = ["$BUILD_ROOT/lib/libtiff.5.7.0.dylib",
                     "$BUILD_ROOT/lib/libtiff.5.dylib",
                     "$BUILD_ROOT/lib/libtiff.dylib",
                     "$BUILD_ROOT/lib/libtiffxx.5.7.0.dylib",
                     "$BUILD_ROOT/lib/libtiffxx.5.dylib",
                     "$BUILD_ROOT/lib/libtiffxx.dylib",
                     "$BUILD_ROOT/include/tiff.h",
                     "$BUILD_ROOT/include/tiffconf.h",
                     "$BUILD_ROOT/include/tiffio.h",
                     "$BUILD_ROOT/include/tiffio.hxx",
                     "$BUILD_ROOT/include/tiffvers.h"]
