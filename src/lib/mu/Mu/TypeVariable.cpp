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

#include <Mu/Class.h>
#include <Mu/Context.h>
#include <Mu/FunctionType.h>
#include <Mu/Interface.h>
#include <Mu/MachineRep.h>
#include <Mu/Module.h>
#include <Mu/NilType.h>
#include <Mu/ReferenceType.h>
#include <Mu/TypePattern.h>
#include <Mu/TypeVariable.h>
#include <Mu/Value.h>
#include <iostream>
#include <string.h>

namespace Mu {
using namespace std;

TypeVariable::TypeVariable(Context* context, const char *name) 
    : Type(context, name, VoidRep::rep())
{
    _isTypeVariable = true;
}

TypeVariable::~TypeVariable()
{
}

Type::MatchResult
TypeVariable::match(const Type* type, Bindings& bindings) const
{
    Bindings::iterator i = bindings.find(this);

    if (i != bindings.end())
    {
        return (*i).second == type ? Match : Conflict;
    }
    else
    {
        bindings[this] = type;
        return Match;
    }
}

Object*
TypeVariable::newObject() const 
{ 
    return 0; 
}

void 
TypeVariable::outputValue(std::ostream& o, Value& value) const
{
    o << "\"" << name() << "\" is a type variable";
}

Value
TypeVariable::nodeEval(const Node* n, Thread &t) const
{
    //
    //  An exception *should* be thrown by whatever function is called
    //  here.
    //

    (*n->func()._voidFunc)(*n, t);
    return Value(); 
}

void
TypeVariable::nodeEval(void*, const Node*,Thread &t) const
{
    return;
}

const Type*
TypeVariable::nodeReturnType(const Node*) const
{
    if (globalModule())
    {
        return globalModule()->context()->unresolvedType();
    }
    else
    {
        return this;
    }
}


} // Namespace  Mu
