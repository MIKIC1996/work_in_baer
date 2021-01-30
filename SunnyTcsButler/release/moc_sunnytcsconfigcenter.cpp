/****************************************************************************
** Meta object code from reading C++ file 'sunnytcsconfigcenter.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sunnytcsconfigcenter.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sunnytcsconfigcenter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SunnyTcsConfigCenter_t {
    QByteArrayData data[9];
    char stringdata0[139];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SunnyTcsConfigCenter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SunnyTcsConfigCenter_t qt_meta_stringdata_SunnyTcsConfigCenter = {
    {
QT_MOC_LITERAL(0, 0, 20), // "SunnyTcsConfigCenter"
QT_MOC_LITERAL(1, 21, 21), // "configPathMap_changed"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 20), // "procedureMap_changed"
QT_MOC_LITERAL(4, 65, 18), // "on_configDig_setOK"
QT_MOC_LITERAL(5, 84, 15), // "SunnyTcsConfig*"
QT_MOC_LITERAL(6, 100, 3), // "con"
QT_MOC_LITERAL(7, 104, 16), // "on_procedureSave"
QT_MOC_LITERAL(8, 121, 17) // "on_procedureClose"

    },
    "SunnyTcsConfigCenter\0configPathMap_changed\0"
    "\0procedureMap_changed\0on_configDig_setOK\0"
    "SunnyTcsConfig*\0con\0on_procedureSave\0"
    "on_procedureClose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SunnyTcsConfigCenter[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    0,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   41,    2, 0x0a /* Public */,
       7,    0,   44,    2, 0x0a /* Public */,
       8,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SunnyTcsConfigCenter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SunnyTcsConfigCenter *_t = static_cast<SunnyTcsConfigCenter *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->configPathMap_changed(); break;
        case 1: _t->procedureMap_changed(); break;
        case 2: _t->on_configDig_setOK((*reinterpret_cast< SunnyTcsConfig*(*)>(_a[1]))); break;
        case 3: _t->on_procedureSave(); break;
        case 4: _t->on_procedureClose(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SunnyTcsConfig* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SunnyTcsConfigCenter::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SunnyTcsConfigCenter::configPathMap_changed)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SunnyTcsConfigCenter::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SunnyTcsConfigCenter::procedureMap_changed)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SunnyTcsConfigCenter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SunnyTcsConfigCenter.data,
      qt_meta_data_SunnyTcsConfigCenter,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SunnyTcsConfigCenter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SunnyTcsConfigCenter::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SunnyTcsConfigCenter.stringdata0))
        return static_cast<void*>(const_cast< SunnyTcsConfigCenter*>(this));
    return QObject::qt_metacast(_clname);
}

int SunnyTcsConfigCenter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SunnyTcsConfigCenter::configPathMap_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void SunnyTcsConfigCenter::procedureMap_changed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
