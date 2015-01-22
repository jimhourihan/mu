//
//  Copyright (c) 2009, Jim Hourihan
//  All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions
//  are met:
//
//     * Redistributions of source code must retain the above
//       copyright notice, this list of conditions and the following
//       disclaimer.
//
//     * Redistributions in binary form must reproduce the above
//       copyright notice, this list of conditions and the following
//       disclaimer in the documentation and/or other materials
//       provided with the distribution.
//
//     * Neither the name of the Jim Hourihan nor the names of its
//       contributors may be used to endorse or promote products
//       derived from this software without specific prior written
//       permission.
//
//  THIS SOFTWARE IS PROVIDED BY Jim Hourihan ''AS IS'' AND ANY EXPRESS
//  OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
//  WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
//  ARE DISCLAIMED. IN NO EVENT SHALL Jim Hourihan BE LIABLE FOR
//  ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
//  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
//  OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
//  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
//  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
//  DAMAGE.
//
#include <Mu/ASTNode.h>
#include <Mu/BaseFunctions.h>
#include <Mu/Class.h>
#include <Mu/Context.h>
#include <Mu/FunctionObject.h>
#include <Mu/FunctionType.h>
#include <Mu/GlobalVariable.h>
#include <Mu/Interface.h>
#include <Mu/MachineRep.h>
#include <Mu/Node.h>
#include <Mu/PartialApplicator.h>
//#include <Mu/PartialEvaluator.h>
#include <Mu/FunctionSpecializer.h>
#include <Mu/PrimitiveObject.h>
#include <Mu/Process.h>
#include <Mu/ReferenceType.h>
#include <Mu/Signature.h>
#include <Mu/Exception.h>
#include <Mu/StackVariable.h>
#include <Mu/VariantInstance.h>
#include <Mu/Thread.h>
#include <Mu/Variable.h>
#include <Mu/config.h>
#include <Mu/Unresolved.h>
#include <iostream>
#include <sstream>
#include <vector>

namespace Mu {
using namespace std;

NoOp::NoOp(Context* context, const char *name) :
    Function(context, name, NoOp::node, Function::Pure,
             Function::Return, "void",
             Function::End)
{
}

NODE_IMPLEMENTATION(NoOp::node,void)
{
    return;
}

//----------------------------------------------------------------------

SimpleBlock::SimpleBlock(Context* context, const char *name)
    : Function(context,
               name, NodeFunc(0),
               Function::ContextDependent,
               Function::Return, "void",
               Function::Args, "?", Function::Optional, "?varargs",
               Function::Maximum, Function::MaxArgValue,
               Function::End)
{
}

const Type*
SimpleBlock::nodeReturnType(const Node *node) const
{
    const Node* n = node->argNode(node->numArgs()-1);
    if (!n) throw UnresolvableSymbolException();
    return n->type();
}

NodeFunc
SimpleBlock::func(Node *node) const
{
    if (node)
    {
        const Type *t = node->type();
        const MachineRep *rep = t->machineRep();
        return rep->simpleBlockFunc();
    }
    else
    {
        return Function::func(node);
    }
}

//----------------------------------------------------------------------

FixedFrameBlock::FixedFrameBlock(Context* context, const char *name)
    : Function(context,
               name, FixedFrameBlock::node,
               Function::ContextDependent | Function::HiddenArgument,
               Function::Return, "void",
               Function::Args, "?", Function::Optional, "?varargs",
               Function::Maximum, Function::MaxArgValue,
               Function::End)
{
}

NodeFunc
FixedFrameBlock::func(Node *node) const
{
    if (node)
    {
        const Type *t = node->type();
        const MachineRep *rep = t->machineRep();
        return rep->frameBlockFunc();
    }
    else
    {
        return Function::func(node);
    }
}


const Type*
FixedFrameBlock::nodeReturnType(const Node *node) const
{
    return node->argNode(node->numArgs()-1)->type();
}

MU_NODE_IMPLEMENTATION(FixedFrameBlock::node, void)
{
    //
    //	Allocate local variable space
    //

    Thread::StackRecord record(MU_NODE_THREAD);
    record.newStackFrame(MU_NODE_DATA(int));

    //
    //	Evaluate frame statements. See simple block above for comments.
    //

    for (int i=0; MU_NODE_THIS.argNode(i); i++)
    {
        MU_NODE_ANY_TYPE_ARG(i);
    }
}



//----------------------------------------------------------------------

DynamicCast::DynamicCast(Context* context, const char *name)
    : Function(context, name, DynamicCast::node, Function::Mapped,
               Function::Return, "?class_or_interface",
               Function::Args, "?class_or_interface", "?class_or_interface",
               Function::End)
{
}

const Type*
DynamicCast::nodeReturnType(const Node *n) const
{
    return dynamic_cast<const Type*>(n->argNode(0)->symbol());
}

MU_NODE_IMPLEMENTATION(DynamicCast::node, Pointer)
{
    const Symbol* sym = MU_NODE_THIS.argNode(0)->symbol();

    if (const Class* c0 = dynamic_cast<const Class*>(sym))
    {
        MU_NODE_DECLARE_ARG(ClassInstance*, o, 1);

        if (o)
        {
            if (const Class* c1 = dynamic_cast<const Class*>(o->type()))
            {
                if (ClassInstance* dobj = c1->dynamicCast(o, c0, true))
                {
                    MU_NODE_RETURN(dobj);
                }
                //if (c1->isA(c0)) NODE_RETURN((Pointer)o);
            }
        }
        else
        {
            //
            //	Let nil pass through
            //

            MU_NODE_RETURN((Pointer)o);
        }
    }
    else if (const Interface* i = dynamic_cast<const Interface*>(sym))
    {
        MU_NODE_DECLARE_ARG(Object*, o, 1);

        if (o)
        {
            if (const Class* c1 = dynamic_cast<const Class*>(o->type()))
            {
                if (c1->implementation(i))
                {
                    MU_NODE_RETURN((Pointer)o);
                }
            }
        }
        else
        {
            //
            //	Can't attempt to cast nil to an interface. Let it throw.
            //

            //  ALLOWING --NEEDS FIXING

            MU_NODE_RETURN(Pointer(0));
        }
    }

    throw BadDynamicCastException(NODE_THREAD);
}
//----------------------------------------------------------------------


DynamicActivation::DynamicActivation(Context* context,
                                     const String& returnType,
                                     const STLVector<String>::Type& args)
    : Function(context, "()", NodeFunc(0),
               Function::DynamicActivation |
                   Function::ContextDependent  |
                   Function::MaybePure,
               Function::Return, returnType.c_str(),
               Function::ArgVector, &args)
{
}

NodeFunc
DynamicActivation::func(Node *node) const
{
    if (node)
    {
        const Type *t;

        if (node->numArgs())
        {
            t = ((const Node*)node)->argNode(0)->type();
        }
        else
        {
            t = returnType();
        }

        const MachineRep *rep = t->machineRep();
        return rep->dynamicActivationFunc();
    }
    else
    {
        return Function::func(node);
    }
}


//----------------------------------------------------------------------


ReturnFromFunction::ReturnFromFunction(Context* context, const char *name, bool arg)
    : Function(context, name, NodeFunc(0),
               Function::ContextDependent,
               Function::Return, (arg ? "?" : "void"),
               Function::Args, (arg ? "?" : 0), Function::End)
{
}

const Type*
ReturnFromFunction::nodeReturnType(const Node *n) const
{
    const ReturnFromFunction* R =
        static_cast<const ReturnFromFunction*>(n->symbol());

    if (R->numArgs())
    {
        return dynamic_cast<const Type*>(n->argNode(0)->type());
    }
    else
    {
        return R->globalModule()->context()->voidType();
    }
}

NodeFunc
ReturnFromFunction::func(Node *node) const
{
    if (node)
    {
        const Type *t;

        if (node->numArgs())
        {
            t = ((const Node*)node)->argNode(0)->type();
        }
        else
        {
            t = returnType();
        }

        const MachineRep *rep = t->machineRep();
        return rep->functionReturnFunc();
    }
    else
    {
        return Function::func(node);
    }
}

//----------------------------------------------------------------------


TailFuseReturn::TailFuseReturn(Context* context, const char *name)
    : Function(context, name, NodeFunc(0),
               Function::ContextDependent,
               Function::Return, ("?"),
               Function::Args, "?",
               Function::End)
{
}

const Type*
TailFuseReturn::nodeReturnType(const Node *n) const
{
    return n->argNode(0)->type();
}

NodeFunc
TailFuseReturn::func(Node *node) const
{
    if (node)
    {
        const Type *t = ((const Node*)node)->argNode(0)->type();
        const MachineRep *rep = t->machineRep();
        return rep->functionTailFuseFunc();
    }
    else
    {
        return Function::func(node);
    }
}

//----------------------------------------------------------------------


Curry::Curry(Context* context, const char *name)
    : Function(context,
               name,
               Curry::node,
               Function::Pure,
               Function::Return, "?function",
               Function::Args, "?function", "?function", "?bool_rep", "?varargs",
               Function::End)
{
}

Curry::~Curry() {}

const Type*
Curry::nodeReturnType(const Node* n) const
{
    return dynamic_cast<const Type*>(n->argNode(0)->symbol());
}

FunctionObject*
Curry::evaluate(Thread& t,
                FunctionObject* inObj,
                const Function::ArgumentVector& args,
                const vector<bool>& mask,
                bool dynamicDispatch)
{
    //
    //  Never do partial application on the result of a lambda
    //  expression (its too difficult to archive). Instead do partial
    //  evaluation. The good side is that there will never be more
    //  than one level of indirection in multiple-curried lambda
    //  expressions. the bad side is that there will be more overhead
    //  upfront.
    //

    Process*        p     = t.process();
    const Function* F     = inObj->function();
    const bool      apply = !F->isLambda();

    try
    {
        if (apply)
        {
            PartialApplicator evaluator(F, p, &t, args, mask, dynamicDispatch);

            const FunctionType* rt = evaluator.result()->type();
            FunctionObject* outObj = new FunctionObject(rt);
            outObj->setDependent(inObj);
            outObj->setFunction(evaluator.result());
            return outObj;
        }
        else
        {
            FunctionSpecializer evaluator(F, p, &t);
            evaluator.partiallyEvaluate(args, mask);

            const FunctionType* rt = evaluator.result()->type();
            FunctionObject* outObj = new FunctionObject(rt);
            outObj->setFunction(evaluator.result());
            return outObj;
        }
    }
    catch (Exception& e)
    {
        ProgramException exc(t);
        exc.message() = e.message();
        exc.message() += " during partial ";
        exc.message() += (apply ? "application" : "evaluation");
        exc.message() += " of ";
        exc.message() += F->name().c_str();
        throw exc;
    }
}

MU_NODE_IMPLEMENTATION(Curry::node, Pointer)
{
    Process* p = MU_NODE_THREAD.process();
    Context* c = p->context();

    MU_NODE_DECLARE_ARG(FunctionObject*, o, 1);
    MU_NODE_DECLARE_ARG(bool, d, 2);

    const Function* F = o->function();
    Function::ArgumentVector args(F->numArgs() + F->numFreeVariables());
    vector<bool> mask(args.size());

    for (int i=0, s=args.size(); i < s; i++)
    {
        mask[i] = MU_NODE_THIS.argNode(i+3)->symbol() != c->noop();

        if (mask[i])
        {
            args[i] = MU_NODE_ANY_TYPE_ARG(i+3);
        }
    }

    MU_NODE_RETURN(Pointer(evaluate(MU_NODE_THREAD, o, args, mask, d)));
}

//----------------------------------------------------------------------


DynamicPartialEvaluate::DynamicPartialEvaluate(Context* context, const char *name)
    : Function(context,
               name,
               DynamicPartialEvaluate::node,
               Function::Pure,
               Function::Return, "?function",
               Function::Args, "?function", "?function", "?varargs",
               Function::End)
{
}

DynamicPartialEvaluate::~DynamicPartialEvaluate() {}

const Type*
DynamicPartialEvaluate::nodeReturnType(const Node* n) const
{
    return dynamic_cast<const Type*>(n->argNode(0)->symbol());
}

MU_NODE_IMPLEMENTATION(DynamicPartialEvaluate::node, Pointer)
{
    typedef FunctionSpecializer Generator;

    MU_NODE_DECLARE_ARG(FunctionObject*, f, 1);

    Generator::ArgumentVector args(f->function()->numArgs() +
                                   f->function()->numFreeVariables());
    Generator::ArgumentMask   mask(args.size());
    Process* p = MU_NODE_THREAD.process();
    Context* c = p->context();

    for (int i=0; i < args.size(); i++)
    {
        mask[i] = MU_NODE_THIS.argNode(i+2)->symbol() != c->noop();

        if (mask[i])
        {
            args[i] = MU_NODE_ANY_TYPE_ARG(i+2);
        }
    }

    try
    {
        Generator evaluator(f->function(), p, &MU_NODE_THREAD);
        evaluator.partiallyEvaluate(args, mask);

        const FunctionType* rt = evaluator.result()->type();
        assert(rt == MU_NODE_THIS.argNode(0)->type());
        FunctionObject* o = new FunctionObject(rt);
        o->setFunction(evaluator.result());
        MU_NODE_RETURN(Pointer(o));
    }
    catch (Exception& e)
    {
        ProgramException exc(MU_NODE_THREAD);
        exc.message() = e.message();
        exc.message() += " during partial evaluation of ";
        exc.message() += f->function()->name().c_str();
        throw exc;
    }
}

//----------------------------------------------------------------------

DynamicPartialApplication::DynamicPartialApplication(Context* context, const char *name)
    : Function(context,
               name,
               DynamicPartialApplication::node,
               Function::Pure,
               Function::Return, "?function",
               Function::Args, "?function", "?function", "?varargs",
               Function::End)
{
}

DynamicPartialApplication::~DynamicPartialApplication() {}

const Type*
DynamicPartialApplication::nodeReturnType(const Node* n) const
{
    return dynamic_cast<const Type*>(n->argNode(0)->symbol());
}

MU_NODE_IMPLEMENTATION(DynamicPartialApplication::node, Pointer)
{
    //
    //  Never do partial application on the result of a lambda
    //  expression (its too difficult to archive). Instead do
    //  partial evaluation. The good side is that there will never
    //  be more than one level of indirection in multiple-curried
    //  lambda expressions. the bad side is that there will be
    //  more overhead upfront.
    //

    Process* p = MU_NODE_THREAD.process();
    Context* c = p->context();
    MU_NODE_DECLARE_ARG(FunctionObject*, f, 1);
    bool apply = f->function()->isLambda();

    try
    {
        if (apply)
        {
            typedef PartialApplicator Generator;
            Generator::ArgumentVector args(f->function()->numArgs() +
                                           f->function()->numFreeVariables());
            Generator::ArgumentMask   mask(args.size());

            for (int i=0; i < args.size(); i++)
            {
                mask[i] = MU_NODE_THIS.argNode(i+2)->symbol() != c->noop();
                if (mask[i])
                {
                    args[i] = MU_NODE_ANY_TYPE_ARG(i+2);
                }
            }

            Generator evaluator(f->function(), p, &MU_NODE_THREAD, args, mask);

            const FunctionType* rt = evaluator.result()->type();
            assert(rt == MU_NODE_THIS.argNode(0)->type());
            FunctionObject* o = new FunctionObject(rt);
            o->setDependent(f);
            o->setFunction(evaluator.result());
            MU_NODE_RETURN(Pointer(o));
        }
        else
        {
            typedef FunctionSpecializer Generator;
            Generator::ArgumentVector args(f->function()->numArgs() +
                                           f->function()->numFreeVariables());
            Generator::ArgumentMask   mask(args.size());

            for (int i=0; i < args.size(); i++)
            {
                mask[i] = MU_NODE_THIS.argNode(i+2)->symbol() != c->noop();

                if (mask[i])
                {
                    args[i] = MU_NODE_ANY_TYPE_ARG(i+2);
                }
            }

            Generator evaluator(f->function(), p, &MU_NODE_THREAD);
            evaluator.partiallyEvaluate(args, mask);

            const FunctionType* rt = evaluator.result()->type();
            assert(rt == MU_NODE_THIS.argNode(0)->type());
            FunctionObject* o = new FunctionObject(rt);
            o->setFunction(evaluator.result());
            MU_NODE_RETURN(Pointer(o));
        }
    }
    catch (Exception& e)
    {
        ProgramException exc(MU_NODE_THREAD);
        exc.message() = e.message();
        exc.message() += " during partial ";
        exc.message() += (apply ? "application" : "evaluation");
        exc.message() += " of ";
        exc.message() += f->function()->name().c_str();
        throw exc;
    }
}

//----------------------------------------------------------------------

NonPrimitiveCondExr::NonPrimitiveCondExr(Context* context, const char *name)
    : Function(context, name,
               NonPrimitiveCondExr::node,
               Function::Pure,
               Function::Return, "?non_primitive_or_nil",
               Function::Args, "bool", "?non_primitive_or_nil", "?non_primitive_or_nil",
               Function::End)
{
}

NonPrimitiveCondExr::~NonPrimitiveCondExr() {}

const Type*
NonPrimitiveCondExr::nodeReturnType(const Node* n) const
{
    const Type* t = n->argNode(1)->type();

    if (t == n->symbol()->globalModule()->context()->nilType())
    {
        return n->argNode(2)->type();
    }
    else
    {
        return t;
    }
}

MU_NODE_IMPLEMENTATION(NonPrimitiveCondExr::node, Pointer)
{
    MU_NODE_DECLARE_ARG(bool, b, 0);

    if (b)
    {
        MU_NODE_DECLARE_ARG(Pointer, p, 1);
        MU_NODE_RETURN(p);
    }
    else
    {
        MU_NODE_DECLARE_ARG(Pointer, p, 2);
        MU_NODE_RETURN(p);
    }
}

//----------------------------------------------------------------------

VariantMatch::VariantMatch(Context* context, const char *name)
    : Function(context, name, VariantMatch::node, Function::None,
               Function::Return, "void",
               Function::Args, "?reference", "?",
               Function::Optional, "?varargs",
               Function::Maximum, Function::MaxArgValue,
               Function::End)
{
}

VariantMatch::~VariantMatch() {}

MU_NODE_IMPLEMENTATION(VariantMatch::node, void)
{
    //
    //  Get result of assignment
    //

    MU_NODE_DECLARE_ARG(Pointer, p, 0);
    VariantInstance* i = *reinterpret_cast<VariantInstance**>(p);

    //
    //  Eval argument corresponding to tag
    //

    if (i)
    {
        const VariantTagType* tt = i->tagType();
        size_t index = tt->index() + 1;
        if (index >= NODE_THIS.numArgs()) throw MissingMatchException(NODE_THREAD);
        MU_NODE_ANY_TYPE_ARG(index);
    }
    else
    {
        throw NilArgumentException(NODE_THREAD);
    }
}

//----------------------------------------------------------------------

namespace BaseFunctions {

MU_NODE_IMPLEMENTATION(dereference, Pointer)
{
    MU_NODE_DECLARE_ARG(Pointer, p, 0);
    Pointer* i = reinterpret_cast<Pointer*>(p);
    NODE_RETURN(*i);
}

MU_NODE_IMPLEMENTATION(assign, Pointer)
{
    MU_NODE_DECLARE_ARG(Pointer, p, 0);
    MU_NODE_DECLARE_ARG(Pointer, o, 1);

    Pointer* i = reinterpret_cast<Pointer*>(p);
    *i = o;

    MU_NODE_RETURN(Pointer(i));
}

MU_NODE_IMPLEMENTATION(eq, bool)
{
    MU_NODE_DECLARE_ARG(Pointer, a, 0);
    MU_NODE_DECLARE_ARG(Pointer, b, 0);

    NODE_RETURN(a == b);
}

MU_NODE_IMPLEMENTATION(neq, bool)
{
    MU_NODE_DECLARE_ARG(Pointer, a, 0);
    MU_NODE_DECLARE_ARG(Pointer, b, 0);

    MU_NODE_RETURN(a != b);
}

MU_NODE_IMPLEMENTATION(print, void)
{
    MU_NODE_DECLARE_ARG(Object*, obj, 0);

    if (obj)
    {
        obj->type()->outputValue(cout, Value(obj));
    }
    else
    {
        cout << "nil" << endl;
    }
}

MU_NODE_IMPLEMENTATION(equals, bool)
{
    MU_NODE_DECLARE_ARG(ClassInstance*, a, 0);
    MU_NODE_DECLARE_ARG(ClassInstance*, b, 0);

    MU_NODE_RETURN(a == b);
}

MU_NODE_IMPLEMENTATION(unresolved, void)
{
    const ASTNode* astnode = static_cast<const ASTNode*>(&MU_NODE_THIS);
    const Context* c = MU_NODE_THREAD.context();
    Name n;

    if (const ASTName* nnode = dynamic_cast<const ASTName*>(astnode))
    {
        n = nnode->name;
    }
    else if (const ASTSymbol* snode = dynamic_cast<const ASTSymbol*>(astnode))
    {
        n = snode->symbol->fullyQualifiedName();
    }

    ostringstream str;
    str << " \"" << n.c_str() << "\""
        << " at " << astnode->sourceFileName().c_str()
        << ", line " << astnode->linenum()
        << ", char " << astnode->charnum();

    string s = str.str();

    if (MU_NODE_THIS.symbol() == c->unresolvedCall())
    {
        UnresolvedFunctionException exc(NODE_THREAD);
        exc.message() += s.c_str();
        throw exc;
    }
    else
    {
        UnresolvedReferenceException exc(MU_NODE_THREAD);
        exc.message() += s.c_str();
        throw exc;
    }
}

MU_NODE_IMPLEMENTATION(abstract, void)
{
    AbstractCallException exc(MU_NODE_THREAD);
    exc.message() += " \"";
    exc.message() += MU_NODE_THIS.symbol()->name().c_str();
    exc.message() += "\"";
    throw exc;
}

MU_NODE_IMPLEMENTATION(classAllocate, Pointer)
{
    const Class* c = static_cast<const Class*>(MU_NODE_THIS.symbol()->scope());
    MU_NODE_RETURN(ClassInstance::allocate(c));
}

MU_NODE_IMPLEMENTATION(objIdent, Pointer)
{
    MU_NODE_DECLARE_ARG(Pointer, p, 0);
    NODE_RETURN(p);
}

MU_NODE_GENERIC_IMPLEMENTATION(constantAnySize)
{
    MU_NODE_THIS.type()->copy(MU_NODE_DATA(MU_NODE_THIS), MU_NODE_RLOC);
}

MU_NODE_IMPLEMENTATION(referenceStack, Pointer)
{
    const StackVariable* sv =
        static_cast<const StackVariable*>(MU_NODE_THIS.symbol());

    size_t index = sv->address() + MU_NODE_THREAD.stackOffset();
    MU_NODE_RETURN(MU_NODE_THREAD.stack()[index].value());
}

MU_NODE_GENERIC_IMPLEMENTATION(dereferenceStack)
{
    const StackVariable* sv =
        static_cast<const StackVariable*>(MU_NODE_THIS.symbol());

    size_t index = sv->address() + MU_NODE_THREAD.stackOffset();
    sv->type()->copy(MU_NODE_THREAD.stack()[index].value(), MU_NODE_RLOC);
}

MU_NODE_IMPLEMENTATION(referenceGlobal, Pointer)
{
    const GlobalVariable* sv =
        static_cast<const GlobalVariable*>(MU_NODE_THIS.symbol());
    Process *process = NODE_THREAD.process();
    NODE_RETURN(process->globals()[gv->address()].value());
}

MU_NODE_GENERIC_IMPLEMENTATION(dereferenceStack)
{
    const GlobalVariable* sv =
        static_cast<const GlobalVariable*>(MU_NODE_THIS.symbol());
    Process *process = NODE_THREAD.process();
    gv->type()->copy(process->globals()[gv->address()].value(), MU_NODE_RLOC);
}

MU_NODE_GENERIC_IMPLEMENTATION(callMethod)
{
    const MemberFunction *f =
        static_cast<const MemberFunction*>(MU_NODE_THIS.symbol());
    MU_NODE_DECLARE_ARG(ClassInstance*, i, 0);
    if (!i) throw NilArgumentException(NODE_THREAD);
    const MemberFunction* F = i->classType()->dynamicLookup(f);
    TYPE t;

    size_t nargs = NODE_THIS.numArgs();
    LOCAL_ARRAY(argv, const Node*, nargs+1);
    TypedDataNode<Pointer> dn(0, PointerRep::rep()->constantFunc(), i->type());
    //DataNode dn(0, PointerRep::rep()->constantFunc(), i->type());
    //dn._data._Pointer = i;
    dn._value = i;
    argv[0] = &dn;
    argv[nargs] = 0;
    for (size_t i = 1; i < nargs; i++) argv[i] = MU_NODE_THIS.argNode(i);
    Node n((Node**)argv, F);

    try
    {
        n->eval(MU_NODE_THREAD, MU_NODE_RLOC);
    }
    catch (...)
    {
        n.releaseArgv();
        throw;
    }

    n.releaseArgv();
}

MU_NODE_GENERIC_IMPLEMENTATION(dereferenceClassMember)
{
    const MemberVariable* v =
        static_cast<const MemberVariable*>(MU_NODE_THIS.symbol());
    MU_NODE_DECLARE_ARG(ClassInstance*, i, 0);
    if (!i) throw NilArgumentException(NODE_THREAD);
    size_t offset = v->instanceOffset();
    Pointer p = i->structure() + offset;
    v->type()->copy(p, MU_NODE_RLOC);
}

MU_NODE_GENERIC_IMPLEMENTATION(unpackVariant)
{
    MU_NODE_DECLARE_ARG(VariantInstance*, i, 0);
    NODE_RETURN(*(i->data<TYPE>()));
}

MU_NODE_IMPLEMENTATION(variantConstructor, Pointer)
{
    const VariantTagType* c =
        static_cast<const VariantTagType*>(MU_NODE_THIS.symbol()->scope());
    VariantInstance* i = VariantInstance::allocate(c);
    MU_NODE_THIS.argNode(0)->eval(MU_NODE_THREAD, i->data<void>());
    MU_NODE_RETURN(i);
}

MU_NODE_GENERIC_IMPLEMENTATION(frameBlock)
{
    Thread::StackRecord record(MU_NODE_THREAD);
    record.newStackFrame(MU_NODE_DATA(int));
    int n = MU_NODE_NUM_ARGS() - 1;

    for (int i=0; i < n; i++) MU_NODE_ANY_TYPE_ARG(i);
    MU_NODE_THIS.argNode(n)->eval(MU_NODE_THREAD, MU_NODE_RLOC);
}

MU_NODE_GENERIC_IMPLEMENTATION(simpleBlock)
{
    int n = MU_NODE_NUM_ARGS() - 1;
    for (int i=0; i < n; i++) MU_NODE_ANY_TYPE_ARG(i);
    MU_NODE_THIS.argNode(n)->eval(MU_NODE_THREAD, MU_NODE_RLOC);
}

MU_NODE_GENERIC_IMPLEMENTATION(patternBlock)
{
    Thread::JumpRecord record(MU_NODE_THREAD, JumpReturnCode::PatternFail);
    int rv = SETJMP(MU_NODE_THREAD.jumpPoint());

    switch (rv)
    {
      case JumpReturnCode::PatternFail:
          MU_NODE_THREAD.jumpPointRestore();
          throw PatternFailedException();
          break;

      case JumpReturnCode::NoJump:
          {
              int n = MU_NODE_NUM_ARGS() - 1;
              for (int i=0; i < n; i++) MU_NODE_ANY_TYPE_ARG(i);
              MU_NODE_THIS.argNode(n)->eval(MU_NODE_THREAD, MU_NODE_RLOC);
              break;
          }
    };
}

MU_NODE_GENERIC_IMPLEMENTATION(functionActivationFunc)
{
    const Function *f = static_cast<const Function*>(MU_NODE_THIS.symbol());
    int n = MU_NODE_NUM_ARGS();
    int s = f->stackSize();
    Thread::StackRecord record(MU_NODE_THREAD);
    record.beginActivation(s);

    for (int i=0; i < s; i++)
    {
        if (i < n)
        {
            MU_NODE_EVAL_VALUE(record.parameterValue(i),
                               NODE_THIS.argNode(i),
                               NODE_THREAD);
        }
        else
        {
            Value val;
            zero(val);
            record.setParameter(i, val);
        }
    }

    record.endParameters();

    const Node *body = f->body();
    if (!body) throw UnimplementedMethodException(NODE_THREAD);

    if (NodeFunc func = body->func())
    {
        NODE_THREAD.jumpPointBegin(JumpReturnCode::Return |
                                   JumpReturnCode::TailFuse);
        int rv = SETJMP(NODE_THREAD.jumpPoint());

        if (rv == JumpReturnCode::NoJump)
        {
            (*func)(*body, NODE_THREAD, MU_NODE_RLOC);
        }
        else
        {
            NODE_THREAD.jumpPointRestore();
            v->type()->copy(p, MU_NODE_RLOC);
        }

        NODE_THREAD.jumpPointEnd();
    }
    else
    {
        throw NilNodeFuncException(NODE_THREAD);
    }
}

MU_NODE_GENERIC_IMPLEMENTATION(dynamicActivation)
{
    if (FunctionObject* fobj = MU_NODE_ARG_OBJECT(0, FunctionObject))
    {
        if (const Function* f = fobj->function())
        {
            Node node(NODE_THIS.argv() + 1, f);
            NodeFunc nf = f->func(&node);
            TYPE p;

            try
            {
                p = (*nf._  ## TYPE ## Func)(node, NODE_THREAD);
            }
            catch (...)
            {
                node.releaseArgv();
                throw;
            }

            node.releaseArgv();
            NODE_RETURN(p);
        }
        else
        {
            throw NilArgumentException(NODE_THREAD);
        }
    }
    else
    {
        throw NilArgumentException(NODE_THREAD);
    }
}

MU_NODE_GENERIC_IMPLEMENTATION(referenceMember)
{
    const MemberVariable* v =
	static_cast<const MemberVariable*>(MU_NODE_THIS.symbol());
    Vector4f *vp = reinterpret_cast<Vector4f*>(NODE_ARG(0,Pointer));
    NODE_RETURN( (Pointer)&(*vp)[v->address()] );
}

} // namespace BaseFunctions


AssignAsReference::AssignAsReference(Context* c) :
    Function(c, "=", BaseFunctions::assign,
             Function::None,
             Function::Return, "?",
             Function::Args, "?non_primitive_reference", "?non_primitive_or_nil",
             Function::End)
{
}

AssignAsReference::~AssignAsReference() {}

const Type*
AssignAsReference::nodeReturnType(const Node* n) const
{
    return n->argNode(0)->type();
}


PatternTest::PatternTest(Context* c) :
    Function(c, "__pattern_test", PatternTest::node,
             Function::None,
             Function::Return, c->boolType()->fullyQualifiedName().c_str(),
             Function::Args, "?",
             Function::Optional, "?",
             Function::End)
{
}

PatternTest::~PatternTest() {}

MU_NODE_IMPLEMENTATION(PatternTest::node, bool)
{
    Thread::JumpRecord record(MU_NODE_THREAD, JumpReturnCode::PatternFail);
    int rv = SETJMP(MU_NODE_THREAD.jumpPoint());
    bool b = false;

    switch (rv)
    {
      case JumpReturnCode::PatternFail:
          MU_NODE_THREAD.jumpPointRestore();
          break;

      case JumpReturnCode::NoJump:
          if (MU_NODE_THIS.numArgs() == 1)
          {
              MU_NODE_ANY_TYPE_ARG(0);
          }
          else
          {
              if (MU_NODE_THIS.argNode(0)->type() == MU_NODE_THIS.type())
              {
                  MU_NODE_DECLARE_ARG(bool, b, 0);
                  if (b) MU_NODE_ANY_TYPE_ARG(1);
              }
              else
              {
                  MU_NODE_ANY_TYPE_ARG(0);
                  MU_NODE_ANY_TYPE_ARG(1);
                  b = true;
              }
          }
          break;

      default:
          abort();
    }

    MU_NODE_RETURN(b);
}

BoolPatternTest::BoolPatternTest(Context* c) :
    Function(c, "__bool_pattern_test", BoolPatternTest::node,
             Function::None,
             Function::Return, c->boolType()->fullyQualifiedName().c_str(),
             Function::Args, "?",
             Function::Optional, "?",
             Function::End)
{
}

BoolPatternTest::~BoolPatternTest() {}

MU_NODE_IMPLEMENTATION(BoolPatternTest::node, bool)
{
    MU_NODE_DECLARE_ARG(bool, b, 0);

    if (!b)
    {
        MU_NODE_THREAD.jump(JumpReturnCode::PatternFail, 1);
    }

    MU_NODE_RETURN(true);
}


CaseTest::CaseTest(Context* c) :
    Function(c, "__case_test", CaseTest::node,
             Function::None,
             Function::Return, c->boolType()->fullyQualifiedName().c_str(),
             Function::Args, "?reference", "?",
             Function::Optional, "?varargs",
             Function::Maximum, Function::MaxArgValue,
             Function::End)
{
}

CaseTest::~CaseTest() {}

MU_NODE_IMPLEMENTATION(CaseTest::node, bool)
{
    MU_NODE_ANY_TYPE_ARG(0);

    for (size_t i = 1; MU_NODE_THIS.argNode(i); i++)
    {
        MU_NODE_DECLARE_ARG(bool, i, 0);

        if (i) MU_NODE_RETURN(true);
    }

    MU_NODE_RETURN(false);
}
//----------------------------------------------------------------------

PatternBlock::PatternBlock(Context* context, const char *name)
    : Function(context,
               name, NodeFunc(0),
               Function::ContextDependent,
               Function::Return, "void",
               Function::Args, "?", Function::Optional, "?varargs",
               Function::Maximum, Function::MaxArgValue,
               Function::End)
{
}


const Type*
PatternBlock::nodeReturnType(const Node *node) const
{
    const Node* n = node->argNode(node->numArgs()-1);
    if (!n) throw UnresolvableSymbolException();
    return n->type();
}

NodeFunc
PatternBlock::func(Node *node) const
{
    if (node)
    {
        const Type *t = node->type();
        const MachineRep *rep = t->machineRep();
        return rep->patternBlockFunc();
    }
    else
    {
        return Function::func(node);
    }
}

} // namespace Mu
