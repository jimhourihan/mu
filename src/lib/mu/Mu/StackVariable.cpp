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

#include <Mu/Type.h>
#include <Mu/StackVariable.h>
#include <Mu/MachineRep.h>
#include <iostream>
#include <Mu/ReferenceType.h>

namespace Mu {

using namespace std;

StackVariable::StackVariable(Context* context,
                             const char *name,
			     const Type *storageClass,
			     int stackPos,
                             Attributes a)
    : Variable(context, name, storageClass, stackPos, a)
{
}

StackVariable::StackVariable(Context* context,
                             const char *name,
			     const char *storageClass,
			     int stackPos,
                             Attributes a)
    : Variable(context, name, storageClass, stackPos, a)
{
}

StackVariable::~StackVariable() {}

String
StackVariable::mangledName() const
{
    static const char* cppkeywords[] =
    { 
        "this", "switch", "default", "auto", "case", "return",
        "throw", "catch", "template", "class", "private", "public",
        "protected", 
        NULL
    };

    for (const char** k = cppkeywords; *k; k++)
    {
        if (name() == *k)
        {
            String o = "__";
            o += name().c_str();
            return o;
        }
    }

    return name();
}

const Type*
StackVariable::nodeReturnType(const Node* n) const
{
    const Type* t = storageClass();

    if (t->isTypePattern())
    {
        return t->nodeReturnType(n);
    }
    else
    {
        const MachineRep* rep = t->machineRep();

        if (n->func() && n->func() == rep->referenceStackFunc())
        {
            return t->referenceType();
        }
        else
        {
            return t;
        }
    }
}

void 
StackVariable::output(ostream &o) const
{
    Variable::output(o);
    o << " (on stack)";
}

void
StackVariable::outputNode(std::ostream &o, const Node *n) const
{
    o << n->type()->name() << " stack " << name();
}

} // namespace Mu
