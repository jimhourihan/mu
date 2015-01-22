#ifndef __MuLang__TupleType__h__
#define __MuLang__TupleType__h__
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
#include <vector>
#include <Mu/Type.h>
#include <Mu/Class.h>
#include <Mu/ClassInstance.h>
#include <Mu/MachineRep.h>

namespace Mu {
class Thread;

class TupleType : public Class
{
  public:
    typedef STLVector<const Type*>::Type Types;

    TupleType(Context* context, const char *name, const Types& fieldTypes);
    ~TupleType();

    virtual void outputValueRecursive(std::ostream&, const ValuePointer, ValueOutputState&) const;
    virtual void load();

    const Types& tupleFieldTypes() const { return _types; }

    static MU_NODE_DECLARATION(defaultConstructor, Pointer);
    static MU_NODE_DECLARATION(aggregateConstructor, Pointer);

  private:
    Types       _types;
};

} // namespace Mu

#endif // __MuLang__TupleType__h__
