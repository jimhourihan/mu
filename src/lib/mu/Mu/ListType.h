#ifndef __MuLang__ListType__h__
#define __MuLang__ListType__h__
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
#include <Mu/ClassInstance.h>

namespace Mu {

//
//  class ListType
//
//  While it makes sense to make ListType a VariantType, it would have
//  different semantics from the other collection classes. Namely,
//  non-primitive types would be copied into the list cell. By making
//  it a Class instead, the List will have the same semantics as array
//  and map.
//

class ListType : public Class
{
public:
    ListType(Context* context, const char* name, const Type* elementType);
    virtual ~ListType();

    virtual MatchResult match(const Type*, Bindings&) const;
    const Type* elementType() const { return _elementType; }

    size_t nextOffset() const { return _nextOffset; }
    size_t valueOffset() const { return _valueOffset; }

    //
    //	Symbol API
    //

    virtual void freeze();

    virtual void outputValueRecursive(std::ostream&, const ValuePointer, ValueOutputState&) const;
    virtual void load();

    static MU_NODE_DECLARATION(construct_aggregate, Pointer);
    static MU_NODE_DECLARATION(cons, Pointer);
    static MU_NODE_DECLARATION(tail, Pointer);
    static MU_NODE_GENERIC_DECLARATION(head);

  private:
    const Type* _elementType;
    size_t      _nextOffset;
    size_t      _valueOffset;
};

} // namespace Mu

#endif // __MuLang__ListType__h__
