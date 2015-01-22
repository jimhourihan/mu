#ifndef __Mu__VariantTagType__h__
#define __Mu__VariantTagType__h__
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
#include <Mu/VariantType.h>

namespace Mu {

//
//  A VariantTagType is a *subclass* of its VariantType
//

class VariantTagType : public Type
{
public:

    //
    //  You can make a VariantTagType with either the type or the name
    //  of the type.
    //

    VariantTagType(Context* context, const char* name, const Type* repType);
    VariantTagType(Context* context, const char* name, const char* repType);
    virtual ~VariantTagType();

    const Type* representationType() const;

    const VariantType* variantType() const 
        { return static_cast<const VariantType*>(scope()); }

    size_t index() const { return _index; }

    //
    //  Type API
    //


    virtual void                serialize(std::ostream&, Archive::Writer&, const ValuePointer) const;
    virtual void                deserialize(std::istream&, Archive::Reader&, ValuePointer) const; 
    virtual void                reconstitute(Archive::Reader&, Object*) const;

    virtual MatchResult match(const Type*, Bindings&) const;
    virtual Object* newObject() const;
    virtual size_t objectSize() const;
    virtual void nodeEval(void*, const Node*,Thread &t) const;
    virtual const Type* nodeReturnType(const Node*) const;

    virtual void            outputValueRecursive(std::ostream&, const ValuePointer, ValueOutputState&) const;
    virtual const Type*     fieldType(size_t) const;
    virtual ValuePointer    fieldPointer(Object*, size_t) const;
    virtual const ValuePointer  fieldPointer(const Object*, size_t) const;
    virtual void            constructInstance(Pointer) const;
    virtual void            copyInstance(Pointer, Pointer) const;
    
    //
    //  Nodes
    //

    static MU_NODE_DECLARATION(upcast, Pointer);

protected:
    virtual void load();
    virtual bool resolveSymbols() const;

private:
    mutable SymbolRef  _repType;
    size_t             _index;

    friend class VariantType;
};


} // namespace Mu

#endif // __Mu__VariantTagType__h__
