#ifndef __MuLang__MathUtilModule__h__
#define __MuLang__MathUtilModule__h__
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

class MathUtilModule : public Module
{
  public:
    MathUtilModule(Context*);
    ~MathUtilModule();

    //
    //  Load function is called when the symbol is added to the
    //  context.
    //

    virtual void load();


    //
    //  Function Nodes
    //

    static NODE_DECLARAION(clamp, float);
    static NODE_DECLARAION(step, float);
    static NODE_DECLARAION(smoothstep, float);
    static NODE_DECLARAION(linstep, float);
    static NODE_DECLARAION(hermite, float);
    static NODE_DECLARAION(lerp, float);
    static NODE_DECLARAION(lerp2f, Vector2f);
    static NODE_DECLARAION(lerp3f, Vector3f);
    static NODE_DECLARAION(lerp4f, Vector4f);
    static NODE_DECLARAION(degrees, float);
    static NODE_DECLARAION(radians, float);
    static NODE_DECLARAION(randomf2, float);
    static NODE_DECLARAION(randomf, float);
    static NODE_DECLARAION(random, int);
    static NODE_DECLARAION(gauss, float);
    static NODE_DECLARAION(seed, void);
    static NODE_DECLARAION(sphrand, Vector3f);
    static NODE_DECLARAION(rotate, Vector3f);

    static NODE_DECLARAION(noise1, float);
    static NODE_DECLARAION(noise2, float);
    static NODE_DECLARAION(noise3, float);
    static NODE_DECLARAION(dnoise1, float);
    static NODE_DECLARAION(dnoise2, Vector2f);
    static NODE_DECLARAION(dnoise3, Vector3f);
};

} // namespace Mu

#endif // __MuLang__MathUtilModule__h__
