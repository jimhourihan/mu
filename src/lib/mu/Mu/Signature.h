#ifndef __Mu__Signature__h__
#define __Mu__Signature__h__
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
#include <Mu/HashTable.h>
#include <Mu/Type.h>
#include <vector>

namespace Mu {
class Signature;
class Context;

//----------------------------------------------------------------------
//
//  class Signature
//
//  This class is produced after functions are resolved.
//

class Signature /*: public Type*/
{
  public:
    MU_GC_STUBBORN_NEW_DELETE

    //
    //  Types
    //

    typedef Symbol::SymbolRefList Types;
    typedef Symbol::SymbolRef SymbolRef;

    //
    //  Constructor / Destructor
    //

    Signature() : _resolved(false), _typesIn(false) {}
    // Signature(const char*);
    ~Signature();

    bool operator==(const Signature& other) const;

    size_t size() const { return _types.size(); }

    void push_back(const Type* t);
    void push_back(Name);

    const Types& types() const { return _types; }

    SymbolRef& operator[] (size_t i) { return _types[i]; }
    const SymbolRef& operator[] (size_t i) const { return _types[i]; }

    bool resolved() const { return _resolved; }
    void resolve(const Context*) const; 

    String functionTypeName() const;

    const Type* argType(size_t i) const { return _types[i+1].symbolOfType<Type>(); }
    const Type* returnType() const { return _types[0].symbolOfType<Type>(); }

  private:
    mutable Types       _types;
    mutable bool        _resolved : 1;
    bool                _typesIn  : 1;
};

struct SignatureTraits
{
    static bool equals(const Signature *a, const Signature *b) 
        { return *a == *b; }
    static unsigned long hash(const Signature*);
};

typedef HashTable<Signature*,SignatureTraits> SignatureHashTable;

} // namespace Mu

#endif // __Mu__Signature__h__
