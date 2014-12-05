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

#include "TupleType.h"
#include <Mu/BaseFunctions.h>
#include <Mu/ClassInstance.h>
#include <Mu/Function.h>
#include <Mu/MemberVariable.h>
#include <Mu/ParameterVariable.h>
#include <Mu/ReferenceType.h>
#include <Mu/Thread.h>
#include <stdio.h>

namespace Mu {
using namespace std;

TupleType::TupleType(Context* context, const char* name, const Types& types)
    : Class(context, name),
      _types(types)
{
    _isMutable = false;
}

TupleType::~TupleType()
{
}

void 
TupleType::outputValueRecursive(ostream &o, 
                                const ValuePointer valuePtr, 
                                ValueOutputState& state) const
{
    if (!valuePtr) return;
    ClassInstance *obj = *reinterpret_cast<ClassInstance**>(valuePtr);

    if (obj)
    {
        o << "(";

        if (state.traversedObjects.find(obj) != state.traversedObjects.end())
        {
            o << "...ad infinitum...";
        }
        else
        {
            state.traversedObjects.insert(obj);
        
            for (int i=0, s=memberVariables().size(); i < s; i++)
            {
                if (i) o << ", ";
                const Type* t = fieldType(i);
                t->outputValueRecursive(o, obj->field(i), state);
            }

            //state.traversedObjects.erase(obj);
        }

        o << ")";
    }
    else
    {
        o << "nil";
    }
}

void
TupleType::load()
{
    USING_MU_FUNCTION_SYMBOLS;
    STLVector<ParameterVariable*>::Type params;
    Context* c = context();

    for (int i=0; i < _types.size(); i++)
    {
        char name[80];
        sprintf(name, "_%d", i);
        const Type* t = _types[i];
        addSymbol(new MemberVariable(c, name, t));
        params.push_back(new ParameterVariable(c, name, t));
    }

    String rname = name();
    rname += "&";
    const char* n = name().c_str();
    const char* fn = fullyQualifiedName().c_str();
    const char* rn = rname.c_str();

    Symbol* g = globalScope();

    g->addSymbol(new ReferenceType(c, rn, this));

    g->addSymbol(new Function(c, n, BaseFunctions::dereference, Cast,
                              Return, n,
                              Args, rn, End));

    g->addSymbol(new Function(c, "=", BaseFunctions::assign, AsOp,
                              Return, rn, 
                              Args, rn, n, End));
                  
    g->addSymbol(new Function(c, n, defaultConstructor, None,
                              Return, fn,
                              End));
                  
    g->addSymbol(new Function(c, n, this,
                              params.size(), &params.front(),
                              aggregateConstructor, Mapped));

//                 EndArguments );
    
    addSymbols( new Function(c, "__allocate", defaultConstructor, None,
                             Return, fn,
                             End),
                
                EndArguments );
}

NODE_IMPLEMENTATION(TupleType::defaultConstructor, Pointer)
{
    Process *p = NODE_THREAD.process();
    const TupleType *c = static_cast<const TupleType*>(NODE_THIS.type());
    //ClassInstance *o = new ClassInstance(c, p, Object::Heap);
    ClassInstance *o = ClassInstance::allocate(c);
    NODE_RETURN(Pointer(o));
}

NODE_IMPLEMENTATION(TupleType::aggregateConstructor, Pointer)
{
    Process* p = NODE_THREAD.process();
    const TupleType* c = static_cast<const TupleType*>(NODE_THIS.type());
    //ClassInstance* o = new ClassInstance(c, p, Object::Heap);
    ClassInstance* o = ClassInstance::allocate(c);
    const Node* n = 0;

    for (size_t i=0; n = NODE_THIS.argNode(i); i++)
    {
	o->fieldType(i)->nodeEval(o->field(i), n, NODE_THREAD);
    }

    NODE_RETURN(Pointer(o));
}

} // namespace Mu
