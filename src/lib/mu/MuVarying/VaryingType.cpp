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

#include "VaryingObject.h"
#include "VaryingType.h"
#include <Mu/BaseFunctions.h>
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

VaryingType::VaryingType(Context* c, const char *name, const Type *elementType)
    : Type(c, name, PointerRep::rep()),
      _elementType(elementType)
{
    _selfManaged = true;
}

VaryingType::~VaryingType()
{
    // nothing
}

Object*
VaryingType::newObject() const
{
    return 0;
}

void
VaryingType::deleteObject(Object *obj) const
{
    delete static_cast<VaryingObject*>(obj);
}

DataNode*
VaryingType::newNode() const
{
    return 0;
}

Value
VaryingType::nodeEval(const Node* n, Thread& thread) const
{
    return Value((*n->func()._PointerFunc)(*n,thread));
}

void
VaryingType::nodeEval(void *p, const Node* n, Thread& thread) const
{
    Pointer *pp = reinterpret_cast<Pointer*>(p);
    *pp = (*n->func()._PointerFunc)(*n,thread);
}

void
VaryingType::outputValue(ostream &o, const Value &value) const
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
VaryingType::markRecursive(Object *o, bool mark) const
{
    VaryingObject *array = static_cast<VaryingObject*>(o);
    const Type *t = elementType();

    if (array->_other)
    {
	array->_other->markRecursive(mark);
    }

    if (t->machineRep() == PointerRep::rep())
    {
	for (int i=0, s=array->size(); i < s; i++)
	{
	    if (Object *e = array->element<Object*>(i))
	    {
		e->markRecursive(mark);
	    }
	}
    }
}

void
VaryingType::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    Symbol *s = scope();
    Context* c = context();

    string tname = name();
    string rname = tname + "&";
    string ename = elementType()->name();

    const char *tn = tname.c_str();
    const char *rn = rname.c_str();
    const char *et = elementType()->name().c_str();
    const char *re = elementType()->referenceType()->name().c_str();

    const MachineRep *erep = elementType()->machineRep();

    s->addSymbols( new ReferenceType(c,rn,this),

		   new Function(c, tn, VaryingType::construct, None,
				Return, tn, End),

		   new Function(c, tn, BaseFunctions::dereference, Cast,
				Return, tn,
				Args, rn, End),

		   EndArguments);

    addSymbols( new Function(c, "__retain", VaryingType::retain, None,
			     Return, tn,
			     Args, tn, End),

		new Function(c, "__release", VaryingType::release, None,
			     Return, tn,
			     Args, tn, End),

		EndArguments );
}


NODE_IMPLEMENTATION(VaryingType::construct, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c = static_cast<const VaryingType*>(NODE_THIS.type());
    VaryingObject *o = new VaryingObject(c, 
					 p->varyingSize(0),
					 p->varyingSize(1),
					 p->varyingSize(2));
    NODE_RETURN(Pointer(o));
}


NODE_IMPLEMENTATION(VaryingType::retain, Pointer)
{
    //
    //	This is applied before calls to functions that retain objects
    //	not under the control fo the VaryingType. An example is the
    //	ArrayType::push_back function which causes the array to hold a
    //	reference to an object. This node will be inserted before the
    //	argument to any retaining function to cause either a copy of
    //	the input (if its already assigned somewhere) and it will set
    //	the assigned bit. The garbage collector will be responsible
    //	for the object after this function is run.
    //

    VaryingObject* o = reinterpret_cast<VaryingObject*>(NODE_ARG(0,Pointer));

    if (o->assigned())
    {
	o = new VaryingObject(o);
    }

    o->setAssigned(true);
    NODE_RETURN(Pointer(o));
}

NODE_IMPLEMENTATION(VaryingType::release, Pointer)
{
    //
    //	This function is inserted at the end of stack frames in order
    //	to immediately release stack objects.
    //

    delete reinterpret_cast<VaryingObject*>(NODE_ARG(0,Pointer));
    NODE_RETURN(Pointer(0));
}


} // namespace Mu
