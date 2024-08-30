/****************************************************************************
** Meta object code from reading C++ file 'trimbar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../trimbar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'trimbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TrimBar_t {
    QByteArrayData data[13];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TrimBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TrimBar_t qt_meta_stringdata_TrimBar = {
    {
QT_MOC_LITERAL(0, 0, 7), // "TrimBar"
QT_MOC_LITERAL(1, 8, 17), // "__SeekJumpChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "seek"
QT_MOC_LITERAL(4, 32, 17), // "__playSeekChanged"
QT_MOC_LITERAL(5, 50, 17), // "__leftSeekChanged"
QT_MOC_LITERAL(6, 68, 18), // "__rightSeekChanged"
QT_MOC_LITERAL(7, 87, 12), // "fitSeekItems"
QT_MOC_LITERAL(8, 100, 5), // "lseek"
QT_MOC_LITERAL(9, 106, 5), // "rseek"
QT_MOC_LITERAL(10, 112, 16), // "fitSeekPlayItems"
QT_MOC_LITERAL(11, 129, 5), // "pseek"
QT_MOC_LITERAL(12, 135, 12) // "setSeekItems"

    },
    "TrimBar\0__SeekJumpChanged\0\0seek\0"
    "__playSeekChanged\0__leftSeekChanged\0"
    "__rightSeekChanged\0fitSeekItems\0lseek\0"
    "rseek\0fitSeekPlayItems\0pseek\0setSeekItems"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TrimBar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       5,    1,   55,    2, 0x06 /* Public */,
       6,    1,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   61,    2, 0x0a /* Public */,
      10,    1,   66,    2, 0x0a /* Public */,
      12,    2,   69,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, QMetaType::QReal,    3,
    QMetaType::Void, QMetaType::QReal,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,    8,    9,
    QMetaType::Void, QMetaType::QReal,   11,
    QMetaType::Void, QMetaType::QReal, QMetaType::QReal,    8,    9,

       0        // eod
};

void TrimBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TrimBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->__SeekJumpChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 1: _t->__playSeekChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 2: _t->__leftSeekChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 3: _t->__rightSeekChanged((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 4: _t->fitSeekItems((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        case 5: _t->fitSeekPlayItems((*reinterpret_cast< qreal(*)>(_a[1]))); break;
        case 6: _t->setSeekItems((*reinterpret_cast< qreal(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TrimBar::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrimBar::__SeekJumpChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TrimBar::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrimBar::__playSeekChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TrimBar::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrimBar::__leftSeekChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TrimBar::*)(qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TrimBar::__rightSeekChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject TrimBar::staticMetaObject = { {
    &QLabel::staticMetaObject,
    qt_meta_stringdata_TrimBar.data,
    qt_meta_data_TrimBar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *TrimBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TrimBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TrimBar.stringdata0))
        return static_cast<void*>(this);
    return QLabel::qt_metacast(_clname);
}

int TrimBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void TrimBar::__SeekJumpChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TrimBar::__playSeekChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TrimBar::__leftSeekChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TrimBar::__rightSeekChanged(qreal _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
