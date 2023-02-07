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

    // ���õ�½�û���Ϣ��json��
    QByteArray setLoginJson(QString nUser, QString nPasswd);

    // �õ��������ظ��ĵ�½״̬�� ״̬�뷵��ֵΪ "000", �� "001"�����е�½section
    QStringList getLoginStatus(QByteArray json);

protected:
    void processResponse(QByteArray strResult);
    void processError();
private:
    int m_loginType;
   // Common m_cm;
};

#endif // HTTPLOGIN_H
