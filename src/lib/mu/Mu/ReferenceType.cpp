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

#include <Mu/Function.h>
#include <Mu/ReferenceType.h>
#include <iostream>
#include <Mu/MachineRep.h>
#include <assert.h>

namespace Mu {

using namespace std;

ReferenceType::ReferenceType(Context* context, const char *typeName, Type *type)
    : Type(context, typeName)
{
    assert(type->_referenceType == 0);
    type->_referenceType = this;

    _isRefType = true;
    _type      = type;
}

Object*
ReferenceType::newObject() const
{ 
    return 0; 
}

void
ReferenceType::load()
{
    // nothing
}

Value 
ReferenceType::nodeEval(void* lval, const Node *n, Thread &thread) const
{
    (*n->func()._PointerFunc)(*n,thread,lval);
}

void
ReferenceType::nodeEval(void *p, const Node *n, Thread &thread) const
{
    Pointer *pp = reinterpret_cast<Pointer*>(p);
    *pp = (*n->func()._PointerFunc)(*n,thread);
}

void 
ReferenceType::outputValue(ostream &o, const Value &value, bool full) const
{
    ValueOutputState state(o, full);
    outputValueRecursive(o, ValuePointer(&value._Pointer), state);
}

void 
ReferenceType::outputValueRecursive(ostream &o,
                                    const ValuePointer p,
                                    ValueOutputState& state) const
{
    const ValuePointer dp = *reinterpret_cast<ValuePointer*>(p);
    dereferenceType()->outputValueRecursive(o, dp, state);
}

Type::MatchResult
ReferenceType::match(const Type *t, Bindings&) const
{
    return this == t ? Match : NoMatch;
}

} // namespace Mu
