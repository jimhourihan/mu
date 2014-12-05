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
#ifndef __MuVarying__VaryingMath__h__
#define __MuVarying__VaryingMath__h__
#include <Mu/Node.h>

namespace Mu {
class Module;

//
//  Varying math functions. These are dumped into the math module when
//  the varying module is loaded.
//

namespace VMath {

void declare(Module* mathModule, Module* mathUtilModule);

NODE_DECLARAION(abs_i, Pointer);
NODE_DECLARAION(max_i, Pointer);
NODE_DECLARAION(min_i, Pointer);
NODE_DECLARAION(abs_f, Pointer);
NODE_DECLARAION(max_f, Pointer);
NODE_DECLARAION(min_f, Pointer);
NODE_DECLARAION(atan2, Pointer);
NODE_DECLARAION(sin, Pointer);
NODE_DECLARAION(cos, Pointer);
NODE_DECLARAION(tan, Pointer);
NODE_DECLARAION(asin, Pointer);
NODE_DECLARAION(acos, Pointer);
NODE_DECLARAION(atan, Pointer);
NODE_DECLARAION(exp, Pointer);
NODE_DECLARAION(expm1, Pointer);
NODE_DECLARAION(log, Pointer);
NODE_DECLARAION(log10, Pointer);
NODE_DECLARAION(log1p, Pointer);
NODE_DECLARAION(pow, Pointer);
NODE_DECLARAION(hypot, Pointer);
NODE_DECLARAION(sqrt, Pointer);
NODE_DECLARAION(inversesqrt, Pointer);
NODE_DECLARAION(cbrt, Pointer);
NODE_DECLARAION(floor, Pointer);
NODE_DECLARAION(ceil, Pointer);
NODE_DECLARAION(rint, Pointer);

// NODE_DECLARAION(truncate, Pointer);
// NODE_DECLARAION(clamp, Pointer);
// NODE_DECLARAION(smoothstep, Pointer);
// NODE_DECLARAION(linstep, Pointer);
// NODE_DECLARAION(hermite, Pointer);

NODE_DECLARAION(clamp, Pointer);
NODE_DECLARAION(smoothstep, Pointer);
NODE_DECLARAION(linstep, Pointer);
NODE_DECLARAION(lerp, Pointer);

NODE_DECLARAION(step, Pointer);
NODE_DECLARAION(random2, Pointer);

NODE_DECLARAION(random, Pointer);
NODE_DECLARAION(degrees, Pointer);
NODE_DECLARAION(radians, Pointer);

NODE_DECLARAION(hermite, Pointer);
NODE_DECLARAION(gauss, Pointer);
NODE_DECLARAION(sphrand, Vector3f);
NODE_DECLARAION(rotate, Vector3f);

} // VMath
} // Mu

#endif // __MuVarying__VaryingMath__h__
