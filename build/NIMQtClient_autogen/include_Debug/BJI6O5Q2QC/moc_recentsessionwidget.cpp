/****************************************************************************
** Meta object code from reading C++ file 'recentsessionwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../window/recentSessionWidget/recentsessionwidget.h"
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
    QByteArrayData data[22];
    char stringdata0[398];
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
QT_MOC_LITERAL(6, 87, 3), // "row"
QT_MOC_LITERAL(7, 91, 19), // "UpdateSessionSignal"
QT_MOC_LITERAL(8, 111, 11), // "sessionData"
QT_MOC_LITERAL(9, 123, 24), // "OpenChattingWindowSignal"
QT_MOC_LITERAL(10, 148, 23), // "InitUserNameCardMapSlot"
QT_MOC_LITERAL(11, 172, 31), // "QMap<QString,nim::UserNameCard>"
QT_MOC_LITERAL(12, 204, 11), // "userNameMap"
QT_MOC_LITERAL(13, 216, 24), // "InitFriendProfileMapSlot"
QT_MOC_LITERAL(14, 241, 32), // "QMap<QString,nim::FriendProfile>"
QT_MOC_LITERAL(15, 274, 12), // "friendProMap"
QT_MOC_LITERAL(16, 287, 22), // "UpdateUserNameCardSlot"
QT_MOC_LITERAL(17, 310, 17), // "nim::UserNameCard"
QT_MOC_LITERAL(18, 328, 12), // "userNameCard"
QT_MOC_LITERAL(19, 341, 23), // "UpdateFriendProfileSlot"
QT_MOC_LITERAL(20, 365, 18), // "nim::FriendProfile"
QT_MOC_LITERAL(21, 384, 13) // "friendProfile"

    },
    "RecentSessionWidget\0UpdateSessionListSignal\0"
    "\0AddOneSessionSignal\0nim::SessionData\0"
    "data\0row\0UpdateSessionSignal\0sessionData\0"
    "OpenChattingWindowSignal\0"
    "InitUserNameCardMapSlot\0"
    "QMap<QString,nim::UserNameCard>\0"
    "userNameMap\0InitFriendProfileMapSlot\0"
    "QMap<QString,nim::FriendProfile>\0"
    "friendProMap\0UpdateUserNameCardSlot\0"
    "nim::UserNameCard\0userNameCard\0"
    "UpdateFriendProfileSlot\0nim::FriendProfile\0"
    "friendProfile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecentSessionWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    2,   55,    2, 0x06 /* Public */,
       7,    1,   60,    2, 0x06 /* Public */,
       9,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    1,   66,    2, 0x0a /* Public */,
      13,    1,   69,    2, 0x0a /* Public */,
      16,    1,   72,    2, 0x0a /* Public */,
      19,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Int,    5,    6,
    QMetaType::Void, 0x80000000 | 4,    8,
    QMetaType::Void, 0x80000000 | 4,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 20,   21,

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
        case 2: _t->UpdateSessionSignal((*reinterpret_cast< const nim::SessionData(*)>(_a[1]))); break;
        case 3: _t->OpenChattingWindowSignal((*reinterpret_cast< const nim::SessionData(*)>(_a[1]))); break;
        case 4: _t->InitUserNameCardMapSlot((*reinterpret_cast< const QMap<QString,nim::UserNameCard>(*)>(_a[1]))); break;
        case 5: _t->InitFriendProfileMapSlot((*reinterpret_cast< const QMap<QString,nim::FriendProfile>(*)>(_a[1]))); break;
        case 6: _t->UpdateUserNameCardSlot((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 7: _t->UpdateFriendProfileSlot((*reinterpret_cast< const nim::FriendProfile(*)>(_a[1]))); break;
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
            using _t = void (RecentSessionWidget::*)(const nim::SessionData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecentSessionWidget::UpdateSessionSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (RecentSessionWidget::*)(const nim::SessionData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecentSessionWidget::OpenChattingWindowSignal)) {
                *result = 3;
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
void RecentSessionWidget::UpdateSessionSignal(const nim::SessionData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void RecentSessionWidget::OpenChattingWindowSignal(const nim::SessionData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE