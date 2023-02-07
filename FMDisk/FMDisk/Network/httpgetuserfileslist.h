#ifndef HTTPGETUSERFILESLIST_H
#define HTTPGETUSERFILESLIST_H

#include <QObject>
#include "ihttpreqres.h"
#include "LoginWindow/logininfoinstance.h"

class HttpGetUserFilesList : public IHttpReqRes
{
    Q_OBJECT
public:
    explicit HttpGetUserFilesList(LoginInfoInstance *loginInfoInstance, qint32 start, qint32 count, Display cmd);
    ~HttpGetUserFilesList();

protected:
    void processResponse(QByteArray strResult);
    void processError();

private:
    void chooseRequestType(Display cmd);
    // …Ë÷√json∞¸
    QByteArray setFilesListJson(QString user, QString token, int start, int count);

private:
    QString m_urlSuffix;

};

#endif // HTTPGETUSERFILESLIST_H
