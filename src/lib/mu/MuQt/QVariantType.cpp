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
#include "QVariantType.h"
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
#include "QSizeType.h"
#include "QDateType.h"
#include "QRectType.h"
#include "QRectFType.h"
#include "QDateTimeType.h"
#include "QPointFType.h"
#include "QUrlType.h"
#include "QPointType.h"
#include "QRegExpType.h"
#include "QTimeType.h"
#include "QByteArrayType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

QVariantType::Instance::Instance(const Class* c) : ClassInstance(c)
{
}

QVariantType::QVariantType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QVariantType::~QVariantType()
{
}

static NODE_IMPLEMENTATION(__allocate, Pointer)
{
    QVariantType::Instance* i = new QVariantType::Instance((Class*)NODE_THIS.type());
    QVariantType::registerFinalizer(i);
    NODE_RETURN(i);
}

void 
QVariantType::registerFinalizer (void* o)
{
    GC_register_finalizer(o, QVariantType::finalizer, 0, 0, 0);
}

void 
QVariantType::finalizer (void* obj, void* data)
{
    QVariantType::Instance* i = reinterpret_cast<QVariantType::Instance*>(obj);
    delete i;
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

Pointer qt_QVariant_QVariant_QVariant_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    setqtype<QVariantType>(param_this,QVariant());
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QRegExp(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_regExp)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QRegExp  arg1 = getqtype<QRegExpType>(param_regExp);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    int arg1 = (int)(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_bool(Mu::Thread& NODE_THREAD, Pointer param_this, bool param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    bool arg1 = (bool)(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_double(Mu::Thread& NODE_THREAD, Pointer param_this, double param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    double arg1 = (double)(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QByteArray(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QByteArray  arg1 = getqtype<QByteArrayType>(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QString  arg1 = qstring(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_stringBSB_ESB_(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QStringList  arg1 = qstringlist(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QDate(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QDate  arg1 = getqtype<QDateType>(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QTime(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QTime  arg1 = getqtype<QTimeType>(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QDateTime(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QDateTime  arg1 = getqtype<QDateTimeType>(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QSize(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QSize  arg1 = getqtype<QSizeType>(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QPoint(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QPoint  arg1 = getqtype<QPointType>(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QPointF(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QPointF  arg1 = getqtype<QPointFType>(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QRect(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QRect  arg1 = getqtype<QRectType>(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QRectF(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QRectF  arg1 = getqtype<QRectFType>(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

Pointer qt_QVariant_QVariant_QVariant_QVariant_QUrl(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_val)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QUrl  arg1 = getqtype<QUrlType>(param_val);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}

void qt_QVariant_clear_void_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QVariant& arg0 = getqtype<QVariantType>(param_this);
    arg0.clear();
    setqtype<QVariantType>(param_this,arg0);
}

bool qt_QVariant_convert_bool_QVariant_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_t)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QVariant& arg0 = getqtype<QVariantType>(param_this);
    QVariant::Type arg1 = (QVariant::Type)(param_t);
    return arg0.convert(arg1);
}

bool qt_QVariant_isNull_bool_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return arg0.isNull();
}

bool qt_QVariant_isValid_bool_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return arg0.isValid();
}

void qt_QVariant_swap_void_QVariant_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_other)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QVariant& arg0 = getqtype<QVariantType>(param_this);
    QVariant  arg1 = getqtype<QVariantType>(param_other);
    arg0.swap(arg1);
    setqtype<QVariantType>(param_this,arg0);
}

bool qt_QVariant_toBool_bool_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return arg0.toBool();
}

Pointer qt_QVariant_toByteArray_QByteArray_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QByteArrayType>(c,arg0.toByteArray(),"qt.QByteArray");
}

Pointer qt_QVariant_toDate_QDate_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QDateType>(c,arg0.toDate(),"qt.QDate");
}

Pointer qt_QVariant_toDateTime_QDateTime_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QDateTimeType>(c,arg0.toDateTime(),"qt.QDateTime");
}

Pointer qt_QVariant_toPoint_QPoint_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QPointType>(c,arg0.toPoint(),"qt.QPoint");
}

Pointer qt_QVariant_toPointF_QPointF_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QPointFType>(c,arg0.toPointF(),"qt.QPointF");
}

Pointer qt_QVariant_toRect_QRect_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QRectType>(c,arg0.toRect(),"qt.QRect");
}

Pointer qt_QVariant_toRectF_QRectF_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QRectFType>(c,arg0.toRectF(),"qt.QRectF");
}

Pointer qt_QVariant_toRegExp_QRegExp_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QRegExpType>(c,arg0.toRegExp(),"qt.QRegExp");
}

Pointer qt_QVariant_toSize_QSize_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QSizeType>(c,arg0.toSize(),"qt.QSize");
}

Pointer qt_QVariant_toString_string_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makestring(c,arg0.toString());
}

Pointer qt_QVariant_toStringList_stringBSB_ESB__QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makestringlist(c,arg0.toStringList());
}

Pointer qt_QVariant_toTime_QTime_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QTimeType>(c,arg0.toTime(),"qt.QTime");
}

Pointer qt_QVariant_toUrl_QUrl_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return makeqtype<QUrlType>(c,arg0.toUrl(),"qt.QUrl");
}

int qt_QVariant_type_int_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return int(arg0.type());
}

int qt_QVariant_userType_int_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    return arg0.userType();
}

bool qt_QVariant_operatorBang_EQ__bool_QVariant_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_v)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    const QVariant  arg1 = getqtype<QVariantType>(param_v);
    return arg0.operator!=(arg1);
}

bool qt_QVariant_operatorEQ_EQ__bool_QVariant_QVariant(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_v)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QVariant& arg0 = getqtype<QVariantType>(param_this);
    const QVariant  arg1 = getqtype<QVariantType>(param_v);
    return arg0.operator==(arg1);
}


static NODE_IMPLEMENTATION(_n_QVariant0, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant2, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QRegExp(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant7, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int)));
}

static NODE_IMPLEMENTATION(_n_QVariant11, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_bool(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, bool)));
}

static NODE_IMPLEMENTATION(_n_QVariant12, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_double(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, double)));
}

static NODE_IMPLEMENTATION(_n_QVariant15, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QByteArray(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant17, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant19, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_stringBSB_ESB_(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant21, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QDate(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant22, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QTime(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant23, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QDateTime(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant27, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QSize(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant29, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QPoint(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant30, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QPointF(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant33, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QRect(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant34, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QRectF(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QVariant35, Pointer)
{
    NODE_RETURN(qt_QVariant_QVariant_QVariant_QVariant_QUrl(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_clear0, void)
{
    qt_QVariant_clear_void_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer));
}

static NODE_IMPLEMENTATION(_n_convert0, bool)
{
    NODE_RETURN(qt_QVariant_convert_bool_QVariant_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int)));
}

static NODE_IMPLEMENTATION(_n_isNull0, bool)
{
    NODE_RETURN(qt_QVariant_isNull_bool_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_isValid0, bool)
{
    NODE_RETURN(qt_QVariant_isValid_bool_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_swap0, void)
{
    qt_QVariant_swap_void_QVariant_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_toBool0, bool)
{
    NODE_RETURN(qt_QVariant_toBool_bool_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toByteArray0, Pointer)
{
    NODE_RETURN(qt_QVariant_toByteArray_QByteArray_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toDate0, Pointer)
{
    NODE_RETURN(qt_QVariant_toDate_QDate_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toDateTime0, Pointer)
{
    NODE_RETURN(qt_QVariant_toDateTime_QDateTime_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toPoint0, Pointer)
{
    NODE_RETURN(qt_QVariant_toPoint_QPoint_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toPointF0, Pointer)
{
    NODE_RETURN(qt_QVariant_toPointF_QPointF_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toRect0, Pointer)
{
    NODE_RETURN(qt_QVariant_toRect_QRect_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toRectF0, Pointer)
{
    NODE_RETURN(qt_QVariant_toRectF_QRectF_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toRegExp0, Pointer)
{
    NODE_RETURN(qt_QVariant_toRegExp_QRegExp_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toSize0, Pointer)
{
    NODE_RETURN(qt_QVariant_toSize_QSize_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toString0, Pointer)
{
    NODE_RETURN(qt_QVariant_toString_string_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toStringList0, Pointer)
{
    NODE_RETURN(qt_QVariant_toStringList_stringBSB_ESB__QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toTime0, Pointer)
{
    NODE_RETURN(qt_QVariant_toTime_QTime_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_toUrl0, Pointer)
{
    NODE_RETURN(qt_QVariant_toUrl_QUrl_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_type0, int)
{
    NODE_RETURN(qt_QVariant_type_int_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_userType0, int)
{
    NODE_RETURN(qt_QVariant_userType_int_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorBang_EQ_0, bool)
{
    NODE_RETURN(qt_QVariant_operatorBang_EQ__bool_QVariant_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorEQ_EQ_0, bool)
{
    NODE_RETURN(qt_QVariant_operatorEQ_EQ__bool_QVariant_QVariant(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}



static int
QVariant_toInt_int(Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QVariant arg0 = getqtype<QVariantType>(param_this);
    return arg0.toInt();
}

static NODE_IMPLEMENTATION(toInt, int)
{
    NODE_RETURN(QVariant_toInt_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

void
QVariantType::load()
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
    new Alias(c, "Type", "int"),
      new SymbolicConstant(c, "Invalid", "int", Value(int(QVariant::Invalid))),
      new SymbolicConstant(c, "BitArray", "int", Value(int(QVariant::BitArray))),
      new SymbolicConstant(c, "Bitmap", "int", Value(int(QVariant::Bitmap))),
      new SymbolicConstant(c, "Bool", "int", Value(int(QVariant::Bool))),
      new SymbolicConstant(c, "Brush", "int", Value(int(QVariant::Brush))),
      new SymbolicConstant(c, "ByteArray", "int", Value(int(QVariant::ByteArray))),
      new SymbolicConstant(c, "Char", "int", Value(int(QVariant::Char))),
      new SymbolicConstant(c, "Color", "int", Value(int(QVariant::Color))),
      new SymbolicConstant(c, "Cursor", "int", Value(int(QVariant::Cursor))),
      new SymbolicConstant(c, "Date", "int", Value(int(QVariant::Date))),
      new SymbolicConstant(c, "DateTime", "int", Value(int(QVariant::DateTime))),
      new SymbolicConstant(c, "Double", "int", Value(int(QVariant::Double))),
      new SymbolicConstant(c, "EasingCurve", "int", Value(int(QVariant::EasingCurve))),
      new SymbolicConstant(c, "Font", "int", Value(int(QVariant::Font))),
      new SymbolicConstant(c, "Hash", "int", Value(int(QVariant::Hash))),
      new SymbolicConstant(c, "Icon", "int", Value(int(QVariant::Icon))),
      new SymbolicConstant(c, "Image", "int", Value(int(QVariant::Image))),
      new SymbolicConstant(c, "Int", "int", Value(int(QVariant::Int))),
      new SymbolicConstant(c, "KeySequence", "int", Value(int(QVariant::KeySequence))),
      new SymbolicConstant(c, "Line", "int", Value(int(QVariant::Line))),
      new SymbolicConstant(c, "LineF", "int", Value(int(QVariant::LineF))),
      new SymbolicConstant(c, "List", "int", Value(int(QVariant::List))),
      new SymbolicConstant(c, "Locale", "int", Value(int(QVariant::Locale))),
      new SymbolicConstant(c, "LongLong", "int", Value(int(QVariant::LongLong))),
      new SymbolicConstant(c, "Map", "int", Value(int(QVariant::Map))),
      new SymbolicConstant(c, "Matrix", "int", Value(int(QVariant::Matrix))),
      new SymbolicConstant(c, "Transform", "int", Value(int(QVariant::Transform))),
      new SymbolicConstant(c, "Matrix4x4", "int", Value(int(QVariant::Matrix4x4))),
      new SymbolicConstant(c, "Palette", "int", Value(int(QVariant::Palette))),
      new SymbolicConstant(c, "Pen", "int", Value(int(QVariant::Pen))),
      new SymbolicConstant(c, "Pixmap", "int", Value(int(QVariant::Pixmap))),
      new SymbolicConstant(c, "Point", "int", Value(int(QVariant::Point))),
      new SymbolicConstant(c, "PointF", "int", Value(int(QVariant::PointF))),
      new SymbolicConstant(c, "Polygon", "int", Value(int(QVariant::Polygon))),
      new SymbolicConstant(c, "Quaternion", "int", Value(int(QVariant::Quaternion))),
      new SymbolicConstant(c, "Rect", "int", Value(int(QVariant::Rect))),
      new SymbolicConstant(c, "RectF", "int", Value(int(QVariant::RectF))),
      new SymbolicConstant(c, "RegExp", "int", Value(int(QVariant::RegExp))),
      new SymbolicConstant(c, "Region", "int", Value(int(QVariant::Region))),
      new SymbolicConstant(c, "Size", "int", Value(int(QVariant::Size))),
      new SymbolicConstant(c, "SizeF", "int", Value(int(QVariant::SizeF))),
      new SymbolicConstant(c, "SizePolicy", "int", Value(int(QVariant::SizePolicy))),
      new SymbolicConstant(c, "String", "int", Value(int(QVariant::String))),
      new SymbolicConstant(c, "StringList", "int", Value(int(QVariant::StringList))),
      new SymbolicConstant(c, "TextFormat", "int", Value(int(QVariant::TextFormat))),
      new SymbolicConstant(c, "TextLength", "int", Value(int(QVariant::TextLength))),
      new SymbolicConstant(c, "Time", "int", Value(int(QVariant::Time))),
      new SymbolicConstant(c, "UInt", "int", Value(int(QVariant::UInt))),
      new SymbolicConstant(c, "ULongLong", "int", Value(int(QVariant::ULongLong))),
      new SymbolicConstant(c, "Url", "int", Value(int(QVariant::Url))),
      new SymbolicConstant(c, "Vector2D", "int", Value(int(QVariant::Vector2D))),
      new SymbolicConstant(c, "Vector3D", "int", Value(int(QVariant::Vector3D))),
      new SymbolicConstant(c, "Vector4D", "int", Value(int(QVariant::Vector4D))),
      new SymbolicConstant(c, "UserType", "int", Value(int(QVariant::UserType))),
    EndArguments);

addSymbols(
    // enums
    // member functions
    new Function(c, "QVariant", _n_QVariant0, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), End),
    // MISSING: QVariant (QVariant; QVariant this, "const QLocale &" l)
    new Function(c, "QVariant", _n_QVariant2, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QRegExp, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "regExp", "qt.QRegExp"), End),
    // MISSING: QVariant (QVariant; QVariant this, "const QEasingCurve &" val)
    // MISSING: QVariant (QVariant; QVariant this, int typeOrUserType, "const void *" copy)
    // MISSING: QVariant (QVariant; QVariant this, QVariant p)
    // MISSING: QVariant (QVariant; QVariant this, "QDataStream &" s)
    new Function(c, "QVariant", _n_QVariant7, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_int, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "int"), End),
    // MISSING: QVariant (QVariant; QVariant this, int val)
    // MISSING: QVariant (QVariant; QVariant this, "qlonglong" val)
    // MISSING: QVariant (QVariant; QVariant this, "qulonglong" val)
    new Function(c, "QVariant", _n_QVariant11, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_bool, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "bool"), End),
    new Function(c, "QVariant", _n_QVariant12, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_double, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "double"), End),
    // MISSING: QVariant (QVariant; QVariant this, "float" val)
    // MISSING: QVariant (QVariant; QVariant this, "const char *" val)
    new Function(c, "QVariant", _n_QVariant15, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QByteArray, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "qt.QByteArray"), End),
    // MISSING: QVariant (QVariant; QVariant this, "const QBitArray &" val)
    new Function(c, "QVariant", _n_QVariant17, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_string, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "string"), End),
    // MISSING: QVariant (QVariant; QVariant this, "const QLatin1String &" val)
    new Function(c, "QVariant", _n_QVariant19, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_stringBSB_ESB_, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "string[]"), End),
    // MISSING: QVariant (QVariant; QVariant this, "const QChar &" c)
    new Function(c, "QVariant", _n_QVariant21, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QDate, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "qt.QDate"), End),
    new Function(c, "QVariant", _n_QVariant22, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QTime, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "qt.QTime"), End),
    new Function(c, "QVariant", _n_QVariant23, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QDateTime, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "qt.QDateTime"), End),
    // MISSING: QVariant (QVariant; QVariant this, "const QList<QVariant> &" val)
    // MISSING: QVariant (QVariant; QVariant this, "const QMap<QString, QVariant> &" val)
    // MISSING: QVariant (QVariant; QVariant this, "const QHash<QString, QVariant> &" val)
    new Function(c, "QVariant", _n_QVariant27, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QSize, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "qt.QSize"), End),
    // MISSING: QVariant (QVariant; QVariant this, "const QSizeF &" val)
    new Function(c, "QVariant", _n_QVariant29, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QPoint, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "qt.QPoint"), End),
    new Function(c, "QVariant", _n_QVariant30, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QPointF, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "qt.QPointF"), End),
    // MISSING: QVariant (QVariant; QVariant this, "const QLine &" val)
    // MISSING: QVariant (QVariant; QVariant this, "const QLineF &" val)
    new Function(c, "QVariant", _n_QVariant33, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QRect, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "qt.QRect"), End),
    new Function(c, "QVariant", _n_QVariant34, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QRectF, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "qt.QRectF"), End),
    new Function(c, "QVariant", _n_QVariant35, None, Compiled, qt_QVariant_QVariant_QVariant_QVariant_QUrl, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "val", "qt.QUrl"), End),
    new Function(c, "clear", _n_clear0, None, Compiled, qt_QVariant_clear_void_QVariant, Return, "void", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "convert", _n_convert0, None, Compiled, qt_QVariant_convert_bool_QVariant_int, Return, "bool", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "t", "int"), End),
    new Function(c, "isNull", _n_isNull0, None, Compiled, qt_QVariant_isNull_bool_QVariant, Return, "bool", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "isValid", _n_isValid0, None, Compiled, qt_QVariant_isValid_bool_QVariant, Return, "bool", Parameters, new Param(c, "this", "qt.QVariant"), End),
    // MISSING: setValue (void; QVariant this, "const T &" value)
    new Function(c, "swap", _n_swap0, None, Compiled, qt_QVariant_swap_void_QVariant_QVariant, Return, "void", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "other", "qt.QVariant"), End),
    // MISSING: toBitArray ("QBitArray"; QVariant this)
    new Function(c, "toBool", _n_toBool0, None, Compiled, qt_QVariant_toBool_bool_QVariant, Return, "bool", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "toByteArray", _n_toByteArray0, None, Compiled, qt_QVariant_toByteArray_QByteArray_QVariant, Return, "qt.QByteArray", Parameters, new Param(c, "this", "qt.QVariant"), End),
    // MISSING: toChar ("QChar"; QVariant this)
    new Function(c, "toDate", _n_toDate0, None, Compiled, qt_QVariant_toDate_QDate_QVariant, Return, "qt.QDate", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "toDateTime", _n_toDateTime0, None, Compiled, qt_QVariant_toDateTime_QDateTime_QVariant, Return, "qt.QDateTime", Parameters, new Param(c, "this", "qt.QVariant"), End),
    // MISSING: toDouble (double; QVariant this, "bool *" ok)
    // MISSING: toEasingCurve ("QEasingCurve"; QVariant this)
    // MISSING: toFloat ("float"; QVariant this, "bool *" ok)
    // MISSING: toHash ("QHash<QString, QVariant>"; QVariant this)
    // MISSING: toInt (int; QVariant this, "bool *" ok)
    // MISSING: toLine ("QLine"; QVariant this)
    // MISSING: toLineF ("QLineF"; QVariant this)
    // MISSING: toList ("QList<QVariant>"; QVariant this)
    // MISSING: toLocale ("QLocale"; QVariant this)
    // MISSING: toLongLong ("qlonglong"; QVariant this, "bool *" ok)
    // MISSING: toMap ("QMap<QString, QVariant>"; QVariant this)
    new Function(c, "toPoint", _n_toPoint0, None, Compiled, qt_QVariant_toPoint_QPoint_QVariant, Return, "qt.QPoint", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "toPointF", _n_toPointF0, None, Compiled, qt_QVariant_toPointF_QPointF_QVariant, Return, "qt.QPointF", Parameters, new Param(c, "this", "qt.QVariant"), End),
    // MISSING: toReal (double; QVariant this, "bool *" ok)
    new Function(c, "toRect", _n_toRect0, None, Compiled, qt_QVariant_toRect_QRect_QVariant, Return, "qt.QRect", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "toRectF", _n_toRectF0, None, Compiled, qt_QVariant_toRectF_QRectF_QVariant, Return, "qt.QRectF", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "toRegExp", _n_toRegExp0, None, Compiled, qt_QVariant_toRegExp_QRegExp_QVariant, Return, "qt.QRegExp", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "toSize", _n_toSize0, None, Compiled, qt_QVariant_toSize_QSize_QVariant, Return, "qt.QSize", Parameters, new Param(c, "this", "qt.QVariant"), End),
    // MISSING: toSizeF ("QSizeF"; QVariant this)
    new Function(c, "toString", _n_toString0, None, Compiled, qt_QVariant_toString_string_QVariant, Return, "string", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "toStringList", _n_toStringList0, None, Compiled, qt_QVariant_toStringList_stringBSB_ESB__QVariant, Return, "string[]", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "toTime", _n_toTime0, None, Compiled, qt_QVariant_toTime_QTime_QVariant, Return, "qt.QTime", Parameters, new Param(c, "this", "qt.QVariant"), End),
    // MISSING: toUInt (int; QVariant this, "bool *" ok)
    // MISSING: toULongLong ("qulonglong"; QVariant this, "bool *" ok)
    new Function(c, "toUrl", _n_toUrl0, None, Compiled, qt_QVariant_toUrl_QUrl_QVariant, Return, "qt.QUrl", Parameters, new Param(c, "this", "qt.QVariant"), End),
    new Function(c, "type", _n_type0, None, Compiled, qt_QVariant_type_int_QVariant, Return, "int", Parameters, new Param(c, "this", "qt.QVariant"), End),
    // MISSING: typeName ("const char *"; QVariant this)
    new Function(c, "userType", _n_userType0, None, Compiled, qt_QVariant_userType_int_QVariant, Return, "int", Parameters, new Param(c, "this", "qt.QVariant"), End),
    // MISSING: value ("T"; QVariant this)
    // static functions
    // MISSING: fromValue (QVariant; "const T &" value)
    // MISSING: nameToType (flags QVariant::Type; "const char *" name)
    // MISSING: typeToName ("const char *"; flags QVariant::Type typ)
    EndArguments);
globalScope()->addSymbols(
    new Function(c, "!=", _n_operatorBang_EQ_0, Op, Compiled, qt_QVariant_operatorBang_EQ__bool_QVariant_QVariant, Return, "bool", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "v", "qt.QVariant"), End),
    // MISSING: = (QVariant; QVariant this, QVariant variant)
    new Function(c, "==", _n_operatorEQ_EQ_0, Op, Compiled, qt_QVariant_operatorEQ_EQ__bool_QVariant_QVariant, Return, "bool", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "v", "qt.QVariant"), End),
    EndArguments);
scope()->addSymbols(
    EndArguments);


addSymbol( new Function(c, "toInt", toInt, None,
                        Compiled, QVariant_toInt_int,
                        Return, "int",
                        Parameters,
                        new Param(c, "this", "qt.QVariant"),
                        End) );

    // MISSING: toInt (int; QVariant this, "bool *" ok)
}

} // Mu
