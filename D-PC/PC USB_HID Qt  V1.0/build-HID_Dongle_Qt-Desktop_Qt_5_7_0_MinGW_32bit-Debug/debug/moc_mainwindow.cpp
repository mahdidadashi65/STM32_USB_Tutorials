/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../HID_Dongle_Qt/mainwindow.h"
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
    QByteArrayData data[18];
    char stringdata0[342];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "MyTimerSlot"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 23), // "on_btnClearResp_clicked"
QT_MOC_LITERAL(4, 48, 24), // "on_pbCloseSerial_clicked"
QT_MOC_LITERAL(5, 73, 23), // "on_pbOpenSerial_clicked"
QT_MOC_LITERAL(6, 97, 28), // "on_pbGetSerialStatus_clicked"
QT_MOC_LITERAL(7, 126, 24), // "on_pbWriteSerial_clicked"
QT_MOC_LITERAL(8, 151, 22), // "on_ckLED3_stateChanged"
QT_MOC_LITERAL(9, 174, 4), // "arg1"
QT_MOC_LITERAL(10, 179, 22), // "on_ckLED2_stateChanged"
QT_MOC_LITERAL(11, 202, 22), // "on_ckLED1_stateChanged"
QT_MOC_LITERAL(12, 225, 29), // "on_ckReceiveData_stateChanged"
QT_MOC_LITERAL(13, 255, 27), // "Proccess_HID_Data_MCU_to_PC"
QT_MOC_LITERAL(14, 283, 8), // "uint8_t*"
QT_MOC_LITERAL(15, 292, 4), // "data"
QT_MOC_LITERAL(16, 297, 23), // "Send_HID_Data_PC_to_MCU"
QT_MOC_LITERAL(17, 321, 20) // "on_pbOpenHID_clicked"

    },
    "MainWindow\0MyTimerSlot\0\0on_btnClearResp_clicked\0"
    "on_pbCloseSerial_clicked\0"
    "on_pbOpenSerial_clicked\0"
    "on_pbGetSerialStatus_clicked\0"
    "on_pbWriteSerial_clicked\0"
    "on_ckLED3_stateChanged\0arg1\0"
    "on_ckLED2_stateChanged\0on_ckLED1_stateChanged\0"
    "on_ckReceiveData_stateChanged\0"
    "Proccess_HID_Data_MCU_to_PC\0uint8_t*\0"
    "data\0Send_HID_Data_PC_to_MCU\0"
    "on_pbOpenHID_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x0a /* Public */,
       3,    0,   80,    2, 0x08 /* Private */,
       4,    0,   81,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    1,   85,    2, 0x08 /* Private */,
      10,    1,   88,    2, 0x08 /* Private */,
      11,    1,   91,    2, 0x08 /* Private */,
      12,    1,   94,    2, 0x08 /* Private */,
      13,    1,   97,    2, 0x08 /* Private */,
      16,    0,  100,    2, 0x08 /* Private */,
      17,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 14,   15,
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
        case 0: _t->MyTimerSlot(); break;
        case 1: _t->on_btnClearResp_clicked(); break;
        case 6: _t->on_ckLED3_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_ckLED2_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_ckLED1_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_ckReceiveData_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->Proccess_HID_Data_MCU_to_PC((*reinterpret_cast< uint8_t*(*)>(_a[1]))); break;
        case 11: _t->Send_HID_Data_PC_to_MCU(); break;
        case 12: _t->on_pbOpenHID_clicked(); break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
