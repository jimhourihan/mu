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
#include "QGradientType.h"
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
#include "QColorType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

QGradientType::Instance::Instance(const Class* c) : ClassInstance(c)
{
}

QGradientType::QGradientType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QGradientType::~QGradientType()
{
}

static NODE_IMPLEMENTATION(__allocate, Pointer)
{
    QGradientType::Instance* i = new QGradientType::Instance((Class*)NODE_THIS.type());
    QGradientType::registerFinalizer(i);
    NODE_RETURN(i);
}

void 
QGradientType::registerFinalizer (void* o)
{
    GC_register_finalizer(o, QGradientType::finalizer, 0, 0, 0);
}

void 
QGradientType::finalizer (void* obj, void* data)
{
    QGradientType::Instance* i = reinterpret_cast<QGradientType::Instance*>(obj);
    delete i;
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

int qt_QGradient_coordinateMode_int_QGradient(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QGradient& arg0 = getqtype<QGradientType>(param_this);
    return int(arg0.coordinateMode());
}

void qt_QGradient_setColorAt_void_QGradient_double_QColor(Mu::Thread& NODE_THREAD, Pointer param_this, double param_position, Pointer param_color)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QGradient& arg0 = getqtype<QGradientType>(param_this);
    qreal arg1 = (double)(param_position);
    const QColor  arg2 = getqtype<QColorType>(param_color);
    arg0.setColorAt(arg1, arg2);
    setqtype<QGradientType>(param_this,arg0);
}

void qt_QGradient_setCoordinateMode_void_QGradient_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_mode)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QGradient& arg0 = getqtype<QGradientType>(param_this);
    QGradient::CoordinateMode arg1 = (QGradient::CoordinateMode)(param_mode);
    arg0.setCoordinateMode(arg1);
    setqtype<QGradientType>(param_this,arg0);
}

void qt_QGradient_setSpread_void_QGradient_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_method)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QGradient& arg0 = getqtype<QGradientType>(param_this);
    QGradient::Spread arg1 = (QGradient::Spread)(param_method);
    arg0.setSpread(arg1);
    setqtype<QGradientType>(param_this,arg0);
}

int qt_QGradient_spread_int_QGradient(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QGradient& arg0 = getqtype<QGradientType>(param_this);
    return int(arg0.spread());
}

int qt_QGradient_type_int_QGradient(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QGradient& arg0 = getqtype<QGradientType>(param_this);
    return int(arg0.type());
}

bool qt_QGradient_operatorBang_EQ__bool_QGradient_QGradient(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_gradient)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QGradient& arg0 = getqtype<QGradientType>(param_this);
    const QGradient  arg1 = getqtype<QGradientType>(param_gradient);
    return arg0.operator!=(arg1);
}

bool qt_QGradient_operatorEQ_EQ__bool_QGradient_QGradient(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_gradient)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QGradient& arg0 = getqtype<QGradientType>(param_this);
    const QGradient  arg1 = getqtype<QGradientType>(param_gradient);
    return arg0.operator==(arg1);
}


static NODE_IMPLEMENTATION(_n_coordinateMode0, int)
{
    NODE_RETURN(qt_QGradient_coordinateMode_int_QGradient(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_setColorAt0, void)
{
    qt_QGradient_setColorAt_void_QGradient_double_QColor(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, double), NODE_ARG(2, Pointer));
}

static NODE_IMPLEMENTATION(_n_setCoordinateMode0, void)
{
    qt_QGradient_setCoordinateMode_void_QGradient_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int));
}

static NODE_IMPLEMENTATION(_n_setSpread0, void)
{
    qt_QGradient_setSpread_void_QGradient_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int));
}

static NODE_IMPLEMENTATION(_n_spread0, int)
{
    NODE_RETURN(qt_QGradient_spread_int_QGradient(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_type0, int)
{
    NODE_RETURN(qt_QGradient_type_int_QGradient(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorBang_EQ_0, bool)
{
    NODE_RETURN(qt_QGradient_operatorBang_EQ__bool_QGradient_QGradient(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorEQ_EQ_0, bool)
{
    NODE_RETURN(qt_QGradient_operatorEQ_EQ__bool_QGradient_QGradient(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}


static NODE_IMPLEMENTATION(setStops, void)
{
    
}

static NODE_IMPLEMENTATION(stops, Pointer)
{
    NODE_RETURN(Pointer(0));
}

void
QGradientType::load()
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
    new Alias(c, "CoordinateMode", "int"),
      new SymbolicConstant(c, "LogicalMode", "int", Value(int(QGradient::LogicalMode))),
      new SymbolicConstant(c, "StretchToDeviceMode", "int", Value(int(QGradient::StretchToDeviceMode))),
      new SymbolicConstant(c, "ObjectBoundingMode", "int", Value(int(QGradient::ObjectBoundingMode))),
    new Alias(c, "Spread", "int"),
      new SymbolicConstant(c, "PadSpread", "int", Value(int(QGradient::PadSpread))),
      new SymbolicConstant(c, "RepeatSpread", "int", Value(int(QGradient::RepeatSpread))),
      new SymbolicConstant(c, "ReflectSpread", "int", Value(int(QGradient::ReflectSpread))),
    new Alias(c, "Type", "int"),
      new SymbolicConstant(c, "LinearGradient", "int", Value(int(QGradient::LinearGradient))),
      new SymbolicConstant(c, "RadialGradient", "int", Value(int(QGradient::RadialGradient))),
      new SymbolicConstant(c, "ConicalGradient", "int", Value(int(QGradient::ConicalGradient))),
      new SymbolicConstant(c, "NoGradient", "int", Value(int(QGradient::NoGradient))),
    EndArguments);

addSymbols(
    // enums
    // member functions
    new Function(c, "coordinateMode", _n_coordinateMode0, None, Compiled, qt_QGradient_coordinateMode_int_QGradient, Return, "int", Parameters, new Param(c, "this", "qt.QGradient"), End),
    new Function(c, "setColorAt", _n_setColorAt0, None, Compiled, qt_QGradient_setColorAt_void_QGradient_double_QColor, Return, "void", Parameters, new Param(c, "this", "qt.QGradient"), new Param(c, "position", "double"), new Param(c, "color", "qt.QColor"), End),
    new Function(c, "setCoordinateMode", _n_setCoordinateMode0, None, Compiled, qt_QGradient_setCoordinateMode_void_QGradient_int, Return, "void", Parameters, new Param(c, "this", "qt.QGradient"), new Param(c, "mode", "int"), End),
    new Function(c, "setSpread", _n_setSpread0, None, Compiled, qt_QGradient_setSpread_void_QGradient_int, Return, "void", Parameters, new Param(c, "this", "qt.QGradient"), new Param(c, "method", "int"), End),
    // MISSING: setStops (void; QGradient this, "const QGradientStops &" stopPoints)
    new Function(c, "spread", _n_spread0, None, Compiled, qt_QGradient_spread_int_QGradient, Return, "int", Parameters, new Param(c, "this", "qt.QGradient"), End),
    // MISSING: stops ("QGradientStops"; QGradient this)
    new Function(c, "type", _n_type0, None, Compiled, qt_QGradient_type_int_QGradient, Return, "int", Parameters, new Param(c, "this", "qt.QGradient"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    new Function(c, "!=", _n_operatorBang_EQ_0, Op, Compiled, qt_QGradient_operatorBang_EQ__bool_QGradient_QGradient, Return, "bool", Parameters, new Param(c, "this", "qt.QGradient"), new Param(c, "gradient", "qt.QGradient"), End),
    new Function(c, "==", _n_operatorEQ_EQ_0, Op, Compiled, qt_QGradient_operatorEQ_EQ__bool_QGradient_QGradient, Return, "bool", Parameters, new Param(c, "this", "qt.QGradient"), new Param(c, "gradient", "qt.QGradient"), End),
    EndArguments);
scope()->addSymbols(
    EndArguments);



// MISSING: setStops (void; QGradient this, "const QGradientStops &" stopPoints)
// MISSING: stops ("QGradientStops"; QGradient this)
//
//  the tuple and array are created in QColorSymbols.cpp

addSymbol( new Function(c, "setStops", setStops, None,
                        //Compiled, QGradient_setStops_,
                        Return, "int",
                        Parameters,
                        new Param(c, "this", "qt.QGradient"),
                        new Param(c, "this", "(double,qt.QColor)[]"),
                        End) );


addSymbol( new Function(c, "stops", stops, None,
                        //Compiled, QGradient_stops_,
                        Return, "(double,qt.QColor)[]",
                        Parameters,
                        new Param(c, "this", "qt.QGradient"),
                        End) );
}

} // Mu
