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

#ifndef __runtime__GLTextModule__h__
#define __runtime__GLTextModule__h__

#include <Mu/Module.h>
#include <Mu/Node.h>

namespace Mu {

class GLTextModule : public Module
{
  public:
    GLTextModule(Context *c, const char *name);
    virtual ~GLTextModule();

    virtual void load();

    static void init();

    static NODE_DECLARATION( TwkGLText_init, void );
    static NODE_DECLARATION( writeAt, void );
    static NODE_DECLARATION( writeAtNLf, int );
    static NODE_DECLARATION( writeAtNLfv, int );
    static NODE_DECLARATION( setSize, void );
    static NODE_DECLARATION( getSize, int );
    static NODE_DECLARATION( bounds, Pointer );
    static NODE_DECLARATION( boundsNL, Pointer );
    static NODE_DECLARATION( color4f, void );
    static NODE_DECLARATION( color3fv, void );
    static NODE_DECLARATION( color4fv, void );
    static NODE_DECLARATION( width, float );
    static NODE_DECLARATION( height, float );
    static NODE_DECLARATION( widthNL, float );
    static NODE_DECLARATION( heightNL, float );
    static NODE_DECLARATION( ascenderHeight, float );
    static NODE_DECLARATION( descenderDepth, float );

};

} // namespace Mu

#endif // __runtime__GLTextModule__h__
