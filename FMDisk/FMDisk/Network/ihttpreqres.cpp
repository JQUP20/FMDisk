#include "IHttpReqRes.h"
#include "Utils/commonFun.h"
//#include "Utils/appConfig.h"
#include <QHttpMultiPart>
#include <QApplication>
#include "Log/logging.h"
#include <QDebug>
#include "LoginWindow/logininfoinstance.h"

IHttpReqRes::IHttpReqRes(QObject *parent)
    : QObject(parent)
    , m_nReconnectTimes(0)
    , m_nOverTimeLen(10)
    , m_bOverTime(false)
    , m_file(NULL)
{
    m_sUrlAddress = commonFun::getRequestUrl();
    for (int i = 0; i < 5; ++i)
    {
        m_fileGroup[i] = NULL;
    }
    initConnect();
}

IHttpReqRes::~IHttpReqRes()
{

}

void IHttpReqRes::setNetManager(QNetworkAccessManager* pManager)
{
    pManager->setNetworkAccessible(QNetworkAccessManager::Accessible);
    m_pManager = pManager;
}

void IHttpReqRes::setReqParams(QByteArray byArr)
{
    byArr.replace("+", "%2B");
    byArr.replace("#", "%23");
    m_reqParams = byArr;
}

void IHttpReqRes::setFilePath(QString filePath)
{
    m_filePath = filePath;
}

void IHttpReqRes::setUploadFileInfo(QString user, QString filename, QString md5, qint64 size)
{
    qDebug() << "IHttpReqRes::setUploadFileInfo";
    m_user = user;
    m_fileName = filename;
    m_md5 = md5;
    m_size = size;
}

void IHttpReqRes::setUploadProgress(DataProgress *dataProgress)
{
    qDebug() << "IHttpReqRes::setUploadProgress";
//    m_dataProgress = dataProgress;
}

void IHttpReqRes::postRequest()
{
    QNetworkRequest request;
//    QSslConfiguration config;
//    config.setPeerVerifyMode(QSslSocket::VerifyNone);
//    config.setProtocol(QSsl::TlsV1SslV3);
//    request.setSslConfiguration(config);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    Log::Info("Address : %s", m_sUrlAddress.toStdString().c_str());
    request.setUrl(QUrl(m_sUrlAddress));
    // 请求头信息
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("application/json"));
    request.setHeader(QNetworkRequest::ContentLengthHeader, QVariant(m_reqParams.size()));

    m_pReply = m_pManager->post(request, m_reqParams);
    Log::Info("post url : %s -- post data : %s", m_sUrlAddress.toStdString().c_str(), m_reqParams.toStdString().c_str());

    connect(m_pReply, SIGNAL(finished()), this, SLOT(slot_ReplyFinished()));

    // 接收服务器发回的http响应消息
//    connect(m_pReply, &QNetworkReply::readyRead, [=]()
//    {
//        Log::Info("finished");
//        // 出错了
//        if (m_pReply->error() != QNetworkReply::NoError)
//        {
//           Log::Error("%s", m_pReply->errorString().toStdString().c_str());
//            //释放资源
//            m_pReply->deleteLater();
//            return;
//        }

//        // 将server回写的数据读出
//        QByteArray json = m_pReply->readAll();
//        /*
//            登陆 - 服务器回写的json数据包格式：
//                成功：{"code":"000"}
//                失败：{"code":"001"}
//        */
//        Log::Info("server return value: %s", json.toStdString().c_str());

//       // m_pReply->deleteLater(); //释放资源s
//    });


    m_bOverTime = false;
    if (!m_overTimer.isActive())
    {
        m_overTimer.start(m_nOverTimeLen * 1000);
    }
}

void IHttpReqRes::postFaceTection()
{
    QNetworkRequest request;
    QSslConfiguration config;
    config.setPeerVerifyMode(QSslSocket::VerifyNone);
    config.setProtocol(QSsl::TlsV1SslV3);
    request.setSslConfiguration(config);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    QString value = QString("form-data; name=\"file\"; filename=\"%1\"").arg(commonFun::getImageFileName(m_filePath));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant(value));
    m_file = new QFile(m_filePath);
    m_file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(m_file);
    m_file->setParent(multiPart);
    multiPart->append(imagePart);


    request.setUrl(QUrl(m_sUrlAddress));
    m_pReply = m_pManager->post(request, multiPart);
    connect(m_pReply, SIGNAL(finished()), this, SLOT(slot_ReplyFinished()));
    m_sTestUrl = request.url().toString().append(m_reqParams); // 测试用
    if (!m_sTestUrl.isEmpty())
    {
        //AppConfigHandler.Info(m_sTestUrl.toStdString());
        Log::Info("%s", m_sTestUrl.toStdString().c_str());
    }

    m_bOverTime = false;
    if (!m_overTimer.isActive())
    {
        m_overTimer.start(m_nOverTimeLen * 1000);
    }
}

void IHttpReqRes::postFaceData(QString sIdCard, QString sName)
{

}

void IHttpReqRes::postUpload(UploadFileInfo *uploadFileInfo)
{
    qDebug() << "postUpload uploadFileInfo : " << uploadFileInfo->fileName;

    QNetworkRequest request;

    QHttpPart imagePart;
    QString disp = QString("form-data; user=\"%1\"; filename=\"%2\"; md5=\"%3\"; size=%4")
            .arg(m_user).arg(m_fileName).arg(m_md5).arg(m_size);
    qDebug() << "disp : " << disp;
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader, disp);
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, "image/jpeg");
    imagePart.setBodyDevice(uploadFileInfo->file);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType, this);
    multiPart->append(imagePart);

    request.setUrl(QUrl(m_sUrlAddress));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "multipart/form-data");
    qDebug() << "m_sUrlAddress : " << m_sUrlAddress;
    m_pReply = m_pManager->post(request, multiPart);
    connect(m_pReply, SIGNAL(finished()), this, SLOT(slot_ReplyFinished()));
    // 有可用数据更新时
//    connect(m_pReply, &QNetworkReply::uploadProgress, [=](qint64 bytesRead, qint64 totalBytes)
//    {
//        if(totalBytes != 0) //这个条件很重要
//        {
//            //cout << bytesRead/1024 << ", " << totalBytes/1024;
//            m_dataProgress->setProgress(bytesRead/1024, totalBytes/1024); //设置进度条
//        }
//    });

}

QString IHttpReqRes::getTestUrl()
{
    return m_sTestUrl;
}

void IHttpReqRes::setOverTimeLengh(int nOverTimeLengh)
{
    m_nOverTimeLen = nOverTimeLengh;
}

bool IHttpReqRes::isOverTime()
{
    return m_bOverTime;
}

void IHttpReqRes::setReqUrlAddress(QString urlAddress)
{
    m_sUrlAddress = urlAddress;
}

void IHttpReqRes::slot_ReplyFinished()
{
    qDebug() << "IHttpReqRes::slot_ReplyFinished()";
    m_bOverTime = false;
    m_overTimer.stop();

    if (m_file != NULL)
    {
        m_file->close();
        m_file->deleteLater();
        m_file = NULL;
    }

    for (int i = 0; i < 5; ++i)
    {
        if (m_fileGroup[i] != NULL)
        {
            m_fileGroup[i]->close();
            m_fileGroup[i]->deleteLater();
            m_fileGroup[i] = NULL;
        }
    }

    QTextCodec *codec = QTextCodec::codecForName("utf8");

    QNetworkReply::NetworkError err = m_pReply->error();

    if (err != QNetworkReply::NoError)
    {
        //AppConfigHandler.Info(QStringLiteral("网络异常: %1; errorCod:%2; errorMsg:%3").arg(m_sTestUrl).arg(err).arg(m_pReply->errorString()).toStdString());
        Log::Info("网络异常: %s; errorCod: %d; errorMsg: %s", m_sTestUrl.toStdString().c_str(), err, m_pReply->errorString().toStdString().c_str());
        processError();
    }
    else
    {
        m_nReconnectTimes = 0;
       // QString strResult = codec->toUnicode(m_pReply->readAll());
        QByteArray strResult = m_pReply->readAll();
        m_pReply->deleteLater();
        m_pReply = NULL;
        qDebug() << "result : " << strResult;


        processResponse(strResult);
    }
}

void IHttpReqRes::slot_overTimeout()
{
    m_bOverTime = true;
    //AppConfigHandler.Info(QStringLiteral("网络超时：%1").arg(m_sTestUrl).toStdString());
    Log::Info("网络超时：%s", m_sTestUrl.toStdString().c_str());
    processError();
}

void IHttpReqRes::initConnect()
{
    connect(&m_overTimer, SIGNAL(timeout()), this, SLOT(slot_overTimeout()));
}
