#ifndef HTTPREFRESHFILES_H
#define HTTPREFRESHFILES_H

#include <QObject>
#include "IHttpReqRes.h"
#include "LoginWindow/logininfoinstance.h"

class HttpRefreshFiles : public IHttpReqRes
{
public:
    explicit HttpRefreshFiles(LoginInfoInstance* loginInfoInstance);
    ~HttpRefreshFiles();

protected:
    void processResponse(QByteArray strResult);
    void processError();

private:
    // 设置json包
    QByteArray setGetCountJson(QString user, QString token);
    // 得到服务器json文件
    QStringList getCountStatus(QByteArray json);
};

#endif // HTTPREFRESHFILES_H
