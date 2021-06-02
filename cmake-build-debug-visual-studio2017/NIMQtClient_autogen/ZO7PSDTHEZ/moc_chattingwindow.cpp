/****************************************************************************
** Meta object code from reading C++ file 'chattingwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../window/chattingWidget/chattingwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chattingwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChattingWindow_t {
    QByteArrayData data[16];
    char stringdata0[240];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChattingWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChattingWindow_t qt_meta_stringdata_ChattingWindow = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ChattingWindow"
QT_MOC_LITERAL(1, 15, 25), // "updateMsgListWidgetSignal"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 19), // "noMoreMessageSignal"
QT_MOC_LITERAL(4, 62, 15), // "sendMessageSlot"
QT_MOC_LITERAL(5, 78, 23), // "updateMsgListWidgetSlot"
QT_MOC_LITERAL(6, 102, 9), // "msgNumber"
QT_MOC_LITERAL(7, 112, 19), // "sendMsgCallbackSlot"
QT_MOC_LITERAL(8, 132, 19), // "nim::SendMessageArc"
QT_MOC_LITERAL(9, 152, 10), // "messageArc"
QT_MOC_LITERAL(10, 163, 14), // "receiveMsgSlot"
QT_MOC_LITERAL(11, 178, 14), // "nim::IMMessage"
QT_MOC_LITERAL(12, 193, 3), // "msg"
QT_MOC_LITERAL(13, 197, 15), // "valueChangeSlot"
QT_MOC_LITERAL(14, 213, 8), // "position"
QT_MOC_LITERAL(15, 222, 17) // "noMoreMessageSlot"

    },
    "ChattingWindow\0updateMsgListWidgetSignal\0"
    "\0noMoreMessageSignal\0sendMessageSlot\0"
    "updateMsgListWidgetSlot\0msgNumber\0"
    "sendMsgCallbackSlot\0nim::SendMessageArc\0"
    "messageArc\0receiveMsgSlot\0nim::IMMessage\0"
    "msg\0valueChangeSlot\0position\0"
    "noMoreMessageSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChattingWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   58,    2, 0x0a /* Public */,
       5,    1,   59,    2, 0x0a /* Public */,
       7,    1,   62,    2, 0x0a /* Public */,
      10,    1,   65,    2, 0x0a /* Public */,
      13,    1,   68,    2, 0x0a /* Public */,
      15,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,

       0        // eod
};

void ChattingWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChattingWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateMsgListWidgetSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->noMoreMessageSignal(); break;
        case 2: _t->sendMessageSlot(); break;
        case 3: _t->updateMsgListWidgetSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->sendMsgCallbackSlot((*reinterpret_cast< const nim::SendMessageArc(*)>(_a[1]))); break;
        case 5: _t->receiveMsgSlot((*reinterpret_cast< const nim::IMMessage(*)>(_a[1]))); break;
        case 6: _t->valueChangeSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->noMoreMessageSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChattingWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChattingWindow::updateMsgListWidgetSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChattingWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChattingWindow::noMoreMessageSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChattingWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ChattingWindow.data,
    qt_meta_data_ChattingWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChattingWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChattingWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChattingWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ChattingWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void ChattingWindow::updateMsgListWidgetSignal(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChattingWindow::noMoreMessageSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
