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

#include <sstream>
#include <limits>

#include <Mu/Symbol.h>
#include <Mu/SymbolTable.h>
#include <Mu/Function.h>
#include <Mu/Exception.h>
#include <Mu/FunctionObject.h>
#include <Mu/Module.h>
#include <Mu/FunctionType.h>
#include <Mu/GarbageCollector.h>
#include <Mu/ParameterVariable.h>
#include <Mu/Process.h>
#include <Mu/Signature.h>
#include <Mu/Thread.h>
#include <Mu/SymbolicConstant.h>
#include <MuLang/Native.h>
#include <MuLang/DynamicArray.h>
#include <MuLang/FixedArray.h>
#include <MuLang/ExceptionType.h>
#include <MuLang/MuLangContext.h>
#include <MuLang/StringType.h>

#include <math.h>
#include <TwkMath/Mat44.h>
#include <TwkMath/Vec3.h>
#include <TwkMath/Iostream.h>

#include "GelatoModule.h"

#define MAX_PARAMETER_TOKENS 255

namespace Mu {

using namespace std;
using namespace Gelato;

int GelatoModule::m_currentAPI = -1;
std::vector<GelatoAPI *> GelatoModule::m_gelatoAPIs;

static void throwBadArgumentException(const Mu::Node& node, 
                                      Mu::Thread& thread,
                                      std::string msg)
{
    ostringstream str;
    const Mu::MuLangContext* context = 
        static_cast<const Mu::MuLangContext*>(thread.context());
    ExceptionType::Exception *e =
        new ExceptionType::Exception(context->exceptionType());
    str << "in " << node.symbol()->fullyQualifiedName() << ": " << msg;
    e->string() += str.str().c_str();
    thread.setException(e);
    throw BadArgumentException(thread, e);
}

static void
throwBadAttribute(Thread& thread, std::string name)
{
    Process* process = thread.process();
    MuLangContext* context = static_cast<MuLangContext*>(process->context());
    ExceptionType::Exception *e =
        new ExceptionType::Exception(context->exceptionType());
    e->string() += "invalid attribute: ";
    e->string() += name.c_str();
    e->string() += "\n";
    thread.setException(e);
    ProgramException exc(thread, e);
    throw exc;
}

void
GelatoModule::init(const char* name, Context* context)
{
    static bool initialized = false;

    if (!initialized)
    {
        initialized = true;
        Module *m = new GelatoModule(name, context);
        context->globalScope()->addSymbol(m);
    }
}

void
GelatoModule::init(const char* name, Context* context, GelatoAPI *renderer)
{
    static bool initialized = false;

    if (!initialized)
    {
        initialized = true;
        Module *m = new GelatoModule(name, context);
        context->globalScope()->addSymbol(m);
    }
    m_currentAPI = m_gelatoAPIs.size();
    m_gelatoAPIs.push_back( renderer );
}


GelatoModule::GelatoModule(const char *name, Context *c)
    : Module(name, c)
{
}

GelatoModule::GelatoModule(const char *name, Context *c, GelatoAPI *renderer)
    : Module(name, c)
{
    m_currentAPI = m_gelatoAPIs.size();
    m_gelatoAPIs.push_back( renderer );
}

GelatoModule::~GelatoModule()
{
}

GelatoAPI *GelatoModule::gelatoAPI()
{
    if( m_currentAPI < 0 )
    {
        throw Mu::Exception( "No renderer!  Call gelato.CreateRenderer() first." );
    }
    return m_gelatoAPIs[m_currentAPI]; 
}

void
GelatoModule::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    MuLangContext* context = (MuLangContext*)globalModule()->context();

    //
    // Instantate types used later...
    //
    context->arrayType(context->stringType(), 1, 0);    // string[]
    context->arrayType(context->boolType(), 1, 0);      // bool[]
    context->arrayType(context->intType(), 1, 0);       // int[]
    context->arrayType(context->floatType(), 1, 0);     // float[]
    context->arrayType(context->byteType(), 1, 0);      // byte[]
    context->arrayType(context->vec2fType(), 1, 0);     // vec2f[]
    context->arrayType(context->vec3fType(), 1, 0);     // vec3f[]
    context->arrayType(context->vec4fType(), 1, 0);     // vec4f[]
    context->arrayType(context->floatType(), 2, 4, 4);  // float[4,4]
    context->arrayType(context->floatType(), 1, 16);    // float[16]
    context->arrayType(context->floatType(), 1, 6);     // float[6]

    addSymbols(


        new Function("CreateRenderer", GelatoModule::CreateRenderer, None,
                     Return, "int",
                     Parameters, new Param("type", "string", Value()),
                     End ),

        new Function("DeleteRenderer", GelatoModule::DeleteRenderer, None,
                     Return, "void",
                     Args, "int",
                     End ),

        new Function("GetNumRenderers", GelatoModule::GetNumRenderers, None,
                     Return, "int",
                     End ),

        new Function("GetCurrentRenderer", GelatoModule::GetCurrentRenderer, 
                     None,
                     Return, "int",
                     End ),

        new Function("SetCurrentRenderer", GelatoModule::SetCurrentRenderer, 
                     None,
                     Return, "void",
                     Args, "int",
                     End ),

        //
        // Note: These are all of the Gelato functions
        //

        // virtual void Input (const char *filename)
        // virtual void Input (const char *filename, const float *bound)
        new Function("Input", GelatoModule::Input, None,
                     Return, "void",
                     Args, "string",
                     Optional, "float[6]",
                     End ),

        // virtual void Camera (const char *name)
        new Function("Camera", GelatoModule::Camera, None,
                     Return, "void",
                     Args, "string",
                     End ),

        // virtual void Output (const char *name, const char *format,
        //                          const char *dataname, const char *cameraname)
        new Function("Output", GelatoModule::Output, None,
                     Return, "void",
                     Args, "string", "string", "string", "string",
                     End ),

        // virtual void World (void)
        new Function("World", GelatoModule::World, None,
                     Return, "void",
                     End),

        // virtual void Render (const char *cameraname=NULL)
        new Function("Render", GelatoModule::Render, None,
                     Return, "void",
                     Parameters, new Param("camera", "string", Value()),
                     End ),

        // virtual void Motion (float time0, ...)
        new Function("Motion", GelatoModule::Motion, None,
                     Return, "void",
                     Args, "float", "?+",
                     Maximum, MAX_PARAMETER_TOKENS,
                     End ),

        // virtual void Motion (const float *times)
        new Function("Motion", GelatoModule::MotionT, None,
                     Return, "void",
                     Args, "float[]",
                     End ),

        // virtual void Comment (const char *format, ...)
        new Function("Comment", GelatoModule::Comment, None,
                     Return, "void",
                     Args, "string",
                     End ),

        // virtual void Command (const char *command)
        new Function("Command", GelatoModule::Command, None,
                     Return, "void",
                     Args, "string",
                     End ),


        // virtual void Parameter (const char *typedname, const void *val)
        // ...
        // NOTE: This function takes a string (typedname, i.e. "float foo")
        //       and ANY one additional parameter.  The implementation will
        //       figure out the second argument's type and call the appropriate
        //       Gelato API Parameter() function.
        new Function("Parameter", GelatoModule::Parameter, None,
                     Return, "void",
                     Args, "string", "?",
                     End ),


        // virtual void Attribute (const char *typedname, const void *val)
        // ...
        // NOTE: This function takes a string (typedname, i.e. "float foo")
        //       and ANY one additional parameter.  The implementation will
        //       figure out the second argument's type and call the appropriate
        //       Gelato API Attribute() function.
        new Function("Attribute", GelatoModule::Attribute, None,
                     Return, "void",
                     Args, "string", "?",
                     End ),

        // virtual bool GetAttribute (const char *name, int *val)
        new Function("GetIntAttribute", GelatoModule::GetIntAttribute, None,
                     Return, "int[]",
                     Args, "string",
                     Optional, "int",
                     End ),

        // virtual bool GetAttribute (const char *name, float *val)
        new Function("GetFloatAttribute", GelatoModule::GetFloatAttribute, None,
                     Return, "float[]",
                     Args, "string",
                     Optional, "int",
                     End ),

        // virtual bool GetAttribute (const char *name, char **val)
        new Function("GetStringAttribute", GelatoModule::GetStringAttribute, None,
                     Return, "string[]",
                     Args, "string",
                     Optional, "int",
                     End ),

        // virtual void PushAttributes (void)
        new Function("PushAttributes", GelatoModule::PushAttributes, None,
                     Return, "void",
                     End ),

        // virtual void PopAttributes (void)
        new Function("PopAttributes", GelatoModule::PopAttributes, None,
                     Return, "void",
                     End ),

        // virtual void SaveAttributes (const char *name, const char *attrs=NULL) 
        new Function("SaveAttributes", GelatoModule::SaveAttributes, None,
                     Return, "void",
                     Args, "string", Optional, "string",
                     End ),

        // virtual void RestoreAttributes(const char *name, const char *attrs=NULL)
        new Function("RestoreAttributes", GelatoModule::RestoreAttributes, None,
                     Return, "void",
                     Args, "string", Optional, "string",
                     End),

        // virtual void Modify(const char *namepattern=NULL)
        new Function("Modify", GelatoModule::Modify, None,
                     Return, "void",
                     Parameters, new Param("namepattern", "string", Value()),
                     End),

        // virtual void PushTransform (void)
        new Function("PushTransform", GelatoModule::PushTransform, None,
                     Return, "void",
                     End ),

        // virtual void PopTransform (void) 
        new Function("PopTransform", GelatoModule::PopTransform, None,
                     Return, "void",
                     End ),

        // virtual void SetTransform (const float *M)
        new Function("SetTransform", GelatoModule::SetTransform, None,
                     Return, "void",
                     Args, "float[16]",
                     End ),

        // virtual void SetTransform (const char *spacename)
        new Function("SetTransform", GelatoModule::SetTransformS, None,
                     Return, "void",
                     Args, "string",
                     End ),

        // virtual void AppendTransform (const float *M)
        new Function("AppendTransform", GelatoModule::AppendTransform, None,
                     Return, "void",
                     Args, "float[16]",
                     End ),

        // virtual void Translate (float x, float y, float z)
        new Function("Translate", GelatoModule::Translate, None,
                     Return, "void",
                     Args, "float", "float", "float",
                     End ),

        // *** Not in the Gelato C API, but handy nonetheless
        new Function("Translate", GelatoModule::TranslateV, None,
                     Return, "void",
                     Args, "vector float[3]",
                     End ),

        // virtual void Rotate (float angle, float x, float y, float z)
        new Function("Rotate", GelatoModule::Rotate, None,
                     Return, "void",
                     Args, "float", "float", "float", "float",
                     End ),

        // *** Not in the Gelato C API, but handy nonetheless
        new Function("Rotate", GelatoModule::RotateV, None,
                     Return, "void",
                     Args, "float", "vector float[3]",
                     End ),

        // virtual void Scale (float x, float y, float z)
        new Function("Scale", GelatoModule::Scale, None,
                     Return, "void",
                     Args, "float", "float", "float",
                     End ),

        // *** Not in the Gelato C API, but handy nonetheless
        new Function("Scale", GelatoModule::ScaleV, None,
                     Return, "void",
                     Args, "vector float[3]",
                     End ),

        // virtual void Shader(const char *shadertype, const char *shadername=NULL,
        //                     const char *layername=NULL)
        //
        // ** Changed to be more python-like.  Can inline parameters, layername not
        //    supported yet
        //
        //
        new Function("Shader", GelatoModule::Shader, None,
                     Return, "void",
                     Args, "string", "string", Optional, "?varargs",
                     Maximum, MAX_PARAMETER_TOKENS, 
                     End ),

        // virtual void Light (const char *lightid, const char *shadername,
        //                     const char *layername=NULL)
        //
        // ** Changed to be more python-like.  Can inline parameters, layername not
        //    supported yet
        //
        new Function("Light", GelatoModule::Light, None,
                     Return, "void",
                     Args, "string", "string", 
                     Optional, "?varargs",
                     Maximum, MAX_PARAMETER_TOKENS, 
                     End),

        // virtual void ShaderGroupBegin (void)
        new Function("ShaderGroupBegin", GelatoModule::ShaderGroupBegin, None,
                     Return, "void",
                     End),

        // virtual void ShaderGroupEnd (void)
        new Function("ShaderGroupEnd", GelatoModule::ShaderGroupEnd, None,
                     Return, "void",
                     End),

        // virtual void ConnectShaders (const char *srclayer, const char *srcparam,
        //                              const char *dstlayer, const char *dstparam)
        new Function("ConnectShaders", GelatoModule::ConnectShaders, None,
                     Return, "void",
                     Args, "string", "string", "string", "string",
                     End),

        // virtual void LightSwitch (const char *lightid, bool on) 
        new Function("LightSwitch", GelatoModule::LightSwitch, None,
                     Return, "void",
                     Args, "string", "bool",
                     End),

        // virtual void Points (int npoints)
        new Function("Points", GelatoModule::Points, None,
                     Return, "void",
                     Args, "?dyn_array",
                     Optional, "?varargs",
                     Maximum, MAX_PARAMETER_TOKENS, 
                     End),

        // virtual void Curves (const char *interp, int ncurves, int nvertspercurve)
        new Function("Curves", GelatoModule::Curves, None,
                     Return, "void",
                     Args, "string", "int", "int",
                     Optional, "?varargs",
                     Maximum, MAX_PARAMETER_TOKENS, 
                     End),

        // virtual void Curves (int ncurves, int nvertspercurve, int order,
        //                      const float *knot, float vmin, float vmax)
        new Function("Curves", GelatoModule::CurvesL, None,
                     Return, "void",
                     Args, "int", "int", "int", 
                           "?dyn_array", "float", "float",
                     End),

        // virtual void Patch (const char *interp, int nu, int nv)
        new Function("Patch", GelatoModule::Patch, None,
                     Return, "void",
                     Args, "string", "int", "int",
                     Optional, "?varargs",
                     Maximum, MAX_PARAMETER_TOKENS, 
                     End),

        // virtual void Patch (int nu, int uorder, const float *uknot,
        //                     float umin, float umax,
        //                     int nv, int vorder, const float *vknot,
        //                     float vmin, float vmax)
        new Function("Patch", GelatoModule::PatchL, None,
                     Return, "void",
                     Args, "int", "int", "?dyn_array", 
                           "int", "int", 
                           "int", "int", "?dyn_array", 
                           "float", "float",
                     End),

        // virtual void TrimCurve (int nloops, const int *ncurves, const int *n,
        //                         const int *order, const float *knot,
        //                         const float *min, const float *max,
        //                         const float *uvw)
        new Function("TrimCurve", GelatoModule::TrimCurve, None,
                     Return, "void",
                     Args, "int", "int[]", "int[]", 
                           "int[]", "float[]", 
                           "float[]", "float[]",
                           "float[]",
                     End),

        // virtual void Mesh (const char *interp, int nfaces,
        //                    const int *nverts, const int *verts)
        new Function("Mesh", GelatoModule::Mesh, None,
                     Return, "void",
                     Args, "string", "int",
                           "int[]", "int[]",
                     End),

        // virtual void Sphere (float radius, float zmin, float zmax,
        //                      float thetamax=360)
        new Function("Sphere", GelatoModule::Sphere, None,
                     Return, "void",
                     Args, "float", "float", "float", 
                     Optional, "float",
                     End),

        // virtual void Sphere (float radius)
        new Function("Sphere", GelatoModule::SphereR, None,
                     Return, "void",
                     Args, "float",
                     End),

        // Non-Gelato function based on RiTransformPoints
        new Function("TransformPoints", GelatoModule::TransformPoints,
                                 NoHint,
                                 Return, "bool",
                                 Args, "string", "string", "(vector float[3])[]",
                                 End),

        EndArguments );

}

// *****************************************************************************

//
NODE_IMPLEMENTATION(GelatoModule::CreateRenderer, int)
{
    const char *type = NULL;

    StringType::String *typeArg = NODE_ARG_OBJECT(0, StringType::String);
    if( typeArg )
    {
        type = typeArg->string().c_str();
    }

    m_currentAPI = m_gelatoAPIs.size();
    m_gelatoAPIs.push_back( GelatoAPI::CreateRenderer( type ) );

    NODE_RETURN( m_currentAPI );
}


NODE_IMPLEMENTATION(GelatoModule::DeleteRenderer, void)
{
    std::vector<GelatoAPI *>::iterator iter = m_gelatoAPIs.begin();

    iter += m_currentAPI;

    delete (*iter);
    m_gelatoAPIs.erase( iter );

    m_currentAPI = -1;
}


NODE_IMPLEMENTATION(GelatoModule::GetNumRenderers, int)
{
    NODE_RETURN( m_gelatoAPIs.size() );
}


NODE_IMPLEMENTATION(GelatoModule::GetCurrentRenderer, int)
{
    NODE_RETURN( m_currentAPI );
}


NODE_IMPLEMENTATION(GelatoModule::SetCurrentRenderer, void)
{
    if( m_currentAPI < m_gelatoAPIs.size() )
    {
        m_currentAPI = NODE_ARG(0,int);
    }
    else
    {
        throwBadArgumentException(NODE_THIS, NODE_THREAD,
                "No such renderer.");
    }
}


// *****************************************************************************

//
NODE_IMPLEMENTATION(GelatoModule::Input, void)
{
    StringType::String *name = NODE_ARG_OBJECT(0, StringType::String);

    if( NODE_NUM_ARGS() == 1 )
    {
        gelatoAPI()->Input( name->string().c_str() );
    }
    else
    {
        FixedArray *t = NODE_ARG_OBJECT(1,FixedArray);

        float bbox[6];
        for( int i = 0; i < 6; ++i ) bbox[i] = t->element<float>( i );

        gelatoAPI()->Input( name->string().c_str(), bbox );
    }

}


//
NODE_IMPLEMENTATION(GelatoModule::Camera, void)
{
    StringType::String *name = NODE_ARG_OBJECT(0, StringType::String);

    gelatoAPI()->Camera( name->string().c_str() );
}

//
NODE_IMPLEMENTATION(GelatoModule::Output, void)
{
    StringType::String *name     = NODE_ARG_OBJECT(0, StringType::String);
    StringType::String *format   = NODE_ARG_OBJECT(1, StringType::String);
    StringType::String *dataname = NODE_ARG_OBJECT(2, StringType::String);
    StringType::String *camera   = NODE_ARG_OBJECT(3, StringType::String);

    gelatoAPI()->Output( name->string().c_str(), 
                         format->string().c_str(), 
                         dataname->string().c_str(), 
                         camera->string().c_str() );
}

//
NODE_IMPLEMENTATION(GelatoModule::World, void)
{
    gelatoAPI()->World();
}

//
NODE_IMPLEMENTATION(GelatoModule::Render, void)
{
    if( NODE_NUM_ARGS() == 1 )
    {
        StringType::String *camera = NODE_ARG_OBJECT(0, StringType::String);
        gelatoAPI()->Render( camera->string().c_str() );
    }
    else
    {
        gelatoAPI()->Render();
    }
}

//
NODE_IMPLEMENTATION(GelatoModule::Motion, void)
{
    size_t numArgs = NODE_NUM_ARGS();
    std::vector<float> timeList;

    timeList.resize( NODE_NUM_ARGS() );
    for (int i = 0; i < numArgs; i++)
    {
       timeList[i] = NODE_ARG(i, float);
    }

    gelatoAPI()->Motion( NODE_NUM_ARGS(), &timeList.front() );
}

//
NODE_IMPLEMENTATION(GelatoModule::MotionT, void)
{
    DynamicArray *times = NODE_ARG_OBJECT(0, DynamicArray);

    gelatoAPI()->Motion(times->size(), times->data<float>());
}

//
NODE_IMPLEMENTATION(GelatoModule::Comment, void)
{
    StringType::String* commenttext = NODE_ARG_OBJECT(0, StringType::String);

    gelatoAPI()->Comment( commenttext->string().c_str() );
}

//
NODE_IMPLEMENTATION(GelatoModule::Command, void)
{
    StringType::String* name = NODE_ARG_OBJECT(0, StringType::String);

    gelatoAPI()->Command( name->string().c_str() );
}

//
NODE_IMPLEMENTATION(GelatoModule::Parameter, void)
{
    Process *p = NODE_THREAD.process();
    MuLangContext *c = static_cast<MuLangContext*>(p->context());

    StringType::String *typedname = NODE_ARG_OBJECT(0, StringType::String);

    const Type *t = NODE_THIS.argNode(1)->type();

    if( t == c->floatType() )
    {
        gelatoAPI()->Parameter( typedname->string().c_str(), NODE_ARG(1,float) );
    }
    else if( t == c->intType() )
    {
        gelatoAPI()->Parameter( typedname->string().c_str(), NODE_ARG(1,int) );
    }
    else if( t == c->stringType() )
    {
        StringType::String *value = NODE_ARG_OBJECT(1, StringType::String);
        gelatoAPI()->Parameter( typedname->string().c_str(),
                                value->string().c_str() );
    }
    else if( ( t == c->arrayType( c->floatType(), 1, 0 ) )
        || ( t == c->arrayType( c->vec3fType(), 1, 0 ) ) )
    {
        DynamicArray *da = NODE_ARG_OBJECT(1, DynamicArray);
        gelatoAPI()->Parameter( typedname->string().c_str(),
                                da->data<float>() );
    }
    else if( t == c->arrayType( c->intType(), 1, 0 ) )
    {
        DynamicArray *da = NODE_ARG_OBJECT(1, DynamicArray);
        gelatoAPI()->Parameter( typedname->string().c_str(),
                                da->data<int>() );
    }
    else if( t == c->arrayType( c->stringType(), 1, 0 ) )
    {
        throwBadArgumentException(NODE_THIS, NODE_THREAD,
                "Parameter: Sorry, string arrays not supported yet...");
// 
//         StringType::String *str = NODE_ARG_OBJECT(1, StringType::String);
//         char **stringPointers = new (char *)[1];
//         stringPointers[0] = strdup( str->string().c_str() );
// 
//         gelatoAPI()->Parameter( typedname->string().c_str(),
//                                 da->data<float>() );
    }
}


//
NODE_IMPLEMENTATION(GelatoModule::Attribute, void)
{
    Process *p = NODE_THREAD.process();
    MuLangContext *c = static_cast<MuLangContext*>(p->context());

    StringType::String *typedname = NODE_ARG_OBJECT(0, StringType::String);

    const Type *t = NODE_THIS.argNode(1)->type();

    if( t == c->floatType() )
    {
        gelatoAPI()->Attribute( typedname->string().c_str(), NODE_ARG(1,float) );
    }
    else if( t == c->intType() )
    {
        gelatoAPI()->Attribute( typedname->string().c_str(), NODE_ARG(1,int) );
    }
    else if( t == c->stringType() )
    {
        StringType::String *value = NODE_ARG_OBJECT(1, StringType::String);
        gelatoAPI()->Attribute( typedname->string().c_str(),
                                value->string().c_str() );
    }
    else if( ( t == c->arrayType( c->floatType(), 1, 0 ) )
        || ( t == c->arrayType( c->vec3fType(), 1, 0 ) ) )
    {
        DynamicArray *da = NODE_ARG_OBJECT(1, DynamicArray);
        gelatoAPI()->Attribute( typedname->string().c_str(),
                                da->data<float>() );
    }
    else if( t == c->arrayType( c->intType(), 1, 0 ) )
    {
        DynamicArray *da = NODE_ARG_OBJECT(1, DynamicArray);
        gelatoAPI()->Attribute( typedname->string().c_str(),
                                da->data<int>() );
    }
    else if( t == c->arrayType( c->stringType(), 1, 0 ) )
    {
        throwBadArgumentException(NODE_THIS, NODE_THREAD,
                "Attribute: Sorry, string arrays not supported yet...");
// 
//         StringType::String *str = NODE_ARG_OBJECT(1, StringType::String);
//         char **stringPointers = new (char *)[1];
//         stringPointers[0] = strdup( str->string().c_str() );
// 
//         gelatoAPI()->Attribute( typedname->string().c_str(),
//                                 da->data<float>() );
    }
}


NODE_IMPLEMENTATION(GelatoModule::GetIntAttribute, Pointer)
{
    std::string attrname = NODE_ARG_OBJECT(0, StringType::String)->string();
    int numValues = 1;
    if( NODE_NUM_ARGS() > 1 )
    {
        numValues = NODE_ARG(1,int);
        char tmpstr[32];
        snprintf( tmpstr, 32, "int[%d]", numValues );
        attrname = tmpstr + attrname;
    }
    else
    {
        attrname = "int " + attrname;
    }
    
    Process *p = NODE_THREAD.process();
    MuLangContext *c = static_cast<MuLangContext*>(p->context());
    const DynamicArrayType *atype = (const DynamicArrayType *)c->arrayType(c->intType(), 1, 0);  // int[]

    DynamicArray *array = new DynamicArray(atype, 1);

    array->resize( numValues );
    gelatoAPI()->GetAttribute( attrname.c_str(), array->data<int>() );

    NODE_RETURN( array );
}


//
NODE_IMPLEMENTATION(GelatoModule::GetFloatAttribute, Pointer)
{
    std::string attrname = NODE_ARG_OBJECT(0, StringType::String)->string();
    int numValues = 1;
    if( NODE_NUM_ARGS() > 1 )
    {
        numValues = NODE_ARG(1,int);
        char tmpstr[32];
        snprintf( tmpstr, 32, "float[%d]", numValues );
        attrname = tmpstr + attrname;
    }
    else
    {
        attrname = "float " + attrname;
    }
    
    Process *p = NODE_THREAD.process();
    MuLangContext *c = static_cast<MuLangContext*>(p->context());
    const DynamicArrayType *atype = (const DynamicArrayType *)c->arrayType(c->floatType(), 1, 0);  // float[]

    DynamicArray *array = new DynamicArray(atype, 1);

    array->resize( numValues );
    gelatoAPI()->GetAttribute( attrname.c_str(), array->data<float>() );
    
    NODE_RETURN( array );
}


//
NODE_IMPLEMENTATION(GelatoModule::GetStringAttribute, Pointer)
{
    std::string attrname = NODE_ARG_OBJECT(0, StringType::String)->string();
    int numValues = 1;
    if( NODE_NUM_ARGS() > 1 )
    {
        numValues = NODE_ARG(1,int);
        char tmpstr[32];
        snprintf( tmpstr, 32, "string[%d]", numValues );
        attrname = tmpstr + attrname;
    }
    else
    {
        attrname = "string " + attrname;
    }
    
    Process *p = NODE_THREAD.process();
    MuLangContext *c = static_cast<MuLangContext*>(p->context());
    const StringType *stype = static_cast<const StringType*>(NODE_THIS.type());
    const DynamicArrayType *atype = (const DynamicArrayType *)c->arrayType(c->stringType(), 1, 0);  // string[]

    DynamicArray *array = new DynamicArray(atype, 1);

    array->resize( numValues );
    char *tmpArray[numValues];
    gelatoAPI()->GetAttribute( attrname.c_str(), tmpArray );
    for( int i = 0; i < numValues; ++i )
    {
        array->element<StringType::String*>(i) = MU_NEW_STRING( tmpArray[i] );
    }
    
    NODE_RETURN( array );
}


//
NODE_IMPLEMENTATION(GelatoModule::PushAttributes, void)
{
    gelatoAPI()->PushAttributes();
}

//
NODE_IMPLEMENTATION(GelatoModule::PopAttributes, void)
{
    gelatoAPI()->PopAttributes();
}

//
NODE_IMPLEMENTATION(GelatoModule::SaveAttributes, void)
{
    StringType::String* name = NODE_ARG_OBJECT(0, StringType::String);

    if( NODE_NUM_ARGS() == 1 )
    {
        gelatoAPI()->SaveAttributes( name->string().c_str() );
    }
    else
    {
        StringType::String *attrs = NODE_ARG_OBJECT(1, StringType::String);
        gelatoAPI()->SaveAttributes( name->string().c_str(),
                                     attrs->string().c_str() );
    }
}

//
NODE_IMPLEMENTATION(GelatoModule::RestoreAttributes, void)
{
    StringType::String* name = NODE_ARG_OBJECT(0, StringType::String);

    if( NODE_NUM_ARGS() == 1 )
    {
        gelatoAPI()->RestoreAttributes( name->string().c_str() );
    }
    else
    {
        StringType::String *attrs = NODE_ARG_OBJECT(1, StringType::String);
        gelatoAPI()->RestoreAttributes( name->string().c_str(),
                                        attrs->string().c_str() );
    }
}


//
NODE_IMPLEMENTATION(GelatoModule::Modify, void)
{
    if( NODE_NUM_ARGS() == 1 )
    {
        StringType::String* namepattern = NODE_ARG_OBJECT(0, StringType::String);
        gelatoAPI()->Modify( namepattern->string().c_str() );
    }
    else
    {
        gelatoAPI()->Modify();
    }
}

//
NODE_IMPLEMENTATION(GelatoModule::PushTransform, void)
{
    gelatoAPI()->PushTransform();
}

//
NODE_IMPLEMENTATION(GelatoModule::PopTransform, void)
{
    gelatoAPI()->PopTransform();
}

//
NODE_IMPLEMENTATION(GelatoModule::SetTransform, void)
{
    FixedArray *xform = NODE_ARG_OBJECT(0, FixedArray);

    gelatoAPI()->SetTransform(xform->data<float>());
}

//
NODE_IMPLEMENTATION(GelatoModule::SetTransformS, void)
{
    StringType::String *spacename = NODE_ARG_OBJECT(0, StringType::String);

    gelatoAPI()->SetTransform( spacename->string().c_str() );
}

//
NODE_IMPLEMENTATION(GelatoModule::AppendTransform, void)
{
    FixedArray *xform = NODE_ARG_OBJECT(0, FixedArray);

    gelatoAPI()->AppendTransform(xform->data<float>());
}

//
NODE_IMPLEMENTATION(GelatoModule::Translate, void)
{
    gelatoAPI()->Translate( NODE_ARG(0, float), 
                            NODE_ARG(1, float), 
                            NODE_ARG(2, float) );
}

//
NODE_IMPLEMENTATION(GelatoModule::TranslateV, void)
{
    const Vector3f &v = NODE_ARG(0, Vector3f);
    gelatoAPI()->Translate( v[0], v[1], v[2] );
}

//
NODE_IMPLEMENTATION(GelatoModule::Rotate, void)
{
    gelatoAPI()->Rotate( NODE_ARG(0, float), 
                         NODE_ARG(1, float), 
                         NODE_ARG(2, float), 
                         NODE_ARG(3, float) );
}

//
NODE_IMPLEMENTATION(GelatoModule::RotateV, void)
{
    const Vector3f &v = NODE_ARG(1, Vector3f);
    gelatoAPI()->Rotate( NODE_ARG(0, float), v[0], v[1], v[2] );
}

//
NODE_IMPLEMENTATION(GelatoModule::Scale, void)
{
    gelatoAPI()->Scale( NODE_ARG(0, float), NODE_ARG(1, float), NODE_ARG(2, float) );
}

//
NODE_IMPLEMENTATION(GelatoModule::ScaleV, void)
{
    const Vector3f &v = NODE_ARG(0, Vector3f);
    gelatoAPI()->Scale( v[0], v[1], v[2] );
}

//
NODE_IMPLEMENTATION(GelatoModule::Shader, void)
{
    const char *shadertype = NODE_ARG_OBJECT(0, StringType::String)->string().c_str();
    const char *shadername = NODE_ARG_OBJECT(1, StringType::String)->string().c_str();
    const char *layername = NULL;
//     if( NODE_NUM_ARGS() > 2 )
//     {
//         layername = NODE_ARG_OBJECT(2, StringType::String)->string().c_str();
//     }

    applyInlineParams( NODE_THIS, NODE_THREAD, 2 );

    gelatoAPI()->Shader( shadertype, shadername, layername ); 
}

//
NODE_IMPLEMENTATION(GelatoModule::Light, void)
{
    const char *lightid = NODE_ARG_OBJECT(0, StringType::String)->string().c_str();
    const char *shadername = NODE_ARG_OBJECT(1, StringType::String)->string().c_str();
    const char *layername = NULL;
//     if( NODE_NUM_ARGS() > 2 )
//     {
//         layername = NODE_ARG_OBJECT(2, StringType::String)->string().c_str();
//     }

    applyInlineParams( NODE_THIS, NODE_THREAD, 2 );
    
    gelatoAPI()->Light( lightid, shadername, layername ); 
}

//
NODE_IMPLEMENTATION(GelatoModule::ShaderGroupBegin, void)
{
    gelatoAPI()->ShaderGroupBegin();
}

//
NODE_IMPLEMENTATION(GelatoModule::ShaderGroupEnd, void)
{
    gelatoAPI()->ShaderGroupEnd();
}

//
NODE_IMPLEMENTATION(GelatoModule::ConnectShaders, void)
{
    StringType::String* srclayer = NODE_ARG_OBJECT(0, StringType::String);
    StringType::String* srcparam = NODE_ARG_OBJECT(1, StringType::String);
    StringType::String* dstlayer = NODE_ARG_OBJECT(2, StringType::String);
    StringType::String* dstparam = NODE_ARG_OBJECT(3, StringType::String);

    gelatoAPI()->ConnectShaders( srclayer->string().c_str(), 
                                 srcparam->string().c_str(), 
                                 dstlayer->string().c_str(), 
                                 dstparam->string().c_str() );
}

//
NODE_IMPLEMENTATION(GelatoModule::LightSwitch, void)
{
    StringType::String* lightid = NODE_ARG_OBJECT(0, StringType::String);

    gelatoAPI()->LightSwitch( lightid->string().c_str(), NODE_ARG(1, bool) );
}

//
NODE_IMPLEMENTATION(GelatoModule::Points, void)
{
    DynamicArray *P = NODE_ARG_OBJECT(0, DynamicArray);

    applyInlineParams( NODE_THIS, NODE_THREAD, 1 );

    gelatoAPI()->Parameter( "P", P->data<float>() );
    gelatoAPI()->Points( P->size() ) ;
}

//
NODE_IMPLEMENTATION(GelatoModule::Curves, void)
{
    StringType::String *interp = NODE_ARG_OBJECT(0, StringType::String);
    const int ncurves = NODE_ARG(1,int);
    const int nvertspercurve = NODE_ARG(2,int);

    applyInlineParams( NODE_THIS, NODE_THREAD, 3 );

    gelatoAPI()->Curves( interp->string().c_str(), ncurves, nvertspercurve );
}

NODE_IMPLEMENTATION(GelatoModule::CurvesL, void)
{
    const int ncurves = NODE_ARG(0, int);
    const int nvertspercurve = NODE_ARG(1, int);
    const int order = NODE_ARG(2, int);
    DynamicArray *knots = NODE_ARG_OBJECT(3, DynamicArray);
    const float vmin = NODE_ARG(4, float);
    const float vmax = NODE_ARG(5, float);
    
    gelatoAPI()->Curves( ncurves, nvertspercurve, order, 
                         knots->data<float>(), vmin, vmax );
}

//
NODE_IMPLEMENTATION(GelatoModule::Patch, void)
{
    StringType::String *interp = NODE_ARG_OBJECT(0, StringType::String);
    const int nu = NODE_ARG(1,int);
    const int nv = NODE_ARG(2,int);

    applyInlineParams( NODE_THIS, NODE_THREAD, 3 );

    gelatoAPI()->Patch( interp->string().c_str(), nu, nv );
}

NODE_IMPLEMENTATION(GelatoModule::PatchL, void)
{
    const int nu = NODE_ARG(0, int);
    const int uorder = NODE_ARG(1, int);
    DynamicArray *uknot = NODE_ARG_OBJECT(2, DynamicArray);
    const float umin = NODE_ARG(3, float);
    const float umax = NODE_ARG(4, float);
    const int nv = NODE_ARG(5, int);
    const int vorder = NODE_ARG(6, int);
    DynamicArray *vknot = NODE_ARG_OBJECT(7, DynamicArray);
    const float vmin = NODE_ARG(8, float);
    const float vmax = NODE_ARG(9, float);
    
    gelatoAPI()->Patch( nu, uorder, uknot->data<float>(),
                        umin, umax,
                        nv, vorder, vknot->data<float>(),
                        vmin, vmax );
}

//
NODE_IMPLEMENTATION(GelatoModule::TrimCurve, void)
{
    const int nloops = NODE_ARG(0, int);
    DynamicArray *ncurves = NODE_ARG_OBJECT(1, DynamicArray);
    DynamicArray *n       = NODE_ARG_OBJECT(2, DynamicArray);
    DynamicArray *order   = NODE_ARG_OBJECT(3, DynamicArray);
    DynamicArray *knot    = NODE_ARG_OBJECT(4, DynamicArray);
    DynamicArray *min     = NODE_ARG_OBJECT(5, DynamicArray);
    DynamicArray *max     = NODE_ARG_OBJECT(6, DynamicArray);
    DynamicArray *uvw     = NODE_ARG_OBJECT(7, DynamicArray);

    gelatoAPI()->TrimCurve( nloops,
                            ncurves->data<int>(),
                            n->data<int>(),
                            order->data<int>(),
                            knot->data<float>(),
                            min->data<float>(),
                            max->data<float>(),
                            uvw->data<float>()
                          );
}

//
NODE_IMPLEMENTATION(GelatoModule::Mesh, void)
{
    StringType::String *interp = NODE_ARG_OBJECT(0, StringType::String);
    const int nfaces = NODE_ARG(1,int);
    DynamicArray *nverts = NODE_ARG_OBJECT(2, DynamicArray);
    DynamicArray *verts  = NODE_ARG_OBJECT(3, DynamicArray);

    gelatoAPI()->Mesh( interp->string().c_str(), 
                       nfaces, nverts->data<int>(), verts->data<int>());
}

//
NODE_IMPLEMENTATION(GelatoModule::Sphere, void)
{
    gelatoAPI()->Sphere( NODE_ARG(0,float), 
                         NODE_ARG(1,float), 
                         NODE_ARG(2,float), 
                         NODE_ARG(3,float) );
}

//
NODE_IMPLEMENTATION(GelatoModule::SphereR, void)
{
    gelatoAPI()->Sphere( NODE_ARG(0,float), -NODE_ARG(0,float), NODE_ARG(0,float));
}


// *****************************************************************************

bool GelatoModule::applyInlineParams( const Mu::Node &node_, 
                                      Mu::Thread &thread_,
                                      int startAtArg )
{
    Process *p = NODE_THREAD.process();
    MuLangContext *c = static_cast<MuLangContext*>(p->context());

    int nArgs = NODE_NUM_ARGS();
    for( int a = startAtArg; a < nArgs; ++a )
    {
        //
        // Get the typed parameter string, checking for goofs.
        //
        const Type *t = NODE_THIS.argNode(a)->type();
        if( t != c->stringType() && 
           t != c->charType() )
        {
            std::cerr << "Expected a string token, but got "
                      << "data of type '" << t->name().c_str() << "'"
                      << std::endl;
            return false;
        }
        
        StringType::String *token = NODE_ARG_OBJECT(a, StringType::String);
        const char *typedname = token->string().c_str();
        
        // This is needed if someone declares a parameter as "float",
        // but passes an int.  Valid only for single values!
        bool castToFloat = false;
        if( token->string().find( "float" ) != token->string().npos )
        {
            castToFloat = true;
        }

        //
        // Move to the next argument...
        //
        ++a;
        t = NODE_THIS.argNode(a)->type();
        
        // Float arrays...
        if( ( t == c->arrayType( c->floatType(), 1, 0 ) )
            || ( t == c->arrayType( c->vec3fType(), 1, 0 ) ) )
        {
            DynamicArray *da = NODE_ARG_OBJECT(a, DynamicArray);
            gelatoAPI()->Parameter( typedname, da->data<float>() );
        }
        // Int arrays...
        else if( t == c->arrayType( c->intType(), 1, 0 ) )
        {
            DynamicArray *da = NODE_ARG_OBJECT(a, DynamicArray);
            gelatoAPI()->Parameter( typedname, da->data<int>() );
        }
        // String...
        else if( t == c->stringType() )
        {
            StringType::String *str = NODE_ARG_OBJECT(a, StringType::String);
            gelatoAPI()->Parameter( typedname, str->string().c_str() );
        }
        // Single vec3
        else if( t == c->vec3fType() )
        {
            Vector3f *v = new Vector3f;
            *v = NODE_ARG(a,Vector3f);
            gelatoAPI()->Parameter( typedname, v );
        }
        // Single float
        else if( t == c->floatType() )
        {
            gelatoAPI()->Parameter( typedname, NODE_ARG(a,float) );
        }
        // Single int
        else if( t == c->intType() )
        {
            if( castToFloat ) // See above
            {
                float f = (float)NODE_ARG(a,int);
                gelatoAPI()->Parameter( typedname, f );
            }
            else
            {
                gelatoAPI()->Parameter( typedname, NODE_ARG(a,int) );
            }
        }
        else if( t == c->arrayType( c->stringType(), 1, 0 ) )
        {
            throwBadArgumentException(NODE_THIS, NODE_THREAD,
                    "Attribute: Sorry, string arrays not supported yet...");
        }
        else
        {
            std::cerr << "RiMu::Unknown data type: '"
                      << t->name().c_str() << "'" << std::endl;
            return false;
        }
    }
    return true;
}


// *****************************************************************************
NODE_IMPLEMENTATION(GelatoModule::TransformPoints, bool)
{
    std::string fromspace = NODE_ARG_OBJECT(0, StringType::String)->c_str();
    std::string tospace = NODE_ARG_OBJECT(1, StringType::String)->c_str();
    DynamicArray *verts = NODE_ARG_OBJECT(2, DynamicArray);

    TwkMath::Mat44f fromMatrix;
    TwkMath::Mat44f toMatrix;

    gelatoAPI()->PushTransform();

    gelatoAPI()->SetTransform( fromspace.c_str() );
    if( ! gelatoAPI()->GetAttribute( "matrix transform", &fromMatrix) ) NODE_RETURN( false );

    gelatoAPI()->SetTransform( tospace.c_str() );
    if( ! gelatoAPI()->GetAttribute( "matrix transform", &toMatrix) ) NODE_RETURN( false );
    
    gelatoAPI()->PopTransform();

    for( int i = 0; i < verts->size(); ++i )
    {
        TwkMath::Vec3f &p = verts->element<TwkMath::Vec3f>( i );
        p = p * fromMatrix.inverted();
        p = p * toMatrix.inverted();
    }
    
    NODE_RETURN( true );
}


} // namespace Mu

