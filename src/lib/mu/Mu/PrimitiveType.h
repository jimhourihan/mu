#ifndef __Mu__PrimitiveType__h__
#define __Mu__PrimitiveType__h__
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

#include <Mu/Type.h>

namespace Mu {

//
//  class PrimitiveType
//
//  A Primitive type is different from other types in that its value
//  can be stored directly in a Value -- i.e. it does not require a
//  Object in order to store the value. (As opposed to Class which is
//  also a type and which must store its value in a ClassInstance).
//

class PrimitiveType : public Type
{
  public:
    PrimitiveType(Context* context, const char *name, const MachineRep*);
    virtual ~PrimitiveType();

    //
    //	Return a new Object which will hold a primitive type (this
    //	will actually return a PrimitiveObject).
    //

    virtual Object*		newObject() const = 0;

    //
    //  The object size is the size of the primitive. 
    //

    virtual size_t              objectSize() const;

    //
    //  Sets the memory to 0
    //
    
    virtual void                constructInstance(Pointer) const;
    virtual void                copyInstance(Pointer, Pointer) const;
};



} // namespace Mu

#endif // __Mu__PrimitiveType__h__

