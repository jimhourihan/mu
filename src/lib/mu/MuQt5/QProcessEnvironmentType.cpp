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
#include "QProcessEnvironmentType.h"
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

QProcessEnvironmentType::Instance::Instance(const Class* c) : ClassInstance(c)
{
}

QProcessEnvironmentType::QProcessEnvironmentType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QProcessEnvironmentType::~QProcessEnvironmentType()
{
}

static NODE_IMPLEMENTATION(__allocate, Pointer)
{
    QProcessEnvironmentType::Instance* i = new QProcessEnvironmentType::Instance((Class*)NODE_THIS.type());
    QProcessEnvironmentType::registerFinalizer(i);
    NODE_RETURN(i);
}

void 
QProcessEnvironmentType::registerFinalizer (void* o)
{
    GC_register_finalizer(o, QProcessEnvironmentType::finalizer, 0, 0, 0);
}

void 
QProcessEnvironmentType::finalizer (void* obj, void* data)
{
    QProcessEnvironmentType::Instance* i = reinterpret_cast<QProcessEnvironmentType::Instance*>(obj);
    delete i;
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

Pointer qt_QProcessEnvironment_QProcessEnvironment_QProcessEnvironment_QProcessEnvironment(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    setqtype<QProcessEnvironmentType>(param_this,QProcessEnvironment());
    return param_this;
}

void qt_QProcessEnvironment_clear_void_QProcessEnvironment(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    arg0.clear();
    setqtype<QProcessEnvironmentType>(param_this,arg0);
}

bool qt_QProcessEnvironment_contains_bool_QProcessEnvironment_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_name)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    const QString  arg1 = qstring(param_name);
    return arg0.contains(arg1);
}

void qt_QProcessEnvironment_insert_void_QProcessEnvironment_string_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_name, Pointer param_value)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    const QString  arg1 = qstring(param_name);
    const QString  arg2 = qstring(param_value);
    arg0.insert(arg1, arg2);
    setqtype<QProcessEnvironmentType>(param_this,arg0);
}

void qt_QProcessEnvironment_insert_void_QProcessEnvironment_QProcessEnvironment(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_e)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    const QProcessEnvironment  arg1 = getqtype<QProcessEnvironmentType>(param_e);
    arg0.insert(arg1);
    setqtype<QProcessEnvironmentType>(param_this,arg0);
}

bool qt_QProcessEnvironment_isEmpty_bool_QProcessEnvironment(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    return arg0.isEmpty();
}

Pointer qt_QProcessEnvironment_keys_stringBSB_ESB__QProcessEnvironment(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    return makestringlist(c,arg0.keys());
}

void qt_QProcessEnvironment_remove_void_QProcessEnvironment_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_name)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    const QString  arg1 = qstring(param_name);
    arg0.remove(arg1);
    setqtype<QProcessEnvironmentType>(param_this,arg0);
}

void qt_QProcessEnvironment_swap_void_QProcessEnvironment_QProcessEnvironment(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_other)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    QProcessEnvironment  arg1 = getqtype<QProcessEnvironmentType>(param_other);
    arg0.swap(arg1);
    setqtype<QProcessEnvironmentType>(param_this,arg0);
}

Pointer qt_QProcessEnvironment_toStringList_stringBSB_ESB__QProcessEnvironment(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    return makestringlist(c,arg0.toStringList());
}

Pointer qt_QProcessEnvironment_value_string_QProcessEnvironment_string_string(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_name, Pointer param_defaultValue)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    const QString  arg1 = qstring(param_name);
    const QString  arg2 = qstring(param_defaultValue);
    return makestring(c,arg0.value(arg1, arg2));
}

bool qt_QProcessEnvironment_operatorBang_EQ__bool_QProcessEnvironment_QProcessEnvironment(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_other)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    const QProcessEnvironment  arg1 = getqtype<QProcessEnvironmentType>(param_other);
    return arg0.operator!=(arg1);
}

bool qt_QProcessEnvironment_operatorEQ_EQ__bool_QProcessEnvironment_QProcessEnvironment(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_other)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QProcessEnvironment& arg0 = getqtype<QProcessEnvironmentType>(param_this);
    const QProcessEnvironment  arg1 = getqtype<QProcessEnvironmentType>(param_other);
    return arg0.operator==(arg1);
}

Pointer qt_QProcessEnvironment_systemEnvironment_QProcessEnvironment(Mu::Thread& NODE_THREAD)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    return makeqtype<QProcessEnvironmentType>(c,QProcessEnvironment::systemEnvironment(),"qt.QProcessEnvironment");
}


static NODE_IMPLEMENTATION(_n_QProcessEnvironment0, Pointer)
{
    NODE_RETURN(qt_QProcessEnvironment_QProcessEnvironment_QProcessEnvironment_QProcessEnvironment(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_clear0, void)
{
    qt_QProcessEnvironment_clear_void_QProcessEnvironment(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer));
}

static NODE_IMPLEMENTATION(_n_contains0, bool)
{
    NODE_RETURN(qt_QProcessEnvironment_contains_bool_QProcessEnvironment_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_insert0, void)
{
    qt_QProcessEnvironment_insert_void_QProcessEnvironment_string_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer));
}

static NODE_IMPLEMENTATION(_n_insert1, void)
{
    qt_QProcessEnvironment_insert_void_QProcessEnvironment_QProcessEnvironment(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_isEmpty0, bool)
{
    NODE_RETURN(qt_QProcessEnvironment_isEmpty_bool_QProcessEnvironment(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_keys0, Pointer)
{
    NODE_RETURN(qt_QProcessEnvironment_keys_stringBSB_ESB__QProcessEnvironment(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_remove0, void)
{
    qt_QProcessEnvironment_remove_void_QProcessEnvironment_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_swap0, void)
{
    qt_QProcessEnvironment_swap_void_QProcessEnvironment_QProcessEnvironment(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_toStringList0, Pointer)
{
    NODE_RETURN(qt_QProcessEnvironment_toStringList_stringBSB_ESB__QProcessEnvironment(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_value0, Pointer)
{
    NODE_RETURN(qt_QProcessEnvironment_value_string_QProcessEnvironment_string_string(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorBang_EQ_0, bool)
{
    NODE_RETURN(qt_QProcessEnvironment_operatorBang_EQ__bool_QProcessEnvironment_QProcessEnvironment(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorEQ_EQ_0, bool)
{
    NODE_RETURN(qt_QProcessEnvironment_operatorEQ_EQ__bool_QProcessEnvironment_QProcessEnvironment(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_systemEnvironment0, Pointer)
{
    NODE_RETURN(qt_QProcessEnvironment_systemEnvironment_QProcessEnvironment(NODE_THREAD));
}



void
QProcessEnvironmentType::load()
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
    new Function(c, "QProcessEnvironment", _n_QProcessEnvironment0, None, Compiled, qt_QProcessEnvironment_QProcessEnvironment_QProcessEnvironment_QProcessEnvironment, Return, "qt.QProcessEnvironment", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), End),
    // MISSING: QProcessEnvironment (QProcessEnvironment; QProcessEnvironment this, QProcessEnvironment other)
    new Function(c, "clear", _n_clear0, None, Compiled, qt_QProcessEnvironment_clear_void_QProcessEnvironment, Return, "void", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), End),
    new Function(c, "contains", _n_contains0, None, Compiled, qt_QProcessEnvironment_contains_bool_QProcessEnvironment_string, Return, "bool", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), new Param(c, "name", "string"), End),
    new Function(c, "insert", _n_insert0, None, Compiled, qt_QProcessEnvironment_insert_void_QProcessEnvironment_string_string, Return, "void", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), new Param(c, "name", "string"), new Param(c, "value", "string"), End),
    new Function(c, "insert", _n_insert1, None, Compiled, qt_QProcessEnvironment_insert_void_QProcessEnvironment_QProcessEnvironment, Return, "void", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), new Param(c, "e", "qt.QProcessEnvironment"), End),
    new Function(c, "isEmpty", _n_isEmpty0, None, Compiled, qt_QProcessEnvironment_isEmpty_bool_QProcessEnvironment, Return, "bool", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), End),
    new Function(c, "keys", _n_keys0, None, Compiled, qt_QProcessEnvironment_keys_stringBSB_ESB__QProcessEnvironment, Return, "string[]", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), End),
    new Function(c, "remove", _n_remove0, None, Compiled, qt_QProcessEnvironment_remove_void_QProcessEnvironment_string, Return, "void", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), new Param(c, "name", "string"), End),
    new Function(c, "swap", _n_swap0, None, Compiled, qt_QProcessEnvironment_swap_void_QProcessEnvironment_QProcessEnvironment, Return, "void", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), new Param(c, "other", "qt.QProcessEnvironment"), End),
    new Function(c, "toStringList", _n_toStringList0, None, Compiled, qt_QProcessEnvironment_toStringList_stringBSB_ESB__QProcessEnvironment, Return, "string[]", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), End),
    new Function(c, "value", _n_value0, None, Compiled, qt_QProcessEnvironment_value_string_QProcessEnvironment_string_string, Return, "string", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), new Param(c, "name", "string"), new Param(c, "defaultValue", "string"), End),
    // static functions
    new Function(c, "systemEnvironment", _n_systemEnvironment0, None, Compiled, qt_QProcessEnvironment_systemEnvironment_QProcessEnvironment, Return, "qt.QProcessEnvironment", End),
    EndArguments);
globalScope()->addSymbols(
    new Function(c, "!=", _n_operatorBang_EQ_0, Op, Compiled, qt_QProcessEnvironment_operatorBang_EQ__bool_QProcessEnvironment_QProcessEnvironment, Return, "bool", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), new Param(c, "other", "qt.QProcessEnvironment"), End),
    // MISSING: = (QProcessEnvironment; QProcessEnvironment this, QProcessEnvironment other)
    new Function(c, "==", _n_operatorEQ_EQ_0, Op, Compiled, qt_QProcessEnvironment_operatorEQ_EQ__bool_QProcessEnvironment_QProcessEnvironment, Return, "bool", Parameters, new Param(c, "this", "qt.QProcessEnvironment"), new Param(c, "other", "qt.QProcessEnvironment"), End),
    EndArguments);
scope()->addSymbols(
    EndArguments);

}

} // Mu
