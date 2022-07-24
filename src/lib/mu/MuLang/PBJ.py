PROJECT = "MuLang"
TYPE    = Types.LIBRARY
LIBS    = ["Mu", "Imath", "stl_ext", "gc"]
USES    = ["reflex", "bison", "boehm_gc", "utfcpp"]

CXX_FLAGS = ["-Wno-deprecated-declarations"]
CXX_FILES = ["BoolType.cpp", "FixedArrayType.cpp",
             "MuLangContext.cpp", "StringType.cpp", "ByteType.cpp",
             "FloatType.cpp", "MuLangLanguage.cpp", "TypePattern.cpp",
             "CharType.cpp", "HalfType.cpp", "NameType.cpp", "VectorType.cpp",
             "DoubleType.cpp", "Int64Type.cpp", "Noise.cpp",
             "VectorTypeModifier.cpp", "DynamicArray.cpp", "IntType.cpp",
             "ObjectInterface.cpp", "VoidType.cpp", "DynamicArrayType.cpp",
             "InteractiveSession.cpp", "RegexType.cpp", "ExceptionType.cpp",
             "MathModule.cpp", "RuntimeModule.cpp", "FixedArray.cpp",
             "MathUtilModule.cpp", "ShortType.cpp"]

PREFIX        = "MUYY"
BISON_FILES   = ["MuGrammar.y"]
REFLEX_FILES  = ["MuLexer.l"]


