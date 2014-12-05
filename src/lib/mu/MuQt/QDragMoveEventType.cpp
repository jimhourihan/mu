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
#include "QDragMoveEventType.h"
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
#include "QRectType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

QDragMoveEventType::QDragMoveEventType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QDragMoveEventType::~QDragMoveEventType()
{
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

void qt_QDragMoveEvent_accept_void_QDragMoveEvent_QRect(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_rectangle)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QDragMoveEvent * arg0 = getqpointer<QDragMoveEventType>(param_this);
    const QRect  arg1 = getqtype<QRectType>(param_rectangle);
    arg0->accept(arg1);
    setqpointer<QDragMoveEventType>(param_this,arg0);
}

void qt_QDragMoveEvent_accept_void_QDragMoveEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QDragMoveEvent * arg0 = getqpointer<QDragMoveEventType>(param_this);
    arg0->accept();
    setqpointer<QDragMoveEventType>(param_this,arg0);
}

Pointer qt_QDragMoveEvent_answerRect_QRect_QDragMoveEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QDragMoveEvent * arg0 = getqpointer<QDragMoveEventType>(param_this);
    return makeqtype<QRectType>(c,arg0->answerRect(),"qt.QRect");
}

void qt_QDragMoveEvent_ignore_void_QDragMoveEvent_QRect(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_rectangle)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QDragMoveEvent * arg0 = getqpointer<QDragMoveEventType>(param_this);
    const QRect  arg1 = getqtype<QRectType>(param_rectangle);
    arg0->ignore(arg1);
    setqpointer<QDragMoveEventType>(param_this,arg0);
}

void qt_QDragMoveEvent_ignore_void_QDragMoveEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QDragMoveEvent * arg0 = getqpointer<QDragMoveEventType>(param_this);
    arg0->ignore();
    setqpointer<QDragMoveEventType>(param_this,arg0);
}


static NODE_IMPLEMENTATION(_n_accept0, void)
{
    qt_QDragMoveEvent_accept_void_QDragMoveEvent_QRect(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_accept1, void)
{
    qt_QDragMoveEvent_accept_void_QDragMoveEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer));
}

static NODE_IMPLEMENTATION(_n_answerRect0, Pointer)
{
    NODE_RETURN(qt_QDragMoveEvent_answerRect_QRect_QDragMoveEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_ignore0, void)
{
    qt_QDragMoveEvent_ignore_void_QDragMoveEvent_QRect(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_ignore1, void)
{
    qt_QDragMoveEvent_ignore_void_QDragMoveEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer));
}



void
QDragMoveEventType::load()
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
    // MISSING: QDragMoveEvent (QDragMoveEvent; QDragMoveEvent this, QPoint pos, flags Qt::DropActions actions, QMimeData data, flags Qt::MouseButtons buttons, flags Qt::KeyboardModifiers modifiers, "Type" type)
    new Function(c, "accept", _n_accept0, None, Compiled, qt_QDragMoveEvent_accept_void_QDragMoveEvent_QRect, Return, "void", Parameters, new Param(c, "this", "qt.QDragMoveEvent"), new Param(c, "rectangle", "qt.QRect"), End),
    new Function(c, "accept", _n_accept1, None, Compiled, qt_QDragMoveEvent_accept_void_QDragMoveEvent, Return, "void", Parameters, new Param(c, "this", "qt.QDragMoveEvent"), End),
    new Function(c, "answerRect", _n_answerRect0, None, Compiled, qt_QDragMoveEvent_answerRect_QRect_QDragMoveEvent, Return, "qt.QRect", Parameters, new Param(c, "this", "qt.QDragMoveEvent"), End),
    new Function(c, "ignore", _n_ignore0, None, Compiled, qt_QDragMoveEvent_ignore_void_QDragMoveEvent_QRect, Return, "void", Parameters, new Param(c, "this", "qt.QDragMoveEvent"), new Param(c, "rectangle", "qt.QRect"), End),
    new Function(c, "ignore", _n_ignore1, None, Compiled, qt_QDragMoveEvent_ignore_void_QDragMoveEvent, Return, "void", Parameters, new Param(c, "this", "qt.QDragMoveEvent"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    EndArguments);
scope()->addSymbols(
    EndArguments);

}

} // Mu
