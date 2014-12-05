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
#ifndef __MuQt__QToolButtonType__h__
#define __MuQt__QToolButtonType__h__
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
class MuQt_QToolButton;

//
//  NOTE: file generated by qt2mu.py
//

class QToolButtonType : public Class
{
  public:

    typedef MuQt_QToolButton MuQtType;
    typedef QToolButton QtType;

    //
    //  Constructors
    //

    QToolButtonType(Context* context, 
           const char* name,
           Class* superClass = 0,
           Class* superClass2 = 0);

    virtual ~QToolButtonType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[18];
};

// Inheritable object

class MuQt_QToolButton : public QToolButton
{
  public:
    virtual ~MuQt_QToolButton();
    MuQt_QToolButton(Pointer muobj, const CallEnvironment*, QWidget * parent) ;
    virtual QSize minimumSizeHint() const;
    virtual QSize sizeHint() const;
  protected:
    virtual void changeEvent(QEvent * e) ;
    virtual void enterEvent(QEvent * e) ;
    virtual bool event(QEvent * event_) ;
    virtual bool hitButton(const QPoint & pos) const;
    virtual void leaveEvent(QEvent * e) ;
    virtual void mousePressEvent(QMouseEvent * e) ;
    virtual void mouseReleaseEvent(QMouseEvent * e) ;
    virtual void nextCheckState() ;
    virtual void paintEvent(QPaintEvent * event) ;
    virtual void timerEvent(QTimerEvent * e) ;
    virtual void checkStateSet() ;
    virtual void focusInEvent(QFocusEvent * e) ;
    virtual void focusOutEvent(QFocusEvent * e) ;
    virtual void keyPressEvent(QKeyEvent * e) ;
    virtual void keyReleaseEvent(QKeyEvent * e) ;
    virtual void mouseMoveEvent(QMouseEvent * e) ;
  public:
    void changeEvent_pub(QEvent * e)  { changeEvent(e); }
    void changeEvent_pub_parent(QEvent * e)  { QToolButton::changeEvent(e); }
    void enterEvent_pub(QEvent * e)  { enterEvent(e); }
    void enterEvent_pub_parent(QEvent * e)  { QToolButton::enterEvent(e); }
    bool event_pub(QEvent * event_)  { return event(event_); }
    bool event_pub_parent(QEvent * event_)  { return QToolButton::event(event_); }
    bool hitButton_pub(const QPoint & pos) const { return hitButton(pos); }
    bool hitButton_pub_parent(const QPoint & pos) const { return QToolButton::hitButton(pos); }
    void leaveEvent_pub(QEvent * e)  { leaveEvent(e); }
    void leaveEvent_pub_parent(QEvent * e)  { QToolButton::leaveEvent(e); }
    void mousePressEvent_pub(QMouseEvent * e)  { mousePressEvent(e); }
    void mousePressEvent_pub_parent(QMouseEvent * e)  { QToolButton::mousePressEvent(e); }
    void mouseReleaseEvent_pub(QMouseEvent * e)  { mouseReleaseEvent(e); }
    void mouseReleaseEvent_pub_parent(QMouseEvent * e)  { QToolButton::mouseReleaseEvent(e); }
    void nextCheckState_pub()  { nextCheckState(); }
    void nextCheckState_pub_parent()  { QToolButton::nextCheckState(); }
    void paintEvent_pub(QPaintEvent * event)  { paintEvent(event); }
    void paintEvent_pub_parent(QPaintEvent * event)  { QToolButton::paintEvent(event); }
    void timerEvent_pub(QTimerEvent * e)  { timerEvent(e); }
    void timerEvent_pub_parent(QTimerEvent * e)  { QToolButton::timerEvent(e); }
    void checkStateSet_pub()  { checkStateSet(); }
    void checkStateSet_pub_parent()  { QToolButton::checkStateSet(); }
    void focusInEvent_pub(QFocusEvent * e)  { focusInEvent(e); }
    void focusInEvent_pub_parent(QFocusEvent * e)  { QToolButton::focusInEvent(e); }
    void focusOutEvent_pub(QFocusEvent * e)  { focusOutEvent(e); }
    void focusOutEvent_pub_parent(QFocusEvent * e)  { QToolButton::focusOutEvent(e); }
    void keyPressEvent_pub(QKeyEvent * e)  { keyPressEvent(e); }
    void keyPressEvent_pub_parent(QKeyEvent * e)  { QToolButton::keyPressEvent(e); }
    void keyReleaseEvent_pub(QKeyEvent * e)  { keyReleaseEvent(e); }
    void keyReleaseEvent_pub_parent(QKeyEvent * e)  { QToolButton::keyReleaseEvent(e); }
    void mouseMoveEvent_pub(QMouseEvent * e)  { mouseMoveEvent(e); }
    void mouseMoveEvent_pub_parent(QMouseEvent * e)  { QToolButton::mouseMoveEvent(e); }
  public:
    const QToolButtonType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QToolButtonType::cachedInstance(const QToolButtonType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QToolButtonType__h__
