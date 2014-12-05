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

#ifndef __runtime__GLUModule__h__
#define __runtime__GLUModule__h__

#include <Mu/Module.h>
#include <Mu/Node.h>

namespace Mu {

class GLUModule : public Module
{
  public:
    GLUModule(Context* c, const char *name);
    virtual ~GLUModule();

    virtual void load();

    static void init();


    //
    // Note:  These are ALL the GLU 1.3 functions.  If they're commented 
    //        out, then they are either unimplemented, or implemented 
    //        slightly differently in Mu.
    //

//     static NODE_DECLARATION( gluBeginCurve, void );
//     static NODE_DECLARATION( gluBeginPolygon, void );
//     static NODE_DECLARATION( gluBeginSurface, void );
//     static NODE_DECLARATION( gluBeginTrim, void );
//     static NODE_DECLARATION( gluBuild1DMipmapLevels, int );
//     static NODE_DECLARATION( gluBuild1DMipmaps, int );
//     static NODE_DECLARATION( gluBuild2DMipmapLevels, int );
    static NODE_DECLARATION( gluBuild2DMipmaps, int );
//     static NODE_DECLARATION( gluBuild3DMipmapLevels, int );
//     static NODE_DECLARATION( gluBuild3DMipmaps, int );
    static NODE_DECLARATION( gluCheckExtension, bool );
//     static NODE_DECLARATION( gluCylinder, void );
//     static NODE_DECLARATION( gluDeleteNurbsRenderer, void );
//     static NODE_DECLARATION( gluDeleteQuadric, void );
//     static NODE_DECLARATION( gluDeleteTess, void );
//     static NODE_DECLARATION( gluDisk, void );
//     static NODE_DECLARATION( gluEndCurve, void );
//     static NODE_DECLARATION( gluEndPolygon, void );
//     static NODE_DECLARATION( gluEndSurface, void );
//     static NODE_DECLARATION( gluEndTrim, void );
    static NODE_DECLARATION( gluErrorString, Pointer );
//     static NODE_DECLARATION( gluGetNurbsProperty, void );
    static NODE_DECLARATION( gluGetString, Pointer );
//     static NODE_DECLARATION( gluGetTessProperty, void );
//     static NODE_DECLARATION( gluLoadSamplingMatrices, void );
    static NODE_DECLARATION( gluLookAt, void );
    static NODE_DECLARATION( gluLookAtv, void ); // ** NON-STANDARD **
//     static NODE_DECLARATION( gluNewNurbsRenderer, Pointer );
//     static NODE_DECLARATION( gluNewQuadric, Pointer );
//     static NODE_DECLARATION( gluNewTess, Pointer );
//     static NODE_DECLARATION( gluNextContour, void );
//     static NODE_DECLARATION( gluNurbsCallback, void );
//     static NODE_DECLARATION( gluNurbsCallbackData, void );
//     static NODE_DECLARATION( gluNurbsCallbackDataEXT, void );
//     static NODE_DECLARATION( gluNurbsCurve, void );
//     static NODE_DECLARATION( gluNurbsProperty, void );
//     static NODE_DECLARATION( gluNurbsSurface, void );
    static NODE_DECLARATION( gluOrtho2D, void );
//     static NODE_DECLARATION( gluPartialDisk, void );
    static NODE_DECLARATION( gluPerspective, void );
//     static NODE_DECLARATION( gluPickMatrix, void );
//     static NODE_DECLARATION( gluProject, int );
//     static NODE_DECLARATION( gluPwlCurve, void );
//     static NODE_DECLARATION( gluQuadricCallback, void );
//     static NODE_DECLARATION( gluQuadricDrawStyle, void );
//     static NODE_DECLARATION( gluQuadricNormals, void );
//     static NODE_DECLARATION( gluQuadricOrientation, void );
//     static NODE_DECLARATION( gluQuadricTexture, void );
    static NODE_DECLARATION( gluScaleImage, int );
//     static NODE_DECLARATION( gluSphere, void );
//     static NODE_DECLARATION( gluTessBeginContour, void );
//     static NODE_DECLARATION( gluTessBeginPolygon, void );
//     static NODE_DECLARATION( gluTessCallback, void );
//     static NODE_DECLARATION( gluTessEndContour, void );
//     static NODE_DECLARATION( gluTessEndPolygon, void );
//     static NODE_DECLARATION( gluTessNormal, void );
//     static NODE_DECLARATION( gluTessProperty, void );
//     static NODE_DECLARATION( gluTessVertex, void );
//     static NODE_DECLARATION( gluUnProject, int );
//     static NODE_DECLARATION( gluUnProject4, int );

};

} // namespace Mu

#endif // __runtime__GLUModule__h__
