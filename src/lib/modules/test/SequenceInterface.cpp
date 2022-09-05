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

#include "SequenceInterface.h"
#include <Mu/BaseFunctions.h>
#include <Mu/Function.h>
#include <Mu/MemberFunction.h>
#include <Mu/ReferenceType.h>

namespace Mu {

using namespace std;

SequenceInterface::SequenceInterface(Context* c) : Interface(c, "sequence")
{
}

SequenceInterface::~SequenceInterface()
{
}

void
SequenceInterface::load()
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

    const char* tn = "test.sequence";
    const char* rn = "test.sequence&";

    s->addSymbols(new ReferenceType(c, "sequence&", this), 
                  
                  new Function(c, "sequence", BaseFunctions::dereference, Cast,
                               Return, tn,
                               Args, rn, End),

                  EndArguments);

    addSymbols( new MemberFunction(c, "clear", NodeFunc(0), None,
                                   Return, "void", 
                                   Args, tn,
                                   End),

                new MemberFunction(c, "push_back", NodeFunc(0), None,
                                   Return, "int", 
                                   Args, tn, "int",
                                   End),

                new MemberFunction(c, "pop_back", NodeFunc(0), None,
                                   Return, "int", 
                                   Args, tn,
                                   End),

                EndArguments);

    globalScope()->addSymbols(

		   new Function(c, "=", BaseFunctions::assign, AsOp,
				Return, rn, 
				Args, rn, tn, End),

                   EndArguments );

}



} // Mu
