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

#include "OStreamType.h"
#include <Mu/Function.h>
#include <Mu/BaseFunctions.h>
#include <Mu/MemberFunction.h>
#include <Mu/Module.h>
#include <Mu/ReferenceType.h>
#include <Mu/Thread.h>
#include <Mu/Vector.h>
#include <MuLang/DynamicArrayType.h>
#include <MuLang/DynamicArray.h>
#include <MuLang/ExceptionType.h>
#include <MuLang/StringType.h>
#include <MuLang/MuLangContext.h>
#include <ctype.h>
#include <iostream>
#include <sstream>

namespace Mu {
using namespace std;
using namespace Mu;

OStreamType::OStream::OStream(const Class *c) 
    : StreamType::Stream(c)
{
}


OStreamType::OStream::~OStream()
{
}

//----------------------------------------------------------------------

OStreamType::OStreamType(Context* c, const char* name, Class *super) 
    : StreamType(c, name, super)
{
}

OStreamType::~OStreamType() {}

Object*
OStreamType::newObject() const
{
    return new OStream(this);
}

void
OStreamType::deleteObject(Object *obj) const
{
    delete static_cast<OStreamType::OStream*>(obj);
}


void
OStreamType::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    Symbol *s = scope();
    MuLangContext* context = (MuLangContext*)globalModule()->context();
    Context* c = context;

    context->arrayType(context->byteType(), 1, 0);

    String tname = fullyQualifiedName();
    String rname = tname + "&";

    const char* tn = tname.c_str();
    const char* rn = rname.c_str();
		  
    s->addSymbols( new ReferenceType(c, "ostream&", this), 

		   new Function(c, "ostream", BaseFunctions::dereference, Cast,
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

    addSymbols( new Function(c, "putc", OStreamType::putc, None,
                             Return, tn,
                             Args, tn, "char", End),

                new Function(c, "write", OStreamType::write, None,
                             Return, tn,
                             Args, tn, "byte", End),

                new Function(c, "write", OStreamType::writeBytes, None,
                             Return, tn,
                             Args, tn, "byte[]", End),

                new Function(c, "seekp", OStreamType::seek, None,
                             Return, tn,
                             Args, tn, "int", End),

                new Function(c, "tellp", OStreamType::tell, None,
                             Return, "int",
                             Args, tn, End),

                EndArguments );
}

NODE_IMPLEMENTATION(OStreamType::putc, Pointer)
{
    OStream* stream = NODE_ARG_OBJECT(0, OStream);
    char c = NODE_ARG(1, char);
    stream->_ostream->put(c);
    NODE_RETURN(stream);
}

NODE_IMPLEMENTATION(OStreamType::write, Pointer)
{
    OStream* stream = NODE_ARG_OBJECT(0, OStream);
    char c = NODE_ARG(1, char);
    stream->_ostream->put(c);
    NODE_RETURN(stream);
}

NODE_IMPLEMENTATION(OStreamType::writeBytes, Pointer)
{
    OStream* stream = NODE_ARG_OBJECT(0, OStream);
    DynamicArray* array = NODE_ARG_OBJECT(1, DynamicArray);
    size_t size = array->size(); // we know its bytes
    stream->_ostream->write(array->data<char>(), size);
    NODE_RETURN(stream);
}

NODE_IMPLEMENTATION(OStreamType::seek, Pointer)
{
    OStream* stream = NODE_ARG_OBJECT(0, OStream);
    size_t n = NODE_ARG(1, int);
    stream->_ostream->seekp(n);
    NODE_RETURN(stream);
}

NODE_IMPLEMENTATION(OStreamType::tell, int)
{
    OStream* stream = NODE_ARG_OBJECT(0, OStream);
    NODE_RETURN(stream->_ostream->tellp());
}


} // namespace Mu

