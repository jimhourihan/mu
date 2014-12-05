#ifndef __MuLang__VaryingComponentType__h__
#define __MuLang__VaryingComponentType__h__
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
#include <MuLang/DynamicArrayType.h>
#include <MuLang/FixedArrayType.h>
#include "VaryingFloatType.h"

namespace Mu {

//
//  class VaryingComponentType
//
//  The VaryingComponentType is a slice of a varying vector type. The
//  slice points to the original varying vector object memory. The
//  underlying representation uses the same VaryingObject.
//
//  The type can be cast to a VaryingFloatType, but cannot be stored
//  in a variable, etc. There are no constructors for this type: its
//  returned and taken as an argument to other functions.
//

class VaryingComponentType : public Type
{
  public:
    VaryingComponentType(Context* c, const char *name, const VaryingFloatType*);
    ~VaryingComponentType();

    typedef VaryingComponentType ThisType;

    const Type* varyingFloatType() const { return _varyingFloatType; }
    const MachineRep* floatRep() const 
	{ return varyingFloatType()->machineRep(); }

    //
    //	Symbol API
    //

    virtual Object* newObject() const;
    virtual void deleteObject(Object*) const;
    virtual Value nodeEval(const Node*, Thread&) const;
    virtual void nodeEval(void*, const Node*, Thread&) const;
    virtual DataNode* newNode() const;
    virtual void outputValue(std::ostream&, const Value&) const;
    virtual void load();
    virtual void markRecursive(Object*, bool) const;

    static NODE_DECLARAION(tofloatvarying, Pointer);
    static NODE_DECLARAION(assign, Pointer);
    static NODE_DECLARAION(assignf, Pointer);

  private:
    const Type*   _varyingFloatType;
};



} // namespace Mu

#endif // __MuLang__VaryingComponentType__h__
