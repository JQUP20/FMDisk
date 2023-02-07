#ifndef HTTPUPLOADINREAL_H
#define HTTPUPLOADINREAL_H

#include <QObject>
#include "ihttpreqres.h"
#include "Utils/HttpStructData.h"
#include "LoginWindow/logininfoinstance.h"

class HttpUploadInReal : public IHttpReqRes
{
    Q_OBJECT
public:
    explicit HttpUploadInReal(UploadFileInfo* uploadFileInfo, LoginInfoInstance* login);
    ~HttpUploadInReal();

protected:
    void processResponse(QByteArray strResult);
    void processError();

};

#endif // HTTPUPLOADINREAL_H
