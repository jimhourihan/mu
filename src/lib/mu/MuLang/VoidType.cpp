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
#include "VoidType.h"
#include <iostream>
#include <Mu/Value.h>
#include <Mu/Function.h>
#include <Mu/BaseFunctions.h>
#include <Mu/Node.h>
#include <Mu/NodeAssembler.h>
#include <Mu/MachineRep.h>

namespace Mu {
using namespace std;

VoidType::VoidType(Context* c) : PrimitiveType(c, "void",VoidRep::rep())
{
}


VoidType::~VoidType() {}

PrimitiveObject*
VoidType::newObject() const
{
    return new PrimitiveObject(this);
}

Value 
VoidType::nodeEval(const Node *n, Thread &thread) const
{
    (*n->func()._voidFunc)(*n,thread);
    return Value();
}

void
VoidType::nodeEval(void*, const Node *n, Thread &thread) const
{
    (*n->func()._voidFunc)(*n,thread);
}

void 
VoidType::constructInstance(Pointer) const
{
    // nothing
}

void 
VoidType::outputValue(ostream &o, const Value &value, bool full) const
{
    o << "void";

}

void
VoidType::outputValueRecursive(std::ostream& o, const ValuePointer, ValueOutputState&) const
{
    o << "void";
}

void
VoidType::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    Symbol* s = scope();
    Context* c = context();

    s->addSymbols( new Function(c, "void", machineRep()->simpleBlockFunc(), Cast,
				Return, "void",
				Args, "?", End),
		   EndArguments );

}

} // namespace Mu

