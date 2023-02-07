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
    //经办人登录应答
    void RespondOnOperatorLogin(QString nCode, QString nToken);
    //
    void ResponseOnRegister(QString nCode);

    void slotOnLogin();
    void slotOnHandleLogin(QString nCode, QString sToken);

    void slotOnRegister();
    void slotOnHandleRegister(RegisterInfo info, InterfaceInputHead head);

    void slotOnServerSet();

private:
    // 读取配置信息，设置默认登录状态，默认设置信息
    void readCfg();

private:
    Ui::Login *ui;

    // 处理网络请求类对象
    QNetworkAccessManager* m_manager;

    QString m_user;   //当前登陆用户
    QString m_passWd;  //登陆密码
    QString m_ip;     //web服务器ip
    QString m_port;   //web服务器端口

    Common m_cm;
    MainWindow* m_mainWin;

    RegisterInfo m_registerInfo;
    InterfaceInputHead m_interfaceHead;
};

#endif // LOGIN_H
