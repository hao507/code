/****************************************************************************
** Meta object code from reading C++ file 'ExComponentWidget.h'
**
** Created: Mon Nov 19 10:58:27 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/ExComponentWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ExComponentWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ExComponentWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      31,   19,   18,   18, 0x08,
      67,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ExComponentWidget[] = {
    "ExComponentWidget\0\0item,column\0"
    "changeSeleted(QTreeWidgetItem*,int)\0"
    "deleteClicked()\0"
};

const QMetaObject ExComponentWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ExComponentWidget,
      qt_meta_data_ExComponentWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ExComponentWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ExComponentWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ExComponentWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ExComponentWidget))
        return static_cast<void*>(const_cast< ExComponentWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ExComponentWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: changeSeleted((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: deleteClicked(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
