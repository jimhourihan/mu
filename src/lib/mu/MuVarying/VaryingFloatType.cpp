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

#include "VaryingFloatType.h"
#include <Mu/Exception.h>
#include <Mu/Function.h>
#include <Mu/MachineRep.h>
#include <Mu/Node.h>
#include <Mu/NodeAssembler.h>
#include <Mu/NodePrinter.h>
#include <Mu/Object.h>
#include <Mu/Process.h>
#include <Mu/ReferenceType.h>
#include <Mu/Thread.h>
#include <Mu/Value.h>
#include <Mu/config.h>
#include <MuLang/ExceptionType.h>
#include <MuLang/FloatType.h>
#include <MuLang/MuLangContext.h>
#include <iostream>
#include <math.h>
#include <sstream>

namespace Mu {
using namespace std;

VaryingFloatType::VaryingFloatType(Context* c, const FloatType* type)
    : VaryingType(c, "varying float", type)
{
}

VaryingFloatType::~VaryingFloatType() {}

void
VaryingFloatType::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    Symbol *s = scope();
    Context* c = context();

    const char* tn  = "varying float";
    const char* rn  = "varying float&";
    const char* en  = "float";
    const char* vbn = "varying bool";

    VaryingType::load();

    s->addSymbols( new Function(c, tn, VaryingFloatType::tovarying_from_scalar,
				Function::Cast,
				Return, tn,
				Args, en, End),

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

		   new Function(c, "==", VaryingFloatType::equals, Op,
				Return, vbn,
				Args, tn, tn, End),

		   new Function(c, "!=", VaryingFloatType::nequals, Op,
				Return, vbn,
				Args, tn, tn, End),

		   new Function(c, ">", VaryingFloatType::ge, Op,
				Return, vbn,
				Args, tn, tn, End),

		   new Function(c, "<", VaryingFloatType::le, Op,
				Return, vbn,
				Args, tn, tn, End),

		   new Function(c, ">=", VaryingFloatType::geq, Op,
				Return, vbn,
				Args, tn, tn, End),

		   new Function(c, "<=", VaryingFloatType::leq, Op,
				Return, vbn,
				Args, tn, tn, End),

        	   new Function(c, "-", VaryingFloatType::uminus, Op,
				Return, tn,
				Args, tn, End),

		   new Function(c, "+", VaryingFloatType::plus, Op,
				Return, tn,
				Args, tn, tn, End),

		   new Function(c, "+", VaryingFloatType::plusf, CommOp,
				Return, tn,
				Args, tn, en, End),

		   new Function(c, "-", VaryingFloatType::minus, Op,
				Return, tn,
				Args, tn, tn, End),

		   new Function(c, "-", VaryingFloatType::minusf, Op,
				Return, tn,
				Args, tn, en, End),

		   new Function(c, "-", VaryingFloatType::fminus, Op,
				Return, tn,
				Args, en, tn, End),

		   new Function(c, "*", VaryingFloatType::times, Op,
				Return, tn,
				Args, tn, tn, End),

		   new Function(c, "*", VaryingFloatType::timesf, CommOp,
				Return, tn,
				Args, tn, en, End),

		   new Function(c, "/", VaryingFloatType::divide, Op,
				Return, tn,
				Args, tn, tn, End),

		   new Function(c, "/", VaryingFloatType::dividef, Op,
				Return, tn,
				Args, tn, en, End),

		   new Function(c, "/", VaryingFloatType::fdivide, Op,
				Return, tn,
				Args, en, tn, End),

		   new Function(c, "?:", VaryingFloatType::conditionalExpr, Op,
				Return, tn,
				Args, vbn, tn, tn, End),

                   new Function(c, "Du", VaryingFloatType::Du, None,
                                Return, tn,
                                Args, tn, End),

                   new Function(c, "Dv", VaryingFloatType::Dv, None,
                                Return, tn,
                                Args, tn, End),

                   new Function(c, "Dw", VaryingFloatType::Dw, None,
                                Return, tn,
                                Args, tn, End),

		   //---

        	   new Function(c, "print", VaryingFloatType::print, None,
				Return, "void",
				Args, tn, End),

		   EndArguments);
}

NODE_IMPLEMENTATION(VaryingFloatType::tovarying_from_scalar, Pointer)
{
    Process *p = NODE_THREAD.process();
    float value = NODE_ARG(0, float);
    const VaryingType *t = static_cast<const VaryingType*>(NODE_THIS.type());
    VaryingObject *o = new VaryingObject(t,
					 p->varyingSize(0),
					 p->varyingSize(1),
					 p->varyingSize(2));

    size_t width = t->elementRep()->width();

    for (float *i = o->data<float>(), *end = i + o->size() * width;
	 i != end;
	 i++)
    {
	*i = value;
    }

    NODE_RETURN(Pointer(o));
}

NODE_IMPLEMENTATION(VaryingFloatType::assign, Pointer)
{
    //
    //	NOTE: assign copies for varying types! They have to look like
    //	primitive scalar types!
    //

    Process *p = NODE_THREAD.process();

    //
    //	Get the type from the second argument node. This one will be a
    //	non-reference type. Alternately, we could get the type by
    //	getting the type of NODE_THIS (which will be a reference type)
    //	and getting its dereference type.
    //

    const VaryingType *c =
	static_cast<const VaryingType*>(NODE_THIS.argNode(1)->type());

    //
    //	Get the storage location and the arguments. Make a new object
    //	to put in the storage location.
    //

    VaryingObject** store;
    VaryingObject* vin;
    VaryingObject* vout;

    size_t width = c->elementRep()->width();

    store = reinterpret_cast<VaryingObject**>(NODE_ARG(0,Pointer));
    vin	  = reinterpret_cast<VaryingObject*>(NODE_ARG(1,Pointer));
    vout  = *store;

    if (!vout || 
        vout->size(0) != p->varyingSize(0) || 
        vout->size(1) != p->varyingSize(1) ||
        vout->size(2) != p->varyingSize(2))
    {
        vout = new VaryingObject(c,
                                 p->varyingSize(0),
                                 p->varyingSize(1),
                                 p->varyingSize(2));
    }
        
    //
    //	From here we're handling raw contiguous memory. This section
    //	should use some type of prefetching.
    //

    float *in   = vin->data<float>();
    float *out  = vout->data<float>();

    VaryingObject* ma;

    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool sense = NODE_THREAD.varyingMaskSense();
	bool *mask = ma->data<bool>();

	if (width == 1)
	{
	    for (float *i = out, *end = i + vout->size();
		 i != end;
		 i++, in++, mask++)
	    {
		if (*mask == sense) *i = *in;
	    }
	}
	else
	{
	    int index = 0;

	    for (float *i = out, *end = i + vout->size() * width;
		 i != end;
		 i++, in++, index++, mask += !(index % width))
	    {
		if (*mask == sense) *i = *in;
	    }
	}
    }
    else
    {
        if (in != out) memcpy(out, in, vout->size() * sizeof(float) * width);
    }

    *store = vout;
    vout->setAssigned(true);
    if (!vin->assigned()) vin->typeDelete();

    NODE_RETURN(Pointer(store));
}

#define ASOP(NAME, OP)                                                  \
NODE_IMPLEMENTATION(NAME, Pointer)                                      \
{                                                                       \
    Process *p = NODE_THREAD.process();                                 \
                                                                        \
    const VaryingType *c =                                              \
	static_cast<const VaryingType*>(NODE_THIS.argNode(1)->type());  \
                                                                        \
    VaryingObject** store;                                              \
    VaryingObject* vin;                                                 \
    VaryingObject* vout;                                                \
                                                                        \
    size_t width = c->elementRep()->width();                            \
                                                                        \
    store = reinterpret_cast<VaryingObject**>(NODE_ARG(0,Pointer));     \
    vin	  = reinterpret_cast<VaryingObject*>(NODE_ARG(1,Pointer));      \
    vout  = *store;                                                     \
                                                                        \
    if (!vout ||                                                        \
        vout->size(0) != p->varyingSize(0) ||                           \
        vout->size(1) != p->varyingSize(1) ||                           \
        vout->size(2) != p->varyingSize(2))                             \
    {                                                                   \
        vout = new VaryingObject(c,                    \
                                 p->varyingSize(0),                     \
                                 p->varyingSize(1),                     \
                                 p->varyingSize(2));                    \
    }                                                                   \
                                                                        \
    float *in   = vin->data<float>();                                   \
    float *out  = vout->data<float>();                                  \
                                                                        \
    VaryingObject* ma;                                                  \
                                                                        \
    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))    \
    {                                                                   \
	bool sense = NODE_THREAD.varyingMaskSense();                    \
	bool *mask = ma->data<bool>();                                  \
                                                                        \
	if (width == 1)                                                 \
	{                                                               \
	    for (float *i = out, *end = i + vout->size();               \
		 i != end;                                              \
		 i++, in++, mask++)                                     \
	    {                                                           \
		if (*mask == sense) *i OP *in;                          \
	    }                                                           \
	}                                                               \
	else                                                            \
	{                                                               \
	    int index = 0;                                              \
                                                                        \
	    for (float *i = out, *end = i + vout->size() * width;       \
		 i != end;                                              \
		 i++, in++, index++, mask += !(index % width))          \
	    {                                                           \
		if (*mask == sense) *i OP *in;                          \
	    }                                                           \
	}                                                               \
    }                                                                   \
    else                                                                \
    {                                                                   \
	for (float *i = out, *end = i + vout->size() * width;           \
	     i != end;                                                  \
	     i++, in++)                                                 \
	{                                                               \
	    *i OP *in;                                                  \
	}                                                               \
    }                                                                   \
                                                                        \
    *store = vout;                                                      \
    vout->setAssigned(true);                                            \
    if (!vin->assigned()) vin->typeDelete();                            \
                                                                        \
    NODE_RETURN(Pointer(store));                                        \
}

ASOP(VaryingFloatType::pluseq, +=)
ASOP(VaryingFloatType::minuseq, -=)
ASOP(VaryingFloatType::timeseq, *=)
ASOP(VaryingFloatType::divideeq, /=)


NODE_IMPLEMENTATION(VaryingFloatType::uminus, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c = static_cast<const VaryingType*>(NODE_THIS.type());

    VaryingObject* vout;
    VaryingObject* vin;

    size_t width = c->elementRep()->width();

    vin = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));

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

    VaryingObject *ma;

    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool *mask = ma->data<bool>();
	bool sense = NODE_THREAD.varyingMaskSense();

	if (width == 1)
	{
	    for (float *i = out, *end = i + vout->size();
		 i != end;
		 i++, in++, mask++)
	    {
		if (*mask == sense) *i = -(*in);
	    }
	}
	else
	{
	    int index = 0;

	    for (float *i = out, *end = i + vout->size() * width;
		 i != end;
		 i++, in++, index++, mask += !(index % width))
	    {
		if (*mask == sense) *i = -(*in);
	    }
	}
    }
    else
    {
	for (float *i = out, *end = i + vout->size() * width;
	     i != end;
	     i++, in++)
	{
	    *i = -(*in);
	}
    }

    NODE_RETURN( Pointer(vout) );
}

#define BINOP(NAME, OP)							\
NODE_IMPLEMENTATION(NAME, Pointer)					\
{									\
    Process *p = NODE_THREAD.process();					\
    const VaryingType *c =						\
	static_cast<const VaryingType*>(NODE_THIS.type());		\
									\
    size_t width = c->elementRep()->width();				\
									\
    VaryingObject* va;							\
    VaryingObject* vb;							\
    VaryingObject* vout = 0;						\
									\
    va = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));	\
    vb = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));	\
									\
    if (!va->assigned()) vout = va;					\
    if (!vb->assigned()) vout = vb;					\
									\
    if (!vout)								\
    {									\
	vout = new VaryingObject(c,			\
				 p->varyingSize(0),			\
				 p->varyingSize(1),			\
				 p->varyingSize(2));			\
    }									\
									\
									\
    float *out	= vout->data<float>();					\
    float *a	= va->data<float>();					\
    float *b	= vb->data<float>();					\
									\
    VaryingObject *ma;							\
									\
    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))	\
    {									\
	bool *mask = ma->data<bool>();					\
	bool sense = NODE_THREAD.varyingMaskSense();			\
									\
	if (width == 1)							\
	{								\
	    for (float *i = out, *end = i + vout->size();		\
		 i != end;						\
		 i++, a++, b++, mask++)					\
	    {								\
		if (*mask == sense) *i = (*a) OP (*b);			\
	    }								\
	}								\
	else								\
	{								\
	    int index = 0;						\
									\
	    for (float *i = out, *end = i + vout->size() * width;	\
		 i != end;						\
		 i++, a++, b++, index++, mask += !(index % width))	\
	    {								\
		if (*mask == sense) *i = (*a) OP (*b);			\
	    }								\
	}								\
    }									\
    else								\
    {									\
	for (float *i = out, *end = i + vout->size() * width;		\
	     i != end;							\
	     i++, a++, b++)						\
	{								\
	    *i = (*a) OP (*b);						\
	}								\
    }									\
									\
    if (!va->assigned() && va != vout) va->typeDelete();		\
    if (!vb->assigned() && vb != vout) vb->typeDelete();		\
									\
    NODE_RETURN( Pointer(vout) );					\
}

BINOP(VaryingFloatType::plus, +)
BINOP(VaryingFloatType::minus, -)
BINOP(VaryingFloatType::times, *)
BINOP(VaryingFloatType::divide, /)

#define BINOP_FLOAT(NAME, OP)						\
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
    float b = NODE_ARG(1, float);					\
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
    float *out	= vout->data<float>();					\
    float *a	= va->data<float>();					\
									\
    VaryingObject *ma;							\
									\
    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))	\
    {									\
	bool *mask = ma->data<bool>();					\
	bool sense = NODE_THREAD.varyingMaskSense();			\
									\
	if (width == 1)							\
	{								\
	    for (float *i = out, *end = i + vout->size();		\
		 i != end;						\
		 i++, a++, mask++)					\
	    {								\
		if (*mask == sense) *i = (*a) OP b;			\
	    }								\
	}								\
	else								\
	{								\
	    int index = 0;						\
									\
	    for (float *i = out, *end = i + vout->size() * width;	\
		 i != end;						\
		 i++, a++, index++, mask += !(index % width))		\
	    {								\
		if (*mask == sense) *i = (*a) OP b;			\
	    }								\
	}								\
    }									\
    else								\
    {									\
	for (float *i = out, *end = i + vout->size() * width;		\
	     i != end;							\
	     i++, a++)							\
	{								\
	    *i = (*a) OP b;						\
	}								\
    }									\
									\
    NODE_RETURN( Pointer(vout) );					\
}

BINOP_FLOAT(VaryingFloatType::plusf, +)
BINOP_FLOAT(VaryingFloatType::timesf, *)
BINOP_FLOAT(VaryingFloatType::minusf, -)
BINOP_FLOAT(VaryingFloatType::dividef, /)

#define IBINOP_FLOAT(NAME, OP)						\
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
    va = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));	\
    float b = NODE_ARG(0, float);					\
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
    float *out	= vout->data<float>();					\
    float *a	= va->data<float>();					\
									\
    VaryingObject *ma;							\
									\
    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))	\
    {									\
	bool *mask = ma->data<bool>();					\
	bool sense = NODE_THREAD.varyingMaskSense();			\
									\
	if (width == 1)							\
	{								\
	    for (float *i = out, *end = i + vout->size();		\
		 i != end;						\
		 i++, a++, mask++)					\
	    {								\
		if (*mask == sense) *i = b OP (*a);			\
	    }								\
	}								\
	else								\
	{								\
	    int index = 0;						\
									\
	    for (float *i = out, *end = i + vout->size() * width;	\
		 i != end;						\
		 i++, a++, index++, mask += !(index % width))		\
	    {								\
		if (*mask == sense) *i = b OP (*a);			\
	    }								\
	}								\
    }									\
    else								\
    {									\
	for (float *i = out, *end = i + vout->size() * width;		\
	     i != end;							\
	     i++, a++)							\
	{								\
	    *i = b OP (*a);						\
	}								\
    }									\
									\
    NODE_RETURN( Pointer(vout) );					\
}

IBINOP_FLOAT(VaryingFloatType::fminus, -)
IBINOP_FLOAT(VaryingFloatType::fdivide, /)

#define RELOP(NAME, OP)							\
NODE_IMPLEMENTATION(NAME, Pointer)					\
{									\
    Process *p = NODE_THREAD.process();					\
    const VaryingType *c =						\
	static_cast<const VaryingType*>(NODE_THIS.type());		\
									\
    VaryingObject* vout;						\
    VaryingObject* va;							\
    VaryingObject* vb;							\
									\
    va = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));	\
    vb = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));	\
									\
    vout = new VaryingObject(c, p->varyingSize(0),				\
			     p->varyingSize(1),				\
			     p->varyingSize(2));			\
									\
									\
    bool *out	= vout->data<bool>();					\
    float *a	= va->data<float>();					\
    float *b	= vb->data<float>();					\
									\
    if (VaryingObject* ma =						\
	static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))		\
    {									\
	bool *mask = ma->data<bool>();					\
	bool sense = NODE_THREAD.varyingMaskSense();			\
									\
	for (bool *i = out, *end = i + vout->size();			\
	     i != end;							\
	     i++, a++, b++, mask++)					\
	{								\
	    if (*mask == sense) *i = (*a) OP (*b);			\
	}								\
    }									\
    else								\
    {									\
	for (bool *i = out, *end = i + vout->size();			\
	     i != end;							\
	     i++, a++, b++)						\
	{								\
	    *i = (*a) OP (*b);						\
	}								\
    }									\
									\
    if (!va->assigned()) va->typeDelete();				\
    if (!vb->assigned()) vb->typeDelete();				\
									\
    NODE_RETURN( Pointer(vout) );					\
}

RELOP(VaryingFloatType::equals,==)
RELOP(VaryingFloatType::nequals,!=)
RELOP(VaryingFloatType::ge,>)
RELOP(VaryingFloatType::le,<)
RELOP(VaryingFloatType::geq,>=)
RELOP(VaryingFloatType::leq,<=)


NODE_IMPLEMENTATION(VaryingFloatType::conditionalExpr, Pointer)
{
    Process *p = NODE_THREAD.process();
    VaryingObject *test = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    VaryingObject* itest = test;

    //
    //	Save mask and mask sense.
    //

    VaryingObject *mask = 
        static_cast<VaryingObject*>(NODE_THREAD.varyingMask());
    bool maskSense  = NODE_THREAD.varyingMaskSense();

    //
    //  True path
    //

    if (mask)
    {
        itest = new VaryingObject(test->varyingType(), 
                                  p->varyingSize(0),
                                  p->varyingSize(1),
                                  p->varyingSize(2));

        bool* mb = mask->data<bool>();
        bool* ib = test->data<bool>();
        bool* b  = itest->data<bool>();
        
        for (bool* eb = b + itest->size(); b != eb; b++, ib++, mb++)
        {
            if (*mb == maskSense) *b = *ib;
            else *b = false;
        }
    }

    NODE_THREAD.setVaryingMask(itest);

    VaryingObject* va;
    VaryingObject* vb;

    NODE_THREAD.setVaryingMaskSense(true);	// true path
    va = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));

    //
    //  False path
    //

    if (mask)
    {
        bool* mb = mask->data<bool>();
        bool* ib = test->data<bool>();
        bool* b  = itest->data<bool>();
        
        for (bool* eb = b + itest->size(); b != eb; b++, ib++, mb++)
        {
            if (*mb == maskSense) *b = *ib;
            else *b = true;
        }
    }

    NODE_THREAD.setVaryingMaskSense(false);	// false path
    vb = reinterpret_cast<VaryingObject*>(NODE_ARG(2, Pointer));

    VaryingObject* vout = 0;
    if (!va->assigned()) vout = va;
    if (!vb->assigned()) vout = vb;

    const VaryingType* c = va->varyingType();
    size_t width = c->elementRep()->width();

    if (!vout)
    {
	vout = new VaryingObject(c, 
				 p->varyingSize(0),
				 p->varyingSize(1),
				 p->varyingSize(2));
    }

    bool *tmask = test->data<bool>();
    float* out  = vout->data<float>();
    float* a    = va->data<float>();
    float* b    = vb->data<float>();

    if (mask)
    {
	bool *ma = mask->data<bool>();

	if (width == 1)
	{
	    for (float *i = out, *end = i + vout->size();
		 i != end;
		 i++, a++, b++, ma++, tmask++)
	    {
		if (*ma == maskSense)
		{
		    *i = *tmask ? *a : *b;
		}
	    }
	}
	else
	{
	    size_t index = 0;

	    for (float *i = out, *end = i + vout->size() * width;
		 i != end;
		 i++, index++, a++, b++, ma+=!(index%width),
		     tmask+=!(index%width))
	    {
		if (*ma == maskSense)
		{
		    *i = *tmask ? *a : *b;
		}
	    }
	}
    }
    else
    {
        size_t index = 0;

	for (float *i = out, *end = i + vout->size() * width;
	     i != end;
	     index++, i++, a++, b++, tmask+=!(index%width))
	{
	    *i = *tmask ? *a : *b;
	}
    }

    //
    //	Restore mask and mask sense
    //

    NODE_THREAD.setVaryingMask(mask);
    NODE_THREAD.setVaryingMaskSense(maskSense);

    if (!test->assigned()) test->typeDelete();
    if (!va->assigned() && vout != va) va->typeDelete();
    if (!vb->assigned() && vout != vb) vb->typeDelete();

    NODE_RETURN(Pointer(vout));
}



//----------------------------------------------------------------------

NODE_IMPLEMENTATION(VaryingFloatType::print, void)
{
    Process *p = NODE_THREAD.process();
    VaryingObject *va = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    const VaryingType *c = va->varyingType();

    size_t width = c->elementRep()->width();
    float *a = va->data<float>();

    cout << c->name() << " (";

    if (VaryingObject* ma =
	static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool *mask = ma->data<bool>();
	bool sense = NODE_THREAD.varyingMaskSense();

	int index = 0;

	for (float *i = a, *end = i + va->size() * width;
	     i != end;
	     i++, index++, mask += !(index % width))
	{
	    if (i != a)
	    {
		cout << " ";

		if (width > 1 && !(index % width))
		{
		    cout << " ";
		}
	    }

	    if (width > 1 && !(index % width)) if (*mask == sense) cout << "*";
	    cout << *i;
	}
    }
    else
    {
	int index = 0;

	for (float *i = a, *end = i + va->size() * width;
	     i != end;
	     i++, index++)
	{
	    if (i != a)
	    {
		if (width > 1 && !(index % width)) cout << " ";
		cout << " ";
	    }
	    cout << *i;
	}
    }

    cout << ")";

    if (!va->assigned()) va->typeDelete();
}



NODE_IMPLEMENTATION(VaryingFloatType::Du, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c = static_cast<const VaryingType*>(NODE_THIS.type());

    VaryingObject* vout;
    VaryingObject* vin;

    size_t width = c->elementRep()->width();

    vin = NODE_ARG_OBJECT(0, VaryingObject);

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

#if 0
    float *out  = vout->data<float>();
    float *in   = vin->data<float>();

    VaryingObject *ma;

    size_t xs = p->varyingSize(0);
    size_t ys = p->varyingSize(1);
    size_t zs = p->varyingSize(2);

    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool *mask = ma->data<bool>();
	bool sense = NODE_THREAD.varyingMaskSense();
    }
    else
    {
        for (int y = 0; y < ys; y++)
        {
            int yoff = y * xs;

            for (int x = 0; x < xs; x++)
            {
                in[yoff + x] = in[
            }
        }
    }
#endif

    NODE_RETURN( Pointer(vout) );
}

NODE_IMPLEMENTATION(VaryingFloatType::Dv, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c = static_cast<const VaryingType*>(NODE_THIS.type());

    VaryingObject* vout;
    VaryingObject* vin;

    size_t width = c->elementRep()->width();

    vin = NODE_ARG_OBJECT(0, VaryingObject);
    return vin;
}

NODE_IMPLEMENTATION(VaryingFloatType::Dw, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c = static_cast<const VaryingType*>(NODE_THIS.type());

    VaryingObject* vout;
    VaryingObject* vin;

    size_t width = c->elementRep()->width();

    vin = NODE_ARG_OBJECT(0, VaryingObject);
    return vin;
}

} // namespace Mu
