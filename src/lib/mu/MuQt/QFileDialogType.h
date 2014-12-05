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
#ifndef __MuQt__QFileDialogType__h__
#define __MuQt__QFileDialogType__h__
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
class MuQt_QFileDialog;

//
//  NOTE: file generated by qt2mu.py
//

class QFileDialogType : public Class
{
  public:

    typedef MuQt_QFileDialog MuQtType;
    typedef QFileDialog QtType;

    //
    //  Constructors
    //

    QFileDialogType(Context* context, 
           const char* name,
           Class* superClass = 0,
           Class* superClass2 = 0);

    virtual ~QFileDialogType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[13];
};

// Inheritable object

class MuQt_QFileDialog : public QFileDialog
{
  public:
    virtual ~MuQt_QFileDialog();
    MuQt_QFileDialog(Pointer muobj, const CallEnvironment*, QWidget * parent, Qt::WindowFlags flags) ;
    MuQt_QFileDialog(Pointer muobj, const CallEnvironment*, QWidget * parent, const QString & caption, const QString & directory, const QString & filter) ;
    virtual void setVisible(bool visible) ;
  protected:
    virtual void accept() ;
    virtual void changeEvent(QEvent * e) ;
    virtual void done(int result) ;
  public:
    virtual QSize minimumSizeHint() const;
    virtual QSize sizeHint() const;
  protected:
    virtual void closeEvent(QCloseEvent * e) ;
    virtual void contextMenuEvent(QContextMenuEvent * e) ;
    virtual bool event(QEvent * e) ;
    virtual bool eventFilter(QObject * o, QEvent * e) ;
    virtual void keyPressEvent(QKeyEvent * e) ;
    virtual void resizeEvent(QResizeEvent * _p16) ;
    virtual void showEvent(QShowEvent * event) ;
  public:
    void accept_pub()  { accept(); }
    void accept_pub_parent()  { QFileDialog::accept(); }
    void changeEvent_pub(QEvent * e)  { changeEvent(e); }
    void changeEvent_pub_parent(QEvent * e)  { QFileDialog::changeEvent(e); }
    void done_pub(int result)  { done(result); }
    void done_pub_parent(int result)  { QFileDialog::done(result); }
    void closeEvent_pub(QCloseEvent * e)  { closeEvent(e); }
    void closeEvent_pub_parent(QCloseEvent * e)  { QFileDialog::closeEvent(e); }
    void contextMenuEvent_pub(QContextMenuEvent * e)  { contextMenuEvent(e); }
    void contextMenuEvent_pub_parent(QContextMenuEvent * e)  { QFileDialog::contextMenuEvent(e); }
    bool event_pub(QEvent * e)  { return event(e); }
    bool event_pub_parent(QEvent * e)  { return QFileDialog::event(e); }
    bool eventFilter_pub(QObject * o, QEvent * e)  { return eventFilter(o, e); }
    bool eventFilter_pub_parent(QObject * o, QEvent * e)  { return QFileDialog::eventFilter(o, e); }
    void keyPressEvent_pub(QKeyEvent * e)  { keyPressEvent(e); }
    void keyPressEvent_pub_parent(QKeyEvent * e)  { QFileDialog::keyPressEvent(e); }
    void resizeEvent_pub(QResizeEvent * _p16)  { resizeEvent(_p16); }
    void resizeEvent_pub_parent(QResizeEvent * _p16)  { QFileDialog::resizeEvent(_p16); }
    void showEvent_pub(QShowEvent * event)  { showEvent(event); }
    void showEvent_pub_parent(QShowEvent * event)  { QFileDialog::showEvent(event); }
  public:
    const QFileDialogType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QFileDialogType::cachedInstance(const QFileDialogType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QFileDialogType__h__
