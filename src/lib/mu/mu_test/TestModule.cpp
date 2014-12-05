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

#include "TestModule.h"
#include "SequenceInterface.h"
#include "BaseType.h"
#include "AClassType.h"
#include "BClassType.h"
#include "CClassType.h"
#include "BarInterface.h"
#include <Mu/Function.h>
#include <Mu/Exception.h>
#include <Mu/Process.h>
#include <Mu/Thread.h>
#include <Mu/ParameterVariable.h>
#include <MuLang/StringType.h>
#include <MuLang/MuLangContext.h>
#include <sstream>
#include <iostream>
#include <stdlib.h>

namespace Mu {
using namespace std;

TestModule::TestModule(Context* c, const char *name)
    : Module(c, name)
{
}

TestModule::~TestModule()
{
}

void
TestModule::load()
{
    Function::ArgKeyword Return     = Function::Return;
    Function::ArgKeyword Args       = Function::Args;
    Function::ArgKeyword Optional   = Function::Optional;
    Function::ArgKeyword End        = Function::End;
    Function::ArgKeyword Parameters = Function::Parameters;

    Function::Attributes CommOp     = Function::Mapped |
                                      Function::Commutative |
                                      Function::Operator |
                                      Function::NoSideEffects;
    Function::Attributes Op         = Function::Mapped |
                                      Function::Operator |
                                      Function::NoSideEffects;
    Function::Attributes Mapped     = Function::Mapped |
                                      Function::NoSideEffects;
    Function::Attributes Cast       = Mapped | Function::Cast;
    Function::Attributes Lossy      = Cast | Function::Lossy;
    Function::Attributes AsOp       = Function::MemberOperator |
                                      Function::Operator;

    MuLangContext* context = (MuLangContext*)globalModule()->context();

    typedef ParameterVariable Param;

    Class* base = new BaseType(context);
    Class* a    = new AClassType(context, base);
    Class* b    = new BClassType(context, base);
    Class* c    = new CClassType(context, base);

    addSymbols( new SequenceInterface(context), 
                new BarInterface(context),
                base, 
                a, b, c,

		EndArguments );


}

} // namespace Mu
