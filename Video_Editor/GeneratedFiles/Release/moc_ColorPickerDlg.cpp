/****************************************************************************
** Meta object code from reading C++ file 'ColorPickerDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ColorPickerDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ColorPickerDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ColorPickerDlg_t {
    QByteArrayData data[10];
    char stringdata0[134];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ColorPickerDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ColorPickerDlg_t qt_meta_stringdata_ColorPickerDlg = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ColorPickerDlg"
QT_MOC_LITERAL(1, 15, 19), // "updatePreviewSignal"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 13), // "colorBtn1Slot"
QT_MOC_LITERAL(4, 50, 13), // "colorBtn2Slot"
QT_MOC_LITERAL(5, 64, 13), // "colorBtn3Slot"
QT_MOC_LITERAL(6, 78, 13), // "colorBtn4Slot"
QT_MOC_LITERAL(7, 92, 13), // "colorBtn5Slot"
QT_MOC_LITERAL(8, 106, 13), // "colorBtn6Slot"
QT_MOC_LITERAL(9, 120, 13) // "colorBtn7Slot"

    },
    "ColorPickerDlg\0updatePreviewSignal\0\0"
    "colorBtn1Slot\0colorBtn2Slot\0colorBtn3Slot\0"
    "colorBtn4Slot\0colorBtn5Slot\0colorBtn6Slot\0"
    "colorBtn7Slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ColorPickerDlg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    0,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ColorPickerDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ColorPickerDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updatePreviewSignal(); break;
        case 1: _t->colorBtn1Slot(); break;
        case 2: _t->colorBtn2Slot(); break;
        case 3: _t->colorBtn3Slot(); break;
        case 4: _t->colorBtn4Slot(); break;
        case 5: _t->colorBtn5Slot(); break;
        case 6: _t->colorBtn6Slot(); break;
        case 7: _t->colorBtn7Slot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ColorPickerDlg::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColorPickerDlg::updatePreviewSignal)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ColorPickerDlg::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_ColorPickerDlg.data,
    qt_meta_data_ColorPickerDlg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ColorPickerDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ColorPickerDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ColorPickerDlg.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ColorPickerDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ColorPickerDlg::updatePreviewSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
