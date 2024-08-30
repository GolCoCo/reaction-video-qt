/****************************************************************************
** Meta object code from reading C++ file 'videolistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../videolistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videolistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoListWidget_t {
    QByteArrayData data[9];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoListWidget_t qt_meta_stringdata_VideoListWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "VideoListWidget"
QT_MOC_LITERAL(1, 16, 13), // "__dragAndDrop"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 2), // "st"
QT_MOC_LITERAL(4, 34, 2), // "ed"
QT_MOC_LITERAL(5, 37, 7), // "refresh"
QT_MOC_LITERAL(6, 45, 20), // "ListItemClickLinster"
QT_MOC_LITERAL(7, 66, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 83, 4) // "item"

    },
    "VideoListWidget\0__dragAndDrop\0\0st\0ed\0"
    "refresh\0ListItemClickLinster\0"
    "QListWidgetItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       5,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void VideoListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->__dragAndDrop((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->refresh(); break;
        case 2: _t->ListItemClickLinster((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VideoListWidget::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoListWidget::__dragAndDrop)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VideoListWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VideoListWidget::refresh)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VideoListWidget::staticMetaObject = { {
    &QListWidget::staticMetaObject,
    qt_meta_stringdata_VideoListWidget.data,
    qt_meta_data_VideoListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VideoListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoListWidget.stringdata0))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int VideoListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void VideoListWidget::__dragAndDrop(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VideoListWidget::refresh()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
