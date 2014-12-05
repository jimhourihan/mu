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
#ifndef __MuQt__QActionType__h__
#define __MuQt__QActionType__h__
#include <iostream>
#include <Mu/Class.h>
#include <Mu/Process.h>
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include <QtNetwork/QtNetwork>
#include <QtWebKit/QtWebKit>
#include <QtWebKitWidgets/QtWebKitWidgets>
#include <QtSvg/QtSvg>
#include <MuQt5/Bridge.h>

namespace Mu {
class MuQt_QAction;

//
//  NOTE: file generated by qt2mu.py
//

class QActionType : public Class
{
  public:

    typedef MuQt_QAction MuQtType;
    typedef QAction QtType;

    //
    //  Constructors
    //

    QActionType(Context* context, 
           const char* name,
           Class* superClass = 0,
           Class* superClass2 = 0);

    virtual ~QActionType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[4];
};

// Inheritable object

class MuQt_QAction : public QAction
{
  public:
    virtual ~MuQt_QAction();
    MuQt_QAction(Pointer muobj, const CallEnvironment*, QObject * parent) ;
    MuQt_QAction(Pointer muobj, const CallEnvironment*, const QString & text, QObject * parent) ;
    MuQt_QAction(Pointer muobj, const CallEnvironment*, const QIcon & icon, const QString & text, QObject * parent) ;
  protected:
    virtual bool event(QEvent * e) ;
  public:
    virtual bool eventFilter(QObject * watched, QEvent * event) ;
  protected:
    virtual void customEvent(QEvent * event) ;
    virtual void timerEvent(QTimerEvent * event) ;
  public:
    bool event_pub(QEvent * e)  { return event(e); }
    bool event_pub_parent(QEvent * e)  { return QAction::event(e); }
    void customEvent_pub(QEvent * event)  { customEvent(event); }
    void customEvent_pub_parent(QEvent * event)  { QAction::customEvent(event); }
    void timerEvent_pub(QTimerEvent * event)  { timerEvent(event); }
    void timerEvent_pub_parent(QTimerEvent * event)  { QAction::timerEvent(event); }
  public:
    const QActionType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QActionType::cachedInstance(const QActionType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QActionType__h__
