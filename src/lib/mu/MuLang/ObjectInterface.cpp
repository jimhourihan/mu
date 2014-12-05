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

#include "ObjectInterface.h"
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

ObjectInterface::ObjectInterface(Context* c) : Interface(c, "object")
{
}

ObjectInterface::~ObjectInterface()
{
}

void
ObjectInterface::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    Symbol *s = scope();
    Context* c = context();

    const char* tn = "object";
    const char* rn = "object&";

    s->addSymbols(new ReferenceType(c, "object&", this), 
                  
                  new Function(c, "object", BaseFunctions::dereference, 
                               Cast,
                               Return, tn,
                               Args, rn, End),

                  EndArguments);

    addSymbols( new MemberFunction(c, "identity", ObjectInterface::identity, None,
                                   Return, tn,
                                   Args, tn,
                                   End),

                EndArguments);

    globalScope()->addSymbols(

		   new Function(c, "=", BaseFunctions::assign, AsOp,
				Return, rn, 
				Args, rn, tn, End),

#if 0
                   new Function(c, "eq", BaseFunctions::eq, CommOp,
                                Return, "bool",
                                Args, tn, tn, End),
#endif

                   EndArguments );

}


NODE_IMPLEMENTATION(ObjectInterface::identity, Pointer)
{
    NODE_RETURN((Pointer)NODE_ARG_OBJECT(0, Object));
}

} // Mu
