#ifndef __MuLang__VaryingVecfType__h__
#define __MuLang__VaryingVecfType__h__
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
#include <Mu/Node.h>
#include "VaryingObject.h"
#include "VaryingType.h"
#include <iosfwd>

namespace Mu {
class VaryingComponentType;

//
//  class VaryingVecfType
//
//  Pile-o-floating-point-numbers class.
//

class VaryingVecfType : public VaryingType
{
  public:
    VaryingVecfType(Context*,
                    const char *name, 
		    const Type* elementType,
		    const VaryingComponentType* componentType);
    ~VaryingVecfType();

    //
    //	Symbol API
    //

    virtual void load();

    //
    //	Functions
    //

    static NODE_DECLARATION(tovarying4_from_vec4,Pointer);
    static NODE_DECLARATION(tovarying3_from_vec3,Pointer);
    static NODE_DECLARATION(tovarying2_from_vec2,Pointer);

    static NODE_DECLARATION(construct_from_varying,Pointer);
    static NODE_DECLARATION(construct_from_1varying,Pointer);

    static NODE_DECLARATION(plus4v,Pointer);
    static NODE_DECLARATION(times4v,Pointer);
    static NODE_DECLARATION(plus3v,Pointer);
    static NODE_DECLARATION(times3v,Pointer);
    static NODE_DECLARATION(plus2v,Pointer);
    static NODE_DECLARATION(times2v,Pointer);

    static NODE_DECLARATION(component0Ref,Pointer);
    static NODE_DECLARATION(component1Ref,Pointer);
    static NODE_DECLARATION(component2Ref,Pointer);
    static NODE_DECLARATION(component3Ref,Pointer);

    static NODE_DECLARATION(index, Pointer);
    static NODE_DECLARATION(dot, Pointer);
    static NODE_DECLARATION(mag, Pointer);
    static NODE_DECLARATION(normalize, Pointer);
    static NODE_DECLARATION(cross, Pointer);

private:
    const VaryingComponentType* _componentType;
};

} // namespace Mu

#endif // __MuLang__VaryingVecfType__h__
