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

#include "BarInterface.h"
#include <Mu/BaseFunctions.h>
#include <Mu/Function.h>
#include <Mu/MemberFunction.h>
#include <Mu/Node.h>
#include <Mu/Process.h>
#include <Mu/ReferenceType.h>
#include <Mu/Thread.h>
#include <MuLang/StringType.h>

namespace Mu {

using namespace std;

BarInterface::BarInterface(Context* c) : Interface(c, "bar_interface")
{
}

BarInterface::~BarInterface()
{
}

void
BarInterface::load()
{
    Function::ArgKeyword Return   = Function::Return;
    Function::ArgKeyword Args     = Function::Args;
    Function::ArgKeyword Optional = Function::Optional;
    Function::ArgKeyword End      = Function::End;

    Function::Attributes None   = Function::None;
    Function::Attributes CommOp = Function::Mapped |
				  Function::Commutative |
				  Function::Operator |
				  Function::NoSideEffects;
    Function::Attributes Op     = Function::Mapped |
				  Function::Operator |
				  Function::NoSideEffects;
    Function::Attributes Mapped = Function::Mapped | Function::NoSideEffects;
    Function::Attributes Cast   = Mapped | Function::Cast;
    Function::Attributes Lossy  = Cast | Function::Lossy;
    Function::Attributes AsOp   = Function::MemberOperator | Function::Operator;

    Symbol *s = scope();
    Context* c = context();

    const char* tn = "test.bar_interface";
    const char* rn = "test.bar_interface&";

    s->addSymbols(new ReferenceType(c, "bar_interface&", this), 
                  
                  new Function(c, "bar_interface", BaseFunctions::dereference, 
                               Cast,
                               Return, tn,
                               Args, rn, End),

                  EndArguments);

    addSymbols( new MemberFunction(c, "bar", BarInterface::bar, None,
                                   Return, "string", 
                                   Args, tn,
                                   End),

                new MemberFunction(c, "foo", BarInterface::foo, None,
                                   Return, "string",
                                   Args, tn,
                                   End),

                EndArguments);

    globalScope()->addSymbols(

		   new Function(c, "=", BaseFunctions::assign, AsOp,
				Return, rn, 
				Args, rn, tn, End),

                   EndArguments );

}

NODE_IMPLEMENTATION(BarInterface::bar, Pointer)
{
    ClassInstance *i = NODE_ARG_OBJECT(0, ClassInstance);
    Process *p = NODE_THREAD.process();
    const StringType *c = static_cast<const StringType*>(NODE_THIS.type());
    NODE_RETURN(c->allocate("bar_interface.bar (default implementation)"));
}


NODE_IMPLEMENTATION(BarInterface::foo, Pointer)
{
    ClassInstance *i = NODE_ARG_OBJECT(0, ClassInstance);
    Process *p = NODE_THREAD.process();
    const StringType *c = static_cast<const StringType*>(NODE_THIS.type());
    NODE_RETURN(c->allocate("bar_interface.foo (default implementation)"));
}



} // Mu
