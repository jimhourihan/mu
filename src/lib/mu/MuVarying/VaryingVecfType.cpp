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

#include <Mu/Exception.h>
#include <Mu/Function.h>
#include <Mu/Vector.h>
#include <Mu/MachineRep.h>
#include <Mu/MemberVariable.h>
#include <Mu/Node.h>
#include <Mu/NodeAssembler.h>
#include <Mu/NodePrinter.h>
#include <Mu/Object.h>
#include <Mu/Process.h>
#include <Mu/ReferenceType.h>
#include <Mu/Thread.h>
#include <Mu/Value.h>
#include <Mu/Vector.h>
#include <Mu/config.h>
#include <MuLang/ExceptionType.h>
#include <MuLang/MuLangContext.h>
#include "VaryingFloatType.h"
#include "VaryingVecfType.h"
#include "VaryingVecfType.h"
#include <iostream>
#include <math.h>
#include <sstream>

namespace Mu {
using namespace std;

VaryingVecfType::VaryingVecfType(Context* c,
                                 const char *name,
				 const Type* type,
				 const VaryingComponentType* compType)
    : VaryingType(c, name, type),
      _componentType(compType)
{

}

VaryingVecfType::~VaryingVecfType() {}

void
VaryingVecfType::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    Symbol *s = scope();
    Context* c = context();

    char en[80];  sprintf(en, "%s", elementType()->name().c_str());
    char tn[80];  sprintf(tn, "varying %s", en);
    char rn[80];  sprintf(rn, "varying %s&", en);
    char vbn[80]; sprintf(vbn, "varying bool");
    const char *ven = "varying float";

    VaryingType::load();

    //
    //	The majority of these are defined in VaryingFloatType. Those
    //	functions are generalized for any width float array so they
    //	work for vector versions as well.
    //

    s->addSymbols( new Function(c, tn, VaryingFloatType::tovarying_from_scalar,
				Cast,
				Return, tn,
				Args, "float", End),

		   new Function(c, tn, VaryingVecfType::construct_from_1varying,
				Cast,
				Return, tn,
				Args, ven, End),

		   new Function(c, "=", VaryingFloatType::assign, AsOp,
				Return, rn,
				Args, rn, tn, End),

		   new Function(c, "+=", VaryingFloatType::pluseq, AsOp,
				Return, rn,
				Args, rn, tn, End),

		   new Function(c, "-=", VaryingFloatType::minuseq, AsOp,
				Return, rn,
				Args, rn, tn, End),

		   new Function(c, "*=", VaryingFloatType::timeseq, AsOp,
				Return, rn,
				Args, rn, tn, End),

		   new Function(c, "/=", VaryingFloatType::divideeq, AsOp,
				Return, rn,
				Args, rn, tn, End),

        	   new Function(c, "-", VaryingFloatType::uminus, Op,
				Return, tn,
				Args, tn, End),

		   new Function(c, "+", VaryingFloatType::plus, Op,
				Return, tn,
				Args, tn, tn, End),

		   new Function(c, "+", VaryingFloatType::plusf, CommOp,
				Return, tn,
				Args, tn, "float", End),

		   new Function(c, "-", VaryingFloatType::minus, Op,
				Return, tn,
				Args, tn, tn, End),

		   new Function(c, "-", VaryingFloatType::minusf, Op,
				Return, tn,
				Args, tn, "float", End),

		   new Function(c, "-", VaryingFloatType::fminus, Op,
				Return, tn,
				Args, "float", tn, End),

		   new Function(c, "*", VaryingFloatType::times, Op,
				Return, tn,
				Args, tn, tn, End),

		   new Function(c, "*", VaryingFloatType::timesf, CommOp,
				Return, tn,
				Args, tn, "float", End),

		   new Function(c, "/", VaryingFloatType::divide, Op,
				Return, tn,
				Args, tn, tn, End),

		   new Function(c, "/", VaryingFloatType::dividef, Op,
				Return, tn,
				Args, tn, "float", End),

		   new Function(c, "/", VaryingFloatType::fdivide, Op,
				Return, tn,
				Args, "float", tn, End),

		   new Function(c, "dot", dot, None,
				Return, ven,
				Args, tn, tn, End),

		   new Function(c, "mag", mag, None,
				Return, ven,
				Args, tn, End),

		   new Function(c, "normalize", normalize, None,
				Return, tn,
				Args, tn, End),

		   new Function(c, "cross", cross, None,
				Return, tn,
				Args, tn, tn, End),

		   new Function(c, "?:", VaryingFloatType::conditionalExpr, Op,
				Return, tn,
				Args, vbn, tn, tn, End),

		   new Function(c, "print", VaryingFloatType::print, None,
				Return, "void",
				Args, tn, End),

		   EndArguments);

    addSymbols( new Function(c, "[]", VaryingVecfType::index, None,
                             Return, "varying vector component",
                             Args, tn, "int", End),

                EndArguments);

    size_t width = elementRep()->width();

    const char *memberNames = "xyzw";
    NodeFunc funcs[4] = { VaryingVecfType::component0Ref,
			  VaryingVecfType::component1Ref,
			  VaryingVecfType::component2Ref,
			  VaryingVecfType::component3Ref };

    for (int i=0; i < width; i++)
    {
	char refName[20]; sprintf(refName, "__%c_ref", memberNames[i]);
	char mv[2];
	mv[0] = memberNames[i];
	mv[1] = 0;

	Function *ref = new Function(c, refName, funcs[i], None,
				     Return, "varying vector component",
				     Args, tn, End);

	FunctionMemberVariable *v =
	    new FunctionMemberVariable(c, mv, ven, ref, ref, i);
	addSymbols(ref, v, EndArguments);
    }


    switch (width)
    {
      case 2:
	  s->addSymbols( new Function(c, tn,
				      VaryingVecfType::tovarying2_from_vec2,
				      Function::Cast,
				      Return, tn,
				      Args, en, End),

			 new Function(c, tn,
				      VaryingVecfType::construct_from_varying,
				      Function::None,
				      Return, tn,
				      Args, ven, ven, End),

			 new Function(c, "*", VaryingVecfType::times2v, CommOp,
				      Return, tn,
				      Args, tn, en, End),

			 new Function(c, "+", VaryingVecfType::plus2v, CommOp,
				      Return, tn,
				      Args, tn, en, End),
			 EndArguments);

	  break;
      case 3:
	  s->addSymbols( new Function(c, tn,
				      VaryingVecfType::tovarying3_from_vec3,
				      Function::Cast,
				      Return, tn,
				      Args, en, End),

			 new Function(c, tn,
				      VaryingVecfType::construct_from_varying,
				      Function::None,
				      Return, tn,
				      Args, ven, ven, ven, End),

			 new Function(c, "*", VaryingVecfType::times3v, CommOp,
				      Return, tn,
				      Args, tn, en, End),

			 new Function(c, "+", VaryingVecfType::plus3v, CommOp,
				      Return, tn,
				      Args, tn, en, End),
			 EndArguments );
	  break;
      case 4:
	  s->addSymbols(new Function(c, tn,
				     VaryingVecfType::tovarying4_from_vec4,
				     Function::Cast,
				     Return, tn,
				     Args, en, End),

			 new Function(c, tn,
				      VaryingVecfType::construct_from_varying,
				      Function::None,
				      Return, tn,
				      Args, ven, ven, ven, ven, End),

			new Function(c, "*", VaryingVecfType::times4v, CommOp,
				     Return, tn,
				     Args, tn, en, End),

			new Function(c, "+", VaryingVecfType::plus4v, CommOp,
				     Return, tn,
				     Args, tn, en, End),
			EndArguments );
	  break;
    }
}


#define TOVARYING(NAME, TYPE)					\
NODE_IMPLEMENTATION(NAME, Pointer)				\
{								\
    Process *p = NODE_THREAD.process();				\
    TYPE value = NODE_ARG(0, TYPE);				\
    const VaryingType *t =					\
	static_cast<const VaryingType*>(NODE_THIS.type());	\
    VaryingObject *o = new VaryingObject(t, p->varyingSize(0),	\
					 p->varyingSize(1),	\
					 p->varyingSize(2));	\
								\
    size_t width = t->elementRep()->width();			\
								\
    for (TYPE *i = o->data<TYPE>(), *end = i + o->size();	\
	 i != end;						\
	 i++)							\
    {								\
	*i = value;						\
    }								\
								\
    NODE_RETURN(Pointer(o));					\
}

TOVARYING(VaryingVecfType::tovarying4_from_vec4, Vector4f)
TOVARYING(VaryingVecfType::tovarying3_from_vec3, Vector3f)
TOVARYING(VaryingVecfType::tovarying2_from_vec2, Vector2f)

NODE_IMPLEMENTATION(VaryingVecfType::construct_from_1varying, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c =
	static_cast<const VaryingType*>(NODE_THIS.type());

    size_t width = c->elementRep()->width();

    VaryingObject *vout = new VaryingObject(c, 
					    p->varyingSize(0),
					    p->varyingSize(1),
					    p->varyingSize(2));

    VaryingObject *comp;
    float *cdata;

    comp  = reinterpret_cast<VaryingObject*>(NODE_ARG(0,Pointer));
    cdata = comp->data<float>();
    float *out= vout->data<float>();

    VaryingObject *ma;

    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool *mask = ma->data<bool>();
	bool sense = NODE_THREAD.varyingMaskSense();

	for (float *i = out, *end = out + vout->size() * width;
	     i < end;
	     i+=width, cdata++, mask++)
	{
	    if (*mask == sense)
	    {
		for (size_t q=0; q < width; q++)
		{
		    i[q] = *cdata;
		}
	    }
	}
    }
    else
    {
	for (float *i = out, *end = out + vout->size() * width;
	     i < end;
	     i+=width, cdata++)
	{
	    for (size_t q=0; q < width; q++)
	    {
		i[q] = *cdata;
	    }
	}
    }

    NODE_RETURN(vout);
}


NODE_IMPLEMENTATION(VaryingVecfType::construct_from_varying, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c =
	static_cast<const VaryingType*>(NODE_THIS.type());

    size_t width = c->elementRep()->width();

    VaryingObject *vout = new VaryingObject(c, 
					    p->varyingSize(0),
					    p->varyingSize(1),
					    p->varyingSize(2));

    VaryingObject *comp[4];
    float *cdata[4];

    for (int i=0; i < width; i++)
    {
	comp[i]  = reinterpret_cast<VaryingObject*>(NODE_ARG(i,Pointer));
	cdata[i] = comp[i]->data<float>();
    }

    float *out= vout->data<float>();

    VaryingObject *ma;

    //
    //  No attension is paid to the mask since we're constructing a
    //  new value.
    //

    for (float *i = out, *end = out + vout->size() * width;
         i < end;
         i+=width)
    {
        for (size_t q=0; q < width; q++)
        {
            i[q] = *(cdata[q]);
            cdata[q]++;
        }
    }

    NODE_RETURN(vout);
}

#define BINOP_VEC(NAME, TYPE, OP)					\
NODE_IMPLEMENTATION(NAME, Pointer)					\
{									\
    Process *p = NODE_THREAD.process();					\
    const VaryingType *c =						\
	static_cast<const VaryingType*>(NODE_THIS.type());		\
									\
    size_t width = c->elementRep()->width();				\
									\
    VaryingObject* va;							\
    VaryingObject* vout = 0;						\
									\
    va = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));	\
    TYPE b = NODE_ARG(1, TYPE);						\
									\
    if (!va->assigned()) vout = va;					\
									\
    if (!vout)								\
    {									\
	vout = new VaryingObject(c, p->varyingSize(0),			\
				 p->varyingSize(1),			\
				 p->varyingSize(2));			\
    }									\
									\
									\
    TYPE *out	= vout->data<TYPE>();					\
    TYPE *a	= va->data<TYPE>();					\
									\
    VaryingObject *ma;							\
									\
    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))	\
    {									\
	bool *mask = ma->data<bool>();					\
	bool sense = NODE_THREAD.varyingMaskSense();			\
									\
	    for (TYPE *i = out, *end = i + vout->size();		\
		 i != end;						\
		 i++, a++, mask++)					\
	    {								\
		if (*mask == sense) *i = (*a) OP b;			\
	    }								\
    }									\
    else								\
    {									\
	for (TYPE *i = out, *end = i + vout->size();			\
	     i != end;							\
	     i++, a++)							\
	{								\
	    *i = (*a) OP b;						\
	}								\
    }									\
									\
    if (!va->assigned() && va != vout) va->typeDelete();		\
    NODE_RETURN( Pointer(vout) );					\
}

BINOP_VEC(VaryingVecfType::plus4v, Vector4f, +)
BINOP_VEC(VaryingVecfType::times4v, Vector4f, *)
BINOP_VEC(VaryingVecfType::plus3v, Vector3f, +)
BINOP_VEC(VaryingVecfType::times3v, Vector3f, *)
BINOP_VEC(VaryingVecfType::plus2v, Vector2f, +)
BINOP_VEC(VaryingVecfType::times2v, Vector2f, *)


#define COMP_REF(NAME, NUM)						\
NODE_IMPLEMENTATION(NAME, Pointer)					\
{									\
    VaryingObject *in = 						\
	reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));		\
    VaryingObject *out = new VaryingObject(in, NUM);              \
    in->setAssigned(true);						\
    NODE_RETURN(Pointer(out));						\
}

COMP_REF(VaryingVecfType::component0Ref, size_t(0));
COMP_REF(VaryingVecfType::component1Ref, size_t(1));
COMP_REF(VaryingVecfType::component2Ref, size_t(2));
COMP_REF(VaryingVecfType::component3Ref, size_t(3));

NODE_IMPLEMENTATION(VaryingVecfType::index, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c =
	static_cast<const VaryingType*>(NODE_THIS.type());
    size_t width = c->elementRep()->width();
    VaryingObject *in =
	reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    int i = NODE_ARG(1, int);

    if (i < 0 || i >= width)
    {
        throw OutOfRangeException(NODE_THREAD);
    }

    VaryingObject *out = new VaryingObject(in, i);
    in->setAssigned(true);
    NODE_RETURN(Pointer(out));
}

NODE_IMPLEMENTATION(VaryingVecfType::dot, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c =
	static_cast<const VaryingType*>(NODE_THIS.type());

    VaryingObject* va =
	reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    VaryingObject* vb =
	reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));
    VaryingObject* vout = new VaryingObject(c,
                                            p->varyingSize(0),
                                            p->varyingSize(1),
                                            p->varyingSize(2));

    size_t width = va->varyingType()->elementRep()->width();

    VaryingObject *mask = 
        static_cast<VaryingObject*>(NODE_THREAD.varyingMask());
    bool maskSense  = NODE_THREAD.varyingMaskSense();

    float *out	= vout->data<float>();
    float *a	= va->data<float>();
    float *b	= vb->data<float>();

    if (mask)
    {
	bool *ma = mask->data<bool>();

        switch (width)
        {
          case 2:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=2, b+=2, ma++)
              {
                  if (*ma == maskSense)
                  {
                      *i = a[0] * b[0] + a[1] * b[1];
                  }
              }
              break;

          case 3:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=3, b+=3, ma++)
              {
                  if (*ma == maskSense)
                  {
                      *i = a[0] * b[0] + a[1] * b[1]  + a[2] * b[2];
                  }
              }
              break;

          case 4:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=4, b+=4, ma++)
              {
                  if (*ma == maskSense)
                  {
                      *i = a[0] * b[0] + a[1] * b[1] 
                          + a[2] * b[2] + a[3] * b[3];
                  }
              }
              break;
        }
    }
    else
    {
        switch (width)
        {
          case 2:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=2, b+=2)
              {
                  *i = a[0] * b[0] + a[1] * b[1];
              }
              break;

          case 3:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=3, b+=3)
              {
                  *i = a[0] * b[0] + a[1] * b[1]  + a[2] * b[2];
              }
              break;

          case 4:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=4, b+=4)
              {
                  *i = a[0] * b[0] + a[1] * b[1] 
                      + a[2] * b[2] + a[3] * b[3];
              }
              break;
        }
    }

    if (va != vout && !va->assigned()) va->typeDelete();
    if (va != vout && !vb->assigned()) vb->typeDelete();
    NODE_RETURN(Pointer(vout));
}

NODE_IMPLEMENTATION(VaryingVecfType::mag, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c =
	static_cast<const VaryingType*>(NODE_THIS.type());

    VaryingObject* va =
	reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));

    VaryingObject* vout = new VaryingObject(c,
                                            p->varyingSize(0),
                                            p->varyingSize(1),
                                            p->varyingSize(2));

    size_t width = va->varyingType()->elementRep()->width();

    VaryingObject *mask = 
        static_cast<VaryingObject*>(NODE_THREAD.varyingMask());
    bool maskSense  = NODE_THREAD.varyingMaskSense();

    float *out	= vout->data<float>();
    float *a	= va->data<float>();

    if (mask)
    {
	bool *ma = mask->data<bool>();

        switch (width)
        {
          case 2:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=2, ma++)
              {
                  if (*ma == maskSense)
                  {
                      *i = sqrt(a[0] * a[0] + a[1] * a[1]);
                  }
              }
              break;

          case 3:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=3, ma++)
              {
                  if (*ma == maskSense)
                  {
                      *i = sqrt(a[0] * a[0] + a[1] * a[1]  + a[2] * a[2]);
                  }
              }
              break;

          case 4:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=4, ma++)
              {
                  if (*ma == maskSense)
                  {
                      *i = sqrt(a[0] * a[0] + a[1] * a[1] 
                          + a[2] * a[2] + a[3] * a[3]);
                  }
              }
              break;
        }
    }
    else
    {
        switch (width)
        {
          case 2:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=2)
              {
                  *i = sqrt(a[0] * a[0] + a[1] * a[1]);
              }
              break;

          case 3:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=3)
              {
                  *i = sqrt(a[0] * a[0] + a[1] * a[1]  + a[2] * a[2]);
              }
              break;

          case 4:
              for (float *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=4)
              {
                  *i = sqrt(a[0] * a[0] + a[1] * a[1] 
                            + a[2] * a[2] + a[3] * a[3]);
              }
              break;
        }
    }

    if (va != vout && !va->assigned()) va->typeDelete();
    NODE_RETURN(Pointer(vout));
}

NODE_IMPLEMENTATION(VaryingVecfType::normalize, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c =
	static_cast<const VaryingType*>(NODE_THIS.type());

    VaryingObject* va =
	reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    VaryingObject* vout = va;

    if (va->assigned())
    {
        vout = new VaryingObject(c, 
                                 p->varyingSize(0),
                                 p->varyingSize(1),
                                 p->varyingSize(2));
    }

    size_t width = va->varyingType()->elementRep()->width();

    VaryingObject *mask = 
        static_cast<VaryingObject*>(NODE_THREAD.varyingMask());
    bool maskSense  = NODE_THREAD.varyingMaskSense();

    if (mask)
    {
	bool *ma = mask->data<bool>();

        switch (width)
        {
          case 2:
              {
                  Vector2f *out = vout->data<Vector2f>();
                  Vector2f *a = va->data<Vector2f>();

                  for (Vector2f *i = out, *end = i + vout->size();
                       i != end;
                       i++, a++, ma++)
                  {
                      if (*ma == maskSense) *i = Mu::normalize(*a);
                  }
              }
              break;

          case 3:
              {
                  Vector3f *out = vout->data<Vector3f>();
                  Vector3f *a = va->data<Vector3f>();

                  for (Vector3f *i = out, *end = i + vout->size();
                       i != end;
                       i++, a++, ma++)
                  {
                      if (*ma == maskSense) *i = Mu::normalize(*a);
                  }
              }
              break;

          case 4:
              {
                  Vector4f *out = vout->data<Vector4f>();
                  Vector4f *a = va->data<Vector4f>();

                  for (Vector4f *i = out, *end = i + vout->size();
                       i != end;
                       i++, a++, ma++)
                  {
                      if (*ma == maskSense) *i = Mu::normalize(*a);
                  }
              }
              break;
        }
    }
    else
    {
        switch (width)
        {
          case 2:
              {
                  Vector2f *out = vout->data<Vector2f>();
                  Vector2f *a = va->data<Vector2f>();
                  for (Vector2f* i = out, *end = i + vout->size();
                       i != end;
                       i++, a++)
                  {
                      *i = Mu::normalize(*a);
                  }
              }
              break;

          case 3:
              {
                  Vector3f *out = vout->data<Vector3f>();
                  Vector3f *a = va->data<Vector3f>();
                  for (Vector3f* i = out, *end = i + vout->size();
                       i != end;
                       i++, a++)
                  {
                      *i = Mu::normalize(*a);
                  }
              }
              break;

          case 4:
              {
                  Vector4f *out = vout->data<Vector4f>();
                  Vector4f *a = va->data<Vector4f>();
                  for (Vector4f* i = out, *end = i + vout->size();
                       i != end;
                       i++, a++)
                  {
                      *i = Mu::normalize(*a);
                  }
              }
              break;
        }
    }

    if (va != vout && !va->assigned()) va->typeDelete();
    NODE_RETURN(Pointer(vout));
}

NODE_IMPLEMENTATION(VaryingVecfType::cross, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c =
	static_cast<const VaryingType*>(NODE_THIS.type());

    VaryingObject* va =
	reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    VaryingObject* vb =
	reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));
    VaryingObject* vout = new VaryingObject(c,
                                            p->varyingSize(0),
                                            p->varyingSize(1),
                                            p->varyingSize(2));

    size_t width = va->varyingType()->elementRep()->width();

    VaryingObject *mask = 
        static_cast<VaryingObject*>(NODE_THREAD.varyingMask());
    bool maskSense  = NODE_THREAD.varyingMaskSense();

    Vector3f *out = vout->data<Vector3f>();
    Vector3f *a   = va->data<Vector3f>();
    Vector3f *b   = vb->data<Vector3f>();

    if (mask)
    {
	bool *ma = mask->data<bool>();

        switch (width)
        {
          case 3:
              for (Vector3f *i = out, *end = i + vout->size();
                   i != end;
                   i++, a++, b++, ma++)
              {
                  if (*ma == maskSense)
                  {
                      *i = Mu::cross(*a, *b);
                  }
              }
              break;

          default:
              throw BadArgumentException(NODE_THREAD);
        }
    }
    else
    {
        switch (width)
        {
          case 3:
              for (Vector3f *i = out, *end = i + vout->size();
                   i != end;
                   i++, a+=3, b+=3)
              {
                  *i = Mu::cross(*a, *b);
              }
              break;

          default:
              throw BadArgumentException(NODE_THREAD);
        }
    }

    if (!va->assigned()) va->typeDelete();
    if (!vb->assigned()) vb->typeDelete();
    NODE_RETURN(Pointer(vout));
}


} // namespace Mu
