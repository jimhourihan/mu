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

#ifndef __runtime__GelatoModule__h__
#define __runtime__GelatoModule__h__

#include <Mu/Module.h>
#include <Mu/Node.h>

#include <gelatoapi.h>

namespace Mu {

class GelatoModule : public Module
{
public:
    GelatoModule(const char *name, Context *c);
    GelatoModule(const char *name, Context *c, GelatoAPI *);
    virtual ~GelatoModule();

    virtual void load();

    static void init(const char*, Context*);
    static void init(const char*, Context*, GelatoAPI *);


    static NODE_DECLARATION(CreateRenderer, int);
    static NODE_DECLARATION(DeleteRenderer, void);
    static NODE_DECLARATION(GetNumRenderers, int);
    static NODE_DECLARATION(GetCurrentRenderer, int);
    static NODE_DECLARATION(SetCurrentRenderer, void);


    //
    // Note:  These are ALL the Gelato functions.
    //
    static NODE_DECLARATION(Input, void);
    static NODE_DECLARATION(Camera, void);
    static NODE_DECLARATION(Output, void);
    static NODE_DECLARATION(World, void);
    static NODE_DECLARATION(Render, void);

    static NODE_DECLARATION(Motion,  void);
    static NODE_DECLARATION(MotionT, void);

    // Inserts a comment
    static NODE_DECLARATION(Comment, void);

    // Executes a command signified by the token command
    static NODE_DECLARATION(Command, void);

    // Set a parameter of the next shader, primitive, camera, or output
    static NODE_DECLARATION(Parameter, void);

    // Set an attribute in the graphics state, with name and explicit type
    static NODE_DECLARATION(Attribute, void);

    // Get the value of a graphics state attribute
    static NODE_DECLARATION(GetIntAttribute, Pointer);
    static NODE_DECLARATION(GetFloatAttribute, Pointer);
    static NODE_DECLARATION(GetStringAttribute, Pointer);

    static NODE_DECLARATION(PushAttributes, void);
    static NODE_DECLARATION(PopAttributes, void);
    static NODE_DECLARATION(SaveAttributes, void);
    static NODE_DECLARATION(RestoreAttributes, void);
    static NODE_DECLARATION(Modify, void);

    // Transformations
    static NODE_DECLARATION(PushTransform, void);
    static NODE_DECLARATION(PopTransform,  void);
    static NODE_DECLARATION(SetTransform,  void);
    static NODE_DECLARATION(SetTransformS, void);
    static NODE_DECLARATION(AppendTransform, void);
    static NODE_DECLARATION(Translate, void);
    static NODE_DECLARATION(TranslateV, void);
    static NODE_DECLARATION(Rotate, void);
    static NODE_DECLARATION(RotateV, void);
    static NODE_DECLARATION(Scale, void);
    static NODE_DECLARATION(ScaleV, void);

    // Shaders
    static NODE_DECLARATION(Shader, void);
    static NODE_DECLARATION(Light,  void);
    static NODE_DECLARATION(ShaderGroupBegin, void);
    static NODE_DECLARATION(ShaderGroupEnd, void);
    static NODE_DECLARATION(ConnectShaders, void);
    static NODE_DECLARATION(LightSwitch, void);

    // Geometry
    // 0-D prims - point clouds
    static NODE_DECLARATION(Points, void);

    // 1-D prims - lines, curves, hair
    static NODE_DECLARATION(Curves, void);
    static NODE_DECLARATION(CurvesL, void);

    // 2-D prims - rectangular patches (NURBS, bicubics, bilinears), and indexed face meshes (polys, polyhedra, subdivs)
    static NODE_DECLARATION(Patch, void);
    static NODE_DECLARATION(PatchL, void);
    static NODE_DECLARATION(TrimCurve, void);

    static NODE_DECLARATION(Mesh, void);

    static NODE_DECLARATION(Sphere, void);
    static NODE_DECLARATION(SphereR, void);

    static NODE_DECLARATION(TransformPoints, bool);

private:
    static bool applyInlineParams( const Mu::Node &node_, 
                                   Mu::Thread &thread_,
                                   int startAtArg );

    static GelatoAPI *gelatoAPI();

private:
    static std::vector<GelatoAPI *> m_gelatoAPIs;
    static int m_currentAPI;

};

} // namespace Mu

#endif // __runtime__GelatoModule__h__
