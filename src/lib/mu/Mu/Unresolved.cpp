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

#include <Mu/Unresolved.h>
#include <Mu/Module.h>
#include <Mu/Context.h>
#include <Mu/MachineRep.h>

namespace Mu {
using namespace std;

UnresolvedSymbol::UnresolvedSymbol(Context* context, const char* n) 
    : Symbol(context, n) 
{
    _datanode = true;
}

UnresolvedSymbol::~UnresolvedSymbol() {}

const Type*
UnresolvedSymbol::nodeReturnType(const Node*) const
{
    const Context* c = globalModule()->context();
    return c->unresolvedType();
}

UnresolvedType::UnresolvedType(Context* context) 
    : Type(context, "type*", VoidRep::rep())
{
    _isUnresolvedType = 1;
}

Object*
UnresolvedType::newObject() const 
{ 
    return 0; 
}


Value
UnresolvedType::nodeEval(const Node* n, Thread &t) const
{
    //
    //  An exception *should* be thrown by whatever function is called
    //  here.
    //

    (*n->func()._voidFunc)(*n, t);
    return Value(); 
}

void
UnresolvedType::nodeEval(void*, const Node*,Thread &t) const
{
    return;
}


UnresolvedCall::UnresolvedCall(Context* context) 
    : UnresolvedSymbol(context, "call*") 
{
}

UnresolvedCall::~UnresolvedCall() {}

UnresolvedCast::UnresolvedCast(Context* context) 
    : UnresolvedSymbol(context, "cast*") 
{
}

UnresolvedCast::~UnresolvedCast() {}

UnresolvedConstructor::UnresolvedConstructor(Context* context) 
    : UnresolvedSymbol(context, "constructor*") 
{
}

UnresolvedConstructor::~UnresolvedConstructor() {}


UnresolvedReference::UnresolvedReference(Context* context) 
    : UnresolvedSymbol(context, "ref*") 
{
}

UnresolvedReference::~UnresolvedReference() {}

UnresolvedDereference::UnresolvedDereference(Context* context) 
    : UnresolvedSymbol(context, "deref*") 
{
}

UnresolvedDereference::~UnresolvedDereference() {}

UnresolvedMemberReference::UnresolvedMemberReference(Context* context) 
    : UnresolvedSymbol(context, "member_ref*") 
{
}

UnresolvedMemberReference::~UnresolvedMemberReference() {}

UnresolvedMemberCall::UnresolvedMemberCall(Context* context) 
    : UnresolvedSymbol(context, "member_call*") 
{
}

UnresolvedMemberCall::~UnresolvedMemberCall() {}

UnresolvedStackReference::UnresolvedStackReference(Context* context) 
    : UnresolvedSymbol(context, "stack_ref*") 
{
}

UnresolvedStackReference::~UnresolvedStackReference() {}


UnresolvedStackDereference::UnresolvedStackDereference(Context* context) 
    : UnresolvedSymbol(context, "stack_deref*") 
{
}

UnresolvedStackDereference::~UnresolvedStackDereference() {}

UnresolvedDeclaration::UnresolvedDeclaration(Context* context) 
    : UnresolvedSymbol(context, "declaration*") 
{
}

UnresolvedDeclaration::~UnresolvedDeclaration() {}

UnresolvedAssignment::UnresolvedAssignment(Context* context) 
    : UnresolvedSymbol(context, "assign*") 
{
}

UnresolvedAssignment::~UnresolvedAssignment() {}


} // namespace Mu
