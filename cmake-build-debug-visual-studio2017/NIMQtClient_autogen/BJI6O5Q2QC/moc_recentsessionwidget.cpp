/****************************************************************************
** Meta object code from reading C++ file 'recentsessionwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../window/recentSessionWidget/recentsessionwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recentsessionwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RecentSessionWidget_t {
    QByteArrayData data[17];
    char stringdata0[259];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecentSessionWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecentSessionWidget_t qt_meta_stringdata_RecentSessionWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "RecentSessionWidget"
QT_MOC_LITERAL(1, 20, 23), // "UpdateSessionListSignal"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 19), // "AddOneSessionSignal"
QT_MOC_LITERAL(4, 65, 16), // "nim::SessionData"
QT_MOC_LITERAL(5, 82, 4), // "data"
QT_MOC_LITERAL(6, 87, 5), // "index"
QT_MOC_LITERAL(7, 93, 19), // "UpdateSessionSignal"
QT_MOC_LITERAL(8, 113, 11), // "sessionData"
QT_MOC_LITERAL(9, 125, 19), // "total_unread_counts"
QT_MOC_LITERAL(10, 145, 21), // "sendMsgCallbackSignal"
QT_MOC_LITERAL(11, 167, 19), // "nim::SendMessageArc"
QT_MOC_LITERAL(12, 187, 10), // "messageArc"
QT_MOC_LITERAL(13, 198, 16), // "receiveMsgSignal"
QT_MOC_LITERAL(14, 215, 14), // "nim::IMMessage"
QT_MOC_LITERAL(15, 230, 3), // "msg"
QT_MOC_LITERAL(16, 234, 24) // "OpenChattingWindowSignal"

    },
    "RecentSessionWidget\0UpdateSessionListSignal\0"
    "\0AddOneSessionSignal\0nim::SessionData\0"
    "data\0index\0UpdateSessionSignal\0"
    "sessionData\0total_unread_counts\0"
    "sendMsgCallbackSignal\0nim::SendMessageArc\0"
    "messageArc\0receiveMsgSignal\0nim::IMMessage\0"
    "msg\0OpenChattingWindowSignal"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecentSessionWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    2,   45,    2, 0x06 /* Public */,
       7,    2,   50,    2, 0x06 /* Public */,
      10,    1,   55,    2, 0x06 /* Public */,
      13,    1,   58,    2, 0x06 /* Public */,
      16,    1,   61,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    6,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 4,    8,

       0        // eod
};

void RecentSessionWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RecentSessionWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateSessionListSignal(); break;
        case 1: _t->AddOneSessionSignal((*reinterpret_cast< const nim::SessionData(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->UpdateSessionSignal((*reinterpret_cast< const nim::SessionData(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->sendMsgCallbackSignal((*reinterpret_cast< const nim::SendMessageArc(*)>(_a[1]))); break;
        case 4: _t->receiveMsgSignal((*reinterpret_cast< const nim::IMMessage(*)>(_a[1]))); break;
        case 5: _t->OpenChattingWindowSignal((*reinterpret_cast< const nim::SessionData(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (RecentSessionWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecentSessionWidget::UpdateSessionListSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RecentSessionWidget::*)(const nim::SessionData & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecentSessionWidget::AddOneSessionSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RecentSessionWidget::*)(const nim::SessionData & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecentSessionWidget::UpdateSessionSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RecentSessionWidget::*)(const nim::SendMessageArc & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecentSessionWidget::sendMsgCallbackSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (RecentSessionWidget::*)(const nim::IMMessage & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecentSessionWidget::receiveMsgSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (RecentSessionWidget::*)(const nim::SessionData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecentSessionWidget::OpenChattingWindowSignal)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RecentSessionWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QListWidget::staticMetaObject>(),
    qt_meta_stringdata_RecentSessionWidget.data,
    qt_meta_data_RecentSessionWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RecentSessionWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecentSessionWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RecentSessionWidget.stringdata0))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int RecentSessionWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void RecentSessionWidget::UpdateSessionListSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RecentSessionWidget::AddOneSessionSignal(const nim::SessionData & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RecentSessionWidget::UpdateSessionSignal(const nim::SessionData & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RecentSessionWidget::sendMsgCallbackSignal(const nim::SendMessageArc & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void RecentSessionWidget::receiveMsgSignal(const nim::IMMessage & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void RecentSessionWidget::OpenChattingWindowSignal(const nim::SessionData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE