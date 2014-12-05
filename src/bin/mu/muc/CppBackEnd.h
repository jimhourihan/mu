#ifndef __muc__CppBackEnd__h__
#define __muc__CppBackEnd__h__
//
//	Copyright (c) 2005 Jim Hourihan
//
//	The coded instructions herein are the sole property of 
//	Jim Hourihan and may not be modified, redistributed, or 
//	used without permission.
//
#include <Mu/Function.h>
#include <Mu/GlobalVariable.h>
#include <Mu/MachineRep.h>
#include <Mu/Module.h>
#include <Mu/Name.h>
#include <Mu/Namespace.h>
#include <Mu/Namespace.h>
#include <Mu/Node.h>
#include <Mu/ParameterVariable.h>
#include <Mu/Process.h>
#include <Mu/Signature.h>
#include <Mu/SymbolTable.h>
#include <Mu/TupleType.h>
#include <Mu/Type.h>
#include <MuLang/DynamicArrayType.h>
#include <MuLang/FixedArrayType.h>
#include <MuLang/MuLangContext.h>
#include <MuLang/StringType.h>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stl_ext/stl_ext_algo.h>

//
//  cppbackend
//
//  This class implements a back end that outputs to a C++ source
//  file.  It basically tries to mimic the structure of a manually
//  created Mu native module or type source file.
//
//  The output file should be compiled into a .so file. There will be
//  an extern function "MuInitialize" which can be called by the
//  Module class to generate symbols in a context.
//

class CppBackEnd
{
public:

    //
    //  Types
    //

    typedef Mu::STLVector<const Mu::Symbol*>::Type   Symbols;
    typedef Mu::SymbolTable::SymbolHashTable         HT;
    typedef Mu::STLSet<const Mu::Function*>::Type    FunctionSet;
    typedef Mu::STLVector<const Mu::Function*>::Type FunctionVector;
    typedef Mu::STLVector<const Mu::Module*>::Type   Modules;
    typedef Mu::STLVector<const Mu::Variable*>::Type Variables;
    typedef Mu::STLSet<const Mu::Namespace*>::Type   NamespaceSet;
    typedef Mu::STLVector<const Mu::Class*>::Type    ClassVector;
    typedef Mu::STLSet<const Mu::Class*>::Type       ConstClassSet;
    typedef Mu::STLSet<const Mu::Type*>::Type        TypeSet;
    typedef Mu::STLVector<const Mu::Type*>::Type     TypeVector;
    typedef Mu::STLVector<const Mu::Node*>::Type     NodeVector;
    typedef Mu::STLSet<const Mu::Node*>::Type        NodeSet;
    typedef Mu::STLSet<const Mu::Signature*>::Type   SignatureSet;

    CppBackEnd(const Mu::String&,
               Mu::Process*,
               Mu::MuLangContext*,
               const Symbols& rootSymbols,
               bool verbose);

private:
    //
    //  These produce strings that will need to be assembled before
    //  output.
    //

    Mu::String nativeConstant(const Mu::Node*);
    Mu::String nativeConstant(const Mu::Node*, 
                               const Mu::Type*, 
                               Mu::ValuePointer,
                               const char* ns=0);
    Mu::String outputCall(const char*, 
                          const Mu::Node*, 
                          const char* ns=0,
                          bool cps=true, 
                          const char* extraArgs=0,
                          int argOffset=0);
    Mu::String nativeExpr(const Mu::Node*);
    Mu::String setupArgVector(const Mu::Node*);
    //
    //  These are used to collect/cache various state
    //

    void collectVariables(const Mu::Symbol*, Variables&);
    void collectFunctions(const Mu::Symbol*, FunctionSet&);
    void collectTypes(const Mu::Symbol*);
    void collectTypes(const Mu::Node*);
    void collectDynamicCalls(const Mu::Node*);
    void collectConstants(const Mu::Node*, NodeSet&);
    void collectState(const Symbols&);
    void collectModuleFunctions(const Mu::Module*, FunctionSet&);
    void declareStackVariables(const Variables& vars);
    void declareConstants(const NodeSet&);

    //
    //  Output functions
    //

    void writeCppStructs(std::ostream&);
    void writeNativeFunctionHeader(std::ostream&, const Mu::Function*);
    void writeNodeFunctionDeclaration(std::ostream&, const Mu::Function*);
    void writeNativeFunction(std::ostream&, const Mu::Function*);
    void writeNodeFunction(std::ostream&, const Mu::Function*);
    void writeFunctions(std::ostream&, const FunctionSet&);
    void writeFileHeaderInfo(std::ostream&);
    void writeStaticGlobals(std::ostream&);
    void writeStaticGlobalConstructors(std::ostream&);
    void writeInlineDepFunctions(std::ostream&);
    void writeModuleDeclaration(std::ostream&, const Mu::Module*);
    void writeCPPInstanceStruct(std::ostream&, const Mu::Class*);
    void writeNamespaceConstructor(std::ostream&, const Mu::Namespace*);
    void writeFunctionConstructor(std::ostream&, const Mu::Function*);
    void writeFunctionConstructorWithScope(std::ostream&, const Mu::Function*);
    void writeSymbolContents(std::ostream&, const Mu::Symbol*);
    void writeModuleLoad(std::ostream&, const Mu::Module*, const FunctionSet&);
    void writeModuleInit(std::ostream&, const Modules&);

    void cppType(std::ostream& out,
                 const Mu::Type* t,
                 bool constant=true);

    void nameAssign(std::ostream& out,
                    const Mu::Type* t,
                    const Mu::String& name,
                    bool constant=true,
                    bool equals=true);

    void nodeAssign(std::ostream& out,
                    const Mu::Node* node, 
                    const Mu::Type* t=0,
                    const char* ns=0,
                    bool constant=true,
                    bool equals=true);

private:
    std::ofstream      m_out;
    Mu::Process*       m_process;
    Mu::MuLangContext* m_context;
    const Symbols&     m_inputSymbols;
    FunctionSet        m_allFunctions;
    FunctionSet        m_rootFunctions;
    NamespaceSet       m_outputNamespaces;
    Modules            m_rootModules;
    ConstClassSet      m_constantClasses;
    TypeSet            m_depTypeSet;
    TypeVector         m_depTypes;
    NodeVector         m_dynCalls;
    NodeSet            m_globals;
    bool               m_verbose;
};


#endif // __muc__CppBackEnd__h__
