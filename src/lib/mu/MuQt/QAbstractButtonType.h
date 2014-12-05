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
#ifndef __MuQt__QAbstractButtonType__h__
#define __MuQt__QAbstractButtonType__h__
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
class MuQt_QAbstractButton;

//
//  NOTE: file generated by qt2mu.py
//

class QAbstractButtonType : public Class
{
  public:

    typedef MuQt_QAbstractButton MuQtType;
    typedef QAbstractButton QtType;

    //
    //  Constructors
    //

    QAbstractButtonType(Context* context, 
           const char* name,
           Class* superClass = 0,
           Class* superClass2 = 0);

    virtual ~QAbstractButtonType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[34];
};

// Inheritable object

class MuQt_QAbstractButton : public QAbstractButton
{
  public:
    virtual ~MuQt_QAbstractButton();
    MuQt_QAbstractButton(Pointer muobj, const CallEnvironment*, QWidget * parent) ;
  protected:
    virtual void checkStateSet() ;
    virtual bool hitButton(const QPoint & pos) const;
    virtual void nextCheckState() ;
    virtual void changeEvent(QEvent * e) ;
    virtual bool event(QEvent * e) ;
    virtual void focusInEvent(QFocusEvent * e) ;
    virtual void focusOutEvent(QFocusEvent * e) ;
    virtual void keyPressEvent(QKeyEvent * e) ;
    virtual void keyReleaseEvent(QKeyEvent * e) ;
    virtual void mouseMoveEvent(QMouseEvent * e) ;
    virtual void mousePressEvent(QMouseEvent * e) ;
    virtual void mouseReleaseEvent(QMouseEvent * e) ;
    virtual void paintEvent(QPaintEvent * e) ;
    virtual void timerEvent(QTimerEvent * e) ;
  public:
    virtual int heightForWidth(int w) const;
    virtual QVariant inputMethodQuery(Qt::InputMethodQuery query) const;
    virtual QSize minimumSizeHint() const;
    virtual QSize sizeHint() const;
  protected:
    virtual void closeEvent(QCloseEvent * event) ;
    virtual void contextMenuEvent(QContextMenuEvent * event) ;
    virtual void dragEnterEvent(QDragEnterEvent * event) ;
    virtual void dragLeaveEvent(QDragLeaveEvent * event) ;
    virtual void dragMoveEvent(QDragMoveEvent * event) ;
    virtual void dropEvent(QDropEvent * event) ;
    virtual void enterEvent(QEvent * event) ;
    virtual bool focusNextPrevChild(bool next) ;
    virtual void hideEvent(QHideEvent * event) ;
    virtual void leaveEvent(QEvent * event) ;
    virtual void mouseDoubleClickEvent(QMouseEvent * event) ;
    virtual void moveEvent(QMoveEvent * event) ;
    virtual void resizeEvent(QResizeEvent * event) ;
    virtual void showEvent(QShowEvent * event) ;
    virtual void tabletEvent(QTabletEvent * event) ;
    virtual void wheelEvent(QWheelEvent * event) ;
  public:
    void checkStateSet_pub()  { checkStateSet(); }
    void checkStateSet_pub_parent()  { QAbstractButton::checkStateSet(); }
    bool hitButton_pub(const QPoint & pos) const { return hitButton(pos); }
    bool hitButton_pub_parent(const QPoint & pos) const { return QAbstractButton::hitButton(pos); }
    void nextCheckState_pub()  { nextCheckState(); }
    void nextCheckState_pub_parent()  { QAbstractButton::nextCheckState(); }
    void changeEvent_pub(QEvent * e)  { changeEvent(e); }
    void changeEvent_pub_parent(QEvent * e)  { QAbstractButton::changeEvent(e); }
    bool event_pub(QEvent * e)  { return event(e); }
    bool event_pub_parent(QEvent * e)  { return QAbstractButton::event(e); }
    void focusInEvent_pub(QFocusEvent * e)  { focusInEvent(e); }
    void focusInEvent_pub_parent(QFocusEvent * e)  { QAbstractButton::focusInEvent(e); }
    void focusOutEvent_pub(QFocusEvent * e)  { focusOutEvent(e); }
    void focusOutEvent_pub_parent(QFocusEvent * e)  { QAbstractButton::focusOutEvent(e); }
    void keyPressEvent_pub(QKeyEvent * e)  { keyPressEvent(e); }
    void keyPressEvent_pub_parent(QKeyEvent * e)  { QAbstractButton::keyPressEvent(e); }
    void keyReleaseEvent_pub(QKeyEvent * e)  { keyReleaseEvent(e); }
    void keyReleaseEvent_pub_parent(QKeyEvent * e)  { QAbstractButton::keyReleaseEvent(e); }
    void mouseMoveEvent_pub(QMouseEvent * e)  { mouseMoveEvent(e); }
    void mouseMoveEvent_pub_parent(QMouseEvent * e)  { QAbstractButton::mouseMoveEvent(e); }
    void mousePressEvent_pub(QMouseEvent * e)  { mousePressEvent(e); }
    void mousePressEvent_pub_parent(QMouseEvent * e)  { QAbstractButton::mousePressEvent(e); }
    void mouseReleaseEvent_pub(QMouseEvent * e)  { mouseReleaseEvent(e); }
    void mouseReleaseEvent_pub_parent(QMouseEvent * e)  { QAbstractButton::mouseReleaseEvent(e); }
    void paintEvent_pub(QPaintEvent * e)  { paintEvent(e); }
    void paintEvent_pub_parent(QPaintEvent * e)  { QAbstractButton::paintEvent(e); }
    void timerEvent_pub(QTimerEvent * e)  { timerEvent(e); }
    void timerEvent_pub_parent(QTimerEvent * e)  { QAbstractButton::timerEvent(e); }
    void closeEvent_pub(QCloseEvent * event)  { closeEvent(event); }
    void closeEvent_pub_parent(QCloseEvent * event)  { QAbstractButton::closeEvent(event); }
    void contextMenuEvent_pub(QContextMenuEvent * event)  { contextMenuEvent(event); }
    void contextMenuEvent_pub_parent(QContextMenuEvent * event)  { QAbstractButton::contextMenuEvent(event); }
    void dragEnterEvent_pub(QDragEnterEvent * event)  { dragEnterEvent(event); }
    void dragEnterEvent_pub_parent(QDragEnterEvent * event)  { QAbstractButton::dragEnterEvent(event); }
    void dragLeaveEvent_pub(QDragLeaveEvent * event)  { dragLeaveEvent(event); }
    void dragLeaveEvent_pub_parent(QDragLeaveEvent * event)  { QAbstractButton::dragLeaveEvent(event); }
    void dragMoveEvent_pub(QDragMoveEvent * event)  { dragMoveEvent(event); }
    void dragMoveEvent_pub_parent(QDragMoveEvent * event)  { QAbstractButton::dragMoveEvent(event); }
    void dropEvent_pub(QDropEvent * event)  { dropEvent(event); }
    void dropEvent_pub_parent(QDropEvent * event)  { QAbstractButton::dropEvent(event); }
    void enterEvent_pub(QEvent * event)  { enterEvent(event); }
    void enterEvent_pub_parent(QEvent * event)  { QAbstractButton::enterEvent(event); }
    bool focusNextPrevChild_pub(bool next)  { return focusNextPrevChild(next); }
    bool focusNextPrevChild_pub_parent(bool next)  { return QAbstractButton::focusNextPrevChild(next); }
    void hideEvent_pub(QHideEvent * event)  { hideEvent(event); }
    void hideEvent_pub_parent(QHideEvent * event)  { QAbstractButton::hideEvent(event); }
    void leaveEvent_pub(QEvent * event)  { leaveEvent(event); }
    void leaveEvent_pub_parent(QEvent * event)  { QAbstractButton::leaveEvent(event); }
    void mouseDoubleClickEvent_pub(QMouseEvent * event)  { mouseDoubleClickEvent(event); }
    void mouseDoubleClickEvent_pub_parent(QMouseEvent * event)  { QAbstractButton::mouseDoubleClickEvent(event); }
    void moveEvent_pub(QMoveEvent * event)  { moveEvent(event); }
    void moveEvent_pub_parent(QMoveEvent * event)  { QAbstractButton::moveEvent(event); }
    void resizeEvent_pub(QResizeEvent * event)  { resizeEvent(event); }
    void resizeEvent_pub_parent(QResizeEvent * event)  { QAbstractButton::resizeEvent(event); }
    void showEvent_pub(QShowEvent * event)  { showEvent(event); }
    void showEvent_pub_parent(QShowEvent * event)  { QAbstractButton::showEvent(event); }
    void tabletEvent_pub(QTabletEvent * event)  { tabletEvent(event); }
    void tabletEvent_pub_parent(QTabletEvent * event)  { QAbstractButton::tabletEvent(event); }
    void wheelEvent_pub(QWheelEvent * event)  { wheelEvent(event); }
    void wheelEvent_pub_parent(QWheelEvent * event)  { QAbstractButton::wheelEvent(event); }
  public:
    const QAbstractButtonType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QAbstractButtonType::cachedInstance(const QAbstractButtonType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QAbstractButtonType__h__
