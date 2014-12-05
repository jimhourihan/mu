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
#include "QActionGroupType.h"
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
#include "QTimerEventType.h"
#include "QIconType.h"
#include "QObjectType.h"
#include "QEventType.h"
#include "QActionType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

//----------------------------------------------------------------------
//  INHERITABLE TYPE IMPLEMENTATION

// destructor
MuQt_QActionGroup::~MuQt_QActionGroup()
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

MuQt_QActionGroup::MuQt_QActionGroup(Pointer muobj, const CallEnvironment* ce, QObject * parent) 
 : QActionGroup(parent)
{
    _env = ce;
    _obj = reinterpret_cast<ClassInstance*>(muobj);
    _obj->retainExternal();
    MuLangContext* c = (MuLangContext*)_env->context();
    _baseType = c->findSymbolOfTypeByQualifiedName<QActionGroupType>(c->internName("qt.QActionGroup"));
}

bool MuQt_QActionGroup::event(QEvent * e) 
{
    if (!_env) return QActionGroup::event(e);
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[0];
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
        return QActionGroup::event(e);
    }
}

bool MuQt_QActionGroup::eventFilter(QObject * watched, QEvent * event) 
{
    if (!_env) return QActionGroup::eventFilter(watched, event);
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[1];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(3);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeinstance<QObjectType>(c,watched,"qt.QObject"));
        args[2] = Value(makeqpointer<QEventType>(c,event,"qt.QEvent"));
        Value rval = _env->call(F, args);
        return (bool)(rval._bool);
    }
    else
    {
        return QActionGroup::eventFilter(watched, event);
    }
}

void MuQt_QActionGroup::customEvent(QEvent * event) 
{
    if (!_env) { QActionGroup::customEvent(event); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[2];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QEventType>(c,event,"qt.QEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QActionGroup::customEvent(event);
    }
}

void MuQt_QActionGroup::timerEvent(QTimerEvent * event) 
{
    if (!_env) { QActionGroup::timerEvent(event); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[3];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makeqpointer<QTimerEventType>(c,event,"qt.QTimerEvent"));
        Value rval = _env->call(F, args);
    }
    else
    {
        QActionGroup::timerEvent(event);
    }
}



//----------------------------------------------------------------------
//  Mu Type CONSTRUCTORS

QActionGroupType::QActionGroupType(Context* c, const char* name, Class* super, Class* super2)
: Class(c, name, vectorOf2(super, super2))
{
}

QActionGroupType::~QActionGroupType()
{
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

static Pointer
QActionGroup_QActionGroup_QObject(Thread& NODE_THREAD, Pointer obj)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    ClassInstance* widget = reinterpret_cast<ClassInstance*>(obj);

    if (!widget)
    {
        return 0;
    }
    else if (QActionGroup* w = object<QActionGroup>(widget))
    {
        QActionGroupType* type = 
            c->findSymbolOfTypeByQualifiedName<QActionGroupType>(c->internName("qt.QActionGroup"), false);
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
    NODE_RETURN( QActionGroup_QActionGroup_QObject(NODE_THREAD, NODE_ARG(0, Pointer)) );
}

Pointer qt_QActionGroup_QActionGroup_QActionGroup_QActionGroup_QObject(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_parent)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QObject * arg1 = object<QObject>(param_parent);
    setobject(param_this, new MuQt_QActionGroup(param_this, NODE_THREAD.process()->callEnv(), arg1));
    return param_this;
}

Pointer qt_QActionGroup_addAction_QAction_QActionGroup_QAction(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_action)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QActionGroup* arg0 = object<QActionGroup>(param_this);
    QAction * arg1 = object<QAction>(param_action);
    return makeinstance<QActionType>(c, arg0->addAction(arg1), "qt.QAction");
}

Pointer qt_QActionGroup_addAction_QAction_QActionGroup_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_text)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QActionGroup* arg0 = object<QActionGroup>(param_this);
    const QString  arg1 = qstring(param_text);
    return makeinstance<QActionType>(c, arg0->addAction(arg1), "qt.QAction");
}

Pointer qt_QActionGroup_addAction_QAction_QActionGroup_QIcon_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_icon, Pointer param_text)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QActionGroup* arg0 = object<QActionGroup>(param_this);
    const QIcon  arg1 = getqtype<QIconType>(param_icon);
    const QString  arg2 = qstring(param_text);
    return makeinstance<QActionType>(c, arg0->addAction(arg1, arg2), "qt.QAction");
}

Pointer qt_QActionGroup_checkedAction_QAction_QActionGroup(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QActionGroup* arg0 = object<QActionGroup>(param_this);
    return makeinstance<QActionType>(c, arg0->checkedAction(), "qt.QAction");
}

void qt_QActionGroup_removeAction_void_QActionGroup_QAction(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_action)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QActionGroup* arg0 = object<QActionGroup>(param_this);
    QAction * arg1 = object<QAction>(param_action);
    arg0->removeAction(arg1);
}

bool qt_QActionGroup_event_bool_QActionGroup_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_e)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QActionGroup* arg0 = object<QActionGroup>(param_this);
    QEvent * arg1 = getqpointer<QEventType>(param_e);
    return isMuQtObject(arg0) ? arg0->QActionGroup::event(arg1) : arg0->event(arg1);
}

bool qt_QActionGroup_eventFilter_bool_QActionGroup_QObject_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_watched, Pointer param_event)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QActionGroup* arg0 = object<QActionGroup>(param_this);
    QObject * arg1 = object<QObject>(param_watched);
    QEvent * arg2 = getqpointer<QEventType>(param_event);
    return isMuQtObject(arg0) ? arg0->QActionGroup::eventFilter(arg1, arg2) : arg0->eventFilter(arg1, arg2);
}

void qt_QActionGroup_customEvent_void_QActionGroup_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_event)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QActionGroup* arg0 = object<QActionGroup>(param_this);
    QEvent * arg1 = getqpointer<QEventType>(param_event);
    if (isMuQtObject(arg0)) ((MuQt_QActionGroup*)arg0)->customEvent_pub_parent(arg1);
    else ((MuQt_QActionGroup*)arg0)->customEvent_pub(arg1);
}

void qt_QActionGroup_timerEvent_void_QActionGroup_QTimerEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_event)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QActionGroup* arg0 = object<QActionGroup>(param_this);
    QTimerEvent * arg1 = getqpointer<QTimerEventType>(param_event);
    if (isMuQtObject(arg0)) ((MuQt_QActionGroup*)arg0)->timerEvent_pub_parent(arg1);
    else ((MuQt_QActionGroup*)arg0)->timerEvent_pub(arg1);
}


static NODE_IMPLEMENTATION(_n_QActionGroup0, Pointer)
{
    NODE_RETURN(qt_QActionGroup_QActionGroup_QActionGroup_QActionGroup_QObject(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_addAction0, Pointer)
{
    NODE_RETURN(qt_QActionGroup_addAction_QAction_QActionGroup_QAction(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_addAction1, Pointer)
{
    NODE_RETURN(qt_QActionGroup_addAction_QAction_QActionGroup_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_addAction2, Pointer)
{
    NODE_RETURN(qt_QActionGroup_addAction_QAction_QActionGroup_QIcon_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_checkedAction0, Pointer)
{
    NODE_RETURN(qt_QActionGroup_checkedAction_QAction_QActionGroup(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_removeAction0, void)
{
    qt_QActionGroup_removeAction_void_QActionGroup_QAction(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_event0, bool)
{
    NODE_RETURN(qt_QActionGroup_event_bool_QActionGroup_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_eventFilter0, bool)
{
    NODE_RETURN(qt_QActionGroup_eventFilter_bool_QActionGroup_QObject_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_customEvent0, void)
{
    qt_QActionGroup_customEvent_void_QActionGroup_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_timerEvent0, void)
{
    qt_QActionGroup_timerEvent_void_QActionGroup_QTimerEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}



void
QActionGroupType::load()
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
                            Compiled, QActionGroup_QActionGroup_QObject,
                            Return, ftn,
                            Parameters,
                            new Param(c, "object", "qt.QObject"),
                            End),

               EndArguments );

addSymbols(
    // enums
    // member functions
    new Function(c, "QActionGroup", _n_QActionGroup0, None, Compiled, qt_QActionGroup_QActionGroup_QActionGroup_QActionGroup_QObject, Return, "qt.QActionGroup", Parameters, new Param(c, "this", "qt.QActionGroup"), new Param(c, "parent", "qt.QObject"), End),
    // MISSING: actions ("QList<QAction *>"; QActionGroup this)
    new Function(c, "addAction", _n_addAction0, None, Compiled, qt_QActionGroup_addAction_QAction_QActionGroup_QAction, Return, "qt.QAction", Parameters, new Param(c, "this", "qt.QActionGroup"), new Param(c, "action", "qt.QAction"), End),
    new Function(c, "addAction", _n_addAction1, None, Compiled, qt_QActionGroup_addAction_QAction_QActionGroup_string, Return, "qt.QAction", Parameters, new Param(c, "this", "qt.QActionGroup"), new Param(c, "text", "string"), End),
    new Function(c, "addAction", _n_addAction2, None, Compiled, qt_QActionGroup_addAction_QAction_QActionGroup_QIcon_string, Return, "qt.QAction", Parameters, new Param(c, "this", "qt.QActionGroup"), new Param(c, "icon", "qt.QIcon"), new Param(c, "text", "string"), End),
    new Function(c, "checkedAction", _n_checkedAction0, None, Compiled, qt_QActionGroup_checkedAction_QAction_QActionGroup, Return, "qt.QAction", Parameters, new Param(c, "this", "qt.QActionGroup"), End),
    // PROP: isEnabled (bool; QActionGroup this)
    // PROP: isExclusive (bool; QActionGroup this)
    // PROP: isVisible (bool; QActionGroup this)
    new Function(c, "removeAction", _n_removeAction0, None, Compiled, qt_QActionGroup_removeAction_void_QActionGroup_QAction, Return, "void", Parameters, new Param(c, "this", "qt.QActionGroup"), new Param(c, "action", "qt.QAction"), End),
    _func[0] = new MemberFunction(c, "event", _n_event0, None, Compiled, qt_QActionGroup_event_bool_QActionGroup_QEvent, Return, "bool", Parameters, new Param(c, "this", "qt.QActionGroup"), new Param(c, "e", "qt.QEvent"), End),
    _func[1] = new MemberFunction(c, "eventFilter", _n_eventFilter0, None, Compiled, qt_QActionGroup_eventFilter_bool_QActionGroup_QObject_QEvent, Return, "bool", Parameters, new Param(c, "this", "qt.QActionGroup"), new Param(c, "watched", "qt.QObject"), new Param(c, "event", "qt.QEvent"), End),
    // MISSING: metaObject ("const QMetaObject *"; QActionGroup this)
    // MISSING: childEvent (void; QActionGroup this, "QChildEvent *" event) // protected
    // MISSING: connectNotify (void; QActionGroup this, "const QMetaMethod &" signal) // protected
    _func[2] = new MemberFunction(c, "customEvent", _n_customEvent0, None, Compiled, qt_QActionGroup_customEvent_void_QActionGroup_QEvent, Return, "void", Parameters, new Param(c, "this", "qt.QActionGroup"), new Param(c, "event", "qt.QEvent"), End),
    // MISSING: disconnectNotify (void; QActionGroup this, "const QMetaMethod &" signal) // protected
    _func[3] = new MemberFunction(c, "timerEvent", _n_timerEvent0, None, Compiled, qt_QActionGroup_timerEvent_void_QActionGroup_QTimerEvent, Return, "void", Parameters, new Param(c, "this", "qt.QActionGroup"), new Param(c, "event", "qt.QTimerEvent"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    EndArguments);
scope()->addSymbols(
    EndArguments);


    const char** propExclusions = 0;

    populate(this, QActionGroup::staticMetaObject, propExclusions);
}

} // Mu
