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
#include "QPointType.h"
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
#include <QtWidgets/QtWidgets>
#include <QtSvg/QtSvg>
#include <QtWebKit/QtWebKit>
#include <QtWebKitWidgets/QtWebKitWidgets>
#include <QtNetwork/QtNetwork>

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

QPointType::Instance::Instance(const Class* c) : ClassInstance(c)
{
}

QPointType::QPointType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QPointType::~QPointType()
{
}

static NODE_IMPLEMENTATION(__allocate, Pointer)
{
    QPointType::Instance* i = new QPointType::Instance((Class*)NODE_THIS.type());
    QPointType::registerFinalizer(i);
    NODE_RETURN(i);
}

void 
QPointType::registerFinalizer (void* o)
{
    GC_register_finalizer(o, QPointType::finalizer, 0, 0, 0);
}

void 
QPointType::finalizer (void* obj, void* data)
{
    QPointType::Instance* i = reinterpret_cast<QPointType::Instance*>(obj);
    delete i;
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

Pointer qt_QPoint_QPoint_QPoint_QPoint(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    setqtype<QPointType>(param_this,QPoint());
    return param_this;
}

Pointer qt_QPoint_QPoint_QPoint_QPoint_int_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_xpos, int param_ypos)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    int arg1 = (int)(param_xpos);
    int arg2 = (int)(param_ypos);
    setqtype<QPointType>(param_this,QPoint(arg1, arg2));
    return param_this;
}

bool qt_QPoint_isNull_bool_QPoint(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    return arg0.isNull();
}

int qt_QPoint_manhattanLength_int_QPoint(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    return arg0.manhattanLength();
}

void qt_QPoint_setX_void_QPoint_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_x)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    int arg1 = (int)(param_x);
    arg0.setX(arg1);
    setqtype<QPointType>(param_this,arg0);
}

void qt_QPoint_setY_void_QPoint_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_y)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    int arg1 = (int)(param_y);
    arg0.setY(arg1);
    setqtype<QPointType>(param_this,arg0);
}

int qt_QPoint_x_int_QPoint(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    return arg0.x();
}

int qt_QPoint_y_int_QPoint(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    return arg0.y();
}

Pointer qt_QPoint_operatorStar_EQ__QPoint_QPoint_double(Mu::Thread& NODE_THREAD, Pointer param_this, double param_factor)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    double arg1 = (double)(param_factor);
    return makeqtype<QPointType>(c,arg0.operator*=(arg1),"qt.QPoint");
}

Pointer qt_QPoint_operatorStar_EQ__QPoint_QPoint_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_factor)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    int arg1 = (int)(param_factor);
    return makeqtype<QPointType>(c,arg0.operator*=(arg1),"qt.QPoint");
}

Pointer qt_QPoint_operatorPlus_EQ__QPoint_QPoint_QPoint(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_point)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    const QPoint  arg1 = getqtype<QPointType>(param_point);
    return makeqtype<QPointType>(c,arg0.operator+=(arg1),"qt.QPoint");
}

Pointer qt_QPoint_operatorMinus_EQ__QPoint_QPoint_QPoint(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_point)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    const QPoint  arg1 = getqtype<QPointType>(param_point);
    return makeqtype<QPointType>(c,arg0.operator-=(arg1),"qt.QPoint");
}

Pointer qt_QPoint_operatorSlash_EQ__QPoint_QPoint_double(Mu::Thread& NODE_THREAD, Pointer param_this, double param_divisor)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QPoint arg0 = getqtype<QPointType>(param_this);
    qreal arg1 = (double)(param_divisor);
    return makeqtype<QPointType>(c,arg0.operator/=(arg1),"qt.QPoint");
}


static NODE_IMPLEMENTATION(_n_QPoint0, Pointer)
{
    NODE_RETURN(qt_QPoint_QPoint_QPoint_QPoint(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QPoint1, Pointer)
{
    NODE_RETURN(qt_QPoint_QPoint_QPoint_QPoint_int_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, int)));
}

static NODE_IMPLEMENTATION(_n_isNull0, bool)
{
    NODE_RETURN(qt_QPoint_isNull_bool_QPoint(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_manhattanLength0, int)
{
    NODE_RETURN(qt_QPoint_manhattanLength_int_QPoint(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_setX0, void)
{
    qt_QPoint_setX_void_QPoint_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int));
}

static NODE_IMPLEMENTATION(_n_setY0, void)
{
    qt_QPoint_setY_void_QPoint_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int));
}

static NODE_IMPLEMENTATION(_n_x0, int)
{
    NODE_RETURN(qt_QPoint_x_int_QPoint(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_y0, int)
{
    NODE_RETURN(qt_QPoint_y_int_QPoint(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorStar_EQ_1, Pointer)
{
    NODE_RETURN(qt_QPoint_operatorStar_EQ__QPoint_QPoint_double(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, double)));
}

static NODE_IMPLEMENTATION(_n_operatorStar_EQ_2, Pointer)
{
    NODE_RETURN(qt_QPoint_operatorStar_EQ__QPoint_QPoint_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int)));
}

static NODE_IMPLEMENTATION(_n_operatorPlus_EQ_0, Pointer)
{
    NODE_RETURN(qt_QPoint_operatorPlus_EQ__QPoint_QPoint_QPoint(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorMinus_EQ_0, Pointer)
{
    NODE_RETURN(qt_QPoint_operatorMinus_EQ__QPoint_QPoint_QPoint(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorSlash_EQ_0, Pointer)
{
    NODE_RETURN(qt_QPoint_operatorSlash_EQ__QPoint_QPoint_double(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, double)));
}



void
QPointType::load()
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
    new Function(c, "QPoint", _n_QPoint0, None, Compiled, qt_QPoint_QPoint_QPoint_QPoint, Return, "qt.QPoint", Parameters, new Param(c, "this", "qt.QPoint"), End),
    new Function(c, "QPoint", _n_QPoint1, None, Compiled, qt_QPoint_QPoint_QPoint_QPoint_int_int, Return, "qt.QPoint", Parameters, new Param(c, "this", "qt.QPoint"), new Param(c, "xpos", "int"), new Param(c, "ypos", "int"), End),
    new Function(c, "isNull", _n_isNull0, None, Compiled, qt_QPoint_isNull_bool_QPoint, Return, "bool", Parameters, new Param(c, "this", "qt.QPoint"), End),
    new Function(c, "manhattanLength", _n_manhattanLength0, None, Compiled, qt_QPoint_manhattanLength_int_QPoint, Return, "int", Parameters, new Param(c, "this", "qt.QPoint"), End),
    // MISSING: rx ("int &"; QPoint this)
    // MISSING: ry ("int &"; QPoint this)
    new Function(c, "setX", _n_setX0, None, Compiled, qt_QPoint_setX_void_QPoint_int, Return, "void", Parameters, new Param(c, "this", "qt.QPoint"), new Param(c, "x", "int"), End),
    new Function(c, "setY", _n_setY0, None, Compiled, qt_QPoint_setY_void_QPoint_int, Return, "void", Parameters, new Param(c, "this", "qt.QPoint"), new Param(c, "y", "int"), End),
    new Function(c, "x", _n_x0, None, Compiled, qt_QPoint_x_int_QPoint, Return, "int", Parameters, new Param(c, "this", "qt.QPoint"), End),
    new Function(c, "y", _n_y0, None, Compiled, qt_QPoint_y_int_QPoint, Return, "int", Parameters, new Param(c, "this", "qt.QPoint"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    // MISSING: *= (QPoint; QPoint this, "float" factor)
    new Function(c, "*=", _n_operatorStar_EQ_1, Op, Compiled, qt_QPoint_operatorStar_EQ__QPoint_QPoint_double, Return, "qt.QPoint", Parameters, new Param(c, "this", "qt.QPoint"), new Param(c, "factor", "double"), End),
    new Function(c, "*=", _n_operatorStar_EQ_2, Op, Compiled, qt_QPoint_operatorStar_EQ__QPoint_QPoint_int, Return, "qt.QPoint", Parameters, new Param(c, "this", "qt.QPoint"), new Param(c, "factor", "int"), End),
    new Function(c, "+=", _n_operatorPlus_EQ_0, Op, Compiled, qt_QPoint_operatorPlus_EQ__QPoint_QPoint_QPoint, Return, "qt.QPoint", Parameters, new Param(c, "this", "qt.QPoint"), new Param(c, "point", "qt.QPoint"), End),
    new Function(c, "-=", _n_operatorMinus_EQ_0, Op, Compiled, qt_QPoint_operatorMinus_EQ__QPoint_QPoint_QPoint, Return, "qt.QPoint", Parameters, new Param(c, "this", "qt.QPoint"), new Param(c, "point", "qt.QPoint"), End),
    new Function(c, "/=", _n_operatorSlash_EQ_0, Op, Compiled, qt_QPoint_operatorSlash_EQ__QPoint_QPoint_double, Return, "qt.QPoint", Parameters, new Param(c, "this", "qt.QPoint"), new Param(c, "divisor", "double"), End),
    EndArguments);
scope()->addSymbols(
    EndArguments);

}

} // Mu
