/****************************************************************************
** Meta object code from reading C++ file 'qmainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../window/qmainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[25];
    char stringdata0[467];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 12), // "LogoutSignal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 21), // "sendMsgCallbackSignal"
QT_MOC_LITERAL(4, 47, 19), // "nim::SendMessageArc"
QT_MOC_LITERAL(5, 67, 10), // "messageArc"
QT_MOC_LITERAL(6, 78, 16), // "receiveMsgSignal"
QT_MOC_LITERAL(7, 95, 14), // "nim::IMMessage"
QT_MOC_LITERAL(8, 110, 3), // "msg"
QT_MOC_LITERAL(9, 114, 20), // "ClickHeaderPhotoSlot"
QT_MOC_LITERAL(10, 135, 16), // "toolLabelChecked"
QT_MOC_LITERAL(11, 152, 34), // "UserCardChangeToChattingWindo..."
QT_MOC_LITERAL(12, 187, 17), // "nim::UserNameCard"
QT_MOC_LITERAL(13, 205, 8), // "nameCard"
QT_MOC_LITERAL(14, 214, 39), // "FriendProfileChangeToChatting..."
QT_MOC_LITERAL(15, 254, 18), // "nim::FriendProfile"
QT_MOC_LITERAL(16, 273, 13), // "friendProfile"
QT_MOC_LITERAL(17, 287, 32), // "SessionChangToChattingWindowSlot"
QT_MOC_LITERAL(18, 320, 16), // "nim::SessionData"
QT_MOC_LITERAL(19, 337, 11), // "sessionData"
QT_MOC_LITERAL(20, 349, 37), // "OpenChattingWindowFromFriendL..."
QT_MOC_LITERAL(21, 387, 12), // "userNameCard"
QT_MOC_LITERAL(22, 400, 39), // "OpenChattingWindowFromRecentS..."
QT_MOC_LITERAL(23, 440, 23), // "CloseChattingWindowSlot"
QT_MOC_LITERAL(24, 464, 2) // "id"

    },
    "MainWindow\0LogoutSignal\0\0sendMsgCallbackSignal\0"
    "nim::SendMessageArc\0messageArc\0"
    "receiveMsgSignal\0nim::IMMessage\0msg\0"
    "ClickHeaderPhotoSlot\0toolLabelChecked\0"
    "UserCardChangeToChattingWindowSlot\0"
    "nim::UserNameCard\0nameCard\0"
    "FriendProfileChangeToChattingWindowSlot\0"
    "nim::FriendProfile\0friendProfile\0"
    "SessionChangToChattingWindowSlot\0"
    "nim::SessionData\0sessionData\0"
    "OpenChattingWindowFromFriendListsSlot\0"
    "userNameCard\0OpenChattingWindowFromRecentSessionSlot\0"
    "CloseChattingWindowSlot\0id"
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
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,
       6,    1,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   76,    2, 0x0a /* Public */,
      10,    0,   77,    2, 0x0a /* Public */,
      11,    1,   78,    2, 0x0a /* Public */,
      14,    1,   81,    2, 0x0a /* Public */,
      17,    1,   84,    2, 0x0a /* Public */,
      20,    1,   87,    2, 0x0a /* Public */,
      22,    1,   90,    2, 0x0a /* Public */,
      23,    1,   93,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, 0x80000000 | 7,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 12,   21,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, QMetaType::QString,   24,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LogoutSignal(); break;
        case 1: _t->sendMsgCallbackSignal((*reinterpret_cast< const nim::SendMessageArc(*)>(_a[1]))); break;
        case 2: _t->receiveMsgSignal((*reinterpret_cast< const nim::IMMessage(*)>(_a[1]))); break;
        case 3: _t->ClickHeaderPhotoSlot(); break;
        case 4: _t->toolLabelChecked(); break;
        case 5: _t->UserCardChangeToChattingWindowSlot((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 6: _t->FriendProfileChangeToChattingWindowSlot((*reinterpret_cast< const nim::FriendProfile(*)>(_a[1]))); break;
        case 7: _t->SessionChangToChattingWindowSlot((*reinterpret_cast< const nim::SessionData(*)>(_a[1]))); break;
        case 8: _t->OpenChattingWindowFromFriendListsSlot((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 9: _t->OpenChattingWindowFromRecentSessionSlot((*reinterpret_cast< const nim::SessionData(*)>(_a[1]))); break;
        case 10: _t->CloseChattingWindowSlot((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::LogoutSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const nim::SendMessageArc & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::sendMsgCallbackSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(const nim::IMMessage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::receiveMsgSignal)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
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
    return QWidget::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MainWindow::LogoutSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MainWindow::sendMsgCallbackSignal(const nim::SendMessageArc & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MainWindow::receiveMsgSignal(const nim::IMMessage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
