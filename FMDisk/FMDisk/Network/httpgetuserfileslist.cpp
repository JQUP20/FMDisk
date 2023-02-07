#include "httpgetuserfileslist.h"
#include "Utils/enumData.h"
#include "Utils/constData.h"
#include "HttpSignal.h"
#include "Utils/commonFun.h"
#include "Utils/appConfigIni.h"
#include "Log/logging.h"
#include "Utils/Common.h"

HttpGetUserFilesList::HttpGetUserFilesList(LoginInfoInstance *loginInfoInstance, qint32 start, qint32 count, Display cmd)
{
    chooseRequestType(cmd);
    setReqUrlAddress(commonFun::getRequestUrl() + m_urlSuffix);

    qDebug() << ":HttpGetUserFilesList";

    cout << "cmd : " << cmd;

    cout << "start : " << start << " end : " << count;

    QByteArray array;

    array = setFilesListJson(loginInfoInstance->getUser(), loginInfoInstance->getToken(), start, count);
    setReqParams(array);
}

HttpGetUserFilesList::~HttpGetUserFilesList()
{

}

void HttpGetUserFilesList::processResponse(QByteArray strResult)
{
    QString nCode;
    nCode = Common::getInstance()->getCode(strResult);

    HttpSignal::instance()->RespondOnGetUserFilesList(nCode, strResult);
}

void HttpGetUserFilesList::processError()
{

}

void HttpGetUserFilesList::chooseRequestType(Display cmd)
{
    if (cmd == Normal)
    {
        m_urlSuffix = c_sHttpOrderGetUserFilesListInNormal;
    }
    else if (cmd == PvAsc)
    {
        m_urlSuffix = c_sHttpOrderGetUserFilesListInPvasc;
    }
    else if (cmd == PvDesc)
    {
        m_urlSuffix = c_sHttpOrderGetUserFilesListInPvdesc;
    }
}

QByteArray HttpGetUserFilesList::setFilesListJson(QString user, QString token, int start, int count)
{
    /*{
        "user": "yoyo"
        "token": "xxx"
        "start": 0
        "count": 10
    }*/
    QMap<QString, QVariant> tmp;
    tmp.insert("user", user);
    tmp.insert("token", token);
    tmp.insert("start", start);
    tmp.insert("count", count);

    QJsonDocument jsonDocument = QJsonDocument::fromVariant(tmp);
    if ( jsonDocument.isNull() )
    {
        cout << " jsonDocument.isNull() ";
        return "";
    }

    //cout << jsonDocument.toJson().data();

    return jsonDocument.toJson();
}
