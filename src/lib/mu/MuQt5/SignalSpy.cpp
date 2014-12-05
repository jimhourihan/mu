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
//     * Neither the name of the Jim Hourihan nor the names of its
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
#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include <QtNetwork/QtNetwork>
#include <Mu/Function.h>
#include <Mu/NodePrinter.h>
#include <Mu/Class.h>
#include <Mu/ClassInstance.h>
#include <MuLang/MuLangContext.h>
#include <MuLang/StringType.h>
//#include "qtModuleIncludes.h"
#include "qtUtils.h"
#include "QObjectType.h"
#include "QWidgetType.h"
#include "QStandardItemType.h"
#include "QListWidgetItemType.h"
#include "QTableWidgetItemType.h"
#include "QTreeWidgetItemType.h"
#include "QUrlType.h"
#include "QActionType.h"
#include "QFontType.h"
#include "QColorType.h"
#include "QPointType.h"
#include "QRectType.h"
#include "QItemSelectionType.h"
#define private public
#include "SignalSpy.h"
#undef private

namespace Mu {
using namespace std;

SignalSpy::SignalSpy(QObject* o, 
                     const char* sig,
                     const Function* F,
                     Process* p)
    : QSignalSpy(o, sig),
      _F(F),
      _process(p),
      _env(p->callEnv())
{
    const MuLangContext* c = static_cast<const MuLangContext*>(p->context());
    _argTypes.resize(F->numArgs());

    const Class* otype = 
        c->findSymbolOfTypeByQualifiedName<Class>(c->internName("qt.QObject"), false);

    const Class* ptype = 
        c->findSymbolOfTypeByQualifiedName<Class>(c->internName("qt.QPoint"), false);

    const Class* twtype = 
        c->findSymbolOfTypeByQualifiedName<Class>(c->internName("qt.QTreeWidgetItem"), false);

    const Class* tbtype = 
        c->findSymbolOfTypeByQualifiedName<Class>(c->internName("qt.QTableWidgetItem"), false);

    const Class* lwtype = 
        c->findSymbolOfTypeByQualifiedName<Class>(c->internName("qt.QListWidgetItem"), false);

    const Class* sitype = 
        c->findSymbolOfTypeByQualifiedName<Class>(c->internName("qt.QStandardItem"), false);

    const Class* mitype = 
        c->findSymbolOfTypeByQualifiedName<Class>(c->internName("qt.QModelIndex"), false);

    const Class* istype = 
        c->findSymbolOfTypeByQualifiedName<Class>(c->internName("qt.QItemSelection"), false);

    const Class* ctype = 
        c->findSymbolOfTypeByQualifiedName<Class>(c->internName("qt.QColor"), false);

    const Class* utype = 
        c->findSymbolOfTypeByQualifiedName<Class>(c->internName("qt.QUrl"), false);

    for (size_t i = 0; i < _argTypes.size(); i++)
    {
        if      (F->argType(i) == c->intType())     _argTypes[i] = IntArg;
        else if (F->argType(i) == c->stringType())  _argTypes[i] = StringArg;
        else if (F->argType(i) == c->boolType())    _argTypes[i] = BoolArg;
        else if (F->argType(i) == ctype)            _argTypes[i] = ColorArg;
        else if (const Class* c = dynamic_cast<const Class*>(F->argType(i)))
        {
            if (c == ptype) _argTypes[i] = PointArg;
            else if (c == twtype) _argTypes[i] = TreeItemArg;
            else if (c == tbtype) _argTypes[i] = TableItemArg;
            else if (c == lwtype) _argTypes[i] = ListItemArg;
            else if (c == sitype) _argTypes[i] = StandardItemArg;
            else if (c == mitype) _argTypes[i] = ModelIndexArg;
            else if (c == istype) _argTypes[i] = ItemSelectionArg;
            else if (c == utype)  _argTypes[i] = UrlArg;
            else if (c->isA(otype)) _argTypes[i] = ObjectArg;
            else 
            {
                _argTypes[i] = UnknownArg;
            }
        }
        else 
        {
            _argTypes[i] = UnknownArg;
        }

        if (_argTypes[i] == UnknownArg)
        {
            cout << "WARNING: " << sig << " not translated correctly" << endl;
        }
    }
}

SignalSpy::~SignalSpy()
{
    _F = 0;
}

int
SignalSpy::qt_metacall(QMetaObject::Call call, int methodId, void **a)
{
    if (call == QMetaObject::InvokeMetaMethod)
    {
        Function::ArgumentVector args(_argTypes.size());
        const MuLangContext* c = static_cast<const MuLangContext*>(_F->context());
        bool failed = false;

        for (size_t i = 0; i < _argTypes.size(); i++)
        {
            //QMetaType::Type type = static_cast<QMetaType::Type>(this->args.at(i));
            //cout << "type = " << QMetaType::typeName(type) << endl;

            switch (_argTypes[i])
            {
              case IntArg:
                  args[i]._int = *reinterpret_cast<int*>(a[i+1]);
                  break;

              case BoolArg:
                  args[i]._bool = *reinterpret_cast<bool*>(a[i+1]);
                  break;

              case StringArg:
                  {
                      QString* s = reinterpret_cast<QString*>(a[i+1]);
                      args[i]._Pointer = c->stringType()->allocate(s->toUtf8().constData());
                  }
                  break;

              case ObjectArg:
                  {
                      QObject** o = reinterpret_cast<QObject**>(a[i+1]);
                      args[i]._Pointer = makeinstance<QObjectType>((QObjectType*)_F->argType(i), *o);
                  }
                  break;

              case ColorArg:
                  {
                      QColor* o = reinterpret_cast<QColor*>(a[i+1]);
                      args[i]._Pointer = makeqtype<QColorType>((Class*)_F->argType(i), *o);
                  }
                  break;

              case UrlArg:
                  {
                      QUrl* o = reinterpret_cast<QUrl*>(a[i+1]);
                      args[i]._Pointer = makeqtype<QUrlType>((Class*)_F->argType(i), *o);
                  }
                  break;

              case PointArg:
                  {
                      QPoint* o = reinterpret_cast<QPoint*>(a[i+1]);
                      args[i]._Pointer = makeqtype<QPointType>((Class*)_F->argType(i), *o);
                  }
                  break;

              case TreeItemArg:
                  {
                      QMetaType::Type type = static_cast<QMetaType::Type>(this->args.at(i));
                      QVariant v(type, a[i+1]);
                      QTreeWidgetItem* o = v.value<QTreeWidgetItem*>();
                      args[i]._Pointer = !o ? NULL :
                          makeqpointer<QTreeWidgetItemType>((QTreeWidgetItemType*)_F->argType(i), o);
                  }
                  break;

              case TableItemArg:
                  {
                      QMetaType::Type type = static_cast<QMetaType::Type>(this->args.at(i));
                      QVariant v(type, a[i+1]);
                      QTableWidgetItem* o = v.value<QTableWidgetItem*>();
                      args[i]._Pointer = !o ? NULL :
                          makeqpointer<QTableWidgetItemType>((QTableWidgetItemType*)_F->argType(i), o);
                  }
                  break;

              case ListItemArg:
                  {
                      QMetaType::Type type = static_cast<QMetaType::Type>(this->args.at(i));
                      QVariant v(type, a[i+1]);
                      QListWidgetItem* o = v.value<QListWidgetItem*>();
                      args[i]._Pointer = !o ? NULL :
                          makeqpointer<QListWidgetItemType>((QListWidgetItemType*)_F->argType(i), o);
                  }
                  break;

              case StandardItemArg:
                  {
                      QMetaType::Type type = static_cast<QMetaType::Type>(this->args.at(i));
                      QVariant v(type, a[i+1]);
                      QStandardItem* o = v.value<QStandardItem*>();
                      args[i]._Pointer = !o ? NULL :
                          makeqpointer<QStandardItemType>((QStandardItemType*)_F->argType(i), o);
                  }
                  break;

              case ModelIndexArg:
                  {
                      QMetaType::Type type = static_cast<QMetaType::Type>(this->args.at(i));
                      QVariant v(type, a[i+1]);
                      QModelIndex o = v.value<QModelIndex>();
                      args[i]._Pointer = makeqtype<QModelIndexType>((Context*)c,o,"qt.QModelIndex");
                  }
                  break;

              case ItemSelectionArg:
                  {
                      QMetaType::Type type = static_cast<QMetaType::Type>(this->args.at(i));
                      QVariant v(type, a[i+1]);
                      QItemSelection o = v.value<QItemSelection>();
                      args[i]._Pointer = makeqtype<QItemSelectionType>((Context*)c,o,"qt.QItemSelection");
                  }
                  break;

              default:
                  failed = true;
                  cout << "SignalSpy::qt_metacall: don't know type: " 
                       << _argTypes[i]
                       << endl;
                  break;
            }
        }

        if (failed) return methodId;

        if (_env)
        {
            _env->call(_F, args);
        }
        else
        {
            Thread* thread = _process->newApplicationThread(); 
            _process->call(thread, _F, args);
            _process->releaseApplicationThread(thread);
        }
    }

    return methodId;
}

//  hijack qt_metacall by using a filtered version of the moc file
//  that has the function renamed to original_qt_metacall

#include "moc_SignalSpy_filtered.hpp"

} // Mu
