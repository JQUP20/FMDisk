#include "logininfoinstance.h"

//static�������������main()�˳������
//��̬���ݳ�Ա���������������ⶨ��
LoginInfoInstance::Garbo LoginInfoInstance::tmp;

//��̬������̬����ռ�
//��̬���ݳ�Ա������������������붨��
LoginInfoInstance* LoginInfoInstance::instance = new LoginInfoInstance;

LoginInfoInstance::LoginInfoInstance()
{

}

LoginInfoInstance::~LoginInfoInstance()
{

}

//�Ѹ��ƹ��캯����=������Ҳ��Ϊ˽��,��ֹ������
LoginInfoInstance::LoginInfoInstance(const LoginInfoInstance& )
{
}

LoginInfoInstance& LoginInfoInstance::operator=(const LoginInfoInstance&)
{
    return *this;
}

//��ȡΨһ��ʵ��
LoginInfoInstance *LoginInfoInstance::getInstance()
{
    return instance;
}

//�ͷŶ����ռ�
void LoginInfoInstance::destroy()
{
    if(NULL != LoginInfoInstance::instance)
    {
        delete LoginInfoInstance::instance;
        LoginInfoInstance::instance = NULL;
       // cout << "instance is detele";
    }
}

//���õ�½��Ϣ
void LoginInfoInstance::setLoginInfo( QString tmpUser, QString tmpIp, QString tmpPort, QString token)
{
    m_user = tmpUser;
    m_ip = tmpIp;
    m_port = tmpPort;
    m_token = token;
}

//��ȡ��½�û�
QString LoginInfoInstance::getUser() const
{
    qDebug() << "getUser";
    return m_user;
}

//��ȡ������ip
QString LoginInfoInstance::getIp() const
{
    return m_ip;
}

//��ȡ�������˿�
QString LoginInfoInstance::getPort() const
{
    return m_port;
}

//��ȡ��½token
QString LoginInfoInstance::getToken() const
{
    qDebug() << "getToken";
    return m_token;
}

