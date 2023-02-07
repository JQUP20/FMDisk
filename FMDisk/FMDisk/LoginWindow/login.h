#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <mainwindow.h>
#include "Utils/Common.h"
#include "Utils/HttpStructData.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

protected:
    void paintEvent(QPaintEvent * );

private:
    void init();
    void initConnect();

private slots:
    //�����˵�¼Ӧ��
    void RespondOnOperatorLogin(QString nCode, QString nToken);
    //
    void ResponseOnRegister(QString nCode);

    void slotOnLogin();
    void slotOnHandleLogin(QString nCode, QString sToken);

    void slotOnRegister();
    void slotOnHandleRegister(RegisterInfo info, InterfaceInputHead head);

    void slotOnServerSet();

private:
    // ��ȡ������Ϣ������Ĭ�ϵ�¼״̬��Ĭ��������Ϣ
    void readCfg();

private:
    Ui::Login *ui;

    // �����������������
    QNetworkAccessManager* m_manager;

    QString m_user;   //��ǰ��½�û�
    QString m_passWd;  //��½����
    QString m_ip;     //web������ip
    QString m_port;   //web�������˿�

    Common m_cm;
    MainWindow* m_mainWin;

    RegisterInfo m_registerInfo;
    InterfaceInputHead m_interfaceHead;
};

#endif // LOGIN_H
