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

#include "ISStreamType.h"

#ifndef TWK_STUB_IT_OUT
#include <Mu/Function.h>
#include <Mu/MemberFunction.h>
#include <Mu/Module.h>
#include <Mu/ReferenceType.h>
#include <Mu/BaseFunctions.h>
#include <Mu/Thread.h>
#include <Mu/Vector.h>
#include <MuLang/ExceptionType.h>
#include <MuLang/StringType.h>
#include <MuLang/MuLangContext.h>
#include <ctype.h>
#include <iostream>
#include <sstream>

namespace Mu {
using namespace std;

ISStreamType::ISStream::ISStream(const Class *c) 
    : IStreamType::IStream(c)
{
}

ISStreamType::ISStream::~ISStream()
{
}

//----------------------------------------------------------------------

ISStreamType::ISStreamType(Context* c, const char* name, Class *super) 
    : IStreamType(c, name, super)
{
}

ISStreamType::~ISStreamType() {}

Object*
ISStreamType::newObject() const
{
    return new ISStream(this);
}

void
ISStreamType::deleteObject(Object *obj) const
{
    delete static_cast<ISStreamType::ISStream*>(obj);
}


void
ISStreamType::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    Symbol *s = scope();
    MuLangContext* context = (MuLangContext*)globalModule()->context();
    Context* c = context;

    String tname = fullyQualifiedName();
    String rname = tname + "&";

    const char* tn = tname.c_str();
    const char* rn = rname.c_str();
		  
    s->addSymbols( new ReferenceType(c, "isstream&", this), 

		   new Function(c, "isstream", ISStreamType::construct, None,
				Return, tn,
				Args, "string", End),

		   new Function(c, "isstream", BaseFunctions::dereference, Cast,
				Return, tn,
				Args, rn, End),

		   EndArguments);

    globalScope()->addSymbols(

		   new Function(c, "print", StreamType::print, None,
				Return, "void", 
				Args, tn, End),

		   new Function(c, "=", BaseFunctions::assign, AsOp,
				Return, rn, 
				Args, rn, tn, End),

                   EndArguments);
}

NODE_IMPLEMENTATION(ISStreamType::construct, Pointer)
{
    const StringType::String* str = NODE_ARG_OBJECT(0, StringType::String);
    Process *p = NODE_THREAD.process();
    const Class *c = static_cast<const ISStreamType*>(NODE_THIS.type());
    ISStreamType::ISStream *o = new ISStreamType::ISStream(c);

    //
    //  Make annotation string
    //

    String an = str->utf8().substr(0, 20);
    if (str->size() > 20) an += "...";
    o->setString(an);

    o->_ios = o->_istream = o->_isstream 
        = new std::istringstream(str->c_str());
    NODE_RETURN(Pointer(o));
}

} // namespace Mu

#endif
