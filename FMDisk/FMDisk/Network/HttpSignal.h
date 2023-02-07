#ifndef HTTPSIGNAL_H
#define HTTPSIGNAL_H

#include <QObject>
#include "Utils/HttpStructData.h"

class HttpSignal : public QObject
{
    Q_OBJECT
public:
    static HttpSignal* instance();
private:
    explicit HttpSignal(QObject *parent = 0);
    ~HttpSignal();
signals:
    void sigOnLogin(QString nCode, QString sMsg);

    void ResponseOnRegister(QString nCode);

    void RespondOnUpload(QString nCode);

    void RespondOnUploadInReal(QString nCode);

    void RespondRefreshFiles(QString sCode, long nCount);
    //
    void RespondOnGetUserFilesList(QString sCode,QByteArray responseResult);


private:
    static HttpSignal* m_pInstance;
};

#endif // HTTPSIGNAL_H
