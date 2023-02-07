#ifndef IHTTPREQRES_H
#define IHTTPREQRES_H

#include <QObject>
#include <QtNetwork>
#include <QSslConfiguration>
#include "Utils/appConfigIni.h"
#include "MainPages/uploadtask.h"

using namespace std;

class IHttpReqRes : public QObject
{
    Q_OBJECT

public:
    IHttpReqRes(QObject *parent = 0);
    ~IHttpReqRes();

    void setNetManager(QNetworkAccessManager* pManager);
    void setReqParams(QByteArray byArr);
    void setFilePath(QString filePath);
    void setUploadFileInfo(QString user, QString filename, QString md5, qint64 size);
    void setUploadProgress(DataProgress *dataprogress);

    void postRequest();
    void postFaceTection();
    void postFaceData(QString sIdCard, QString sName);
    void postUpload(UploadFileInfo *uploadFileInfo);
    QString getTestUrl(); // 测试用
    void setOverTimeLengh(int nOverTimeLengh); // 设置超时时长
    bool isOverTime(); // 请求是否超时
protected:
    virtual void processResponse(QByteArray strResult) = 0;
    virtual void processError() = 0;
    virtual void setReqUrlAddress(QString urlAddress);
private slots:
    void slot_ReplyFinished();
    void slot_overTimeout();

private:
    void initConnect();
protected:
    QNetworkAccessManager*  m_pManager;
    QNetworkRequest			m_request;
    QNetworkReply*          m_pReply;
    QByteArray				m_reqParams;
    int						m_nReconnectTimes;
    //QString					m_strResult;
    QString m_sUrlAddress;
    QString m_sTestUrl; // 测试用
    QTimer m_overTimer; // 超时定时器
    int m_nOverTimeLen; // 超时时长
    bool m_bOverTime; // 是否超时
    QString m_filePath;
    QFile *m_file;
    QFile *m_fileGroup[5];

    QString m_user;
    QString m_fileName;
    QString m_md5;
    qint64 m_size;

    DataProgress *m_dataProgress;
};

#endif // IHTTPREQRES_H
