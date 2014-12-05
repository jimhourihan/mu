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

#include <MuLang/MuLangContext.h>
#include <MuVarying/VaryingModule.h>
#include <MuVarying/VaryingTypeModifier.h>
#include <MuVarying/VaryingMath.h>

namespace Mu {
using namespace std;

VaryingModule::VaryingModule(Context* c, const char *name)
    : Module(c, name) {}

Module*
VaryingModule::init(const char *name, Context *context)
{
    Module *m = new VaryingModule(context, name);
    MuLangContext *c = static_cast<MuLangContext*>(context);
    Symbol *s = c->globalScope();

    //
    //	The varying type modifier. Add it at the root scope.
    //

    TypeModifier* varying = new VaryingTypeModifier(context);
    s->addSymbol( varying );

    //
    //	Instantiate the bool and float type (Do I really need to do this?)
    //

    varying->transform(c->boolType(), c);
    varying->transform(c->floatType(), c);
    varying->transform(c->vec2fType(), c);
    varying->transform(c->vec3fType(), c);
    varying->transform(c->vec4fType(), c);

    //
    //	Add stuff the "varying" module. These functions are almost
    //	inaccessable. The only way to get to the "varying" module is
    //	to use the root namespace alias "__root" like this:
    //
    //	    __root.varying.foo();
    //
    //	So you could use aliasing to make it easy:
    //
    //	    varying_module = __root.varying;
    //	    varying_module.foo();
    //
    //	    -or-
    //
    //	    use __root.varying;
    //

    c->globalScope()->addSymbol(m);

    Name mathModule = c->lookupName("math");
    Module *math = c->globalScope()->findSymbolOfType<Module>(mathModule);

    Name mathUtilModule = c->lookupName("math_util");
    Module *mathUtil = c->globalScope()->findSymbolOfType<Module>(mathUtilModule);

    if (math && mathUtil)
    {
	VMath::declare(math, mathUtil);
    }

    return m;
}


} // namespace Mu
