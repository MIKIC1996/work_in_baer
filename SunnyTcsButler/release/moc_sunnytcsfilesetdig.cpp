/****************************************************************************
** Meta object code from reading C++ file 'sunnytcsfilesetdig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sunnytcsfilesetdig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'sunnytcsfilesetdig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SunnyTcsFileSetDig_t {
    QByteArrayData data[11];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SunnyTcsFileSetDig_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SunnyTcsFileSetDig_t qt_meta_stringdata_SunnyTcsFileSetDig = {
    {
QT_MOC_LITERAL(0, 0, 18), // "SunnyTcsFileSetDig"
QT_MOC_LITERAL(1, 19, 10), // "file_setOk"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 14), // "file_setCancel"
QT_MOC_LITERAL(4, 46, 22), // "on_currentNode_changed"
QT_MOC_LITERAL(5, 69, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(6, 86, 7), // "current"
QT_MOC_LITERAL(7, 94, 8), // "previous"
QT_MOC_LITERAL(8, 103, 16), // "on_okBtn_clicked"
QT_MOC_LITERAL(9, 120, 20), // "on_cancelbtn_clicked"
QT_MOC_LITERAL(10, 141, 19) // "on_Btn_save_clicked"

    },
    "SunnyTcsFileSetDig\0file_setOk\0\0"
    "file_setCancel\0on_currentNode_changed\0"
    "QTreeWidgetItem*\0current\0previous\0"
    "on_okBtn_clicked\0on_cancelbtn_clicked\0"
    "on_Btn_save_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SunnyTcsFileSetDig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   46,    2, 0x08 /* Private */,
       8,    0,   51,    2, 0x08 /* Private */,
       9,    0,   52,    2, 0x08 /* Private */,
      10,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 5,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SunnyTcsFileSetDig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SunnyTcsFileSetDig *_t = static_cast<SunnyTcsFileSetDig *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->file_setOk(); break;
        case 1: _t->file_setCancel(); break;
        case 2: _t->on_currentNode_changed((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 3: _t->on_okBtn_clicked(); break;
        case 4: _t->on_cancelbtn_clicked(); break;
        case 5: _t->on_Btn_save_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SunnyTcsFileSetDig::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SunnyTcsFileSetDig::file_setOk)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (SunnyTcsFileSetDig::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SunnyTcsFileSetDig::file_setCancel)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject SunnyTcsFileSetDig::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_SunnyTcsFileSetDig.data,
      qt_meta_data_SunnyTcsFileSetDig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SunnyTcsFileSetDig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SunnyTcsFileSetDig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SunnyTcsFileSetDig.stringdata0))
        return static_cast<void*>(const_cast< SunnyTcsFileSetDig*>(this));
    return QWidget::qt_metacast(_clname);
}

int SunnyTcsFileSetDig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void SunnyTcsFileSetDig::file_setOk()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void SunnyTcsFileSetDig::file_setCancel()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
