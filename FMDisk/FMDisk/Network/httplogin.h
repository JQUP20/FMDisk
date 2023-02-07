#ifndef HTTPLOGIN_H
#define HTTPLOGIN_H

#include <QObject>
#include "IHttpReqRes.h"
//#include "Utils/Common.h"

class HttpLogin : public IHttpReqRes
{
    Q_OBJECT

public:
    explicit HttpLogin(QString nUser, QString nPasswd);
    ~HttpLogin();

    // 设置登陆用户信息的json包
    QByteArray setLoginJson(QString nUser, QString nPasswd);

    // 得到服务器回复的登陆状态， 状态码返回值为 "000", 或 "001"，还有登陆section
    QStringList getLoginStatus(QByteArray json);

protected:
    void processResponse(QByteArray strResult);
    void processError();
private:
    int m_loginType;
   // Common m_cm;
};

#endif // HTTPLOGIN_H
