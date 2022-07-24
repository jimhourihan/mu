PROJECT      = "imath"
TYPE         = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM = BuildTypes.CMAKE
VERSION      = "3.1.4"
libnums      = [3, 1, 29, 3, 0]
LICENSE      = "BSD"
AUTHORS      = "Academy Software Foundation"
ARCHIVE      = f"Imath-{VERSION}.tar.gz"
URL          = f"https://github.com/AcademySoftwareFoundation/Imath/archive/refs/tags/v{VERSION}.tar.gz"
ORIGIN_TREE  = "pbj"
EXPORT_LIBS  = ["Imath"]

def lib_names (name, vnums):
    (a, b, c, d, e) = vnums
    return [f"$BUILD_ROOT/lib/lib{name}-{a}_{b}.{c}.dylib",
            f"$BUILD_ROOT/lib/lib{name}-{a}_{b}.{c}.{d}.{e}.dylib",
            f"$BUILD_ROOT/lib/lib{name}-{a}_{b}.dylib",
            f"$BUILD_ROOT/lib/lib{name}.dylib"]

TARGET = lib_names("Imath", libnums) + ["$BUILD_ROOT/include/Imath"]
