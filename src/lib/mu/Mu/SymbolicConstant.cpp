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

#include <Mu/SymbolicConstant.h>
#include <Mu/Context.h>
#include <Mu/Type.h>

namespace Mu {
using namespace std;

SymbolicConstant::SymbolicConstant(Context* context,
                                   const char *name,
				   const Type *type,
				   const Value &v)
    : Symbol(context, name), _value(v)
{
    _type.symbol = type;
    _state = ResolvedState;
}

SymbolicConstant::SymbolicConstant(Context* context,
                                   const char *name,
				   const char *type,
				   const Value &v)
    : Symbol(context, name), _value(v)
{
    _type.name = context->internName(type).nameRef();
}

SymbolicConstant::~SymbolicConstant()
{
}

const Type* 
SymbolicConstant::nodeReturnType(const Node*) const
{
    if (!isResolved()) resolve();
    return type();
}

void 
SymbolicConstant::outputNode(std::ostream& o,const Node*) const
{
    output(o);
}

void
SymbolicConstant::output(std::ostream& o) const
{
    Symbol::output(o);

    o << " = "
      << type()->fullyQualifiedName()
      << " ";
    
    type()->outputValue(o, _value);
}

bool
SymbolicConstant::resolveSymbols() const
{
    if (const Type *s = 
	globalScope()->findSymbolOfType<Type>(Name(_type.name)))
    {
	_type.symbol = s;
	return true;
    }
    else
    {
	return false;
    }
}

const Type* 
SymbolicConstant::type() const
{
    if (!isResolved()) resolve();
    return static_cast<const Type*>(_type.symbol);
}


} // namespace Mu
