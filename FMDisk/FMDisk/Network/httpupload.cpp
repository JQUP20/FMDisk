#include "httpupload.h"
#include <QScriptEngine>
#include <QScriptValue>

//#include "Utils/appconfig.h"
#include "Utils/enumData.h"
#include "Utils/constData.h"
#include "HttpSignal.h"
#include "Utils/commonFun.h"
#include "Utils/appConfigIni.h"
#include "Log/logging.h"
#include "Utils/Common.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>


HttpUpload::HttpUpload(UploadFileInfo *uploadFileInfo, LoginInfoInstance *login)
{
    setReqUrlAddress(commonFun::getRequestUrl() + c_sHttpOrderMd5CheckAction);

//    QString allParam = QString("phone=%1&pwd=%2").arg(nUser).arg(nPasswd);
    QByteArray array;
    //array.append(allParam);
    //setReqParams(array);

    array = setMd5Json(login->getUser(), login->getToken(), uploadFileInfo->md5, uploadFileInfo->fileName);
    setReqParams(array);
}

HttpUpload::~HttpUpload()
{

}

void HttpUpload::processResponse(QByteArray strResult)
{
      QString nCode = Common::getInstance()->getCode(strResult);

      HttpSignal::instance()->RespondOnUpload(nCode);
}

void HttpUpload::processError()
{

}

QByteArray HttpUpload::setMd5Json(QString user, QString token, QString md5, QString fileName)
{
    QMap<QString, QVariant> tmp;
    tmp.insert("user", user);
    tmp.insert("token", token);
    tmp.insert("md5", md5);
    tmp.insert("fileName", fileName);

    /*json数据如下
    {
        user:xxxx,
        token:xxxx,
        md5:xxx,
        fileName: xxx
    }
    */
    QJsonDocument jsonDocument = QJsonDocument::fromVariant(tmp);
    if ( jsonDocument.isNull() )
    {
       // cout << " jsonDocument.isNull() ";
        return "";
    }

    //cout << jsonDocument.toJson().data();

    return jsonDocument.toJson();
}
