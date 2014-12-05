#ifndef __Mu__SymbolTable__h__
#define __Mu__SymbolTable__h__
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

#include <Mu/config.h>
#include <Mu/StringHashTable.h>
#include <Mu/Symbol.h>

namespace Mu {

//
//  class SymbolTable
//
//  Manages symbols for a scope. Uses HashTable<> to store them.
//

class SymbolTable
{
    struct SymbolTraits
    {
	static bool equals(const Symbol* a, const Symbol* b)
	    { return a->name() == b->name(); }
	static unsigned long hash(const Symbol *s)
	    { return (s->name().hash()); }
    };

  public:
    MU_GC_NEW_DELETE
    typedef HashTable<Symbol*,SymbolTraits> SymbolHashTable;
    typedef SymbolHashTable::Item Item;

    class Iterator
    {
      public:
        Iterator(SymbolTable* t) : _i(t->hashTable()) {}

        const Symbol* operator* () const { return *_i; }
        operator bool () const { return _i; }
        void operator ++ () { ++_i; }

      private:
        SymbolTable::SymbolHashTable::Iterator _i;
    };

    class RecursiveIterator
    {
      public:
        typedef STLVector<SymbolTable::Iterator>::Type ITVector;

        RecursiveIterator(SymbolTable* t);

        const Symbol* operator* () const { return *_itstack.back(); }
        operator bool () const { return _itstack.empty() ? false : bool(_itstack.back()); }
        void operator ++ ();

      private:
        void fillLeaf();
        
      private:
        ITVector _itstack;
    };

    SymbolTable();
    ~SymbolTable();

    //
    //	Adds a symbol to the symbol table.  If there is already an
    //	existing symbol with the same name, then the symbol is added
    //	as an overloaded occurance.
    //

    void		    add(Symbol*);

    //
    //	These functions let you search by symbol name.
    //

    //Symbol*		    find(const String&) const;
    Symbol*		    find(const Name&) const;
    bool		    exists(Symbol*) const;

    SymbolHashTable&	    hashTable() { return _hashTable; }

  private:

  private:
    SymbolHashTable	    _hashTable;
};



} // namespace Mu

#endif // __Mu__SymbolTable__h__
