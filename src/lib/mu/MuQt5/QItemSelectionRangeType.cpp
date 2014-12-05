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
#include "QItemSelectionRangeType.h"
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
#include "QAbstractItemModelType.h"
#include "QModelIndexType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

QItemSelectionRangeType::Instance::Instance(const Class* c) : ClassInstance(c)
{
}

QItemSelectionRangeType::QItemSelectionRangeType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QItemSelectionRangeType::~QItemSelectionRangeType()
{
}

static NODE_IMPLEMENTATION(__allocate, Pointer)
{
    QItemSelectionRangeType::Instance* i = new QItemSelectionRangeType::Instance((Class*)NODE_THIS.type());
    QItemSelectionRangeType::registerFinalizer(i);
    NODE_RETURN(i);
}

void 
QItemSelectionRangeType::registerFinalizer (void* o)
{
    GC_register_finalizer(o, QItemSelectionRangeType::finalizer, 0, 0, 0);
}

void 
QItemSelectionRangeType::finalizer (void* obj, void* data)
{
    QItemSelectionRangeType::Instance* i = reinterpret_cast<QItemSelectionRangeType::Instance*>(obj);
    delete i;
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

Pointer qt_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    setqtype<QItemSelectionRangeType>(param_this,QItemSelectionRange());
    return param_this;
}

Pointer qt_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QModelIndex_QModelIndex(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_topLeft, Pointer param_bottomRight)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QModelIndex  arg1 = getqtype<QModelIndexType>(param_topLeft);
    const QModelIndex  arg2 = getqtype<QModelIndexType>(param_bottomRight);
    setqtype<QItemSelectionRangeType>(param_this,QItemSelectionRange(arg1, arg2));
    return param_this;
}

Pointer qt_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QModelIndex(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_index)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QModelIndex  arg1 = getqtype<QModelIndexType>(param_index);
    setqtype<QItemSelectionRangeType>(param_this,QItemSelectionRange(arg1));
    return param_this;
}

int qt_QItemSelectionRange_bottom_int_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return arg0.bottom();
}

bool qt_QItemSelectionRange_contains_bool_QItemSelectionRange_QModelIndex(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_index)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    const QModelIndex  arg1 = getqtype<QModelIndexType>(param_index);
    return arg0.contains(arg1);
}

bool qt_QItemSelectionRange_contains_bool_QItemSelectionRange_int_int_QModelIndex(Mu::Thread& NODE_THREAD, Pointer param_this, int param_row, int param_column, Pointer param_parentIndex)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    int arg1 = (int)(param_row);
    int arg2 = (int)(param_column);
    const QModelIndex  arg3 = getqtype<QModelIndexType>(param_parentIndex);
    return arg0.contains(arg1, arg2, arg3);
}

int qt_QItemSelectionRange_height_int_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return arg0.height();
}

Pointer qt_QItemSelectionRange_indexes_qt__QModelIndexBSB_ESB__QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return makeqmodelindexlist(c,arg0.indexes());
}

Pointer qt_QItemSelectionRange_intersected_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_other)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    const QItemSelectionRange  arg1 = getqtype<QItemSelectionRangeType>(param_other);
    return makeqtype<QItemSelectionRangeType>(c,arg0.intersected(arg1),"qt.QItemSelectionRange");
}

bool qt_QItemSelectionRange_intersects_bool_QItemSelectionRange_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_other)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    const QItemSelectionRange  arg1 = getqtype<QItemSelectionRangeType>(param_other);
    return arg0.intersects(arg1);
}

bool qt_QItemSelectionRange_isEmpty_bool_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return arg0.isEmpty();
}

bool qt_QItemSelectionRange_isValid_bool_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return arg0.isValid();
}

int qt_QItemSelectionRange_left_int_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return arg0.left();
}

Pointer qt_QItemSelectionRange_model_QAbstractItemModel_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return makeinstance<QAbstractItemModelType>(c, arg0.model(), "qt.QAbstractItemModel");
}

Pointer qt_QItemSelectionRange_parent_QModelIndex_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return makeqtype<QModelIndexType>(c,arg0.parent(),"qt.QModelIndex");
}

int qt_QItemSelectionRange_right_int_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return arg0.right();
}

int qt_QItemSelectionRange_top_int_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return arg0.top();
}

int qt_QItemSelectionRange_width_int_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    return arg0.width();
}

bool qt_QItemSelectionRange_operatorBang_EQ__bool_QItemSelectionRange_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_other)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    const QItemSelectionRange  arg1 = getqtype<QItemSelectionRangeType>(param_other);
    return arg0.operator!=(arg1);
}

bool qt_QItemSelectionRange_operatorLT__bool_QItemSelectionRange_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_other)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    const QItemSelectionRange  arg1 = getqtype<QItemSelectionRangeType>(param_other);
    return arg0.operator<(arg1);
}

bool qt_QItemSelectionRange_operatorEQ_EQ__bool_QItemSelectionRange_QItemSelectionRange(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_other)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QItemSelectionRange arg0 = getqtype<QItemSelectionRangeType>(param_this);
    const QItemSelectionRange  arg1 = getqtype<QItemSelectionRangeType>(param_other);
    return arg0.operator==(arg1);
}


static NODE_IMPLEMENTATION(_n_QItemSelectionRange0, Pointer)
{
    NODE_RETURN(qt_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QItemSelectionRange2, Pointer)
{
    NODE_RETURN(qt_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QModelIndex_QModelIndex(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QItemSelectionRange3, Pointer)
{
    NODE_RETURN(qt_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QModelIndex(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_bottom0, int)
{
    NODE_RETURN(qt_QItemSelectionRange_bottom_int_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_contains0, bool)
{
    NODE_RETURN(qt_QItemSelectionRange_contains_bool_QItemSelectionRange_QModelIndex(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_contains1, bool)
{
    NODE_RETURN(qt_QItemSelectionRange_contains_bool_QItemSelectionRange_int_int_QModelIndex(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, int), NODE_ARG(3, Pointer)));
}

static NODE_IMPLEMENTATION(_n_height0, int)
{
    NODE_RETURN(qt_QItemSelectionRange_height_int_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_indexes0, Pointer)
{
    NODE_RETURN(qt_QItemSelectionRange_indexes_qt__QModelIndexBSB_ESB__QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_intersected0, Pointer)
{
    NODE_RETURN(qt_QItemSelectionRange_intersected_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_intersects0, bool)
{
    NODE_RETURN(qt_QItemSelectionRange_intersects_bool_QItemSelectionRange_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_isEmpty0, bool)
{
    NODE_RETURN(qt_QItemSelectionRange_isEmpty_bool_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_isValid0, bool)
{
    NODE_RETURN(qt_QItemSelectionRange_isValid_bool_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_left0, int)
{
    NODE_RETURN(qt_QItemSelectionRange_left_int_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_model0, Pointer)
{
    NODE_RETURN(qt_QItemSelectionRange_model_QAbstractItemModel_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_parent0, Pointer)
{
    NODE_RETURN(qt_QItemSelectionRange_parent_QModelIndex_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_right0, int)
{
    NODE_RETURN(qt_QItemSelectionRange_right_int_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_top0, int)
{
    NODE_RETURN(qt_QItemSelectionRange_top_int_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_width0, int)
{
    NODE_RETURN(qt_QItemSelectionRange_width_int_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorBang_EQ_0, bool)
{
    NODE_RETURN(qt_QItemSelectionRange_operatorBang_EQ__bool_QItemSelectionRange_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorLT_0, bool)
{
    NODE_RETURN(qt_QItemSelectionRange_operatorLT__bool_QItemSelectionRange_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorEQ_EQ_0, bool)
{
    NODE_RETURN(qt_QItemSelectionRange_operatorEQ_EQ__bool_QItemSelectionRange_QItemSelectionRange(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}



void
QItemSelectionRangeType::load()
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
    new Function(c, "QItemSelectionRange", _n_QItemSelectionRange0, None, Compiled, qt_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange, Return, "qt.QItemSelectionRange", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    // MISSING: QItemSelectionRange (QItemSelectionRange; QItemSelectionRange this, QItemSelectionRange other)
    new Function(c, "QItemSelectionRange", _n_QItemSelectionRange2, None, Compiled, qt_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QModelIndex_QModelIndex, Return, "qt.QItemSelectionRange", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), new Param(c, "topLeft", "qt.QModelIndex"), new Param(c, "bottomRight", "qt.QModelIndex"), End),
    new Function(c, "QItemSelectionRange", _n_QItemSelectionRange3, None, Compiled, qt_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange_QModelIndex, Return, "qt.QItemSelectionRange", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), new Param(c, "index", "qt.QModelIndex"), End),
    new Function(c, "bottom", _n_bottom0, None, Compiled, qt_QItemSelectionRange_bottom_int_QItemSelectionRange, Return, "int", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    // MISSING: bottomRight ("const QPersistentModelIndex &"; QItemSelectionRange this)
    new Function(c, "contains", _n_contains0, None, Compiled, qt_QItemSelectionRange_contains_bool_QItemSelectionRange_QModelIndex, Return, "bool", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), new Param(c, "index", "qt.QModelIndex"), End),
    new Function(c, "contains", _n_contains1, None, Compiled, qt_QItemSelectionRange_contains_bool_QItemSelectionRange_int_int_QModelIndex, Return, "bool", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), new Param(c, "row", "int"), new Param(c, "column", "int"), new Param(c, "parentIndex", "qt.QModelIndex"), End),
    new Function(c, "height", _n_height0, None, Compiled, qt_QItemSelectionRange_height_int_QItemSelectionRange, Return, "int", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    new Function(c, "indexes", _n_indexes0, None, Compiled, qt_QItemSelectionRange_indexes_qt__QModelIndexBSB_ESB__QItemSelectionRange, Return, "qt.QModelIndex[]", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    new Function(c, "intersected", _n_intersected0, None, Compiled, qt_QItemSelectionRange_intersected_QItemSelectionRange_QItemSelectionRange_QItemSelectionRange, Return, "qt.QItemSelectionRange", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), new Param(c, "other", "qt.QItemSelectionRange"), End),
    new Function(c, "intersects", _n_intersects0, None, Compiled, qt_QItemSelectionRange_intersects_bool_QItemSelectionRange_QItemSelectionRange, Return, "bool", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), new Param(c, "other", "qt.QItemSelectionRange"), End),
    new Function(c, "isEmpty", _n_isEmpty0, None, Compiled, qt_QItemSelectionRange_isEmpty_bool_QItemSelectionRange, Return, "bool", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    new Function(c, "isValid", _n_isValid0, None, Compiled, qt_QItemSelectionRange_isValid_bool_QItemSelectionRange, Return, "bool", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    new Function(c, "left", _n_left0, None, Compiled, qt_QItemSelectionRange_left_int_QItemSelectionRange, Return, "int", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    new Function(c, "model", _n_model0, None, Compiled, qt_QItemSelectionRange_model_QAbstractItemModel_QItemSelectionRange, Return, "qt.QAbstractItemModel", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    new Function(c, "parent", _n_parent0, None, Compiled, qt_QItemSelectionRange_parent_QModelIndex_QItemSelectionRange, Return, "qt.QModelIndex", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    new Function(c, "right", _n_right0, None, Compiled, qt_QItemSelectionRange_right_int_QItemSelectionRange, Return, "int", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    new Function(c, "top", _n_top0, None, Compiled, qt_QItemSelectionRange_top_int_QItemSelectionRange, Return, "int", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    // MISSING: topLeft ("const QPersistentModelIndex &"; QItemSelectionRange this)
    new Function(c, "width", _n_width0, None, Compiled, qt_QItemSelectionRange_width_int_QItemSelectionRange, Return, "int", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    new Function(c, "!=", _n_operatorBang_EQ_0, Op, Compiled, qt_QItemSelectionRange_operatorBang_EQ__bool_QItemSelectionRange_QItemSelectionRange, Return, "bool", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), new Param(c, "other", "qt.QItemSelectionRange"), End),
    new Function(c, "<", _n_operatorLT_0, Op, Compiled, qt_QItemSelectionRange_operatorLT__bool_QItemSelectionRange_QItemSelectionRange, Return, "bool", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), new Param(c, "other", "qt.QItemSelectionRange"), End),
    new Function(c, "==", _n_operatorEQ_EQ_0, Op, Compiled, qt_QItemSelectionRange_operatorEQ_EQ__bool_QItemSelectionRange_QItemSelectionRange, Return, "bool", Parameters, new Param(c, "this", "qt.QItemSelectionRange"), new Param(c, "other", "qt.QItemSelectionRange"), End),
    EndArguments);
scope()->addSymbols(
    EndArguments);

}

} // Mu
