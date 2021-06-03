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
    QByteArrayData data[18];
    char stringdata0[269];
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
QT_MOC_LITERAL(4, 62, 25), // "closeChattingWindowSignal"
QT_MOC_LITERAL(5, 88, 2), // "id"
QT_MOC_LITERAL(6, 91, 15), // "sendMessageSlot"
QT_MOC_LITERAL(7, 107, 23), // "updateMsgListWidgetSlot"
QT_MOC_LITERAL(8, 131, 9), // "msgNumber"
QT_MOC_LITERAL(9, 141, 19), // "sendMsgCallbackSlot"
QT_MOC_LITERAL(10, 161, 19), // "nim::SendMessageArc"
QT_MOC_LITERAL(11, 181, 10), // "messageArc"
QT_MOC_LITERAL(12, 192, 14), // "receiveMsgSlot"
QT_MOC_LITERAL(13, 207, 14), // "nim::IMMessage"
QT_MOC_LITERAL(14, 222, 3), // "msg"
QT_MOC_LITERAL(15, 226, 15), // "valueChangeSlot"
QT_MOC_LITERAL(16, 242, 8), // "position"
QT_MOC_LITERAL(17, 251, 17) // "noMoreMessageSlot"

    },
    "ChattingWindow\0updateMsgListWidgetSignal\0"
    "\0noMoreMessageSignal\0closeChattingWindowSignal\0"
    "id\0sendMessageSlot\0updateMsgListWidgetSlot\0"
    "msgNumber\0sendMsgCallbackSlot\0"
    "nim::SendMessageArc\0messageArc\0"
    "receiveMsgSlot\0nim::IMMessage\0msg\0"
    "valueChangeSlot\0position\0noMoreMessageSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChattingWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       3,    0,   62,    2, 0x06 /* Public */,
       4,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   66,    2, 0x0a /* Public */,
       7,    1,   67,    2, 0x0a /* Public */,
       9,    1,   70,    2, 0x0a /* Public */,
      12,    1,   73,    2, 0x0a /* Public */,
      15,    1,   76,    2, 0x0a /* Public */,
      17,    0,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, QMetaType::Int,   16,
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
        case 2: _t->closeChattingWindowSignal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->sendMessageSlot(); break;
        case 4: _t->updateMsgListWidgetSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->sendMsgCallbackSlot((*reinterpret_cast< const nim::SendMessageArc(*)>(_a[1]))); break;
        case 6: _t->receiveMsgSlot((*reinterpret_cast< const nim::IMMessage(*)>(_a[1]))); break;
        case 7: _t->valueChangeSlot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->noMoreMessageSlot(); break;
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
        {
            using _t = void (ChattingWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChattingWindow::closeChattingWindowSignal)) {
                *result = 2;
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
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
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

// SIGNAL 2
void ChattingWindow::closeChattingWindowSignal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
