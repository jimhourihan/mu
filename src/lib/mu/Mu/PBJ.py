PROJECT	   = "Mu"
TYPE       = Types.LIBRARY

CXX_FILES = ["HashTable.cpp", "StringHashTable.cpp", "Name.cpp",
             "Symbol.cpp", "SymbolTable.cpp", "Namespace.cpp", "Node.cpp",
             "Object.cpp", "Type.cpp", "TypePattern.cpp", "Function.cpp",
             "PrimitiveType.cpp", "Variable.cpp", "StackVariable.cpp",
             "GlobalVariable.cpp", "Context.cpp", "Process.cpp",
             "Thread.cpp", "NodeAssembler.cpp", "NodeVisitor.cpp",
             "NodePrinter.cpp", "BaseFunctions.cpp", "ReferenceType.cpp",
             "Module.cpp", "Construct.cpp", "MemberVariable.cpp",
             "TypeModifier.cpp", "MachineRep.cpp", "MemberFunction.cpp",
             "Class.cpp", "ClassInstance.cpp", "ParameterVariable.cpp",
             "Exception.cpp", "NodePatch.cpp", "SymbolicConstant.cpp",
             "Environment.cpp", "Alias.cpp", "GarbageCollector.cpp",
             "Signature.cpp", "FunctionType.cpp", "FunctionObject.cpp",
             "Interface.cpp", "InterfaceImp.cpp", "Archive.cpp",
             "NilType.cpp", "Language.cpp", "PartialApplicator.cpp",
             "FunctionSpecializer.cpp", "Unresolved.cpp",
             "FreeVariable.cpp", "NodeSimplifier.cpp", "TupleType.cpp",
             "ParameterModifier.cpp", "UTF8.cpp", "TypeVariable.cpp",
             "VariantType.cpp", "VariantTagType.cpp",
             "VariantInstance.cpp", "List.cpp", "ListType.cpp",
             "StructType.cpp", "OpaqueType.cpp", "SymbolType.cpp",
             "ASTNode.cpp"]

LIBS = ["Imath", "stl_ext", "gc"]
USES = ["boehm_gc", "utfcpp"]

# GC_malloc_stubborn and GC_change_stubborn are deprecated
# but not sure how to replace them yet.
CXX_FLAGS = ["-Wno-deprecated-declarations"]

EXCLUDE_SRCDIR_FROM_IPATH = True

