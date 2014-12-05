//******************************************************************************
// Copyright (c) 2005 Tweak Inc. 
// All rights reserved.
//******************************************************************************
#include "CppBackEnd.h"
#include <Mu/Name.h>
#include <Mu/ReferenceType.h>
#include <Mu/TupleType.h>
#include <Mu/FreeVariable.h>
#include <Mu/FunctionType.h>
#include <Mu/FunctionObject.h>
#include <MuLang/DynamicArrayType.h>
#include <MuLang/FixedArrayType.h>
#include <MuLang/FixedArray.h>
#include <MuLang/DynamicArray.h>
#include <MuLang/RegexType.h>
#include <Mu/MemberVariable.h>

using namespace std;
using namespace Mu;
using namespace stl_ext;

CppBackEnd::CppBackEnd(const String& filename,
                       Mu::Process* p,
                       Mu::MuLangContext* c,
                       const Symbols& symbols,
                       bool verbose)
    : m_inputSymbols(symbols),
      m_context(c),
      m_process(p),
      m_out(filename.c_str()),
      m_verbose(verbose)
{
    if (!m_out) throw "bad";

    collectState(symbols);
    writeFileHeaderInfo(m_out);
    writeStaticGlobals(m_out);
    writeInlineDepFunctions(m_out);

    for (int i=0; i < m_rootModules.size(); i++)
    {
        const Module* m = m_rootModules[i];
        FunctionSet funcs;

        writeModuleDeclaration(m_out, m);
        writeCppStructs(m_out);
        collectModuleFunctions(m, funcs);
        writeFunctions(m_out, m_allFunctions);
        writeModuleLoad(m_out, m, funcs);
    }

    writeModuleInit(m_out, m_rootModules);
}


void
CppBackEnd::cppType(ostream& out, const Type* t, bool constant)
{
    const Type* d = 0;
    bool ref = t->isReferenceType();
    bool refprim = false;

    if (ref) 
    {
        d = ((ReferenceType*)t)->dereferenceType();
        refprim = d->isPrimitiveType();
    }

    if (ref /*|| t->machineRep() == PointerRep::rep()*/) constant = false;

    if (constant) out << "const ";
    out << (refprim ? d->machineRep()->name() : t->machineRep()->name())
        << (refprim ? "& " : " ");
}

void
CppBackEnd::nameAssign(ostream& out,
                       const Type* t,
                       const String& name,
                       bool constant,
                       bool equals)
{
    cppType(out, t, constant);
    out << name;
    if (equals) out << " = ";
}

void
CppBackEnd::nodeAssign(ostream& out,
                       const Node* node, 
                       const Type* t,
                       const char* ns,
                       bool constant,
                       bool equals)
{
    const Type* ta = t ? t : node->type();
    String name = node->mangledId();

    nameAssign(out, ta, ns ? (name + ns) : name, constant, equals);
}

String
CppBackEnd::nativeConstant(const Node* node,
                           const Type* t,
                           const ValuePointer p,
                           const char* ns)
{
    ostringstream out;

    if (t == m_context->stringType())
    {
        nodeAssign(out, node, t, ns);
        out << "MU_NEW_STRING(";
        t->outputValue(out, p);
        out << ");\n";
    }
    else if (t == m_context->regexType())
    {
        nodeAssign(out, node, t, ns);
        RegexType::Regex** r = reinterpret_cast<RegexType::Regex**>(p);
        out << "MU_NEW_REGEX(";
        StringType::outputQuotedString(out, (*r)->string());
        out << ", " << (*r)->flags() << ");\n";
    }
    else if (t == m_context->vec2fType())
    {
        nodeAssign(out, node, t, ns);
        const Vector2f* vp = 
            reinterpret_cast<const Vector2f*>(p);

        out << "constructVector<float,2>(" << (*vp)[0]
            << ", " << (*vp)[1]
            << ");\n";
    }
    else if (t == m_context->vec3fType())
    {
        nodeAssign(out, node, t, ns);
        const Vector3f* vp = 
            reinterpret_cast<const Vector3f*>(p);

        out << "constructVector<float,3>(" << (*vp)[0]
            << ", " << (*vp)[1]
            << ", " << (*vp)[2]
            << ");\n";
    }
    else if (t == m_context->vec4fType())
    {
        nodeAssign(out, node, t, ns);
        const Vector4f* vp = 
            reinterpret_cast<const Vector4f*>(p);

        out << "constructVector<float,4>(" << (*vp)[0]
            << ", " << (*vp)[1]
            << ", " << (*vp)[2]
            << ", " << (*vp)[3]
            << ");\n";
    }
    else if (t->isPrimitiveType())
    {
        nodeAssign(out, node, t, ns);
        t->outputValue(out, p);
        out << ";\n";
    }
    else if (const FunctionType* f =
             dynamic_cast<const FunctionType*>(t))
    {
        if (FunctionObject* o =
            *reinterpret_cast<FunctionObject**>(p))
        {
            if (const Function* F = o->function())
            {
                if (F->isLambda())
                {
                    out << "Function* " << F->mangledId() << " = ";
                    writeFunctionConstructor(out, F);
                    out << ";" << endl;

                    out << "s->addAnonymousSymbol("
                        << F->mangledId()
                        << ");" << endl;
                }
                else
                {
                    out << "const Function* " << F->mangledId() << " = ";
                    out << "c->findSymbolOfTypeByMangledName<Function>(\""
                        << F->mangledName()
                        << "\",Symbol::internName(\""
                        << F->fullyQualifiedName()
                        << "\"));\n";

                }
            
                nodeAssign(out, node, t, ns);

                out << "MU_NEW_FUNCTIONOBJ(" 
                    << F->mangledId()
                    << ");\n";
            }
        }
    }
    else if (const Class* c = dynamic_cast<const Class*>(t))
    {
        ClassInstance* o =
            *reinterpret_cast<ClassInstance**>(p);

        if (t->isSequence())
        {
            if (const DynamicArrayType* a = 
                dynamic_cast<const DynamicArrayType*>(t))
            {
                DynamicArray* array = static_cast<DynamicArray*>(o);
                const Type* etype = a->elementType();
                size_t size = array->size();

                for (int i=0; i < size; i++)
                {
                    ostringstream nout;
                    nout << (ns ? ns : "")
                         << "_" << i;

                    out << nativeConstant(node, 
                                          etype, 
                                          (ValuePointer)array->elementPointer(i),
                                          nout.str().c_str());
                }

                out << "DynamicArray* " << node->mangledId()
                    << " = new DynamicArray(NODE_THREAD, \""
                    << t->fullyQualifiedName()
                    << "\");\n"
                    << node->mangledId()
                    << "->resize(" << size << ");\n";

                for (int i=0; i < size; i++)
                {
                    ostringstream nout;
                    nout << (ns ? ns : "")
                         << "_" << i;
                    
                    out << node->mangledId() << "->element<"
                        << etype->machineRep()->name()
                        << ">(" << i << ") = "
                        << node->mangledId()
                        << nout.str().c_str()
                        << ";\n";
                }
            }
            else if (const FixedArrayType* a = 
                     dynamic_cast<const FixedArrayType*>(t))
            {
                FixedArray* array = static_cast<FixedArray*>(o);
                const Type* etype = a->elementType();
                size_t size = array->size();
                
                for (int i=0; i < size; i++)
                {
                    ostringstream nout;
                    nout << (ns ? ns : "")
                         << "_" << i;
                    
                    out << nativeConstant(node, 
                                          etype, 
                                          (ValuePointer)array->elementPointer(i),
                                          nout.str().c_str());
                }
                
                out << "FixedArray* " << node->mangledId()
                    << " = static_cast<FixedArray*>(MU_ALLOC_INSTANCE(NODE_THREAD, \""
                    << t->fullyQualifiedName()
                    << "\",0));\n";
                
                for (int i=0; i < size; i++)
                {
                    ostringstream nout;
                    nout << (ns ? ns : "")
                         << "_" << i;
                    
                    out << node->mangledId() << "->element<"
                        << etype->machineRep()->name()
                        << ">(" << i << ") = "
                        << node->mangledId()
                        << nout.str().c_str()
                        << ";\n";
                }
            }
        }
        else if (t->isFixedSize())
        {
            //
            //  It would be much better to allocate *first* and then
            //  fill in the memory directly instead of making a copy
            //  the way this code does. A new ClassInstance::allocator
            //  call would be needed.
            //

            const Type* ft = 0;
            for (int i=0; ft = o->fieldType(i); i++)
            {
                ostringstream nout;
                nout << (ns ? ns : "")
                     << "_" << i;

                out << nativeConstant(node, ft, o->field(i),
                                      nout.str().c_str());
            }

            String structname = "new ";
            structname += t->mangledName();
            structname += "_S";

            nodeAssign(out, node, t, ns, true, false); // no const, no rval

            out << "_S = "
                << structname
                << "(";

            for (int i=0; ft = o->fieldType(i); i++)
            {
                ostringstream nout;
                nout << node->mangledId()
                     << (ns ? ns : "")
                     << "_" << i;

                if (i) out << ", ";
                out << nout.str();
            }

            out << ");\n";

            nodeAssign(out, node, t, ns, true, false); // no const, no rval

            string tn = "\"";
            tn += t->fullyQualifiedName().c_str();
            tn += "\"";

            out << " = "
                << "MU_ALLOC_INSTANCE(NODE_THREAD, "
                << tn
                << ", "
                << node->mangledId()
                << (ns ? ns : "")
                << "_S"
                << ");\n";
        }
        else
        {
            // dynamically sized
            abort();
        }

        m_constantClasses.insert(c);
    }

    return out.str().c_str();
}

Mu::String
CppBackEnd::nativeConstant(const Node* node)
{
    const Type* t = static_cast<const Type*>(node->symbol());
    const DataNode* dn = static_cast<const DataNode*>(node);
    ostringstream out;

    collectTypes(t);

    if (t == m_context->vec2fType())
    {
        return nativeConstant(node,
                              t,
                              (ValuePointer)&dn->_data._Vector2f);
    }
    else if (t == m_context->vec3fType())
    {
        return nativeConstant(node,
                              t,
                              (ValuePointer)&dn->_data._Vector3f);
    }
    else if (t == m_context->vec4fType())
    {
        return nativeConstant(node,
                              t,
                              (ValuePointer)&dn->_data._Vector4f);
    }
    else if (t->isPrimitiveType())
    {
        nodeAssign(out, node);
        t->outputValue(out, dn->_data);
        out << ";\n";
    }
    else
    {
        return nativeConstant(node, 
                              t,
                              (ValuePointer)&dn->_data._Pointer);
    }

    return out.str().c_str();
}

Mu::String
CppBackEnd::outputCall(const char* name, 
                       const Node* node, 
                       const char* ns,
                       bool cps,
                       const char* extraArgs,
                       int argOffset)
{
    ostringstream out;

    for (int q=argOffset; q < node->numArgs(); q++)
    {
        out << nativeExpr(node->argNode(q));
    }

    const Type* t   = node->type();
    const Symbol* s = node->symbol();

    if (t->machineRep() != VoidRep::rep())
    {
        nodeAssign(out, node, 0, ns);
    }

    out << name << "(";

    if (cps) out << "NODE_THREAD";

    if (extraArgs) 
    {
        if (cps) out << ", " << extraArgs;
    }

    for (int q=argOffset; q < node->numArgs(); q++)
    {
        if (q || cps || extraArgs) out << ", ";
        out << node->argNode(q)->mangledId();
    }

    out << ");\n";

    return out.str().c_str();
}

Mu::String
CppBackEnd::setupArgVector(const Node* node)
{
    ostringstream out;

    out << nativeExpr(node->argNode(1));
    out << "FunctionObject* __in = reinterpret_cast<FunctionObject*>("
        << node->argNode(1)->mangledId()
        << ");\n";

    out << "const Function* __F = reinterpret_cast<const FunctionObject*>(__in)->function();\n";

    out << "Function::ArgumentVector __args(" 
        << (node->numArgs() - 2)
        << ");\n";

    out << "std::vector<bool> __mask("
        << (node->numArgs() - 2)
        << ");\n";
    
    for (int i=2; i < node->numArgs(); i++)
    {
        const Node* arg = node->argNode(i);
        bool exists = arg->symbol() != m_context->noop();
        const char* mval = exists ? "true" : "false";
        
        if (exists)
        {

            out << nativeExpr(arg)
                << "__args[" << (i-2)  
                << "]._" << arg->type()->machineRep()->name()
                << " = " << arg->mangledId() 
                << ";\n";
        }

        out << "__mask[" << (i-2) << "] = " << mval << ";\n";
    }

    return out.str().c_str();
}

Mu::String
CppBackEnd::nativeExpr(const Node* node)
{
    const Symbol* s = node->symbol();
    ostringstream out;

    if (const Function* f = dynamic_cast<const Function*>(s))
    {
        if (f == m_context->simpleBlock())
        {
            for (int i=0; i < node->numArgs(); i++)
            {
                const Node* a = node->argNode(i);

                if (a->symbol() != m_context->simpleBlock())
                {
                    out << nativeExpr(a);
                }
                else
                {
                    out << "{\n" << nativeExpr(a) << "}\n";
                }
            }
        }
        else if (f == m_context->returnFromFunction())
        {
            out << nativeExpr(node->argNode(0));
            out << "return " << node->argNode(0)->mangledId() << ";\n";
        }
        else if (f == m_context->returnFromVoidFunction())
        {
            out << nativeExpr(node->argNode(0));
            out << "return;\n";
        }
        else if (f->isConstructor())
        {
            if (const TupleType* tt = 
                dynamic_cast<const TupleType*>(f->returnType()))
            {
                String tn = "\"";
                tn += tt->name().c_str();
                tn += "\"";

                String structname = "new ";
                structname += tt->mangledName();
                structname += "_S";

                out << outputCall(structname.c_str(), node, "_S", false);

                nodeAssign(out, node);

                out << "MU_ALLOC_INSTANCE(NODE_THREAD, "
                    << tn
                    << ", "
                    << node->mangledId()
                    << "_S);\n";
            }
            else if (const FixedArrayType* a =
                     dynamic_cast<const FixedArrayType*>(f->returnType()))
            {
                const Type* e = a->elementType();

                for (int q=0; q < node->numArgs(); q++)
                {
                    out << nativeExpr(node->argNode(q));
                }

                out << "FixedArray* " << node->mangledId()
                    << " = static_cast<FixedArray*>(MU_ALLOC_INSTANCE(NODE_THREAD, \""
                    << a->fullyQualifiedName()
                    << "\",0));\n";
                
                for (int q=0; q < node->numArgs(); q++)
                {
                    out << node->mangledId()
                        << "->element<" << e->machineRep()->name()
                        << ">(" << q << ") = "
                        << node->argNode(q)->mangledId()
                        << ";\n";
                }
            }
            else if (const DynamicArrayType* a =
                     dynamic_cast<const DynamicArrayType*>(f->returnType()))
            {
                const Type* e = a->elementType();

                for (int q=0; q < node->numArgs(); q++)
                {
                    out << nativeExpr(node->argNode(q));
                }

                out << "DynamicArray* " << node->mangledId() 
                    << " = new DynamicArray(NODE_THREAD, \""
                    << a->fullyQualifiedName()
                    << "\");\n";
                
                out << node->mangledId()
                    << "->resize(" << node->numArgs()
                    << ");\n";

                for (int q=0; q < node->numArgs(); q++)
                {
                    out << node->mangledId()
                        << "->element<" << e->machineRep()->name()
                        << ">(" << q << ") = "
                        << node->argNode(q)->mangledId()
                        << ";\n";
                }
            }
            else if (f->returnType() == m_context->vec2fType())
            {
                for (int q=0; q < node->numArgs(); q++)
                {
                    out << nativeExpr(node->argNode(q));
                }

                nodeAssign(out, node);
                
                out << "constructVector<float,2>(" 
                    << node->argNode(0)->mangledId()
                    << ", " 
                    << node->argNode(1)->mangledId()
                    << ");\n";
            }
            else if (f->returnType() == m_context->vec3fType())
            {
                for (int q=0; q < node->numArgs(); q++)
                {
                    out << nativeExpr(node->argNode(q));
                }

                nodeAssign(out, node);
                
                out << "constructVector<float,3>(" 
                    << node->argNode(0)->mangledId()
                    << ", " 
                    << node->argNode(1)->mangledId()
                    << ", " 
                    << node->argNode(2)->mangledId()
                    << ");\n";
            }
            else if (f->returnType() == m_context->vec4fType())
            {
                for (int q=0; q < node->numArgs(); q++)
                {
                    out << nativeExpr(node->argNode(q));
                }

                nodeAssign(out, node);
                
                out << "constructVector<float,4>(" 
                    << node->argNode(0)->mangledId()
                    << ", " 
                    << node->argNode(1)->mangledId()
                    << ", " 
                    << node->argNode(2)->mangledId()
                    << ", " 
                    << node->argNode(3)->mangledId()
                    << ");\n";
            }
            else
            {
                out << outputCall(f->mangledName().c_str(), node);
            }
        }
        else if (f == m_context->dynamicPartialApply())
        {
            //
            //  Now uses "curry" below
            //

            nodeAssign(out, node, 0, 0, false, false);

            out << ";\n{\n"
                << setupArgVector(node)
                << "PartialApplicator __pa(__F, NODE_THREAD.process(), &NODE_THREAD, __args, __mask);\n"
                << "Function* __nF = __pa.result();\n"
                << "FunctionObject* __out = MU_NEW_FUNCTIONOBJ(__nF);\n"
                << "__out->setDependent(__in);\n"
                << node->mangledId() << " = __out;\n"
                << "}\n";
            
        }
        else if (f == m_context->dynamicPartialEval())
        {
            //
            //  Now uses "curry" below
            //

            nodeAssign(out, node, 0, 0, false, false);

            out << ";\n{\n"
                << setupArgVector(node)
                << "FunctionSpecializer __fs(__F, NODE_THREAD.process(), &NODE_THREAD);\n"
                << "__fs.partiallyEvaluate(__args, __mask);\n"
                << "Function* __nF = __fs.result();\n"
                << node->mangledId() << " = MU_NEW_FUNCTIONOBJ(__nF);\n"
                << "}\n";
        }
        else if (f == m_context->curry())
        {
            nodeAssign(out, node, 0, 0, false, false);

            out << ";\n{\n"
                << setupArgVector(node)
                << node->mangledId() << " = Curry::evaluate(NODE_THREAD,__in,__args,__mask);\n"
                << "}\n";
        }
        else if (f->name() == "__if")
        {
            out << nativeExpr(node->argNode(0));

            out << "if ("
                << node->argNode(0)->mangledId()
                << ")\n{\n"
                << nativeExpr(node->argNode(1))
                << "\n}\n";

            if (node->numArgs() == 3)
            {
                out << "else\n{\n"
                    << nativeExpr(node->argNode(2))
                    << "\n}\n";
            }
        }
        else if (f->name() == "?:")
        {
            nodeAssign(out, node, 0, 0, false, false);
            out << ";\n";
                
            out << nativeExpr(node->argNode(0))
                << "if (" << node->argNode(0)->mangledId() << ")\n{\n"
                << nativeExpr(node->argNode(1))
                << node->mangledId()
                << " = "
                << node->argNode(1)->mangledId()
                << ";\n}\nelse\n{\n"
                << nativeExpr(node->argNode(2))
                << node->mangledId()
                << " = "
                << node->argNode(2)->mangledId()
                << ";\n}\n";
        }
        else if (f->name() == "__for")
        {
            out << nativeExpr(node->argNode(0))
                << "for(;;)\n{\n"
                << nativeExpr(node->argNode(1))
                << "if (!(" << node->argNode(1)->mangledId()
                << ")) break;\n"
                << nativeExpr(node->argNode(3))
                << nativeExpr(node->argNode(2))
                << "}\n";
        }
        else if (f->name() == "__while")
        {
            out << "for(;;)\n{\n"
                << nativeExpr(node->argNode(0))
                << "if (!(" << node->argNode(0)->mangledId()
                << ")) break;\n"
                << nativeExpr(node->argNode(1))
                << "}\n";
        }
        else if (f->name() == "__do_while")
        {
            out << "for(;;)\n{\n"
                << nativeExpr(node->argNode(0))
                << nativeExpr(node->argNode(1))
                << "if (!(" << node->argNode(1)->mangledId()
                << ")) break;\n"
                << "}\n";
        }
        else if (f->name() == "__repeat")
        {
            out << nativeExpr(node->argNode(0))
                << "for (unsigned int __r__=0; __r__<"
                << node->argNode(0)->mangledId()
                << "; __r__++)\n{\n"
                << nativeExpr(node->argNode(1))
                << ";\n}\n";
        }
        else if (f->name() == "__break")
        {
            out << "break";
            out << ";";
        }
        else if (f->name() == "__continue")
        {
            out << "continue";
            out << ";";
        }
        else if (f->name() == "[]")
        {
            if (const DynamicArrayType* a = 
                dynamic_cast<const DynamicArrayType*>(f->argType(0)))
            {
                for (int i=0; i < node->numArgs(); i++)
                {
                    out << nativeExpr(node->argNode(i));
                }

                nodeAssign(out, node);

                out << "reinterpret_cast<DynamicArray*>(" 
                    << node->argNode(0)->mangledId()
                    << ")->element<"
                    << a->elementType()->machineRep()->name()
                    << ">("; 

                for (int i=1; i < node->numArgs(); i++)
                {
                    if (i > 1) out << ",";
                    out << node->argNode(i)->mangledId();
                }

                out << ");\n";
            }
            else if (const FixedArrayType* a = 
                dynamic_cast<const FixedArrayType*>(f->argType(0)))
            {
                for (int i=0; i < node->numArgs(); i++)
                {
                    out << nativeExpr(node->argNode(i));
                }

                nodeAssign(out, node);

                out << "reinterpret_cast<FixedArray*>(" 
                    << node->argNode(0)->mangledId()
                    << ")->element<"
                    << a->elementType()->machineRep()->name()
                    << ">("; 

                for (int i=1; i < node->numArgs(); i++)
                {
                    if (i > 1) out << ",";
                    out << node->argNode(i)->mangledId();
                }

                out << ");\n";
            }
            else
            {
                out << outputCall(f->mangledName().c_str(), node);
            }
        }
        else if (f->name() == "()")
        {
            const Node* arg0 = node->argNode(0);

            if (dynamic_cast<const FunctionType*>(arg0->symbol()))
            {
                //
                //  Special case : can call directly because this is a
                //  constant.
                //

                const DataNode*       dn = static_cast<const DataNode*>(arg0);
                const Pointer         p  = dn->_data._Pointer;
                const FunctionObject* fo = reinterpret_cast<const FunctionObject*>(p);
                const Function*       pf = fo->function();

                out << outputCall(pf->mangledName().c_str(), node, 0, true, 0, 1);
            }
            else
            {
                //
                //  Dynamic call (through interpreter)
                //

                out << outputCall(f->mangledName().c_str(), node);
            }
        }
        else if (f->name() == "size" && f->numArgs() == 1)
        {
            if (const DynamicArrayType* a = 
                dynamic_cast<const DynamicArrayType*>(f->argType(0)))
            {
                out << nativeExpr(node->argNode(0));
                nodeAssign(out, node);
                out << "reinterpret_cast<const DynamicArray*>("
                    << node->argNode(0)->mangledId() << ")->"
                    << f->name() << "();\n";
            }
            else if (const FixedArrayType* a = 
                dynamic_cast<const FixedArrayType*>(f->argType(0)))
            {
                out << nativeExpr(node->argNode(0));
                nodeAssign(out, node);
                out << "reinterpret_cast<const FixedArray*>("
                    << node->argNode(0)->mangledId() << ")->"
                    << f->name() << "();\n";
            }
            else
            {
                out << outputCall(f->mangledName().c_str(), node);
            }
        }
        else
        {
            //
            //  General function call
            //

            out << outputCall(f->mangledName().c_str(), node);
        }
    }
    else if (const Variable* v = dynamic_cast<const Variable*>(s))
    {
        const Type* t = node->type();

        if (const MemberVariable* mv =
            dynamic_cast<const MemberVariable*>(v))
        {
            String m = node->argNode(0)->type()->mangledName();
            m += "_S";

            out << nativeExpr(node->argNode(0));
            nodeAssign(out, node);
            out << "reinterpret_cast<ClassInstance*>("
                << node->argNode(0)->mangledId()
                << ")->data<" 
                << m 
                << ">()->"
                << mv->name().c_str()
                << ";\n";
        }
        else
        {
            nodeAssign(out, node);

            if (t->isReferenceType())
            {
                const ReferenceType* rt = static_cast<const ReferenceType*>(t);
                
                if (!rt->dereferenceType()->isPrimitiveType())
                {
                    out << "&";
                }
            }
            
            out << v->mangledName();

            out << ";\n";
        }
    }
    else if (const Type* t = dynamic_cast<const Type*>(s))
    {
        if (t->isPrimitiveType())
        {
            out << nativeConstant(node);
        }
        else
        {
            nodeAssign(out, node);
            out << "globals.c" << node->mangledId()
                << ";\n";
        }
    }
    else
    {
        abort();
    }

    return out.str().c_str();
}

//----------------------------------------------------------------------

void
CppBackEnd::collectVariables(const Symbol* S, Variables& vars)
{
    if (S->symbolTable())
    {
	HT& table = S->symbolTable()->hashTable();

	for (HT::Iterator i(table); i; ++i) 
        {
            if (Variable* v = dynamic_cast<Variable*>(*i))
            {
                if (StackVariable* sv = dynamic_cast<StackVariable*>(v))
                {
                    if (!dynamic_cast<ParameterVariable*>(sv))
                    {
                        vars.push_back(v);
                    }
                }
                else if (GlobalVariable* gv = dynamic_cast<GlobalVariable*>(v))
                {
                    vars.push_back(v);
                }
            }
            else if (Namespace* ns = dynamic_cast<Namespace*>(*i))
            {
                collectVariables(ns, vars);
            }
        }
    }
}

void
CppBackEnd::collectFunctions(const Symbol* S, FunctionSet& funcs)
{
    if (const Function* f = dynamic_cast<const Function*>(S))
    {
        funcs.insert(f);
        if (f->body()) collectTypes(f->body());
    }

    if (S->symbolTable())
    {
	HT& table = S->symbolTable()->hashTable();

	for (HT::Iterator i(table); i; ++i) 
        {
            if (Function* f = dynamic_cast<Function*>(*i))
            {
                funcs.insert(f);
            }

            collectFunctions(*i, funcs);
        }
    }
}

void
CppBackEnd::collectDynamicCalls(const Node* n)
{
    const Symbol* sym = n->symbol();

    if (sym->name() == "()")
    {
        const Node* arg0 = n->argNode(0);

        if (const Type* t = 
            dynamic_cast<const FunctionType*>(arg0->type()))
        {
            m_dynCalls.push_back(n);
        }
    }

    for (int i=0, s=n->numArgs(); i < s; i++)
    {
        collectDynamicCalls(n->argNode(i));
    }
}

void
CppBackEnd::collectConstants(const Node* n, NodeSet& nodeSet)
{
    if (const Type* t = dynamic_cast<const Type*>(n->symbol()))
    {
        const DataNode* dn = static_cast<const DataNode*>(n);

        if (!t->isPrimitiveType()) 
        {
            if (dn->_data._Pointer) nodeSet.insert(n);
        }

        if (const FunctionType* ft = dynamic_cast<const FunctionType*>(t))
        {
            //
            //  This could be an anonymous function or
            //  a reference to a function
            //

            const DataNode* dn = static_cast<const DataNode*>(n);

            if (const Pointer p = dn->_data._Pointer)
            {
                const FunctionObject* fo = reinterpret_cast<const FunctionObject*>(p);
                const Function*       F  = fo->function();

                m_allFunctions.insert(F);
                if (F->body()) collectConstants(F->body(), nodeSet);
            }
        }
    }

    for (int i=0, s=n->numArgs(); i < s; i++)
    {
        collectConstants(n->argNode(i), nodeSet);
    }
}

void
CppBackEnd::collectTypes(const Node* n)
{
    collectTypes(n->type());
    
    for (int i=0, s=n->numArgs(); i < s; i++)
    {
        collectTypes(n->argNode(i));
    }
}

void
CppBackEnd::collectTypes(const Symbol* S)
{
    if (const Type* t = dynamic_cast<const Type*>(S))
    {
        if (t->isPrimitiveType() || 
            t->isReferenceType() ||
            t == m_context->stringType() ||
            t == m_context->regexType())
        {
            return;
        }

        if (m_depTypeSet.find(t) == m_depTypeSet.end())
        {
            m_depTypeSet.insert(t);
            m_depTypes.push_back(t);
        }
        else
        {
            return;
        }
    }

    if (S->symbolTable())
    {
	const HT& table = S->symbolTable()->hashTable();

	for (HT::Iterator i(table); i; ++i) 
        {
            collectTypes(*i);
        }
    }

    Symbol::ConstSymbolVector deps;
    S->symbolDependancies(deps);

    for (int i=0; i < deps.size(); i++) 
    {
        collectTypes(deps[i]);
    }
}

void
CppBackEnd::collectModuleFunctions(const Module* m, FunctionSet& functions)
{
    if (m->symbolTable())
    {
	HT& table = m->symbolTable()->hashTable();

	for (HT::Iterator i(table); i; ++i) 
        {
            if (Function* f = dynamic_cast<Function*>(*i))
            {
                functions.insert(f);
            }
        }
    }
}


void
CppBackEnd::collectState(const Symbols& symbols)
{
    for (int i=0; i < symbols.size(); i++)
    {
        if (const Function* f = dynamic_cast<const Function*>(symbols[i]))
        {
            collectFunctions(symbols[i], m_allFunctions);
        }
        else if (const Module* m = dynamic_cast<const Module*>(symbols[i]))
        {
            m_rootModules.push_back(m);
        }

        collectTypes(symbols[i]);
    }

    if (m_verbose)
    {
        cout << "INFO: ---- dep types ----\n";

        for (int i=0; i < m_depTypes.size(); i++)
        {
            cout << "    " <<  m_depTypes[i]->fullyQualifiedName() << endl;
        }
    }

    for (FunctionSet::iterator i = m_allFunctions.begin();
         i != m_allFunctions.end();
         ++i)
    {
        m_rootFunctions.insert(*i);
    }

    //
    //  Remove all non-root functions from rootFunctions memeber
    //  also find any namespaces that will need to be output
    //

    for (FunctionSet::iterator i = m_allFunctions.begin();
         i != m_allFunctions.end();
         ++i)
    {
        const Function* f = *i;

        for (const Symbol* s = f->scope(); s; s = s->scope())
        {
            //
            //  The function better not have a parent function which
            //  is NOT in allFunctions! 
            //

            if (const Function* pf = dynamic_cast<const Function*>(s))
            {
                if (m_allFunctions.find(pf) != m_allFunctions.end())
                {
                    m_rootFunctions.erase(pf);
                }
            }
            else if (const Namespace* ns = dynamic_cast<const Namespace*>(s))
            {
                m_outputNamespaces.insert(ns);
            }
        }
    }

    //
    //  find constants in the functions
    //

    for (FunctionSet::iterator i = m_allFunctions.begin();
         i != m_allFunctions.end();
         ++i)
    {
        const Node* n = (*i)->body();

        if (n) 
        {
            collectConstants(n, m_globals);
            collectDynamicCalls(n);
        }
    }
}

void
CppBackEnd::declareStackVariables(const Variables& vars)
{
    for (int i=0; i < vars.size(); i++)
    {
        if (dynamic_cast<const GlobalVariable*>(vars[i]))
        {
            m_out << "static ";
        }

        m_out << vars[i]->storageClass()->machineRep()->name()
              << " "
              << vars[i]->mangledName()
              << ";"
              << endl;
    }
}

void
CppBackEnd::declareConstants(const NodeSet& nodes)
{
    for (NodeSet::const_iterator i = nodes.begin();
         i != nodes.end();
         ++i)
    {
        const Node* n = *i;
        const Type* t = static_cast<const Type*>(n->symbol());

        if (const DynamicArrayType* a = dynamic_cast<const DynamicArrayType*>(t))
        {
            m_out << "DynamicArray* " << n->mangledId() 
                  << " = new DynamicArray(NODE_THREAD, \""
                  << a->fullyQualifiedName()
                  << "\");\n";
        }
        else if (const FixedArrayType* a = dynamic_cast<const FixedArrayType*>(t))
        {
            m_out << "FixedArray* " << n->mangledId() 
                  << " = static_cast<FixedArray*>(MU_ALLOC_INSTANCE(NODE_THREAD, \""
                  << a->fullyQualifiedName()
                  << "\",0));\n";
        }
    }
}

//----------------------------------------------------------------------

void
CppBackEnd::writeNativeFunctionHeader(ostream& out, const Function* F)
{
    if (F->hasParameters())
    {
        cout << "WRITING: "; F->output(cout); cout << endl;
        out << F->returnType()->machineRep()->name() 
            << " "
            << F->mangledName()
            << "(Mu::Thread& NODE_THREAD";
    
        int nparams = F->numArgs() + F->numFreeVariables();

        for (int i=0; i < nparams; i++)
        {
            out << ", "
                << F->argType(i)->machineRep()->name()
                << " " 
                << F->parameter(i)->mangledName();
        }
    
        out << ")";
    }
}

void
CppBackEnd::writeNodeFunctionDeclaration(ostream& out, const Function* F)
{
    out << "NODE_DECLARATION(NODE_" 
        << F->mangledName()
        << ", "
        << F->returnType()->machineRep()->name()
        << ");" << endl;
}

void
CppBackEnd::writeNativeFunction(ostream& out, const Function* F)
{
    if (!F->body()) return;

    Variables vars;
    collectVariables(F, vars);

    writeNativeFunctionHeader(out, F);
    out << endl << "{" << endl;
    
    declareStackVariables(vars);

    bool oneExpr = F->body()->symbol() != m_context->simpleBlock() &&
        F->returnType() == F->body()->type();

    out << nativeExpr(F->body());

    if (oneExpr && F->body()->type() != m_context->voidType())
    {
        out << "return " << F->body()->mangledId() << ";\n";
    }

    out << "}" << endl;
}


void
CppBackEnd::writeNodeFunction(ostream& out, const Function* F)
{
    STLVector<const Variable*>::Type vars;
    collectVariables(F, vars);

    int nparams = F->numArgs() + F->numFreeVariables();

    out << "NODE_IMPLEMENTATION(NODE_" 
        << F->mangledName()
        << ", "
        << F->returnType()->machineRep()->name()
        << ")" << endl 
        << "{" << endl;

    for (int i=0; i < nparams; i++)
    {
        const Type* t = F->argType(i);

        if (t->isPrimitiveType())
        {
            out << t->machineRep()->name() 
                << " a" << i << " = "
                << "NODE_ARG(" << i << ", " 
                << t->machineRep()->name()
                << ");" << endl;
        }
        else
        {
            out << t->machineRep()->name()
                << " a" << i << " = "
                << "NODE_ARG_OBJECT(" << i << ", " 
                << t->machineRep()->name()
                << ");" << endl;
        }
    }

    if (F->returnType() != m_context->voidType())
    {
        out << "NODE_RETURN("
            << F->mangledName()
            << "(NODE_THREAD";

        for (int i=0; i < nparams; i++)
        {
            out << ", a" << i;
        }

        out << "));" << endl;
    }
    else
    {
        out << F->mangledName() << "(NODE_THREAD";

        for (int i=0; i < nparams; i++)
        {
            out << ", a" << i;
        }

        out << ");" << endl;
    }

    out << "}" << endl;
}

void
CppBackEnd::writeFunctions(ostream& out, const FunctionSet& symbols)
{
    out << "// PROTO ----------------------------------------" << endl;

    for (FunctionSet::iterator i = symbols.begin();
         i != symbols.end();
         ++i)
    {
        if (const Function* F = dynamic_cast<const Function*>(*i))
        {
            writeNodeFunctionDeclaration(out, F);
            writeNativeFunctionHeader(out, F);
            out << ";" << endl;
        }
    }

    out << "// NATIVE ----------------------------------------" << endl;

    for (FunctionSet::iterator i = symbols.begin();
         i != symbols.end();
         ++i)
    {
        if (const Function* F = dynamic_cast<const Function*>(*i))
        {
            writeNativeFunction(out, F);
            out << endl;
        }
    }

    out << "// NODES ----------------------------------------" << endl;

    for (FunctionSet::iterator i = symbols.begin();
         i != symbols.end();
         ++i)
    {
        if (const Function* F = dynamic_cast<const Function*>(*i))
        {
            writeNodeFunction(out, F);
            out << endl;
        }
    }
}

//----------------------------------------------------------------------

void
CppBackEnd::writeStaticGlobals(ostream& out)
{
    out << "\n// Globals/Constants\n"
        << "struct ModuleGlobals\n{\n";

    for (NodeSet::iterator i = m_globals.begin();
         i != m_globals.end();
         ++i)
    {
        const Node* n = *i;
        const Type* t = n->type();

        if (!t->isPrimitiveType())
        {
            out << t->machineRep()->name()
                << " c"
                << n->mangledId()
                << "; // " 
                << t->fullyQualifiedName()
                << "\n";
        }
    }

    out << "};\n\n";
    out << "static ModuleGlobals globals;\n";
}


void
CppBackEnd::writeStaticGlobalConstructors(ostream& out)
{
    int count = 0;

    for (NodeSet::iterator i = m_globals.begin();
         i != m_globals.end();
         ++i)
    {
        const Node* n = *i;
        const Type* t = n->type();

        out << nativeConstant(n);

        if (!t->isPrimitiveType())
        {
            out << "p->constants().push_back((Object*)"
                << "(globals.c" << n->mangledId()
                << " = "
                << n->mangledId()
                << "));\n";
        }
        else
        {
        }
    }
}

void
CppBackEnd::writeInlineDepFunctions(ostream& out)
{
    for (int i=m_depTypes.size(); i--;)
    {
        const Type* t = m_depTypes[i];

        if (const FunctionType* f =
            dynamic_cast<const FunctionType*>(t))
        {
            const Signature* s = f->signature();

            out << "#define EQ__" 
                << f->mangledName() << "Amp__" 
                << f->mangledName() << "Amp__" 
                << f->mangledName()
                << "(T,A,B) (*((Pointer*)(A))=(B))\n";
        }
    }

    SignatureSet sigs;

    for (int i=m_dynCalls.size(); i--;)
    {
        const Node* n = m_dynCalls[i];
        const Function* F = dynamic_cast<const Function*>(n->symbol());
        const FunctionType* t = 
            static_cast<const FunctionType*>(n->argNode(0)->type());
        const Signature* s = t->signature();

        if (sigs.find(s) != sigs.end()) continue;
        sigs.insert(s);

        out << "\nstatic "
            << s->returnType()->machineRep()->name()
            << " "
            << F->mangledName()
            << "(Thread& NODE_THREAD, ";

        for (int i=0; i < n->numArgs(); i++)
        {
            if (i) out << ", ";
            out << "const "
                << n->argNode(i)->type()->machineRep()->name()
                << " __p" << i;
        }

        out << ")\n{\n";

        out << "if (Function::CompiledFunction __cf = ((FunctionObject*)__p0)->function()->compiledFunction())\n"
            << "{\n"
            << "typedef " << F->returnType()->machineRep()->name()
            << " (*__CF)(Mu::Thread&";
        
        for (int i=1; i < n->numArgs(); i++)
        {
            out << "," << n->argNode(i)->type()->machineRep()->name();
        }

        out << ");\n";
        if (F->returnType() != m_context->voidType())
        {
            out << "return ";
        }

        out << "(__CF(__cf))(NODE_THREAD";
        for (int i=1; i < n->numArgs(); i++)
        {
            out << ", __p" << i;
        }
        out << ");\n";
        out << "}\n";

        out << "Function::ArgumentVector args(" 
            << (n->numArgs() - 1)
            << ");\n";

        for (int i=1; i < n->numArgs(); i++)
        {
            out << "args[" << (i-1) << "]._" 
                << n->argNode(i)->type()->machineRep()->name()
                << " = __p" << i << ";\n";
        }

        if (s->returnType() == m_context->voidType())
        {
            out << "NODE_THREAD.call(((FunctionObject*)__p0)->function(),args,false);\n";
        }
        else
        {
            out << "return NODE_THREAD.call(((FunctionObject*)__p0)->function(),args,false)._"
                << s->returnType()->machineRep()->name()
                << ";\n";
        }

        out << "}\n";
    }
}

//----------------------------------------------------------------------

void
CppBackEnd::writeFileHeaderInfo(ostream& out)
{
    out << "// muc GENERATED INTERMEDIATE FILE" << endl;
    out << "// " << __DATE__ << ", " << __TIME__ << endl;
    out << "#include <MuLang/Native.h>" << endl << endl;
    out << "using namespace Mu;" << endl;
}

//----------------------------------------------------------------------

void
CppBackEnd::writeModuleDeclaration(ostream& out, const Module* m)
{
    String mname = m->mangledName();

    out << "class " << mname << " : public Module" << endl
        << "{ public:" << endl
        << mname << "(Context* c) : Module(\"" << m->name() << "\",c) {}" << endl
        << "virtual ~" << mname << "() {}" << endl
        << "virtual void load();" << endl
        << "};\n\n" << endl;
}

void
CppBackEnd::writeCppStructs(ostream& out)
{
    for (int i=m_depTypes.size(); i--;)
    {
        const Type*         t = m_depTypes[i];
        const FunctionType* f = dynamic_cast<const FunctionType*>(t);
        const Class*        c = dynamic_cast<const Class*>(t);

        if (t->isFixedSize() && !t->isSequence())
        {
            if (c && !f)
            {
                writeCPPInstanceStruct(out, c);
            }
        }
        else
        {
        }
    }
}

void
CppBackEnd::writeCPPInstanceStruct(ostream& out, const Class* t)
{
    assert(t->isFixedSize());
    String m0 = t->mangledName(); 
    String m = m0 + "_S";

    out << "struct " << m << "\n{\n";

    const Type* ft = 0;

    out << m << "(";

    for (int f = 0; ft = t->fieldType(f); f++)
    {
        if (f) out << ", ";
        out << ft->machineRep()->name() << " a" << f;
    }

    out << ") : ";

    for (int f = 0; ft = t->fieldType(f); f++)
    {
        if (f) out << ", ";
        out << "_" << f << "(a" << f << ")";
    }

    out << " {}\n";

    out << "MU_ARENA_ALLOC_OPERATORS()\n";

    for (int f = 0; ft = t->fieldType(f); f++)
    {
        out << ft->machineRep()->name() 
              << " _" << f << ";\n";
    }

    out << "};\n";

    out << "#define EQ__"
        << m0 << "Amp__"
        << m0 << "Amp__"
        << m0 << "(T,A,B) ((*(Pointer*)(A))=(B))\n\n";
}

void
CppBackEnd::writeNamespaceConstructor(ostream& out, const Namespace* n)
{
    if (m_outputNamespaces.find(n) != m_outputNamespaces.end())
    {
        out << "{" << endl
            << "Namespace* N = new Namespace(\"" 
            << n->name() << "\");" << endl
            << "S->addSymbol(N);" << endl
            << "{" << endl;
        
        out << "Symbol* S = N;" << endl;

        writeSymbolContents(out, n);

        out << "}" << endl
            << "}" << endl;
    }
}

void
CppBackEnd::writeFunctionConstructor(ostream& out, const Function* f)
{
    out << "new Function(";
    if (f->isLambda()) out << "\"" << f->name() << "\"";
    else out << "\"" << f->name() << "\"";

    out << ", " << "NODE_" << f->mangledName() << ", "
        << f->baseAttributes() << "," << endl
        << "Return, \"" 
        << f->returnType()->fullyQualifiedName() << "\"," << endl;

    out << "Compiled, " << f->mangledName() << ", " << endl; 

    if (f->numArgs() + f->numFreeVariables()) 
    {
        out << "Parameters, " << endl;
        int nparams = f->numArgs() + f->numFreeVariables();

        for (int q=0; q < nparams; q++)
        {
            const ParameterVariable* pv = f->parameter(q);
            
            if (dynamic_cast<const FreeVariable*>(pv))
            {
                out << "new FreeParam";
            }
            else
            {
                out << "new Param";
            }
            
            out << "(\"" << pv->name() << "\", \""
                << pv->storageClass()->fullyQualifiedName()
                << "\")," << endl;
        }
    }

    out << "End)";
}

void
CppBackEnd::writeFunctionConstructorWithScope(ostream& out, 
                                              const Function* f)
{
    out << "{" << endl
        << "Function* F = ";

    writeFunctionConstructor(out, f);

    out << ";" << endl
        << "S->addSymbol(F);" << endl
        << "{" << endl
        << "Symbol* S = F;" << endl;
    
    writeSymbolContents(out, f);
    
    out << "}" << endl
        << "}" << endl;
}

void
CppBackEnd::writeSymbolContents(ostream& out, const Symbol* s)
{
    if (s->symbolTable())
    {
	HT& table = s->symbolTable()->hashTable();

	for (HT::Iterator i(table); i; ++i) 
        {
            if (Function* ff = dynamic_cast<Function*>(*i))
            {
                writeFunctionConstructorWithScope(out, ff);
            }
            else if (Namespace* ns = dynamic_cast<Namespace*>(*i))
            {
                writeNamespaceConstructor(out, ns);
            }
        }
    }
}

void
CppBackEnd::writeModuleLoad(ostream& out, 
                            const Module* m,
                            const FunctionSet& functions)
{
    String mname = m->mangledName();

    out << "void" << endl
        << mname << "::load()" << endl
        << "{" << endl
        << "USING_MU_FUNCTION_SYMBOLS;"
        << "MuLangContext* c = (MuLangContext*)(globalModule()->context());"
        << "Symbol* S = this;" << endl;

    //
    //  Write functions
    //

    for (FunctionSet::iterator i = functions.begin();
         i != functions.end();
         ++i)
    {
        writeFunctionConstructorWithScope(out, *i);
    }

    out << "}" << endl;
}

void
CppBackEnd::writeModuleInit(ostream& out, const Modules& modules)
{
    //
    //  Declare initialize function
    //

    out << endl
        << "extern \"C\" {" << endl
        << "Module*" << endl
        << "MuInitialize(const char* name, Context* c, Process* p)" << endl
        << "{ USING_MU_FUNCTION_SYMBOLS;" << endl;

    //
    //  Cache a new process and the global scope
    //
    
    out << "Symbol *s = c->globalScope();\n"
        << "Thread *thread__ = p->newApplicationThread();\n"
        << "Thread& thread_ = *thread__;\n";

    //
    //  Generate types needed by this module
    //

    if (!m_depTypes.empty()) out << "// GENERATE TYPES" << endl;

    for (int i=m_depTypes.size(); i--;)
    {
        const Type* t = m_depTypes[i];

        if (dynamic_cast<const TupleType*>(t) ||
            dynamic_cast<const DynamicArrayType*>(t) ||
            dynamic_cast<const FixedArrayType*>(t) ||
            dynamic_cast<const FunctionType*>(t))
        {
            out << "const Type* " << t->mangledId() <<  " = "
                << "c->parseType(\"" << t->fullyQualifiedName()
                << "\", p);\n";
        }
    }

    //
    //  Add modules to global scope
    //

    out << "// ADD MODULE" << endl;
    
    for (int i=0; i < modules.size(); i++)
    {
        const Module* m = modules[i];

        out << "Module* __module = new "
            << m->mangledName()
            << "(c);\n"
            << "s->addSymbol(__module);\n";
    }

    out << "// CONSTRUCT CONSTANTS" << endl;

    //
    //  global constructors
    //

    writeStaticGlobalConstructors(out);

    out << "// PROLOG" << endl;

    out << "p->releaseApplicationThread(thread__);\n"
        << "return __module;\n"
        << "}\n"
        << "};" << endl;
}

