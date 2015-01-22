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

#include "ListType.h"
#include "List.h"
#include <Mu/Function.h>
#include <Mu/ReferenceType.h>
#include <Mu/BaseFunctions.h>
#include <Mu/MemberVariable.h>
#include <Mu/Process.h>
#include <Mu/Thread.h>
#include <Mu/ClassInstance.h>

namespace Mu {
using namespace std;

ListType::ListType(Context* context, const char* name, const Type* type)
    : Class(context, name, 0),
      _elementType(type)
{
    _isMutable = false;
    _isCollection = true;
}

ListType::~ListType()
{
}

void 
ListType::outputValueRecursive(ostream &o,
                               const ValuePointer vp,
                               ValueOutputState& state) const
{
    ClassInstance *obj = *reinterpret_cast<ClassInstance**>(vp);

    if (obj)
    {
        o << "[";

        for (List list(0, obj); *list; ++list)
        {
            list.type()->elementType()->outputValueRecursive(o, list.valuePointer(), state);
            if (list.next()) o << ", ";
        }

        o << "]";
    }
    else
    {
        o << "nil";
    }
}

Type::MatchResult
ListType::match(const Type* t, Bindings& b) const
{
    if (const ListType* ltype = dynamic_cast<const ListType*>(t))
    {
        return elementType()->match(ltype->elementType(), b);
    }
    else
    {
        return Class::match(t, b);
    }
}


void
ListType::load()
{
    USING_MU_FUNCTION_SYMBOLS
    Class::load();

    //
    //  Generate reference type
    //

    String tname = name().c_str();
    String rtname = tname;
    rtname += "&";
    String ename = elementType()->fullyQualifiedName().c_str();
    String ername = ename + "&";
    
    const char* tn  = tname.c_str();
    const char* rn  = rtname.c_str();
    const char* en  = ename.c_str();
    const char* ern = ername.c_str();

    const MachineRep *erep = elementType()->machineRep();

    //
    //  Dereference
    //

    Symbol* s = scope();
    Context* c = context();

    s->addSymbols(new ReferenceType(c, rn, this),
                  
                  new Function(c, tn, BaseFunctions::dereference,
                               Cast, Return, tn, Args, tn,
                               End),

                  new Function(c, tn, ListType::construct_aggregate, 
                               Mapped,
                               Args, en, Optional, "?+", Maximum, 999999,
                               Return, tn, End),
                  
                  new Function(c, "=", BaseFunctions::assign,
                               Function::MemberOperator | Function::Operator,
                               Return, rn,
                               Args, rn, tn, End),
                  
                  new Function(c, "eq", BaseFunctions::eq, CommOp,
                               Return, "bool",
                               Args, tn, tn, End),
                  
                  EndArguments);

    globalScope()->addSymbols( new Function(c, "cons", ListType::cons, Mapped,
                                            Return, tn,
                                            Args, en, tn, End),

                               new Function(c, "tail", ListType::tail, Mapped,
                                            Return, tn,
                                            Args, tn, End),

                               new Function(c, "head", head, Mapped,
                                            Return, en,
                                            Args, tn, End),
                                            
                               EndArguments);

    addSymbols( new MemberVariable(c, "value", en),
                new MemberVariable(c, "next", tn),
                EndArguments);

    freeze();
}

void
ListType::freeze()
{
    Class::freeze();
    _valueOffset = memberVariables()[0]->instanceOffset();
    _nextOffset = memberVariables()[1]->instanceOffset();
    _isGCAtomic = false;
}

MU_NODE_IMPLEMENTATION(ListType::construct_aggregate, Pointer)
{
    Process*        p    = MU_NODE_THREAD.process();
    const ListType* c    = static_cast<const ListType*>(MU_NODE_THIS.type());
    const Node*     n    = 0;

    List list(static_cast<const ListType*>(MU_NODE_THIS.type()), p);

    for (size_t i=0; n = MU_NODE_THIS.argNode(i); i++)
    {
        list.append(MU_NODE_THREAD, MU_NODE_THIS.argNode(i));
    }

    MU_NODE_RETURN(list.head());
}

MU_NODE_IMPLEMENTATION(ListType::construct_aggregate, ClassInstance*)
{
    Process*        p    = MU_NODE_THREAD.process();
    const ListType* c    = static_cast<const ListType*>(MU_NODE_THIS.type());
    const Node*     n    = 0;

    List list(static_cast<const ListType*>(MU_NODE_THIS.type()), p);

    List list(static_cast<const ListType*>(MU_NODE_THIS.type()),
              MU_NODE_THREAD,
              MU_NODE_THIS.argNode(0));

    for (size_t i=0; n = MU_NODE_THIS.argNode(i); i++)
    {
        list.append(MU_NODE_THREAD, MU_NODE_THIS.argNode(i));
    }

    MU_NODE_RETURN(list.head());
}


MU_NODE_IMPLEMENTATION(ListType::cons, ClassInstance*)
{
    Process*        p     = MU_NODE_THREAD.process();
    const ListType* c     = static_cast<const ListType*>(MU_NODE_THIS.type());
    const Type*     etype = c->elementType();
    ClassInstance*  head  = ClassInstance::allocate(c);
    ClassInstance** next  = (ClassInstance**)(head->structure() + c->nextOffset());

    MU_NODE_DECLARE_TYPE_ARG(etype, value, 0);
    MU_NODE_DECLARE_ARG(ClassInstance*, nextP, 1);
    *next = nextP;
    MU_NODE_RETURN(head);
}

MU_NODE_IMPLEMENTATION(ListType::tail, ClassInstance*)
{
    MU_NODE_DECLARE_ARG(ClassInstance*, head, 0);
    if (!head) throw NilArgumentException(MU_NODE_THREAD);           
    const ListType *c = static_cast<const ListType*>(MU_NODE_THIS.type());
    ClassInstance** next = (ClassInstance**)(head->structure() + c->nextOffset());
    MU_NODE_RETURN(*next);
}

MU_NODE_GENERIC_IMPLEMENTATION(ListType::head)
{
    MU_NODE_DECLARE_ARG(ClassInstance*, head, 0);
    if (!head) throw NilArgumentException(MU_NODE_THREAD);
    const ListType *c = static_cast<const ListType*>(head->type());
    c->copy(head->structure() + c->valueOffset(), MU_NODE_RLOC);
}

} // namespace Mu
