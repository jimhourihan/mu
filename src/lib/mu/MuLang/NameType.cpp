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

#include "NameType.h"
#include "StringType.h"
#include <Mu/MachineRep.h>
#include <Mu/Function.h>
#include <Mu/ReferenceType.h>
#include <Mu/Process.h>
#include <Mu/Thread.h>
#include "MuLangContext.h"

namespace Mu {
using namespace std;

NameType::NameType(Context* c) : PrimitiveType(c, "name", PointerRep::rep())
{
}

NameType::~NameType() {}

PrimitiveObject*
NameType::newObject() const
{
    return new PrimitiveObject(this);
}

Value 
NameType::nodeEval(const Node *n, Thread &thread) const
{
    return Value((*n->func()._PointerFunc)(*n,thread));
}

void
NameType::nodeEval(void*, const Node *n, Thread &thread) const
{
    (*n->func()._PointerFunc)(*n,thread);
}

void 
NameType::outputValue(ostream &o, const Value &value, bool full) const
{
    String s = Name(Name::Ref(value._Pointer)).c_str();
    StringType::outputQuotedString(o, s);
}

void
NameType::outputValueRecursive(std::ostream& o,
                               const ValuePointer p,
                               ValueOutputState&) const
{
    Name::Ref* ref = reinterpret_cast<Name::Ref*>(p);
    String s = Name(*ref).c_str();
    StringType::outputQuotedString(o, s);
}

void
NameType::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    //
    //  All of the Int functions are inlined in Native.h
    //  So here the NativeInlined attribute is set in
    //  for all function attributes.
    //

    Mapped  |= NativeInlined;
    CommOp  |= NativeInlined;
    Op      |= NativeInlined;
    AsOp    |= NativeInlined;
    Lossy   |= NativeInlined;
    Cast    |= NativeInlined;

    Symbol *s = scope();

    String tname = fullyQualifiedName();
    String rname = tname + "&";

    const char* tn = tname.c_str();
    const char* rn = rname.c_str();

    Context* c = context();

    s->addSymbols( new ReferenceType(c, "name&", this),

		   new Function(c, "name", NameType::dereference, Cast,
				Return, tn,
				Args, rn, End),

		   EndArguments );

    globalScope()->addSymbols (
                                              
		   new Function(c, "=", NameType::assign, AsOp,
				Return, rn, 
				Args, rn, tn, End),
                   
		   new Function(c, "string", NameType::to_string, Cast,
				Return, "string", 
				Args, tn, End),

		   EndArguments );

}

NODE_IMPLEMENTATION(NameType::dereference, Pointer)
{
    Name::Ref* ip = reinterpret_cast<Name::Ref*>(NODE_ARG(0, Pointer));
    NODE_RETURN(Pointer(*ip));
}

NODE_IMPLEMENTATION(NameType::assign, Pointer)
{
    Name::Ref* ip = reinterpret_cast<Name::Ref*>(NODE_ARG(0, Pointer));
    *ip = NODE_ARG(1, Name::Ref);				 
    NODE_RETURN(Pointer(ip));				
}

NODE_IMPLEMENTATION(NameType::to_string, Pointer)
{
    Process *p = NODE_THREAD.process();
    MuLangContext *c = static_cast<MuLangContext*>(p->context());
    Name name(NODE_ARG(0, Name::Ref));

    NODE_RETURN(c->stringType()->allocate(name));
}

} // namespace Mu

