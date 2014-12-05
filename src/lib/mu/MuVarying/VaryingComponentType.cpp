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

#include "VaryingComponentType.h"
#include "VaryingObject.h"
#include <Mu/Exception.h>
#include <Mu/Function.h>
#include <Mu/MachineRep.h>
#include <Mu/MemberFunction.h>
#include <Mu/ParameterVariable.h>
#include <Mu/Process.h>
#include <Mu/ReferenceType.h>
#include <Mu/Thread.h>
#include <MuLang/ExceptionType.h>
#include <iostream>
#include <memory.h>
#include <string>

namespace Mu {
using namespace std;

VaryingComponentType::VaryingComponentType(Context* c,
                                           const char *name,
					   const VaryingFloatType *ft)
    : Type(c, name, PointerRep::rep()),
      _varyingFloatType(ft)
{
    //_selfManaged = true;
}

VaryingComponentType::~VaryingComponentType()
{
    // nothing
}

Object*
VaryingComponentType::newObject() const
{
    return 0;
}

void
VaryingComponentType::deleteObject(Object *obj) const
{
    delete static_cast<VaryingObject*>(obj);
}

DataNode*
VaryingComponentType::newNode() const
{
    return 0;
}

Value
VaryingComponentType::nodeEval(const Node* n, Thread& thread) const
{
    return Value((*n->func()._PointerFunc)(*n,thread));
}

void
VaryingComponentType::nodeEval(void *p, const Node* n, Thread& thread) const
{
    Pointer *pp = reinterpret_cast<Pointer*>(p);
    *pp = (*n->func()._PointerFunc)(*n,thread);
}

void
VaryingComponentType::outputValue(ostream &o, const Value &value) const
{
    VaryingObject *s = reinterpret_cast<VaryingObject*>(value._Pointer);

    if (s)
    {
	o << s->type()->name();
	o << "@";
	o << s;
    }
    else
    {
	o << "nil";
    }
}

void
VaryingComponentType::markRecursive(Object *o, bool mark) const
{
}

void
VaryingComponentType::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    Symbol *s = scope();
    Context* c = context();

    const char *tn = name().c_str();
    const char *fn = varyingFloatType()->name().c_str();

    s->addSymbols( new Function(c, fn, ThisType::tofloatvarying, Cast,
				Return, fn,
				Args, tn, End),

		   new Function(c, "=", ThisType::assign, AsOp,
				Return, tn,
				Args, tn, tn, End),

		   new Function(c, "=", ThisType::assignf, AsOp,
				Return, tn,
				Args, tn, fn, End),

		   EndArguments);
}

NODE_IMPLEMENTATION(VaryingComponentType::tofloatvarying, Pointer)
{
    Process *p = NODE_THREAD.process();

    const VaryingFloatType *ft = 
	static_cast<const VaryingFloatType*>(NODE_THIS.type());
    const ThisType *t = 
	static_cast<const ThisType*>(NODE_THIS.argNode(0)->type());

    VaryingObject* co;
    VaryingObject* o;
    
    co = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    o  = new VaryingObject(ft,
			   p->varyingSize(0),
			   p->varyingSize(1),
			   p->varyingSize(2));

    size_t width = co->varyingType()->elementRep()->width();
    size_t coff  = co->component();
    float *comp  = co->data<float>() + coff;

    VaryingObject *ma;

    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool *mask = ma->data<bool>();
	bool sense = NODE_THREAD.varyingMaskSense();

	for (float *i = o->data<float>(), *end = i + o->size();
	     i < end;
	     i++, comp += width, mask++)
	{
	    if (*mask == sense) *i = *comp;
	}
    }
    else
    {
	for (float *i = o->data<float>(), *end = i + o->size();
	     i < end;
	     i++, comp += width)
	{
	    *i = *comp;
	}
    }

    //co->typeDelete();  its tiny, let the gc handle it
    NODE_RETURN(Pointer(o));
}


NODE_IMPLEMENTATION(VaryingComponentType::assign, Pointer)
{
    Process *p = NODE_THREAD.process();

    const ThisType *t = 
	static_cast<const ThisType*>(NODE_THIS.argNode(0)->type());

    VaryingObject* vout;
    VaryingObject* vin;
    
    vout = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    vin  = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));

    size_t ow = vout->varyingType()->elementRep()->width();
    size_t iw = vin->varyingType()->elementRep()->width();

    size_t oc = vout->component();
    size_t ic = vin->component();

    float *in = vin->data<float>() + ic;

    VaryingObject *ma;

    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool *mask = ma->data<bool>();
	bool sense = NODE_THREAD.varyingMaskSense();

	for (float *i = vout->data<float>()+oc, *end = i + vout->size() * ow;
	     i < end;
	     i += ow, in += iw, mask++)
	{
	    if (*mask == sense) *i = *in;
	}
    }
    else
    {
	for (float *i = vout->data<float>()+oc, *end = i + vout->size() * ow;
	     i < end;
	     i += ow, in += iw)
	{
	    *i = *in;
	}
    }

    NODE_RETURN(Pointer(vout));
}

NODE_IMPLEMENTATION(VaryingComponentType::assignf, Pointer)
{
    Process *p = NODE_THREAD.process();

    const ThisType *t = 
	static_cast<const ThisType*>(NODE_THIS.argNode(0)->type());

    VaryingObject* vout;
    VaryingObject* vin;
    
    vout = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    vin  = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));

    size_t oc = vout->component();
    size_t ow = vout->varyingType()->elementRep()->width();

    float *in = vin->data<float>();

    VaryingObject *ma;

    if (ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool *mask = ma->data<bool>();
	bool sense = NODE_THREAD.varyingMaskSense();

	for (float *i = vout->data<float>() + oc, *end = i + vout->size() * ow;
	     i < end;
	     i += ow, in++, mask++)
	{
	    if (*mask == sense) *i = *in;
	}
    }
    else
    {
	for (float *i = vout->data<float>() + oc, *end = i + vout->size() * ow;
	     i < end;
	     i += ow, in++)
	{
	    *i = *in;
	}
    }

    NODE_RETURN(Pointer(vout));
}

} // namespace Mu
