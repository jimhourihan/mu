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
#include "QBrushType.h"
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
#include "QColorType.h"
#include "QMatrixType.h"
#include "QPixmapType.h"
#include "QImageType.h"
#include "QVariantType.h"
#include "QTransformType.h"
#include "QGradientType.h"

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

QBrushType::Instance::Instance(const Class* c) : ClassInstance(c)
{
}

QBrushType::QBrushType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QBrushType::~QBrushType()
{
}

static NODE_IMPLEMENTATION(__allocate, Pointer)
{
    QBrushType::Instance* i = new QBrushType::Instance((Class*)NODE_THIS.type());
    QBrushType::registerFinalizer(i);
    NODE_RETURN(i);
}

void 
QBrushType::registerFinalizer (void* o)
{
    GC_register_finalizer(o, QBrushType::finalizer, 0, 0, 0);
}

void 
QBrushType::finalizer (void* obj, void* data)
{
    QBrushType::Instance* i = reinterpret_cast<QBrushType::Instance*>(obj);
    delete i;
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

Pointer qt_QBrush_QBrush_QBrush_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    setqtype<QBrushType>(param_this,QBrush());
    return param_this;
}

Pointer qt_QBrush_QBrush_QBrush_QBrush_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_style)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    Qt::BrushStyle arg1 = (Qt::BrushStyle)(param_style);
    setqtype<QBrushType>(param_this,QBrush(arg1));
    return param_this;
}

Pointer qt_QBrush_QBrush_QBrush_QBrush_QColor_int(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_color, int param_style)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QColor  arg1 = getqtype<QColorType>(param_color);
    Qt::BrushStyle arg2 = (Qt::BrushStyle)(param_style);
    setqtype<QBrushType>(param_this,QBrush(arg1, arg2));
    return param_this;
}

Pointer qt_QBrush_QBrush_QBrush_QBrush_int_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_color, int param_style)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    Qt::GlobalColor arg1 = (Qt::GlobalColor)(param_color);
    Qt::BrushStyle arg2 = (Qt::BrushStyle)(param_style);
    setqtype<QBrushType>(param_this,QBrush(arg1, arg2));
    return param_this;
}

Pointer qt_QBrush_QBrush_QBrush_QBrush_QColor_QPixmap(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_color, Pointer param_pixmap)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QColor  arg1 = getqtype<QColorType>(param_color);
    const QPixmap  arg2 = getqtype<QPixmapType>(param_pixmap);
    setqtype<QBrushType>(param_this,QBrush(arg1, arg2));
    return param_this;
}

Pointer qt_QBrush_QBrush_QBrush_QBrush_int_QPixmap(Mu::Thread& NODE_THREAD, Pointer param_this, int param_color, Pointer param_pixmap)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    Qt::GlobalColor arg1 = (Qt::GlobalColor)(param_color);
    const QPixmap  arg2 = getqtype<QPixmapType>(param_pixmap);
    setqtype<QBrushType>(param_this,QBrush(arg1, arg2));
    return param_this;
}

Pointer qt_QBrush_QBrush_QBrush_QBrush_QPixmap(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_pixmap)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QPixmap  arg1 = getqtype<QPixmapType>(param_pixmap);
    setqtype<QBrushType>(param_this,QBrush(arg1));
    return param_this;
}

Pointer qt_QBrush_QBrush_QBrush_QBrush_QImage(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_image)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QImage  arg1 = getqtype<QImageType>(param_image);
    setqtype<QBrushType>(param_this,QBrush(arg1));
    return param_this;
}

Pointer qt_QBrush_QBrush_QBrush_QBrush_QGradient(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_gradient)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QGradient  arg1 = getqtype<QGradientType>(param_gradient);
    setqtype<QBrushType>(param_this,QBrush(arg1));
    return param_this;
}

Pointer qt_QBrush_color_QColor_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QBrush& arg0 = getqtype<QBrushType>(param_this);
    return makeqtype<QColorType>(c,arg0.color(),"qt.QColor");
}

bool qt_QBrush_isOpaque_bool_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QBrush& arg0 = getqtype<QBrushType>(param_this);
    return arg0.isOpaque();
}

Pointer qt_QBrush_matrix_QMatrix_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QBrush& arg0 = getqtype<QBrushType>(param_this);
    return makeqtype<QMatrixType>(c,arg0.matrix(),"qt.QMatrix");
}

void qt_QBrush_setColor_void_QBrush_QColor(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_color)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QBrush& arg0 = getqtype<QBrushType>(param_this);
    const QColor  arg1 = getqtype<QColorType>(param_color);
    arg0.setColor(arg1);
    setqtype<QBrushType>(param_this,arg0);
}

void qt_QBrush_setColor_void_QBrush_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_color)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QBrush& arg0 = getqtype<QBrushType>(param_this);
    Qt::GlobalColor arg1 = (Qt::GlobalColor)(param_color);
    arg0.setColor(arg1);
    setqtype<QBrushType>(param_this,arg0);
}

void qt_QBrush_setMatrix_void_QBrush_QMatrix(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_matrix)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QBrush& arg0 = getqtype<QBrushType>(param_this);
    const QMatrix  arg1 = getqtype<QMatrixType>(param_matrix);
    arg0.setMatrix(arg1);
    setqtype<QBrushType>(param_this,arg0);
}

void qt_QBrush_setStyle_void_QBrush_int(Mu::Thread& NODE_THREAD, Pointer param_this, int param_style)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QBrush& arg0 = getqtype<QBrushType>(param_this);
    Qt::BrushStyle arg1 = (Qt::BrushStyle)(param_style);
    arg0.setStyle(arg1);
    setqtype<QBrushType>(param_this,arg0);
}

void qt_QBrush_setTexture_void_QBrush_QPixmap(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_pixmap)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QBrush& arg0 = getqtype<QBrushType>(param_this);
    const QPixmap  arg1 = getqtype<QPixmapType>(param_pixmap);
    arg0.setTexture(arg1);
    setqtype<QBrushType>(param_this,arg0);
}

void qt_QBrush_setTextureImage_void_QBrush_QImage(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_image)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QBrush& arg0 = getqtype<QBrushType>(param_this);
    const QImage  arg1 = getqtype<QImageType>(param_image);
    arg0.setTextureImage(arg1);
    setqtype<QBrushType>(param_this,arg0);
}

void qt_QBrush_setTransform_void_QBrush_QTransform(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_matrix)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QBrush& arg0 = getqtype<QBrushType>(param_this);
    const QTransform  arg1 = getqtype<QTransformType>(param_matrix);
    arg0.setTransform(arg1);
    setqtype<QBrushType>(param_this,arg0);
}

int qt_QBrush_style_int_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QBrush& arg0 = getqtype<QBrushType>(param_this);
    return int(arg0.style());
}

void qt_QBrush_swap_void_QBrush_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_other)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QBrush& arg0 = getqtype<QBrushType>(param_this);
    QBrush  arg1 = getqtype<QBrushType>(param_other);
    arg0.swap(arg1);
    setqtype<QBrushType>(param_this,arg0);
}

Pointer qt_QBrush_texture_QPixmap_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QBrush& arg0 = getqtype<QBrushType>(param_this);
    return makeqtype<QPixmapType>(c,arg0.texture(),"qt.QPixmap");
}

Pointer qt_QBrush_textureImage_QImage_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QBrush& arg0 = getqtype<QBrushType>(param_this);
    return makeqtype<QImageType>(c,arg0.textureImage(),"qt.QImage");
}

Pointer qt_QBrush_transform_QTransform_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QBrush& arg0 = getqtype<QBrushType>(param_this);
    return makeqtype<QTransformType>(c,arg0.transform(),"qt.QTransform");
}

bool qt_QBrush_operatorBang_EQ__bool_QBrush_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_brush)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QBrush& arg0 = getqtype<QBrushType>(param_this);
    const QBrush  arg1 = getqtype<QBrushType>(param_brush);
    return arg0.operator!=(arg1);
}

bool qt_QBrush_operatorEQ_EQ__bool_QBrush_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_brush)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    const QBrush& arg0 = getqtype<QBrushType>(param_this);
    const QBrush  arg1 = getqtype<QBrushType>(param_brush);
    return arg0.operator==(arg1);
}

Pointer qt_QBrush_QVariant_QVariant_QVariant_QBrush(Mu::Thread& NODE_THREAD, Pointer param_this, Pointer param_from)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QBrush arg1 = getqtype<QBrushType>(param_from);
    setqtype<QVariantType>(param_this,QVariant(arg1));
    return param_this;
}


static NODE_IMPLEMENTATION(_n_QBrush0, Pointer)
{
    NODE_RETURN(qt_QBrush_QBrush_QBrush_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QBrush1, Pointer)
{
    NODE_RETURN(qt_QBrush_QBrush_QBrush_QBrush_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int)));
}

static NODE_IMPLEMENTATION(_n_QBrush2, Pointer)
{
    NODE_RETURN(qt_QBrush_QBrush_QBrush_QBrush_QColor_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, int)));
}

static NODE_IMPLEMENTATION(_n_QBrush3, Pointer)
{
    NODE_RETURN(qt_QBrush_QBrush_QBrush_QBrush_int_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, int)));
}

static NODE_IMPLEMENTATION(_n_QBrush4, Pointer)
{
    NODE_RETURN(qt_QBrush_QBrush_QBrush_QBrush_QColor_QPixmap(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QBrush5, Pointer)
{
    NODE_RETURN(qt_QBrush_QBrush_QBrush_QBrush_int_QPixmap(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int), NODE_ARG(2, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QBrush6, Pointer)
{
    NODE_RETURN(qt_QBrush_QBrush_QBrush_QBrush_QPixmap(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QBrush7, Pointer)
{
    NODE_RETURN(qt_QBrush_QBrush_QBrush_QBrush_QImage(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_QBrush9, Pointer)
{
    NODE_RETURN(qt_QBrush_QBrush_QBrush_QBrush_QGradient(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_color0, Pointer)
{
    NODE_RETURN(qt_QBrush_color_QColor_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_isOpaque0, bool)
{
    NODE_RETURN(qt_QBrush_isOpaque_bool_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_matrix0, Pointer)
{
    NODE_RETURN(qt_QBrush_matrix_QMatrix_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_setColor0, void)
{
    qt_QBrush_setColor_void_QBrush_QColor(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setColor1, void)
{
    qt_QBrush_setColor_void_QBrush_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int));
}

static NODE_IMPLEMENTATION(_n_setMatrix0, void)
{
    qt_QBrush_setMatrix_void_QBrush_QMatrix(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setStyle0, void)
{
    qt_QBrush_setStyle_void_QBrush_int(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, int));
}

static NODE_IMPLEMENTATION(_n_setTexture0, void)
{
    qt_QBrush_setTexture_void_QBrush_QPixmap(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setTextureImage0, void)
{
    qt_QBrush_setTextureImage_void_QBrush_QImage(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_setTransform0, void)
{
    qt_QBrush_setTransform_void_QBrush_QTransform(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_style0, int)
{
    NODE_RETURN(qt_QBrush_style_int_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_swap0, void)
{
    qt_QBrush_swap_void_QBrush_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer));
}

static NODE_IMPLEMENTATION(_n_texture0, Pointer)
{
    NODE_RETURN(qt_QBrush_texture_QPixmap_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_textureImage0, Pointer)
{
    NODE_RETURN(qt_QBrush_textureImage_QImage_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_transform0, Pointer)
{
    NODE_RETURN(qt_QBrush_transform_QTransform_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorBang_EQ_0, bool)
{
    NODE_RETURN(qt_QBrush_operatorBang_EQ__bool_QBrush_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_n_operatorEQ_EQ_0, bool)
{
    NODE_RETURN(qt_QBrush_operatorEQ_EQ__bool_QBrush_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}

static NODE_IMPLEMENTATION(_co_n_QVariant0, Pointer)
{
    NODE_RETURN(qt_QBrush_QVariant_QVariant_QVariant_QBrush(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer), NODE_ARG(1, Pointer)));
}



void
QBrushType::load()
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
    new Function(c, "QBrush", _n_QBrush0, None, Compiled, qt_QBrush_QBrush_QBrush_QBrush, Return, "qt.QBrush", Parameters, new Param(c, "this", "qt.QBrush"), End),
    new Function(c, "QBrush", _n_QBrush1, None, Compiled, qt_QBrush_QBrush_QBrush_QBrush_int, Return, "qt.QBrush", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "style", "int"), End),
    new Function(c, "QBrush", _n_QBrush2, None, Compiled, qt_QBrush_QBrush_QBrush_QBrush_QColor_int, Return, "qt.QBrush", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "color", "qt.QColor"), new Param(c, "style", "int", Value((int)Qt::SolidPattern)), End),
    new Function(c, "QBrush", _n_QBrush3, None, Compiled, qt_QBrush_QBrush_QBrush_QBrush_int_int, Return, "qt.QBrush", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "color", "int"), new Param(c, "style", "int", Value((int)Qt::SolidPattern)), End),
    new Function(c, "QBrush", _n_QBrush4, None, Compiled, qt_QBrush_QBrush_QBrush_QBrush_QColor_QPixmap, Return, "qt.QBrush", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "color", "qt.QColor"), new Param(c, "pixmap", "qt.QPixmap"), End),
    new Function(c, "QBrush", _n_QBrush5, None, Compiled, qt_QBrush_QBrush_QBrush_QBrush_int_QPixmap, Return, "qt.QBrush", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "color", "int"), new Param(c, "pixmap", "qt.QPixmap"), End),
    new Function(c, "QBrush", _n_QBrush6, None, Compiled, qt_QBrush_QBrush_QBrush_QBrush_QPixmap, Return, "qt.QBrush", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "pixmap", "qt.QPixmap"), End),
    new Function(c, "QBrush", _n_QBrush7, None, Compiled, qt_QBrush_QBrush_QBrush_QBrush_QImage, Return, "qt.QBrush", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "image", "qt.QImage"), End),
    // MISSING: QBrush (QBrush; QBrush this, QBrush other)
    new Function(c, "QBrush", _n_QBrush9, None, Compiled, qt_QBrush_QBrush_QBrush_QBrush_QGradient, Return, "qt.QBrush", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "gradient", "qt.QGradient"), End),
    new Function(c, "color", _n_color0, None, Compiled, qt_QBrush_color_QColor_QBrush, Return, "qt.QColor", Parameters, new Param(c, "this", "qt.QBrush"), End),
    new Function(c, "isOpaque", _n_isOpaque0, None, Compiled, qt_QBrush_isOpaque_bool_QBrush, Return, "bool", Parameters, new Param(c, "this", "qt.QBrush"), End),
    new Function(c, "matrix", _n_matrix0, None, Compiled, qt_QBrush_matrix_QMatrix_QBrush, Return, "qt.QMatrix", Parameters, new Param(c, "this", "qt.QBrush"), End),
    new Function(c, "setColor", _n_setColor0, None, Compiled, qt_QBrush_setColor_void_QBrush_QColor, Return, "void", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "color", "qt.QColor"), End),
    new Function(c, "setColor", _n_setColor1, None, Compiled, qt_QBrush_setColor_void_QBrush_int, Return, "void", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "color", "int"), End),
    new Function(c, "setMatrix", _n_setMatrix0, None, Compiled, qt_QBrush_setMatrix_void_QBrush_QMatrix, Return, "void", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "matrix", "qt.QMatrix"), End),
    new Function(c, "setStyle", _n_setStyle0, None, Compiled, qt_QBrush_setStyle_void_QBrush_int, Return, "void", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "style", "int"), End),
    new Function(c, "setTexture", _n_setTexture0, None, Compiled, qt_QBrush_setTexture_void_QBrush_QPixmap, Return, "void", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "pixmap", "qt.QPixmap"), End),
    new Function(c, "setTextureImage", _n_setTextureImage0, None, Compiled, qt_QBrush_setTextureImage_void_QBrush_QImage, Return, "void", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "image", "qt.QImage"), End),
    new Function(c, "setTransform", _n_setTransform0, None, Compiled, qt_QBrush_setTransform_void_QBrush_QTransform, Return, "void", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "matrix", "qt.QTransform"), End),
    new Function(c, "style", _n_style0, None, Compiled, qt_QBrush_style_int_QBrush, Return, "int", Parameters, new Param(c, "this", "qt.QBrush"), End),
    new Function(c, "swap", _n_swap0, None, Compiled, qt_QBrush_swap_void_QBrush_QBrush, Return, "void", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "other", "qt.QBrush"), End),
    new Function(c, "texture", _n_texture0, None, Compiled, qt_QBrush_texture_QPixmap_QBrush, Return, "qt.QPixmap", Parameters, new Param(c, "this", "qt.QBrush"), End),
    new Function(c, "textureImage", _n_textureImage0, None, Compiled, qt_QBrush_textureImage_QImage_QBrush, Return, "qt.QImage", Parameters, new Param(c, "this", "qt.QBrush"), End),
    new Function(c, "transform", _n_transform0, None, Compiled, qt_QBrush_transform_QTransform_QBrush, Return, "qt.QTransform", Parameters, new Param(c, "this", "qt.QBrush"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    new Function(c, "!=", _n_operatorBang_EQ_0, Op, Compiled, qt_QBrush_operatorBang_EQ__bool_QBrush_QBrush, Return, "bool", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "brush", "qt.QBrush"), End),
    // MISSING: = (QBrush; QBrush this, QBrush brush)
    new Function(c, "==", _n_operatorEQ_EQ_0, Op, Compiled, qt_QBrush_operatorEQ_EQ__bool_QBrush_QBrush, Return, "bool", Parameters, new Param(c, "this", "qt.QBrush"), new Param(c, "brush", "qt.QBrush"), End),
    EndArguments);
scope()->addSymbols(
    new Function(c, "QVariant", _co_n_QVariant0, Cast, Compiled, qt_QBrush_QVariant_QVariant_QVariant_QBrush, Return, "qt.QVariant", Parameters, new Param(c, "this", "qt.QVariant"), new Param(c, "from", "qt.QBrush"), End),
    EndArguments);

}

} // Mu
