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

#include <Mu/Alias.h>
#include <Mu/Context.h>
#include <iostream>

namespace Mu {
using namespace std;

Alias::Alias(Context* context, const char* name, Symbol *symbol) 
    : Symbol(context, name)
{
    _symbol.symbol = symbol;
    _state = ResolvedState;
}

Alias::Alias(Context* context, const char* name, const char *symbol)
    : Symbol(context, name)
{
    _symbol.name = context->internName(symbol).nameRef();
}

Alias::~Alias()
{
}

const Type* 
Alias::nodeReturnType(const Node*) const
{
    return 0;
}

void 
Alias::outputNode(std::ostream& o,const Node*) const
{
    output(o);
}

void
Alias::output(std::ostream& o) const
{
    o << fullyQualifiedName() << " -> " << alias()->fullyQualifiedName();
}

bool
Alias::resolveSymbols() const
{
    if (const Symbol *s = 
	globalScope()->findSymbolByQualifiedName(Name(_symbol.name)))
    {
	_symbol.symbol = s;
	return true;
    }
    else
    {
	return false;
    }
}

const Symbol* 
Alias::alias() const
{
    if (!isResolved()) resolve();
    return _symbol.symbol;
}

Symbol* 
Alias::alias()
{
    if (!isResolved()) resolve();
    return const_cast<Symbol*>(_symbol.symbol);
}

void
Alias::set(const Symbol *s)
{
    _symbol.symbol = s;
    _state = ResolvedState;
}

void
Alias::symbolDependancies(ConstSymbolVector& symbols)
{
    if (symbolState() != ResolvedState) resolveSymbols();
    symbols.push_back(alias());
}

} // namespace Mu
