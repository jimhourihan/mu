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
#include "QWindowStateChangeEventType.h"
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

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

QWindowStateChangeEventType::QWindowStateChangeEventType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

QWindowStateChangeEventType::~QWindowStateChangeEventType()
{
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

int qt_QWindowStateChangeEvent_oldState_int_QWindowStateChangeEvent(Mu::Thread& NODE_THREAD, Pointer param_this)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    QWindowStateChangeEvent * arg0 = getqpointer<QWindowStateChangeEventType>(param_this);
    return int(arg0->oldState());
}


static NODE_IMPLEMENTATION(_n_oldState0, int)
{
    NODE_RETURN(qt_QWindowStateChangeEvent_oldState_int_QWindowStateChangeEvent(NODE_THREAD, NONNIL_NODE_ARG(0, Pointer)));
}



void
QWindowStateChangeEventType::load()
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
    new Function(c, "oldState", _n_oldState0, None, Compiled, qt_QWindowStateChangeEvent_oldState_int_QWindowStateChangeEvent, Return, "int", Parameters, new Param(c, "this", "qt.QWindowStateChangeEvent"), End),
    // static functions
    EndArguments);
globalScope()->addSymbols(
    EndArguments);
scope()->addSymbols(
    EndArguments);

}

} // Mu
