#include "login.h"
#include "ui_login.h"

#include "Network/httpagent.h"

#include <QPainter>
#include <QMessageBox>
#include "Log/logging.h"

#include "logininfoinstance.h"
#include "Utils/des.h"

QNetworkAccessManager *manager = new QNetworkAccessManager();

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    // 此处无需指定父窗口
    m_mainWin = new MainWindow;

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle(QStringLiteral("登录"));

    init();
    initConnect();
}

Login::~Login()
{
    delete ui;
}

void Login::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pixmap(":/images/login_bk.jpg");
    painter.drawPixmap(0, 0, width(), height(), pixmap);
}

void Login::init()
{
    this->setWindowIcon(QIcon(":/images/logo.ico"));
    m_mainWin->setWindowIcon(QIcon(":/images/logo.ico"));
    // 去掉边框
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    // 设置当前窗口的字体信息
    this->setFont(QFont("新宋体", 12, QFont::Bold, false));
    // 密码
    ui->log_pwd->setEchoMode(QLineEdit::Password);
    ui->reg_pwd->setEchoMode(QLineEdit::Password);
    ui->reg_surepwd->setEchoMode(QLineEdit::Password);
    // 当前显示的窗口
    ui->stackedWidget->setCurrentIndex(0);
    ui->log_usr->setFocus();
    // 数据的格式提示
    ui->log_usr->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 3~16");
    ui->reg_usr->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 3~16");
    ui->reg_nickname->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 3~16");
    ui->log_pwd->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 6~18");
    ui->reg_pwd->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 6~18");
    ui->reg_surepwd->setToolTip("合法字符:[a-z|A-Z|#|@|0-9|-|_|*],字符个数: 6~18");
    // 读取配置文件信息，并初始化
    readCfg();
    // 加载图片信息 - 显示文件列表的时候用，在此初始化
    m_cm.getFileTypeList();

#if 1
    // 测试数据
    ui->reg_usr->setText("kevin_666");
    ui->reg_nickname->setText("kevin@666");
    ui->reg_pwd->setText("123456");
    ui->reg_surepwd->setText("123456");
    ui->reg_phone->setText("11111111111");
    ui->reg_mail->setText("abc@qq.com");

#endif
}

void Login::initConnect()
{
    connect(ui->login_btn, SIGNAL(clicked()), this, SLOT(slotOnLogin()));
    connect(ui->register_btn, SIGNAL(clicked()), this, SLOT(slotOnRegister()));
    connect(ui->set_ok_btn, SIGNAL(clicked(bool)), this, SLOT(slotOnServerSet()));

    connect(HttpAgent::instance(), SIGNAL(sigOnLogin(QString,QString)), this, SLOT(slotOnHandleLogin(QString,QString)));
    connect(HttpAgent::instance(), SIGNAL(RespondOnRegister(QString)), this, SLOT(ResponseOnRegister(QString)));
   // connect

    // 注册
    connect(ui->log_register_btn, &QToolButton::clicked, [=]()
    {
        // 切换到注册界面
        ui->stackedWidget->setCurrentWidget(ui->register_page);
        ui->reg_usr->setFocus();
    });
    // 设置按钮
    connect(ui->title_widget, &TitleWidget::showSetWidget, [=]()
    {
        // 切换到设置界面
        ui->stackedWidget->setCurrentWidget(ui->set_page);
        ui->address_server->setFocus();
    });
    // 关闭按钮
    connect(ui->title_widget, &TitleWidget::closeWindow, [=]()
    {
        // 如果是注册窗口
        if(ui->stackedWidget->currentWidget() == ui->register_page)
        {
            // 清空数据
            ui->reg_mail->clear();
            ui->reg_usr->clear();
            ui->reg_nickname->clear();
            ui->reg_pwd->clear();
            ui->reg_surepwd->clear();
            ui->reg_phone->clear();
            // 窗口切换
            ui->stackedWidget->setCurrentWidget(ui->login_page);
            ui->log_usr->setFocus();
        }
        // 如果是设置窗口
        else if(ui->stackedWidget->currentWidget() == ui->set_page)
        {
            // 清空数据
            ui->address_server->clear();
            ui->port_server->clear();
            // 窗口切换
            ui->stackedWidget->setCurrentWidget(ui->login_page);
            ui->log_usr->setFocus();
        }
        // 如果是登录窗口
        else if(ui->stackedWidget->currentWidget() == ui->login_page)
        {
            close();
        }
    });
    // 切换用户 - 重新登录
    connect(m_mainWin, &MainWindow::changeUser, [=]()
    {
        m_mainWin->hide();
        this->show();
    });
}

void Login::RespondOnOperatorLogin(QString nCode, QString nToken)
{

}

void Login::ResponseOnRegister(QString nCode)
{
    if (NULL == nCode)
        QMessageBox::warning(this, tr("注册异常"), tr("注册异常！！！"));

    /*
    注册 - server端返回的json格式数据：
        成功:         {"code":"002"}
        该用户已存在：  {"code":"003"}
        失败:         {"code":"004"}
    */
    // 判断状态码
    if("002" == nCode)
    {
        //注册成功
        QMessageBox::information(this, "注册成功", "注册成功，请登录");

        //清空行编辑内容
        ui->reg_usr->clear();
        ui->reg_nickname->clear();
        ui->reg_pwd->clear();
        ui->reg_surepwd->clear();
        ui->reg_phone->clear();
        ui->reg_mail->clear();

        //设置登陆窗口的登陆信息
        ui->log_usr->setText(m_registerInfo.user);
        ui->log_pwd->setText(m_registerInfo.firstPassWd);
        ui->rember_pwd->setChecked(true);

        //切换到登录界面
        ui->stackedWidget->setCurrentWidget(ui->login_page);
    }
    else if("003" == nCode)
    {
        QMessageBox::warning(this, "注册失败", QString("[%1]该用户已经存在!!!").arg(m_registerInfo.user));
    }
    else if("004" == nCode)
    {
        QMessageBox::warning(this, "注册失败", "注册失败！！！");
    }
}

void Login::slotOnLogin()
{
    qDebug() << "start login..";
    // 获取用户登录信息
    m_user = ui->log_usr->text();
    m_passWd = ui->log_pwd->text();
    m_ip = ui->address_server->text();
    m_port = ui->port_server->text();

#if 0
    // 数据校验
    QRegExp regexp(USER_REG);
    if(!regexp.exactMatch(user))
    {
        QMessageBox::warning(this, "警告", "用户名格式不正确");
        ui->log_usr->clear();
        ui->log_usr->setFocus();
        return;
    }
    regexp.setPattern(PASSWD_REG);
    if(!regexp.exactMatch(pwd))
    {
        QMessageBox::warning(this, "警告", "密码格式不正确");
        ui->log_pwd->clear();
        ui->log_pwd->setFocus();
        return;
    }
#endif

    m_cm.writeLoginInfo(m_user, m_passWd, ui->rember_pwd->isChecked());
    HttpAgent::instance()->RequestOnLogin(m_user, m_passWd);

}

void Login::slotOnHandleLogin(QString nCode, QString sToken)
{
    if (nCode != "000")
    {
        QMessageBox::warning(this, "登录失败", "用户名或密码不正确！！！");
    }
    else
    {
        Log::Info("login success");

        // 设置登陆信息，显示文件列表界面需要使用这些信息
        LoginInfoInstance *p = LoginInfoInstance::getInstance(); //获取单例
        p->setLoginInfo(m_user, m_ip, m_port, sToken);


        // 当前窗口隐藏
        this->hide();
        // 主界面窗口显示
        m_mainWin->showMainWindow();
    }
}

void Login::slotOnRegister()
{
    m_registerInfo.user = ui->reg_usr->text();
    m_registerInfo.nickName = ui->reg_usr->text();
    m_registerInfo.firstPassWd = ui->reg_pwd->text();
    m_registerInfo.ensurePassWd = ui->reg_surepwd->text();
    m_registerInfo.phone = ui->reg_phone->text();
    m_registerInfo.mail = ui->reg_mail->text();

#if 0
    // 数据校验
    QRegExp regexp(USER_REG);
    if(!regexp.exactMatch(userName))
    {
        QMessageBox::warning(this, "警告", "用户名格式不正确");
        ui->reg_usr->clear();
        ui->reg_usr->setFocus();
        return;
    }
    if(!regexp.exactMatch(nickName))
    {
        QMessageBox::warning(this, "警告", "昵称格式不正确");
        ui->reg_nickname->clear();
        ui->reg_nickname->setFocus();
        return;
    }
    regexp.setPattern(PASSWD_REG);
    if(!regexp.exactMatch(firstPwd))
    {
        QMessageBox::warning(this, "警告", "密码格式不正确");
        ui->reg_pwd->clear();
        ui->reg_pwd->setFocus();
        return;
    }
    if(surePwd != firstPwd)
    {
        QMessageBox::warning(this, "警告", "两次输入的密码不匹配, 请重新输入");
        ui->reg_surepwd->clear();
        ui->reg_surepwd->setFocus();
        return;
    }
    regexp.setPattern(PHONE_REG);
    if(!regexp.exactMatch(phone))
    {
        QMessageBox::warning(this, "警告", "手机号码格式不正确");
        ui->reg_phone->clear();
        ui->reg_phone->setFocus();
        return;
    }
    regexp.setPattern(EMAIL_REG);
    if(!regexp.exactMatch(email))
    {
        QMessageBox::warning(this, "警告", "邮箱码格式不正确");
        ui->reg_mail->clear();
        ui->reg_mail->setFocus();
        return;
    }
#endif



   HttpAgent::instance()->RequestOnRegister(m_registerInfo, m_interfaceHead);
}

void Login::slotOnHandleRegister(RegisterInfo info, InterfaceInputHead head)
{
    QString ip = ui->address_server->text();
    QString port = ui->port_server->text();

    // 数据判断
    // 服务器IP
    // \\d 和 \\. 中第一个\是转义字符, 这里使用的是标准正则
//    QRegExp regexp(IP_REG);
//    if(!regexp.exactMatch(ip))
//    {
//        QMessageBox::warning(this, "警告", "您输入的IP格式不正确, 请重新输入!");
//        return;
//    }
//    // 端口号
//    regexp.setPattern(PORT_REG);
//    if(!regexp.exactMatch(port))
//    {
//        QMessageBox::warning(this, "警告", "您输入的端口格式不正确, 请重新输入!");
//        return;
//    }
    // 跳转到登陆界面
    ui->stackedWidget->setCurrentWidget(ui->login_page);
    // 将配置信息写入配置文件中
    m_cm.writeWebInfo(ip, port);
}

void Login::slotOnServerSet()
{

}

void Login::readCfg()
{
    QString user = m_cm.getCfgValue("login", "user");
    QString pwd = m_cm.getCfgValue("login", "pwd");
    QString remeber = m_cm.getCfgValue("login", "remember");
    int ret = 0;

    if(remeber == "yes")//记住密码
    {
        //密码解密
        unsigned char encPwd[512] = {0};
        int encPwdLen = 0;
        //toLocal8Bit(), 转换为本地字符集，默认windows则为gbk编码，linux为utf-8编码
        QByteArray tmp = QByteArray::fromBase64( pwd.toLocal8Bit());
        ret = DesDec( (unsigned char *)tmp.data(), tmp.size(), encPwd, &encPwdLen);
        if(ret != 0)
        {
            cout << "DesDec";
            return;
        }

    #ifdef _WIN32 //如果是windows平台
        //fromLocal8Bit(), 本地字符集转换为utf-8
        ui->log_pwd->setText( QString::fromLocal8Bit( (const char *)encPwd, encPwdLen ) );
    #else //其它平台
        ui->log_pwd->setText( (const char *)encPwd );
    #endif

        ui->rember_pwd->setChecked(true);

    }
    else //没有记住密码
    {
        ui->log_pwd->setText("");
        ui->rember_pwd->setChecked(false);
    }

    //用户解密
    unsigned char encUsr[512] = {0};
    int encUsrLen = 0;
    //toLocal8Bit(), 转换为本地字符集，如果windows则为gbk编码，如果linux则为utf-8编码
    QByteArray tmp = QByteArray::fromBase64( user.toLocal8Bit());
    ret = DesDec( (unsigned char *)tmp.data(), tmp.size(), encUsr, &encUsrLen);
    if(ret != 0)
    {
        cout << "DesDec";
        return;
    }

    #ifdef _WIN32 //如果是windows平台
        //fromLocal8Bit(), 本地字符集转换为utf-8
        ui->log_usr->setText( QString::fromLocal8Bit( (const char *)encUsr, encUsrLen ) );
    #else //其它平台
        ui->log_usr->setText( (const char *)encUsr );
    #endif

    QString ip = m_cm.getCfgValue("web_server", "ip");
    QString port = m_cm.getCfgValue("web_server", "port");
    ui->address_server->setText(ip);
    ui->port_server->setText(port);
}

