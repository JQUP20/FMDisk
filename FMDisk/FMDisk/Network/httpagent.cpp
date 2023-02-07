#include "HttpAgent.h"
#include "Utils/ThreadManager.h"
#include "HttpClient.h"
#include "httpsignal.h"

HttpAgent* HttpAgent::m_pInstance = NULL;

HttpAgent *HttpAgent::instance()
{
    if (m_pInstance == NULL)
    {
        m_pInstance = new HttpAgent;
    }
    return m_pInstance;
}

void HttpAgent::RequestOnLogin(QString nUser, QString nPasswd)
{
    HttpClient::instance()->RequestOnLogin(nUser, nPasswd);
}

void HttpAgent::RequestOnRegister(RegisterInfo registerInfo, InterfaceInputHead header)
{
    HttpClient::instance()->RequestOnRegister(registerInfo, header);
}

void HttpAgent::RequestOnUpload(UploadFileInfo *uploadFileInfo, LoginInfoInstance *loginInfoInstance)
{
    HttpClient::instance()->RequestOnUpload(uploadFileInfo, loginInfoInstance);
}

void HttpAgent::RequestOnUploadInReal(UploadFileInfo *uploadFileInfo, LoginInfoInstance *loginInfoInstance)
{
    HttpClient::instance()->RequestOnUploadInReal(uploadFileInfo, loginInfoInstance);
}

void HttpAgent::RequestOnDownload(DownloadFileInfo downloadFileInfo)
{

}

void HttpAgent::RequestOnRefreshFiles(LoginInfoInstance *loginInfoInstance)
{
    HttpClient::instance()->RequestOnRefreshFiles(loginInfoInstance);
}

void HttpAgent::RequestOnGetUserFilesList(LoginInfoInstance *loginInfoInstance, qint32 start, qint32 count, Display cmd)
{
    HttpClient::instance()->RequestOnGetUserFilesList(loginInfoInstance, start, count, cmd);
}

HttpAgent::HttpAgent(QObject *parent)
    : QObject(parent)
{
    initConnect();
    moveToThread(ThreadManager::getAgentThread());
    ThreadManager::getAgentThread()->start();
}

HttpAgent::~HttpAgent()
{

}

void HttpAgent::initConnect()
{
    connect(HttpSignal::instance(), SIGNAL(sigOnLogin(QString, QString)), this, SIGNAL(sigOnLogin(QString, QString)));
    connect(HttpSignal::instance(), SIGNAL(ResponseOnRegister(QString)), this, SIGNAL(RespondOnRegister(QString)));
    connect(HttpSignal::instance(), SIGNAL(RespondOnUpload(QString)), this, SIGNAL(RespondOnUpload(QString)));
    connect(HttpSignal::instance(), SIGNAL(RespondOnUploadInReal(QString)), this, SIGNAL(RespondOnUploadInReal(QString)));
    connect(HttpSignal::instance(), SIGNAL(RespondRefreshFiles(QString,long)), this, SIGNAL(RespondOnRefreshFiles(QString, long)));
    connect(HttpSignal::instance(), SIGNAL(RespondOnGetUserFilesList(QString,QByteArray)), this, SIGNAL(RespondOnGetUserFilesList(QString,QByteArray)));
}

