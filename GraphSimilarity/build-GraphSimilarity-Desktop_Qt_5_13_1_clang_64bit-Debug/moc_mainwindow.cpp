/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[15];
    char stringdata0[193];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 14), // "slot_openGraph"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 14), // "slot_saveGraph"
QT_MOC_LITERAL(4, 42, 22), // "slot_calculateGraphLet"
QT_MOC_LITERAL(5, 65, 12), // "slot_btnNext"
QT_MOC_LITERAL(6, 78, 17), // "on_btnGen_clicked"
QT_MOC_LITERAL(7, 96, 8), // "genGraph"
QT_MOC_LITERAL(8, 105, 5), // "Graph"
QT_MOC_LITERAL(9, 111, 7), // "nodeNum"
QT_MOC_LITERAL(10, 119, 7), // "edgeNum"
QT_MOC_LITERAL(11, 127, 21), // "on_comboBox_activated"
QT_MOC_LITERAL(12, 149, 5), // "index"
QT_MOC_LITERAL(13, 155, 19), // "on_btnClear_clicked"
QT_MOC_LITERAL(14, 175, 17) // "on_btnGFD_clicked"

    },
    "MainWindow\0slot_openGraph\0\0slot_saveGraph\0"
    "slot_calculateGraphLet\0slot_btnNext\0"
    "on_btnGen_clicked\0genGraph\0Graph\0"
    "nodeNum\0edgeNum\0on_comboBox_activated\0"
    "index\0on_btnClear_clicked\0on_btnGFD_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    2,   74,    2, 0x08 /* Private */,
       7,    1,   79,    2, 0x28 /* Private | MethodCloned */,
       7,    0,   82,    2, 0x28 /* Private | MethodCloned */,
      11,    1,   83,    2, 0x08 /* Private */,
      13,    0,   86,    2, 0x08 /* Private */,
      14,    0,   87,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 8, QMetaType::Int, QMetaType::Int,    9,   10,
    0x80000000 | 8, QMetaType::Int,    9,
    0x80000000 | 8,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_openGraph(); break;
        case 1: _t->slot_saveGraph(); break;
        case 2: _t->slot_calculateGraphLet(); break;
        case 3: _t->slot_btnNext(); break;
        case 4: _t->on_btnGen_clicked(); break;
        case 5: { Graph _r = _t->genGraph((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< Graph*>(_a[0]) = std::move(_r); }  break;
        case 6: { Graph _r = _t->genGraph((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Graph*>(_a[0]) = std::move(_r); }  break;
        case 7: { Graph _r = _t->genGraph();
            if (_a[0]) *reinterpret_cast< Graph*>(_a[0]) = std::move(_r); }  break;
        case 8: _t->on_comboBox_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_btnClear_clicked(); break;
        case 10: _t->on_btnGFD_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
