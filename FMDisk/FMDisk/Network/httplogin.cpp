#include "httplogin.h"
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

HttpLogin::HttpLogin(QString nUser, QString nPasswd)
{
   // m_loginType = nType;
    setReqUrlAddress(commonFun::getRequestUrl() + c_sHttpOrderLoginAction);

    QString allParam = QString("phone=%1&pwd=%2").arg(nUser).arg(nPasswd);
    QByteArray array;
    //array.append(allParam);
    //setReqParams(array);

    QString encPwd = Common::getInstance()->getStrMd5(nPasswd);
    array = setLoginJson(nUser, encPwd);
    setReqParams(array);
}

HttpLogin::~HttpLogin()
{

}

QByteArray HttpLogin::setLoginJson(QString nUser, QString nPasswd)
{
    QMap<QString, QVariant> loginInfo;
    loginInfo.insert("user", nUser);
    loginInfo.insert("pwd", nPasswd);

    /*json��������
        {
            user:xxxx,
            pwd:xxx
        }
    */

    QJsonDocument jsonDocument = QJsonDocument::fromVariant(loginInfo);
    if ( jsonDocument.isNull() )
    {
      //  qDebug() << " jsonDocument.isNull() ";
        return "";
    }

    return jsonDocument.toJson();
}

QStringList HttpLogin::getLoginStatus(QByteArray json)
{
    QJsonParseError error;
    QStringList list;

    // ����Դ����jsonת��ΪJsonDocument
    // ��QByteArray������һ��QJsonDocument�����������ǵĶ�д����
    QJsonDocument doc = QJsonDocument::fromJson(json, &error);
    if (error.error == QJsonParseError::NoError)
    {
        if (doc.isNull() || doc.isEmpty())
        {
            //cout << "doc.isNull() || doc.isEmpty()";
            return list;
        }

        if( doc.isObject() )
        {
            //ȡ���������������
            QJsonObject obj = doc.object();
            //cout << "���������ص�����" << obj;
            //״̬��
            list.append( obj.value( "code" ).toString() );
            //��½token
            list.append( obj.value( "token" ).toString() );
        }
    }
    else
    {
        //cout << "err = " << error.errorString();
    }

    return list;
}

void HttpLogin::processResponse(QByteArray strResult)
{
//    QScriptEngine engine;
//    QScriptValue sc = engine.evaluate("value=" + strResult);
//    int nCode = sc.property("code").toInt32();
//    QString sMsg = sc.property("desc").toString();
//    /*
//        ��½ - ��������д��json���ݰ���ʽ��
//            �ɹ���{"code":"000"}
//            ʧ�ܣ�{"code":"001"}
//    */
//    if (!sc.property("code").isValid())
//    {
//        //AppConfigHandler.Info(QStringLiteral("HttpLogin ���ز���json��ʽ����").toStdString());
//        Log::Info("HttpLogin ���ز���json��ʽ����");
//        nCode = e_connectServerError;
//        //sMsg = c_sServerJsonError;
//    }
//    if (nCode != e_success)
//    {
//        //AppConfigHandler.Info(this->getTestUrl().toStdString());
//        Log::Info("%s", this->getTestUrl().toStdString().c_str());
//    }

//    //AppConfigHandler.Info("HttpLogin" + strResult.toStdString());
//    Log::Info("HttpLogin %s", strResult.toStdString().c_str());
//    QString userId = sc.property("data").property("id").toString();
//    QString userName = sc.property("data").property("name").toString();
//    if (m_loginType == t_login)
//    {
//        HttpSignal::instance()->sigOnLogin(nCode, sMsg, userName, userId);
//    }
//    else if (m_loginType == t_switch)
//    {
//      //  HttpSignal::instance()->sigOnSwitch(nCode, sMsg, userName, userId);
//    }
//    else if (m_loginType == t_shift)
//    {
//        //HttpSignal::instance()->sigOnShiftLogin(nCode, sMsg, userName, userId);
//    }
//    this->deleteLater();

    QStringList tmpList = getLoginStatus(strResult); //common.h
    QString nCode = tmpList.at(0);
    QString nToken = tmpList.at(1);
//    if( nCode == "000" )
//    {
//        Log::Info("login success");

        // ���õ�½��Ϣ����ʾ�ļ��б������Ҫʹ����Щ��Ϣ
        HttpSignal::instance()->sigOnLogin(nCode, nToken);
//    }
//    else
//    {
//       // QMessageBox::warning(this, "��¼ʧ��", "�û��������벻��ȷ������");
//    }

    this->deleteLater(); //�ͷ���Դ
}

void HttpLogin::processError()
{
    if (m_loginType == t_login)
    {
       // HttpSignal::instance()->sigOnLogin(e_connectServerError, c_sNetError, "", "");
    }
    else if (m_loginType == t_switch)
    {
       // HttpSignal::instance()->sigOnSwitch(e_connectServerError, c_sNetError, "", "");
    }
    else if (m_loginType == t_shift)
    {
        //HttpSignal::instance()->sigOnShiftLogin(e_connectServerError, c_sNetError, "", "");
    }
    this->deleteLater();
}

