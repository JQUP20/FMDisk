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

    // �˴�����ָ��������
    m_mainWin = new MainWindow;

    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle(QStringLiteral("��¼"));

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
    // ȥ���߿�
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    // ���õ�ǰ���ڵ�������Ϣ
    this->setFont(QFont("������", 12, QFont::Bold, false));
    // ����
    ui->log_pwd->setEchoMode(QLineEdit::Password);
    ui->reg_pwd->setEchoMode(QLineEdit::Password);
    ui->reg_surepwd->setEchoMode(QLineEdit::Password);
    // ��ǰ��ʾ�Ĵ���
    ui->stackedWidget->setCurrentIndex(0);
    ui->log_usr->setFocus();
    // ���ݵĸ�ʽ��ʾ
    ui->log_usr->setToolTip("�Ϸ��ַ�:[a-z|A-Z|#|@|0-9|-|_|*],�ַ�����: 3~16");
    ui->reg_usr->setToolTip("�Ϸ��ַ�:[a-z|A-Z|#|@|0-9|-|_|*],�ַ�����: 3~16");
    ui->reg_nickname->setToolTip("�Ϸ��ַ�:[a-z|A-Z|#|@|0-9|-|_|*],�ַ�����: 3~16");
    ui->log_pwd->setToolTip("�Ϸ��ַ�:[a-z|A-Z|#|@|0-9|-|_|*],�ַ�����: 6~18");
    ui->reg_pwd->setToolTip("�Ϸ��ַ�:[a-z|A-Z|#|@|0-9|-|_|*],�ַ�����: 6~18");
    ui->reg_surepwd->setToolTip("�Ϸ��ַ�:[a-z|A-Z|#|@|0-9|-|_|*],�ַ�����: 6~18");
    // ��ȡ�����ļ���Ϣ������ʼ��
    readCfg();
    // ����ͼƬ��Ϣ - ��ʾ�ļ��б��ʱ���ã��ڴ˳�ʼ��
    m_cm.getFileTypeList();

#if 1
    // ��������
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

    // ע��
    connect(ui->log_register_btn, &QToolButton::clicked, [=]()
    {
        // �л���ע�����
        ui->stackedWidget->setCurrentWidget(ui->register_page);
        ui->reg_usr->setFocus();
    });
    // ���ð�ť
    connect(ui->title_widget, &TitleWidget::showSetWidget, [=]()
    {
        // �л������ý���
        ui->stackedWidget->setCurrentWidget(ui->set_page);
        ui->address_server->setFocus();
    });
    // �رհ�ť
    connect(ui->title_widget, &TitleWidget::closeWindow, [=]()
    {
        // �����ע�ᴰ��
        if(ui->stackedWidget->currentWidget() == ui->register_page)
        {
            // �������
            ui->reg_mail->clear();
            ui->reg_usr->clear();
            ui->reg_nickname->clear();
            ui->reg_pwd->clear();
            ui->reg_surepwd->clear();
            ui->reg_phone->clear();
            // �����л�
            ui->stackedWidget->setCurrentWidget(ui->login_page);
            ui->log_usr->setFocus();
        }
        // ��������ô���
        else if(ui->stackedWidget->currentWidget() == ui->set_page)
        {
            // �������
            ui->address_server->clear();
            ui->port_server->clear();
            // �����л�
            ui->stackedWidget->setCurrentWidget(ui->login_page);
            ui->log_usr->setFocus();
        }
        // ����ǵ�¼����
        else if(ui->stackedWidget->currentWidget() == ui->login_page)
        {
            close();
        }
    });
    // �л��û� - ���µ�¼
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
        QMessageBox::warning(this, tr("ע���쳣"), tr("ע���쳣������"));

    /*
    ע�� - server�˷��ص�json��ʽ���ݣ�
        �ɹ�:         {"code":"002"}
        ���û��Ѵ��ڣ�  {"code":"003"}
        ʧ��:         {"code":"004"}
    */
    // �ж�״̬��
    if("002" == nCode)
    {
        //ע��ɹ�
        QMessageBox::information(this, "ע��ɹ�", "ע��ɹ������¼");

        //����б༭����
        ui->reg_usr->clear();
        ui->reg_nickname->clear();
        ui->reg_pwd->clear();
        ui->reg_surepwd->clear();
        ui->reg_phone->clear();
        ui->reg_mail->clear();

        //���õ�½���ڵĵ�½��Ϣ
        ui->log_usr->setText(m_registerInfo.user);
        ui->log_pwd->setText(m_registerInfo.firstPassWd);
        ui->rember_pwd->setChecked(true);

        //�л�����¼����
        ui->stackedWidget->setCurrentWidget(ui->login_page);
    }
    else if("003" == nCode)
    {
        QMessageBox::warning(this, "ע��ʧ��", QString("[%1]���û��Ѿ�����!!!").arg(m_registerInfo.user));
    }
    else if("004" == nCode)
    {
        QMessageBox::warning(this, "ע��ʧ��", "ע��ʧ�ܣ�����");
    }
}

void Login::slotOnLogin()
{
    qDebug() << "start login..";
    // ��ȡ�û���¼��Ϣ
    m_user = ui->log_usr->text();
    m_passWd = ui->log_pwd->text();
    m_ip = ui->address_server->text();
    m_port = ui->port_server->text();

#if 0
    // ����У��
    QRegExp regexp(USER_REG);
    if(!regexp.exactMatch(user))
    {
        QMessageBox::warning(this, "����", "�û�����ʽ����ȷ");
        ui->log_usr->clear();
        ui->log_usr->setFocus();
        return;
    }
    regexp.setPattern(PASSWD_REG);
    if(!regexp.exactMatch(pwd))
    {
        QMessageBox::warning(this, "����", "�����ʽ����ȷ");
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
        QMessageBox::warning(this, "��¼ʧ��", "�û��������벻��ȷ������");
    }
    else
    {
        Log::Info("login success");

        // ���õ�½��Ϣ����ʾ�ļ��б������Ҫʹ����Щ��Ϣ
        LoginInfoInstance *p = LoginInfoInstance::getInstance(); //��ȡ����
        p->setLoginInfo(m_user, m_ip, m_port, sToken);


        // ��ǰ��������
        this->hide();
        // �����洰����ʾ
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
    // ����У��
    QRegExp regexp(USER_REG);
    if(!regexp.exactMatch(userName))
    {
        QMessageBox::warning(this, "����", "�û�����ʽ����ȷ");
        ui->reg_usr->clear();
        ui->reg_usr->setFocus();
        return;
    }
    if(!regexp.exactMatch(nickName))
    {
        QMessageBox::warning(this, "����", "�ǳƸ�ʽ����ȷ");
        ui->reg_nickname->clear();
        ui->reg_nickname->setFocus();
        return;
    }
    regexp.setPattern(PASSWD_REG);
    if(!regexp.exactMatch(firstPwd))
    {
        QMessageBox::warning(this, "����", "�����ʽ����ȷ");
        ui->reg_pwd->clear();
        ui->reg_pwd->setFocus();
        return;
    }
    if(surePwd != firstPwd)
    {
        QMessageBox::warning(this, "����", "������������벻ƥ��, ����������");
        ui->reg_surepwd->clear();
        ui->reg_surepwd->setFocus();
        return;
    }
    regexp.setPattern(PHONE_REG);
    if(!regexp.exactMatch(phone))
    {
        QMessageBox::warning(this, "����", "�ֻ������ʽ����ȷ");
        ui->reg_phone->clear();
        ui->reg_phone->setFocus();
        return;
    }
    regexp.setPattern(EMAIL_REG);
    if(!regexp.exactMatch(email))
    {
        QMessageBox::warning(this, "����", "�������ʽ����ȷ");
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

    // �����ж�
    // ������IP
    // \\d �� \\. �е�һ��\��ת���ַ�, ����ʹ�õ��Ǳ�׼����
//    QRegExp regexp(IP_REG);
//    if(!regexp.exactMatch(ip))
//    {
//        QMessageBox::warning(this, "����", "�������IP��ʽ����ȷ, ����������!");
//        return;
//    }
//    // �˿ں�
//    regexp.setPattern(PORT_REG);
//    if(!regexp.exactMatch(port))
//    {
//        QMessageBox::warning(this, "����", "������Ķ˿ڸ�ʽ����ȷ, ����������!");
//        return;
//    }
    // ��ת����½����
    ui->stackedWidget->setCurrentWidget(ui->login_page);
    // ��������Ϣд�������ļ���
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

    if(remeber == "yes")//��ס����
    {
        //�������
        unsigned char encPwd[512] = {0};
        int encPwdLen = 0;
        //toLocal8Bit(), ת��Ϊ�����ַ�����Ĭ��windows��Ϊgbk���룬linuxΪutf-8����
        QByteArray tmp = QByteArray::fromBase64( pwd.toLocal8Bit());
        ret = DesDec( (unsigned char *)tmp.data(), tmp.size(), encPwd, &encPwdLen);
        if(ret != 0)
        {
            cout << "DesDec";
            return;
        }

    #ifdef _WIN32 //�����windowsƽ̨
        //fromLocal8Bit(), �����ַ���ת��Ϊutf-8
        ui->log_pwd->setText( QString::fromLocal8Bit( (const char *)encPwd, encPwdLen ) );
    #else //����ƽ̨
        ui->log_pwd->setText( (const char *)encPwd );
    #endif

        ui->rember_pwd->setChecked(true);

    }
    else //û�м�ס����
    {
        ui->log_pwd->setText("");
        ui->rember_pwd->setChecked(false);
    }

    //�û�����
    unsigned char encUsr[512] = {0};
    int encUsrLen = 0;
    //toLocal8Bit(), ת��Ϊ�����ַ��������windows��Ϊgbk���룬���linux��Ϊutf-8����
    QByteArray tmp = QByteArray::fromBase64( user.toLocal8Bit());
    ret = DesDec( (unsigned char *)tmp.data(), tmp.size(), encUsr, &encUsrLen);
    if(ret != 0)
    {
        cout << "DesDec";
        return;
    }

    #ifdef _WIN32 //�����windowsƽ̨
        //fromLocal8Bit(), �����ַ���ת��Ϊutf-8
        ui->log_usr->setText( QString::fromLocal8Bit( (const char *)encUsr, encUsrLen ) );
    #else //����ƽ̨
        ui->log_usr->setText( (const char *)encUsr );
    #endif

    QString ip = m_cm.getCfgValue("web_server", "ip");
    QString port = m_cm.getCfgValue("web_server", "port");
    ui->address_server->setText(ip);
    ui->port_server->setText(port);
}

