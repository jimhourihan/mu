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

#include <Mu/MemberFunction.h>
#include <Mu/Class.h>

namespace Mu {
using namespace std;

MemberFunction::MemberFunction(Context* context, const char *name) 
    : Function(context, name), _offset(0), _destructor(false)
{
    _method = true;
}

MemberFunction::MemberFunction(Context* context,
                               const char *name, 
			       NodeFunc func, 
                               Function::Attributes attributes, ...)
    : Function(context, name), _offset(0)
{
    _method = true;
    _destructor = attributes & Destructor;
    va_list ap;
    va_start(ap, attributes);
    init(func, attributes, ap);
    va_end(ap);
}

MemberFunction::MemberFunction(Context* context,
                               const char* name, 
			       const Type* returnType,
			       int nparams, 
			       ParameterVariable** v, 
			       Node* n,
			       Attributes attributes)
    : Function(context, name, returnType, nparams, v, n, attributes), 
      _offset(0)
{
    _method = true;
    _destructor = attributes & Destructor;
}

MemberFunction::MemberFunction(Context* context,
                               const char* name, 
			       const Type* returnType,
			       int nparams, 
			       ParameterVariable** v, 
			       NodeFunc f,
			       Attributes attributes)
    : Function(context, name, returnType, nparams, v, f, attributes), 
      _offset(0)
{
    _method = true;
    _destructor = attributes & Destructor;
}

MemberFunction::~MemberFunction() {}

void
MemberFunction::output(std::ostream& o) const
{
    Function::output(o);
    o << " (member)";
}

bool
MemberFunction::isConstructor() const
{
    return name() == scope()->name();
}

Class*
MemberFunction::memberClass()
{
    return dynamic_cast<Class*>(scope());
}

const Class*
MemberFunction::memberClass() const
{
    return dynamic_cast<const Class*>(scope());
}

bool
MemberFunction::matches(const Function* f) const
{
    if (name() == f->name())
    {
	int n = numArgs();
	if (n == f->numArgs())
	{
	    if (returnTypeName() == f->returnTypeName())
	    {
		for (int i=1; i<n; i++)
		{
		    if (argTypeName(i) != f->argTypeName(i)) return false;
		}

		return true;
	    }
	}
    }

    return false;
}



void
MemberFunction::findOverridingFunctions(MemberFunctionVector& funcs) const
{
    const Class* c = memberClass();
    c->findOverridingFunctions(this, funcs);
}

} // namespace Mu
