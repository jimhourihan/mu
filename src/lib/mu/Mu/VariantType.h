#ifndef __Mu__VariantType__h__
#define __Mu__VariantType__h__
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
#include <Mu/Class.h>

namespace Mu {
class VariantTagType;

//
//  class VariantType
//
//  A disjoint (tagged) union type. No value is of VariantType. A
//  value must be a VariantTagType. A variable may be a VariantType
//  but not a VariantTagType (although this restriction could be
//  lifted).
//

class VariantType : public Type
{
public:
    //
    //  Types
    //

    //
    //  Construction
    //
    //  You can create a VariantType in two steps:
    //
    //  1) Create the type and add it to the scope you want:
    //
    //      VariantType* t = new VariantType("Foo");
    //      scope->addSymbol(t);
    //
    //  2) Create (and add) the VariantTagTypes
    //
    //      t->addSymbols( VariantTagType("A", "int"),
    //                     VariantTagType("B", "float"),
    //                     VariantTagType("C", "string"),
    //                     EndArguments );
    //

    //
    //  When using this constructor, ancillary functions are created
    //  for you. There should be an even number of arguments to the
    //  function.
    //

    VariantType(Context* context, const char* name);

    virtual ~VariantType();

    virtual void addSymbol(Symbol*);
    size_t numTagTypes() const { return _numTags; }

    //
    //  Type and Symbol API
    //

    virtual MatchResult match(const Type*, Bindings&) const;
    virtual Object* newObject() const;
    virtual size_t objectSize() const;
    virtual void nodeEval(void*, const Node*,Thread &t) const;
    virtual void outputValue(std::ostream&, const Value&, bool full=false) const;
    virtual void outputValueRecursive(std::ostream&, const ValuePointer, ValueOutputState&) const;
    virtual void constructInstance(Pointer) const;
    virtual void copyInstance(Pointer, Pointer) const;

protected:
    virtual void load();

private:
    static MU_NODE_DECLARATION(match, void);

private:
    size_t          _numTags;
};

} // namespace Mu

#endif // __Mu__VariantType__h__
