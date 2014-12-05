#ifndef __MuLang__MathModule__h__
#define __MuLang__MathModule__h__
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
#include <Mu/Module.h>
#include <Mu/Node.h>

namespace Mu {
class Context;

class MathModule : public Module
{
  public:
    MathModule(Context*);
    ~MathModule();

    //
    //	Load function is called when the symbol is added to the
    //	context.
    //

    virtual void load();


    //
    //	Function Nodes
    //

    static NODE_DECLARAION(abs_i,int);
    static NODE_DECLARAION(max_i,int);
    static NODE_DECLARAION(min_i,int);

    static NODE_DECLARAION(abs_f,float);
    static NODE_DECLARAION(max_f,float);
    static NODE_DECLARAION(min_f,float);
    static NODE_DECLARAION(atan2,float);
    static NODE_DECLARAION(sin,float);
    static NODE_DECLARAION(cos,float);
    static NODE_DECLARAION(tan,float);
    static NODE_DECLARAION(asin,float);
    static NODE_DECLARAION(acos,float);
    static NODE_DECLARAION(atan,float);
    static NODE_DECLARAION(exp,float);
    static NODE_DECLARAION(expm1,float);
    static NODE_DECLARAION(log,float);
    static NODE_DECLARAION(log10,float);
    static NODE_DECLARAION(log1p,float);
    static NODE_DECLARAION(pow,float);
    static NODE_DECLARAION(hypot,float);
    static NODE_DECLARAION(sqrt,float);
    static NODE_DECLARAION(inversesqrt,float);
    static NODE_DECLARAION(cbrt,float);
    static NODE_DECLARAION(floor,float);
    static NODE_DECLARAION(ceil,float);
    static NODE_DECLARAION(rint,float);

    static NODE_DECLARAION(abs_d,double);
    static NODE_DECLARAION(max_d,double);
    static NODE_DECLARAION(min_d,double);
    static NODE_DECLARAION(atan2_d,double);
    static NODE_DECLARAION(sin_d,double);
    static NODE_DECLARAION(cos_d,double);
    static NODE_DECLARAION(tan_d,double);
    static NODE_DECLARAION(asin_d,double);
    static NODE_DECLARAION(acos_d,double);
    static NODE_DECLARAION(atan_d,double);
    static NODE_DECLARAION(exp_d,double);
    static NODE_DECLARAION(expm1_d,double);
    static NODE_DECLARAION(log_d,double);
    static NODE_DECLARAION(log10_d,double);
    static NODE_DECLARAION(log1p_d,double);
    static NODE_DECLARAION(pow_d,double);
    static NODE_DECLARAION(hypot_d,double);
    static NODE_DECLARAION(sqrt_d,double);
    static NODE_DECLARAION(inversesqrt_d,double);
    static NODE_DECLARAION(cbrt_d,double);
    static NODE_DECLARAION(floor_d,double);
    static NODE_DECLARAION(ceil_d,double);
    static NODE_DECLARAION(rint_d,double);
};

} // namespace Mu

#endif // __MuLang__MathModule__h__
