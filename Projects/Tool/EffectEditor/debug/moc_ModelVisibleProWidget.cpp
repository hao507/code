/****************************************************************************
** Meta object code from reading C++ file 'ModelVisibleProWidget.h'
**
** Created: Tue Dec 11 17:48:21 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/ModelVisibleProWidget.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModelVisibleProWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ModelVisibleProWidget[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      29,   23,   22,   22, 0x08,
      66,   64,   22,   22, 0x08,
     100,   64,   22,   22, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ModelVisibleProWidget[] = {
    "ModelVisibleProWidget\0\0pro,b\0"
    "boolValueChanged(QtProperty*,bool)\0,\0"
    "enumValueChanged(QtProperty*,int)\0"
    "doubleValueChanged(QtProperty*,double)\0"
};

const QMetaObject ModelVisibleProWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ModelVisibleProWidget,
      qt_meta_data_ModelVisibleProWidget, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ModelVisibleProWidget::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ModelVisibleProWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ModelVisibleProWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ModelVisibleProWidget))
        return static_cast<void*>(const_cast< ModelVisibleProWidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int ModelVisibleProWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: boolValueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: enumValueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: doubleValueChanged((*reinterpret_cast< QtProperty*(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
