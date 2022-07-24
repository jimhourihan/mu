PROJECT      = "utfcpp"
TYPE         = Types.COMPONENT_LIBRARIES
BUILD_SYSTEM = BuildTypes.CMAKE
VERSION      = "3.2.1"
LICENSE      = "Boost"
AUTHORS      = "Nemanja Trifunovic"
ARCHIVE      = f"utfcpp-{VERSION}.tar.gz"
URL          = f"https://github.com/nemtrif/utfcpp/archive/refs/v{VERSION}/{ARCHIVE}"
ORIGIN_TREE  = "pbj"
EXPORT_LIBS  = []
TARGET       = ["$BUILD_ROOT/include/utf8cpp"]

CONFIGURE_OPTIONS  = ["-DUTF8_TESTS=OFF", "-DUTF8_SAMPLES=OFF"] 