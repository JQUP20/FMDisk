#include "httpregister.h"

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

HttpRegister::HttpRegister(RegisterInfo registerInfo, InterfaceInputHead header)
{
    setReqUrlAddress(commonFun::getRequestUrl() + c_sHttpOrderRegisterAction);

//    QString allParam = QString("phone=%1&pwd=%2").arg(nUser).arg(nPasswd);
    QByteArray array;
    //array.append(allParam);
    //setReqParams(array);

  //  QString encPwd = Common::getInstance()->getStrMd5(registerInfo.firstPassWd);
   // array = setLoginJson(registerInfo.user, encPwd);
    array = createRegisterJson(registerInfo, header);
    setReqParams(array);
}

HttpRegister::~HttpRegister()
{

}

void HttpRegister::processResponse(QByteArray strResult)
{
    QString nCode = Common::getInstance()->getCode(strResult); //common.h


    HttpSignal::instance()->ResponseOnRegister(nCode);
}

void HttpRegister::processError()
{

}

QByteArray HttpRegister::createRegisterJson(RegisterInfo registerInfo, InterfaceInputHead header)
{
    QMap<QString, QVariant> reg;
    QString encPwd = Common::getInstance()->getStrMd5(registerInfo.firstPassWd);
    reg.insert("userName", registerInfo.user);
    reg.insert("nickName", registerInfo.nickName);
    reg.insert("firstPwd", encPwd);
    reg.insert("phone", registerInfo.phone);
    reg.insert("email", registerInfo.mail);

    /*json数据如下
        {
            userName:xxxx,
            nickName:xxx,
            firstPwd:xxx,
            phone:xxx,
            email:xxx
        }
    */
    QJsonDocument jsonDocument = QJsonDocument::fromVariant(reg);

    if ( jsonDocument.isNull() )
    {
        //cout << " jsonDocument.isNull() ";
        return "";
    }

    //cout << jsonDocument.toJson().data();

    return jsonDocument.toJson();
}
