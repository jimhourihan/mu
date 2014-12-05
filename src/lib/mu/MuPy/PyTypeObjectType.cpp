//
//  Copyright (c) 2011, Jim Hourihan
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
//     * Neither the name of the Mu project nor the names of its
//       contributors may be used to endorse or promote products
//       derived from this software without specific prior written
//       permission.
// 
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
//  TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
//  PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
//  HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
//  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
//  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
//  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
//  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
#include "Python.h"
#include "object.h"
#include "PyTypeObjectType.h"
#include <Mu/Function.h>
#include <Mu/MachineRep.h>
#include <Mu/Node.h>
#include <Mu/NodeAssembler.h>
#include <Mu/ReferenceType.h>
#include <Mu/SymbolicConstant.h>
#include <Mu/Value.h>
#include <Mu/config.h>
#include <iostream>

namespace Mu {
using namespace std;

PyTypeObjectType::PyTypeObjectType(Context* c, const char* name) 
    : OpaqueType(c, name)
{
}

PyTypeObjectType::~PyTypeObjectType() {}

void 
PyTypeObjectType::outputValue(ostream &o, const Value &value, bool full) const
{
    o << "<#" << fullyQualifiedName() << " ";

    if (value._Pointer)
    {
        PyTypeObject* t = reinterpret_cast<PyTypeObject*>(value._Pointer);
        o << t->tp_name;
    }
    else
    {
        o << "nil";
    }

    o << ">";
}

void
PyTypeObjectType::outputValueRecursive(ostream &o, 
                                 const ValuePointer vp,
                                 ValueOutputState& state) const
{
    Pointer p = *reinterpret_cast<Pointer*>(vp);

    o << "<#" << fullyQualifiedName() << " ";

    if (p)
    {
        PyTypeObject* t = reinterpret_cast<PyTypeObject*>(p);
        o << t->tp_name;
    }
    else
    {
        o << "nil";
    }

    o << ">";
}

void
PyTypeObjectType::load()
{
    OpaqueType::load();

    USING_MU_FUNCTION_SYMBOLS;
    Symbol *s = scope();

    string rname = name();
    rname += "&";
    const char* n = fullyQualifiedName().c_str();
    string nref = n;
    nref += "&";
    const char* nr = nref.c_str();

    Context* c = context();

    globalScope()->addSymbols(

		   EndArguments);

}

} // Mu

