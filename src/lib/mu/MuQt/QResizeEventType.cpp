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
//     * Neither the name of the software nor the names of its
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
#include "QResizeEventType.h"
#include <QtGui/QtGui>
#include <QtSvg/QtSvg>
#include <QtWebKit/QtWebKit>
#include <QtNetwork/QtNetwork>
#include "QWidgetType.h"
#include "QActionType.h"
#include "QIconType.h"
#include <Mu/BaseFunctions.h>
#include <Mu/Alias.h>
#include <Mu/SymbolicConstant.h>
#include <Mu/Thread.h>
#include <Mu/ClassInstance.h>
#include <Mu/Function.h>
#include <Mu/MemberFunction.h>
#include <Mu/MemberVariable.h>
#include <Mu/Node.h>
#include <Mu/Exception.h>
#include <Mu/ParameterVariable.h>
#include <Mu/ReferenceType.h>
#include <Mu/Value.h>
#include <MuLang/MuLangContext.h>
#include <MuLang/StringType.h>
#include "QSizeType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

QResizeEventType::QResizeEventType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QResizeEventType::~QResizeEventType()
{
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

Pointer qt_QResizeEvent_QResizeEvent_QResizeEvent_QResizeEvent_QSize_QSize(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_size, Pointer param_oldSize)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QSize  arg1 = getqtype<QSizeType>(param_size);
    const QSize  arg2 = getqtype<QSizeType>(param_oldSize);
    setqpointer<QResizeEventType>(param_this,new QResizeEvent(arg1, arg2));
    return param_this;
}

Pointer qt_QResizeEvent_oldSize_QSize_QResizeEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QResizeEvent * arg0 = getqpointer<QResizeEventType>(param_this);
    return makeqtype<QSizeType>(c,arg0->oldSize(),"qt.QSize");
}

Pointer qt_QResizeEvent_size_QSize_QResizeEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QResizeEvent * arg0 = getqpointer<QResizeEventType>(param_this);
    return makeqtype<QSizeType>(c,arg0->size(),"qt.QSize");
}


static NODE_IMPLEMENTATION(_n_QResizeEvent0, Pointer)
{
    NODE_RETURN(qt_QResizeEvent_QResizeEvent_QResizeEvent_QResizeEvent_QSize_QSize(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_oldSize0, Pointer)
{
    NODE_RETURN(qt_QResizeEvent_oldSize_QSize_QResizeEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_size0, Pointer)
{
    NODE_RETURN(qt_QResizeEvent_size_QSize_QResizeEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}



void
QResizeEventType::load()
{
    USING_MU_FUNCTION_SYMBOLS;
    MuLangContext* c = static_cast<MuLangContext*>(context());
    Module* global = globalModule();
    
    const string typeName        = name();
    const string refTypeName     = typeName + "&";
    const string fullTypeName    = fullyQualifiedName();
    const string fullRefTypeName = fullTypeName + "&";
    const char*  tn              = typeName.c_str();
    const char*  ftn             = fullTypeName.c_str();
    const char*  rtn             = refTypeName.c_str();
    const char*  frtn            = fullRefTypeName.c_str();

    scope()->addSymbols(new ReferenceType(c, rtn, this),

                        new Function(c, tn, BaseFunctions::dereference, Cast,
                                     Return, ftn,
                                     Args, frtn, End),

                        EndArguments);
    
    addSymbols(new Function(c, "__allocate", BaseFunctions::classAllocate, None,
                            Return, ftn,
                            End),

               new MemberVariable(c, "native", "qt.NativeObject"),

               EndArguments );


addSymbols(
    EndArguments);

addSymbols(
    // enums
    // member functions
    new Function(c, "QResizeEvent", _n_QResizeEvent0, None, Compiled, qt_QResizeEvent_QResizeEvent_QResizeEvent_QResizeEvent_QSize_QSize, Return, "qt.QResizeEvent", Parameters, new Param(c, "this", "qt.QResizeEvent"), new Param(c, "size", "qt.QSize"), new Param(c, "oldSize", "qt.QSize"), End),
    new Function(c, "oldSize", _n_oldSize0, None, Compiled, qt_QResizeEvent_oldSize_QSize_QResizeEvent, Return, "qt.QSize", Parameters, new Param(c, "this", "qt.QResizeEvent"), End),
    new Function(c, "size", _n_size0, None, Compiled, qt_QResizeEvent_size_QSize_QResizeEvent, Return, "qt.QSize", Parameters, new Param(c, "this", "qt.QResizeEvent"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    EndArguments);
scope()->addSymbols(
    EndArguments);

}

} // Mu
