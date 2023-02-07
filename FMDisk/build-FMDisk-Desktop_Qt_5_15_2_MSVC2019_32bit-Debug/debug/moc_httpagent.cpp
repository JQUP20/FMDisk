/****************************************************************************
** Meta object code from reading C++ file 'httpagent.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../FMDisk/Network/httpagent.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'httpagent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HttpAgent_t {
    QByteArrayData data[13];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HttpAgent_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HttpAgent_t qt_meta_stringdata_HttpAgent = {
    {
QT_MOC_LITERAL(0, 0, 9), // "HttpAgent"
QT_MOC_LITERAL(1, 10, 10), // "sigOnLogin"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 5), // "nCode"
QT_MOC_LITERAL(4, 28, 6), // "nToken"
QT_MOC_LITERAL(5, 35, 17), // "RespondOnRegister"
QT_MOC_LITERAL(6, 53, 15), // "RespondOnUpload"
QT_MOC_LITERAL(7, 69, 21), // "RespondOnUploadInReal"
QT_MOC_LITERAL(8, 91, 21), // "RespondOnRefreshFiles"
QT_MOC_LITERAL(9, 113, 5), // "sCode"
QT_MOC_LITERAL(10, 119, 6), // "nCount"
QT_MOC_LITERAL(11, 126, 25), // "RespondOnGetUserFilesList"
QT_MOC_LITERAL(12, 152, 14) // "responseResult"

    },
    "HttpAgent\0sigOnLogin\0\0nCode\0nToken\0"
    "RespondOnRegister\0RespondOnUpload\0"
    "RespondOnUploadInReal\0RespondOnRefreshFiles\0"
    "sCode\0nCount\0RespondOnGetUserFilesList\0"
    "responseResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HttpAgent[] = {

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
       1,    2,   44,    2, 0x06 /* Public */,
       5,    1,   49,    2, 0x06 /* Public */,
       6,    1,   52,    2, 0x06 /* Public */,
       7,    1,   55,    2, 0x06 /* Public */,
       8,    2,   58,    2, 0x06 /* Public */,
      11,    2,   63,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::Long,    9,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    9,   12,

       0        // eod
};

void HttpAgent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HttpAgent *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigOnLogin((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->RespondOnRegister((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->RespondOnUpload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->RespondOnUploadInReal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->RespondOnRefreshFiles((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 5: _t->RespondOnGetUserFilesList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HttpAgent::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpAgent::sigOnLogin)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HttpAgent::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpAgent::RespondOnRegister)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (HttpAgent::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpAgent::RespondOnUpload)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (HttpAgent::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpAgent::RespondOnUploadInReal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (HttpAgent::*)(QString , long );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpAgent::RespondOnRefreshFiles)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (HttpAgent::*)(QString , QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HttpAgent::RespondOnGetUserFilesList)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HttpAgent::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_HttpAgent.data,
    qt_meta_data_HttpAgent,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HttpAgent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HttpAgent::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HttpAgent.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int HttpAgent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void HttpAgent::sigOnLogin(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void HttpAgent::RespondOnRegister(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void HttpAgent::RespondOnUpload(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void HttpAgent::RespondOnUploadInReal(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void HttpAgent::RespondOnRefreshFiles(QString _t1, long _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void HttpAgent::RespondOnGetUserFilesList(QString _t1, QByteArray _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
