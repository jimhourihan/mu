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
#include <Mu/BaseFunctions.h>
#include <Mu/GlobalVariable.h>
#include <Mu/ReferenceType.h>
#include <iostream>

namespace Mu {

using namespace std;

GlobalVariable::GlobalVariable(Context* context,
                               const char *name,
			       const Type *storageClass,
			       int offset,
			       Variable::Attributes a,
			       Node *initializer)
    
    : Variable(context, name, storageClass, offset, a),
      _initializer(initializer)
{
}

GlobalVariable::~GlobalVariable() {}

const Type*
GlobalVariable::nodeReturnType(const Node* n) const
{
    if (n->func() == NodeFunc(BaseFunctions::referenceGlobal))
    {
	return storageClass()->referenceType();
    }
    else
    {
	return storageClass();
    }
}


void GlobalVariable::output(ostream &o) const
{
    Variable::output(o);
    o << " (global)";
}

void
GlobalVariable::outputNode(std::ostream &o, const Node *n) const
{
    o << n->type()->name() << " global " << name();
}

} // namespace Mu

