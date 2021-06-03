/****************************************************************************
** Meta object code from reading C++ file 'friendlistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../window/friendsWidget/friendlistwidget.h"
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
    QByteArrayData data[9];
    char stringdata0[146];
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
QT_MOC_LITERAL(5, 68, 18), // "UpdateFriendSignal"
QT_MOC_LITERAL(6, 87, 24), // "OpenChattingWindowSignal"
QT_MOC_LITERAL(7, 112, 16), // "AddOneFriendSlot"
QT_MOC_LITERAL(8, 129, 16) // "UpdateFriendSlot"

    },
    "FriendListWidget\0AddOneFriendSignal\0"
    "\0nim::UserNameCard\0userNameCard\0"
    "UpdateFriendSignal\0OpenChattingWindowSignal\0"
    "AddOneFriendSlot\0UpdateFriendSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FriendListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    1,   42,    2, 0x06 /* Public */,
       6,    1,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   48,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void FriendListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FriendListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AddOneFriendSignal((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 1: _t->UpdateFriendSignal((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 2: _t->OpenChattingWindowSignal((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 3: _t->AddOneFriendSlot((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
        case 4: _t->UpdateFriendSlot((*reinterpret_cast< const nim::UserNameCard(*)>(_a[1]))); break;
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
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::UpdateFriendSignal)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(const nim::UserNameCard & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::OpenChattingWindowSignal)) {
                *result = 2;
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
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
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
void FriendListWidget::UpdateFriendSignal(const nim::UserNameCard & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FriendListWidget::OpenChattingWindowSignal(const nim::UserNameCard & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
