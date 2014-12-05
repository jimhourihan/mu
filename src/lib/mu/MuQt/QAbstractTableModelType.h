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
#ifndef __MuQt__QAbstractTableModelType__h__
#define __MuQt__QAbstractTableModelType__h__
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
class MuQt_QAbstractTableModel;

//
//  NOTE: file generated by qt2mu.py
//

class QAbstractTableModelType : public Class
{
  public:

    typedef MuQt_QAbstractTableModel MuQtType;
    typedef QAbstractTableModel QtType;

    //
    //  Constructors
    //

    QAbstractTableModelType(Context* context, 
           const char* name,
           Class* superClass = 0,
           Class* superClass2 = 0);

    virtual ~QAbstractTableModelType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[22];
};

// Inheritable object

class MuQt_QAbstractTableModel : public QAbstractTableModel
{
  public:
    virtual ~MuQt_QAbstractTableModel();
    MuQt_QAbstractTableModel(Pointer muobj, const CallEnvironment*, QObject * parent) ;
    virtual bool dropMimeData(const QMimeData * data, Qt::DropAction action, int row, int column, const QModelIndex & parent) ;
    virtual QModelIndex index(int row, int column, const QModelIndex & parent) const;
    virtual QModelIndex buddy(const QModelIndex & index) const;
    virtual bool canFetchMore(const QModelIndex & parent) const;
    virtual int columnCount(const QModelIndex & parent) const ;
    virtual QVariant data(const QModelIndex & index, int role) const ;
    virtual void fetchMore(const QModelIndex & parent) ;
    virtual Qt::ItemFlags flags(const QModelIndex & index) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    virtual bool insertColumns(int column, int count, const QModelIndex & parent) ;
    virtual bool insertRows(int row, int count, const QModelIndex & parent) ;
    virtual QModelIndexList match(const QModelIndex & start, int role, const QVariant & value, int hits, Qt::MatchFlags flags) const;
    virtual QMimeData * mimeData(const QModelIndexList & indexes) const;
    virtual QStringList mimeTypes() const;
    virtual bool removeColumns(int column, int count, const QModelIndex & parent) ;
    virtual bool removeRows(int row, int count, const QModelIndex & parent) ;
    virtual int rowCount(const QModelIndex & parent) const ;
    virtual bool setData(const QModelIndex & index, const QVariant & value, int role) ;
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant & value, int role) ;
    virtual void sort(int column, Qt::SortOrder order) ;
    virtual QSize span(const QModelIndex & index) const;
    virtual Qt::DropActions supportedDropActions() const;
  public:
    const QAbstractTableModelType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QAbstractTableModelType::cachedInstance(const QAbstractTableModelType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QAbstractTableModelType__h__
