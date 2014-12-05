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
#include "QMimeDataType.h"
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
#include "QObjectType.h"
#include "QEventType.h"
#include "QUrlType.h"
#include "QVariantType.h"
#include "QTimerEventType.h"
#include "QByteArrayType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

//----------------------------------------------------------------------
//  INHERITABLE TYPE IMPLEMENTATION

// destructor
MuQt_QMimeData::~MuQt_QMimeData()
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

MuQt_QMimeData::MuQt_QMimeData(Pointer muobj, const CallEnvironment* ce) 
 : QMimeData()
{
    _env = ce;
    _obj = reinterpret_cast<ClassInstance*>(muobj);
    _obj->retainExternal();
    MuLangContext* c = (MuLangContext*)_env->context();
    _baseType = c->findSymbolOfTypeByQualifiedName<QMimeDataType>(c->internName("qt.QMimeData"));
}

QStringList MuQt_QMimeData::formats() const
{
    if (!_env) return QMimeData::formats();
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[0];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(1);
        args[0] = Value(Pointer(_obj));
        Value rval = _env->call(F, args);
        return qstringlist(rval._Pointer);
    }
    else
    {
        return QMimeData::formats();
    }
}

bool MuQt_QMimeData::hasFormat(const QString & mimeType) const
{
    if (!_env) return QMimeData::hasFormat(mimeType);
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[1];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(2);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makestring(c,mimeType));
        Value rval = _env->call(F, args);
        return (bool)(rval._bool);
    }
    else
    {
        return QMimeData::hasFormat(mimeType);
    }
}

QVariant MuQt_QMimeData::retrieveData(const QString & mimeType, QVariant::Type type) const
{
    if (!_env) return QMimeData::retrieveData(mimeType, type);
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[2];
    const MemberFunction* F = _obj->classType()->dynamicLookup(F0);
    if (F != F0) 
    {
        Function::ArgumentVector args(3);
        args[0] = Value(Pointer(_obj));
        args[1] = Value(makestring(c,mimeType));
        args[2] = Value(int(type));
        Value rval = _env->call(F, args);
        return getqtype<QVariantType>(rval._Pointer);
    }
    else
    {
        return QMimeData::retrieveData(mimeType, type);
    }
}

bool MuQt_QMimeData::event(QEvent * e) 
{
    if (!_env) return QMimeData::event(e);
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
        return QMimeData::event(e);
    }
}

bool MuQt_QMimeData::eventFilter(QObject * watched, QEvent * event) 
{
    if (!_env) return QMimeData::eventFilter(watched, event);
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[4];
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
        return QMimeData::eventFilter(watched, event);
    }
}

void MuQt_QMimeData::customEvent(QEvent * event) 
{
    if (!_env) { QMimeData::customEvent(event); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[5];
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
        QMimeData::customEvent(event);
    }
}

void MuQt_QMimeData::timerEvent(QTimerEvent * event) 
{
    if (!_env) { QMimeData::timerEvent(event); return; }
    MuLangContext* c = (MuLangContext*)_env->context();
    const MemberFunction* F0 = _baseType->_func[6];
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
        QMimeData::timerEvent(event);
    }
}



//----------------------------------------------------------------------
//  Mu Type CONSTRUCTORS

QMimeDataType::QMimeDataType(Context* c, const char* name, Class* super, Class* super2)
: Class(c, name, vectorOf2(super, super2))
{
}

QMimeDataType::~QMimeDataType()
{
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

static Pointer
QMimeData_QMimeData_QObject(Thread& NODE_THREAD, Pointer obj)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    ClassInstance* widget = reinterpret_cast<ClassInstance*>(obj);

    if (!widget)
    {
        return 0;
    }
    else if (QMimeData* w = object<QMimeData>(widget))
    {
        QMimeDataType* type = 
            c->findSymbolOfTypeByQualifiedName<QMimeDataType>(c->internName("qt.QMimeData"), false);
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
    NODE_RETURN( QMimeData_QMimeData_QObject(NODE_THREAD, NODE_ARG(0, Pointer)) );
}

Pointer qt_QMimeData_QMimeData_QMimeData_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    setobject(param_this, new MuQt_QMimeData(param_this, NODE_THREAD.process()->callEnv()));
    return param_this;
}

void qt_QMimeData_clear_void_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    arg0->clear();
}

Pointer qt_QMimeData_colorData_QVariant_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return makeqtype<QVariantType>(c,arg0->colorData(),"qt.QVariant");
}

Pointer qt_QMimeData_data_QByteArray_QMimeData_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_mimeType)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    const QString  arg1 = qstring(param_mimeType);
    return makeqtype<QByteArrayType>(c,arg0->data(arg1),"qt.QByteArray");
}

Pointer qt_QMimeData_formats_stringBSB_ESB__QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return isMuQtObject(arg0) ? makestringlist(c,arg0->QMimeData::formats()) : makestringlist(c,arg0->formats());
}

bool qt_QMimeData_hasColor_bool_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return arg0->hasColor();
}

bool qt_QMimeData_hasFormat_bool_QMimeData_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_mimeType)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    const QString  arg1 = qstring(param_mimeType);
    return isMuQtObject(arg0) ? arg0->QMimeData::hasFormat(arg1) : arg0->hasFormat(arg1);
}

bool qt_QMimeData_hasHtml_bool_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return arg0->hasHtml();
}

bool qt_QMimeData_hasImage_bool_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return arg0->hasImage();
}

bool qt_QMimeData_hasText_bool_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return arg0->hasText();
}

bool qt_QMimeData_hasUrls_bool_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return arg0->hasUrls();
}

Pointer qt_QMimeData_html_string_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return makestring(c,arg0->html());
}

Pointer qt_QMimeData_imageData_QVariant_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return makeqtype<QVariantType>(c,arg0->imageData(),"qt.QVariant");
}

void qt_QMimeData_removeFormat_void_QMimeData_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_mimeType)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    const QString  arg1 = qstring(param_mimeType);
    arg0->removeFormat(arg1);
}

void qt_QMimeData_setColorData_void_QMimeData_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_color)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    const QVariant  arg1 = getqtype<QVariantType>(param_color);
    arg0->setColorData(arg1);
}

void qt_QMimeData_setData_void_QMimeData_string_QByteArray(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_mimeType, Pointer param_data)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    const QString  arg1 = qstring(param_mimeType);
    const QByteArray  arg2 = getqtype<QByteArrayType>(param_data);
    arg0->setData(arg1, arg2);
}

void qt_QMimeData_setHtml_void_QMimeData_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_html)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    const QString  arg1 = qstring(param_html);
    arg0->setHtml(arg1);
}

void qt_QMimeData_setImageData_void_QMimeData_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_image)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    const QVariant  arg1 = getqtype<QVariantType>(param_image);
    arg0->setImageData(arg1);
}

void qt_QMimeData_setText_void_QMimeData_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_text)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    const QString  arg1 = qstring(param_text);
    arg0->setText(arg1);
}

void qt_QMimeData_setUrls_void_QMimeData_qt__QUrlBSB_ESB_(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_urls)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    const QList<QUrl>  arg1 = qtypelist<QUrl,QUrlType>(param_urls);
    arg0->setUrls(arg1);
}

Pointer qt_QMimeData_text_string_QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return makestring(c,arg0->text());
}

Pointer qt_QMimeData_urls_qt__QUrlBSB_ESB__QMimeData(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    return makeqtypelist<QUrl, QUrlType>(c,arg0->urls(),"qt.QUrl");
}

Pointer qt_QMimeData_retrieveData_QVariant_QMimeData_string_int(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_mimeType, int param_type)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    const QString  arg1 = qstring(param_mimeType);
    QVariant::Type arg2 = (QVariant::Type)(param_type);
    return isMuQtObject(arg0) ? makeqtype<QVariantType>(c,((MuQt_QMimeData*)arg0)->retrieveData_pub_parent(arg1, arg2),"qt.QVariant") : makeqtype<QVariantType>(c,((MuQt_QMimeData*)arg0)->retrieveData_pub(arg1, arg2),"qt.QVariant");
}

bool qt_QMimeData_event_bool_QMimeData_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_e)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    QEvent * arg1 = getqpointer<QEventType>(param_e);
    return isMuQtObject(arg0) ? arg0->QMimeData::event(arg1) : arg0->event(arg1);
}

bool qt_QMimeData_eventFilter_bool_QMimeData_QObject_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_watched, Pointer param_event)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    QObject * arg1 = object<QObject>(param_watched);
    QEvent * arg2 = getqpointer<QEventType>(param_event);
    return isMuQtObject(arg0) ? arg0->QMimeData::eventFilter(arg1, arg2) : arg0->eventFilter(arg1, arg2);
}

void qt_QMimeData_customEvent_void_QMimeData_QEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_event)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    QEvent * arg1 = getqpointer<QEventType>(param_event);
    if (isMuQtObject(arg0)) ((MuQt_QMimeData*)arg0)->customEvent_pub_parent(arg1);
    else ((MuQt_QMimeData*)arg0)->customEvent_pub(arg1);
}

void qt_QMimeData_timerEvent_void_QMimeData_QTimerEvent(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_event)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QMimeData* arg0 = object<QMimeData>(param_this);
    QTimerEvent * arg1 = getqpointer<QTimerEventType>(param_event);
    if (isMuQtObject(arg0)) ((MuQt_QMimeData*)arg0)->timerEvent_pub_parent(arg1);
    else ((MuQt_QMimeData*)arg0)->timerEvent_pub(arg1);
}


static NODE_IMPLEMENTATION(_n_QMimeData0, Pointer)
{
    NODE_RETURN(qt_QMimeData_QMimeData_QMimeData_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_clear0, void)
{
    qt_QMimeData_clear_void_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer));
}

static NODE_IMPLEMENTATION(_n_colorData0, Pointer)
{
    NODE_RETURN(qt_QMimeData_colorData_QVariant_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_data0, Pointer)
{
    NODE_RETURN(qt_QMimeData_data_QByteArray_QMimeData_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_formats0, Pointer)
{
    NODE_RETURN(qt_QMimeData_formats_stringBSB_ESB__QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_hasColor0, bool)
{
    NODE_RETURN(qt_QMimeData_hasColor_bool_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_hasFormat0, bool)
{
    NODE_RETURN(qt_QMimeData_hasFormat_bool_QMimeData_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_hasHtml0, bool)
{
    NODE_RETURN(qt_QMimeData_hasHtml_bool_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_hasImage0, bool)
{
    NODE_RETURN(qt_QMimeData_hasImage_bool_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_hasText0, bool)
{
    NODE_RETURN(qt_QMimeData_hasText_bool_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_hasUrls0, bool)
{
    NODE_RETURN(qt_QMimeData_hasUrls_bool_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_html0, Pointer)
{
    NODE_RETURN(qt_QMimeData_html_string_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_imageData0, Pointer)
{
    NODE_RETURN(qt_QMimeData_imageData_QVariant_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_removeFormat0, void)
{
    qt_QMimeData_removeFormat_void_QMimeData_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setColorData0, void)
{
    qt_QMimeData_setColorData_void_QMimeData_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setData0, void)
{
    qt_QMimeData_setData_void_QMimeData_string_QByteArray(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer));
}

static NODE_IMPLEMENTATION(_n_setHtml0, void)
{
    qt_QMimeData_setHtml_void_QMimeData_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setImageData0, void)
{
    qt_QMimeData_setImageData_void_QMimeData_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setText0, void)
{
    qt_QMimeData_setText_void_QMimeData_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setUrls0, void)
{
    qt_QMimeData_setUrls_void_QMimeData_qt__QUrlBSB_ESB_(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_text0, Pointer)
{
    NODE_RETURN(qt_QMimeData_text_string_QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_urls0, Pointer)
{
    NODE_RETURN(qt_QMimeData_urls_qt__QUrlBSB_ESB__QMimeData(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_retrieveData0, Pointer)
{
    NODE_RETURN(qt_QMimeData_retrieveData_QVariant_QMimeData_string_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, int)));
}

static NODE_IMPLEMENTATION(_n_event0, bool)
{
    NODE_RETURN(qt_QMimeData_event_bool_QMimeData_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_eventFilter0, bool)
{
    NODE_RETURN(qt_QMimeData_eventFilter_bool_QMimeData_QObject_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_customEvent0, void)
{
    qt_QMimeData_customEvent_void_QMimeData_QEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_timerEvent0, void)
{
    qt_QMimeData_timerEvent_void_QMimeData_QTimerEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}



void
QMimeDataType::load()
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
                            Compiled, QMimeData_QMimeData_QObject,
                            Return, ftn,
                            Parameters,
                            new Param(c, "object", "qt.QObject"),
                            End),

               EndArguments );

addSymbols(
    // enums
    // member functions
    new Function(c, "QMimeData", _n_QMimeData0, None, Compiled, qt_QMimeData_QMimeData_QMimeData_QMimeData, Return, "qt.QMimeData", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "clear", _n_clear0, None, Compiled, qt_QMimeData_clear_void_QMimeData, Return, "void", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "colorData", _n_colorData0, None, Compiled, qt_QMimeData_colorData_QVariant_QMimeData, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "data", _n_data0, None, Compiled, qt_QMimeData_data_QByteArray_QMimeData_string, Return, "qt.QByteArray", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "mimeType", "string"), End),
    _func[0] = new MemberFunction(c, "formats", _n_formats0, None, Compiled, qt_QMimeData_formats_stringBSB_ESB__QMimeData, Return, "string[]", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "hasColor", _n_hasColor0, None, Compiled, qt_QMimeData_hasColor_bool_QMimeData, Return, "bool", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    _func[1] = new MemberFunction(c, "hasFormat", _n_hasFormat0, None, Compiled, qt_QMimeData_hasFormat_bool_QMimeData_string, Return, "bool", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "mimeType", "string"), End),
    new Function(c, "hasHtml", _n_hasHtml0, None, Compiled, qt_QMimeData_hasHtml_bool_QMimeData, Return, "bool", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "hasImage", _n_hasImage0, None, Compiled, qt_QMimeData_hasImage_bool_QMimeData, Return, "bool", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "hasText", _n_hasText0, None, Compiled, qt_QMimeData_hasText_bool_QMimeData, Return, "bool", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "hasUrls", _n_hasUrls0, None, Compiled, qt_QMimeData_hasUrls_bool_QMimeData, Return, "bool", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "html", _n_html0, None, Compiled, qt_QMimeData_html_string_QMimeData, Return, "string", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "imageData", _n_imageData0, None, Compiled, qt_QMimeData_imageData_QVariant_QMimeData, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "removeFormat", _n_removeFormat0, None, Compiled, qt_QMimeData_removeFormat_void_QMimeData_string, Return, "void", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "mimeType", "string"), End),
    new Function(c, "setColorData", _n_setColorData0, None, Compiled, qt_QMimeData_setColorData_void_QMimeData_QVariant, Return, "void", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "color", "qt.QVariant"), End),
    new Function(c, "setData", _n_setData0, None, Compiled, qt_QMimeData_setData_void_QMimeData_string_QByteArray, Return, "void", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "mimeType", "string"), new Param(c, "data", "qt.QByteArray"), End),
    new Function(c, "setHtml", _n_setHtml0, None, Compiled, qt_QMimeData_setHtml_void_QMimeData_string, Return, "void", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "html", "string"), End),
    new Function(c, "setImageData", _n_setImageData0, None, Compiled, qt_QMimeData_setImageData_void_QMimeData_QVariant, Return, "void", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "image", "qt.QVariant"), End),
    new Function(c, "setText", _n_setText0, None, Compiled, qt_QMimeData_setText_void_QMimeData_string, Return, "void", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "text", "string"), End),
    new Function(c, "setUrls", _n_setUrls0, None, Compiled, qt_QMimeData_setUrls_void_QMimeData_qt__QUrlBSB_ESB_, Return, "void", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "urls", "qt.QUrl[]"), End),
    new Function(c, "text", _n_text0, None, Compiled, qt_QMimeData_text_string_QMimeData, Return, "string", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    new Function(c, "urls", _n_urls0, None, Compiled, qt_QMimeData_urls_qt__QUrlBSB_ESB__QMimeData, Return, "qt.QUrl[]", Parameters, new Param(c, "this", "qt.QMimeData"), End),
    _func[2] = new MemberFunction(c, "retrieveData", _n_retrieveData0, None, Compiled, qt_QMimeData_retrieveData_QVariant_QMimeData_string_int, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "mimeType", "string"), new Param(c, "type", "int"), End),
    _func[3] = new MemberFunction(c, "event", _n_event0, None, Compiled, qt_QMimeData_event_bool_QMimeData_QEvent, Return, "bool", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "e", "qt.QEvent"), End),
    _func[4] = new MemberFunction(c, "eventFilter", _n_eventFilter0, None, Compiled, qt_QMimeData_eventFilter_bool_QMimeData_QObject_QEvent, Return, "bool", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "watched", "qt.QObject"), new Param(c, "event", "qt.QEvent"), End),
    // MISSING: metaObject ("const QMetaObject *"; QMimeData this)
    // MISSING: childEvent (void; QMimeData this, "QChildEvent *" event) // protected
    // MISSING: connectNotify (void; QMimeData this, "const QMetaMethod &" signal) // protected
    _func[5] = new MemberFunction(c, "customEvent", _n_customEvent0, None, Compiled, qt_QMimeData_customEvent_void_QMimeData_QEvent, Return, "void", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "event", "qt.QEvent"), End),
    // MISSING: disconnectNotify (void; QMimeData this, "const QMetaMethod &" signal) // protected
    _func[6] = new MemberFunction(c, "timerEvent", _n_timerEvent0, None, Compiled, qt_QMimeData_timerEvent_void_QMimeData_QTimerEvent, Return, "void", Parameters, new Param(c, "this", "qt.QMimeData"), new Param(c, "event", "qt.QTimerEvent"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    EndArguments);
scope()->addSymbols(
    EndArguments);


    const char** propExclusions = 0;

    populate(this, QMimeData::staticMetaObject, propExclusions);
}

} // Mu
