#include "httpclient.h"
#include "httplogin.h"
#include "httpregister.h"
#include "httpupload.h"
#include "httpuploadinreal.h"
#include "httprefreshfiles.h"
#include "httpgetuserfileslist.h"

#include <QDebug>

HttpClient* HttpClient::m_pInstance = NULL;

HttpClient *HttpClient::instance()
{
    if (m_pInstance == NULL)
    {
        m_pInstance = new HttpClient;
    }
    return m_pInstance;
}

HttpClient::HttpClient(QObject *parent)
    : QObject(parent)
{
    m_pManager = new QNetworkAccessManager();
}

HttpClient::~HttpClient()
{

}

void HttpClient::setToken(QString sToken)
{
    m_sToken = sToken;
}

void HttpClient::RequestOnLogin(QString nUser, QString nPasswd)
{
    HttpLogin *p = new HttpLogin(nUser, nPasswd);
    p->setNetManager(m_pManager);
    p->postRequest();
}

void HttpClient::RequestOnRegister(RegisterInfo registerInfo, InterfaceInputHead header)
{
    HttpRegister *p = new HttpRegister(registerInfo, header);
    p->setNetManager(m_pManager);
    p->postRequest();
}

void HttpClient::RequestOnUpload(UploadFileInfo *uploadFileInfo, LoginInfoInstance *login)
{
    HttpUpload *p = new HttpUpload(uploadFileInfo, login);
    p->setNetManager(m_pManager);
    p->postRequest();
}

void HttpClient::RequestOnUploadInReal(UploadFileInfo *uploadFileInfo, LoginInfoInstance *login)
{
    HttpUploadInReal *p = new HttpUploadInReal(uploadFileInfo, login);
    p->setNetManager(m_pManager);
    p->postUpload(uploadFileInfo);
}

void HttpClient::RequestOnRefreshFiles(LoginInfoInstance *loginInfoInstance)
{
    qDebug() << "httpclient request refresh";
    HttpRefreshFiles *p = new HttpRefreshFiles(loginInfoInstance);
    p->setNetManager(m_pManager);
    p->postRequest();
}

void HttpClient::RequestOnGetUserFilesList(LoginInfoInstance *loginInfoInstance, qint32 start, qint32 count, Display cmd)
{
    HttpGetUserFilesList *p = new HttpGetUserFilesList(loginInfoInstance, start, count, cmd);
    p->setNetManager(m_pManager);
    p->postRequest();
}

