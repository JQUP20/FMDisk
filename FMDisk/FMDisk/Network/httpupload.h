#ifndef HTTPUPLOAD_H
#define HTTPUPLOAD_H

#include <QObject>
#include "ihttpreqres.h"
#include "Utils/HttpStructData.h"
#include "LoginWindow/logininfoinstance.h"

class HttpUpload : public IHttpReqRes
{
    Q_OBJECT
public:
    explicit HttpUpload(UploadFileInfo* uploadFileInfo, LoginInfoInstance* login);
    ~HttpUpload();

protected:
    void processResponse(QByteArray strResult);
    void processError();

    // ����md5��Ϣ��json��
    QByteArray setMd5Json(QString user, QString token, QString md5, QString fileName);

};

#endif // HTTPUPLOAD_H
