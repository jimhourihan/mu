#ifndef __MuLang__VaryingFloatType__h__
#define __MuLang__VaryingFloatType__h__
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
#include "VaryingObject.h"
#include "VaryingType.h"
#include <Mu/Node.h>
#include <MuLang/FloatType.h>
#include <iosfwd>

namespace Mu {

//
//  class VaryingFloatType
//
//  Pile-o-floating-point-numbers class.
//

class VaryingFloatType : public VaryingType
{
  public:
    VaryingFloatType(Context* c, const FloatType*);
    ~VaryingFloatType();

    //
    //	Symbol API
    //

    virtual void load();

    //
    //	Operators, most of these actually work for a float or any
    //	vector size. The operators use the MachineRep::width() to
    //	figure out how much memory to traverse.
    //

    static NODE_DECLARAION(tovarying_from_scalar, Pointer);

    static NODE_DECLARAION(assign, Pointer);
    static NODE_DECLARAION(uminus, Pointer);
    static NODE_DECLARAION(plus, Pointer);
    static NODE_DECLARAION(plusf, Pointer);
    static NODE_DECLARAION(minus, Pointer);
    static NODE_DECLARAION(minusf, Pointer);
    static NODE_DECLARAION(fminus, Pointer);
    static NODE_DECLARAION(times, Pointer);
    static NODE_DECLARAION(timesf, Pointer);
    static NODE_DECLARAION(divide, Pointer);
    static NODE_DECLARAION(dividef, Pointer);
    static NODE_DECLARAION(fdivide, Pointer);
    static NODE_DECLARAION(equals, Pointer);
    static NODE_DECLARAION(nequals, Pointer);
    static NODE_DECLARAION(ge, Pointer);
    static NODE_DECLARAION(le, Pointer);
    static NODE_DECLARAION(geq, Pointer);
    static NODE_DECLARAION(leq, Pointer);
    static NODE_DECLARAION(pluseq, Pointer);
    static NODE_DECLARAION(minuseq, Pointer);
    static NODE_DECLARAION(timeseq, Pointer);
    static NODE_DECLARAION(divideeq, Pointer);
    static NODE_DECLARAION(conditionalExpr, Pointer);

    static NODE_DECLARAION(Du, Pointer);
    static NODE_DECLARAION(Dv, Pointer);
    static NODE_DECLARAION(Dw, Pointer);

    static NODE_DECLARAION(print, void);
};

} // namespace Mu

#endif // __MuLang__VaryingFloatType__h__
