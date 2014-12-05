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

#include "VaryingMath.h"
#include <Mu/Module.h>
#include <Mu/Process.h>
#include <Mu/Thread.h>
#include <MuLang/Noise.h>
#include <MuVarying/VaryingObject.h>
#include <MuVarying/VaryingType.h>
#include <algorithm>
#include <math.h>
#include <stdlib.h>

using namespace std;

#ifdef TWK_NO_FLOAT_INTRINSICS
extern "C" {
static float sinf(float x) { return float(::sin(double(x))); }
static float cosf(float x) { return float(::cos(double(x))); }
static float tanf(float x) { return float(::tan(double(x))); }
static float asinf(float x) { return float(::asin(double(x))); }
static float acosf(float x) { return float(::acos(double(x))); }
static float atanf(float x) { return float(::atan(double(x))); }
static float expf(float x) { return float(::exp(double(x))); }
static float expm1f(float x) { return float(::expm1(double(x))); }
static float logf(float x) { return float(::log(double(x))); }
static float log10f(float x) { return float(::log10(double(x))); }
static float log1pf(float x) { return float(::log1p(double(x))); }
static float sqrtf(float x) { return float(::sqrt(double(x))); }
static float cbrtf(float x) { return float(::cbrt(double(x))); }
//static float floorf(float x) { return float(::floor(double(x))); }
//static float ceilf(float x) { return float(::ceil(double(x))); }
//static float rintf(float x) { return float(::rint(double(x))); }

static float powf(float x, float y) 
{ 
    return float(::pow(double(x), double(y))); 
}

static float atan2f(float x, float y) 
{ 
    return float(::atan2(double(x), double(y))); 
}

static float hypotf(float x, float y) 
{ 
    return float(::hypot(double(x), double(y))); 
}
}
#endif

inline float frand(double a)
{
    return float( double(::random()) / double(ULONG_MAX >> 1) * a );
}

static float f_random(float a) { return frand(a); }
static float f_random2(float min, float max) { return frand(max - min) + min; }

static float inversesqrtf(float x) { return float(1.0 / ::sqrt(double(x))); }
static float max_f(float x, float y) { return x > y ? x : y; }
static float min_f(float x, float y) { return x < y ? x : y; }
static int max_i(int x, int y) { return x > y ? x : y; }
static int min_i(int x, int y) { return x < y ? x : y; }
static int abs_i(int x) { return x < 0 ? -x : x; }

static float step(float a, float t) { return t < a ? 0.0f : 1.0f; }

static float clamp(float val, float min, float max)
{
    return val < min ? min : (val > max ? max : val);
}

static float linstep(float a, float b, float t)
{
    bool invert = false;

    if (a > b)
    {
        invert = true;
        swap(a, b);
    }

    if (t < a)
    {
	return (invert ? 1.0f : 0.0f);
    }
    else
    {
	if (t < b)
	{
	    if (invert)
	    {
		return ( (t - b) / (a - b) );
	    }
	    else
	    {
		return ( (t - a) / (b - a) );
	    }
	}
	else
	{
	    return invert ? 0.0f : 1.0f;
	}
    }
}

static float smoothstep(float a, float b, float t)
{
    bool invert = false;

    if (a > b)
    {
        invert = true;
        swap(a, b);
    }

    t  = (t - a) / (b - a);

    if (t < 0.0)
    {
	return (invert ? 1.0f : 0.0f);
    }
    else
    {
	if (t < 1.0)
	{
	    const float t2 = t * t; 
	    const float t3 = t2 * t ;
            const float r = float(-2.f * t3 + 3.f * t2);
	    return invert ? 1.0f - r : r;
	}
	else
	{
	    return invert ? 0.0f : 1.0f;
	}
    }
}

static float lerp(float a, float b, float t)
{
    return b * t + a * (1.0f - t);
}

static float degrees (float a)  { return a * 57.29578; }
static float radians (float a) { return a * 0.017453293; }

namespace Mu {
namespace VMath {

typedef float (*FloatGeneratorFunction)(float);
typedef float (*UnaryFloatMathFunction)(float);
typedef float (*UnaryVecMathFunction)(const float*);
typedef float (*BinaryFloatMathFunction)(float,float);
typedef float (*TertiaryFloatMathFunction)(float,float,float);

typedef int   (*UnaryIntMathFunction)(int);
typedef int   (*BinaryIntMathFunction)(int,int);


VaryingObject* 
map(Process *p, 
    VaryingObject* vin, 
    VaryingObject* ma, 
    bool sense, 
    UnaryFloatMathFunction F)
{
    const VaryingType *c = vin->varyingType();

    VaryingObject* vout;

    size_t width = c->elementRep()->width();

    if (vin->assigned())
    {
	vout = new VaryingObject(c, 
				 p->varyingSize(0),
				 p->varyingSize(1),
				 p->varyingSize(2));
    }
    else
    {
	vout = vin;
    }

    float *out  = vout->data<float>();
    float *in   = vin->data<float>();

    if (ma)
    {
	bool *mask = ma->data<bool>();

        for (float *i = out, *end = i + vout->size();
             i != end;
             i++, in++, mask++)
        {
            if (*mask == sense) *i = (*F)(*in);
        }
    }
    else
    {
	for (float *i = out, *end = i + vout->size();
	     i != end;
	     i++, in++)
	{
	    *i = (*F)(*in);
	}
    }

    return vout;
}

VaryingObject* 
map(Process *p, 
    VaryingObject* vin, 
    VaryingObject* ma, 
    bool sense, 
    UnaryIntMathFunction F)
{
    const VaryingType *c = vin->varyingType();

    VaryingObject* vout;

    size_t width = c->elementRep()->width();

    if (vin->assigned())
    {
	vout = new VaryingObject(c, 
				 p->varyingSize(0),
				 p->varyingSize(1),
				 p->varyingSize(2));
    }
    else
    {
	vout = vin;
    }

    int *out  = vout->data<int>();
    int *in   = vin->data<int>();

    if (ma)
    {
	bool *mask = ma->data<bool>();

        for (int *i = out, *end = i + vout->size();
             i != end;
             i++, in++, mask++)
        {
            if (*mask == sense) *i = (*F)(*in);
        }
    }
    else
    {
	for (int *i = out, *end = i + vout->size();
	     i != end;
	     i++, in++)
	{
	    *i = (*F)(*in);
	}
    }

    return vout;
}

VaryingObject* 
map(Process *p, 
    const VaryingType* tout,
    VaryingObject* vin, 
    VaryingObject* ma, 
    bool sense, 
    UnaryVecMathFunction F)
{
    const VaryingType* tin = vin->varyingType();

    VaryingObject* vout;

    size_t width = tin->elementRep()->width();

    if (vin->assigned())
    {
	vout = new VaryingObject(tout, 
				 p->varyingSize(0),
				 p->varyingSize(1),
				 p->varyingSize(2));
    }
    else
    {
	vout = vin;
    }

    float *out  = vout->data<float>();
    float *in   = vin->data<float>();

    if (ma)
    {
	bool *mask = ma->data<bool>();

        for (float *i = out, *end = i + vout->size();
             i != end;
             i++, in+=width, mask++)
        {
            if (*mask == sense) *i = (*F)(in);
        }
    }
    else
    {
	for (float *i = out, *end = i + vout->size();
	     i != end;
	     i++, in+=width)
	{
	    *i = (*F)(in);
	}
    }

    return vout;
}


#define SINGLE_ARG(NAME, FUNC)							 \
NODE_IMPLEMENTATION(NAME, Pointer)						 \
{										 \
    Process *p = NODE_THREAD.process();						 \
    VaryingObject* vin = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer)); \
    VaryingObject* ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask());	 \
    bool sense = NODE_THREAD.varyingMaskSense();				 \
    VaryingObject* vout = map(p, vin, ma, sense, FUNC);				 \
    return vout; \
}

#define SINGLE_VARG(NAME, FUNC)                                                  \
NODE_IMPLEMENTATION(NAME, Pointer)                                               \
{                                                                                \
    Process *p = NODE_THREAD.process();                                          \
    VaryingObject* vin = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer)); \
    VaryingObject* ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask());  \
    bool sense = NODE_THREAD.varyingMaskSense();                                 \
    const VaryingType* vtype =                                                   \
         static_cast<const VaryingType*>(NODE_THIS.type());                      \
    VaryingObject* vout = map(p, vtype, vin, ma, sense, FUNC);                   \
    return vout;                                                                 \
}

SINGLE_ARG(sin, ::sinf);
SINGLE_ARG(cos, ::cosf);
SINGLE_ARG(tan, ::tanf);
SINGLE_ARG(asin, ::asinf);
SINGLE_ARG(acos, ::acosf);
SINGLE_ARG(atan, ::atanf);
SINGLE_ARG(exp, ::expf);
SINGLE_ARG(expm1, ::expm1f);
SINGLE_ARG(log, ::logf);
SINGLE_ARG(log10, ::log10f);
SINGLE_ARG(log1p, ::log1pf);
SINGLE_ARG(sqrt, ::sqrtf);
SINGLE_ARG(cbrt, ::cbrtf);
SINGLE_ARG(floor, ::floorf);
SINGLE_ARG(ceil, ::ceilf);
SINGLE_ARG(rint, ::rintf);
SINGLE_ARG(inversesqrt, ::inversesqrtf);
SINGLE_ARG(abs_f, ::fabsf);
SINGLE_ARG(abs_i, ::abs_i);
SINGLE_ARG(random, ::f_random)
SINGLE_ARG(degrees, ::degrees)
SINGLE_ARG(radians, ::radians)
SINGLE_ARG(noise1, Mu::noise1)
SINGLE_VARG(noise2, Mu::noise2)
SINGLE_VARG(noise3, Mu::noise3)
SINGLE_VARG(noise4, Mu::noise3)

VaryingObject* 
map(Process *p, 
    VaryingObject* vin0, 
    VaryingObject* vin1, 
    VaryingObject* ma, 
    bool sense, 
    BinaryFloatMathFunction F)
{
    const VaryingType *c = vin0->varyingType();

    VaryingObject* vout;

    size_t width = c->elementRep()->width();

    if (vin0->assigned() && vin1->assigned())
    {
	vout = new VaryingObject(c, 
				 p->varyingSize(0),
				 p->varyingSize(1),
				 p->varyingSize(2));
    }
    else
    {
	vout = vin0->assigned() ? vin1 : vin0;
    }

    float *out  = vout->data<float>();
    float *in0  = vin0->data<float>();
    float *in1  = vin1->data<float>();

    if (ma)
    {
	bool *mask = ma->data<bool>();

        for (float *i = out, *end = i + vout->size();
             i != end;
             i++, in0++, in1++, mask++)
        {
            if (*mask == sense) *i = (*F)(*in0, *in1);
        }
    }
    else
    {
	for (float *i = out, *end = i + vout->size();
	     i != end;
	     i++, in0++, in1++)
	{
	    *i = (*F)(*in0, *in1);
	}
    }

    return vout;
}

VaryingObject* 
map(Process *p, 
    VaryingObject* vin0, 
    VaryingObject* vin1, 
    VaryingObject* ma, 
    bool sense, 
    BinaryIntMathFunction F)
{
    const VaryingType *c = vin0->varyingType();

    VaryingObject* vout;

    size_t width = c->elementRep()->width();

    if (vin0->assigned() && vin1->assigned())
    {
	vout = new VaryingObject(c, 
				 p->varyingSize(0),
				 p->varyingSize(1),
				 p->varyingSize(2));
    }
    else
    {
	vout = vin0->assigned() ? vin1 : vin0;
    }

    int *out  = vout->data<int>();
    int *in0  = vin0->data<int>();
    int *in1  = vin1->data<int>();

    if (ma)
    {
	bool *mask = ma->data<bool>();

        for (int *i = out, *end = i + vout->size();
             i != end;
             i++, in0++, in1++, mask++)
        {
            if (*mask == sense) *i = (*F)(*in0, *in1);
        }
    }
    else
    {
	for (int *i = out, *end = i + vout->size();
	     i != end;
	     i++, in0++, in1++)
	{
	    *i = (*F)(*in0, *in1);
	}
    }

    return vout;
}


#define DOUBLE_ARG(NAME, FUNC)							 \
NODE_IMPLEMENTATION(NAME, Pointer)						 \
{										 \
    Process *p = NODE_THREAD.process();						 \
    VaryingObject* vin0 = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer)); \
    VaryingObject* vin1 = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer)); \
    VaryingObject* ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask());	 \
    bool sense = NODE_THREAD.varyingMaskSense();				 \
    VaryingObject* vout = map(p, vin0, vin1, ma, sense, FUNC);			\
    NODE_RETURN(vout); \
}

DOUBLE_ARG(pow, ::powf)
DOUBLE_ARG(hypot, ::hypotf)
DOUBLE_ARG(atan2, ::atan2f)
DOUBLE_ARG(max_f, ::max_f);
DOUBLE_ARG(min_f, ::min_f);
DOUBLE_ARG(max_i, ::max_i);
DOUBLE_ARG(min_i, ::min_i);
DOUBLE_ARG(step, ::step)
DOUBLE_ARG(random2, ::f_random2)


VaryingObject* 
map(Process *p, 
    VaryingObject* vin0, 
    VaryingObject* vin1, 
    VaryingObject* vin2, 
    VaryingObject* ma, 
    bool sense, 
    TertiaryFloatMathFunction F)
{
    const VaryingType *c = vin0->varyingType();

    VaryingObject* vout;

    size_t width = c->elementRep()->width();

    if (vin0->assigned() && vin1->assigned())
    {
	vout = new VaryingObject(c, 
				 p->varyingSize(0),
				 p->varyingSize(1),
				 p->varyingSize(2));
    }
    else
    {
	vout = vin0->assigned() ? vin1 : vin0;
    }

    float *out  = vout->data<float>();
    float *in0  = vin0->data<float>();
    float *in1  = vin1->data<float>();
    float *in2  = vin2->data<float>();

    if (ma)
    {
	bool *mask = ma->data<bool>();

        for (float *i = out, *end = i + vout->size();
             i != end;
             i++, in0++, in1++, in2++, mask++)
        {
            if (*mask == sense) *i = (*F)(*in0, *in1, *in2);
        }
    }
    else
    {
	for (float *i = out, *end = i + vout->size();
	     i != end;
	     i++, in0++, in1++, in2++)
	{
	    *i = (*F)(*in0, *in1, *in2);
	}
    }

    return vout;
}


#define TRIPLE_ARG(NAME, FUNC)                                                          \
NODE_IMPLEMENTATION(NAME, Pointer)                                                      \
{                                                                                       \
    Process *p = NODE_THREAD.process();                                                 \
    VaryingObject* vin0 = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));       \
    VaryingObject* vin1 = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));       \
    VaryingObject* vin2 = reinterpret_cast<VaryingObject*>(NODE_ARG(2, Pointer));       \
    VaryingObject* ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask());         \
    bool sense = NODE_THREAD.varyingMaskSense();                                        \
    VaryingObject* vout = map(p, vin0, vin1, vin2, ma, sense, FUNC);                    \
    NODE_RETURN(vout);                                                                  \
}

TRIPLE_ARG(clamp, ::clamp)
TRIPLE_ARG(linstep, ::linstep)
TRIPLE_ARG(smoothstep, ::smoothstep)
TRIPLE_ARG(lerp, ::lerp)

void
declare(Module *math, Module *util)
{
    USING_MU_FUNCTION_SYMBOLS;

    Context* c = math->context();

    const char *vf = "varying float";
    const char *vi = "varying int";
    const char *v2f = "varying vector float[2]";
    const char *v3f = "varying vector float[3]";
    const char *v4f = "varying vector float[4]";

    math->
    addSymbols( new Function(c, "max", VMath::max_f, None,
			     Return, vf, 
			     Args, vf, vf, End),

		new Function(c, "min", VMath::min_f, None,
			     Return, vf, 
			     Args, vf, vf, End),

		new Function(c, "abs", VMath::abs_f, None,
			     Return, vf, 
			     Args, vf, End),

#if 0
		new Function(c, "max", VMath::max_i, None,
			     Return, "int", 
			     Args, "int", "int", End),
		
		new Function(c, "min", VMath::min_i, None,
			     Return, "int", 
			     Args, "int", "int", End),
		
		new Function(c, "abs", VMath::abs_i, None,
			     Return, "int", 
			     Args, "int", End),
#endif

		new Function(c, "sin", VMath::sin, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "cos", VMath::cos, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "tan", VMath::tan, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "asin", VMath::asin, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "acos", VMath::acos, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "atan", VMath::atan, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "atan2", VMath::atan2, None,
			     Return, vf, 
			     Args, vf, vf, End),

		new Function(c, "exp", VMath::exp, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "expm1", VMath::expm1, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "log", VMath::log, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "log10", VMath::log10, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "log1p", VMath::log1p, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "sqrt", VMath::sqrt, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "inversesqrt", VMath::inversesqrt, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "cbrt", VMath::cbrt, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "floor", VMath::floor, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "ceil", VMath::ceil, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "rint", VMath::rint, None,
			     Return, vf, 
			     Args, vf, End),

		new Function(c, "pow", VMath::pow, None,
			     Return, vf, 
			     Args, vf, vf, End),

		new Function(c, "hypot", VMath::hypot, None,
			     Return, vf, 
			     Args, vf, vf, End),

		Symbol::EndArguments );

    
    util->
    addSymbols( new Function(c, "clamp", VMath::clamp, None,
			     Return, vf, 
			     Args, vf, vf, vf, End),

                new Function(c, "linstep", VMath::linstep, None,
			     Return, vf, 
			     Args, vf, vf, vf, End),

                new Function(c, "smoothstep", VMath::smoothstep, None,
			     Return, vf, 
			     Args, vf, vf, vf, End),

                new Function(c, "lerp", VMath::lerp, None,
			     Return, vf, 
			     Args, vf, vf, vf, End),

                new Function(c, "step", VMath::step, None,
			     Return, vf, 
			     Args, vf, vf, End),

                new Function(c, "random", VMath::random, None,
			     Return, vf, 
			     Args, vf, End),

                new Function(c, "random", VMath::random2, None,
			     Return, vf, 
			     Args, vf, vf, End),

                new Function(c, "degrees", VMath::degrees, None,
			     Return, vf, 
			     Args, vf, End),

                new Function(c, "radians", VMath::radians, None,
			     Return, vf, 
			     Args, vf, End),

                new Function(c, "noise", VMath::noise1, None,
			     Return, vf, 
			     Args, vf, End),

                new Function(c, "noise", VMath::noise2, None,
			     Return, vf, 
			     Args, v2f, End),

                new Function(c, "noise", VMath::noise3, None,
			     Return, vf, 
			     Args, v3f, End),

                new Function(c, "noise", VMath::noise4, None,
			     Return, vf, 
			     Args, v4f, End),

		Symbol::EndArguments );
}


} // VMath
} // Mu
