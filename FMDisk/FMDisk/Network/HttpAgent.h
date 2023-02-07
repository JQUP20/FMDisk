#ifndef HTTPAGENT_H
#define HTTPAGENT_H

#include <QObject>
#include "Utils/HttpStructData.h"
#include "MainPages/filelistpage.h"
#include "LoginWindow/logininfoinstance.h"

class HttpAgent : public QObject
{
    Q_OBJECT

public:
    static HttpAgent* instance();

    void RequestOnLogin(QString nUser, QString nPasswd);
    //
    void RequestOnRegister(RegisterInfo registerInfo, InterfaceInputHead header);
    //
    void RequestOnUpload(UploadFileInfo* uploadFileInfo, LoginInfoInstance* login);

    void RequestOnUploadInReal(UploadFileInfo* uploadFileInfo, LoginInfoInstance* loginInfoInstance);

    void RequestOnDownload(DownloadFileInfo downloadFileInfo);
    //
    void RequestOnRefreshFiles(LoginInfoInstance* loginInfoInstance);
    //
    void RequestOnGetUserFilesList(LoginInfoInstance* loginInfoInstance, qint32 start, qint32 count, Display cmd);


private:
    explicit HttpAgent(QObject *parent = 0);
    ~HttpAgent();

    void initConnect();

signals:
    void sigOnLogin(QString nCode, QString nToken);
    void RespondOnRegister(QString nCode);
    void RespondOnUpload(QString nCode);
    void RespondOnUploadInReal(QString nCode);
    void RespondOnRefreshFiles(QString sCode, long nCount);
    void RespondOnGetUserFilesList(QString sCode, QByteArray responseResult);

private:
    static HttpAgent* m_pInstance;
};

#endif // HTTPAGENT_H
