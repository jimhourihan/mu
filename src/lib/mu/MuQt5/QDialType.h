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
#ifndef __MuQt__QDialType__h__
#define __MuQt__QDialType__h__
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
class MuQt_QDial;

//
//  NOTE: file generated by qt2mu.py
//

class QDialType : public Class
{
  public:

    typedef MuQt_QDial MuQtType;
    typedef QDial QtType;

    //
    //  Constructors
    //

    QDialType(Context* context, 
           const char* name,
           Class* superClass = 0,
           Class* superClass2 = 0);

    virtual ~QDialType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[12];
};

// Inheritable object

class MuQt_QDial : public QDial
{
  public:
    virtual ~MuQt_QDial();
    MuQt_QDial(Pointer muobj, const CallEnvironment*, QWidget * parent) ;
    virtual QSize minimumSizeHint() const;
    virtual QSize sizeHint() const;
  protected:
    virtual bool event(QEvent * e) ;
    virtual void mouseMoveEvent(QMouseEvent * e) ;
    virtual void mousePressEvent(QMouseEvent * e) ;
    virtual void mouseReleaseEvent(QMouseEvent * e) ;
    virtual void paintEvent(QPaintEvent * pe) ;
    virtual void resizeEvent(QResizeEvent * e) ;
    virtual void changeEvent(QEvent * ev) ;
    virtual void keyPressEvent(QKeyEvent * ev) ;
    virtual void timerEvent(QTimerEvent * e) ;
    virtual void wheelEvent(QWheelEvent * e) ;
  public:
    bool event_pub(QEvent * e)  { return event(e); }
    bool event_pub_parent(QEvent * e)  { return QDial::event(e); }
    void mouseMoveEvent_pub(QMouseEvent * e)  { mouseMoveEvent(e); }
    void mouseMoveEvent_pub_parent(QMouseEvent * e)  { QDial::mouseMoveEvent(e); }
    void mousePressEvent_pub(QMouseEvent * e)  { mousePressEvent(e); }
    void mousePressEvent_pub_parent(QMouseEvent * e)  { QDial::mousePressEvent(e); }
    void mouseReleaseEvent_pub(QMouseEvent * e)  { mouseReleaseEvent(e); }
    void mouseReleaseEvent_pub_parent(QMouseEvent * e)  { QDial::mouseReleaseEvent(e); }
    void paintEvent_pub(QPaintEvent * pe)  { paintEvent(pe); }
    void paintEvent_pub_parent(QPaintEvent * pe)  { QDial::paintEvent(pe); }
    void resizeEvent_pub(QResizeEvent * e)  { resizeEvent(e); }
    void resizeEvent_pub_parent(QResizeEvent * e)  { QDial::resizeEvent(e); }
    void changeEvent_pub(QEvent * ev)  { changeEvent(ev); }
    void changeEvent_pub_parent(QEvent * ev)  { QDial::changeEvent(ev); }
    void keyPressEvent_pub(QKeyEvent * ev)  { keyPressEvent(ev); }
    void keyPressEvent_pub_parent(QKeyEvent * ev)  { QDial::keyPressEvent(ev); }
    void timerEvent_pub(QTimerEvent * e)  { timerEvent(e); }
    void timerEvent_pub_parent(QTimerEvent * e)  { QDial::timerEvent(e); }
    void wheelEvent_pub(QWheelEvent * e)  { wheelEvent(e); }
    void wheelEvent_pub_parent(QWheelEvent * e)  { QDial::wheelEvent(e); }
  public:
    const QDialType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QDialType::cachedInstance(const QDialType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QDialType__h__
