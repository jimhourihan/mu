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
#include "QMouseEventType.h"
#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include <QtSvg/QtSvg>
#include <QtWebKit/QtWebKit>
#include <QtWebKitWidgets/QtWebKitWidgets>
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
#include "QPointFType.h"
#include "QPointType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

QMouseEventType::QMouseEventType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QMouseEventType::~QMouseEventType()
{
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

int qt_QMouseEvent_button_int_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return int(arg0->button());
}

int qt_QMouseEvent_buttons_int_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return int(arg0->buttons());
}

Pointer qt_QMouseEvent_globalPos_QPoint_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return makeqtype<QPointType>(c,arg0->globalPos(),"qt.QPoint");
}

int qt_QMouseEvent_globalX_int_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return arg0->globalX();
}

int qt_QMouseEvent_globalY_int_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return arg0->globalY();
}

Pointer qt_QMouseEvent_localPos_QPointF_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return makeqtype<QPointFType>(c,arg0->localPos(),"qt.QPointF");
}

Pointer qt_QMouseEvent_pos_QPoint_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return makeqtype<QPointType>(c,arg0->pos(),"qt.QPoint");
}

Pointer qt_QMouseEvent_screenPos_QPointF_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return makeqtype<QPointFType>(c,arg0->screenPos(),"qt.QPointF");
}

Pointer qt_QMouseEvent_windowPos_QPointF_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return makeqtype<QPointFType>(c,arg0->windowPos(),"qt.QPointF");
}

int qt_QMouseEvent_x_int_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return arg0->x();
}

int qt_QMouseEvent_y_int_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMouseEvent * arg0 = getqpointer<QMouseEventType>(param_this);
    return arg0->y();
}


static NODE_IMPLEMENTATION(_n_button0, int)
{
    NODE_RETURN(qt_QMouseEvent_button_int_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_buttons0, int)
{
    NODE_RETURN(qt_QMouseEvent_buttons_int_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_globalPos0, Pointer)
{
    NODE_RETURN(qt_QMouseEvent_globalPos_QPoint_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_globalX0, int)
{
    NODE_RETURN(qt_QMouseEvent_globalX_int_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_globalY0, int)
{
    NODE_RETURN(qt_QMouseEvent_globalY_int_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_localPos0, Pointer)
{
    NODE_RETURN(qt_QMouseEvent_localPos_QPointF_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_pos0, Pointer)
{
    NODE_RETURN(qt_QMouseEvent_pos_QPoint_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_screenPos0, Pointer)
{
    NODE_RETURN(qt_QMouseEvent_screenPos_QPointF_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_windowPos0, Pointer)
{
    NODE_RETURN(qt_QMouseEvent_windowPos_QPointF_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_x0, int)
{
    NODE_RETURN(qt_QMouseEvent_x_int_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_y0, int)
{
    NODE_RETURN(qt_QMouseEvent_y_int_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}



void
QMouseEventType::load()
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
    // MISSING: QMouseEvent (QMouseEvent; QMouseEvent this, "Type" type, QPointF localPos, flags Qt::MouseButton button, flags Qt::MouseButtons buttons, flags Qt::KeyboardModifiers modifiers)
    // MISSING: QMouseEvent (QMouseEvent; QMouseEvent this, "Type" type, QPointF localPos, QPointF screenPos, flags Qt::MouseButton button, flags Qt::MouseButtons buttons, flags Qt::KeyboardModifiers modifiers)
    // MISSING: QMouseEvent (QMouseEvent; QMouseEvent this, "Type" type, QPointF localPos, QPointF windowPos, QPointF screenPos, flags Qt::MouseButton button, flags Qt::MouseButtons buttons, flags Qt::KeyboardModifiers modifiers)
    new Function(c, "button", _n_button0, None, Compiled, qt_QMouseEvent_button_int_QMouseEvent, Return, "int", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    new Function(c, "buttons", _n_buttons0, None, Compiled, qt_QMouseEvent_buttons_int_QMouseEvent, Return, "int", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    new Function(c, "globalPos", _n_globalPos0, None, Compiled, qt_QMouseEvent_globalPos_QPoint_QMouseEvent, Return, "qt.QPoint", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    new Function(c, "globalX", _n_globalX0, None, Compiled, qt_QMouseEvent_globalX_int_QMouseEvent, Return, "int", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    new Function(c, "globalY", _n_globalY0, None, Compiled, qt_QMouseEvent_globalY_int_QMouseEvent, Return, "int", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    new Function(c, "localPos", _n_localPos0, None, Compiled, qt_QMouseEvent_localPos_QPointF_QMouseEvent, Return, "qt.QPointF", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    new Function(c, "pos", _n_pos0, None, Compiled, qt_QMouseEvent_pos_QPoint_QMouseEvent, Return, "qt.QPoint", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    new Function(c, "screenPos", _n_screenPos0, None, Compiled, qt_QMouseEvent_screenPos_QPointF_QMouseEvent, Return, "qt.QPointF", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    new Function(c, "windowPos", _n_windowPos0, None, Compiled, qt_QMouseEvent_windowPos_QPointF_QMouseEvent, Return, "qt.QPointF", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    new Function(c, "x", _n_x0, None, Compiled, qt_QMouseEvent_x_int_QMouseEvent, Return, "int", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    new Function(c, "y", _n_y0, None, Compiled, qt_QMouseEvent_y_int_QMouseEvent, Return, "int", Parameters, new Param(c, "this", "qt.QMouseEvent"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    EndArguments);
scope()->addSymbols(
    EndArguments);

}

} // Mu
