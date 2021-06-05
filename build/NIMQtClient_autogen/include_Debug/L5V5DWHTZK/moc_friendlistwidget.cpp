/****************************************************************************
** Meta object code from reading C++ file 'friendlistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../window/friendsWidget/friendlistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'friendlistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FriendListWidget_t {
    QByteArrayData data[19];
    char stringdata0[384];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FriendListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FriendListWidget_t qt_meta_stringdata_FriendListWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "FriendListWidget"
QT_MOC_LITERAL(1, 17, 18), // "AddOneFriendSignal"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 17), // "nim::UserNameCard"
QT_MOC_LITERAL(4, 55, 12), // "userNameCard"
QT_MOC_LITERAL(5, 68, 24), // "OpenChattingWindowSignal"
QT_MOC_LITERAL(6, 93, 25), // "InitUserNameCardMapSignal"
QT_MOC_LITERAL(7, 119, 31), // "QMap<QString,nim::UserNameCard>"
QT_MOC_LITERAL(8, 151, 11), // "userNameMap"
QT_MOC_LITERAL(9, 163, 26), // "InitFriendProfileMapSignal"
QT_MOC_LITERAL(10, 190, 32), // "QMap<QString,nim::FriendProfile>"
QT_MOC_LITERAL(11, 223, 12), // "friendProMap"
QT_MOC_LITERAL(12, 236, 24), // "UpdateUserNameCardSignal"
QT_MOC_LITERAL(13, 261, 25), // "UpdateFriendProfileSignal"
QT_MOC_LITERAL(14, 287, 18), // "nim::FriendProfile"
QT_MOC_LITERAL(15, 306, 13), // "friendProfile"
QT_MOC_LITERAL(16, 320, 16), // "AddOneFriendSlot"
QT_MOC_LITERAL(17, 337, 22), // "UpdateUserNameCardSlot"
QT_MOC_LITERAL(18, 360, 23) // "UpdateFriendProfileSlot"

    },
    "FriendListWidget\0AddOneFriendSignal\0"
    "\0nim::UserNameCard\0userNameCard\0"
    "OpenChattingWindowSignal\0"
    "InitUserNameCardMapSignal\0"
    "QMap<QString,nim::UserNameCard>\0"
    "userNameMap\0InitFriendProfileMapSignal\0"
    "QMap<QString,nim::FriendProfile>\0"
    "friendProMap\0UpdateUserNameCardSignal\0"
    "UpdateFriendProfileSignal\0nim::FriendProfile\0"
    "friendProfile\0AddOneFriendSlot\0"
    "UpdateUserNameCardSlot\0UpdateFriendProfileSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FriendListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       6,    1,   65,    2, 0x06 /* Public */,
       9,    1,   68,    2, 0x06 /* Public */,
      12,    1,   71,    2, 0x06 /* Public */,
      13,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    1,   77,    2, 0x0a /* Public */,
      17,    1,   80,    2, 0x0a /* Public */,
      18,    1,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 14,   15,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 14,   15,

       0        // eod
};

void FriendListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FriendListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddOneFriendSignal((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 1: _t->OpenChattingWindowSignal((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 2: _t->InitUserNameCardMapSignal((*reinterpret_cast< const QMap<QString,nim::UserNameCard>(*)>(_a[1]))); break;
        case 3: _t->InitFriendProfileMapSignal((*reinterpret_cast< const QMap<QString,nim::FriendProfile>(*)>(_a[1]))); break;
        case 4: _t->UpdateUserNameCardSignal((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 5: _t->UpdateFriendProfileSignal((*reinterpret_cast< const nim::FriendProfile(*)>(_a[1]))); break;
        case 6: _t->AddOneFriendSlot((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 7: _t->UpdateUserNameCardSlot((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 8: _t->UpdateFriendProfileSlot((*reinterpret_cast< const nim::FriendProfile(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FriendListWidget::*)(const nim::UserNameCard & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::AddOneFriendSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(const nim::UserNameCard & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::OpenChattingWindowSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(const QMap<QString,nim::UserNameCard> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::InitUserNameCardMapSignal)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(const QMap<QString,nim::FriendProfile> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::InitFriendProfileMapSignal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(const nim::UserNameCard & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::UpdateUserNameCardSignal)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(const nim::FriendProfile & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::UpdateFriendProfileSignal)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FriendListWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QListWidget::staticMetaObject>(),
    qt_meta_stringdata_FriendListWidget.data,
    qt_meta_data_FriendListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FriendListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FriendListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FriendListWidget.stringdata0))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int FriendListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
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
void FriendListWidget::AddOneFriendSignal(const nim::UserNameCard & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FriendListWidget::OpenChattingWindowSignal(const nim::UserNameCard & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FriendListWidget::InitUserNameCardMapSignal(const QMap<QString,nim::UserNameCard> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void FriendListWidget::InitFriendProfileMapSignal(const QMap<QString,nim::FriendProfile> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FriendListWidget::UpdateUserNameCardSignal(const nim::UserNameCard & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FriendListWidget::UpdateFriendProfileSignal(const nim::FriendProfile & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
