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

#include "IStreamType.h"
#include <Mu/BaseFunctions.h>
#include <Mu/Function.h>
#include <Mu/MemberFunction.h>
#include <Mu/Module.h>
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

IStreamType::IStream::IStream(const Class *c) 
    : StreamType::Stream(c)
{
}


IStreamType::IStream::~IStream()
{
}

//----------------------------------------------------------------------

IStreamType::IStreamType(Context* c, const char* name, Class *super) 
    : StreamType(c, name, super)
{
}

IStreamType::~IStreamType() {}

Object*
IStreamType::newObject() const
{
    return new IStream(this);
}

void
IStreamType::deleteObject(Object *obj) const
{
    delete static_cast<IStreamType::IStream*>(obj);
}


void
IStreamType::load()
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
		  
    s->addSymbols( new ReferenceType(c, "istream&", this), 

		   new Function(c, "istream", BaseFunctions::dereference, Cast,
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

    addSymbols( new Function(c, "getc", IStreamType::sgetc, None,
                             Return, tn,
                             End),

                new Function(c, "gets", IStreamType::gets, None,
                             Return, "string",
                             Args, tn, "string", 
                             End),

                new Function(c, "read", IStreamType::read, None,
                             Return, "byte",
                             Args, tn, End),

                new Function(c, "read", IStreamType::readBytes, None,
                             Return, "int",
                             Args, tn, "byte[]", "int", End),

                new Function(c, "seekg", IStreamType::seek, None,
                             Return, tn,
                             Args, tn, "int", End),

                new Function(c, "seekg", IStreamType::seek2, None,
                             Return, tn,
                             Args, tn, "int", "int", End),

                new Function(c, "tellg", IStreamType::tell, None,
                             Return, "int",
                             Args, tn, End),

                new Function(c, "gcount", IStreamType::count, None,
                             Return, "int",
                             Args, tn, End),

                new Function(c, "putback", IStreamType::putback, None,
                             Return, tn,
                             Args, tn, "int", End),

                new Function(c, "unget", IStreamType::unget, None,
                             Return, tn,
                             Args, tn, End),

                new Function(c, "in_avail", IStreamType::in_avail, None,
                             Return, "int",
                             Args, tn, End),

                EndArguments );
}

NODE_IMPLEMENTATION(IStreamType::sgetc, char)
{
    IStream* stream = NODE_ARG_OBJECT(0, IStream);
    char c;
    stream->_istream->get(c);
    NODE_RETURN(c);
}

NODE_IMPLEMENTATION(IStreamType::gets, Pointer)
{
    Process *p = NODE_THREAD.process();
    MuLangContext* context = static_cast<MuLangContext*>(p->context());
    const Class *stype = static_cast<const StringType*>(NODE_THIS.type());

    IStream* stream         = NODE_ARG_OBJECT(0, IStream);
    const StringType::String* s   = NODE_ARG_OBJECT(1, StringType::String);

    char c;
    const String del = s->c_str();
    istream* is = stream->_istream;

    ostringstream ostr;

    while (!is->eof() && !is->fail())
    {
        is->get(c);

        if (del.find(c) != String::npos) break;
        else ostr << char(c);
    };

    NODE_RETURN(context->stringType()->allocate(ostr));
}

NODE_IMPLEMENTATION(IStreamType::read, char)
{
    IStream* stream = NODE_ARG_OBJECT(0, IStream);
    char c;
    stream->_istream->get(c);
    NODE_RETURN(c);
}

NODE_IMPLEMENTATION(IStreamType::readBytes, int)
{
    IStream* stream = NODE_ARG_OBJECT(0, IStream);
    DynamicArray* array = NODE_ARG_OBJECT(1, DynamicArray);
    size_t n = NODE_ARG(2, int);
    size_t size = array->size();    // we know its bytes
    array->resize(size + n);
    size_t nread = 0;
#if COMPILER == GCC2_95
    stream->_istream->read(array->data<char>() + size, n);
    nread = n;  // bogus return value here when using 2.95!
#else
    nread = stream->_istream->readsome(array->data<char>() + size, n);
#endif
    array->resize(size + nread);
    NODE_RETURN(nread);
}

NODE_IMPLEMENTATION(IStreamType::seek, Pointer)
{
    IStream* stream = NODE_ARG_OBJECT(0, IStream);
    size_t n = NODE_ARG(1, int);
    stream->_istream->seekg(n);
    NODE_RETURN(stream);
}

NODE_IMPLEMENTATION(IStreamType::seek2, Pointer)
{
    IStream* stream = NODE_ARG_OBJECT(0, IStream);
    size_t n = NODE_ARG(1, int);
    size_t dir = NODE_ARG(2, int);
    stream->_istream->seekg(n, ios_base::seekdir(dir));
    NODE_RETURN(stream);
}

NODE_IMPLEMENTATION(IStreamType::tell, int)
{
    IStream* stream = NODE_ARG_OBJECT(0, IStream);
    NODE_RETURN(stream->_istream->tellg());
}

NODE_IMPLEMENTATION(IStreamType::count, int)
{
    IStream* stream = NODE_ARG_OBJECT(0, IStream);
    NODE_RETURN(stream->_istream->gcount());
}

NODE_IMPLEMENTATION(IStreamType::putback, Pointer)
{
    IStream* stream = NODE_ARG_OBJECT(0, IStream);
    char c = NODE_ARG(1, char);
    stream->_istream->putback(c);
    NODE_RETURN(stream);
}

NODE_IMPLEMENTATION(IStreamType::unget, Pointer)
{
    IStream* stream = NODE_ARG_OBJECT(0, IStream);
    stream->_istream->unget();
    NODE_RETURN(stream);
}

NODE_IMPLEMENTATION(IStreamType::in_avail, int)
{
    IStream* stream = NODE_ARG_OBJECT(0, IStream);
    NODE_RETURN(stream->_istream->rdbuf()->in_avail());
}

} // namespace Mu

