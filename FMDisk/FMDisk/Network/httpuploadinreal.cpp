#include "httpuploadinreal.h"

#include "Utils/enumData.h"
#include "Utils/constData.h"
#include "HttpSignal.h"
#include "Utils/commonFun.h"
#include "Utils/appConfigIni.h"
#include "Log/logging.h"
#include "Utils/Common.h"


HttpUploadInReal::HttpUploadInReal(UploadFileInfo *uploadFileInfo, LoginInfoInstance *login)
{
    setReqUrlAddress(commonFun::getRequestUrl() + c_sHttpOrderUploadAction);

//    QString allParam = QString("phone=%1&pwd=%2").arg(nUser).arg(nPasswd);
//    QByteArray array;
    //array.append(allParam);
    //setReqParams(array);
    qDebug() << "HttpUploadInReal .. ";

    QString user = login->getUser();
//     QString user = "kevin_666";
//     QString fileName = "ui_filepropertyinfo.h";
//     QString md5 = "af4155758298348a918bc26db16e0af9";
//     qint64 size = 9871;

     qDebug() << "HttpUploadInReal : " << "uploadFileInfo : " << uploadFileInfo->fileName << " " << uploadFileInfo->size;

    setUploadFileInfo(user, uploadFileInfo->fileName, uploadFileInfo->md5, uploadFileInfo->size);
//    setUploadProgress(uploadFileInfo->dp);
}

HttpUploadInReal::~HttpUploadInReal()
{

}

void HttpUploadInReal::processResponse(QByteArray strResult)
{
    QString nCode = Common::getInstance()->getCode(strResult);

    HttpSignal::instance()->RespondOnUploadInReal(nCode);
}

void HttpUploadInReal::processError()
{

}

