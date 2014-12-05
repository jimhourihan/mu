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
#ifndef __MuQt__QLocalSocketType__h__
#define __MuQt__QLocalSocketType__h__
#include <iostream>
#include <Mu/Class.h>
#include <Mu/Process.h>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtNetwork/QtNetwork>
#include <QtWebKit/QtWebKit>
#include <QtSvg/QtSvg>
#include <MuQt/Bridge.h>

namespace Mu {
class MuQt_QLocalSocket;

//
//  NOTE: file generated by qt2mu.py
//

class QLocalSocketType : public Class
{
  public:

    typedef MuQt_QLocalSocket MuQtType;
    typedef QLocalSocket QtType;

    //
    //  Constructors
    //

    QLocalSocketType(Context* context, 
           const char* name,
           Class* superClass = 0,
           Class* superClass2 = 0);

    virtual ~QLocalSocketType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[13];
};

// Inheritable object

class MuQt_QLocalSocket : public QLocalSocket
{
  public:
    virtual ~MuQt_QLocalSocket();
    MuQt_QLocalSocket(Pointer muobj, const CallEnvironment*, QObject * parent) ;
    virtual qint64 bytesAvailable() const;
    virtual qint64 bytesToWrite() const;
    virtual bool canReadLine() const;
    virtual void close() ;
    virtual bool isSequential() const;
    virtual bool waitForBytesWritten(int msecs) ;
    virtual bool waitForReadyRead(int msecs) ;
    virtual bool atEnd() const;
    virtual bool open(QIODevice::OpenMode mode) ;
    virtual qint64 pos() const;
    virtual bool reset() ;
    virtual bool seek(qint64 pos) ;
    virtual qint64 size() const;
  public:
    const QLocalSocketType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QLocalSocketType::cachedInstance(const QLocalSocketType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QLocalSocketType__h__
