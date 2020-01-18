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
    QByteArrayData data[14];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "sig_aaa"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 14), // "slot_openGraph"
QT_MOC_LITERAL(4, 35, 14), // "slot_saveGraph"
QT_MOC_LITERAL(5, 50, 22), // "slot_calculateGraphLet"
QT_MOC_LITERAL(6, 73, 12), // "slot_btnNext"
QT_MOC_LITERAL(7, 86, 17), // "on_btnGen_clicked"
QT_MOC_LITERAL(8, 104, 8), // "genGraph"
QT_MOC_LITERAL(9, 113, 5), // "Graph"
QT_MOC_LITERAL(10, 119, 7), // "nodeNum"
QT_MOC_LITERAL(11, 127, 7), // "edgeNum"
QT_MOC_LITERAL(12, 135, 21), // "on_comboBox_activated"
QT_MOC_LITERAL(13, 157, 5) // "index"

    },
    "MainWindow\0sig_aaa\0\0slot_openGraph\0"
    "slot_saveGraph\0slot_calculateGraphLet\0"
    "slot_btnNext\0on_btnGen_clicked\0genGraph\0"
    "Graph\0nodeNum\0edgeNum\0on_comboBox_activated\0"
    "index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    2,   70,    2, 0x08 /* Private */,
       8,    1,   75,    2, 0x28 /* Private | MethodCloned */,
       8,    0,   78,    2, 0x28 /* Private | MethodCloned */,
      12,    1,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 9, QMetaType::Int, QMetaType::Int,   10,   11,
    0x80000000 | 9, QMetaType::Int,   10,
    0x80000000 | 9,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sig_aaa(); break;
        case 1: _t->slot_openGraph(); break;
        case 2: _t->slot_saveGraph(); break;
        case 3: _t->slot_calculateGraphLet(); break;
        case 4: _t->slot_btnNext(); break;
        case 5: _t->on_btnGen_clicked(); break;
        case 6: { Graph _r = _t->genGraph((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< Graph*>(_a[0]) = std::move(_r); }  break;
        case 7: { Graph _r = _t->genGraph((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Graph*>(_a[0]) = std::move(_r); }  break;
        case 8: { Graph _r = _t->genGraph();
            if (_a[0]) *reinterpret_cast< Graph*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->on_comboBox_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sig_aaa)) {
                *result = 0;
                return;
            }
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
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::sig_aaa()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
