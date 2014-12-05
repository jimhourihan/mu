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

#include <Mu/ReferenceType.h>
#include <Mu/Context.h>
#include <Mu/Type.h>
#include <Mu/Variable.h>
#include <iostream>

namespace Mu {

using namespace std;

Variable::Variable(Context* context, 
                   const char *name, 
		   const Type *storageClass, 
		   int address,
		   Variable::Attributes attributes) 
    : Symbol(context, name)
{
    _type 	 = storageClass;
    _state	 = ResolvedState;
    _address     = address;
    _initialized = 0;
    init(attributes);
    resolveSymbols();
}

Variable::Variable(Context* context, 
                   const char *name, 
		   const char *storageClass,
		   int address,
		   Variable::Attributes attributes) 
    : Symbol(context, name)
{
    _type 	 = SymbolRef(context->internName(storageClass));
    _state	 = UntouchedState;
    _address	 = address;
    _initialized = 0;
    init(attributes);
}

Variable::~Variable() {}

void
Variable::init(Attributes attributes)
{
    _readable     = attributes &     Readable;
    _writable     = attributes &     Writable;
    _singleUse    = attributes &    SingleUse;
    _singleAssign = attributes & SingleAssign;
    _implicitType = attributes & ImplicitType;
}

Variable::Attributes
Variable::attributes() const
{
    return  (_readable      ? Readable      : NoVariableAttr) &
            (_writable      ? Writable      : NoVariableAttr) &
            (_singleAssign  ? SingleAssign  : NoVariableAttr) &
            (_implicitType  ? ImplicitType  : NoVariableAttr) &
            (_singleUse     ? SingleUse     : NoVariableAttr);
}

const Type*
Variable::storageClass() const
{ 
    if (!isResolved()) resolve();

    if (symbolState() == ResolvedState)
    {
        return static_cast<const Type*>(_type.symbol);
    }
    else
    {
        return 0;
    }
}

Name
Variable::storageClassName() const
{
    if (isResolved()) return storageClass()->fullyQualifiedName();
    else return _type.name;
}

void
Variable::setStorageClass(const Type* t)
{
    _type.symbol = t;
}

void 
Variable::output(ostream &o) const
{
    Symbol::output(o);
    o << " (" << storageClass()->fullyQualifiedName() << ")";
}

bool 
Variable::resolveSymbols() const
{
    if (isResolved()) return true;
    Name n = _type.name;

    Symbol::ConstSymbolVector symbols = globalScope()->findSymbolsOfType<Type>(n);

    if (symbols.size() == 1)
    {
        _type.symbol = symbols.front();
	return true;
    }
    else
    {
	//cerr << "Variable::resolveSymbols() cant find "
	    //"type " << n << endl;
	return false;
    }
}

const Type*
Variable::nodeReturnType(const Node*) const
{
    if (!isResolved()) resolve();
    const Type* t = static_cast<const Type*>(_type.symbol);

    if ( t && t->referenceType() ) return t->referenceType();
    else return t;
}

const Function* Variable::referenceFunction() const { return 0; }
const Function* Variable::extractFunction() const { return 0; }

void
Variable::symbolDependancies(ConstSymbolVector& symbols) const
{
    if (symbolState() != ResolvedState) resolveSymbols();
    symbols.push_back(storageClass());
}

} // namespace Mu

