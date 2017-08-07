/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../QCrtDraw/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[268];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "OnOpenProject"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 15), // "OnCreateProject"
QT_MOC_LITERAL(4, 42, 13), // "OnSaveProject"
QT_MOC_LITERAL(5, 56, 14), // "OnCloseProject"
QT_MOC_LITERAL(6, 71, 15), // "OnViewTransform"
QT_MOC_LITERAL(7, 87, 15), // "OnAddController"
QT_MOC_LITERAL(8, 103, 18), // "OnDeleteController"
QT_MOC_LITERAL(9, 122, 9), // "OnAddLoop"
QT_MOC_LITERAL(10, 132, 12), // "OnDeleteLoop"
QT_MOC_LITERAL(11, 145, 13), // "OnAddBuilding"
QT_MOC_LITERAL(12, 159, 16), // "OnDeleteBuilding"
QT_MOC_LITERAL(13, 176, 10), // "OnAddLayer"
QT_MOC_LITERAL(14, 187, 13), // "OnDeleteLayer"
QT_MOC_LITERAL(15, 201, 14), // "OnSetBackImage"
QT_MOC_LITERAL(16, 216, 19), // "OnEditDeviceChanged"
QT_MOC_LITERAL(17, 236, 6), // "nIndex"
QT_MOC_LITERAL(18, 243, 18), // "UpdateToolbarState"
QT_MOC_LITERAL(19, 262, 5) // "state"

    },
    "MainWindow\0OnOpenProject\0\0OnCreateProject\0"
    "OnSaveProject\0OnCloseProject\0"
    "OnViewTransform\0OnAddController\0"
    "OnDeleteController\0OnAddLoop\0OnDeleteLoop\0"
    "OnAddBuilding\0OnDeleteBuilding\0"
    "OnAddLayer\0OnDeleteLayer\0OnSetBackImage\0"
    "OnEditDeviceChanged\0nIndex\0"
    "UpdateToolbarState\0state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08 /* Private */,
       3,    0,   95,    2, 0x08 /* Private */,
       4,    0,   96,    2, 0x08 /* Private */,
       5,    0,   97,    2, 0x08 /* Private */,
       6,    0,   98,    2, 0x08 /* Private */,
       7,    0,   99,    2, 0x08 /* Private */,
       8,    0,  100,    2, 0x08 /* Private */,
       9,    0,  101,    2, 0x08 /* Private */,
      10,    0,  102,    2, 0x08 /* Private */,
      11,    0,  103,    2, 0x08 /* Private */,
      12,    0,  104,    2, 0x08 /* Private */,
      13,    0,  105,    2, 0x08 /* Private */,
      14,    0,  106,    2, 0x08 /* Private */,
      15,    0,  107,    2, 0x08 /* Private */,
      16,    1,  108,    2, 0x0a /* Public */,
      18,    1,  111,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   19,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnOpenProject(); break;
        case 1: _t->OnCreateProject(); break;
        case 2: _t->OnSaveProject(); break;
        case 3: _t->OnCloseProject(); break;
        case 4: _t->OnViewTransform(); break;
        case 5: _t->OnAddController(); break;
        case 6: _t->OnDeleteController(); break;
        case 7: _t->OnAddLoop(); break;
        case 8: _t->OnDeleteLoop(); break;
        case 9: _t->OnAddBuilding(); break;
        case 10: _t->OnDeleteBuilding(); break;
        case 11: _t->OnAddLayer(); break;
        case 12: _t->OnDeleteLayer(); break;
        case 13: _t->OnSetBackImage(); break;
        case 14: _t->OnEditDeviceChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->UpdateToolbarState((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
