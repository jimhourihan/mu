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
#include "QSplitterType.h"
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
#include "QPaintEventType.h"
#include "QWidgetType.h"
#include "QResizeEventType.h"
#include "QByteArrayType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

//----------------------------------------------------------------------
//  INHERITABLE TYPE IMPLEMENTATION

// destructor
MuQt_QSplitter::~MuQt_QSplitter()
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

MuQt_QSplitter::MuQt_QSplitter(Pointer muobj, const CallEnvironment* ce, QWidget * parent) 
 : QSplitter(parent)
{
    _env = ce;
    _obj = reinterpret_cast<ClassInstance*>(muobj);
    _obj->retainExternal();
    MuLangContext* c = (MuLangContext*)_env->context();
    _baseType = c->findSymbolOfTypeByQualifiedName<QSplitterType>(c->internName("qt.QSplitter"));
}

MuQt_QSplitter::MuQt_QSplitter(Pointer muobj, const CallEnvironment* ce, Qt::Orientation orientation, QWidget * parent) 
 : QSplitter(orientation, parent)
{
    _env = ce;
    _obj = reinterpret_cast<ClassInstance*>(muobj);
    _obj->retainExternal();
    MuLangContext* c = (MuLangContext*)_env->context();
    _baseType = c->findSymbolOfTypeByQualifiedName<QSplitterType>(c->internName("qt.QSplitter"));
}

QSize MuQt_QSplitter::minimumSizeHint() const
{
    if (!_env) return QSplitter::minimumSizeHint();
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[0];
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
        return QSplitter::minimumSizeHint();
    }
}

QSize MuQt_QSplitter::sizeHint() const
{
    if (!_env) return QSplitter::sizeHint();
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
        return QSplitter::sizeHint();
    }
}

void MuQt_QSplitter::changeEvent(QEvent * ev) 
{
    if (!_env) { QSplitter::changeEvent(ev); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[2];
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
        QSplitter::changeEvent(ev);
    }
}

bool MuQt_QSplitter::event(QEvent * e) 
{
    if (!_env) return QSplitter::event(e);
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[3];
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
        return QSplitter::event(e);
    }
}

void MuQt_QSplitter::resizeEvent(QResizeEvent * _p14) 
{
    if (!_env) { QSplitter::resizeEvent(_p14); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[4];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QResizeEventType>(c,_p14,"qt.QResizeEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QSplitter::resizeEvent(_p14);
    }
}

void MuQt_QSplitter::paintEvent(QPaintEvent * _p13) 
{
    if (!_env) { QSplitter::paintEvent(_p13); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[5];
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
        QSplitter::paintEvent(_p13);
    }
}



//----------------------------------------------------------------------
//  Mu Type CONSTRUCTORS

QSplitterType::QSplitterType(Context* c, const char* name, Class* super, Class* super2)
: Class(c, name, vectorOf2(super, super2))
{
}

QSplitterType::~QSplitterType()
{
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

static Pointer
QSplitter_QSplitter_QObject(Thread& NODE_THREAD, Pointer obj)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    ClassInstance* widget = reinterpret_cast<ClassInstance*>(obj);

    if (!widget)
    {
        return 0;
    }
    else if (QSplitter* w = object<QSplitter>(widget))
    {
        QSplitterType* type = 
            c->findSymbolOfTypeByQualifiedName<QSplitterType>(c->internName("qt.QSplitter"), false);
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
    NODE_RETURN( QSplitter_QSplitter_QObject(NODE_THREAD, NODE_ARG(0, Pointer)) );
}

Pointer qt_QSplitter_QSplitter_QSplitter_QSplitter_QWidget(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_parent)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QWidget * arg1 = object<QWidget>(param_parent);
    setobject(param_this, new MuQt_QSplitter(param_this, NODE_THREAD.process()->callEnv(), arg1));
    return param_this;
}

Pointer qt_QSplitter_QSplitter_QSplitter_QSplitter_int_QWidget(Mu::Thread& NODE_THREAD, Pointer param_this, int param_orientation, Pointer param_parent)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    Qt::Orientation arg1 = (Qt::Orientation)(param_orientation);
    QWidget * arg2 = object<QWidget>(param_parent);
    setobject(param_this, new MuQt_QSplitter(param_this, NODE_THREAD.process()->callEnv(), arg1, arg2));
    return param_this;
}

void qt_QSplitter_addWidget_void_QSplitter_QWidget(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_widget)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    QWidget * arg1 = object<QWidget>(param_widget);
    arg0->addWidget(arg1);
}

int qt_QSplitter_count_int_QSplitter(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    return arg0->count();
}

int qt_QSplitter_indexOf_int_QSplitter_QWidget(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_widget)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    QWidget * arg1 = object<QWidget>(param_widget);
    return arg0->indexOf(arg1);
}

void qt_QSplitter_insertWidget_void_QSplitter_int_QWidget(Mu::Thread& NODE_THREAD, Pointer param_this, int param_index, Pointer param_widget)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    int arg1 = (int)(param_index);
    QWidget * arg2 = object<QWidget>(param_widget);
    arg0->insertWidget(arg1, arg2);
}

bool qt_QSplitter_isCollapsible_bool_QSplitter_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_index)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    int arg1 = (int)(param_index);
    return arg0->isCollapsible(arg1);
}

void qt_QSplitter_refresh_void_QSplitter(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    arg0->refresh();
}

bool qt_QSplitter_restoreState_bool_QSplitter_QByteArray(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_state)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    const QByteArray  arg1 = getqtype<QByteArrayType>(param_state);
    return arg0->restoreState(arg1);
}

Pointer qt_QSplitter_saveState_QByteArray_QSplitter(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    return makeqtype<QByteArrayType>(c,arg0->saveState(),"qt.QByteArray");
}

void qt_QSplitter_setCollapsible_void_QSplitter_int_bool(Mu::Thread& NODE_THREAD, Pointer param_this, int param_index, bool param_collapse)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    int arg1 = (int)(param_index);
    bool arg2 = (bool)(param_collapse);
    arg0->setCollapsible(arg1, arg2);
}

void qt_QSplitter_setStretchFactor_void_QSplitter_int_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_index, int param_stretch)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    int arg1 = (int)(param_index);
    int arg2 = (int)(param_stretch);
    arg0->setStretchFactor(arg1, arg2);
}

Pointer qt_QSplitter_widget_QWidget_QSplitter_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_index)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    int arg1 = (int)(param_index);
    return makeinstance<QWidgetType>(c, arg0->widget(arg1), "qt.QWidget");
}

Pointer qt_QSplitter_minimumSizeHint_QSize_QSplitter(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    return isMuQtObject(arg0) ? makeqtype<QSizeType>(c,arg0->QSplitter::minimumSizeHint(),"qt.QSize") : makeqtype<QSizeType>(c,arg0->minimumSizeHint(),"qt.QSize");
}

Pointer qt_QSplitter_sizeHint_QSize_QSplitter(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    return isMuQtObject(arg0) ? makeqtype<QSizeType>(c,arg0->QSplitter::sizeHint(),"qt.QSize") : makeqtype<QSizeType>(c,arg0->sizeHint(),"qt.QSize");
}

int qt_QSplitter_closestLegalPosition_int_QSplitter_int_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_pos, int param_index)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    int arg1 = (int)(param_pos);
    int arg2 = (int)(param_index);
    return ((MuQt_QSplitter*)arg0)->closestLegalPosition_pub(arg1, arg2);
}

void qt_QSplitter_moveSplitter_void_QSplitter_int_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_pos, int param_index)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    int arg1 = (int)(param_pos);
    int arg2 = (int)(param_index);
    ((MuQt_QSplitter*)arg0)->moveSplitter_pub(arg1, arg2);
}

void qt_QSplitter_setRubberBand_void_QSplitter_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_pos)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    int arg1 = (int)(param_pos);
    ((MuQt_QSplitter*)arg0)->setRubberBand_pub(arg1);
}

void qt_QSplitter_changeEvent_void_QSplitter_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_ev)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    QEvent * arg1 = getqpointer<QEventType>(param_ev);
    if (isMuQtObject(arg0)) ((MuQt_QSplitter*)arg0)->changeEvent_pub_parent(arg1);
    else ((MuQt_QSplitter*)arg0)->changeEvent_pub(arg1);
}

bool qt_QSplitter_event_bool_QSplitter_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_e)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    QEvent * arg1 = getqpointer<QEventType>(param_e);
    return isMuQtObject(arg0) ? ((MuQt_QSplitter*)arg0)->event_pub_parent(arg1) : ((MuQt_QSplitter*)arg0)->event_pub(arg1);
}

void qt_QSplitter_resizeEvent_void_QSplitter_QResizeEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param__p14)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    QResizeEvent * arg1 = getqpointer<QResizeEventType>(param__p14);
    if (isMuQtObject(arg0)) ((MuQt_QSplitter*)arg0)->resizeEvent_pub_parent(arg1);
    else ((MuQt_QSplitter*)arg0)->resizeEvent_pub(arg1);
}

void qt_QSplitter_paintEvent_void_QSplitter_QPaintEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param__p13)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QSplitter* arg0 = object<QSplitter>(param_this);
    QPaintEvent * arg1 = getqpointer<QPaintEventType>(param__p13);
    if (isMuQtObject(arg0)) ((MuQt_QSplitter*)arg0)->paintEvent_pub_parent(arg1);
    else ((MuQt_QSplitter*)arg0)->paintEvent_pub(arg1);
}


static NODE_IMPLEMENTATION(_n_QSplitter0, Pointer)
{
    NODE_RETURN(qt_QSplitter_QSplitter_QSplitter_QSplitter_QWidget(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QSplitter1, Pointer)
{
    NODE_RETURN(qt_QSplitter_QSplitter_QSplitter_QSplitter_int_QWidget(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_addWidget0, void)
{
    qt_QSplitter_addWidget_void_QSplitter_QWidget(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_count0, int)
{
    NODE_RETURN(qt_QSplitter_count_int_QSplitter(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_indexOf0, int)
{
    NODE_RETURN(qt_QSplitter_indexOf_int_QSplitter_QWidget(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_insertWidget0, void)
{
    qt_QSplitter_insertWidget_void_QSplitter_int_QWidget(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, Pointer));
}

static NODE_IMPLEMENTATION(_n_isCollapsible0, bool)
{
    NODE_RETURN(qt_QSplitter_isCollapsible_bool_QSplitter_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int)));
}

static NODE_IMPLEMENTATION(_n_refresh0, void)
{
    qt_QSplitter_refresh_void_QSplitter(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer));
}

static NODE_IMPLEMENTATION(_n_restoreState0, bool)
{
    NODE_RETURN(qt_QSplitter_restoreState_bool_QSplitter_QByteArray(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_saveState0, Pointer)
{
    NODE_RETURN(qt_QSplitter_saveState_QByteArray_QSplitter(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_setCollapsible0, void)
{
    qt_QSplitter_setCollapsible_void_QSplitter_int_bool(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, bool));
}

static NODE_IMPLEMENTATION(_n_setStretchFactor0, void)
{
    qt_QSplitter_setStretchFactor_void_QSplitter_int_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, int));
}

static NODE_IMPLEMENTATION(_n_widget0, Pointer)
{
    NODE_RETURN(qt_QSplitter_widget_QWidget_QSplitter_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int)));
}

static NODE_IMPLEMENTATION(_n_minimumSizeHint0, Pointer)
{
    NODE_RETURN(qt_QSplitter_minimumSizeHint_QSize_QSplitter(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_sizeHint0, Pointer)
{
    NODE_RETURN(qt_QSplitter_sizeHint_QSize_QSplitter(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_closestLegalPosition0, int)
{
    NODE_RETURN(qt_QSplitter_closestLegalPosition_int_QSplitter_int_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, int)));
}

static NODE_IMPLEMENTATION(_n_moveSplitter0, void)
{
    qt_QSplitter_moveSplitter_void_QSplitter_int_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, int));
}

static NODE_IMPLEMENTATION(_n_setRubberBand0, void)
{
    qt_QSplitter_setRubberBand_void_QSplitter_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int));
}

static NODE_IMPLEMENTATION(_n_changeEvent0, void)
{
    qt_QSplitter_changeEvent_void_QSplitter_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_event0, bool)
{
    NODE_RETURN(qt_QSplitter_event_bool_QSplitter_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_resizeEvent0, void)
{
    qt_QSplitter_resizeEvent_void_QSplitter_QResizeEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_paintEvent0, void)
{
    qt_QSplitter_paintEvent_void_QSplitter_QPaintEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}



void
QSplitterType::load()
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
                            Compiled, QSplitter_QSplitter_QObject,
                            Return, ftn,
                            Parameters,
                            new Param(c, "object", "qt.QObject"),
                            End),

               EndArguments );

addSymbols(
    // enums
    // member functions
    new Function(c, "QSplitter", _n_QSplitter0, None, Compiled, qt_QSplitter_QSplitter_QSplitter_QSplitter_QWidget, Return, "qt.QSplitter", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "parent", "qt.QWidget"), End),
    new Function(c, "QSplitter", _n_QSplitter1, None, Compiled, qt_QSplitter_QSplitter_QSplitter_QSplitter_int_QWidget, Return, "qt.QSplitter", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "orientation", "int"), new Param(c, "parent", "qt.QWidget"), End),
    new Function(c, "addWidget", _n_addWidget0, None, Compiled, qt_QSplitter_addWidget_void_QSplitter_QWidget, Return, "void", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "widget", "qt.QWidget"), End),
    // PROP: childrenCollapsible (bool; QSplitter this)
    new Function(c, "count", _n_count0, None, Compiled, qt_QSplitter_count_int_QSplitter, Return, "int", Parameters, new Param(c, "this", "qt.QSplitter"), End),
    // MISSING: getRange (void; QSplitter this, int index, "int *" min, "int *" max)
    // MISSING: handle ("QSplitterHandle *"; QSplitter this, int index)
    // PROP: handleWidth (int; QSplitter this)
    new Function(c, "indexOf", _n_indexOf0, None, Compiled, qt_QSplitter_indexOf_int_QSplitter_QWidget, Return, "int", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "widget", "qt.QWidget"), End),
    new Function(c, "insertWidget", _n_insertWidget0, None, Compiled, qt_QSplitter_insertWidget_void_QSplitter_int_QWidget, Return, "void", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "index", "int"), new Param(c, "widget", "qt.QWidget"), End),
    new Function(c, "isCollapsible", _n_isCollapsible0, None, Compiled, qt_QSplitter_isCollapsible_bool_QSplitter_int, Return, "bool", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "index", "int"), End),
    // PROP: opaqueResize (bool; QSplitter this)
    // PROP: orientation (flags Qt::Orientation; QSplitter this)
    new Function(c, "refresh", _n_refresh0, None, Compiled, qt_QSplitter_refresh_void_QSplitter, Return, "void", Parameters, new Param(c, "this", "qt.QSplitter"), End),
    new Function(c, "restoreState", _n_restoreState0, None, Compiled, qt_QSplitter_restoreState_bool_QSplitter_QByteArray, Return, "bool", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "state", "qt.QByteArray"), End),
    new Function(c, "saveState", _n_saveState0, None, Compiled, qt_QSplitter_saveState_QByteArray_QSplitter, Return, "qt.QByteArray", Parameters, new Param(c, "this", "qt.QSplitter"), End),
    // PROP: setChildrenCollapsible (void; QSplitter this, bool _p4)
    new Function(c, "setCollapsible", _n_setCollapsible0, None, Compiled, qt_QSplitter_setCollapsible_void_QSplitter_int_bool, Return, "void", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "index", "int"), new Param(c, "collapse", "bool"), End),
    // PROP: setHandleWidth (void; QSplitter this, int _p3)
    // PROP: setOpaqueResize (void; QSplitter this, bool opaque)
    // PROP: setOrientation (void; QSplitter this, flags Qt::Orientation _p15)
    // MISSING: setSizes (void; QSplitter this, "const QList<int> &" list)
    new Function(c, "setStretchFactor", _n_setStretchFactor0, None, Compiled, qt_QSplitter_setStretchFactor_void_QSplitter_int_int, Return, "void", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "index", "int"), new Param(c, "stretch", "int"), End),
    // MISSING: sizes ("QList<int>"; QSplitter this)
    new Function(c, "widget", _n_widget0, None, Compiled, qt_QSplitter_widget_QWidget_QSplitter_int, Return, "qt.QWidget", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "index", "int"), End),
    _func[0] = new MemberFunction(c, "minimumSizeHint", _n_minimumSizeHint0, None, Compiled, qt_QSplitter_minimumSizeHint_QSize_QSplitter, Return, "qt.QSize", Parameters, new Param(c, "this", "qt.QSplitter"), End),
    _func[1] = new MemberFunction(c, "sizeHint", _n_sizeHint0, None, Compiled, qt_QSplitter_sizeHint_QSize_QSplitter, Return, "qt.QSize", Parameters, new Param(c, "this", "qt.QSplitter"), End),
    new Function(c, "closestLegalPosition", _n_closestLegalPosition0, None, Compiled, qt_QSplitter_closestLegalPosition_int_QSplitter_int_int, Return, "int", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "pos", "int"), new Param(c, "index", "int"), End),
    // MISSING: createHandle ("QSplitterHandle *"; QSplitter this) // protected
    new Function(c, "moveSplitter", _n_moveSplitter0, None, Compiled, qt_QSplitter_moveSplitter_void_QSplitter_int_int, Return, "void", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "pos", "int"), new Param(c, "index", "int"), End),
    new Function(c, "setRubberBand", _n_setRubberBand0, None, Compiled, qt_QSplitter_setRubberBand_void_QSplitter_int, Return, "void", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "pos", "int"), End),
    _func[2] = new MemberFunction(c, "changeEvent", _n_changeEvent0, None, Compiled, qt_QSplitter_changeEvent_void_QSplitter_QEvent, Return, "void", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "ev", "qt.QEvent"), End),
    // MISSING: childEvent (void; QSplitter this, "QChildEvent *" c) // protected
    _func[3] = new MemberFunction(c, "event", _n_event0, None, Compiled, qt_QSplitter_event_bool_QSplitter_QEvent, Return, "bool", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "e", "qt.QEvent"), End),
    _func[4] = new MemberFunction(c, "resizeEvent", _n_resizeEvent0, None, Compiled, qt_QSplitter_resizeEvent_void_QSplitter_QResizeEvent, Return, "void", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "_p14", "qt.QResizeEvent"), End),
    _func[5] = new MemberFunction(c, "paintEvent", _n_paintEvent0, None, Compiled, qt_QSplitter_paintEvent_void_QSplitter_QPaintEvent, Return, "void", Parameters, new Param(c, "this", "qt.QSplitter"), new Param(c, "_p13", "qt.QPaintEvent"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    EndArguments);
scope()->addSymbols(
    EndArguments);


    const char** propExclusions = 0;

    populate(this, QSplitter::staticMetaObject, propExclusions);
}

} // Mu
