#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include "Utils/HttpStructData.h"
#include "LoginWindow/logininfoinstance.h"


class HttpClient : public QObject
{
    Q_OBJECT
public:
    static HttpClient* instance();
    void setToken(QString sToken);

    void RequestOnLogin(QString nUser, QString nPasswd);
    void RequestOnRegister(RegisterInfo registerInfo, InterfaceInputHead header);
    void RequestOnUpload(UploadFileInfo *uploadFileInfo, LoginInfoInstance *login);
    void RequestOnUploadInReal(UploadFileInfo *uploadFileInfo, LoginInfoInstance *login);
    void RequestOnRefreshFiles(LoginInfoInstance *loginInfoInstance);
    void RequestOnGetUserFilesList(LoginInfoInstance *loginInfoInstance, qint32 start, qint32 count, Display cmd);
private:
    explicit HttpClient(QObject *parent = NULL);
    ~HttpClient();

private:
    static HttpClient* m_pInstance;
    QString m_strTokenInfo;
    QNetworkAccessManager* m_pManager;
    QString m_sToken;

};

#endif // HTTPCLIENT_H
