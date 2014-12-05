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
//     * Neither the name of Jim Hourihan nor the names of the
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
#include "qtUtils.h"
#include <Mu/Thread.h>
#include <MuLang/MuLangContext.h>
#include <MuLang/ExceptionType.h>
#include <Mu/ParameterVariable.h>
#include <Mu/Type.h>
#include <iostream>
#include <sstream>
#include <typeinfo>

namespace Mu {
using namespace std;

Pointer
assertNotNil(Thread& thread, const Node& node, Pointer p, size_t n)
{
    if (!p)
    {
        MuLangContext *context = (MuLangContext*)thread.context();
        const Symbol* s = node.symbol();
        const Function* f = dynamic_cast<const Function*>(s);


        ostringstream str;
        str << "Argument " << n;

        if (f && f->hasParameters())
        {
            str << " (" << f->parameter(n)->name() << " of type "
                << f->parameter(n)->storageClass()->fullyQualifiedName()
                << ")";
        }

        str << " in function " << s->fullyQualifiedName()
            << ": unexpected nil argument";

        ExceptionType::Exception *e = 
            new ExceptionType::Exception(context->exceptionType());
        e->string() += str.str().c_str();
        thread.setException(e);
        ProgramException exc(thread);
        exc.message() = str.str().c_str();
        throw exc;
    }

    return p;
}

Class::ClassVector vectorOf2(Class* a, Class *b)
{
    Class::ClassVector array(2);
    array[0] = a;
    array[1] = b;
    return array;
}

bool isMuQtObject(QObject* o)
{
    //
    //  This is a pretty poor way to do this, but it works
    //

    return o ? strstr(typeid(*o).name(), "MuQt") != 0 : false;
}

bool isMuQtLayoutItem(QLayoutItem* o) { return o ? strstr(typeid(*o).name(), "MuQt") != 0 : false; }
bool isMuQtPaintDevice(QPaintDevice* o) { return o ? strstr(typeid(*o).name(), "MuQt") != 0 : false; }

#if 0
static MuQtQObjectFinalizer(void* obj, void* data)
{
    ClassInstance* i = reinterpret_cast<ClassInstance*>(obj);
    Pointer* pp = i->data<Pointer>();
    if (*pp == this) *pp = 0;
}


NODE_IMPLEMENTATION(__allocate_register_gc_qobject, Pointer)
{
    const Class* c = static_cast<const Class*>(NODE_THIS.symbol()->scope());
    ClassInstance* i = ClassInstance::allocate(c);
    GC_register_finalizer(o, MuQtQObjectFinalizer, 0, 0, 0);
}
#endif

}
