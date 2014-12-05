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
#include "QLinearGradientType.h"
#include "QActionType.h"
#include "QWidgetType.h"
#include <Mu/Alias.h>
#include <Mu/BaseFunctions.h>
#include <Mu/ClassInstance.h>
#include <Mu/Exception.h>
#include <Mu/Function.h>
#include <Mu/MemberFunction.h>
#include <Mu/MemberVariable.h>
#include <Mu/Node.h>
#include <Mu/ParameterVariable.h>
#include <Mu/ReferenceType.h>
#include <Mu/SymbolicConstant.h>
#include <Mu/Thread.h>
#include <Mu/Value.h>
#include <MuLang/MuLangContext.h>
#include <MuLang/StringType.h>
#include <QtGui/QtGui>
#include <QtSvg/QtSvg>
#include <QtWebKit/QtWebKit>
#include <QtNetwork/QtNetwork>
#include "QPointFType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

QLinearGradientType::Instance::Instance(const Class* c) : ClassInstance(c)
{
}

QLinearGradientType::QLinearGradientType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QLinearGradientType::~QLinearGradientType()
{
}

static NODE_IMPLEMENTATION(__allocate, Pointer)
{
    QLinearGradientType::Instance* i = new QLinearGradientType::Instance((Class*)NODE_THIS.type());
    QLinearGradientType::registerFinalizer(i);
    NODE_RETURN(i);
}

void 
QLinearGradientType::registerFinalizer (void* o)
{
    GC_register_finalizer(o, QLinearGradientType::finalizer, 0, 0, 0);
}

void 
QLinearGradientType::finalizer (void* obj, void* data)
{
    QLinearGradientType::Instance* i = reinterpret_cast<QLinearGradientType::Instance*>(obj);
    delete i;
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

Pointer qt_QLinearGradient_QLinearGradient_QLinearGradient_QLinearGradient(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    setqtype<QLinearGradientType>(param_this,QLinearGradient());
    return param_this;
}

Pointer qt_QLinearGradient_QLinearGradient_QLinearGradient_QLinearGradient_QPointF_QPointF(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_start, Pointer param_finalStop)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QPointF  arg1 = getqtype<QPointFType>(param_start);
    const QPointF  arg2 = getqtype<QPointFType>(param_finalStop);
    setqtype<QLinearGradientType>(param_this,QLinearGradient(arg1, arg2));
    return param_this;
}

Pointer qt_QLinearGradient_QLinearGradient_QLinearGradient_QLinearGradient_double_double_double_double(Mu::Thread& NODE_THREAD, Pointer param_this, double param_x1, double param_y1, double param_x2, double param_y2)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    qreal arg1 = (double)(param_x1);
    qreal arg2 = (double)(param_y1);
    qreal arg3 = (double)(param_x2);
    qreal arg4 = (double)(param_y2);
    setqtype<QLinearGradientType>(param_this,QLinearGradient(arg1, arg2, arg3, arg4));
    return param_this;
}

Pointer qt_QLinearGradient_finalStop_QPointF_QLinearGradient(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLinearGradient arg0 = getqtype<QLinearGradientType>(param_this);
    return makeqtype<QPointFType>(c,arg0.finalStop(),"qt.QPointF");
}

void qt_QLinearGradient_setFinalStop_void_QLinearGradient_QPointF(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_stop)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLinearGradient arg0 = getqtype<QLinearGradientType>(param_this);
    const QPointF  arg1 = getqtype<QPointFType>(param_stop);
    arg0.setFinalStop(arg1);
    setqtype<QLinearGradientType>(param_this,arg0);
}

void qt_QLinearGradient_setFinalStop_void_QLinearGradient_double_double(Mu::Thread& NODE_THREAD, Pointer param_this, double param_x, double param_y)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLinearGradient arg0 = getqtype<QLinearGradientType>(param_this);
    qreal arg1 = (double)(param_x);
    qreal arg2 = (double)(param_y);
    arg0.setFinalStop(arg1, arg2);
    setqtype<QLinearGradientType>(param_this,arg0);
}

void qt_QLinearGradient_setStart_void_QLinearGradient_QPointF(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_start)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLinearGradient arg0 = getqtype<QLinearGradientType>(param_this);
    const QPointF  arg1 = getqtype<QPointFType>(param_start);
    arg0.setStart(arg1);
    setqtype<QLinearGradientType>(param_this,arg0);
}

void qt_QLinearGradient_setStart_void_QLinearGradient_double_double(Mu::Thread& NODE_THREAD, Pointer param_this, double param_x, double param_y)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLinearGradient arg0 = getqtype<QLinearGradientType>(param_this);
    qreal arg1 = (double)(param_x);
    qreal arg2 = (double)(param_y);
    arg0.setStart(arg1, arg2);
    setqtype<QLinearGradientType>(param_this,arg0);
}

Pointer qt_QLinearGradient_start_QPointF_QLinearGradient(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLinearGradient arg0 = getqtype<QLinearGradientType>(param_this);
    return makeqtype<QPointFType>(c,arg0.start(),"qt.QPointF");
}


static NODE_IMPLEMENTATION(_n_QLinearGradient0, Pointer)
{
    NODE_RETURN(qt_QLinearGradient_QLinearGradient_QLinearGradient_QLinearGradient(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QLinearGradient1, Pointer)
{
    NODE_RETURN(qt_QLinearGradient_QLinearGradient_QLinearGradient_QLinearGradient_QPointF_QPointF(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QLinearGradient2, Pointer)
{
    NODE_RETURN(qt_QLinearGradient_QLinearGradient_QLinearGradient_QLinearGradient_double_double_double_double(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, double), NODE_ARG(2, double), NODE_ARG(3, double), NODE_ARG(4, double)));
}

static NODE_IMPLEMENTATION(_n_finalStop0, Pointer)
{
    NODE_RETURN(qt_QLinearGradient_finalStop_QPointF_QLinearGradient(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_setFinalStop0, void)
{
    qt_QLinearGradient_setFinalStop_void_QLinearGradient_QPointF(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setFinalStop1, void)
{
    qt_QLinearGradient_setFinalStop_void_QLinearGradient_double_double(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, double), NODE_ARG(2, double));
}

static NODE_IMPLEMENTATION(_n_setStart0, void)
{
    qt_QLinearGradient_setStart_void_QLinearGradient_QPointF(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setStart1, void)
{
    qt_QLinearGradient_setStart_void_QLinearGradient_double_double(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, double), NODE_ARG(2, double));
}

static NODE_IMPLEMENTATION(_n_start0, Pointer)
{
    NODE_RETURN(qt_QLinearGradient_start_QPointF_QLinearGradient(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}



void
QLinearGradientType::load()
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
    
    addSymbols(new Function(c, "__allocate", __allocate, None,
                            Return, ftn,
                            End),

               EndArguments );

addSymbols(
    EndArguments);

addSymbols(
    // enums
    // member functions
    new Function(c, "QLinearGradient", _n_QLinearGradient0, None, Compiled, qt_QLinearGradient_QLinearGradient_QLinearGradient_QLinearGradient, Return, "qt.QLinearGradient", Parameters, new Param(c, "this", "qt.QLinearGradient"), End),
    new Function(c, "QLinearGradient", _n_QLinearGradient1, None, Compiled, qt_QLinearGradient_QLinearGradient_QLinearGradient_QLinearGradient_QPointF_QPointF, Return, "qt.QLinearGradient", Parameters, new Param(c, "this", "qt.QLinearGradient"), new Param(c, "start", "qt.QPointF"), new Param(c, "finalStop", "qt.QPointF"), End),
    new Function(c, "QLinearGradient", _n_QLinearGradient2, None, Compiled, qt_QLinearGradient_QLinearGradient_QLinearGradient_QLinearGradient_double_double_double_double, Return, "qt.QLinearGradient", Parameters, new Param(c, "this", "qt.QLinearGradient"), new Param(c, "x1", "double"), new Param(c, "y1", "double"), new Param(c, "x2", "double"), new Param(c, "y2", "double"), End),
    new Function(c, "finalStop", _n_finalStop0, None, Compiled, qt_QLinearGradient_finalStop_QPointF_QLinearGradient, Return, "qt.QPointF", Parameters, new Param(c, "this", "qt.QLinearGradient"), End),
    new Function(c, "setFinalStop", _n_setFinalStop0, None, Compiled, qt_QLinearGradient_setFinalStop_void_QLinearGradient_QPointF, Return, "void", Parameters, new Param(c, "this", "qt.QLinearGradient"), new Param(c, "stop", "qt.QPointF"), End),
    new Function(c, "setFinalStop", _n_setFinalStop1, None, Compiled, qt_QLinearGradient_setFinalStop_void_QLinearGradient_double_double, Return, "void", Parameters, new Param(c, "this", "qt.QLinearGradient"), new Param(c, "x", "double"), new Param(c, "y", "double"), End),
    new Function(c, "setStart", _n_setStart0, None, Compiled, qt_QLinearGradient_setStart_void_QLinearGradient_QPointF, Return, "void", Parameters, new Param(c, "this", "qt.QLinearGradient"), new Param(c, "start", "qt.QPointF"), End),
    new Function(c, "setStart", _n_setStart1, None, Compiled, qt_QLinearGradient_setStart_void_QLinearGradient_double_double, Return, "void", Parameters, new Param(c, "this", "qt.QLinearGradient"), new Param(c, "x", "double"), new Param(c, "y", "double"), End),
    new Function(c, "start", _n_start0, None, Compiled, qt_QLinearGradient_start_QPointF_QLinearGradient, Return, "qt.QPointF", Parameters, new Param(c, "this", "qt.QLinearGradient"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    EndArguments);
scope()->addSymbols(
    EndArguments);

}

} // Mu
