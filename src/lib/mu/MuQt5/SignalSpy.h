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
//     * Neither the name of the Jim Hourihan nor the names of its
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
#ifndef __MuQt__SignalSpy__h__
#define __MuQt__SignalSpy__h__
#include <iostream>
#include <Mu/FunctionObject.h>
#include <Mu/Thread.h>
#include <QtTest/QtTest>

namespace Mu {

class SignalSpy : public QSignalSpy
{
    Q_OBJECT

  public:
    enum Types
    {
        UnknownArg,
        IntArg,
        StringArg,
        BoolArg,
        PointArg,
        ObjectArg,
        ActionArg,
        ColorArg,
        TreeItemArg,
        ListItemArg,
        TableItemArg,
        StandardItemArg,
        ModelIndexArg,
        ItemSelectionArg,
        UrlArg,
    };

    SignalSpy(QObject*, 
              const char* signal, 
              const Function* F,
              Process* p);

    virtual ~SignalSpy();

    int original_qt_metacall(QMetaObject::Call, int, void**);

  private:
    const Function*        _F;
    Process*               _process;
    const CallEnvironment* _env;
    std::vector<Types>     _argTypes;
};

} // Mu

#endif // __MuQt__SignalSpy__h__
