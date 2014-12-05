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

#include <Mu/BaseFunctions.h>
#include <Mu/ClassInstance.h>
#include <Mu/Exception.h>
#include <Mu/Function.h>
#include <Mu/MachineRep.h>
#include <Mu/ReferenceType.h>
#include <Mu/SymbolTable.h>
#include <Mu/VariantInstance.h>
#include <Mu/VariantTagType.h>
#include <Mu/VariantType.h>
#include <algorithm>
#include <typeinfo>

namespace Mu {
using namespace std;

VariantType::VariantType(Context* context, const char* name) 
    : Type(context, name, PointerRep::rep()),
      _numTags(0)
{
    _isPrimitive = false;
}

VariantType::~VariantType() {}

Type::MatchResult
VariantType::match(const Type *type, Bindings& b) const
{
    if (this == type || 
        (dynamic_cast<const VariantTagType*>(type) && 
         type->scope() == this))
    {
        return Match;
    }

    return Type::match(type, b);
}


Object*
VariantType::newObject() const
{
    return 0;
}

size_t
VariantType::objectSize() const
{
    return 0;
}

void
VariantType::constructInstance(Pointer) const
{
    // what to do here?
}

void 
VariantType::copyInstance(Pointer src, Pointer dst) const
{
    reinterpret_cast<VariantInstance*>(src)->tagType()->copyInstance(src, dst);
}

Value
VariantType::nodeEval(const Node* n, Thread& thread) const
{
    return Value((*n->func()._PointerFunc)(*n,thread));
}

void
VariantType::nodeEval(void *p, const Node* n, Thread& thread) const
{
    Pointer *pp = reinterpret_cast<Pointer*>(p);
    *pp = (*n->func()._PointerFunc)(*n,thread);
}

void 
VariantType::outputValue(ostream &o, const Value &value, bool full) const
{
    ValueOutputState state(o, full);
    outputValueRecursive(o, ValuePointer(&value._Pointer), state);
}

void 
VariantType::outputValueRecursive(ostream &o,
                                  const ValuePointer p,
                                  ValueOutputState& state) const
{
    if (p)
    {
        const VariantInstance *i = *reinterpret_cast<const VariantInstance**>(p);
        if (i) i->tagType()->outputValueRecursive(o, p, state);
        else o << "nil";
    }
    else
    {
        o << "nil";
    }
}


void
VariantType::addSymbol(Symbol* s)
{
    if (VariantTagType* tt = dynamic_cast<VariantTagType*>(s))
    {
        tt->_index = _numTags++;
    }

    Type::addSymbol(s);
}

void
VariantType::load()
{
    Type::load();
}

} // namespace Mu
