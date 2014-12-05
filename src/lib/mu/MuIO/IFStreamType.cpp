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

#include "IFStreamType.h"
#include <Mu/BaseFunctions.h>
#include <Mu/Function.h>
#include <Mu/MemberFunction.h>
#include <Mu/Module.h>
#include <Mu/ReferenceType.h>
#include <Mu/Thread.h>
#include <Mu/Vector.h>
#include <MuLang/ExceptionType.h>
#include <MuLang/MuLangContext.h>
#include <MuLang/StringType.h>
#include <ctype.h>
#include <iostream>
#include <sstream>
/* AJG - TIFF? */
// #include <tiffio.h>

namespace Mu {
using namespace std;

void 
IFStreamType::finalizer (void* obj, void* data)
{
    IFStreamType::IFStream* i = reinterpret_cast<IFStreamType::IFStream*>(obj);

    if (i->_ifstream != &cin)
    {
        delete i->_ifstream;
        i->_ifstream = 0;
    }
}

IFStreamType::IFStream::IFStream(const Class *c) 
    : IStreamType::IStream(c)
{
    GC_register_finalizer(this, IFStreamType::finalizer, 0, 0, 0);
}


IFStreamType::IFStream::~IFStream()
{
}

//----------------------------------------------------------------------

IFStreamType::IFStreamType(Context* c, const char* name, Class *super) 
    : IStreamType(c, name, super)
{
}

IFStreamType::~IFStreamType() {}

Object*
IFStreamType::newObject() const
{
    return new IFStream(this);
}

void
IFStreamType::deleteObject(Object *obj) const
{
    delete static_cast<IFStreamType::IFStream*>(obj);
}


void
IFStreamType::load()
{
    USING_MU_FUNCTION_SYMBOLS;

    Symbol *s = scope();
    Context* c = context();
    MuLangContext* context = (MuLangContext*)globalModule()->context();

    String tname = fullyQualifiedName();
    String rname = tname + "&";

    const char* tn = tname.c_str();
    const char* rn = rname.c_str();

    s->addSymbols( new ReferenceType(c, "ifstream&", this), 

		   new Function(c, "ifstream", IFStreamType::construct0, None,
				Return, tn, End),

		   new Function(c, "ifstream", IFStreamType::construct, None,
				Return, tn,
				Args, "string",
                                End),

		   new Function(c, "ifstream", IFStreamType::construct1, None,
				Return, tn,
				Args, "string", "int",
                                End),

		   new Function(c, "ifstream", BaseFunctions::dereference, Cast,
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

    addSymbols( new Function(c, "close", IFStreamType::close, None,
                             Return, "void",
                             Args, tn, End),

                new Function(c, "open", IFStreamType::open, None,
                             Return, "void",
                             Args, tn, "string", "int", End),

                new Function(c, "is_open", IFStreamType::is_open, None,
                             Return, "bool",
                             Args, tn, End),


		EndArguments );

}

NODE_IMPLEMENTATION(IFStreamType::construct0, Pointer)
{
    Process *p = NODE_THREAD.process();
    const Class *c = static_cast<const IFStreamType*>(NODE_THIS.type());
    IFStreamType::IFStream *o = new IFStreamType::IFStream(c);
    o->_ios = o->_istream = o->_ifstream = new std::ifstream();
    NODE_RETURN(Pointer(o));
}

NODE_IMPLEMENTATION(IFStreamType::construct, Pointer)
{
    const StringType::String* file = NODE_ARG_OBJECT(0, StringType::String);

    Process *p = NODE_THREAD.process();
    const Class *c = static_cast<const IFStreamType*>(NODE_THIS.type());
    IFStreamType::IFStream *o = new IFStreamType::IFStream(c);
    o->setString(file->c_str());
    o->_ios = o->_istream = o->_ifstream = new std::ifstream(file->c_str());
    NODE_RETURN(Pointer(o));
}

NODE_IMPLEMENTATION(IFStreamType::construct1, Pointer)
{
    const StringType::String* file = NODE_ARG_OBJECT(0, StringType::String);
    ios_base::openmode mode = (ios_base::openmode)NODE_ARG(1, int);

    Process *p = NODE_THREAD.process();
    const Class *c = static_cast<const IFStreamType*>(NODE_THIS.type());
    IFStreamType::IFStream *o = new IFStreamType::IFStream(c);
    o->setString(file->c_str());
    o->_ios = o->_istream = o->_ifstream = new std::ifstream(file->c_str(), mode);
    NODE_RETURN(Pointer(o));
}

NODE_IMPLEMENTATION(IFStreamType::close, void)
{
    IFStreamType::IFStream* stream =
        NODE_ARG_OBJECT(0, IFStreamType::IFStream);
    stream->_ifstream->close();

    if (stream->_ifstream != &cin)
    {
        delete stream->_ifstream;
        stream->_ifstream = 0;
    }
}

NODE_IMPLEMENTATION(IFStreamType::is_open, bool)
{
    IFStreamType::IFStream* stream =
        NODE_ARG_OBJECT(0, IFStreamType::IFStream);
    NODE_RETURN( stream->_ifstream->is_open() );
}

NODE_IMPLEMENTATION(IFStreamType::open, void)
{
    IFStreamType::IFStream* stream =
        NODE_ARG_OBJECT(0, IFStreamType::IFStream);
    const StringType::String* file = NODE_ARG_OBJECT(1, StringType::String);
    int flags = NODE_ARG(2, int);
    stream->_ifstream->open(file->c_str(), ios::openmode(flags));
}


} // namespace Mu

