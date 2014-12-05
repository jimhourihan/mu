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

#include "VaryingBoolType.h"
#include <MuLang/BoolType.h>
#include <MuLang/ExceptionType.h>
#include <Mu/Function.h>
#include <Mu/Node.h>
#include <Mu/Thread.h>
#include <Mu/NodeAssembler.h>
#include <Mu/ReferenceType.h>
#include <Mu/Value.h>
#include <Mu/MachineRep.h>
#include <Mu/NodePrinter.h>
#include <Mu/config.h>
#include <Mu/Exception.h>
#include <iostream>
#include <sstream>
#include <MuLang/MuLangContext.h>
#include <Mu/Process.h>
#include <Mu/Object.h>

namespace Mu {
using namespace std;

VaryingBoolType::VaryingBoolType(Context* c, const BoolType* boolType) 
    : VaryingType(c, "varying bool", boolType)
{
}

VaryingBoolType::~VaryingBoolType() {}

void
VaryingBoolType::load()
{
    USING_MU_FUNCTION_SYMBOLS;
    Symbol *s = scope();
    Context* c = context();

    const char* tn = "varying bool";
    const char* rn = "varying bool&";
    const char* en = "bool";

    VaryingType::load();

    s->addSymbols( new Function(c, tn, VaryingBoolType::tovarying, Function::Cast,
				Return, tn,
				Args, en, End),

		   new Function(c, "=", VaryingBoolType::assign, AsOp,
				Return, rn, 
				Args, rn, tn, End),

        	   new Function(c, "!", VaryingBoolType::logicalNot, Op,
				Return, tn, 
				Args, tn, End),

		   new Function(c, "&&", VaryingBoolType::logicalAnd, Op,
				Return, tn, 
				Args, tn, tn, End),

		   new Function(c, "||", VaryingBoolType::logicalOr, Op,
				Return, tn, 
				Args, tn, tn, End),

		   new Function(c, "__if", VaryingBoolType::__if, None,
				Return, "void",
				Args, tn, "?", End),

		   new Function(c, "__if", VaryingBoolType::__if_else, None,
				Return, "void",
				Args, tn, "?", "?", End),

		   new Function(c, "?:", VaryingBoolType::conditionalExpr, Op,
				Return, tn, 
				Args, tn, tn, tn, End),

		   EndArguments);
}

NODE_IMPLEMENTATION(VaryingBoolType::tovarying, Pointer)
{
    Process *p = NODE_THREAD.process();
    bool value = NODE_ARG(0, bool);
    const VaryingType *t = static_cast<const VaryingType*>(NODE_THIS.type());
    VaryingObject *o = new VaryingObject(t,
					 p->varyingSize(0),
					 p->varyingSize(1),
					 p->varyingSize(2));

    bool *out = o->data<bool>();
    memset(out, value ? 1 : 0, o->size());

    NODE_RETURN(Pointer(o));
}

NODE_IMPLEMENTATION(VaryingBoolType::assign, Pointer)
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

    VaryingObject** store = 
	reinterpret_cast<VaryingObject**>(NODE_ARG(0,Pointer));

    VaryingObject* va = 
	reinterpret_cast<VaryingObject*>(NODE_ARG(1,Pointer));

    VaryingObject* vb = *store;

    VaryingObject *o = new VaryingObject(c,
					 p->varyingSize(0),
					 p->varyingSize(1),
					 p->varyingSize(2));

    //
    //	From here we're handling raw contiguous memory. This section
    //	should use some type of prefetching.
    //

    bool *out = o->data<bool>();
    bool *a   = va->data<bool>();
    bool *b   = vb ? vb->data<bool>() : 0;

    VaryingObject* ma;

    if ((ma = static_cast<VaryingObject*>(NODE_THREAD.varyingMask())) &&  b)
    {
	bool sense = NODE_THREAD.varyingMaskSense();
	bool *mask = ma->data<bool>();

	for (bool *i = out, *end = i + o->size();
	     i != end;
	     i++, a++, mask++, b++)
	{
	    if (*mask == sense) *i = *a;
	    else *i = *b;
	}
    }
    else
    {
	memcpy(out, a, va->size());
    }

    *store = o;
    if (vb) vb->typeDelete();
    if (!va->assigned()) va->typeDelete();
    o->setAssigned(true);

    NODE_RETURN(Pointer(store));
}


NODE_IMPLEMENTATION(VaryingBoolType::logicalNot, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c = static_cast<const VaryingType*>(NODE_THIS.type());

    VaryingObject *o = new VaryingObject(c,
					 p->varyingSize(0),
					 p->varyingSize(1),
					 p->varyingSize(2));


    VaryingObject *va = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));

    bool *out  = o->data<bool>();
    bool *a    = va->data<bool>();

    if (VaryingObject* ma = 
	static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool *mask = ma->data<bool>();
	bool sense = NODE_THREAD.varyingMaskSense();

	for (bool *i = out, *end = i + o->size();
	     i != end;
	     i++, a++, mask++)
	{
	    if (*mask == sense) *i = !(*a);
	}
    }
    else
    {
	for (bool *i = out, *end = i + o->size();
	     i != end;
	     i++, a++)
	{
	    *i = !(*a);
	}
    }

    if (!va->assigned()) va->typeDelete();

    NODE_RETURN( Pointer(o) );
}

NODE_IMPLEMENTATION(VaryingBoolType::logicalOr, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c = static_cast<const VaryingType*>(NODE_THIS.type());
    VaryingObject *o = new VaryingObject(c,
					 p->varyingSize(0),
					 p->varyingSize(1),
					 p->varyingSize(2));

    VaryingObject *va = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    VaryingObject *vb = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));

    bool *out	= o->data<bool>();
    bool *a	= va->data<bool>();
    bool *b	= vb->data<bool>();

    if (VaryingObject* ma = 
	static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool *mask = ma->data<bool>();
	bool sense = NODE_THREAD.varyingMaskSense();

	for (bool *i = out, *end = i + o->size(); 
	     i != end; 
	     i++, a++, b++, mask++)
	{
	    if (*mask == sense) *i = (*a) || (*b);
	}
    }
    else
    {
	for (bool *i = out, *end = i + o->size(); 
	     i != end; 
	     i++, a++, b++)
	{
	    *i = (*a) || (*b);
	}
    }

    if (!va->assigned()) va->typeDelete();
    if (!vb->assigned()) vb->typeDelete();

    NODE_RETURN( Pointer(o) );
}

NODE_IMPLEMENTATION(VaryingBoolType::logicalAnd, Pointer)
{
    Process *p = NODE_THREAD.process();
    const VaryingType *c = static_cast<const VaryingType*>(NODE_THIS.type());
    VaryingObject *o = new VaryingObject(c,
					 p->varyingSize(0),
					 p->varyingSize(1),
					 p->varyingSize(2));

    VaryingObject *va = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    VaryingObject *vb = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));

    bool *out = o->data<bool>();
    bool *a   = va->data<bool>();
    bool *b   = vb->data<bool>();

    if (VaryingObject* ma = 
	static_cast<VaryingObject*>(NODE_THREAD.varyingMask()))
    {
	bool *mask = ma->data<bool>();
	bool sense = NODE_THREAD.varyingMaskSense();

	for (bool *i = out, *end = i + o->size(); 
	     i != end; 
	     i++, a++, b++, mask++)
	{
	    if (*mask == sense) *i = (*a) && (*b);
	}
    }
    else
    {
	for (bool *i = out, *end = i + o->size(); 
	     i != end; 
	     i++, a++, b++)
	{
	    *i = (*a) && (*b);
	}
    }

    if (!va->assigned()) va->typeDelete();
    if (!vb->assigned()) vb->typeDelete();

    NODE_RETURN( Pointer(o) );
}

static bool
hasUniformValue(VaryingObject* obj)
{
    bool* b = obj->data<bool>();
    bool* e = b + obj->size();
    bool  v = *b;
    
    for (b++; b != e; b++)
    {
        if (*b != v) return false;
    }

    return true;
}

NODE_IMPLEMENTATION(VaryingBoolType::__if, void)
{
    Process* p = NODE_THREAD.process();

    //
    //  Make the union of the existing mask and the incoming mask
    //

    VaryingObject *mask = 
        static_cast<VaryingObject*>(NODE_THREAD.varyingMask());
    bool maskSense  = NODE_THREAD.varyingMaskSense();

    VaryingObject* test = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    VaryingObject* itest = test;

    if (mask)
    {
        if (itest->assigned())
        {
            itest = new VaryingObject(test->varyingType(),
                                      p->varyingSize(0),
                                      p->varyingSize(1),
                                      p->varyingSize(2));
        }
        
        bool* mb = mask->data<bool>();
        bool* ib = test->data<bool>();
        bool* b  = itest->data<bool>();
        
        for (bool* eb = b + itest->size(); b != eb; b++, ib++, mb++)
        {
            if (*mb == maskSense) *b = *ib;
            else *b = false;
        }
    }

    bool skip_it;

    if (skip_it = hasUniformValue(itest))
    {
        skip_it = *itest->data<bool>() != true;
    }

    if (!skip_it)
    {
        //
        //	Save mask and mask sense.
        //
        
        NODE_THREAD.setVaryingMask(itest);

        //
        //	Evaluate body
        //

        NODE_THREAD.setVaryingMaskSense(true);
        NODE_ANY_TYPE_ARG(1);

        //
        //	Restore mask and mask sense
        //

        NODE_THREAD.setVaryingMask(mask);
        NODE_THREAD.setVaryingMaskSense(maskSense);
    }

    if (!test->assigned()) test->typeDelete();
    if (test != itest) itest->typeDelete();
}

NODE_IMPLEMENTATION(VaryingBoolType::__if_else, void)
{
    Process *p = NODE_THREAD.process();

    //
    //  Make the union of the existing mask and the incoming mask
    //

    VaryingObject *mask = 
        static_cast<VaryingObject*>(NODE_THREAD.varyingMask());
    bool maskSense  = NODE_THREAD.varyingMaskSense();

    VaryingObject* test = reinterpret_cast<VaryingObject*>(NODE_ARG(0, Pointer));
    VaryingObject* itest = test;

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

    bool uniform, uval;

    if (uniform = hasUniformValue(itest))
    {
        uval = itest->data<bool>();
    }

    NODE_THREAD.setVaryingMask(itest);

    //
    //	Evaluate then and else portions. Since this is varying, both paths
    //	need to be evaluated.
    //

    if (!uniform || (uniform && uval == true))
    {
        NODE_THREAD.setVaryingMaskSense(true);	// true path
        NODE_ANY_TYPE_ARG(1);
    }

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

    if (uniform = hasUniformValue(itest))
    {
        uval = itest->data<bool>();
    }

    if (!uniform || (uniform && uval == false))
    {
        NODE_THREAD.setVaryingMaskSense(false);	// false path
        NODE_ANY_TYPE_ARG(2);
    }

    //
    //	Restore mask and mask sense
    //

    NODE_THREAD.setVaryingMask(mask);
    NODE_THREAD.setVaryingMaskSense(maskSense);

    if (test != itest) itest->typeDelete();
    if (!test->assigned()) test->typeDelete();
}


NODE_IMPLEMENTATION(VaryingBoolType::conditionalExpr, Pointer)
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

    bool uniform, uval;

    if (uniform = hasUniformValue(itest))
    {
        uval = itest->data<bool>();
    }

    if (!uniform || (uniform && uval ==true))
    {
        NODE_THREAD.setVaryingMaskSense(true);	// true path
        va = reinterpret_cast<VaryingObject*>(NODE_ARG(1, Pointer));
    }

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

    if (uniform = hasUniformValue(itest))
    {
        uval = itest->data<bool>();
    }

    if (!uniform || (uniform && uval == false))
    {
        NODE_THREAD.setVaryingMaskSense(false);	// false path
        vb = reinterpret_cast<VaryingObject*>(NODE_ARG(2, Pointer));
    }

    //
    //  Integrate results
    //

    VaryingObject* vout = 0;
    if (!va->assigned()) vout = va;
    if (!vb->assigned()) vout = vb;

    if (!vout) 
    {
	vout = new VaryingObject(va->varyingType(),
				 p->varyingSize(0),
				 p->varyingSize(1),
				 p->varyingSize(2));
    }

    bool* tmask = test->data<bool>();
    bool* out   = vout->data<bool>();
    bool* a     = va->data<bool>();
    bool* b     = vb->data<bool>();

    if (mask)
    {
	bool *ma  = mask->data<bool>();

	for (bool *i = out, *end = i + vout->size();
	     i != end; i++, a++, b++, ma++, tmask++)
	{
	    if (*ma == maskSense)
	    {
                *i = *tmask ? *a : *b;
	    }
	}
    }
    else
    {
	for (bool *i = out, *end = i + vout->size();
	     i != end; 
	     i++, a++, b++, tmask++)
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



} // namespace Mu
