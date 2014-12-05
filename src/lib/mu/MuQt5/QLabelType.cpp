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
#include "QLabelType.h"
#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include <QtSvg/QtSvg>
#include <QtNetwork/QtNetwork>
#include <QtWebKit/QtWebKit>
#include <QtWebKitWidgets/QtWebKitWidgets>
#include "QWidgetType.h"
#include "QActionType.h"
#include "QIconType.h"
#include <Mu/BaseFunctions.h>
#include <Mu/Thread.h>
#include <Mu/Alias.h>
#include <Mu/SymbolicConstant.h>
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
#include "QEventType.h"
#include "QMouseEventType.h"
#include "QPaintEventType.h"
#include "QFocusEventType.h"
#include "QContextMenuEventType.h"
#include "QKeyEventType.h"
#include "QWidgetType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

//----------------------------------------------------------------------
//  INHERITABLE TYPE IMPLEMENTATION

// destructor
MuQt_QLabel::~MuQt_QLabel()
{
    if (_obj)
    {
        *_obj->data<Pointer>() = Pointer(0);
        _obj->releaseExternal();
    }
    _obj = 0;
    _env = 0;
    _baseType = 0;
}

MuQt_QLabel::MuQt_QLabel(Pointer muobj, const CallEnvironment* ce, QWidget * parent, Qt::WindowFlags f) 
 : QLabel(parent, f)
{
    _env = ce;
    _obj = reinterpret_cast<ClassInstance*>(muobj);
    _obj->retainExternal();
    MuLangContext* c = (MuLangContext*)_env->context();
    _baseType = c->findSymbolOfTypeByQualifiedName<QLabelType>(c->internName("qt.QLabel"));
}

MuQt_QLabel::MuQt_QLabel(Pointer muobj, const CallEnvironment* ce, const QString & text, QWidget * parent, Qt::WindowFlags f) 
 : QLabel(text, parent, f)
{
    _env = ce;
    _obj = reinterpret_cast<ClassInstance*>(muobj);
    _obj->retainExternal();
    MuLangContext* c = (MuLangContext*)_env->context();
    _baseType = c->findSymbolOfTypeByQualifiedName<QLabelType>(c->internName("qt.QLabel"));
}

int MuQt_QLabel::heightForWidth(int w) const
{
    if (!_env) return QLabel::heightForWidth(w);
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[0];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(w);
        Value rval = _env->call(F, args);
        return (int)(rval._int);
    }
    else
    {
        return QLabel::heightForWidth(w);
    }
}

QSize MuQt_QLabel::minimumSizeHint() const
{
    if (!_env) return QLabel::minimumSizeHint();
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[1];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(1);
        args[0] = Value(Pointer(_obj));
        Value rval = _env->call(F, args);
        return getqtype<QSizeType>(rval._Pointer);
    }
    else
    {
        return QLabel::minimumSizeHint();
    }
}

QSize MuQt_QLabel::sizeHint() const
{
    if (!_env) return QLabel::sizeHint();
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[2];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(1);
        args[0] = Value(Pointer(_obj));
        Value rval = _env->call(F, args);
        return getqtype<QSizeType>(rval._Pointer);
    }
    else
    {
        return QLabel::sizeHint();
    }
}

void MuQt_QLabel::changeEvent(QEvent * ev) 
{
    if (!_env) { QLabel::changeEvent(ev); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[3];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QEventType>(c,ev,"qt.QEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QLabel::changeEvent(ev);
    }
}

void MuQt_QLabel::contextMenuEvent(QContextMenuEvent * ev) 
{
    if (!_env) { QLabel::contextMenuEvent(ev); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[4];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QContextMenuEventType>(c,ev,"qt.QContextMenuEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QLabel::contextMenuEvent(ev);
    }
}

bool MuQt_QLabel::event(QEvent * e) 
{
    if (!_env) return QLabel::event(e);
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[5];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QEventType>(c,e,"qt.QEvent"));
        Value rval = _env->call(F, args);
        return (bool)(rval._bool);
    }
    else
    {
        return QLabel::event(e);
    }
}

void MuQt_QLabel::focusInEvent(QFocusEvent * ev) 
{
    if (!_env) { QLabel::focusInEvent(ev); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[6];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QFocusEventType>(c,ev,"qt.QFocusEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QLabel::focusInEvent(ev);
    }
}

bool MuQt_QLabel::focusNextPrevChild(bool next) 
{
    if (!_env) return QLabel::focusNextPrevChild(next);
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[7];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(next);
        Value rval = _env->call(F, args);
        return (bool)(rval._bool);
    }
    else
    {
        return QLabel::focusNextPrevChild(next);
    }
}

void MuQt_QLabel::focusOutEvent(QFocusEvent * ev) 
{
    if (!_env) { QLabel::focusOutEvent(ev); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[8];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QFocusEventType>(c,ev,"qt.QFocusEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QLabel::focusOutEvent(ev);
    }
}

void MuQt_QLabel::keyPressEvent(QKeyEvent * ev) 
{
    if (!_env) { QLabel::keyPressEvent(ev); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[9];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QKeyEventType>(c,ev,"qt.QKeyEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QLabel::keyPressEvent(ev);
    }
}

void MuQt_QLabel::mouseMoveEvent(QMouseEvent * ev) 
{
    if (!_env) { QLabel::mouseMoveEvent(ev); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[10];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QMouseEventType>(c,ev,"qt.QMouseEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QLabel::mouseMoveEvent(ev);
    }
}

void MuQt_QLabel::mousePressEvent(QMouseEvent * ev) 
{
    if (!_env) { QLabel::mousePressEvent(ev); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[11];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QMouseEventType>(c,ev,"qt.QMouseEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QLabel::mousePressEvent(ev);
    }
}

void MuQt_QLabel::mouseReleaseEvent(QMouseEvent * ev) 
{
    if (!_env) { QLabel::mouseReleaseEvent(ev); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[12];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QMouseEventType>(c,ev,"qt.QMouseEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QLabel::mouseReleaseEvent(ev);
    }
}

void MuQt_QLabel::paintEvent(QPaintEvent * _p13) 
{
    if (!_env) { QLabel::paintEvent(_p13); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[13];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QPaintEventType>(c,_p13,"qt.QPaintEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QLabel::paintEvent(_p13);
    }
}



//----------------------------------------------------------------------
//  Mu Type CONSTRUCTORS

QLabelType::QLabelType(Context* c, const char* name, Class* super, Class* super2)
: Class(c, name, vectorOf2(super, super2))
{
}

QLabelType::~QLabelType()
{
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

static Pointer
QLabel_QLabel_QObject(Thread& NODE_THREAD, Pointer obj)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    ClassInstance* widget = reinterpret_cast<ClassInstance*>(obj);

    if (!widget)
    {
        return 0;
    }
    else if (QLabel* w = object<QLabel>(widget))
    {
        QLabelType* type = 
            c->findSymbolOfTypeByQualifiedName<QLabelType>(c->internName("qt.QLabel"), false);
        ClassInstance* o = ClassInstance::allocate(type);
        setobject(o, w);
        return o;
    }
    else
    {
        throw BadCastException();
    }
}

static NODE_IMPLEMENTATION(castFromObject, Pointer)
{
    NODE_RETURN( QLabel_QLabel_QObject(NODE_THREAD, NODE_ARG(0, Pointer)) );
}

Pointer qt_QLabel_QLabel_QLabel_QLabel_QWidget_int(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_parent, int param_f)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QWidget * arg1 = object<QWidget>(param_parent);
    Qt::WindowFlags arg2 = (Qt::WindowFlags)(param_f);
    setobject(param_this, new MuQt_QLabel(param_this, NODE_THREAD.process()->callEnv(), arg1, arg2));
    return param_this;
}

Pointer qt_QLabel_QLabel_QLabel_QLabel_string_QWidget_int(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_text, Pointer param_parent, int param_f)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QString  arg1 = qstring(param_text);
    QWidget * arg2 = object<QWidget>(param_parent);
    Qt::WindowFlags arg3 = (Qt::WindowFlags)(param_f);
    setobject(param_this, new MuQt_QLabel(param_this, NODE_THREAD.process()->callEnv(), arg1, arg2, arg3));
    return param_this;
}

Pointer qt_QLabel_buddy_QWidget_QLabel(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    return makeinstance<QWidgetType>(c, arg0->buddy(), "qt.QWidget");
}

int qt_QLabel_selectionStart_int_QLabel(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    return arg0->selectionStart();
}

void qt_QLabel_setBuddy_void_QLabel_QWidget(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_buddy)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QWidget * arg1 = object<QWidget>(param_buddy);
    arg0->setBuddy(arg1);
}

void qt_QLabel_setSelection_void_QLabel_int_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_start, int param_length)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    int arg1 = (int)(param_start);
    int arg2 = (int)(param_length);
    arg0->setSelection(arg1, arg2);
}

int qt_QLabel_heightForWidth_int_QLabel_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_w)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    int arg1 = (int)(param_w);
    return isMuQtObject(arg0) ? arg0->QLabel::heightForWidth(arg1) : arg0->heightForWidth(arg1);
}

Pointer qt_QLabel_minimumSizeHint_QSize_QLabel(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    return isMuQtObject(arg0) ? makeqtype<QSizeType>(c,arg0->QLabel::minimumSizeHint(),"qt.QSize") : makeqtype<QSizeType>(c,arg0->minimumSizeHint(),"qt.QSize");
}

Pointer qt_QLabel_sizeHint_QSize_QLabel(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    return isMuQtObject(arg0) ? makeqtype<QSizeType>(c,arg0->QLabel::sizeHint(),"qt.QSize") : makeqtype<QSizeType>(c,arg0->sizeHint(),"qt.QSize");
}

void qt_QLabel_changeEvent_void_QLabel_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_ev)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QEvent * arg1 = getqpointer<QEventType>(param_ev);
    if (isMuQtObject(arg0)) ((MuQt_QLabel*)arg0)->changeEvent_pub_parent(arg1);
    else ((MuQt_QLabel*)arg0)->changeEvent_pub(arg1);
}

void qt_QLabel_contextMenuEvent_void_QLabel_QContextMenuEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_ev)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QContextMenuEvent * arg1 = getqpointer<QContextMenuEventType>(param_ev);
    if (isMuQtObject(arg0)) ((MuQt_QLabel*)arg0)->contextMenuEvent_pub_parent(arg1);
    else ((MuQt_QLabel*)arg0)->contextMenuEvent_pub(arg1);
}

bool qt_QLabel_event_bool_QLabel_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_e)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QEvent * arg1 = getqpointer<QEventType>(param_e);
    return isMuQtObject(arg0) ? ((MuQt_QLabel*)arg0)->event_pub_parent(arg1) : ((MuQt_QLabel*)arg0)->event_pub(arg1);
}

void qt_QLabel_focusInEvent_void_QLabel_QFocusEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_ev)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QFocusEvent * arg1 = getqpointer<QFocusEventType>(param_ev);
    if (isMuQtObject(arg0)) ((MuQt_QLabel*)arg0)->focusInEvent_pub_parent(arg1);
    else ((MuQt_QLabel*)arg0)->focusInEvent_pub(arg1);
}

bool qt_QLabel_focusNextPrevChild_bool_QLabel_bool(Mu::Thread& NODE_THREAD, Pointer param_this, bool param_next)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    bool arg1 = (bool)(param_next);
    return isMuQtObject(arg0) ? ((MuQt_QLabel*)arg0)->focusNextPrevChild_pub_parent(arg1) : ((MuQt_QLabel*)arg0)->focusNextPrevChild_pub(arg1);
}

void qt_QLabel_focusOutEvent_void_QLabel_QFocusEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_ev)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QFocusEvent * arg1 = getqpointer<QFocusEventType>(param_ev);
    if (isMuQtObject(arg0)) ((MuQt_QLabel*)arg0)->focusOutEvent_pub_parent(arg1);
    else ((MuQt_QLabel*)arg0)->focusOutEvent_pub(arg1);
}

void qt_QLabel_keyPressEvent_void_QLabel_QKeyEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_ev)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QKeyEvent * arg1 = getqpointer<QKeyEventType>(param_ev);
    if (isMuQtObject(arg0)) ((MuQt_QLabel*)arg0)->keyPressEvent_pub_parent(arg1);
    else ((MuQt_QLabel*)arg0)->keyPressEvent_pub(arg1);
}

void qt_QLabel_mouseMoveEvent_void_QLabel_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_ev)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QMouseEvent * arg1 = getqpointer<QMouseEventType>(param_ev);
    if (isMuQtObject(arg0)) ((MuQt_QLabel*)arg0)->mouseMoveEvent_pub_parent(arg1);
    else ((MuQt_QLabel*)arg0)->mouseMoveEvent_pub(arg1);
}

void qt_QLabel_mousePressEvent_void_QLabel_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_ev)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QMouseEvent * arg1 = getqpointer<QMouseEventType>(param_ev);
    if (isMuQtObject(arg0)) ((MuQt_QLabel*)arg0)->mousePressEvent_pub_parent(arg1);
    else ((MuQt_QLabel*)arg0)->mousePressEvent_pub(arg1);
}

void qt_QLabel_mouseReleaseEvent_void_QLabel_QMouseEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_ev)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QMouseEvent * arg1 = getqpointer<QMouseEventType>(param_ev);
    if (isMuQtObject(arg0)) ((MuQt_QLabel*)arg0)->mouseReleaseEvent_pub_parent(arg1);
    else ((MuQt_QLabel*)arg0)->mouseReleaseEvent_pub(arg1);
}

void qt_QLabel_paintEvent_void_QLabel_QPaintEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param__p13)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QLabel* arg0 = object<QLabel>(param_this);
    QPaintEvent * arg1 = getqpointer<QPaintEventType>(param__p13);
    if (isMuQtObject(arg0)) ((MuQt_QLabel*)arg0)->paintEvent_pub_parent(arg1);
    else ((MuQt_QLabel*)arg0)->paintEvent_pub(arg1);
}


static NODE_IMPLEMENTATION(_n_QLabel0, Pointer)
{
    NODE_RETURN(qt_QLabel_QLabel_QLabel_QLabel_QWidget_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, int)));
}

static NODE_IMPLEMENTATION(_n_QLabel1, Pointer)
{
    NODE_RETURN(qt_QLabel_QLabel_QLabel_QLabel_string_QWidget_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer), NODE_ARG(3, int)));
}

static NODE_IMPLEMENTATION(_n_buddy0, Pointer)
{
    NODE_RETURN(qt_QLabel_buddy_QWidget_QLabel(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_selectionStart0, int)
{
    NODE_RETURN(qt_QLabel_selectionStart_int_QLabel(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_setBuddy0, void)
{
    qt_QLabel_setBuddy_void_QLabel_QWidget(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setSelection0, void)
{
    qt_QLabel_setSelection_void_QLabel_int_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, int));
}

static NODE_IMPLEMENTATION(_n_heightForWidth0, int)
{
    NODE_RETURN(qt_QLabel_heightForWidth_int_QLabel_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int)));
}

static NODE_IMPLEMENTATION(_n_minimumSizeHint0, Pointer)
{
    NODE_RETURN(qt_QLabel_minimumSizeHint_QSize_QLabel(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_sizeHint0, Pointer)
{
    NODE_RETURN(qt_QLabel_sizeHint_QSize_QLabel(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_changeEvent0, void)
{
    qt_QLabel_changeEvent_void_QLabel_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_contextMenuEvent0, void)
{
    qt_QLabel_contextMenuEvent_void_QLabel_QContextMenuEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_event0, bool)
{
    NODE_RETURN(qt_QLabel_event_bool_QLabel_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_focusInEvent0, void)
{
    qt_QLabel_focusInEvent_void_QLabel_QFocusEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_focusNextPrevChild0, bool)
{
    NODE_RETURN(qt_QLabel_focusNextPrevChild_bool_QLabel_bool(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, bool)));
}

static NODE_IMPLEMENTATION(_n_focusOutEvent0, void)
{
    qt_QLabel_focusOutEvent_void_QLabel_QFocusEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_keyPressEvent0, void)
{
    qt_QLabel_keyPressEvent_void_QLabel_QKeyEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_mouseMoveEvent0, void)
{
    qt_QLabel_mouseMoveEvent_void_QLabel_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_mousePressEvent0, void)
{
    qt_QLabel_mousePressEvent_void_QLabel_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_mouseReleaseEvent0, void)
{
    qt_QLabel_mouseReleaseEvent_void_QLabel_QMouseEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_paintEvent0, void)
{
    qt_QLabel_paintEvent_void_QLabel_QPaintEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}



void
QLabelType::load()
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


               new Function(c, tn, castFromObject, Cast,
                            Compiled, QLabel_QLabel_QObject,
                            Return, ftn,
                            Parameters,
                            new Param(c, "object", "qt.QObject"),
                            End),

               EndArguments );

addSymbols(
    // enums
    // member functions
    new Function(c, "QLabel", _n_QLabel0, None, Compiled, qt_QLabel_QLabel_QLabel_QLabel_QWidget_int, Return, "qt.QLabel", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "parent", "qt.QWidget"), new Param(c, "f", "int", Value((int)0)), End),
    new Function(c, "QLabel", _n_QLabel1, None, Compiled, qt_QLabel_QLabel_QLabel_QLabel_string_QWidget_int, Return, "qt.QLabel", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "text", "string"), new Param(c, "parent", "qt.QWidget"), new Param(c, "f", "int", Value((int)0)), End),
    // PROP: alignment (flags Qt::Alignment; QLabel this)
    new Function(c, "buddy", _n_buddy0, None, Compiled, qt_QLabel_buddy_QWidget_QLabel, Return, "qt.QWidget", Parameters, new Param(c, "this", "qt.QLabel"), End),
    // PROP: hasScaledContents (bool; QLabel this)
    // PROP: hasSelectedText (bool; QLabel this)
    // PROP: indent (int; QLabel this)
    // PROP: margin (int; QLabel this)
    // MISSING: movie ("QMovie *"; QLabel this)
    // PROP: openExternalLinks (bool; QLabel this)
    // MISSING: picture ("const QPicture *"; QLabel this)
    // PROP: pixmap (QPixmap; QLabel this)
    // PROP: selectedText (string; QLabel this)
    new Function(c, "selectionStart", _n_selectionStart0, None, Compiled, qt_QLabel_selectionStart_int_QLabel, Return, "int", Parameters, new Param(c, "this", "qt.QLabel"), End),
    // PROP: setAlignment (void; QLabel this, flags Qt::Alignment _p13)
    new Function(c, "setBuddy", _n_setBuddy0, None, Compiled, qt_QLabel_setBuddy_void_QLabel_QWidget, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "buddy", "qt.QWidget"), End),
    // PROP: setIndent (void; QLabel this, int _p3)
    // PROP: setMargin (void; QLabel this, int _p3)
    // PROP: setOpenExternalLinks (void; QLabel this, bool open)
    // PROP: setScaledContents (void; QLabel this, bool _p4)
    new Function(c, "setSelection", _n_setSelection0, None, Compiled, qt_QLabel_setSelection_void_QLabel_int_int, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "start", "int"), new Param(c, "length", "int"), End),
    // PROP: setTextFormat (void; QLabel this, flags Qt::TextFormat _p14)
    // PROP: setTextInteractionFlags (void; QLabel this, flags Qt::TextInteractionFlags flags)
    // PROP: setWordWrap (void; QLabel this, bool on)
    // PROP: text (string; QLabel this)
    // PROP: textFormat (flags Qt::TextFormat; QLabel this)
    // PROP: textInteractionFlags (flags Qt::TextInteractionFlags; QLabel this)
    // PROP: wordWrap (bool; QLabel this)
    _func[0] = new MemberFunction(c, "heightForWidth", _n_heightForWidth0, None, Compiled, qt_QLabel_heightForWidth_int_QLabel_int, Return, "int", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "w", "int"), End),
    _func[1] = new MemberFunction(c, "minimumSizeHint", _n_minimumSizeHint0, None, Compiled, qt_QLabel_minimumSizeHint_QSize_QLabel, Return, "qt.QSize", Parameters, new Param(c, "this", "qt.QLabel"), End),
    _func[2] = new MemberFunction(c, "sizeHint", _n_sizeHint0, None, Compiled, qt_QLabel_sizeHint_QSize_QLabel, Return, "qt.QSize", Parameters, new Param(c, "this", "qt.QLabel"), End),
    _func[3] = new MemberFunction(c, "changeEvent", _n_changeEvent0, None, Compiled, qt_QLabel_changeEvent_void_QLabel_QEvent, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "ev", "qt.QEvent"), End),
    _func[4] = new MemberFunction(c, "contextMenuEvent", _n_contextMenuEvent0, None, Compiled, qt_QLabel_contextMenuEvent_void_QLabel_QContextMenuEvent, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "ev", "qt.QContextMenuEvent"), End),
    _func[5] = new MemberFunction(c, "event", _n_event0, None, Compiled, qt_QLabel_event_bool_QLabel_QEvent, Return, "bool", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "e", "qt.QEvent"), End),
    _func[6] = new MemberFunction(c, "focusInEvent", _n_focusInEvent0, None, Compiled, qt_QLabel_focusInEvent_void_QLabel_QFocusEvent, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "ev", "qt.QFocusEvent"), End),
    _func[7] = new MemberFunction(c, "focusNextPrevChild", _n_focusNextPrevChild0, None, Compiled, qt_QLabel_focusNextPrevChild_bool_QLabel_bool, Return, "bool", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "next", "bool"), End),
    _func[8] = new MemberFunction(c, "focusOutEvent", _n_focusOutEvent0, None, Compiled, qt_QLabel_focusOutEvent_void_QLabel_QFocusEvent, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "ev", "qt.QFocusEvent"), End),
    _func[9] = new MemberFunction(c, "keyPressEvent", _n_keyPressEvent0, None, Compiled, qt_QLabel_keyPressEvent_void_QLabel_QKeyEvent, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "ev", "qt.QKeyEvent"), End),
    _func[10] = new MemberFunction(c, "mouseMoveEvent", _n_mouseMoveEvent0, None, Compiled, qt_QLabel_mouseMoveEvent_void_QLabel_QMouseEvent, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "ev", "qt.QMouseEvent"), End),
    _func[11] = new MemberFunction(c, "mousePressEvent", _n_mousePressEvent0, None, Compiled, qt_QLabel_mousePressEvent_void_QLabel_QMouseEvent, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "ev", "qt.QMouseEvent"), End),
    _func[12] = new MemberFunction(c, "mouseReleaseEvent", _n_mouseReleaseEvent0, None, Compiled, qt_QLabel_mouseReleaseEvent_void_QLabel_QMouseEvent, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "ev", "qt.QMouseEvent"), End),
    _func[13] = new MemberFunction(c, "paintEvent", _n_paintEvent0, None, Compiled, qt_QLabel_paintEvent_void_QLabel_QPaintEvent, Return, "void", Parameters, new Param(c, "this", "qt.QLabel"), new Param(c, "_p13", "qt.QPaintEvent"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    EndArguments);
scope()->addSymbols(
    EndArguments);


    const char** propExclusions = 0;

    populate(this, QLabel::staticMetaObject, propExclusions);
}

} // Mu
