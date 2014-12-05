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

#include "AClassType.h"
#include <Mu/BaseFunctions.h>
#include <Mu/Function.h>
#include <Mu/MemberFunction.h>
#include <Mu/MemberVariable.h>
#include <Mu/Module.h>
#include <Mu/ParameterVariable.h>
#include <Mu/ReferenceType.h>
#include <Mu/Thread.h>
#include <Mu/Vector.h>
#include <MuLang/DynamicArrayType.h>
#include <MuLang/DynamicArray.h>
#include <MuLang/ExceptionType.h>
#include <MuLang/MuLangContext.h>
#include <MuLang/StringType.h>
#include <ctype.h>
#include <iostream>
#include <sstream>

namespace Mu {
using namespace std;
using namespace Mu;

//----------------------------------------------------------------------


AClassType::AClassType(Context* c, Class *super) : Class(c, "a_class", super)
{
}

AClassType::~AClassType() {}


void
AClassType::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    Symbol *s = scope();
    MuLangContext* context = (MuLangContext*)globalModule()->context();
    Context* c = context;

    String tname = s->name();
    tname += ".";
    tname += "a_class";

    String rname = tname + "&";

    const char* tn = tname.c_str();
    const char* rn = rname.c_str();
		  
    s->addSymbols( new ReferenceType(c, "a_class&", this), 

		   new Function(c, "a_class", AClassType::construct, None,
				Return, tn, 
                                Args, "string",
                                End),

		   new Function(c, "a_class", BaseFunctions::dereference, Cast,
				Return, tn,
				Args, rn, End),

		   EndArguments);

    globalScope()->addSymbols(

		   new Function(c, "print", AClassType::print, None,
				Return, "void", 
				Args, tn, End),

		   new Function(c, "=", BaseFunctions::assign, AsOp,
				Return, rn, 
				Args, rn, tn, End),

                   EndArguments);

    typedef ParameterVariable Param;

    addSymbols( new MemberVariable(c, "value", "int"),

                new MemberFunction(c, "foo", AClassType::foo, None,
                                   Return, "string",
                                   Args, tn,
                                   End),

                new MemberFunction(c, "bar", AClassType::bar, None,
                                   Return, "string",
                                   Args, tn,
                                   End),

		EndArguments );

}

NODE_IMPLEMENTATION(AClassType::construct, Pointer)
{
    StringType::String* name = NODE_ARG_OBJECT(0, StringType::String);
    if (!name) throw NilArgumentException();

    Process *p = NODE_THREAD.process();
    const Class *c = static_cast<const AClassType*>(NODE_THIS.type());
    ClassInstance *o = ClassInstance::allocate(c);

    Layout *x = reinterpret_cast<Layout*>(o->structure());
    x->name = name;

    NODE_RETURN(Pointer(o));
}

NODE_IMPLEMENTATION(AClassType::print, void)
{
    ClassInstance *i = NODE_ARG_OBJECT(0, ClassInstance);
    i->type()->outputValue(cout, Value(i));
}

NODE_IMPLEMENTATION(AClassType::foo, Pointer)
{
    ClassInstance *i = NODE_ARG_OBJECT(0, ClassInstance);
    Layout *x = reinterpret_cast<Layout*>(i->structure());
    Process *p = NODE_THREAD.process();
    MuLangContext* c = static_cast<MuLangContext*>(p->context());

    ostringstream str;

    if (x->name)
    {
        str << x->name->c_str();
        str << "->";
    }

    str << "a_class.foo";
    NODE_RETURN(c->stringType()->allocate(str));
}

NODE_IMPLEMENTATION(AClassType::bar, Pointer)
{
    ClassInstance *i = NODE_ARG_OBJECT(0, ClassInstance);
    Layout *x = reinterpret_cast<Layout*>(i->structure());
    Process *p = NODE_THREAD.process();
    MuLangContext* c = static_cast<MuLangContext*>(p->context());

    ostringstream str;

    if (x->name)
    {
        str << x->name->c_str();
        str << "->";
    }

    str << "a_class.bar";
    NODE_RETURN(c->stringType()->allocate(str));
}


} // namespace Mu

