/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../StructuralAnlysis/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata0[315];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 31), // "on_actionSave_Results_triggered"
QT_MOC_LITERAL(4, 68, 8), // "readFile"
QT_MOC_LITERAL(5, 77, 11), // "std::string"
QT_MOC_LITERAL(6, 89, 8), // "fileName"
QT_MOC_LITERAL(7, 98, 13), // "drawStructure"
QT_MOC_LITERAL(8, 112, 14), // "drawDStructure"
QT_MOC_LITERAL(9, 127, 28), // "on_pushButton_ZoomIn_clicked"
QT_MOC_LITERAL(10, 156, 26), // "on_pushButton_ZOut_clicked"
QT_MOC_LITERAL(11, 183, 24), // "on_actionClear_triggered"
QT_MOC_LITERAL(12, 208, 28), // "on_pushButton_solve_released"
QT_MOC_LITERAL(13, 237, 41), // "on_horizontalSlider_scaleDisp..."
QT_MOC_LITERAL(14, 279, 8), // "position"
QT_MOC_LITERAL(15, 288, 15), // "drawConstraints"
QT_MOC_LITERAL(16, 304, 10) // "drawForces"

    },
    "MainWindow\0on_actionOpen_triggered\0\0"
    "on_actionSave_Results_triggered\0"
    "readFile\0std::string\0fileName\0"
    "drawStructure\0drawDStructure\0"
    "on_pushButton_ZoomIn_clicked\0"
    "on_pushButton_ZOut_clicked\0"
    "on_actionClear_triggered\0"
    "on_pushButton_solve_released\0"
    "on_horizontalSlider_scaleDisp_sliderMoved\0"
    "position\0drawConstraints\0drawForces"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    1,   76,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,
      15,    0,   88,    2, 0x08 /* Private */,
      16,    0,   89,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_actionOpen_triggered(); break;
        case 1: _t->on_actionSave_Results_triggered(); break;
        case 2: _t->readFile((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 3: _t->drawStructure(); break;
        case 4: _t->drawDStructure(); break;
        case 5: _t->on_pushButton_ZoomIn_clicked(); break;
        case 6: _t->on_pushButton_ZOut_clicked(); break;
        case 7: _t->on_actionClear_triggered(); break;
        case 8: _t->on_pushButton_solve_released(); break;
        case 9: _t->on_horizontalSlider_scaleDisp_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->drawConstraints(); break;
        case 11: _t->drawForces(); break;
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
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
