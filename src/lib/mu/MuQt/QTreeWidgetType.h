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
#ifndef __MuQt__QTreeWidgetType__h__
#define __MuQt__QTreeWidgetType__h__
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
class MuQt_QTreeWidget;

//
//  NOTE: file generated by qt2mu.py
//

class QTreeWidgetType : public Class
{
  public:

    typedef MuQt_QTreeWidget MuQtType;
    typedef QTreeWidget QtType;

    //
    //  Constructors
    //

    QTreeWidgetType(Context* context, 
           const char* name,
           Class* superClass = 0,
           Class* superClass2 = 0);

    virtual ~QTreeWidgetType();

    static bool isInheritable() { return true; }
    static inline ClassInstance* cachedInstance(const MuQtType*);

    //
    //  Class API
    //

    virtual void load();

    MemberFunction* _func[36];
};

// Inheritable object

class MuQt_QTreeWidget : public QTreeWidget
{
  public:
    virtual ~MuQt_QTreeWidget();
    MuQt_QTreeWidget(Pointer muobj, const CallEnvironment*, QWidget * parent) ;
    virtual void setSelectionModel(QItemSelectionModel * selectionModel) ;
  protected:
    virtual bool dropMimeData(QTreeWidgetItem * parent, int index, const QMimeData * data, Qt::DropAction action) ;
    virtual QMimeData * mimeData(const QList<QTreeWidgetItem *> items) const;
    virtual QStringList mimeTypes() const;
    virtual Qt::DropActions supportedDropActions() const;
    virtual void dropEvent(QDropEvent * event) ;
    virtual bool event(QEvent * e) ;
  public:
    virtual void dataChanged(const QModelIndex & topLeft, const QModelIndex & bottomRight) ;
    virtual QModelIndex indexAt(const QPoint & point) const;
    virtual void keyboardSearch(const QString & search) ;
    virtual void reset() ;
    virtual void selectAll() ;
    virtual void setRootIndex(const QModelIndex & index) ;
    virtual QRect visualRect(const QModelIndex & index) const;
  protected:
    virtual void currentChanged(const QModelIndex & current, const QModelIndex & previous) ;
    virtual void dragMoveEvent(QDragMoveEvent * event) ;
    virtual int horizontalOffset() const;
    virtual bool isIndexHidden(const QModelIndex & index) const;
    virtual void keyPressEvent(QKeyEvent * event) ;
    virtual void mouseDoubleClickEvent(QMouseEvent * event) ;
    virtual void mouseMoveEvent(QMouseEvent * event) ;
    virtual void mousePressEvent(QMouseEvent * event) ;
    virtual void mouseReleaseEvent(QMouseEvent * event) ;
    virtual void paintEvent(QPaintEvent * event) ;
    virtual void rowsAboutToBeRemoved(const QModelIndex & parent, int start, int end) ;
    virtual void rowsInserted(const QModelIndex & parent, int start, int end) ;
    virtual void scrollContentsBy(int dx, int dy) ;
    virtual QModelIndexList selectedIndexes() const;
    virtual void selectionChanged(const QItemSelection & selected, const QItemSelection & deselected) ;
    virtual void setSelection(const QRect & rect, QItemSelectionModel::SelectionFlags command) ;
    virtual int sizeHintForColumn(int column) const;
    virtual void timerEvent(QTimerEvent * event) ;
    virtual void updateGeometries() ;
    virtual int verticalOffset() const;
    virtual bool viewportEvent(QEvent * event) ;
    virtual QRegion visualRegionForSelection(const QItemSelection & selection) const;
  public:
    bool dropMimeData_pub(QTreeWidgetItem * parent, int index, const QMimeData * data, Qt::DropAction action)  { return dropMimeData(parent, index, data, action); }
    bool dropMimeData_pub_parent(QTreeWidgetItem * parent, int index, const QMimeData * data, Qt::DropAction action)  { return QTreeWidget::dropMimeData(parent, index, data, action); }
    QModelIndex indexFromItem_pub(QTreeWidgetItem * item, int column) const { return indexFromItem(item, column); }
    QModelIndex indexFromItem_pub_parent(QTreeWidgetItem * item, int column) const { return QTreeWidget::indexFromItem(item, column); }
    QTreeWidgetItem * itemFromIndex_pub(const QModelIndex & index) const { return itemFromIndex(index); }
    QTreeWidgetItem * itemFromIndex_pub_parent(const QModelIndex & index) const { return QTreeWidget::itemFromIndex(index); }
    QMimeData * mimeData_pub(const QList<QTreeWidgetItem *> items) const { return mimeData(items); }
    QMimeData * mimeData_pub_parent(const QList<QTreeWidgetItem *> items) const { return QTreeWidget::mimeData(items); }
    QStringList mimeTypes_pub() const { return mimeTypes(); }
    QStringList mimeTypes_pub_parent() const { return QTreeWidget::mimeTypes(); }
    Qt::DropActions supportedDropActions_pub() const { return supportedDropActions(); }
    Qt::DropActions supportedDropActions_pub_parent() const { return QTreeWidget::supportedDropActions(); }
    void dropEvent_pub(QDropEvent * event)  { dropEvent(event); }
    void dropEvent_pub_parent(QDropEvent * event)  { QTreeWidget::dropEvent(event); }
    bool event_pub(QEvent * e)  { return event(e); }
    bool event_pub_parent(QEvent * e)  { return QTreeWidget::event(e); }
    void currentChanged_pub(const QModelIndex & current, const QModelIndex & previous)  { currentChanged(current, previous); }
    void currentChanged_pub_parent(const QModelIndex & current, const QModelIndex & previous)  { QTreeWidget::currentChanged(current, previous); }
    void dragMoveEvent_pub(QDragMoveEvent * event)  { dragMoveEvent(event); }
    void dragMoveEvent_pub_parent(QDragMoveEvent * event)  { QTreeWidget::dragMoveEvent(event); }
    int horizontalOffset_pub() const { return horizontalOffset(); }
    int horizontalOffset_pub_parent() const { return QTreeWidget::horizontalOffset(); }
    bool isIndexHidden_pub(const QModelIndex & index) const { return isIndexHidden(index); }
    bool isIndexHidden_pub_parent(const QModelIndex & index) const { return QTreeWidget::isIndexHidden(index); }
    void keyPressEvent_pub(QKeyEvent * event)  { keyPressEvent(event); }
    void keyPressEvent_pub_parent(QKeyEvent * event)  { QTreeWidget::keyPressEvent(event); }
    void mouseDoubleClickEvent_pub(QMouseEvent * event)  { mouseDoubleClickEvent(event); }
    void mouseDoubleClickEvent_pub_parent(QMouseEvent * event)  { QTreeWidget::mouseDoubleClickEvent(event); }
    void mouseMoveEvent_pub(QMouseEvent * event)  { mouseMoveEvent(event); }
    void mouseMoveEvent_pub_parent(QMouseEvent * event)  { QTreeWidget::mouseMoveEvent(event); }
    void mousePressEvent_pub(QMouseEvent * event)  { mousePressEvent(event); }
    void mousePressEvent_pub_parent(QMouseEvent * event)  { QTreeWidget::mousePressEvent(event); }
    void mouseReleaseEvent_pub(QMouseEvent * event)  { mouseReleaseEvent(event); }
    void mouseReleaseEvent_pub_parent(QMouseEvent * event)  { QTreeWidget::mouseReleaseEvent(event); }
    void paintEvent_pub(QPaintEvent * event)  { paintEvent(event); }
    void paintEvent_pub_parent(QPaintEvent * event)  { QTreeWidget::paintEvent(event); }
    void rowsAboutToBeRemoved_pub(const QModelIndex & parent, int start, int end)  { rowsAboutToBeRemoved(parent, start, end); }
    void rowsAboutToBeRemoved_pub_parent(const QModelIndex & parent, int start, int end)  { QTreeWidget::rowsAboutToBeRemoved(parent, start, end); }
    void rowsInserted_pub(const QModelIndex & parent, int start, int end)  { rowsInserted(parent, start, end); }
    void rowsInserted_pub_parent(const QModelIndex & parent, int start, int end)  { QTreeWidget::rowsInserted(parent, start, end); }
    void scrollContentsBy_pub(int dx, int dy)  { scrollContentsBy(dx, dy); }
    void scrollContentsBy_pub_parent(int dx, int dy)  { QTreeWidget::scrollContentsBy(dx, dy); }
    QModelIndexList selectedIndexes_pub() const { return selectedIndexes(); }
    QModelIndexList selectedIndexes_pub_parent() const { return QTreeWidget::selectedIndexes(); }
    void selectionChanged_pub(const QItemSelection & selected, const QItemSelection & deselected)  { selectionChanged(selected, deselected); }
    void selectionChanged_pub_parent(const QItemSelection & selected, const QItemSelection & deselected)  { QTreeWidget::selectionChanged(selected, deselected); }
    void setSelection_pub(const QRect & rect, QItemSelectionModel::SelectionFlags command)  { setSelection(rect, command); }
    void setSelection_pub_parent(const QRect & rect, QItemSelectionModel::SelectionFlags command)  { QTreeWidget::setSelection(rect, command); }
    int sizeHintForColumn_pub(int column) const { return sizeHintForColumn(column); }
    int sizeHintForColumn_pub_parent(int column) const { return QTreeWidget::sizeHintForColumn(column); }
    void timerEvent_pub(QTimerEvent * event)  { timerEvent(event); }
    void timerEvent_pub_parent(QTimerEvent * event)  { QTreeWidget::timerEvent(event); }
    void updateGeometries_pub()  { updateGeometries(); }
    void updateGeometries_pub_parent()  { QTreeWidget::updateGeometries(); }
    int verticalOffset_pub() const { return verticalOffset(); }
    int verticalOffset_pub_parent() const { return QTreeWidget::verticalOffset(); }
    bool viewportEvent_pub(QEvent * event)  { return viewportEvent(event); }
    bool viewportEvent_pub_parent(QEvent * event)  { return QTreeWidget::viewportEvent(event); }
    QRegion visualRegionForSelection_pub(const QItemSelection & selection) const { return visualRegionForSelection(selection); }
    QRegion visualRegionForSelection_pub_parent(const QItemSelection & selection) const { return QTreeWidget::visualRegionForSelection(selection); }
  public:
    const QTreeWidgetType* _baseType;
    ClassInstance* _obj;
    const CallEnvironment* _env;
};

inline ClassInstance* QTreeWidgetType::cachedInstance(const QTreeWidgetType::MuQtType* obj) { return obj->_obj; }

} // Mu

#endif // __MuQt__QTreeWidgetType__h__
