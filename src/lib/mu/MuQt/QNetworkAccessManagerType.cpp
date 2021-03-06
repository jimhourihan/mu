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
#include "QNetworkAccessManagerType.h"
#include <QtGui/QtGui>
#include <QtSvg/QtSvg>
#include <QtNetwork/QtNetwork>
#include <QtWebKit/QtWebKit>
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
#include "QObjectType.h"
#include "QNetworkCookieJarType.h"
#include "QEventType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

//----------------------------------------------------------------------
//  INHERITABLE TYPE IMPLEMENTATION

// destructor
MuQt_QNetworkAccessManager::~MuQt_QNetworkAccessManager()
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

MuQt_QNetworkAccessManager::MuQt_QNetworkAccessManager(Pointer muobj, const CallEnvironment* ce, QObject * parent) 
 : RvNetworkAccessManager(parent)
{
    _env = ce;
    _obj = reinterpret_cast<ClassInstance*>(muobj);
    _obj->retainExternal();
    MuLangContext* c = (MuLangContext*)_env->context();
    _baseType = c->findSymbolOfTypeByQualifiedName<QNetworkAccessManagerType>(c->internName("qt.QNetworkAccessManager"));
}

bool MuQt_QNetworkAccessManager::event(QEvent * e) 
{
    if (!_env) return QNetworkAccessManager::event(e);
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
        return QNetworkAccessManager::event(e);
    }
}

bool MuQt_QNetworkAccessManager::eventFilter(QObject * watched, QEvent * event) 
{
    if (!_env) return QNetworkAccessManager::eventFilter(watched, event);
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
        return QNetworkAccessManager::eventFilter(watched, event);
    }
}

void MuQt_QNetworkAccessManager::customEvent(QEvent * event) 
{
    if (!_env) { QNetworkAccessManager::customEvent(event); return; }
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
        QNetworkAccessManager::customEvent(event);
    }
}

void MuQt_QNetworkAccessManager::timerEvent(QTimerEvent * event) 
{
    if (!_env) { QNetworkAccessManager::timerEvent(event); return; }
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
        QNetworkAccessManager::timerEvent(event);
    }
}



//----------------------------------------------------------------------
//  Mu Type CONSTRUCTORS

QNetworkAccessManagerType::QNetworkAccessManagerType(Context* c, const char* name, Class* super, Class* super2)
: Class(c, name, vectorOf2(super, super2))
{
}

QNetworkAccessManagerType::~QNetworkAccessManagerType()
{
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

static Pointer
QNetworkAccessManager_QNetworkAccessManager_QObject(Thread& NODE_THREAD, Pointer obj)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    ClassInstance* widget = reinterpret_cast<ClassInstance*>(obj);

    if (!widget)
    {
        return 0;
    }
    else if (QNetworkAccessManager* w = object<QNetworkAccessManager>(widget))
    {
        QNetworkAccessManagerType* type = 
            c->findSymbolOfTypeByQualifiedName<QNetworkAccessManagerType>(c->internName("qt.QNetworkAccessManager"), false);
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
    NODE_RETURN( QNetworkAccessManager_QNetworkAccessManager_QObject(NODE_THREAD, NODE_ARG(0, Pointer)) );
}

Pointer qt_QNetworkAccessManager_QNetworkAccessManager_QNetworkAccessManager_QNetworkAccessManager_QObject(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_parent)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QObject * arg1 = object<QObject>(param_parent);
    setobject(param_this, new MuQt_QNetworkAccessManager(param_this, NODE_THREAD.process()->callEnv(), arg1));
    return param_this;
}

Pointer qt_QNetworkAccessManager_cookieJar_QNetworkCookieJar_QNetworkAccessManager(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QNetworkAccessManager* arg0 = object<QNetworkAccessManager>(param_this);
    return makeinstance<QNetworkCookieJarType>(c, arg0->cookieJar(), "qt.QNetworkCookieJar");
}

void qt_QNetworkAccessManager_setCookieJar_void_QNetworkAccessManager_QNetworkCookieJar(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_cookieJar)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QNetworkAccessManager* arg0 = object<QNetworkAccessManager>(param_this);
    QNetworkCookieJar * arg1 = object<QNetworkCookieJar>(param_cookieJar);
    arg0->setCookieJar(arg1);
}

bool qt_QNetworkAccessManager_event_bool_QNetworkAccessManager_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_e)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QNetworkAccessManager* arg0 = object<QNetworkAccessManager>(param_this);
    QEvent * arg1 = getqpointer<QEventType>(param_e);
    return isMuQtObject(arg0) ? arg0->QNetworkAccessManager::event(arg1) : arg0->event(arg1);
}

bool qt_QNetworkAccessManager_eventFilter_bool_QNetworkAccessManager_QObject_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_watched, Pointer param_event)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QNetworkAccessManager* arg0 = object<QNetworkAccessManager>(param_this);
    QObject * arg1 = object<QObject>(param_watched);
    QEvent * arg2 = getqpointer<QEventType>(param_event);
    return isMuQtObject(arg0) ? arg0->QNetworkAccessManager::eventFilter(arg1, arg2) : arg0->eventFilter(arg1, arg2);
}

void qt_QNetworkAccessManager_customEvent_void_QNetworkAccessManager_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_event)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QNetworkAccessManager* arg0 = object<QNetworkAccessManager>(param_this);
    QEvent * arg1 = getqpointer<QEventType>(param_event);
    if (isMuQtObject(arg0)) ((MuQt_QNetworkAccessManager*)arg0)->customEvent_pub_parent(arg1);
    else ((MuQt_QNetworkAccessManager*)arg0)->customEvent_pub(arg1);
}

void qt_QNetworkAccessManager_timerEvent_void_QNetworkAccessManager_QTimerEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_event)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QNetworkAccessManager* arg0 = object<QNetworkAccessManager>(param_this);
    QTimerEvent * arg1 = getqpointer<QTimerEventType>(param_event);
    if (isMuQtObject(arg0)) ((MuQt_QNetworkAccessManager*)arg0)->timerEvent_pub_parent(arg1);
    else ((MuQt_QNetworkAccessManager*)arg0)->timerEvent_pub(arg1);
}


static NODE_IMPLEMENTATION(_n_QNetworkAccessManager0, Pointer)
{
    NODE_RETURN(qt_QNetworkAccessManager_QNetworkAccessManager_QNetworkAccessManager_QNetworkAccessManager_QObject(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_cookieJar0, Pointer)
{
    NODE_RETURN(qt_QNetworkAccessManager_cookieJar_QNetworkCookieJar_QNetworkAccessManager(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_setCookieJar0, void)
{
    qt_QNetworkAccessManager_setCookieJar_void_QNetworkAccessManager_QNetworkCookieJar(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_event0, bool)
{
    NODE_RETURN(qt_QNetworkAccessManager_event_bool_QNetworkAccessManager_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_eventFilter0, bool)
{
    NODE_RETURN(qt_QNetworkAccessManager_eventFilter_bool_QNetworkAccessManager_QObject_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_customEvent0, void)
{
    qt_QNetworkAccessManager_customEvent_void_QNetworkAccessManager_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_timerEvent0, void)
{
    qt_QNetworkAccessManager_timerEvent_void_QNetworkAccessManager_QTimerEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}



void
QNetworkAccessManagerType::load()
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
                            Compiled, QNetworkAccessManager_QNetworkAccessManager_QObject,
                            Return, ftn,
                            Parameters,
                            new Param(c, "object", "qt.QObject"),
                            End),

               EndArguments );

addSymbols(
    // enums
    // member functions
    new Function(c, "QNetworkAccessManager", _n_QNetworkAccessManager0, None, Compiled, qt_QNetworkAccessManager_QNetworkAccessManager_QNetworkAccessManager_QNetworkAccessManager_QObject, Return, "qt.QNetworkAccessManager", Parameters, new Param(c, "this", "qt.QNetworkAccessManager"), new Param(c, "parent", "qt.QObject"), End),
    // MISSING: activeConfiguration ("QNetworkConfiguration"; QNetworkAccessManager this)
    // MISSING: cache ("QAbstractNetworkCache *"; QNetworkAccessManager this)
    // MISSING: configuration ("QNetworkConfiguration"; QNetworkAccessManager this)
    new Function(c, "cookieJar", _n_cookieJar0, None, Compiled, qt_QNetworkAccessManager_cookieJar_QNetworkCookieJar_QNetworkAccessManager, Return, "qt.QNetworkCookieJar", Parameters, new Param(c, "this", "qt.QNetworkAccessManager"), End),
    // MISSING: deleteResource (QNetworkReply; QNetworkAccessManager this, "const QNetworkRequest &" request)
    // MISSING: get (QNetworkReply; QNetworkAccessManager this, "const QNetworkRequest &" request)
    // MISSING: head (QNetworkReply; QNetworkAccessManager this, "const QNetworkRequest &" request)
    // PROP: networkAccessible (flags QNetworkAccessManager::NetworkAccessibility; QNetworkAccessManager this)
    // MISSING: post (QNetworkReply; QNetworkAccessManager this, "const QNetworkRequest &" request, QIODevice data)
    // MISSING: post (QNetworkReply; QNetworkAccessManager this, "const QNetworkRequest &" request, QByteArray data)
    // MISSING: post (QNetworkReply; QNetworkAccessManager this, "const QNetworkRequest &" request, "QHttpMultiPart *" multiPart)
    // MISSING: proxy ("QNetworkProxy"; QNetworkAccessManager this)
    // MISSING: proxyFactory ("QNetworkProxyFactory *"; QNetworkAccessManager this)
    // MISSING: put (QNetworkReply; QNetworkAccessManager this, "const QNetworkRequest &" request, QIODevice data)
    // MISSING: put (QNetworkReply; QNetworkAccessManager this, "const QNetworkRequest &" request, "QHttpMultiPart *" multiPart)
    // MISSING: put (QNetworkReply; QNetworkAccessManager this, "const QNetworkRequest &" request, QByteArray data)
    // MISSING: sendCustomRequest (QNetworkReply; QNetworkAccessManager this, "const QNetworkRequest &" request, QByteArray verb, QIODevice data)
    // MISSING: setCache (void; QNetworkAccessManager this, "QAbstractNetworkCache *" cache)
    // MISSING: setConfiguration (void; QNetworkAccessManager this, "const QNetworkConfiguration &" config)
    new Function(c, "setCookieJar", _n_setCookieJar0, None, Compiled, qt_QNetworkAccessManager_setCookieJar_void_QNetworkAccessManager_QNetworkCookieJar, Return, "void", Parameters, new Param(c, "this", "qt.QNetworkAccessManager"), new Param(c, "cookieJar", "qt.QNetworkCookieJar"), End),
    // PROP: setNetworkAccessible (void; QNetworkAccessManager this, flags QNetworkAccessManager::NetworkAccessibility accessible)
    // MISSING: setProxy (void; QNetworkAccessManager this, "const QNetworkProxy &" proxy)
    // MISSING: setProxyFactory (void; QNetworkAccessManager this, "QNetworkProxyFactory *" factory)
    // MISSING: createRequest (QNetworkReply; QNetworkAccessManager this, flags QNetworkAccessManager::Operation op, "const QNetworkRequest &" req, QIODevice outgoingData) // protected
    _func[0] = new MemberFunction(c, "event", _n_event0, None, Compiled, qt_QNetworkAccessManager_event_bool_QNetworkAccessManager_QEvent, Return, "bool", Parameters, new Param(c, "this", "qt.QNetworkAccessManager"), new Param(c, "e", "qt.QEvent"), End),
    _func[1] = new MemberFunction(c, "eventFilter", _n_eventFilter0, None, Compiled, qt_QNetworkAccessManager_eventFilter_bool_QNetworkAccessManager_QObject_QEvent, Return, "bool", Parameters, new Param(c, "this", "qt.QNetworkAccessManager"), new Param(c, "watched", "qt.QObject"), new Param(c, "event", "qt.QEvent"), End),
    // MISSING: metaObject ("const QMetaObject *"; QNetworkAccessManager this)
    // MISSING: childEvent (void; QNetworkAccessManager this, "QChildEvent *" event) // protected
    // MISSING: connectNotify (void; QNetworkAccessManager this, "const char *" signal) // protected
    _func[2] = new MemberFunction(c, "customEvent", _n_customEvent0, None, Compiled, qt_QNetworkAccessManager_customEvent_void_QNetworkAccessManager_QEvent, Return, "void", Parameters, new Param(c, "this", "qt.QNetworkAccessManager"), new Param(c, "event", "qt.QEvent"), End),
    // MISSING: disconnectNotify (void; QNetworkAccessManager this, "const char *" signal) // protected
    _func[3] = new MemberFunction(c, "timerEvent", _n_timerEvent0, None, Compiled, qt_QNetworkAccessManager_timerEvent_void_QNetworkAccessManager_QTimerEvent, Return, "void", Parameters, new Param(c, "this", "qt.QNetworkAccessManager"), new Param(c, "event", "qt.QTimerEvent"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    EndArguments);
scope()->addSymbols(
    EndArguments);


    const char** propExclusions = 0;

    populate(this, QNetworkAccessManager::staticMetaObject, propExclusions);
}

} // Mu
