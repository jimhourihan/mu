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
#include "$TType.h"
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
{%%handRolledInclude%%}

//
//  NOTE: this file was automatically generated by qt2mu.py
//

namespace Mu {
using namespace std;

//----------------------------------------------------------------------
//  INHERITABLE TYPE IMPLEMENTATION

{%%nativeMuQtClassImplemenation%%}

//----------------------------------------------------------------------
//  Mu Type CONSTRUCTORS

$TType::$TType(Context* c, const char* name, Class* super)
    : Class(c, name, super)
{
}

$TType::~$TType()
{
}

//----------------------------------------------------------------------
//  PRE-COMPILED FUNCTIONS

static Pointer
$T_$T_QLayoutItem(Thread& NODE_THREAD, Pointer obj)
{
    MuLangContext* c = static_cast<MuLangContext*>(NODE_THREAD.context());
    ClassInstance* item = reinterpret_cast<ClassInstance*>(obj);

    if (!item)
    {
        return 0;
    }
    else if ($T* i = layoutitem<$T>(item))
    {
        $TType* type = 
            c->findSymbolOfTypeByQualifiedName<$TType>(c->internName("qt.$T"), false);
        ClassInstance* o = ClassInstance::allocate(type);
        setlayoutitem(o, i);
        return o;
    }
    else
    {
        throw BadCastException();
    }
}

static NODE_IMPLEMENTATION(castFromLayoutItem, Pointer)
{
    NODE_RETURN( $T_$T_QLayoutItem(NODE_THREAD, NODE_ARG(0, Pointer)) );
}

{%%definitions%%}
{%%handRolledDefinitions%%}

void
$TType::load()
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

               {%%nativeObject%%}

               new Function(c, tn, castFromLayoutItem, Cast,
                            Compiled, $T_$T_QLayoutItem,
                            Return, ftn,
                            Parameters,
                            new Param(c, "layoutItem", "qt.QLayoutItem"),
                            End),

               EndArguments );

    {%%addSymbols%%}
    {%%addHandRolledSymbols%%}
}

} // Mu
