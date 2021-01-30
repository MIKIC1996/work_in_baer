/****************************************************************************
** Meta object code from reading C++ file 'sunnytcsprocedurechilddig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sunnytcsprocedurechilddig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sunnytcsprocedurechilddig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SunnyTcsProcedureChildDig_t {
    QByteArrayData data[9];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SunnyTcsProcedureChildDig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SunnyTcsProcedureChildDig_t qt_meta_stringdata_SunnyTcsProcedureChildDig = {
    {
QT_MOC_LITERAL(0, 0, 25), // "SunnyTcsProcedureChildDig"
QT_MOC_LITERAL(1, 26, 10), // "childDigOk"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 4), // "path"
QT_MOC_LITERAL(4, 43, 5), // "index"
QT_MOC_LITERAL(5, 49, 10), // "childClose"
QT_MOC_LITERAL(6, 60, 17), // "on_Btn_ok_clicked"
QT_MOC_LITERAL(7, 78, 24), // "on_currentAction_changed"
QT_MOC_LITERAL(8, 103, 6) // "action"

    },
    "SunnyTcsProcedureChildDig\0childDigOk\0"
    "\0path\0index\0childClose\0on_Btn_ok_clicked\0"
    "on_currentAction_changed\0action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SunnyTcsProcedureChildDig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   34,    2, 0x06 /* Public */,
       5,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   42,    2, 0x08 /* Private */,
       7,    1,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,

       0        // eod
};

void SunnyTcsProcedureChildDig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SunnyTcsProcedureChildDig *_t = static_cast<SunnyTcsProcedureChildDig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->childDigOk((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->childClose((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->on_Btn_ok_clicked(); break;
        case 3: _t->on_currentAction_changed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SunnyTcsProcedureChildDig::*_t)(QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SunnyTcsProcedureChildDig::childDigOk)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SunnyTcsProcedureChildDig::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SunnyTcsProcedureChildDig::childClose)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SunnyTcsProcedureChildDig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SunnyTcsProcedureChildDig.data,
      qt_meta_data_SunnyTcsProcedureChildDig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SunnyTcsProcedureChildDig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SunnyTcsProcedureChildDig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SunnyTcsProcedureChildDig.stringdata0))
        return static_cast<void*>(const_cast< SunnyTcsProcedureChildDig*>(this));
    return QWidget::qt_metacast(_clname);
}

int SunnyTcsProcedureChildDig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SunnyTcsProcedureChildDig::childDigOk(QString _t1, QString _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SunnyTcsProcedureChildDig::childClose(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
