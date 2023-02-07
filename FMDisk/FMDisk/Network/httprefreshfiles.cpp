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

    /*json��������
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

    //����Դ����jsonת��ΪJsonDocument
    //��QByteArray������һ��QJsonDocument�����������ǵĶ�д����
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError) //û�г���
    {
        if (doc.isNull() || doc.isEmpty())
        {
            cout << "doc.isNull() || doc.isEmpty()";
            return list;
        }

        if( doc.isObject() )
        {
            QJsonObject obj = doc.object();//ȡ���������������
            list.append( obj.value( "token" ).toString() ); //��½token
            list.append( obj.value( "num" ).toString() ); //�ļ�����
            qDebug() << "num : " << obj.value( "num" ).toString();
        }
    }
    else
    {
        cout << "err = " << error.errorString();
    }

    return list;
}
