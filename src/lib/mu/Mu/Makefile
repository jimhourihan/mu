#  -*- mode: makefile -*-
# 
#  Copyright (C) 2001  Jim Hourihan
# 
#  The coded instructions herein are the sole property of Jim Hourihan
#  and may not be modified, redistributed, or used without permission.
# 

PROJECT	   = Mu
TYPE       = LIBRARY

CXXFILES   =    HashTable           StringHashTable     Name                \
                Symbol              SymbolTable         Namespace           \
                Node                Object              Type                \
                TypePattern         Function            PrimitiveType       \
                Variable            StackVariable       GlobalVariable      \
                Context             Process             Thread              \
                NodeAssembler       NodeVisitor         NodePrinter         \
                BaseFunctions       ReferenceType       Module              \
                MemberVariable      TypeModifier        \
                MachineRep          MemberFunction      Class               \
                ClassInstance       ParameterVariable   Exception           \
                NodePatch           SymbolicConstant    Environment         \
                Alias               GarbageCollector    Signature           \
                FunctionType        FunctionObject      Interface           \
                InterfaceImp        Archive             NilType             \
                Language            PartialApplicator   FunctionSpecializer \
                Unresolved          FreeVariable        NodeSimplifier      \
                TupleType           ParameterModifier   UTF8		    \
                TypeVariable        VariantType         VariantTagType	    \
                VariantInstance	    List		ListType	    \
		StructType	    OpaqueType		SymbolType	    \
		ASTNode

LIBS         = Half stl_ext gc 

EXCLUDE_SRCDIR_FROM_IPATH = true

include $(SRC_ROOT)/build/Makefile.master

