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

#include <Mu/SymbolTable.h>
#include <iostream>

namespace Mu {
using namespace std;

SymbolTable::RecursiveIterator::RecursiveIterator(SymbolTable* t)
{
    _itstack.push_back(SymbolTable::Iterator(t));
    fillLeaf();
}

void
SymbolTable::RecursiveIterator::fillLeaf()
{
    while (1)
    {
        const Symbol* s = *_itstack.back();
        
        if (SymbolTable* st = s->symbolTable())
        {
            _itstack.push_back(SymbolTable::Iterator(st));
        }
        else
        {
            break;
        }
    }
}

void 
SymbolTable::RecursiveIterator::operator ++ ()
{
    if (!_itstack.empty())
    {
        ++_itstack.back();

        if (!_itstack.empty())
        {
            if (!_itstack.back()) _itstack.pop_back();
            else fillLeaf();
        }
    }
}

static void symboltable_finalizer(void* obj, void* data)
{
    //cout << "FINALIZER: " << obj << endl;
}


SymbolTable::SymbolTable() 
{
    //GC_finalization_proc ofn;
    //void *odata;
    //GC_register_finalizer(this, symboltable_finalizer, 0, &ofn, &odata);
}

SymbolTable::~SymbolTable() {}

void
SymbolTable::add(Symbol* s)
{
    if (const Item *i = _hashTable.find(s))
    {
	i->data()->appendOverload(s);
    }
    else
    {
	_hashTable.add(s);
    }
}

bool
SymbolTable::exists(Symbol *s) const
{
    return _hashTable.find(s) ? true : false;
}

// Symbol*
// SymbolTable::find(const String& s) const
// {
//     if (Name n = Symbol::namePool().find(s))
// 	return find(n);
//     else
// 	return 0;
// }

Symbol*
SymbolTable::find(const Name& name) const
{
    for (const Item *i=_hashTable.firstItemOf(name.hash()); i; i=i->next())
	if (i->data()->name() == name) return i->data();
    return 0;
}


} // namespace Mu
