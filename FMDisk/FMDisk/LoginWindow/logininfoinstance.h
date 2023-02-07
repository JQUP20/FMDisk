#ifndef LOGININFOINSTANCE_H
#define LOGININFOINSTANCE_H

#include <QString>
#include "Utils/common.h"


//����ģʽ����Ҫ���浱ǰ��½�û�����������Ϣ
class LoginInfoInstance
{
public:
     static LoginInfoInstance *getInstance(); //��֤Ψһһ��ʵ��
     static void destroy(); //�ͷŶ����ռ�

     void setLoginInfo( QString tmpUser, QString tmpIp, QString tmpPort,  QString token="");//���õ�½��Ϣ
     QString getUser() const;   //��ȡ��½�û�
     QString getIp() const;     //��ȡ������ip
     QString getPort() const;   //��ȡ�������˿�
     QString getToken() const;  //��ȡ��½token

private:
    //�������������Ϊ˽�е�
    LoginInfoInstance();
    ~LoginInfoInstance();
    //�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
    LoginInfoInstance(const LoginInfoInstance&);
    LoginInfoInstance& operator=(const LoginInfoInstance&);

    //����Ψһ��������������������ɾ��Singleton��ʵ��
    class Garbo
    {
    public:
        ~Garbo()
        {
            //�ͷŶ����ռ�
            LoginInfoInstance::destroy();
        }
    };

    //����һ����̬��Ա�������������ʱ��ϵͳ���Զ�����������������
    //static�������������main()�˳������
    static Garbo tmp; //��̬���ݳ�Ա���������������ⶨ��


    //��̬���ݳ�Ա������������������붨��
    static LoginInfoInstance *instance;


    QString m_user;   //��ǰ��½�û�
    QString m_token;  //��½token
    QString m_ip;     //web������ip
    QString m_port;   //web�������˿�
};

#endif // LOGININFOINSTANCE_H
