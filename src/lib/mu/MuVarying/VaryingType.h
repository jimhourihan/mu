#ifndef __MuLang__VaryingType__h__
#define __MuLang__VaryingType__h__
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

namespace Mu {

//
//  class VaryingType
//
//  In some sense, the VaryingType is a limited case of the fixed
//  ArrayType. However, there are no operators or functions that allow the
//  user to access the internal state on a per-element basis. The point
//  being, the type should be completely opaque to the user.
//
//  The VaryingType requires support in the Thread object in order to
//  work correctly. There is only one size for varying objects in a
//  particular Process.
//
//  Note that assignment makes a copy for varying types. 
//

class VaryingType : public Type
{
  public:
    VaryingType(Context* c, const char *name, const Type *elementType);
    ~VaryingType();

    const Type* elementType() const { return _elementType; }
    const MachineRep* elementRep() const { return elementType()->machineRep(); }

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

    static NODE_DECLARAION(constant, Pointer);
    static NODE_DECLARAION(dereference, Pointer);
    static NODE_DECLARAION(construct, Pointer);
    static NODE_DECLARAION(retain, Pointer);
    static NODE_DECLARAION(release, Pointer);

  private:
    const Type*   _elementType;
};



} // namespace Mu

#endif // __MuLang__VaryingType__h__
