/****************************************************************************
** Meta object code from reading C++ file 'configsetdig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../configsetdig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configsetdig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ConfigSetDig_t {
    QByteArrayData data[14];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConfigSetDig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConfigSetDig_t qt_meta_stringdata_ConfigSetDig = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ConfigSetDig"
QT_MOC_LITERAL(1, 13, 9), // "setCancel"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 5), // "setOk"
QT_MOC_LITERAL(4, 30, 15), // "SunnyTcsConfig*"
QT_MOC_LITERAL(5, 46, 4), // "file"
QT_MOC_LITERAL(6, 51, 18), // "on_clear_configDig"
QT_MOC_LITERAL(7, 70, 22), // "on_currentNode_changed"
QT_MOC_LITERAL(8, 93, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(9, 110, 7), // "current"
QT_MOC_LITERAL(10, 118, 8), // "previous"
QT_MOC_LITERAL(11, 127, 16), // "on_okBtn_clicked"
QT_MOC_LITERAL(12, 144, 21), // "on_item_okBtn_clicked"
QT_MOC_LITERAL(13, 166, 20) // "on_cancelBtn_clicked"

    },
    "ConfigSetDig\0setCancel\0\0setOk\0"
    "SunnyTcsConfig*\0file\0on_clear_configDig\0"
    "on_currentNode_changed\0QTreeWidgetItem*\0"
    "current\0previous\0on_okBtn_clicked\0"
    "on_item_okBtn_clicked\0on_cancelBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConfigSetDig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   53,    2, 0x08 /* Private */,
       7,    2,   54,    2, 0x08 /* Private */,
      11,    0,   59,    2, 0x08 /* Private */,
      12,    0,   60,    2, 0x08 /* Private */,
      13,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 8,    9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ConfigSetDig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConfigSetDig *_t = static_cast<ConfigSetDig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setCancel(); break;
        case 1: _t->setOk((*reinterpret_cast< SunnyTcsConfig*(*)>(_a[1]))); break;
        case 2: _t->on_clear_configDig(); break;
        case 3: _t->on_currentNode_changed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 4: _t->on_okBtn_clicked(); break;
        case 5: _t->on_item_okBtn_clicked(); break;
        case 6: _t->on_cancelBtn_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
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
            typedef void (ConfigSetDig::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConfigSetDig::setCancel)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ConfigSetDig::*_t)(SunnyTcsConfig * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConfigSetDig::setOk)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ConfigSetDig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ConfigSetDig.data,
      qt_meta_data_ConfigSetDig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConfigSetDig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConfigSetDig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConfigSetDig.stringdata0))
        return static_cast<void*>(const_cast< ConfigSetDig*>(this));
    return QWidget::qt_metacast(_clname);
}

int ConfigSetDig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ConfigSetDig::setCancel()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ConfigSetDig::setOk(SunnyTcsConfig * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
