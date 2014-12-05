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
#ifndef __MuQt__QLayoutItemType__h__
#define __MuQt__QLayoutItemType__h__
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
class MuQt_QLayoutItem;

//
//  NOTE: file generated by qt2mu.py
//

class QLayoutItemType : public Class
{
  public:

    struct Struct { QLayoutItem* object; };
    typedef MuQt_QLayoutItem MuQtType;
    typedef QLayoutItem QtType;

    //
    //  Constructors
    //

    QLayoutItemType(Context* context, const char* name, Class* superClass = 0);
    virtual ~QLayoutItemType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[14];
};

// Inheritable object

class MuQt_QLayoutItem : public QLayoutItem
{
  public:
    virtual ~MuQt_QLayoutItem();
    MuQt_QLayoutItem(Pointer muobj, const CallEnvironment*, Qt::Alignment alignment) ;
    virtual QSizePolicy::ControlTypes controlTypes() const;
    virtual Qt::Orientations expandingDirections() const ;
    virtual QRect geometry() const ;
    virtual bool hasHeightForWidth() const;
    virtual int heightForWidth(int w) const;
    virtual void invalidate() ;
    virtual bool isEmpty() const ;
    virtual QLayout * layout() ;
    virtual QSize maximumSize() const ;
    virtual int minimumHeightForWidth(int w) const;
    virtual QSize minimumSize() const ;
    virtual void setGeometry(const QRect & r) ;
    virtual QSize sizeHint() const ;
    virtual QWidget * widget() ;
  public:
    const QLayoutItemType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QLayoutItemType::cachedInstance(const QLayoutItemType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QLayoutItemType__h__
