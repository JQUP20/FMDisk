/****************************************************************************
** Meta object code from reading C++ file 'filelistpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../FMDisk/MainPages/filelistpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filelistpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileListPage_t {
    QByteArrayData data[29];
    char stringdata0[463];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileListPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileListPage_t qt_meta_stringdata_FileListPage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "FileListPage"
QT_MOC_LITERAL(1, 13, 16), // "loginAgainSignal"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 12), // "gotoTransfer"
QT_MOC_LITERAL(4, 44, 14), // "TransferStatus"
QT_MOC_LITERAL(5, 59, 6), // "status"
QT_MOC_LITERAL(6, 66, 15), // "RequestOnUpload"
QT_MOC_LITERAL(7, 82, 21), // "RequestOnUploadInReal"
QT_MOC_LITERAL(8, 104, 15), // "UploadFileInfo*"
QT_MOC_LITERAL(9, 120, 14), // "uploadFileInfo"
QT_MOC_LITERAL(10, 135, 17), // "RequestOnDownload"
QT_MOC_LITERAL(11, 153, 17), // "DownloadFileInfo*"
QT_MOC_LITERAL(12, 171, 16), // "downloadFileInfo"
QT_MOC_LITERAL(13, 188, 21), // "RequestOnRefreshFiles"
QT_MOC_LITERAL(14, 210, 7), // "Display"
QT_MOC_LITERAL(15, 218, 3), // "cmd"
QT_MOC_LITERAL(16, 222, 25), // "RequestOnGetUserFilesList"
QT_MOC_LITERAL(17, 248, 16), // "slotOnUploadFile"
QT_MOC_LITERAL(18, 265, 22), // "slotOnUploadFileInReal"
QT_MOC_LITERAL(19, 288, 18), // "slotOnDownloadFile"
QT_MOC_LITERAL(20, 307, 18), // "slotOnRefreshFiles"
QT_MOC_LITERAL(21, 326, 22), // "slotOnGetUserFilesList"
QT_MOC_LITERAL(22, 349, 15), // "RespondOnUpload"
QT_MOC_LITERAL(23, 365, 5), // "nCode"
QT_MOC_LITERAL(24, 371, 21), // "RespondOnUploadInReal"
QT_MOC_LITERAL(25, 393, 21), // "RespondOnRefreshFiles"
QT_MOC_LITERAL(26, 415, 6), // "nCount"
QT_MOC_LITERAL(27, 422, 25), // "RespondOnGetUserFilesList"
QT_MOC_LITERAL(28, 448, 14) // "responseResult"

    },
    "FileListPage\0loginAgainSignal\0\0"
    "gotoTransfer\0TransferStatus\0status\0"
    "RequestOnUpload\0RequestOnUploadInReal\0"
    "UploadFileInfo*\0uploadFileInfo\0"
    "RequestOnDownload\0DownloadFileInfo*\0"
    "downloadFileInfo\0RequestOnRefreshFiles\0"
    "Display\0cmd\0RequestOnGetUserFilesList\0"
    "slotOnUploadFile\0slotOnUploadFileInReal\0"
    "slotOnDownloadFile\0slotOnRefreshFiles\0"
    "slotOnGetUserFilesList\0RespondOnUpload\0"
    "nCode\0RespondOnUploadInReal\0"
    "RespondOnRefreshFiles\0nCount\0"
    "RespondOnGetUserFilesList\0responseResult"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileListPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    1,   95,    2, 0x06 /* Public */,
       6,    0,   98,    2, 0x06 /* Public */,
       7,    1,   99,    2, 0x06 /* Public */,
      10,    1,  102,    2, 0x06 /* Public */,
      13,    1,  105,    2, 0x06 /* Public */,
      16,    1,  108,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  111,    2, 0x08 /* Private */,
      18,    1,  112,    2, 0x08 /* Private */,
      19,    1,  115,    2, 0x08 /* Private */,
      20,    1,  118,    2, 0x08 /* Private */,
      21,    1,  121,    2, 0x08 /* Private */,
      22,    1,  124,    2, 0x08 /* Private */,
      24,    1,  127,    2, 0x08 /* Private */,
      25,    2,  130,    2, 0x08 /* Private */,
      27,    2,  135,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void, QMetaType::QString, QMetaType::Long,   23,   26,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,   23,   28,

       0        // eod
};

void FileListPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileListPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginAgainSignal(); break;
        case 1: _t->gotoTransfer((*reinterpret_cast< TransferStatus(*)>(_a[1]))); break;
        case 2: _t->RequestOnUpload(); break;
        case 3: _t->RequestOnUploadInReal((*reinterpret_cast< UploadFileInfo*(*)>(_a[1]))); break;
        case 4: _t->RequestOnDownload((*reinterpret_cast< DownloadFileInfo*(*)>(_a[1]))); break;
        case 5: _t->RequestOnRefreshFiles((*reinterpret_cast< Display(*)>(_a[1]))); break;
        case 6: _t->RequestOnGetUserFilesList((*reinterpret_cast< Display(*)>(_a[1]))); break;
        case 7: _t->slotOnUploadFile(); break;
        case 8: _t->slotOnUploadFileInReal((*reinterpret_cast< UploadFileInfo*(*)>(_a[1]))); break;
        case 9: _t->slotOnDownloadFile((*reinterpret_cast< DownloadFileInfo*(*)>(_a[1]))); break;
        case 10: _t->slotOnRefreshFiles((*reinterpret_cast< Display(*)>(_a[1]))); break;
        case 11: _t->slotOnGetUserFilesList((*reinterpret_cast< Display(*)>(_a[1]))); break;
        case 12: _t->RespondOnUpload((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->RespondOnUploadInReal((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->RespondOnRefreshFiles((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< long(*)>(_a[2]))); break;
        case 15: _t->RespondOnGetUserFilesList((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QByteArray(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FileListPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileListPage::loginAgainSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FileListPage::*)(TransferStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileListPage::gotoTransfer)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FileListPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileListPage::RequestOnUpload)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FileListPage::*)(UploadFileInfo * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileListPage::RequestOnUploadInReal)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FileListPage::*)(DownloadFileInfo * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileListPage::RequestOnDownload)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FileListPage::*)(Display );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileListPage::RequestOnRefreshFiles)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FileListPage::*)(Display );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileListPage::RequestOnGetUserFilesList)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FileListPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_FileListPage.data,
    qt_meta_data_FileListPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FileListPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileListPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileListPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int FileListPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void FileListPage::loginAgainSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void FileListPage::gotoTransfer(TransferStatus _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FileListPage::RequestOnUpload()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void FileListPage::RequestOnUploadInReal(UploadFileInfo * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void FileListPage::RequestOnDownload(DownloadFileInfo * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void FileListPage::RequestOnRefreshFiles(Display _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void FileListPage::RequestOnGetUserFilesList(Display _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
