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
    QByteArrayData data[52];
    char stringdata0[885];
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
QT_MOC_LITERAL(4, 68, 24), // "on_actionClear_triggered"
QT_MOC_LITERAL(5, 93, 25), // "on_actionJoints_triggered"
QT_MOC_LITERAL(6, 119, 26), // "on_actionMembers_triggered"
QT_MOC_LITERAL(7, 146, 30), // "on_actionConstraints_triggered"
QT_MOC_LITERAL(8, 177, 25), // "on_actionForces_triggered"
QT_MOC_LITERAL(9, 203, 29), // "on_actionProperties_triggered"
QT_MOC_LITERAL(10, 233, 28), // "on_pushButton_solve_released"
QT_MOC_LITERAL(11, 262, 27), // "on_pushButton_Disp_released"
QT_MOC_LITERAL(12, 290, 41), // "on_horizontalSlider_scaleDisp..."
QT_MOC_LITERAL(13, 332, 8), // "position"
QT_MOC_LITERAL(14, 341, 29), // "on_pushButton_Stress_released"
QT_MOC_LITERAL(15, 371, 25), // "on_checkBox_const_toggled"
QT_MOC_LITERAL(16, 397, 7), // "checked"
QT_MOC_LITERAL(17, 405, 25), // "on_checkBox_Force_toggled"
QT_MOC_LITERAL(18, 431, 9), // "drawJoint"
QT_MOC_LITERAL(19, 441, 11), // "drawMembers"
QT_MOC_LITERAL(20, 453, 15), // "drawConstraints"
QT_MOC_LITERAL(21, 469, 10), // "drawForces"
QT_MOC_LITERAL(22, 480, 14), // "drawDStructure"
QT_MOC_LITERAL(23, 495, 19), // "pushButton_addJoint"
QT_MOC_LITERAL(24, 515, 20), // "pushButton_addmember"
QT_MOC_LITERAL(25, 536, 24), // "pushButton_addconstraint"
QT_MOC_LITERAL(26, 561, 19), // "pushButton_addforce"
QT_MOC_LITERAL(27, 581, 25), // "pushButton_setDProperties"
QT_MOC_LITERAL(28, 607, 10), // "wheelEvent"
QT_MOC_LITERAL(29, 618, 12), // "QWheelEvent*"
QT_MOC_LITERAL(30, 631, 5), // "event"
QT_MOC_LITERAL(31, 637, 6), // "zoomIn"
QT_MOC_LITERAL(32, 644, 7), // "zoomOut"
QT_MOC_LITERAL(33, 652, 8), // "readFile"
QT_MOC_LITERAL(34, 661, 11), // "std::string"
QT_MOC_LITERAL(35, 673, 8), // "fileName"
QT_MOC_LITERAL(36, 682, 13), // "clearToolbars"
QT_MOC_LITERAL(37, 696, 10), // "solveReady"
QT_MOC_LITERAL(38, 707, 23), // "on_actionUndo_triggered"
QT_MOC_LITERAL(39, 731, 10), // "clearJoint"
QT_MOC_LITERAL(40, 742, 11), // "clearMember"
QT_MOC_LITERAL(41, 754, 15), // "clearConstraint"
QT_MOC_LITERAL(42, 770, 10), // "clearForce"
QT_MOC_LITERAL(43, 781, 9), // "clearFile"
QT_MOC_LITERAL(44, 791, 3), // "num"
QT_MOC_LITERAL(45, 795, 9), // "clearDraw"
QT_MOC_LITERAL(46, 805, 23), // "on_actionRedo_triggered"
QT_MOC_LITERAL(47, 829, 9), // "redoJoint"
QT_MOC_LITERAL(48, 839, 10), // "redoMember"
QT_MOC_LITERAL(49, 850, 14), // "redoConstraint"
QT_MOC_LITERAL(50, 865, 9), // "redoForce"
QT_MOC_LITERAL(51, 875, 9) // "drawJNums"

    },
    "MainWindow\0on_actionOpen_triggered\0\0"
    "on_actionSave_Results_triggered\0"
    "on_actionClear_triggered\0"
    "on_actionJoints_triggered\0"
    "on_actionMembers_triggered\0"
    "on_actionConstraints_triggered\0"
    "on_actionForces_triggered\0"
    "on_actionProperties_triggered\0"
    "on_pushButton_solve_released\0"
    "on_pushButton_Disp_released\0"
    "on_horizontalSlider_scaleDisp_sliderMoved\0"
    "position\0on_pushButton_Stress_released\0"
    "on_checkBox_const_toggled\0checked\0"
    "on_checkBox_Force_toggled\0drawJoint\0"
    "drawMembers\0drawConstraints\0drawForces\0"
    "drawDStructure\0pushButton_addJoint\0"
    "pushButton_addmember\0pushButton_addconstraint\0"
    "pushButton_addforce\0pushButton_setDProperties\0"
    "wheelEvent\0QWheelEvent*\0event\0zoomIn\0"
    "zoomOut\0readFile\0std::string\0fileName\0"
    "clearToolbars\0solveReady\0"
    "on_actionUndo_triggered\0clearJoint\0"
    "clearMember\0clearConstraint\0clearForce\0"
    "clearFile\0num\0clearDraw\0on_actionRedo_triggered\0"
    "redoJoint\0redoMember\0redoConstraint\0"
    "redoForce\0drawJNums"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      43,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  229,    2, 0x08 /* Private */,
       3,    0,  230,    2, 0x08 /* Private */,
       4,    0,  231,    2, 0x08 /* Private */,
       5,    0,  232,    2, 0x08 /* Private */,
       6,    0,  233,    2, 0x08 /* Private */,
       7,    0,  234,    2, 0x08 /* Private */,
       8,    0,  235,    2, 0x08 /* Private */,
       9,    0,  236,    2, 0x08 /* Private */,
      10,    0,  237,    2, 0x08 /* Private */,
      11,    0,  238,    2, 0x08 /* Private */,
      12,    1,  239,    2, 0x08 /* Private */,
      14,    0,  242,    2, 0x08 /* Private */,
      15,    1,  243,    2, 0x08 /* Private */,
      17,    1,  246,    2, 0x08 /* Private */,
      18,    0,  249,    2, 0x08 /* Private */,
      19,    0,  250,    2, 0x08 /* Private */,
      20,    0,  251,    2, 0x08 /* Private */,
      21,    0,  252,    2, 0x08 /* Private */,
      22,    0,  253,    2, 0x08 /* Private */,
      23,    0,  254,    2, 0x08 /* Private */,
      24,    0,  255,    2, 0x08 /* Private */,
      25,    0,  256,    2, 0x08 /* Private */,
      26,    0,  257,    2, 0x08 /* Private */,
      27,    0,  258,    2, 0x08 /* Private */,
      28,    1,  259,    2, 0x08 /* Private */,
      31,    0,  262,    2, 0x08 /* Private */,
      32,    0,  263,    2, 0x08 /* Private */,
      33,    1,  264,    2, 0x08 /* Private */,
      36,    0,  267,    2, 0x08 /* Private */,
      37,    0,  268,    2, 0x08 /* Private */,
      38,    0,  269,    2, 0x08 /* Private */,
      39,    0,  270,    2, 0x08 /* Private */,
      40,    0,  271,    2, 0x08 /* Private */,
      41,    0,  272,    2, 0x08 /* Private */,
      42,    0,  273,    2, 0x08 /* Private */,
      43,    1,  274,    2, 0x08 /* Private */,
      45,    0,  277,    2, 0x08 /* Private */,
      46,    0,  278,    2, 0x08 /* Private */,
      47,    0,  279,    2, 0x08 /* Private */,
      48,    0,  280,    2, 0x08 /* Private */,
      49,    0,  281,    2, 0x08 /* Private */,
      50,    0,  282,    2, 0x08 /* Private */,
      51,    0,  283,    2, 0x08 /* Private */,

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
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void, QMetaType::Bool,   16,
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
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 34,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
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
        case 2: _t->on_actionClear_triggered(); break;
        case 3: _t->on_actionJoints_triggered(); break;
        case 4: _t->on_actionMembers_triggered(); break;
        case 5: _t->on_actionConstraints_triggered(); break;
        case 6: _t->on_actionForces_triggered(); break;
        case 7: _t->on_actionProperties_triggered(); break;
        case 8: _t->on_pushButton_solve_released(); break;
        case 9: _t->on_pushButton_Disp_released(); break;
        case 10: _t->on_horizontalSlider_scaleDisp_sliderMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_pushButton_Stress_released(); break;
        case 12: _t->on_checkBox_const_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_checkBox_Force_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->drawJoint(); break;
        case 15: _t->drawMembers(); break;
        case 16: _t->drawConstraints(); break;
        case 17: _t->drawForces(); break;
        case 18: _t->drawDStructure(); break;
        case 19: _t->pushButton_addJoint(); break;
        case 20: _t->pushButton_addmember(); break;
        case 21: _t->pushButton_addconstraint(); break;
        case 22: _t->pushButton_addforce(); break;
        case 23: _t->pushButton_setDProperties(); break;
        case 24: _t->wheelEvent((*reinterpret_cast< QWheelEvent*(*)>(_a[1]))); break;
        case 25: _t->zoomIn(); break;
        case 26: _t->zoomOut(); break;
        case 27: _t->readFile((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 28: _t->clearToolbars(); break;
        case 29: _t->solveReady(); break;
        case 30: _t->on_actionUndo_triggered(); break;
        case 31: _t->clearJoint(); break;
        case 32: _t->clearMember(); break;
        case 33: _t->clearConstraint(); break;
        case 34: _t->clearForce(); break;
        case 35: _t->clearFile((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 36: _t->clearDraw(); break;
        case 37: _t->on_actionRedo_triggered(); break;
        case 38: _t->redoJoint(); break;
        case 39: _t->redoMember(); break;
        case 40: _t->redoConstraint(); break;
        case 41: _t->redoForce(); break;
        case 42: _t->drawJNums(); break;
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
        if (_id < 43)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 43;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 43)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 43;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
