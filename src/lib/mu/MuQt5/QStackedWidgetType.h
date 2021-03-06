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
#ifndef __MuQt__QStackedWidgetType__h__
#define __MuQt__QStackedWidgetType__h__
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
class MuQt_QStackedWidget;

//
//  NOTE: file generated by qt2mu.py
//

class QStackedWidgetType : public Class
{
  public:

    typedef MuQt_QStackedWidget MuQtType;
    typedef QStackedWidget QtType;

    //
    //  Constructors
    //

    QStackedWidgetType(Context* context, 
           const char* name,
           Class* superClass = 0,
           Class* superClass2 = 0);

    virtual ~QStackedWidgetType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[4];
};

// Inheritable object

class MuQt_QStackedWidget : public QStackedWidget
{
  public:
    virtual ~MuQt_QStackedWidget();
    MuQt_QStackedWidget(Pointer muobj, const CallEnvironment*, QWidget * parent) ;
  protected:
    virtual bool event(QEvent * e) ;
  public:
    virtual QSize sizeHint() const;
  protected:
    virtual void changeEvent(QEvent * ev) ;
    virtual void paintEvent(QPaintEvent * _p13) ;
  public:
    bool event_pub(QEvent * e)  { return event(e); }
    bool event_pub_parent(QEvent * e)  { return QStackedWidget::event(e); }
    void changeEvent_pub(QEvent * ev)  { changeEvent(ev); }
    void changeEvent_pub_parent(QEvent * ev)  { QStackedWidget::changeEvent(ev); }
    void paintEvent_pub(QPaintEvent * _p13)  { paintEvent(_p13); }
    void paintEvent_pub_parent(QPaintEvent * _p13)  { QStackedWidget::paintEvent(_p13); }
  public:
    const QStackedWidgetType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QStackedWidgetType::cachedInstance(const QStackedWidgetType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QStackedWidgetType__h__
