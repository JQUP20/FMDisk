#include "httprefreshfiles.h"

#include "Utils/enumData.h"
#include "Utils/constData.h"
#include "HttpSignal.h"
#include "Utils/commonFun.h"
#include "Utils/appConfigIni.h"
#include "Log/logging.h"
#include "Utils/Common.h"


HttpRefreshFiles::HttpRefreshFiles(LoginInfoInstance *loginInfoInstance)
{
    setReqUrlAddress(commonFun::getRequestUrl() + c_sHttpOrderRefreshFilesAction);

    QByteArray array;

    QString user = loginInfoInstance->getUser();
    QString token = loginInfoInstance->getToken();

    array = setGetCountJson(user, token);

    setReqParams(array);
}

HttpRefreshFiles::~HttpRefreshFiles()
{

}

void HttpRefreshFiles::processResponse(QByteArray strResult)
{
    qDebug() << "HttpRefreshFiles::processResponse ";

    qDebug() << "strResult : " << strResult;

    QStringList list = getCountStatus(strResult);

    QString sCode = list.at(0);
    long nCount = list.at(1).toLong();

    qDebug() << "nCount : " << nCount;

    HttpSignal::instance()->RespondRefreshFiles(sCode, nCount);
}

void HttpRefreshFiles::processError()
{

}

QByteArray HttpRefreshFiles::setGetCountJson(QString user, QString token)
{
    QMap<QString, QVariant> tmp;
    tmp.insert("user", user);
    tmp.insert("token", token);

    /*json数据如下
    {
        user:xxxx
        token: xxxx
    }
    */
    QJsonDocument jsonDocument = QJsonDocument::fromVariant(tmp);
    if ( jsonDocument.isNull() )
    {
        cout << " jsonDocument.isNull() ";
        return "";
    }

    //cout << jsonDocument.toJson().data();
    return jsonDocument.toJson();
}

QStringList HttpRefreshFiles::getCountStatus(QByteArray json)
{
    QJsonParseError error;
    QStringList list;

    //cout << "json = " << json.data();

    //将来源数据json转化为JsonDocument
    //由QByteArray对象构造一个QJsonDocument对象，用于我们的读写操作
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError) //没有出错
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return list;
        }

        if( doc.isObject() )
        {
            QJsonObject obj = doc.object();//取得最外层这个大对象
            list.append( obj.value( "token" ).toString() ); //登陆token
            list.append( obj.value( "num" ).toString() ); //文件个数
            qDebug() << "num : " << obj.value( "num" ).toString();
        }
    }
    else
    {
        cout << "err = " << error.errorString();
    }

    return list;
}
